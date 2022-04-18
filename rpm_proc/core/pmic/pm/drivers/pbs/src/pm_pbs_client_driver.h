#ifndef __PM_PBS_CLIENT_DRIVER_H__
#define __PM_PBS_CLIENT_DRIVER_H__

/*! \file pm_pbs_client_driver.h 
*  \n 
*  \brief PBS Client driver type definitions and init function prototype.   
*  \n  
*  \n &copy; Copyright 2015 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/drivers/pbs/src/pm_pbs_client_driver.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/25/15   kt      Initial version
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_comm.h"


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

typedef enum 
{
  PM_PBS_CLIENT_0  = 0,   /**< PBS client 0. */
  PM_PBS_CLIENT_1  = 1,   /**< PBS client 1. */
  PM_PBS_CLIENT_2  = 2,   /**< PBS client 2. */
  PM_PBS_CLIENT_3  = 3,   /**< PBS client 3. */
  PM_PBS_CLIENT_4  = 4,   /**< PBS client 4. */
  PM_PBS_CLIENT_5  = 5,   /**< PBS client 5. */
  PM_PBS_CLIENT_6  = 6,   /**< PBS client 6. */
  PM_PBS_CLIENT_7  = 7,   /**< PBS client 7. */
  PM_PBS_CLIENT_8  = 8,   /**< PBS client 8. */
  PM_PBS_CLIENT_9  = 9,   /**< PBS client 9. */
  PM_PBS_CLIENT_10 = 10,  /**< PBS client 10. */
  PM_PBS_CLIENT_11 = 11,  /**< PBS client 11. */
  PM_PBS_CLIENT_12 = 12,  /**< PBS client 12. */
  PM_PBS_CLIENT_13 = 13,  /**< PBS client 13. */
  PM_PBS_CLIENT_14 = 14,  /**< PBS client 14. */
  PM_PBS_CLIENT_15 = 15,  /**< PBS client 15. */
  PM_PBS_CLIENT_INVALID
}pm_pbs_client_type;

typedef struct
{
    pm_register_address_type base_address;
    pm_register_address_type peripheral_offset;
    pm_register_address_type trig_ctl;
    pm_register_address_type en_ctl;
}pm_pbs_client_register_info_type;

typedef struct
{
    pm_comm_info_type                  *comm_ptr;
    pm_pbs_client_register_info_type   *pbs_client_reg_table;   
    uint8                              num_of_peripherals;
}pm_pbs_client_data_type;

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
void pm_pbs_client_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_pbs_client_data_type* pm_pbs_client_get_data(uint8 pmic_index);

uint8 pm_pbs_client_get_num_peripherals(uint8 pmic_index);

pm_err_flag_type pm_pbs_client_sw_trigger(uint8 pmic_chip, pm_pbs_client_type client);

#endif /* __PM_PBS_CLIENT_DRIVER_H__ */
