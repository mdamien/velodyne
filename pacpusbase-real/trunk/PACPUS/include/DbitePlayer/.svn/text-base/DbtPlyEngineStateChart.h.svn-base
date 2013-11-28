/*********************************************************************
// created:    2007/04/12 - 16:30

//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player Engine state chart header file
*********************************************************************/


#ifndef _DBTPLYENGINESTATECHART_H_
#define _DBTPLYENGINESTATECHART_H_


#include <QObject>
#include "kernel/ComponentBase.h"


// The values that can be taken by the state chart
enum STATECHART_VALUES 
{ 
  PLAY_STATE = 1,
  PAUSE_STATE = 2, 
  STOP_STATE = 3,
};


class DbtPlyEngineStateChart : public QObject
{
  Q_OBJECT 

public:
  // constructor
  DbtPlyEngineStateChart();

  // destructor
  ~DbtPlyEngineStateChart();

  // return the state of the engine
  inline STATECHART_VALUES state() { return state_; }

  // return the current speed of the reading
  inline float speed() { return speed_; }

  // return true if the player is reading data backward
  inline bool doesReadBackward(){ return reverse_; }

  inline void readBackward() { reverse_ = true; }
  inline void readForward() { reverse_ = false; }

  // Each state is implemented in its own method
  void play(int incomingEvent);
  void pause(int incomingEvent, road_time_t *tNow);
  void stop(int incomingEvent, road_time_t *tNow);
 
  
private:
  STATECHART_VALUES state_;
  float speed_;
  bool reverse_;

};


#endif
