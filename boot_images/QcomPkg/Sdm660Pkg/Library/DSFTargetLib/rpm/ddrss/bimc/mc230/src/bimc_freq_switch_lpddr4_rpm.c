/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/src/bimc_freq_switch_lpddr4_rpm.c#8 $
$DateTime: 2017/03/31 01:29:53 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_rpm.h"
#include "ddrss_rpm.h"
#include "target_config_rpm.h"


#define FREQ_SWITCH_NO_ZQCAL_ENABLE   1
#define FREQ_SWITCH_WITH_ZQCAL_ENABLE 0


//================================================================================================//
// BIMC PRE CLOCK SWITCH SEQUENCE
//================================================================================================//
boolean BIMC_Pre_Clock_Switch (DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint32 reg_offset_dpe  = 0;
   uint32 new_period_ps   = 0;
   uint32 curr_period_ps  = 0;
   uint8  rl              = 0;
   uint8  rl_cs0          = 0;
   uint8  rl_cs1          = 0;
   uint8  wl              = 0;
   uint8  mr2_wr_val      = 0;
   uint8  ch              = 0;
   uint8  curr_fsp_op     = 0;
   uint8  new_fsp_op      = 0;
   uint8  curr_DBI_en     = 0;
   uint8  new_DBI_en      = 0;
   uint8  ODTLon_wrdata   = 0;
   uint8  tWPRE_field     = 0;
   uint8  MR3_wrdata      = 0;
   uint8  MR1_wrdata      = 0;
   uint8  MR11_wrdata     = 0;
   uint8  MR13_wrdata_1   = 0;
   uint8  MR13_wrdata_2   = 0;
   uint8  curr_params_idx = 0;
   uint8  new_params_idx  = 0;
   uint8  new_RL_WL_idx   = 0;

   uint8  tvrcg_disable_wait_time = 0;
   uint8  tfc_wait_time           = 0;
   uint32 total_tfc_wait_time     = 0;
   uint8  tfc_precise_wait_time   = 0;
   uint32 tFC_spec           = ddr->cdt_params.lpddr.tFC;
   uint32 tVRCG_DISABLE_spec = ddr->cdt_params.lpddr.tVRCG_DISABLE;

   uint8      (*ODTLon_ptr)[2] = ODTLon;
   
#if FREQ_SWITCH_WITH_ZQCAL_ENABLE
   uint32 reg_offset_shke  = 0;
   uint8  tzqlat_wait_time = 0;
#endif

#if DSF_PERIODIC_TRAINING_EN
   uint8  cs             = 0;
   DDR_CHIPSELECT qualified_cs = (DDR_CHIPSELECT)(ddr->detected_ddr_device[0].populated_chipselect);
   uint32 reg_offset_dtts_sram  = 0;
   uint8  num_samples[NUM_CH][NUM_CS][NUM_DIE_PCH] = {{{0}}};
   uint8  bit_vec         = 0;
   uint8  comp_bit_vec    = 0; 
   uint32 fw_active_mask  = 0x10000;
   
   uint8 max_num_samples = 0;
   uint16 dit_runtime    = 0;
   uint8  trac_ndx       = 0;
   uint32 trac_freq      = 0;
   uint8  dit_read_wait  = 0;
#endif

   
   uint32 new_clk_khz;
   uint32 curr_clk_khz;
   uint8 new_clk_idx;
   
#if (DSF_PERIODIC_TRAINING_EN || DSF_RCW_TRAINING_EN)
   // Training data structure pointer
   training_data *training_data_ptr;
   
   training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
#endif

   
   new_clk_khz = ddr->misc.new_clk_in_kHz;
   curr_clk_khz = ddr->misc.current_clk_in_kHz;
   
   // get the clk index in clock plan
   for (new_clk_idx = 0; new_clk_idx < ddr->misc.ddr_num_clock_levels; new_clk_idx++)
   {
      if (new_clk_khz <= ddr->misc.clock_plan[new_clk_idx].clk_freq_in_khz)
         break;
   }
   
   
   new_params_idx  = BIMC_Freq_Switch_Params_Index (ddr, new_clk_khz);
   curr_params_idx = BIMC_Freq_Switch_Params_Index (ddr, curr_clk_khz);
   
   new_RL_WL_idx  = BIMC_RL_WL_Freq_Index (ddr, new_clk_khz);
   
   curr_fsp_op = ddr->extended_cdt_runtime.bimc_freq_switch[curr_params_idx].fsp;
   curr_DBI_en = ddr->extended_cdt_runtime.bimc_freq_switch[curr_params_idx].rd_dbi;
   new_fsp_op  = ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].fsp;
   new_DBI_en  = ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].rd_dbi;

   if (new_DBI_en == RL_DBI_OFF) 
   { 
        if (ddr->ddr_size_info.ddr0_cs0_io_width == DEVICE_WIDTH_IS_x16)
		{
            rl_cs0     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_Off_x16; //use different sets of RL if DBI OFF & x16
        }
		else
		{    
            rl_cs0     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_Off_x8; //use different sets of RL if DBI OFF & x8
        }
   }       
   else
   {
        if (ddr->ddr_size_info.ddr0_cs0_io_width == DEVICE_WIDTH_IS_x16)
		{
            rl_cs0     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_On_x16; //use different sets of RL if DBI enabled & x16
        }
		else
		{
            rl_cs0     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_On_x8; //use different sets of RL if DBI enabled & x8
        }
   }

   if (new_DBI_en == RL_DBI_OFF) 
   { 
        if (ddr->ddr_size_info.ddr0_cs1_io_width == DEVICE_WIDTH_IS_x16)
		{
            rl_cs1     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_Off_x16; //use different sets of RL if DBI OFF & x16
        }
		else
		{    
            rl_cs1     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_Off_x8; //use different sets of RL if DBI OFF & x8
        }
   }       
   else
   {
        if (ddr->ddr_size_info.ddr0_cs1_io_width == DEVICE_WIDTH_IS_x16)
		{
            rl_cs1     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_On_x16; //use different sets of RL if DBI enabled & x16
        }
		else
		{
            rl_cs1     = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].RL_DBI_On_x8; //use different sets of RL if DBI enabled & x8
        }
   }

   if (rl_cs0 >= rl_cs1)
   {
       rl   = rl_cs0;
   }
   else
   {
       rl   = rl_cs1;
   }
   wl         = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].WL;
    
   // Get 8bit value for MRs
   mr2_wr_val = ddr->extended_cdt_runtime.dram_latency[new_RL_WL_idx].MR2;
   MR3_wrdata = ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].MR3;
   MR1_wrdata = ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].MR1;
   MR11_wrdata = ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].MR11;
   
   new_period_ps = CONVERT_CYC_TO_PS / new_clk_khz; //unit in ps

   
#if DSF_PERIODIC_TRAINING_EN   

   max_num_samples = training_data_ptr->results.dit.dit_loop_count;
   dit_runtime    = training_data_ptr->results.dit.dit_runtime_count;
   trac_ndx       = training_data_ptr->results.dit.dit_trac_ndx;
   if (trac_ndx < ddr->misc.ddr_num_clock_levels)
   {
      trac_freq      = ddr->misc.clock_plan[trac_ndx].clk_freq_in_khz;
   }
   dit_read_wait  = 1 + ((dit_runtime*1000)/curr_clk_khz); //unit in us
   
   if ((new_clk_idx == trac_ndx) || (new_clk_idx == (trac_ndx - 1)))
   {
	 if ((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
	  {
		  channel = DDR_CH1;
	  }
   }

   // Check if DTTS Imem and Dmem are loaded and if tracking index is provided by boot training
   if (HWIO_DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn_INI(REG_OFFSET_DTTS(0),15) == 1 && trac_ndx != 0xFF)
   {
      // Check if in tracking freq
      if(curr_clk_khz >= trac_freq)
      {
         for (ch = 0; ch < NUM_CH; ch++)
         {
            if (channel>>ch & 0x1)
            {
               // Disable power down features to keep the clock running for DIT oscillator in DRAM
               HWIO_OUTXF2 (REG_OFFSET_DPE(ch), DPE_PWR_CTRL_0, CLK_STOP_PWR_DN_EN, PWR_DN_EN, 0, 0);
               HWIO_OUTXF (REG_OFFSET_DPE(ch), DPE_CONFIG_2, DDR_CK_ON_DBG, 1);
               HWIO_OUTXF (REG_OFFSET_DPE(ch), DPE_CONFIG_4, LOAD_ALL_CONFIG, 1);
               
               // Disable interval timer for periodic MPC/MR18/MR19
               HWIO_OUTXF (REG_OFFSET_SHKE(ch), SHKE_INTERVAL_TIMER_CNTL_1, INTERVAL_TIMER, 0);
               
               // Assert a flag in DTTS Dmem to indicate a freq switch is about to happen so that no new PHY update will happen
               out_dword (REG_OFFSET_DTTS_SRAM(ch) + FREQ_SWITCH_REQ, 1);
               
               // Ignore any more DIT values from SHKE
               HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_FW_DBG_CTL, DTTS_WAKEUP_DISABLE_ALL);
            }
         }
         
         // Wait to complete the DIT accumulation window
         seq_wait(dit_read_wait,US);
         
         for (ch = 0; ch < NUM_CH; ch++)
         {
            if (channel>>ch & 0x1)
            {
               // Re-enable power down features
               HWIO_OUTXF2 (REG_OFFSET_DPE(ch), DPE_PWR_CTRL_0, CLK_STOP_PWR_DN_EN, PWR_DN_EN, 1, 1);
               HWIO_OUTXF (REG_OFFSET_DPE(ch), DPE_CONFIG_2, DDR_CK_ON_DBG, 0);
               HWIO_OUTXF (REG_OFFSET_DPE(ch), DPE_CONFIG_4, LOAD_ALL_CONFIG, 1);
               
               // Wait for DTTS FW to complete phy update if needed
               while((HWIO_INX (REG_OFFSET_DTTS(ch),DTTS_CFG_FW_STATUS_1) & fw_active_mask) != DTTS_FW_IDLE);
            }
         }
      }
      
      // if switching into to 1600Mhz new freq
      // Polling if DTTS image is loaded in first place.
      // IF DTTS image is loaded, then enable DTTS in acq mode.
      // poll for acq_done
      
      //before entering freq switch
      // disable DTTS and slow down SHKE timer
      // Assumed that the current frequency will be acquisiton frequency.
      
      else if (new_clk_khz >= trac_freq  )
      {
         for (ch = 0; ch < NUM_CH; ch++)
         {
            if (channel>>ch & 0x1)
            {
               // Enable DTTS FW in acquire mode
               out_dword   (REG_OFFSET_DTTS_SRAM(ch)+ACQ_TRAC_MODE,DTTS_ACQUIRE_MODE);

               // Disable power down features to keep the clock running for DIT oscillator in DRAM
               HWIO_OUTXF2 (REG_OFFSET_DPE(ch),DPE_PWR_CTRL_0,CLK_STOP_PWR_DN_EN,PWR_DN_EN,0,0);
               HWIO_OUTXF  (REG_OFFSET_DPE(ch),DPE_CONFIG_2,DDR_CK_ON_DBG,1);
               HWIO_OUTXF (REG_OFFSET_DPE(ch),DPE_CONFIG_4,LOAD_ALL_CONFIG,1);

               // Disable HW based self refresh
               BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 0, 0);
               BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 1, 0);

               // Generate bit vector to indicate ch, cs and 2 dies per channel
               for (cs = 0; cs < NUM_CS;cs++)
               {
                  if (qualified_cs >> cs & 0x1)
                  {
                     comp_bit_vec |= (1 <<(cs*NUM_DIE_PCH +NUM_DIE_PCH*NUM_CS*ch));
                  }
               }
            }
         }
         for (;comp_bit_vec!=bit_vec;)
         {
            uint32 MR18_data = 0;
            uint32 MR19_data = 0;            
            DDR_CHANNEL ch_1hot    = DDR_CH_NONE;
            DDR_CHIPSELECT cs_1hot = DDR_CS_NONE;
            
            for (ch = 0; ch < NUM_CH; ch++)
            {
               if (channel>>ch & 0x1)
               {
                  for (cs = 0; cs < NUM_CS;cs++)
                  {
                     if (qualified_cs >> cs & 0x1)
                     {
                        // Issue DIT start and wait until done
                        HWIO_OUTXF2 (REG_OFFSET_SHKE(ch), SHKE_MPC_CNTL, ISSUE_TO_RANK, MPC_START, CS_1HOT(cs), 1);
                        while (HWIO_INXF (REG_OFFSET_SHKE(ch), SHKE_MPC_CNTL, MPC_START) == 1);
                     }  
                  }   
               }   
            }

            // Wait to complete the DIT accumulation window
            seq_wait(dit_read_wait,US);
            
            // Read DIT values
            for (ch = 0; ch < NUM_CH; ch++)
            {
               if (channel>>ch & 0x1)
               {
                  ch_1hot = CH_1HOT(ch);
                  reg_offset_dtts_sram = REG_OFFSET_DTTS_SRAM(ch);
                  for (cs = 0; cs < NUM_CS;cs++)
                  {
                     if (qualified_cs >> cs & 0x1)
                     {
                        uint16 osc_cha = 0;
//                        uint16 osc_chb = 0;
                        cs_1hot = CS_1HOT(cs);
                        MR18_data = BIMC_MR_Read (ch_1hot,cs_1hot,JEDEC_MR_18);
                        MR19_data = BIMC_MR_Read (ch_1hot,cs_1hot,JEDEC_MR_19);
                        osc_cha = ((MR19_data&0x000000ff)<<8) |  (MR18_data&0x000000ff);
//                        osc_chb = ((MR19_data&0x00ff0000)>>8) | ((MR18_data&0x00ff0000)>>16);
                        if (num_samples[ch][cs][0] < max_num_samples && osc_cha != 0 && osc_cha != 0xFFFF)
                        {
                           out_dword(reg_offset_dtts_sram + CHA_OSC_ARR+(cs << 2)+(num_samples[ch][cs][0]<< 3) ,osc_cha  );
                           num_samples[ch][cs][0]++;
                           if (num_samples[ch][cs][0] == max_num_samples)
                              bit_vec |= (1 <<(cs*NUM_DIE_PCH +NUM_DIE_PCH*NUM_CS*ch));
                        }

/*                        if (num_samples[ch][cs][1] < max_num_samples && osc_chb != 0 && osc_chb != 0xFFFF)
                        {
                           out_dword(reg_offset_dtts_sram + CHB_OSC_ARR+(cs << 2)+(num_samples[ch][cs][1]<< 3) ,osc_chb);
                           num_samples[ch][cs][1]++;
                           if (num_samples[ch][cs][1] == max_num_samples)
                              bit_vec |= (2 <<(cs*NUM_DIE_PCH +NUM_DIE_PCH*NUM_CS*ch));
                        }*/
                     }  
                  }   
               }   
            }
         }
         for (ch = 0; ch < NUM_CH; ch++)
         {
            if (channel>>ch & 0x1)
            {
               // Release DTTS FW seqeuncer
               HWIO_OUTX  (REG_OFFSET_DTTS(ch),DTTS_CFG_FW_RELEASE_CTL,1);

               // Enable back power down features
               HWIO_OUTXF2 (REG_OFFSET_DPE(ch),DPE_PWR_CTRL_0,CLK_STOP_PWR_DN_EN,PWR_DN_EN,1,1);
               HWIO_OUTXF  (REG_OFFSET_DPE(ch),DPE_CONFIG_2,DDR_CK_ON_DBG,0);
               HWIO_OUTXF (REG_OFFSET_DPE(ch),DPE_CONFIG_4,LOAD_ALL_CONFIG,1);

               // Enable HW based self refresh
               BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 0, 1);
               BIMC_HW_Self_Refresh_Ctrl (ddr, ch, 1, 1);
               
               // Wait for DTTS FW to complete phy update if needed
               while((HWIO_INX (REG_OFFSET_DTTS(ch), DTTS_CFG_FW_STATUS_1) & fw_active_mask) != DTTS_FW_IDLE);
            }
         }
      }
   }

#endif

   // If ODT feature enabled
   if (ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].odt)
   {
     tWPRE_field   = (ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].MR1 & 0x04) >> 2;
     ODTLon_wrdata = ODTLon_ptr[new_RL_WL_idx][tWPRE_field];
   }
   
   //If FSP switching required
   if (curr_fsp_op != new_fsp_op)
   {
      MR13_wrdata_1 = MR13_wrdata[new_fsp_op][0];
      MR13_wrdata_2 = MR13_wrdata[new_fsp_op][1];
    curr_period_ps = CONVERT_CYC_TO_PS / curr_clk_khz;
      
      //tVRCG_DISABLE wait time calcuation. cdt_params has resolution of 100ps, multiply by 100 to convert to 1ps
      tvrcg_disable_wait_time = div_ceil( ( tVRCG_DISABLE_spec * 100), new_period_ps);

      // tFC wait time
      total_tfc_wait_time = div_ceil( ( tFC_spec * 100), curr_period_ps);
      if ( total_tfc_wait_time > 255) {
         tfc_wait_time  = (total_tfc_wait_time) >> 1;
         tfc_precise_wait_time = 1;
      }
      else {
        tfc_wait_time  = total_tfc_wait_time;
        tfc_precise_wait_time = 0;
      }


#if FREQ_SWITCH_WITH_ZQCAL_ENABLE
    tzqlat_wait_time = div_ceil( ( ddr->cdt_params.lpddr.tZQLAT * 100), new_period_ps);
#endif

   }

   for (ch = 0; ch < 2; ch++)
   {
      reg_offset_dpe = REG_OFFSET_DPE(ch);
#if FREQ_SWITCH_WITH_ZQCAL_ENABLE
   reg_offset_shke = REG_OFFSET_SHKE(ch);
#endif

   if ((channel >> ch) & 0x1)
   {
      // Program the new period
      HWIO_OUTXFI (REG_OFFSET_GLOBAL0, BIMC_MISC_GLOBAL_CSR_DDR_CHn_CLK_PERIOD, ch, PERIOD, new_period_ps);
   
      HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_16, WR_LATENCY, RD_LATENCY, wl, rl);
   
      if (ddr->extended_cdt_runtime.bimc_freq_switch[new_params_idx].odt) {
      HWIO_OUTXF (reg_offset_dpe, DPE_DRAM_TIMING_LP4_ODTLON_CNTL, LP4_ODTLON, ODTLon_wrdata);
      }
      
      //Populate RCW training results into RCW registers.
#if DSF_RCW_TRAINING_EN      
      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_TDQSCK_CTRL0, TDQSCK_BYTE0, TDQSCK_BYTE1,
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][0][0],
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][0][1]);
/*      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_TDQSCK_CTRL1, TDQSCK_BYTE2, TDQSCK_BYTE3,
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][0][2],
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][0][3]);*/
      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_RANK1_TDQSCK_CTRL0, TDQSCK_BYTE0, TDQSCK_BYTE1,
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][1][0],
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][1][1]);
/*      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_RANK1_TDQSCK_CTRL1, TDQSCK_BYTE2, TDQSCK_BYTE3,
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][1][2],
          training_data_ptr->results.rcw.bimc_tDQSCK[new_clk_idx][ch][1][3]);*/
#else
      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_TDQSCK_CTRL0, TDQSCK_BYTE0, TDQSCK_BYTE1, 0x16, 0x16);
      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_TDQSCK_CTRL1, TDQSCK_BYTE2, TDQSCK_BYTE3, 0x16, 0x16);
           
      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_RANK1_TDQSCK_CTRL0, TDQSCK_BYTE0, TDQSCK_BYTE1, 0x16, 0x16);
      HWIO_OUTXF2 (reg_offset_dpe, DPE_RCW_RANK1_TDQSCK_CTRL1, TDQSCK_BYTE2, TDQSCK_BYTE3, 0x16, 0x16);

#endif

      if (curr_DBI_en != new_DBI_en)
      {
        // setup DBI_RD flag in DPE
        HWIO_OUTXF (reg_offset_dpe, DPE_CONFIG_9, DBI_RD, new_DBI_en);
      }

      // FSP switching not required
      if  (curr_fsp_op == new_fsp_op)
      {
        // This bit enables hardware frequency switch sequence with MRWs before frequency switch
        HWIO_OUTXF  (reg_offset_dpe, DPE_CONFIG_3, HW_FREQ_SW_WITH_ZQCAL, 1);	  
        //Schedule MRW to be executed before traffic stall
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_0, W_ADDR, W_DATA, JEDEC_MR_39, (new_clk_khz/10000));  //MR39 to indicate target freq
		
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_0, W_ADDR, W_DATA, JEDEC_MR_1, MR1_wrdata);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_1, W_ADDR, W_DATA, JEDEC_MR_2, mr2_wr_val);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_2, W_ADDR, W_DATA, JEDEC_MR_3, MR3_wrdata);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_3, W_ADDR, W_DATA, JEDEC_MR_11, MR11_wrdata);		
        HWIO_OUTX   (reg_offset_dpe, DPE_MRW_FREQ_SWITCH, 0x0001000F);
      }
      else // FSP switching required
      {
#if FREQ_SWITCH_NO_ZQCAL_ENABLE
        // This bit enables hardware frequency switch sequence with MRWs before frequency switch
        HWIO_OUTXF  (reg_offset_dpe, DPE_CONFIG_3, HW_FREQ_SW_WITH_ZQCAL, 1);

        //Schedule MRW to be executed before traffic stall
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_0, W_ADDR, W_DATA, JEDEC_MR_13, MR13_wrdata_1);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_1, W_ADDR, W_DATA, JEDEC_MR_39, (new_clk_khz/10000));  //MR39 to indicate target freq		

        //wait for tFC
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_0, tfc_wait_time);
  
        // 2^(tfc_precise_wait_time) plus 'tfc_wait_time' gives the total tFC wait time in DPE clock cycles. This is because 'WAIT_TIME_0' is 8bit max
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_WAIT_TYPE, WAIT_PRECISE_0, tfc_precise_wait_time);

        //Schedule MRW to be executed after clock switch and before traffic unstall
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_0, W_ADDR, W_DATA, JEDEC_MR_13, MR13_wrdata_2);
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_0, tvrcg_disable_wait_time);

        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_1, W_ADDR, W_DATA, JEDEC_MR_1, MR1_wrdata);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_2, W_ADDR, W_DATA, JEDEC_MR_2, mr2_wr_val);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_3, W_ADDR, W_DATA, JEDEC_MR_3, MR3_wrdata);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_4, W_ADDR, W_DATA, JEDEC_MR_11, MR11_wrdata);		
        HWIO_OUTX   (reg_offset_dpe, DPE_MRW_FREQ_SWITCH, 0x0003001F);


#endif

#if FREQ_SWITCH_WITH_ZQCAL_ENABLE
        HWIO_OUTXF  (reg_offset_dpe, DPE_CONFIG_3, HW_FREQ_SW_WITH_ZQCAL, 1);
        // set zq cal mode as latch only
        HWIO_OUTXF  (reg_offset_shke, SHKE_PERIODIC_ZQCAL_1, ZQCAL_MODE, 2);

        // Software Loop wait for 1 us, seq_wait(uint32 time_value, SEQ_TimeUnit time_unit)
        // time_unit can be us/ms/sec
        seq_wait(1, US);

        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_0,  W_ADDR, W_DATA, JEDEC_MR_3, MR3_wrdata);
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_0, 0xD);
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_0, XO_DIV6_EN, 1);
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_WAIT_TYPE, WAIT_TYPE_1, 1);

        //Schedule MRW to be executed during traffic stall(post stall and before clock switch)
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_2,  W_ADDR, W_DATA, JEDEC_MR_13, MR13_wrdata_1);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_3, W_ADDR, W_DATA, JEDEC_MR_39, (new_clk_khz/10000));  //MR39 to indicate target freq
        //wait for tFC
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_2, tfc_wait_time);
        // 2^(tfc_precise_wait_time) plus 'tfc_wait_time' gives the 'total tFC wait time' in DPE clock cycles. This is because 'WAIT_TIME_2' is 8bit max
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_BEFORE_FREQ_SWITCH_WAIT_TYPE, WAIT_PRECISE_2, tfc_precise_wait_time);

        //Schedule MRW to be executed after clock switch and before traffic unstall
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_0, W_ADDR, W_DATA, JEDEC_MR_13, MR13_wrdata_2);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_0, WAIT_TIME_1, tvrcg_disable_wait_time, tzqlat_wait_time);
        HWIO_OUTXF  (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_WAIT_TYPE, WAIT_TYPE_1, 2);

        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_2, W_ADDR, W_DATA, JEDEC_MR_1, MR1_wrdata);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_3, W_ADDR, W_DATA, JEDEC_MR_2, mr2_wr_val);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_4, W_ADDR, W_DATA, JEDEC_MR_3, MR3_wrdata);
        HWIO_OUTXF2 (reg_offset_dpe, DPE_MRW_AFTER_FREQ_SWITCH_5, W_ADDR, W_DATA, JEDEC_MR_11, MR11_wrdata);		
        HWIO_OUTX   (reg_offset_dpe, DPE_MRW_FREQ_SWITCH, 0x000F003F);
#endif
      }

      // Choose tMRD based on freq since DPE supports only cycle based CSR.
      // tMRD = max(14ns, 10nCK). For freq less than 714.286MHz (1.4ns), use 10 cycles.
      // For freq from 714.286 to 1866MHz, use (14ns/0.536) = 27 cycles.
      if (new_clk_khz < TMRW_FREQ_THRESHOLD) {
         HWIO_OUTXF2 (reg_offset_dpe, DPE_TIMER_2, TMRW_MSB, TMRW, 0x0, 0xA);
      }
      else {
         HWIO_OUTXF2 (reg_offset_dpe, DPE_TIMER_2, TMRW_MSB, TMRW, 0x1, 0xB);
      }
      
      //update DPE CONFIG_8 based on new_freq_index
      HWIO_OUTX (reg_offset_dpe, DPE_CONFIG_8, dpe_config_8[new_clk_idx]);
      
      //Update clock cycles before PD and SR exit based on the clocking mode
#if PHY_LVDS_GATING_DELAY
      if(ddr->misc.chip_version >= 0x0200) {
         if (ddr->misc.clock_plan[new_clk_idx].clk_mode == 0)
         {
             HWIO_OUTX (reg_offset_dpe, DPE_TIMER_3, dpe_timer_3[0]);
             HWIO_OUTX (reg_offset_dpe, DPE_DRAM_TIMING_13, dpe_timing_13[0]);
         }
         else 
         {
             HWIO_OUTX (reg_offset_dpe, DPE_TIMER_3, dpe_timer_3[1]);
             HWIO_OUTX (reg_offset_dpe, DPE_DRAM_TIMING_13, dpe_timing_13[1]);      
         }
      }
#endif
    }
  }
  
  return TRUE;
}


//================================================================================================//
// BIMC POST CLOCK SWITCH SEQUENCE
//================================================================================================//
boolean BIMC_Post_Clock_Switch (DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
  uint8 ch = 0;
  
  
#if DSF_PERIODIC_TRAINING_EN
  uint32 new_clk_khz;
  uint32 curr_clk_khz;
  uint8 new_clk_idx;
  training_data *training_data_ptr;
  uint8  trac_ndx    = 0;
  uint32 trac_freq   = 0;

  training_data_ptr  = (training_data *)(&ddr->flash_params.training_data);
  trac_ndx    = training_data_ptr->results.dit.dit_trac_ndx;
  if (trac_ndx < ddr->misc.ddr_num_clock_levels)
  {
     trac_freq   = ddr->misc.clock_plan[trac_ndx].clk_freq_in_khz;
  }
  new_clk_khz = ddr->misc.new_clk_in_kHz;
  curr_clk_khz = ddr->misc.current_clk_in_kHz;
	
	
  // get the clk index in clock plan
  for (new_clk_idx = 0; new_clk_idx < ddr->misc.ddr_num_clock_levels; new_clk_idx++)
  {
      if (new_clk_khz <= ddr->misc.clock_plan[new_clk_idx].clk_freq_in_khz)
      break;
  }
	
 // if (ddr->misc.clock_plan[new_clk_idx].clk_mode == 1)
	if ((new_clk_idx == trac_ndx) || (new_clk_idx == (trac_ndx - 1)))
     {
       if ((ddr->misc.platform_id == STARLORD_PLATFORM_ID) && (ddr->misc.chip_version == 0x0100))
        {
	      channel = DDR_CH1;
        }
     }
  
#endif


  for (ch = 0; ch < 2; ch++)
  {
    if ((channel >> ch) & 0x1)
    {
      //Poll on the status bit to track MRW_AFTER_FREQ_SWITCH completion
      while (HWIO_INXF (REG_OFFSET_DPE(ch), DPE_MEMC_STATUS_0, FREQSW_IN_PROGRESS));

      //Reset 'after freq switch wait time 0' to 0
      HWIO_OUTXF  (REG_OFFSET_DPE(ch), DPE_MRW_AFTER_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_0, 0);
      // This bit enables hardware freq switch sequence with MRWs before frequency switch
      HWIO_OUTXF  (REG_OFFSET_DPE(ch), DPE_CONFIG_3, HW_FREQ_SW_WITH_ZQCAL, 0);
#if FREQ_SWITCH_WITH_ZQCAL_ENABLE
      // Enable Periodic ZQCAL for both ranks
      HWIO_OUTXF  (REG_OFFSET_SHKE(ch), SHKE_PERIODIC_ZQCAL, RANK_SEL, 3);
  
      //Reset 'after freq switch wait time 1' to 0
      HWIO_OUTXF  (REG_OFFSET_DPE(ch), DPE_MRW_AFTER_FREQ_SWITCH_WAIT_TIME, WAIT_TIME_1, 0);
#endif


#if DSF_PERIODIC_TRAINING_EN
      // Check if DTTS Imem and Dmem are loaded and if tracking index is provided by boot training
      if (HWIO_DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn_INI(REG_OFFSET_DTTS(ch),15) == 1 && trac_ndx != 0xFF)
      {
         if (curr_clk_khz >= trac_freq)
         {
            // Deassert flag in DTTS Dmem to indicate a freq switch is complete
            out_dword (REG_OFFSET_DTTS_SRAM(ch)+FREQ_SWITCH_REQ,0);
         }
         if (new_clk_khz >= trac_freq)
         {
            // Enable interval timer for periodic MPC/MR18/MR19
            HWIO_OUTXF (REG_OFFSET_SHKE(ch), SHKE_INTERVAL_TIMER_CNTL_1, INTERVAL_TIMER, 1);
            
            // Enable tracking mode in DTTS FW
            out_dword(REG_OFFSET_DTTS_SRAM(ch)+ACQ_TRAC_MODE,DTTS_TRACKING_MODE);
#if DSF_PERIODIC_TRAINING_ALGO_DEBUG_EN == 0
            HWIO_OUTX  (REG_OFFSET_DTTS(ch),DTTS_CFG_FW_DBG_CTL,DTTS_WAKEUP_ENABLE_SHKE_ONLY);
#endif
         }
      }
#endif

    }
  }
#if FREQ_SWITCH_WITH_ZQCAL_ENABLE
  HWIO_OUTXF  (REG_OFFSET_SHKE(0), SHKE_PERIODIC_ZQCAL_1, ZQCAL_MODE, 3);
#endif

  // Reset manual_1 wait timer to 0
  BIMC_Wait_Timer_Setup (channel, WAIT_XO_CLOCK, 0x00);

  return TRUE;
}



