/*! \file pm_init.c
*   \n
*   \brief This file contains PMIC initialization function which initializes the PMIC Comm
*   \n layer, PMIC drivers and PMIC applications.
*   \n
*   \n &copy; Copyright 2010-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
11/03/16   aab     Updated pm_driver_post_init() to clear OCP status
08/04/16   aab     Updated pm_driver_init() to support debug logging
01/25/16   aab     Updated pm_driver_init() to support RUMI targets with out PMIC
09/25/15   aab     Updated pm_device_setup(void) and Renamed pm_target_information_spmi_chnl_cfg() to pm_bus_init() 
08/08/15   aab     Added pm_device_setup()
06/23/15   aab     Updated pm_driver_init() to ensure if pm device is initialized.
                    pm_driver_init may be called directly in dload mode.
05/31/15   aab     Removed pm_oem_init()
07/16/14   akm     Comm change Updates
03/31/14   akm     Cleanup
01/15/13   aab     Fixed KW error
05/10/11   jtn     Fix RPM init bug for 8960
07/01/10   umr     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_resource_manager.h"
#include "pm_sbl_boot.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_target_information.h"
#include "SpmiCfg.h"
#include "pm_boot.h"
#include "CoreVerify.h"
#include "pm_utils.h"
#include "pm_app_vreg.h"


/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/
static boolean pm_device_setup_done = FALSE;


/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
pm_err_flag_type
pm_device_setup(void)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

    if(FALSE == pm_device_setup_done)
    {
       //SPMI init: Must be called before calling any SPMI R/W.
       err_flag |= pm_bus_init();

        err_flag |= pm_comm_channel_init_internal();
        err_flag |= pm_version_detect();

        pm_device_setup_done = TRUE;
    }
    return err_flag;
}




pm_err_flag_type pm_driver_init( void )
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    pm_sbl_specific_data_type *config_param_ptr = NULL;
    uint32 initial_num_spmi_trans;

    err_flag |= pm_device_setup();     
    pm_target_information_init();
    pm_comm_info_init();

    config_param_ptr = (pm_sbl_specific_data_type*)pm_target_information_get_specific_info(PM_PROP_SBL_SPECIFIC_DATA);
    CORE_VERIFY_PTR(config_param_ptr);
    initial_num_spmi_trans = pm_log_num_spmi_transaction(0, FALSE);

    //PMICs are Not currently supported in RUMI
    uint8 pmic_index = (uint8) PMIC_A_SLAVEID_PRIM / 2;
    pm_model_type pmic_model = PMIC_IS_INVALID;
    pmic_model = pm_get_pmic_model(pmic_index);
    if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
    {
        return err_flag = PM_ERR_FLAG__SUCCESS; //Temp Fix:  PMICs are Not currently supported in RUMI
    }

    err_flag |= pm_driver_pre_init ();
    pm_resource_manager_init();
    err_flag |= pm_driver_post_init ();
    
    pm_log_num_spmi_transaction(initial_num_spmi_trans, config_param_ptr->verbose_uart_logging);
    err_flag |= pm_app_vreg_clear_ocp_status(); // To Clear OCP Status of LDO's and SMPS.
    return err_flag;
}



/* =========================================================================
**  Function :  pm_target_information_spmi_chnl_cfg
** =========================================================================*/
/**
  Description: The function retrieves PMIC property handle.
               On success it queries the SPMI configurations.
               It configures SPMI channel and interrupt ownership for peripherals.
  @param [in] pmic_prop: property name
  @return
  PM_ERR_FLAG__SUCCESS on success otherwise PM_ERR_FLAG__SPMI_OPT_ERR.
  @dependencies
  SPMI APIs.
  @sa None
*/

pm_err_flag_type
pm_bus_init()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

  /* Initialize SPMI and enable SPMI global interrupt. */
  if (SpmiCfg_Init(TRUE) == SPMI_SUCCESS)
  {
    /* Auto configure SPMI channel and peripheral interrupt ownership. */
    if (SpmiCfg_SetDynamicChannelMode(TRUE) != SPMI_SUCCESS)
    {
      err_flag = PM_ERR_FLAG__SPMI_OPT_ERR;
    }
  }
  else 
  {
     err_flag  = PM_ERR_FLAG__SPMI_OPT_ERR;
  }

  return err_flag;
}
