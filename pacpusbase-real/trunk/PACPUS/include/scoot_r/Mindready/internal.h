/* internal.h - IEEE 1394 driver internal management routines */

/* Copyright(c) 1999, Sederta Inc. All rights reserved. */

/*
modification history
--------------------
01h,08Dec99,sp25 Moved macro used to build name in sdPci400Drv.h
01g,08Dec99,lep  Remove cmnSupport.h
01f,06Dec99,lep  Removed sysGetDevicePoolId
01e,03Dec99,sp25 Added a macro used to build the device name when calling
				 vxWorks open function.
01d,10Aug99,fb4 Updated copyright
01c,9Jul99,fb4 Added support for cmnSupport mbuf/mblock version
01b,18May99,fb4 Added _DEV parameter to RESUME_ON_POOL_EMPTY
01a,17May99,fb4 This file was created.
*/

/*
This module contains driver internal routines needed for device management
*/

#ifndef __INCinternalh
#define __INCinternalh

#ifdef _cplusplus
extern "C" {
#endif /* _cplusplus */

/* includes */

#include "sdtypes.h"
#include "services.h"

/* defines */

#define RESUME_ON_POOL_EMPTY(_DEV) sysResumeOnPoolEmpty(_DEV)

/* typedefs */

/* globals */

/* locals */

/* forward declarations */

STATUS sysResumeOnPoolEmpty(ADAPTER_HANDLE * devNumber);

#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif /* __INCinternalh */
