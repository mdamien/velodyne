/*********************************************************************
// created:    2007/04/12 - 16:30 
//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player File Manager header file
             
*********************************************************************/



#ifndef _DBTPLYFILEMANAGER_H_
#define _DBTPLYFILEMANAGER_H_

#include <QObject>
#include <QThread>
#include <QSemaphore>
#include <QWaitCondition>

#include "kernel/road_time.h"
#include "kernel/ComponentBase.h"
#include "DbitePlayer/DbtPlyEngine.h"


class DbtPlyEngine;


class DbtPlyFileManager : public QThread, public ComponentBase
{
  Q_OBJECT

public:
  // constructor
  DbtPlyFileManager(QString name);      
  // destructor
  ~DbtPlyFileManager(); 
  
  // the player replays only the last data that has not been yet replayed
  void playMode1 (road_time_t tDbt, bool rev);
  // the player replays all the data that have not been yet replayed
  void playMode2 (road_time_t tDbt, bool rev);
  
  // virtual method: call when new DBT data are replayed
  virtual void processData(road_time_t time,road_timerange_t timeRange, void * data) = 0;
  virtual void displayUI();

  // 3 Virtual methods relative to the ComponentBase inheritance
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
  virtual void startActivity();
  virtual void stopActivity();

  // The loop of the thread
  virtual void run();

public slots:
  // slot activated by the engine when it computes new DBT time
  void  playData(road_time_t tDbt,road_time_t tNow, bool reverse);

  // put the file descriptor to the beginning of the file
  void beginfile();

signals:
  // signal sent to the engine to provide to it the tmin and tmax of the file
  void tMinMaxIs (road_time_t tmin, road_time_t tmax);


protected:
  // a pointer on the player engine
  DbtPlyEngine * eng_;

  // the absolute path of the DBT file
  QString dbtProperty_;
  QStringList dbtFile_; 

  // The directory where the DBT file is located
  QString dbtPath_; 

  // Display or not the graphical interface
  bool ui_; 

  struct dbtStruct {    
    void * buffer;
    road_time_t t;
    road_timerange_t tr;
  };
  struct dbtStructFile {
    // the DBT file descriptor
    hdfile_t* pfile;
    // the buffer where the data are stored after the reading and the associated time, timerange and file descriptor
    dbtStruct cur;
    // the previous DBT data, these ones that must be processed
    dbtStruct toProcess;
  };
  QList<dbtStructFile> dbt_;
  int dbtIndex_;




private:
  // reading backward? 
  bool reverse_;

  // the estimated DBT time sent by the engine and computed relatively to the state of the player
  road_time_t timeToRead_;

  // The mode of replay
  // see playModeN method
  int mode_;

  // The minimum and maximum time of the data contained in the file
  road_time_t tMin_, tMax_;

  // the synchronization semaphore with the engine
  QSemaphore * sync_; 

  // For statistics purpose - delta time between the instant when the tDbt is computed and the instant when it is
  // taken into account by the file manager
  int deltaTDbtTab_[1000];
  int deltaTDbtTabLoop_;
};


#endif


