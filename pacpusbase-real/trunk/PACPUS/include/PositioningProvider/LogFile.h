/*********************************************************************
//  created:    2006/10/27 - 8:51
//  filename:   LogFile.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: LogFile.h 172 2006-12-15 10:37:49Z pbonnifa $
//
//  purpose:    Header File for the Logfile Description - WARNING :
//				captures half of the events listened !!!!!
*********************************************************************/

#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include "struct.h"

class LogFile : public QThread
{
public:
	LogFile();
	~LogFile();
	void						openFile();
	void						run();

private:
	FILE*						file_;
	bool						processing_;
	class PositioningComputing*	myEKF_;
	class PositioningSensors*	mySensors_;
	struct s_SensorsData		sensorData_;
	struct s_MatchedPosition	myMatchedPos_;
	bool						done_;

};

#endif /* !_LOGFILE_H_ */
