/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/header/ddrss_training_rpm.h#7 $
$DateTime: 2017/03/06 02:01:52 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/08/14   jeasley      Update DDRSS_wrlvl prototype to use zero based channel and cs.
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __DDRSS_TRAINING_RPM_H__
#define __DDRSS_TRAINING_RPM_H__

#define VREF_MP_HP                  2
#define PINS_PER_PHY_CONNECTED_CA   6

#define NUM_PRFS_BANDS            8

#define DTTS_ACQUIRE_MODE        0x1
#define DTTS_TRACKING_MODE       0x2

#define DTTS_WAKEUP_DISABLE_ALL        0x70000
#define DTTS_WAKEUP_ENABLE_ALL         0x00000
#define DTTS_WAKEUP_ENABLE_SHKE_ONLY   0x60000

#define SHKE_TRIGGER_ENABLE         0x1
#define SHKE_TRIGGER_DISABLE        0x2
#define DTTS_FW_IDLE                0

// PHY Power Collapse Broadcast for dual channel devices
#define PC_PHY_CA_DQ_BROADCAST    0x1FBF
#define PC_CC_BROADCAST           0x2040

#define PINS_PER_PHY                    10
#define PINS_PER_PHY_CONNECTED_NO_DBI    8
#define PINS_PER_PHY_CONNECTED_WITH_DBI  9

extern uint32 freq_range[6]; //for 1353MHz expansion. 
extern uint8 connected_bit_mapping_no_DBI_A  [PINS_PER_PHY_CONNECTED_NO_DBI];
extern uint8 connected_bit_mapping_no_DBI_B  [PINS_PER_PHY_CONNECTED_NO_DBI];
extern uint8 connected_bit_mapping_with_DBI_A [PINS_PER_PHY_CONNECTED_WITH_DBI];
extern uint8 connected_bit_mapping_with_DBI_B [PINS_PER_PHY_CONNECTED_WITH_DBI];
//extern uint8 connected_bit_mapping_CA [PINS_PER_PHY_CONNECTED_CA];


/***************************************************************************************************
 Training data struct
 This is the organization of ddr->flash_params.training_data struct
 ***************************************************************************************************/
struct training_results
{
   struct
   {
     uint16 dit_count[NUM_CH][NUM_CS][NUM_DIE_PCH]; // 8998: 2 * (2 * 2 * 2) = 16.
     uint32 dit_training_freq;                      // 8998: 4. 
     uint16 dit_runtime_count;                      // 8998: 2. 
     uint8  dit_fine_step_limit;                    // 8998: 1. 
     uint16 dit_interval_per_sec;                   // 8998: 2. 
     uint8  dit_loop_count;                         // 8998: 1. 
     uint16  dit_acq_ndx;                           // 8998: 2. 
     uint16  dit_trac_ndx;                          // 8998: 2. 
   } dit; // 8998: Total = 30.

   struct
   {
     /* 
      uint16 wrlvl_stat_dq [NUM_PRFS_BANDS][NUM_CH][NUM_PLL][NUM_DQ_PCH]; // 8998: 8 * 2 * (2 * 4) = 128.
      uint16 t90_stat_dq   [NUM_PRFS_BANDS][NUM_CH][NUM_DQ_PCH];    // 8998: 8 * (2 * 4) = 64.
      uint16 iodqs_stat_dq [NUM_PRFS_BANDS][NUM_CH][NUM_DQ_PCH];    // 8998: 8 * (2 * 4) = 64.

      uint16 wrlvl_stat_ca [NUM_PRFS_BANDS][NUM_CH][NUM_PLL][NUM_CA_PCH];    // 8998: 8 * 2 * (2 * 2) = 32.
      uint16 t90_stat_ca   [NUM_PRFS_BANDS][NUM_CH][NUM_CA_PCH];    // 8998: 8 * 2 * (2 * 2) = 32.
      uint16 iodqs_stat_ca [NUM_PRFS_BANDS][NUM_CH][NUM_CA_PCH];    // 8998: 8 * 2 * (2 * 2) = 32.
      */
      uint16 wrlvl_stat_dq [NUM_CH][NUM_DQ_PCH]; // 8998:  2 * 2  = 4.
      uint16 t90_stat_dq   [NUM_CH][NUM_DQ_PCH];    // 8998: 2 * 2 = 4.
      uint16 iodqs_stat_dq [NUM_CH][NUM_DQ_PCH];    // 8998: 2 * 2 = 4.

      uint16 wrlvl_stat_ca [NUM_CH][NUM_CA_PCH];    // 8998: 2  = 2.
      uint16 t90_stat_ca   [NUM_CH][NUM_CA_PCH];    // 8998: 2 = 2.
      uint16 iodqs_stat_ca [NUM_CH][NUM_CA_PCH];    // 8998: 2 = 2.
      uint16 cmdqs_stat_rd [NUM_CH][NUM_CS][NUM_DQ_PCH];    // 8998: 2 * (2 * 4) = 16.
      uint16 iodqs_stat_rd [NUM_CH][NUM_CS][NUM_DQ_PCH];    // 8998: 2 * (2 * 4) = 16.     
   } dcc; // 8998: Total = 384.

   struct
   {
      uint8 coarse_vref    [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 fine_vref      [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 range_vref      [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 coarse_cdc     [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 fine_cdc       [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 dq_retmr       [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 dq_half_cycle  [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 dq_full_cycle  [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];       // 8998: 8 * 2 * 2 * 2 = 64.
      uint8 perbit_delay   [NUM_CH][NUM_CS][NUM_CA_PCH][PINS_PER_PHY];         // 8998: 2 * 2 * 2 * 10 = 80.
   } ca_vref; // 8998: Total = 528.


   struct
   {
      uint8  dq_dqs_retmr       [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];  //8998: 8 * 2 * 2 * 4 = 128.
      uint8  dq_coarse_dqs_delay[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];  //8998: 8 * 2 * 2 * 4 = 128.
      uint8  dq_fine_dqs_delay  [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];  //8998: 8 * 2 * 2 * 4 = 128.
                                                                                   
      uint8  ca_dqs_retmr       [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];  //8998: 8 * 2 * 2 * 2 = 64.
      uint8  ca_coarse_dqs_delay[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];  //8998: 8 * 2 * 2 * 2 = 64.
   } wrlvl; // 8998: Total = 512 //896.

   struct
   {
      uint8 bimc_tDQSCK [MAX_NUM_CLOCK_PLAN][NUM_CH][NUM_CS][NUM_DQ_PCH];   // 8998: 15 * 2 * 2 * 4 = 240.
   } rcw; // 8998: Total = 240.

   struct
   {
      uint8 coarse_vref [VREF_MP_HP][NUM_CH][NUM_CS][NUM_DQ_PCH];           // 8998: 2 * 2 * 2 * 2 = 16.// change by Sagar
     // uint8 coarse_vref [VREF_MP_HP][NUM_CH][NUM_CS][NUM_DQ_PCH];           // 8998: 2 * 2 * 2 * 2 = 16.
      uint8 coarse_cdc  [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];       // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 coarse_dcc  [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];       // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 fine_cdc    [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];       // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 perbit_delay[NUM_CH][NUM_CS][NUM_DQ_PCH][PINS_PER_PHY];         // 8998: 2 * 2 * 4 * 10 = 160.
      uint8 perbit_vref [NUM_CH][NUM_CS][NUM_DQ_PCH][PINS_PER_PHY];         // 8998: 2 * 2 * 4 * 10 = 160.
      uint8 rd_dcc      [NUM_CH][NUM_CS][NUM_DQ_PCH];                       // 8998: 2 * 2 * 4 = 16.
      uint8 clk_dcc_mag  [NUM_CH][NUM_CA_PCH];                              // 8998: 2 * 2 = 4.      
      uint8 clk_dcc_sign [NUM_CH][NUM_CA_PCH];                              // 8998: 2 * 2 = 4. 
   //   uint16 wr_io_dcc [NUM_CH][NUM_CS][NUM_DQ_PCH];                         //8998: 2 * 2 * 4 = 16 * 2B = 32B.   
   } rd_dqdqs; // 8998: Total = 744

   struct
   {
      uint8 coarse_vref[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                                // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 coarse_cdc [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                                // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 fine_cdc   [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                                // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 coarse_best_eye_vref_value[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                 // 8998: 8 * 2 * 2 * 2 = 64. // Changed by Sagar
      uint8 coarse_max_eye_left_boundary_cdc_value[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];     // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 coarse_max_eye_right_boundary_cdc_value[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];    // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 dq_retmr      [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                             // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 dq_half_cycle [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                             // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 dq_full_cycle [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];                             // 8998: 8 * 2 * 2 * 4 = 128.
      uint8 perbit_delay[NUM_CH][NUM_CS][NUM_DQ_PCH][PINS_PER_PHY];                                 // 8998: 2 * 2 * 4 * 10 = 160.
      uint16 wr_io_dcc[NUM_CH][NUM_CS][NUM_DQ_PCH];                                                   //8998: 2 * 2 * 4 *2B = 32.  
   } wr_dqdqs; // 8998: Total = 1280.

};

typedef struct
{
   struct training_results results; // 8998 : Total = 3466 //3850 uint8s.
} training_data;


/***************************************************************************************************
 Periodic Training
 ***************************************************************************************************/
#define REG_OFFSET_DTTS_SRAM(uint8)     ((uint8 == 0) ? \
                                        BIMC_BASE + SEQ_BIMC_BIMC_S_DDR0_DTTS_SRAM_OFFSET  : \
                                        BIMC_BASE + SEQ_BIMC_BIMC_S_DDR1_DTTS_SRAM_OFFSET)


#endif /* __DDRSS_TRAINING_RPM_H__ */
