/* llaError.h - SedNet2 error codes */

/* Copyright(c) 2001, Mindready Solutions Inc. All rights reserved. */

/*
 * Modification history
 * ----------------------------------------------------------------------------
 * $Log: /SedNet2/Design/Src/Lla/Multi/winNT4/main/dispatch/inc/llaError.h $
 * 
 * 10    9/14/01 4:22p Sro
 * removed HLA error code
 *
 * 9     8/30/01 11:51a Sro
 * change error code offset to negatif
 *
 * 8     8/17/01 10:53a Sro
 * change of errno system
 *
 * 7     7/20/01 3:02p Spa
 * Removed redundant errno value
 *
 * 6     7/20/01 3:00p Spa
 * Added an invalid gap count errno
 *
 * 5     7/16/01 10:52a Spa
 * Added SDERR_INVALID_LICENCE errno value
 *
 * 4     7/05/01 1:26p Jfha
 * Add a new line a the end of the file to remove warning in Linux
 *
 * 3     5/17/01 10:47a Spa
 * Added SDERR_INVALID_CTX_HANDLE error code
 *
 * 2     5/10/01 5:07p Spa
 * Renamed serverr.h
 *
 * 1     4/18/01 10:40a Sparadis
 * Initial version
 *
 * 4     4/17/01 7:50p Sparadis
 * Pre-alpha release. Ready to be linked with the rest of the LLA and
 * tested
 * ------------------------------------------------------------------------------
 * $NoKeywords: $
 */

#ifndef __INCllaErrorh
#define __INCllaErrorh

#ifdef _cplusplus
extern "C" {
#endif /* _cplusplus */

/* includes */

/* defines */

/* M_sdLink1394Lib shall move in vxModNum.h */
/* Start at 501 since the first 500 module numbers are reserved by WRS */
/* Range allocated 0x1F50000 to 0x1F5FFFF */

#define M_sdLink1394Lib     (0x1F50000) /* 0x1F5 << 16 */

/* LLA error codes range from 0x1001 to 0x1FFFF */

#define LLA_ERR_CODE_OFFSET		(-M_sdLink1394Lib | 0x1000)

#define SDERR_HW_ACCESS_FAILED		(LLA_ERR_CODE_OFFSET | 0x01)
#define SDERR_NOT_ISR_CALLABLE		(LLA_ERR_CODE_OFFSET | 0x02)
#define SDERR_NOT_SUPPORTED_BY_HW	(LLA_ERR_CODE_OFFSET | 0x03)
#define SDERR_NODE_ALONE_ON_BUS		(LLA_ERR_CODE_OFFSET | 0x04)
#define SDERR_SYS_UNAVAILABLE		(LLA_ERR_CODE_OFFSET | 0x05)
#define SDERR_INVALID_GEN_COUNT		(LLA_ERR_CODE_OFFSET | 0x06)
#define SDERR_INVALID_CHAN_LIST		(LLA_ERR_CODE_OFFSET | 0x07)
#define SDERR_NOT_BUS_ROOT			(LLA_ERR_CODE_OFFSET | 0x08)
#define SDERR_INVALID_ADDR			(LLA_ERR_CODE_OFFSET | 0x09)
#define SDERR_UNSUPPORTED			(LLA_ERR_CODE_OFFSET | 0x0A)
#define SDERR_INVALID_HANDLE		(LLA_ERR_CODE_OFFSET | 0x0B)
#define SDERR_INVALID_CMD			(LLA_ERR_CODE_OFFSET | 0x0C)
#define SDERR_INVALID_PACKET		(LLA_ERR_CODE_OFFSET | 0x0D)
#define SDERR_TOO_MUCH_CBACK		(LLA_ERR_CODE_OFFSET | 0x0E)
#define SDERR_INVALID_DESC			(LLA_ERR_CODE_OFFSET | 0x0F)
#define SDERR_COMM_DISABLED			(LLA_ERR_CODE_OFFSET | 0x10)
#define SDERR_INVALID_PARAM			(LLA_ERR_CODE_OFFSET | 0x11)
#define SDERR_BUFFER_EMPTY			(LLA_ERR_CODE_OFFSET | 0x12)
#define SDERR_CHAN_UNAVAILABLE		(LLA_ERR_CODE_OFFSET | 0x13)
#define SDERR_MULTI_CHAN_UNAVAIL	(LLA_ERR_CODE_OFFSET | 0x14)
#define SDERR_CTX_UNAVAILABLE		(LLA_ERR_CODE_OFFSET | 0x15)
#define SDERR_INVALID_ADP_INDEX		(LLA_ERR_CODE_OFFSET | 0x16)
#define SDERR_DEV_UNAVAILABLE		(LLA_ERR_CODE_OFFSET | 0x17)
#define SDERR_DEV_UNINITIALIZED		(LLA_ERR_CODE_OFFSET | 0x18)
#define SDERR_DEV_UNATTACHED		(LLA_ERR_CODE_OFFSET | 0x19)
#define SDERR_INVALID_DEVDESC		(LLA_ERR_CODE_OFFSET | 0x20)
#define SDERR_INVALID_CTX_HANDLE	(LLA_ERR_CODE_OFFSET | 0x21)
#define SDERR_INVALID_LICENCE		(LLA_ERR_CODE_OFFSET | 0x22)
#define SDERR_INIT_FAILED			(LLA_ERR_CODE_OFFSET | 0x23)
#define SDERR_FAILED				(LLA_ERR_CODE_OFFSET | 0x24)

#define SDERR_INVALID_GAP_COUNT		(LLA_ERR_CODE_OFFSET | 0x25)
#define SDERR_INVALID_FLAGS			(LLA_ERR_CODE_OFFSET | 0x26)

/* typedefs */

/* globals */

/* locals */

/* forward declarations */

#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif /* __INCllaErrorh */
