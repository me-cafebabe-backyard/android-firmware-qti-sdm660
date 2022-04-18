 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/ddr_cc_mccc/ddr_cc_mccc10/src/ddr_cc_mccc.c#2 $
$DateTime: 2017/01/08 08:21:59 $
$Author: pwbldsvc $
================================================================================*/

#include "ddr_cc_mccc.h"
#include "ddr_cc_mccc_config.h"
#include "ddrss.h"


// DDR_CC_MCCC_Config --- one time settings through new DDR_CC_MCCC calculator, Need to have a parser for this new calculator
void DDR_CC_MCCC_Config(DDR_STRUCT *ddr)
{
   ddr_cc_mccc_set_config(ddr, DDR_PHY_SS_BASE, ddr_cc_mccc_regs_config_base, ddr_cc_mccc_regs_config_ch_delta, ddr_cc_mccc_regs_config_delta);
}

