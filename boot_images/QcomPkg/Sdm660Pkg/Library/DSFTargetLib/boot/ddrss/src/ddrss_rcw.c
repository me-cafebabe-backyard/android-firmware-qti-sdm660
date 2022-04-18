/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_rcw.c#10 $
$DateTime: 2018/01/31 04:21:03 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"


void DDRSS_rcw (DDR_STRUCT *ddr,
                uint8 ch,
                uint8 cs,
                PHY_BUS dq,
                training_params_t *training_params_ptr,
                uint8 rcw_start_clk_idx,
                uint8 rcw_clk_idx,
                uint8 low_speed_clk_idx) 
{

   uint8   all_found        = 0;
   uint8   num_half_cycle   = 0;
   uint8   loop_cnt         = 0;
   uint8   max_coarse_delay = 0;
   uint8   max_fine_delay   = 0;
   
   uint8   rcw_training_enable[NUM_DQ_PCH] = {1,1};
   uint8   byte_done[NUM_DQ_PCH]           = {0,0};
   uint8   byte_not_done[NUM_DQ_PCH]       = {1,1};   
   uint8   byte_lane                  = 0;
   uint32  dq0_ddr_phy_base           = 0;
   uint8   bit                        = 0;

   uint32 dpe_config_11              = 0;  
   uint32 pre_rcw_training_prfs      = 0;
   uint32 pre_RD_CDC				=0; 
   uint32 hprx_en_mprx_dis_prfs      = 0;
  uint32 total_ddr_size=0;   
   loop_cnt          = training_params_ptr->rcw.max_loopcnt;
   max_coarse_delay  = training_params_ptr->rcw.max_coarse_cdc;
   max_fine_delay    = training_params_ptr->rcw.max_fine_cdc;
       
    // Read current PWRS setting
    pre_rcw_training_prfs = HWIO_INX ((REG_OFFSET_DDR_PHY_CH(0) + DQ0_DDR_PHY_OFFSET), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG);
    
	pre_RD_CDC = HWIO_INX ((REG_OFFSET_DDR_PHY_CH(0) + DQ0_DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CDCEXT_RD_4_CTL_CFG);  
	
    // Disable MPRX & enable HPRX
    hprx_en_mprx_dis_prfs = pre_rcw_training_prfs;
    hprx_en_mprx_dis_prfs &= ~((1 << 7) | (1 << 8) | (1 << 10)); // Clear bits 7, 8, and 10
    hprx_en_mprx_dis_prfs |= ((1 << 9) | (1 << 11) | (1 << 12)); // Set bits 9, 11, and 12
    
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;   
    
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {
      // Turn off IO qualifier
      HWIO_OUTXF  ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_4_CFG, LPDDR4_MODE, 0);
      
      // Disable MPRX & enable HPRX
      HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG, hprx_en_mprx_dis_prfs);

      HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
            DDR_PHY_DDRPHY_PAD_CNTL_0_CFG,         
            PULL_N_DQS,                 
            0x3); 
      HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
            DDR_PHY_DDRPHY_PAD_CNTL_0_CFG,         
            PULL_DQS,                 
            0x1); 
      
      HWIO_OUTX  ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CDCEXT_RD_4_CTL_CFG, 0); // setting RD CDC to 0 to remove offset for RCW training 
      
	  
	  
	  
      for(bit = 0; bit < PINS_PER_PHY; bit++)
      {
            DDR_PHY_hal_cfg_local_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                          LOCAL_VREF_MID_VALUE,
                                          cs, 
                                          bit);
      } 
      
          //enable single ended DQS HPRX receiver
      HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
          DDR_PHY_DDRPHY_PAD_DQS_1_CFG,
          DQS_PAD_RFU,
          0x1); 
    }

     
   //store original value, will restore back when exiting RCW  
 dpe_config_11 = HWIO_INX (REG_OFFSET_DPE(ch), DPE_CONFIG_11); 
   
   //set PHY_HIGH_FREQ_OFFSET=0 and reduce RCW enabling threshold before starting the RCW training 
 HWIO_OUTXF(REG_OFFSET_DPE(ch), DPE_CONFIG_11,PHY_HIGH_FREQ_OFFSET, 0x0); //0x3

 HWIO_OUTXF(REG_OFFSET_DPE(ch),DPE_RCW_CTRL_1,PHY_RDDATA_EN_ASSERT_ADD_CYC_HF, 0x1);
 HWIO_OUTXF(REG_OFFSET_DPE(ch),DPE_RCW_RANK1_CTRL,PHY_RDDATA_EN_ASSERT_ADD_CYC_HF, 0x1);

 // Load all the calculated settings into DPE actual registers
 HWIO_OUTXF(REG_OFFSET_DPE(ch), DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1); 
 
    // Frequency switch to load settings
    ddr_external_set_clk_speed (ddr->misc.clock_plan[rcw_clk_idx].clk_freq_in_khz);
 
   
    //Enable PHY for RCW training ,and set register
    for (num_half_cycle =  0; num_half_cycle <= 8; num_half_cycle = num_half_cycle+2)  
    {
        //ddr_printf ("HALF CYCLE LOOP : num_half_cycle = %d, all_found =  %d\n",num_half_cycle, all_found);
        if (all_found == 0) 
        {
            //CC num_half_cycle = 1;
            if (num_half_cycle == 1)
            set_rcw_enable (rcw_training_enable, num_half_cycle, ch, dq);
            else
            set_rcw_enable (byte_not_done, num_half_cycle, ch, dq);
            
            //Initialize fine delay to zero
            set_rcw_cdc_delay(0, RCW_FINE_DELAY, HP_MODE, ch, CS_INX(DDR_CS0), byte_not_done, dq);
            
            //STEP THROUGH ALL COARSE CDC DELAYS
            cdc_delay_search (loop_cnt, max_coarse_delay, max_fine_delay, RCW_COARSE_DELAY,  &all_found, ch, cs, byte_done, byte_not_done, num_half_cycle, dq);
            
            //When reach max coarse delay and NOT Found, fine delay sesarch to
            //extend CDC delay
            if (! all_found) {
#if DSF_RCW_TRAINING_LOG
             //ddr_printf (DDR_NORMAL,"EXTENDED FINE DELAY SEARCH : num_half_cycle = %d\n",num_half_cycle);
#endif
               cdc_delay_search (loop_cnt, max_coarse_delay, max_fine_delay, RCW_FINE_DELAY, &all_found, ch, cs,  byte_done, byte_not_done,num_half_cycle, dq) ;
            }
        }
    }
if(! all_found)
{
#if DSF_RCW_TRAINING_LOG
   //ddr_printf (DDR_NORMAL,"Channel %d and rank %d is a fail\n", ch, cs); 
#endif
}
   DDRSS_bimc_rcw_start_delay_write_flash_params(ddr, ch, cs, dq, training_params_ptr, rcw_start_clk_idx, rcw_clk_idx);
   
   //restore back PHY_HIGH_FREQ_OFFSET before exiting RCW
 HWIO_OUTX (REG_OFFSET_DPE(ch), DPE_CONFIG_11, dpe_config_11);

   HWIO_OUTXF(REG_OFFSET_DPE(ch),DPE_RCW_CTRL_1,PHY_RDDATA_EN_ASSERT_ADD_CYC_HF, 0x0);
   HWIO_OUTXF(REG_OFFSET_DPE(ch),DPE_RCW_RANK1_CTRL,PHY_RDDATA_EN_ASSERT_ADD_CYC_HF, 0x0);

 HWIO_OUTX  (REG_OFFSET_DPE(ch), DPE_CONFIG_4, 1); 
	// Figure out how much DDR we actually have.
    total_ddr_size = ddr->ddr_size_info.ddr0_cs0_mb
                        + ddr->ddr_size_info.ddr0_cs1_mb
                        + ddr->ddr_size_info.ddr1_cs0_mb
                        + ddr->ddr_size_info.ddr1_cs1_mb;
      for(byte_lane = 0; byte_lane < dq; byte_lane++)      
        {
			//if(ddr->misc.platform_id == STARLORD_PLATFORM_ID)
			if(ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4)
			{ 
				//For all Hynix 4GB devices, dont disable weak pulls (WA based on SLT/RMA issues)
				//if((((ddr->detected_ddr_device[0].manufacture_name == HYNIX)&&(total_ddr_size==0x1000)))==0)
				//{
					//Disable weak pulls for DQS
					  HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
							DDR_PHY_DDRPHY_PAD_CNTL_0_CFG,         
							PULL_N_DQS,                 
							0x0); 
					  HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
							DDR_PHY_DDRPHY_PAD_CNTL_0_CFG,         
							PULL_DQS,                 
							0x0);
				//}
			}
         //disable single ended DQS HPRX  
          HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),     
                DDR_PHY_DDRPHY_PAD_DQS_1_CFG,         
                DQS_PAD_RFU,                 
                0x0);
        }

   rcw_training_enable[0] = 1;
   rcw_training_enable[1] = 1;
   set_rcw_enable (rcw_training_enable, 0/*num_half_cycle*/, ch, dq); //clear half/full cycle to zero

   rcw_training_enable[0] = 0;
   rcw_training_enable[1] = 0;
   set_rcw_enable (rcw_training_enable, 0/*num_half_cycle*/, ch, dq); //disable RCW training

   set_rcw_cdc_delay(0, RCW_FINE_DELAY, HP_MODE, ch, CS_INX(DDR_CS0), byte_not_done, dq);    //clear fine delay to zero
   set_rcw_cdc_delay(0, RCW_COARSE_DELAY, HP_MODE, ch, CS_INX(DDR_CS0), byte_not_done, dq);  //clear coarse delay to zero
   
   // Restore the IO Qualifier
   for(byte_lane = 0; byte_lane < dq; byte_lane++)
   {
       HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_HI_CFG, pre_rcw_training_prfs);	
       HWIO_OUTXF  ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_RCWPREAMBEXT_TOP_4_CFG, LPDDR4_MODE, 1);
	   HWIO_OUTX  ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_CDCEXT_RD_4_CTL_CFG, pre_RD_CDC); // setting RD CDC to back to original value
   } 

   // Perform a dummy MR read to workaround read hang due to RCW training
   ddr_external_set_clk_speed (ddr->misc.clock_plan[low_speed_clk_idx].clk_freq_in_khz);
   BIMC_MR_Read (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_5);

   // Set the current training frequency 
   ddr_external_set_clk_speed (ddr->misc.clock_plan[rcw_clk_idx].clk_freq_in_khz);
}

//-------------------------------------------------------------------
// RCW CDC COARSE AND FINE DELAY SEARCH
//-------------------------------------------------------------------
// loop_cnt         : number fo time to run read test
// coarse_fine_sel  : select to run coarse delay sweep or fine delay sweep
// all_found        : all_byte_done = 1, search finished, 0: not finish
// ch               : pass from top, 1 or 0

void cdc_delay_search (uint8 loop_cnt, uint8 max_coarse_delay, uint8 max_fine_delay, uint8 coarse_fine_sel,  uint8 *all_found, uint8 ch, uint8 cs, uint8 *byte_done, uint8 *byte_not_done, uint8 num_half_cycle, PHY_BUS dq) {

   uint8    max_delay;
   uint8    byte_zero_cnt[NUM_DQ_PCH]   = {0,0};
   uint8     byte_one_cnt[NUM_DQ_PCH]   = {0,0};
   uint8    byte_indx, lp, indx;
   uint8    delay ;

   if (coarse_fine_sel == 1)
       max_delay = max_coarse_delay;
   else
       max_delay = max_fine_delay;

   for (delay = 0; delay < max_delay; delay++)  {

   //---------------------------------------------------------------------
   //  Set CDC coarse delay
   //---------------------------------------------------------------------
#if DSF_RCW_TRAINING_LOG
   //ddr_printf ("CDC_DELAY_SEARCH:  FORLOOP delay =   %d, max_delay = %d\n ", delay, max_delay);
#endif
   set_rcw_cdc_delay(delay, coarse_fine_sel, HP_MODE, ch,  CS_INX(DDR_CS0), byte_not_done, dq);

   //clear counters
   for (indx = 0; indx < dq ; indx++) {
     byte_one_cnt[indx] = 0;
     byte_zero_cnt[indx] = 0;
   }

   for (lp = 0; lp < loop_cnt; lp++)  {
     //BIMC FUNCTION CALL TO SEND MRR READ to DRAM
     BIMC_MR_Read (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_5);

     //Read RCW_MON status
     read_rcw_status (byte_one_cnt, byte_zero_cnt, dq, ch);
   }

     //Check read result
     for (byte_indx = 0; byte_indx < dq; byte_indx++) {
#if DSF_RCW_TRAINING_LOG
      //ddr_printf (DDR_NORMAL,"CDC_DELAY_SEARCH: :check result byte_one_cnt =  %d, byte_zero_cnt = %d \n ",byte_one_cnt[byte_indx], byte_zero_cnt[byte_indx]  );
#endif
        if (byte_one_cnt[byte_indx] > byte_zero_cnt[byte_indx]) {
           byte_done[byte_indx] = 1;
           byte_not_done[byte_indx] = 0;
        }
     }

     //---------------------------------------------------------------------
     //Disable training for the bytes that already done
     //---------------------------------------------------------------------
     set_rcw_enable (byte_not_done, num_half_cycle, ch, dq);

     if ((byte_done[0] == 1 ) &&
         (byte_done[1] == 1 ))
         {
            *all_found = 1;
            break;
         }


   }  //max coarse/fine delay for loop
}


//-------------------------------------------------------------------
// ENABLE RCW
//-------------------------------------------------------------------
// enable        : 1: enable rcw training, 0: disable
// num_cycle     : 1: half cycle, 2: full cycle , 3: one and half cycle

void set_rcw_enable (uint8 enable[4],  uint8 num_cycle,  uint8 ch, PHY_BUS dq)
{
   uint8 byte_lane = 0;
   uint32 dq0_ddr_phy_base;   // DDR PHY DQ0 base address

   dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

   for (byte_lane = 0; byte_lane < dq; byte_lane++) {

      DDR_PHY_hal_cfg_cdc_rcw(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)  ,
                           enable[byte_lane], num_cycle);
   }
}

//-------------------------------------------------------------------
// SET RCW CDC delay
//-------------------------------------------------------------------
void set_rcw_cdc_delay ( uint8 rcw_delay,  uint8 coarse_fine, uint8 mode, uint8 ch, uint8 cs , uint8 enable[NUM_DQ_PCH], PHY_BUS dq)
{
   uint8 byte_lane = 0;
   uint32 dq0_ddr_phy_base;   // DDR PHY DQ0 base address

   dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
#if DSF_RCW_TRAINING_LOG
 //ddr_printf (DDR_NORMAL,"SET_RCW_DELAY: delay = %d, coarse_fine = %d\n",rcw_delay, coarse_fine);
#endif
   for (byte_lane = 0; byte_lane < dq; byte_lane++) {

      if (enable[byte_lane])
      DDR_PHY_hal_cfg_cdc_slave_rcw(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)  ,
                           rcw_delay, coarse_fine, HP_MODE, cs);
   }
}

//-------------------------------------------------------------------
// READ RCW STATUS
//-------------------------------------------------------------------
void  read_rcw_status (uint8 *byte_one_cnt, uint8 *byte_zero_cnt, PHY_BUS dq, uint8 ch)
{

   uint8 byte_indx = 0;
   uint8 pass[NUM_DQ_PCH] = {0,0};   
   uint32 dq0_ddr_phy_base;   // DDR PHY DQ0 base address

   dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

 for (byte_indx =0; byte_indx < dq; byte_indx++) {

      DDR_PHY_rd_mon_status(dq0_ddr_phy_base + (byte_indx * DDR_PHY_OFFSET)  ,
                         &pass[byte_indx]);
      byte_one_cnt[byte_indx] +=  pass[byte_indx];
      byte_zero_cnt[byte_indx] +=  (pass[byte_indx] == 1) ? 0 : 1;

   }
}

void DDRSS_bimc_rcw_start_delay_write_flash_params (DDR_STRUCT *ddr,
                                                    uint8 ch,
                                                    uint8 cs,
                                                    PHY_BUS dq,
                                                    training_params_t *training_params_ptr,
                                                    uint8 rcw_start_clk_idx,
                                                    uint8 rcw_clk_idx)
{
//---------------------------------------------------------------------
// Write the FLASH_PARAMETERS data structure  by reading the registers
//---------------------------------------------------------------------
    uint8  byte_lane;                 // loop counter
    uint8  final_coarse_delay; // Final CDC coarse value value
    uint8  final_fine_delay;   // Final CDC fine delay value
    uint8  final_num_cycle;    // Final CDC fine delay value
    uint32 dq0_ddr_phy_base;   // DDR PHY DQ0 base address
    uint8  rcw_cal_idx;        // index to the rest of frequency points with ODT on
    uint32 tDQSCK_in_ps;
    uint32 tDQSCK_in_ps_adjust;
    uint32 rcw_training_period;
    uint32 rcw_cal_period;
    uint32 bimc_tDQSCK_in_100ps;
    double cycle_ratio; 
    
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
    
    rcw_training_period = (CONVERT_CYC_TO_PS / (ddr->misc.clock_plan[rcw_clk_idx].clk_freq_in_khz)); //unit in ps
     
    // Set DDR PHY DQ0 Base
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
    

    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        // Read the DQ PHY RCW registers
        final_coarse_delay = DDR_PHY_hal_sta_rcw_coarse(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),CS_INX(DDR_CS0));
        final_fine_delay   = DDR_PHY_hal_sta_rcw_fine(dq0_ddr_phy_base   + (byte_lane * DDR_PHY_OFFSET),CS_INX(DDR_CS0));
        final_num_cycle    = DDR_PHY_hal_sta_rcw_num_cycle(dq0_ddr_phy_base   + (byte_lane * DDR_PHY_OFFSET));
        //calculate tDQSCK value based on RCW training result
        //tDQSCK_in_ps = (((final_num_cycle-2)    * (rcw_training_period / 2)) + // We reduce RCW result by 1 cycle (-2 half cycles) to get tDQSCK
        tDQSCK_in_ps = (((final_num_cycle) * (rcw_training_period / 2)) +
                      // Since we perform RCW training with single ended DQS HPRX receiver which has less delay than MPRX,
                      // we need to add some delay for use with MPRX frequencies
                      ((final_coarse_delay + RCW_HPRX_MPRX_COARSE_CDC_DLY_DIFF) * (training_params_ptr->rcw.coarse_cdc_step)) +
                      (final_fine_delay   * (training_params_ptr->rcw.fine_cdc_step)));

        //for (rcw_cal_idx = (rcw_clk_idx + 1); rcw_cal_idx < ddr->misc.ddr_num_clock_levels; rcw_cal_idx++)
        for (rcw_cal_idx = rcw_start_clk_idx; rcw_cal_idx < ddr->misc.ddr_num_clock_levels; rcw_cal_idx++) //enable RCW training at 300000MHz       
        //assuming RCW training index + 1 is the starting point of ODT on. 
        {
           tDQSCK_in_ps_adjust = tDQSCK_in_ps;
           
           if(ddr->misc.clock_plan[rcw_cal_idx].clk_freq_in_khz > HIGHEST_MPRX_FPRS_FREQ)
           {
               tDQSCK_in_ps_adjust -= (RCW_HPRX_MPRX_COARSE_CDC_DLY_DIFF * training_params_ptr->rcw.coarse_cdc_step); // For HPRX frequencies remove the delay that is added for MPRX frequencies
           }
           
           rcw_cal_period = CONVERT_CYC_TO_PS / ddr->misc.clock_plan[rcw_cal_idx].clk_freq_in_khz;
           
         /* 
         // Apply positive offset to frequencies above a threshold
           if (ddr->misc.clock_plan[rcw_cal_idx].clk_freq_in_khz > RCW_POSITIVE_OFFSET_FREQ_THRESHOLD)
           {
               tDQSCK_in_ps_adjust += (RCW_POSITIVE_OFFSET_IN_CLK * rcw_cal_period);
           }
           
           // Apply negative offset to all frequencies
           if (tDQSCK_in_ps_adjust < (RCW_NEGATIVE_OFFSET_IN_CLK * rcw_cal_period))
           {
               tDQSCK_in_ps_adjust = 0;
           }
           else 
           {
               tDQSCK_in_ps_adjust -= (RCW_NEGATIVE_OFFSET_IN_CLK * rcw_cal_period);
           }
         */
            //tDQSCK_in_ps_adjust = (tDQSCK_in_ps_adjust / 100) *100; //convert to 100ps before ratio calculation.
            
           cycle_ratio = ((double) tDQSCK_in_ps_adjust) / rcw_cal_period;
        
         // BIMC rounds down tDQSCK to lower cycle value. If tDQSCK in ps is more than half period, then
         // add half period and 100ps to get a round up.
           if ((cycle_ratio - (tDQSCK_in_ps_adjust / rcw_cal_period)) > 0.5) 
              bimc_tDQSCK_in_100ps = ((tDQSCK_in_ps_adjust + (rcw_cal_period / 2) + 100) / 100);
           else 
              bimc_tDQSCK_in_100ps = (tDQSCK_in_ps_adjust / 100);
           
           //  Store register values into flash training data structure
          // training_data_ptr->results.rcw.bimc_tDQSCK[rcw_cal_idx][ch][cs][byte_lane] = bimc_tDQSCK_in_100ps;
          //for (rcw_cal_idx = rcw_start_clk_idx; rcw_cal_idx < ddr->misc.ddr_num_clock_levels; rcw_cal_idx++)
            {
              training_data_ptr->results.rcw.bimc_tDQSCK[rcw_cal_idx][ch][cs][byte_lane] = bimc_tDQSCK_in_100ps;
            }
         //  training_data_ptr->results.rcw.bimc_tDQSCK[rcw_cal_idx][ch][cs][byte_lane] = 0x16;
#if DSF_RCW_TRAINING_LOG
         //ddr_printf(DDR_NORMAL,"CH = %d, cs = %d, BYTE = %d, RCW value = %d\n",ch, cs,byte_lane, bimc_tDQSCK_in_100ps);
#endif
        }
    }
}


