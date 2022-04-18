/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2016, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_dcc.c#7 $
$DateTime: 2017/03/06 02:01:52 $
$Author: pwbldsvc $
================================================================================*/

#include "ddrss.h"

void DDRSS_dcc_boot (DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 training_sel, uint32 clk_freq_khz)
{
    uint32 ch               = 0;
    uint32 reg_offset_dpe   = 0;
    uint8  freq_band        = 0;
    
#if DSF_DCC_TRAINING_DQ_DCC_EN    
    uint8  byte_lane        = 0;
    uint32 dq0_ddr_phy_base = 0;
    uint16 wrlvl_stat_dq[NUM_CH][NUM_DQ_PCH]    = {{0,0}, {0,0}};
    uint16   t90_stat_dq[NUM_CH][NUM_DQ_PCH]    = {{0,0}, {0,0}};
    uint16 iodqs_stat_dq[NUM_CH][NUM_DQ_PCH]    = {{0,0}, {0,0}};
#endif     

#if DSF_DCC_TRAINING_CA_DCC_EN
    uint8  ca               = 0;
    uint16 wrlvl_stat_ca[NUM_CH][NUM_DQ_PCH]    = {{0,0}, {0,0}};
    uint16   t90_stat_ca[NUM_CH][NUM_DQ_PCH]    = {{0,0}, {0,0}};
    uint16 iodqs_stat_ca[NUM_CH][NUM_DQ_PCH]    = {{0,0}, {0,0}};
#endif

#if (DSF_DCC_TRAINING_DQ_DCC_EN || DSF_DCC_TRAINING_CA_DCC_EN )    
    uint32 inst_offset      = 0;
    uint32 fpm_prfs_2_pwrs_1_lo_cfg   = 0;
    uint32 fpm_prfs_3_pwrs_1_lo_cfg   = 0;
    uint32 fpm_prfs_4_pwrs_1_lo_cfg   = 0;
    uint32 fpm_prfs_5_pwrs_1_lo_cfg   = 0;
    uint32 fpm_prfs_6_pwrs_1_lo_cfg   = 0;
    uint32 fpm_prfs_7_pwrs_1_lo_cfg   = 0;
    uint32 sw_ca_pad_oe_over_mode_dqs = 0;
    
    //uint8  pll              = 0;    
      
    // Pointer for training data structure
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
#endif
    // Calculate the freq_band (range or PHY band)
    for (freq_band = sizeof(freq_range)/sizeof(freq_range[0]); freq_band > 0; freq_band--)
    {
       if (clk_freq_khz >= freq_range[freq_band-1])
          break;
    }
        freq_band++;

    // Loop through selected channel(s)
    for (ch = 0; ch < NUM_CH; ch++) 
    {

        // Base pointer to BIMC
        reg_offset_dpe   = REG_OFFSET_DPE(ch);

        // Turn on continuous GCC clock per channel (turned on during training by default)
        HWIO_OUTXF2 (reg_offset_dpe, DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x1, 0x1);

      if ((channel >> ch) & 0x1) 
      {
#if DSF_DCC_TRAINING_DQ_DCC_EN
        // Base pointer to DDR_PHY
        dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
        
        // Loop through all PHY DQs (byte_lanes)
        for (byte_lane=0;byte_lane<NUM_DQ_PCH;byte_lane++) 
        {
            // Set individual PHY DQ base address
            inst_offset = dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET);

            // Turn on continuous DDRCC clock (per byte lane)
            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY, 0);
            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY_BYPASS, 1);
            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRAFFIC_CGC_EN, 1);
            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_BIST_TOP_CGC_CFG, BIST_TOP_CGC_EN, 1);             

            // WRLVL DCC training
            if (training_sel & 0x1) {
      
                // Start WRLVL DCC Training and poll for completion
                wrlvl_stat_dq[ch][byte_lane] = DDR_PHY_rtn_training_dcc_wrlvl(ddr,inst_offset);
                
#if DSF_DCC_TRAINING_DQ_DCC_LOG
                ddr_printf(DDR_NORMAL,"    Channel %u Byte %u WRLVL DQS DCC Adjustment: %x\n",ch,byte_lane,wrlvl_stat_dq[ch][byte_lane]);
#endif         
                // Load the data structure with the DCC training results
             //   training_data_ptr->results.dcc.wrlvl_stat_dq[freq_band][ch][pll][byte_lane] = wrlvl_stat_dq[ch][byte_lane];
				training_data_ptr->results.dcc.wrlvl_stat_dq[ch][byte_lane] = wrlvl_stat_dq[ch][byte_lane];

            }

            // WR90 DCC training
            if (training_sel & 0x2) {

                // Start WR90 DCC Training and poll for completion
                t90_stat_dq[ch][byte_lane] = DDR_PHY_rtn_training_dcc_t90(ddr, inst_offset);
                
#if DSF_DCC_TRAINING_DQ_DCC_LOG
                ddr_printf(DDR_NORMAL,"    Channel %u Byte %u WR90 DQS DCC Adjustment: %x\n",ch,byte_lane,t90_stat_dq[ch][byte_lane]);
#endif
                // Load the data structure with the DCC training results
              //  training_data_ptr->results.dcc.t90_stat_dq[freq_band][ch][byte_lane] = t90_stat_dq[ch][byte_lane];
				training_data_ptr->results.dcc.t90_stat_dq[ch][byte_lane] = t90_stat_dq[ch][byte_lane];
            }

            // IO DCC training
            if (training_sel & 0x4) 
            {
                // Store IO settings
                fpm_prfs_2_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG);
                fpm_prfs_3_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG);
                fpm_prfs_4_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG);
                fpm_prfs_5_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG);
                fpm_prfs_6_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG);
                fpm_prfs_7_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG);
                
                // Change DQ IOs for DCC training
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG,fpm_prfs_2_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG,fpm_prfs_3_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG,fpm_prfs_4_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG,fpm_prfs_5_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG,fpm_prfs_6_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG,fpm_prfs_7_pwrs_1_lo_cfg | 0x7FF8);
                
                // SW frequency switch to update IO registers
                DDRSS_ddr_phy_sw_freq_switch(ddr,ch);
                
                // Enable PAD SW override 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQS, 1);
                
                // Disable PAD OE 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);
              
                //select BIST in datapath
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, WR_DP_SRC_SEL ,  0x1);
                
                // Enable DQS PAD OE 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 1);
              
                // Toggle DQS with BIST
                HWIO_OUTX  (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_LO_CFG , 0xFFFFFFFF);
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_HI_CFG , BIST_PTRN_CNT_HI,  0xFFFF);
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_HI_CFG , BIST_MOD,  0x00);
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_HI_CFG , BIST_STRT,  0x01);
          
                // Run IO DCC and read DQS DCC status
                iodqs_stat_dq[ch][byte_lane]  = DDR_PHY_rtn_training_dcc_io_dqs(ddr, inst_offset);

                // Select ITE Datapath
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, WR_DP_SRC_SEL , 0);
                
                // Disable PAD SW override 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_PAD_MODE_DQS, 0);

                // Disable DQS PAD OE 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_PAD_ENABLE_OE_DQS, 0);                 

                // Disable DQS toggle with BIST
                HWIO_OUTX  (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_LO_CFG , 0x0);
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_HI_CFG , BIST_PTRN_CNT_HI,  0x0);
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_HI_CFG , BIST_MOD,  0x00);
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_BIST_PTRN_CNT_HI_CFG , BIST_STRT,  0x00);
          
                // Restore the IO registers previous to DCC
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG,fpm_prfs_2_pwrs_1_lo_cfg );
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG,fpm_prfs_3_pwrs_1_lo_cfg );
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG,fpm_prfs_4_pwrs_1_lo_cfg );
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG,fpm_prfs_5_pwrs_1_lo_cfg );
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG,fpm_prfs_6_pwrs_1_lo_cfg );
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG,fpm_prfs_7_pwrs_1_lo_cfg );
                
                // SW frequency switch to update the IO registers
                DDRSS_ddr_phy_sw_freq_switch(ddr,ch);
                
                // Load the status into the results data structure
              //  training_data_ptr->results.dcc.iodqs_stat_dq[freq_band][ch][byte_lane] = iodqs_stat_dq[ch][byte_lane];
              training_data_ptr->results.dcc.iodqs_stat_dq[ch][byte_lane] = iodqs_stat_dq[ch][byte_lane];
#if DSF_DCC_TRAINING_DQ_DCC_LOG
                ddr_printf(DDR_NORMAL,"    Channel %u Byte %u IO    DQS DCC Adjustment: %x\n",ch,byte_lane,iodqs_stat_dq[ch][byte_lane]);
#endif
            } // if training_sel == 4

            // Turn off continuous DDRCC clock  
            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, DISABLE_PHY_BYPASS, 0);
            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_CMHUB_TOP_0_CFG, TRAFFIC_CGC_EN, 0);

            HWIO_OUTXF(inst_offset, DDR_PHY_DDRPHY_BIST_TOP_CGC_CFG, BIST_TOP_CGC_EN, 0); 

        } // for byte_lane
     
#endif // DSF_DCC_TRAINING_DQ_DCC_EN

        //------------------------------------------------------------------------------------------------------
        // CA (CLK) training
        //------------------------------------------------------------------------------------------------------
#if DSF_DCC_TRAINING_CA_DCC_EN
        // Train each CA clock (CA-DQS) 
        for (ca=0;ca<NUM_CA_PCH;ca++) 
        {
            // Set CA Base Address
            if (ca == 0) {
                inst_offset = REG_OFFSET_DDR_PHY_CH (ch) + CA0_DDR_PHY_OFFSET;
            }
/*            else {
                inst_offset = REG_OFFSET_DDR_PHY_CH (ch) + CA1_DDR_PHY_OFFSET;
            }*/
            
            // WRLVL DCC Training
            if (training_sel & 0x1) {
             
                // Call WRLVL training routine
                wrlvl_stat_ca[ch][ca] = DDR_PHY_rtn_training_dcc_wrlvl(ddr, inst_offset);
                
#if DSF_DCC_TRAINING_CA_DCC_LOG                
                ddr_printf(DDR_NORMAL,"    Channel %u CA %u WRLVL CK DCC Adjustment: %x\n",ch,ca,wrlvl_stat_ca[ch][ca]);
#endif
                // Write DCC Data structure with the adjustment result 
               // training_data_ptr->results.dcc.wrlvl_stat_ca[freq_band][ch][pll][ca] = wrlvl_stat_ca[ch][ca];
				training_data_ptr->results.dcc.wrlvl_stat_ca[ch][ca] = wrlvl_stat_ca[ch][ca];
            }
            
            // WR DCC Training
            if (training_sel & 0x2) {

                // Call WR90 training routine
                t90_stat_ca[ch][ca] = DDR_PHY_rtn_training_dcc_t90(ddr, inst_offset);

                // Write WR90 restore register with the adjustment result
                HWIO_OUTXF (inst_offset, DDR_PHY_DDRPHY_DCC_TOP_3_CFG , CM_ADJ_DQ_SW_OVRD_VAL,t90_stat_ca[ch][ca]); // WR90

                // Write DCC Data structure with the adjustment result 
                
#if DSF_DCC_TRAINING_CA_DCC_LOG
                ddr_printf(DDR_NORMAL,"    Channel %u CA %u WR90  CK  DCC Adjustment: %x\n",ch, ca,t90_stat_ca[ch][ca]);
#endif    
            
				//training_data_ptr->results.dcc.t90_stat_ca[freq_band][ch][ca] = t90_stat_ca[ch][ca];
				training_data_ptr->results.dcc.t90_stat_ca[ch][ca] = t90_stat_ca[ch][ca];
            }
        
            // IO DCC Training
            if (training_sel & 0x4) 
            {
                // Store IO settings
                fpm_prfs_2_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG);
                fpm_prfs_3_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG);
                fpm_prfs_4_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG);
                fpm_prfs_5_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG);
                fpm_prfs_6_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG);
                fpm_prfs_7_pwrs_1_lo_cfg = HWIO_INX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG);
                
                // Store PAD SW override 
                sw_ca_pad_oe_over_mode_dqs = HWIO_INXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_CA_PAD_OE_OVR_MODE_DQS);
                                
                // Change DQ IOs for DCC training
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG,fpm_prfs_2_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG,fpm_prfs_3_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG,fpm_prfs_4_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG,fpm_prfs_5_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG,fpm_prfs_6_pwrs_1_lo_cfg | 0x7FF8);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG,fpm_prfs_7_pwrs_1_lo_cfg | 0x7FF8);
                
                // SW frequency switch to update the IO registers
                DDRSS_ddr_phy_sw_freq_switch(ddr,ch);
                
                // Enable PAD SW override
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_CA_PAD_OE_OVR_MODE_DQS, 1);

                // Enable DQS PAD OE 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_CA_PAD_OE_OVR_DQS, 1);        

                // Run IO DCC and read DQS DCC status
                iodqs_stat_ca[ch][ca]  = DDR_PHY_rtn_training_dcc_io_dqs(ddr, inst_offset);
                
                // Disable PAD SW override 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_CA_PAD_OE_OVR_MODE_DQS, 0);

                // Disable DQS PAD OE 
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_OE_CFG, SW_CA_PAD_OE_OVR_DQS, 0);        

#if DSF_DCC_TRAINING_CA_DCC_LOG
                ddr_printf(DDR_NORMAL,"    Channel %u CA %u IO    CK  DCC Adjustment: %x\n",ch,ca,iodqs_stat_ca[ch][ca]);
#endif
                // Restore PAD SW override
                HWIO_OUTXF (inst_offset,DDR_PHY_DDRPHY_CMIO_PAD_MODE_CFG, SW_CA_PAD_OE_OVR_MODE_DQS, sw_ca_pad_oe_over_mode_dqs);    

                // Restore the IO registers previous to DCC
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_2_PWRS_1_LO_CFG,fpm_prfs_2_pwrs_1_lo_cfg);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_3_PWRS_1_LO_CFG,fpm_prfs_3_pwrs_1_lo_cfg);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_4_PWRS_1_LO_CFG,fpm_prfs_4_pwrs_1_lo_cfg);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_5_PWRS_1_LO_CFG,fpm_prfs_5_pwrs_1_lo_cfg);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_6_PWRS_1_LO_CFG,fpm_prfs_6_pwrs_1_lo_cfg);
                HWIO_OUTX (inst_offset, DDR_PHY_DDRPHY_FPM_PRFS_7_PWRS_1_LO_CFG,fpm_prfs_7_pwrs_1_lo_cfg);
                
                // SW frequency switch to update the IO registers
                DDRSS_ddr_phy_sw_freq_switch(ddr,ch);
     
                // Load the DQS status into the results data structure
               // training_data_ptr->results.dcc.iodqs_stat_ca[freq_band][ch][ca] = iodqs_stat_ca[ch][ca];
               training_data_ptr->results.dcc.iodqs_stat_ca[ch][ca] = iodqs_stat_ca[ch][ca];

            }
        } // for ca
#endif // DSF_DCC_TRAINING_CA_DCC_EN

      } // if ch

      // Turn off continuous GCC clock  
      HWIO_OUTXF2 (reg_offset_dpe, DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x0, 0x0);
    } // for ch
    
} // DDRSS_dcc_boot

