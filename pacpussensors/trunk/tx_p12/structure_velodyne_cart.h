#ifndef STRUCTURE_VELODYNE_CART_H
#define STRUCTURE_VELODYNE_CART_H

#define VELODYNE_BLOCK_SIZE 100
#define VELODYNE_PACKET_SIZE 1206
#define VELODYNE_SCAN_SIZE 4166
#define VELODYNE_NB_BLOCKS_PER_PACKET 12

#pragma pack(push, 1)

// 25 bytes size
typedef struct VelodyneCartPoint
{
  float distance; // in meter - if 0 no return up to 65m
  double X,Y,Z; // in meter if 0 no return up to 65m
  unsigned char intensity; // 255 most intense return
}VelodyneCartPoint;

// 100=VELODYNE_BLOCK_SIZE bytes size
typedef struct VelodyneCartBlock
{
  unsigned short block; // 0xEEFF upper and 0xDDFF lower
  float alpha; // azimuth in  degrees
  float beta; // elevation in  degrees
  struct VelodyneCartPoint Points[32]; // a couple of distance and intensity representing a point
}VelodyneCartBlock;


// size : 100*4166 + 2*4166 + 8 + 4 = 424 944 bytes
// structure containing data of a complete revolution of the lidar
typedef struct VelodyneCartData
{
  VelodyneCartBlock Data[VELODYNE_SCAN_SIZE];    // data of one block of 32 beams (upper or lower)
  unsigned short scanCount[VELODYNE_SCAN_SIZE];   // scan count relative to polarData above
  road_time_t time;             // time got in the packet containing first angle
  road_timerange_t timerange;   // timerange = diff( t(angle=0) - t(lastangle) )
  short range;                  // not all polarData are useful, use range to know until which index you can use the data
}VelodyneCartData;

#pragma pack(pop)

#endif // STRUCTURE_VELODYNE_CART_H
