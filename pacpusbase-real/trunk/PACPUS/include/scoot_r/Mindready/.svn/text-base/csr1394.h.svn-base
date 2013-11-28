/* csr1394.h - IEEE 1394-1995 Standard CSR defines */

/* Copyright(c) 1999, Sederta Inc. All rights reserved. */

/*
 * $Log: /Common/Design/Src/Default/Dev/Linux/main/csr1394.h $
 * 
 * 7     7/05/01 5:49p Jfha
 * Add a new line at the end of the file for linux
 * 
 * 6     2/20/01 5:03p Jfha
 * Change comment type
 *
 * $NoKeywords: $
 */

/*
01g,19dec00,blc Relocated CSR services to services.h
01f,05jun00,apou Added Broadcast Channel address
01e,10Jan00,lep Added CSR_LOCK service
01d,19Aug99,fb4 Moved CSR stuff from services.h
01c,17Aug99,fb4 Reloaded file from version 0.5f
01b,10Aug99,fb4 Updated copyright
01a,20Jul99,fb4 This file was created
*/

/*
This module contains IEEE 1394-1995 Standard CSR defines.
*/

#ifndef __INCcsr1394h
#define __INCcsr1394h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */

/* defines */

/* addresses */

#define CSR1394_STATE_CLEAR_ADDR            0x0000
#define CSR1394_STATE_SET_ADDR              0x0004
#define CSR1394_NODE_IDS_ADDR               0x0008
#define CSR1394_RESET_START_ADDR            0x000C
#define CSR1394_SPLIT_TIMEOUT_HI_ADDR       0x0018
#define CSR1394_SPLIT_TIMEOUT_LOW_ADDR      0x001C

#define CSR1394_CYCLE_TIME_ADDR		        0x0200
#define CSR1394_BUS_TIME_ADDR		        0x0204
#define CSR1394_BUSY_TIMEOUT_ADDR	        0x0210
#define CSR1394_PRIORITY_BUDGET_ADDR	    0x0218
#define CSR1394_BUS_MANAGER_ID_ADDR	        0x021C
#define CSR1394_BANDWIDTH_AVAILABLE_ADDR    0x0220
#define CSR1394_CHANNELS_AVAILABLE_HI_ADDR	0x0224
#define CSR1394_CHANNELS_AVAILABLE_LOW_ADDR	0x0228
#define CSR1394_BROADCAST_CHANNEL_ADDR		0x0234

#define CSR1394_ROM_INFO_ADDR               0x0400
#define CSR1394_ROM_BUS_ID_ADDR             0x0404
#define CSR1394_ROM_BUS_OPTIONS_ADDR        0x0408
#define CSR1394_ROM_GUID_HI_ADDR            0x040C
#define CSR1394_ROM_GUID_LOW_ADDR           0x0410
#define CSR1394_ROM_ROOT_DIR_ADDR           0x0414
#define CSR1394_ROM_LOW_ADDR	            CSR1394_ROM_INFO_ADDR
#define CSR1394_ROM_SIZE	                0x0400
#define CSR1394_ROM_HI_ADDR	                CSR1394_ROM_INFO_ADDR \
                                                + CSR1394_ROM_SIZE

#define CSR1394_TOPOLOGY_MAP_LOW_ADDR	    0x1000
#define CSR1394_TOPOLOGY_MAP_SIZE	        0x0400
#define CSR1394_TOPOLOGY_MAP_HI_ADDR	    CSR1394_TOPOLOGY_MAP_LOW_ADDR \
                                                + CSR1394_TOPOLOGY_MAP_SIZE
#define CSR1394_SPEED_MAP_LOW_ADDR	        0x2000
#define CSR1394_SPEED_MAP_SIZE	            0x1000
#define CSR1394_SPEED_MAP_HI_ADDR	        CSR1394_SPEED_MAP_LOW_ADDR \
                                                + CSR1394_SPEED_MAP_SIZE

/*
 * CSR registers. See IEEE 1394-1995 Standard Paragraph 4.3.4.2
 *
 * Mapping:
 *
 * CYCLE_TIME register:
 * --------------------
 * MSB                              LSB
 *  31   25 24         12 11         0
 * |-------|-------------|------------|
 * |xxxxxxx|xxxxxxxxxxxxx|xxxxxxxxxxxx|
 * |-------|-------------|------------|
 *
 * <0-11> cycle_offset - Increment each isochronous cycle. Wrap around to 0 when
 *                       3071 is reached
 * <12-24> cycle_count - Increment when the cycle_offset wraps around. Wrap
 *                       around when 7999 is reached.
 * <25-31> second_count - Increment when the cycle_count wraps around. Wrap
 *                        around when 127 is reached
 * This register is fully read/write.
 *
 * BUS_TIME register:
 * --------------------
 * MSB                              LSB
 *  31                      7 6     0
 * |-------------------------|-------|
 * |xxxxxxxxxxxxxxxxxxxxxxxxx|xxxxxxx|
 * |-------------------------|-------|
 *
 * <0-6> second_count_lo - Contain the second_count field of the cycle time
 *                         register. This field is read only.
 * <7-31> second_count_hi - Increment when the second_count_lo wraps around.
 *                          This field is read/write
 *
 */

/* shifts */

#define CSR1394_CYCLE_OFFSET_SHFT		0
#define CSR1394_CYCLE_COUNT_SHFT		12
#define CSR1394_SECOND_COUNT_SHFT		25
#define CSR1394_SECOND_COUNT_HI_SHFT	7
#define CSR1394_SECOND_COUNT_LO_SHFT	0

/* masks */

#define CSR1394_CYCLE_OFFSET_MASK		0xFFF
#define CSR1394_CYCLE_COUNT_MASK		0x1FFF
#define CSR1394_SECOND_COUNT_MASK		0x7F
#define CSR1394_SECOND_COUNT_HI_MASK	0x1FFFFFF
#define CSR1394_SECOND_COUNT_LO_MASK	0x7F

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCcsr1394h */
