#ifndef RUETUBE_HPP
#define RUETUBE_HPP

#ifdef RUETUBE_EXPORTS
#define RUETUBE_API __declspec(dllexport)
#else
#define RUETUBE_API __declspec(dllimport)
#endif

//#include "../../Include/rue_data.h"

#include "../Include/rue_data.h"

RUETUBE_API void sendnbre(unsigned long );
RUETUBE_API void sendroute(ruedata , TB_2D_DELTAPOINT * );
RUETUBE_API void recieveroutenb (unsigned long & );
RUETUBE_API void recieveroutedetails (int , ruedata & );
RUETUBE_API void recieveroutepts (int , TB_2D_DELTAPOINT * , unsigned long );


/*RUETUBE_API void sendroute(unsigned long, ruedata *);
RUETUBE_API void recieveroute (unsigned long &, ruedata *);
RUETUBE_API void recieveroutenb (unsigned long &);
RUETUBE_API void recieveroutedetails (unsigned long & , ruedata *);
//RUETUBE_API void recieveroutepts (unsigned long & , TB_2D_DELTAPOINT * );*/
#endif