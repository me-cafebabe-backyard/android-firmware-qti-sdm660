#ifndef PM_RPM_UTILITIES_H
#define PM_RPM_UTILITIES_H

 /*! \file pm_rpm_utilities.h
 *
 *  \brief This file contains RPM PMIC utility function prototypes.
 *
 *  &copy; Copyright 2012 - 2014 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_rpm_utilities.h#1 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/23/13   hs      Fixed the naming convention in \config.
04/12/13   hs      Code refactoring.

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_rpm_npa.h"
#include "npa.h"
#include "pm_npa.h"
#include "pm_pwr_alg.h"
#include "com_dtypes.h"
#include "pm_comm.h"
#include "pm_rpm_target.h"

/*===========================================================================

                        MACROS AND TYPE DEFINITIONS

===========================================================================*/

#define PM_NUM_OF_RAIL_STATUS_REGS 8
#define PM_SETTLE_LOG_ARRAY_SIZE 3

/* Rail status register dump info */
typedef struct
{
    uint64 time_stamp;
    pm_err_flag_type err_flag;
    uint32 slave_id;
    uint32 base_address;
    uint8 status1_base_reg_dump[PM_NUM_OF_RAIL_STATUS_REGS];
    uint8 vset_lb_base_reg_dump[PM_NUM_OF_RAIL_STATUS_REGS];
    uint8 pd_ctl_base_reg_dump[PM_NUM_OF_RAIL_STATUS_REGS];
}pm_rail_status_info_type;

/* Settling errors log info */
typedef struct
{
    uint32 actual_time_us;
    uint32 estimated_time_us;
    pm_rail_status_info_type rail_status;
    /* Battery status */
    pm_battery_status_type batt_status;
}pm_settle_info_type;

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

/**
 * @brief This function is used to do memcpy and memcmp.
 * @param source Pointer to the source of data to be copied, type-casted to a pointer of type const void*.
 * @param destination Pointer to the destination array where the content is to be copied, type-casted to 
          a pointer of type void*.
 * @param num Number of bytes to copy.
 * 
 * @return Returns an integral value indicating the relationship between the content of the memory blocks:
   A zero value indicates that the contents of both memory blocks are equal.
   A value greater than zero indicates that the first byte that does not match in both memory blocks has a 
   greater value in ptr1 than in ptr2 as if evaluated as unsigned char values; And a value less than zero 
   indicates the opposite.
 */
int pm_rpm_int_copy(void *source, void *destination, size_t num);

/**
 * @brief This function is used to check if a regulator has settled by reading the real time status of VREG_OK register.
 * @param settle_start_time The timestamp at which the rail started to settle. 
 * @param estimated_settling_time_us The estimated time (in uS) that the rail is supposed to take to settle.
 * @param vreg_ok_status Function pointer for checking the VREG_OK status
 * @param pwr_res Pointer to the power resource. 
 * @param resource Pointer to the driver resource. 
 * @param resource_index Resource index.
 * @param settling error enabled - to ignore settling errors
 * 
 * @return returns the final VREG_OK status.
 * @note vreg_ok_status function pointer needs to be initialized when this function gets called.
 */
boolean pm_rpm_check_vreg_settle_status(uint64 settle_start_time, uint32 estimated_settling_time_us, 
                                        pm_pwr_data_type *pwr_res, pm_comm_info_type *comm_ptr, 
                                        uint8 resource_index, boolean settling_err_en);

/**
 * @brief This function is used to check if a regulator has settled by reading the real time status of STEPPER_DONE register.
 * @param settle_start_time The timestamp at which the rail started to settle. 
 * @param estimated_settling_time_us The estimated time (in uS) that the rail is supposed to take to settle.
 * @param stepper_done_status Function pointer for checking the STEPPER_DONE status
 * @param pwr_res Pointer to the power resource.
 * @param resource Pointer to the driver resource. 
 * @param resource_index Resource index.
 * @param settling error enabled - to ignore settling errors
 * 
 * @return returns the final STEPPER_DONE status..
 * @note stepper_done_status function pointer needs to be initialized when this function gets called.
 */
boolean pm_rpm_check_stepper_settle_status(uint64 settle_start_time, uint32 estimated_settling_time_us, 
                                           pm_pwr_data_type *pwr_res, pm_comm_info_type *comm_ptr, 
                                           uint8 resource_index, boolean settling_err_en);

/**
 * @brief This function is used to calculate the vset value from 
 *        voltage.
 * @param rsrc_type RPM resource type.
 * @param rsrc_index resource index.
 * @param volt_uv Voltage value in micro volts.
 * @param vset Pointer to calculated vset value to be returned.
 * 
 * @return return PM_ERR_FLAG__SUCCESS if successful else ERROR.
 */
pm_err_flag_type pm_rpm_calculate_vset(rpm_resource_type rsrc_type, uint32 rsrc_index, uint32 volt_uv, uint32* vset);

/**
 * @brief This function is used to return the current voltage 
 *        status of the rail.
 * @param rsrc_type RPM resource type.
 * @param rsrc_index resource index.
 * @param volt_uv Pointer to voltage value in micro volts to be 
 *                returned.
 * 
 * @return return PM_ERR_FLAG__SUCCESS if successful else ERROR.
 */
pm_err_flag_type pm_rpm_volt_level_status(rpm_resource_type rsrc_type, uint32 rsrc_index, uint32* volt_uv);

/**
 * @brief This function is used to get the raw sw mode status.
 * @param rsrc_type RPM resource type.
 * @param rsrc_index resource index.
 * @param mode Pointer to raw mode reg value to be returned.
 * 
 * @return return PM_ERR_FLAG__SUCCESS if successful else ERROR.
 */
pm_err_flag_type pm_rpm_sw_mode_status_raw(rpm_resource_type rsrc_type, uint32 rsrc_index, uint8* mode);

/**
 * @brief This function is used to return whether the power rail 
 *        peripheral has the new unified register.
 * @param rsrc_type RPM resource type.
 * @param rsrc_index resource index.
 * @param is_periph_unified_reg Pointer to return if the periph 
 *             has unified register
 * 
 * @return return PM_ERR_FLAG__SUCCESS if successful else ERROR.
 */
pm_err_flag_type pm_rpm_is_periph_unified_reg(rpm_resource_type rsrc_type, uint32 rsrc_index, boolean* is_periph_unified_reg);

/**
 * @brief This function is used to collect the power rail status 
 *        register dump.
 * @param slave_id power rail slave id.
 * @param base_address power rail base address
 * @param rail_status Pointer to return the status
 * 
 * @return return PM_ERR_FLAG__SUCCESS if successful else ERROR.
 */
pm_err_flag_type pm_rpm_status_reg_dump(uint32 slave_id, uint32 base_address, pm_rail_status_info_type* rail_status);

#endif //PM_RPM_UTILITIES_H


