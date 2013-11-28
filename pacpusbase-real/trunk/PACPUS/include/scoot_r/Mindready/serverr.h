/* serverr.h - IEEE 1394-1995 SedNet2 error codes */

/* Copyright(c) 1999, Sederta Inc. All rights reserved. */

/*
modification history
--------------------
01u,11Jul00,sro  Added Windows specific error code.
01t,15Sep00,spa  Added SDERR_DEV_UNAVAILABLE error code.
01s,08Sep00,spa  Corrected duplicate values for 2 error codes
01r,05Sep00,spa  Added SDERR_INVALID_DEV_NAME HLA error code
01q,31Aug00,spa  Added isochronous error code
01p,12Jul00,spa  Added SDERR_BUFFER_EMPTY lla error code
01o,12Jul00,pbe  Added SDERR_NO_RX_ISO_CHANNEL_FOUND and
					SDERR_NO_RX_ISO_AVAILABLE
01n,2June00,spa  Added SDERR_INVALID_DESC error code.
				 Changed M_sdPci400Lib for M_sdLink1394Lib
01m,06Apr00,pbe  Added SDERR_CBACK_PENDING error code.
01l,04fev00,sp25 Added invalid packet error code
01k,27Jan00,sp25 Change wrong force root error code
01j,25Jan00,sp25 Added error codes
01i,21Jan00,sp25 Added SDERR_INVALID_RESP_CODE
01h,14Jan00,pbe Added SDERR_INVALID_GAP_COUNT
01g,12Jan00,sp25 Added HLA error codes
01f,04Jan00,sp25 Changed error code value
01e,25Nov99,sp25 Added link and phy layer error values
01d,10Aug99,fb4 Updated copyright
01c,15Jul99,fb4 Removed LK_ISOCH and LK_ASYNC codes. Added definition of new
                error code set.
01b,15Apr99,fb4 Added LK_ISOCH and LK_ASYNC codes
01a,17Mar99,fb4 This file was created.
*/

/*
This module contains SedNet2 error codes
*/

#ifndef __INCserverrh
#define __INCserverrh

#ifdef _cplusplus
extern "C" {
#endif /* _cplusplus */

/* includes */

/* defines */

/* M_sdLink1394Lib shall move in vxModNum.h */
/* Start at 501 since the first 500 module numbers are reserved by WRS */
/* Range allocated 0x1F50000 to 0x1F5FFFF */

#define M_sdLink1394Lib     (0x1F50000) /* 0x1F5 << 16 */

#define SD_SUCCESS	(M_sdLink1394Lib | 0x01)
#define SD_ERROR	(M_sdLink1394Lib | 0x02)

/* LLA error codes range from 0x1001 to 0x1FFFF */

#define LLA_ERR_CODE_OFFSET		(M_sdLink1394Lib | 0x1000)

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


/* Windows specific error code */
#define SDERR_INVALID_LEVEL					(LLA_ERR_CODE_OFFSET | 0x51)
#define SDERR_INSUFFICIENT_BUFFER			(LLA_ERR_CODE_OFFSET | 0x52)
#define SDERR_DRIVER_ALREADY_INITIALIZED	(LLA_ERR_CODE_OFFSET | 0x53)
#define SDERR_INIT_FAILED					(LLA_ERR_CODE_OFFSET | 0x54)
#define SDERR_DRIVER_NOT_INITIALIZED		(LLA_ERR_CODE_OFFSET | 0x55)
#define SDERR_INCORRECT_DRIVER_VERSION		(LLA_ERR_CODE_OFFSET | 0x56)
#define SDERR_LOADING_DRIVER_ERROR			(LLA_ERR_CODE_OFFSET | 0x57)
#define SDERR_ADAPTER_ALREADY_IN_USE		(LLA_ERR_CODE_OFFSET | 0x58)

/* HLA error code range rom 0x2001 to 0x2FFF */

#define HLA_ERR_CODE_OFFSET		(M_sdLink1394Lib | 0x2000)

#define SDERR_INVALID_NODE_NB			(HLA_ERR_CODE_OFFSET | 0x01)
#define SDERR_INVALID_BUS_NB			(HLA_ERR_CODE_OFFSET | 0x02)
#define SDERR_INVALID_TLABEL			(HLA_ERR_CODE_OFFSET | 0x03)
#define SDERR_INVALID_OFFLOW			(HLA_ERR_CODE_OFFSET | 0x04)
#define SDERR_INVALID_RCODE				(HLA_ERR_CODE_OFFSET | 0x05)
#define SDERR_INVALID_DATALEN			(HLA_ERR_CODE_OFFSET | 0x06)
#define SDERR_INVALID_XTCODE			(HLA_ERR_CODE_OFFSET | 0x07)
#define SDERR_INVALID_TCODE				(HLA_ERR_CODE_OFFSET | 0x08)
#define SDERR_INVALID_CHANNEL			(HLA_ERR_CODE_OFFSET | 0x09)
#define SDERR_INVALID_TAG				(HLA_ERR_CODE_OFFSET | 0x0A)
#define SDERR_INVALID_SPEED				(HLA_ERR_CODE_OFFSET | 0x0B)
#define SDERR_OUT_OF_MEMORY				(HLA_ERR_CODE_OFFSET | 0x0C)
#define SDERR_DRIVER_FAILED				(HLA_ERR_CODE_OFFSET | 0x0D)
#define SDERR_CANT_OPEN_DEV				(HLA_ERR_CODE_OFFSET | 0x0E)
#define SDERR_INVALID_GAP_COUNT			(HLA_ERR_CODE_OFFSET | 0x0F)
#define SDERR_INVALID_RESP_CODE			(HLA_ERR_CODE_OFFSET | 0x10)
#define SDERR_INVALID_PRIORITY			(HLA_ERR_CODE_OFFSET | 0x11)
#define SDERR_INVALID_DATA_PTR			(HLA_ERR_CODE_OFFSET | 0x12)
#define SDERR_INVALID_ARGUMENT			(HLA_ERR_CODE_OFFSET | 0x13)
#define SDERR_INVALID_PHY_ID			(HLA_ERR_CODE_OFFSET | 0x14)
#define SDERR_INVALID_FORCE_ROOT		(HLA_ERR_CODE_OFFSET | 0x15)
#define SDERR_INVALID_SYNCHRO			(HLA_ERR_CODE_OFFSET | 0x16)
#define SDERR_INVALID_SET_GAP_COUNT		(HLA_ERR_CODE_OFFSET | 0x17)
#define SDERR_CBACK_PENDING				(HLA_ERR_CODE_OFFSET | 0x18)
#define SDERR_INVALID_FLAGS				(HLA_ERR_CODE_OFFSET | 0x19)
#define SDERR_NO_RX_ISO_CHANNEL_FOUND	(HLA_ERR_CODE_OFFSET | 0x20)
#define SDERR_NO_RX_ISO_AVAILABLE		(HLA_ERR_CODE_OFFSET | 0x21)
#define SDERR_INVALID_DEV_NAME			(HLA_ERR_CODE_OFFSET | 0x22)


/* typedefs */

/* globals */

/* locals */

/* forward declarations */

#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif /* __INCserverrh */