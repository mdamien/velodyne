// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @version $Id: DbiteFile.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include <Pacpus/kernel/DbiteFile.h>
#include <Pacpus/kernel/DbiteException.h>
#include <Pacpus/kernel/DbiteFileTypes.h>
#include <Pacpus/kernel/Log.h>

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>

using namespace pacpus;
using namespace std;

// FIXME: record size is only 8-bit long!
typedef int8_t VariableDataSizeT;

DECLARE_STATIC_LOGGER("pacpus.core.DbiteFile");

namespace pacpus
{
  VariableDataSizeTag VariableDataSize;
  ReadModeTag ReadMode;
  WriteModeTag WriteMode;
  DiagnoseModeTag DiagnoseMode;
}

bool doesFileExist(const string & path);

DbiteFile::DbiteFile()
    : mIsWriting(false)
{
    setPath("");

    (void) ReadMode; // unused
    (void) WriteMode; // unused
    (void) VariableDataSize; // unused
    (void) DiagnoseMode; // unused
}

DbiteFile::~DbiteFile()
{
    if (isOpen()) {
        close();
    }
}

DbiteFile::operator string()
{
    static const int64_t kMicrosInSecond = 1000 * 1000;
    stringstream os;

    os << "Signature    : " << getSignature() << endl;
    os << "Version      : " << getVersion() << endl;
    os << "Header size  : " << getDataOffset() << " [bytes]" << endl;
    os << "Record size  : " << getRecordSize() << " [bytes]" << endl;
    os << "Data type    : " << getType() << endl;
    os << "Time min.    : " << getTimeMin() << endl;
    os << "Time max.    : " << getTimeMax() << endl;
    os << "Duration     : " << (getTimeMax() - getTimeMin()) / kMicrosInSecond << " [seconds]" << endl;
    os << "File size    : " << getFileSize() << " [bytes]" << endl;
    os << "Record count : " << getRecordCount() << endl;

    return os.str();
}

const string & DbiteFile::getPath() const
{
    return mPath;
}

void DbiteFile::setPath(const string & path)
{
    mPath = path;
}

void DbiteFile::open(const string & path, ReadModeTag)
{
    mIsWriting = false;
    if (isOpen()) {
        LOG_DEBUG("file is already open, closing...");
        close();
    }

    setPath(path);

    mFile.open(getPath().c_str(), ios_base::binary | ios_base::in);
    try {
        checkFileOpen();
    } catch (DbiteException & e) {
        LOG_ERROR("Dbite exception: " << e.what());
        close();
        throw DbiteException("cannot open file for reading");
    }

    try {
        readHeader();
    } catch (DbiteException & e) {
        LOG_ERROR("Dbite exception: " << e.what());
        // TODO: readAndDiagnoseHeader();
        close();
        throw DbiteException("cannot read header");
    }
    verifyHeader();
    goToDataBegin();
}

void DbiteFile::open(const string & path, WriteModeTag)
{
    openWriteMode(path);
}

void DbiteFile::open(const string & path, WriteModeTag, hdfile_header_t::DataTypeT type, hdfile_header_t::DataSizeT dataSize)
{
    openWriteMode(path, type);
    setRecordSize(dataSize);
}

void DbiteFile::open(const string & path, WriteModeTag, hdfile_header_t::DataTypeT type, VariableDataSizeTag tag)
{
    openWriteMode(path, type);
    setRecordSize(tag);
}

void DbiteFile::openWriteMode(const string & path, hdfile_header_t::DataTypeT type)
{
    openWriteMode(path);
    setType(type);
}

void DbiteFile::openWriteMode(const string & path)
{
    mIsWriting = true;
    if (isOpen()) {
        LOG_DEBUG("file is already open, closing...");
        close();
    }

    setPath(path);
    bool fileExists = doesFileExist(path);
    ios_base::openmode openmode;
    if (fileExists) {
        openmode = ios_base::binary | ios_base::in | ios_base::out;
    } else {
        openmode = ios_base::binary | ios_base::out;
    }
    mFile.open(getPath().c_str(), openmode);
    if (!isOpen()) {
        LOG_ERROR("cannot open file for writing");
        throw DbiteException("cannot open file for writing");
    }

    if (fileExists) {
        // file exists
        LOG_DEBUG("file already exists, appending");
        try {
            readHeader();
            // TODO: check if same type and record size
        } catch (DbiteException & e) {
            LOG_ERROR("Dbite exception: " << e.what());
            // TODO: readAndDiagnoseHeader();
            close();
            throw DbiteException("cannot read header");
        }
    } else {
        // file does not exist
        initializeHeader();
        writeHeader();
    }
    //goToDataBegin();
    goToFileEnd();
}

void DbiteFile::initializeHeader()
{
    setSignature();
    setType(FILE_DBT_UNKNOWN);
    setVersion(VERSION_NUMBER);
    setDataOffset(sizeof(hdfile_header_t));
    setRecordSize(0);
    // same as header size
    setFileSize(getDataOffset());
    setTimeMin(numeric_limits<road_time_t>::max());
    setTimeMax(numeric_limits<road_time_t>::min());
    setRecordCount(0);
}

void DbiteFile::close()
{
    if (!isOpen()) {
        LOG_WARN("file is not open");
        return;
    }
    closeDbite();
    setPath("");
}

void DbiteFile::closeDbite()
{
    if (mIsWriting) {
        try {
            writeHeader();
        } catch (DbiteException & e) {
            LOG_ERROR("cannot write header on close: " << e.what());
        }
    }
    mFile.close();
}

bool DbiteFile::isOpen() const
{
    return mFile.is_open();
}

void DbiteFile::goToFileBegin()
{
    LOG_DEBUG("goToFileBegin()");
    mFile.clear();
    setReadPosition(0);
    setWritePosition(0);
}

void DbiteFile::goToDataBegin()
{
    LOG_DEBUG("goToDataBegin()");
    LOG_TRACE("getDataOffset() = " << getDataOffset());
    mFile.clear();
    setReadPosition(getDataOffset());
    setWritePosition(getDataOffset());
}

void DbiteFile::goToFileEnd()
{
    LOG_TRACE("goToFileEnd()");
    LOG_TRACE("getFileSize() = " << getFileSize());
    mFile.clear();
    // do not use fstream::seekg/seekp(0, ios_base::end),
    // because in case of write failure,
    // we should write at position=getFileSize() which can be before the actual file end
    setReadPosition(getFileSize());
    setWritePosition(getFileSize());
}

int64_t DbiteFile::getReadPosition()
{
    checkFileOpen();
    return mFile.tellg();
}

int64_t DbiteFile::getWritePosition()
{
    checkFileOpen();
    return mFile.tellp();
}

void DbiteFile::setReadPosition(int64_t offset, ios_base::seekdir direction)
{
    LOG_TRACE("set read position = " << offset << " direction = " << direction);
    checkFileOpen();
    mFile.seekg(offset, direction);
    if (mFile.fail()) {
        LOG_ERROR("failed to set write position");
    }
}

void DbiteFile::setReadPosition(int64_t position)
{
    LOG_TRACE("set read position = " << position);
    checkFileOpen();
    mFile.seekg(position);
    if (mFile.fail()) {
        LOG_ERROR("failed to set read position");
    }
}

void DbiteFile::setWritePosition(int64_t offset, ios_base::seekdir direction)
{
    LOG_TRACE("set write position = " << offset << " direction = " << direction);
    checkFileOpen();
    mFile.seekp(offset, direction);
    if (mFile.fail()) {
        LOG_ERROR("failed to set write position");
    }
}

void DbiteFile::setWritePosition(int64_t position)
{
    LOG_TRACE("set write position = " << position);
    checkFileOpen();
    mFile.seekp(position);
    if (mFile.fail()) {
        LOG_ERROR("failed to set write position");
    }
}

const hdfile_header_t & DbiteFile::getHeader() const
{
    return mHeader;
}

hdfile_header_t & DbiteFile::header()
{
    return mHeader;
}

void DbiteFile::readHeader()
{
    goToFileBegin();
    checkFileOpen();
    read((char *)(&mHeader), sizeof(mHeader));
    LOG_DEBUG("file: " << getPath());
    LOG_TRACE("header read:\n" << string(*this));
}

void DbiteFile::verifyHeader()
{
    // verify file size
    const int64_t realFileSize = getRealFileSize();
    const hdfile_header_t::FileSizeT fileSize = getFileSize();
    if (realFileSize != fileSize) {
        LOG_WARN("real file size different than header information");
        LOG_INFO("real file size = " << realFileSize);
        LOG_INFO("file size = " << fileSize);
    }

    if (getVersion() != VERSION_NUMBER) {
        LOG_ERROR("bad version number");
        throw DbiteException("bad version number");
    }

    if (!isSignatureCorrect()) {
        LOG_ERROR("bad signature");
        throw DbiteException("bad signature");
    }

    LOG_DEBUG("header verified");
}

void DbiteFile::writeHeader()
{
    LOG_DEBUG("writing header:\n" << string(*this));

    goToFileBegin();

    LOG_DEBUG("begin position=" << getWritePosition());

    const size_t bytesToWrite = sizeof(mHeader);
    write((char *)(&mHeader), bytesToWrite);
    LOG_DEBUG("header written");

    LOG_DEBUG("final position=" << getWritePosition());
}

string DbiteFile::getSignature() const
{
    const char signature[] = { getHeader().Signature[0], getHeader().Signature[1], getHeader().Signature[2], getHeader().Signature[3], '\0' };
    return signature;
}

bool DbiteFile::isSignatureCorrect() const
{
    if ('R' != getHeader().Signature[0]) {
        return false;
    }
    if ('O' != getHeader().Signature[1]) {
        return false;
    }
    if ('A' != getHeader().Signature[2]) {
        return false;
    }
    if ('D' != getHeader().Signature[3]) {
        return false;
    }
    return true;
}

void DbiteFile::setSignature()
{
    header().Signature[0] = 'R';
    header().Signature[1] = 'O';
    header().Signature[2] = 'A';
    header().Signature[3] = 'D';
}

hdfile_header_t::DataTypeT DbiteFile::getType() const
{
    return getHeader().Type;
}

void DbiteFile::setType(hdfile_header_t::DataTypeT type)
{
    header().Type = type;
}

hdfile_header_t::VersionT DbiteFile::getVersion() const
{
    return getHeader().VersionNumber;
}

void DbiteFile::setVersion(hdfile_header_t::VersionT version)
{
    header().VersionNumber = version;
}

hdfile_header_t::DataOffsetT DbiteFile::getDataOffset() const
{
    return getHeader().DataOffset;
}

void DbiteFile::setDataOffset(hdfile_header_t::DataOffsetT dataOffset)
{
    header().DataOffset = dataOffset;
}

hdfile_header_t::DataSizeT DbiteFile::getRecordSize() const
{
    return getHeader().DataSize;
}

void DbiteFile::setRecordSize(hdfile_header_t::DataSizeT recordSize)
{
    header().DataSize = recordSize;
}

void DbiteFile::setRecordSize(VariableDataSizeTag)
{
    header().DataSize = hdfile_header_t::kVariableRecordSize;
}

hdfile_header_t::FileSizeT DbiteFile::getFileSize() const
{
    if (getHeader().FileSize < getHeader().DataOffset) {
        LOG_WARN("wrong header information: file size lesser than data offset");
    }
    return getHeader().FileSize;
}

void DbiteFile::setFileSize(hdfile_header_t::FileSizeT fileSize)
{
    header().FileSize = fileSize;
}

int64_t DbiteFile::getRealFileSize()
{
    checkFileOpen();

    mFile.clear();
    // save position
    int64_t oldReadPosition = getReadPosition();
    int64_t oldWritePosition = getWritePosition();

    // go to file end and get position = file size
    goToFileEnd();
    int64_t fileSize = mFile.tellg();

    // restore position
    setReadPosition(oldReadPosition);
    setWritePosition(oldWritePosition);
    return fileSize;
}

road_time_t DbiteFile::getTimeMin() const
{
    return getHeader().TimeMin;
}

void DbiteFile::setTimeMin(road_time_t time)
{
    header().TimeMin = time;
}

road_time_t DbiteFile::getTimeMax() const
{
    return getHeader().TimeMax;
}

void DbiteFile::setTimeMax(road_time_t time)
{
    header().TimeMax = time;
}

hdfile_header_t::RecordCountT DbiteFile::getRecordCount() const
{
    return getHeader().NbRecords;
}

void DbiteFile::setRecordCount(hdfile_header_t::RecordCountT recourdCount)
{
    header().NbRecords = recourdCount;
}

bool DbiteFile::isVariableDataSize() const
{
    return hdfile_header_t::kVariableRecordSize == getRecordSize();
}

bool DbiteFile::readRecord(size_t recordIndex, road_time_t & time, road_timerange_t & timeRange, char * data, size_t & dataSize)
{
    LOG_DEBUG("reading record no. " << recordIndex);

    if (isVariableDataSize()) {
        LOG_ERROR("cannot read nth record in a variable");
        throw DbiteException("cannot read nth record in a variable");
    }

    int64_t nthRecordPosition = getDataOffset() + recordIndex * (getRecordSize() + sizeof(road_time_t) + sizeof(road_timerange_t));
    LOG_DEBUG(recordIndex << "th record position = " << nthRecordPosition);
    if (getFileSize() < nthRecordPosition) {
        LOG_WARN("wanted to read past the file end");
        //throw DbiteException("wanted to read past the file end");
    }
    mFile.clear();
    setReadPosition(nthRecordPosition);

    return readRecord(time, timeRange, data, dataSize);
}

bool DbiteFile::readRecord(road_time_t & time, road_timerange_t & timeRange, char * buffer, size_t & bufferSize, const ReadDirection & direction)
{
    if (!buffer) {
        LOG_WARN("data buffer must be a non-NULL pointer");
        throw DbiteException("data buffer must be a non-NULL pointer");
    }

    return readRecordNoBufferCheck(time, timeRange, buffer, bufferSize, direction);
}

bool DbiteFile::readRecord(road_time_t & time, road_timerange_t & timeRange, char * buffer, const ReadDirection & direction)
{
    size_t bufferSize = getRecordSize();
    return readRecord(time, timeRange, buffer, bufferSize, direction);
}

bool DbiteFile::readRecord(road_time_t & time, road_timerange_t & timeRange, const ReadDirection & direction)
{
    size_t bufferSize = 0;
    return readRecordNoBufferCheck(time, timeRange, (char *) NULL, bufferSize, direction);
}

bool DbiteFile::readRecordNoBufferCheck(road_time_t & time, road_timerange_t & timeRange, char * buffer, size_t & bufferSize, const ReadDirection & direction)
{
    switch (direction) {
    case ReadForward:
        return readRecordForward(time, timeRange, buffer, bufferSize);
        break;

    case ReadBackward:
        return readRecordBackward(time, timeRange, buffer, bufferSize);
        break;

    default:
        assert(false && "wrong ReadDirection parameter");
        return false;
    }
}

bool DbiteFile::readRecordForward(road_time_t & time, road_timerange_t & timeRange, char * buffer, size_t & bufferSize)
{
    LOG_TRACE("reading record...");
    checkFileOpen();

    int64_t initialPosition = getReadPosition();
    LOG_TRACE("initial position    = " << initialPosition);

    ////////////////////////////////////////
    // read acquisition time
    mFile.read((char *)(&time), sizeof(time));
    if (!mFile) {
        if (isEndOfFile()) {
            bufferSize = 0;
            return false;
        }
        LOG_ERROR("cannot read acquisition time");
        throw DbiteException("cannot read acquisition time");
    }

    ////////////////////////////////////////
    // read acquisition time range
    read((char *)(&timeRange), sizeof(timeRange));

    ////////////////////////////////////////
    // get data and record size
    size_t dataSize = 0;
    size_t recordSize = sizeof(time) + sizeof(timeRange);
    if (isVariableDataSize()) {
        recordSize += 2 * sizeof(VariableDataSizeT);

        // read record size
        VariableDataSizeT readVarDataSize = 0;
        read((char *)(&readVarDataSize), sizeof(VariableDataSizeT));
        dataSize = static_cast<size_t>(readVarDataSize);
        LOG_DEBUG("variable record size = " << dataSize);
    } else {
        dataSize = getRecordSize();
    }
    recordSize += dataSize;

    ////////////////////////////////////////
    // read/skip data
    if (buffer) {
        if (bufferSize < dataSize) {
            LOG_WARN("buffer is smaller than the record size");
            LOG_INFO("buffer size = " << bufferSize);
            LOG_INFO("data   size = " << dataSize);
            throw DbiteException("buffer is smaller than the data size");
            // TODO: don't throw exception, but read only as much data as possible
        }

        // read data
        read(buffer, dataSize);

        if (isVariableDataSize()) {
            // read record size
            VariableDataSizeT readVarDataSize = 0;
            read((char *)(&readVarDataSize), sizeof(VariableDataSizeT));
            size_t varDataSize = static_cast<size_t>(readVarDataSize);
            LOG_TRACE("variable record size = " << varDataSize);

            if (dataSize != varDataSize) {
                LOG_WARN("corrupted data: data sizes differ");
                LOG_INFO("data size (before) = " << dataSize);
                LOG_INFO("data size (after)  = " << varDataSize);
            }
        }
    } else {
        // skip data
        setReadPosition(dataSize, ios_base::cur);
        if (isVariableDataSize()) {
            setReadPosition(dataSize, ios_base::cur);
        }
    }

    ////////////////////////////////////////
    // check how many bytes were read/skipped
    int64_t positionDifference = getReadPosition() - initialPosition;
    if (positionDifference != recordSize) {
        LOG_WARN("should be read   : " << recordSize << " [bytes]");
        LOG_WARN("was actually read: " << positionDifference << " [bytes]");
    }
    return true;
}

bool DbiteFile::readRecordBackward(road_time_t & time, road_timerange_t & timeRange, char * buffer, size_t & bufferSize)
{
    int64_t initialPosition = getReadPosition();
    LOG_TRACE("initial position    = " << initialPosition);

    size_t dataSize = 0;
    size_t recordSize = sizeof(time) + sizeof(timeRange);
    if (isVariableDataSize()) {
        recordSize += 2 * sizeof(VariableDataSizeT);

        // go back sizeof(VariableDataSizeT)
        setReadPosition(initialPosition - sizeof(VariableDataSizeT));

        // read VariableDataSizeT
        VariableDataSizeT readVarDataSize = 0;
        read((char *)(&readVarDataSize), sizeof(VariableDataSizeT));
        dataSize = static_cast<size_t>(readVarDataSize);
        LOG_DEBUG("variable record size = " << dataSize);
    } else {
        dataSize = getRecordSize();
    }
    // recordSize = sizeof(time) + sizeof(timeRange) + dataSize + [2 * sizeof(VariableDataSizeT)]
    recordSize += dataSize;

    // go back to the beginning of the previous record
    setReadPosition(initialPosition - recordSize);

    bool readResult = false;
    try {
        // read forward
        readResult = readRecordForward(time, timeRange, buffer, bufferSize);
    } catch (DbiteException & e) {
        setReadPosition(initialPosition);
        throw e;
    }

    // go back to the beginning of the previous record
    setReadPosition(initialPosition - recordSize);
    return readResult;
}

bool DbiteFile::writeRecord(const road_time_t & time, const road_timerange_t & timeRange, const char * data, const size_t dataSize)
{
    LOG_DEBUG("writing record:" << "\t"
              << "time=" << time << "\t"
              << "time range=" << timeRange << "\t"
              << "data size=" << dataSize);
    checkFileOpen();

    if (isVariableDataSize()) {
        if (dataSize > static_cast<size_t>(numeric_limits<VariableDataSizeT>::max())) {
            LOG_ERROR("variable data size too big");
            throw DbiteException("variable data size too big");
        }
    }

    int64_t initialPosition = getWritePosition();
    LOG_TRACE("getFileSize() = " << getFileSize());
    LOG_TRACE("getWritePosition() = " << getWritePosition());
    assert(initialPosition == getFileSize());

    size_t writtenBytes = 0;
    try {
        // write acquisition time, acquisition time range, data
        // if variable size, then write record size before and after data

        write((const char *)(&time), sizeof(time));
        writtenBytes += sizeof(time);

        write((const char *)(&timeRange), sizeof(timeRange));
        writtenBytes += sizeof(timeRange);

        if (isVariableDataSize()) {
            write((const char *)(&dataSize), sizeof(VariableDataSizeT));
            writtenBytes += sizeof(VariableDataSizeT);
        }
        write((const char *)(data), dataSize);
        writtenBytes += dataSize;

        if (isVariableDataSize()) {
            write((const char *)(&dataSize), sizeof(VariableDataSizeT));
            writtenBytes += sizeof(VariableDataSizeT);
        }
    } catch (DbiteException & e) {
        LOG_ERROR("Dbite exception: " << e.what());
        LOG_INFO("restoring initial write position");
        
        // on error, go back to record start
        setWritePosition(- (int64_t) writtenBytes, ios_base::cur);
        throw e;
    }
 
    // check how many bytes were written
    int64_t finalPosition = getWritePosition();
    int64_t positionDifference = finalPosition - initialPosition;
    LOG_TRACE("position difference = " << positionDifference);
    size_t totalRecordSize = dataSize + sizeof(time) + sizeof(timeRange);

    setFileSize(finalPosition);     // FIXME: possible loss of data, conversion int64_t -> FileSizeT
    setRecordCount(getRecordCount() + 1);
    setTimeMin(min(getTimeMin(), time));
    setTimeMax(max(getTimeMax(), time));

    if (positionDifference != totalRecordSize) {
        LOG_WARN("should be written   : " << totalRecordSize << " [bytes]");
        LOG_WARN("was actually written: " << positionDifference << " [bytes]");
    }
    return true;
}

void DbiteFile::read(fstream::char_type * s, streamsize n)
{
    mFile.read(s, n);
    if (!mFile) {
        LOG_ERROR("cannot read data");
        throw DbiteException("cannot read data");
    }
}

void DbiteFile::write(const fstream::char_type * s, streamsize n)
{
    mFile.write(s, n);
    if (!mFile) {
        LOG_ERROR("cannot write data");
        throw DbiteException("cannot write data");
    }
}

bool DbiteFile::isEndOfFile()
{
    return mFile.eof();
}

void DbiteFile::checkFileOpen()
{
    if (!isOpen()) {
        string errorMessage = "file is not open";
        LOG_WARN(errorMessage);
        throw DbiteException(errorMessage.c_str());
    }
}

bool doesFileExist(const string & path)
{
    bool fileExist = false;
    fstream f(path.c_str(), ios_base::in);
    if (f.good()) {
        fileExist = true;
    }
    f.close();
    return fileExist;
}
