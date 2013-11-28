// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    June, 2011
/// @version $Id: hdfile_header_t.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_HDFILE_HEADER_T_H
#define DEF_HDFILE_HEADER_T_H

#include <Pacpus/kernel/cstdint.h>
#include <Pacpus/kernel/road_time.h>

/// @todo Documentation
#define HEADER_SIGNATURE_LENGTH 4
/// @todo Documentation
#define VERSION_NUMBER 2

#pragma pack(push,4)
/// @todo Documentation
struct hdfile_header_t
{
    /// @todo Documentation
    typedef  int8_t SignatureT;
    /// @todo Documentation
    typedef int32_t DataTypeT;
    /// @todo Documentation
    typedef int32_t VersionT;
    /// @todo Documentation
    typedef int32_t DataSizeT;
    /// @todo Documentation
    typedef int32_t DataOffsetT;
    /// @todo Documentation
    /// @todo FIXME: file size should be 64-bit long to support large (>2GB) files
    typedef int32_t FileSizeT;
    /// @todo Documentation
    typedef int32_t RecordCountT;

    /// @todo Documentation
    static const DataSizeT kVariableRecordSize = -1;

    /// @todo Documentation
    SignatureT      Signature[HEADER_SIGNATURE_LENGTH];
    /// Record data type.
    /// Should default to ::FILE_DBT_UNKNOWN
    /// @see DbiteFileTypes.h for more information about available types.
    DataTypeT       Type;
    /// File format version
    VersionT        VersionNumber;
    /// Offset indicating the start of the data [bytes]
    DataOffsetT     DataOffset;
    /// Current size of the data, without header [bytes]
    DataSizeT       DataSize;
    /// Current size of the file [bytes]
    FileSizeT       FileSize;
    /// @todo Documentation
    road_time_t     TimeMin;
    /// @todo Documentation
    road_time_t     TimeMax;
    /// Number of records already in the file
    RecordCountT    NbRecords;
};
#pragma pack(pop)

#endif // DEF_HDFILE_HEADER_T_H
