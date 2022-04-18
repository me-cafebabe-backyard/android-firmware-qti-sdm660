/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/src/ddrss_freq_switch_rpm.c#7 $
$DateTime: 2017/01/24 08:15:05 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/07/14   ejose        Initial version
================================================================================*/

#include "ddrss_rpm.h"
#include "ddr_phy_technology.h"

//================================================================================================//
// DDR Pre-Clock Frequency Switch
//================================================================================================//
boolean HAL_DDR_Pre_Clock_Switch (DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_clk_khz,
                                  uint32 new_clk_khz)
{

    uint8 new_clk_idx = 0;
    uint8 ch = 0;
    uint8 dq = 0;
    uint8 ca = 0;
    uint32 dq0_ddr_phy_base  = 0;
    uint32 ca0_ddr_phy_base  = 0;
    uint8 ddrcc_target_pll = 0;
    uint32 pll_update_rate = 0x22D; // full rate
    uint8 mccc_sw_mode     = 0;
   
   ddr->misc.new_clk_in_kHz = new_clk_khz;
   ddr->misc.current_clk_in_kHz = curr_clk_khz;
    // Get the clk index in clock plan
    for (new_clk_idx = 0; new_clk_idx < ddr->misc.ddr_num_clock_levels; new_clk_idx++)
    {
        if (new_clk_khz <= ddr->misc.clock_plan[new_clk_idx].clk_freq_in_khz)
            break;
    }
    
   // Set up the MCCC to do the clock switch
   MCCC_Pre_Clock_Switch(ddr, channel);

   BIMC_Pre_Clock_Switch (ddr, channel);//, curr_clk_khz, new_clk_khz, new_clk_idx);
    
   // Turn on cfg clock used for accessing DDR_PHY/DDR_CC CSRs
   ddr_external_set_ddrss_cfg_clk (TRUE);
    
   // Check if the clock mode is DDRCC to configure MCCC SW mode and to set ddrcc target PLL select
   if (ddr->misc.clock_plan[new_clk_idx].clk_mode == 1)
   {
        ddrcc_target_pll =  ! (HWIO_INXF (REG_OFFSET_DDR_CC_CH(0) + DDR_CC_OFFSET,
                             DDR_CC_DDRCC_PLLCTRL_STATUS, ACTIVE_PLL));
        // Check for legacy mode in the previous transaction
        // SDM630-660 has only one valid gasket and DDR CC instances
        if (HWIO_INXF(REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_MCCC_OFFSET, DDR_CC_MCCC_DDRCC_MCCC_TOP_CFG, MCCC_LEGACY_CLK_MODE) == 0x1)
        { 
           mccc_sw_mode     = 1;

           //Overriding pll_select in MCCC to match the ddrcc  MC_CLK_MUX_POL :Select the mc_clk source mux polarity
           HWIO_OUTXF (REG_OFFSET_MCCC_CH(0), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL, ddrcc_target_pll);
           HWIO_OUTXF (REG_OFFSET_MCCC_CH(1), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL, ddrcc_target_pll);
           //Setting MCCC control source clock HW or SW; for GCC-DDRCC it would be set to '1' (SW mode)
           HWIO_OUTXF (REG_OFFSET_MCCC_CH(0), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL_SW_CTL, mccc_sw_mode);
           HWIO_OUTXF (REG_OFFSET_MCCC_CH(1), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL_SW_CTL, mccc_sw_mode);
           //MCCC requires for DDRCC to start on the same PLL when switching to DDRCC for the first time
           //Rest of the cases the pll select would toggle.
           HWIO_OUTXF (REG_OFFSET_DDR_PHY_CH(0) + DDR_CC_MCCC_OFFSET, DDR_CC_MCCC_DDRCC_MCCC_TOP_CFG, MCCC_INIT_PLL_SELECT, ddrcc_target_pll);
        }
   }

   //Preparing the gasket with appropriate clock mode, hw/sw mode, period
   DDR_CC_MCCC_Pre_Clock_Switch (ddr, channel, new_clk_idx);
 
    // Loop through channels
   for (ch = 0; ch < 2; ch++)
   {
       if ((channel >> ch) & 0x1)
       {
           dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
           ca0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
           
           // Enable DLL PHY/MC phase clock
               for (dq = 0; dq < NUM_DQ_PCH; dq++)
               {
                   HWIO_OUTXF(dq0_ddr_phy_base + (dq * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_TOP_CTRL_0_CFG, PH_CGC_MODE, 0 );
               }
               
               for (ca = 0; ca < NUM_CA_PCH; ca++)
               {
                   HWIO_OUTXF(ca0_ddr_phy_base + (ca * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_TOP_CTRL_0_CFG, PH_CGC_MODE, 0 );
               }
               
               // Increase PLL update rate (low to high frequency switch only)
               if ((curr_clk_khz < F_RANGE_3) && (new_clk_khz >= F_RANGE_3))
               {
                   for (dq = 0; dq < NUM_DQ_PCH; dq++)
                   {
                       HWIO_OUTX(dq0_ddr_phy_base + (dq * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCMSTR_CTL_CFG, pll_update_rate );
                   }
                   
                   for (ca = 0; ca < NUM_CA_PCH; ca++)
                   {
                       HWIO_OUTX(ca0_ddr_phy_base + (ca * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCMSTR_CTL_CFG, pll_update_rate );
                   }
               }
           
               // Check if the clock mode is DDRCC to configure DDRCC PLLs
               if (ddr->misc.clock_plan[new_clk_idx].clk_mode == 1) 
               {
                 // Execute target-specific sequence to program the PLLs in the DDRCC.
                 // Target-specific code, as DDRCC PLL programming characteristics and CSRs
                 // are different across targets. Targets 8992 and 8994 are the same, 8996 is different.
                 // Sequence is in target_config.c
                 DDR_CC_Pre_Clock_Switch(ddr, ch, new_clk_idx, ddrcc_target_pll);
               }
       }
   }
   
   return TRUE;
}

//================================================================================================//
// DDR Clock Frequency Switch
//================================================================================================//
boolean HAL_DDR_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_clk_khz,
                                 uint32 new_clk_khz)
{
   boolean return_value;
   
   // Call the MCCC to do the actual clock switch
   return_value = MCCC_Clock_Switch(ddr, channel);
   
   return return_value;
}

//================================================================================================//
// DDR Post-Clock Frequency Switch
//================================================================================================//
boolean HAL_DDR_Post_Clock_Switch (DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_clk_khz,
                                   uint32 new_clk_khz)
{
    uint8 new_clk_idx  = 0;
    uint8 curr_clk_idx = 0;
    uint8 ch = 0;
    uint8 dq = 0;
    uint8 ca = 0;
    uint32 dq0_ddr_phy_base  = 0;
    uint32 ca0_ddr_phy_base  = 0;
    uint32 pll_update_rate = 0x62D;  // half rate
    
    // Get the clk index in clock plan
    for (new_clk_idx = 0; new_clk_idx < ddr->misc.ddr_num_clock_levels; new_clk_idx++)
    {
        if (new_clk_khz <= ddr->misc.clock_plan[new_clk_idx].clk_freq_in_khz)
            break;
    }
    
    for (curr_clk_idx = 0; curr_clk_idx < ddr->misc.ddr_num_clock_levels; curr_clk_idx++)
    {
        if (curr_clk_khz <= ddr->misc.clock_plan[curr_clk_idx].clk_freq_in_khz)
            break;
    }
    
    BIMC_Post_Clock_Switch (ddr, channel);//, curr_clk_khz, new_clk_khz);

    //Setting MCCC control source clock to HW mode
    MCCC_Post_Clock_Switch(ddr, channel);
    
    // Loop through channels
    for (ch = 0; ch < 2; ch++)
    {
        if ((channel >> ch) & 0x1)
        {
            dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            ca0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
            
            // Disable DLL PHY/MC phase clock
                for (dq = 0; dq < NUM_DQ_PCH; dq++)
                {
                    HWIO_OUTXF(dq0_ddr_phy_base + (dq * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_TOP_CTRL_0_CFG, PH_CGC_MODE, 1 );
                }
                
                for (ca = 0; ca < NUM_CA_PCH; ca++)
                {
                    HWIO_OUTXF(ca0_ddr_phy_base + (ca * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_TOP_CTRL_0_CFG, PH_CGC_MODE, 1 );
                }
                
                // Decrease PLL update rate (high to low frequency switch only)
                if ((curr_clk_khz >= F_RANGE_3) && (new_clk_khz < F_RANGE_3))
                {
                    for (dq = 0; dq < NUM_DQ_PCH; dq++)
                    {
                        HWIO_OUTX(dq0_ddr_phy_base + (dq * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCMSTR_CTL_CFG, pll_update_rate );
                    }
                    
                    for (ca = 0; ca < NUM_CA_PCH; ca++)
                    {
                        HWIO_OUTX(ca0_ddr_phy_base + (ca * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCMSTR_CTL_CFG, pll_update_rate );
                    }
                }
        }
    }
    
    // Turn off cfg clock used for accessing DDR_PHY/DDR_CC CSRs
    ddr_external_set_ddrss_cfg_clk (FALSE);
	// Save the new clock frequency as the current clock frequency
    ddr->misc.current_clk_in_kHz = ddr->misc.new_clk_in_kHz;
    
   return TRUE;
}

//================================================================================================//
// DDR Pre-Voltage Switch
//================================================================================================//
boolean HAL_DDR_Pre_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_volt_level,
                                   uint32 new_volt_level)
{
   boolean return_value;
   
   // Call the MCCC to do pre-voltage-switch adjustments
   return_value = MCCC_Pre_Voltage_Switch(ddr, channel);
   
   return return_value;
}

//================================================================================================//
// DDR Pre-Voltage Switch
//================================================================================================//
boolean HAL_DDR_Post_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_volt_level,
                                    uint32 new_volt_level)
{
   boolean return_value;
   
   // Call the MCCC to do post-voltage-switch adjustments
   return_value = MCCC_Post_Voltage_Switch(ddr, channel);
   
   return return_value;
}



