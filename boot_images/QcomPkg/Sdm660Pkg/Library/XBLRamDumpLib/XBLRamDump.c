/** @file XBLRamDump.c
  Top-Level Logic for XBLRamDump.c
  
  Copyright (c) 2014-2017, Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/11/17   bd      PMIC WDG support in DLOAD mode for minidump case
 04/04/17   bd      Disable display in DLOAD mode
 03/08/17   sj      Added the logic to enable display if battery threshold match
 02/17/17   din     Updated DDR dload cookie
 10/14/16   digant  set kpd pwr and pshold to hardreset
 10/12/16   digant  boot_set_pwrkey_to_hardreset
 08/08/16   digant  disable display support to fix tip/crm
 05/19/16   kpa     Added support for Display
 09/10/15   kpa     Use dcache_flush_region instead of mmu_flush_cache.
 08/24/15   ck      Added logic to enter PBL EDL if ramdump is not allowed
 09/30/14   ck      efs_boot_initialize must be called before any storage functions
 08/08/14   ck      Added boot_shared_functions_consumer.h
 07/28/14   ck      Initial revision

=============================================================================*/

#include "boot_target.h"
#include "boothw_target.h"
#include "boot_dload_debug.h"
#include "boot_raw_partition_ramdump.h"
#include "boot_sd_ramdump.h"
#include "boot_sahara.h"
#include "boot_extern_efs_interface.h"
#include "boot_shared_functions_consumer.h"
#include "BootDisplay.h"
#include "pm_fg_batt_info.h"

/*===========================================================================
**  Function :  XBLRamDumpDisplayInfo
** ==========================================================================
*/
/*!
* 
* @brief
*   This function displays messages onto screen
*
* @param[in] 
*   None
*
* @par Dependencies
*   None 
* 
* @retval
*   None
* 
*/ 
static void XBLRamDumpDisplayInfo(void)
{
  uint8 *boot_log_base_ptr = NULL;
  uintnt boot_log_init_info_size = 0 ;
  boolean status = FALSE;
  DALResult result;

  uint8* scaled_buffer = NULL;  

  boot_display_init();

  /* Example use of display scaling api*/
  
  /*Allocate buffer for image scaling */
  result = DALSYS_Malloc(GLYPH_BUFF_3X_SIZE_BYTES, (void *)&scaled_buffer);  
  BL_VERIFY(result == DAL_SUCCESS, BL_ERROR_GROUP_DAL|result);
  
  boot_display_set_font_color(COLOR_BLUE);  
  boot_display_scaled_message((uint8 *)"\n\n\rQUALCOMM ", 
                            SCALE_3X, scaled_buffer, GLYPH_BUFF_3X_SIZE_BYTES);

  boot_display_set_scale_factor(SCALE_3X);
  boot_display_set_font_color(COLOR_RED);  
  boot_display_message((uint8 *)"CrashDump Mode\n\r");
  
  boot_display_set_font_color(COLOR_YELLOW);  
  boot_display_message((uint8 *)"__________________________\n\n\r");
                                 
  boot_display_set_font_color(COLOR_WHITE);  
  status = boot_log_get_init_info(&boot_log_base_ptr, &boot_log_init_info_size);
  if (status == TRUE)
  {
    boot_display_buffer(boot_log_base_ptr, boot_log_init_info_size, 
                        SCALE_2X, scaled_buffer, GLYPH_BUFF_2X_SIZE_BYTES);
  }

  /* Free Allocated buffers */
  result = DALSYS_Free((void *)scaled_buffer);  
  BL_VERIFY(result == DAL_SUCCESS, BL_ERROR_GROUP_DAL|result); 
}

/*===========================================================================
**  Function :  XBLRamDumpMain
** ==========================================================================
*/
/*!
* 
* @brief
*   This function is entry point for XBL Ramdump image
*
* @param[in] 
*   None
*
* @par Dependencies
*   None 
* 
* @retval
*   None
* 
*/ 
VOID XBLRamDumpMain( VOID )
{
  struct boot_sahara_interface* sbl_sahara_interface = NULL;
  int *p = (int *)(0x146BF650);

  /* Update the ddr_dload cookie */
  *p = (*p & 0xFFFF0000) | 0xDEE1 ;


  /* Inform the shared functions library where the shared functions table is
     and verify that it was initialized by the producer. */
  boot_shared_functions_init();

  /* configure power key to do a hardreset */
  boot_set_pwrkey_reset_type(BOOT_HARD_RESET_TYPE);
  
  /*configure pshold to hardreset */
  boot_set_pshold_reset_type(BOOT_HARD_RESET_TYPE);
  
  /* Display RAM dump info on screen */
  
  /*
  Display framebuffer uses memory from APPS space and during DLOAD mode, any APPS data present, will get zeroed out.
  To avoid this , Kernel & Ramdump should use the framebuffer from same address.
  Until these changes are available disable the Display functionality in Ramdump mode.
  if (boot_check_display_allowed())
  {
  	XBLRamDumpDisplayInfo();
  } */

  /* boot_efs_boot_initialize must be called before any storage functionality.
     Even if it was called in XBLLoader it is safe to call it again here. */
  boot_efs_boot_initialize();


  /* If download mode is not available then no need to continue and spin.
     Enter PBL EDL in this scenario. */
  if(!dload_mem_debug_supported())
  { 
    boot_log_message("dload_mem_debug_supported returned error");
    boot_dload_transition_pbl_forced_dload();
  }


 /*-----------------------------------------------------------------------
   * Ram dump to eMMC raw partition, this function will reset device 
   * after successful dump collection if cookie is set 
   *----------------------------------------------------------------------*/
  boot_ram_dump_to_raw_parition();
  
  
#ifdef FEATURE_BOOT_RAMDUMPS_TO_SD_CARD   
  /*----------------------------------------------------------------------
   * Take the Ramdumps to SD card if  cookie file is
   *   present in SD card 
   *---------------------------------------------------------------------*/
  boot_ram_dumps_to_sd_card();
#endif /*FEATURE_BOOT_RAMDUMPS_TO_SD_CARD*/  


  /* Disable PMIC for QPST case, since QPST attache is manual and may result in WDOG expiry */
  boot_pm_pon_wdog_enable(PMIC_DEVICE_INDEX, PM_OFF);  
  /* Enter Sahara */

  /* Get Sahara interface */
  sbl_sahara_interface = sbl_sahara_get_interface();
  BL_VERIFY(sbl_sahara_interface != NULL, BL_ERROR_GROUP_BOOT|BL_ERR_NULL_PTR_PASSED);
  
  /* Set Sahara mode to memory debug */
  sbl_sahara_interface->sahara_mode = SAHARA_MODE_MEMORY_DEBUG;
  
  /* Flush the cache before calling into sahara so that all data is flushed to memory */  
  dcache_flush_region((void *)SCL_SBL1_DDR_ZI_BASE, SCL_SBL1_DDR_ZI_SIZE);
  dcache_flush_region((void *)SCL_SBL1_OCIMEM_DATA_BASE, SCL_SBL1_OCIMEM_DATA_SIZE);
  
  /* Enter Sahara */
  boot_sahara_entry(sbl_sahara_interface);
  
  boot_display_deinit();
}

