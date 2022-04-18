 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/mccc/mccc10/src/mccc_rpm.c#8 $
$DateTime: 2017/02/02 05:44:06 $
$Author: pwbldsvc $
================================================================================*/

#include "mccc_rpm.h"
#include "ddrss_rpm.h"

 
 

// Power Collapse Entry
boolean MCCC_Enter_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint8  ch              = 0;
   
   // Disable MCCC clocks
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Disable mccc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_MC_CLK_CBCR, CLK_ENABLE, 0);
         
         // Disable mc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_CLK_CBCR, CLK_ENABLE, 0);
      }
   }
   
   return TRUE;
}


// Power Collapse Exit
boolean MCCC_Exit_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

   uint8  ch              = 0;

   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Enable mc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_CLK_CBCR, CLK_ENABLE, 1);
         
         // Enable mccc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_MC_CLK_CBCR, CLK_ENABLE, 1);
      }
   }

  return TRUE;
}
 


boolean MCCC_Pre_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint32 new_period_ps   = 0;
   uint32 new_clk_khz;
   
   new_clk_khz = ddr->misc.new_clk_in_kHz;

   new_period_ps = CONVERT_CYC_TO_PS / new_clk_khz; //unit in ps

   // Program the new period
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_CLK_PERIOD, new_period_ps);

  return TRUE;
}


boolean MCCC_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

#if 0
    uint32 ch = 0;
  
   
   //workaround to fix freq switch issue during SL bringup - "gasket to MCCC handshake"
   for (ch=0; ch<1; ch++)
	{
		HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_ENA, 1);
		HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_SET, 1);
	}
	
#endif
	
   // Program Update bit to 1 to start frequency switch
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE, 1);

   //Poll Update bit. 0 when freq switch complete
   while (HWIO_INX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE));
  // "dummy MR Workaround" for single channel frequency switch
   // writing to a read only MR register so that no other config is disturbed    
   BIMC_MR_Write (CH_1HOT(0),CS_1HOT(0),JEDEC_MR_7, 0x0/*MR data*/);
   
   
#if 0    
   //workaround to fix freq switch issue during SL bringup - "gasket to MCCC handshake"
   for (ch=0; ch<1; ch++)
	{
		//BIMC_MR_Read (CH_1HOT(ch),CS_1HOT(cs),JEDEC_MR_18);
		while((HWIO_INXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SAA_STATUS, ACK1) != 0) && 
		      (HWIO_INXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SAA_STATUS, ACK0) != 0))  {;}
		HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_ENA, 0);
		HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_SET, 0);
	}
	// end workaround - "gasket to MCCC handshake"

#endif
  return TRUE;
}


boolean MCCC_Post_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  //Setting MCCC control source clock to HW ; for GCC-DDRCC it would be have been set to '1' (SW mode)
  //After the switch is complete it can be set to HW mode irrespective of type of switch
   HWIO_OUTXF (REG_OFFSET_MCCC_CH(0), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL_SW_CTL, 0);
   HWIO_OUTXF (REG_OFFSET_MCCC_CH(1), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL_SW_CTL, 0);
  return TRUE;
}



// May need pre and post voltage switch to remove stages of supper buffer. This to be experimented with post SOD. Code to be ready for P4 (2/20)
boolean MCCC_Pre_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Empty for now; use for any needed optimizations
  return TRUE;
}


boolean MCCC_Post_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  // Empty for now; use for any needed optimizations
  return TRUE;
}


