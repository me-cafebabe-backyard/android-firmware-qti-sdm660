/*=============================================================================

                       Boot Shared Functions Producer

GENERAL DESCRIPTION
  This file contains definitions of functions for boot shared functions.

Copyright 2014 - 2017 by QUALCOMM Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/11/17   bd      PMIC WDG support in DLOAD mode for minidump case
03/08/17   sj      Added Api to qurey the battery status in XBL ramdump
03/08/17   bd      Add SDCC read APIs for DLOAD mode
02/28/17   yps     Share platform-id APIs from XBL-loader->XBL-ramdump over shared-function-table interface
02/07/17   vg      Share DAL APIs from XBL-loader->XBL-ramdump over shared-function-table interface
01/19/17   bd       Add boot_dload_read_saved_cookie
12/08/16   kvs     Added sbl1_get_current_el
11/07/16   yps    enable boot_pm_dev_get_pon_reason_history in ramdump
09/06/16   yps     Enable Smem API in Ramdump
10/14/16   ds      boot_set_pwrkey_reset_type and boot_set_pshold_reset_type
10/12/16   ds      boot_set_pwrkey_to_hardreset
07/15/16   yps     Remove Sec lib
06/23/16   kpa     Added api's to support Display in ramdump image
06/20/16   kpa     Added DALSYS_Malloc and DALSYS_Free functions
06/13/16   jch      added pm_schg_usb_get_typec_status
04/06/16   kpa     rename boot_fastcall_scm_2arg to boot_fastcall_scm
03/09/16   kpa     remove cache api's from shared functions, add fastcall
02/26/16   aab     Updated to match latest pmic charger driver
01/12/16   kameya  Rename qusb_pbl_dload_check to qusb_ldr_utils_fedl_check
09/16/15   kpa     Added dcache_inval_region
08/24/15   ck      Added boot_dload_transition_pbl_forced_dload
08/06/15   as      Use shared functions
08/01/15   kpa     Added dcache_flush_region
07/28/15   rp      Added Clock_SetBIMCSpeed
06/25/15   as      Added sbl1_get_shared_data and boot_sbl_qsee_interface_get_image_entry
04/23/15   kpa     Added pmic and hotplug apis
10/01/14   ck      Removed Hotplug functions
09/30/14   ck      Added boot_err_fatal
09/30/14   ck      Removing efs functions as EFS driver properly split
09/23/14   ck      Added boot extern crypto, efs, and seccfg interface functions
07/15/14   ck      Intial creation
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_shared_functions_producer.h"


void
boot_shared_functions_register(void)
{
  boot_shared_functions_type * function_table = 
    (boot_shared_functions_type *)SCL_SBL1_SHARED_FUNCTIONS_TABLE_BASE;


  /* Assign each function pointer here.  When adding new functions simply
     add to this list. */

  function_table->boot_CeMLDeInit = &boot_CeMLDeInit;
  function_table->boot_CeMLHashDeInit = &boot_CeMLHashDeInit;
  function_table->boot_CeMLHashFinal = &boot_CeMLHashFinal;
  function_table->boot_CeMLHashInit = &boot_CeMLHashInit;
  function_table->boot_CeMLHashSetParam = &boot_CeMLHashSetParam;
  function_table->boot_CeMLHashUpdate = &boot_CeMLHashUpdate;
  function_table->boot_CeMLInit = &boot_CeMLInit;
  function_table->boot_PrngML_getdata_lite = &boot_PrngML_getdata_lite;
  function_table->boot_sw_cipher_init = &boot_sw_cipher_init;
  function_table->boot_sw_cipher_post_init = &boot_sw_cipher_post_init;
  function_table->boot_encr_aes_key = &boot_encr_aes_key;  
  function_table->boot_sw_cipher = &boot_sw_cipher;  
  function_table->boot_clobber_clear_whitelist_table = &boot_clobber_clear_whitelist_table;
  function_table->boot_clobber_check_global_whitelist_range = &boot_clobber_check_global_whitelist_range;
  function_table->boot_dload_transition_pbl_forced_dload = &boot_dload_transition_pbl_forced_dload;
  function_table->boot_dload_set_cookie = &boot_dload_set_cookie;
  function_table->boot_dload_read_saved_cookie = &boot_dload_read_saved_cookie;
  function_table->boot_enable_led = &boot_enable_led;
  function_table->boot_err_fatal = &boot_err_fatal;
  function_table->boot_error_handler = bl_err_if.error_handler;
  function_table->boot_flash_dev_if_get_singleton = &boot_flash_dev_if_get_singleton;
  function_table->boot_get_ddr_info = &boot_get_ddr_info;
  function_table->boot_hw_reset = &boot_hw_reset;
  function_table->boot_install_error_callback = bl_err_if.install_callback;
  function_table->boot_log_message = &boot_log_message;
  function_table->boot_pbl_is_auth_enabled = &boot_pbl_is_auth_enabled;
  function_table->boot_is_auth_enabled = &boot_is_auth_enabled;
  function_table->boot_auth_load_header = &boot_auth_load_header;
  function_table->boot_update_auth_image_info = &boot_update_auth_image_info;
  function_table->boot_auth_image = &boot_auth_image;
  function_table->boot_pm_dev_get_power_on_reason = &boot_pm_dev_get_power_on_reason;
  function_table->boot_pm_get_pon_reason_history_to_dump = &boot_pm_get_pon_reason_history_to_dump;
  function_table->boot_qsee_is_memory_dump_allowed = &boot_qsee_is_memory_dump_allowed;
  function_table->boot_qsee_is_retail_unlocked = &boot_qsee_is_retail_unlocked;
  function_table->boot_qsee_zero_peripheral_memory = &boot_qsee_zero_peripheral_memory;
  function_table->boot_toggle_led = &boot_toggle_led;
  function_table->boot_toggle_led_init = &boot_toggle_led_init;
  function_table->boot_sbl_qsee_interface_get_image_entry = &boot_sbl_qsee_interface_get_image_entry;

  function_table->sbl1_get_shared_data = &sbl1_get_shared_data;
  function_table->sbl_error_handler = &sbl_error_handler;
  function_table->sbl1_hw_get_reset_status = &sbl1_hw_get_reset_status;
  function_table->sbl1_load_ddr_training_data_from_partition = &sbl1_load_ddr_training_data_from_partition;

  function_table->hotplug_get_partition_size_by_image_id = &hotplug_get_partition_size_by_image_id;
  function_table->dev_sdcc_write_bytes = &dev_sdcc_write_bytes;
  function_table->dev_sdcc_read_bytes = &dev_sdcc_read_bytes;
  function_table->get_hotplug_dev_handle = &get_hotplug_dev_handle;  
  
  function_table->boot_set_pwrkey_reset_type = &boot_set_pwrkey_reset_type;
  function_table->boot_set_pshold_reset_type = &boot_set_pshold_reset_type;
   
  /*API's used by USB driver */
  function_table->pm_schg_usb_irq_status = &pm_schg_usb_irq_status;
  function_table->pm_schg_usb_get_typec_status = &pm_schg_usb_get_typec_status;
  function_table->qusb_ldr_utils_fedl_check = &qusb_ldr_utils_fedl_check;
  
  function_table->Clock_SetBIMCSpeed = &Clock_SetBIMCSpeed;

  function_table->boot_scm = &boot_scm;
  function_table->sbl1_get_current_el = &sbl1_get_current_el;
  function_table->DALSYS_Malloc = &DALSYS_Malloc;
  function_table->boot_DalPlatformInfo_PlatformInfo = &boot_DalPlatformInfo_PlatformInfo;
  function_table->boot_DalPlatformInfo_ChipId = &boot_DalPlatformInfo_ChipId;
  function_table->boot_DalPlatformInfo_ChipFamily = &boot_DalPlatformInfo_ChipFamily;
  function_table->DALSYS_Free = &DALSYS_Free;
  
  function_table->DAL_DeviceAttach=&DAL_DeviceAttach;
  function_table->DAL_DeviceAttachEx=&DAL_DeviceAttachEx;
  function_table->DAL_DeviceDetach=&DAL_DeviceDetach;
  
  function_table->DALSYS_GetDALPropertyHandle=&DALSYS_GetDALPropertyHandle;
  function_table->DALSYS_GetDALPropertyHandleStr=&DALSYS_GetDALPropertyHandleStr;
  function_table->DALSYS_GetPropertyValue=&DALSYS_GetPropertyValue;
  
  function_table->DALSYS_memset=&DALSYS_memset;
  function_table->DALSYS_LogEvent=&DALSYS_LogEvent;
  function_table->DALSYS_BusyWait=&DALSYS_BusyWait;
  
  function_table->DALSYS_EventCreate=&DALSYS_EventCreate;
  function_table->DALSYS_DestroyObject=&DALSYS_DestroyObject;
  function_table->DALSYS_EventCtrlEx=&DALSYS_EventCtrlEx;
  function_table->DALSYS_SyncCreate=&DALSYS_SyncCreate;
  function_table->DALSYS_MemRegionAlloc=&DALSYS_MemRegionAlloc;
  function_table->DALSYS_MemInfo=&DALSYS_MemInfo;
  function_table->DALSYS_EventMultipleWait=&DALSYS_EventMultipleWait;
  
  function_table->busywait = &busywait;
  function_table->busywait_init = &busywait_init;
  function_table->boot_log_get_init_info = &boot_log_get_init_info;  

  function_table->boot_smem_get_addr = &boot_smem_get_addr;
  
  function_table->boot_check_display_vbatt = &boot_check_display_vbatt;
  
  function_table->boot_pm_pon_wdog_enable = &boot_pm_pon_wdog_enable;

  /* Fill in version number and magic cookie values so consumer knows table has
     been populated. */
  function_table->version = SHARED_FUNCTIONS_VERSION;
  function_table->magic_cookie_1 = SHARED_FUNCTIONS_MAGIC_COOKIE_1;
  function_table->magic_cookie_2 = SHARED_FUNCTIONS_MAGIC_COOKIE_2;
}

