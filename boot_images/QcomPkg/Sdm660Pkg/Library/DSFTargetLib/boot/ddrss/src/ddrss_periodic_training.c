

/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header:
$DateTime:
$Author:
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include "dtts_load_ram.h"

#define PHY_DQ_BYTE_MAPPING_SWAP             1
#define NUM_SLABS                            (FINE_STEPS_PER_COARSE * 2) //12
#define NUM_DIT_FREQS                        2
#define DIT_CNT_1SEC                         32000
#define DIT_MRRD_CNT_1_MSEC                  3200

boolean HAL_DDR_Periodic_Training(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 mode)
{
   uint8  ch = 0;
   uint8  cs = 0;
   uint8 max_dit_step = 0;
   uint32 reg_offset_dtts_sram  = 0;
   uint32 reg_offset_shke  = 0;
   uint32 reg_offset_dtts  = 0;
   uint32 reg_offset_phy   = 0;
   uint8 dq = 0;
   DDR_CHIPSELECT qualified_cs = DDR_CS_NONE;
   uint8 freq_idx = 0;
   uint16 dtts_wakeup_interval = 0;
   uint16 dit_read_cnt = 0;
   uint8 acq_ndx = 0;
   uint8 trac_ndx = 0;
   uint8 trac_prfs_index = 0;
   uint8 max_num_samples = 4;
   training_data *training_data_ptr;
   uint32 dit_runtime_count = 0;
   uint16 MR23_value        = 0;
   uint32 acq_freq     = 0;
   uint32 track_freq   = 0;
   uint8 threshold = 0;
   
   
   training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
   acq_ndx    = training_data_ptr->results.dit.dit_acq_ndx;

   trac_ndx    = training_data_ptr->results.dit.dit_trac_ndx;
   
	if (acq_ndx < MAX_NUM_CLOCK_PLAN)
	{
		acq_freq   = ddr->misc.clock_plan[acq_ndx].clk_freq_in_khz;
		track_freq = ddr->misc.clock_plan[trac_ndx].clk_freq_in_khz;
	}
	
   trac_prfs_index = DDRSS_Get_Freq_Index (ddr, track_freq);
   
   //calculate SHKE INTERVAL_TIMER_CNTL_1 threshold
   threshold = (CONVERT_CYC_TO_PS / track_freq)/100;
   
   max_dit_step = training_data_ptr->results.dit.dit_fine_step_limit;
   max_num_samples =training_data_ptr->results.dit.dit_loop_count;
   dtts_wakeup_interval  = DIT_CNT_1SEC/ ((max_num_samples+1)*training_data_ptr->results.dit.dit_interval_per_sec) ;
   dit_runtime_count = training_data_ptr->results.dit.dit_runtime_count;
   if (dit_runtime_count < 2048)
   {
        MR23_value = dit_runtime_count / 16;
   }
   else
   {
     if (dit_runtime_count == 2048)
       MR23_value = 0x40;
     else if (dit_runtime_count == 4096)
       MR23_value = 0x80;
     else if (dit_runtime_count == 8196)
       MR23_value = 0xC0;
   }

   dit_read_cnt =  0x6+(dit_runtime_count*(DIT_MRRD_CNT_1_MSEC))/acq_freq;
   
   if (acq_ndx != 0xFF)
   {

       { // Loading dtts firmware image
          for (ch = 0; ch < 2; ch++)
          {
             if ((channel >> ch) & 0x1)
             {
                reg_offset_phy  = REG_OFFSET_DDR_PHY_CH(ch);
                reg_offset_dtts = REG_OFFSET_DTTS(ch);
                qualified_cs = (DDR_CHIPSELECT) (chip_select & (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
                BIMC_MR_Write (CH_1HOT(ch),qualified_cs, JEDEC_MR_23,MR23_value);
                reg_offset_dtts_sram = REG_OFFSET_DTTS_SRAM(ch);
                //Load DTTS data SRAM
                dtts_load_dsram(reg_offset_dtts_sram,ch);
                // Load DTTS instruction SRAM
                dtts_load_isram(reg_offset_dtts_sram+0x2000,ch);
                out_dword(reg_offset_dtts_sram+ACQ_TRAC_MODE,DTTS_TRACKING_MODE);
                out_dword(reg_offset_dtts_sram+NUM_SLAB,NUM_SLABS);
#ifdef DSF_PERIODIC_TRAINING_ALGO_DEBUG_EN
                out_dword(reg_offset_dtts_sram+CDC_UPDATE_FORCED,1);
#endif
                out_dword(reg_offset_dtts_sram+PHY_CSR_CH_OFFSET,REG_OFFSET_DDR_PHY_CH(ch));
#if DSF_DTTS_HANG_EN
                out_dword(reg_offset_dtts_sram+HANG_EN,1);

#endif

                // Progrmaing the offsets for the functional /fpm cdc.
                //(4*FPM_PERF_BAND_1600)
#if PHY_DQ_BYTE_MAPPING_SWAP
                // DQ2 -> DQ3
              
                switch(trac_prfs_index)
                {
                case 6 :
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_6_CTL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_6_CTL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                    break;
                case 7 :
                default :
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_7_CTL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_7_CTL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                    break; 
                }

                out_dword(reg_offset_dtts_sram+FUNCCDCREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CMCDCWR_CTL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+FUNCCDCREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CMCDCWR_CTL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYBISCREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_BISC_CTRL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYBISCREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_BISC_CTRL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYUPDREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_UPDATE_INTF_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYUPDREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_UPDATE_INTF_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
#else

                switch(trac_prfs_index)
                {
                case 6 :
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_6_CTL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_6_CTL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                    break;
                case 7 :
                default :
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_7_CTL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                    out_dword(reg_offset_dtts_sram+FPMBASEREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CDCEXT_WR_7_CTL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                    break;
                }

                out_dword(reg_offset_dtts_sram+FUNCCDCREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CMCDCWR_CTL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+FUNCCDCREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_CMCDCWR_CTL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYBISCREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_BISC_CTRL_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYBISCREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_BISC_CTRL_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYUPDREG+ 0,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_UPDATE_INTF_CFG_ADDR(DQ0_DDR_PHY_OFFSET)));
                out_dword(reg_offset_dtts_sram+PHYUPDREG+ 4,reg_offset_phy+(HWIO_DDR_PHY_DDRPHY_UPDATE_INTF_CFG_ADDR(DQ1_DDR_PHY_OFFSET)));
#endif

                HWIO_DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn_OUTI(reg_offset_dtts,15,1);
                HWIO_DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn_OUTI(reg_offset_dtts,0,1);

             }
          }
       } // Loading dtts firmware image
// Populating the CDC values.

       for (ch = 0; ch < 2; ch++)
       {

          uint32 cdc_waddr = 0 ;
          uint32 prev_cdc_waddr = 0;
          reg_offset_dtts_sram = REG_OFFSET_DTTS_SRAM(ch);
          reg_offset_shke = REG_OFFSET_SHKE(ch);
          cdc_waddr = reg_offset_dtts_sram+BOOT_CDC;
          prev_cdc_waddr = reg_offset_dtts_sram+PREV_CDC;
          if ((channel >> ch) & 0x1)
          {
             qualified_cs = (DDR_CHIPSELECT) (chip_select & (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
             for (freq_idx = trac_prfs_index-1; freq_idx <= trac_prfs_index; freq_idx++) //TODO
             {
                for (cs = 0; cs < 2; cs++)
                {
                    if ((qualified_cs>> cs) & 0x1)
                    {
                        for (dq = 0; dq < NUM_DQ_PCH; dq++)
                        {
                            uint8 coarse_cdc = 0;
                            uint8 fine_cdc = 0;
                            coarse_cdc=training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_idx][ch][cs][dq];
                            fine_cdc  =training_data_ptr->results.wr_dqdqs.fine_cdc[freq_idx][ch][cs][dq] - max_dit_step;
                            out_dword(cdc_waddr,(fine_cdc << 5)|coarse_cdc);
                            out_dword(prev_cdc_waddr,(fine_cdc << 5)|coarse_cdc);
                            out_dword(prev_cdc_waddr-PREV_CDC+PREV_CDC_FINE_STEP,max_dit_step);
                            cdc_waddr += 4;
                            prev_cdc_waddr += 4;
                        }
						cdc_waddr += 8;
                           prev_cdc_waddr += 8;
                    }
                    else
                    {
                        cdc_waddr += 16;
                        prev_cdc_waddr += 16;

                    }
                }
             }
          }
       }


       for (ch = 0; ch < 2; ch++)
       {
          if ((channel >> ch) & 0x1)
          {
             qualified_cs = (DDR_CHIPSELECT) (chip_select & (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
             reg_offset_dtts_sram = REG_OFFSET_DTTS_SRAM(ch);
             reg_offset_shke = REG_OFFSET_SHKE(ch);
             reg_offset_dtts = REG_OFFSET_DTTS(ch);
             HWIO_OUTXF2 (REG_OFFSET_SHKE(ch), SHKE_INTERVAL_TIMER_CNTL, INTERVAL_TIMER_TRIGGER,INTERVAL_TIMER_READ,dtts_wakeup_interval,dit_read_cnt);
             HWIO_OUTXF  (REG_OFFSET_SHKE(ch), SHKE_INTERVAL_TIMER_CNTL_1, THERSHOLD, threshold);
             out_dword((reg_offset_dtts_sram+MAX_FINE_STEPS_FROM_BOOT),max_dit_step);
             if (qualified_cs ==  DDR_CS_BOTH) 
             {
                out_dword(reg_offset_dtts_sram+NUM_RANK,2);
             }
             else 
             {
                out_dword(reg_offset_dtts_sram+NUM_RANK,1);
             }

             out_dword(reg_offset_dtts_sram+TOT_SAMPLES,max_num_samples);
             DDRSS_Periodic_Training_load_dit_struct_to_dtts(ddr,ch,qualified_cs);
             HWIO_DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn_OUTI(REG_OFFSET_DTTS(ch),1,1);
             //Idle pattern when DTTS has the bus.
             HWIO_DTTS_CFG_PXI_CA_CMD_TABLEn_OUTI(REG_OFFSET_DTTS(ch),16,0x00100100);
             HWIO_DTTS_CFG_PXI_CA_CMD_TABLEn_OUTI(REG_OFFSET_DTTS(ch),17,0x00100100);
             HWIO_DTTS_CFG_PXI_CA_CMD_TABLEn_OUTI(REG_OFFSET_DTTS(ch),18,0x00100100);
             HWIO_DTTS_CFG_PXI_CA_CMD_TABLEn_OUTI(REG_OFFSET_DTTS(ch),19,0x00100100);
             HWIO_DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE2_n_OUTI(REG_OFFSET_DTTS(ch),31, 0x1FE01F0C);
             // Enabling the SHKE DTTS wakeup after image load
#ifdef DSF_PERIODIC_TRAINING_ALGO_DEBUG_EN
             out_dword(reg_offset_dtts_sram+ALGO_DEBUG,1);
#else
//        out_dword(reg_offset_dtts_sram+DISABLE_CDC_UPD,1);
             HWIO_OUTXF (reg_offset_shke, SHKE_INTERVAL_TIMER_CNTL_1, RANK_EN,qualified_cs);
#endif
          }
       }
   
   } // if (acq_ndx != 0xFF)
   
   // Save the PXI config registers that do not get retained   
#if DSF_PERIODIC_TRAINING_EN
   // The DTTS PXI control settings that do not get retained during power collapse.  Save them in an unused area
   //    of the DTTS DSRAM, so they can be restored after power is restored.
   for (ch = 0; ch < NUM_CH; ch++)
   {
          // Idle pattern when DTTS has the bus.
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 8, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_CMD_TABLEn, 16));
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 9, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_CMD_TABLEn, 17));
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 10, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_CMD_TABLEn, 18));
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 11, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_CMD_TABLEn, 19));
                               
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 12, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0));
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 13, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 1));
                               
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 14, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE2_n, 31));
                               
          // Flag to ensure DTTS Imem and Dmem is loaded correctly.
          HWIO_OUTXI(REG_OFFSET_DTTS_SRAM(ch), DTTS_SRAM_DTTS_DSRAM_WORDn, 15, 
                               HWIO_INXI(REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 15));
   }
#endif



   return TRUE;
}



boolean DDRSS_Periodic_Training_load_dit_struct_to_dtts(DDR_STRUCT *ddr,    uint8  ch , DDR_CHIPSELECT qualified_cs)
{
   uint8  cs = 0;
   uint8 freq_idx = 0;
   uint8 slab_ndx = 0;
   uint8 die_ndx = 0;
   uint32 reg_offset_dtts_sram  = 0;

   uint32 boot_osc_value_cha = 0;
   uint32 boot_osc_value_chb = 0;
   uint32 temp_addr = 0;
   uint32 clk_freq  = 0;
   uint16 dit_slope[NUM_DIT_COUNT] = {0};

   reg_offset_dtts_sram = REG_OFFSET_DTTS_SRAM(ch);


   for (cs = 0; cs < 2; cs++)
     {
       if ((qualified_cs>> cs) & 0x1)
         {
           for (freq_idx = 0; freq_idx < NUM_DIT_FREQS;freq_idx++) //TODO
             {
               clk_freq = ddr->misc.clock_plan[ddr->misc.ddr_num_clock_levels-NUM_DIT_FREQS+freq_idx].clk_freq_in_khz;


               for(die_ndx = 0;die_ndx < NUM_DIE_PCH;die_ndx++)
               {
                   DDRSS_DIT_Slope(ddr,ch,cs,die_ndx,clk_freq,dit_slope);
                   for (slab_ndx = 0;slab_ndx < NUM_SLABS;slab_ndx++)
                   {
                       //temp_addr = reg_offset_dtts_sram+OSC_SLAB+ (freq_idx * 4*NUM_DIE_PCH* NUM_CS*16)+(cs*4*16*NUM_DIE_PCH)+(die_ndx*4*16)+(4*slab_ndx);
					   temp_addr = reg_offset_dtts_sram+OSC_SLAB+ (freq_idx * 4*2* NUM_CS*16)+(cs*4*16*2)+(die_ndx*4*16)+(4*slab_ndx);
                       out_dword( temp_addr, dit_slope[(NUM_SLABS-1)-slab_ndx] );
                   }
                   if (die_ndx == 0)
                   {
                      boot_osc_value_cha = ( dit_slope[4] + dit_slope[5] )/ 2;
                   }
                   else{
                      boot_osc_value_chb = ( dit_slope[4] + dit_slope[5] )/ 2;
                   }

               }
               temp_addr = reg_offset_dtts_sram+BOOT_OSC_ARR  + (freq_idx * 4* NUM_CS) + (4*cs);
               out_dword((temp_addr), (boot_osc_value_chb << 16)|boot_osc_value_cha);
             }
         }
     }
   return TRUE;
}
