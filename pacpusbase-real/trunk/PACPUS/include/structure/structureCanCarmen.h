/*********************************************************************
//  created:    2008/2/28 - 16:24
//  filename:   structureCanCarmen.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Description of the CAN structures for Carmen
//
// to add: 
// 094 - comodos
// 612 - eclairage
// 208 - couple
// 349 - couple boite vitesse
// 552 - heure
// 
// to verify: 
//  350 and 319 not present in real time acquisition 
*********************************************************************/


#ifndef __STRUCTURECANCARMEN_H__
#define __STRUCTURECANCARMEN_H__

#include "kernel/road_time.h"

// corresponding CAN frame = 0x44D
typedef struct{
  float frontWheelsSpeed;     // mean speed of the front wheels (in km/h)
  float rearLeftWheelSpeed;   // speed of the rear left wheel (in km/h)
  float rearRightWheelSpeed;  // speed of the rear right wheel (in km/h)
  float rpmFrontWheels;       // mean rpm of the front wheels (in tr/min)
}StructWheelSpeed;


typedef struct{
  road_time_t time;
  road_timerange_t timerange;
  StructWheelSpeed d;
}TimestampedStructWheelSpeed;


// corresponding CAN frame = 0x350
typedef struct{
  float frontLeftSuspension;  // suspension clearance front left in mm
  float frontRightSuspension; // suspension clearance front right in mm
  float rearLeftSuspension;   // suspension clearance rear left in mm
  float rearRightSuspension;  // suspension clearance rear right in mm
  float trim;                 // the trim in degree
}StructSuspension;

typedef struct{
  road_time_t time;
  road_timerange_t timerange;
  StructSuspension d;
}TimestampedStructSuspension;

// corresponding CAN frame = 0x38D
typedef struct{
  float vehicleSpeed;         // vehicle speed in km/h (referenced to the wheels)
  float distance;             // odometer in m (referenced to the wheels). Internally coded as integer 16 bits. Roll over to 0 when value reachs FFFFh (6553.5m to be verified experimentally). 
  float longitudinalAcc;      // longitudinal acceleration in m/s2 (referenced to the wheels)
}StructVehicleSpeed;

typedef struct{
  road_time_t time;
  road_timerange_t timerange;
  StructVehicleSpeed d;
}TimestampedStructVehicleSpeed;

// corresponding CAN frame = 0x319
typedef struct{
  char yawAccFailSt;          // ? 
  bool latAccCal;             // calibration?
  bool latAccValid;           // flag use/don't use
  bool yawRateCal;            // calibration?
  bool yawRateValid;          // flag use/don't use
  float yawRate;              // yaw rate in deg/s
  float latAcc;               // lateral acceleration in m/s2
  float yawSensorOscFreq;     // in Hz
  unsigned long yawSensorSN;  // ?
}StructRawLateralDynamics;

typedef struct{
  road_time_t time;
  road_timerange_t timerange;
  StructRawLateralDynamics d;
}TimestampedStructRawLateralDynamics;

// corresponding CAN frame = 0x305
typedef struct {
  float angle;                // in deg - >0 in trigonometric direction (to the left)
  long rate;                  // in deg/s
  long optRate;               // in deg/s optimized rotation rate of the steering wheel
  char errorCode;             // error code - 4 bits
  bool trim;                  // trim must be at 1, if 0 don't use angle and rate
  bool calibration;           // calibration
  bool sensorState;           // sensor state
  char checksum;              // checksum - 4 bits
}StructSteeringWheel;

typedef struct{
  road_time_t time;
  road_timerange_t timerange;
  StructSteeringWheel d;
}TimestampedStructSteeringWheel;

// corresponding CAN frame = 0x3CD
typedef struct {
  float yawRate;              // >0 in trigonometric direction in deg/s
  float latAcc;               // >0 to the right in m/s2
  float brakePressure;        // master cylinder pressure in bar
  char braking;               // 2 bits
  bool perfLatAccSens;        // ?
  bool perfYawRateSens;       // ?
  bool latAccUncert;          // ?
  bool yawRateUncert;         // ?
  bool brakeContactHS;        // ?
  bool brakeContact;          // ?
  bool muSplitSituation;      // ?
  bool stopEmissionBicapReq;  // ?
}StructLateralDynamics;       


typedef struct{
  road_time_t time;
  road_timerange_t timerange;
  StructLateralDynamics d;
}TimestampedStructLateralDynamics;



#endif
