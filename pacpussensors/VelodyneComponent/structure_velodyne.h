#ifndef STRUCTURE_VELODYNE_H
#define STRUCTURE_VELODYNE_H

// VELODYNE_BLOCK_SIZE = sizeof(unsigned short = uint16) * 2 + sizeof(VelodyneRawPoint = uint16,uint8) * kVelodynePointsPerBlock = 2*2 + (2+1)*32 = 4 + 96 = 100
#define VELODYNE_BLOCK_SIZE 100
// FIXME: unused
// VELODYNE_PACKET_SIZE =
#define VELODYNE_PACKET_SIZE 1206
#define VELODYNE_SCAN_SIZE 4166
#define VELODYNE_NB_BLOCKS_PER_PACKET 12

#define kVelodyneUpperBlock 0xEEFF
#define kVelodyneLowerBlock 0xDDFF
#define kVelodynePointsPerBlock 32

#pragma pack(push, 1)

// 3 bytes size
typedef struct VelodyneRawPoint
{
    uint16_t distance; // 0.2cm increments - if 0 no return up to 65m
    uint8_t intensity; // 255 most intense return
} VelodyneRawPoint;

// 100=VELODYNE_BLOCK_SIZE bytes size
typedef struct VelodyneBlock
{
    /// 0xEEFF upper and 0xDDFF lower
    uint16_t block;

    /// azimuth in 100th of degrees [0-35999]
    uint16_t angle;

    /// a couple of distance and intensity representing a point
    struct VelodyneRawPoint rawPoints[kVelodynePointsPerBlock];

	/* FIXME, block pacpus sensor with these 6 more bytes
	// change VELODYNE_BLOCK_SIZE to 106 after
    // Status (see p. 29 Rev C 2011).
    uint32_t timestamp; // 10e-06.
    uint8_t  code;       // ASCII code.
    uint8_t  codeValue; // Value of the code, see the Rev C.
	*/
} VelodyneBlock;

// size : VELODYNE_BLOCK_SIZE*VELODYNE_SCAN_SIZE + sizeof(unsigned short = uint16)*VELODYNE_SCAN_SIZE
//          + sizeof(road_time_t = unsigned long long = uint64) + sizeof(road_timerange_t = int = int32) + sizeof(short = int16)
//      = 100*4166 + 2*4166 + 8 + 4 + 2 = 424 946 bytes
// structure containing data of a complete revolution of the lidar
typedef struct VelodynePolarData
{
    /// data of one block of 32 beams (upper or lower)
    VelodyneBlock polarData[VELODYNE_SCAN_SIZE];

    /// scan count relative to polarData above
    uint16_t scanCount[VELODYNE_SCAN_SIZE];

    /// Timestamp of each block.
    //road_time_t dataTime[VELODYNE_SCAN_SIZE];

    /// time got in the packet containing first angle
    road_time_t time;
    /// timerange = diff( t(angle=0) - t(lastangle) )
    road_timerange_t timerange;

    // FIXME: rename
    /// not all polarData are useful, use range to know until which index you can use the data
    int16_t range;
} VelodynePolarData;

#pragma pack(pop)

#endif // STRUCTURE_VELODYNE_H
