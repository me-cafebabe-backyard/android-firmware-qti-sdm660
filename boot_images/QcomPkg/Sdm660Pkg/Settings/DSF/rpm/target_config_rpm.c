/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/DSF/rpm/target_config_rpm.c#5 $
$DateTime: 2016/12/30 05:44:11 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/11/14   arindamm     Initial creation for 8994 V1-only code.
================================================================================*/

#include "ddrss_rpm.h"
#include "target_config_rpm.h"


uint8 dll_analog_freq_range[]= {
   15 ,  /*  <300MHz  */
   7 ,  /*  <400MHz  */   
   3 ,  /*  <500MHz  */
   1 ,  /*  <700MHz  */
   0    /*  < 1.89GHz  */
};

uint32 dll_analog_freq_range_table[]    = {300000, 400000, 500000, 700000, 1890000};
uint8  dll_analog_freq_range_table_size = sizeof(dll_analog_freq_range_table)/sizeof(uint8);



/* =============================================================================
**  Function : DDR_CC_Pre_Clock_Switch
** =============================================================================
*/
/**
*   @brief
*   DDRCC PLL programming in the pre-clock-switch routine. Platform-specific code,
*   as DDRCC PLL programming characteristics and CSRs are different across targets.
*   Targets 8992 and 8994 are the same, 8996 is different.
*
*   @param[in]  ddr              Pointer to ddr conifiguration struct
*   @param[in]  new_clk_index    Index into the clock plan structure corresponding to the requested frequency.
*   @param[in]  ddrcc_target_pll Parameter that selects which PLL to program.
*
*   @retval  None.
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/

//================================================================================================//
// Based on Freq_Switch_Params band, get an index for selecting in Freq_Switch_Params table
//================================================================================================//
uint8 DDRCC_dll_analog_freq_range_table_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz)
{
   uint8 clk_idx = 0;

   for (clk_idx = 0; (clk_idx < dll_analog_freq_range_table_size); clk_idx++)
   {
      if (clk_freq_khz <= dll_analog_freq_range_table[clk_idx])
         break;
   }

   return clk_idx;
}





void DDR_CC_Pre_Clock_Switch(DDR_STRUCT *ddr, uint8 ch, uint8 new_clk_idx, uint8 ddrcc_target_pll)
{
    uint8  dll_params_idx;
    uint32 new_clk_khz;


    
    new_clk_khz = ddr->misc.clock_plan[new_clk_idx].clk_freq_in_khz;
    dll_params_idx  = DDRCC_dll_analog_freq_range_table_Index (ddr, new_clk_khz);


// We should revisit below PLL registers if freq plan changes. 
//DDR Freq (MHz)  Freq/19.2  Freq/9.6
//  412.8            21.5    43
//  547.2            28.5    57
//  681.6            35.5    71
//  768              40      80
//  1017.6          53      106
//  1296            67.5    135
//  1353.6          70.5    141
//  1555.2          81      162
//  1804.8          94      188
//PLL registers to be checked if freq plan changes
//DIV_FRAC_START1
//DIV_FRAC_START2
//PLLLOCK_CMP3
//KVCO_COUNT1
//KVCO_COUNT2



  
    if (ddrcc_target_pll) {

        // SerDes PLL  and DLL sequence for next PLL/DLL programming
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_SYSCLK_EN_RESET,0x1);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_SYSCLK_EN_RESET,0x0);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_DEC_START,
                  ddr->misc.clock_plan[new_clk_idx].pll_dec_start);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_DIV_FRAC_START3,
                   ddr->misc.clock_plan[new_clk_idx].pll_div_frac_start3);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_PLLLOCK_CMP1,
                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp1);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_PLLLOCK_CMP2,
                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp2);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_VCO_COUNT1,
                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count1);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_VCO_COUNT2,
                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count2);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_PLL_LPF2_POSTDIV,
                   ddr->misc.clock_plan[new_clk_idx].pll_pll_lpf2_postdiv);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_KVCO_CODE,
                   ddr->misc.clock_plan[new_clk_idx].pll_kvco_code);                    
        HWIO_OUTXF (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_PHYDLL1_ANALOG_CFG0, FREQRANGE,
                    dll_analog_freq_range[dll_params_idx]);    

        
    } else {

        // SerDes PLL  and DLL sequence for next PLL/DLL programming
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_SYSCLK_EN_RESET,0x1);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_SYSCLK_EN_RESET,0x0);  
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_DEC_START,
                  ddr->misc.clock_plan[new_clk_idx].pll_dec_start);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_DIV_FRAC_START3,
                   ddr->misc.clock_plan[new_clk_idx].pll_div_frac_start3);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_PLLLOCK_CMP1,
                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp1);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_PLLLOCK_CMP2,
                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp2);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_VCO_COUNT1,
                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count1);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_VCO_COUNT2,
                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count2);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_PLL_LPF2_POSTDIV,
                   ddr->misc.clock_plan[new_clk_idx].pll_pll_lpf2_postdiv);
        HWIO_OUTX (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_KVCO_CODE,
                   ddr->misc.clock_plan[new_clk_idx].pll_kvco_code);
        HWIO_OUTXF (REG_OFFSET_DDR_CC_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_PHYDLL0_ANALOG_CFG0, FREQRANGE,
                   dll_analog_freq_range[dll_params_idx]);           

    }
}        

//void DDR_CC_Pre_Clock_Switch(DDR_STRUCT *ddr, uint8 ch, uint8 new_clk_idx, uint8 ddrcc_target_pll)
//{
//    uint8  dll_params_idx;
//  uint32 new_clk_khz;
//  
//  new_clk_khz = ddr->misc.clock_plan[new_clk_idx].clk_freq_in_khz;
//  dll_params_idx  = DDRCC_dll_analog_freq_range_table_Index (ddr, new_clk_khz);
//  
//    if (ddrcc_target_pll) {
//        //Step 1
//        //Step 3
//  
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_SYSCLK_EN_RESET,0x1);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_SYSCLK_EN_RESET,0x0);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_DEC_START,
//                  ddr->misc.clock_plan[new_clk_idx].pll_dec_start);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_DIV_FRAC_START3,
//                   ddr->misc.clock_plan[new_clk_idx].pll_div_frac_start3);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_PLLLOCK_CMP1,
//                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp1);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_PLLLOCK_CMP2,
//                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp2);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_VCO_COUNT1,
//                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count1);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_VCO_COUNT2,
//                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count2);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_PLL_LPF2_POSTDIV,
//                   ddr->misc.clock_plan[new_clk_idx].pll_pll_lpf2_postdiv);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_KVCO_CODE,
//                   ddr->misc.clock_plan[new_clk_idx].pll_kvco_code);                    
//        // HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_PHYDLL1_ANALOG_CFG0, FREQRANGE,
//                   // dll_analog_freq_range[new_clk_idx]);           
//        HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_PHYDLL1_ANALOG_CFG0, FREQRANGE,
//                    dll_analog_freq_range[dll_params_idx]);             
//           //step 4
//        //step 5
//      // while(HWIO_INXF (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL1_RESET_SM_READY_STATUS,CORE_READY) == 0);
//        
//    } else {
//        //Step 1
//        //step 3
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_SYSCLK_EN_RESET,0x1);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_SYSCLK_EN_RESET,0x0);  
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_DEC_START,
//                  ddr->misc.clock_plan[new_clk_idx].pll_dec_start);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_DIV_FRAC_START3,
//                   ddr->misc.clock_plan[new_clk_idx].pll_div_frac_start3);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_PLLLOCK_CMP1,
//                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp1);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_PLLLOCK_CMP2,
//                   ddr->misc.clock_plan[new_clk_idx].pll_plllock_cmp2);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_VCO_COUNT1,
//                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count1);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_VCO_COUNT2,
//                   ddr->misc.clock_plan[new_clk_idx].pll_vco_count2);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_PLL_LPF2_POSTDIV,
//                   ddr->misc.clock_plan[new_clk_idx].pll_pll_lpf2_postdiv);
//        HWIO_OUTX (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_KVCO_CODE,
//                   ddr->misc.clock_plan[new_clk_idx].pll_kvco_code);
//        // HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_PHYDLL0_ANALOG_CFG0, FREQRANGE,
//                   // dll_analog_freq_range[new_clk_idx]);
//        HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_PHYDLL0_ANALOG_CFG0, FREQRANGE,
//                   dll_analog_freq_range[dll_params_idx]);           
//        //step 4 
//        //step 5
//      // while(HWIO_INXF (REG_OFFSET_DDR_PHY_CH(ch) + DDR_CC_OFFSET, DDR_CC_DDRCC_SDPLL0_RESET_SM_READY_STATUS,CORE_READY) == 0);                
//    }
//}
