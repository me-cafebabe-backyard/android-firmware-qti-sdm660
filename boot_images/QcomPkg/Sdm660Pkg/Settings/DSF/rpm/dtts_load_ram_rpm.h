#ifndef __DTTS_LOAD_RAM_RPM_H__
#define __DTTS_LOAD_RAM_RPM_H__


/*==============================================================================
                      Warning: This file is auto-generated
================================================================================
                   Copyright (c) 2015 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#define NUM_SLAB	0x14CC
#define CURR_OSC	0x14D0
#define CURR_OSC_MIN	0x14D4
#define CURR_OSC_MAX	0x14D8
#define OSC_SLAB_NDX	0x14DC
#define OSC_SLAB	0x14E0
#define PHYBISCREG	0x16E0
#define PHYUPDREG	0x16F0
#define FPMBASEREG	0x1700
#define FUNCCDCREG	0x1710
#define PHY_CSR_CH_OFFSET	0x1720
#define UPDCDC	0x1724
#define PREVCDC	0x1744
#define OSC_THRESHOLD	0x1764
#define FREQ_SWITCH_REQ	0x1774
#define SAMPLED_ENOUGH	0x1778
#define ALGO_DEBUG	0x177C
#define CDC_BOOT_COARSE_FINE_LOG	0x1780
#define HANG_EN	0x17C0
#define CDC_VALUE_CHANGES_CNT	0x17C4
#define CDC_VALUE_CHANGES_PTR	0x17C8
#define CDC_CHANGE_LOG	0x17CC
#define OSC_CNT_PREV_MIN_CHB	0x186C
#define OSC_CNT_PREV_MIN_CHA	0x1874
#define OSC_CNT_PREV_MAX_CHB	0x187C
#define OSC_CNT_PREV_MAX_CHA	0x1884
#define OSC_CNT_MIN_MAX_LOG_PTR	0x188C
#define OSC_CNT_MIN_MAX_LOG	0x189C
#define ERROR_CNT	0x1B1C
#define DISABLE_CDC_UPD	0x1B20
#define CDC_UPDATE_NEEDED	0x1B24
#define CDC_UPDATE_FORCED	0x1B28
#define NEW_CDC_GT_CURR	0x1B2C
#define CDC_DELTA_FROM_CURR	0x1B30
#define OSCAVGGTBOOT	0x1B34
#define OSC_AVG	0x1B54
#define OSCDELTA	0x1B74
#define MAX_STEP_SIZE	0x1B94
#define MAX_DELTA_REG	0x1B98
#define MAX_DIT_DELTA	0x1BA8
#define DELTA	0x1BC8
#define NUM_CDC_UPD_TRAC_FORCED	0x1BCC
#define NUM_CDC_UPD_ACQ_FORCED	0x1BD0
#define NUM_CDC_UPD_TRAC_NEEDED	0x1BD4
#define NUM_CDC_UPD_ACQ_NEEDED	0x1BD8
#define CHA_SUM	0x1BDC
#define CHB_SUM	0x1BEC
#define CHA_OSC_ARR	0x1BFC
#define CHB_OSC_ARR	0x1CFC
#define LOG_PTR	0x1DFC
#define PT_REQ_CNT_PER_FREQ	0x1E00
#define PT_REQ_CNT_CURR_SWITCH	0x1E10
#define PT_REQ_CNT_TOTAL	0x1E18
#define FREQ_SWITCH_CNT	0x1E20
#define NUM_VALID_SAMPLES	0x1E24
#define FLAG_SAMPLES	0x1E28
#define OSC_CNT_PTR	0x1E38
#define ACQ_CNT	0x1E48
#define PT_CALC_READY	0x1E50
#define ACQ_DONE	0x1E58
#define ACQ_TRAC_MODE_LAST	0x1E5C
#define ACQ_TRAC_MODE	0x1E60
#define CH_INDX	0x1E64
#define DQ_INDX	0x1E68
#define RANK_INDX	0x1E6C
#define FREQ_INDX	0x1E70
#define BOOT_OSC_CNT_CHA	0x1E74
#define BOOT_OSC_CNT_CHB	0x1E7C
#define CURR_OSC_CNT_CHA	0x1E84
#define CURR_OSC_CNT_CHB	0x1E88
#define CURR_RANK	0x1E8C
#define WAKEUP_REASON	0x1E90
#define CDC_DELTA_FINE_STEPS	0x1E94
#define PREV_CDC_FINE_STEP	0x1EB4
#define BOOT_CDC_FINE	0x1ED4
#define BOOT_CDC_COARSE	0x1EF4
#define NEXT_CDC	0x1F14
#define PREV_CDC	0x1F54
#define BOOT_CDC	0x1F94
#define MAX_FINE_STEPS_FROM_BOOT	0x1FD4
#define BOOT_OSC_ARR	0x1FD8
#define CURR_SAMPLES	0x1FE8
#define TOT_SAMPLES	0x1FEC
#define NUM_RANK	0x1FF0
#define CDC_ERROR	0x1FF4
#define PT_ENABLE	0x1FF8
#define SUM	0x1FFC


#endif
