/*=============================================================================

                       Boot Shared Functions Consumer

GENERAL DESCRIPTION
  This file contains definitions of functions for boot shared functions

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
01/19/17   bd      Add boot_dload_read_saved_cookie
12/08/16   kvs     Added sbl1_get_current_el
11/07/16   yps     enable boot_pm_dev_get_pon_reason_history in ramdump
09/06/16   yps     Enable Smem API in Ramdump
10/14/16   ds      boot_set_pwrkey_reset_type and boot_set_pshold_reset_type
10/12/16   ds      boot_set_pwrkey_to_hardreset
07/15/16   yps     Remove Sec lib
06/23/16   kpa     Added api's to support Display in ramdump image
06/09/16   kpa     Added DALSYS_Malloc and DALSYS_Free functions
06/13/16   jch      added pm_schg_usb_get_typec_status
04/06/16   kpa     rename boot_fastcall_scm_2arg to boot_fastcall_scm
03/09/16   kpa     remove cache api's from shared functions, add fastcall
01/12/16   ka      Renamed qusb_pbl_dload_check() to qusb_ldr_utils_fedl_check()
09/16/15   kpa     Added dcache_inval_region
08/24/15   ck      Added boot_dload_transition_pbl_forced_dload
08/06/15   as      Use shared functions
08/01/15   kpa     Added dcache_flush_region
07/28/15   rp      Added Clock_SetBIMCSpeed
07/11/15   rp	   Changed boot_enable_led function to add an additional parameter
06/25/15   as      Added sbl1_get_shared_data and boot_sbl_qsee_interface_get_image_entry
04/23/15   kpa     Added pmic and hotplug apis
10/01/14   ck      Removed Hotplug functions
09/30/14   ck      Added boot_err_fatal
09/30/14   ck      Removing efs functions as EFS driver properly split
09/23/14   ck      Added boot_extern_crypto_interface functions
09/23/14   ck      Added boot_extern_efs_interface functions
09/23/14   ck      Added boot_extern_seccfg_interface functions
08/05/14   ck      Updated boot_clobber_check_global_whitelist_range prototype
07/14/14   ck      Intial creation
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_shared_functions.h"


/* Following prototypes were copied from boot_error_handler.c */
void boot_error_handler
(
  const char* filename_ptr,     /* File this function was called from -
                                   defined by __FILE__ */
  uint32      line,             /* Line number this function was called
                                   from - defined by  __LINE__ */
  uint32      err_code          /* Enum that describes error type */
);
static void boot_install_error_callback
(
  bl_error_callback_func_type,
  void *,
  bl_error_callback_node_type *node_ptr
);


/* Assign boot shared functions table to memory carved out in scatter load */
static boot_shared_functions_type * shared_functions_table =
  (boot_shared_functions_type *) SCL_SBL1_SHARED_FUNCTIONS_TABLE_BASE;


/* Boot error handler uses a global bl_err_if structure.  Create a new one
   here and assign with functions from the producer. */
boot_error_if_type bl_err_if = 
{
  boot_error_handler,
  boot_install_error_callback
};


boolean boot_shared_functions_init(void)
{
  boolean init_valid = FALSE;


  /* Verify that the shared functions table is the proper version and it was
     filled out by a producer. */
  if ((shared_functions_table->version == SHARED_FUNCTIONS_VERSION) &&
      (shared_functions_table->magic_cookie_1 == SHARED_FUNCTIONS_MAGIC_COOKIE_1) &&
      (shared_functions_table->magic_cookie_2 == SHARED_FUNCTIONS_MAGIC_COOKIE_2))
  {
    init_valid = TRUE;
  }
  
  return init_valid;
}


boolean boot_check_display_allowed()
{
	return shared_functions_table->boot_check_display_vbatt();
}


/* The following functions are the "shim" layer between the original function
   call and execution via function pointer. For each entry in the boot shared
   functions type structure there must be a shim. */

boot_flash_dev_if_type * boot_flash_dev_if_get_singleton(void)
{
  return shared_functions_table->boot_flash_dev_if_get_singleton();
}


void boot_error_handler(const char * filename_ptr,
                        uint32 line,
                        uint32 error)
{
  shared_functions_table->boot_error_handler(filename_ptr,
                                             line,
                                             error);
}


void boot_install_error_callback(bl_error_callback_func_type cb_func,
                                 void * data_ptr,
                                 bl_error_callback_node_type * node_ptr)
{
  shared_functions_table->boot_install_error_callback(cb_func,
                                                      data_ptr,
                                                      node_ptr);
}


boot_boolean boot_enable_led(uint32 led_color, boot_boolean led_on)
{
  return shared_functions_table->boot_enable_led(led_color, led_on);
}


void boot_hw_reset(boot_hw_reset_type reset_type)
{
  shared_functions_table->boot_hw_reset(reset_type);
}


boot_boolean boot_toggle_led(void)
{
  return shared_functions_table->boot_toggle_led();
}


void boot_toggle_led_init(void)
{
  shared_functions_table->boot_toggle_led_init();
}


void boot_log_message(char * message)
{
  shared_functions_table->boot_log_message(message);
}


void boot_clobber_clear_whitelist_table(void)
{
  shared_functions_table->boot_clobber_clear_whitelist_table();
}


boolean boot_clobber_check_global_whitelist_range(const void * start_addr,
                                                  uintnt size)
{
  return shared_functions_table->
    boot_clobber_check_global_whitelist_range(start_addr,
                                              size);
}


void boot_dload_transition_pbl_forced_dload(void)
{
  shared_functions_table->boot_dload_transition_pbl_forced_dload();
}


void boot_dload_set_cookie(void)
{
  shared_functions_table->boot_dload_set_cookie();
}

uint32 boot_dload_read_saved_cookie(void)
{
  return shared_functions_table->boot_dload_read_saved_cookie();
}


boot_boolean boot_pbl_is_auth_enabled(void)
{
  return shared_functions_table->boot_pbl_is_auth_enabled();
}


secboot_hw_etype boot_is_auth_enabled(boot_boolean * is_auth_enabled)
{
  return shared_functions_table->boot_is_auth_enabled(is_auth_enabled);
}


void boot_auth_load_header( mi_boot_image_header_type* image_header )
{
  return shared_functions_table->boot_auth_load_header(image_header);
}


void boot_update_auth_image_info( uint8* hash_buffer_base_addr )
{
  return shared_functions_table->boot_update_auth_image_info(hash_buffer_base_addr);
}


bl_error_boot_type boot_auth_image( struct bl_shared_data_type *bl_shared_data, uint32 image_type )
{
  return shared_functions_table->boot_auth_image(bl_shared_data, image_type);
}


bl_shared_data_type * sbl1_get_shared_data(void)
{
  return shared_functions_table->sbl1_get_shared_data();
}


void sbl_error_handler(void)
{
  shared_functions_table->sbl_error_handler();
}


sbl_if_shared_ddr_device_info_type * boot_get_ddr_info(void)
{
  return shared_functions_table->boot_get_ddr_info();
}


uint32 sbl1_hw_get_reset_status(void)
{
  return shared_functions_table->sbl1_hw_get_reset_status();
}


void sbl1_load_ddr_training_data_from_partition(uint8 * ddr_training_data_buf,
                                                uint32 ddr_training_data_size)
{
  shared_functions_table->
    sbl1_load_ddr_training_data_from_partition(ddr_training_data_buf,
                                               ddr_training_data_size);
}


pm_err_flag_type boot_pm_dev_get_power_on_reason(unsigned pmic_device_index,
                                                 uint64 * pwr_on_reason)
{
  return shared_functions_table->
    boot_pm_dev_get_power_on_reason(pmic_device_index,
                                    pwr_on_reason);
}

pm_err_flag_type boot_pm_get_pon_reason_history_to_dump(pm_pbs_pon_reason_history_data_type* pon_reason_history) 
{ 
  return shared_functions_table-> 
    boot_pm_get_pon_reason_history_to_dump(pon_reason_history); 
} 


boot_boolean
boot_qsee_is_memory_dump_allowed(secboot_verified_info_type * secboot_info)
{
  return shared_functions_table->boot_qsee_is_memory_dump_allowed(secboot_info);
}


boot_boolean
boot_qsee_is_retail_unlocked(secboot_verified_info_type * secboot_info)
{
  return shared_functions_table->boot_qsee_is_retail_unlocked(secboot_info);
}


void boot_qsee_zero_peripheral_memory(void)
{
  shared_functions_table->boot_qsee_zero_peripheral_memory();
}


CeMLErrorType boot_CeMLDeInit(void)
{
  return shared_functions_table->boot_CeMLDeInit();
}


CeMLErrorType boot_CeMLHashDeInit(CeMLCntxHandle ** _h)
{
  return shared_functions_table->boot_CeMLHashDeInit(_h);
}


CeMLErrorType boot_CeMLHashFinal(CeMLCntxHandle * _h,
                                 CEMLIovecListType * ioVecOut)
{
  return shared_functions_table->boot_CeMLHashFinal(_h,
                                                    ioVecOut);
} 


CeMLErrorType boot_CeMLHashInit(CeMLCntxHandle ** _h,
                                CeMLHashAlgoType pAlgo)
{
  return shared_functions_table->boot_CeMLHashInit(_h,
                                                   pAlgo);
}


CeMLErrorType boot_CeMLHashSetParam(CeMLCntxHandle * _h,
                                    CeMLHashParamType nParamID, 
                                    const void * pParam, 
                                    uint32 cParam,
                                    CeMLHashAlgoType pAlgo)
{
  return shared_functions_table->boot_CeMLHashSetParam(_h,
                                                       nParamID,
                                                       pParam,
                                                       cParam,
                                                       pAlgo);
}


CeMLErrorType boot_CeMLHashUpdate(CeMLCntxHandle * _h,
                                  CEMLIovecListType ioVecIn)
{
  return shared_functions_table->boot_CeMLHashUpdate(_h,
                                                     ioVecIn);
}


CeMLErrorType boot_CeMLInit(void)
{
  return shared_functions_table->boot_CeMLInit();
}

PrngML_Result_Type boot_PrngML_getdata_lite(uint8*  random_ptr, uint16  random_len)
{
  return shared_functions_table->boot_PrngML_getdata_lite(random_ptr,random_len);
}

void boot_sw_cipher_init(void)
{
  shared_functions_table->boot_sw_cipher_init();
}

void boot_sw_cipher_post_init(void)
{
  shared_functions_table->boot_sw_cipher_post_init();
}

void boot_encr_aes_key(uint8 *in, uint32 inlen, uint8 *out, uint32 *outlen)
{
  shared_functions_table->boot_encr_aes_key(in, inlen, out, outlen);
}

int boot_sw_cipher (
   void   *in, 
   size_t  in_len, 
   void   *out, 
   size_t  out_len,
   void   *key_aes, 
   size_t  key_aes_len,
   void   *key_hmac, 
   size_t  key_hmac_len,
   void   *nonce, 
   size_t  nonce_len,
   void   *tag,
   size_t  tag_len,
   boolean    dir                    //false: encrypt, true: decrypt
)

{
  return shared_functions_table->boot_sw_cipher(in, in_len, out, out_len, key_aes, 
                    key_aes_len,key_hmac, key_hmac_len,nonce, nonce_len, tag, tag_len, dir );
}


void boot_err_fatal(void)
{
  shared_functions_table->boot_err_fatal();
}

uint64 hotplug_get_partition_size_by_image_id(image_type image_id)
{
  return shared_functions_table->hotplug_get_partition_size_by_image_id(image_id);
}

boolean dev_sdcc_write_bytes(void * ram_addr,
                             uint64 dst_offset,
                             uint32 bytes_to_write,
                             image_type image_id)
{
  return shared_functions_table->dev_sdcc_write_bytes(ram_addr,
                                                      dst_offset,
                                                      bytes_to_write,
                                                      image_id);
}

boolean dev_sdcc_read_bytes(void * ram_addr,
                             uint64 dst_offset,
                             uint32 bytes_to_read,
                             uint32 parti_id)
{
  return shared_functions_table->dev_sdcc_read_bytes(ram_addr,
                                                      dst_offset,
                                                      bytes_to_read,
                                                      parti_id);
}

int16 get_hotplug_dev_handle(image_type image_id)
{
  return shared_functions_table->get_hotplug_dev_handle(image_id);
}

void boot_set_pwrkey_reset_type(boot_hw_reset_type reset_type)
{
  shared_functions_table->boot_set_pwrkey_reset_type(reset_type);
}

void boot_set_pshold_reset_type(boot_hw_reset_type reset_type)
{
  shared_functions_table->boot_set_pshold_reset_type(reset_type);
}

  /*API's used by USB driver */

pm_err_flag_type pm_schg_usb_irq_status(uint32 device_index, 
                                                  pm_schg_usb_irq_type irq, 
                                                  pm_irq_status_type type, 
                                                  boolean *status )
{
  return shared_functions_table->pm_schg_usb_irq_status(device_index,
                                                                 irq,
                                                                 type,
                                                                 status);
}
  
pm_err_flag_type pm_schg_usb_get_typec_status(uint32 pmic_device, 
                                              pm_schg_usb_typec_status_type *typec_status)
{
  return shared_functions_table->pm_schg_usb_get_typec_status(pmic_device, typec_status);
}

boolean qusb_ldr_utils_fedl_check(void)
{
  return shared_functions_table->qusb_ldr_utils_fedl_check();
}

boolean Clock_SetBIMCSpeed(uint32 nFreqKHz )
{
  return shared_functions_table->Clock_SetBIMCSpeed(nFreqKHz);
}

int32 boot_sbl_qsee_interface_get_image_entry(boot_sbl_qsee_interface * sbl_qsee_interface,
                                              secboot_sw_type image_id)
{
  return shared_functions_table->boot_sbl_qsee_interface_get_image_entry(sbl_qsee_interface,
                                                                         image_id);
}


int boot_scm(uintnt smc_id, uintnt param_id, uintnt r0, uintnt r1, uintnt r2,
             uintnt r3, uintnt session_id, boot_tzt_result_regs_t* resp_buff_ptr)
{
  return shared_functions_table->boot_scm(smc_id, param_id, r0, r1, r2, r3, session_id, resp_buff_ptr);
}

uint32 sbl1_get_current_el( void )
{
  return shared_functions_table->sbl1_get_current_el();
}

DALResult DALSYS_Malloc(uint32 dwSize, void **ppMem)
{
  return shared_functions_table->DALSYS_Malloc(dwSize, ppMem);
}

DALResult DALSYS_Free(void *pmem)
{
  return shared_functions_table->DALSYS_Free(pmem);
}

DALResult
DAL_DeviceAttach(DALDEVICEID DeviceId,DalDeviceHandle **phDevice)
{
  return shared_functions_table->DAL_DeviceAttach(DeviceId,phDevice);
}

DALResult
DAL_DeviceAttachEx(const char *pszArg, DALDEVICEID DeviceId,
               DALInterfaceVersion ClientVersion,DalDeviceHandle **phDevice)
{
  return shared_functions_table->DAL_DeviceAttachEx(pszArg,DeviceId,ClientVersion,phDevice);
}
			   
DALResult
DAL_DeviceDetach(DalDeviceHandle *hDevice)
{
  return shared_functions_table->DAL_DeviceDetach(hDevice);
}

DALResult
DALSYS_GetDALPropertyHandle(DALDEVICEID DeviceId,DALSYSPropertyHandle hDALProps)
{
  return shared_functions_table->DALSYS_GetDALPropertyHandle(DeviceId,hDALProps);
}

DALResult
DALSYS_GetDALPropertyHandleStr(const char *pszDevName, DALSYSPropertyHandle hDALProps)
{
  return shared_functions_table->DALSYS_GetDALPropertyHandleStr(pszDevName,hDALProps);
}

DALResult
DALSYS_GetPropertyValue(DALSYSPropertyHandle hDALProps, const char *pszName,
                  uint32 dwId,
                   DALSYSPropertyVar *pDALPropVar)
{
  return shared_functions_table->DALSYS_GetPropertyValue(hDALProps,pszName,dwId,pDALPropVar);
}

void DALSYS_LogEvent(DALDEVICEID DeviceId, uint32 dwLogEventType, const char * pszFmt,
                ...)
{
  return shared_functions_table->DALSYS_LogEvent(DeviceId,dwLogEventType,pszFmt);                 
}

void
DALSYS_BusyWait(uint32 pause_time_us)
{
  return shared_functions_table->DALSYS_BusyWait(pause_time_us);
}

VOID * DALSYS_memset(VOID * buffer, UINT8 value, UINTN length)
{
  return shared_functions_table->DALSYS_memset(buffer,value,length);
}

DALResult
DALSYS_EventCreate(uint32 dwAttribs, DALSYSEventHandle *phEvent,
               DALSYSEventObj *pEventObj)
{
   return shared_functions_table->DALSYS_EventCreate(dwAttribs,phEvent,pEventObj);
}

DALResult
DALSYS_DestroyObject(DALSYSObjHandle hObj)
{
  return shared_functions_table->DALSYS_DestroyObject(hObj);
}

DALResult
DALSYS_EventCtrlEx(DALSYSEventHandle hEvent, uint32 dwCtrl, uint32 dwParam,
                   void *pPayload, uint32 dwPayloadSize)
{
  return shared_functions_table->DALSYS_EventCtrlEx(hEvent,  dwCtrl,  dwParam,
                    pPayload,  dwPayloadSize);
}
 
DALResult
DALSYS_SyncCreate(uint32 dwAttribs,
                  DALSYSSyncHandle *phSync,
                  DALSYSSyncObj *pSyncObj)
{
  return shared_functions_table->DALSYS_SyncCreate(dwAttribs,phSync,pSyncObj);               
}

DALResult DALSYS_MemRegionAlloc (uint32 dwAttribs, DALSYSMemAddr VirtualAddr,
               DALSYSMemAddr PhysicalAddr, uint32 dwLen, DALSYSMemHandle *phMem,DALSYSMemObj *pMemObj)
{
  return shared_functions_table->DALSYS_MemRegionAlloc(dwAttribs,VirtualAddr,PhysicalAddr,dwLen,phMem,pMemObj);
}

DALResult
DALSYS_MemInfo(DALSYSMemHandle hMem, DALSYSMemInfo *pMemInfo)
{
  return shared_functions_table->DALSYS_MemInfo(hMem,pMemInfo);
}    

DALResult 
DALSYS_EventMultipleWait (DALSYSEventHandle* phEvent, int nEvents,
                         uint32 dwTimeoutUs,uint32 *pdwEventIdx)
{
  return shared_functions_table->DALSYS_EventMultipleWait(phEvent,nEvents,dwTimeoutUs,pdwEventIdx);                          
}
DALResult boot_DalPlatformInfo_Platforminfo(void *pPlatforminfo)
{
  return shared_functions_table->boot_DalPlatformInfo_PlatformInfo(pPlatforminfo);
}

DALResult boot_DalPlatformInfo_ChipId(void * pChipSetId)

{
  return shared_functions_table->boot_DalPlatformInfo_ChipId(pChipSetId);
}

DALResult boot_DalPlatformInfo_ChipFamily(void * pChipsetfamily)

{
  return shared_functions_table->boot_DalPlatformInfo_ChipFamily(pChipsetfamily);
}

void busywait (uint32 pause_time_us)
{
  return shared_functions_table->busywait(pause_time_us);
}

DALResult busywait_init(void)
{
  return shared_functions_table->busywait_init();
}

boolean boot_log_get_init_info(uint8 **log_base_addr_ptr, uintnt *size_ptr)
{
  return shared_functions_table->boot_log_get_init_info(log_base_addr_ptr,
                                                         size_ptr);
}

void * boot_smem_get_addr(smem_mem_type smem_type, uint32 *buf_size)
{
  return shared_functions_table->boot_smem_get_addr(smem_type, buf_size);
}

pm_err_flag_type boot_pm_pon_wdog_enable(uint8 pmic_device_index,pm_on_off_type enable)
{
  return shared_functions_table->boot_pm_pon_wdog_enable(pmic_device_index, enable);
}
