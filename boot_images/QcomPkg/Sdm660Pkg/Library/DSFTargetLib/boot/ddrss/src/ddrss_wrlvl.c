/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_wrlvl.c#8 $
$DateTime: 2018/12/26 02:55:51 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
07/09/14   jeasley      Added IO control.  Removed CA fine training.  
05/27/14   jeasley      Convert coarse and fine step variables to COARSE_STEP_IN_PS
                        and FINE_STEP_IN_PS
05/22/14   jeasley      Optimized calc routine
05/21/14   jeasley      Updated the convert routine to use half-cycle only
05/08/14   jeasley      Changed channel and cs to zero based.  Removed DRAM register access.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

/***************************************************************************************************
   Description: The DDRSS Write Leveling Routine performs the LPDDR4 write leveling function.
   Write Leveling is used to determine the skew at the DRAM device between the CK and DQS strobe.
   The hardware does not support training for cs (rank) 1.  The rank 0 results are populated to 
   rank 1 after rank 0 is trained.   
 
***************************************************************************************************/
#include "ddrss.h"

void DDRSS_wrlvl( DDR_STRUCT *ddr, 
                  uint8 ch, 
                  uint8 cs, 
                  PHY_BUS dq,
                  PHY_BUS ca,
                  uint32 clk_freq_khz, 
                  uint32 wrlvl_clk_freq_idx,
                  training_params_t *training_params_ptr)
{  
  //============================================================
  // WRLVL Main Code Thread
  //============================================================

  //-------------------------------------------------------------------------------------
  // Check for CLK->DQS negative skew and update CA PHY WRLVL CDCs
  //-------------------------------------------------------------------------------------

  //  DDRSS_wrlvl_ca(ddr,ch,cs,clk_freq_khz,training_params_ptr, wrlvl_clk_freq_idx);

  //-------------------------------------------------------------------------------------
  // Loop and repeat the Write Leveling procedure until all DQ PHYs are done or error
  //-------------------------------------------------------------------------------------

  DDRSS_wrlvl_dqs(ddr,ch,cs,dq,clk_freq_khz,training_params_ptr,wrlvl_clk_freq_idx);

} // DDR_PHY_wrlvl


void DDRSS_wrlvl_ca(DDR_STRUCT *ddr,uint8 ch, uint8 cs, PHY_BUS ca, PHY_BUS dq, uint32 clk_freq_khz, training_params_t *training_params_ptr, uint32 wrlvl_clk_freq_idx )
{
  //-------------------------------------------------------------------------------------
  // Check for DQS->CLK skew. If the CLK is early, add delay to the CA PHY WRLVL CDC
  // There are two DQ PHYs for each CA PHY.  Both DQ PHYs for each CA PHY must start with
  // a zero (fail) Write Level value.  
  //-------------------------------------------------------------------------------------

  uint8  wrlvl_ca_done                 = 0;  // CA wrlvl routine status
  uint8  bisc_status                   = 0;  // Device WRLVL result
  uint8  feedback_percent              = 0;  // Local feedback percent
  uint8  ca_lane                       = 0;  // CA Loop counter
  uint8  loopcnt                       = 0;  // CA Loop counter
  uint8  byte_lane                     = 0;  // DQ Loop counter
  uint8  done                          = 0;  // Loop done counter
  uint8  wrlvl_max_coarse_cdc          = 0;  // Coarse CDC Saturation Value
  uint8  wrlvl_max_loopcnt             = 0;  // Coarse CDC Saturation Value

  uint8     byte_one_cnt[NUM_DQ_PCH]   = {0};
  uint8    byte_zero_cnt[NUM_DQ_PCH]   = {0};
  uint8     byte_ca_done[NUM_DQ_PCH]   = {0};   // CA status of the dq bytes
  uint8         ca_delay[NUM_CA_PCH]   = {0};   // CA Write level coarse delay
  uint8         ca_retmr[NUM_CA_PCH]   = {0};   // CA retmr value
  
  uint32 dq0_ddr_phy_base              = 0;     // DDR PHY DQ0 Base Address
  uint32 ca0_ddr_phy_base              = 0;     // DDR PHY CA0 Base Address
  
  uint8  cs0_delay                     = 0;     // Temporary storage of CS0 coarse delay
  uint32 index                         = 0;     // PRFS loop index
  uint8  prfs_retmr                    = 0;     // PRFS loop retimer value
  
  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

  // Set DQ0 PHY BASE for the channel and cs
  dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
  ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
  
  // Set CDC Saturation Limits from the training params data structure
  wrlvl_max_coarse_cdc   = training_params_ptr->wrlvl.max_coarse_cdc;
  wrlvl_max_loopcnt      = training_params_ptr->wrlvl.max_loopcnt;
 
 // Enable software override to DQS/DQ pad OEs.
  for (byte_lane = 0; byte_lane < dq; byte_lane++) 
  {
    // Turn on continuous DDRCC clock (per byte lane to drive the DQS pulses)
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY_BYPASS, 1);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRAFFIC_CGC_EN, 1);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_TOP_CGC_CFG, BIST_TOP_CGC_EN, 1);     
    
    // Enable PAD SW override 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQS, 1);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQ, 0x3FF);

    // Disable PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQ,  0);

    //select BIST in datapath
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, WR_DP_SRC_SEL ,  0x1);

    // Enable DQS PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 1);

    // Enable DQ PAD IE
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_ENABLE_IE_DQ, 0x3FF);
   // HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_MODE_IE_DQ, 0x3FF);

    // Set SW Enable for DQS pulses
    HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_CTRL_0_CFG, 0x5);
    
    // Select CDC delay element for rank 1
    if (cs ==1)
    {
      HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, DLY_SEL, 0x1);
    }
  }

  // Initialize CA WRLVL CDC to zero delay
  for (ca_lane=0;ca_lane<ca;ca_lane++) {

    DDR_PHY_hal_cfg_cdc_slave_wrlvl(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                               0, 
                               1, // coarse
                               1, // hp_mode
                               cs);//cs

    DDR_PHY_hal_cfg_cdc_slave_wrlvl(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                               0, 
                               0, // fine
                               1, // hp_mode
                               cs);//cs

    DDR_PHY_hal_cfg_wrlvl_retmr(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                                cs, // cs
                                0);// retmr
  }

  // Loop until all DQs are done or error
  while (wrlvl_ca_done < dq) 
  {
    // Read the bisc_status (Write Level result) from each DQ PHY pair
    for (byte_lane=0;byte_lane<dq;byte_lane++) {

      // Map the CA -> DQ.
      // Map the DQ to the CA CDC delays for 8996
      if ((byte_lane == 0) || (byte_lane == 1)) {
        ca_lane = 0;
      }
      else {
        ca_lane = 1;
      }

      if (ca_delay[ca_lane] >= wrlvl_max_coarse_cdc) {
        byte_ca_done[byte_lane] = 1;
      }
      else {
        if (byte_ca_done[byte_lane] == 0) {

          byte_one_cnt[byte_lane]  = 0;
          byte_zero_cnt[byte_lane] = 0;

          for (loopcnt = wrlvl_max_loopcnt;loopcnt > 0;loopcnt-- ) {

            // Send two DQS pulses to all DQ PHYs
            HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_TRIGGER_CFG, 0x0);
            HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_TRIGGER_CFG, 0x1);     
            HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_TRIGGER_CFG, 0x0);     

            bisc_status =  DDR_PHY_hal_sta_wrlvl_training(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET));
  
            // Collapse the status to a single bit
            bisc_status = (bisc_status & 0x00000001);

            //  Check the bisc status and increment the one or zero count
            if (bisc_status == 1) {
               byte_one_cnt[byte_lane]++;
            } else {
               byte_zero_cnt[byte_lane]++;
            }
          }

          // Calculate the threshold in percent for Write Level pass (histogram)
          if ((byte_one_cnt[byte_lane] + byte_zero_cnt[byte_lane]) != 0) {
            feedback_percent =  ((byte_one_cnt[byte_lane] * 100) / (byte_one_cnt[byte_lane] + byte_zero_cnt[byte_lane]));
          }
          else {
            feedback_percent = 0;
          }

          // Check bisc status.  If equal to one (pass), increment the CA WRLVL delay (CA CLK and Data)
          if (feedback_percent != 0) {
            ca_delay[ca_lane]++;
  
            DDR_PHY_hal_cfg_cdc_slave_wrlvl(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                                           ca_delay[ca_lane], 
                                           1, // coarse
                                           1, // hp_mode
                                           0 );

            
            ca_retmr[ca_lane] = DDRSS_CDC_Retimer_Value(0, 0, ca_delay[ca_lane], 0, clk_freq_khz);
            
            DDR_PHY_hal_cfg_wrlvl_retmr(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                                        0,
                                        ca_retmr[ca_lane]);
          }
          else {
           byte_ca_done[byte_lane] = 1;
          }

        } // if byte_ca_done
      } // else byte_ca_done
    } // for byte_lane

    // Aggregate all of the byte status to determine the ca done state
    wrlvl_ca_done = 0;
    for (done = 0; done < dq; done++) {
      wrlvl_ca_done = wrlvl_ca_done + byte_ca_done[done];
    }
      
  } // while wrlvl_ca_done

  // De activate WRLVL test modes 
  for (byte_lane = 0; byte_lane < dq; byte_lane++) 
  {
    // Disable PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQ, 0);

    //De-select BIST in datapath
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, WR_DP_SRC_SEL, 0x0);

    // Disable DQS PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);

    // Disable DQ PAD IE
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_ENABLE_IE_DQ, 0);
  //  HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_MODE_IE_DQ, 0);  

    // Disble WRLVL pulse control
    HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_CTRL_0_CFG, 0x0);

    // Disable PAD SW override 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQS, 0);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQ, 0);

    // Turn off continuous DDRCC clock (per byte lane)
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY_BYPASS, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRAFFIC_CGC_EN, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_TOP_CGC_CFG, BIST_TOP_CGC_EN, 0);     
    
    // De-select rank 1 delay element
    if (cs ==1)
    {
        HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, DLY_SEL, 0x0);
    } 
  }

  for (ca_lane=0;ca_lane<ca;ca_lane++) 
  {
    if (cs == 1)
    {
      // Pick the largest CA delay across both ranks
      cs0_delay = training_data_ptr->results.wrlvl.ca_coarse_dqs_delay[wrlvl_clk_freq_idx][ch][0][ca_lane];
      
      // Check if CS1 coarse delay is less than CS0 coarse delay
      if (ca_delay[ca_lane] < cs0_delay)
      {
        // Use CS0 values
        ca_delay[ca_lane] = cs0_delay;
        ca_retmr[ca_lane] = training_data_ptr->results.wrlvl.ca_dqs_retmr[wrlvl_clk_freq_idx][ch][0][ca_lane];
      }
	      // Write the EXT registers including and below the trained frequency
      //for (index = wrlvl_clk_freq_idx; index >= LOWEST_WRLVL_COPY_PRFS; index--)
      for (index = MAX_TRAINING_FREQ_INDEX; index >= LOWEST_WRLVL_COPY_PRFS; index--)
      {
      // Obtain retimer setting for highest frequency from clock plan in PRFS band
        prfs_retmr = DDRSS_CDC_Retimer_Value(0, 0, ca_delay[ca_lane], 0, DDRSS_Get_Highest_Freq_In_PRFS_Band(ddr, index));
      
      // Save training result
        training_data_ptr->results.wrlvl.ca_dqs_retmr[index][ch][0][ca_lane]        = prfs_retmr;
        training_data_ptr->results.wrlvl.ca_coarse_dqs_delay[index][ch][0][ca_lane] = ca_delay[ca_lane];
      
      // Write the EXT DCC register 
        DDR_PHY_hal_cfg_cdcext_wrlvl_update(ca0_ddr_phy_base  + (ca_lane * DDR_PHY_OFFSET),
                                          index, 
                                          0, //cs
                                          0, //fine
                                          ca_delay[ca_lane]); //coarse
                                        
        DDR_PHY_hal_cfg_wrlvlext_ctl_update(ca0_ddr_phy_base  + (ca_lane * DDR_PHY_OFFSET), 
                                          index, 
                                          0, 
                                          prfs_retmr);
      }
    }
   
    DDR_PHY_hal_cfg_cdc_slave_wrlvl(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                               ca_delay[ca_lane], 
                               1, // coarse
                               1, // hp_mode
                               0);//cs

    DDR_PHY_hal_cfg_wrlvl_retmr(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                                0, // cs
                                ca_retmr[ca_lane]);// retmr
        //  Store register values into the training data structure
    training_data_ptr->results.wrlvl.ca_dqs_retmr[wrlvl_clk_freq_idx][ch][0][ca_lane]        = ca_retmr[ca_lane];
    training_data_ptr->results.wrlvl.ca_coarse_dqs_delay[wrlvl_clk_freq_idx][ch][0][ca_lane] = ca_delay[ca_lane];
    

/*
  
    DDR_PHY_hal_cfg_cdc_slave_wrlvl(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                               ca_delay[ca_lane], 
                               1, // coarse
                               1, // hp_mode
                               cs);//cs

    DDR_PHY_hal_cfg_wrlvl_retmr(ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET),
                                cs, // cs
                                ca_retmr[ca_lane]);// retmr

    DDR_PHY_hal_cfg_cdcext_wrlvl_update(ca0_ddr_phy_base  + (ca_lane * DDR_PHY_OFFSET),
                                        wrlvl_clk_freq_idx, 
                                        cs, //cs
                                        0, //fine
                                        ca_delay[ca_lane]); //coarse
                                        
    DDR_PHY_hal_cfg_wrlvlext_ctl_update(ca0_ddr_phy_base  + (ca_lane * DDR_PHY_OFFSET), 
                                        wrlvl_clk_freq_idx, 
                                        cs, 
                                        ca_retmr[ca_lane]);
                                        
    //  Store register values into the training data structure
    training_data_ptr->results.wrlvl.ca_dqs_retmr[wrlvl_clk_freq_idx][ch][cs][ca_lane]        = ca_retmr[ca_lane];
    training_data_ptr->results.wrlvl.ca_coarse_dqs_delay[wrlvl_clk_freq_idx][ch][cs][ca_lane] = ca_delay[ca_lane];

	*/
    
#if DSF_WRLVL_TRAINING_LOG    
    ddr_printf(DDR_NORMAL,"    WRLVL ch %d rank %d CA %d coarse = %d\n",ch,cs,ca,ca_delay[ca_lane]);
#endif
    

  }
  #if DSF_WRLVL_TRAINING_LOG      
  ddr_printf(DDR_NORMAL,"\n");
  #endif

}// DDRSS_wrlvl_ca


void DDRSS_wrlvl_dqs(DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint32 clk_freq_khz, training_params_t *training_params_ptr, uint32 wrlvl_clk_freq_idx)
{
  //-----------------------------------------------------------------------------
  //  For the selected frequency, measure dqs->clk delay (wrlvl_max_loopcnt) 
  //  times for each wrlvl delay value. if the one count
  //  is greater than the zero count, the wrlvl training is finished.
  //  If not, the coarse CDC register is incremented. When the coarse CDC passes, 
  //  it is decremented and the loop repeats and increments the fine CDC delay.
  //  This loop is kept continued until either the one count is bigger than the
  //  zero count or when the wrlvl delay value reaches its maximum limit (MAX_CDC).
  //--------------------------------------------------------------------------------------

  // Local Variables
  uint8  byte_lane                           = 0;     // byte_lane loop counter
  uint8  done                         = 0;     // done loop counter
  uint8  loopcnt                      = 0;     // number of byte_lane measurements
  uint8  feedback_percent             = 50;    // Percent of feedback ones in sample
  uint8  wrlvl_dqs_done               = 0;     // Status of the wrlvl routine
  uint8  bisc_status                  = 0;     // Status of the wrlvl result

  uint16     byte_one_cnt[NUM_DQ_PCH] = {0};   // Count of 1 in dq0 measurement
  uint16    byte_zero_cnt[NUM_DQ_PCH] = {0};   // Count of 0 in dq0 measurement
  uint8  fine_dqs_started[NUM_DQ_PCH] = {0};   // Status of the dq bytes
  uint8     byte_dqs_done[NUM_DQ_PCH] = {0};   // Status of the dq bytes
  uint8    fine_dqs_delay[NUM_DQ_PCH] = {0};   // Write Level fine delay
  uint8  coarse_dqs_delay[NUM_DQ_PCH] = {0};   // Write level coarse delay
  uint8   coarse_dqs_done[NUM_DQ_PCH] = {0};   // Write level coarse delay status
  uint8         dqs_retmr[NUM_DQ_PCH] = {0};   // Local dqs re-timer variable
  
  uint8  wrlvl_max_loopcnt            = 0;     // Maximum measurement loop count
  uint8  wrlvl_max_coarse_cdc         = 0;     // Coarse CDC saturation limit
  uint8  wrlvl_max_fine_cdc           = 0;     // Fine CDC saturation limit
  uint8  wrlvl_feedback_percent       = 0;     // Feedback histogram pass percent
  uint32 dq0_ddr_phy_base             = 0;     // DDR PHY DQ0 base address
  uint8  wrlvl_coarse_cdc_step        = 0;     // Coarse CDC step
  uint8  wrlvl_fine_cdc_step          = 0;     // Fine CDC step
  uint32 index                        = 0;     // PRFS loop index
  uint8  rank_index                   = 0;     // PRFS loop index
  uint8  prfs_retmr                   = 0;     // PRFS loop retimer value
  
  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
  
  // Set DQ0 PHY BASE for the channel and cs
  dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

  wrlvl_max_loopcnt      = training_params_ptr->wrlvl.max_loopcnt;
  wrlvl_max_coarse_cdc   = training_params_ptr->wrlvl.max_coarse_cdc;
  wrlvl_max_fine_cdc     = training_params_ptr->wrlvl.max_fine_cdc;
  wrlvl_feedback_percent = training_params_ptr->wrlvl.feedback_percent;
  wrlvl_coarse_cdc_step  = training_params_ptr->wrlvl.coarse_cdc_step;
  wrlvl_fine_cdc_step    = training_params_ptr->wrlvl.fine_cdc_step;
  

 // Enable software override to DQS/DQ pad OEs.
  for (byte_lane = 0; byte_lane < dq; byte_lane++) 
  {
    // Turn on continuous DDRCC clock (per byte lane)
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY_BYPASS, 1);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRAFFIC_CGC_EN, 1);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_TOP_CGC_CFG, BIST_TOP_CGC_EN, 1);     
       
      
    // Enable PAD SW override 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQS, 1);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQ, 0x3FF);

    // Disable PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQ, 0);

    //select BIST in datapath
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, WR_DP_SRC_SEL, 0x1);

    // Enable DQS PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 1);

    // Enable DQ PAD IE
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_ENABLE_IE_DQ, 0x3FF);
  //  HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_MODE_IE_DQ, 0x3FF);

    // Set SW Enable for DQS pulses
    HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_CTRL_0_CFG, 0x5);
    
    if (cs ==1)
    {
        HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, DLY_SEL, 0x1);
    } 
  }

  	//TODO: remove later 
	if (clk_freq_khz == WRLVL_PASS1_FREQ)
	{
		//Set WRLVL Fine/Coarse delay to "0"
		for (byte_lane = 0; byte_lane < dq; byte_lane++) 
		{    
			DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 0 , 0, 1, 0 ); // Set WRLVL Fine delay to "0", for Rank0
			DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 0 , 1, 1, 0 ); // Set WRLVL Coarse delay to "0", , for Rank0
			
			DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 0 , 0, 1, 1 ); // Set WRLVL Fine delay to "0", for Rank1
			DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 0 , 1, 1, 1 ); // Set WRLVL Coarse delay to "0", , for Rank1
		}
	}
	
	for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
		if (cs == 0)
		{
			fine_dqs_delay[byte_lane] = (((HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG, CTL))&0x3E0)>>5);
			coarse_dqs_delay[byte_lane] = (((HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG, CTL))&0x1F));
		}
		if (cs == 1)
		{
			fine_dqs_delay[byte_lane] = (((HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG, CTL))&0xF8000)>>15);
			coarse_dqs_delay[byte_lane] = (((HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_CTL_CFG, CTL))&0x7C00)>>10);
		}
	}
  // Loop through each DQ until Done or Error
  while (wrlvl_dqs_done < dq) 
  {
         
    // Setup all of the DQ PHYs
    for (byte_lane = 0; byte_lane < dq; byte_lane++) {

      // Update WRLVL CDC
      if (byte_dqs_done[byte_lane] == 0) 
      {
        if (fine_dqs_started[byte_lane]) {
          DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                          fine_dqs_delay[byte_lane], 
                                          0, // fine 
                                          1, // hp_mode
                                          cs );
        }
        else {
          DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                        coarse_dqs_delay[byte_lane], 
                                        1, // coarse 
                                        1, // hp_mode
                                        cs );
        }

        dqs_retmr[byte_lane] = DDRSS_CDC_Retimer_Value(0, 0, coarse_dqs_delay[byte_lane], fine_dqs_delay[byte_lane], clk_freq_khz);

        DDR_PHY_hal_cfg_wrlvl_retmr(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                    cs,
                                    dqs_retmr[byte_lane]);
      }

      //  Repeat the WRLVL test for max_loopcount to make a 1 dimensional histogram
      for (loopcnt = wrlvl_max_loopcnt;loopcnt > 0;loopcnt-- ) 
      {
        // Update the status of bytes that are not done
        if (byte_dqs_done[byte_lane] == 0) {

          // Send a Write Level DQS pulse to all PHYs
          HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_TRIGGER_CFG, 0x0);
          HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_TRIGGER_CFG, 0x1);          
          HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_TRIGGER_CFG, 0x0);          

          bisc_status = DDR_PHY_hal_sta_wrlvl_training(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET));
        
          // Collapse the status to a single bit
          bisc_status = (bisc_status & 0x00000001);

          //  Check the bisc status and increment the one or zero count
          if (bisc_status == 1) {
             byte_one_cnt[byte_lane]++;
          } else {
             byte_zero_cnt[byte_lane]++;
          }

        } // if (!byte_dqs_done
      } // for (loopcnt
    } //  End of loop for a given wrlvl delay value

    
    //=========================================================================
    // Process the Write Level Loop Result
    //=========================================================================
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
      //-------------------------------------------------------------------------
      // Write Level Result Process Flow Control
      //-------------------------------------------------------------------------

      // Process the DQ if it is not done
      if (byte_dqs_done[byte_lane] == 0) 
      {
      // Calculate the threshold in percent for Write Level pass (histogram)
        if ((byte_one_cnt[byte_lane] + byte_zero_cnt[byte_lane]) != 0) {
          feedback_percent =  ((byte_one_cnt[byte_lane] * 100) / (byte_one_cnt[byte_lane] + byte_zero_cnt[byte_lane]));
        }
        else {
          feedback_percent = 0;
        }
  
        // Generate an Error and terminate if CDC overflows
        if ((coarse_dqs_delay[byte_lane] >= (wrlvl_max_coarse_cdc - 1)) && (fine_dqs_delay[byte_lane] >= wrlvl_max_fine_cdc)) {
          byte_dqs_done[byte_lane]   = 1;
        }
        // Coarse completed and the fine one count is greater than the zero count: wrlvl is complete
        else if ((coarse_dqs_done[byte_lane] == 1) && (fine_dqs_started[byte_lane] == 1) && 
                 (feedback_percent >= wrlvl_feedback_percent)) {
          byte_dqs_done[byte_lane] = 1;
        }
        // Course is complete and fine has not started : subtract one from coarse and start fine
        else if ((fine_dqs_started[byte_lane] == 0) && 
                 ((feedback_percent >= wrlvl_feedback_percent) || (coarse_dqs_delay[byte_lane] == wrlvl_max_coarse_cdc))) {
          coarse_dqs_done[byte_lane] = 1;
          fine_dqs_started[byte_lane] = 1;
          if (coarse_dqs_delay[byte_lane] != 0) {
            coarse_dqs_delay[byte_lane] -= wrlvl_coarse_cdc_step;

            // Update decremented coarse CDC
            DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                          coarse_dqs_delay[byte_lane], 
                                          1, // coarse 
                                          1, // hp_mode
                                          cs );
          }
        }
        // Coarse is complete and the one count is NOT greater than the zero count : increment fine
        else if ((coarse_dqs_done[byte_lane] == 1) && 
                 (feedback_percent < wrlvl_feedback_percent)) {
          fine_dqs_delay[byte_lane] += wrlvl_fine_cdc_step;
        }
        else {
        // Increment coarse delay 
          coarse_dqs_delay[byte_lane] += wrlvl_coarse_cdc_step;
        } 


      }// if !byte_dqs_done

      // Reset byte counters for the next iteration
      byte_one_cnt[byte_lane]  = 0;
      byte_zero_cnt[byte_lane] = 0;

    } // for (byte_lane

    // Aggregate all of the byte status to determine the done state
    wrlvl_dqs_done = 0;
    for (done = 0; done < dq; done++) {
      wrlvl_dqs_done = wrlvl_dqs_done + byte_dqs_done[done];
    }

  } // while (wrlvl_dqs_done<)


  for (byte_lane = 0; byte_lane < dq; byte_lane++) {

  	if (cs == 1) // if rank = 1 then average both rank0 and rank1 values
   	{
	 	coarse_dqs_delay[byte_lane] = (training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[wrlvl_clk_freq_idx][ch][0][byte_lane] +
							 coarse_dqs_delay[byte_lane]) / 2;
	 	fine_dqs_delay[byte_lane]   = (training_data_ptr->results.wrlvl.dq_fine_dqs_delay[wrlvl_clk_freq_idx][ch][0][byte_lane] +
							 fine_dqs_delay[byte_lane]) / 2;
        dqs_retmr[byte_lane] = DDRSS_CDC_Retimer_Value(0, 0, coarse_dqs_delay[byte_lane], fine_dqs_delay[byte_lane], clk_freq_khz);

		for (rank_index = 0; rank_index < NUM_CS ; rank_index++)
		{
			// save the averaged values to rank 0 regs and rank1 regs
			DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),   
				fine_dqs_delay[byte_lane],                                      
			  	0, // fine 
			  	1, // hp_mode
			  	rank_index);
	    	DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
			  	coarse_dqs_delay[byte_lane],
			  	1, // coarse                                      
			  	1, // hp_mode
			  	rank_index);
			DDR_PHY_hal_cfg_wrlvl_retmr(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                    rank_index,
                                    dqs_retmr[byte_lane]);
		
			DDR_PHY_hal_cfg_wrlvlext_ctl_update(dq0_ddr_phy_base  + (byte_lane * DDR_PHY_OFFSET),
			  	wrlvl_clk_freq_idx,
			  	rank_index, // cs
			  	dqs_retmr[byte_lane]); // full cycle
			DDR_PHY_hal_cfg_cdcext_wrlvl_update(dq0_ddr_phy_base  + (byte_lane * DDR_PHY_OFFSET),
				wrlvl_clk_freq_idx,
				rank_index, // cs
				fine_dqs_delay[byte_lane],
				coarse_dqs_delay[byte_lane]);
			//  Store averaged values into the training data structure
    		training_data_ptr->results.wrlvl.dq_dqs_retmr[wrlvl_clk_freq_idx][ch][rank_index][byte_lane]        = dqs_retmr[byte_lane];
    		training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[wrlvl_clk_freq_idx][ch][rank_index][byte_lane] = coarse_dqs_delay[byte_lane];
    		training_data_ptr->results.wrlvl.dq_fine_dqs_delay[wrlvl_clk_freq_idx][ch][rank_index][byte_lane]   = fine_dqs_delay[byte_lane];

			// Write the EXT registers including and below the trained frequency
    		//for (index = wrlvl_clk_freq_idx; index >= LOWEST_WRLVL_COPY_PRFS; index--)   
    		for (index = MAX_TRAINING_FREQ_INDEX; index >= LOWEST_WRLVL_COPY_PRFS; index--)   
    		{
                // Obtain retimer setting for highest frequency from clock plan in PRFS band
                prfs_retmr = DDRSS_CDC_Retimer_Value(0, 0, coarse_dqs_delay[byte_lane], fine_dqs_delay[byte_lane], DDRSS_Get_Highest_Freq_In_PRFS_Band(ddr, index));
      			// Copy training result
      			training_data_ptr->results.wrlvl.dq_dqs_retmr[index][ch][rank_index][byte_lane]        = prfs_retmr;
      			training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[index][ch][rank_index][byte_lane] = coarse_dqs_delay[byte_lane];
      			training_data_ptr->results.wrlvl.dq_fine_dqs_delay[index][ch][rank_index][byte_lane]   = fine_dqs_delay[byte_lane];
      
      		// Write the EXT DCC register
      			DDR_PHY_hal_cfg_cdcext_wrlvl_update(dq0_ddr_phy_base  + (byte_lane * DDR_PHY_OFFSET),
                                          index,
                                          rank_index,
                                          fine_dqs_delay[byte_lane],
                                          coarse_dqs_delay[byte_lane]);
                                          
      			DDR_PHY_hal_cfg_wrlvlext_ctl_update(dq0_ddr_phy_base  + (byte_lane * DDR_PHY_OFFSET),
                                          index,
                                          rank_index,
                                          dqs_retmr[byte_lane]);
    		}
		}
				
	}//end of if(cs == 1)
	else
	{ // cs ==0
		
    // Write the trained WRLVL values 
    	DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                    fine_dqs_delay[byte_lane], 
                                    0, // fine 
                                    1, // hp_mode
                                    0 );

    	DDR_PHY_hal_cfg_cdc_slave_wrlvl(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                    coarse_dqs_delay[byte_lane], 
                                    1, // coarse 
                                    1, // hp_mode
                                    0 );
                                    
    	DDR_PHY_hal_cfg_wrlvl_retmr(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                    0,
                                    dqs_retmr[byte_lane]);
                                      
    //  Store register values into the training data structure
    	training_data_ptr->results.wrlvl.dq_dqs_retmr[wrlvl_clk_freq_idx][ch][0][byte_lane]        = dqs_retmr[byte_lane];
    	training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[wrlvl_clk_freq_idx][ch][0][byte_lane] = coarse_dqs_delay[byte_lane];
    	training_data_ptr->results.wrlvl.dq_fine_dqs_delay[wrlvl_clk_freq_idx][ch][0][byte_lane]   = fine_dqs_delay[byte_lane];
    
	}

    // Disable PAD OE 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQ, 0);

    //De-select BIST in datapath
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, WR_DP_SRC_SEL, 0x0);

    // Disable DQ PAD IE
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_ENABLE_IE_DQ, 0);
 //   HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_IE_CFG, SW_PAD_MODE_IE_DQ, 0);

    // Disble WRLVL pulse control
    HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_WRLVL_CTRL_0_CFG, 0x0);

    // Disable PAD SW override 
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQS, 0);
    HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQ, 0);

    // Turn off continuous DDRCC clock (per byte lane)
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY, 0); 
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY_BYPASS, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRAFFIC_CGC_EN, 0);
    HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_BIST_TOP_CGC_CFG, BIST_TOP_CGC_EN, 0); 
    #if DSF_WRLVL_TRAINING_LOG    
    ddr_printf(DDR_NORMAL,"    WRLVL ch %d rank %d DQ %d coarse = %d  fine = %d\n",ch,cs,byte_lane,coarse_dqs_delay[byte_lane],fine_dqs_delay[byte_lane]);
    ddr_printf(DDR_NORMAL,"\n");
    #endif    
    if (cs ==1)
    {
        HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCWRLVL_TOP_CFG, DLY_SEL, 0x0);
    } 
  } // for (byte_lane)
} // DDRSS_wrlvl_dqs

// EOF
