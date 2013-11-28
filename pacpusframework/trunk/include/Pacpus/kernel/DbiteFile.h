// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    June, 2012
/// @version $Id: DbiteFile.h 114 2013-06-25 08:55:43Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_DBITEFILE_H
#define DEF_PACPUS_DBITEFILE_H

#include <Pacpus/kernel/cstdint.h>
#include <Pacpus/kernel/FileLibConfig.h>
#include <Pacpus/kernel/hdfile_header_t.h>
#include <Pacpus/kernel/road_time.h>

#include <fstream>
#include <iosfwd>
#include <string>

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 4251)
#endif // _MSC_VER

namespace pacpus {

/// @todo Documentation
struct FILELIB_API VariableDataSizeTag {};
/// @todo Documentation
FILELIB_API extern VariableDataSizeTag VariableDataSize;

/// @todo Documentation
struct FILELIB_API ReadModeTag {};
/// @todo Documentation
FILELIB_API extern ReadModeTag ReadMode;

/// @todo Documentation
struct FILELIB_API WriteModeTag {};
/// @todo Documentation
FILELIB_API extern WriteModeTag WriteMode;

/// @todo Documentation
struct FILELIB_API DiagnoseModeTag {};
/// @todo Documentation
FILELIB_API extern DiagnoseModeTag DiagnoseMode;

/// @todo Documentation
class FILELIB_API DbiteFile
{
public:
    /// @todo Documentation
    enum ReadDirection
    {
        ReadForward
        , ReadBackward
    };

    /// @throws nothing
    DbiteFile();
    /// @throws nothing
    ~DbiteFile();

    /// Opens the file in read mode.
    ///
    /// @throws DbiteException on I/O error (read: cannot open the file)
    /// @throws DbiteException on invalid file signature
    void open(const std::string & path, ReadModeTag);

    /// Opens the file in write mode using default settings.
    /// It is necessary to set data type and data size afterwards.
    ///
    /// @throws DbiteException on I/O error (write: cannot write the header)
    /// @see setRecordSize
    /// @see setType
    void open(const std::string & path, WriteModeTag);

    /// Opens the file in write mode using given data type and data size.
    ///
    /// @code
    ///     DbiteFile dbt;
    ///     dbt.open(path, WriteMode, type, dataSize);
    /// @endcode
    /// is equivalent to
    /// @code
    ///     DbiteFile dbt;
    ///     dbt.open(path, WriteMode)
    ///     dbt.setRecordSize(dataSize);
    ///     dbt.setType(type);
    /// @endcode
    ///
    /// @throws DbiteException on I/O error (write: cannot write the header)
    void open(const std::string & path, WriteModeTag, hdfile_header_t::DataTypeT type, hdfile_header_t::DataSizeT dataSize);

    /// Opens the file in write mode using given data type and variable data size.
    ///
    /// @code
    ///     DbiteFile dbt;
    ///     dbt.open(path, WriteMode, type, VariableDataSize);
    /// @endcode
    /// is equivalent to
    /// @code
    ///     DbiteFile dbt;
    ///     dbt.open(path, WriteMode)
    ///     dbt.setRecordSize(VariableDataSize);
    ///     dbt.setType(type);
    /// @endcode
    ///
    /// @throws DbiteException on I/O error (write: cannot write the header)
    void open(const std::string & path, WriteModeTag, hdfile_header_t::DataTypeT type, VariableDataSizeTag);

    /// Tries to diagnose and repair the file.
    /// @throws DbiteException on I/O error (write: cannot write the header)
    //void open(const std::string & path, DiagnoseModeTag); // TODO

    /// @throws nothing
    void close();
    /// @throws nothing
    bool isOpen() const;

    /// @throws DbiteException when file is not open
    void goToFileBegin();
    /// @throws DbiteException when file is not open
    void goToFileEnd();
    /// @throws DbiteException when file is not open
    void goToDataBegin();

    /// @throws nothing
    const std::string & getPath() const;
    /// @throws nothing
    std::string getSignature() const;
    /// @throws nothing
    hdfile_header_t::DataTypeT getType() const;
    /// @throws nothing
    hdfile_header_t::VersionT getVersion() const;
    /// @throws nothing
    hdfile_header_t::DataOffsetT getDataOffset() const;
    /// @throws nothing
    hdfile_header_t::DataSizeT getRecordSize() const;
    // FIXME: file size should be 64-bit long, have to change the hdfile_header_t structure as well
    /// @throws nothing
    hdfile_header_t::FileSizeT getFileSize() const;
    /// @returns the real size of the written file in [bytes] as obtaine from system.
    int64_t getRealFileSize();
    /// @throws nothing
    road_time_t getTimeMin() const;
    /// @throws nothing
    road_time_t getTimeMax() const;
    /// @throws nothing
    hdfile_header_t::RecordCountT getRecordCount() const;

    /// @throws nothing
    void setType(hdfile_header_t::DataTypeT type);
    /// @throws nothing
    void setRecordSize(hdfile_header_t::DataSizeT recordSize);
    /// @throws nothing
    void setRecordSize(VariableDataSizeTag tag);
    /// @throws nothing
    void setTimeMin(road_time_t time);
    /// @throws nothing
    void setTimeMax(road_time_t time);
    /// @throws nothing
    void setRecordCount(hdfile_header_t::RecordCountT recourdCount);

    /// prints header
    /// @throws nothing
    operator std::string();

    /// @throws nothing
    bool isVariableDataSize() const;

    /// @throws DbiteException on I/O error
    bool readRecord(size_t recordIndex, road_time_t & time, road_timerange_t & timeRange, char * data);
    /// @throws DbiteException on I/O error
    bool readRecord(size_t recordIndex, road_time_t & time, road_timerange_t & timeRange, char * data, size_t & dataSize);
    /// @throws DbiteException on I/O error
    bool readRecord(road_time_t & time, road_timerange_t & timeRange, char * data, const ReadDirection & direction = ReadForward);
    /// @throws DbiteException on I/O error
    bool readRecord(road_time_t & time, road_timerange_t & timeRange, char * data, size_t & dataSize, const ReadDirection & direction = ReadForward);
    /// Reads only time and time range and moves the file position to the beginning of the next record
    /// @throws DbiteException on I/O error
    bool readRecord(road_time_t & time, road_timerange_t & timeRange, const ReadDirection & direction = ReadForward);
    /// @throws DbiteException on I/O error
    bool writeRecord(const road_time_t & time, const road_timerange_t & timeRange, const char * data, const size_t dataSize);
    /// @throws DbiteException on I/O error
    template <typename T>
    bool writeRecord(const road_time_t & time, const road_timerange_t & timeRange, const T* data);

    /// @throws nothing
    bool isEndOfFile();

private:
    /// @throws nothing
    void setPath(const std::string & path);
    /// @throws nothing
    void setVersion(hdfile_header_t::VersionT version);
    /// @throws nothing
    void setDataOffset(hdfile_header_t::DataOffsetT dataOffset);
    /// @throws nothing
    void setFileSize(hdfile_header_t::FileSizeT fileSize);

    void initializeHeader();

    bool isSignatureCorrect() const;
    void setSignature();

    const hdfile_header_t & getHeader() const;
    hdfile_header_t & header();
    void writeHeader();

    void openWriteMode(const std::string & path);
    void openWriteMode(const std::string & path, hdfile_header_t::DataTypeT type);
    void closeDbite();
    void closeDbite(ReadModeTag);
    void closeDbite(WriteModeTag);
    void readHeader();
    void verifyHeader();

    /// @throws DbiteException when file is not open
    int64_t getReadPosition();
    /// @throws DbiteException when file is not open
    int64_t getWritePosition();
    /// @throws DbiteException when file is not open
    void setReadPosition(int64_t offset, std::ios_base::seekdir direction);
    /// @throws DbiteException when file is not open
    void setReadPosition(int64_t position);
    /// @throws DbiteException when file is not open
    void setWritePosition(int64_t offset, std::ios_base::seekdir direction);
    /// @throws DbiteException when file is not open
    void setWritePosition(int64_t position);

    /// @throws DbiteException on I/O error
    bool readRecordNoBufferCheck(road_time_t & time, road_timerange_t & timeRange, char * data, size_t & dataSize, const ReadDirection & direction);
    /// @throws DbiteException on I/O error
    bool readRecordForward(road_time_t & time, road_timerange_t & timeRange, char * data, size_t & dataSize);
    /// @throws DbiteException on I/O error
    bool readRecordBackward(road_time_t & time, road_timerange_t & timeRange, char * data, size_t & dataSize);

    /// @throws DbiteException on I/O error
    void read(std::fstream::char_type * s, std::streamsize n);
    /// @throws DbiteException on I/O error
    void write(const std::fstream::char_type * s, std::streamsize n);

    /// @throws DbiteException when file is not open
    void checkFileOpen();

private:
    std::fstream mFile;
    hdfile_header_t mHeader;
    bool mIsWriting;
    std::string mPath;

    bool mIsVariableRecordSize;
};

template <typename T>
bool DbiteFile::writeRecord(const road_time_t & time, const road_timerange_t & timeRange, const T* data)
{
  return writeRecord(time, timeRange, (const char*) data, sizeof(T));
}

} // namespace pacpus

#ifdef _MSC_VER
#   pragma warning(pop)
#endif // _MSC_VER

#endif // DEF_PACPUS_DBITEFILE_H
