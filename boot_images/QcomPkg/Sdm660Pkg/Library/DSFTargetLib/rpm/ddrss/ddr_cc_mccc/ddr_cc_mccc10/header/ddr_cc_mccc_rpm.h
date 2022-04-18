 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/ddr_cc_mccc/ddr_cc_mccc10/header/ddr_cc_mccc_rpm.h#2 $
$DateTime: 2016/12/30 05:44:11 $
$Author: pwbldsvc $
================================================================================*/

#ifndef __DDR_CC_MCCC_RPM_H__
#define __DDR_CC_MCCC_RPM_H__

#include "HAL_SNS_DDR.h"
#include "ddr_cc_mccc_seq_hwiobase.h"
#include "ddr_cc_mccc_seq_hwioreg.h"
#include "target_config_rpm.h"
#include "ddrss_rpm.h"

#define DDR_CC_MCCC_CH_OFFSET            0
// Clock Switch Functions
boolean DDR_CC_MCCC_Pre_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint8 new_clk_idx);
boolean DDR_CC_MCCC_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean DDR_CC_MCCC_Post_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);

// Voltage Switch Functions
// May need pre and post voltage switch to remove stages of supper buffer. This to be experimented with post SOD. Code to be ready for P4 (2/20)
boolean DDR_CC_MCCC_Pre_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean DDR_CC_MCCC_Post_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel);

#endif // #ifdef _DDR_CC_MCCC_RPM_H_
