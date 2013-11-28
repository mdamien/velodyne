// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @version    $Id: TestFileLib.cpp 76 2013-01-10 17:05:10Z kurdejma $

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4265 4365 4571 4640)
#endif // _MSC_VER

#define BOOST_TEST_MODULE TestFileLib
#include <boost/test/unit_test.hpp>

#ifdef _MSC_VER
#   pragma warning(pop)
#endif // _MSC_VER

#include <boost/noncopyable.hpp>
#include <cstdio>

#include "kernel/DbiteException.h"
#include "kernel/DbiteFile.h"
#include "kernel/Log.h"

DECLARE_STATIC_LOGGER("pacpus.core.TestFileLib");

using namespace boost;
using namespace pacpus;
using namespace std;

struct HasExceptionMessage
        : noncopyable
{
    HasExceptionMessage(const string expectedMessage)
        : mExpectedMessage(expectedMessage)
    {
    }

    bool operator()(const DbiteException & ex)
    {
        BOOST_TEST_CHECKPOINT("what() =" << ex.what());
        return mExpectedMessage == ex.what();
    }

private:
    const string mExpectedMessage;
};

BOOST_AUTO_TEST_SUITE(suiteBasic)

BOOST_AUTO_TEST_CASE(isNotOpenAfterConstruction)
{
    DbiteFile df;
    BOOST_CHECK(!df.isOpen());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(suiteRead)

BOOST_AUTO_TEST_CASE(opensFileWithoutData)
{
    DbiteFile df;
    df.open("data/ok-empty-data.dbt", ReadMode);
    
    BOOST_CHECK_EQUAL(df.getDataOffset(), 48);
    BOOST_CHECK_EQUAL(df.getPath(), "data/ok-empty-data.dbt");
    BOOST_CHECK_EQUAL(df.getFileSize(), 48);
    BOOST_CHECK_EQUAL(df.getFileSize(), df.getRealFileSize());
    BOOST_CHECK_EQUAL(df.getRecordCount(), 0);
    BOOST_CHECK_EQUAL(df.getRecordSize(), 32);
    BOOST_CHECK_EQUAL(df.getSignature(), "ROAD");
    BOOST_CHECK(df.getTimeMin() <= df.getTimeMax());
    BOOST_CHECK_EQUAL(df.getType(), 12210);
    BOOST_CHECK_EQUAL(df.getVersion(), 2);
}

BOOST_AUTO_TEST_CASE(readsFileSingleData)
{
    DbiteFile df;
    df.open("data/ok-single-data.dbt", ReadMode);

    BOOST_CHECK_EQUAL(df.getDataOffset(), 44);
    BOOST_CHECK_EQUAL(df.getPath(), "data/ok-single-data.dbt");
    BOOST_CHECK_EQUAL(df.getFileSize(), 64);
    BOOST_CHECK_EQUAL(df.getFileSize(), df.getRealFileSize());
    BOOST_CHECK_EQUAL(df.getRecordCount(), 1);
    BOOST_CHECK_EQUAL(df.getRecordSize(), 8);
    BOOST_CHECK_EQUAL(df.getSignature(), "ROAD");
    BOOST_CHECK_EQUAL(df.getTimeMin(), df.getTimeMax());
    BOOST_CHECK_EQUAL(df.getTimeMin(), static_cast<road_time_t>(1311847165023717));
    BOOST_CHECK_EQUAL(df.getTimeMax(), static_cast<road_time_t>(1311847165023717));
    BOOST_CHECK_EQUAL(df.getType(), 100);
    BOOST_CHECK_EQUAL(df.getVersion(), 2);

    road_time_t t;
    road_timerange_t tr;
    char data[8];

    df.readRecord(t, tr, data);
    BOOST_CHECK_EQUAL(t, static_cast<road_time_t>(1311847165023717));
    BOOST_CHECK_EQUAL(tr, 0);

    int64_t value = *((uint64_t *)data);
    BOOST_CHECK_EQUAL(value, (int64_t) (static_cast<uint64_t>(15) << 32) + 0);
}

BOOST_AUTO_TEST_CASE(readsFileManyData)
{
    DbiteFile df;
    df.open("data/ok-many-data.dbt", ReadMode);

    BOOST_CHECK_EQUAL(df.getDataOffset(), 44);
    BOOST_CHECK_EQUAL(df.getPath(), "data/ok-many-data.dbt");
    BOOST_CHECK_EQUAL(df.getFileSize(), 344);
    BOOST_CHECK_EQUAL(df.getFileSize(), df.getRealFileSize());
    BOOST_CHECK_EQUAL(df.getRecordCount(), 15);
    BOOST_CHECK_EQUAL(df.getRecordSize(), 8);
    BOOST_CHECK_EQUAL(df.getSignature(), "ROAD");
    BOOST_CHECK(df.getTimeMin() < df.getTimeMax());
    BOOST_CHECK_EQUAL(df.getTimeMin(), static_cast<road_time_t>(1311847165023717));
    BOOST_CHECK_EQUAL(df.getTimeMax(), static_cast<road_time_t>(1311847166112739));
    BOOST_CHECK_EQUAL(df.getType(), 100);
    BOOST_CHECK_EQUAL(df.getVersion(), 2);

    for (uint64_t ir = 0; ir < df.getRecordCount(); ++ir) {
        road_time_t t;
        road_timerange_t tr;
        char data[8];

        df.readRecord(t, tr, data);
        BOOST_CHECK(df.getTimeMin() <= t);
        BOOST_CHECK(t <= df.getTimeMax());
        BOOST_CHECK_EQUAL(tr, 0);

        int64_t value = *((uint64_t *)data);
        BOOST_CHECK_EQUAL(value, (int64_t) (ir << 32) + 0x01A0);
    }
}

BOOST_AUTO_TEST_CASE(throwsDbiteExceptionOnEmptyFile)
{
    DbiteFile df;
    BOOST_CHECK_THROW(
        (df.open("data/bad-empty-file.dbt", ReadMode))
        , DbiteException
    );
    BOOST_CHECK_EXCEPTION(
        (df.open("data/bad-empty-file.dbt", ReadMode))
        , DbiteException
        , HasExceptionMessage("cannot read header")
    );
}

BOOST_AUTO_TEST_CASE(throwsDbiteExceptionOnIncompleteHeader)
{
    DbiteFile df;
    BOOST_CHECK_THROW(
        (df.open("data/bad-incomplete-header.dbt", ReadMode))
        , DbiteException
    );
    BOOST_CHECK_EXCEPTION(
        (df.open("data/bad-incomplete-header.dbt", ReadMode))
        , DbiteException
        , HasExceptionMessage("cannot read header")
    );
}

BOOST_AUTO_TEST_CASE(throwsDbiteExceptionOnBadSignature)
{
    DbiteFile df;
    BOOST_CHECK_THROW(
        (df.open("data/bad-signature.dbt", ReadMode))
        , DbiteException
    );
    BOOST_CHECK_EXCEPTION(
        (df.open("data/bad-signature.dbt", ReadMode))
        , DbiteException
        , HasExceptionMessage("bad signature")
    );
}

BOOST_AUTO_TEST_CASE(throwsDbiteExceptionOnWrongVersion)
{
    DbiteFile df;
    BOOST_CHECK_THROW(
        (df.open("data/bad-wrong-version.dbt", ReadMode))
        , DbiteException
    );
    BOOST_CHECK_EXCEPTION(
        (df.open("data/bad-wrong-version.dbt", ReadMode))
        , DbiteException
        , HasExceptionMessage("bad version number")
    );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(suiteWrite)

BOOST_AUTO_TEST_CASE(throwsDbiteExceptionWhenFileDoesntExist)
{
    DbiteFile df;
    const char * kInexistingFilename = "";
    
    BOOST_CHECK_THROW(
        (df.open(kInexistingFilename, ReadMode))
        , DbiteException
    );
    BOOST_CHECK_EXCEPTION(
        (df.open(kInexistingFilename, ReadMode))
        , DbiteException
        , HasExceptionMessage("cannot open file for reading")
    );
}

BOOST_AUTO_TEST_CASE(throwsDbiteExceptionWhenCannotCreateTheFile)
{
    DbiteFile df;
    const char * kIllegalFilename = "";

    BOOST_CHECK_THROW(
        (df.open(kIllegalFilename, WriteMode))
        , DbiteException
    );
    BOOST_CHECK_EXCEPTION(
        (df.open(kIllegalFilename, WriteMode))
        , DbiteException
        , HasExceptionMessage("cannot open file for writing")
    );
}

// TODO: creates file for writing when it doesn't exist
// TODO: creates file for writing when it exists ??? warning?

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(suiteWrite)
    
BOOST_AUTO_TEST_CASE(writesNormallyWhenTheFileDoesntExist)
{
    DbiteFile df;
    const char * filename = "data/unexisting-file.dbt";

    // delete file
    ::remove(filename);

    // create
    df.open(filename, WriteMode, 0x4321, 0x1234);
    BOOST_REQUIRE(df.isOpen());
    df.close();
    
    df.open(filename, ReadMode);
    BOOST_REQUIRE(df.isOpen());
    BOOST_CHECK_EQUAL(df.getPath(), filename);
    BOOST_CHECK_EQUAL(df.getFileSize(), df.getRealFileSize());
    BOOST_CHECK_EQUAL(df.getRecordCount(), 0);
    BOOST_CHECK_EQUAL(df.getRecordSize(), 0x1234);
    BOOST_CHECK_EQUAL(df.getSignature(), "ROAD");
    BOOST_CHECK_EQUAL(df.getType(), 0x4321);
    BOOST_CHECK_EQUAL(df.getVersion(), 2);
    df.close();
}

BOOST_AUTO_TEST_CASE(appendsAtEndWhenFileExists)
{
    DbiteFile df;
    const hdfile_header_t::DataSizeT dataSize = 0x1234;
    const hdfile_header_t::DataTypeT dataType = 0x4321;
    const char * filename = "data/existing-file-no-data.dbt";
    
    road_time_t time = 0xAABBCCDD;
    road_timerange_t tr = 0xABCD;
    char data[dataSize];

    // delete file
    ::remove(filename);

    // create
    df.open(filename, WriteMode, dataType, 0x1234);
    BOOST_REQUIRE(df.isOpen());
    df.close();
    BOOST_REQUIRE(!df.isOpen());

    // append
    df.open(filename, WriteMode, dataType, dataSize);
    BOOST_REQUIRE(df.isOpen());
    df.writeRecord(time++, tr, data, dataSize);
    df.close();
    BOOST_REQUIRE(!df.isOpen());

    // check
    df.open(filename, ReadMode);
    BOOST_CHECK_EQUAL(df.getPath(), filename);
    BOOST_CHECK_EQUAL(df.getFileSize(), df.getRealFileSize());
    BOOST_CHECK_EQUAL(df.getRecordCount(), 1);
    BOOST_CHECK_EQUAL(df.getRecordSize(), dataSize);
    BOOST_CHECK_EQUAL(df.getSignature(), "ROAD");
    BOOST_CHECK_EQUAL(df.getType(), dataType);
    BOOST_CHECK_EQUAL(df.getVersion(), 2);
    df.close();

    // append
    df.open(filename, WriteMode, dataType, dataSize);
    BOOST_REQUIRE(df.isOpen());
    df.writeRecord(time++, tr, data, dataSize);
    df.close();
    BOOST_REQUIRE(!df.isOpen());

    // check
    df.open(filename, ReadMode);
    BOOST_CHECK_EQUAL(df.getPath(), filename);
    BOOST_CHECK_EQUAL(df.getFileSize(), df.getRealFileSize());
    BOOST_CHECK_EQUAL(df.getRecordCount(), 2);
    BOOST_CHECK_EQUAL(df.getRecordSize(), dataSize);
    BOOST_CHECK_EQUAL(df.getSignature(), "ROAD");
    BOOST_CHECK_EQUAL(df.getType(), dataType);
    BOOST_CHECK_EQUAL(df.getVersion(), 2);
    df.close();
}

BOOST_AUTO_TEST_SUITE_END()
