#ifndef __PMIC_SBL_CONFIG_TEST_H__
#define __PMIC_SBL_CONFIG_TEST_H__

/*! \file  pm_sbl_config_test.h
 *  
 *  \brief  Contains PMIC Set Mode validation test related declaration
 *  \details  This file contains the Set Mode validation test driver API. 
 *  
 *  &copy; Copyright 2013-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
09/13/16   aab     Updated logging text to match the rest of SBL logging 
09/08/15   pbarot  Update test based on CLogic implementation
06/23/15   pbarot  Creation, Moved Settings validation test code to this file
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#define PM_SBL_TEST_OFFSET_SEC_ACCESS 0x00D0 /* this offset will not be validated */
#define PM_SBL_TEST_OFFSET_INT_EN 0x0015 /* this offset will not be validated */
#define PM_SBL_TEST_REVID_SBL_ID_0 0x0150 /* register to read SBL version */
#define PM_SBL_TEST_REVID_SBL_ID_1 0x0151 /* register to read SBL version */

typedef struct pm_settings_test_flag_reg_info_type
{
  pm_register_address_type         flag_register;          /* flag register utilized to trigger settings validation test code functions*/
} pm_settings_test_flag_reg_info_type;


/*=============================================================================

                              FUNCTION PROTOTYPES

=============================================================================*/

pm_err_flag_type pm_sbl_config_test(void);
pm_err_flag_type pm_pbs_ram_version_validation_test(void);


#endif // __PMIC_SBL_CONFIG_TEST_H__

