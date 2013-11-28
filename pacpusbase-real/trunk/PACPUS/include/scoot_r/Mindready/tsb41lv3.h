/* tsb41lv3.c - TSB41LV03 typedef and defines */

/* Copyright(c) 1999, Sederta Inc. All rights reserved. */

/*
modification history
--------------------
01h,11Jul00,spa Changed main structure
01g,2Sep99,fb4 Added TSB41LV03_INIT_TIME and updated TSB41LV03_RESET_TIME
01f,17Aug99,fb4 Added TSB41LV03_RESET_TIME
01e,10Aug99,fb4 Updated copyright
01d,2Jul99,fb4 Updated TSB41LV03_CPS_MASK mask
01c,28Apr99,fb4 Corrected compilation stuff
01b,27Apr99,fb4 Update from offset 6 of ..._REGOFF (not used)
01a,27Apr99,fb4 This file was created.
*/

/*
This module contains specific typedef and defines for the Texas Instrument
IEEE 1394 physical layer TSB41LV03.

INCLUDES FILES: sdtypes.h
*/

#ifndef __INCtsb41lv3h
#define __INCtsb41lv3h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */

#include "stdint.h"

/* defines */

#define TSB41LV03_RESET_TIME    10   /* Reset time in usec */
#define TSB41LV03_INIT_TIME 2000     /* Re-initialization time in usec */

/*
 * Register offsets
 */

#define TSB41LV03_PHY_ID_REGOFF     0x0
#define TSB41LV03_GAPCOUNT_REGOFF   0x1
#define TSB41LV03_PORT_REGOFF       0x2
#define TSB41LV03_SPEED_REGOFF      0x3
#define TSB41LV03_POWER_REGOFF      0x4
#define TSB41LV03_INT_REGOFF        0x5
#define TSB41LV03_SELECT_REGOFF     0x7
#define TSB41LV03_STAT_REGOFF       0x8
#define TSB41LV03_PEER_REGOFF       0x9

/*
 * Physical ID register
 */

#define TSB41LV03_PHY_ID_SHFT   2
#define TSB41LV03_R_SHFT        1
#define TSB41LV03_CPS_SHFT      0

#define TSB41LV03_PHY_ID_MASK   ((uint32_t)0x3F << TSB41LV03_PHY_ID_SHFT)
#define TSB41LV03_R_MASK        ((uint32_t)0x1 << TSB41LV03_R_SHFT)
#define TSB41LV03_CPS_MASK      ((uint32_t)0x1 << TSB41LV03_CPS_SHFT)

/*
 * Gap count register
 */

#define TSB41LV03_RHB_SHFT      7
#define TSB41LV03_IBR_SHFT      6
#define TSB41LV03_GC_SHFT       0

#define TSB41LV03_RHB_MASK      ((uint32_t)0x1 << TSB41LV03_RHB_SHFT)
#define TSB41LV03_IBR_MASK      ((uint32_t)0x1 << TSB41LV03_IBR_SHFT)
#define TSB41LV03_GC_MASK       ((uint32_t)0x3F << TSB41LV03_GC_SHFT)

/*
 * Port register
 */

#define TSB41LV03_EXTENDED_SHFT     5
#define TSB41LV03_NUM_PORTS_SHFT    0

#define TSB41LV03_EXTENDED_MASK     ((uint32_t)0x7 << TSB41LV03_EXTENDED_SHFT)
#define TSB41LV03_NUM_PORTS_MASK    ((uint32_t)0xF << TSB41LV03_NUM_PORTS_SHFT)

/*
 * Speed register
 */

#define TSB41LV03_SPEED_SHFT    5
#define TSB41LV03_DELAY_SHFT    0

#define TSB41LV03_SPEED_MASK    ((uint32_t)0x7 << TSB41LV03_SPEED_SHFT)
#define TSB41LV03_DELAY_MASK    ((uint32_t)0xF << TSB41LV03_DELAY_SHFT)

/*
 * Power register
 */

#define TSB41LV03_LSTAT_SHFT    7
#define TSB41LV03_CSTAT_SHFT    6
#define TSB41LV03_JITTER_SHFT   3
#define TSB41LV03_CLASS_SHFT    0

#define TSB41LV03_LSTAT_MASK    ((uint32_t)0x1 << TSB41LV03_LSTAT_SHFT)
#define TSB41LV03_CSTAT_MASK    ((uint32_t)0x1 << TSB41LV03_CSTAT_SHFT)
#define TSB41LV03_JITTER_MASK   ((uint32_t)0x7 << TSB41LV03_JITTER_SHFT)
#define TSB41LV03_CLASS_MASK    ((uint32_t)0x7 << TSB41LV03_CLASS_SHFT)

/*
 * Interrupt register
 */

#define TSB41LV03_RPIE_SHFT 7
#define TSB41LV03_ISBR_SHFT 6
#define TSB41LV03_CTOI_SHFT 5
#define TSB41LV03_CPSI_SHFT 4
#define TSB41LV03_STOI_SHFT 3
#define TSB41LV03_PEI_SHFT  2
#define TSB41LV03_EAA_SHFT  1
#define TSB41LV03_EMC_SHFT  0

#define TSB41LV03_RPIE_MASK ((uint32_t)0x1 << TSB41LV03_RPIE_SHFT)
#define TSB41LV03_ISBR_MASK ((uint32_t)0x1 << TSB41LV03_ISBR_SHFT)
#define TSB41LV03_CTOI_MASK ((uint32_t)0x1 << TSB41LV03_CTOI_SHFT)
#define TSB41LV03_CPSI_MASK ((uint32_t)0x1 << TSB41LV03_CPSI_SHFT)
#define TSB41LV03_STOI_MASK ((uint32_t)0x1 << TSB41LV03_STOI_SHFT)
#define TSB41LV03_PEI_MASK  ((uint32_t)0x1 << TSB41LV03_PEI_SHFT)
#define TSB41LV03_EAA_MASK  ((uint32_t)0x1 << TSB41LV03_EAA_SHFT)
#define TSB41LV03_EMC_MASK  ((uint32_t)0x1 << TSB41LV03_EMC_SHFT)

/*
 * Port and page select register
 */

#define TSB41LV03_PAGE_SHFT 5
#define TSB41LV03_PORT_SHFT 0

#define TSB41LV03_PAGE_MASK ((uint32_t)0x7 << TSB41LV03_PAGE_SHFT)
#define TSB41LV03_PORT_MASK ((uint32_t)0xF << TSB41LV03_PORT_SHFT)

/*
 * Status register
 */

#define TSB41LV03_ASTAT_SHFT    6
#define TSB41LV03_BSTAT_SHFT    4
#define TSB41LV03_CH_SHFT       3
#define TSB41LV03_CON_SHFT      2
#define TSB41LV03_BIAS_SHFT     1
#define TSB41LV03_DIS_SHFT      0

#define TSB41LV03_ASTAT_MASK    ((uint32_t)0x3 << TSB41LV03_ASTAT_SHFT)
#define TSB41LV03_BSTAT_MASK    ((uint32_t)0x3 << TSB41LV03_BSTAT_SHFT)
#define TSB41LV03_CH_MASK       ((uint32_t)0x1 << TSB41LV03_CH_SHFT)
#define TSB41LV03_CON_MASK      ((uint32_t)0x1 << TSB41LV03_CON_SHFT)
#define TSB41LV03_BIAS_MASK     ((uint32_t)0x1 << TSB41LV03_BIAS_SHFT)
#define TSB41LV03_DIS_MASK      ((uint32_t)0x1 << TSB41LV03_DIS_SHFT)

/*
 * Peer register
 */

#define TSB41LV03_PEER_SPEED_SHFT   5
#define TSB41LV03_PIE_SHFT          4
#define TSB41LV03_FAULT_SHFT        3

#define TSB41LV03_PEER_SPEED_MASK   ((uint32_t)0x7 << TSB41LV03_PEER_SPEED_SHFT)
#define TSB41LV03_PIE_MASK          ((uint32_t)0x1 << TSB41LV03_PIE_SHFT)
#define TSB41LV03_FAULT_MASK        ((uint32_t)0x1 << TSB41LV03_FAULT_SHFT)

#define TSB41LV03_MAX_NB_PORT   3
/* typedefs */

typedef struct portHeader
    {
    uint8_t status;
    uint8_t peer;
    uint8_t reserved[6];
    }PORT;

typedef struct tsb41lv03_s
    {
    uint8_t phyId;
    uint8_t gapCount;
    uint8_t port;
    uint8_t speed;
    uint8_t power;
    uint8_t interrupt;
    uint8_t reserved1;
    uint8_t select;
    PORT portStat[TSB41LV03_MAX_NB_PORT];
    } tsb41lv03_t;

/* globals */

/* locals */

/* forward declarations */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCtsb41lv3h */
