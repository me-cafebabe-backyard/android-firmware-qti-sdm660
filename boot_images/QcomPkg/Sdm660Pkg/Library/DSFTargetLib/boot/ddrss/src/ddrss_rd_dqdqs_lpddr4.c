/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_rd_dqdqs_lpddr4.c#6 $
$DateTime: 2017/02/06 06:08:34 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
06/20/14   jeasley      Removed training_data pointer.
06/19/14   jeasley      Add passband_info_(left/right).  Correct mid address.
06/18/14   jeasley      Remove subtract 1 from right edge.
06/13/14   jeasley      Update Global VREF after training.
06/11/14   jeasley      Add final CDC update, correct compare result accumulation
05/27/14   jeasley      Added CDC update routines during coarse and fine loops
05/07/14   jeasley      Modified coarse_odd_flag calculation.  Added offset references
                        for DDR PHY DQ addresses. 
05/07/14   jeasley      Added DDRSS_mem_write, updated code per review with Prabha.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include <string.h>

extern uint8 dq_dbi_bit;
extern uint8 dq_spare_bit;


// -------------------------------------------------------------------------
// DDR PHY RD DQ-DQS Training 
// -------------------------------------------------------------------------
boolean DDRSS_rd_dqdqs_lpddr4 (DDR_STRUCT *ddr, 
                               uint8 ch, 
                               uint8 cs, 
                               PHY_BUS ca,
                               PHY_BUS dq,
                               training_params_t *training_params_ptr,
                               ddrss_rdwr_dqdqs_local_vars *local_vars,
                               uint32 clk_freq_khz,
                               uint8  max_prfs_index)
{ 
    uint8 dq_pin_num      = 0;
    uint8 byte_lane       = 0;
  //  uint8 ca_lane         = 0;
    uint8 bit             = 0;
    uint8 clk_idx         = 0;
    uint8 current_clk_inx = 0;
    uint8 mp_hp           = 0;
    uint8 scale           = 0;
    uint32 scaled_dq_vref_cdc_delay_in_ps = 0;
   // uint8 best_vref_per_ca[NUM_CA_PCH] = {0};
    dbi_struct dbi_struct_info;
    best_eye_struct rd_best_eye_coarse[NUM_DQ_PCH];
    best_eye_struct   rd_best_eye_fine[NUM_DQ_PCH][PINS_PER_PHY];
    uint8              perbit_mid_max_left [NUM_DQ_PCH] = {0};
    uint8              perbit_mid_min_right[NUM_DQ_PCH] = {0};
    uint8                   perbit_mid_min [NUM_DQ_PCH] = {0};
    uint32          dq_vref_cdc_delay_in_ps[NUM_DQ_PCH] = {0};
    
    uint8 fine_start_vref_value                  =  0;
    uint8 fine_max_vref_value                    =  0;
    uint8 fine_left_start_cdc_value[NUM_DQ_PCH]  = {0};
    uint8 fine_right_start_cdc_value[NUM_DQ_PCH] = {0};
    uint8 coarse_center   [NUM_DQ_PCH]           = {0};
    uint32 dq0_ddr_phy_base                      =  0;
    uint32 reg_offset_dpe                        =  0;

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
 
    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

    // Set mp-hp bit for Vref selection
    //mp_hp = (clk_freq_khz <= F_RANGE_3) ? MPRX : HPRX;
    mp_hp = (clk_freq_khz <= HIGHEST_MPVREF_PRFS_FREQ) ? MPVREF : HPVREF;
    
    // Set DBI flag to indicate Enable DBI or not
    reg_offset_dpe = REG_OFFSET_DPE (ch);

    dbi_struct_info.dbi_flag = HWIO_INXF (reg_offset_dpe, DPE_CONFIG_9, DBI_RD);
    dbi_struct_info.dq_pin_num_max = (dbi_struct_info.dbi_flag == 1) ? 
                                       PINS_PER_PHY_CONNECTED_WITH_DBI 
                                    :  PINS_PER_PHY_CONNECTED_NO_DBI;

    dbi_struct_info.connected_bit_mapping_A = (dbi_struct_info.dbi_flag == 1) ? 
                                               connected_bit_mapping_with_DBI_A 
                                            :  connected_bit_mapping_no_DBI_A;    
   
    // Calculate the maximum training clock frequency index
    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
        if (clk_freq_khz >= freq_range[clk_idx-1])
            break;
    }
    current_clk_inx = clk_idx + 1;
    
    // Initialize the CDC and VREF registers
    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        // Zero out the coarse and fine CDC values before training
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 0, 1, 1, cs);
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 0, 0, 1, cs);
    
        // Set the local per-bit VREF to LOCAL_VREF_MID_VALUE
        for(dq_pin_num = 0; dq_pin_num < PINS_PER_PHY; dq_pin_num++)
        {
            if (current_clk_inx == max_prfs_index)
            {
                DDR_PHY_hal_cfg_local_vref (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                            LOCAL_VREF_MID_VALUE, 
                                            cs,
                                            dq_pin_num                                            
                                            );
            }
    
            perbit_mid_min_right[byte_lane] = 0xFF;
        }
    }    
    
    // ---------------------------------------------------------------------------------
    // Coarse Training.    
    // ---------------------------------------------------------------------------------
    
    // Step 2: Vref CDC Coarse Training.
    DDRSS_RD_Vref_CDC_Coarse_Schmoo (ddr,
                                     ch,
                                     cs,
                                     ca,
                                     dq,
                                     training_data_ptr,
                                     training_params_ptr, 
                                     rd_best_eye_coarse, 
                                     local_vars, 
                                     clk_freq_khz,
                                     current_clk_inx,
                                     max_prfs_index);

    //Average of 2 DQ Vref's are programmed in corresponding CA Vref 
   // best_vref_per_ca[0] = (rd_best_eye_coarse[0].best_vref_value + rd_best_eye_coarse[1].best_vref_value) / 2;
    // Load the data structure with the final coarse values

#if DSF_RD_DQDQS_TRAINING_LOG
    ddr_printf(DDR_NORMAL, "\n");
#endif

    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {
        // Use the trained global VREF if the current frequency is the maximum 
        if ((current_clk_inx == max_prfs_index) && (cs == 0))
        {
        	// Check for minimum vref, if trained value is less than the minimum Vref then set the min Vref as the best Vref
        	if(rd_best_eye_coarse[byte_lane].best_vref_value < training_params_ptr->rd_dqdqs.coarse_vref_low_limit_hprx)
        	{
        		rd_best_eye_coarse[byte_lane].best_vref_value = training_params_ptr->rd_dqdqs.coarse_vref_low_limit_hprx ;
        	}
            DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                        rd_best_eye_coarse[byte_lane].best_vref_value,
                                        clk_freq_khz,
                                        cs);
    
            training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][0][byte_lane] = rd_best_eye_coarse[byte_lane].best_vref_value;
            training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][1][byte_lane] = rd_best_eye_coarse[byte_lane].best_vref_value;
#if DSF_RD_DQDQS_TRAINING_LOG
            ddr_printf(DDR_NORMAL, "  DQ %d Global VREF = %d,\n",
                       byte_lane,rd_best_eye_coarse[byte_lane].best_vref_value);
#endif
        }
        // Use the maximum frequency global VREF for the other terminated clock frequencies 
        else if (clk_freq_khz > LOWEST_TRAINED_FPRS_FREQ)          
        {
            // Use the max frequency global VREF for all frequencies below the maximum
            DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                        training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][0][byte_lane],
                                        clk_freq_khz,
                                        0); // Rank 0
        }
        // Unterminated clock frequencies
        else if (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ)          
        {
            DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                        rd_best_eye_coarse[byte_lane].best_vref_value,
                                        clk_freq_khz,
                                        0);
            
            // Copy the unterminated global rank 0 VREF to rank 1
            if  (ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH)
            {
                DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                            rd_best_eye_coarse[byte_lane].best_vref_value,
                                            clk_freq_khz,
                                            1);
            }

#if DSF_RD_DQDQS_TRAINING_LOG
          ddr_printf(DDR_NORMAL, "  DQ %d Global VREF = %d,\n",
                     byte_lane,rd_best_eye_coarse[byte_lane].best_vref_value);
#endif
            training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][0][byte_lane] = rd_best_eye_coarse[byte_lane].best_vref_value;
            training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][1][byte_lane] = rd_best_eye_coarse[byte_lane].best_vref_value;

        }
       

    } 
    for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
    {
        
        if(rd_best_eye_coarse[byte_lane].vref_all_fail_flag == 1)
        {
            return FALSE;
        }
        training_data_ptr->results.rd_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane] = rd_best_eye_coarse[byte_lane].best_cdc_value;
    }

    // ---------------------------------------------------------------------------------
    // Fine Training.    
    // ---------------------------------------------------------------------------------
    
    if(training_params_ptr->rd_dqdqs.fine_training_enable == 1)
    {
        // Calculate the fine VREF start and maximum values
        if(training_params_ptr->rd_dqdqs.fine_vref_enable == 1)
        {
          if(mp_hp == HPVREF)
          {
              if (current_clk_inx == max_prfs_index)
              {
                  fine_start_vref_value = training_params_ptr->rd_dqdqs.fine_vref_start_value;                
                  fine_max_vref_value   = training_params_ptr->rd_dqdqs.fine_vref_max_value;
              }
              
          }
          else
          {
              fine_start_vref_value = LOCAL_VREF_MID_VALUE;
              fine_max_vref_value   = LOCAL_VREF_MID_VALUE;
          }
            
        }
        else
        {
            // If fine_vref_enable is not enabled (ie., = 0), 
            // then there is no vref schmoo and the best_vref_value found from coarse training is the only vref 
            // (start as well as max) available for fine training.
            fine_start_vref_value = LOCAL_VREF_MID_VALUE;
            fine_max_vref_value   = LOCAL_VREF_MID_VALUE;
        }
        
#if DSF_RD_DQDQS_TRAINING_LOG
        ddr_printf(DDR_NORMAL,"\n");
#endif
        
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {    
#if DSF_RD_DQDQS_TRAINING_LOG
            ddr_printf(DDR_NORMAL,"  RD Byte %d Left Boundary = %d Right Boundary = %d,\n",byte_lane,
                       rd_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value,
                       rd_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value);
#endif

            // CDC value for sweeping left. Fine CDC left boundary starting value cannot be less than 0
            if (rd_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value == 0) 
            {
                rd_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value = 0;
            }
            else 
            {
                rd_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value -= 1;
            }
            
            // CDC value for sweeping right. Check for odd sum of left and right boundary
            if (((rd_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value + 
                  rd_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value) & 0x1) == 0x1)  
            {
                rd_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value -= 1; 
            }
            fine_left_start_cdc_value[byte_lane]  = rd_best_eye_coarse[byte_lane].max_eye_left_boundary_cdc_value; 
            fine_right_start_cdc_value[byte_lane] = rd_best_eye_coarse[byte_lane].max_eye_right_boundary_cdc_value; 
        
            // Set coarse start for fine left schmoo 
            DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                          fine_left_start_cdc_value[byte_lane], 
                                          0x1, // coarse set
                                          0x1, 
                                          cs);   
        } // byte_lane
    
        // Sweep the fine left edge
        DDRSS_RD_Vref_CDC_Fine_Schmoo (ddr, 
                                       ch, 
                                       cs, 
                                       dq,
                                       training_data_ptr, 
                                       training_params_ptr, 
                                       fine_start_vref_value, 
                                       fine_max_vref_value, 
                                       local_vars->ddrss_rdwr_fine_cdc_boundary.fine_left_boundary_cdc_value, 
                                       SWEEP_LEFT,
                                       local_vars,
                                       clk_freq_khz,
                                       current_clk_inx,
                                       max_prfs_index,
                                       &dbi_struct_info);

        // Set start coarse CDC for fine sweep right search
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                          fine_right_start_cdc_value[byte_lane], 
                                          0x1, // coarse set
                                          0x1, 
                                          cs);   
        }
        
        // Fine sweep the right edge
        DDRSS_RD_Vref_CDC_Fine_Schmoo (ddr, 
                                       ch, 
                                       cs,
                                       dq,
                                       training_data_ptr, 
                                       training_params_ptr, 
                                       fine_start_vref_value, 
                                       fine_max_vref_value, 
                                       local_vars->ddrss_rdwr_fine_cdc_boundary.fine_right_boundary_cdc_value, 
                                       SWEEP_RIGHT, 
                                       local_vars,
                                       clk_freq_khz,
                                       current_clk_inx,
                                       max_prfs_index,
                                       &dbi_struct_info);
        
        
        // Step 4 for Fine Training: Find the best vref and cdc edges and values and populate best_eye_ptr.
#if DSF_RD_DQDQS_TRAINING_LOG
        ddr_printf(DDR_NORMAL,"\n");
#endif
        
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for (bit = 0; bit < PINS_PER_PHY; bit ++)
            {
                DDRSS_Post_Histogram_Fine_Best_Eye_Cal (rd_best_eye_fine, 
                                                        local_vars->ddrss_rdwr_fine_cdc_boundary.fine_left_boundary_cdc_value, 
                                                        local_vars->ddrss_rdwr_fine_cdc_boundary.fine_right_boundary_cdc_value, 
                                                        fine_start_vref_value, 
                                                        fine_max_vref_value, 
                                                        training_data_ptr, 
                                                        training_params_ptr, 
                                                        0x2, 
                                                        byte_lane,
                                                        bit);

                if (current_clk_inx == max_prfs_index)
                {
                    // Populate the trained local vref values to the registers and the data structure              
                    DDR_PHY_hal_cfg_local_vref (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                rd_best_eye_fine[byte_lane][bit].best_vref_value,
                                                cs,
                                                bit                                            
                                                );
  
                    training_data_ptr->results.rd_dqdqs.perbit_vref[ch][cs][byte_lane][bit] = 
                                      rd_best_eye_fine[byte_lane][bit].best_vref_value;
                }
            }
        }

        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for (bit = 0; bit < PINS_PER_PHY; bit ++)
            {
                if (!((bit == dq_dbi_bit) || (bit == dq_spare_bit)))
                {
                    if (rd_best_eye_fine[byte_lane][bit].max_eye_left_boundary_cdc_value > perbit_mid_max_left[byte_lane])
                    {
                        perbit_mid_max_left [byte_lane] = rd_best_eye_fine[byte_lane][bit].max_eye_left_boundary_cdc_value;
                    }
                    if (rd_best_eye_fine[byte_lane][bit].max_eye_right_boundary_cdc_value < perbit_mid_min_right[byte_lane])
                    {
                        perbit_mid_min_right[byte_lane] = rd_best_eye_fine[byte_lane][bit].max_eye_right_boundary_cdc_value;
                    }
                }
            }
            
            // Calculate the fine CDC based on the fine left and right first failing bits
            perbit_mid_min [byte_lane] = (perbit_mid_max_left[byte_lane] + perbit_mid_min_right[byte_lane])/2;
        }
#if DSF_RD_DQDQS_TRAINING_LOG        
        ddr_printf(DDR_NORMAL, "\n");
#endif
        
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {     
            // Finish by setting the coarse and fine center values        
            coarse_center[byte_lane] = (fine_left_start_cdc_value[byte_lane] + fine_right_start_cdc_value[byte_lane])/2;

            DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                          coarse_center[byte_lane],
                                          0x1, // coarse set
                                          0x1, 
                                          cs);   
    
            // Fine trained fine value
            DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                          perbit_mid_min[byte_lane], 
                                          0x0, // fine set
                                          0x1, 
                                          cs); 
            
            training_data_ptr->results.rd_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane] = coarse_center[byte_lane];
            training_data_ptr->results.rd_dqdqs.fine_cdc   [current_clk_inx][ch][cs][byte_lane] = perbit_mid_min[byte_lane];
            
#if DSF_RD_DQDQS_TRAINING_LOG
            ddr_printf(DDR_NORMAL,"    DQ %d RD Center : Coarse = %d  Fine = %d,\n", 
                                  byte_lane, coarse_center[byte_lane],perbit_mid_min[byte_lane]);
#endif
            
            // Calculate CDC total delay in ps
            dq_vref_cdc_delay_in_ps[byte_lane] = 
            ((training_data_ptr->results.rd_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] * COARSE_STEP_IN_PS) +
                (training_data_ptr->results.rd_dqdqs.fine_cdc[current_clk_inx][ch][cs][byte_lane] * FINE_STEP_IN_PS));
        
        } //byte_lane.
#if DSF_RD_DQDQS_TRAINING_LOG
        ddr_printf(DDR_NORMAL,"\n");
#endif
        
        if ((clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))          
        {
            // For 800MHz copy the rank0 value to rank1 to store in data structure          
            for(byte_lane = 0; byte_lane < dq; byte_lane++)
            {
                training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][0][byte_lane] = rd_best_eye_coarse[byte_lane].best_vref_value;
                training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][1][byte_lane] = rd_best_eye_coarse[byte_lane].best_vref_value;
            }
        }
        // Scale training values
        if(clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ)
        {
          for (scale = 0; scale < NUM_SCALE_BANDS; scale++)
          {
            for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {                            
                scaled_dq_vref_cdc_delay_in_ps = ((clk_freq_khz * dq_vref_cdc_delay_in_ps[byte_lane]) / SCALE_FREQ(scale));
                DDRSS_midpoint_to_CDC_lpddr4 (ddr,
                                              scaled_dq_vref_cdc_delay_in_ps, 
                                              clk_freq_khz, 
                                              ch, 
                                              cs, 
                                              (training_data *)(&ddr->flash_params.training_data), 
                                              2,  // 2 for rd-dqdqs
                                              byte_lane,
                                              SCALE_BAND(scale));
                
            } //byte_lane 
          } // scale            
        } // clk_freq_khz
    }
    
    // Populate the CDC EXT registers
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {
        DDR_PHY_hal_cfg_cdcext_slave_rd ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                          cs,
                                          coarse_center[byte_lane],
                                          1/*coarse*/,
                                          HP_MODE,
                                          current_clk_inx
                                          );
     
        DDR_PHY_hal_cfg_cdcext_slave_rd ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                          cs,
                                          perbit_mid_min[byte_lane],
                                          0/*fine*/,
                                          HP_MODE,
                                          current_clk_inx
                                          );
    
        // Copy the rank0 value to rank1 registers and store in the data structure.
        if ((clk_freq_khz < HIGHEST_RANK_EN_FREQ) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))                    
        {
            DDR_PHY_hal_cfg_cdcext_slave_rd ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                              1,
                                              coarse_center[byte_lane],
                                              1/*coarse*/,
                                              HP_MODE,
                                              current_clk_inx
                                              );
        
            DDR_PHY_hal_cfg_cdcext_slave_rd ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                              1,
                                              perbit_mid_min[byte_lane],
                                              0/*fine*/,
                                              HP_MODE,
                                              current_clk_inx
                                              );
    
            training_data_ptr->results.rd_dqdqs.coarse_cdc[current_clk_inx][ch][1][byte_lane] = coarse_center[byte_lane];
            training_data_ptr->results.rd_dqdqs.fine_cdc  [current_clk_inx][ch][1][byte_lane] = perbit_mid_min[byte_lane];
        }
    }
    
    return TRUE; 
    
}
