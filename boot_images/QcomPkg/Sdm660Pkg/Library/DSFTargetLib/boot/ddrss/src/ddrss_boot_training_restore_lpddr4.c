/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_boot_training_restore_lpddr4.c#9 $
$DateTime: 2017/05/26 00:34:56 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/08/14   jeasley      Change wrlvl to zero based channel and chip select.
                        Moved DRAM routines from wrlvl.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/
#include "ddrss.h"
#include "target_config.h"

// Needed for the perbit Restore sequence.
extern uint8 dq_dbi_bit;
extern uint8 dq_spare_bit;
extern uint8 connected_bit_mapping_CA [PINS_PER_PHY_CONNECTED_CA];


boolean HAL_DDR_Boot_Training_Restore(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   
    // Restore only if DSF version number matches, which indicates training has already been done 
    // for this version of the DSF at least once before.
    if (ddr->flash_params.version == TARGET_DDR_SYSTEM_FIRMWARE_VERSION)
    {
        DDRSS_training_restore_lpddr4 (ddr, channel, chip_select);
    }
    // If the version number does not match, return FALSE, so that caller of DSF can 
    // call HAL_DDR_Boot_Training() with INIT in order to re-train.
    else
    {
        ddr_printf(DDR_NORMAL, "\nDSF version changed, triggering re-training..\n");
        ddr_printf(DDR_NORMAL, " Previous DSF version : %u\n", ddr->flash_params.version);
        ddr_printf(DDR_NORMAL, " Current  DSF version : %u\n\n", TARGET_DDR_SYSTEM_FIRMWARE_VERSION);
        return FALSE;
    }
    
    // Post Boot Training setup.
    DDRSS_Post_Boot_Training(ddr, channel, chip_select);
   
    return TRUE; 
}


// --------------------------------------------------
// Training results restore
// --------------------------------------------------
void DDRSS_training_restore_lpddr4 (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
    uint8  ch                = 0;
    uint32 ca0_ddr_phy_base  = 0;
    uint8  training_ddr_freq_indx = 0;
    uint32 PRFS_BAND_THRESHOLD[NUM_PRFS_BANDS]  = {F_RANGE_0, F_RANGE_1, F_RANGE_2, F_RANGE_3,F_RANGE_4,F_RANGE_5, F_RANGE_6, F_RANGE_7};
    uint8  prfs_index = TRAINING_START_PRFS; 
    uint8  training_table_index = 0; 
    uint8  min_training_prfs_index = 0xff; 
    

#if (DSF_CA_VREF_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
     uint8  freq            = 0;
#endif

#if (DSF_CA_VREF_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN || DSF_WR_VREF_BYTE_MODE_EN)
    uint8  cs                = 0;
#endif

#if (DSF_RD_DQDQS_DCC || DSF_DCC_TRAINING_DQ_DCC_EN || DSF_DCC_TRAINING_CA_DCC_EN || DSF_WRLVL_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
    uint8  byte_lane   = 0;
    PHY_BUS  dq        = DQ;
#if DSF_WR_VREF_BYTE_MODE_EN
	uint8    MR31_value = 0;
	IO_WIDTH wr_io_width = X16MODE;
#endif
#endif

#if DSF_RD_DQDQS_TRAINING_EN
    uint8  bit               = 0;
    uint32 clk_freq_khz      = 0;
    uint32 training_freq_table[MAX_TRAINING_FREQ_NUM] =  {0};
#endif 

#if (DSF_CA_VREF_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
    uint8  fsp_op            = 0;
    uint8  fsp_wr            = 0;
    uint8  fsp_range         = 0;
    uint8 MR13_value         = 0;
    uint8 MR_value_die1      = 0;
#endif

#if (DSF_CA_VREF_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN)
    uint8  mp_hp             = 0;
#endif  

#if (DSF_RD_DQDQS_DCC || DSF_DCC_TRAINING_DQ_DCC_EN || DSF_DCC_TRAINING_CA_DCC_EN  || DSF_CA_VREF_TRAINING_EN || \
     DSF_WRLVL_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
    uint32 dq0_ddr_phy_base  = 0;
#endif

#if (DSF_RD_DQDQS_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
    uint32    reg_offset_dpe = 0; 
    dbi_struct dbi_struct_info;
#endif

#if (DSF_DCC_TRAINING_CA_DCC_EN || DSF_CA_VREF_TRAINING_EN || DSF_WRLVL_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN)
    uint8  ca_lane  = 0;
    PHY_BUS  ca     = CA;
#endif

#if (DSF_WRLVL_TRAINING_EN || DSF_RD_DQDQS_TRAINING_EN || DSF_WR_DQDQS_TRAINING_EN)
    //allow input to override detected CS
    DDR_CHIPSELECT qualified_cs = (DDR_CHIPSELECT)(chip_select & ddr->detected_ddr_device[0].populated_chipselect);
#endif
    
    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    //search through frequency table to automatically identify training frequency
    for (training_ddr_freq_indx = 0; training_ddr_freq_indx < ddr->misc.ddr_num_clock_levels; training_ddr_freq_indx++)
    { 
        if ((ddr->misc.clock_plan[training_ddr_freq_indx].clk_freq_in_khz) > PRFS_BAND_THRESHOLD[prfs_index])
        {
            if ((ddr->misc.clock_plan[training_ddr_freq_indx-1].clk_freq_in_khz) > PRFS_BAND_THRESHOLD[prfs_index - 1]) //make sure we have a frequency in this band
            {
#if DSF_RD_DQDQS_TRAINING_EN			
                training_freq_table[training_table_index] = ddr->misc.clock_plan[training_ddr_freq_indx -1].clk_freq_in_khz;
#endif
                
                if (min_training_prfs_index > prfs_index)
                {
                    min_training_prfs_index = prfs_index;
                }
                training_table_index++;
                prfs_index++;
            }
            else
            {
                prfs_index++;  //don't advance training table index
            }
        }
        if (training_ddr_freq_indx == ddr->misc.ddr_num_clock_levels-1) 
        {
#if DSF_RD_DQDQS_TRAINING_EN
            training_freq_table[training_table_index] = ddr->misc.clock_plan[training_ddr_freq_indx].clk_freq_in_khz;		
#endif
        }
    }

#if (DSF_DCC_TRAINING_DQ_DCC_EN || DSF_RD_DQDQS_DCC || DSF_DCC_TRAINING_CA_DCC_EN)             
     //--------------------------------------------------------------------------------------
    // Restore DCC values
    //--------------------------------------------------------------------------------------
    for (ch = 0; ch < NUM_CH; ch++) 
    {
        if ((channel >> ch) & 0x1)
        {
            // DDR PHY DQ base address
            dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            
#if DSF_DCC_TRAINING_DQ_DCC_EN            
            // Restore DQ PHY DCC
            for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {

					 // Select the CSR for the adjusters
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MODE,  0); // WRLVL
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD, 1); // W90
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,IO_MODE,  0); // IO

					 // Select the CSR for the adjusters
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MODE,  1); // WRLVL
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD, 0); // W90
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,IO_MODE,  1); // IO	
	 
				 // Assert Clock Gate enables
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_4_CFG, IO_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 1);
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_4_CFG, CM_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 1);
 
				 // Open the latch enable to drive the trained value into the adjuster
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 1);
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WR_CDC_LATCH_EN, 1);
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_3_CFG, IO_ADJ_DQ_SW_OVRD, 1);
	 
				 // Restore the training registers from the data structure	
				 // WRLVL CDC
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MAN_ADJ, 
							 training_data_ptr->results.dcc.wrlvl_stat_dq [ch][byte_lane]);
				// training_data_ptr->results.dcc.wrlvl_stat_dq[freq_band][ch][pll][byte_lane]
	 
				 // WR90 CDC
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD_VAL,
							 training_data_ptr->results.dcc.t90_stat_dq[ch][byte_lane]);
	 			//training_data_ptr->results.dcc.t90_stat_dq[freq_band][ch][byte_lane] 
				 // IO DQS
				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_1_CFG,IO_MAN_ADJ,
							 training_data_ptr->results.dcc.iodqs_stat_dq [ch][byte_lane]);
				 // Assert Clock Gate disables
				 //05/25/17 Commented the below based on bootup issues debug for the DCC values to take effect
				 //HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_4_CFG, IO_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 0);
				 //HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_4_CFG, CM_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 0);
 				
				 // latch disable 
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 0);
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WR_CDC_LATCH_EN, 0);				
////				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_DCC_TOP_3_CFG, IO_ADJ_DQ_SW_OVRD, 0);	

					 // Di - Select the CSR for the adjusters
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MODE,  0); // WRLVL
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD, 1); // W90
//				 HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),DDR_PHY_DDRPHY_DCC_TOP_0_CFG,IO_MODE,  0); // IO				 
			}//dq
#endif

#if DSF_RD_DQDQS_DCC  
          // Restore DQ PHY DCC
            // TODO: Temporary fix for KW
//          for (byte_lane = 0; byte_lane < dq; byte_lane++) 
//          {     
            // Byte 0       
            HWIO_OUTXF(dq0_ddr_phy_base, 
                        DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, 
                        DCC_CTL, 
                        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][0]
                      );

            // Byte 1                      
            HWIO_OUTXF(dq0_ddr_phy_base + DDR_PHY_OFFSET, 
                        DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, 
                        DCC_CTL, 
                        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][1]
                      );
                      
//          }
#endif

#if DSF_DCC_TRAINING_CA_DCC_EN  
            // Restore CA PHY DCC
            for (ca_lane = 0; ca_lane < ca; ca_lane++) 
            {             
                // Set CA Base Address
                if (ca_lane == 0) {
                    ca0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH (ch) + CA0_DDR_PHY_OFFSET;
                }
                else {
                    ca0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH (ch) + DDR_PHY_OFFSET;
                }           
                                                             
					 // Set up DCC restore mode
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MODE,  0); // WRLVL
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD, 1); // W90
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,IO_MODE,  0); // IO
					 // Set up DCC restore mode
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MODE,  1); // WRLVL
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD, 0); // W90
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,IO_MODE,  1); // IO
				 
				 // Assert Clock Gate enables
				 HWIO_OUTXF (ca0_ddr_phy_base, DDR_PHY_DDRPHY_DCC_TOP_4_CFG, IO_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 1);
				 HWIO_OUTXF (ca0_ddr_phy_base, DDR_PHY_DDRPHY_DCC_TOP_4_CFG, CM_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 1);
	 
				 // Open the latch enable to drive the trained values into the adjusters
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 1);
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WR_CDC_LATCH_EN, 1);
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG, IO_ADJ_DQ_SW_OVRD, 1);
	 
				 // Restore the training registers from the data structure
				 // WRLVL CDC
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MAN_ADJ, 
							 training_data_ptr->results.dcc.wrlvl_stat_ca [ch][ca_lane]);
	 
				 // WR90 CDC
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD_VAL,
							 training_data_ptr->results.dcc.t90_stat_ca[ch][ca_lane]);
	 
				 // IO DQS
				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_1_CFG,IO_MAN_ADJ,
								 training_data_ptr->results.dcc.iodqs_stat_ca [ch][ca_lane]);
				 // Assert Clock Gate enables
				 //05/25/17 Commented the below based on bootup issues debug for the DCC values to take effect
				 //HWIO_OUTXF (ca0_ddr_phy_base, DDR_PHY_DDRPHY_DCC_TOP_4_CFG, IO_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 0);
				 //HWIO_OUTXF (ca0_ddr_phy_base, DDR_PHY_DDRPHY_DCC_TOP_4_CFG, CM_SW_OVRRD_UPDT_INT_CLK_CGC_EN_SEL, 0);				 

				 //disable latch
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 0);
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WR_CDC_LATCH_EN, 0);
////				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG, IO_ADJ_DQ_SW_OVRD, 0);
				 
					 // Set up DCC restore mode
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,CM_MODE,  0); // WRLVL
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_3_CFG,CM_ADJ_DQ_SW_OVRD, 1); // W90
//				 HWIO_OUTXF (ca0_ddr_phy_base,DDR_PHY_DDRPHY_DCC_TOP_0_CFG,IO_MODE,  0); // IO				 
     		 }//ca
#endif
        } //if
    }//ch   
#endif

    // Write the DCC_CTL register.
    for (ch = 0; ch < NUM_CH; ch++) 
    {
        if ((channel >> ch) & 0x1)
        {

            ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
            
            HWIO_OUTXF2(ca0_ddr_phy_base, DDR_PHY_DDRPHY_DCC_TOP_5_CFG, IO_DCC_DQS_OFFSET_MAGNITUDE, IO_DCC_DQS_OFFSET_SIGN, 
                                         training_data_ptr->results.rd_dqdqs.clk_dcc_mag[ch][0], training_data_ptr->results.rd_dqdqs.clk_dcc_sign[ch][0]);
        }
    }
    
    //--------------------------------------------------------------------------------------
    // Restore CA VREF values
    //--------------------------------------------------------------------------------------
#if DSF_CA_VREF_TRAINING_EN

    // CA training is only at 1862MHz/Band 6
    if (prfs_index == (training_table_index + 3))
    {    
        freq = (training_table_index + 3);
        for (ch = 0; ch < NUM_CH; ch++) 
        {
            // Set ddr phy base address for CA PHYs
            ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;

		  if ((channel >> ch) & 0x1)
		   {	
            for (cs = 0; cs < NUM_CS; cs++) 
            {
                if ((chip_select >> cs) & 0x1)
                {           
                    
                     // Set FSP-WR=1 to write MR11, 12 and 14 values
                    BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(0), JEDEC_MR_13, 0x40);

                    // Write the VREF to the DRAM MR_12.
                    DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_12, 
                    training_data_ptr->results.ca_vref.range_vref[freq][ch][cs][0], 
                    0);

                    for (ca_lane = 0; ca_lane < ca; ca_lane++) 
                    {
                        // Set SDR mode
                        HWIO_OUTXF (ca0_ddr_phy_base + (ca_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_TOP_CTRL_4_CFG, SW_ODDR_SDR_MODE_EN,  0);
                    } //ca_lane 
                }
            } //cs 
		  } //if
        }//ch
    }//freq
#endif
  
    //--------------------------------------------------------------------------------------
    // Restore WRLVL values
    //--------------------------------------------------------------------------------------
#if  DSF_WRLVL_TRAINING_EN
    //wrlvl training is only done at 1866Mhz now
   // if (prfs_index == (training_table_index + 3))
     for (freq = prfs_index; freq >= LOWEST_WRLVL_COPY_PRFS; freq--)  
    {
        for (ch = 0; ch < NUM_CH; ch++) 
        {
            if ((channel >> ch) & 0x1)
            {
            // DDR PHY base address
            ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
            dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET; 
            
            for (cs = 0; cs < NUM_CS; cs++) 
            {
              if ((qualified_cs >> cs) & 0x1)
              {
                  for (byte_lane = 0; byte_lane < dq; byte_lane++) 
                  {
                    // Restore WRLVL Retimer values
                    DDR_PHY_hal_cfg_wrlvlext_ctl_update(dq0_ddr_phy_base  + (byte_lane * DDR_PHY_OFFSET), 
                                                        freq, 
                                                        cs, 
                                                        training_data_ptr->results.wrlvl.dq_dqs_retmr[freq][ch][cs][byte_lane] 
                                                        );
                    
                    // Restore WRLVL DQS CDC values
                    DDR_PHY_hal_cfg_cdcext_wrlvl_update(dq0_ddr_phy_base  + (byte_lane * DDR_PHY_OFFSET),
                                                  freq, 
                                                  cs,
                                                  training_data_ptr->results.wrlvl.dq_fine_dqs_delay[freq][ch][cs][byte_lane],
                                                  training_data_ptr->results.wrlvl.dq_coarse_dqs_delay  [freq][ch][cs][byte_lane]);
                  }//byte_lane

                  for (ca_lane = 0; ca_lane < ca; ca_lane++) 
                  {                   
                    // Restore CA Retimer values
                    DDR_PHY_hal_cfg_wrlvlext_ctl_update(ca0_ddr_phy_base  + (ca_lane * DDR_PHY_OFFSET), 
                                                        freq, 
                                                        0, 
                                                        training_data_ptr->results.wrlvl.ca_dqs_retmr[freq][ch][0][ca_lane] 
                                                        );
                    
                    // Restore CA Coarse CDC values
                    DDR_PHY_hal_cfg_cdcext_wrlvl_update(ca0_ddr_phy_base  + (ca_lane * DDR_PHY_OFFSET),
                                                        freq, 
                                                        0,
                                                        0,
                                                        training_data_ptr->results.wrlvl.ca_coarse_dqs_delay[freq][ch][0][ca_lane]
                                                        ); // fine always set to 0                                  
                  }// ca_lane
              }// if
            }  //if
            }// cs
        }// ch
    }// freq
#endif

    //--------------------------------------------------------------------------------------
    // Restore RCW values
    //--------------------------------------------------------------------------------------
    
    // RCW training values is updated directly in ddr_result_struct
    
    //--------------------------------------------------------------------------------------
    // Restore RD_DQDQS values
    //--------------------------------------------------------------------------------------
#if DSF_RD_DQDQS_TRAINING_EN
    // Set DBI flag to indicate Enable DBI or not
    reg_offset_dpe = REG_OFFSET_DPE(0); // Channel 0 only. DBI setting should be the same for Channel 1.
    dbi_struct_info.dbi_flag = HWIO_INXF (reg_offset_dpe, DPE_CONFIG_9, DBI_RD);
    // Set the number of bits and mapping table for perbit training
    dbi_struct_info.dq_pin_num_max = (dbi_struct_info.dbi_flag == 1) ? 
                                       PINS_PER_PHY_CONNECTED_WITH_DBI : PINS_PER_PHY_CONNECTED_NO_DBI;
    dbi_struct_info.connected_bit_mapping_A = (dbi_struct_info.dbi_flag == 1) ? 
                                               connected_bit_mapping_with_DBI_A : connected_bit_mapping_no_DBI_A;
    
    for (ch = 0; ch < NUM_CH; ch++) 
    {
        // Set DDR PHY base address
        dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
                
        if ((channel >> ch) & 0x1)
        {
        for (cs = 0; cs < NUM_CS; cs++) 
        {
          if ((qualified_cs >> cs) & 0x1)
          {
            for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {

                for (bit = 0; bit < PINS_PER_PHY; bit++) 
                {
                    DDR_PHY_hal_cfg_local_vref (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                               training_data_ptr->results.rd_dqdqs.perbit_vref[ch][cs][byte_lane][bit],
                                               cs,
                                               bit);  
                                               
                    DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                                bit,
                                                0,    /* 0 for RX.*/ 
                                                cs, 
                                                training_data_ptr->results.rd_dqdqs.perbit_delay[ch][cs][byte_lane][bit]);
                }
    
                DDR_PHY_hal_cfg_local_vref (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),   //restore dqs io_qualifier local Vref
                           DQS_VREF,
                           cs,
                           10);    
            }//for
          }//qualified_cs
        }//cs
      }//if
    }//ch

    // Restore rd_dqdqs CDC values
    for (freq = min_training_prfs_index - NUM_SCALE_BANDS; freq <= prfs_index; freq++)  //need to restore band1's scaling value.  
    {
        // 800 MHz -> 2
        if (freq <= 3) {
            clk_freq_khz = training_freq_table[0];  //777600;
            mp_hp = 0;
        }
        else {
            clk_freq_khz = training_freq_table[training_table_index];  //Top Speed ;
            mp_hp = 1;
        }

        for (ch = 0; ch < NUM_CH; ch++) 
        {
          ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
          dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
                        
            if ((channel >> ch) & 0x1)
            {
            for (cs = 0; cs < NUM_CS; cs++) 
            {
              if ((qualified_cs >> cs) & 0x1)
              {
                    for (byte_lane = 0; byte_lane < dq; byte_lane++)
                    {
                    // Restore the VREF_TRIM and RFU based on the 800 MHz termination threshold
                    	DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                                     training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][cs][byte_lane],
                                                     clk_freq_khz,
                                                     cs);
                        // Restore coarse CDC values
                        DDR_PHY_hal_cfg_cdcext_slave_rd (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                     cs, 
                                                     training_data_ptr->results.rd_dqdqs.coarse_cdc [freq][ch][cs][byte_lane], 
                                                     1/*coarse*/, 
                                                     HP_MODE, 
                                                     freq
                                                    );   
                        // Restore fine CDC values
                        DDR_PHY_hal_cfg_cdcext_slave_rd (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                     cs, 
                                                     training_data_ptr->results.rd_dqdqs.fine_cdc [freq][ch][cs][byte_lane], 
                                                     0/*fine*/, 
                                                     HP_MODE, 
                                                     freq
                                                    );
                    }//byte_lane
              }//if
            }//cs
            }//if
        }//ch
    }//freq
#endif

    //--------------------------------------------------------------------------------------
    // Restore WR_DQDQS values
    //--------------------------------------------------------------------------------------
#if DSF_WR_DQDQS_TRAINING_EN
    // Set DBI flag to indicate Enable DBI or not
    reg_offset_dpe = REG_OFFSET_DPE(0); // Channel 0 only. DBI setting should be the same for Channel 1.
    dbi_struct_info.dbi_flag = HWIO_INXF (reg_offset_dpe, DPE_CONFIG_9, DBI_WR);
    // Set the number of bits and mapping table for perbit training
    dbi_struct_info.dq_pin_num_max = (dbi_struct_info.dbi_flag == 1) ? 
                                       PINS_PER_PHY_CONNECTED_WITH_DBI : PINS_PER_PHY_CONNECTED_NO_DBI;   
    dbi_struct_info.connected_bit_mapping_A = (dbi_struct_info.dbi_flag == 1) ? 
                                               connected_bit_mapping_with_DBI_A : connected_bit_mapping_no_DBI_A;
    
    
    for (freq = 0 /*1*/; freq <= prfs_index; freq++) 
    {
        for (ch = 0; ch < NUM_CH; ch++) 
        {
            if ((channel >> ch) & 0x1)
            {
            // Set the PHY base address
            dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;
            for (cs = 0; cs < NUM_CS; cs++) 
            {
                if ((qualified_cs >> cs) & 0x1)
                {
                
                    //fsp_op = (freq > FSP_THRESHOLD_PRFS_BAND) ? 1 : 0 ;
                    fsp_wr = (freq > FSP_THRESHOLD_PRFS_BAND) ? 1 : 0 ;                 
                    fsp_range = (freq > FSP_THRESHOLD_PRFS_BAND) ? 0: 1;
            
                    // Write DRAM MR13 and MR14 with the FSP only for max FSP0 freq(768MHz) and FSP1 freq(1804MHz)
                    if ((freq == FSP_THRESHOLD_PRFS_BAND ) || (freq == prfs_index)) 
                    {
                        MR13_value = ((fsp_op << 7) | (fsp_wr << 6) | (0 << 5) | (0 << 3) | (0 << 2) | (0 << 0));
                        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_13, MR13_value);
#if DSF_WR_VREF_BYTE_MODE_EN
						wr_io_width = (cs == 0 )? 
										(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs0 :
										(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs1;
						if (wr_io_width == X16MODE)
						{
						MR_value_die1 = ((fsp_range << 6) | ((training_data_ptr->results.wr_dqdqs.coarse_vref[freq][ch][cs][0] + training_data_ptr->results.wr_dqdqs.coarse_vref[freq][ch][cs][1]) << 0 ));
                		DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR_value_die1,0);
						}
						else // if io_width = X8mode
						{
						// Program Vref per DQ byte for rank 1 using the byte mode.
						// MR 31 is used to program Vref/ DQ for rank1
							for(byte_lane = 0; byte_lane < dq; byte_lane++)
							{
							//Enable byte mode for individual bytes
							MR31_value = 1 << (7 - byte_lane) | 0 << (6 + byte_lane); // Enable the byte to receive MR14 values and disable the other Byte
							BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
							//Program the Vref value
							MR_value_die1 =((fsp_range << 6) | (training_data_ptr->results.wr_dqdqs.coarse_vref[freq][ch][cs][byte_lane] << 0));				
							DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR_value_die1, 0);
							// Disable the Byte mode
							MR31_value = 0x0;
							BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
							}
						}

#else            
                        //MR_value_die1 = ((fsp_range << 6) | (training_data_ptr->results.wr_dqdqs.fine_best_eye_vref_value[freq][ch][cs][0] << 0));
                       // MR_value_die1 = ((fsp_range << 6) | (training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[freq][ch][cs][0] << 0));
                       MR_value_die1 = ((fsp_range << 6) | ((training_data_ptr->results.wr_dqdqs.coarse_vref[freq][ch][cs][0] + training_data_ptr->results.wr_dqdqs.coarse_vref[freq][ch][cs][1])/2 << 0 ));
                        DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR_value_die1,0);
#endif
                    }
    
                    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
                    {
                        // Per-bit CDC
                        for (bit = 0; bit < PINS_PER_PHY; bit++) 
                        {
                            DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                                        bit,
                                                        1,   /* 1 for TX.*/
                                                        cs, 
                                                        training_data_ptr->results.wr_dqdqs.perbit_delay[ch][cs][byte_lane][bit]); 
                        }
                        
                        // Restore the Coarse CDC
                        DDR_PHY_hal_cfg_cdcext_slave_wr (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                        cs, 
                                                        training_data_ptr->results.wr_dqdqs.coarse_cdc[freq][ch][cs][byte_lane], 
                                                        1/*coarse*/, 
                                                        HP_MODE, 
                                                        freq
                                                    );
                        
                        
                        // Restore the Fine CDC
                        DDR_PHY_hal_cfg_cdcext_slave_wr (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                        cs, 
                                                        training_data_ptr->results.wr_dqdqs.fine_cdc[freq][ch][cs][byte_lane], 
                                                        0/*fine*/, 
                                                        HP_MODE, 
                                                        freq
                                                    );
                        
                        // Restore Retimer, HC and FC values
                        DDR_PHY_hal_cfg_wrext_ctl_update (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                        freq, 
                                                        cs, 
                                                        training_data_ptr->results.wr_dqdqs.dq_retmr     [freq][ch][cs][byte_lane], 
                                                        training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq][ch][cs][byte_lane], 
                                                        training_data_ptr->results.wr_dqdqs.dq_full_cycle[freq][ch][cs][byte_lane]
                                                        );
    
                    } //byte_lane
                }
            }//cs
            }
        }//ch
    
    }//freq
    
    fsp_wr = fsp_op;
    for (ch = 0; ch < NUM_CH; ch++) 
    {
        if ((channel >> ch) & 0x1)
        {
            for (cs = 0; cs < NUM_CS; cs++) 
            {    
                if ((qualified_cs >> cs) & 0x1)
                {
                    MR13_value = ((fsp_op << 7) | (fsp_wr << 6) | (0 << 5) | (0 << 3) | (0 << 2) | (0 << 0));
                    BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_13, MR13_value);
                }
            } //cs
        }
    } //ch
#endif  

} // DDRSS_restore

