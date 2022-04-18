 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/ddr_cc_mccc/ddr_cc_mccc10/header/ddr_cc_mccc.h#1 $
$DateTime: 2016/12/19 10:54:29 $
$Author: pwbldsvc $
================================================================================*/

#ifndef __DDR_CC_MCCC_H__
#define __DDR_CC_MCCC_H__

#include "HAL_SNS_DDR.h"
#include "ddr_cc_mccc_seq_hwiobase.h"
#include "ddr_cc_mccc_seq_hwioreg.h"
#include "target_config_rpm.h"
#include "ddrss.h"
#include "ddr_cc_mccc_config.h"
#include "ddr_cc_mccc_rpm.h"


// DDR_CC_MCCC_Config. One time settings through DDR_CC_MCCC calculator
void DDR_CC_MCCC_Config(DDR_STRUCT *ddr);
 
#endif // #ifdef _MCCC_H_
