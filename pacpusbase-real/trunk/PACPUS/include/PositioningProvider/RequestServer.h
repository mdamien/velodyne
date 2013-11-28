/*********************************************************************
//  created:    2006/10/18 - 15:05
//  filename:   RequestServer.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: RequestServer.h 238 2007-04-20 13:01:10Z gdherbom $
//
//  purpose:    This class is used to respond to a client with a "request"
//				event. It sends data_ready in respond.
*********************************************************************/

#ifndef _REQUESTSERVER_H_
#define _REQUESTSERVER_H_

#include "struct.h"

class RequestServer : public QThread
{
public:
	RequestServer (class MapMatching*);
	~RequestServer ();
	void						extrapolatePosition ();
	void						mapMatching();
	void						run ();
  void            stop (); 
  int							THREAD_ALIVE;

	
private:
	struct s_MatchedPosition*	initMatchedStruct();
	HANDLE						request_;
  HANDLE            internalRequest_; 
	HANDLE						data_ready_;
	HANDLE						endit_;
	HANDLE						requestsWait_[3];
	class PositioningComputing*	posComp_;
	struct s_MatchedPosition	myMatchedPosition_;
	void*						clientShMemory_;
	road_time_t					time_;
	class MapMatching*			myMapMatching_;
	class PositioningSensors*	sensors_;
  class MapClientSocket* myMapClient_; 
	bool						ended_;
	struct s_position			old_;

};

#endif /* !_REQUESTSERVER_H_ */
