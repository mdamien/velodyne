/*********************************************************************
//  created:    2006/12/21 - 11:05
//  filename:   VisualManagerFrame.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: VisualManagerFrame.h 216 2007-04-03 13:33:56Z gdherbom $
//
//  purpose:    
*********************************************************************/

#ifndef _VISUALMANAGERFRAME_H_
#define _VISUALMANAGERFRAME_H_

#include "struct.h"

class VisualManagerFrame : public Form1
{
	Q_OBJECT

public:
	VisualManagerFrame ();
	~VisualManagerFrame ();
public slots:
	void					stateEdit(int s);
	void					roadEdit(long id);
	void					wayEdit(int w);
	void					distEdit(double d);

private:
	
};

#endif /* !_VISUALMANAGERFRAME_H_ */
