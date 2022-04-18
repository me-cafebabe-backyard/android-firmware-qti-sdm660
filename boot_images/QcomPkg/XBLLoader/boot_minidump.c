/*===========================================================================

                              Minidump table parser

GENERAL DESCRIPTION
  This module scans the SMEM location to read address/size pair and populates 
  them it to memory dump table  

Copyright 2017 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================
                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        -------------------------------------------------------
02/02/17   bd      Call smem_init for minidump case
01/17/17   bd      Initial version

=============================================================================*/


/*==========================================================================

                   INCLUDE FILES

===========================================================================*/
#include "boot_minidump.h"
#include "boot_dload_debug.h"
#include "boot_shared_imem_cookie.h"
#include "boot_error_if.h"
#include "boot_shared_functions.h"
#include "smem.h"
#include "smem_type.h"
#include "LoaderUtils.h"
#include "boot_logger.h"
#include "boot_ddr_info.h"

#define MD_MAX_SIZE_VALUE (1024 * 1024 * 1024)


static boot_minindump_smem_area  *md_smem_base = NULL;
static uint64 ddr_end_addr = 0;

/*=============================================================================

        LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/*===========================================================================

FUNCTION add_one_region_to_dump

DESCRIPTION
  This function adds a region  dump table 

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
static void add_one_region_to_dump(boot_minidump_smem_region *r)
{
  char dump_region_name[DLOAD_DEBUG_STRLEN_BYTES] = "md_";
  char dump_region_bin_name[DLOAD_DEBUG_STRLEN_BYTES] = "md_";

  strlcat(dump_region_name, r->region_name, MD_REGION_NAME_LENGTH);
  strlcat(dump_region_bin_name, r->region_name, MD_REGION_NAME_LENGTH);
  strlcat(dump_region_bin_name, ".BIN", sizeof(dump_region_bin_name));
  
  dload_debug_add_region(OPTIONAL_DEF_SAVE,
          (r->region_base_address), (r->region_size),
          dump_region_name, dump_region_bin_name);
}

/*===========================================================================

FUNCTION md_get_smem_base_address

DESCRIPTION
  This function initializes the smem base address for minidump region 

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
static void md_get_smem_base_address(void)
{
  uint32 md_smem_size = MD_TOTAL_SMEM_SIZE;

  smem_init();
  md_smem_base = (boot_minindump_smem_area  *)smem_get_addr( SBL_MINIDUMP_SMEM_ID, &md_smem_size);
}

/*===========================================================================

FUNCTION md_is_valid_smem_entry

DESCRIPTION
  This function does boundary checks for address and size 

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
static boolean md_is_valid_smem_entry(uint64 base, uint64 size)
{
  char smem_error_check[100];
  
  /* Include L2 TCM, to be able to dump encryption keys, if required */
  if((base > SCL_L2_TCM_BASE_ADDR) && (base < ddr_end_addr)
    && (size != 0x0) && ((base+size) < ddr_end_addr))
  {
    return TRUE;
  }

  if(base != 0x0)
  {
    qsnprintf (smem_error_check, 100, "Minidump : Invalid entry : base=0x%lx size=0x%lx", base, size);
    boot_log_message(smem_error_check);  
  }
 
  return FALSE;
}  

/*===========================================================================

FUNCTION add_minidump_regions

DESCRIPTION
  This function adds all minidump regions into dump table

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void add_minidump_regions(void)
{

#if defined (QCOM_XBL_MINIDUMP)  

  uint32 index = 0;
  uint32 md_smem_size = MD_TOTAL_SMEM_SIZE;
  boot_minidump_smem_region  *region_info = NULL;
  sbl_if_shared_ddr_device_info_type *available_ddr;
  
  md_get_smem_base_address();
  
  if( NULL == md_smem_base )
  {
    boot_log_message("smem_get_addr returned NULL; No Minidump regions to be added");
    return ;
  }

  available_ddr = boot_get_ddr_info();
  ddr_end_addr = available_ddr->ddr_info[0].cs_addr;

  while(index < available_ddr->noofddr)
  {
    ddr_end_addr += available_ddr->ddr_info[index].ramsize << CONVERT_TO_MB_SHIFT;    
    index++;
  } 
   
  region_info = &(md_smem_base->region_info[0]);
  while( ((uintnt)md_smem_base + md_smem_size) > ((uintnt)region_info ))
  {
    if(md_is_valid_smem_entry(region_info->region_base_address, region_info->region_size))
      add_one_region_to_dump(region_info);
    
    region_info++;
  }  

#endif
}
