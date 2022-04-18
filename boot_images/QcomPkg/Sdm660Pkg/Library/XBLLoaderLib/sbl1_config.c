/**
 * @file sbl1_config.c
 * @brief
 * Source file for 8996 SBL1 bootloader configuration
 *
 * DEFINED VARIABLES:
 * sbl1_config_table   - Boot configuration entries for SBL1
 * load_qsee_pre_procs - SBL1 procedures run prior to QSEE loading
 *
 * Copyright (C) 2011-2017 by Qualcomm Technologies, Inc. All Rights Reserved.
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
        
when       who     what, where, why
--------   ---     ---------------------------------------------------------
02/28/17   sb      Add DDR heap to DAL for deviceprogrammer
10/18/16   ds      Load PMIC in dload mode
07/15/16   yps     Remove Sec lib
07/08/16   rp      Added DDI support
06/30/16   digant  Load APDP before QSEE devcfg
05/09/16   digant  STI image mmu mapping port and enablement
05/03/16   rp	   Remove sbl1_wait_for_ddr_training & sbl1_post_ddr_training_init,
				   needed only if training is done on RPM
03/27/16   kpa     Updates to always load core image from xbl segment     
12/15/15   plc     Make SMC call to TZ Milestone if in EL1, else direct call
11/16/15   plc     Make PIMEM NonCacheable for now
10/22/15   plc     Replaced tlb invalidate with generic EL-agnostic call
10/15/15   wg      Added Android LK (abl) loading logic to XBL
10/13/15   plc     Sync to 8996 tip
10/07/15   plc     Enable DDR calls and cache/mmu calls.  DDR calls will be 
                   made at top level, and at lower level skipped with run-
                   time check if we are running on Virtio instead of RUMI
09/22/15   wg      Unstubbed Populate Ram Partition Table
09/08/15   wg      Unstub smem
08/25/15   plc     Bring in relevant 8996 tip changes
08/07/15   plc     Stubbing smem, cache/mmu, ddr and more for presi virtio
07/01/15   as      Added seg_elf_entry_point for images
03/02/15   kpa     Updates to load TZ/Qsee Dev config image
02/18/15   kpa     Rename sbl1_hw_pmic_init to sbl1_hw_pre_ddr_init
02/12/15   ck      Removed boot_secure_watchdog_init call
01/27/15   kpa     Added boot_config_data_table_default_init
01/14/15   kedara  Update TZ region attributes.
11/24/14   wek     Change function name for device programmer.
10/29/14   kpa     Support 64 bit memory map
10/27/14   kedara  Added SAFE 1.0
10/14/14   kedara  Load Pmic Elf image
09/24/14   kedara  Updates to support loading xbl core segments
09/09/14   kedara  Include boot_page_table_armv8.h update qsee_jump_func
07/14/14   ck      Moved boot_ram_dumps_to_sd_card to XBLRamDump
07/14/14   ck      Moved boot_ram_dump_to_raw_partition to XBLRamDump
06/26/14   kedara  fix llvm compiler warnings.
05/11/14   kedara  Branch for 8996, fix compiler warnings.
04/15/14   ck      Moved boot_dload_check before loading of QSEE as debug info is in SBL
04/10/14   ck      Added call to APT library
03/24/14   ck      Utilizing new boot_sbl_qsee_interface_get_* functions
03/21/14   ck      Added support to load SEC partition
03/18/14   ck      Updated boot_hw_reset calls as they now take a reset type parameter
03/06/14   ck      Moved sbl1_populate_initial_mem_map to sbl1_main_ctl
03/05/14   ck      Enabling AUTH for loaded images
02/28/14   ck      Moved sbl1_hw_deinit as it MUST be after sbl1_boot_logger_deinit
02/26/14   ck      Added logic to mark QSEE page table has Executable right before jumping
02/12/14   ck      Added AARCH64_ENABLE fuse check
02/10/14   ck      sbl1_tlmm_init needs to be after SMEM initialization
02/05/14   ck      Added 64 bit logic to qsee_jump_func
01/28/14   kpa     Update dload check, smem api locations
01/09/14   ck      Added logic to qsee_jump_func to store QSEE entry point and elf type
01/08/14   ck      Added boot_secure_watchdog_init call
12/18/13   ck      Removed call to boot_dload_dump_tz
12/16/13   ck      Removed sbl1_qfprom_test as TZ runs after SBL in Bear family.
12/09/13   ck      Removed call to sbl1_update_sbl1_rollback_fuse and
                   sbl1_update_all_rollback_fuses as this is done in QSEE for Bear family
12/06/13   ck      Replaced boot_pbl_is_auth_enabled call with boot_is_auth_enabled
10/24/13   ck      Bear boot flow is very linear now, everything initializes
                   before the first image is loaded.
10/17/13   ck      Removed unused functions.  Memory map change.
08/13/13   aus     Pass the TZ secboot verified info structure to TZ image
08/08/13   jz      Fixed the issue in WDT load when the partition doesn't exist
07/29/13   aus     Support for loading ELF SDI image
06/26/13   aus     Remove sbl1_dead_battery_charge
05/08/13   yp      Call boot_pm_vib_off to stop vibrate for 8X26 and 8x10.
04/02/13   dh      Use boot_dload_is_dload_mode_set instead of uefi dump cookie
                   to determin if device is in dload mode
03/11/13   kedara  boot config entry to control xpu configurations per image.
03/05/13   dh      Use mmu_l1_pagetable_base in sbl_shared_data as a common
                   pointer to page table base
02/28/13   kedara  call boot_set_tz_execute_status to indicate tz ready.
02/27/13   dh      Don't lower krait frequency prior to ddr training 
                   if we are in uefi dump mode 
                   Remove sbl1_relocate_page_table from dload path.
                   it will be called in sbl1_post_ddr_init if dload mode is set
02/27/13   dh      Call sbl1_hw_platform_pre_ddr before rpm is loaded to share 
                   platform id to rpm, call sbl1_hw_platform_smem to store 
                   platform info to smem
02/20/13   dh      Move all qfprom api after rpm xpu sync
02/15/13   dh      Add boot_dload_dump_tz in pre tz functions
02/14/13   kedara  Added sbl1_update_all_rollback_fuses in load_appsbl_post_procs
02/12/13   dh      Call boot_clock_set_L2_perf_level and boot_clock_set_cpu_perf_level
                   to Put krait to SVS mode before rpm is released
02/07/13   dh      Move SDI loading after RPM, delay page table relocation until DDR training
01/24/13   jz      Updated memory region names
01/24/13   dh      Pass secboot_shared_data to SDI as we pass it to TZ
12/12/12   jz      Do not load SDI when in dload mode
12/03/12   dh      Remove sbl1_rollback_version_update
11/27/12   dh      Add sbl1_rpm_sync in load_appsbl_post_procs
11/28/12   dh      Add a field in config table for Roll back protection feature
                   Blow sbl1 version roll back protection fuse as soon as tz is initialized
11/16/12   dh      Check for L2 cache parity error in appsbl_jump_func, if error
                   exists set dload cookie and reset
                   Move sbl1_boot_logger_deinit inside appsbl_jump_func
           Move boot_shared_imem_init before sbl1_hw_init in sbl1_main_ctl
10/23/12   dh      Map RPM code ram and data ram as shared device to prevent XPU violation
                   before signal rpm fw to go
10/17/12   jz      Turn on TZ elf image support
10/08/12   jz      Turn on RPM elf image support
09/26/12   dh      Move sbl1_hw_init_secondary after sbl1_post_ddr_data_init
           since pmic api in hw_init_secondary uses DDR heap
09/19/12   dh      Only load debug image if its image header is valid, this will support
                   optional debug image flashing
08/20/12   kedara  Added flag to support loading elf in chunks (ssa)
08/01/12   dh      Add sbl1_hw_deinit
07/23/12   dh      Add sbl1_wait_for_ddr_training 
07/19/12   dh      Add sbl1_qfprom_test
07/16/12   dh      Move sbl1_hw_init to sbl1_main_ctl
06/14/12   kedara  Initialize whitelist config table entry to NULL
05/29/12   dh      Move sbl1_hw_init_secondary right after ddr init
                   Add sbl1_tlmm_init after boot_smem_init
05/24/12   dh      combine sbl1_ddr_data_init and sbl1_relocate_page_table into
                   sbl1_post_ddr_data_init
05/24/12   dh      Delay rpm jump to after smem init since rpm uses smem
05/08/12   dh      Add sbl1_dead_battery_charge
04/18/12   dh      passing appsbl entry address in tz milestone call as tz will
                   jump to appsbl.Mark TZ as non-executable and read only after
                   we executed it
03/22/12   dh      Load the wdog debug image(WDT) after tz
03/14/12   dh      relocate page table to ddr once ddr is up
02/03/12   dh      Skip tz execution for pre silicon build
12/01/11   dh      Add sbl1_rollback_version_update and sbl1_signal_tz_sbl_done.
11/30/11   dh      Add sbl1_ddr_data_init
10/31/11   dh      Add dload function list
10/18/11   dh      Initial Creation 

============================================================================
                     Copyright 2014-2015 Qualcomm Technologies Incorporated.
                            All Rights Reserved.
                    Qualcomm Confidential and Proprietary
===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/
#include "boot_mc.h"
#include "boot_config.h"
#include "boot_flash_target.h"
#include "boot_flash_dev_if.h"
#include "boot_authenticator.h"
#include "boot_config_data.h"
#include "boot_dload.h"
#include "boot_loader.h"
#include "boot_ram_init.h"
#include "boot_logger.h"
#include "boot_page_table_armv8.h"
#include "boot_cache_mmu.h"
#include "boot_smem.h"
#include "boot_ram_partition.h"
#include "sbl1_hw.h"
#include "sbl1_mc.h"
#include "boot_dload.h"
#include "boothw_target.h"
#include "boot_rollback_version.h"
#include "boot_extern_clk_interface.h"
#include "boot_extern_ddr_interface.h"
#include "boot_shared_imem_cookie.h"
#include "boot_extern_pmic_interface.h"
#include "boot_extern_deviceprogrammer_interface.h"
#include "boot_extern_apt_interface.h"
#include "boot_extern_vsense_interface.h"
#include "boot_elf_header.h"
#include "sys_debug.h"
#include "boot_hash_buffer.h"
#include "boot_util.h"
#include "LoaderAptLib.h"
#include "boot_dload_dump.h"
#include "boot_fastcall_tz.h"
#include "boot_extern_ddi_interface.h"


/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define QSEE_BOOT_LOG_STR (uint8 *)"QSEE Image Loaded, Delta"
#define QHEE_BOOT_LOG_STR (uint8 *)"QHEE Image Loaded, Delta"
#define RPM_BOOT_LOG_STR (uint8 *)"RPM Image Loaded, Delta"
#define APPSBL_BOOT_LOG_STR (uint8 *)"APPSBL Image Loaded, Delta"
#define PMIC_BOOT_LOG_STR (uint8 *)"PMIC Image Loaded, Delta"
#define QSEE_DEVCFG_BOOT_LOG_STR (uint8 *)"QSEE Dev Config Image Loaded, Delta"
#define APDP_BOOT_LOG_STR (uint8 *)"APDP Image Loaded, Delta"
#define STI_BOOT_LOG_STR (uint8 *)"STI Image Loaded, Delta"
#define ABL_BOOT_LOG_STR (uint8 *)"ABL Image Loaded, Delta"

#define BOOT_XBL_CORE_COOKIE1 (((uint64)'b' << 0) | \
                               ((uint64)'o' << 8) | \
                               ((uint64)'o' << 16) | \
                               ((uint64)'t' << 24) | \
                               ((uint64)' ' << 32) | \
                               ((uint64)'t' << 40) | \
                               ((uint64)'o' << 48) | \
                               ((uint64)' ' << 56) )

#define BOOT_XBL_CORE_COOKIE2 (((uint64)'x' << 0) | \
                               ((uint64)'b' << 8) | \
                               ((uint64)'l' << 16) | \
                               ((uint64)' ' << 24) | \
                               ((uint64)'c' << 32) | \
                               ((uint64)'o' << 40) | \
                               ((uint64)'r' << 48) | \
                               ((uint64)'e' << 56) )

typedef struct
{
  uint64 cookie1;
  uint64 cookie2;
} xbl_core_cookie;
/*==========================================================================
                      DEFINE PARTITION IDs
===========================================================================*/
extern uint8 qsee_partition_id[];
extern uint8 qhee_partition_id[];
extern uint8 rpm_partition_id[];
extern uint8 appsbl_partition_id[];
extern uint8 sbl1_partition_id[];
extern uint8 pmic_partition_id[];
extern uint8 qsee_devcfg_image_partition_id[];
extern uint8 apdp_partition_id[];
extern uint8 sti_partition_id[];
extern uint8 abl_partition_id[];

boot_configuration_table_entry sbl1_config_table[];

/* TODO: _FIX_ for 8996. TZ cannot access shared data in L2 TCM since it disables mmu.
  If mmu disabling in TZ is postponed beyond shared data copy, a branch 'bl' instrn
  seemed to have issues. Hence temporarily 
*/
struct boot_sbl_qsee_interface sbl_qsee_interface_ddr SECTION(".bss.BOOT_DDR_ZI_DATA_ZONE");
uint32 appsbl_index = 0;

/* SYSTEM_DEBUG_QSEE_INFO is memory specified in the scatter file for SBL
   and system debug to share information about where QSEE was loaded and
   if it's a 32 bit or 64 bit image. */
extern uintnt Image$$SYSTEM_DEBUG_QSEE_INFO$$Base;

/*==========================================================================
                      DEFINE WHITELIST TABLES
===========================================================================*/
static whitelist_region_type xbl_core_table[] = {XBL_CORE_WHITELIST_REGION_TABLE};

/*==========================================================================
                     PRE/POST PROCEDURE DEFINITIONS 
===========================================================================*/
/* Restore hash segment buffer to DDR. Reclaim Memory used for PMIC elf loading */ 
static void sbl1_restore_hash_segment_buffer(bl_shared_data_type *bl_shared_data )
{
  boot_restore_hash_segment_buffer(bl_shared_data);
  boot_clobber_remove_global_protection_region ((void *)HASH_SEGMENT_TEMP_BASE, 
                                                HASH_SEGMENT_SIZE);
  #if defined( FEATURE_DDI_IMAGE  )
  boot_clobber_remove_global_protection_region ((void *)SCL_PMIC_CONFIG_BUF_BASE_DDI,
                                               SCL_PMIC_CONFIG_BUF_SIZE);

  #else

  boot_clobber_remove_global_protection_region ((void *)SCL_PMIC_CONFIG_BUF_BASE,
                                               SCL_PMIC_CONFIG_BUF_SIZE);

  #endif
 
}

/* Wrapper function to hand control to deviceprogrammer or DDI image */ 
static void sbl1_hand_control_to_devprog_ddr_or_ddi(bl_shared_data_type *bl_shared_data)
{
#if defined (FEATURE_DEVICEPROGRAMMER_IMAGE)

  boot_boolean result = FALSE;
  struct mem_block devprg_mem_block;
  
  /* Update attributes for non-cacheable regions */
  devprg_mem_block.p_base = SCL_SBL1_OCIMEM_DATA_BASE;
  devprg_mem_block.v_base = SCL_SBL1_OCIMEM_DATA_BASE;
  devprg_mem_block.size_in_kbytes = SCL_SBL1_OCIMEM_DATA_SIZE >> 10;
  devprg_mem_block.memory_mapping = MMU_L3_SECTION_MAPPING;
  devprg_mem_block.access = MMU_PAGETABLE_MEM_READ_WRITE;
  devprg_mem_block.cachetype = MMU_PAGETABLE_MEM_NON_CACHEABLE;
  devprg_mem_block.executable = MMU_PAGETABLE_NON_EXECUTABLE_REGION;

  result =
    boot_mmu_page_table_map_single_mem_block((uint64*)mmu_get_page_table_base(),
                                             &devprg_mem_block);
  BL_VERIFY(result, BL_ERR_MMU_PGTBL_MAPPING_FAIL|BL_ERROR_GROUP_BOOT);

  devprg_mem_block.p_base = SCL_SBL1_PAGE_TABLE_BASE;
  devprg_mem_block.v_base = SCL_SBL1_PAGE_TABLE_BASE;
  devprg_mem_block.size_in_kbytes = SCL_SBL1_PAGE_TABLE_SIZE >> 10;

  result =
    boot_mmu_page_table_map_single_mem_block((uint64*)mmu_get_page_table_base(),
                                             &devprg_mem_block);
  BL_VERIFY(result, BL_ERR_MMU_PGTBL_MAPPING_FAIL|BL_ERROR_GROUP_BOOT);

  mmu_invalidate_tlb();

  /* Add the DDR heap to DAL */
  sbl1_ddr_heap_init();
  boot_hand_control_to_deviceprogrammer_ddr_main(bl_shared_data);
  
#elif defined (FEATURE_DDI_IMAGE)

  boot_hand_control_to_DDR_Debug_Image_main(bl_shared_data);
#endif /* FEATURE_DDI_IMAGE */
}


/*==========================================================================
                  FUNCTIONS TO EXECUTE BEFORE PMIC LOADING
===========================================================================*/
boot_procedure_func_type load_pmic_pre_procs[] = 
{
  /* Save reset register logs */
  boot_save_reset_register_log,
  
  /* Initialize the flash device */
  boot_flash_init,
  
  /*-----------------------------------------------------------------------
   Initialize the default CDT before reading CDT from flash
  -----------------------------------------------------------------------*/
  boot_config_data_table_default_init,
    
  /*-----------------------------------------------------------------------
   API called twice, this first time passes default compiled CDT contents
   to DDR driver, in case CDT only contains Platform CDB.  Second call
   will update DDR driver with Flashed CDT DDR CDB contents, if DDR CDB 
   was found in flashed CDT
  -----------------------------------------------------------------------*/
  sbl1_ddr_set_default_params,
  
  /* Copy the configure data table from flash */
  boot_config_data_table_init,
  
  /* Store platform id */
  sbl1_hw_platform_pre_ddr,
  
  /* Temporarily use the hash segment in RPM code RAM */
  boot_move_hash_segment_buffer,
  
  /* Initialize the sec img auth library with pbl shared data */
//plc  boot_sec_img_auth_init,

  /*----------------------------------------------------------------------
   Last entry in the table.
  ----------------------------------------------------------------------*/
  NULL 
};

/*==========================================================================
                  FUNCTIONS TO EXECUTE AFTER PMIC LOADING
===========================================================================*/
boot_procedure_func_type load_pmic_post_procs[] = 
{  
  /* Use the hash segment originally allocated in DDR */
  sbl1_restore_hash_segment_buffer,

  /* Last entry in the table */ 
  NULL 
};


/*==========================================================================
                  FUNCTIONS TO EXECUTE BEFORE APDP LOADING
===========================================================================*/
boot_procedure_func_type load_apdp_image_pre_procs[] = 
{
  /* Initialize PMIC and railway driver */
  sbl1_hw_pre_ddr_init,

  /* Configure ddr parameters based on eeprom CDT table data. */
  sbl1_ddr_set_params,
  
  /* Initialize DDR */
  (boot_procedure_func_type)sbl1_ddr_init,

  /*----------------------------------------------------------------------
   Run deviceprogrammer if compiling the deviceprogrammer_ddr image.
   In XBL builds the function below is stubbed out (does nothing)
  ----------------------------------------------------------------------*/
  sbl1_hand_control_to_devprog_ddr_or_ddi,
  
#ifndef FEATURE_DEVICEPROGRAMMER_IMAGE
  
  /* Initialize SBL1 DDR ZI region, relocate boot log to DDR */   
  sbl1_post_ddr_init,
  
  sbl1_hw_init_secondary, 
  
  #endif /*FEATURE_DEVICEPROGRAMMER_IMAGE*/

  /* Last entry in the table. */
  NULL 
};

/*==========================================================================
   FUNCTIONS TO EXECUTE AFTER APDP LOADING
===========================================================================*/
boot_procedure_func_type load_apdp_image_post_procs[] = 
{
 #ifndef FEATURE_DEVICEPROGRAMMER_IMAGE

/* Backup QSEE and QHEE region for ramdumps */  
  boot_dload_dump_security_regions,

  /* Check to see if DLOAD mode needs to be entered */
  boot_dload_check,
  
  /* Set the memory barrier pointer to shared memory */
  boot_cache_set_memory_barrier,

  /*----------------------------------------------------------------------
   Put SMEM in debug state such that smem_alloc() calls will return NULL. 
   The state is changed back to normal once smem_boot_init() is called.
   This call has to be made after setting the memory barrier.
  ----------------------------------------------------------------------*/
  boot_smem_debug_init,  
    
  /* Initialize shared memory after dload to preserve logs */
  boot_smem_init,
  
  /* Allocate memory for minidump table */
  boot_smem_alloc_for_minidump,  
  
 #ifndef FEATURE_RUMI_BOOT
  /* Stub out for rumi build. pmic api  pm_get_power_on_status gets 
     called from below api to get power on reason */ 
  /*----------------------------------------------------------------------
   Store Power on Status in SMEM. 
   Needs to be done after PMIC and SMEM initialization
  ----------------------------------------------------------------------*/
  boot_smem_store_pon_status,
 #endif
 
  /*----------------------------------------------------------------------
   Store the platform id to smem
  ----------------------------------------------------------------------*/
  sbl1_hw_platform_smem,

  boot_clock_init_rpm,

  boot_vsense_copy_to_smem,

  /*----------------------------------------------------------------------
   Get shared data out of the flash device module
  ----------------------------------------------------------------------*/
  boot_share_flash_data,
  
  /*----------------------------------------------------------------------
   populate the ram partition table
  ----------------------------------------------------------------------*/
  boot_populate_ram_partition_table,

  /*----------------------------------------------------------------------
   Initialize GPIO for low power configuration
  ----------------------------------------------------------------------*/
  sbl1_tlmm_init,
  
  /*-----------------------------------------------------------------------
   Calls efs cookie handling api to perform efs backup/restore
  -----------------------------------------------------------------------*/  
  sbl1_efs_handle_cookies,
    
  /*-----------------------------------------------------------------------
   APT Security Test
   ----------------------------------------------------------------------*/
  (boot_procedure_func_type)boot_apt_test,

#endif /* FEATURE_DEVICEPROGRAMMER_IMAGE */

  /* Last entry in the table. */
  NULL 
};

/*==========================================================================
   FUNCTIONS TO EXECUTE AFTER QSEE DEV CONFIG LOADING
===========================================================================*/
boot_procedure_func_type load_qsee_devcfg_image_post_procs[] = 
{

#ifndef FEATURE_DEVICEPROGRAMMER_IMAGE

  /* Load SEC partition if it exists.  This must be done after QSEE is
     loaded as the partition is loaded into a QSEE buffer. */
  sbl1_load_sec_partition,

#endif
 /* Last entry in the table. */
  NULL 
};

/*==========================================================================
   FUNCTIONS TO EXECUTE AFTER QSEE  LOADING
===========================================================================*/
boot_procedure_func_type load_qsee_image_post_procs[] = 
{

#ifndef FEATURE_DEVICEPROGRAMMER_IMAGE

  /* play power on vibration */
  sbl1_hw_play_vibr,

#endif
 /* Last entry in the table. */
  NULL 
};

/*==========================================================================
        List of SBL1 procedures to execute prior to dload entry
===========================================================================*/
boot_procedure_func_type sbl1_pre_dload_procs[] =
{
  /*-----------------------------------------------------------------------
   * Initialization functions for dload. This has to be the first function 
   * called before Dload entry
   *----------------------------------------------------------------------*/
  boot_init_for_dload,
  
  /*-----------------------------------------------------------------------
   * Setup clocks for ram dump
   *----------------------------------------------------------------------*/
  sbl1_hw_dload_init,
  
  /*-----------------------------------------------------------------------
   * NULL pointer indicates the end of the list
   *-----------------------------------------------------------------------*/
  NULL
};


/*==========================================================================
        List of SBL1 procedures to execute after APPSBL is loaded
===========================================================================*/
boot_procedure_func_type sbl1_post_appsbl_procs[] =
{
  /*-----------------------------------------------------------------------
   * Determine APPSBL architecture and update SBL - QSEE interface
   *----------------------------------------------------------------------*/
  sbl1_appsbl_arch_determination,
  
  /*-----------------------------------------------------------------------
   * NULL pointer indicates the end of the list
   *-----------------------------------------------------------------------*/
  NULL
};


/*==========================================================================
                     CONFIG FUNCTION DEFINITIONS 
===========================================================================*/

/* Executing QSEE from SBL1 */ 
static void qsee_jump_func(bl_shared_data_type *bl_shared_data )
{
  boot_boolean result = FALSE;
  boot_boolean         is_auth_enabled = FALSE;
  struct mem_block qsee_mem_block;
  sys_debug_qsee_info_type * qsee_info =
    (sys_debug_qsee_info_type *)&Image$$SYSTEM_DEBUG_QSEE_INFO$$Base;


  qsee_info->entry_point = (uint64)NULL;
  qsee_info->elf_class = (uint32)NULL;

  /* Flush the cache before entering QSEE */
  dcache_flush_region((void *)SCL_QSEE_CODE_BASE, SCL_QSEE_TOTAL_SIZE);
  dcache_flush_region((void *)SCL_pIMEM_BASE, SCL_pIMEM_MINIMUM_SIZE);

  boot_pm_vib_off();
  
  /* De-Initialize the boot logger */
  sbl1_boot_logger_deinit();
  
  boot_is_auth_enabled(&is_auth_enabled);
  if((TRUE == is_auth_enabled) && (L2_parity_error_in_sbl))
  {
    boot_hw_reset(BOOT_HARD_RESET_TYPE);
  }
  else if(L2_parity_error_in_sbl)
  {
    boot_dload_set_cookie();
    boot_hw_reset(BOOT_WARM_RESET_TYPE);
  }  


  /* Search image entries in QSEE interface for QSEE and get entry point.
     The entry point and elf type of QSEE must be stored so if an abnormal
     reset occurs the system debug image knows how to get to QSEE.  A small
     section has been carved out in the system debug image memory for this
     data. 
  */
  qsee_info->entry_point =
    boot_sbl_qsee_interface_get_entry_point(&(bl_shared_data->sbl_qsee_interface),
                                            SECBOOT_QSEE_SW_TYPE);
  qsee_info->elf_class =
    boot_sbl_qsee_interface_get_eident(&(bl_shared_data->sbl_qsee_interface),
                                       SECBOOT_QSEE_SW_TYPE);

  /* Verify entry point is not null */
  BL_VERIFY(qsee_info->entry_point != (uint64)NULL,
            BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);
  
  /* Verify QSEE ELF class is valid */
  BL_VERIFY((qsee_info->elf_class == ELF_CLASS_64) ||
            (qsee_info->elf_class == ELF_CLASS_32),
            BL_ERR_ELF_CLASS_INVALID|BL_ERROR_GROUP_BOOT);


  /* Mark QSEE page table as executable */
  qsee_mem_block.p_base = SCL_QSEE_CODE_BASE;
  qsee_mem_block.v_base = SCL_QSEE_CODE_BASE;
  qsee_mem_block.size_in_kbytes = SCL_QSEE_TOTAL_SIZE >> 10;
  qsee_mem_block.memory_mapping = MMU_L3_SECTION_MAPPING;
  qsee_mem_block.access = MMU_PAGETABLE_MEM_READ_WRITE;
  qsee_mem_block.cachetype = MMU_PAGETABLE_DEVICE_SHARED;
  qsee_mem_block.executable = MMU_PAGETABLE_EXECUTABLE_REGION;

  result =
    boot_mmu_page_table_map_single_mem_block((uint64 *)(uintnt)bl_shared_data->sbl_shared_data->mmu_l1_pagetable_base,
                                             &qsee_mem_block);
  BL_VERIFY(result, BL_ERR_MMU_PGTBL_MAPPING_FAIL|BL_ERROR_GROUP_BOOT);

  qsee_mem_block.p_base = SCL_pIMEM_BASE;
  qsee_mem_block.v_base = SCL_pIMEM_BASE;
  qsee_mem_block.size_in_kbytes = SCL_pIMEM_SIZE >> 10;
  qsee_mem_block.memory_mapping = MMU_L2_SECTION_MAPPING;
  qsee_mem_block.access = MMU_PAGETABLE_MEM_READ_WRITE;
  qsee_mem_block.cachetype = MMU_PAGETABLE_MEM_NON_CACHEABLE;
  qsee_mem_block.executable = MMU_PAGETABLE_EXECUTABLE_REGION;

  result =
    boot_mmu_page_table_map_single_mem_block((uint64 *)(uintnt)bl_shared_data->sbl_shared_data->mmu_l1_pagetable_base,
                                             &qsee_mem_block);
  BL_VERIFY(result, BL_ERR_MMU_PGTBL_MAPPING_FAIL|BL_ERROR_GROUP_BOOT);

  mmu_invalidate_tlb();

  /* Store the index of appsbl image entry in sbl qsee interface for TZ to fetch
    the appsbl entry point. Needed as image ID can no longer be used to identify
    appsbl image.
  */
  (bl_shared_data->sbl_qsee_interface).appsbl_entry_index = 
                      sbl1_config_table[appsbl_index].sbl_qsee_interface_index ;
                      
  qmemcpy(&sbl_qsee_interface_ddr, &(bl_shared_data->sbl_qsee_interface),
            sizeof(boot_sbl_qsee_interface));
   
  dcache_flush_region((void *)&sbl_qsee_interface_ddr, sizeof(boot_sbl_qsee_interface));            
   
  /* Deinit hardware.  This must be done AFTER sbl1_boot_logger_deinit() 
    This is also used to turn off VMEM memory clocks. So ensure the api code/buffers
    are not in memory if it is being used.
  */  
  sbl1_hw_deinit();
  
 /* clearing the continuous boot failure count which is stored in IMEM */
  if (boot_shared_imem_cookie_ptr != NULL)
  {
	boot_shared_imem_cookie_ptr->boot_fail_count = 0;
  }
  
  /* "Exit" bootloader and enter QSEE context.
    */
    
  boot_fastcall_tz_no_rsp(TZ_SBL_END_MILESTONE,
                          TZ_SBL_END_MILESTONE_PARAM_ID,
                          (uint32)(&sbl_qsee_interface_ddr),
                          (uint32)(sizeof(sbl_qsee_interface_ddr)),
                          0,0);
  /*Must not reach here*/
  while(1);
}


/* Executing STI from SBL1 */ 
static void sti_jump_func(bl_shared_data_type *bl_shared_data )
{
  boot_boolean result = FALSE;
  struct mem_block sti_mem_block;

  sys_debug_qsee_info_type * sti_info =
    (sys_debug_qsee_info_type *)&Image$$SYSTEM_DEBUG_QSEE_INFO$$Base;

  /*  STI is apt's test image to verify loader. If STI image is loaded
    it is the final image that loader jumps to instead of QSEE image.
    The image is like of extention of xbl loader so the deinit api's
    need not be called.
  */  

  sti_info->entry_point = (uint64)NULL;
  sti_info->elf_class = (uint32)NULL;

  /* De-Initialize the boot logger */
  sbl1_boot_logger_deinit();
  
  if(L2_parity_error_in_sbl)
  {
    boot_dload_set_cookie();
    boot_hw_reset(BOOT_WARM_RESET_TYPE);
  }  


  /* Search image entries in QSEE interface for STI and get entry point.
  */
  sti_info->entry_point =
    boot_sbl_qsee_interface_get_entry_point(&(bl_shared_data->sbl_qsee_interface),
                                            SECBOOT_STI_SW_TYPE);
  sti_info->elf_class =
    boot_sbl_qsee_interface_get_eident(&(bl_shared_data->sbl_qsee_interface),
                                       SECBOOT_STI_SW_TYPE);

  /* Verify entry point is not null */
  BL_VERIFY(sti_info->entry_point != (uint64)NULL,
            BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);
  
  /* Verify STI ELF class is valid */
  BL_VERIFY((sti_info->elf_class == ELF_CLASS_64) ||
            (sti_info->elf_class == ELF_CLASS_32),
            BL_ERR_ELF_CLASS_INVALID|BL_ERROR_GROUP_BOOT);

  /* Flush the cache before entering STI */
  dcache_flush_region((void *)SCL_XBL_CORE_CODE_BASE, SCL_XBL_CORE_TOTAL_SIZE);
  dcache_flush_region((void *)sti_info, sizeof(sys_debug_qsee_info_type));

   /* Mark STI page table as executable */
	sti_mem_block.p_base = SCL_LOADERTEST_CODE_BASE;
	sti_mem_block.v_base = SCL_LOADERTEST_CODE_BASE;
	sti_mem_block.size_in_kbytes = SCL_LOADERTEST_CODE_SIZE >> 10;
	sti_mem_block.memory_mapping = MMU_L2_SECTION_MAPPING;
	sti_mem_block.access = MMU_PAGETABLE_MEM_READ_WRITE;
	sti_mem_block.cachetype = MMU_PAGETABLE_DEVICE_SHARED;
	sti_mem_block.executable = MMU_PAGETABLE_EXECUTABLE_REGION;

  result =
    boot_mmu_page_table_map_single_mem_block((uint64 *)(uintnt)bl_shared_data->sbl_shared_data->mmu_l1_pagetable_base,
                                             &sti_mem_block);
  BL_VERIFY(result, BL_ERR_MMU_PGTBL_MAPPING_FAIL|BL_ERROR_GROUP_BOOT);

  mmu_invalidate_tlb();

  boot_log_message("STI Image Entry");

  /* "Exit" bootloader and enter STI context.
     Note: This function should not return.
  */
  apt_sti_init(sti_info->entry_point);
  
/*Must not reach here*/
 while(1);
}


/* Conditionally cancel RPM loading in SBL1 */
static boot_boolean rpm_load_cancel(bl_shared_data_type *bl_shared_data)
{
  boot_boolean is_auth_enabled = FALSE;

  boot_is_auth_enabled(&is_auth_enabled);

  /* Do not load RPM if we are in DLOAD mode and auth is disabled. 
   * This is to preserve RPM code ram for the memory debug tools */
  return (boot_boolean)(boot_dload_is_dload_mode_set() == TRUE && 
                        is_auth_enabled == FALSE);
}

/* Conditionally cancel APPSBL loading in SBL1 */
static boot_boolean appsbl_load_cancel(bl_shared_data_type *bl_shared_data)
{
  boot_boolean cancel = FALSE;
  uint32 index = 0;
 
 /*
   Note:
   appsbl_load_cancel behaves a bit different than other load_cancel api's.
   The api modifies parameters to switch to loading XBL Core segments
   using XBL elf info passed by bootrom.  
 */
  
  do
  {
    /* Iterate over config table to find APPSBL entry */
    while(sbl1_config_table[index].host_img_id != (uintnt)NULL)
    {
       if(sbl1_config_table[index].target_img_sec_type 
          == SECBOOT_APPSBL_SW_TYPE)
       {
         break;
       }
       index++;
    }
    
    /* Verify Appsbl entry is found */
    BL_VERIFY(sbl1_config_table[index].host_img_id != (uint64)NULL,
            BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);

    /* Store the index for future use */
    appsbl_index = index;  
  
    /*Update APPSBL entry to enable loading XBL core segments*/
    sbl1_config_table[index].target_img_type = CONFIG_IMG_ELF_SEG;
    sbl1_config_table[index].whitelist_table = xbl_core_table;
    sbl1_config_table[index].target_img_sec_type = SECBOOT_SBL_SW_TYPE;
    boot_elf_ziinit_structures(NULL);
    boot_set_elf_and_prog_header(
        bl_shared_data->sbl_shared_data->pbl_shared_data->elf_meta_info.elf_hdr,
        bl_shared_data->sbl_shared_data->pbl_shared_data->elf_meta_info.prog_hdr
      );
    boot_set_hash_segment_buffer(
        (void *)bl_shared_data->sbl_shared_data->pbl_shared_data->elf_meta_info.hash_seg_hdr
    );

    /* Configure the target image using custom partition ID information */ 
    boot_flash_configure_target_image(sbl1_partition_id);
  
  }while(0);
  
  return cancel;
}

/* Conditionally cancel ABL loading in XBL */
static boot_boolean abl_load_cancel(bl_shared_data_type *bl_shared_data)
{  
  boot_flash_trans_if_type *trans_if;    
  boot_boolean cancel = TRUE;
  uint32 index = 0;
  mi_boot_image_header_type abl_header;
  
  do
  {
    /* Iterate over config table to find ABL entry */
    while(sbl1_config_table[index].host_img_id!= (uintnt)NULL)
    {
       if(sbl1_config_table[index].target_img_sec_type 
          == SECBOOT_ABL_SW_TYPE)
       {
         break;
       }
       index++;
    }

    /* Do not load ABL if image not found in the config table */
    if(sbl1_config_table[index].host_img_id == (uintnt)NULL)
    {
       break;
    }

    /* Load only if ABL partition exists */
    boot_flash_configure_target_image(abl_partition_id);
    trans_if = boot_flash_dev_open_image(GEN_IMG);
    if(trans_if == NULL )
    {
       break;
    }
    boot_flash_dev_close_image( &trans_if );

	/* Validate the ELF header and load the image only if the header is valid */
	if (!boot_elf_verify_image_header(abl_partition_id, &abl_header))
	{
		/* Partition is not flashed */
		break;
	}      
    
    /* All conditions are satisfied, load ABL image */
    cancel = FALSE;
  } while(0);

  return cancel;
}

/* Conditionally cancel PMIC loading in SBL1 */
static boot_boolean pmic_load_cancel(bl_shared_data_type *bl_shared_data)
{
  /* Cancel loading for Device Programmer or if XBL loader is in dload mode */
  return (boot_boolean)((bl_shared_data->build_type == SBL_BUILD_DEVICEPROGRAMMER_DDR) ||
                        (bl_shared_data->build_type == SBL_BUILD_DDRDEBUGIMAGE));
}


/* Conditionally cancel APDP loading in SBL1 */
static boot_boolean apdp_load_cancel(bl_shared_data_type *bl_shared_data)
{  
  boot_flash_trans_if_type *trans_if;    
  boot_boolean cancel = TRUE;
  uint32 index = 0;
  mi_boot_image_header_type apdp_header;
  
  do
  {
    /* Iterate over config table to find APDP entry */
    while(sbl1_config_table[index].host_img_id!= (uintnt)NULL)
    {
       if(sbl1_config_table[index].target_img_sec_type 
          == SECBOOT_APDP_SW_TYPE)
       {
         break;
       }
       index++;
    }

    /* Do not load APDP if image not found in the config table */
    if(sbl1_config_table[index].host_img_id == (uintnt)NULL)
    {
       break;
    }

    /* Load only if APDP partition exists */
    boot_flash_configure_target_image(apdp_partition_id);
    trans_if = boot_flash_dev_open_image(GEN_IMG);
    if(trans_if == NULL )
    {
       break;
    }
    boot_flash_dev_close_image( &trans_if );

    /* Validate the ELF header and load the APDP image only if the 
      header is valid 
    */
    if (!boot_elf_verify_image_header(apdp_partition_id, &apdp_header))
    {
      /* Partition is not flashed */
      break;
    }
    
    /* All conditions are satisfied, load APDP image */
    cancel = FALSE;
  } while(0);

  return cancel;
}

/* Conditionally cancel Qsee enumeration/ Dev config image loading in SBL1 */
static boot_boolean qsee_devcfg_image_load_cancel(bl_shared_data_type *bl_shared_data)
{
  boot_flash_trans_if_type *trans_if; 
  boot_boolean cancel = TRUE;

  do
  {
    /* Load only if Qsee enumeration/ dev config image partition exists */
    boot_flash_configure_target_image(qsee_devcfg_image_partition_id);
    trans_if = boot_flash_dev_open_image(GEN_IMG);

    if(trans_if != NULL )
    {
      boot_flash_dev_close_image( &trans_if );
      cancel = FALSE;
      break;
    }
  }while(0);
  
  return cancel;
}

/* Conditionally cancel STI loading in SBL1 */
static boot_boolean sti_load_cancel(bl_shared_data_type *bl_shared_data)
{
  boot_flash_trans_if_type *trans_if; 
  mi_boot_image_header_type sti_header;  
  boot_boolean cancel = TRUE;
  boot_boolean is_auth_enabled = TRUE;
  secboot_hw_etype status = E_SECBOOT_HW_FAILURE;
   
 /*
   Note:
   STI (APT's loader test image) to be loaded only if partition is present,
   image is flashed, authentication not enabled and debug disable fuses
   not blown   
 */
  
  do
  {
    /* Load only if STI partition exists */
    boot_flash_configure_target_image(sti_partition_id);
    trans_if = boot_flash_dev_open_image(GEN_IMG);
    if(trans_if == NULL )
    {
       break;
    }
    boot_flash_dev_close_image( &trans_if );

    /* Validate the ELF header and load the STI image only if the 
      header is valid 
    */
    if (!boot_elf_verify_image_header(sti_partition_id, &sti_header))
    {
      /* Partition is not flashed */
      break;
    }
    
    /* Do not load STI image if authentication is enabled or
      debug disable fuses are blown.
    */
    if(DEBUG_DISABLED_APPS)
    {
      break;
    }

    status = boot_is_auth_enabled(&is_auth_enabled);
    BL_VERIFY((status == E_SECBOOT_HW_SUCCESS), (uint16)status|BL_ERROR_GROUP_SECURITY); 

    if(is_auth_enabled == TRUE)
    {
      break;
    }
    
    /* All conditions are satisfied, load STI image */
    cancel = FALSE;
  
  }while(0);
  
  return cancel;
}


/*==========================================================================
                      DEFINE TARGET BOOT CONFIG TABLE
===========================================================================*/
boot_configuration_table_entry sbl1_config_table[] = 
{

  /* SBL1 -> PMIC */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_PMIC_SW_TYPE,       /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    FALSE,                      /* jump */
    NULL,                       /* exec_func */
    NULL,                       /* jump_func */
    load_pmic_pre_procs,        /* pre_procs */ 
    load_pmic_post_procs,       /* post_procs */
    pmic_load_cancel,           /* load_cancel */
    pmic_partition_id,          /* target_img_partition_id */
    (uint8*)PMIC_BOOT_LOG_STR,  /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled */
    TRUE,                       /* enable_rollback_protection*/
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/    
    0x0,                        /* sbl_qsee_interface_index */
    0x0                         /* seg_elf_entry_point*/
  },

  /* SBL1 -> APDP */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_APDP_SW_TYPE,       /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    FALSE,                      /* jump */
    NULL,                       /* exec_func */
    NULL,                       /* jump_func */
    load_apdp_image_pre_procs,    /* pre_procs */ 
    load_apdp_image_post_procs,   /* post_procs */
    apdp_load_cancel,           /* load_cancel */
    apdp_partition_id,          /* target_img_partition_id */
    APDP_BOOT_LOG_STR,          /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled */
    TRUE,                       /* enable_rollback_protection*/
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/    
    0x0,                        /* sbl_qsee_interface_index */
    0x0                         /* seg_elf_entry_point*/
  },

  /* SBL1 -> Qsee Dev config image  */
  {
    SBL1_IMG,                            /* host_img_id */
    CONFIG_IMG_QC,                       /* host_img_type */
    GEN_IMG,                             /* target_img_id */
    CONFIG_IMG_ELF,                      /* target_img_type */
    SECBOOT_QSEE_DEVCFG_SW_TYPE,         /* target_img_sec_type */ 
    TRUE,                                /* load */
    TRUE,                                /* auth */
    FALSE,                               /* exec */
    FALSE,                               /* jump */
    NULL,                                /* exec_func */
    NULL,                                /* jump_func */
    NULL,                                /* pre_procs */ 
    load_qsee_devcfg_image_post_procs,   /* post_procs */
    qsee_devcfg_image_load_cancel,       /* load_cancel */
    qsee_devcfg_image_partition_id,      /* target_img_partition_id */
    QSEE_DEVCFG_BOOT_LOG_STR,            /* target_img_str */
    NULL,                                /* whitelist table */
    FALSE,                               /* boot_ssa_enabled */
    FALSE,                               /* enable_rollback_protection*/
    FALSE,                               /* enable_xpu */
    0x0,                                 /* xpu_proc_id*/    
    0x0,                                 /* sbl_qsee_interface_index */
    0x0                                  /* seg_elf_entry_point*/
  },  
  
 /* SBL1 -> QSEE */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_QSEE_SW_TYPE,       /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    FALSE,                      /* jump */
    NULL,                       /* exec_func */
    NULL,                       /* jump_func */
    NULL,                       /* pre_procs */ 
    load_qsee_image_post_procs, /* post_procs */
    NULL,                       /* load_cancel */
    qsee_partition_id,          /* target_img_partition_id */
    QSEE_BOOT_LOG_STR,          /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled */
    TRUE,                       /* enable_rollback_protection*/
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/    
    0x0,                        /* sbl_qsee_interface_index */
    0x0                         /* seg_elf_entry_point*/
  },


  /* SBL1 -> QHEE */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_QHEE_SW_TYPE,       /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    FALSE,                      /* jump */
    NULL,                       /* exec_func */
    NULL,                       /* jump_func */
    NULL,                       /* pre_procs */ 
    NULL,                       /* post_procs */
    NULL,                       /* load_cancel */
    qhee_partition_id,          /* target_img_partition_id */
    QHEE_BOOT_LOG_STR,          /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled */
    TRUE,                       /* enable_rollback_protection*/
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/    
    0x0,                        /* sbl_qsee_interface_index */
    0x0                         /* seg_elf_entry_point*/
  },


  /* SBL1 -> RPM */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_RPM_FW_SW_TYPE,     /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    FALSE,                      /* jump */
    NULL,                       /* exec_func */
    NULL,                       /* jump_func */
    NULL,                       /* pre_procs */ 
    NULL,                       /* post_procs */
    rpm_load_cancel,            /* load_cancel */
    rpm_partition_id,           /* target_img_partition_id */
    RPM_BOOT_LOG_STR,           /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled  */
    TRUE,                       /* enable_rollback_protection */
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/
    0x0,                        /* sbl_qsee_interface_index */
    0x0                         /* seg_elf_entry_point*/
  },

  
  /* SBL1 -> STI */
  {
    SBL1_IMG,                     /* host_img_id */
    CONFIG_IMG_QC,                /* host_img_type */
    GEN_IMG,                      /* target_img_id */
    CONFIG_IMG_ELF,               /* target_img_type */
    SECBOOT_STI_SW_TYPE,          /* target_img_sec_type */ 
    TRUE,                         /* load */
    TRUE,                         /* auth */
    FALSE,                        /* exec */
    TRUE,                         /* jump */
    NULL,                         /* exec_func */
    sti_jump_func,                /* jump_func */
    NULL,                         /* pre_procs */ 
    NULL,                         /* post_procs */
    sti_load_cancel,              /* load_cancel */
    sti_partition_id,             /* target_img_partition_id */
    STI_BOOT_LOG_STR,             /* target_img_str */
    NULL,                         /* whitelist table */
    FALSE,                        /* boot_ssa_enabled  */
    TRUE,                         /* enable_rollback_protection */
    FALSE,                        /* enable_xpu */
    0x0,                          /* xpu_proc_id*/   
    0x0,                          /* sbl_qsee_interface_index */
    0x0                           /* seg_elf_entry_point*/
  },


  /* SBL1 -> ABL */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_ABL_SW_TYPE,        /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    FALSE,                       /* jump */
    NULL,                       /* exec_func */
    NULL,                       /* jump_func */
    NULL,                       /* pre_procs */ 
    NULL,                       /* post_procs */
    abl_load_cancel,            /* load_cancel */
    abl_partition_id,           /* target_img_partition_id */
    ABL_BOOT_LOG_STR,           /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled  */
    TRUE,                       /* enable_rollback_protection */
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/   
    0x0,                        /* sbl_qsee_interface_index */
    SCL_XBL_CORE_CODE_BASE      /* seg_elf_entry_point*/
  },  


  /* SBL1 -> APPSBL */
  {
    SBL1_IMG,                   /* host_img_id */
    CONFIG_IMG_QC,              /* host_img_type */
    GEN_IMG,                    /* target_img_id */
    CONFIG_IMG_ELF,             /* target_img_type */
    SECBOOT_APPSBL_SW_TYPE,     /* target_img_sec_type */ 
    TRUE,                       /* load */
    TRUE,                       /* auth */
    FALSE,                      /* exec */
    TRUE,                       /* jump */
    NULL,                       /* exec_func */
    qsee_jump_func,             /* jump_func */
    NULL,                       /* pre_procs */ 
    sbl1_post_appsbl_procs,     /* post_procs */
    appsbl_load_cancel,         /* load_cancel */
    appsbl_partition_id,        /* target_img_partition_id */
    APPSBL_BOOT_LOG_STR,        /* target_img_str */
    NULL,                       /* whitelist table */
    FALSE,                      /* boot_ssa_enabled  */
    TRUE,                       /* enable_rollback_protection */
    FALSE,                      /* enable_xpu */
    0x0,                        /* xpu_proc_id*/   
    0x0,                        /* sbl_qsee_interface_index */
    SCL_XBL_CORE_CODE_BASE      /* seg_elf_entry_point*/
  },


  /* LAST ENTRY */
  {
    NONE_IMG,
  }

};
