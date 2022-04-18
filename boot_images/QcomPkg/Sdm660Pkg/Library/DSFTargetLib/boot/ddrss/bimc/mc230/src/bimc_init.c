/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/bimc/mc230/src/bimc_init.c#11 $
$DateTime: 2018/09/27 20:55:21 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc.h"
#include "ddrss.h"

//================================================================================================//
// BIMC One-Time Settings
//================================================================================================//
void BIMC_Config(DDR_STRUCT *ddr)
{
   bimc_set_config(ddr, BIMC_BASE, bimc_global0_config_base, bimc_global0_config_ch_delta, bimc_global0_config_delta);
   bimc_set_config(ddr, BIMC_BASE, bimc_scmo_config_base,    bimc_scmo_config_ch_delta,    bimc_scmo_config_delta);
   bimc_set_config(ddr, BIMC_BASE, bimc_dpe_config_base,     bimc_dpe_config_ch_delta,     bimc_dpe_config_delta);
   bimc_set_config(ddr, BIMC_BASE, bimc_shke_config_base,    bimc_shke_config_ch_delta,    bimc_shke_config_delta);
   bimc_set_config(ddr, BIMC_BASE, bimc_dtts_config_base,    bimc_dtts_config_ch_delta,    bimc_dtts_config_delta);
}


boolean BIMC_Init_Pre_MCCC_Init_GHS(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{

   uint8  ch = 0;

   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {
         // The following section of code is split into 2 segments.
         // First section of code will program mccc switch state to accept the 
         // data rate, clock rate etc. from MCCC.  The clock enables are all 
         // turned off going to external world such as DDRCC and CA/DQ PHYs
         // This will ensure that mccc rate changes are clean WRT external world  


         // Program MCCC Switch states to make sure rate information is captured in bimc 
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_MCCC_SWITCH_STATE, ch, FREQ_RATIO_REG_STATE, 1);
  
         // Turn off clocks to DDRCC
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DDRCC, ch, CLKEN_DDRCC_ENA, 1);
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DDRCC, ch, CLKEN_DDRCC_SET, 0);
    
         // Turn off clocks to CA PHY 
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_ENA, 1);
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_SET, 0);
    
         // Turn off clocks to DQ PHY
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DQPHY, ch, CLKEN_DQPHY_ENA, 1);
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DQPHY, ch, CLKEN_DQPHY_SET, 0);
      }
   }
   
   return TRUE;
}


boolean BIMC_Init_Post_MCCC_Init_GHS(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint8  ch = 0;
   
   // Channel CSR config
   for (ch = 0; ch < NUM_CH; ch++)
   {
      if (channel>>ch & 0x1)
      {

         // Now that the data and clock rates are captured, 
         // enable all clocks to be controlled by HW design.
         // basically removing hijacking that happened before. 
  
         // Disable clock off to DDRCC 
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DDRCC, ch, CLKEN_DDRCC_ENA, 0);
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DDRCC, ch, CLKEN_DDRCC_SET, 0);

         // Disable clock off to CA PHY
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_ENA, 0);
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_CAPHY, ch, CLKEN_CAPHY_SET, 0);

         // Disable clock off to DQ PHY
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DQPHY, ch, CLKEN_DQPHY_ENA, 0);
     HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_SW_CLKEN_DQPHY, ch, CLKEN_DQPHY_SET, 0);
      }
   }
   
   return TRUE;
}

//================================================================================================//
// Set up init clk period.
// Update AC timing parameters from CDT, recalculate and load DPE timing actual registers
//================================================================================================//
void BIMC_Pre_Init_Setup (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint32 tREFI_in_XO     = 0;
   uint32 period          = 0;
   uint8  ch              = 0;
   uint32 reg_offset_dpe  = 0;
   uint32 reg_offset_shke = 0;
   uint8  new_RL_WL_idx   = 0;
   uint32 tXP_adjusted    = 0;
   uint32 clk_freq_khz;

   clk_freq_khz = ddr->misc.current_clk_in_kHz;
   period = CONVERT_CYC_TO_PS / clk_freq_khz; //unit in ps

   new_RL_WL_idx  = BIMC_RL_WL_Freq_Index (ddr, clk_freq_khz);

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_dpe  = REG_OFFSET_DPE(ch);
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         // Program the new period
         HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_CLK_PERIOD, ch, PERIOD, period);

         // Common AC Timing parameters between LP3 and LP4
         HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_0, TRASMIN, ddr->cdt_params.lpddr.tRAS_Min);
         HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_1, TRCD, ddr->cdt_params.lpddr.tRCD);
         HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_2, TRRD, ddr->cdt_params.lpddr.tRRD);
         HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_4, TRTP, ddr->cdt_params.lpddr.tRTP);
         HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_5, TRPAB, TRPPB,
                      ddr->cdt_params.lpddr.tRP_AB, ddr->cdt_params.lpddr.tRP_PB);
         HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_6, TFAW, TCKE,
                      ddr->cdt_params.lpddr.tFAW, ddr->cdt_params.lpddr.tCKE);
         HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_9, MIN_SR_DURATION, ddr->cdt_params.lpddr.tCKESR);

         // Add CKE rise slew rate (1.2ns) into tXP.
         tXP_adjusted = ddr->cdt_params.lpddr.tXP + 12;
         HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_11, TXPNR_ACT_PWR_DN, TXPR_ACT_PWR_DN,
                      tXP_adjusted, tXP_adjusted);
         HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_12, TXPNR_PCHG_PWR_DN, TXPR_PCHG_PWR_DN,
                      tXP_adjusted, tXP_adjusted);

         HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_16, RD_LATENCY, WR_LATENCY,
                      ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_Off_x16, ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].WL);
           
         HWIO_OUTXF  (reg_offset_dpe, DPE_TIMER_2, TMRR, ddr->cdt_params.lpddr.tMRR);

         if (15 < ddr->cdt_params.lpddr.tMRW) {
            HWIO_OUTXF (reg_offset_dpe, DPE_TIMER_2, TMRW, ddr->cdt_params.lpddr.tMRW);
         }
         else
         {
            HWIO_OUTXF (reg_offset_dpe, DPE_TIMER_2, TMRW, 15);
         }

         //load page_close_timer from eCDT
         HWIO_OUTXF (reg_offset_dpe, DPE_OPT_CTRL_1, PG_OPEN_TIMER, ddr->extended_cdt_runtime.page_close_timer);

         // cdt_params has resolution of 100ps, multiplied by 100 to convert to 1ps
         tREFI_in_XO = (ddr->cdt_params.lpddr.tREFI * 100) / XO_PERIOD_IN_PS - 1;

         HWIO_OUTXF (reg_offset_shke, SHKE_AUTO_REFRESH_CNTL,   TREFI, tREFI_in_XO);
         HWIO_OUTXF (reg_offset_shke, SHKE_AUTO_REFRESH_CNTL_1, TREFI, tREFI_in_XO);

         // AC Timing parameters
         BIMC_Program_Lpddr_AC_Parameters( ddr, (DDR_CHANNEL)ch);

         // Kick off timing parameter calculation and wait until done
         HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_4, RECALC_PS_PARAMS, 0x1);
         while (HWIO_INXF (reg_offset_dpe, DPE_MEMC_STATUS_1, CYC_CALC_VALID));

         // Load all the calculated settings into DPE actual registers
         HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);
      }
   }
}


//================================================================================================//
// Device Initialization
// Select LPDDR3 or LPDDR4 initialization routines for enabling CK and CKE.
// Does ZQ calibration and RL/WL programming
//================================================================================================//
void BIMC_Memory_Device_Init (DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select,
                              uint8 in_self_refresh)
{
   uint8 ch = 0x0;
   uint8 cs = 0;
   DDR_CHIPSELECT  cs_1hot = DDR_CS0;
   uint32 reg_offset_shke = 0;
   uint8  RL_WL_idx  = 0;
   uint32 clk_freq_khz;

   clk_freq_khz = ddr->misc.current_clk_in_kHz;
   if (in_self_refresh == 0)
   {
       BIMC_Memory_Device_Init_Lpddr (ddr, ecdt, channel, chip_select);
       BIMC_ZQ_Calibration (ddr, channel, chip_select);

       // RL and WL MR write
       RL_WL_idx  = BIMC_RL_WL_Freq_Index (ddr, clk_freq_khz);
       BIMC_MR_Write (channel, chip_select, JEDEC_MR_2, ddr->extended_cdt_runtime.dram_latency[RL_WL_idx].MR2 );

   }

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         // Set rank init complete signal
         if (chip_select & DDR_CS0) {
            HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, 1);
         }
         if (chip_select & DDR_CS1) {
            HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK1_INITCOMPLETE, 1);
         }
      }
   }
   if (in_self_refresh == 1)
   {
    for (ch = 0; ch < 2; ch++)
    {
        reg_offset_shke = REG_OFFSET_SHKE(ch);
  
        if ((channel >> ch) & 0x1)
        {
          // Set rank init complete signal
          if (chip_select & DDR_CS0) {
              HWIO_OUTXF2 (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, RANK0_EN, 1, 1);            
          }
          if (chip_select & DDR_CS1) {
              HWIO_OUTXF2 (reg_offset_shke, SHKE_CONFIG, RANK1_INITCOMPLETE, RANK1_EN, 1, 1);  
          }
        }
    }
                    
    for (cs = 0; cs < 2; cs++)
    {
      cs_1hot = CS_1HOT(cs);

      if ((chip_select >> cs) & 0x1)
      {
         // Set up the DDR device latencies so that we can read and write to it.
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_2, 0);  //read write latency
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_13, 0x80); //set FSP_OP=1, FSP_WR=0
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_2, 0);  //read write latency                       
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_13, 0);
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_2, 0);  //read write latency                       
         seq_wait(1, MS);
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_1, 0x06);   
         if(ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X)
         {
            BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_3, 0xB0); //10  < F <= 400MHz, set MR3[0],PU-CAL=VDDQ/2.5 for fsp0, it was 0xB1(VDDQ/3)
         }
         else
         {
            BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_3, 0xB0); //10  < F <= 400MHz, set MR3[0],PU-CAL=VDDQ/2.5 for fsp0, it was 0xB1(VDDQ/3)   
         }
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_11, 0x0);
         BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_22, 0xFC);
      }
	  
	  if(ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X) 
      {
         if(chip_select == DDR_CS_BOTH)
         {
				//If we have byte mode or hybrid mode, make sure there is no double termination 
				if((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_0)) & 0x2) ==0x2)){  //check if device supports byte mode, both ranks return same value if device supports byte mode
					//if both byte mode CS0=0x84, CS1=0xFC
					if( ((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x78);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x78);
					}
					//if CS0 is byte mode and CS1 is x16
					if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x16) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x78);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x38);
					}

					//if CS0 is x16 and CS1 is x8
					if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x16) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x78);
					}						
				
				}
			else {
				BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);
				BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x38);
			}
			
		 }
         else if(chip_select == DDR_CS0)
         {
            BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);  //FSP-1, SoC ODT = 60ohm, CK/CS/CA = 1 
                                                                   //CK term, CA unterm,CS unterm 
         }
      }
      else
      {
 
            BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, 0x00);  //FSP-1, SoC ODT = 80ohm, CK/CS = 0, CA = 1. Same for LP4 for both ranks 
      }
	  
	  
	  //  BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);//0x38//added
	    //BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x78);//0x78//added
    }
    // Enable auto-refresh as early as possible   
    BIMC_Auto_Refresh_Ctrl (channel, chip_select, 1);
   }
}

//================================================================================================//
// This function detects DRAM Geometry. An MR8 read provides the rank density information.
// Accordingly, the number of rows and columns is filled out from a Look-Up Table (LUT).
// channel=DDR_CH_BOTH is not supported in this function
//================================================================================================//
boolean BIMC_DDR_Geometry_Detection(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select,
                                    uint32 mr8_value)
{
   uint32 device_type     = 0;
   uint32 device_density  = 0;
   uint32 device_io_width = 0;
   uint32 nrows  = 0;
   uint32 ncols  = 0;
   uint32 width  = 0;
   uint32 nbanks = 8;
   uint8  ch_inx = 0;
   uint8  (*lpddr_geometry_ptr)[2][2] = lpddr_geometry_table;

   device_type     = (mr8_value & 0x3);
   device_density  = (mr8_value & 0x3C) >> 2;
   device_io_width = (mr8_value & 0xC0) >> 6;

   ch_inx = CH_INX(channel);

   // Detect S8 x32/x16 LPDDR3 and S16 x16 (per channel) LPDDR4 only
   if ( ( (ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR3) && ( (device_type != 3) || (device_io_width >= 2) ) )  ||
        ( (ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4) && ( (device_type != 0) || (device_io_width >= 2) ) )  )
   {   return FALSE;   }
   
#if 0
   if ( ( ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR3) && (device_type == 3))
   {
      device_density -= 4;
   }
#endif

   if(device_io_width < 2)
   {
     width = interface_width [device_io_width];
     nrows =  (uint32)lpddr_geometry_ptr[device_density][device_io_width][0];
     ncols =  (uint32)lpddr_geometry_ptr[device_density][device_io_width][1];
   }

   if (chip_select == DDR_CS0)
   {
      ddr->detected_ddr_device[ch_inx].num_rows_cs0        = nrows;
      ddr->detected_ddr_device[ch_inx].num_cols_cs0        = ncols;
      ddr->detected_ddr_device[ch_inx].num_banks_cs0       = nbanks;
      ddr->detected_ddr_device[ch_inx].interface_width_cs0 = width;
   }
   else if (chip_select == DDR_CS1)
   {
      ddr->detected_ddr_device[ch_inx].num_rows_cs1        = nrows;
      ddr->detected_ddr_device[ch_inx].num_cols_cs1        = ncols;
      ddr->detected_ddr_device[ch_inx].num_banks_cs1       = nbanks;
      ddr->detected_ddr_device[ch_inx].interface_width_cs1 = width;
   }

   return TRUE;
}

//================================================================================================//
// void BIMC_DDR_Topology_Detection(channel, chip_select, ddr)
// This function auto-detects the presence of a rank.
// If a rank is present, it proceeds to finding the geometry (and subsequently num rank/cols).
// If a rank is not present (a timed-out MRR), it disables the rank, CK and CKE.
// Channel=DDR_CH_BOTH is not supported in this function
//================================================================================================//
DDR_CHIPSELECT BIMC_DDR_Topology_Detection(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint8  cs = 0;
   uint32 mr8_value        = 0;
   uint8  ch_inx           = 0;
   DDR_CHIPSELECT  cs_1hot = DDR_CS0;
   uint32 reg_offset_shke  = 0;
   DDR_CHIPSELECT populated_chip_select = DDR_CS_NONE;

   ch_inx = CH_INX(channel);
   reg_offset_shke = REG_OFFSET_SHKE(ch_inx);

   // rank_en/rank_initcomplete is set to 1 so that MR8 read can go through. If rank is unpopulated,
   // this will be unset later on.
   HWIO_OUTXF4 (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, RANK0_EN, RANK1_INITCOMPLETE, RANK1_EN,
                1, 1, 1, 1);
   for (cs = 0; cs < 2; cs++)
   {
      cs_1hot = CS_1HOT(cs);

      if ((chip_select >> cs) & 0x1)
      {
         mr8_value = BIMC_MR_Read(channel, cs_1hot, JEDEC_MR_8);

         // Timeout occurred. Rank is NOT populated.
         if (HWIO_INXF (reg_offset_shke, SHKE_MREG_RDATA_STATUS, MREG_TIMEOUT) == 1)
         {
            // Disable the unpopulated rank
            if (cs == 0)
            {
               HWIO_OUTXF2 (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, RANK0_EN, 0, 0);
               ddr->detected_ddr_device[ch_inx].num_rows_cs0        = 0;
               ddr->detected_ddr_device[ch_inx].num_cols_cs0        = 0;
               ddr->detected_ddr_device[ch_inx].num_banks_cs0       = 0;
               ddr->detected_ddr_device[ch_inx].interface_width_cs0 = 0;
            }
            if (cs == 1)
            {
               HWIO_OUTXF2 (reg_offset_shke, SHKE_CONFIG, RANK1_INITCOMPLETE, RANK1_EN, 0, 0);
               ddr->detected_ddr_device[ch_inx].num_rows_cs1        = 0;
               ddr->detected_ddr_device[ch_inx].num_cols_cs1        = 0;
               ddr->detected_ddr_device[ch_inx].num_banks_cs1       = 0;
               ddr->detected_ddr_device[ch_inx].interface_width_cs1 = 0;
            }

            // Disable CKE to the unpopulated rank
            HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, CKE_OFF, cs_1hot, 0x1);
            while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_OFF));

            // Disable CK to the unpopulated rank
            HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, CK_OFF, cs_1hot, 0x1);
            while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CK_OFF));
         }
         else
         // Rank is populated
         {
            BIMC_DDR_Geometry_Detection(ddr, channel, cs_1hot, mr8_value);
            populated_chip_select |= (cs ? DDR_CS1 : DDR_CS0);

            // Read manufacturer ID from MR5.
            ddr->detected_ddr_device[ch_inx].manufacture_name = (BIMC_MR_Read(channel, cs_1hot, JEDEC_MR_5)& 0xFF);
         }
      }
   }

   return (populated_chip_select);
}


//================================================================================================//
// BIMC DRAM Address Setting up
// channel=DDR_CH_BOTH is not supported in this function
// cs=DDR_CS_BOTH is not supported in this function
//================================================================================================//

void BIMC_DDR_Addr_Setup (DDR_STRUCT *ddr, uint8 ch, uint8 cs)
{
    uint32 addr_base_9_2   = 0;
    uint32 size_in_mb      = 0;
    uint32 addr_mask       = 0;
    uint32 num_rows        = 0;
    uint32 num_cols        = 0;
    uint32 num_banks       = 0;
    uint32 reg_offset_scmo = 0;
    uint32 reg_offset_dpe  = 0;
    
    uint64 base_addr    = 0xFFFFFFFFFFFFFFFF;
    static uint64 ch0_cs0_size = 0;
    static uint64 ch0_cs1_size = 0;
    static uint64 ch1_cs0_size = 0;
    uint64 addr_offset  = 0;
    uint64 total_package_size  = 0;
    
    uint8 num_rows_cs0[2]  = {0};
    uint8 num_cols_cs0[2]  = {0};
    uint8 num_banks_cs0[2] = {0};
    uint8 num_rows_cs1[2]  = {0};
    uint8 num_cols_cs1[2]  = {0};
    uint8 num_banks_cs1[2] = {0};
    
    uint32 ddr0_cs0_mb     = 0;
    uint32 ddr0_cs1_mb     = 0;
    uint32 ddr1_cs0_mb     = 0;
    uint32 ddr1_cs1_mb     = 0;
    uint32 cs_size_in_mb   = 0;
    uint8  ch_num          = 0;
    uint8  mr8_value       = 0;
    uint8  device_density  = 0;
    uint8  device_io_width = 0;
    uint8  ch0_cs1_en      = 0;
    uint8  ch1_cs1_en      = 0;

    uint32 tWR             = 0;
    uint32 tWTR            = 0;
    
    
    for (ch_num=0; ch_num<2; ch_num++)
    {
        num_rows_cs0[ch_num]  = ddr->detected_ddr_device[ch_num].num_rows_cs0;
        num_cols_cs0[ch_num]  = ddr->detected_ddr_device[ch_num].num_cols_cs0;
        num_banks_cs0[ch_num] = ddr->detected_ddr_device[ch_num].num_banks_cs0;
        num_rows_cs1[ch_num]  = ddr->detected_ddr_device[ch_num].num_rows_cs1;
        num_cols_cs1[ch_num]  = ddr->detected_ddr_device[ch_num].num_cols_cs1;
        num_banks_cs1[ch_num] = ddr->detected_ddr_device[ch_num].num_banks_cs1;
    }

    ch0_cs1_en = ddr->detected_ddr_device[0].populated_chipselect >> 1;
    ch1_cs1_en = ddr->detected_ddr_device[1].populated_chipselect >> 1;

    mr8_value = BIMC_MR_Read((DDR_CHANNEL)(CH_1HOT(ch)), CS_1HOT(cs), JEDEC_MR_8);
    device_density  = (mr8_value & 0x3C) >> 2;
    device_io_width = (mr8_value & 0xC0) >> 6;

    addr_offset = ((uint64) 1) << lpddr_size_table[device_density][ddr->misc.bus_width_pch/16-1][1];
    cs_size_in_mb = lpddr_size_table[device_density][ddr->misc.bus_width_pch/16-1][0];

    if (device_io_width == DEVICE_WIDTH_IS_x8)
    {
       cs_size_in_mb    *= 2;
       addr_offset      *= 2;
    }
    
    if (cs == 0)  // Rank0
    {
    
        if(ch == 0) //CH0, rank0
        {
            ddr0_cs0_mb = cs_size_in_mb;
            ddr->ddr_size_info.ddr0_cs0_mb       = ddr0_cs0_mb;
            ddr->ddr_size_info.ddr0_cs0_io_width = device_io_width;
            ch0_cs0_size = addr_offset;
            ch1_cs0_size = addr_offset;
        }
        else //CH1, rank0
        {
            ddr1_cs0_mb = cs_size_in_mb;
            ddr->ddr_size_info.ddr1_cs0_mb = ddr1_cs0_mb;
            ddr->ddr_size_info.ddr1_cs0_io_width = device_io_width;
            ch1_cs0_size = addr_offset;

        }
    }
    else //rank1
    {
        if((ch == 0) & ch0_cs1_en) //CH0, rank1
        {
            ddr0_cs1_mb = cs_size_in_mb;
            ddr->ddr_size_info.ddr0_cs1_mb = ddr0_cs1_mb;
            ddr->ddr_size_info.ddr0_cs1_io_width = device_io_width;
            ch0_cs1_size = addr_offset;
            //ch1_cs1_size is never used in base addr calc
        }
        else if((ch == 1) & ch1_cs1_en) //CH1, rank1
        {
            ddr1_cs1_mb = cs_size_in_mb;
            ddr->ddr_size_info.ddr1_cs1_mb = ddr1_cs1_mb;
            ddr->ddr_size_info.ddr1_cs1_io_width = device_io_width;
        }
        else // rank1 non-exist
        {
            ddr0_cs1_mb = 0;
            ddr1_cs1_mb = 0;
            ddr->ddr_size_info.ddr0_cs1_mb = 0;
            ddr->ddr_size_info.ddr1_cs1_mb = 0;
        }
   }

    
    if (cs == 0)  // Rank 0
    {
        num_rows  = num_rows_cs0[ch];
        num_cols  = num_cols_cs0[ch];
        num_banks = num_banks_cs0[ch];
    
    
        if(ch == 0) //CH0
        {
            size_in_mb = ddr0_cs0_mb;
    
            /* Regardless of interleave vs non-interleave
            * we always populate CH0 CS0 at the base, no calculation needed.*/
            base_addr = SCMO_BASE;
            ddr->ddr_size_info.ddr0_cs0_addr = base_addr;
        }
        else /* CH1 */
        {
            size_in_mb = ddr1_cs0_mb;
    
            /* CH1 CS0 base address depends on interleave vs non-interleave
            * interleaved base will be [base of CH0 CS0]
            * non-interleaved base will be [base of CH0 CS0] +
            *                              [ramsize of CH0 CS0]
            interleave_en for both channel are the same within one rank, using channel 0*/
            if(ddr->detected_ddr_device[0].interleave_en & DDR_CS0_INTERLEAVE)
            {
                base_addr = SCMO_BASE;
            }
            else
            {
                /* Non-interleaved memory follows logical base address increments
                * CH1 CS0 follows CH0 CS0,
                * CH0 CS1 follows CH1 CS0,
                * etc.
                */
			if((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
			{ 
                
				base_addr = SCMO_BASE + (ch0_cs0_size + ch0_cs1_size + ch1_cs0_size);
            }
			else 
			{
			    base_addr = SCMO_BASE + ch0_cs0_size;
			}
            }
            ddr->ddr_size_info.ddr1_cs0_addr = base_addr;
        }
        //minimum supported density (right shift by 26)
        reg_offset_scmo = REG_OFFSET_SCMO(ch);   
        addr_base_9_2 = (base_addr >> 26);
        HWIO_OUTXFI (reg_offset_scmo, SCMO_CFG_ADDR_BASE_CSn, cs, ADDR_BASE, addr_base_9_2);    
    }
    else // cs == 1 ; Rank 1 selected
    {
        num_rows  = num_rows_cs1[ch];
        num_cols  = num_cols_cs1[ch];
        num_banks = num_banks_cs1[ch];
    
    
        if(ch == 0) //CH0
        size_in_mb = ddr0_cs1_mb;
        else
        size_in_mb = ddr1_cs1_mb;
    
        /* CH0 CS1 base address depends on interleave vs non-interleave
        * interleaved base will be [base of CH0 CS0] + [ramsize of CH0 CS0] * 2
        * non-interleaved base will be [base of CH0 CS0]
        *                                    + [ramsize of CH0 CS0]
        *                                    + [ramsize of CH1 CS0]
        interleave_en for both channel are the same within one rank, using channel 0*/
        
		if((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
		{ 
        
			base_addr = SCMO_BASE + (ch0_cs0_size);
		}
		else
		{
		        //base_addr = SCMO_BASE + (ch0_cs0_size + ch1_cs0_size);
			base_addr = SCMO_BASE + (ch0_cs0_size + ch1_cs0_size);
		}
		
        total_package_size = ddr->ddr_size_info.ddr0_cs0_mb + ddr->ddr_size_info.ddr0_cs1_mb + ddr->ddr_size_info.ddr1_cs0_mb + ddr->ddr_size_info.ddr1_cs1_mb;
		if((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
		{
         if ((total_package_size > 0xC00) && (total_package_size <= 0x1000))  //double SCMO CS1 base address if total DRAM size in a package is between 3GB and 4GB 
	        {
	            // base_addr = 2 * base_addr; 
	        }
		}
		else 
		{
		 if ((total_package_size > 0xC00) && (total_package_size <= 0x1800))  //double SCMO CS1 base address if total DRAM size in a package is between 3GB and 4GB 
			{
            base_addr = 2 * base_addr; 
			}	       
		}
        addr_base_9_2 = (base_addr >> 26);
        
        if(ddr->detected_ddr_device[0].interleave_en & DDR_CS1_INTERLEAVE)
        {
            ddr->ddr_size_info.ddr0_cs1_addr = base_addr;
            ddr->ddr_size_info.ddr1_cs1_addr = base_addr;
            
            // update SCMO_ADDR_BASE dynamically
            // minimum supported density (right shift by 26)
            HWIO_OUTXFI (REG_OFFSET_SCMO(0), SCMO_CFG_ADDR_BASE_CSn, cs, ADDR_BASE, addr_base_9_2);
            HWIO_OUTXFI (REG_OFFSET_SCMO(1), SCMO_CFG_ADDR_BASE_CSn, cs, ADDR_BASE, addr_base_9_2);         
        }
        else
        {
            /* Non-interleaved memory follows logical base address increments
            * CH1 CS0 follows CH0 CS0,
            * CH0 CS1 follows CH1 CS0,
            * etc.
            */
            if(ch == 0) //CH0
            {
                ddr->ddr_size_info.ddr0_cs1_addr = base_addr;
                
                // update SCMO_ADDR_BASE dynamically
                // minimum supported density (right shift by 26)
                HWIO_OUTXFI (REG_OFFSET_SCMO(0), SCMO_CFG_ADDR_BASE_CSn, cs, ADDR_BASE, addr_base_9_2);
            }
            else
            {
		    if((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
			{
				base_addr = SCMO_BASE + (ch0_cs0_size + ch1_cs0_size); // + ch1_cs0_size);                
			}
			else
			{
				base_addr = SCMO_BASE + (ch0_cs0_size + ch0_cs1_size + ch1_cs0_size);

			}
        total_package_size = ddr->ddr_size_info.ddr0_cs0_mb + ddr->ddr_size_info.ddr0_cs1_mb + ddr->ddr_size_info.ddr1_cs0_mb + ddr->ddr_size_info.ddr1_cs1_mb;
        if ((total_package_size > 0xC00) && (total_package_size <= 0x1000))  //double SCMO CS1 base address if total DRAM size in a package is between 3GB and 4GB 
                {
		    		  if((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
					{
                   
					}
					else
					{
						base_addr = 2 * base_addr; 	
					}
					
				
                }
                ddr->ddr_size_info.ddr1_cs1_addr = base_addr;
                
                // update SCMO_ADDR_BASE dynamically
                // minimum supported density (right shift by 26)
                addr_base_9_2 = (base_addr >> 26);
                HWIO_OUTXFI (REG_OFFSET_SCMO(1), SCMO_CFG_ADDR_BASE_CSn, cs, ADDR_BASE, addr_base_9_2);
            }
        }

    }


    switch(size_in_mb){
        case 8192 : addr_mask = 0x80;
            break;
        case 4096 : addr_mask = 0xc0;
            break;
        case 2048 : addr_mask = 0xe0;
            break;
        case 1536 : addr_mask = 0xe0;
            break;  
        case 1024 : addr_mask = 0xf0;
            break;
        case 768  : addr_mask = 0xf0;
            break;
        case 512  : addr_mask = 0xf8;
            break;
        case 256  : addr_mask = 0xfc;
            break;
        case 128  : addr_mask = 0xfe;
            break;
        case 64   : addr_mask = 0xff;
            break;
        default   : addr_mask = 0x00;
            break;
    }

    reg_offset_scmo = REG_OFFSET_SCMO(ch);
    reg_offset_dpe  = REG_OFFSET_DPE(ch);
    
    HWIO_OUTXFI (reg_offset_scmo, SCMO_CFG_ADDR_MAP_CSn,  cs, BANK_SIZE, num_banks >> 3);// 0x0:BANKS_4
                                                                                     // 0x1:BANKS_8
    HWIO_OUTXFI (reg_offset_scmo, SCMO_CFG_ADDR_MAP_CSn,  cs, ROW_SIZE,  num_rows - 13); // 0x0:ROWS_13
                                                                                     // 0x1:ROWS_14
                                                                                     // 0x2:ROWS_15
                                                                                     // 0x3:ROWS_16
    HWIO_OUTXFI (reg_offset_scmo, SCMO_CFG_ADDR_MAP_CSn,  cs, COL_SIZE,  num_cols - 8);  // 0x0:COLS_8
                                                                                     // 0x1:COLS_9
                                                                                     // 0x2:COLS_10
                                                                                     // 0x3:COLS_11
    
    // Convert base addr to [9:2] for SCMO base CSR. Divide base address by 64MB which is the
    // minimum supported density (right shift by 26)
    
    HWIO_OUTXFI (reg_offset_scmo, SCMO_CFG_ADDR_MASK_CSn, cs, ADDR_MASK, addr_mask);
    
    if (num_banks != 0) 
    {
        HWIO_OUTXFI (reg_offset_scmo, SCMO_CFG_ADDR_MAP_CSn, cs, RANK_EN, 1);
    }
    
    if (cs == 0)  // Rank 0
    {
        if(ddr->misc.platform_id == STARHAWK_PLATFORM_ID)	//This condition is added since the recommended tRFC and tXSR value for Micron 12Gb DRAM is different. But due to BIMC limitation, the value overflows for 1555MHz and 1804MHz and causes fail. So this change is done only for SDM630 which has Fmax as 1296MHz
		{
			//update tRFC/tXSR based on chip density
			if (ddr->cdt_params.lpddr.tRFC == 0) 
			{
				ddr->cdt_params.lpddr.tRFC = lpddr_timing_table_sdm630[device_density][0];
			}
			HWIO_OUTXF (reg_offset_dpe, DPE_DRAM_TIMING_3, TRFCAB, ddr->cdt_params.lpddr.tRFC);
			
			if (ddr->cdt_params.lpddr.tXSR == 0) 
			{ 
				ddr->cdt_params.lpddr.tXSR = lpddr_timing_table_sdm630[device_density][1];
			}
		} 	//only for Starhawk
		else
		{// For SDM660
			//update tRFC/tXSR based on chip density
			if (ddr->cdt_params.lpddr.tRFC == 0) 
			{
				ddr->cdt_params.lpddr.tRFC = lpddr_timing_table[device_density][0];
			}
			HWIO_OUTXF (reg_offset_dpe, DPE_DRAM_TIMING_3, TRFCAB, ddr->cdt_params.lpddr.tRFC);
			
			if (ddr->cdt_params.lpddr.tXSR == 0) 
			{ 
				ddr->cdt_params.lpddr.tXSR = lpddr_timing_table[device_density][1];
			}
		}
        HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_10, TXSRD, TXSNR,
                    ddr->cdt_params.lpddr.tXSR, ddr->cdt_params.lpddr.tXSR);
        
    }
    //update tWTR/tWR based on device_io_width x16 or x8 device            
    if (ddr->cdt_params.lpddr.tWR == 0) 
    {
        if(cs == 0){ //Rank 0
            HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_1, TWR, TWR_MIN_CYC, lpddr_byte_mode_timing_table[0][device_io_width], lpddr_byte_mode_timing_table[1][device_io_width]);
        }
        if(cs == 1){ //Rank 1
            tWR = HWIO_INXF (reg_offset_dpe, DPE_DRAM_TIMING_1, TWR);
            if(lpddr_byte_mode_timing_table[0][device_io_width] > tWR){
                HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_1, TWR, TWR_MIN_CYC, lpddr_byte_mode_timing_table[0][device_io_width], lpddr_byte_mode_timing_table[1][device_io_width]);
            }
        }

    }else{
        HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_1, TWR, TWR_MIN_CYC, ddr->cdt_params.lpddr.tWR, lpddr_byte_mode_timing_table[1][device_io_width]);
    }
    
    if (ddr->cdt_params.lpddr.tWTR == 0) 
    {
        if(cs == 0){ //Rank 0
            HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_2, TWTR, TWTR_MIN_CYC, lpddr_byte_mode_timing_table[2][device_io_width], lpddr_byte_mode_timing_table[3][device_io_width]);
        }
        if(cs == 1){ //Rank 1
            tWTR = HWIO_INXF (reg_offset_dpe, DPE_DRAM_TIMING_2, TWTR);
            if(lpddr_byte_mode_timing_table[2][device_io_width] > tWTR){
                HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_2, TWTR, TWTR_MIN_CYC, lpddr_byte_mode_timing_table[2][device_io_width], lpddr_byte_mode_timing_table[3][device_io_width]);
            }
        }
    }else{
        HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_2, TWTR, TWTR_MIN_CYC, ddr->cdt_params.lpddr.tWTR, lpddr_byte_mode_timing_table[3][device_io_width]);
    }
                
    // Kick off timing parameter calculation and wait until done
    HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_4, RECALC_PS_PARAMS, 0x1);
    while (HWIO_INXF (reg_offset_dpe, DPE_MEMC_STATUS_1, CYC_CALC_VALID));

    // Load all the calculated settings into DPE actual registers
    HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);
    
}


//================================================================================================//
// BIMC Post Initialization sequence  //
// Channel=DDR_CH_BOTH is not supported in this function
//================================================================================================//
void BIMC_Post_Init_Setup (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   uint8 interface_width_index_cs0 = 0;
   uint8 interface_width_index_cs1 = 0;
   uint8 ch_inx                    = 0;
   uint32 reg_offset_dpe           = 0;
   uint32 reg_offset_scmo          = 0;
   uint32 reg_offset_shke          = 0;


   ch_inx          = CH_INX(channel);
   reg_offset_dpe  = REG_OFFSET_DPE(ch_inx);
   reg_offset_scmo = REG_OFFSET_SCMO(ch_inx);
   reg_offset_shke = REG_OFFSET_SHKE(ch_inx);


   if (chip_select & DDR_CS0)
   {
      if (ddr->detected_ddr_device[ch_inx].interleave_en & DDR_CS0_INTERLEAVE)
      {
         HWIO_OUTXF (reg_offset_scmo, SCMO_CFG_SLV_INTERLEAVE_CFG , INTERLEAVE_CS0, 1);
      }

      switch(ddr->detected_ddr_device[ch_inx].interface_width_cs0)
      {
         case 64 : interface_width_index_cs0 = 0x3;
            break;
         case 32 : interface_width_index_cs0 = 0x2;
            break;
         case 16 : interface_width_index_cs0 = 0x1;
            break;
         case  8 : interface_width_index_cs0 = 0x0;
            break;   
         default : interface_width_index_cs0 = 0x0;
            break;
      }

      HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_0, DEVICE_CFG_RANK0, interface_width_index_cs0);

      BIMC_DDR_Addr_Setup (ddr, ch_inx, CS_INX(DDR_CS0));

      // Bank number 4: 0x00; Bank number 8: 0x01
      HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, NUM_BANKS, (ddr->detected_ddr_device[ch_inx].num_banks_cs0) >> 3 );

   }

   if (chip_select & DDR_CS1)
   {
      if (ddr->detected_ddr_device[ch_inx].interleave_en & DDR_CS1_INTERLEAVE)
      {
         HWIO_OUTXF (reg_offset_scmo, SCMO_CFG_SLV_INTERLEAVE_CFG , INTERLEAVE_CS1, 1);
      }

      switch(ddr->detected_ddr_device[ch_inx].interface_width_cs1)
      {
         case 64 : interface_width_index_cs1 = 0x3;
            break;
         case 32 : interface_width_index_cs1 = 0x2;
            break;
         case 16 : interface_width_index_cs1 = 0x1;
            break;
         case  8 : interface_width_index_cs1 = 0x0;
            break;   
         default : interface_width_index_cs1 = 0x0;
            break;
      }

      HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_0, DEVICE_CFG_RANK1, interface_width_index_cs1);

      BIMC_DDR_Addr_Setup (ddr, ch_inx, CS_INX(DDR_CS1));

      //Bank number 4: 0x00; Bank number 8: 0x01
      HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, NUM_BANKS, (ddr->detected_ddr_device[ch_inx].num_banks_cs1) >> 3 );
   }

   //Storing tWR and TWTR into CDT for re-use in SDI path
   if(ddr->cdt_params.lpddr.tWR == 0){
       ddr->cdt_params.lpddr.tWR = HWIO_INXF (reg_offset_dpe, DPE_DRAM_TIMING_1, TWR); 
   }
   if(ddr->cdt_params.lpddr.tWTR == 0){
       ddr->cdt_params.lpddr.tWTR = HWIO_INXF (reg_offset_dpe, DPE_DRAM_TIMING_2, TWTR); 
   }

   // bank count for both ranks
   HWIO_OUTXF2 (reg_offset_dpe, DPE_CONFIG_1, NUM_BANKS_RANK0, NUM_BANKS_RANK1,
                ddr->detected_ddr_device[ch_inx].num_banks_cs0, ddr->detected_ddr_device[ch_inx].num_banks_cs1);

   // Enable activity based channel clock gating after init. This clock gating was disable in one-time
   // settings so that PHY will recieve clock during PHY init.
   HWIO_OUTXF2 (reg_offset_dpe, DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x0, 0x0);

   // Enable Power Down
   HWIO_OUTXF2 (reg_offset_dpe, DPE_PWR_CTRL_0, PWR_DN_EN, CLK_STOP_PWR_DN_EN, 0x1, 0x1);
   HWIO_OUTXF  (reg_offset_dpe, DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

   // Enable all periodic functions: auto refresh, hw self refresh, periodic ZQCAL, periodic SRR,
   BIMC_All_Periodic_Ctrl (ddr, channel, chip_select, 0x01/*0x01 for enable*/);
   
}


