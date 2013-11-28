/* lla.h - SedNet2 Low Level API */

/* Copyright(c) 2001, Mindready Solutions, Inc. All rights reserved. */

/*
This module contains typedef and define for the link and physical layers
services.
*/

#ifndef __INCllah
#define __INCllah

#ifdef _cplusplus
extern "C" {
#endif /* _cplusplus */

/* includes */
#include <stdint.h>
#include <stdbool.h>

#include <dbuf.h>

#include "ieee1394.h"
#include "rom1394.h"

/* defines */
#define SDNET2_VERSION "2.2.2"


/* insure that OK and ERROR are define */
#ifndef OK
#define OK		(0)
#endif

#ifndef ERROR
#define ERROR	(-1)
#endif

/* Flags used when doing isochronous configuration */
#define ISO_CONT_CREATE_CTX			(0x1 << 0)
#define ISO_CONT_DELETE_CTX			(0x1 << 1)
#define ISO_CONT_SET_CFG			(0x1 << 2)
#define ISO_CONT_GET_CFG			(0x1 << 3)
#define ISO_CONT_PER_PACKET			(0x1 << 4)
#define ISO_CONT_BUFFER_FILL		(0x1 << 5)
#define ISO_CONT_STRIP_HDR			(0x1 << 6)
#define ISO_CONT_SYNCH_MATCH		(0x1 << 7)
#define ISO_CONT_CYCLE_MATCH		(0x1 << 8)
#define ISO_CONT_TAG_MATCH			(0x1 << 9)


/* Flag used when doing tag matching in isochronous Rx config. */
#define ISO_TAG0					(0x1 << 0)
#define ISO_TAG1					(0x1 << 1)
#define ISO_TAG2					(0x1 << 2)
#define ISO_TAG3					(0x1 << 3)

/* Flags used when doing isochronous cycle generation configuration */
#define ISO_CYCLE_INTERN			(0x1 << 0)
#define ISO_CYCLE_SOFTWR			(0x1 << 1)
#define ISO_CYCLE_EXTERN			(0x1 << 2)

/* Flags used when doing asynchronous configuration */
#define LLA_ASY_REQ					(0x1 << 0)
#define LLA_ASY_RESP				(0x1 << 1)

/* Flags used when configuring auto response feature */
#define LLA_ENABLE					(0x1 << 0)
#define LLA_DISABLE					(0x1 << 1)
#define LLA_ALL_BUSES				(0x1 << 2)

/* Flags used when reseting an adapter */
#define LLA_HARD_RESET				(0x1 << 0)
#define LLA_SOFT_RESET				(0x1 << 1)

/*
 * Used with LK_CONFIG_REQ to specify if a remote access
 * concern a base register or a paged registers.
 */
#define LLA_BASE_REG				1
#define LLA_PAGED_REG				2

/*
 * Non-compliant IEEE 1394 LK_DATA_CONF status for generation count management.
 * This status is returned when the generation count passed via LK_DATA_REQ is
 * not equal to 0 and when it does not match the current bus reset number (from
 * 1 to 255
 */
#define GENERATION_COUNT_MISMATCH	0x3

/* Non-compliant IEEE 1394 LK_DATA_CONF status, this value is used when a packet has been flushed by the lla */
#define PACKET_FLUSHED				0x4

/*
 * Non-compliant IEEE 1394 LK_DATA_CONF status, this value is used when the timeout
 * specified for an asynchronous response expired and the packet been flushed.
 */
#define TRANSMIT_TIMEOUT			0x5

/* LK_ISO_CONF status. (Non-compliant IEEE1394) */
#define LLA_ISO_TX_GOOD				0
#define LLA_ISO_TX_BAD				1

/*
 * Define the number of interrupt signal available to
 * bind a callback on.
 */
#define LLA_MAX_NUMOF_INTERR_SIGNAL	10

/* Define each int signal (values has nothing to do with any hardware mapping)*/
#define LLA_LOCKRESP_ERR_INT		0
#define LLA_CYCLE_64SEC_INT			1
#define LLA_CY_LOST_INT				2
#define LLA_CYCLE_INCONS_INT		3
#define LLA_STATE_TIMEOUT_INT		4
#define LLA_PORT_EVENT_INT			5


/* typedefs */
typedef struct llaAdapterObject_s llaAdapter_t;

/* Type for service routines */

/*
 *   This data type is used when retreiving the present status of the local node.
 */
typedef struct llaPresentStatus_s
{
	unsigned phyId;						/* IEEE 1394-1995 Std 4.3.8 */
	unsigned gapCount;					/* IEEE 1394-1995 Std 4.3.8 */
	unsigned phySpeed;					/* IEEE 1394-1995 Std 4.3.7 */
	bool forceRoot;						/* IEEE 1394-1995 Std 4.3.8 */
	bool cablePowerActive;				/* IEEE 1394-1995 Std 4.3.8 */
	bool initiatedReset;				/* IEEE 1394-1995 Std 4.3.8 */
	bool busRoot;						/* IEEE 1394-1995 Std 4.3.8 */

	struct
	{
		unsigned arbARx;				/* IEEE 1394-1995 Std 4.2.2 */
		unsigned arbBRx;				/* IEEE 1394-1995 Std 4.2.2 */
		bool child;						/* IEEE 1394-1995 Std 4.3.9 */
		bool connected;					/* IEEE 1394-1995 Std 4.3.9 */

	} port[IEEE1394_NPORT_MAX];

	unsigned numberOfPorts;

} llaPresentStatus_t;


/*
 *   This data type defines the physical ID of a node concerned by a configuration packet.
 */
typedef struct llaPhyId_s
{
	unsigned phyId;						/* Physical ID */
	unsigned genCount;					/* Gen count for which phy id is valid*/

} llaPhyId_t;


/*
 *   This data type describes a node ID.
 */
typedef struct llaNodeId_s
{
	unsigned busId;						/* IEEE 1394-1995 Std paragraph 8.3.2.3.1 */
	unsigned phyId;						/* IEEE 1394-1995 Std paragraph 8.3.2.3.2 */
	unsigned genCount;					/* Gen count for which node id is valid*/

} llaNodeId_t;


/*
 *   This data type describes a list of isochronous channel.
 */
typedef struct llaChanList_s
{
	unsigned listLength;
	unsigned list[IEEE1394_MAX_NB_CHANNEL];

} llaChanList_t;


/*
 *  Data type used when configuring a list of isochronous channel the node will listen
 *  on (llaSetChannelList). Note that some features are only supported by OHCI chipset.
 *  Using an OHCI feature on a non-OHCI chipset will issue an error.
 */
typedef struct llaChanListConfig_s
{
	int *ctxHandle;						/* Context handle pointer */

	unsigned configFlags;				/* Configuration flag */
	unsigned tagMatch;					/* Tag match value */
	unsigned syncMatch;					/* Synchro field to compare */
	unsigned cycleDelay;				/* Delay in 125us unit, before accepting the first packet */

	llaChanList_t chanList;				/* Channel list to listen on */

} llaChanListConfig_t;


/*
 *  This data type represents an asynchronous packet header
 */
typedef struct llaAsyHdr_s
{
	uint32_t destinationLow;			/* IEEE 1394-1995 Std 6.2.4.2.2 */
	unsigned destinationHigh;			/* IEEE 1394-1995 Std 6.2.4.2.2 */
	unsigned dataLength;				/* IEEE 1394-1995 Std 6.2.4.8 */
	unsigned transactionCode;			/* IEEE 1394-1995 Std 6.2.4.5 */
	unsigned extendedTransactionCode;	/* IEEE 1394-1995 Std 6.2.4.9 */
	unsigned transactionLabel;			/* IEEE 1394-1995 Std 6.2.4.3 */
	unsigned retryCode;					/* IEEE 1394-1995 Std 6.2.4.4 */
	unsigned responseCode;				/* IEEE 1394-1995 Std 6.2.4.10 */
	unsigned priority;					/* IEEE 1394-1995 Std 6.2.4.6 */
	unsigned speed;						/* IEEE 1394-1995 Std Table 4-2 */
	unsigned timeStamp;					/* cycle timer compare value */

	llaNodeId_t srcNodeId;				/* IEEE 1394-1995 Std 6.2.4.7 */
	llaNodeId_t destNodeId;				/* IEEE 1394-1995 Std 6.2.4.2.1 */

} llaAsyHdr_t;


/*
 *  This data type represents an isochronous packet header.
 */
typedef struct llaIsoHdr_s
{
	unsigned dataLength;				/* IEEE 1394-1995 Std 6.2.4.8 */
	unsigned tag;						/* IEEE 1394-1995 Std 6.2.4.12 */
	unsigned channel;					/* IEEE 1394-1995 Std 6.2.4.13 */
	unsigned synchro;					/* IEEE 1394-1995 Std 6.2.4.14 */
	unsigned speed;						/* IEEE 1394-1995 Std Table 4-2 */
	unsigned timeStamp;					/* cycle timer compare value */
	bool skip;							/* Skip packet enable flag */
	bool cycleMatch;					/* Cycle match enable flag */

} llaIsoHdr_t;



/*
 *  This data type describes a received selfid packet.
 */
typedef struct llaConfigIn_s
{
	uint32_t *list;
	unsigned listLength;
	unsigned genCount;

} llaConfigIn_t;


/*
 *  This data type describes a received selfid packet.
 */
typedef struct llaLkEvent_s
{
	unsigned event;
	unsigned genCount;

} llaLkEvent_t;

/* !+!jpo modify Unsupported comments //!+![sro] #pragma pack(1) */

/* If compiling for big endian CPU */

#if	_BYTE_ORDER == _BIG_ENDIAN
/* Physical-layer events */
typedef struct llaPhEvent_s
{
	unsigned			event;
	union
	{
		uint32_t		quadlet;
		struct
		{
			uint32_t	pkType:2;		/* PHY packet type */
			uint32_t	phyId:6;		/* Physical Id */
			uint32_t	:2;
			uint32_t	extType:4;		/* Extended PHY packet type */
			uint32_t	:18;
		} generic;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	root:1;
			uint32_t	:23;
		} busResetComplete;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	root:1;
			uint32_t	:23;
		} selfIdComplete;
		union
		{
			struct
			{
				uint32_t :2;
				uint32_t phyId:6;
				uint32_t next:1;		/* 0 = first packet for this node */
				uint32_t activeLink:1;
				uint32_t gapCount:6;
				uint32_t speed:2;
				uint32_t :2;
				uint32_t contender:1;
				uint32_t powerClass:3;
				uint32_t port0:2;
				uint32_t port1:2;
				uint32_t port2:2;
				uint32_t initiatedReset:1;
				uint32_t more:1;		/* 1 = more self-id paquet to come */
			} packet0;
			struct
			{
				uint32_t :2;
				uint32_t phyId:6;
				uint32_t next:1;		/* 1 = second or third packet for this node */
				uint32_t n:3;
				uint32_t :2;
				uint32_t port3:2;
				uint32_t port4:2;
				uint32_t port5:2;
				uint32_t port6:2;
				uint32_t port7:2;
				uint32_t port8:2;
				uint32_t port9:2;
				uint32_t port10:2;
				uint32_t :1;
				uint32_t more:1;
			} packet1;
			struct
			{
				uint32_t :2;
				uint32_t phyId:6;
				uint32_t next:1;
				uint32_t n:3;
				uint32_t :2;
				uint32_t port11:2;
				uint32_t port12:2;
				uint32_t port13:2;
				uint32_t port14:2;
				uint32_t port15:2;
				uint32_t :8;
			} packet2;
		} selfId;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:24;
		} linkOn;
		struct
		{
			uint32_t	:2;
			uint32_t	rootId:6;
			uint32_t	setForceRoot:1;
			uint32_t	setGapCount:1;
			uint32_t	gapCount:6;
			uint32_t	:16;
		} phyCfg;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:24;
		} ping;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:2;
			uint32_t	regType:4;
			uint32_t	page:3;
			uint32_t	port:4;
			uint32_t	reg:3;
			uint32_t	:8;
		} remAcc;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:2;
			uint32_t	regType:4;
			uint32_t	page:3;
			uint32_t	port:4;
			uint32_t	reg:3;
			uint32_t	data:8;
		} remReply;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:9;
			uint32_t	port:4;
			uint32_t	:8;
			uint32_t	cmd:3;
		} remCmd;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:9;
			uint32_t	port:4;
			uint32_t	:3;
			uint32_t	fault:1;
			uint32_t	connected:1;
			uint32_t	bias:1;
			uint32_t	disabled:1;
			uint32_t	ok:1;
			uint32_t	cmd:3;
		} remConf;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:24;
		} resume;
		struct
		{
			uint32_t	:2;
			uint32_t	phyId:6;		/* remote Node ID */
			uint32_t	:2;
			uint32_t	type:4;			/* Extended PHY packet type */
			uint32_t	:2;
			uint32_t	delay:16;		/* in unit of 49.152 MHz clock cycle */
		} pingResp;
	} packet;
	unsigned			genCount;

} llaPhEvent_t;

/* If compiling for little endian CPU */

#elif _BYTE_ORDER == _LITTLE_ENDIAN
typedef struct llaPhEvent_s
{
	unsigned			event;
	union
	{
		uint32_t		quadlet;
		struct
		{
			uint32_t	:18;
			uint32_t	extType:4;		/* Extended PHY packet type */
			uint32_t	:2;
			uint32_t	phyId:6;		/* Physical Id */
			uint32_t	pkType:2;		/* PHY packet type */
		} generic;
		struct
		{
			uint32_t	:23;
			uint32_t	root:1;
			uint32_t	phyId:6;
			uint32_t	:2;
		} busResetComplete;
		struct
		{
			uint32_t	:23;
			uint32_t	root:1;
			uint32_t	phyId:6;
			uint32_t	:2;
		} selfIdComplete;
		union
		{
			struct
			{
				uint32_t more:1;		/* 1 = more self-id paquet to come */
				uint32_t initiatedReset:1;
				uint32_t port2:2;
				uint32_t port1:2;
				uint32_t port0:2;
				uint32_t powerClass:3;
				uint32_t contender:1;
				uint32_t :2;
				uint32_t speed:2;
				uint32_t gapCount:6;
				uint32_t activeLink:1;
				uint32_t next:1;		/* 0 = first packet for this node */
				uint32_t phyId:6;
				uint32_t :2;

			} packet0;
			struct
			{
				uint32_t more:1;
				uint32_t :1;
				uint32_t port10:2;
				uint32_t port9:2;
				uint32_t port8:2;
				uint32_t port7:2;
				uint32_t port6:2;
				uint32_t port5:2;
				uint32_t port4:2;
				uint32_t port3:2;
				uint32_t :2;
				uint32_t n:3;
				uint32_t next:1;		/* 1 = second or third packet for this node */
				uint32_t phyId:6;
				uint32_t :2;
			} packet1;
			struct
			{
				uint32_t :8;
				uint32_t port15:2;
				uint32_t port14:2;
				uint32_t port13:2;
				uint32_t port12:2;
				uint32_t port11:2;
				uint32_t :2;
				uint32_t n:3;
				uint32_t next:1;
				uint32_t phyId:6;
				uint32_t :2;
			} packet2;
		} selfId;
		struct
		{
			uint32_t	:24;
			uint32_t	phyId:6;
			uint32_t	:2;

		} linkOn;
		struct
		{
			uint32_t	:16;
			uint32_t	gapCount:6;
			uint32_t	setGapCount:1;
			uint32_t	setForceRoot:1;
			uint32_t	rootId:6;
			uint32_t	:2;
		} phyCfg;
		struct
		{
			uint32_t	:24;
			uint32_t	phyId:6;
			uint32_t	:2;
		} ping;
		struct
		{
			uint32_t	:8;
			uint32_t	reg:3;
			uint32_t	port:4;
			uint32_t	page:3;
			uint32_t	regType:4;
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:2;
		} remAcc;
		struct
		{
			uint32_t	data:8;
			uint32_t	reg:3;
			uint32_t	port:4;
			uint32_t	page:3;
			uint32_t	regType:4;
			uint32_t	:2;
			uint32_t	phyId:6;
			uint32_t	:2;
		} remReply;
		struct
		{
			uint32_t	cmd:3;
			uint32_t	:8;
			uint32_t	port:4;
			uint32_t	:9;
			uint32_t	phyId:6;
			uint32_t	:2;
		} remCmd;
		struct
		{
			uint32_t	cmd:3;
			uint32_t	ok:1;
			uint32_t	disabled:1;
			uint32_t	bias:1;
			uint32_t	connected:1;
			uint32_t	fault:1;
			uint32_t	:3;
			uint32_t	port:4;
			uint32_t	:9;
			uint32_t	phyId:6;
			uint32_t	:2;
		} remConf;
		struct
		{
			uint32_t	:24;
			uint32_t	phyId:6;
			uint32_t	:2;
		} resume;
		struct
		{
			uint32_t	delay:16;		/* in unit of 49.152 MHz clock cycle */
			uint32_t	:2;
			uint32_t	type:4;			/* Extended PHY packet type */
			uint32_t	:2;
			uint32_t	phyId:6;		/* remote Node ID */
			uint32_t	:2;
		} pingResp;
	} packet;
	unsigned			genCount;

} llaPhEvent_t;

#else
	#error _BYTE_ORDER must be defined to either _LITTLE_ENDIAN or _BIG_ENDIAN
#endif /* _BYTE_ORDER */

#define LLA_HW_CONT_SIZE	(2048)		/* !+! [sro] size in bytes */

/*
 *  This data type is used when dumping hardware registers
 */
typedef char llaHwCont_t[LLA_HW_CONT_SIZE];


/*
 *   This data type describes the prototype of the interrupt callback.
 */
typedef void (llaIntCb_t)
(
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the cycle indication callback prototype.
 */
typedef void (llaCycleCb_t)
(
	unsigned cycleCount,				/* Current cycle count */
	unsigned secondCount,				/* Current cycle count */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the bus event indication callback prototype.
 */
typedef void (llaBusEventCb_t)
(
	unsigned busEvent,					/* Bus event */
	unsigned genCount,					/* Generation count */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the asynchronous packet reception callback prototype.
 */
typedef void (llaAsyInCb_t)
(
	dbuf_t *pData,						/* Describe the raw packet received */
	unsigned status,					/* Reception status */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the isochronous packet reception callback prototype.
 */
typedef void (llaIsoInCb_t)
(
	dbuf_t *pData,						/* Describe the receive packet */
	unsigned status,					/* Reception status */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the configuration packet reception callback prototype.
 */
typedef void (llaConfigInCb_t)
(
	llaConfigIn_t *pConfigIn,
	void *pContext 						/* Context passed when registering */
);



/*
 *   This data type describes the link event indication callback prototype.
 */
typedef void (llaLkEventCb_t)
(
	llaLkEvent_t *pLkEvent,
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the physical event callback prototype.
 */
typedef void (llaPhEventCb_t)
(
	llaPhEvent_t *pPhEvent,				/* Packet information */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the isochronous confirmation callback prototype.
 */
typedef void (llaIsoOutCb_t)
(
	unsigned status,					/* Transmission status */
	unsigned timeStamp,					/* Cycle timer val when the pkt was tx*/
	dbuf_t *pData,						/* Dynbuf used for tx */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the asynchronous confirmation callback prototype.
 */
typedef void (llaAsyOutCb_t)
(
	unsigned status,					/* Transmission status */
	unsigned acknowledge,				/* Acknowledge value */
	dbuf_t *pData,						/* Dynbuf used for tx */
	void *pContext						/* Context passed when registering */
);


/*
 *   This data type describes the posted write failure callback prototype.
 */
typedef void (llaPostWrFailCb_t)
(
	llaNodeId_t *pNodeId,				/* !+! */
	unsigned destOffsetHigh,			/* !+! */
	uint32_t destOffsetLow,				/* !+! */
	void *pContext						/* !+! */
);


/*
 *   This data type describes callback prototype used by the library whenever
 *   it has a reception dynbuf ready to be receycled.
 */
typedef void (llaRecycleDbufCb_t)
(
	dbuf_t *pData,						/* !+! */
	void *pContext						/* !+! */
);


/* prototypes */


/* Initialize library */
int llaInit(void);

/* Free resource */
void llaRelease(void);

/* Get a handle on the selected 1394 card */
llaAdapter_t *llaAttach(unsigned index);

/* Free the selected 1394 card */
int llaDetach(llaAdapter_t *pAdapter);

/* Count adapters availlable in the system */
unsigned llaGetAdapterCount(void);

/* Get information about a given adapter */
int llaGetRomInfo(unsigned index, romInfo_t *info);



/*
 *      PH_CONT.req services
 */


/* PH_CONT.req - Perform a bus reset */
int llaBusReset
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_CONT.req - Perform a short bus reset */
int llaShortBusReset
(
	llaAdapter_t *adpHandle				/* Handle on the adapter */
);


/* PH_CONT.req - Disable transmission at the PHY layer level. */
int llaDisableTransmit
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_CONT.req - Enable transmission at the PHY layer level. */
int llaEnableTransmit
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_CONT.req - Get the present status of the node */
int llaGetPresentStatus
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaPresentStatus_t *pPresentStatus	/* ptr to an empty structure */
);

/* PH_CONT.req - Activate the link layer. */
int llaSetLinkActive
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_CONT.req - Set the local gap count. */
int llaSetGapCount
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned value						/* gap count value */
);

/* PH_CONT.req - Ask to become the bus root at the next bus reset. */
int llaSetForceRoot
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_CONT.req - Cancel the bus root at the next bus reset. */
int llaClearForceRoot
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_UTIL.req - Get the local phy id */
int llaGetPhyId
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaPhyId_t *pPhyId					/* Current PHY id and gen count */
);

/* PH_UTIL.req - Get the power of the local node */
int llaGetPwrClass
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_UTIL.req - Get the current bus reset ID. */
int llaGetGenerationCount
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned *pGenCount					/* Generation count output pointer */
);

/* PH_UTIL.req - Unactivate the link layer. */
int llaSetLinkOff
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_UTIL.req - Set the node as the bus contender. */
int llaSetContender
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_UTIL.req - Cancel the node as the bus contender. */
int llaClearContender
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* PH_EVENT.ind - Install callback on PH_EVENT.ind service */
int llaSetPhEventCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaPhEventCb_t *pCallback,			/* indication callback routine */
	void *pContext						/* context for callback */
);

/* LK_CONT.req - Reset the link layer. */
int llaLinkReset
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* LK_CONT.req - Initialize the link layer. */
int llaLinkInitialize
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* !+! */
int llaSetCycleConfig
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned source,					/* Cycle source */
	unsigned period						/* Cycle period */
);

/* LK_CONT.req - Start genaration of cycle start packet. */
int llaEnableCycleMaster
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* LK_CONT.req - Stop genaration of cycle start packet. */
int llaDisableCycleMaster
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* LK_CONT.req - Set the node ID. In OHCI implementation, only the bus number can be set. */
int llaSetNodeId
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaNodeId_t *pNodeId			/* Node ID to set */
);

/* LK_CONT.req - Get the node ID. */
int llaGetNodeId
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaNodeId_t *pNodeId				/* Node ID to get */
);

/* LK_CONT.req - Get request channel list */
int llaGetChannelList
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaChanList_t *pChanList			/* Channel list info */
);

/* LK_EVENT.ind - Install callback on LK_EVENT.ind service */
int llaSetLkEventCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaLkEventCb_t *pCallback,			/* !+! */
	void *pContext						/* !+! */
);

/* LK_CONFIG.req - Send a link on packet. */
int llaSendLinkOnPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaPhyId_t *pPhyId			/* Physical id of the destination */
);

/* LK_CONFIG.req - Send a PHY config packet. */
int llaSendPhyConfigPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	bool setForceRoot,					/* If the pkt is to set a root */
	const llaPhyId_t *pRootPhyId,		/* Node ID of the next root */
	bool setGapCount,					/* If the pkt is to set gap cnt*/
	unsigned gapCountValue				/* New gap count value */
);

/* LK_CONFIG.req - Send a ping packet. */
int llaSendPingPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaPhyId_t *pPhyId			/* Destination Phy ID*/
);

/* LK_CONFIG.req - Send a remote command. */
int llaSendRemCmdPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaPhyId_t *pPhyId,			/* Destination PHY ID*/
	unsigned port,						/* Port number */
	unsigned cmd						/* Command */
);

/* LK_CONFIG.req - Send a remote access. */
int llaSendRemAccPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaPhyId_t *pPhyId,			/* Destination PHY ID */
	unsigned page,						/* Page to access */
	unsigned port,						/* Port to access */
	unsigned reg,						/* Register to access */
	unsigned regType					/* Register type */
);

/* LK_CONFIG.req - Send a resume access. */
int llaSendResumePkt
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* LK_CONFIG.ind - Install callback on config packet reception */
int llaSetConfigInCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaConfigInCb_t *pCallback,			/* Callback pointer */
	void *pContext						/* context for callback */
);

/* LK_DATA.req - Send a quadlet write request packet */
int llaSendQWriteReqPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	uint32_t quadlet,					/* quadlet to transmit */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext						/* confirmation context */
);


/* LK_DATA.req - Send a quadlet read request packet */
int llaSendQReadReqPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext						/* confirmation context */
);

/* LK_DATA.req - Send a block write request packet */
int llaSendBWriteReqPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	dbuf_t *pData,						/* dynbuf to transmit (payload) */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext						/* confirmation context */
);

/* LK_DATA.req - Send a block read request packet */
int llaSendBReadReqPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext						/* confirmation context */
);

/* LK_DATA.req - Send a lock request packet */
int llaSendLockReqPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	dbuf_t *pData,						/* Packet payload	  	*/
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext						/* confirmation context */
);

/* LK_DATA.resp - Send a quadlet read response packet */
int llaSendQReadRespPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	uint32_t quadlet,					/* quadlet to transmit */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback */
	void *pContext,						/* confirmation context */
	unsigned timeout					/* Timeout in 125탎 unit */
);

/* LK_DATA.resp - Send a block read response packet */
int llaSendBReadRespPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	dbuf_t *pData,						/* dynbuf to transmit */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext,						/* confirmation context */
	unsigned timeout					/* Timeout in 125탎 unit*/
);

/* LK_DATA.resp - Send a write response packet */
int llaSendWriteRespPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext,						/* confirmation context */
	unsigned timeout					/* Timeout in unit of 125 탎 */
);

/* LK_DATA.resp - Send a lock response packet */
int llaSendLockRespPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaAsyHdr_t *pHeader,			/* asy common header */
	dbuf_t			*pData,				/* Packet payload	  	*/
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext,						/* confirmation context */
	unsigned timeout					/* Timeout in unit of 125 탎 */
);

/* LK_DATA.ind - Install callback on async packet reception */
int llaSetAsyInCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaAsyInCb_t *pCallback,			/* Cback done upon pk rx*/
	void *pContext,						/* context for callback */
	unsigned packetType					/* Pkt type:req or resp*/
);

/* LK_BUS.ind - Install callback on LK_BUS.ind service */
int llaSetBusEventCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaBusEventCb_t *pCallback,			/* callback ptr */
	void *pContext						/* context for callback */
);

/* LK_ISO_CONT.req - Setup an isochronous channel to listen to. */
int llaSetChannelList
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaChanListConfig_t *pChanListConfig	/* Config info */
);

/* LK_ISO.req - Send an isochronous packet */
int llaSendIsoPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaIsoHdr_t *pHeader,			/* iso header */
	dbuf_t *pData,						/* dynBuf to transmit */
	llaIsoOutCb_t *pCallback,			/* Confirmation cback */
	void *pContext						/* context returned to cback above */
);

/* LK_ISO.req - Send an asynchronous stream packet */
int llaSendAsyStreamPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	const llaIsoHdr_t *pHeader,			/* iso header */
	dbuf_t *pData,						/* dynBuf to transmit */
	llaAsyOutCb_t *pConfCb,				/* confirmation callback*/
	void *pContext						/* context returned to cback above */
);

/* LK_ISO.ind - Install callback on LK_ISO.ind service */
int llaSetIsoInCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	int ctxHandle,						/* Context handle recv when config */
	llaIsoInCb_t *pCallback,			/* Cback done upon each rceived pkts */
	void *pContext
);

/* LK_CYCLE.ind - Install callback on LK_CYCLE.ind service */
int llaSetCycleCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaCycleCb_t *pCallback,			/* !+! */
	void *pContext						/* !+! */
);

/* CSR_CONT.req - Read a CSR */
int llaCsrRead
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* CSR address */
	uint32_t *pValue					/* !+! */
);

/* CSR_CONT.req - Write to a CSR */
int llaCsrWrite
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* CSR address */
	uint32_t value						/* Value to write */
);

/* CSR_CONT.req - Perform a lock access to a CSR */
int llaCsrLock
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* CSR address */
	uint32_t oldValue,					/* !+! */
	uint32_t *pNewValue					/* !+! */
);

/* SW_CONT.req - Enable reception of asynchronous packets */
int llaStartAsyRecv
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	dbuf_t *pData,						/* dynbuf list for recv */
	unsigned configFlag,				/* configuration flag */
	unsigned fCount,					/* callback frequency */
	llaRecycleDbufCb_t *pIndCb,			/* indication callback */
	void *pContext						/* indication context */
);

/* SW_CONT.req - Disable reception of asynchronous packets */
int llaStopAsyRecv
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	dbuf_t **ppData,					/* unused dynbuf returned here */
	unsigned configFlag					/* Request or response */
);

int llaPauseAsyRecv
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned configFlag					/* configuration flag */
);

int llaResumeAsyRecv
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned configFlag					/* configuration flag */
);


/* SW_CONT.req - Enable reception of isochronous packets */
int llaStartIsoRecv
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	dbuf_t *pData,						/* dynbuf list for recv */
	int ctxHandle,						/* Context handle */
	unsigned nbOfBytes,					/* Number of bytes */
	unsigned configFlag,				/* Configuration flag */
	unsigned fCount,					/* callback frequency */
	llaRecycleDbufCb_t *pIndCb,			/* indication callback */
	void *pContext						/* indication context */
);

/* SW_CONT.req - Disable reception of isochronous packets */
int llaStopIsoRecv
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	dbuf_t **ppData,					/* dynbuf list for recv */
	int ctxHandle						/* Get from llaSetChannelList */
);

/* SW_CONT.req - Bind a callback to a specific event. */
int llaSetIntCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned interrupt,					/* Interrupt to monitor */
	llaIntCb_t *pCallback,				/* !+! */
	void *pContext						/* !+! */
);

/* SW_CONT.req - Unbind callback from an event */
int llaClearIntCb
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned interrupt					/* Interrupt to monitor */
);

/* SW_CONT.req - Perform a manual isochronous cycle */
int llaDoIsoCycle
(
	llaAdapter_t *pAdapter				/* Handle on the device */
);

/* SW_CONT.req - Hard or soft reset the device */
int llaDeviceReset
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned resetType					/* software or hardware */
);

/* SW_CONT.req - Enable auto response feature on the local node */
int llaAutoResp
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	uint32_t nodesHigh,					/* Nodes 32 to 62 */
	uint32_t nodesLow,					/* Nodes 0 to 31 */
	unsigned configFlag,				/* Service configuration flag */
	llaPostWrFailCb_t *pCallback,		/* Posted write failure cback */
	void *pContext						/* Context returned to cback above */
);

/* SW_DECODE.req - Decode an asychronous packet */
int llaDecodeAsyPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaAsyHdr_t *pHeader,				/* !+! */
	dbuf_t *pData						/* !+! */
);

/* SW_DECODE.req - Decode an isochronous packet */
int llaDecodeIsoPkt
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaIsoHdr_t *pHeader,				/* Iso header */
	dbuf_t *pData,						/* Spawn dynbuf rx in rx cback */
	unsigned rxMode						/* Reception mode */
);

/* SW_DECODE.req - Get the next iso packet in a buffer filled */
dbuf_t *llaGetNextIsoPacket
(
	llaAdapter_t	*pAdapter,	/* Handle on the device */
	dbufPool_t		*pPool,		/* Pool where the returned dbuf will be took */	
	dbuf_t			*pOriData	/* Original dbuf rx from cback */
);

/* HW_CONT.req - Dump all the link layer registers (OHCI) */
int llaDumpLinkLayerRegisters
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaHwCont_t *pHwCont				/* !+! */
);

/* HW_CONT.req - Write to an OHCI register */
int llaWriteLinkRegister
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset to write (bytes)*/
	uint32_t value						/* Value to write */
);

/* HW_CONT.req - Read an OHCI register */
int llaReadLinkRegister
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset (in bytes) */
	uint32_t *pValue					/* Value returned here */
);

/* HW_CONT.req - Set a bit of an OHCI register */
int llaSetLinkBit
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset (in bytes)*/
	uint32_t mask						/* Mask with the bit to set at 1*/
);

/* HW_CONT.req - Clear a bit of an OHCI register */
int llaClearLinkBit
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset (in bytes)*/
	uint32_t mask						/* Mask with the bit to set at 1*/
);

/* HW_CONT.req - Dump all readable registers of the physical layer. */
int llaDumpPhyLayerRegisters
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	llaHwCont_t *pHwCont				/* !+! */
);

/* HW_CONT.req - Write to a register of the physical layer. */
int llaWritePhyRegister
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset (in bytes) */
	uint8_t value						/* Value to write */
);

/* HW_CONT.req - Read a register of the physical layer. */
int llaReadPhyRegister
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset (in bytes) */
	uint8_t *pValue						/* Value returned here */
);

/* HW_CONT.req - Set a bit of a register of the physical layer. */
int llaSetPhyBit
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset */
	uint8_t mask						/* Mask with bit to set at 1*/
);

/* HW_CONT.req - Clear a bit of a register of the phy layer. */
int llaClearPhyBit
(
	llaAdapter_t *pAdapter,				/* Handle on the device */
	unsigned offset,					/* Register offset */
	uint8_t mask						/* Mask with bit to set at 1*/
);


/* llaGetLastError - return the last Error code value */
int llaGetLastError(void);



#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif /* __INCllah */
