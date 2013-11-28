// This DLL was compiled as a Standard C Language Dynamic Link Libtrary.
// So in order to be compatible with C++ program, we must add the command extern "C"
// for the whole include file.
#ifndef ROAD_TIME_H
#define ROAD_TIME_H

#ifdef __cplusplus
extern "C" {
#endif 

// Just for having the definition of a road_time_t element (typedef unsigned __int64 road_time_t;)
// For me it looks very heavy to do that but ...
#include <stdio.h>


#ifdef WIN32
typedef unsigned __int64 road_time_t;
typedef int road_timerange_t;   

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ROAD_TIME_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ROAD_TIME_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef ROAD_TIME_EXPORTS
#define ROAD_TIME_API __declspec(dllexport)
#else
#define ROAD_TIME_API __declspec(dllimport)
#endif


// Structure exchanged to give the Initialization parameters. All these fields are filled when the
// first process attached to the DLL. It gives the Real Time and the value of the Performance Counter
// at the same time.
// Description of each field is provided inside the structure
struct Initialisation_Time
{
	road_time_t    Real_Time;							//Time (extended to micro seconds precision)
														//that was given by the Real Time Clock of
														//windows (using ftime()) at the first time the DLL was called.
	unsigned __int64	Multimedia_Counter;				//Correpsonding number of cycles of the CPU Performance Counter,
        													//if it is available. Normally it is the Multimedia Counter.
														//If the Performance Counter is not availaible, normally it
														//should return the Real Time Counter Value (accuracy of 10 ms)..
	unsigned __int64	Multimedia_Counter_Frequency;	//Frequency of the Performance Counter, if it is available
        													//This Frequency is given in Hertz.
	road_time_t    delta_t;								//Delta_t is used to have less work when asking time.
														//Delta_t is equal to Real_Time - (Multimedia_Counter/Multimedia_Counter_Frequancy)/1000000

};

// This method just return the actual time using a method based on delta_t (1 less operation).
// Return a road_time_t: ellapsed time in microseconds since the 1/01/1970
//ROAD_TIME_API road_time_t road_time(void);
road_time_t ROAD_TIME_API road_time(void);
// This method just return the actual time using all the fields of the Initiaiztion_Time Structure.
// Return a road_time_t: ellapsed time in microseconds since the 1/01/1970
//ROAD_TIME_API road_time_t road_time2(void);
road_time_t ROAD_TIME_API road_time2(void);
// This method just return the Initialization Parameter
// Return an Initialization_Time structure (see below)
//ROAD_TIME_API struct Initialisation_Time road_time_init(void);
struct Initialisation_Time ROAD_TIME_API road_time_init(void);

#else // linux

#include <sys/time.h>

typedef unsigned long long road_time_t;
typedef int road_timerange_t;

static road_time_t road_time(void)
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return(road_time_t)((road_time_t)(t.tv_sec)*1000000 + (road_time_t)(t.tv_usec));
}

#endif
#ifdef __cplusplus
}
#endif

#endif
