/*******************************************************************************
*
*	PROJECT:	Common library for HLA examples
*
*	FILE:		common.h
*
*	CONTENT:	Contains many differents function that could be used in the
*               HLA examples.
*
*
*	COPYRIGTH:	2001, Mindready Solutions Inc, All rights reserved.
*
*/


#ifndef  __HLA_COMMON_H_
#define  __HLA_COMMON_H_



/*----------------------------------------------------------------------------*/
/*                        SeNet2 Error definition                             */
/* The error number is returned differently depending of the OS               */
/*----------------------------------------------------------------------------*/
#ifdef WIN32
	#define ERRNO GetLastError()
#elif
	/*Ohter platform definition*/
#endif





/* Function declaration */

extern int BecomeTheRoot(SDNET2_HANDLE *hDevice, UINT32 maxRetry);
extern void     PrintError (int error);
extern char* sdNet2Error (int error);



#endif /*__HLA_COMMON_H_*/