/*********************************************************************
//  created:    2007/07/28 - 11:38
//  filename:   DbtPlyIOShMemTel.h
//
//  author:     Gerald Dherbomez 
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Class to exchange data via shared memory
//
*********************************************************************/



#ifndef _DBTPLYIOSHMEMTEL_H_
#define _DBTPLYIOSHMEMTEL_H_

#include "kernel/road_time.h"

// Structure d'echange des donnees telemetriques en memoire partagee
typedef struct 
{
  road_time_t time;    // temps en microsencondes depuis le 1er janvier 1970
  road_timerange_t tr; // intervalle d'erreur de la datation
  int size;            // nombre de donnees dans le tableau distance 
  float *distance;     // donnees telemetriques
 }TELEMETER_DATA;


#ifdef WIN32
#include <windows.h>

// Nom de la memoire partagee
#define SHMEMNAME       "ShMemTelSickLMS"

// Nom du semaphore de protection de la memoire partagee
#define SEM_SHMEMNAME   "Sem_ShMemTelSickLMS"


class DbtPlyIOShMemTel
{
public:
  DbtPlyIOShMemTel(); 
  ~DbtPlyIOShMemTel(); 
  void lockMemory(); 
  void unlockMemory();
  void createSharedMemory( int mapSize );
  void openSharedMemory();
  void closeSharedMemory();
  void setData(TELEMETER_DATA data);
  TELEMETER_DATA* allocTelemeterData(int size); 
  void deleteTelemeterData(void * ptr);
  
private: 
  HANDLE handle;                // handle de la memoire partagee
  TELEMETER_DATA* telem_data;             // le tableau de donnees mappe en memoire
  HANDLE sc_shmem;              // semaphore de protection de la memoire partagee
  int size; 
};
#endif


#endif
