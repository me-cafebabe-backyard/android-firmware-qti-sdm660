 /****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/mccc/mccc10/src/mccc.c#4 $
$DateTime: 2016/12/19 10:54:29 $
$Author: pwbldsvc $
================================================================================*/

#include "mccc.h"
#include "mccc_config.h"
#include "ddrss.h"


// MCCC_Config --- one time settings through new MCCC calculator, Need to have a parser for this new calculator
void MCCC_Config(DDR_STRUCT *ddr)
{
   mccc_set_config(ddr, MCCC_BASE, mccc_regs_config_base,    mccc_regs_config_ch_delta,    mccc_regs_config_delta);
   mccc_set_config(ddr, MCCC_BASE, mccc_ch_regs_config_base, mccc_ch_regs_config_ch_delta, mccc_ch_regs_config_delta);
}

// MCCC clk and MC clk CBCR enable for successful CSR writes
void MCCC_Clk_CBCR_Enable(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint8 ch = 0;

   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Enable mccc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_CLK_CBCR, CLK_ENABLE, 1);
         // Enable mc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_MC_CLK_CBCR, CLK_ENABLE, 1);
      }
   }
}
 

 
// Cold Boot Initialization
boolean MCCC_Init(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

   uint32 new_period_ps   = 0;
   uint8  ch              = 0;
   uint32 init_clk_khz, ddrcc_gcc_boundary_freq;
   uint32 ddrcc_clk_index;

   // One-time settings
   MCCC_Config(ddr);

   init_clk_khz = ddr->misc.current_clk_in_kHz;
   new_period_ps = CONVERT_CYC_TO_PS / init_clk_khz; //unit in ps
   
   // Calculate and program the Band 1 threshold in psec (at the GCC/DDRCC freq threshold).
   // Walk through the table to figure out where the boundary between GCC and DDRCC clock modes
   //    (clk_mode 0 and clk_mode 1) is.
   for (ddrcc_clk_index = 0; ddrcc_clk_index < MAX_NUM_CLOCK_PLAN; ddrcc_clk_index++)
   { 
      if (ddr->misc.clock_plan[ddrcc_clk_index].clk_mode == 1)
      {
         break;
      }
   }
   
   if (ddrcc_clk_index == MAX_NUM_CLOCK_PLAN)
   {
      // If we went past the end of the table (ie, everything is GCC, then set the boundary freq just above 
      //    the last freq.
      ddrcc_gcc_boundary_freq = ddr->misc.clock_plan[MAX_NUM_CLOCK_PLAN-1].clk_freq_in_khz + 50;
   }
   else
   {
     // The GCC/DDRCC boundary point is within the table.  It is just halfway between the first DDRCC freq 
     //    and the last GCC freq
     ddrcc_gcc_boundary_freq = (ddr->misc.clock_plan[ddrcc_clk_index].clk_freq_in_khz 
                                          + ddr->misc.clock_plan[ddrcc_clk_index-1].clk_freq_in_khz ) / 2;
   }

  // Program the GCC/DDRCC boundary freq in psec.
  // Overwrites the definition from mccc_config.c.
   HWIO_OUTXF (REG_OFFSET_MCCC, MCCC_REGS_BAND1_UPPER_FREQ_THRESHOLD, THRESHOLD_PERIOD, 
                                CONVERT_CYC_TO_PS / ddrcc_gcc_boundary_freq);

   // Program the init period
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_CLK_PERIOD, new_period_ps);

   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Enable mccc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_CLK_CBCR, CLK_ENABLE, 1);

         // Enable mc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_MC_CLK_CBCR, CLK_ENABLE, 1);

      }
   }

  return TRUE;
}


// Cold Boot Initialization workaround to latch clock mode into MC
// Executed Prior to MCCC_Init & MCCC_Config
boolean MCCC_Init_GHS(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

   uint32 new_period_ps   = 0;
   uint8  ch              = 0;
   uint32 init_clk_khz;

   init_clk_khz = ddr->misc.current_clk_in_kHz;
   new_period_ps = CONVERT_CYC_TO_PS / init_clk_khz; //unit in ps

   // Program the init period
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_CLK_PERIOD, new_period_ps);

   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Enable mccc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_CLK_CBCR, CLK_ENABLE, 1);

         // Enable mc_clk
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_MC_CLK_CBCR, CLK_ENABLE, 1);

         // Mask External Freq Switch Acks
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_ACK0_MASK, 1);
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_ACK1_MASK, 1);

         // SW Override Update
         HWIO_OUTX (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE_UPDATE, 1);

         // Clear SW Override Update
         HWIO_OUTX (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE_UPDATE, 0);

      }
   }

   // Common CSR config
   // Clock Mode Config
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_BAND0_UPPER_FREQ_THRESHOLD, 0x0000CB70);
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_BAND1_UPPER_FREQ_THRESHOLD, 0x00000724);
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_BAND1_CFG0, 0x00000100);

   // Set final state to 1
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_FSM_CFG, 0x00000001);


   // Frequency Switch #1 Start
   // Program Update bit to 1 to start internal frequency switch
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE, 1);

   //Poll Update bit. 0 when freq switch complete
   while (HWIO_INX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE));
   // Frequency Switch #1 End


   // Frequency Switch #2 Start
   // Program Update bit to 1 to start internal frequency switch
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE, 1);

   //Poll Update bit. 0 when freq switch complete
   while (HWIO_INX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE));
   // Frequency Switch #2 End

  return TRUE;
}



// Cold Boot Initialization Cleanup
boolean MCCC_Init_Cleanup(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

   uint8  ch              = 0;

   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Mask External Freq Switch Req & Acks
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_REQ_MASK, 1);
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_ACK0_MASK, 1);
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_ACK1_MASK, 1);

         // SW Override Update
         HWIO_OUTX (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE_UPDATE, 1);

         // Clear SW Override Update
         HWIO_OUTX (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE_UPDATE, 0);

         // Hold mc_clk mux polarity at 0 via SW CTL. Needed for 1st internal switch.
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL_SW_CTL, 1);
      }
   }

   // Common CSR config
   // Enable Task Mask Cfg0. Mask all tasks but SSP. Force SSP update.
   HWIO_OUTXF (REG_OFFSET_MCCC, MCCC_REGS_TASK_MASK_CFG0, ENABLE, 1);

   // Remove all Cross-Channel states except final state 15
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_STATE_EXIT_COND, MCCC_INT_FREQ_SWITCH_STATE_EXIT_COND_CFG);


   // Frequency Switch Start
   // Program Update bit to 1 to start internal frequency switch
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE, 1);

   //Poll Update bit. 0 when freq switch complete
   while (HWIO_INX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_UPDATE));
   // Frequency Switch End


   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // Unmask External Freq Switch Req & Acks
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_REQ_MASK, 0);
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_ACK0_MASK, 0);
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE1, FREQ_SWITCH_STATE_ACK1_MASK, 0);

         // SW Override Update
         HWIO_OUTX (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE_UPDATE, 1);

         // Clear SW Override Update
         HWIO_OUTX (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_OVERRIDE_UPDATE, 0);

         // Remove mc_clk mux polarity SW CTL
         HWIO_OUTXF (REG_OFFSET_MCCC_CH(ch), MCCC_CH_REGS_SW_CTL0, MC_CLK_MUX_POL_SW_CTL, 0);
      }
   }

   // Common CSR config
   // Disable Task Mask Cfg0.
   HWIO_OUTXF (REG_OFFSET_MCCC, MCCC_REGS_TASK_MASK_CFG0, ENABLE, 0);

   // Reconfigure Cross-Channel states
   HWIO_OUTX (REG_OFFSET_MCCC, MCCC_REGS_FREQ_SWITCH_STATE_EXIT_COND, MCCC_INIT_FREQ_SWITCH_STATE_EXIT_COND_CFG);

  return TRUE;
}

