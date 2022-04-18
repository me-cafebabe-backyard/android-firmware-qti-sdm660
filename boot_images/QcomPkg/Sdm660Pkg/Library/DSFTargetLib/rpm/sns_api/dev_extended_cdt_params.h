#ifndef __DEV_EXTENDED_CDT_PARAMS_H__
#define __DEV_EXTENDED_CDT_PARAMS_H__

/*=============================================================================

DDR Device Extended CDT PARAMETERS
Header File

GENERAL DESCRIPTION
This file defines the extended DDR paramters that is stored/retrieved from CDT partition


Copyright 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*==============================================================================
                                EDIT HISTORY

================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
06/12/15   tw      Initial version.
==============================================================================*/
/*==========================================================================

                               INCLUDE FILES
===========================================================================*/
#include "HALcomdef.h"

// ===============================================================================
// This file contains structure declarations for the Extended CDT. In this MSM8996
// DSF, the Extended CDT is not being processed. It has been put in purely to freeze
// the data structures and APIs. Application of Extended CDT parameters into DDR
// subsystem and boot-time and run-time will be implemented in a future DSF release.
// ===============================================================================

#define NUM_ECDT_DRAM_LATENCY_STRUCTS   16
#define NUM_ECDT_FREQ_SWITCH_STRUCTS    8
#define NUM_ECDT_PRFS_BANDS             8
#define NUM_ECDT_FSP_BANDS              2

// ===============================================================================
// Extended CDT structure declarations
// ===============================================================================

struct ecdt_dram_soc_odt_input_struct         // Onetime, not runtime
{
    uint8   apply_override;
    uint8   dram_soc_odt;               // MR22, can only set for FSP0 and FSP1
}__attribute__((__packed__));

// ------------------------------- MSM Drive Strength -------------------------------------------
struct ecdt_msm_drive_strength_input_struct // One time, member of msm_drv_str_odt_struct
{
    uint8   apply_override;
    uint8   pull_up_drive_strength;
    uint8   pull_down_drive_strength;
    uint8   vOH;
}__attribute__((__packed__));

// ------------------------------- MSM ODT -------------------------------------------------------
struct ecdt_msm_odt_input_struct           // On time, member of msm_drv_str_odt_struct
{
    uint8   apply_override;
    uint8   dqs_odt_enable;
    uint8   dqs_odt;
    uint8   dq_odt_enable;
    uint8   dq_odt;
}__attribute__((__packed__));

// ------------------------------- MSM RDT2 -------------------------------------------------------
struct ecdt_msm_rd_t2_input_struct           // On time, member of msm_drv_str_odt_struct
{
    uint8   apply_override;
    uint8   rd_t2_coarse_cdc;
}__attribute__((__packed__));

struct ecdt_msm_drv_str_odt_rdt2_input_struct   // One time
{
    uint32  frequency_in_kHz;
    struct  ecdt_msm_drive_strength_input_struct   msm_drive_strength_ca;
    struct  ecdt_msm_drive_strength_input_struct   msm_drive_strength_dq;
    struct  ecdt_msm_odt_input_struct              msm_odt;
    struct  ecdt_msm_rd_t2_input_struct            msm_rd_t2;
}__attribute__((__packed__));

// --------------------------------- DRAM Latency --------------------------------------------------
struct ecdt_dram_latency_runtime_struct
{
    uint8   RL_DBI_Off_x16;
    uint8   RL_DBI_On_x16;
    uint8   RL_DBI_Off_x8;
    uint8   RL_DBI_On_x8;
    uint8   WL;
    uint8   MR2;
    uint32  rl_wl_freq_in_kHz;
}__attribute__((__packed__));

struct ecdt_dram_latency_input_struct
{
    uint8   apply_override;
    struct ecdt_dram_latency_runtime_struct dram_latency;
}__attribute__((__packed__));

// --------------------------------- BIMC Frequency Switch Params -------------------------------------
struct ecdt_bimc_freq_switch_params_runtime_struct
{
    uint8   rd_dbi;
    uint8   odt;
    uint8   fsp;
    uint8   MR1;
    uint8   MR3;
    uint8   MR11;
    uint32  freq_switch_range_in_kHz;
}__attribute__((__packed__));

struct ecdt_bimc_freq_switch_params_input_struct
{
    uint8   apply_override;
    struct  ecdt_bimc_freq_switch_params_runtime_struct bimc_freq_switch_params;
}__attribute__((__packed__));

// ----------------------------------- Extended CDT Runtime Structure -------------------------------------
// This structure is a member of DDR_STRUCT for use during run-time operations. It is populated by DSF
// code processing the extended_cdt_input_struct{} members with their apply_override knobs.
// ---------------------------------------------------------------------------------------------------------
struct extended_cdt_runtime_struct
{
    uint8   hw_self_refresh_enable[2];                       /* Default 1 to enable. 0 used for debug, one entry per channel. */
    uint8   MR4_polling_enable;                              /* Default 1 to enable. 0 used for debug. */
    uint8   periodic_training_enable;                        /* 1: Enable periodic training, 0: Disable periodic training */
    uint16  page_close_timer;                                /* PG_OPEN_TIMER is 12bit wide and is in DDR clock cycles */
    
    struct  ecdt_dram_latency_runtime_struct                 dram_latency[NUM_ECDT_DRAM_LATENCY_STRUCTS];
    struct  ecdt_bimc_freq_switch_params_runtime_struct      bimc_freq_switch[NUM_ECDT_FREQ_SWITCH_STRUCTS];
}__attribute__((__packed__));

// ----------------------------------- Extended CDT ECDT Structure -------------------------------------
// This structure is passed in to HAL_DDR_Init().
// ------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------
// This file contains structure declarations for the Extended CDT. In this MSM8996
// DSF, the Extended CDT is not being processed. It has been put in purely to freeze
// the data structures and APIs. Application of Extended CDT parameters into DDR
// subsystem and boot-time and run-time will be implemented in a future DSF release.
// ------------------------------------------------------------------------------------------------------
struct extended_cdt_input_struct
{
    struct  ecdt_dram_soc_odt_input_struct                 dram_soc_odt[NUM_ECDT_FSP_BANDS];
    struct  ecdt_msm_drv_str_odt_rdt2_input_struct         msm_drv_str_odt_rdt2[NUM_ECDT_PRFS_BANDS];
    
    struct  ecdt_dram_latency_input_struct                 dram_latency[NUM_ECDT_DRAM_LATENCY_STRUCTS];
    struct  ecdt_bimc_freq_switch_params_input_struct      bimc_freq_switch[NUM_ECDT_FREQ_SWITCH_STRUCTS];
}__attribute__((__packed__)) ;

typedef struct __attribute__((__packed__)) 
{
    uint8  version;                                                 /* Extended CDT version number. */

    uint8   hw_self_refresh_enable[2];                              /* Default 1 to enable. 0 used for debug, one entry per channel. */
    uint8   MR4_polling_enable;                                     /* Default 1 to enable. 0 used for debug. */
    uint8   periodic_training_enable;                               /* 1: Enable periodic training, 0: Disable periodic training */
    uint16  page_close_timer;                                       /* PG_OPEN_TIMER is 12bit wide and is in DDR clock cycles */
    
    struct  extended_cdt_input_struct   extended_cdt_ecdt;

}EXTENDED_CDT_STRUCT;

#endif /* __DEV_EXTENDED_CDT_PARAMS_H__ */

