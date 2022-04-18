#ifndef BOOT_SHARED_FUNCTIONS_H
#define BOOT_SHARED_FUNCTIONS_H

/*===========================================================================

                                Boot Shared Functions
                                Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Boot's shared 
  functions. 

Copyright 2014 - 2017 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who      what, where, why
--------   ----     ----------------------------------------------------------
05/11/17   bd       PMIC WDG support in DLOAD mode for minidump case
03/08/17   sj       Added Api to qurey the battery status in XBL ramdump
03/08/17   bd       Add SDCC read API for DLOAD mode
02/28/17   yps      Share platform-id APIs from XBL-loader->XBL-ramdump over shared-function-table interface
02/07/17   vg       Share DAL APIs from XBL-loader->XBL-ramdump over shared-function-table interface
01/19/17   bd       Add boot_dload_read_saved_cookie
12/08/16   kvs     Added sbl1_get_current_el
11/07/16   yps      enable boot_pm_dev_get_pon_reason_history in ramdump
10/14/16   ds       boot_set_pwrkey_reset_type and boot_set_pshold_reset_type
09/06/16   yps      Enable Smem API in Ramdump
10/12/16   ds       boot_set_pwrkey_to_hardreset
07/15/16   yps      Remove Sec lib
06/23/16   kpa      Added api's to support Display in ramdump image
06/20/16   kpa      Added DALSYS_Malloc and DALSYS_Free functions
06/13/16   jch      added pm_schg_usb_get_typec_status
04/06/16   kpa      rename boot_fastcall_scm_2arg to boot_fastcall_scm
03/09/16   kpa      Remove cache api's from shared functions, add fastcall support
01/12/16   ka       Renamed qusb_pbl_dload_check() to qusb_ldr_utils_fedl_check()
09/16/15   kpa      Added dcache_inval_region
08/24/15   ck       Added boot_dload_transition_pbl_forced_dload
08/06/15   as       Use shared functions
08/01/15   kpa      Added dcache_flush_region
07/28/15   rp       Added Clock_SetBIMCSpeed
07/11/15   rp	    Changed boot_enable_led function declaration
06/25/15   as       Added sbl1_get_shared_data and boot_sbl_qsee_interface_get_image_entry
04/23/15   kpa      Added pmic and hotplug apis
10/01/14   ck       Removed Hotplug functions
09/30/14   ck       Added boot_err_fatal
09/30/14   ck       Removing efs functions as EFS driver properly split
09/23/14   ck       Added boot_extern_crypto_interface functions
09/23/14   ck       Added boot_extern_efs_interface functions
09/23/14   ck       Added boot_extern_seccfg_interface functions
08/05/14   ck       Updated boot_clobber_check_global_whitelist_range prototype
07/14/14   ck       Initial creation
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include BOOT_PBL_H
#include "boot_comdef.h"
#include "boot_cache_mmu.h"
#include "boot_clobber_prot.h"
#include "boot_ddr_info.h"
#include "boot_dload.h"
#include "boot_error_handler.h"
#include "boot_extern_crypto_interface.h"
#include "boot_extern_hotplug_interface.h"
#include "boot_extern_pmic_interface.h"
#include "boot_extern_seccfg_interface.h"
#include "boot_flash_dev_if.h"
#include "boot_logger.h"
#include "boot_sdcc.h"
#include "boot_visual_indication.h"
#include "boothw_target.h"
#include "sbl1_hw.h"
#include "sbl1_mc.h"
#include "pm_schg_usb.h"
#include "qusb_ldr_utils.h"
#include "ClockBoot.h"
#include "boot_authenticator.h"
#include "boot_fastcall_tz.h"
#include "boot_sbl_shared.h"
#include "DALSys.h"
#include "busywait.h"
#include "boot_extern_smem_interface.h"
#include "boot_extern_platforminfo_interface.h"

#include <cil_loader.h>
#include "DALDeviceId.h"
/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define SHARED_FUNCTIONS_VERSION           8
#define SHARED_FUNCTIONS_MAGIC_COOKIE_1    0x8420C107
#define SHARED_FUNCTIONS_MAGIC_COOKIE_2    0x3B9A68DF


/* Single structure that houses all of the functions to be shared between
   XBLLoader and any other image running at the same time as XBLLoader.
   I.E. XBLDebug */

typedef struct
{
  uint64 version;
  uint32 magic_cookie_1;
  uint32 magic_cookie_2;


  CeMLErrorType(* boot_CeMLDeInit)(void);

  CeMLErrorType(* boot_CeMLHashDeInit)(CeMLCntxHandle **);

  CeMLErrorType(* boot_CeMLHashFinal)(CeMLCntxHandle *,
                                      CEMLIovecListType *); 

  CeMLErrorType(* boot_CeMLHashInit)(CeMLCntxHandle **,
                                     CeMLHashAlgoType);

  CeMLErrorType(* boot_CeMLHashSetParam)(CeMLCntxHandle *,
                                         CeMLHashParamType, 
                                         const void *, 
                                         uint32,
                                         CeMLHashAlgoType);

  CeMLErrorType(* boot_CeMLHashUpdate)(CeMLCntxHandle *,
                                       CEMLIovecListType);

  CeMLErrorType(* boot_CeMLInit)(void);

  PrngML_Result_Type(* boot_PrngML_getdata_lite)(uint8*  random_ptr, uint16  random_len); 

  void(* boot_sw_cipher_init)(void);
  
  void(* boot_sw_cipher_post_init)(void);

  void(* boot_encr_aes_key)(uint8 *in, uint32 inlen, uint8 *out, uint32 *outlen);
  
int (* boot_sw_cipher) (
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
);

  void(* boot_clobber_clear_whitelist_table)(void);

  boolean(* boot_clobber_check_global_whitelist_range)(const void *,
                                                       uintnt);

  void(* boot_dload_transition_pbl_forced_dload)(void);

  void(* boot_dload_set_cookie)(void);
  
  uint32(* boot_dload_read_saved_cookie)(void);

  boot_boolean(* boot_enable_led)(uint32, boot_boolean);

  void(* boot_err_fatal)(void);

  void(* boot_error_handler)(const char *,
                             uint32,
                             uint32);

  boot_flash_dev_if_type *(* boot_flash_dev_if_get_singleton)(void);

  sbl_if_shared_ddr_device_info_type *(* boot_get_ddr_info)(void);

  void(* boot_hw_reset)(boot_hw_reset_type);

  void(* boot_install_error_callback)(bl_error_callback_func_type,
                                      void *,
                                      bl_error_callback_node_type *);

  void (* boot_log_message)(char *);

  boot_boolean(* boot_pbl_is_auth_enabled)(void);

  secboot_hw_etype (* boot_is_auth_enabled)(boot_boolean * is_auth_enabled);

  void (* boot_auth_load_header)( mi_boot_image_header_type* image_header );

  void (* boot_update_auth_image_info)( uint8* hash_buffer_base_addr );

  bl_error_boot_type (* boot_auth_image)( struct bl_shared_data_type *bl_shared_data, uint32 image_type );

  pm_err_flag_type(* boot_pm_dev_get_power_on_reason)(unsigned,
                                                      uint64 *);
  
  pm_err_flag_type(* boot_pm_get_pon_reason_history_to_dump)(pm_pbs_pon_reason_history_data_type *); 
  
  boot_boolean(* boot_toggle_led)(void);

  void(* boot_toggle_led_init)(void);

  boot_boolean(* boot_qsee_is_memory_dump_allowed)(secboot_verified_info_type *);

  boot_boolean(* boot_qsee_is_retail_unlocked)(secboot_verified_info_type *);

  void(* boot_qsee_zero_peripheral_memory)(void);

  int32(* boot_sbl_qsee_interface_get_image_entry)(boot_sbl_qsee_interface * sbl_qsee_interface,
                                                    secboot_sw_type image_id);

  bl_shared_data_type * (* sbl1_get_shared_data)(void);

  void(* sbl_error_handler)(void);

  uint32(* sbl1_hw_get_reset_status)(void);

  void(* sbl1_load_ddr_training_data_from_partition)(uint8 *,
                                                     uint32);

  uint64 (*hotplug_get_partition_size_by_image_id)( image_type image_id );                                                     
  
  boolean(* dev_sdcc_write_bytes)(void *, uint64, uint32, image_type);
  
  boolean(* dev_sdcc_read_bytes)(void *, uint64, uint32, image_type);
  
  int16 (* get_hotplug_dev_handle)(image_type image_id);  
  
  void(* boot_set_pwrkey_reset_type)(boot_hw_reset_type);
  
  void (* boot_set_pshold_reset_type)(boot_hw_reset_type);
  
  /*API's used by USB driver */

  pm_err_flag_type(* pm_schg_usb_irq_status)(uint32, 
                                             pm_schg_usb_irq_type, 
                                             pm_irq_status_type, 
                                             boolean *);

  pm_err_flag_type(* pm_schg_usb_get_typec_status)(uint32 pmic_device, 
                                                   pm_schg_usb_typec_status_type *typec_status);

  boolean(* qusb_ldr_utils_fedl_check)(void);

  boolean(*Clock_SetBIMCSpeed)(uint32 );
  
  int (* boot_scm)( uintnt smc_id, uintnt param_id, uintnt r0, uintnt r1, uintnt r2,
                    uintnt r3, uintnt session_id, boot_tzt_result_regs_t* resp_buff_ptr);

  uint32 (* sbl1_get_current_el)( void );	
  
  DALResult (* DALSYS_Malloc)(uint32 dwSize, void **ppMem);

  DALResult (* DALSYS_Free)(void *pmem);
  
  DALResult (*DAL_DeviceAttach)(DALDEVICEID DeviceId,DalDeviceHandle **phDevice);
  
  DALResult
  (*DAL_DeviceAttachEx)(const char *pszArg, DALDEVICEID DeviceId,
               DALInterfaceVersion ClientVersion,DalDeviceHandle **phDevice);

  DALResult (*DAL_DeviceDetach)(DalDeviceHandle *hDevice);
  
  
  DALResult (*DALSYS_GetDALPropertyHandle)(DALDEVICEID DeviceId,DALSYSPropertyHandle hDALProps);

  DALResult (*DALSYS_GetDALPropertyHandleStr)(const char *pszDevName, DALSYSPropertyHandle hDALProps);

  DALResult (*DALSYS_GetPropertyValue)(DALSYSPropertyHandle hDALProps, const char *pszName,
                  uint32 dwId,
                   DALSYSPropertyVar *pDALPropVar);
                   
   VOID * (* DALSYS_memset)(VOID * buffer, UINT8 value, UINTN length);
   
   void (* DALSYS_LogEvent)(DALDEVICEID DeviceId, uint32 dwLogEventType, const char * pszFmt,
                ...);
                
   DALResult (*DALSYS_EventCreate) (uint32 dwAttribs, DALSYSEventHandle *phEvent,
               DALSYSEventObj *pEventObj);

   DALResult (*DALSYS_DestroyObject) (DALSYSObjHandle hObj);
   
   DALResult (*DALSYS_EventCtrlEx) (DALSYSEventHandle hEvent, uint32 dwCtrl, uint32 dwParam,
                   void *pPayload, uint32 dwPayloadSize);
                   
   DALResult (*DALSYS_SyncCreate)(uint32 dwAttribs,
                  DALSYSSyncHandle *phSync,
                  DALSYSSyncObj *pSyncObj);

   DALResult (*DALSYS_MemRegionAlloc) (uint32 dwAttribs, DALSYSMemAddr VirtualAddr,
               DALSYSMemAddr PhysicalAddr, uint32 dwLen, DALSYSMemHandle *phMem,DALSYSMemObj *pMemObj);
   
   DALResult (*DALSYS_MemInfo)(DALSYSMemHandle hMem, DALSYSMemInfo *pMemInfo);   
   
   DALResult (*DALSYS_EventMultipleWait) (DALSYSEventHandle* phEvent, int nEvents,
                         uint32 dwTimeoutUs,uint32 *pdwEventIdx);
                         
   void (*DALSYS_BusyWait) (uint32 pause_time_us);
  DALResult (*boot_DalPlatformInfo_PlatformInfo)(void *pPlatforminfo);

  DALResult (*boot_DalPlatformInfo_ChipId)(void *pChipSetId);

  DALResult (*boot_DalPlatformInfo_ChipFamily)(void *pChipsetfamily);
  void ( *busywait)(uint32 pause_time_us);
  
  DALResult ( *busywait_init)(void);
  
  boolean ( *boot_log_get_init_info)(uint8 **log_base_addr_ptr,
                                     uintnt *size_ptr);

  void * ( *boot_smem_get_addr)(smem_mem_type smem_type, uint32 *buf_size);
  
   boolean(*boot_check_display_vbatt)(void );
   
  pm_err_flag_type (*boot_pm_pon_wdog_enable)(uint8 pmic_device_index,pm_on_off_type enable);
  
} boot_shared_functions_type;

#endif /* BOOT_SHARED_FUNCTIONS */


