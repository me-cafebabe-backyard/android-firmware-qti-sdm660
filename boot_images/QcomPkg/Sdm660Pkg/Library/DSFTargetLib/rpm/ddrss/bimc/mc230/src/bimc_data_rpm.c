/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/src/bimc_data_rpm.c#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_rpm.h"

extern uint8 RL_WL_freq_range_table_size;
extern uint8 bimc_freq_switch_params_table_size;

//================================================================================================================================//
// Updates the CLKEN_WR_EXTEND, CLKEN_RD_EXTEND, TRAFFIC_WR_EXTEND, TRAFFIC_RD_EXTEND valus in DPE config_8 based on frequency
//================================================================================================================================//
uint32 dpe_config_8[]= {
   0x00010001 ,  /*  100MHz     */
   0x00010001 ,  /*  150MHz     */
   0x00010001 ,  /*  200MHz     */
   0x00020002 ,  /*  300MHz     */
   0x03070307 ,  /*  412.8MHz   */
   0x03070307 ,  /*  547.2MHz   */
   0x03070307 ,  /*  681.6MHz   */
   0x03070307 ,  /*  768.0MHz   */
   0x03070307 ,  /*  1017.6MHz  */
   0x03070307 ,  /*  1353.6MHz  */
   0x03070307 ,  /*  1555.2MHz  */
   0x03070307    /*  1804.8MHz  */
};


//================================================================================================================================//
// Updates DPE_TIMER_3 and DPE_DRAM_TIMING_13 for DDRCC frequency. 
// This is a LVDS Clock Gating feature and does not change GCC mode value
//================================================================================================================================//
#if PHY_LVDS_GATING_DELAY
uint32 dpe_timer_3[]= {
   0x00010460 ,  /*  GCC mode    */
   0x00010460    /*  DDRCC mode, stage1: 0x000104C0, stage 2: 0x00010460   */ 
};

uint32 dpe_timing_13[]= {
   0x405E6000 ,  /*  GCC mode    */
   0x405E6000    /*  DDRCC mode, stage1: 0x405EC000, stage 2: 0x405E6000  */ 
};
#endif


//================================================================================================//
// Based on device RL/WL/ODTLon frequency band, get an index for selecting in RL/WL/ODTLon table
//================================================================================================//
uint8 BIMC_RL_WL_Freq_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz)
{
   uint8 clk_idx;

    for (clk_idx = 0; (clk_idx < RL_WL_freq_range_table_size /*NUM_ECDT_DRAM_LATENCY_STRUCTS*/); clk_idx++)
    {
        if (clk_freq_khz <= ddr->extended_cdt_runtime.dram_latency[clk_idx].rl_wl_freq_in_kHz)
            break;
    }
     
   return clk_idx;
}


//================================================================================================//
// Based on Freq_Switch_Params band, get an index for selecting in Freq_Switch_Params table
//================================================================================================//
uint8 BIMC_Freq_Switch_Params_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz)
{
   uint8 clk_idx = 0;

    for (clk_idx = 0; clk_idx < bimc_freq_switch_params_table_size; clk_idx++)
    {
        if (clk_freq_khz <= ddr->extended_cdt_runtime.bimc_freq_switch[clk_idx].freq_switch_range_in_kHz)
            break;
    }
      
   return clk_idx;
}




