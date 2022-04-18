/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_wr_dqdqs_lpddr4.c#8 $
$DateTime: 2017/03/08 03:07:43 $
$Author: pwbldsvc $
================================================================================================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/08/14   pvenkat      Added Offset references for DDR PHY DQ.
05/06/14   pvenkat      Added NUM_CA_PHY in results.vref_value instead of die1 and die2 separately.
                        Incorporated PINS_PER_PHY for dq_num instead of hard-coded 9.
05/06/14   arindamm     Moved static local arrays out into a general purpose array
                        in the ddrss_boot_training file. That area gets passed as
                        pointer to DDRSS_wr_dqdqs() and callees, which uses it as
                        local variable storage. 
05/05/14   pvenkat      Removed multiple array declarations- now done in the respective routines only.
                        MR13 has FSP[7:6] as variables.
                        Updated to ch and cs everywhere, instead of channel and chip_select.
                        Added odd/even coarse cdc value for calculating fine cdc value.
                        Separate rank check in DDRSS_MR_Write_per_die(), updated the register; enable = 0, not 2. 
                        Added MRxx parameter to DDRSS_MR_Write_per_die().                        
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include <string.h>

// -------------------------------------------------------------------------
// DDR PHY WR DQ-DQS Training.
// -------------------------------------------------------------------------
boolean DDRSS_wr_dqdqs_lpddr4 (DDR_STRUCT *ddr, 
                               uint8 ch, 
                               uint8 cs, 
                               PHY_BUS dq,
                               training_params_t *training_params_ptr,
                               ddrss_rdwr_dqdqs_local_vars *local_vars,
                               uint32 clk_freq_khz,
                               uint8 max_prfs_index)
{    
    uint32          dq0_ddr_phy_base = 0; 
    uint32            reg_offset_dpe = 0;
    uint8                        bit = 0;
    uint8                  byte_lane = 0;
    uint8                 MR13_value = 0;
    uint8                     fsp_op = 0;
    uint8                     fsp_wr = 0;
    uint8        MR14_vref_range_bit = 0;
    uint8            MR14_value_die1 = 0;
    uint8   best_eye_vref_value_die1 = 0;
#if DSF_WR_VREF_BYTE_MODE_EN
	uint8		          MR31_value = 0;
	IO_WIDTH             wr_io_width = X16MODE;
#endif
    uint8           coarse_wrlvl_delay[NUM_DQ_PCH] = {0};
    uint8             fine_wrlvl_delay[NUM_DQ_PCH] = {0};
    uint8    fine_left_start_cdc_value[NUM_DQ_PCH] = {0};
    uint8   fine_right_start_cdc_value[NUM_DQ_PCH] = {0};
    uint32     dq_vref_cdc_delay_in_ps[NUM_DQ_PCH] = {0};  
    
    dbi_struct dbi_struct_info;
    best_eye_struct wr_best_eye_coarse[NUM_DQ_PCH];
    
    uint8          clk_idx = 0;
    uint8  current_clk_inx = 0;
    uint32   half_cycle_ps = 0;
    uint8         freq_inx = 0;    
    uint32          period = 0;    
    
    uint8  scale         = 0;
    uint8  scaled_band   = 0;
    uint32 scaled_freq   = 0;
    uint32 scaled_period = 0;
    uint32 scaled_delay  = 0;
    
    // Training data structure pointer 
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
#if DSF_WR_VREF_BYTE_MODE_EN
	wr_io_width = (cs == 0 )? 
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs0 :
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs1;
#endif


    half_cycle_ps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / 2);
    period        = (CONVERT_CYC_TO_PS / clk_freq_khz);

    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
    // Choose Vref_Range_bit according to frequency threshold.
    MR14_vref_range_bit = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 0: 1;

    
    // Set DBI flag to indicate Enable DBI or not
    reg_offset_dpe = REG_OFFSET_DPE (ch);
    dbi_struct_info.dbi_flag = HWIO_INXF (reg_offset_dpe, DPE_CONFIG_9, DBI_WR);
    
    // Set the number of bits and mapping table for perbit training
    dbi_struct_info.dq_pin_num_max = (dbi_struct_info.dbi_flag == 1) ? 
                                       PINS_PER_PHY_CONNECTED_WITH_DBI : PINS_PER_PHY_CONNECTED_NO_DBI;

    dbi_struct_info.connected_bit_mapping_A = (dbi_struct_info.dbi_flag == 1) ? 
                                               connected_bit_mapping_with_DBI_A : connected_bit_mapping_no_DBI_A;

    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    current_clk_inx = clk_idx + 1;
    
    // Initialize perbit setting, half cycle, full cycle and retimer to 0 before WR training start.
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {   
        // Initialize the WRLVL delays
        coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
        fine_wrlvl_delay  [byte_lane] = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];
    }

    if(current_clk_inx == max_prfs_index)  //only reset per-bit for highest freq. 
    {
      for(byte_lane = 0; byte_lane < dq; byte_lane++)
      {
        for(bit = 0; bit < PINS_PER_PHY; bit++)
        {
            DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                            bit, 
                                            1,  /* 1 for TX. */
                                            cs, 
                                            training_params_ptr->wr_dqdqs.pbit_start_value);
        }
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), training_params_ptr->wr_dqdqs.coarse_cdc_start_value, 1, 1, cs);  //coarse delay
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), training_params_ptr->wr_dqdqs.fine_cdc_top_freq_start_value, 0, 1, cs); //fine delay
      }
    }
    else 
    {
      for(byte_lane = 0; byte_lane < dq; byte_lane++)
      {
      // Zero out the coarse and fine CDC values before training
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), training_params_ptr->wr_dqdqs.coarse_cdc_start_value, 1, 1, cs);
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), training_params_ptr->wr_dqdqs.fine_cdc_start_value, 0, 1, cs);
      }
    }
      
    // ---------------------------------------------------------------------------------
    // Half and full cycle search
    // ---------------------------------------------------------------------------------
    DDRSS_WR_half_full_cycle_search (ddr,
                                    ch,
                                    cs,
                                    dq,
                                    training_data_ptr,
                                    training_params_ptr,
                                    coarse_wrlvl_delay,
                                    fine_wrlvl_delay,
                                    local_vars,
                                    clk_freq_khz,
                                    max_prfs_index);
    // ---------------------------------------------------------------------------------
    // Coarse Training.    
    // ---------------------------------------------------------------------------------
    
    if(current_clk_inx == max_prfs_index)  //only do per-bit training at highest freq
    {    
        // Vref CDC Coarse Training.
        DDRSS_WR_Vref_CDC_Coarse_Schmoo (ddr, 
                                        ch, 
                                        cs,
                                        dq,                                        
                                        training_data_ptr, 
                                        training_params_ptr, 
                                        coarse_wrlvl_delay,
                                        fine_wrlvl_delay,
                                        wr_best_eye_coarse, 
                                        local_vars, 
                                        0,   //first do coarse schmoo with phase 0 only just for pbit training
                                        clk_freq_khz,
                                        max_prfs_index);
        
        // For WR Training, we need Coarse Right and Left CDC Edge values for periodic training.
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {
            training_data_ptr->results.wr_dqdqs.coarse_max_eye_left_boundary_cdc_value[current_clk_inx][ch][cs][byte_lane]  = wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value;
            training_data_ptr->results.wr_dqdqs.coarse_max_eye_right_boundary_cdc_value[current_clk_inx][ch][cs][byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value;   
        }       
    
        // Process vref for die1 and die2.
        if ((current_clk_inx == max_prfs_index) || ( clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))
        {
#if DSF_WR_VREF_BYTE_MODE_EN

		if (wr_io_width == X16MODE)
		{
			best_eye_vref_value_die1 = ((wr_best_eye_coarse[0].best_vref_value + wr_best_eye_coarse[1].best_vref_value) / 2);
        	MR14_value_die1 =((MR14_vref_range_bit << 6) | (best_eye_vref_value_die1 << 0));
			DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR14_value_die1, 0);
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
				MR14_value_die1 =((MR14_vref_range_bit << 6) | (wr_best_eye_coarse[byte_lane].best_vref_value << 0));				
				DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR14_value_die1, 0);
				// Disable the Byte mode
				MR31_value = 0x0;
				BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
        	}
		}
#else
        best_eye_vref_value_die1 = ((wr_best_eye_coarse[0].best_vref_value + wr_best_eye_coarse[1].best_vref_value) / 2);
        MR14_value_die1 =((MR14_vref_range_bit << 6) | (best_eye_vref_value_die1 << 0));
        DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR14_value_die1, 0);  //only update MR14 at top FSP0/768MHz and FSP1/1804MHz
#endif

#if DSF_WR_DQDQS_TRAINING_LOG
            ddr_printf (DDR_NORMAL,"    WR Coarse VREF (die1) = (%d ),\n\n",best_eye_vref_value_die1);
#endif
        }
        
        // FSP value is 0 for 777MHz and 1 for 1036MHz and above.
        fsp_op = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;
        fsp_wr = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;        
        MR13_value = (fsp_op << 7) | (fsp_wr << 6) | (0 << 5) | (0/*high_current_mode*/ << 3) | (0 << 2) | (0 << 0);
        
        // Copy the MR14 value from rank0 into rank1 for 777MHz trainings.
        if (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ)
        {
            BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(1), JEDEC_MR_13, MR13_value); 
			
#if DSF_WR_VREF_BYTE_MODE_EN
		if (wr_io_width == X16MODE)
		{
			best_eye_vref_value_die1 = ((wr_best_eye_coarse[0].best_vref_value + wr_best_eye_coarse[1].best_vref_value) / 2);
        	MR14_value_die1 =((MR14_vref_range_bit << 6) | (best_eye_vref_value_die1 << 0));
			DDRSS_MR_Write_on_die(ddr, ch, 1, JEDEC_MR_14, MR14_value_die1, 0);
		}
		else // if io_width = X8mode
		{
			// Program Vref per DQ byte for rank 1 using the byte mode.
			// MR 31 is used to program Vref/ DQ for rank1
			for(byte_lane = 0; byte_lane < dq; byte_lane++)
        	{
        		//Enable byte mode for individual bytes
        		MR31_value = 1 << (7 - byte_lane) | 0 << (6 + byte_lane); // Enable the byte to receive MR14 values and disable the other Byte
				BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(1), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
				//Program the Vref value
				MR14_value_die1 =((MR14_vref_range_bit << 6) | (wr_best_eye_coarse[byte_lane].best_vref_value << 0));				
				DDRSS_MR_Write_on_die(ddr, ch, 1, JEDEC_MR_14, MR14_value_die1, 0);
				// Disable the Byte mode
				MR31_value = 0x0;
				BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(1), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
        	}
		}		
#else
			DDRSS_MR_Write_on_die(ddr, ch, 1, JEDEC_MR_14, MR14_value_die1, 0);

#endif
        }
        
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {
            training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane] = wr_best_eye_coarse[byte_lane].best_cdc_value;
    
            //copy training Vref (1804MHz and 768MHz Vref values to other frequences where we don't do Vref training)
            if ((current_clk_inx == max_prfs_index) || (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))              
            {
                training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][cs][byte_lane] = wr_best_eye_coarse[byte_lane].best_vref_value;
               // training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][cs][0] = best_eye_vref_value_die1;
    
                if ((clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
                {
                    training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][1][byte_lane] = wr_best_eye_coarse[byte_lane].best_vref_value;
                //    training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][1][0] = best_eye_vref_value_die1;
                }    
            }
            else 
            {
                training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][cs][byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch][cs][byte_lane];
              //  training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][cs][0] = training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[max_prfs_index][ch][cs][0];
                
                // Copy vref value from 1804 rank1 to rank1 for 1017MHz.
                if ((clk_freq_khz < ODT_FPRS_THRESHOLD_FREQ) && (ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
                {
                    training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][1][byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch][1][byte_lane];
                 //   training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][1][0] = training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[max_prfs_index][ch][1][0];
                }
            }
            
            dq_vref_cdc_delay_in_ps[byte_lane] = (training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] * COARSE_STEP_IN_PS);
            
            if(wr_best_eye_coarse[byte_lane].vref_all_fail_flag == 1)
            {
                return FALSE;
            }
        }   
    }   
 
    // ---------------------------------------------------------------------------------
    // Fine Training.    
    // ---------------------------------------------------------------------------------
    
    // Vref CDC Fine Training.
    if(training_params_ptr->wr_dqdqs.fine_training_enable == 1)
    {       
        for (byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
        {            
            // Cdc value for sweeping left. Fine CDC left boundary starting value cannot be less than 0.
            if (wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value == 0) 
            {
               fine_left_start_cdc_value[byte_lane] = 0;
            }
            else 
            {
               if(current_clk_inx == max_prfs_index) 
               {
                    fine_left_start_cdc_value[byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value - 0 * training_params_ptr->wr_dqdqs.coarse_cdc_step;  //per-bit default = 0xF
               }
               else 
               {
                    fine_left_start_cdc_value[byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value - 1 * training_params_ptr->wr_dqdqs.coarse_cdc_step;
               }
            }
            // Cdc value for sweeping right.
            fine_right_start_cdc_value[byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value ;         
        }
        
        if(current_clk_inx == max_prfs_index)  //only do per-bit training at highest freq
        {
            // Write per-bit training, for 1804MHz only.
            DDRSS_wr_pbit_schmoo(ddr, 
                                 ch, 
                                 cs, 
                                 dq,
                                 training_params_ptr, 
                                 local_vars,
                                 fine_right_start_cdc_value,
                                 clk_freq_khz);
                                 
#if DSF_WR_DQS_IO_DCC_TRAINING_EN  
            //Perform Write DQS IO DCC training for 1804MHz only
            DDRSS_WR_DQS_IO_DCC_training (ddr, 
                                          ch,
                                          cs,
                                          training_data_ptr,
                                          training_params_ptr,
                                          local_vars,
                                          clk_freq_khz);
#endif
        }

        if(current_clk_inx == max_prfs_index)
        {
          if (cs == 0)
          {
#if DSF_WR_DQ_DCC_TRAINING_EN
            DDRSS_wr_dqdqs_dq_dcc (ddr,
                                   ch,
                                   cs,
                                   dq,
                                   training_params_ptr,
                                   local_vars,
                                   fine_right_start_cdc_value,
                                   clk_freq_khz);
#endif
          }
           
#if DSF_WR_DQS_DCC_TRAINING_EN
          DDRSS_wr_dqdqs_dqs_dcc (ddr,
                                  ch,
                                  cs,
                                  dq,
                                  training_params_ptr, 
                                  local_vars,
                                  fine_right_start_cdc_value,
                                  clk_freq_khz);
#endif
        }
        // Vref CDC Coarse Training.
        DDRSS_WR_Vref_CDC_Coarse_Schmoo (ddr, 
                                        ch, 
                                        cs, 
                                        dq,
                                        training_data_ptr, 
                                        training_params_ptr, 
                                        coarse_wrlvl_delay,
                                        fine_wrlvl_delay,
                                        wr_best_eye_coarse, 
                                        local_vars, 
                                        2,   //now do coarse schmoo with phase 3
                                        clk_freq_khz,
                                        max_prfs_index);
    
        // For WR Training, we need Coarse Right and Left CDC Edge values for periodic training.
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {
            training_data_ptr->results.wr_dqdqs.coarse_max_eye_left_boundary_cdc_value[current_clk_inx][ch][cs][byte_lane]  = wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value;
            training_data_ptr->results.wr_dqdqs.coarse_max_eye_right_boundary_cdc_value[current_clk_inx][ch][cs][byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value;   
        }       

				// Process vref for die1 and die2.
		if ((current_clk_inx == max_prfs_index) || ( clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))
		{
#if DSF_WR_VREF_BYTE_MODE_EN
		if (wr_io_width == X16MODE)
		{
			best_eye_vref_value_die1 = ((wr_best_eye_coarse[0].best_vref_value + wr_best_eye_coarse[1].best_vref_value) / 2);
        	MR14_value_die1 =((MR14_vref_range_bit << 6) | (best_eye_vref_value_die1 << 0));
			DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR14_value_die1, 0);
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
				MR14_value_die1 =((MR14_vref_range_bit << 6) | (wr_best_eye_coarse[byte_lane].best_vref_value << 0));				
				DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR14_value_die1, 0);
				// Disable the Byte mode
				MR31_value = 0x0;
				BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
        	}
		}

#else
		best_eye_vref_value_die1 = ((wr_best_eye_coarse[0].best_vref_value + wr_best_eye_coarse[1].best_vref_value) / 2);
		MR14_value_die1 =((MR14_vref_range_bit << 6) | (best_eye_vref_value_die1 << 0));
		DDRSS_MR_Write_on_die(ddr, ch, cs, JEDEC_MR_14, MR14_value_die1, 0);  //only update MR14 at top FSP0/768MHz and FSP1/1804MHz
#endif
		
#if DSF_WR_DQDQS_TRAINING_LOG
        ddr_printf (DDR_NORMAL,"    WR 2nd Coarse VREF (die1) = (%d),\n\n",best_eye_vref_value_die1);
#endif
		}

        
        // FSP value is 0 for 777MHz and 1 for 1036MHz and above.
        fsp_op = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;
        fsp_wr = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 1 : 0 ;        
        MR13_value = (fsp_op << 7) | (fsp_wr << 6) | (0 << 5) | (0/*high_current_mode*/ << 3) | (0 << 2) | (0 << 0);
        
		// Copy the MR14 value from rank0 into rank1 for 777MHz trainings.
		if (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ)
		{
			BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(1), JEDEC_MR_13, MR13_value); 
					
#if DSF_WR_VREF_BYTE_MODE_EN
		if (wr_io_width == X16MODE)
		{
			best_eye_vref_value_die1 = ((wr_best_eye_coarse[0].best_vref_value + wr_best_eye_coarse[1].best_vref_value) / 2);
        	MR14_value_die1 =((MR14_vref_range_bit << 6) | (best_eye_vref_value_die1 << 0));
			DDRSS_MR_Write_on_die(ddr, ch, 1, JEDEC_MR_14, MR14_value_die1, 0);
		}
		else // if io_width = X8mode
		{
			// Program Vref per DQ byte for rank 1 using the byte mode.
			// MR 31 is used to program Vref/ DQ for rank1
			for(byte_lane = 0; byte_lane < dq; byte_lane++)
        	{
        		//Enable byte mode for individual bytes
        		MR31_value = 1 << (7 - byte_lane) | 0 << (6 + byte_lane); // Enable the byte to receive MR14 values and disable the other Byte
				BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(1), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
				//Program the Vref value
				MR14_value_die1 =((MR14_vref_range_bit << 6) | (wr_best_eye_coarse[byte_lane].best_vref_value << 0));				
				DDRSS_MR_Write_on_die(ddr, ch, 1, JEDEC_MR_14, MR14_value_die1, 0);
				// Disable the Byte mode
				MR31_value = 0x0;
				BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(1), JEDEC_MR_31, MR31_value); // write to DDR_CS1 = 2
        	}
		}		
#else
			DDRSS_MR_Write_on_die(ddr, ch, 1, JEDEC_MR_14, MR14_value_die1, 0);
		
#endif
		}

        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {
            training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane] = wr_best_eye_coarse[byte_lane].best_cdc_value;
    
            //copy training Vref (1804MHz and 768MHz Vref values to other frequences where we don't do Vref training)
            if ((current_clk_inx == max_prfs_index) || (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))              
            {
                training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][cs][byte_lane] = wr_best_eye_coarse[byte_lane].best_vref_value;
             //   training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][cs][0] = best_eye_vref_value_die1;

                if ((clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
                {
                    training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][1][byte_lane] = wr_best_eye_coarse[byte_lane].best_vref_value;
             //      training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][1][0] = best_eye_vref_value_die1;
                }    
            }
            else 
            {
                training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][cs][byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch][cs][byte_lane];
            //    training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][cs][0] = training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[max_prfs_index][ch][cs][0];
                
                // Copy vref value from 1804 rank1 to rank1 for 1017MHz.
                if ((clk_freq_khz < ODT_FPRS_THRESHOLD_FREQ) && (ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
                {
                    training_data_ptr->results.wr_dqdqs.coarse_vref[current_clk_inx][ch][1][byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch][1][byte_lane];
            //        training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][1][0] = training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[max_prfs_index][ch][1][0];
                }
            }
            
            dq_vref_cdc_delay_in_ps[byte_lane] = (training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] * COARSE_STEP_IN_PS);
            
            if(wr_best_eye_coarse[byte_lane].vref_all_fail_flag == 1)
            {
                return FALSE;
            }
        }
        
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {            
            // Cdc value for sweeping left. Fine CDC left boundary starting value cannot be less than 0.
            if (wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value == 0) 
            {
               fine_left_start_cdc_value[byte_lane] = 0;
            }
            else 
            {
               if(current_clk_inx == max_prfs_index) 
               {
                    fine_left_start_cdc_value[byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value - 0 * training_params_ptr->wr_dqdqs.coarse_cdc_step;  //per-bit default = 0xF
               }
               else 
               {
                    fine_left_start_cdc_value[byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value - 1 * training_params_ptr->wr_dqdqs.coarse_cdc_step;
               }
            }
            
            // Cdc value for sweeping right.
            if((wr_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value + 3) <= COARSE_CDC_MAX_VALUE)
            {
                fine_right_start_cdc_value[byte_lane] = wr_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value + 3;
            }
            else
            {
                fine_right_start_cdc_value[byte_lane] = COARSE_CDC_MAX_VALUE;
            }
        }

        // 1D fine Training for 2nd based on pbit training results. 
        DDRSS_WR_CDC_1D_Schmoo (ddr, 
                                ch, 
                                cs, 
                                dq,
                                training_data_ptr,
                                training_params_ptr, 
                                local_vars,
                                wr_best_eye_coarse, 
                                fine_left_start_cdc_value,
                                fine_right_start_cdc_value,                                           
                                clk_freq_khz,
                                max_prfs_index);
 
        
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {            
            // Write the fine_training values into phy regs and training_params.    
            DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane], 1, 1, cs);  // 1 for coarse_delay_mode. 1 for hp_mode.
            DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), training_data_ptr->results.wr_dqdqs.fine_cdc [current_clk_inx][ch][cs][byte_lane], 0, 1, cs);  // 0 for fine_delay_mode. 1 for hp_mode.
#if DSF_WR_DQDQS_TRAINING_LOG
            ddr_printf (DDR_NORMAL,"    WR Byte %d Training Center : Coarse = %d  Fine = %d,\n",
                         byte_lane,
                         training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane],
                         training_data_ptr->results.wr_dqdqs.fine_cdc [current_clk_inx][ch][cs][byte_lane]);
#endif
            
            DDRSS_CDC_Retimer (ddr, 
                               cs, 
                               training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane], 
                               training_data_ptr->results.wr_dqdqs.fine_cdc [current_clk_inx][ch][cs][byte_lane], 
                               coarse_wrlvl_delay[byte_lane],
                               fine_wrlvl_delay[byte_lane],  
                               (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                               clk_freq_khz);
            
            dq_vref_cdc_delay_in_ps[byte_lane] = ((training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] * COARSE_STEP_IN_PS)
                                                  + (training_data_ptr->results.wr_dqdqs.fine_cdc[current_clk_inx][ch][cs][byte_lane] * FINE_STEP_IN_PS));
                                                  
        } //byte_lane       
    }
    
#if DSF_WR_DQDQS_TRAINING_LOG
    ddr_printf (DDR_NORMAL,"\n");
#endif

    // Get the frequency index.
    freq_inx = DDRSS_Get_Freq_Index (ddr, clk_freq_khz);
    
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {      
        DDRSS_writing_ext_CSR_lpddr4 (ddr,
                                      ch,
                                      cs,
                                      0,
                                      (training_data *)(&ddr->flash_params.training_data),
                                      TRAINING_TYPE_WR_DQDQS,
                                      byte_lane,
                                      freq_inx); 
    }
    
    // Scaling for frequencies below training
    if(clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ)
    {
      for (scale = 0; scale < NUM_SCALE_BANDS; scale++)
      {
        // Frequency target for scaling
        scaled_freq = SCALE_FREQ(scale);
        
        // Clock period for scaled frequency
        scaled_period = (CONVERT_CYC_TO_PS / scaled_freq);
        
        // Band for scaled result
        scaled_band = SCALE_BAND(scale);
        
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {
            scaled_delay = dq_vref_cdc_delay_in_ps[byte_lane];
            
            // Convert the delay value based on half_cycle for the trained frequency
            if(training_data_ptr->results.wr_dqdqs.dq_half_cycle[current_clk_inx][ch][cs][byte_lane] == 1)
            {
                scaled_delay += half_cycle_ps;
            }
            
            // Remove T/4 from trained frequency
            scaled_delay -= period / 4;
            
            // Add T/4 from scaled frequency
            scaled_delay += scaled_period / 4;
            
            // Account for half-cycle if greater than T/2
            if(scaled_delay >= (scaled_period / 2))
            {
                training_data_ptr->results.wr_dqdqs.dq_half_cycle[scaled_band][ch][cs][byte_lane] = 1;
                scaled_delay -= (scaled_period / 2);
            }
            else
            {
                training_data_ptr->results.wr_dqdqs.dq_half_cycle[scaled_band][ch][cs][byte_lane] = 0;
            }
            
            // Limit in case of overflow to 1250ps.
            if(scaled_delay >= (COARSE_STEP_IN_PS * COARSE_CDC_MAX_VALUE))
            {
                scaled_delay = (COARSE_STEP_IN_PS * COARSE_CDC_MAX_VALUE);
            }
            
            // Calculate coarse delay
            training_data_ptr->results.wr_dqdqs.coarse_cdc[scaled_band][ch][cs][byte_lane] = (scaled_delay / COARSE_STEP_IN_PS);
            
            // Calculate fine delay
            training_data_ptr->results.wr_dqdqs.fine_cdc[scaled_band][ch][cs][byte_lane] = ((scaled_delay % COARSE_STEP_IN_PS) / FINE_STEP_IN_PS);
            
            // Set retimer based on coarse and fine cdc.
            DDRSS_CDC_Retimer (ddr, cs,
                               training_data_ptr->results.wr_dqdqs.coarse_cdc[scaled_band][ch][cs][byte_lane],
                               training_data_ptr->results.wr_dqdqs.fine_cdc[scaled_band][ch][cs][byte_lane],
                               coarse_wrlvl_delay[byte_lane],
                               fine_wrlvl_delay[byte_lane],
                               (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                               scaled_freq);
            
            DDRSS_writing_ext_CSR_lpddr4 (ddr,
                                  ch,
                                  cs,
                                  0,
                                  (training_data *)(&ddr->flash_params.training_data),
                                  TRAINING_TYPE_WR_DQDQS,
                                  byte_lane,
                                  scaled_band);
            
            // Reset back 768MHz retimer value.
            DDRSS_CDC_Retimer (ddr, cs,
                               training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane],
                               training_data_ptr->results.wr_dqdqs.fine_cdc[current_clk_inx][ch][cs][byte_lane],
                               coarse_wrlvl_delay[byte_lane],
                               fine_wrlvl_delay[byte_lane],
                               (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                               clk_freq_khz);
        } //byte_lane.
      } // scale
    } //clk_freq
    
    return TRUE;

}


// -------------------------------------------------------------------------
// Low-Speed WR Training for band0/1.
// -------------------------------------------------------------------------
boolean DDRSS_wr_dqdqs_lpddr4_tdqs2dq_cal (DDR_STRUCT *ddr, 
                                           uint8 ch, 
                                           uint8 cs, 
                                           PHY_BUS dq,
                                           training_params_t *training_params_ptr, 
                                           uint32 clk_freq_khz)
{
    uint16                       period = 0;
    uint8                     byte_lane = 0;
    uint32             dq0_ddr_phy_base = 0;
    uint32                  tdqs2dq_min = 0;
    uint8                      freq_inx = 0;
    uint8              coarse_cdc_value = 0;
    uint8                fine_cdc_value = 0;  
    uint8                 dq_half_cycle = 0;
	uint8                 retimer_value = 0;
    uint16            dit_runtime_count = 0; 
	IO_WIDTH               dit_io_width = X16MODE;
    
    uint16                    tdqs2dq[NUM_DIE_PCH] = {0}; 
    uint16  dit_count[NUM_CH][NUM_CS][NUM_DIE_PCH] = {{{0}}};
    
    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
    
    // Base pointer to DDR_PHY
    dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch)+ DQ0_DDR_PHY_OFFSET;
    
    // Calculate T/4
    period = CONVERT_CYC_TO_PS / clk_freq_khz;
	dit_io_width = (cs == 0 )? 
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs0 :
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs1;

    dit_runtime_count = training_data_ptr->results.dit.dit_runtime_count;

    DDRSS_DIT_Read (ddr, ch, cs, training_params_ptr, 0, dit_count, clk_freq_khz);

    tdqs2dq[0] = ((period * dit_runtime_count) / (2 * dit_count[ch][cs][0]));
	ddr_printf(DDR_NORMAL, " TDQS2DQ in ps for Channel %d Rank %d die 0 = %d ps\n",ch,cs, tdqs2dq[0] );
	tdqs2dq[1] = 0;
//	training_data_ptr->results.dit.dit_count[ch][cs][0] = tdqs2dq[0];
//	training_data_ptr->results.dit.dit_count[ch][cs][1] = 0;
	if (dit_io_width == X8MODE)
	{
		tdqs2dq[1] = ((period * dit_runtime_count) / (2 * dit_count[ch][cs][1]));
		ddr_printf(DDR_NORMAL, " TDQS2DQ in ps for Channel %d Rank %d die 1 = %d ps\n",ch,cs, tdqs2dq[1] );
//		training_data_ptr->results.dit.dit_count[ch][cs][1] = tdqs2dq[1];
	}
	
    // Choose the min value of the two dies.
    tdqs2dq_min = (dit_io_width == X8MODE ) ?
    				((tdqs2dq[0]< tdqs2dq[1]) ? tdqs2dq[0] : tdqs2dq[1]) 
    				: tdqs2dq[0]; /*((tdqs2dq[0]< tdqs2dq[1]) ? tdqs2dq[0] : tdqs2dq[1]);*/
    
    
    if(tdqs2dq_min > LOW_SPEED_HALF_CYC_CONV_THRESHOLD)
    {
        dq_half_cycle = 1;
        coarse_cdc_value = 0;
        fine_cdc_value = 0;		
		retimer_value = LOW_SPEED_HALF_CYC_RETIMER_VALUE;	
        #if DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_LOG
        ddr_printf(DDR_NORMAL, "  WR TDQS2DQ Channel %d Rank %d = HALF Cycle\n",ch,cs);
        #endif
    }
    else 
    {
        dq_half_cycle = 0;
        coarse_cdc_value = LOW_SPEED_NO_HALF_CYC_COARSE_CDC_VALUE;
        fine_cdc_value = LOW_SPEED_NO_HALF_CYC_FINE_CDC_VALUE;
		retimer_value = LOW_SPEED_NO_HALF_CYC_RETIMER_VALUE;
        #if DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_LOG
        ddr_printf(DDR_NORMAL, "  WR TDQS2DQ Channel %d Rank %d Coarse = %d Fine = %d\n",ch,cs,coarse_cdc_value, fine_cdc_value);
        #endif        
    }
        
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {        
        for(freq_inx = 0; freq_inx <= 0; freq_inx++) // For band0 only
        {
            // Save results
            training_data_ptr->results.wr_dqdqs.fine_cdc[freq_inx][ch][cs][byte_lane] = fine_cdc_value;
            training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_inx][ch][cs][byte_lane] = coarse_cdc_value;
            training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq_inx][ch][cs][byte_lane] = dq_half_cycle;
            training_data_ptr->results.wr_dqdqs.dq_retmr[freq_inx][ch][cs][byte_lane] = retimer_value;
            
          
    
            // Update Registers.
            DDR_PHY_hal_cfg_cdcext_slave_wr ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                                cs,
                                                training_data_ptr->results.wr_dqdqs.fine_cdc[freq_inx][ch][cs][byte_lane],
                                                0/*fine*/,
                                                HP_MODE,
                                                freq_inx);
                                                
            DDR_PHY_hal_cfg_cdcext_slave_wr ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                                cs,
                                                training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_inx][ch][cs][byte_lane],
                                                1/*coarse*/,
                                                HP_MODE,
                                                freq_inx);
        
            DDR_PHY_hal_cfg_wrext_ctl_update ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                                freq_inx,
                                                cs,
                                                training_data_ptr->results.wr_dqdqs.dq_retmr[freq_inx][ch][cs][byte_lane],
                                                training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq_inx][ch][cs][byte_lane],
                                                0);  // dq_full_cycle = 0.
                                                
        } //freq_inx.
    } //byte_lane.
    
    return TRUE;
    
}




