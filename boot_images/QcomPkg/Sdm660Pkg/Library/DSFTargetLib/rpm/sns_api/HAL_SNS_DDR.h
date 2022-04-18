#ifndef __HAL_SNS_DDR_H__
#define __HAL_SNS_DDR_H__

/**---------------------------------------------------------------------------
* @file     HAL_sns_DDR.h
*
* @brief    DDR HW abstraction layer
*
* Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
*--------------------------------------------------------------------------*/

/*=============================================================================

                                   DDR HAL
                            H e a d e r  F i l e
GENERAL DESCRIPTION
This is the header file for ddr HAL. This file is shared across targets

EXTERNALIZED FUNCTIONS
  
INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/sns_api/HAL_SNS_DDR.h#9 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/015/14  tw      Modified clockplan structure to add new fields to support
                   dynamic clockplan sharing
12/01/13   dp      Initial revision.
=============================================================================*/


/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "HALhwio.h"

#include "ddr_cores.h"
#include "ddr_common.h"
#include "dev_cdt_params.h"
#include "dev_extended_cdt_params.h"
#include "dev_flash_params.h"
#include "ddr_external.h"
#include "ddr_status_reg.h"
#include "ddr_ioctl.h"
#include "ddr_log.h"

#define MAX_NUM_CLOCK_PLAN 15

// Enumerations to support one-time training (DDR_TRAINING_MODE_INIT) or check if training is required (DDR_TRAINING_MODE_CHECK).
// caller software will call HAL_DDR_Boot_Training(DDR_TRAINING_MODE_INIT) if the prior call HAL_DDR_Boot_Training(DDR_TRAINING_MODE_CHECK)
// has returned TRUE. These enumerations are to be used for both HAL_DDR_Boot_Training() and HAL_DDR_Periodic_Training().
typedef enum {
    DDR_TRAINING_MODE_CHECK = 0,
    DDR_TRAINING_MODE_INIT,
    DDR_TRAINING_MODE_MAX = 0x7f
} DDR_TRAINING_MODE;


// Modes for Power Collapse.
typedef enum {
    DDR_POWER_CLPS_MODE_BIMC_ONLY = 0,
    DDR_POWER_CLPS_MODE_PHY_ONLY,
    DDR_POWER_CLPS_MODE_MAX = 0x7F
} DDR_POWER_CLPS_MODE;

typedef enum
{
    PHY_POWER_CLPS_SAVE         = 0x0,
    PHY_POWER_CLPS_RESTORE      = 0x1,
    PHY_POWER_CLPS_SAVE_RESTORE = 0x2
} PCC_MODE;


/**********************/
/*** DDR Clock Plan ***/
/**********************/
/**
 * ddr_clock_plan: DDR Clock Plan Data Structure.
 * This structure needs to be populated run time after querying clock driver
 */
// Structure declaration for PLL programming values used by targets 8996.
// This structure is a member of the ddr_clock_plan structure, inside a union that
// carries the PLL programming structures for both kinds of PLLS, 8992 and 8994 as 
// one structure, and 8996 as the other structure. 
// The build flag DDRCC_PLL_EXTENSION needs to be defined from outside the DSF.
// #define DDRCC_PLL_EXTENSION_0 1
#if DDRCC_PLL_EXTENSION_0
//struct ddr_clock_plan
//{
//  uint32 clk_freq_in_khz; /**< Clock freq in khz*/
//  uint32 clk_mode;        /**< Clocking mode: 0=GCC 1=DDRCC*/
//  
//  uint32  clk_ratio;  
//  uint32  pll_prop_gain_rate_1;
//  uint32  pll_outdiv_rate;
//  uint32  pll_lockdet_rate_1;
//  uint32  decimal_div_start;
//  uint32  frac_div_start_low;
//  uint32  frac_div_start_mid;
//  uint32  frac_div_start_high;
//  uint32  clock_inverters;
//  uint32  reserve_0;
//  uint32  reserve_1;
//
//};

struct ddr_clock_plan
{
  uint32 clk_freq_in_khz; /**< Clock freq in khz*/
  uint32 clk_mode;        /**< Clocking mode: 0=GCC 1=DDRCC*/
  uint32 clk_ratio;
  
  uint32  pll_dec_start;
  uint32  pll_div_frac_start3;
  uint32  pll_plllock_cmp1;
  uint32  pll_plllock_cmp2;
  uint32  pll_vco_count1;
  uint32  pll_vco_count2;
  uint32  pll_pll_lpf2_postdiv;
  uint32  pll_kvco_code;  
  uint32 reserve_00;

  uint32 reserve_0;
  uint32 reserve_1;
};
#else // #if DDRCC_PLL_EXTENSION
// Structure declaration for PLL programming values used by targets 8992 and 8994.
// This structure is a member of the ddr_clock_plan structure, inside a union that
// carries the PLL programming structures for both kinds of PLLS, 8992 and 8994 as 
// one structure, and 8996 as the other structure. 
struct ddr_clock_plan
{
  uint32 clk_freq_in_khz; /**< Clock freq in khz*/
  uint32 clk_mode;        /**< Clocking mode: 0=GCC 1=DDRCC*/
  
  uint32 pll_l;
  uint32 pll_alpha;
  uint32 pll_postdiv;

  uint32 reserve_0;
  uint32 reserve_1;
};
#endif  // #if DDRCC_PLL_EXTENSION

/**************************/
/*** Miscellaneous Info ***/
/**************************/
/**
 * ddr_misc: Miscellaneous Information Data Structure.
 */
struct ddr_misc
{
  struct ddr_clock_plan clock_plan[MAX_NUM_CLOCK_PLAN]; /**< Struct of valid clock plan frequencies for DDR */
  uint32 ddr_num_clock_levels;
  uint32 max_ddr_frequency;                 /**< requested max frequency at boot time; actual supported max frequency after boot */
  uint32 misc_cfg[10];                      /**< Index 0: Small Eye Detect Flag             */
                                            /**< Index 1: TBD*/
                                            /**< Index 2: TBD                               */
                                            /**< Index 3: TBD                               */
                                            /**< Index 4: TBD                               */
                                            /**< Index 5-9: TBD                             */
  uint32 platform_id;
  uint32 chip_version;
  uint32 bus_width_pch;
  uint32 current_clk_in_kHz;
  uint32 new_clk_in_kHz;
  uint32 target_silicon;
  uint32 package_type;
  uint32 ddr_struct_cookie;
  uint32 ext_buck_id;                      
  uint32 rsv[10];             
};

/**********************/
/*** DDR Debug ***/
/**********************/
/**
 * ddr_dbg: DDR Debug Data Structure.
 * If this element is zero, it means that there is no debug
 * structure that the DDR System Firmware needs to process.
 * A non-zero value in this element will be used by the DDR System Firmware as a
 * pointer to a debug structure whose contents will be determined by debug requirements
 * as they come up.
 */
union ddr_dbg
{
  uint32 ptr32;   /**< Store pointer to DDR Debug Structure */
  uint64 ptr64;   /**< Store pointer to DDR Debug Structure */
};

/*******************************************/
/*** Central DDR Parameter datastructure ***/
/*******************************************/
/**
 * DDR_STRUCT: Central DDR Parameter Data Structure.
 * Caller of DDR System Firmware will pass a pointer to this data structure
 * with every call made to top-level functions such as HAL_DDR_Init().
 */
typedef struct
{
  uint32                                version;                /**< DDR System Firmware Version */
  uint32                                rpm_version;            /**< Version of RPM-only code in DDR System Firmware */
  struct ddr_ctlr                       ctlr;                   /**< DDR Controller Information Structure */
  struct ddr_phy                        phy;                    /**< DDR PHY Information Structure */
  struct detected_ddr_device_params     detected_ddr_device[2]; /**< Detected DDR size and manufacturer information for each channel */
  ddr_device_params                     cdt_params;             /**< DDR Common Device Table array, same for each channel */
  struct ddr_misc                       misc;                   /**< Miscellaneous Info Data Structure */
  ddr_sns_size_info                     ddr_size_info;          /**< DDR part details , including type,interleave,size & start address per channel & cs */
  struct ddr_params_partition           flash_params;           /**< DDR Flash Parameter table*/
  struct extended_cdt_runtime_struct    extended_cdt_runtime;   /**< Extended Configuration Data Table */
  uint32                                ecdt_input;             /**< Pointer to ECDT input structures */
  uint32                                rsvd[29];               /**< Reserved padding bytes*/
  union ddr_dbg                         dbg;                    /**< DDR Debug Data Structure */
  ddr_status_reg                        status_registers[2];    /**< status register values for pre/post clock/vol switch */
  uint32                                ddi_buf[100];           /**< Reserved for DDI tool*/
} DDR_STRUCT;

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

/* =============================================================================
**  Function : HAL_DDR_Init
** =============================================================================
*/
/**
*   @brief
*   Initialize DDR controller, as well as DDR device.
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel      channel to initialize for
*   @param[in]  chip_select  Chip select to initialize for
*   @param[in]  clk_freq_khz Clock speed (in KHz) to initialize for
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
// ------------------------------------------------------------------------------------------------------
// The API HAL_DDR_Init() takes a new parameter: EXTENDED_CDT_STRUCT *ecdt. In this MSM8996
// DSF, the Extended CDT is not being processed. It has been put in purely to freeze
// the data structures and APIs. Application of Extended CDT parameters into DDR
// subsystem and boot-time and run-time will be implemented in a future DSF release.
// ------------------------------------------------------------------------------------------------------
boolean HAL_DDR_Init(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select,
                     uint32 clk_freq_khz);

/* =============================================================================
**  Function : HAL_DDR_Boot_Training_Init
** =============================================================================
*/
/**
*   @brief
*   Execute all one time DDR trainings
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel      channel to initialize for
*   @param[in]  chip_select  Chip select to initialize for

*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Boot_Training_Init(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
                              
/* =============================================================================
**  Function : HAL_DDR_Boot_Training_Restore
** =============================================================================
*/
/**
*   @brief
*   Execute DDR Training Restore.
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel      channel to initialize for
*   @param[in]  chip_select  Chip select to initialize for

*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Boot_Training_Restore(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);
                              
/* =============================================================================
**  Function : HAL_DDR_Periodic_Training
** =============================================================================
*/
/**
*   @brief
*   Setup state for any DDR perioidic trianings
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel      channel to initialize for
*   @param[in]  chip_select  Chip select to initialize for
*   @param[in]  mode         DDR_TRAINING_MODE_INIT or DDR_TRAINING_MODE_CHECK to initialize periodic training or check if it is required.
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Periodic_Training(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 mode);

/* =============================================================================
**  Function : HAL_DDR_Pre_Clock_Switch
** =============================================================================
*/
/**
*   @brief
*   Init state before DDR clock switch
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel    channel to initialize for
*   @param[in]  curr_clk_khz Current CLK freq in KHZ before clock switch
*   @param[in]  new_clk_khz  New CLK freq in KHZ after clock switch
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Pre_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_clk_khz,
                                 uint32 new_clk_khz);
				 
/* =============================================================================
**  Function : HAL_DDR_Clock_Switch
** =============================================================================
*/
/**
*   @brief
*   Perform the DDR clock switch
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel    channel to initialize for
*   @param[in]  curr_clk_khz Current CLK freq in KHZ before clock switch
*   @param[in]  new_clk_khz  New CLK freq in KHZ after clock switch
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_clk_khz,
                                 uint32 new_clk_khz);

/* =============================================================================
**  Function : HAL_DDR_Post_Clock_Switch
** =============================================================================
*/
/**
*   @brief
*   Init state after DDR clock switch
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel    channel to initialize for
*   @param[in]  curr_clk_khz Current CLK freq in KHZ before clock switch
*   @param[in]  new_clk_khz  New CLK freq in KHZ after clock switch
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Post_Clock_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_clk_khz,
                                  uint32 new_clk_khz);

/* =============================================================================
**  Function : HAL_DDR_Pre_Voltage_Switch
** =============================================================================
*/
/**
*   @brief
*   Init state before DDR voltage switch
*
*   @param[in]  ddr             Pointer to ddr conifiguration struct
*   @param[in]  channel       channel to initialize for
*   @param[in]  curr_volt_level Current voltage level before voltage switch
*   @param[in]  new_volt_level  New voltage level after voltage switch
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Pre_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_volt_level,
                                   uint32 new_volt_level);

/* =============================================================================
**  Function : HAL_DDR_Post_Voltage_Switch
** =============================================================================
*/
/**
*   @brief
*   Init state after DDR voltage switch
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel    channel to initialize for
*   @param[in]  curr_volt_level Current voltage level before voltage switch
*   @param[in]  new_volt_level  New voltage level after voltage switch
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Post_Voltage_Switch(DDR_STRUCT *ddr, DDR_CHANNEL channel, uint32 curr_volt_level,
                                    uint32 new_volt_level);

/* ============================================================================
**  Function : HAL_DDR_Enter_Self_Refresh
** ============================================================================
*/
/*!
*   @brief
*   This function triggers the ddr to enter self refresh mode for channel EBI0/1
*
*   @details
*   This function triggers the ddr to enter self refresh mode for channel EBI0/1
*
*
*   @par Dependencies
*   This code must not reside on the ddr that is being put to self refresh.
*
*   @par Side Effects
*   DDR is in self refresh mode and if both CS is selected, or only 1 CS is physically
*   present, then the ddr clock is turned off, at this point, any writes to ddr will
*   fail since the controller is not going to respond.
*
*   @retval  None
*
*   @sa None
*/
boolean HAL_DDR_Enter_Self_Refresh(DDR_STRUCT *ddr, DDR_CHANNEL channel,
                                   DDR_CHIPSELECT chip_select);

/* ============================================================================
**  Function : HAL_DDR_Exit_Self_Refresh
** ============================================================================
*/
/*!
*   @brief
*   This function triggers the ddr to exit self refresh mode for channel EBI0/1
*
*   @details
*   This function triggers the ddr to exit self refresh mode for channel EBI0/1
*
*   @par Dependencies
*
*
*   @par Side Effects
*
*   @retval  None
*
*   @sa None
*/
boolean HAL_DDR_Exit_Self_Refresh(DDR_STRUCT *ddr, DDR_CHANNEL channel,
                                  DDR_CHIPSELECT chip_select);

/* =============================================================================
**  Function : HAL_DDR_Enter_Power_Collapse
** =============================================================================
*/
/**
*   @brief
*   Init state before entry of power collapse
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*   @param[in]  channel    channel to initialize for
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Enter_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_POWER_CLPS_MODE collapse_mode, 
                                     uint32 clk_freq_khz);
/* =============================================================================
**  Function : HAL_DDR_Exit_Power_Collapse
** =============================================================================
*/
/**
*   @brief
*   Init state after exit of power collapse
*
*   @param[in]  ddr          Pointer to ddr configuration struct
*   @param[in]  channel    channel to initialize for
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Exit_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_POWER_CLPS_MODE collapse_mode, 
                                    uint32 clk_freq_khz);
/* ============================================================================
**  Function : HAL_DDR_Enter_Deep_Power_Down
** ============================================================================
*/
/*!
*   @brief
*   This function will put the ddr into DPD mode
*
*   @details
*   This function will trigger the ddr to be put into deep power down mode.
*   In the case where we only have 1 device on the channel (CS0 only), or both
*   chip select are chosen, we will also turn off ddr clock.
*
*   @param channel   -  [IN] channel to configure DPD for
*
*   @par Dependencies
*   The desired CS to be configured for Deep Power Down Must be configured first by
*   calling HAL_DDR_Chipselect().
*
*   @par Side Effects
*   After ddr has gone into Deep Power Down, all the data stored will be lost.
*   Also, when returning from deep power down, we must reinitialize the DDR.
*
*   @retval  None
*
*   @sa None
*/
boolean HAL_DDR_Enter_Deep_Power_Down(DDR_STRUCT *ddr, DDR_CHANNEL channel,
                                      DDR_CHIPSELECT);

/* ============================================================================
**  Function : HAL_DDR_Exit_Deep_Power_Down
** ============================================================================
*/
/*!
*   @brief
*   Brief_Description_Goes_here
*
*   @details
*   Detailed_Description_Goes_here
*
*   @param clkspeed   -  [IN] Clock speed to reinitialize ddr for
*
*   @par Dependencies
*   Clock must be setup for initialization speed.
*   LPDDR1 - no limitation
*   LPDDR2 - < 50Mhz
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
boolean HAL_DDR_Exit_Deep_Power_Down(DDR_STRUCT *ddr, DDR_CHANNEL channel,
                                     DDR_CHIPSELECT, uint32 clkspeed);

/* =============================================================================
**  Function : HAL_DDR_Read_Mode_Register
** =============================================================================
*/
/**
*   @brief
*   Read DDR mode register.
*
*   @param[in]  channel    channel to read mode register for
*   @param[in]  chip_select  Chip select to read mode register for
*   @param[in]  mr_addr      Mode register address
*
*   @return
*   Mode register data that is read back.
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint32 HAL_DDR_Read_Mode_Register(DDR_STRUCT *ddr, DDR_CHANNEL channel,
                                  DDR_CHIPSELECT chip_select, uint32 mr_addr);

/* =============================================================================
**  Function : HAL_DDR_Write_Mode_Register
** =============================================================================
*/
/**
*   @brief
*   Write DDR mode register.
*
*   @param[in]  channel    channel to write mode register for
*   @param[in]  chip_select  Chip select to write mode register for
*   @param[in]  mr_addr      Mode register address
*   @param[in]  mr_data      Mode register data to write
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_Write_Mode_Register(DDR_STRUCT *ddr, DDR_CHANNEL channel,
                                    DDR_CHIPSELECT chip_select, uint32 mr_addr, uint32 mr_data);

/* =============================================================================
**  Function : HAL_DDR_ZQ_Calibration
** =============================================================================
*/
/**
*   @brief
*   Perform manual ZQ calibration.
*
*   @param[in]  channel    Channel to perform ZQ calibration on.
*   @param[in]  chip_select  Chip select to perform ZQ calibration on.
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_ZQ_Calibration (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);

/* =============================================================================
**  Function : HAL_DDR_IOCTL
** =============================================================================
*/
/**
*   @brief
*   Standard IOCTL API for various controls, debug, get/set APIs.
*
*   @param[in]  ddr         Pointer to ddr configuration struct.
*   @param[in]  cmd         Indicates the type of IOCTL commands.
*   @param[in]  arg         Pointer to structure/union of all possible arguments.
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean HAL_DDR_IOCTL (DDR_STRUCT *ddr, IOCTL_CMD ioctl_cmd, IOCTL_ARG *ioctl_arg);

#endif /* __HAL_SNS_DDR_H__ */
