
#ifndef _STRUCTURE_TELEMETRE_H_
#define _STRUCTURE_TELEMETRE_H_


#include "kernel/road_time.h"


// some constants defined for the Alasca component
#define MAX_SCAN_POINT 8648
#define MAX_SCAN_POINT_PER_LAYER 2162
#define UTC_MAGIC_WORD 0x55544300


// Data recorded in the DBITE file
// Alasca XT laserscanner
typedef struct{
  unsigned char scannertype;
  unsigned long timeStart;	  // time start of the scan
  float startAngle;			      // the start angle of the measurement (in [rad*e4])
  float endAngle;			        // the stop angle of the measurement (in [rad*e4])
  unsigned long nbPoint;		  // number of points 
  long dataPos;               // the position of the data in the binary file associated to the dbt file
}AlascaXT;


// An Alasca point 
// see Manual_Alasca.pdf page 27
// Orientation of the frame regarding the car:
// X ahead, Y on the left and Z upside
struct ScanPoint{
  unsigned char scannerId;    // ID of the scanner that has detected the point - Alasca has type 2
  unsigned char layerNumber;  // channel (0 = bottom channel ...)
  unsigned char echoNumber;	  // subChannel (0 = A, 1 = B ...) 
  unsigned char pointStatus;  // ground, rain, dirt ...
  short x;                    // X coordinate in centimeters			
  short y;                    // Y coordinate in centimeters				
  short z;                    // Z coordinate in centimeters
  unsigned short width;       // the echo width
};



// Data obtained after decoding 
// The complete structure is written in shared memory 
// Only the point[MAX_SCAN_POINT] array is recorded in the binary file 
// associated to the DBT file (see struct AlascaXT)
struct ScanAlascaData{
  unsigned char scannertype;        // Alasca has type 2
  unsigned long timeStart;	        // time start of the scan 
  float startAngle;			            // the start angle of the measurement (in [rad*e4])
  float endAngle;			              // the stop angle of the measurement (in [rad*e4])
  unsigned long nbPoint;		        // number of points 
  road_time_t time;                 // DBT timestamp
  road_timerange_t timerange;       // DBT timerange
  ScanPoint point[MAX_SCAN_POINT];  // the data, see struct ScanPoint
};


struct SortedScanAlascaData{
  double xYellow[MAX_SCAN_POINT_PER_LAYER]; 
  double yYellow[MAX_SCAN_POINT_PER_LAYER]; 
  double xGreen[MAX_SCAN_POINT_PER_LAYER]; 
  double yGreen[MAX_SCAN_POINT_PER_LAYER]; 
  double xBlue[MAX_SCAN_POINT_PER_LAYER]; 
  double yBlue[MAX_SCAN_POINT_PER_LAYER]; 
  double xRed[MAX_SCAN_POINT_PER_LAYER]; 
  double yRed[MAX_SCAN_POINT_PER_LAYER]; 

  int totalSize; 
  int yellowSize; 
  int greenSize; 
  int blueSize; 
  int redSize; 
};


// Sick LMS 221 laserscanner
typedef struct{
	float data[101];
}TELEMETRE_100;


// Sick LMS 291 laserscanner
typedef struct{
	float data[181];
}TELEMETRE_180;



// cf. page 23
// faire une structure avec le nb de secteurs 

// pour chaque secteur : 
// donnees statiques : timestamp debut et fin - angles debut et fin - pas de l'angle nb de pts dans le secteur 
// tableaux => donnees de base : distance direction et echo amplitude

typedef struct{
  
}SickLdoemData; 



#endif
