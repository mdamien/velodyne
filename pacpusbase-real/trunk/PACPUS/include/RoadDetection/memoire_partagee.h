/*********************************************************************
//  created:    2007/02/23 - 11:24
//  filename:   memoire_partagee.h
//
//  author:     Gerald Dherbomez 
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Projet CETIM 
//              Recuperation de donnees telemetriques en memoire partagee
*********************************************************************/


#ifndef __MEMOIRE_PARTAGEE_H__
#define __MEMOIRE_PARTAGEE_H__


#ifdef __cplusplus
extern "C" {
#endif 

// Nom de la memoire partagee
#define SHMEMNAME       "ShMemTelSickLMS"

// Nom du semaphore de protection de la memoire partagee
#define SEM_SHMEMNAME   "Sem_ShMemTelSickLMS"

#include <windows.h>
#include "kernel\road_time.h"

// Structure d'echange des donnees telemetriques en memoire partagee
typedef struct 
{
  road_time_t time;    // temps en microsencondes depuis le 1er janvier 1970
  road_timerange_t tr; // intervalle d'erreur de la datation
  int size;            // nombre de donnees dans le tableau distance 
  float *distance;     // donnees telemetriques
 }TELEMETER_DATA;


// fonction utilisee pour creer le memoire partagee
// ouverture automatique de la memoire a la creation
void createSharedMemory( int size ); 

// ouvre un segment de memoire partagee existant
void openSharedMemory(); 

// fonction de fermeture de la memoire partagee
void closeSharedMemory(); 

// fonction de lecture de la memoire partagee
// Attention cette fonction nécessite en entrée un 
// tableau correctement alloué
// Le nombre de donnees "distance" doit correspondre
// au nombre de donnee en memoire partagee (nbTelemterData()) 
// bloque automatiquement la memoire (lockMemory et unlockMemory)
TELEMETER_DATA* getData(TELEMETER_DATA* out); 

// fontion d'ecriture en memoire partagee
// bloque automatiquement la memoire (lockMemory et unlockMemory)
void setData(TELEMETER_DATA data);
 
// fonction d'initialisation de la structure TELEMETER_DATA  
TELEMETER_DATA* allocTelemeterData(int size); 

// Libere une structure TELEMETER_DATA and desalloue la memoire
void deleteTelemeterData(TELEMETER_DATA* ptr);

// bloque la memoire partagee 
void lockMemory();

// debloque la memoire partagee
void unlockMemory(); 

// renvoie le nombre de points telemetriques
int nbTelemeterData(); 


#ifdef __cplusplus
}
#endif

#endif