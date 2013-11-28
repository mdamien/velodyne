/* tsb12lv23.c - TSB12LV23 typedef and defines */

/* Copyright(c) 1999, Sederta Inc. All rights reserved. */

/*
modification history
--------------------
01f,10Oct00,spa Raise to 50 the number of retry to read the phy layer
01e,31Aug00,spa Merge 4 UINT16 (CAP_ID PM_CAP PM_CSR PM_Ext) into
                2 UINT32 (CAP and PM) in the chip mapping.
01d,28Jun00,spa Added Posted Write Addr Hi register mapping.
01c,14Jun00,spa Changed tabulation
01b,30May00,spa Added event ack codes
01a,12May00,spa This file was created.
*/

/*
This module contains specific typedef and defines for the Texas Instrument
IEEE 1394 link layer layer TSB12LV23.

INCLUDES FILES: sdtypes.h
*/

#ifndef __INCtsb12lv23h
#define __INCtsb12lv23h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */
#include "stdint.h"

/* defines */

#define TSB12LV23_MAX_GEN_CNT 255           /* Roll over for generation count */

#define TSB12LV23_MAX_NB_ISO_RX_CTX         32
#define TSB12LV23_MAX_NB_ISO_TX_CTX         32
#define TSB12LV23_NB_ASY_CTX                4

/*
 * Register offsets
 */
#define TSB12LV23_OHCI_VERSION          0x0000  /* OHCI Verison + ROM supp. */
#define TSB12LV23_GUID_ROM              0x0004  /* ROM access               */
#define TSB12LV23_AT_RETRIES            0x0008  /* Nb retry for Async Tx    */
#define TSB12LV23_CSR_DATA              0x000c  /* To access the host CSR   */
#define TSB12LV23_CSR_CMP_DATA          0x0010  /* Compare data for CSR     */
#define TSB12LV23_CSR_CONTROL           0x0014  /* Select the CSR           */
/* Registers used to map the ROM & the Bus Info Block (BIB) */
#define TSB12LV23_CFG_ROM_HEADER        0x0018  /* ROM header (crc + length)*/
#define TSB12LV23_BUS_ID                0x001c  /* 1st quad = '1394'        */
#define TSB12LV23_BUS_OPTIONS           0x0020  /* 2nd quad = Capabilities  */
#define TSB12LV23_GUID_HI               0x0024  /* 3th quad = Unique Id HI  */
#define TSB12LV23_GUID_LO               0x0028  /* 4th quad = Unique Id LO  */
#define TSB12LV23_PCI_SUB_ID            0x002c  /* PCI subsystem id */
#define TSB12LV23_CFG_ROM_MAP           0x0034  /* Start address of Cfg rom */
/* Error handling */
#define TSB12LV23_POSTED_WR_ADDR_LO     0x0038
#define TSB12LV23_POSTED_WR_ADDR_HI     0x003c
/* Dummy register */
#define TSB12LV23_VENDOR_ID             0x0040  /* Read-only, contains 0    */
#define TSB12LV23_CAP_ID                0x0044  /* Read-only, contains 0    */
#define TSB12LV23_PWR_CAP               0x0046  /* Read-only, contains 0    */
#define TSB12LV23_PWR_STATUS            0x0048  /* Read-only, contains 0    */
#define TSB12LV23_PWR_MGT_EXT           0x004A  /* Read-only, contains 0    */
/* Main control register (Swap/Enable/reset/ etc.) */
#define TSB12LV23_HC_CONTROL_SET        0x0050
#define TSB12LV23_HC_CONTROL_CLR        0x0054
/* Self ID packets */
#define TSB12LV23_SELF_ID_BUFFER        0x0064  /* Pnt on 2k buffer for SID */
#define TSB12LV23_SELF_ID_COUNT         0x0068  /* Nb SelfId                */
/* Isochronous channel enable mask */
#define TSB12LV23_IR_CHAN_MASK_HI_SET   0x0070  /* Iso Rx ctrl for 32 to 63 */
#define TSB12LV23_IR_CHAN_MASK_HI_CLR   0x0074
#define TSB12LV23_IR_CHAN_MASK_LO_SET   0x0078  /* Iso Rx ctrl for 0 to 31  */
#define TSB12LV23_IR_CHAN_MASK_LO_CLR   0x007c
/* Interrupt handling */
#define TSB12LV23_INT_EVENT_SET         0x0080  /* Interrupt event reg      */
#define TSB12LV23_INT_EVENT_CLR         0x0084
#define TSB12LV23_INT_MASK_SET          0x0088  /* Interrupt mask regs      */
#define TSB12LV23_INT_MASK_CLR          0x008c
/* Isochronous transmit event register */
#define TSB12LV23_ISO_TX_INT_EVENT_SET  0x0090  /* Iso Tx event             */
#define TSB12LV23_ISO_TX_INT_EVENT_CLR  0x0094
#define TSB12LV23_ISO_TX_MASK_EVENT_SET 0x0098  /* Iso Tx mask              */
#define TSB12LV23_ISO_TX_MASK_EVENT_CLR 0x009c
/* Isochronous receive event register */
#define TSB12LV23_ISO_RX_INT_EVENT_SET  0x00a0  /* Iso Rx event             */
#define TSB12LV23_ISO_RX_INT_EVENT_CLR  0x00a4
#define TSB12LV23_ISO_RX_MASK_EVENT_SET 0x00a8  /* Iso Rx mask              */
#define TSB12LV23_ISO_RX_MASK_EVENT_CLR 0x00ac
/* Fairness control */
#define TSB12LV23_FAIRNESS_CONTROL      0x00dc
/* Link core protocol control */
#define TSB12LV23_LINK_CONTROL_SET      0x00e0
#define TSB12LV23_LINK_CONTROL_CLR      0x00e4
/* Node identification */
#define TSB12LV23_NODE_ID               0x00e8  /* Read-only. Node #        */
/* PHY access */
#define TSB12LV23_PHY_CONTROL           0x00ec  /* Access to phy registers  */
/* Isochronous reference cycle timer */
#define TSB12LV23_ISO_CYCLE_TIMER       0x00f0
/* This registers handle the async reception on a per node basis */
#define TSB12LV23_ASY_REQ_FILTER_HI_SET 0x0100
#define TSB12LV23_ASY_REQ_FILTER_HI_CLR 0x0104
#define TSB12LV23_ASY_REQ_FILTER_LO_SET 0x0108
#define TSB12LV23_ASY_REQ_FILTER_LO_CLR 0x010c
#define TSB12LV23_PHY_REQ_FILTER_HI_SET 0x0110
#define TSB12LV23_PHY_REQ_FILTER_HI_CLR 0x0114
#define TSB12LV23_PHY_REQ_FILTER_LO_SET 0x0118
#define TSB12LV23_PHY_REQ_FILTER_LO_CLR 0x011c
/* Upper bound register */
#define TSB12LV23_PHY_UPPER_BOUND       0x0120  /* NOT IMPLEMENTED  */
/* Asynchronous request transmit */
#define TSB12LV23_ATRQ_CTRL_SET         0x0180
#define TSB12LV23_ATRQ_CTRL_CLR         0x0184
#define TSB12LV23_ATRQ_CMD_PTR          0x018c
/* Asynchronous response transmit */
#define TSB12LV23_ATRS_CTRL_SET         0x01a0
#define TSB12LV23_ATRS_CTRL_CLR         0x01a4
#define TSB12LV23_ATRS_CMD_PTR          0x01ac
/* Asynchronous request receive */
#define TSB12LV23_ARRQ_CTRL_SET         0x01c0
#define TSB12LV23_ARRQ_CTRL_CLR         0x01c4
#define TSB12LV23_ARRQ_CMD_PTR          0x01cc
/* Asynchronous response receive */
#define TSB12LV23_ARRS_CTRL_SET         0x01e0
#define TSB12LV23_ARRS_CTRL_CLR         0x01e4
#define TSB12LV23_ARRS_CMD_PTR          0x01ec
/* Isochronous Transmit context (base + 16 * no) */
#define TSB12LV23_ISO_TX_CTRL_SET(_CTX_NB)      (0x0200 + (_CTX_NB << 4))
#define TSB12LV23_ISO_TX_CTRL_CLR(_CTX_NB)      (0x0204 + (_CTX_NB << 4))
#define TSB12LV23_ISO_TX_CMD_PTR(_CTX_NB)       (0x020c + (_CTX_NB << 4))
/* Isochronous Receive context (base + 32 * no) */
#define TSB12LV23_ISO_RX_CTRL_SET(_CTX_NB)      (0x0400 + (_CTX_NB << 5))
#define TSB12LV23_ISO_RX_CTRL_CLR(_CTX_NB)      (0x0404 + (_CTX_NB << 5))
#define TSB12LV23_ISO_RX_CMD_PTR(_CTX_NB)       (0x040c + (_CTX_NB << 5))
#define TSB12LV23_ISO_CTX_MATCH(_CTX_NB)        (0x0410 + (_CTX_NB << 5))

/* globals */

typedef struct
    {
    struct ctxControlReg
        {
        uint32_t set;
        uint32_t clear;
        } ctxControl;
    uint32_t    reserved2;
    uint32_t    commandPtr;
    } lv23Context_t;

typedef struct
    {
    struct IsoCtxCtrlReg
        {
        uint32_t set;
        uint32_t clear;
        } ctxControl;
    uint32_t    reserved1;
    uint32_t    commandPtr;
    uint32_t    contextMatch;
    uint32_t    reserved[3];
    } lv23IsoRxContext_t;

typedef struct tsb12lv23
    {
    uint32_t    version;        /* 00h */
    uint32_t    GUID_ROM;       /* 04h */
    uint32_t    ATRetries;      /* 08h */
    uint32_t    csrData;        /* 0Ch */
    uint32_t    csrCompareData; /* 10h */
    uint32_t    csrControl;     /* 14h */
    uint32_t    configRomHdr;   /* 18h */
    uint32_t    busId;          /* 1Ch */
    uint32_t    busOptions;     /* 20h */
    uint32_t    guiIdHi;        /* 24h */
    uint32_t    guiIdLo;        /* 28h */
    uint32_t    SSID;           /* 2Ch */
    uint32_t    reserved30;     /* 30h */
    uint32_t    configROMmap;       /* 34h */
    uint32_t    postedWriteAddrLo;  /* 38h */
    uint32_t    postedWriteAddrHi;  /* 3Ch */
    uint32_t    vendorId;       /* 40h */
    uint32_t    CAP;            /* 44h */
    uint32_t    PM;             /* 48h */
    uint32_t    reserved4c;     /* 4Ch */
    struct  hcControlHdr
        {
        uint32_t set;       /* 50h */
        uint32_t clr;   /* 54h */
        }hcControl;
    uint32_t    reserved58_60[3];   /* 58h - 60h */
    uint32_t    selfIdBuffer;       /* 64h */
    uint32_t    selfIdCount;        /* 68h */
    uint32_t    reserved6c;         /* 6Ch */
    struct  irChannelMaskHiReg
        {
        uint32_t set;           /* 70h */
        uint32_t clr;           /* 74h */
        }irChannelMaskHi;
    struct  irChannelMaskLoReg
        {
        uint32_t set;           /* 78h */
        uint32_t clr;           /* 7Ch */
        } irChannelMaskLo;
    struct  intEventReg
        {
        uint32_t set;           /* 80h */
        uint32_t clr;           /* 84h */
        } intEvent;
    struct  intMaskReg
        {
        uint32_t set;               /* 88h */
        uint32_t clr;               /* 8Ch */
        } intMask;
    struct  isoTxIntEventReg
        {
        uint32_t set;               /* 90h */
        uint32_t clr;               /* 94h */
        } isoTxIntEvent;
    struct  isoTxIntMaskReg
        {
        uint32_t set;               /* 98h */
        uint32_t clr;               /* 9Ch */
        } isoTxIntMask;
    struct  isoRxIntEventReg
        {
        uint32_t set;               /* A0h */
        uint32_t clr;               /* A4h */
        } isoRxIntEvent;
    struct  isoRxIntMaskReg
        {
        uint32_t set;               /* A8h */
        uint32_t clr;               /* ACh */
        } isoRxIntMask;
    uint32_t    initialBandwidthAv;     /* B0h */
    uint32_t    initialChannelsAvHi;    /* B4h */
    uint32_t    initialChannelsAvLo;    /* B8h */
    uint32_t    reservedbc_d8[8];       /* BCh - D8h */
    uint32_t    fairnessControl;        /* DCh */
    struct  linkControlReg
        {
        uint32_t set;                   /* E0h */
        uint32_t clr;               /* E4h */
        } linkControl;
    uint32_t    nodeId;             /* E8h */
    uint32_t    phyControl;         /* ECh */
    uint32_t    isoCycleTimer;      /* F0h */
    uint32_t    reservedf4_fc[3];   /* F4h - FCh */
    struct  asyncReqFilterHiReg
        {
        uint32_t set;               /* 100h */
        uint32_t clr;           /* 104h */
        } asyncReqFilterHi;
    struct  asyncReqFilterLoReg
        {
        uint32_t set;               /* 108h */
        uint32_t clr;           /* 10Ch */
        } asyncReqFilterLo;
    struct  phyReqFilterHiReg
        {
        uint32_t set;               /* 110h */
        uint32_t clr;           /* 114h */
        } phyReqFilterHi;
    struct  phyReqFilterLoReg
        {
        uint32_t set;               /* 118h */
        uint32_t clr;           /* 11Ch */
        } phyReqFilterLo;
    uint32_t            phyUpperBound;          /* 120h */
    uint32_t            reserved124_17c[23];    /* 124h - 17Ch */
    lv23Context_t   ATRQ;                   /* 180h - 18Ch */
    uint32_t            reserved190_19c[4];     /* 190h - 19Ch */
    lv23Context_t   ATRS;                   /* 1A0h - 1ACh */
    uint32_t            reserved1b0_1bc[4];     /* 1B0h - 1BCh */
    lv23Context_t   ARRQ;                   /* 1C0h - 1CCh */
    uint32_t            reserved1d0_1dc[4];     /* 1DCh - 1CCh */
    lv23Context_t   ARRS;                   /* 1E0h - 1ECh */
    uint32_t            reserved1f0_1ff[4];     /* 1F0h - 1FCh */
    lv23Context_t       IsoTxContext[32];
    lv23IsoRxContext_t  IsoRxContext[32];
    } tsb12lv23_t;


/*
 * Definition of interrupts event bits
 */

#define TSB12LV23_INT_REQ_TX_COMPLETE       0x00000001
#define TSB12LV23_INT_RES_TX_COMPLETE       0x00000002
#define TSB12LV23_INT_ARRQ                  0x00000004
#define TSB12LV23_INT_ARRS                  0x00000008
#define TSB12LV23_INT_RQ_PKT                0x00000010
#define TSB12LV23_INT_RS_PKT                0x00000020
#define TSB12LV23_INT_ISO_TX                0x00000040
#define TSB12LV23_INT_ISO_RX                0x00000080
#define TSB12LV23_INT_POSTED_WRITE_ERR      0x00000100
#define TSB12LV23_INT_LOCK_RESP_ERR         0x00000200
#define TSB12LV23_INT_SELF_ID_COMPLETE2     0x00008000
#define TSB12LV23_INT_SELF_ID_COMPLETE      0x00010000
#define TSB12LV23_INT_BUS_RESET             0x00020000
#define TSB12LV23_INT_REG_ACCESS_FAILED     0x00040000
#define TSB12LV23_INT_PHY                   0x00080000
#define TSB12LV23_INT_CYCLE_SYNC            0x00100000
#define TSB12LV23_INT_CYCLE_64              0x00200000
#define TSB12LV23_INT_CYCLE_LOST            0x00400000
#define TSB12LV23_INT_CYCLE_INCONSISTENT    0x00800000
#define TSB12LV23_INT_UNRECOVERABLE_ERROR   0x01000000
#define TSB12LV23_INT_CYCLE_TOO_LONG        0x02000000
#define TSB12LV23_INT_PHY_REG_RX            0x04000000
#define TSB12LV23_INT_ACK_TARDY             0x08000000
#define TSB12LV23_INT_MASTER_ENABLE         0x80000000

/*
 * Version register
 * ----------------
 *
 *  31         25   23            16 15            8 7              0
 * |-------------|-|----------------|---------------|----------------|
 * | xxxxxxxxxxx |G| Version        | xxxxxxxxxxxxx | Revision       |
 * |-------------|-|----------------|---------------|----------------|
 *
 * <0-7>    Minor Revision number of the OHCI (Bcd encoded)
 * <16-23>  Major Version of the OHCI (Bcd encoded)
 * <24>     The GUID_ROM bit indicating that the Global unique ID ROM is present
 */

/* Shifts */

#define TSB12LV23_REVISION_SHFT     0
#define TSB12LV23_VERSION_SHFT      16
#define TSB12LV23_GUID_SHFT         24

/* Masks */

#define TSB12LV23_VERSION_MASK  ((uint32_t)0xFF << TSB12LV23_VERSION_SHFT)
#define TSB12LV23_REVISION_MASK ((uint32_t)0xFF << TSB12LV23_REVISION_SHFT)
#define TSB12LV23_GUID_MASK     ((uint32_t)0x1 << TSB12LV23_GUID_SHFT)

/*
 * GUID ROM Register
 * -----------------
 *
 * 31 30     26     23            16 15            8 7              0
 * |-|---------|-|-|----------------|---------------|----------------|
 * |A| xxxxxxx |S|x| rdData         | xxxxxxxxxxxxx | miniROM        |
 * |-|---------|-|-|----------------|---------------|----------------|
 *
 * <0-7>    First byte locate of the miniROM
 * <16-23>  The data read from the GUID ROM
 * <25>     Read trigger when transition from 0 to 1
 * <31>     Reset the GUID ROM to 0
 */

/* Shifts */

#define TSB12LV23_MINI_ROM_SHFT     0
#define TSB12LV23_ROM_DATA_SHFT     16
#define TSB12LV23_ROM_START_SHFT    25
#define TSB12LV23_ROM_RESET_SHFT    31

/* Masks */

#define TSB12LV23_MINI_ROM_MASK     ((uint32_t)0xFF << TSB12LV23_MINI_ROM_SHFT)
#define TSB12LV23_ROM_DATA_MASK     ((uint32_t)0xFF << TSB12LV23_ROM_DATA_SHFT)
#define TSB12LV23_ROM_START_MASK    ((uint32_t)0x1 << TSB12LV23_ROM_START_SHFT)
#define TSB12LV23_ROM_RESET_MASK    ((uint32_t)0x1 << TSB12LV23_ROM_RESET_SHFT)

/*
 * ATRetries Register
 * ------------------
 *
 * 31   29 28                    16 15    12 11    8 7      4 3     0
 * |------|------------------------|--------|-------|--------|-------|
 * | A    | cycleLimit             | xxxxxx | B     | C      | D     |
 * |------|------------------------|--------|-------|--------|-------|
 *
 * <0-3>    Maximum Async. Transmit Request Retries
 * <4-7>    Maximum Async. Transmit Response Retries
 * <8-11>   Maximum Physical Response Retries
 * <16-28>  Cycle Limit
 * <29-31>  Second Limit
 */

/* Shifts */

#define TSB12LV23_ATREQ_RETRIES_SHFT    0
#define TSB12LV23_ATRESP_RETRIES_SHFT   4
#define TSB12LV23_PHYS_RETRIES_SHFT     8
#define TSB12LV23_CYCLE_LIMIT_SHFT      16
#define TSB12LV23_SECOND_LIMIT_SHFT     29

/* Masks */

#define TSB12LV23_ATREQ_RETRIES_MASK    ((uint32_t)0xF << TSB12LV23_ATREQ_RETRIES_SHFT)
#define TSB12LV23_ATRESP_RETRIES_MASK   ((uint32_t)0xF << TSB12LV23_ATRESP_RETRIES_SHFT)
#define TSB12LV23_PHYS_RETRIES_MASK     ((uint32_t)0xF << TSB12LV23_PHYS_RETRIES_SHFT)
#define TSB12LV23_CYCLE_LIMIT_MASK      ((uint32_t)0x1FFF << TSB12LV23_CYCLE_LIMIT_SHFT)
#define TSB12LV23_SECOND_LIMIT_MASK     ((uint32_t)0x7 << TSB12LV23_SECOND_LIMIT_SHFT)

/*
 * CSR Control register
 * --------------------
 *
 *  31 30 29                      16 15            8 7         2 1  0
 * |--|--|--------------------------|---------------|-----------|----|
 * |A |B | xxxxxxxxxxxxxxxxxxxxxxxx | selfIDgen.    | xxxxxxxxx | C  |
 * |--|--|--------------------------|---------------|-----------|----|
 *
 * <0-1>    CSR selection
 * <8-15>   Self ID generation
 * <30>     CSR generation failed
 * <31>     CSR operation done
 */

/* Shifts */

#define TSB12LV23_CSR_SELECT_SHFT       0
#define TSB12LV23_CSR_GENERATION_SHFT   8
#define TSB12LV23_CSR_GEN_FAILED_SHFT   30
#define TSB12LV23_CSR_DONE_SHFT         31

/* Masks */

#define TSB12LV23_CSR_SELECT_MASK       ((uint32_t)0x3 << TSB12LV23_CSR_SELECT_SHFT)
#define TSB12LV23_CSR_GENERATION_MASK   ((uint32_t)0xFF << TSB12LV23_CSR_GENERATION_SHFT)
#define TSB12LV23_CSR_GEN_FAILED_MASK   ((uint32_t)0x1 << TSB12LV23_CSR_GEN_FAILED_SHFT)
#define TSB12LV23_CSR_DONE_MASK         ((uint32_t)0x1 << TSB12LV23_CSR_DONE_SHFT)

/* CSR selection */

#define TSB12LV23_CSR_SELECT_BUS_MGR_ID     0x0
#define TSB12LV23_CSR_SELECT_BANDWIDTH      0x1
#define TSB12LV23_CSR_SELECT_CHANNELS_HI    0x2
#define TSB12LV23_CSR_SELECT_CHANNELS_LO    0x3

/* Arbitrary value for read operations on these CSRs */
#define TSB12LV23_CSR_READ_VALUE            0xFFFFFFFF

/*
 * Posted Write Addr Hi register
 * -----------------------------
 *
 *  31                 22 21       16 15                            0
 * |---------------------|-----------|-------------------------------|
 * |      bus number     | node nb   |           offset hi           |
 * |---------------------|-----------|-------------------------------|
 *
 * <0-15>   offset hi of the request that failed
 * <16-21>  Node number of the sender of the request that failed
 * <22-31>  Bus number of the sender of the request that failed
 */

/* Shifts */

#define TSB12LV23_PWA_HI_OFFSET_SHFT        0
#define TSB12LV23_PWA_HI_NODNB_SHFT         16
#define TSB12LV23_PWA_HI_BUSNB_SHFT         22

/* Masks */

#define TSB12LV23_PWA_HI_OFFSET_MASK    ((uint32_t)0xFFFF << TSB12LV23_PWA_HI_OFFSET_SHFT)
#define TSB12LV23_PWA_HI_NODNB_MASK     ((uint32_t)0x3F << TSB12LV23_PWA_HI_NODNB_SHFT)
#define TSB12LV23_PWA_HI_BUSNB_MASK     ((uint32_t)0x3FF    << TSB12LV23_PWA_HI_BUSNB_SHFT)

/*
 * Posted Write Addr Low register
 * ------------------------------
 *
 *  31                                                              0
 * |-----------------------------------------------------------------|
 * |                            offset low                           |
 * |-----------------------------------------------------------------|
 *
 * <0-31>   offset low of the request that failed
 */

/*
 * HCControl Register
 * ------------------
 *
 * 31       27  24     21 20         15                           0
 * |-|-|-|-|------|-|-|-----|-|-|-|-|------------------------------|
 * |A|B|C|D| xxxx |E|F| xxx |G|H|I|J| xxxxxxxxxxxxxxxxxxxxxxxxxxxx |
 * |-|-|-|-|------|-|-|-----|-|-|-|-|------------------------------|
 *
 * <16>     Soft Reset
 * <17>     Link enable
 * <18>     Posted Write Enable
 * <19>     LPS
 * <22>     aPhyEnhanceEnable
 * <23>     programPhyEnable
 * <28>     csrGenVerifyEnable
 * <29>     ackTradyEnable
 * <30>     noByteSwapData
 * <31>     BIBimageValid
 */

/* Shifts */

#define TSB12LV23_SOFT_RESET_SHFT   16
#define TSB12LV23_LINK_ENABLE_SHFT  17
#define TSB12LV23_PW_ENABLED_SHFT   18
#define TSB12LV23_LPS_SHFT          19
#define TSB12LV23_PHY_ENHANCE_SHFT  22
#define TSB12LV23_PHY_ENABLE_SHFT   23
#define TSB12LV23_CSR_VERIFY_SHFT   28
#define TSB12LV23_ACK_TARDY_SHFT    29
#define TSB12LV23_BYTE_SWAP_SHFT    30
#define TSB12LV23_BIB_IMAGE_SHFT    31

/* Masks */

#define TSB12LV23_SOFT_RESET_MASK   ((uint32_t)0x01 << TSB12LV23_SOFT_RESET_SHFT)
#define TSB12LV23_LINK_ENABLE_MASK  ((uint32_t)0x01 << TSB12LV23_LINK_ENABLE_SHFT)
#define TSB12LV23_PW_ENABLED_MASK   ((uint32_t)0x01 << TSB12LV23_PW_ENABLED_SHFT)
#define TSB12LV23_LPS_MASK          ((uint32_t)0x01 << TSB12LV23_LPS_SHFT)
#define TSB12LV23_PHY_ENHANCE_MASK  ((uint32_t)0x01 << TSB12LV23_PHY_ENHANCE_SHFT)
#define TSB12LV23_PHY_ENABLE_MASK   ((uint32_t)0x01 << TSB12LV23_PHY_ENABLE_SHFT)
#define TSB12LV23_CSR_VERIFY_MASK   ((uint32_t)0x01 << TSB12LV23_CSR_VERIFY_SHFT)
#define TSB12LV23_ACK_TARDY_MASK    ((uint32_t)0x01 << TSB12LV23_ACK_TARDY_SHFT)
#define TSB12LV23_BYTE_SWAP_MASK    ((uint32_t)0x01 << TSB12LV23_BYTE_SWAP_SHFT)
#define TSB12LV23_BIB_IMAGE_MASK    ((uint32_t)0x01 << TSB12LV23_BIB_IMAGE_SHFT)

/*
 * Bus options Register
 * ----------------------
 *
 *  31 30 29 28 27 26 24 23         16 15     12 11     8 7 6 5  3 2   0
 * |--|--|--|--|--|-----|-------------|---------|--------|---|----|-----|
 * |A |B |C |D |E |xxxx | cyc_clk_acc | max_rec | xxxxxx | g | xx | F   |
 * |--|--|--|--|--|-----|-------------|---------|--------|---|----|-----|
 *
 * <0-2>    Link speed
 * <6-7>    Generation counter
 * <12-15>  max_rec
 * <16-23>  cyc_clk_acc
 * <27>     pmc
 * <28>     bmc
 * <29>     isc
 * <30>     cmc
 * <31>     irmc
 */

/* Shifts */

#define TSB12LV23_BUS_LINK_SPEED_SHFT   0
#define TSB12LV23_BUS_GEN_COUNT_SHFT    6
#define TSB12LV23_BUS_MAX_REC_SHFT      12
#define TSB12LV23_BUS_CLK_ACC_SHFT      16
#define TSB12LV23_BUS_PMC_SHFT          27
#define TSB12LV23_BUS_BMC_SHFT          28
#define TSB12LV23_BUS_ISC_SHFT          29
#define TSB12LV23_BUS_CMC_SHFT          30
#define TSB12LV23_BUS_IRMC_SHFT         31

/* Masks */

#define TSB12LV23_BUS_LINK_SPEED_MASK   ((uint32_t)0x7 << TSB12LV23_BUS_LINK_SPEED_SHFT)
#define TSB12LV23_BUS_GEN_COUNT_MASK    ((uint32_t)0x3 << TSB12LV23_BUS_GEN_COUNT_SHFT)
#define TSB12LV23_BUS_MAX_REC_MASK      ((uint32_t)0xF << TSB12LV23_BUS_MAX_REC_SHFT)
#define TSB12LV23_BUS_CLK_ACC_MASK      ((uint32_t)0xFF << TSB12LV23_BUS_CLK_ACC_SHFT)
#define TSB12LV23_BUS_PMC_MASK          ((uint32_t)0x1 << TSB12LV23_BUS_PMC_SHFT)
#define TSB12LV23_BUS_BMC_MASK          ((uint32_t)0x1 << TSB12LV23_BUS_BMC_SHFT)
#define TSB12LV23_BUS_ISC_MASK          ((uint32_t)0x1 << TSB12LV23_BUS_ISC_SHFT)
#define TSB12LV23_BUS_CMC_MASK          ((uint32_t)0x1 << TSB12LV23_BUS_CMC_SHFT)
#define TSB12LV23_BUS_IRMC_MASK         ((uint32_t)0x1 << TSB12LV23_BUS_IRMC_SHFT)

#define TSB12LV23_GET_MAX_REC(_OHCI, _DWORD)                            \
    {                                                                   \
            RD_PCI_MEM_DWORD((_OHCI)->busOptions, (_DWORD));            \
            _DWORD = 0x1 << ((((_DWORD) & TSB12LV23_BUS_MAX_REC_MASK)   \
                               >> TSB12LV23_BUS_MAX_REC_SHFT) + 1);     \
    }


/*
 * GUID Hi Register
 * ----------------
 *
 *  31                                  8 7              0
 * |-------------------------------------|----------------|
 * | Node vendor ID                      | Chip_ID_Hi     |
 * |-------------------------------------|----------------|
 *
 * <0-7>    Chip ID Hi
 * <8-31>   Node vendor ID
 */

/* Shifts */

#define TSB12LV23_GUID_CHIP_ID_HI_SHFT  0
#define TSB12LV23_GUID_VENDOR_ID_SHFT   8

/* Masks */

#define TSB12LV23_GUID_CHIP_ID_HI_MASK  ((uint32_t)0xFF << TSB12LV23_GUID_CHIP_ID_HI_SHFT)
#define TSB12LV23_GUID_VENDOR_ID_MASK   ((uint32_t)0xFFFFFF << TSB12LV23_GUID_VENDOR_ID_SHFT)

/*
 * Self ID Count Register
 * ----------------------
 *
 * 31 30        24 23             16 15  13 12                2 1 0
 * |-|------------|-----------------|------|-------------------|---|
 * |A| xxxxxxxxxx | selfID gen.     | xxxx | selfID size (quad)|xx |
 * |-|------------|-----------------|------|-------------------|---|
 *
 * <2-12>   Self ID size (in quadlets)
 * <16-23>  Self ID Generation
 * <31>     Self ID error
 */

/* Shifts */

#define TSB12LV23_SELF_ID_SIZE_SHFT     2
#define TSB12LV23_SELF_ID_GEN_SHFT      16
#define TSB12LV23_SELF_ID_ERROR_SHFT    31

/* Masks */

#define TSB12LV23_SELF_ID_SIZE_MASK     ((uint32_t)0x7FF << TSB12LV23_SELF_ID_SIZE_SHFT)
#define TSB12LV23_SELF_ID_GEN_MASK      ((uint32_t)0xFF << TSB12LV23_SELF_ID_GEN_SHFT)
#define TSB12LV23_SELF_ID_ERROR_MASK    ((uint32_t)0x01 << TSB12LV23_SELF_ID_ERROR_SHFT)

/* Macros */

#define TSB12LV23_GET_GEN_COUNT(_OHCI, _DWORD)                  \
    {                                                           \
            RD_PCI_MEM_DWORD((_OHCI)->selfIdCount, (_DWORD));   \
            _DWORD = ((_DWORD) & TSB12LV23_SELF_ID_GEN_MASK)    \
                        >> TSB12LV23_SELF_ID_GEN_SHFT;          \
    }

/*
 * LinkControl Register
 * --------------------
 *
 * 31             23       19         11     8                    0
 * |----------------|-|-|-|-------------|-|-|----------------------|
 * | xxxxxxxxxxxxxx |A|B|C| xxxxxxxxxxx |D|E|xxxxxxxxxxxxxxxxxxxxx |
 * |----------------|-|-|-|-------------|-|-|----------------------|
 *
 * <9>      rcvSelfID
 * <10>     rcvPhyPkt
 * <20>     cycleTimerEnable
 * <21>     cycleMaster
 * <22>     cycleSource
 */

/* Shifts */

#define TSB12LV23_RCV_SELF_ID_SHFT      9
#define TSB12LV23_RCV_PHY_PKT_SHFT      10
#define TSB12LV23_CYCLE_TIMER_EN_SHFT   20
#define TSB12LV23_CYCLE_MASTER_SHFT     21
#define TSB12LV23_CYCLE_SOURCE_SHFT     22

/* Masks */

#define TSB12LV23_RCV_SELF_ID_MASK      ((uint32_t)0x01 << TSB12LV23_RCV_SELF_ID_SHFT)
#define TSB12LV23_RCV_PHY_PKT_MASK      ((uint32_t)0x01 << TSB12LV23_RCV_PHY_PKT_SHFT)
#define TSB12LV23_CYCLE_TIMER_EN_MASK   ((uint32_t)0x01 << TSB12LV23_CYCLE_TIMER_EN_SHFT)
#define TSB12LV23_CYCLE_MASTER_MASK     ((uint32_t)0x01 << TSB12LV23_CYCLE_MASTER_SHFT)
#define TSB12LV23_CYCLE_SOURCE_MASK     ((uint32_t)0x01 << TSB12LV23_CYCLE_SOURCE_SHFT)

/*
 * Node ID and status Register
 * ---------------------------
 *
 *  31 30 29  27 26                   17 16             6 5           0
 * |--|--|---|--|-----------------------|----------------|------------|
 * | A| B|xx | C| xxxxxxxxxxx           | busNumber      | nodeNumber |
 * |--|--|---|--|-----------------------|----------------|------------|
 *
 * <0-5>    Physical node number
 * <6-15>   Bus number
 * <27>     CPS (cable power status) is set when OK
 * <30>     root is set when it is the root node
 * <31>     iDValid is set when it is a valid node number
 */

/* Shifts */

#define TSB12LV23_NOD_NODE_SHFT     0
#define TSB12LV23_NOD_BUS_SHFT      6
#define TSB12LV23_NOD_CPS_SHFT      27
#define TSB12LV23_NOD_ROOT_SHFT     30
#define TSB12LV23_NOD_VALID_SHFT    31

/* Masks */

#define TSB12LV23_NOD_NODE_MASK     ((uint32_t)0x3F << TSB12LV23_NOD_NODE_SHFT)
#define TSB12LV23_NOD_BUS_MASK      ((uint32_t)0x3FF << TSB12LV23_NOD_BUS_SHFT)
#define TSB12LV23_NOD_CPS_MASK      ((uint32_t)0x1 << TSB12LV23_NOD_CPS_SHFT)
#define TSB12LV23_NOD_ROOT_MASK     ((uint32_t)0x1 << TSB12LV23_NOD_ROOT_SHFT)
#define TSB12LV23_NOD_VALID_MASK    ((uint32_t)0x1 << TSB12LV23_NOD_VALID_SHFT)


/*
 * PhyControl Register
 * -------------------
 *
 * 31 30    27    24 23            16     13 11      8 7              0
 * |-|-----|--------|----------------|-|-|--|---------|----------------|
 * |A| xxx | rdAddr |     rdData     |B|C|xx| regAddr |  wrData        |
 * |-|-----|--------|----------------|-|-|--|---------|----------------|
 *
 * <0-7>    Data to write in the PHY register
 * <8-11>   Register address to reasd or write
 * <14>     Bit initiating a write request
 * <15>     Bit initiating a read request
 * <16-23>  Contains the data read from the PHY layer
 * <24-27>  The last address read from the PHY
 * <31>     Set to 1 when the operation is completed
 */

/* Shifts */

#define TSB12LV23_PHY_WR_DATA_SHFT  0
#define TSB12LV23_PHY_REG_ADDR_SHFT 8
#define TSB12LV23_PHY_WR_REQ_SHFT   14
#define TSB12LV23_PHY_RD_REQ_SHFT   15
#define TSB12LV23_PHY_RD_DATA_SHFT  16
#define TSB12LV23_PHY_RD_ADDR_SHFT  24
#define TSB12LV23_PHY_DONE_SHFT     31

/* Masks */

#define TSB12LV23_PHY_WR_DATA_MASK  ((uint32_t)0xFF << TSB12LV23_PHY_WR_DATA_SHFT)
#define TSB12LV23_PHY_REG_ADDR_MASK ((uint32_t)0xF << TSB12LV23_PHY_REG_ADDR_SHFT)
#define TSB12LV23_PHY_WR_REQ_MASK   ((uint32_t)0x1 << TSB12LV23_PHY_WR_REQ_SHFT)
#define TSB12LV23_PHY_RD_REQ_MASK   ((uint32_t)0x1 << TSB12LV23_PHY_RD_REQ_SHFT)
#define TSB12LV23_PHY_RD_DATA_MASK  ((uint32_t)0xFF << TSB12LV23_PHY_RD_DATA_SHFT)
#define TSB12LV23_PHY_RD_ADDR_MASK  ((uint32_t)0xF << TSB12LV23_PHY_RD_ADDR_SHFT)
#define TSB12LV23_PHY_DONE_MASK     ((uint32_t)0x1 << TSB12LV23_PHY_DONE_SHFT)


/*
 * Isoch. Cycle Timer register
 * ---------------------------
 *
 *  31          25 24                  12 11                     0
 * |--------------|----------------------|------------------------|
 * | cycleSeconds | cycleCount           | cycleOffset            |
 * |--------------|----------------------|------------------------|
 *
 * <0-11>   Cycle Offset. 24.576-MHz cycle-timer counter.
 * <12-24>  Cycle Count. 8000-Hz cycle-timer counter.
 * <25-31>  Seconds Count. 1-Hz cycle-timer counter.
 */

/* Shifts. */

#define TSB12LV23_SECOND_COUNT_SHFT     25
#define TSB12LV23_CYCLE_COUNT_SHFT      12
#define TSB12LV23_CYCLE_OFFSET_SHFT     0

/* Masks. */

#define TSB12LV23_SECOND_COUNT_MASK ((uint32_t)0x007F << TSB12LV23_SECOND_COUNT_SHFT)
#define TSB12LV23_CYCLE_COUNT_MASK  ((uint32_t)0x1FFF << TSB12LV23_CYCLE_COUNT_SHFT)
#define TSB12LV23_CYCLE_OFFSET_MASK ((uint32_t)0x0FFF << TSB12LV23_CYCLE_OFFSET_SHFT)


/*
 * Asynchronous Request Filter Register
 * ------------------------------------
 */
#define TSB12LV23_ASYNC_REQ_FILTER_ALL  0x80000000


/*
 * ContextControl Register
 * -----------------------
 *
 * 31                            16 15   13 12 11 10 9  8 7    5 4        0
 * |-------------------------------|--|----|--|--|--|----|------|----------|
 * | xxxxxxxxxxxxxxxxxxxxxxxxxxxxx |R |xxxx|W |D |A |xxxx| Spd  | xferCode |
 * |-------------------------------|--|----|--|--|--|----|------|----------|
 *
 * <0-4>    Contains the reception / transmission status code
 * <5-7>    Contains the transmission speed
 * <10>     Active bit
 * <11>     Dead bit
 * <12>     Wake bit
 * <15>     Run bit
 */

/* Shifts */

#define TSB12LV23_CC_CODE_SHFT      0
#define TSB12LV23_CC_SPEED_SHFT     5
#define TSB12LV23_CC_ACTIVE_SHFT    10
#define TSB12LV23_CC_DEAD_SHFT      11
#define TSB12LV23_CC_WAKE_SHFT      12
#define TSB12LV23_CC_RUN_SHFT       15

/* Masks */

#define TSB12LV23_CC_CODE_MASK      ((uint32_t)0x1F << TSB12LV23_CC_CODE_SHFT)
#define TSB12LV23_CC_SPEED_MASK     ((uint32_t)0x07 << TSB12LV23_CC_SPEED_SHFT)
#define TSB12LV23_CC_ACTIVE_MASK    ((uint32_t)0x01 << TSB12LV23_CC_ACTIVE_SHFT)
#define TSB12LV23_CC_DEAD_MASK      ((uint32_t)0x01 << TSB12LV23_CC_DEAD_SHFT)
#define TSB12LV23_CC_WAKE_MASK      ((uint32_t)0x01 << TSB12LV23_CC_WAKE_SHFT)
#define TSB12LV23_CC_RUN_MASK       ((uint32_t)0x01 << TSB12LV23_CC_RUN_SHFT)

/* Used for fast acknowledge type identification */
#define TSB12LV23_CC_ACODE_MASK     ((uint32_t)0x0F << TSB12LV23_CC_CODE_SHFT)
#define TSB12LV23_CC_ASTAT_MASK     ((uint32_t)0x10 << TSB12LV23_CC_CODE_SHFT)


/*
 * Iso Tx ContextControl Register
 * ------------------------------
 *
 * 31  30                        16 15   13 12 11 10 9  8 7    5 4        0
 * |--|----------------------------|--|----|--|--|--|----|------|----------|
 * |C | cycleMatch                 |R |xxxx|W |D |A |xxxx| Spd  | xferCode |
 * |--|----------------------------|--|----|--|--|--|----|------|----------|
 *
 * <0-4>    Contains the reception / transmission status code
 * <5-7>    Speed (not meaningful for isochronous transmit context)
 * <10>     Active bit
 * <11>     Dead bit
 * <12>     Wake bit
 * <15>     Run bit
 * <16-30>  Cycle match
 * <31>     Cycle match enabled
 */

/* Shifts */

#define TSB12LV23_CC_ISO_TX_CM_SHFT     16
#define TSB12LV23_CC_ISO_TX_CM_EN_SHFT  31

/* Masks */

#define TSB12LV23_CC_ISO_TX_CM_MASK     ((uint32_t)0x7FFF << TSB12LV23_CC_ISO_TX_CM_SHFT)
#define TSB12LV23_CC_ISO_TX_CM_EN_MASK  ((uint32_t)0x1 << TSB12LV23_CC_ISO_TX_CM_EN_SHFT)


/*
 * Iso Rx ContextControl Register
 * ------------------------------
 *
 *  31 30 29 28 27 26            16 15   13 12 11 10 9  8 7    5 4        0
 * |--|--|--|--|--|----------------|--|----|--|--|--|----|------|----------|
 * |B |H |C |M |DB| xxxxxxxxxxxxxx |R |xxxx|W |D |A |xxxx| Spd  | xferCode |
 * |--|--|--|--|--|----------------|--|----|--|--|--|----|------|----------|
 *
 * <0-4>    Contains the reception / transmission status code
 * <5-7>    Contains the received speed
 * <10>     Active bit
 * <11>     Dead bit
 * <12>     Wake bit
 * <15>     Run bit
 * <27>     Dual buffer mode
 * <28>     Multi channel mode
 * <29>     Cycle match enabled
 * <30>     Isochronous header
 * <31>     Buffer fill mode
 */

/* Shifts */

#define TSB12LV23_CC_ISO_RX_DUAL_MODE_SHFT  27
#define TSB12LV23_CC_ISO_RX_M_CH_MODE_SHFT  28
#define TSB12LV23_CC_ISO_RX_CM_EN_SHFT      29
#define TSB12LV23_CC_ISO_RX_HEADER_SHFT     30
#define TSB12LV23_CC_ISO_RX_BUF_FILL_SHFT   31

/* Masks */

#define TSB12LV23_CC_ISO_RX_DUAL_MODE_MASK  ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_DUAL_MODE_SHFT)
#define TSB12LV23_CC_ISO_RX_M_CH_MODE_MASK  ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_M_CH_MODE_SHFT)
#define TSB12LV23_CC_ISO_RX_CM_EN_MASK      ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_CM_EN_SHFT)
#define TSB12LV23_CC_ISO_RX_HEADER_MASK     ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_HEADER_SHFT)
#define TSB12LV23_CC_ISO_RX_BUF_FILL_MASK   ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_BUF_FILL_SHFT)



/*
 * Iso Rx ContextMatch Register
 * ----------------------------
 *
 *  31 30 29 28 27 26                    12 11   8 7  6  5        0
 * |--|--|--|--|--|------------------------|------|--|--|----------|
 * |T3|T2|T1|T0|xx| cycleMatch             | sync |xx|TF| channel  |
 * |--|--|--|--|--|------------------------|------|--|--|----------|
 *
 * <0-5>    Channel Number
 * <6>      Tag 1 Sync Filter
 * <8-11>   Sync field match
 * <12-26>  Cycle match
 * <27>     Dual buffer mode
 * <28>     Tag 0 match
 * <29>     Tag 1 match
 * <30>     Tag 2 match
 * <31>     Tag 3 match
 */

/* Shifts */

#define TSB12LV23_CC_ISO_RX_CHANNEL_SHFT    0
#define TSB12LV23_CC_ISO_RX_TAG1_FILT_SHFT  6
#define TSB12LV23_CC_ISO_RX_SYNC_SHFT       8
#define TSB12LV23_CC_ISO_RX_CM_SHFT         12
#define TSB12LV23_CC_ISO_RX_T0_SHFT         28
#define TSB12LV23_CC_ISO_RX_T1_SHFT         29
#define TSB12LV23_CC_ISO_RX_T2_SHFT         30
#define TSB12LV23_CC_ISO_RX_T3_SHFT         31

/* Masks */

#define TSB12LV23_CC_ISO_RX_CHANNEL_MASK    ((uint32_t)0x3F << TSB12LV23_CC_ISO_RX_CHANNEL_SHFT)
#define TSB12LV23_CC_ISO_RX_TAG1_FILT_MASK  ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_TAG1_FILT_SHFT)
#define TSB12LV23_CC_ISO_RX_SYNC_MASK       ((uint32_t)0xF << TSB12LV23_CC_ISO_RX_SYNC_SHFT)
#define TSB12LV23_CC_ISO_RX_CM_MASK         ((uint32_t)0x7FFF << TSB12LV23_CC_ISO_RX_CM_SHFT)
#define TSB12LV23_CC_ISO_RX_T0_MASK         ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_T0_SHFT)
#define TSB12LV23_CC_ISO_RX_T1_MASK         ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_T1_SHFT)
#define TSB12LV23_CC_ISO_RX_T2_MASK         ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_T2_SHFT)
#define TSB12LV23_CC_ISO_RX_T3_MASK         ((uint32_t)0x1 << TSB12LV23_CC_ISO_RX_T3_SHFT)


/*
 * xferStatus and timeStamp
 * ------------------------
 *
 *  31   29 28 27 26 25 24 23  21 20      16 15 13 12                      0
 * |--|----|--|--|--|-----|------|----------|-----|-------------------------|
 * |R |xxxx|W |D |A |xxxxx| Spd  | xferCode | sec.| cycleCount              |
 * |--|----|--|--|--|-----|------|----------|-----|-------------------------|
 *
 * <0-15>   TimeStamp
 * <0-12>   cycleCount
 * <13-15>  cycleSeconds
 * <16-20>  Contains the reception / transmission status code
 * <21-23>  Contains the transmission speed
 * <26>     Active bit
 * <27>     Dead bit
 * <28>     Wake bit
 * <31>     Run bit
 */

/* Shifts */

#define TSB12LV23_TIME_STAMP_SHFT       0
#define TSB12LV23_TIME_STAMP_COUNT_SHFT 0
#define TSB12LV23_TIME_STAMP_SEC_SHFT   13
#define TSB12LV23_XFER_CODE_SHFT        16
#define TSB12LV23_XFER_SPEED_SHFT       21
#define TSB12LV23_XFER_ACTIVE_SHFT      26
#define TSB12LV23_XFER_DEAD_SHFT        27
#define TSB12LV23_XFER_WAKE_SHFT        28
#define TSB12LV23_XFER_RUN_SHFT         31

/* Masks */

#define TSB12LV23_TIME_STAMP_MASK       ((uint32_t)0xFFFF << TSB12LV23_TIME_STAMP_SHFT)
#define TSB12LV23_TIME_STAMP_COUNT_MASK ((uint32_t)0x1FFF << TSB12LV23_TIME_STAMP_COUNT_SHFT)
#define TSB12LV23_TIME_STAMP_SEC_MASK   ((uint32_t)0x7 << TSB12LV23_TIME_STAMP_SEC_SHFT)
#define TSB12LV23_XFER_CODE_MASK        ((uint32_t)0x1F << TSB12LV23_XFER_CODE_SHFT)
#define TSB12LV23_XFER_SPEED_MASK       ((uint32_t)0x07 << TSB12LV23_XFER_SPEED_SHFT)
#define TSB12LV23_XFER_ACTIVE_MASK      ((uint32_t)0x01 << TSB12LV23_XFER_ACTIVE_SHFT)
#define TSB12LV23_XFER_DEAD_MASK        ((uint32_t)0x01 << TSB12LV23_XFER_DEAD_SHFT)
#define TSB12LV23_XFER_WAKE_MASK        ((uint32_t)0x01 << TSB12LV23_XFER_WAKE_SHFT)
#define TSB12LV23_XFER_RUN_MASK         ((uint32_t)0x01 << TSB12LV23_XFER_RUN_SHFT)

#define TSB12LV23_TIME_STAMP_COUNT_ROLLOVER		8000

/* Packet event code */
#define TSB12LV23_EVT_NO_STATUS         0x0
#define TSB12LV23_EVT_LONG_PACKET       0x2
#define TSB12LV23_EVT_MISSING_ACK       0x3
#define TSB12LV23_EVT_UNDERRUN          0x4
#define TSB12LV23_EVT_OVERRUN           0x5
#define TSB12LV23_EVT_DESCRIPTOR_READ   0x6
#define TSB12LV23_EVT_DATA_READ         0x7
#define TSB12LV23_EVT_DATA_WRITE        0x8
#define TSB12LV23_EVT_BUS_RESET         0x9
#define TSB12LV23_EVT_TIMEOUT           0xA
#define TSB12LV23_EVT_TCODE_ERR         0xB
#define TSB12LV23_EVT_UNKNOWN           0xE
#define TSB12LV23_EVT_FLUSHED           0xF

#define TSB12LV23_EVT_ACK_CMPL          0x11
#define TSB12LV23_EVT_ACK_PEND          0x12
#define TSB12LV23_EVT_ACK_BUSY_X        0x14
#define TSB12LV23_EVT_ACK_BUSY_A        0x15
#define TSB12LV23_EVT_ACK_BUSY_B        0x16
#define TSB12LV23_EVT_ACK_TARDY         0x1B
#define TSB12LV23_EVT_ACK_DATA_ERR      0x1D
#define TSB12LV23_EVT_ACK_TYPE_ERR      0x1E

/* locals */

/* forward declarations */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCtsb12lv23h */
