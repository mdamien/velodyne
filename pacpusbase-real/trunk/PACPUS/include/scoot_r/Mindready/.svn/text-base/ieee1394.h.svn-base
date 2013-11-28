/* ieee1394.h - IEEE Std 1394-1995 and IEEE Std 1394a-2000 Standards defines */

/* Copyright(c) 1999, Sederta Inc. All rights reserved. */

/*
 * $Log: /Common/Design/Src/misc/Dev/winNT4/main/inc/ieee1394.h $
 * 
 * 16    8/28/01 3:36p Sro
 * Addition of an LK_DATA.ind status - IEEE1394_COMPLETE
 *
 * 15    4/03/01 15:33 Blc
 * Added IEEE1394_MAX_NB_CHANNELS as a replacement for misspelled constant
 * IEEE1394_MAX_NB_CHANNEL.
 *
 * 14    4/03/01 1:14p Sparadis
 * Added size of OHCI packet headers in transmission
 *
 * 13    3/27/01 14:21 Blc
 * Added two constants to identify the local bus id and the broadcast phy
 * id.
 *
 * 12    3/09/01 15:48 Blc
 * Added constant IEEE1394_MAX_NB_NODES which replaces incorrectly defined
 * (and wrongly spelled) constant IEEE1394_MAX_NB_NODE.
 *
 * 11    3/05/01 3:02p Jpou
 * Reordered extended phy codes sequence.
 *
 * 10    2/20/01 5:03p Jfha
 * Change comment type
 *
 * $NoKeywords: $
 */

/*
01y,07feb01,blc Added tokens to identify ports in self-id packets.
01x,06feb01,blc Added a token to identify the pseudo-packet Ping Response
01w,02feb01,blc Replaced IEEE1394_RETRY_0 with IEEE1394_RETRY_1.
				Replaced IEEE1394_SELF_ID with OHCI_TCODE_PHY_PK.
				Created tcode IEEE1394_TCODE_INTERNAL.
				Added PHY event IEEE1394_SELF_ID_RCV.
				Added and reviewed macros to handle PHY packets.
01v,21jan01,blc Added PHY events for extended PHY packets.
01u,10Oct00,spa Added OHCI packets header size.
01t,21Sep00,spa Added IEEE1394_MAX_NB_NODE define.
01s,15Sep00,spa Added IEEE1394_MAX_NB_CHANNEL define.
01p,18Aug00,apou Added IEEE1394_ACK_TARDY for 1394a
01r,31Jul00,spa Added IEEE1394_SPEED_MASK define.
01q,28Jul00,spa Completed extended phy packet definition
01p,14Jun00,spa Added extended phy packet stuff
01o,25May00,spa Added IEEE1394_SPEED_SHFT for OHCI compatibility
01o,01Feb00,pdr IEEE1394_SPEED_SHFT added
01n,11Oct99,fb4 IEEE1394_SELFID_ID to IEEE1394_SELFID_PKID
01m,10Aug99,fb4 Updated copyright
01l,16Jul99,fb4 Added IEEE1394_LKON_PKID and definition of phy-config packet
01k,9Jul99,fb4 Added link-on paket definition
01j,9Jul99,fb4 Added definition of link-On packet
01i,20May99,fb4 Added IEEE1394_CHILD, IEEE1394_PARENT, IEEE1394_NOT_CONNECTED
                and IEEE1394_NOT_PRESENT
01h,17May99,fb4 Added defines for self-id packets
01g,3May99,jou Updated IEEE1394_OFFSETLOW_MASK from 0xFFFFFFFC to 0xFFFFFFFF
01f,30Apr99,fb4 Added IEEE1394_RELEASE define
01e,29Apr99,fb4 Added IEEE1394_CRC_ISOCH_PLOAD and IEEE1394_ISOCH_PLOAD
01d,18Apr99,fb4 Updated LK_DATA.conf and LK_DATA.ind constants for 2 bits coding
01c,18Apr99,fb4 Added header length
01b,23Mar99,fb4 Updated data payload
01a,17Mar99,fb4 This file was created
*/

/*
This module contains IEEE 1394-1995 and IEEE 1394a Standards defines.
*/

#ifndef __INCieee1394h
#define __INCieee1394h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */

/* defines */

/* Used for debugging purpose */

#define IEEE1394_RELEASE 1

/* General purpose constants */

#define IEEE1394_CHANNEL_LIST_LENGTH	2	/* Max. number of iso. channel */
											/* that can be listened at a time*/
#define IEEE1394_NPORT_MAX				27	/* Maximum number of port of the */
											/* physical layer */

/* Physical constants. See IEEE 1394-1995 Standard Paragraph 4.2.2 */

#define IEEE1394_ARB_A_RX_0		0x0
#define IEEE1394_ARB_A_RX_1		0x1
#define IEEE1394_ARB_A_RX_Z		0x3
#define IEEE1394_ARB_B_RX_0		0x0
#define IEEE1394_ARB_B_RX_1		0x1
#define IEEE1394_ARB_B_RX_Z		0x3

/* Speed constants. See IEEE 1394-1995 Standard Table 4-2 */

#define IEEE1394_SPEED_SHFT		16		/* 1394 OHCI specific */
#define IEEE1394_SPEED_MASK		0x7
#define IEEE1394_100MBITS_SPEED	0x0		/* 100 Mbits rate */
#define IEEE1394_200MBITS_SPEED	0x1		/* 200 Mbits rate */
#define IEEE1394_400MBITS_SPEED	0x2		/* 400 Mbits rate */
#define IEEE1394_100MBITS_DATA	512		/* Max. amount of data at 100Mbits */
#define IEEE1394_200MBITS_DATA	1024	/* Max. amount of data at 200Mbits */
#define IEEE1394_400MBITS_DATA	2048	/* Max. amount of data at 400Mbits */

/*
 * Node identification constants in asynchronous packets.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.7
 */

#define IEEE1394_BUS_NUMBER_SHFT	22		/* Bus number bits shift */
#define IEEE1394_BUS_NUMBER_MASK	0x3FF	/* Bus number bits mask */
#define IEEE1394_BUS_NUMBER_MIN		0x0		/* Min. bus number */
#define IEEE1394_BUS_NUMBER_MAX		0x3FF	/* Max. bus number */
#define IEEE1394_NODE_NUMBER_SHFT	16		/* Node number bits shift */
#define IEEE1394_NODE_NUMBER_MASK	0x3F	/* Node number bits mask */
#define IEEE1394_NODE_NUMBER_MIN	0x0		/* Min. node number */
#define IEEE1394_NODE_NUMBER_MAX	0x3F	/* Max. node number */

/* See IEEE Std 1394-1995 Paragraph 6.2.4.2.1 */
#define IEEE1394_BUS_ID_LOCAL		0x3FF	/* Bus ID value identifying the local bus */
#define IEEE1394_PHY_ID_BROADCAST	0x3F	/* Physical ID value used for broadcasting to all nodes on a bus */

/* The use of IEEE1394_MAX_NB_NODE(64) is deprecated since a valid physical ID */
/* must be in th erange 0..62. The correct constant is IEEE1394_MAX_NB_NODES(63). */
#define IEEE1394_MAX_NB_NODE		64		/* Max qty of node on a bus */
#define IEEE1394_MAX_NB_NODES		63		/* Maximum number of nodes on a bus */

/*
 * Retry code constants in asynchronous packets.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.4
 */

#define IEEE1394_RETRY_CODE_SHFT	8	/* Retry code bits shift */
#define IEEE1394_RETRY_CODE_MASK	0x3 /* Retry code bits mask */
#define IEEE1394_RETRY_1			0x0 /* Value for retry code 1 */
#define IEEE1394_RETRY_X			0x1 /* Value for retry code X */
#define IEEE1394_RETRY_A			0x2 /* Value for retry code A */
#define IEEE1394_RETRY_B			0x3 /* Value for retry code B */

/*
 * The use of IEEE1394_RETRY_0 is deprecated.
 * This code is replaced with IEEE1394_RETRY_1.
 * IEEE1394_RETRY_0 is kept for backward compatibility
 * and will be removed in future release.
 */

#define IEEE1394_RETRY_0			IEEE1394_RETRY_1

/*
 * Transaction label constants in asynchronous packets.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.3
 */

#define IEEE1394_TLABEL_SHFT	10		/* Transaction label bits shift */
#define IEEE1394_TLABEL_MASK	0x3F	/* Transaction label bits mask */
#define IEEE1394_TLABEL_MIN		0x0		/* Min. transaction label value */
#define IEEE1394_TLABEL_MAX	0x3F		/* Max. transaction label value */

/*
 * Transaction code constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.5
 */

#define IEEE1394_TCODE_SHFT			4	/* Transaction code bits shift */
#define IEEE1394_TCODE_MASK			0xF	/* Transaction code bits mask */
#define IEEE1394_QUAD_WRREQ			0x0	/* Quadlet write request value */
#define IEEE1394_BLOCK_WRREQ		0x1	/* Block write request value */
#define IEEE1394_WRRESP				0x2	/* Write response value */
#define IEEE1394_QUAD_RDREQ			0x4	/* Quadlet read request value */
#define IEEE1394_BLOCK_RDREQ		0x5	/* Block read request value */
#define IEEE1394_QUAD_RDRESP		0x6	/* Quadlet read response value */
#define IEEE1394_BLOCK_RDRESP		0x7	/* Block read response value */
#define IEEE1394_CYCLE_START_REQ	0x8	/* Isochronous cycle start value */
#define IEEE1394_LOCK_REQ			0x9	/* Lock request value */
#define IEEE1394_ISOBLOCK_REQ		0xA	/* Isochronous block request value */
#define IEEE1394_LOCK_RESP			0xB	/* Lock response value */
#define IEEE1394_TCODE_INTERNAL		0xE	/* Used internally by some link layers (1394a) */

/*
 * The use of IEEE1394_SELF_ID is deprecated. *
 * The recommended code to use is OHCI_TCODE_PHY_PK.
 */

#define IEEE1394_SELF_ID			IEEE1394_TCODE_INTERNAL
#define OHCI_TCODE_PHY_PK			IEEE1394_TCODE_INTERNAL

/*
 * Response code constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.10
 */

#define IEEE1394_RCODE_SHFT				12	/* Response code bits shift */
#define IEEE1394_RCODE_MASK				0xF	/* Response code bits mask */
#define IEEE1394_RCODE_COMPLETE			0x0	/* Response complete value */
#define IEEE1394_RCODE_CONFLICT_ERROR	0x4	/* Resp. conflict error value */
#define IEEE1394_RCODE_DATA_ERROR		0x5	/* Response data error value */
#define IEEE1394_RCODE_TYPE_ERROR		0x6	/* Response type error value */
#define IEEE1394_RCODE_ADDR_ERROR		0x7	/* Response address error value */

/*
 * Priority code constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.6. Cable implementation must set
 * this value to 0.
 */

#define IEEE1394_PRIORITY_SHFT	0	/* Priority bits shift */
#define IEEE1394_PRIORITY_MASK	0x0	/* Priority bits mask */
#define IEEE1394_PRIORITY_MIN	0x0	/* Min. priority value */
#define IEEE1394_PRIORITY_MAX	0xF	/* Max. priority value */

/*
 * Extended transaction code constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.9.
 */

#define IEEE1394_XTCODE_SHFT	0	/* Extended transaction code bits shift */
#define IEEE1394_XTCODE_MASK	0xFF /* Extended transaction code bits mask */
#define IEEE1394_MASK_SWAP		0x1	/* Mask swap value */
#define IEEE1394_COMPARE_SWAP	0x2 /* Compare and swap */
#define IEEE1394_FETCH_ADD		0x3 /* Fetch and add */
#define IEEE1394_LITTLE_ADD		0x4 /* Little add */
#define IEEE1394_BOUNDED_ADD	0x5 /* Bounded */
#define IEEE1394_WRAP_ADD		0x6 /* Wrapp and add */
#define IEEE1394_VENDOR_DEP		0x7 /* Vendor dependent operation */

/*
 * Address offset high and low constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.2
 */

#define IEEE1394_OFFSETHIGH_SHFT	0	/* Offset high bits shift */
#define IEEE1394_OFFSETHIGH_MASK	0xFFFF	/* Offset high bits mask */
#define IEEE1394_OFFSETLOW_SHFT		0	/* Offset low bits shift */
#define IEEE1394_OFFSETLOW_MASK ((uint32_t)(0xFFFFFFFF)) /* Offset low mask */

/*
 * Data length constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.8
 */

#define IEEE1394_DATALENGTH_SHFT	16		/* Data length bits shift */
#define IEEE1394_DATALENGTH_MASK	0xFFFF	/* Data length bits mask */
#define IEEE1394_DATALENGTH_MIN		0		/* Min. data length value */

/*
 * Acknowledge constants in asynchronous packet.
 * See IEEE 1394-1995 Standard Table 6-13
 */

#define IEEE1394_ACK_SHFT		0	/* Acknowledge bits shift */
#define IEEE1394_ACK_MASK		0xF	/* Acknowledge bits shift */
#define IEEE1394_ACK_COMPLETE	0x1	/* Acknowledge complete value */
#define IEEE1394_ACK_PENDING	0x2	/* Acknowledge pending value */
#define IEEE1394_ACK_BUSY_X		0x4	/* Acknowledge busy X value */
#define IEEE1394_ACK_BUSY_A		0x5	/* Acknowledge busy A value */
#define IEEE1394_ACK_BUSY_B		0x6	/* Acknowledge busy B value */
#define IEEE1394_ACK_TARDY		0xB	/* Acknowledge retransmission value */
#define IEEE1394_ACK_DATA_ERROR	0xD	/* Acknowledge data error value */
#define IEEE1394_ACK_TYPE_ERROR	0xE	/* Acknowledge type error value */

/*
 * Channel constants in isochronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.13
 */

#define IEEE1394_CHANNEL_SHFT	8		/* Iso. channel bits shift */
#define IEEE1394_CHANNEL_MASK	0x3F	/* Iso. channel bits mask */
#define IEEE1394_CHANNEL_MIN	0x0		/* Minimum channel value */
#define IEEE1394_CHANNEL_MAX	0x3F	/* Maximum channel value */
#define IEEE1394_MAX_NB_CHANNELS 64		/* Maximum number of isochronous channels */

/* The constant IEEE1394_MAX_NB_CHANNEL is misspelled. */
/* Its use is deprecated. It will be removed in a future release. */
#define IEEE1394_MAX_NB_CHANNEL	IEEE1394_MAX_NB_CHANNELS


/*
 * TAG constants in isochronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.12
 */

#define IEEE1394_TAG_SHFT			14	/* TAG bits shift */
#define IEEE1394_TAG_MASK			0x3	/* TAG bits mask */
#define IEEE1394_TAG_UNFORMATTED	0x0	/* Data unformated value */
#define IEEE1394_TAG_FORMAT1		0x1	/* Reserved */
#define IEEE1394_TAG_FORMAT2		0x2	/* Reserved */
#define IEEE1394_TAG_FORMAT3		0x3	/* Reserved */

/*
 * Synchronization constants in isochronous packet.
 * See IEEE 1394-1995 Standard Paragraph 6.2.4.14
 */

#define IEEE1394_SYNCHRO_SHFT	0	/* Synchronization bits shift */
#define IEEE1394_SYNCHRO_MASK	0xF	/* Synchronization bits mask */
#define IEEE1394_SYNCHRO_MIN	0x0	/* Minimum synchronization value */
#define IEEE1394_SYNCHRO_MAX	0xF	/* Maximum synchronization value */

/*
 * LK_DATA.ind constants. These constants are used to return the status of
 * a packet that was received. See IEEE 1394-1995 Standard Paragraph 6.1.2.3
 */

#define IEEE1394_GOOD			0x0 /* Packet received with no error */
#define IEEE1394_BROADCAST		0x1 /* Broadcast pk received with no err. */
#define IEEE1394_DATA_CRC_ERROR	0x2 /* Data block CRC check failed */
#define IEEE1394_FORMAT_ERROR	0x3 /* Field(s) with invalid value(s) */
#define IEEE1394_COMPLETE		0x4 /* Packet received with no error */

/*
 * LK_DATA.conf constants. These constants are used to return the status of
 * a packet that was sent. See IEEE 1394-1995 Standard Paragraph 6.1.2.2
 */

#define IEEE1394_ACKNOWLEDGE_RECEIVED	0x0 /* Acknowledge received */
#define IEEE1394_ACKNOWLEDGE_MISSING	0x1 /* Acknowledge not received */
#define IEEE1394_BROADCAST_SENT			0x2 /* Broadcast packet sent */

/*
 * LK_EVENT.ind constants. They are used to indicate event detected by the link
 * layer. See IEEE 1394-1995 Standard Paragraph 6.1.1.3
 */

#define IEEE1394_UNEXPECTED_CHANNEL_DETECTED		(1<<0) /* Unallocated */
														/* channel detected */
#define IEEE1394_HEADER_CRC_ERROR_DETECTED			(1<<1) /* Header CRC */
													/* check error detected */
#define IEEE1394_UNKNOWN_TRANSACTION_CODE_DETECTED	(1<<2) /* Invalid */
													/* transaction detected */
#define IEEE1394_BUS_OCCUPANCY_VIOLATION_DETECTED	(1<<3) /* Bus held too */
																/* longer */
#define IEEE1394_CYCLE_TOO_LONG						(1<<4)	/* Too long */
											/* isochronous cycle detected */
#define IEEE1394_DUPLICATE_CHANNEL_DETECTED			(1<<5) /* Two iso. pk */
										/* with the same channel detected */

/*
 * LK_BUS.ind constant. It use to report serial bus event.
 * See IEEE 1394-1995 Standard Paragraph 6.1.2.5
 */

#define IEEE1394_ARB_RESET_GAP	(1<<0) /* Arbitration reset gap detected */

/*
 * PH_EVENT.ind constants. They are used to report events detected by the
 * physical layer.
 */

#define IEEE1394_CABLE_POWER_FAIL	(1<<0) /* Loss of cable power detected */
#define IEEE1394_BUS_RESET_START	(1<<1) /* Bus reset detected */
#define IEEE1394_BUS_RESET_COMPLETE	(1<<2) /* Bus reset completed */
#define IEEE1394_CONFIG_TIMEOUT		(1<<3) /* Self-identification timed out */
#define IEEE1394_LINK_ON			(1<<4) /* Link-On packet received */
#define IEEE1394_SELF_ID_COMPLETE	(1<<5) /* Self-identification completed */
#define IEEE1394_PHY_CONFIG_RCV		(1<<6) /* PHY configuration packet received */
#define IEEE1394_REMOTE_ACCESS_RCV	(1<<7) /* Remote Access packet received */
#define IEEE1394_REMOTE_COMMAND_RCV	(1<<8) /* Remote Command packet received */
#define IEEE1394_REMOTE_REPLY		(1<<9) /* Remote Reply packet */
#define IEEE1394_REMOTE_CONF		(1<<10)/* Remote Confirmation packet */
#define IEEE1394_RESUME_RCV			(1<<11)/* Resume packet received */
#define IEEE1394_PING_RCV			(1<<12)/* Ping packet received */
#define IEEE1394_SELF_ID_RCV		(1<<13)/* Self-Id packet received */
#define IEEE1394_PING_RESPONSE		(1<<14)/* Ping Response pseudo-packet received */

/* Packet header length in bytes, CRC included */

#define IEEE1394_CRC_ISOCH_PLOAD	8	/* Isochronous payload */
#define IEEE1394_CRC_BLOCK_PLOAD	20	/* Block payload */
#define IEEE1394_CRC_QUAD_PLOAD		16	/* Quadlet payload */

/* Packet header length in bytes, CRC not included */

#define IEEE1394_ISOCH_PLOAD	(IEEE1394_CRC_ISOCH_PLOAD-4) /* Isoch payload */
#define IEEE1394_BLOCK_PLOAD	(IEEE1394_CRC_BLOCK_PLOAD-4) /* Block payload */
#define IEEE1394_QUAD_PLOAD		(IEEE1394_CRC_QUAD_PLOAD-4)	/* Quadlet payload*/
#define IEEE1394_PHY_PLOAD		(16)

/* Received OHCI Packet header length in bytes */
#define IEEE1394_OHCI_BF_ISOCH_HDR_SZ	4	/* Buffer fill mode */
#define IEEE1394_OHCI_PB_ISOCH_HDR_SZ	8	/* Packet per buffer mode */
#define IEEE1394_OHCI_PHY_HDR_SZ		16
#define IEEE1394_OHCI_BLOCK_HDR_SZ		16
#define IEEE1394_OHCI_NO_DTA_HDR_SZ		16
#define IEEE1394_OHCI_QUAD_HDR_SZ		20
#define IEEE1394_OHCI_ASY_STR_HDR_SZ	8

/* Transmit OHCI Packet header size */

#define IEEE1394_ASY_DATA_HDR_SZ		16	/* Asy packet with data (quad or block) */
#define IEEE1394_ASY_NO_DATA_HDR_SZ		12	/* Packet with no data (quad or PHY) */
#define IEEE1394_ISO_HDR_SZ				8	/* Isoch packet or asynch stream */


/* Common to all PHY packets */

#define IEEE1394_PHY_PK_TYPE_SHFT		30	/* PHY packet type */
#define IEEE1394_PHY_PK_TYPE_MASK		0x3
#define IEEE1394_PHY_ID_SHFT			24	/* Physical Id */
#define IEEE1394_PHY_ID_MASK			0x3F

/*
 * Self identification packet. See IEEE 1394-1995 Standard Paragraph 4.3.4.1
 *
 * Self-ID packet 0
 * ----------------
 * MSB                                         LSB
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |10|      |0| |      |  |  | |   |  |  |  | | |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |              LOGICAL INVERSE                |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 *
 * <0> MORE - If set, another self-id packet for this node will immediately
 *            follow. If set and the next phy-id is different, then some self-id
 *            packet was lost.
 * <1> INIT_RESET - This node initiated the current bus reset.
 * <2-3> PORT2 - 11 connected to child node, 10 connected to parent node, 01 not
 *               connected to another node, 00 not present on this physical.
 * <4-5> PORT1 - See definition of PORT2.
 * <6-7> PORT0 - See definition of PORT2.
 * <8-10> POWER_CLASS - Power comsumption
 *                      000 Does not need power and does not repeat power
 *                      001 Self powered and provides minimum of 15 W
 *                      010 Self powered and provides minimum of 30 W
 *                      011 Self powered and provides minimum of 45 W
 *                      100 May be powered from bus and is using up to 1 W
 *                      101 Powered from bus and is using 1 W, need 2 W more
 *                          when link active
 *                      110 Powered from bus and is using 1 W, need 5 W more
 *                          when link active
 *                      111 Powered from bus and is using 1 W, need 9 W more
 *                          when link active
 * <11> CONTENDER - When set, the node is bus or isochronous contender
 * <12-13> PHY_DELAY - Worst-case repeater data delay
 * <14-15> PHY_SPEED - Speed capabilities
 *                     00 - 100MBits
 *                     01 - 200MBits
 *                     10 - 400MBits
 *                     11 - Reserved
 * <16-21> GAP_COUNT - Current value of PHY_CONFIGURATION.gap_count field
 * <22> LINK_ACTIVE - When set, the node has an active link and a transaction
 *                    layer
 * <23> NEXT - Set to zero
 * <24-29> PHY_ID - Physical ID
 * <30-31> SELF_ID - Self-ID packet identifier
 *
 * Self-ID packet 1
 * ----------------
 * MSB                                         LSB
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |10|      |1| |      |  |  | |   |  |  |  | | |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |              LOGICAL INVERSE                |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 *
 * <0> MORE - If set, another self-id packet for this node will immediately
 *            follow. If set and the next phy-id is different, then some self-id
 *            packet was lost.
 * <1> R - Reserved.
 * <2-3> PORT10 - See definition of PORT2.
 * <4-5> PORT9 - See definition of PORT2.
 * <6-7> PORT8 - See definition of PORT2.
 * <8-9> PORT7 - See definition of PORT2.
 * <10-11> PORT6 - See definition of PORT2.
 * <12-13> PORT5 - See definition of PORT2.
 * <14-15> PORT4 - See definition of PORT2.
 * <16-17> PORT3 - See definition of PORT2.
 * <18-19> Reserved
 * <20-22> Extended - Self-ID packet sequence number for the node. 0 to 2
 *                    corresponds to self-ID packet 1 through 3.
 * <23> NEXT - Set to one
 * <24-29> PHY_ID - Physical ID
 * <30-31> SELF_ID - Self-ID packet identifier
 *
 * Self-ID packet 2
 * ----------------
 * MSB                                         LSB
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |10|      |1| |      |  |  | |   |  |  |  | | |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |              LOGICAL INVERSE                |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 *
 * <0> MORE - If set, another self-id packet for this node will immediately
 *            follow. If set and the next phy-id is different, then some self-id
 *            packet was lost.
 * <1> R - Reserved.
 * <2-3> PORT18 - See definition of PORT2.
 * <4-5> PORT17 - See definition of PORT2.
 * <6-7> PORT16 - See definition of PORT2.
 * <8-9> PORT15 - See definition of PORT2.
 * <10-11> PORT14 - See definition of PORT2.
 * <12-13> PORT13 - See definition of PORT2.
 * <14-15> PORT12 - See definition of PORT2.
 * <16-17> PORT11 - See definition of PORT2.
 * <18-19> Reserved
 * <20-22> Extended - Self-ID packet sequence number for the node. 0 to 2
 *                    corresponds to self-ID packet 1 through 3.
 * <23> NEXT - Set to one
 * <24-29> PHY_ID - Physical ID
 * <30-31> SELF_ID - Self-ID packet identifier
 *
 * Self-ID packet 3
 * ----------------
 * MSB                                         LSB
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |10|      |1| |      |  |  | |   |  |  |  | | |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 * |              LOGICAL INVERSE                |
 * |--|------|-|-|------|--|--|-|---|--|--|--|-|-|
 *
 * <0> MORE - If set, another self-id packet for this node will immediately
 *            follow. If set and the next phy-id is different, then some self-id
 *            packet was lost.
 * <1> R - Reserved.
 * <2-3> PORT26 - See definition of PORT2.
 * <4-5> PORT25 - See definition of PORT2.
 * <6-7> PORT24 - See definition of PORT2.
 * <8-9> PORT23 - See definition of PORT2.
 * <10-11> PORT22 - See definition of PORT2.
 * <12-13> PORT21 - See definition of PORT2.
 * <14-15> PORT20 - See definition of PORT2.
 * <16-17> PORT19 - See definition of PORT2.
 * <18-19> Reserved
 * <20-22> Extended - Self-ID packet sequence number for the node. 0 to 2
 *                    corresponds to self-ID packet 1 through 3.
 * <23> NEXT - Set to one
 * <24-29> PHY_ID - Physical ID
 * <30-31> SELF_ID - Self-ID packet identifier
 *
 */

/* Shifts */

#define IEEE1394_SELFID_ID_SHFT		30
#define IEEE1394_NEXT_SHFT			23
#define IEEE1394_LINK_ACTIVE_SHFT	22
#define IEEE1394_GAP_COUNT_SHFT		16
#define IEEE1394_PHY_SPEED_SHFT		14
#define IEEE1394_PHY_DELAY_SHFT		12
#define IEEE1394_CONTENDER_SHFT		11
#define IEEE1394_POWER_CLASS_SHFT	8
#define IEEE1394_PORT0_SHFT			6
#define IEEE1394_PORT1_SHFT			4
#define IEEE1394_PORT2_SHFT			2
#define IEEE1394_INIT_RESET_SHFT	1
#define IEEE1394_MORE_SHFT			0

#define IEEE1394_EXTENDED_SHFT		20
#define IEEE1394_RSV_SHFT			18
#define IEEE1394_PORTA_SHFT			16
#define IEEE1394_PORTB_SHFT			14
#define IEEE1394_PORTC_SHFT			12
#define IEEE1394_PORTD_SHFT			10
#define IEEE1394_PORTE_SHFT			8
#define IEEE1394_PORTF_SHFT			6
#define IEEE1394_PORTG_SHFT			4
#define IEEE1394_PORTH_SHFT			2
#define IEEE1394_R_SHFT				1

#define IEEE1394_PORT3_SHFT			16
#define IEEE1394_PORT4_SHFT			14
#define IEEE1394_PORT5_SHFT			12
#define IEEE1394_PORT6_SHFT			10
#define IEEE1394_PORT7_SHFT			8
#define IEEE1394_PORT8_SHFT			6
#define IEEE1394_PORT9_SHFT			4
#define IEEE1394_PORT10_SHFT		2
#define IEEE1394_PORT11_SHFT		16
#define IEEE1394_PORT12_SHFT		14
#define IEEE1394_PORT13_SHFT		12
#define IEEE1394_PORT14_SHFT		10
#define IEEE1394_PORT15_SHFT		8

/* Masks */

#define IEEE1394_SELFID_ID_MASK		0x3
#define IEEE1394_NEXT_MASK			0x1
#define IEEE1394_LINK_ACTIVE_MASK	0x1
#define IEEE1394_GAP_COUNT_MASK		0x3F
#define IEEE1394_PHY_SPEED_MASK		0x3
#define IEEE1394_PHY_DELAY_MASK		0x3
#define IEEE1394_CONTENDER_MASK		0x1
#define IEEE1394_POWER_CLASS_MASK	0x7
#define IEEE1394_PORT0_MASK			0x3
#define IEEE1394_PORT1_MASK			0x3
#define IEEE1394_PORT2_MASK			0x3
#define IEEE1394_INIT_RESET_MASK	0x1
#define IEEE1394_MORE_MASK			0x1

#define IEEE1394_EXTENDED_MASK		0x7
#define IEEE1394_RSV_MASK			0x3
#define IEEE1394_PORTA_MASK			0x3
#define IEEE1394_PORTB_MASK			0x3
#define IEEE1394_PORTC_MASK			0x3
#define IEEE1394_PORTD_MASK			0x3
#define IEEE1394_PORTE_MASK			0x3
#define IEEE1394_PORTF_MASK			0x3
#define IEEE1394_PORTG_MASK			0x3
#define IEEE1394_PORTH_MASK			0x3
#define IEEE1394_R_MASK				0x1

#define IEEE1394_PORT3_MASK			0x3
#define IEEE1394_PORT4_MASK			0x3
#define IEEE1394_PORT5_MASK			0x3
#define IEEE1394_PORT6_MASK			0x3
#define IEEE1394_PORT7_MASK			0x3
#define IEEE1394_PORT8_MASK			0x3
#define IEEE1394_PORT9_MASK			0x3
#define IEEE1394_PORT10_MASK		0x3
#define IEEE1394_PORT11_MASK		0x3
#define IEEE1394_PORT12_MASK		0x3
#define IEEE1394_PORT13_MASK		0x3
#define IEEE1394_PORT14_MASK		0x3
#define IEEE1394_PORT15_MASK		0x3

/* Values */

#define IEEE1394_SELFID_PKID		0x2	/* Self-ID packet identifier */
#define IEEE1394_PHY_SPD100			0x0	/* 100Mbits physical layer */
#define IEEE1394_PHY_SPD200			0x1	/* 200Mbits physical layer */
#define IEEE1394_PHY_SPD400			0x2	/* 400Mbits physical layer */
#define IEEE1394_DELAY_LE144		0x0	/* Repeater data delay <= 144 nsec */
#define IEEE1394_NOPOW				0x0 /* No need of power, doesn't repeat it*/
#define IEEE1394_SELFPOW_15W		0x1 /* Self powered, provides 15W */
#define IEEE1394_SELFPOW_30W		0x2 /* Self powered, provides 30W */
#define IEEE1394_SELFPOW_45W		0x3 /* Self powered, provides 45W */
#define IEEE1394_BUSPOW_1W			0x4	/* Need 1W of power */
#define IEEE1394_BUSPOW_2W			0x5	/* Need 2W of power */
#define IEEE1394_BUSPOW_5W			0x6	/* Need 5W of power */
#define IEEE1394_BUSPOW_9W			0x7	/* Need 9W of power */
/*
 * There is a zero self-ID packet who is always present. The first, second and
 * third ones are sent only if the node has more than three ports.
 */
#define IEEE1394_SELF_ID_PK1		0x0 /* First self-ID packet */
#define IEEE1394_SELF_ID_PK2		0x1 /* Second self-ID packet */
#define IEEE1394_SELF_ID_PK3		0x2 /* Third self-ID packet */
#define IEEE1394_CHILD				0x3 /* Port is active and connected to a child node. */
#define IEEE1394_PARENT				0x2 /* Port is active and connected to a parent node. */
#define IEEE1394_NOT_CONNECTED		0x1 /* Port is not active (disabled, disconnected or suspended). */
#define IEEE1394_NOT_PRESENT		0x0 /* Port is not present on this PHY. */

/*
 * Link-On packet. See IEEE 1394-1995 Standard Paragraph 4.3.4.2
 *
 * MSB                              LSB
 * |--|------|------------------------|
 * |01|phy_ID|000000000000000000000000|
 * |--|------|------------------------|
 * |        LOGICAL INVERSE           |
 * |----------------------------------|
 *
 * <0-23> Reserved - Set to 0
 * <24-29> phy_ID - Physical ID of the destination node
 * <30-31> link_On_Id - Packet identifier. Must be set to 01b
 *
 * <0-31> Logical inverse of the first quadlet
 */

/* shifts */

#define IEEE1394_LKON_PKID_SHFT		30	/* Packet ID bit offset */
#define IEEE1394_LKON_PHY_ID_SHFT	24	/* Destination physical ID bit offset */

/* masks */

#define IEEE1394_LKON_PKID_MASK		0x3	/* Packet ID mask */
#define IEEE1394_LKON_PHY_ID_MASK	0x3F/* Destination physical ID mask */

/* values */

#define IEEE1394_LKON_PKID			0x1	/* Packet ID */

/*
 * Phy-config packet. See IEEE 1394-1995 Standard Paragraph 4.3.4.3
 *
 * MSB                              LSB
 * |--|------|-|-|------|----------------|
 * |00|phy_ID|R|T|Gapcnt|0000000000000000|
 * |--|------|-|-|------|----------------|
 * |          LOGICAL INVERSE            |
 * |-------------------------------------|
 *
 * <0-15> Reserved - Set to 0
 * <16-21> Gapcnt - Gapcount value
 * <22> T - Set gapcount
 * <23> R - Set force root
 * <24-29> phy_ID - Physical ID of the destination node
 * <30-31> phy_config_Id - Packet identifier. Must be set to 00b
 *
 * <0-31> Logical inverse of the first quadlet
 */

/* shifts */

#define IEEE1394_PHYCFG_PKID_SHFT		30	/* Packet ID bit offset */
#define IEEE1394_PHYCFG_PHY_ID_SHFT		24	/* Physical ID bit offset */
#define IEEE1394_PHYCFG_R_SHFT			23	/* Set force root bit offset */
#define IEEE1394_PHYCFG_T_SHFT			22	/* Set gapcount bit offset */
#define IEEE1394_PHYCFG_GAPCOUNT_SHFT	16	/* Gapcount bit offset */

/* masks */

#define IEEE1394_PHYCFG_PKID_MASK		0x3	/* Packet ID bit mask */
#define IEEE1394_PHYCFG_PHY_ID_MASK		0x3F/* Physical ID bit mask */
#define IEEE1394_PHYCFG_R_MASK			0x1	/* Set force root bit mask */
#define IEEE1394_PHYCFG_T_MASK			0x1	/* Set gapcount bit mask */
#define IEEE1394_PHYCFG_GAPCOUNT_MASK	0x3F/* Gapcount bit mask */

/* values */

#define IEEE1394_PHYCFG_PKID			0x0	/* Packet ID */

/*
 * Extended phy packets. See IEEE Std 1394a-2000 Standard Paragraph 8.5.4
 */

/* Defines common to all packet types */

/* shifts */

#define IEEE1394_EXTPHY_PKID_SHFT		30	/* Extended PHY packet ID bit offset */
#define IEEE1394_EXTPHY_PHY_ID_SHFT		24	/* Physical ID bit offset */
#define IEEE1394_EXTPHY_FLAG_SHFT		22	/* Extended PHY packet flag bit offset */
#define IEEE1394_EXTPHY_TYPE_SHFT		18	/* Extended PHY packet type bit offset */

/* masks */

#define IEEE1394_EXTPHY_PKID_MASK		0x3
#define IEEE1394_EXTPHY_PHY_ID_MASK		0x3F
#define IEEE1394_EXTPHY_FLAG_MASK		0x3	/* Extended PHY packet flag bit mask */
#define IEEE1394_EXTPHY_TYPE_MASK		0xF

/* value */

#define IEEE1394_EXTPHY_FLAG			0

/* Ping packets (P1394a Standard Paragraph 8.5.4.1)
 *
 * 31 30 29   24 23 22 21   18 17                          0
 * |---|--------|-----|-------|-----------------------------|
 * |0 0| phy_ID | 0 0 | type  |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0|
 * |---|--------|-----|-------|-----------------------------|
 * |                     LOGICAL INVERSE                    |
 * |--------------------------------------------------------|
 *
 * <0-17>	Unused - Set to 0
 * <18-21>	Type - Packet type, set to 0
 * <22-23>	Unused - Set to 0
 * <24-29>	Destination Physical ID
 * <30-31>	Set to 0
 *
 * <0-31> Logical inverse of the first quadlet
 */

#define IEEE1394_EXTPHY_PING_PK_TYPE	0x0

/* Remote access packet (P1394a Standard Paragraph 8.5.4.2)
 *
 * 31 30 29   24 23 22 21  18 17 15 14  11 10  8 7         0
 * |---|--------|-----|------|-----|------|-----|-----------|
 * |0 0| phy_ID | 0 0 | type |page | port | reg | reserved  |
 * |---|--------|-----|------|-----|------|-----|-----------|
 * |                     LOGICAL INVERSE                    |
 * |--------------------------------------------------------|
 *
 * <8-10>	Reg - This field in combination with page and port, specifies
 *			the PHY register. If type indicates a read of the base PHY
 *			registers this field directly addresses one of the first eigth
 *			PHY registers. Otherwise, the PHY registers address is 1000b + reg
 * <11-14>	port - Correspond to the Port_select field of the PHY registers
 * <15-17>	page - Correspond to the Page_select field of the PHY registers
 * <18-22>	type - Packet type :	1 => Reg read (base registers)
 *									5 => Reg read (paged registers)
 * <24-29>	phy_ID - Destination of this packet.
 *
 * <0-31> Logical inverse of the first quadlet
 */

#define IEEE1394_EXTPHY_RMT_ACC_B_TYPE	0x1
#define IEEE1394_EXTPHY_RMT_ACC_P_TYPE	0x5

#define IEEE1394_EXTPHY_PAGE_SHFT		15	/* Page bit offset */
#define IEEE1394_EXTPHY_PORT_SHFT		11	/* Port bit offset */
#define IEEE1394_EXTPHY_REG_SHFT		8	/* Register bit offset */

#define IEEE1394_EXTPHY_PAGE_MASK		0x7
#define IEEE1394_EXTPHY_PORT_MASK		0xF
#define IEEE1394_EXTPHY_REG_MASK		0x7

/* Remote reply packet (P1394a Standard Paragraph 8.5.4.3)
 *
 * 31 30 29   24 23 22 21  18 17 15 14  11 10  8 7         0
 * |---|--------|-----|------|-----|------|-----|-----------|
 * |0 0| phy_ID | 0 0 | type |page | port | reg |   data    |
 * |---|--------|-----|------|-----|------|-----|-----------|
 * |                     LOGICAL INVERSE                    |
 * |--------------------------------------------------------|
 *
 * <0-7>	Data - Current value of the registers read
 * <8-10>	Reg - This field in combination with page and port, specifies
 *			the PHY register. If type indicates a read of the base PHY
 *			registers this field directly addresses one of the first eigth
 *			PHY registers. Otherwise, the PHY registers address is 1000b + reg
 * <11-14>	port - Correspond to the Port_select field of the PHY registers
 * <15-17>	page - Correspond to the Page_select field of the PHY registers
 * <18-22>	type - Register type :	3 => Reg read (base registers)
 *									7 => Reg read (paged registers)
 * <24-29>	phy_ID - Destination of this packet.
 *
 * <0-31> Logical inverse of the first quadlet
 */

#define IEEE1394_EXTPHY_RMT_REP_B_TYPE	0x3
#define IEEE1394_EXTPHY_RMT_REP_P_TYPE	0x7
#define IEEE1394_EXTPHY_DATA_SHFT		0	/* Data bit offset */
#define IEEE1394_EXTPHY_DATA_MASK		0xFF

/* Remote command packet (P1394a Standard Paragraph 8.5.4.4)
 *
 * 31 30 29   24 23 22 21  18 17 15 14  11 10          3 2  1
 * |---|--------|-----|------|-----|------|-------------|----|
 * |0 0| phy_ID | 0 0 | type |0 0 0| port | 0 0 0 0 0 0 |cmd |
 * |---|--------|-----|------|-----|------|-------------|----|
 * |                     LOGICAL INVERSE                     |
 * |---------------------------------------------------------|
 *
 * <0-2>	cmd - Command to send:
 *					0 => NOP
 *					1 => Transmit TX_DISABLE_NOTIFY then disable port
 *					2 => Initiate suspend
 *					4 => Clear port's Fault bit to zero
 *					5 => Enable port
 *					6 => Resume port
 * <11-14>	port - This field select the port.
 * <18-22>	type - Packet type, set to 8.
 * <24-29>	phy_ID - Destination of this packet.
 *
 * <0-31> Logical inverse of the first quadlet
 */

#define IEEE1394_EXTPHY_REM_CMD_TYPE	0x8
#define IEEE1394_EXTPHY_CMND_SHFT		0	/* Command bit offset */
#define IEEE1394_EXTPHY_CMND_MASK		0x7	/* Command bit mask */

#define IEEE1394_EXTPHY_NOP				0x0
#define IEEE1394_EXTPHY_DISABLE_PORT	0x1
#define IEEE1394_EXTPHY_INIT_SUSPEND	0x2
#define IEEE1394_EXTPHY_CLR_FAULT_BIT	0x4
#define IEEE1394_EXTPHY_ENABLE_PORT		0x5
#define IEEE1394_EXTPHY_RESUME_PORT		0x6

/* Remote confirmation packet (P1394a Standard Paragraph 8.5.4.5)
 *
 * 31 30 29   24 23 22 21  18 17 15 14  11 10  8 7 6 5 4 3  2 0
 * |---|--------|-----|------|-----|------|-----|-|-|-|-|--|---|
 * |0 0| phy_ID | 0 0 | type |0 0 0| port |0 0 0|f|c|b|d|ok|cmd|
 * |---|--------|-----|------|-----|------|-----|-|-|-|-|--|---|
 * |                     LOGICAL INVERSE                       |
 * |-----------------------------------------------------------|
 *
 * <0-2>	cmd - Remote command that generated this packet
 * <3>		ok - One if the command was accepted
 * <4>		d - Current value of the Disable bit from the PHY
 *			register 1000b for the addressed port
 * <5>		b - Current value of the Bias bit from the PHY
 *			register 1000b for the addressed port
 * <6>		c - Current value of the Connected bit from the PHY
 *			register 1000b for the addressed port
 * <7>		f - Current value of the Fault bit from the PHY
 *			register 1000b for the addressed port
 * <11-14>	port - PHY port to which this packets pertains
 * <18-21>	type - Packet type, set to Ah.
 * <24-29>	phy_ID - Source of this packet.
 * <0-31> Logical inverse of the first quadlet
 */

#define IEEE1394_EXTPHY_RMT_CONF_TYPE	0xA

#define IEEE1394_EXTPHY_FAULT_SHFT		0x7
#define IEEE1394_EXTPHY_CONECT_SHFT		0x6
#define IEEE1394_EXTPHY_BIAS_SHFT		0x5
#define IEEE1394_EXTPHY_DISABLE_SHFT	0x4
#define IEEE1394_EXTPHY_OK_SHFT			0x3

#define IEEE1394_EXTPHY_FAULT_MASK		0x1
#define IEEE1394_EXTPHY_CONECT_MASK		0x1
#define IEEE1394_EXTPHY_BIAS_MASK		0x1
#define IEEE1394_EXTPHY_DISABLE_MASK	0x1
#define IEEE1394_EXTPHY_OK_MASK			0x1

/* Resume packets (P1394a Standard Paragraph 8.5.4.6)
 *
 * 31 30 29   24 23 22 21   18 17                          0
 * |---|--------|-----|-------|-----------------------------|
 * |0 0| phy_ID | 0 0 | type  |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0|
 * |---|--------|-----|-------|-----------------------------|
 * |                     LOGICAL INVERSE                    |
 * |--------------------------------------------------------|
 *
 * <0-17>	Unused - Set to 0
 * <18-21>	Type - Packet type, set to 0
 * <22-23>	Unused - Set to Fh
 * <24-29>	Destination Physical ID
 * <30-31>	Set to 0
 *
 * <0-31> Logical inverse of the first quadlet
 */

#define IEEE1394_EXTPHY_RESUME_TYPE		0xF

/* typedefs */

/* globals */

/* locals */

/* forward declarations */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCieee1394h */
