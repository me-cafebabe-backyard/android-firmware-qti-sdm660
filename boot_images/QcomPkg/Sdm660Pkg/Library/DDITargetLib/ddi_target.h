#ifndef _BOOT_DDI_TARGET_H
#define _BOOT_DDI_TARGET_H
/*===========================================================================

                    BOOT DDI TARGET DECLARATIONS

DESCRIPTION
  Contains target specific code for Boot DDR Debug Image tool.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
20/12/2016  zhz     Added the target related function
09/14/2016  jh       Initial file creation
===========================================================================*/

#include "ddr_common.h"
#include "HALhwio.h"
#include "ddrss_rpm.h"

#define ADDRESS_DECODE_RANK_BIT_LOCATION 30 
#define ADDRESS_DECODE_RANK_BIT_WIDTH 0x1 

#define ADDRESS_DECODE_CHANNEL_BIT_LOCATION 10
#define ADDRESS_DECODE_CHANNEL_BIT_WIDTH 0x1

#define DDI_BIMC_DDR0_DPE_BASE       (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_DPE_OFFSET)
#define DDI_BIMC_DDR1_DPE_BASE       (BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_DPE_OFFSET)

#define DDI_DPE_CONFIG_9_VAL_DISABLE (HWIO_DPE_CONFIG_9_ARBITER_OPTIMIZER_BMSK | HWIO_DPE_CONFIG_9_EARLY_TRAFFIC_EN_BMSK)
#define DDI_DPE_CONFIG_4_VAL_DISABLE (HWIO_DPE_CONFIG_4_LOAD_ALL_CONFIG_BMSK)

#define DDI_DDR_PHY_CH0_CA0_BASE (REG_OFFSET_DDR_PHY_CH(0) + CA0_DDR_PHY_OFFSET)
#define DDI_DDR_PHY_CH1_CA0_BASE (REG_OFFSET_DDR_PHY_CH(1) + CA0_DDR_PHY_OFFSET)

#define DDI_DDR_PHY_CH0_DQ0_BASE (REG_OFFSET_DDR_PHY_CH(0) + DQ0_DDR_PHY_OFFSET)
#define DDI_DDR_PHY_CH0_DQ1_BASE (REG_OFFSET_DDR_PHY_CH(0) + DQ1_DDR_PHY_OFFSET)

#define DDI_DDR_PHY_CH1_DQ0_BASE (REG_OFFSET_DDR_PHY_CH(1) + DQ0_DDR_PHY_OFFSET)
#define DDI_DDR_PHY_CH1_DQ1_BASE (REG_OFFSET_DDR_PHY_CH(1) + DQ1_DDR_PHY_OFFSET)

#define MASKDQCAOVRDRV      0x38
#define MASKDQCAHIODT       0x3
#define MASKDQCALOODT       0x80000000
#define MASKDQCAPU          0xE00
#define MASKDQDQSCACKVOH    0x18000

#define SHIFTDQCAOVRDRV     3
#define SHIFTDQCALOODT      31
#define SHIFTDQCAHIODT      1
#define SHIFTDQCAPU         9
#define SHIFTDQDQSCACKVOH   15

#define MASKDQSCKOVRDRV     0x1C0
#define MASKDQSCKODT        0x1C
#define MASKDQSCKPU         0x7000
#define SHIFTDQSCKOVRDRV    6
#define SHIFTDQSCKODT       2
#define SHIFTDQSCKPU        12

uint32 ddi_ReadVDD1();
uint32 ddi_ReadVDD2();
uint32 ddi_ReadVDDQ();
uint16 ddi_WriteVDD1(uint32 voltage);
uint16 ddi_WriteVDD2(uint32 voltage);
uint16 ddi_WriteVDDQ(uint32 voltage);
void enableBroadcastDQ();
void enableBroadcastCA();
void disableBroadcast();
void update_soc_drive_strength(void);
boolean  disableDBI();
boolean ddi_ChangePHYSettings(int testline,int prfs,int ovrdrv,int PU,int ODT,int VOH,int ODTE );
boolean  readPHYSettings(uint8 prfs);
boolean ddi_ReadPHYSettings(uint8 testline, uint8 prfs);
#endif /* _BOOT_DDI_TARGET_H */
