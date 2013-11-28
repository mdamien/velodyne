/* rom1394.h - IEEE Std 1394-1995 node ROM access */

/* Copyright(c) 1999-2001, Mindready Solutions Inc. All rights reserved. */

/*
 * Modification History
 * ----------------------------------------------------------------------------
 * $Log: /Common/Design/Src/misc/Dev/VxWorks/main/inc/rom1394.h $
 * 
 * 9     9/05/01 9:49 Blc
 * Added explicit padding for every bit fields.
 *
 * 8     7/05/01 1:26p Jfha
 * Add a new line a the end of the file to remove warning in Linux
 *
 * 7     5/14/01 11:22 Blc
 * Updated file header as per coding standard. Added missing include for
 * standard integer types.
 *
 * 6     3/22/01 11:39 Blc
 * Renamed ROM_INFO to romInfo_t.
 *
 * 5     2/20/01 5:03p Jfha
 * Change comment type
 * ----------------------------------------------------------------------------
 * $NoKeywords: $
 */

#ifndef __INCrom1394h
#define __INCrom1394h

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

#include <stdint.h>

/* defines */

#define ROM_TYPE0_COMPANY_NAME_SIZE	8
#define ROM_TYPE0_MODEL_NAME_SIZE	14

/* typedefs */

typedef union romInfo
{
	struct type0Hdr
	{
		uint32_t swVersion:24;
		uint32_t :8;
		uint32_t hwVersion:24;
		uint32_t :8;
		uint32_t companyId:24;
		uint32_t :8;
		uint8_t chipIdHi:8;
		uint32_t chipIdLo:32;
		uint8_t irmc:1;
		uint8_t cmc:1;
		uint8_t isc:1;
		uint8_t bmc:1;
		uint8_t :4;
		uint8_t cycClkAcc:8;
		uint8_t maxRec:4;
		uint8_t maxRom:2;
		uint8_t :2;
		char companyName[ROM_TYPE0_COMPANY_NAME_SIZE];
		char modelName[ROM_TYPE0_MODEL_NAME_SIZE];
#ifdef INCLUDE_1394BACKPLANE   /* BACKPLANE support */
        uint8_t isCable;
        uint8_t linkSpeed;  /* 0 = 50 & 100 MBS, 2 = 400 MBS */
#endif /* BACKPLANE support */
	} type0;
} romInfo_t;

/* For backward compatibility. Will be removed in a future release. */
typedef romInfo_t ROM_INFO;

/* globals */

/* locals */

/* forward declarations */

#ifdef __cplusplus
}
#endif

#endif /* __INCrom1394h */

