#ifndef __PM_FG_DRIVER_H__
#define __PM_FG_DRIVER_H__

/*! \file pm_fg_driver.h
 *  \n
 *  \brief This file contains FG peripheral driver related function prototypes,
 *         enums and driver data structure type.   
 *  \n  
 *  \n &copy; Copyright 2014-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/pmic/pm/drivers/fg/src/pm_fg_driver.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
11/18/14    aab    Added fg_adc_usr_register_ds
09/22/14    aab    Porting FG driver to SBL 
08/20/14    al     Updating comm lib 
04/02/14    va     New File
========================================================================== */

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "pm_err_flags.h"
#include "pm_comm.h"

/*===========================================================================
                        TYPE DEFINES AND ENUMS
===========================================================================*/

/*  FG ADC User register */
typedef struct
{
  pm_register_address_type base_address;
  pm_register_address_type peripheral_offset;

  // bcl values after first reading from ADC are obtained
  pm_register_address_type fg_adc_usr_bcl_values;    //0x053
  // VBAT
  pm_register_address_type fg_adc_usr_vbat;          //0x054
  pm_register_address_type fg_adc_usr_vbat_cp;       //0x056
  //Gain Correction
  pm_register_address_type fg_adc_usr_bcl_v_gain_batt;//0x060

}fg_adc_usr_register_ds;

typedef struct
{
  fg_adc_usr_register_ds  *adc_usr_register;

}fg_register_ds;

typedef struct
{
    pm_comm_info_type     *comm_ptr;
    fg_register_ds        *fg_register;
    uint8                 num_of_peripherals;
}pm_fg_data_type;


/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/

/* driver init */
void pm_fg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_fg_data_type* pm_fg_get_data(uint8 pmic_index);

uint8 pm_fg_get_num_peripherals(uint8 pmic_index);

#endif // __PM_FG_DRIVER_H__
