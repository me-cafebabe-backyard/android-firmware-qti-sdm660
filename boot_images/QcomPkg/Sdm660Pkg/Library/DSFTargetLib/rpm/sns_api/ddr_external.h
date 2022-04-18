#ifndef __DDR_EXTERNAL_H__
#define __DDR_EXTERNAL_H__

/*=============================================================================

                                DDR EXTERNAL
                                Header File
GENERAL DESCRIPTION
 This file defines the external environment APIs that DDR HAL layers may need to invoke


Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/sns_api/ddr_external.h#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
12/01/13   dp      Initial version.
==============================================================================*/
/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "HALcomdef.h"
#include "seq_hwio.h"

/*==============================================================================
                                  TYPES
==============================================================================*/

enum{
    DDR_SOC_MSM8994_V1 = 0x000B0100,
    DDR_SOC_MSM8994_V2 = 0x000B0200,
    DDR_SOC_MSM8992_V1 = 0x000E0100,
    DDR_SOC_MSM8996_V1 = 0x30000100,
    DDR_SOC_MSM8996_V2 = 0x30000200,
    DDR_SOC_MSM8997_V1 = 0x30050100,
    DDR_SOC_MSM8998_V1 = 0x30020100
};

typedef enum 
{	
  DDR_TRAINING_READ,	
  DDR_TRAINING_WRITE, 
  DDR_TRAINING_CACK
}ddr_training_type;

typedef struct 
{
  uint8 currentChannel;
  uint8 currentChipSelect;
  uint8 currentFreqIndex;
  uint8 best_cdc_value;
  uint8 best_vref_value;
  uint32 FreqInKhz;
  ddr_training_type trainingType;	
}ddr_training_args;

/*==============================================================================
                                  MACROS
==============================================================================*/
/* Macro for round-up division */
#define div_ceil(n, d)  (((n) + (d) - 1) / (d))

/*==============================================================================
                                  FUNCTION PROTOTYPES
==============================================================================*/

#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED
  boolean ddr_external_set_clk_speed(uint32 clk_in_khz);
#else
  static inline boolean ddr_external_set_clk_speed(uint32 clk_in_khz)
  {
    return TRUE;
  }
#endif



/* ============================================================================
**  Function : ddr_mpm_config_ebi1_freeze_io
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library while entering/exiting Power Collapse
*   
*   @details
*   This api will be called by SNS library to enable/disable IO clamps during PC
*   
*   @param 
*   @param flag             -  [IN] boolean flag to enable/disable IO clamps
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
  void ddr_mpm_config_ebi1_freeze_io( boolean flag ); 
#else 
  static inline void ddr_mpm_config_ebi1_freeze_io( boolean flag ) 
  { 
    return; 
  } 
#endif


/* ============================================================================
**  Function : ddr_mpm_config_ebi1_freeze_io_sdi
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library while entering/exiting Power Collapse
*   
*   @details
*   This api will be called by SNS library to enable/disable IO clamps during PC
*   
*   @param 
*   @param flag             -  [IN] boolean flag to enable/disable IO clamps
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
  void ddr_mpm_config_ebi1_freeze_io_sdi( boolean flag ); 
#else 
  static inline void ddr_mpm_config_ebi1_freeze_io_sdi( boolean flag ) 
  { 
    return; 
  } 
#endif


/* ============================================================================
**  Function : seq_wait
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to introduce wait/delay
*   
*   @details
*   This api will call the relevant busywait function to introduce needed delay.
*   
*   @param 
*   @param time_value       -  [IN] delay time .
*   @param time_unit        -  [IN] time in units (SEC/MS/US/NS etc)
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED
  void seq_wait(uint32 time_value, SEQ_TimeUnit time_unit);
#else
  static inline void seq_wait(uint32 time_value, SEQ_TimeUnit time_unit)
  {
    return;
  } 
#endif

/* ============================================================================
**  Function : ddr_external_get_buffer
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to get a buffer for training
*   intermediate data
*   
*   @details
*   This function is called by external library to get a buffer for training
*   intermediate data
*   
*   @param 
*   @param buffer             -  [IN/OUT] uint32 ** buffer where we will populate 
*                                                   with pointer to buffer
*   @param size               -  [IN/OUT] uint32 *  we will populate with size of 
*                                                   buffer
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   reutrn operation success\failure
*   
*   @sa None
*/
#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
  boolean ddr_external_get_buffer(void **buffer, uint32 *size);
#else
  static inline boolean ddr_external_get_buffer(void **buffer, uint32 *size)
  {
    return TRUE;
  } 
#endif

/* ============================================================================
**  Function : ddr_external_page_to_storage
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to save ddr training logs to 
* 	external non-volatile storage
*   
*   @details
*   This function is called by external library to save ddr training logs to 
* 	external non-volatile storage. This api has to take care of offsets for 
* 	saving to external storage so we do not run out of space.
*   api will perform a memset 0 on input buffer of input size before returning
*   
*   @param 
*   @param buffer             -  [IN] uint32 * buffer where traiing logs are located
*   @param size               -  [IN] uint32 * size of data in buffer
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  void
*
*   
*   @sa None
*/

#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
void ddr_external_page_to_storage( void * buffer, uint32 size );
#else
  static inline void ddr_external_page_to_storage( void * buffer, uint32 size )
  {
    return;
  } 
#endif

/* ============================================================================
**  Function : ddr_external_get_training_log_size
** ============================================================================
*/
/*!
*   @brief
*   This function is used to return the current stored training log size
*   
*   @details
*   This function is used to return the current stored training log size
*   
*   @param 
*   None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  uint32
*   size of current trainig log saved to emmc
*   
*   @sa None
*/
#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
uint32 ddr_external_get_training_log_size(void);
#else
  static inline uint32 ddr_external_get_training_log_size(void)
  {
    return 0;
  } 
#endif

/* ============================================================================
**  Function : ddr_external_set_ddrss_cfg_clk
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to set( ON/OFF ) the GCC_DDR_DIM_CFG
*   
*   @details
*   This function is called by external library to set( ON/OFF ) the GCC_DDR_DIM_CFG
*   
*   @param 
*   @param boolean            -  [IN] boolean flag to enable/disable GCC_DDR_DIM_CFG clock
*                                                   
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   reutrn operation success\failure
*   
*   @sa None
*/

#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
  boolean ddr_external_set_ddrss_cfg_clk(boolean on_off);
#else
  static inline boolean ddr_external_set_ddrss_cfg_clk(boolean on_off)
  {
    return TRUE;
  } 
#endif

/* ============================================================================
**  Function : ddr_abort(void)
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to abort if a small eye is found.
*   
*   @details
*   This function is called by external library to abort if a small eye is found.
*   
*   @param 
*   @param boolean            -  [IN] boolean flag to enable/disable GCC_DDR_DIM_CFG clock
*                                                   
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   reutrn operation success\failure
*   
*   @sa None
*/

#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED 
  void ddr_abort(void);
#else
  static inline void ddr_abort(void)
  {
    return;
  } 
#endif

/* ============================================================================
**  Function : ddr_external_send_data_to_ddi
** ============================================================================
*/
/*!
*   @brief
*   This function is called during training to pass training results to ddi
*   
*   @details
*   This function is called during training to pass training results to ddi
*   
*   @param 
*   @param flag             -  [IN] boolean flag to enable/disable IO clamps
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
#ifdef FEATURE_BOOT_EXTERN_DDR_COMPLETED
  void ddr_external_send_data_to_ddi(void * buffer, uint32 size, ddr_training_args* tArgs, void *training_params_ptr);
#else 
  static inline void ddr_external_send_data_to_ddi(void * buffer, uint32 size, ddr_training_args* tArgs , void *training_params_ptr)
  { 
    return; 
  } 
#endif

#endif /* __DDR_EXTERNAL_H__ */

