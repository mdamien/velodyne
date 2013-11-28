/*********************************************************************
// created:    2007/04/12 - 16:30

//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player Engine header file
*********************************************************************/




#ifndef _DBTPLYENGINE_H_
#define _DBTPLYENGINE_H_


#include <QSemaphore>

#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"
#include "DbitePlayer/DbtPlyEngineStateChart.h"
#include "DbitePlayer/DbtPlyUserInterface.h"
#include <stdio.h>



// forward declaration 
class DbtPlyEngineStateChart;



#ifdef WIN32
const __int64 UINT64_MAX = _UI64_MAX; 
#else 
typedef unsigned long long UINT64; 
const unsigned long long UINT64_MAX = ULLONG_MAX; 
#endif  




class DbtPlyEngine : public QThread, public ComponentBase
{
  Q_OBJECT 

public:
  // constructor
  DbtPlyEngine(QString name);
  // destructor
  ~DbtPlyEngine();
  
  // return the directory where the data are stored
  QString getDataDir(); 

  // return the current replay time
  road_time_t getTime(){return tDbt_;};

  // return true if the player is playing
  bool isPlaying();

protected:
  // The 3 virtual methods relative to the ComponentBase inheritance
  virtual void startActivity();
  virtual void stopActivity();
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

  // The thread main loop
  virtual void run();
  
  
private:
  // The state chart of the engine (speed, state and direction)
  DbtPlyEngineStateChart *stateChart_;
  
  // A semaphore of protection of the critical section 
  QSemaphore *tMinMaxSem_;
  // tmin and tmax regarding to all the DBT files replayed
  road_time_t tDbtMin_, tDbtMax_;

  // tNow_ = the current time when the trigger alerts the engine
  // tDbt_ = the DBT time at which the data have to be replayed corresponding the state of the engine
  // lastTNow_, lastTDbt_ = respectively, the previous tNow_ and tDbt_
  road_time_t tNow_, lastTNow_, tDbt_, lastTDbt_;

  // the direction of reading: forward=1 or backward=-1 used to compute the tDbt that must be replayed
  short direction_;

  // the synchronization semaphore with the trigger
  QSemaphore * sync_; 

  // where the data are stored
  QString dataDir_;

signals:
  void play(road_time_t timeToPlay,road_time_t actualTime, bool direction);  
  void stopfile();
  void displayStateSig(int state, float speed);
  void timeMinMax(road_time_t tMin, road_time_t tMax);
  void curReplayTime(road_time_t time);
  
public slots:
  void engReceiver();
  void changeState (int event);
  void changeDirection (bool reverse);
  void tMinMax(road_time_t tMin, road_time_t tMax);
	void pauseEvent();
	void playEvent();

};

#endif
