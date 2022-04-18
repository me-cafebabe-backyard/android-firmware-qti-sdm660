 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/ddr_cc_mccc/ddr_cc_mccc10/src/ddr_cc_mccc_rpm.c#2 $
$DateTime: 2016/12/30 05:44:11 $
$Author: pwbldsvc $
================================================================================*/

#include "ddr_cc_mccc_rpm.h"
#include "ddrss_rpm.h"

boolean DDR_CC_MCCC_Pre_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint8 new_clk_idx)
{
   uint32 new_period_ps   = 0;
   uint32 new_clk_khz;
   
   new_clk_khz = ddr->misc.new_clk_in_kHz;
   new_period_ps = CONVERT_CYC_TO_PS / new_clk_khz; //unit in ps

   //Replacing the gcc_legacy_clk_mode from QFI 1.0
   HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_MCCC_OFFSET, DDR_CC_MCCC_DDRCC_MCCC_TOP_CFG, MCCC_LEGACY_CLK_MODE,
                  !(ddr->misc.clock_plan[new_clk_idx].clk_mode));
   //FPM_PERIOD bus to DDRCC and DDRPHY in QFI1.0 to QFI1.1 gastket 0x1388: 200MHz (default)
   HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_MCCC_OFFSET, DDR_CC_MCCC_DDRCC_MCCC_TOP_CFG2, MCCC_FPM_PERIOD, new_period_ps);
   //FREQ_RATIO bus to DDRCC and DDRPHY in QFI1.0 to QFI1.1 gasket 00: ratio 1:1 (default) 01: ratio 1:2 10;11: not supported
   HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_MCCC_OFFSET, DDR_CC_MCCC_DDRCC_MCCC_TOP_CFG3, MCCC_FREQ_RATIO, 
                   ddr->misc.clock_plan[new_clk_idx].clk_ratio);

  return TRUE;
}


boolean DDR_CC_MCCC_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Empty for now; use for any needed optimizations
  return TRUE;
}


boolean DDR_CC_MCCC_Post_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Empty for now; use for any needed optimizations
  return TRUE;
}



// May need pre and post voltage switch to remove stages of supper buffer. This to be experimented with post SOD. Code to be ready for P4 (2/20)
boolean DDR_CC_MCCC_Pre_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Empty for now; use for any needed optimizations
  return TRUE;
}


boolean DDR_CC_MCCC_Post_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Empty for now; use for any needed optimizations
  return TRUE;
}


