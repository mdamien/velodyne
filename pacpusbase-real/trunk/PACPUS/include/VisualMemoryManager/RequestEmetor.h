/*********************************************************************
//  created:    2006/11/20 - 10:32
//  filename:   RequestEmetor.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: RequestEmetor.h 216 2007-04-03 13:33:56Z gdherbom $
//
//  purpose:    
*********************************************************************/

#ifndef _REQUESTEMETOR_H_
#define _REQUESTEMETOR_H_

# include "../../include/VisualMemoryManager/struct.h"

class RequestEmetor
{
public:
	RequestEmetor();
	~RequestEmetor();
	struct s_MatchedPosition*		getPosition();
	void							sendRequest();

private:
	struct s_MatchedPosition*		myMatchedPosition_;
	void*							clientShMemory_;
	HANDLE							request_;
	HANDLE							data_ready_;
	DWORD							timeOut_;

};

#endif /* !_REQUESTEMETOR_H_ */
