 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/mccc/mccc10/header/mccc_rpm.h#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================*/

#ifndef __MCCC_RPM_H__
#define __MCCC_RPM_H__

#include "HAL_SNS_DDR.h"
#include "mccc_seq_hwiobase.h"
#include "mccc_seq_hwioreg.h"
#include "target_config_rpm.h"
#include "ddrss_rpm.h"


#define REG_OFFSET_MCCC                 (MCCC_BASE + SEQ_MCCC_MCCC_MCCC_REGS_OFFSET)

#define REG_OFFSET_MCCC_CH(uint8)       ((uint8 == 0) ? \
                                        (MCCC_BASE + SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET) : \
                                        (MCCC_BASE + SEQ_MCCC_MCCC_CH1_MCCC_CH_REGS_OFFSET))
										
#define MCCC_CH_OFFSET                  (SEQ_MCCC_MCCC_CH1_MCCC_CH_REGS_OFFSET-SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET)



#define MCCC_INT_FREQ_SWITCH_STATE_EXIT_COND_CFG  0x30008000
#define MCCC_INIT_FREQ_SWITCH_STATE_EXIT_COND_CFG 0x3000801C


// Power Collapse Entry/Exit Functions
boolean MCCC_Enter_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean MCCC_Exit_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel);
 
// Clock Switch Functions
boolean MCCC_Pre_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean MCCC_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean MCCC_Post_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);

// Voltage Switch Functions
// May need pre and post voltage switch to remove stages of supper buffer. This to be experimented with post SOD. Code to be ready for P4 (2/20)
boolean MCCC_Pre_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean MCCC_Post_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);

#endif // #ifdef _MCCC_RPM_H_
