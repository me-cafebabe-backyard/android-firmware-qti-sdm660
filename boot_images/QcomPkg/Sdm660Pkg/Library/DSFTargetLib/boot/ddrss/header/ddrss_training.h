/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/header/ddrss_training.h#9 $
$DateTime: 2018/12/26 02:55:51 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/08/14   jeasley      Update DDRSS_wrlvl prototype to use zero based channel and cs.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __DDRSS_TRAINING_H__
#define __DDRSS_TRAINING_H__

#include "ddr_phy_technology.h"
#include "ddrss_rpm.h"

typedef enum
{
    TRAINING_TYPE_CA_VREF   = 0,
    TRAINING_TYPE_WR_DQDQS  = 1,
    TRAINING_TYPE_RD_DQDQS  = 2,
    TRAINING_TYPE_MAX       = 0x7f
} TRAINING_TYPE;

typedef enum 
{
  DQ = (uint8) 2,
  CA = (uint8) 1
//  DQ_8997 = (uint8) 2,
//  CA_8997 = (uint8) 1
} PHY_BUS;

typedef enum
{
	X16MODE = (uint32) 16,
	X8MODE  = (uint32) 8
} IO_WIDTH;

#define MAX_BUS_WIDTH 32
#define BYTE_SIZE     8

// Threshold parameters
// Must be coordinated with PHY and BIMC Config settings

#define HIGHEST_TRAINED_FPRS_FREQ F_RANGE_7

#define ODT_FPRS_THRESHOLD_FREQ   F_RANGE_4
#define HIGHEST_MPRX_FPRS_FREQ    F_RANGE_3
#define HIGHEST_MPVREF_PRFS_FREQ  F_RANGE_3
#define HIGHEST_GCC_PLL_FREQ      F_RANGE_1

#define RCW_THRESHOLD_FREQ        F_RANGE_3

#define LOWEST_TRAINED_FPRS_FREQ  F_RANGE_3
#define RCW_THRESHOLD_FREQ        F_RANGE_3 
#define HIGHEST_RANK_EN_FREQ      F_RANGE_4 

#define LOWEST_SCALED_PRFS_FREQ   F_RANGE_1
#define LOWEST_FPRS_FREQ          F_RANGE_0 

#define ODT_FSP_EN_FREQ_THRESHOLD 1000000 //Match with settings in bimc_data.c
#define FSP_THRESHOLD_PRFS_BAND   3       //Match DRAM FPS settings with PHY PRFS bands

// Training flow parameters
#define TRAINING_START_PRFS       3
#define LOWEST_WRLVL_COPY_PRFS    1//2
#define MAX_TRAINING_FREQ_NUM     5
#define NUM_SCALE_BANDS           2
#define MAX_TRAINING_FREQ_INDEX   7
#define SCALE_BAND(scale)         ((scale==0)? (2) \
                                             : (1))
                                              
#define SCALE_FREQ(freq)          ((freq==0) ? (F_RANGE_2) \
                                             : (F_RANGE_1))

#define RX_DCC                      10
#define TX_DCC                      16
#define PHASE                       2
#define CLK_DCC_OFFSET_RANGE        7     //2*3(range) + 1

#define ODT_FSP_EN_FREQ_THRESHOLD 1000000 //Match with settings in bimc_data.c



#define FEATURE_DISABLE            0
#define FEATURE_ENABLE             1
#define DCC_TRAINING_WRLVL_WR90_IO 7
#define DCC_TRAINING_WR90          2
#define DCC_TRAINING_WRLVL         1
#define DCC_TRAINING_WR90_IO       6

#define FSP_OP_BOOT               0x0
#define FSP_OP_HIGH               0x1

#define MPVREF                    0
#define HPVREF                    1

#define MR23_data                 0x3F

#define IO_QUAL_OFFSET_DOUBLE_STEP_SIZE 0x5
#define LOCAL_VREF_MID_VALUE            0x08
#define LOCAL_VREF_MAX_VALUE            0x0F

#define LP_MODE                   0
#define HP_MODE                   1
#define SWEEP_LEFT                0
#define SWEEP_RIGHT               1

#define DCC_TRAINING_SEL          7         // Selecting all three DCC training flows
#define MR12_VREF_RANGE_BIT       0         // MR12 OP6 -> 0: Vref Range 0; 1: MR12 Vref Range 1
#define CA_VREF_RANGE_THRESHOLD   30

#define NUM_RETIMER               3
#define NUM_DDRCC_RETIMER_FREQ    7
#define NUM_GCC_RETIMER_FREQ      6

#define NUM_FULL                  3
#define NUM_HALF                  2

//RCW related
#define   RCW_COARSE_DELAY                      1
#define   RCW_FINE_DELAY                        0
#define   RCW_HPRX_MPRX_COARSE_CDC_DLY_DIFF     3
#define   RCW_NEGATIVE_OFFSET_IN_CLK            0 // all frequencies
#define   RCW_POSITIVE_OFFSET_IN_CLK            1 // only frequencies over threshold
#define   RCW_POSITIVE_OFFSET_FREQ_THRESHOLD    F_RANGE_5

//WRLVL training
#define WRLVL_PASS1_FREQ                        1017600
#define WRLVL_PASS1_PRFS_INDEX                       4

// Defines for Periodic Training
#define LOG2(i) (( (i)>=8u)? ( (i)>=32u)?5 :  ( (i)>=16u)?4 : 3 :  ( (i)>=4u)?2 :  ( (i)>=2u)?1 : 0 )
#define PT_SLAB_THRESHOLD_PS      10
#define NUM_DIT_COUNT 12 // NOTE: NUM_DIT_COUN must be an even number


/***************************************************************************************************
 Training Params Struct
 ***************************************************************************************************/
typedef struct
{
   struct
   {
      uint8 max_loopcnt;
   } dcc;

   struct
   {
      uint8 max_loopcnt;
   } dit;

   struct
   {
      uint8 max_loopcnt;
      uint8 cdc_training_enable;
      uint8 coarse_vref_start_value;
      uint8 coarse_vref_max_value;
      uint8 coarse_vref_step;
      uint8 coarse_cdc_start_value;
      uint8 coarse_cdc_max_value;
      uint8 coarse_cdc_step;
      uint8 fine_training_enable;
      uint8 fine_cdc_max_value;
      uint8 fine_cdc_step;
      uint8 fine_vref_enable;
      uint8 fine_vref_step;
      uint8 fine_perbit_start_value;
   } ca_vref;

   struct
   {
      uint8 max_loopcnt;
      uint8 max_coarse_cdc;
      uint8 max_fine_cdc;
      uint8 coarse_cdc_step;
      uint8 fine_cdc_step;
      uint8 feedback_percent;
   } wrlvl;

   struct
   {
       uint8  max_loopcnt;
       uint8  max_coarse_cdc;
       uint8  max_fine_cdc;
       uint8  coarse_cdc_step;
       uint8  fine_cdc_step;
   } rcw;

   struct
   {
      uint8 max_loopcnt;
      uint8 coarse_vref_start_mprx;
      uint8 coarse_vref_min_mprx;
      uint8 coarse_vref_max_mprx;
      uint8 coarse_vref_start_hprx;
      uint8 coarse_vref_min_hprx;
      uint8 coarse_vref_max_hprx;
      uint8 coarse_vref_start_value;
      uint8 coarse_vref_max_value;
      uint8 coarse_vref_step;
      uint8 coarse_cdc_start_value;
      uint8 coarse_cdc_max_value;
      uint8 coarse_cdc_step;
      uint8 coarse_cdc_min_width_lf;
      uint8 coarse_cdc_min_width_hf;
      uint8 coarse_cdc_max_window_width;
      uint8 coarse_hp_vref_mask_min_delta;
      uint8 coarse_hp_vref_mask_max_delta;
      uint8 coarse_mp_vref_mask_min_delta;
      uint8 coarse_mp_vref_mask_max_delta;
      uint8 coarse_cdc_min_width_value;
      uint8 fine_training_enable;
      uint8 fine_vref_start_value;
      uint8 fine_vref_max_value;
      uint8 fine_cdc_start_value;
      uint8 fine_cdc_max_value;
      uint8 fine_cdc_step;
      uint8 fine_vref_enable;
      uint8 fine_vref_step;
      uint8 pbit_start_value;
      uint8 coarse_vref_low_limit_hprx;
   } rd_dqdqs;

   struct
   {
      uint8 max_loopcnt;
      uint8 coarse_vref_start_value;
      uint8 coarse_vref_max_value;
      uint8 coarse_vref_step;
      uint8 coarse_cdc_start_value;
      uint8 coarse_cdc_max_value;
      uint8 coarse_cdc_step;
      uint8 coarse_cdc_min_width_lf;
      uint8 coarse_cdc_min_width_hf;
      uint8 coarse_MR14_1_vref_mask_min_delta;
      uint8 coarse_MR14_1_vref_mask_max_delta;
      uint8 coarse_MR14_0_vref_mask_min_delta;
      uint8 coarse_MR14_0_vref_mask_max_delta;
      uint8 coarse_cdc_min_width_value;
      uint8 fine_training_enable;
      uint8 fine_cdc_top_freq_start_value;
      uint8 fine_cdc_start_value;
      uint8 fine_cdc_top_freq_max_value;
      uint8 coarse_cdc_min_window_width; 
      uint8 coarse_cdc_max_window_width; 
      uint8 fine_cdc_max_value;
      uint8 fine_cdc_step;
      uint8 fine_vref_enable;
      uint8 fine_vref_step;
      uint8 pbit_start_value;
   } wr_dqdqs;

} training_params_t;


void DDRSS_set_training_params (training_params_t *training_params_ptr);


/***************************************************************************************************
 CA Vref training
 ***************************************************************************************************/

extern uint8 ca_training_pattern_lpddr3[CA_PATTERN_NUM][6];
extern uint8 ca_training_pattern_lpddr4[CA_PATTERN_NUM][3];


typedef struct
{
  uint8 best_cdc_value;
  uint8 best_fine_cdc_value;
  uint8 best_vref_value;
  uint16 best_dcc_value; 
  uint8 max_eye_right_boundary_cdc_value;
  uint8 max_eye_left_boundary_cdc_value;
  uint8 bottom_max_eye_vref_value;
  uint8 top_max_eye_vref_value;
  uint8 vref_all_fail_flag;
} best_eye_struct;

typedef struct
{
  uint8 vertical_best_cdc_value;
  uint8 vertical_best_vref_value;
  uint8 max_eye_top_boundary_vref_value;
  uint8 max_eye_bottom_boundary_vref_value;
  uint8 vertical_cdc_all_fail_flag;
} vertical_best_eye_struct;

typedef struct
{
  uint8 ca_coarse_vref;  // Coarse vref of SMALLER vref CA
  uint8 ca_vref_diff;    // Difference value of two CA vref
  uint8 ca_vref_flag;    // Flag to identify the CA with a SMALLER vref
} ca_vref_diff_struct;

typedef struct {
       uint8 coarse_fail_count_table       [NUM_CA_PCH][COARSE_VREF][COARSE_CDC];  //8998: 2 * 56 * 50 = 5600B.
       uint8 left_fine_fail_count_table    [NUM_CA_PCH][PINS_PER_PHY][FINE_VREF][FINE_CDC];  //8998: 2 * 10 * 9 * 9 = 1620B.
       uint8 right_fine_fail_count_table   [NUM_CA_PCH][PINS_PER_PHY][FINE_VREF][FINE_CDC];  //8998: 1620B.
       uint8 left_boundary_fine_cdc_value  [NUM_CA_PCH][PINS_PER_PHY][FINE_CDC];  //8998: 2 * 10 * 9 = 180B.
       uint8 right_boundary_fine_cdc_value [NUM_CA_PCH][PINS_PER_PHY][FINE_CDC];  //8998: 180B.
       uint8 vref_fail_count_table          [NUM_CA_PCH][80];  //8998: 2 * 56 * 50 = 5600B.

} ddrss_ca_vref_local_vars; //8998 total size: 9200B = 9.2KB.


/***************************************************************************************************
 Write Leveling
 ***************************************************************************************************/
// Structure for wrlvl convert routine
typedef struct {
  uint32 dqs_retmr;
  uint32 coarse_dqs_delay;
  uint32 fine_dqs_delay;
  uint32 dqs_full_cycle;
  uint32 dqs_half_cycle;
} wrlvl_params_struct;


/***************************************************************************************************
 Write and Read training
 ***************************************************************************************************/
// Structure containing what would otherwise be local variables used by the ddrss_rd_dqdqs(), ddrss_wr_dqdqs() functions and its callees.
typedef struct {
    struct {
        uint8 fine_left_boundary_cdc_value[NUM_DQ_PCH][PINS_PER_PHY][FINE_VREF];  //8998: 4 * 10 * 9 = 360B.
        uint8 fine_right_boundary_cdc_value[NUM_DQ_PCH][PINS_PER_PHY][FINE_VREF]; //8998: 360B.
    } ddrss_rdwr_fine_cdc_boundary;

    struct {
        uint8 coarse_dq_passband_info[NUM_DQ_PCH][COARSE_VREF][COARSE_CDC];                     //8998: 4 * 56 * 25 = 5600B.
        uint8 coarse_dq_full_half_cdc[NUM_DQ_PCH][NUM_FULL][NUM_HALF][COARSE_CDC];              //8998: 4 * 3 * 2 * 25 = 600B.
        uint8 coarse_dq_dcc_info[NUM_DQ_PCH][NUM_CS][RX_DCC];                                   //8998: 4 * 2 * 10 = 80B. 
        uint8 coarse_dq_clk_dcc_info[NUM_DQ_PCH][NUM_CS][PHASE][COARSE_CDC * FINE_STEPS_PER_COARSE];   //8998: 4 * 2 * 9 * 2 * (25 * 7) = 25200B.
                                                                                                //use the same structure to store WR_dqs_coarse_fine_schmoo info  
        uint8 dcc_width[NUM_DQ_PCH][NUM_CS][RX_DCC];                                            //8998: 4 * 2 * 10 = 80B.
        uint8 best_dcc[NUM_DQ_PCH][NUM_CS];                                                     //8998: 4 * 2 = 8B.
        uint8 rd_dcc_ctl[NUM_DQ_PCH][NUM_CS][RX_DCC];                                           //8998: 4 * 2 * 10 = 80B.
        uint8 clk_dcc_width[NUM_DQ_PCH][NUM_CS][PHASE];                                         //8998: 4 * 2 * 9 * 2 = 144B.
        uint8 clk_dq_dcd[NUM_DQ_PCH][NUM_CS][CLK_DCC_OFFSET_RANGE];                             //8998: 4 * 2 * 9 = 72B.
        uint8 coarse_fail_count_table[NUM_DQ_PCH][COARSE_VREF];                                 //8998: 4 * 56 = 224B.
        uint8 coarse_dq_1D_passband_info[NUM_DQ_PCH][COARSE_CDC];                               //8998: 4 * 25 = 100B.
        uint8 wr_dcc_1ST_pass_coarse[NUM_DQ_PCH][PHASE];                                        //8998: 4 * 2  = 8B.
        uint8 wr_dcc_1ST_pass_fine[NUM_DQ_PCH][PHASE];                                          //8998: 4 * 2  = 8B.
        uint8 wr_dcc_1ST_pass_half_cycle[NUM_DQ_PCH][PHASE];                                    //8998: 4 * 2  = 8B.
        uint8 wr_dcc_1ST_pass_full_cycle[NUM_DQ_PCH][PHASE];                                    //8998: 4 * 2  = 8B.
        uint8 wr_dcc_1ST_pass_index[NUM_DQ_PCH][PHASE];                                         //8998: 4 * 2  = 8B.
        uint8 wr_dcc_ctl[NUM_DQ_PCH][NUM_CS][TX_DCC];                                           //8998: 4 * 2 * 15 = 120B.
    } coarse_schmoo;

    struct {
        uint8 fine_dq_passband_info_left[NUM_DQ_PCH][PINS_PER_PHY][FINE_VREF][FINE_CDC];        //8998: 4 * 10 * 9 * 9 = 3240B.
        uint8 fine_dq_passband_info_right[NUM_DQ_PCH][PINS_PER_PHY][FINE_VREF][FINE_CDC];       //8998: 3240B.
        uint8 fine_rd_dq_passband_info_left[NUM_DQ_PCH][PINS_PER_PHY][FINE_VREF][FINE_RD_CDC];  //8998: 4 * 10 * 9 * 9 = 3240B.
        uint8 fine_rd_dq_passband_info_right[NUM_DQ_PCH][PINS_PER_PHY][FINE_VREF][FINE_RD_CDC]; //8998: 3240B.
        uint8 fine_dq_1D_passband_info[NUM_DQ_PCH][2 * FINE_CDC];                               //8998: 4 * 2 * 9 = 72B.
    } fine_schmoo;

} ddrss_rdwr_dqdqs_local_vars; // 8998 total size: ~45KB.

typedef struct
{
  uint8 dbi_flag;  // Coarse vref of SMALLER vref CA
  uint8 dq_pin_num_max;    // Difference value of two CA vref
  uint8 *connected_bit_mapping_A;
} dbi_struct;


#endif /* __DDRSS_TRAINING_H__ */
