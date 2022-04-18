#ifndef __PM_DROOP_DETECT_INTERNAL_H__
#define __PM_DROOP_DETECT_INTERNAL_H__

/*! \file pm_droop_detect_internal.h
 *  \n
 *  \brief This file contains PMIC RPM droop detection related enums, struct types
 *         and function prototypes used internally by the driver.
 *  
 *  \n &copy; Copyright 2014-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_droop_detect_internal.h#1 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/22/14   kt      Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_rpm_utilities.h"
#include "com_dtypes.h"
#include "timetick.h"

/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/

// Num of peripheral's droop detection debug info is stored
#define PM_DROOP_LOG_ARRAY_SIZE        3

// INT_LATCHED_CLR register offset
#define PM_INT_LATCHED_CLR_REG_OFFSET  0x14

/** 
  @enum pm_droop_detect_info_type
  @brief Power Rails droop detection debug info type 
 */
typedef struct
{
    uint64  time_stamp;
    uint32  slave_id;
    uint32  base_address;
    uint8   irq_mask;
}pm_droop_detect_info_type;


typedef struct
{
  pm_droop_detect_info_type *pm_droop_detect_info;
  pm_rail_status_info_type  *pm_droop_rail_status;
  uint32 *pm_droop_detect_count;
  boolean *pm_droop_detect_abort_enable;
  boolean *pm_droop_detect_isr_triggered;
}pm_debug_droop_info_type;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/

/**
 * @brief This function is used to enable/disable the droop 
 *        detection.
 * @param pwr_data Pointer to the power data
 * @param comm_ptr Pointer to the comm. 
 * @param resource_index Resource index.
 * @param enable TRUE/FALSE to enable/disable the droop 
 *               detection.
 * 
 * @return err_flag pm_err_flag_type.
 */
pm_err_flag_type pm_droop_detect_irq_enable(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, 
                                            uint8 resource_index, boolean enable);


/**
 * @brief This function is used to configure the droop 
 *        detection where the VREG_OK/VREG_ERROR irq trigger
 *        type is configured to FALLING_EDGE and an ISR is
 *        registered to the VREG_OK/VREG_ERROR interrupt.
 * @param pwr_data Pointer to the power data
 * @param comm_ptr Pointer to the comm. 
 * @param resource_index Resource index.
 * @param isr_ctx ISR argument to be passed. 
 * 
 * @return err_flag pm_err_flag_type.
 */
pm_err_flag_type pm_droop_detect_irq_config(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, 
                                            uint8 resource_index, uint32 isr_ctx);

#endif //__PM_DROOP_DETECT_INTERNAL_H__
