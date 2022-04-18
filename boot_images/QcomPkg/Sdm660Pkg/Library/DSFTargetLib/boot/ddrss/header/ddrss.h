/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/header/ddrss.h#9 $
$DateTime: 2017/03/08 03:07:43 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __DDRSS_H__
#define __DDRSS_H__

#include "HAL_SNS_DDR.h"
#include "ddr_ss_seq_hwioreg.h"
#include "ddr_ss_seq_hwiobase.h"

#define DIT_NORMAL_DELTA          20

#define DIT_FINE_STEP_LIMIT       (FINE_STEPS_PER_COARSE - 1) //4
#define DIT_FINE_STEP_IN_PS       FINE_STEP_IN_PS //10
#define DIT_INTERVAL_PER_SEC      4

#define NUM_PHY_PCC_LL            64 // Number of PCC Link List Elements
#define NUM_CC_PCC_LL             60 // Number of PCC Link List Elements

#include "ddrss_training.h"
#include "bimc.h"
#include "dtts_load_ram.h"

#include "ddr_phy.h"
#include "ddr_phy_config.h"

#include "mccc.h"
#include "ddr_cc_mccc.h"

#include "target_config.h"

// Define in ddrss_phy_wrapper.c
void DDR_PHY_CC_Config(DDR_STRUCT *ddr);
boolean DDR_PHY_Init_GHS (DDR_STRUCT *ddr, DDR_CHANNEL channel);
void DDR_PHY_CC_init (DDR_STRUCT *ddr, DDR_CHANNEL channel);

// PHY eCDT.
void DDR_PHY_CC_eCDT_Override(DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL channel);  
   
/***************************************************************************************************
 Common training functions
 ***************************************************************************************************/
boolean DDRSS_boot_training_lpddr4 (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
void DDRSS_training_restore_lpddr4 (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
boolean DDRSS_Post_Boot_Training(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);

uint8 DDRSS_Get_Freq_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz);
uint32 DDRSS_Get_Highest_Freq_In_PRFS_Band (DDR_STRUCT *ddr, uint32 prfs_index);
void DDRSS_Get_Training_Address(DDR_STRUCT *ddr);

void DDRSS_MR_Write_on_die (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 MR_addr, uint8 MR_data,uint8 die);



void DDRSS_Post_Histogram_Coarse_Horizon_Eye_Max_Rectangle (DDR_STRUCT *ddr,
                                              uint8 ch,
                                              uint8 cs,
                                              best_eye_struct *best_eye_ptr,
                                              uint8 (*coarse_fail_count_ptr)[COARSE_VREF][COARSE_CDC],
                                              training_data *training_data_ptr,
                                              training_params_t *training_params_ptr,
                                              uint8 training_type,  /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                                              uint8 phy_inx,
                                              uint32 clk_freq_khz,
                                              uint8 current_clk_inx,
                                              uint8 max_prfs_index
                                             );
uint16 Max_sub_area_histogram(uint8 *sub_area_histogram_ptr,
                                       uint8 *rectangle_left_cdc,
                                       uint8 *rectangle_right_cdc,
                                       uint8 *rectangle_bottom_vref,
                                       uint8 start_width_value,
                                       uint8 max_width_value
                                       );
uint16 sub_histogram_max_rect_area(uint8 *hist_sum_arr_ptr,
                                       uint8 *rectangle_left_cdc,
                                       uint8 *rectangle_right_cdc,
                                       uint8 *rectangle_bottom_vref,
                                       uint8 start_width_value,
                                       uint8 max_width_value
                                       );


void DDRSS_Post_Histogram_Fine_Each_Boundary (uint8 (*fine_fail_count_ptr)[PINS_PER_PHY][FINE_VREF][FINE_CDC],
                                              uint8 (*boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                              uint8 start_vref,
                                              uint8 max_vref,
                                              training_data *training_data_ptr,
                                              training_params_t *training_params_ptr,
                                              uint8 left_right,
                                              uint8 training_type,
                                              uint8 phy_inx,
                                              uint8 bit
                                             );

void DDRSS_Post_Histogram_RD_Fine_Each_Boundary (uint8 (*fine_fail_count_ptr)[PINS_PER_PHY][FINE_VREF][FINE_RD_CDC],
                                                 uint8 (*boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                                 uint8 start_vref,
                                                 uint8 max_vref,
                                                 training_data *training_data_ptr,
                                                 training_params_t *training_params_ptr,
                                                 uint8 left_right,
                                                 uint8 phy_inx,
                                                 uint8 bit
                                                );

void DDRSS_Post_Histogram_Fine_Best_Eye_Cal (best_eye_struct (*best_eye_ptr)[PINS_PER_PHY],
                                             uint8 (*left_boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                             uint8 (*right_boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                             uint8 start_vref, 
                                             uint8 max_vref,   
                                             training_data *training_data_ptr,
                                             training_params_t *training_params_ptr,
                                             uint8 training_type, /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                                             uint8 phy_inx,
                                             uint8 bit   
                                            );

uint8 DDRSS_CDC_Retimer_Value (
                        uint8 coarse_dqs_delay,
                        uint8 fine_dqs_delay,
                        uint8 coarse_wrlvl_delay,
                        uint8 fine_wrlvl_delay,
                        uint32 clk_freq_khz
                       );
                                            
void DDRSS_CDC_Retimer (DDR_STRUCT *ddr,
                        uint8 cs,
                        uint8 coarse_dqs_delay,
                        uint8 fine_dqs_delay,
                        uint8 coarse_wrlvl_delay,
                        uint8 fine_wrlvl_delay,
                        uint32 cadq_ddr_phy_base,
                        uint32 clk_freq_khz
                       );

boolean DDRSS_midpoint_to_CDC_lpddr4 (DDR_STRUCT *ddr,
                               uint32 middle, 
                               uint32 clk_freq_in_khz,  
                               uint8  ch,
                               uint8  cs,
                               training_data *training_data_ptr,
                               uint8  training_type,
                               uint8  phy_inx,
                               uint8 freq_inx
                              );

void DDRSS_writing_ext_CSR_lpddr4 (DDR_STRUCT *ddr,
                                   uint8 ch, 
                                   uint8 cs, 
                                   wrlvl_params_struct *convert_cdc_ptr,  
                                   training_data *training_data_ptr,
                                   uint8 training_type,
                                   uint8 phy_inx,
                                   uint8 freq_inx
                                  );

void DDRSS_cdc_convert (DDR_STRUCT *ddr, 
                        wrlvl_params_struct *wrlvl_params_ptr, 
                        uint32 wrlvl_delay, 
                        uint32 period, 
                        uint8  training_type, 
                        uint8 half_cycle, 
                        uint8 full_cycle);

uint16 DDRSS_dq_remapping (uint8 pattern);
void ddr_mem_copy(uint32 * source, uint32 * destination, uint32 size, uint32 burst);

/***************************************************************************************************
 CA Vref training
 ***************************************************************************************************/



boolean DDRSS_Vrefonly_lpddr4  (DDR_STRUCT    *ddr,
                       uint8         ch,  
                       uint8         cs, 
                       PHY_BUS       ca,
                       uint8         prfs_index,
                       training_params_t *training_params_ptr,
                       ddrss_ca_vref_local_vars *local_vars,
                       uint32 clk_freq_khz
                      );

void DDRSS_passing_region_scan( uint8 *start, uint8 *stop, uint8 fail_count_histogram[], uint32 histogram_size);

void BIMC_Set_CA_Training_Pattern( uint8 ch, 
                                   uint16 pre_rising_pattern, 
                                   uint16 pre_falling_pattern, 
                                   uint16 rising_pattern, 
                                   uint16 falling_pattern, 
                                   uint16 post_rising_pattern, 
                                   uint16 post_falling_pattern);

void BIMC_Send_CA_Pattern(uint8 ch, uint8 cs);

/***************************************************************************************************
 DCC Training
 ***************************************************************************************************/
void DDRSS_dcc_boot (DDR_STRUCT *ddr, 
                     DDR_CHANNEL channel, 
                     //PHY_BUS dq, 
                     //PHY_BUS ca, 
                     uint32 training_sel, 
                     uint32 clk_freq_khz);

/***************************************************************************************************
 Write Leveling
 ***************************************************************************************************/                       
void DDRSS_wrlvl (DDR_STRUCT *ddr,
                  uint8 ch,
                  uint8 cs,
                  PHY_BUS dq,
                  PHY_BUS ca,
                  uint32 clk_freq_khz,
                  uint32 wrlvl_clk_freq_idx,
                  training_params_t *training_params_ptr);

void DDRSS_wrlvl_ca(DDR_STRUCT *ddr,
                    uint8 ch,
                    uint8 cs,
                    PHY_BUS ca,
                    PHY_BUS dq,
                    uint32 clk_freq_khz,
                    training_params_t *training_params_ptr,
                    uint32 wrlvl_clk_freq_idx);

void DDRSS_wrlvl_dqs(DDR_STRUCT *ddr,
                     uint8 ch,
                     uint8 cs,
                     PHY_BUS dq,
                     uint32 clk_freq_khz,
                     training_params_t *training_params_ptr,
                     uint32 wrlvl_clk_freq_idx);

/***************************************************************************************************
 Write and Read training
 ***************************************************************************************************/
boolean DDRSS_rd_dqdqs_lpddr4 (DDR_STRUCT *ddr,
                               uint8 ch,
                               uint8 cs,
                               PHY_BUS ca,
                               PHY_BUS dq,
                               training_params_t *training_params_ptr,
                               ddrss_rdwr_dqdqs_local_vars *local_vars,
                               uint32 clk_freq_khz,
                               uint8 max_prfs_index);
                               
void DDRSS_rd_dqdqs_dcc_schmoo (DDR_STRUCT *ddr, 
                                uint8 ch, 
                                uint8 cs, 
                                PHY_BUS dq,
                                training_params_t *training_params_ptr, 
                                ddrss_rdwr_dqdqs_local_vars *local_vars,
                                uint32 clk_freq_khz);
                                
void DDRSS_rd_dqdqs_dcc_adjust (DDR_STRUCT *ddr, 
                                uint8 ch, 
                                uint8 cs, 
                                PHY_BUS dq,
                                training_params_t *training_params_ptr, 
                                ddrss_rdwr_dqdqs_local_vars *local_vars,
                                uint32 clk_freq_khz);     

void DDRSS_rd_dqdqs_perbit (DDR_STRUCT *ddr, 
                            uint8 ch, 
                            uint8 cs, 
                            PHY_BUS dq,
                            training_params_t *training_params_ptr, 
                            ddrss_rdwr_dqdqs_local_vars *local_vars,
                            uint8 *rd_left_edge_coarse,
                            uint32 clk_freq_khz);                                
                                
void DDRSS_clk_dcc_rd_dqdqs_schmoo (DDR_STRUCT *ddr,
                                    uint8 ch,
                                    uint8 cs,
                                    PHY_BUS ca,
                                    PHY_BUS dq,
                                    training_params_t *training_params_ptr,
                                    ddrss_rdwr_dqdqs_local_vars *local_vars,
                                    uint32 clk_freq_khz,
                                    uint8 training_ddr_freq_indx_eq_training_table_index);
                                
void DDRSS_RD_Vref_CDC_Coarse_Schmoo (DDR_STRUCT *ddr,
                                      uint8 ch,
                                      uint8 cs,
                                      PHY_BUS ca,
                                      PHY_BUS dq,
                                      training_data *training_data_ptr,
                                      training_params_t *training_params_ptr,
                                      best_eye_struct *best_eye_ptr,
                                      ddrss_rdwr_dqdqs_local_vars *local_vars,
                                      uint32 clk_freq_khz,
                                      uint8  current_clk_inx,
                                      uint8  max_prfs_index);

void DDRSS_RD_Vref_CDC_Fine_Schmoo (DDR_STRUCT *ddr,
                                    uint8 ch,
                                    uint8 cs,
                                    PHY_BUS dq,
                                    training_data *training_data_ptr,
                                    training_params_t *training_params_ptr,
                                    uint8 fine_start_vref_value,
                                    uint8 fine_max_vref_value,
                                    uint8 (*rd_boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                    uint8 direction,
                                    ddrss_rdwr_dqdqs_local_vars *local_vars,
                                    uint32 clk_freq_khz,
                                    uint8  current_clk_inx,
                                    uint8  max_prfs_index,
                                    dbi_struct *dbi_struct_ptr);

void DDRSS_set_global_vref ( uint32 global_vref,  uint32 ch );


void DDRSS_rcw (DDR_STRUCT *ddr,
                uint8 ch,
                uint8 cs,
                PHY_BUS dq,
                training_params_t *training_params_ptr,
                uint8 rcw_start_clk_idx,
                uint8 rcw_clk_idx,
                uint8 low_speed_clk_idx);

void read_rcw_status (uint8 *byte_one_cnt, uint8 *byte_zero_cnt, PHY_BUS dq, uint8 ch);
void set_rcw_cdc_delay ( uint8 rcw_delay,  uint8 coarse_fine, uint8 mode, uint8 ch, uint8 cs, uint8 enable[NUM_DQ_PCH], PHY_BUS dq );
void cdc_delay_search (uint8 loop_cnt, 
                       uint8 max_coarse_delay, 
                       uint8 max_fine_delay, 
                       uint8 coarse_fine_sel,  
                       uint8 *all_found, 
                       uint8 ch, 
                       uint8 cs, 
                       uint8 *byte_done, 
                       uint8 *byte_not_done, 
                       uint8 num_half_cycle,
                       PHY_BUS dq);
void set_rcw_enable (uint8 enable[4],  uint8 num_cycle,  uint8 ch, PHY_BUS dq);

void DDRSS_bimc_rcw_start_delay_write_flash_params (DDR_STRUCT *ddr,
                                                    uint8 ch,
                                                    uint8 cs,
                                                    PHY_BUS dq,
                                                    training_params_t *training_params_ptr,
                                                    uint8 rcw_start_clk_idx,
                                                    uint8 rcw_clk_idx);
void DDRSS_RD_left_edge_search  (DDR_STRUCT *ddr, 
                                 uint8 ch, 
                                 uint8 cs, 
                                 PHY_BUS dq,
                                 training_data *training_data_ptr,
                                 training_params_t *training_params_ptr,
                                 uint8 *rd_left_edge_coarse,
                                 uint32 clk_freq_khz);
                                 
void DDRSS_wr_dqdqs_dq_dcc (DDR_STRUCT *ddr, 
                            uint8 ch, 
                            uint8 cs, 
                            PHY_BUS dq,
                            training_params_t *training_params_ptr, 
                            ddrss_rdwr_dqdqs_local_vars *local_vars,
                            uint8 *coarse_cdc_left_start_value,
                            uint32 clk_freq_khz);
                                
void DDRSS_wr_dqdqs_dqs_dcc (DDR_STRUCT *ddr, 
                             uint8 ch, 
                             uint8 cs, 
                             PHY_BUS dq,
                             training_params_t *training_params_ptr, 
                             ddrss_rdwr_dqdqs_local_vars *local_vars,
                             uint8 *coarse_cdc_left_start_value,
                             uint32 clk_freq_khz);
                                
/***************************************************************************************************
VREF DQ WRITE TRAINING
 ***************************************************************************************************/
boolean DDRSS_wr_dqdqs_lpddr4 (DDR_STRUCT *ddr,
                               uint8 ch,
                               uint8 cs,
                               PHY_BUS dq,
                               training_params_t *training_params_ptr,
                               ddrss_rdwr_dqdqs_local_vars *local_vars,
                               uint32 clk_freq_khz,
                               uint8 max_prfs_index);

void DDRSS_WR_Vref_CDC_Coarse_Schmoo (DDR_STRUCT *ddr,
                                      uint8 ch,
                                      uint8 cs,
                                      PHY_BUS dq,
                                      training_data *training_data_ptr,
                                      training_params_t *training_params_ptr,
                                      uint8 *coarse_wrlvl_delay,
                                      uint8 *fine_wrlvl_delay,
                                      best_eye_struct *best_eye_ptr,
                                      ddrss_rdwr_dqdqs_local_vars *local_vars,
                                      uint8 phase,
                                      uint32 clk_freq_khz,
                                      uint8 max_prfs_index);
                                    
boolean DDRSS_wr_dqdqs_lpddr4_tdqs2dq_cal (DDR_STRUCT *ddr, 
                                           uint8 ch, 
                                           uint8 cs, 
                                           PHY_BUS dq,
                                           training_params_t *training_params_ptr, 
                                           uint32 clk_freq_khz);


void DDRSS_wr_pbit_schmoo (DDR_STRUCT *ddr, 
                           uint8 ch, 
                           uint8 cs, 
                           PHY_BUS dq,
                           training_params_t *training_params_ptr, 
                           ddrss_rdwr_dqdqs_local_vars *local_vars,
                           uint8 *coarse_cdc_left_start_value,
                           uint32 clk_freq_khz);
                           
void DDRSS_WR_DQS_IO_DCC_training (DDR_STRUCT *ddr, 
                                      uint8 ch,
                                      uint8 cs,
                                      PHY_BUS dq,
                                      training_data *training_data_ptr,
                                      training_params_t *training_params_ptr,
                                      ddrss_rdwr_dqdqs_local_vars *local_vars,
                                      uint32 clk_freq_khz);

void DDRSS_WR_coarse_fine_phase_schmoo (DDR_STRUCT *ddr, 
                                        uint8 ch,
                                        uint8 cs,
                                        PHY_BUS dq, 
                                        training_data *training_data_ptr,
                                        training_params_t *training_params_ptr,
                                        ddrss_rdwr_dqdqs_local_vars *local_vars,
                                        uint32 clk_freq_khz);
void DDRSS_WR_DQS_IO_DCC_schmoo (DDR_STRUCT *ddr, 
                                 uint8 ch,
                                 uint8 cs,
                                 PHY_BUS dq,
                                 training_data *training_data_ptr,
                                 training_params_t *training_params_ptr,                                                       
                                 ddrss_rdwr_dqdqs_local_vars *local_vars,
                                 uint8 byte_lane,
                                 uint8 phase);                                                      

void DDRSS_WR_CDC_1D_Fine_Schmoo (DDR_STRUCT *ddr, 
                                  uint8 ch, 
                                  uint8 cs, 
                                  PHY_BUS dq,
                                  training_data *training_data_ptr,
                                  training_params_t *training_params_ptr, 
                                  ddrss_rdwr_dqdqs_local_vars *local_vars,
                                  best_eye_struct *best_eye_ptr,
                                  uint8 *coarse_cdc_value,
                                  uint32 clk_freq_khz,
                                  uint8 max_prfs_index,
                                  uint8 direction);
                                  
void DDRSS_WR_CDC_1D_Schmoo (DDR_STRUCT *ddr, 
                             uint8 ch, 
                             uint8 cs, 
                             PHY_BUS dq,
                             training_data *training_data_ptr,
                             training_params_t *training_params_ptr, 
                             ddrss_rdwr_dqdqs_local_vars *local_vars,
                             best_eye_struct *best_eye_ptr,
                             uint8 *coarse_cdc_left_start_value,
                             uint8 *coarse_cdc_right_start_value,
                             uint32 clk_freq_khz,
                             uint8 max_prfs_index);

void DDRSS_WR_half_full_cycle_search  (DDR_STRUCT *ddr, 
                                  uint8 ch, 
                                  uint8 cs, 
                                  PHY_BUS dq,
                                  training_data *training_data_ptr,
                                  training_params_t *training_params_ptr,
                                  uint8 *coarse_wrlvl_delay,
                                  uint8 *fine_wrlvl_delay,
                                  ddrss_rdwr_dqdqs_local_vars *local_vars,
                                  uint32 clk_freq_khz,
                                  uint8 max_prfs_index);
                                 
/***************************************************************************************************
 Memory read/write routine used for training. 
 ***************************************************************************************************/
void __blocksCopy(uint32 *source, uint32 *destination, uint32 num_words);

#if DSF_PXI_TRAINING_EN
void Calculate_RCW_PXI(DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint32 curr_clk_khz);
void Write_PXI_Table_Data(uint32 base_address, uint32* table_data, uint8 table_depth);
void Initialize_PXI_Tables                  (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 wr_rd, uint8 dbi);
void DDRSS_mem_write_PXI                    (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 dbi, uint8 prbs);
uint8 *DDRSS_mem_read_per_byte_phase_PXI    (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 phase, uint8 prbs);
uint8 *DDRSS_mem_read_per_byte_DBI_phase_PXI(DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 read_test_loop_cnt, uint8 phase);
uint32 DDRSS_mem_read_per_bit_phase_PXI     (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY], uint8 phase, uint8 prbs);
#else
uint8 *DDRSS_mem_read_per_byte_phase        (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 phase);
uint8 *DDRSS_mem_read_per_byte_DBI_phase    (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 phase);
uint32 DDRSS_mem_read_per_bit_phase         (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY], uint8 phase);
void DDRSS_mem_write (DDR_STRUCT *ddr, uint8 ch, uint8 cs);
#endif


/***************************************************************************************************
 Periodic Training
 ***************************************************************************************************/
#define REG_OFFSET_DTTS_SRAM(uint8)     ((uint8 == 0) ? \
                                        BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_DTTS_SRAM_OFFSET  : \
                                        BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_DTTS_SRAM_OFFSET)

void  DDRSS_DIT_Read (DDR_STRUCT *ddr, 
                      uint8 ch, 
                      uint8 cs, 
                      training_params_t *training_params_ptr,
                      uint8 dit_ave,
                      uint16 (*dit_count)[NUM_CS][NUM_DIE_PCH],
                      uint32 clk_freq_khz);

void  DDRSS_DIT_Runtime (DDR_STRUCT *ddr,
                      uint8 ch,
                      uint8 cs,
                      training_params_t *training_params_ptr,
                      uint16 (*dit_count)[NUM_CS][NUM_DIE_PCH],
                      uint32 clk_freq_khz);

void DDRSS_DIT_Slope(DDR_STRUCT *ddr, 
                     uint8 ch, 
                     uint8 cs, 
                     uint8 die, 
                     uint32 clk_freq_khz,
                     uint16 (*dit_mid_count));

void DDRSS_DIT_Capture(uint8 ch, 
                       uint8 cs, 
                       uint16 dit_runtime_count, 
                       uint32 *MR_19_18_data);

boolean DDRSS_Periodic_Training_load_dit_struct_to_dtts(DDR_STRUCT *ddr, 
                                                        uint8  ch, 
                                                        DDR_CHIPSELECT chip_select);

/***************************************************************************************************
 Training Data Based on Bus Width
 ***************************************************************************************************/
void DDRSS_Create_Training_Data(uint8 bus_width_pch);

/***************************************************************************************************
 Data eye plots
 ***************************************************************************************************/
void DDRSS_rd_dqdqs_coarse_fine_plot (DDR_STRUCT *ddr, 
                                      training_params_t *training_params_ptr,
                                      uint32 clk_freq_khz);
void DDRSS_wr_dqdqs_coarse_fine_plot (DDR_STRUCT *ddr, 
                                      training_params_t *training_params_ptr,
                                      uint32 clk_freq_khz);
                                      
void DDRSS_rd_dqdqs_coarse_fine_plot_pivot (DDR_STRUCT *ddr,
                                            char *fout,
                                            training_params_t *training_params_ptr,
                                            uint32 clk_freq_khz
                                            );                                      
/***************************************************************************************************
 PHY Power Collapse
 ***************************************************************************************************/
void DDR_PHY_rtn_ca_pcc_link_list_load (uint32 ddr_phy_addr_base);
void DDR_PHY_rtn_dq_pcc_link_list_load (uint32 ddr_phy_addr_base);
void DDR_CC_rtn_pcc_link_list_load (uint32 ddr_cc_addr_base);
                                      
#endif /* __DDRSS_H__ */
 
