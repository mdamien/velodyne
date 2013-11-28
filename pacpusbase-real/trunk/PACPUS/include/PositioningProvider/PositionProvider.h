/*********************************************************************
//  created:    2006/10/16 - 11:48
//  filename:   PositionProvider.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: PositionProvider.h 190 2007-01-25 11:10:12Z gdherbom $
//
//  purpose:    Definition of the central control class of the program
*********************************************************************/

#ifndef _POSITIONPROVIDER_H_
#define _POSITIONPROVIDER_H_

#include "struct.h"

class PositionProvider : public  QObject, public ComponentBase, public QThread
{
	Q_OBJECT

public:
	PositionProvider (const char*);
	~PositionProvider();
	void						configureComponent(XmlComponentConfig config);
	void						startActivity ();
	void						stopActivity ();
	void						run ();
	void						init ();
	enum e_Server_mode			serverMode;

signals:
	QString						changeServerMode ();

private:
	class PositioningSensors*	mySensors_;
	class RequestServer*		myRequestServer_;
	class MapMatching*			myMapMatching_;
	class PositioningComputing* myPositioning_;
};

#endif /* !_POSITIONPROVIDER_H_ */
