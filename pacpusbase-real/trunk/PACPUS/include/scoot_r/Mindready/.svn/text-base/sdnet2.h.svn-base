/* sdnet02.h - sednet2 high level api include file */

/* Copyright 1997-1999 Sederta Inc. */

/*
modification history
--------------------
02d,15Sep00,spa	Removed unused macros.
02c,15Sep00,spa	Added max packets length.
02b,15Sep00,spa	Corrected the maximum number of isoch channel
02a,14Sep00,spa  Removed OHCI events defines. Added max payload length.
01z,14Sep00,spa  Added OHCI events defines. Removed config constants.
01y,13Sep00,spa  Added a third parameter to SDNET2_CBACK and add the time stamp to
				 SDNET2_ASYNCH structure
01x,11Sep00,spa  Removed unused include
01w,06Sep00,spa  Now open takes a devIndex instead of a string
01v,17Jul00,pbe   Removed inclusion of private hlaFifo.h
01u,12Jul00,pbe   Corrected flag overlap, added SDNET2_TYPE_FLAGS, modified
					SDNET2_BUFFERS_STATUS
01t,29May00,pbe   Moved DEV_ID_LENGTH to sdPrivate.h
01s,25May00,pbe   Major modifications due to use of OHCI devices
01r,13Apr00,pbe   Corrected a structure name for coherence
01q,11Apr00,pbe   Moved private data and structures to sdPrivate.h
01p,10Apr00,pbe   Added prototype of sdNET2_PrintStatistics
01o,06Apr00,pbe   Added SDNET2_ASYNCHRONOUS_RESP and SDNET2_ASYNCHRONOUS_REQ
					to give SDNET2_ASYNCHRONOUS. Adde SDNET2_FORCE_CBACK. Added
					cbHandlerQueuePacketsCnt to SDNET2_BUFFERS_STATUS structure
01n,27Mar00,pbe   Renamed SDNET2_FLUSH_STATUS into SDNET2_BUFFERS_STATUS and
					all the fields ending with Flush now ends with Cnt
01m,27Mar00,pbe   Added SDNET2_FLUSH_STATUSa structure for chained buffer
					status
01l,29Feb00,sp25  Changed xtCode field size to UINT16 in the
				  structure defining asynchronous packets,
				  removed forgotten bit field in isoch pk struct
01k,22Feb00,sp25  Complete restructuration of the HLA layer
01j,25jan00,sp25  Added global config variables.
01i,25jan00,sp25  Added multiple open of the same device
01h,25Jan00,sp25  Added handle counter in device struct
01g,17Jan00,sp25  Added context chained buffers for reception.
01f,06Jan00,sp25  Changed busResetId for generationCount in structures.
				  Major change in HLA.
01e,06Jan00,sp25  Moved error code to serverr.h
01d,07Dec99,lep  Change data ptr from UINT8* to UINT32*
01c,03Dec99,lep  Change data ptr from UINT32* to UINT8*
01b,25nov99,lep  Reorganization of SDNET2_HLA_DESC structure
01a,30sep99,sp25 This file was created.
*/

/*
This file defines structures and constants used by the high level
API of SEDNET2
*/

#ifndef __sdnet2h
#define __sdnet2h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */
#include "sdtypes.h"
#include "ieee1394.h"

#include "tsb12lv23.h"
#include "tsb41lv3.h"

#include "llaError.h"

/* defines */
#define SD_SUCCESS	(M_sdLink1394Lib | 0x01)
#define SD_ERROR	(M_sdLink1394Lib | 0x02)


/* HLA error code range rom 0x2001 to 0x2FFF */
#define HLA_ERR_CODE_OFFSET				(M_sdLink1394Lib | 0x2000)

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
#define SDERR_INVALID_RESP_CODE			(HLA_ERR_CODE_OFFSET | 0x10)
#define SDERR_INVALID_PRIORITY			(HLA_ERR_CODE_OFFSET | 0x11)
#define SDERR_INVALID_DATA_PTR			(HLA_ERR_CODE_OFFSET | 0x12)
#define SDERR_INVALID_ARGUMENT			(HLA_ERR_CODE_OFFSET | 0x13)
#define SDERR_INVALID_PHY_ID			(HLA_ERR_CODE_OFFSET | 0x14)
#define SDERR_INVALID_FORCE_ROOT		(HLA_ERR_CODE_OFFSET | 0x15)
#define SDERR_INVALID_SYNCHRO			(HLA_ERR_CODE_OFFSET | 0x16)
#define SDERR_INVALID_SET_GAP_COUNT		(HLA_ERR_CODE_OFFSET | 0x17)
#define SDERR_CBACK_PENDING				(HLA_ERR_CODE_OFFSET | 0x18)
#define SDERR_NO_RX_ISO_CHANNEL_FOUND	(HLA_ERR_CODE_OFFSET | 0x20)
#define SDERR_NO_RX_ISO_AVAILABLE		(HLA_ERR_CODE_OFFSET | 0x21)
#define SDERR_INVALID_DEV_NAME			(HLA_ERR_CODE_OFFSET | 0x22)



/* Maximum length of the packets */
#define SDNET2_MAX_ASYNCH_PK_LENGTH	(2048)
#define SDNET2_MAX_ISOCH_PK_LENGTH	(4096)

#define SDNET2_MAX_LOCK_REQ_PK_LENGTH	(16)
#define SDNET2_MAX_LOCK_RESP_LENGTH		(8)

/*
 * This value indicates to the HLA to compute himself a valid
 * timestamp when sending aysnchronous response packet.
 */
#define SDNET2_COMPUTE_TIMESTAMP		((UINT16) ~0)


/* SDNET2_TESTIT services value */

#define SDNET2_IOC_HLA_OFFSET	((UINT32) 0x1100)

/* HLA ioctl services */
#define SDNET2_IOC_SET_CYCLE_MASTER		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x1)
#define SDNET2_IOC_CLEAR_CYCLE_MASTER	((UINT32) SDNET2_IOC_HLA_OFFSET | 0x2)
#define SDNET2_IOC_SET_NODE_ID			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x3)
#define SDNET2_IOC_GET_NODE_ID			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x4)
#define SDNET2_IOC_SET_CHANNEL_LIST		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x5)
#define SDNET2_IOC_RESET_BUS			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x6)
#define SDNET2_IOC_PRESENT_STATUS		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x7)
#define SDNET2_IOC_SET_LINK_ON			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x8)
#define SDNET2_IOC_SET_LINK_OFF			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x9)
#define SDNET2_IOC_SET_GAP_COUNT		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x10)
#define SDNET2_IOC_SET_FORCE_ROOT		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x11)
#define SDNET2_IOC_CLEAR_FORCE_ROOT		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x12)
#define SDNET2_IOC_GET_GENERATION_COUNT	((UINT32) SDNET2_IOC_HLA_OFFSET | 0x13)
#define SDNET2_IOC_SET_CONTENDER		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x14)
#define SDNET2_IOC_CLEAR_CONTENDER		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x15)
#define SDNET2_IOC_SET_BUS_TIME			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x16)
#define SDNET2_IOC_GET_BUS_TIME			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x17)
#define SDNET2_IOC_RESET_DEVICE			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x18)
#define SDNET2_IOC_FLUSH_BUFFERS		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x19)
#define SDNET2_IOC_GET_BUFFERS_STATUS	((UINT32) SDNET2_IOC_HLA_OFFSET | 0x20)
#define SDNET2_IOC_STOP_RECEPTION		((UINT32) SDNET2_IOC_HLA_OFFSET | 0x21)

#define SDNET2_IOC_HW_ACCESS			((UINT32) SDNET2_IOC_HLA_OFFSET | 0x22)


/* HLA packets type */
/* The first 6 bits are used to code the isochronous channel number, which
	range is between 0 to 63 */
#define SDNET2_ISO_CHANNELS_MASK		 (UINT32)0x3F
#define SDNET2_ISOCHRONOUS				((UINT32)1<<6)
#define SDNET2_LINK_ON					((UINT32)1<<7)
#define SDNET2_PHY_CONFIG				((UINT32)1<<8)
#define SDNET2_SELF_ID					((UINT32)1<<9)
#define SDNET2_CYCLE_START				((UINT32)1<<10)


#define SDNET2_EXT_PING					((UINT32)1<<16)
#define SDNET2_EXT_REM_CMD				((UINT32)1<<17)
#define SDNET2_EXT_REM_ACC				((UINT32)1<<18)
#define SDNET2_EXT_RESUME				((UINT32)1<<19)
#define SDNET2_EXT_REM_CONF 			((UINT32)1<<20)
#define SDNET2_EXT_REM_REPLY			((UINT32)1<<21)


#define SDNET2_ASYNCHRONOUS_RESP		((UINT32)1<<11)
#define SDNET2_ASYNCHRONOUS_REQ			((UINT32)1<<12)
#define SDNET2_ASYNCHRONOUS				(SDNET2_ASYNCHRONOUS_RESP | \
										SDNET2_ASYNCHRONOUS_REQ)

#define SDNET2_TYPE_FLAGS				(SDNET2_ISOCHRONOUS	| \
										SDNET2_LINK_ON		| \
										SDNET2_PHY_CONFIG	| \
										SDNET2_SELF_ID		| \
										SDNET2_CYCLE_START	| \
										SDNET2_ASYNCHRONOUS)

/* Notification type */
#define SDNET2_PRE_NOTIFICATION			((UINT32)1<<13)
#define SDNET2_POST_NOTIFICATION		((UINT32)1<<14)

/* Used to replace the actual callback by new one */
#define SDNET2_FORCE_CBACK				((UINT32)1<<15)

/* Possibles returns value of the callbacks installed on rx of cycle start */
#define	SDNET2_NO_MORE		((UINT32) NULL)
#define SDNET2_MORE			~(SDNET2_NO_MORE)

/* Level of reset */
/*
//!+![sro]#define SDNET2_SOFT_RESET 		((UINT32) 0)
//!+![sro]#define SDNET2_HARD_RESET		((UINT32) 1)
*/
#define SDNET2_SOFT_RESET 		((VOID*) 10)
#define SDNET2_HARD_RESET		((VOID*) 20)



/* Hardware Access Command Type */
#define SDNET2_HW_ACCESS_OFFSET	((UINT32) 0x0)

#define SDNET2_DUMP_LINK		((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x1)
#define SDNET2_DUMP_PHY			((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x2)
#define SDNET2_PHY_READ_REG		((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x3)
#define SDNET2_PHY_WRITE_REG	((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x4)
#define SDNET2_PHY_SET_BIT		((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x5)
#define SDNET2_PHY_CLR_BIT		((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x6)
#define SDNET2_LINK_READ_REG	((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x7)
#define SDNET2_LINK_WRITE_REG	((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x8)
#define SDNET2_LINK_SET_BIT		((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x9)
#define SDNET2_LINK_CLR_BIT		((UINT32) SDNET2_HW_ACCESS_OFFSET | 0x10)


/* typedef */

/* Structure used to set/get the node identifier */
typedef struct sdNet2NodeIdHdr
{
	UINT16 busNumber;		/* IEEE 1394-1995 Std 6.2.4.2.1 */
	UINT8 nodeNumber;		/* IEEE 1394-1995 Std 6.2.4.2.1 */
} SDNET2_NODEID;

/* Structure used set the isochronous channel to listen from */
typedef struct sdNet2ChannelHdr
{
	UINT8 listSize;							/* Number of channel to listen from */
	UINT8 list[IEEE1394_MAX_NB_CHANNEL];	/* Channels to listem from */
} SDNET2_CHANNEL;

/* Structure used set/get the physical present status of the node */
typedef struct sdNet2PhyStatHdr
{
	UINT8 physicalId;				/* IEEE 1394-1995 Std 4.3.8 */
	UINT8 gapCount;					/* IEEE 1394-1995 Std 4.3.8 */
	UINT8 phySpeed;					/* IEEE 1394-1995 Std 4.3.7 */
	UINT8 forceRoot;				/* IEEE 1394-1995 Std 4.3.8 */
	UINT8 cablePowerActive;			/* IEEE 1394-1995 Std 4.3.8 */
	UINT8 initiatedReset;			/* IEEE 1394-1995 Std 4.3.8 */
	UINT8 busRoot;					/* IEEE 1394-1995 Std 4.3.8 */
	struct sdNet2phContConfPortHdr
	{
		UINT8 child;				/* IEEE 1394-1995 Std 4.3.9 */
		UINT8 connected;			/* IEEE 1394-1995 Std 4.3.9 */
		UINT8 arbARx;				/* IEEE 1394-1995 Std 4.2.2 */
		UINT8 arbBRx;				/* IEEE 1394-1995 Std 4.2.2 */
	} port[IEEE1394_NPORT_MAX];
	UINT8 numberOfPorts;
} SDNET2_PHYSTAT;

/* Structure used to get/set the local bus time */
typedef struct sdNet2BusTimeHdr		/* IEEE 1394-1995 Std 8.3.2.3.1 */
{
	UINT32 cycleCount;	/* Current offset in the isoch cycles (gran.:125us) */
	UINT32 secondCount;	/* Number of second elapsed since the driver loaded */
} SDNET2_BUSTIME;

/* Structure used to send/receive asynchronous packets */
typedef struct sdNet2AsyncHdr
{
	UINT32 generationCount;		/* Current bus reset number */
	struct asyncHeaderHdr
	{
		UINT16 busNumber;				/* IEEE 1394-1995 Std 6.2.4.2.1 */
		UINT8 nodeNumber;				/* IEEE 1394-1995 Std 6.2.4.2.1 */
		UINT16 destinationHigh;			/* IEEE 1394-1995 Std 6.2.4.2.2 */
		UINT32 destinationLow;			/* IEEE 1394-1995 Std 6.2.4.2.2 */
		UINT8 transactionCode;			/* IEEE 1394-1995 Std 6.2.4.5 */
		UINT16 extendedTransactionCode;	/* IEEE 1394-1995 Std 6.2.4.9 */
		UINT8 transactionLabel;			/* IEEE 1394-1995 Std 6.2.4.3 */
		UINT8 retryCode;				/* IEEE 1394-1995 Std 6.2.4.4 */
		UINT8 responseCode;				/* IEEE 1394-1995 Std 6.2.4.10 */
		UINT16 dataLength;				/* IEEE 1394-1995 Std 6.2.4.8 */
		UINT8 priority;					/* IEEE 1394-1995 Std 6.2.4.6 */
		UINT8 speed;					/* IEEE 1394-1995 Std Table 4-2 */
	} header;
	UINT32 *data;	/* Pointer to the buffer of data, must be 32 bits aligned */
	UINT8 status;	/* Only valid when receiving an asynch packet. */
					/* See IEEE 1394-1995 Std. 6.1.2.3 */
	UINT16	timeStamp; /* TimeStamp tagged to the packet */
} SDNET2_ASYNC;

/* Structure used to send/receive isochronous packets */
typedef struct sdNet2IsochHdr
{
	struct isochHeaderHdr
	{
		UINT8 tag;			/* IEEE 1394-1995 Std 6.2.4.12 */
		UINT8 channel;		/* IEEE 1394-1995 Std 6.2.4.13 */
		UINT8 synchro;		/* IEEE 1394-1995 Std 6.2.4.14 */
		UINT8 speed;		/* IEEE 1394-1995 Std Table 4-2 */
		UINT16 dataLength;	/* IEEE 1394-1995 Std 6.2.4.8 */
	} header;
	UINT32 *data;	/* Data pointer, must be 32 bits aligned */
	UINT8 status;	/* Only valid when receiving an isoch packet. */
					/* See IEEE 1394-1995 Std. 6.1.2.3 */
} SDNET2_ISOCH;

/* Structure used when receiving self-id packets */
/* See IEEE 1394-1995 Std. Table 4-29 */
typedef struct sdNet2SelfIdHdr
{
	struct selfIdHeaderHdr
	{
		UINT8 phyId;
		UINT8 gapCount;
		UINT8 linkActive;
		UINT8 phySpeed;
		UINT8 phyDelay;
		UINT8 contender;
		UINT8 powerClass;
		UINT8 numberOfPorts;
		UINT8 initiatedReset;
		UINT8 port[IEEE1394_NPORT_MAX];
	} block[IEEE1394_NODE_NUMBER_MAX + 1];
	UINT8 numOfBlock;
	UINT32 generationCount;
} SDNET2_SELFID;

/* Structure used when sending/receiving link on packets */
typedef struct sdNet2LinkOnHdr /* IEEE 1394-1995 Std 4.3.4.2 */
{
	UINT8 phyId;
	UINT32 generationCount;	/* Current bus reset number */
} SDNET2_LINKON;

/* Structure used when sending/receiving phy config packets */
typedef struct sdNet2PhyConfigHdr /* IEEE 1394-1995 Std 4.3.4.2 */
{
	UINT8 phyId;
	UINT8 forceRoot;
	UINT8 setGapCount;
	UINT8 gapCount;
	UINT32 generationCount;
} SDNET2_PHYCONFIG;

/* Structure used when sending/receiving ping packets */
typedef struct sdNet2PingHdr
{
	UINT8 phyId;
	UINT32 generationCount;
} SDNET2_PING;

/* Structure used when sending/receiving remote command packets */
typedef struct sdNet2RemCmdHdr
{
	UINT8 phyId;
	UINT8 port;
	UINT8 cmd;
	UINT32 generationCount;
} SDNET2_REMCMD;

/* Structure used when sending/receiving remote command packets */
typedef struct sdNet2RemConfHdr
{
	UINT8 phyId;
	UINT8 port;
	UINT8 fault;
	UINT8 connected;
	UINT8 bias;
	UINT8 disabled;
	UINT8 ok;
	UINT8 cmd;
	UINT32 generationCount;
} SDNET2_REMCONF;

/* Structure used when sending/receiving remote access packets */
typedef struct sdNet2RemAccHdr
{
	UINT8 phyId;
	UINT8 page;
	UINT8 port;
	UINT8 reg;
	UINT8 regType;
	UINT32 generationCount;
} SDNET2_REMACC;

/* Structure used when sending/receiving remote access packets */
typedef struct sdNet2RemReplyHdr
{
	UINT8 phyId;
	UINT8 page;
	UINT8 port;
	UINT8 reg;
	UINT8 regType;
	UINT8 data;
	UINT32 generationCount;
} SDNET2_REMREPLY;

/* Structure used when sending/receiving resume packets */
typedef struct sdNet2ResumeHdr
{
	UINT8 phyId;
	UINT32 generationCount;	/* Current bus reset number */
} SDNET2_RESUME;


/* Structure used when receiving cycle start packets */
typedef struct sdNet2CyStartHdr /* IEEE 1394-1995 Std 6.2.2.2.3 */
{
	struct cyStartHeaderHdr
	{
		UINT16 busNumber;
		UINT8 nodeNumber;
		UINT16 destinationHigh;
		UINT32 destinationLow;
		UINT8 transactionCode;
		UINT8 transactionLabel;
		UINT8 retryCode;
		UINT8 priority;
		UINT8 speed;
	} header;
	UINT32 data;
} SDNET2_CYSTART;

/* !+! */
typedef struct sdNet2hwHdr
{
	unsigned cmdType;

	union
	{
		tsb12lv23_t link;
		tsb41lv03_t phy;

		struct linkRegHdr
		{
			UINT32 offset;
			UINT32 value;
		} linkReg;

		struct linkBitHdr
		{
			UINT32 offset;
			UINT32 mask;
			UINT32 value;
		} linkBit;

		struct phyRegHdr
		{
			UINT32 offset;
			UINT32 value;
		} phyReg;

		struct phyBitHdr
		{
			UINT32 offset;
			UINT8 mask;
			UINT32 value;
		} phyBit;

	} cmd;

} SDNET2_HW_ACC;


/* Structure used to get the acknowledge of a sent packet */
typedef struct sdNet2ConfHdr
{
	UINT8 status;
	UINT8 acknowledge; /* IEEE 1394-1995 Std Table 6.2.5.2.2 */
} SDNET2_CONF;

/* Handle to a device */
typedef int SDNET2_HANDLE;

/* Callbacks prototypes */
typedef int (*SDNET2_CBACK)(void *context1, void *context2, UINT32 **newBuffer);

/* Packets pointer */
typedef UINT32*	SDNET2_PACKET;

/* Status of a function */
typedef UINT32 SDNET2_STATUS;


/* Structure used to indicate the number of buffers to flush and, after the
	call to sdNET2_IOControl(), the number of buffers effectively flushed */
typedef struct sdNet2BuffersStatus
{
	/*
	 * Number of asynchronous request packets in FIFO
	 */
	INT32 asyReqRecvPacketsCnt;
	/*
	 * Number of asynchronous response packets in FIFO
	 */
	INT32 asyRespRecvPacketsCnt;
	/*
	 * Number of isochronous packets in FIFO
	 */
	INT32 isoRecvPacketsCnt;
	/*
	 * Number of link on packets in FIFO
	 */
	INT32 linkonRecvPacketsCnt;
	/*
	 * Number of phy config packets flushed from the RECEIVE queue
	 */
	INT32 phyconfigRecvPacketsCnt;

} SDNET2_BUFFERS_STATUS;


/* High Level Api prototypes */
SDNET2_STATUS sdNET2_Init(void);
SDNET2_STATUS sdNET2_Release(void);

SDNET2_STATUS sdNET2_OpenDevice(SDNET2_HANDLE* handle,
                                UINT32 devIndex,
                                UINT32 flags);

SDNET2_STATUS sdNET2_CloseDevice(SDNET2_HANDLE* handle);

SDNET2_STATUS sdNET2_SendPacket(SDNET2_HANDLE* handle,
                                SDNET2_PACKET packet,
                                SDNET2_CONF* confPtr,
                                SDNET2_CBACK callback,
                                void* context,
                                UINT32 flags);

SDNET2_STATUS sdNET2_ReceivePacket(SDNET2_HANDLE* handle,
                                   SDNET2_PACKET packet,
                                   SDNET2_CBACK callback,
                                   void* context,
                                   UINT32 flags);

SDNET2_STATUS sdNET2_IOControl(SDNET2_HANDLE* handle,
                               UINT32 command,
                               void* ioData);

#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* __sdnet2h */