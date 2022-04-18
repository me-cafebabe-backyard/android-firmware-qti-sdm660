 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/mccc/mccc10/header/mccc.h#4 $
$DateTime: 2016/12/19 10:54:29 $
$Author: pwbldsvc $
================================================================================*/

#ifndef __MCCC_H__
#define __MCCC_H__

#include "HAL_SNS_DDR.h"
#include "mccc_seq_hwiobase.h"
#include "mccc_seq_hwioreg.h"
#include "target_config_rpm.h"
#include "ddrss.h"
#include "mccc_config.h"
#include "mccc_rpm.h"


// MCCC_Config. One time settings through MCCC calculator
void MCCC_Config(DDR_STRUCT *ddr);
// MCCC clk and MC clk CBCR enable for successful CSR writes
void MCCC_Clk_CBCR_Enable(DDR_STRUCT *ddr, DDR_CHANNEL channel);
 
// Cold Boot Initialization
boolean MCCC_Init(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean MCCC_Init_Cleanup(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean MCCC_Init_GHS(DDR_STRUCT *ddr, DDR_CHANNEL channel);

#endif // #ifdef _MCCC_H_
