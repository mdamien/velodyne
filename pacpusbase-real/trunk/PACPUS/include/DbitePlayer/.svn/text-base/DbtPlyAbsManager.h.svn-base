/*********************************************************************
//  created:    2007/07/28 - 11:51
//  filename:   DbtPlyAbsManager.h
//
//  author:     Gerald Dherbomez 
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Dbite Player ABS Manager
*********************************************************************/


#ifndef _DBTPLYABSMANAGER_H_
#define _DBTPLYABSMANAGER_H_

#include <qlcdnumber.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlayout.h>

#include "DbitePlayer/DbtPlyFileManager.h"
#include "structure/structure_abs_original.h"

#include "PacpusTools/ShMem.h"




class DbtPlyAbsManager : public DbtPlyFileManager
{
  Q_OBJECT

public:
	DbtPlyAbsManager(QString name);
	~DbtPlyAbsManager();

signals:
  void displayAbsVAvG(double);
  void displayAbsVAvD(double);
  void displayAbsVArG(double);
  void displayAbsVArD(double);

protected:
  void processData(road_time_t t, road_timerange_t tr , void *buf);
  void displayUI();


private:
  data_abs_original* val; 
  QWidget *w; 
  QGroupBox *speed; 
  QLabel* labVAvG; 
  QLCDNumber *lcdVAvD;
  QLabel *labVAvD;
  QLCDNumber *lcdVAvG;
  QLabel* labVArG; 
  QLCDNumber *lcdVArD;
  QLabel* labVArD; 
  QLCDNumber *lcdVArG; 

  // variables for output
  ShMem * shMem_; 
  donnees_abs_zy dataToTransmit_ ;
};


#endif
