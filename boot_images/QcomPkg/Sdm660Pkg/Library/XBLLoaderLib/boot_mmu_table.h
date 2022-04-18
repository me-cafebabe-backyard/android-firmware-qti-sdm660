#ifndef BOOT_MMU_TABLE_H
#define BOOT_MMU_TABLE_H

/*=============================================================================

                      MSM8996 SBL MMU Table

GENERAL DESCRIPTION
    This module contains the memory map for MSM8996 SBL.

Copyright 2013, 2014, 2016 by Qualcomm Technologies, Inc. All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
09/23/16   digant  L3 mapping for first 2MB from 0x00000000, remove redirect region to get more L3 pages
08/26/16   digant  0x114000000 -- 0x114100000 mark read only
08/15/16   digant  remove OCIMEM mapping to avoid mapping tz regions
08/15/16   digant  Optimal cache settings for A53
06/20/16   rp	   Added DTTS sections in initial_memory_map to have mmu attributes as device shared
06/02/16   rp	   Remove SCL_DDR_TRAINING_DATA_BUF_SIZE from L2TCM DATA MMU mappings
03/26/16   kpa     Update Qsee regions mmu attributes to be device shared.
03/23/16   kpa     Configure mmu DEP attributes for ddr driver segment
11/17/15   plc     Mark RAMDUMP region as non-cacheable fo rnow
10/13/15   plc     Update cache regions to be similar to 8996 tip
10/07/15   plc     Update order of RPM_CODE_RAM entries
09/08/15   kpa     Change cacheable regions to be inner-outer wbwara
07/28/15   rp      Mark the page table section in OCIMEM to be non cacheable
07/26/15   kpa     remove pimem mapping from sbl_initial_memory_map
07/01/15   rq      Added lower ddr memory map
02/03/15   wek     Make MMU Attributes static, reverts change on 02/03/15.
02/12/15   kpa     Mark RPM code ram XBL rom buffer as readonly.
02/06/15   kpa     Mark OCIMEM XBL data buffer as uncached for UFS buffers
02/04/15   kpa     Mark DDR mem block MMU_PAGETABLE_DEVICE_SHARED
02/03/15   wek     Change MMU Attributes at runtime for DeviceProgrammer.
01/22/15   kpa     Update XBL data size in L2 TCM.
01/14/15   kpa     Mark L2 TCM region inner/outer WB-RWA.
12/09/14   kpa     Add mmu config for pIMEM vault region
11/20/14   ck      Temporarily mark RamDump region in additional memory map
09/09/14   kedara  Temporarily mark Qsee region exec from start.
                   Map SCL_DDR_pIMEM_BASE. 
08/25/14   kedara  Update memory map. 
08/08/14   ck      Renamed/resized page table entry for SCL_DLOAD_BUFFERS_BASE
06/12/14   kedara  Initial version for 8996. 
04/23/14   ck      Mark the Security Control Block region as read only
04/09/14   ck      Updated initial and additional memory map with proper granularity
03/18/14   ck      Made SBL L2/TCM cacheable for speed increase and setup DEP
02/27/14   ck      Removing RPM Data RAM as A53 does not have visibility
02/25/14   ck      Changed sbl1_ddr_mem_block to Inner cacheable / Outer non-cacheable
02/22/14   dhaval  defined sys_debug code, data regions
02/10/14   ck      Updated QHEE and APPSBL page table entry to match QSEE and NON_EXECUTABLE
02/06/14   ck      Updated SDI region names
01/30/14   kpa     Mark DDR driver region executable
01/13/14   ck      Changed QSEE DDR region to be covered by a L1 page table and
                   be Inner cacheable / Outer non-cacheable to resolve transition issue.
10/17/13   ck      Modified initial memory to only include IMEM and DDR.
                   Everything else is mapped after DDR initialization.
09/09/13   ck      Initial revision for 8916

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "boot_cache_mmu.h"
#include "boot_page_table_armv8.h"

/*=============================================================================
Memory Map Structure
  PBL only maps a limited number of memories: 
  OCIMEM, RPM CODE RAM, RPM DATA RAM,  APPS PBL ROM, L2, L3 TCM locked region.
  
  With Aarch64 Page Tables, we will need to take care of all required regions.
  
  SBL (XBLLoader) is responsible to map the memory it will use such as DDR 
  and ram dump regions.  

  Memory regions greater than or equal to 1GB are placed in the Level 1 pagetables. 
  Memory regions greater than or equal to 2MB are placed in the Level 2 pagetables.
  The rest regions less than 2MB (4KB)are placed in Level 3 pagetables. 
  All regions are marked with the default domain.
=============================================================================*/



/*=============================================================================
    SBL initial Memory Map  
    This memory map is populated before DDR is intialized.
    Regions that have XPU protection turned on should be marked as 
    DEVICE memory(strongly ordered) to eliminate the processor doing 
    speculative data access and NON-EXECUTABLE to eliminate 
    speculative instruction execution.
=============================================================================*/

/* Note:
     On HoneyBadger family there are no free L2, L3 page table entries in the 
     memory map region shared by PBL.
     PBL already populates 5 L3 pagetables (4KB each) in the available 20KB 
     L3 page table space. Similarly L2 page table address space has 512 entries
     mapping whole 1 GB address space.
     bootrom only maps 1GB in L1 page table. For DDR we need to populate remaining
     L1 entries.

     Data Execution Prevention(DEP) for SBL RW region:
     All SBL region except code should be marked as non executable

     Data Execution Prevention(DEP) for SBL CODE region:
     All SBL code region should be marked as read only and exec 
     DEP already taken care of via sbl_initial_memory_map[]
*/


static struct mem_block sbl_initial_memory_map[] =
{
 /* SBL1 Code and Vectors.  Reusable L3. */
  { SCL_SBL1_CODE_BASE,
    SCL_SBL1_CODE_BASE,
    SCL_SBL1_CODE_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_ONLY,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_EXECUTABLE_REGION, },

  /* SBL1 Stack and Data (RW + ZI), Training data buffer. Reusable L3 */
  { SCL_SBL1_STACK_BASE,
    SCL_SBL1_STACK_BASE,
    (SCL_SBL1_STACK_SIZE + SCL_SBL1_DATA_SIZE + SCL_SBL1_DATA_ZI_SIZE) >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /* SBL1 Page Table and Shared Functions Table, noncached */
  { SCL_SBL1_PAGE_TABLE_BASE,
    SCL_SBL1_PAGE_TABLE_BASE, 
    (SCL_SBL1_PAGE_TABLE_SIZE + SCL_SBL1_SHARED_FUNCTIONS_TABLE_SIZE) >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },    

  /* System debug image(SDI) segment lies in OCIMEM (16KB)
     code section must be marked as executable.
  */
  { 
    SCL_SYSTEM_DEBUG_CO_RO_BASE,
    SCL_SYSTEM_DEBUG_CO_RO_BASE, 
    SCL_SYSTEM_DEBUG_CO_RO_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_ONLY,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_EXECUTABLE_REGION, },  
  { 
    SCL_SYSTEM_DEBUG_DATA_BASE,
    SCL_SYSTEM_DEBUG_DATA_BASE, 
    SCL_SYSTEM_DEBUG_DATA_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  { 
    SCL_SBL1_OCIMEM_DATA_BASE,
    SCL_SBL1_OCIMEM_DATA_BASE, 
    SCL_SBL1_OCIMEM_DATA_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  { 
    SHARED_IMEM_BASE,
    SHARED_IMEM_BASE, 
    SHARED_IMEM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },
    
  /* DDR region, must be marked as shared device initially. New L1 mapping */
  { DDR_MEM_BASE,
    DDR_MEM_BASE, 
    DDR_MEM_SIZE >> 10,
    MMU_L1_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_DEVICE_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },
     
  /* DDR region, must be marked as shared device initially. New L1 mapping */  
  { 
	DDR_MEM_LOWER_BASE,	  
	DDR_MEM_LOWER_BASE,	  
	DDR_MEM_LOWER_SIZE >> 10,    
	MMU_L1_SECTION_MAPPING,	  
	MMU_PAGETABLE_MEM_READ_WRITE, 	
	MMU_PAGETABLE_DEVICE_SHARED,	
	MMU_PAGETABLE_NON_EXECUTABLE_REGION, },
   
  /*RPM Data RAM, Cacheable, Non-Executable */  
  { SCL_RPM_DATA_RAM_BASE,
    SCL_RPM_DATA_RAM_BASE, 
    SCL_RPM_DATA_RAM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /*DDR Driver code segment , Cacheable, Executable */  
  { SCL_SBL1_DDR_DSF_ROM_BASE,
    SCL_SBL1_DDR_DSF_ROM_BASE,
    SCL_SBL1_DDR_DSF_ROM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_ONLY,
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_EXECUTABLE_REGION, },

  /*DDR Driver data segment , Cacheable, Non-Executable */      
  { SCL_SBL1_DDR_DSF_DATA_BASE,
    SCL_SBL1_DDR_DSF_DATA_BASE, 
    SCL_SBL1_DDR_DSF_DATA_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, }, 

  /*DTTS_SRAM section , L3 shared device, Non-Executable */  
  { SCL_DDR0_DTTS_SRAM_BASE,
    SCL_DDR0_DTTS_SRAM_BASE, 
    SCL_DDR_DTTS_SRAM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_DEVICE_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },
	
  /*DTTS_SRAM section , L3 shared device, Non-Executable */    
  { SCL_DDR1_DTTS_SRAM_BASE,
    SCL_DDR1_DTTS_SRAM_BASE, 
    SCL_DDR_DTTS_SRAM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_DEVICE_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },	
	
	{ SCL_UNUSED_ADDRESS_BASE,
    SCL_UNUSED_ADDRESS_BASE, 
    SCL_UNUSED_ADDRESS_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_ONLY, 
    MMU_PAGETABLE_DEVICE_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },
  /* Last Region Marker */
  { MMU_LAST_ADDRESS, MMU_LAST_ADDRESS }

};


/*=============================================================================
    SBL1 Addtional Memory Map  
    
    Addtional memory regions that need to be mapped in SBL1. 
    This memory map is populated after DDR is intialized.
    Regions that have XPU protection turned on should be marked as 
    DEVICE memory(strongly ordered) to eliminate the processor doing 
    speculative data access and NON-EXECUTABLE to eliminate 
    speculative instruction execution.
=============================================================================*/
const struct mem_block sbl1_addtional_memory_map[] =
{ 
  /*SBL1 DDR ZI, L2 cacheable */  
  { SCL_SBL1_DDR_DATA_BASE,
    SCL_SBL1_DDR_DATA_BASE, 
    SCL_SBL1_DDR_DATA_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /*SBL1 DDR Page table, non-cacheable 
    Page table region must be mapped as non-cachable to be consistent with 
    the setting in TTBR0(we set page table walk as non-cachable)*/  
  { SCL_SBL1_DDR_PAGE_TABLE_BASE,
    SCL_SBL1_DDR_PAGE_TABLE_BASE, 
    SCL_SBL1_DDR_PAGE_TABLE_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION,  },   
    
  /*SBL1 DDR Uncached ZI, 4KB , non-cacheable*/  
  { SCL_SBL1_DDR_UNCACHED_ZI_BASE,
    SCL_SBL1_DDR_UNCACHED_ZI_BASE, 
    SCL_SBL1_DDR_UNCACHED_ZI_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /* SMEM Region, 2MB , Shared memory */ 
  { SCL_SHARED_RAM_BASE,
    SCL_SHARED_RAM_BASE, 
    SCL_SHARED_RAM_SIZE >> 10,
    MMU_L2_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_MEM_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /*QSEE pImem Region,L2 cacheable, Non-Executable,
    marked as Executable before jumping to it. */  
  { SCL_DDR_pIMEM_BASE,
    SCL_DDR_pIMEM_BASE, 
    SCL_DDR_pIMEM_SIZE >> 10,
    MMU_L2_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_DEVICE_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },    
    
  /*QHEE, cacheable, Non-Executable */  
  { SCL_QHEE_CODE_BASE,
    SCL_QHEE_CODE_BASE, 
    SCL_QHEE_TOTAL_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /*RPM Code RAM, Cacheable, Non-Executable */  
  { SCL_RPM_CODE_RAM_BASE,
    SCL_RPM_CODE_RAM_BASE, 
    SCL_RPM_CODE_RAM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /*APPSBL, cacheable, Executable */  
  { SCL_APPSBL_CODE_BASE,
    SCL_APPSBL_CODE_BASE, 
    SCL_APPSBL_TOTAL_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /* XBLRamDump region cacheable, non-exec */  
  { SCL_RAMDUMP_CODE_BASE,
    SCL_RAMDUMP_CODE_BASE, 
    SCL_RAMDUMP_TOTAL_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE, 
    MMU_PAGETABLE_INNER_WBWARA_OUTER_NONCACHE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /* Security control region as read-only */
  { SECURITY_CONTROL_BASE,
    SECURITY_CONTROL_BASE, 
    QFPROM_READONLY_BLOCK_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_ONLY, 
    MMU_PAGETABLE_DEVICE_SHARED,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  /* Add addtional memory region here */
  
  /* Last Region Marker */
  { MMU_LAST_ADDRESS, MMU_LAST_ADDRESS }
};


/*=============================================================================
    DDI Memory Map  
    
    Addtional memory regions that need to be mapped in DDI. 
    This memory map is populated before DDR is intialized.
=============================================================================*/
#ifdef FEATURE_DDI_IMAGE
const struct mem_block sbl1_ddi_memory_map[] =
{
  { SCL_L2_TCM_DDI_ZI_BASE_ADDR,
    SCL_L2_TCM_DDI_ZI_BASE_ADDR,
    SCL_L2_TCM_DDI_ZI_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE,
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },

  { SCL_L2_TCM_DDI_BASE_ADDR,
    SCL_L2_TCM_DDI_BASE_ADDR,
    SCL_L2_TCM_DDI_TCM_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_ONLY,
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_EXECUTABLE_REGION, },
    
  { SCL_VMEM_DDI_DATA_BASE,
    SCL_VMEM_DDI_DATA_BASE,
    SCL_VMEM_DDI_DATA_SIZE >> 10,
    MMU_L3_SECTION_MAPPING,
    MMU_PAGETABLE_MEM_READ_WRITE,
    MMU_PAGETABLE_MEM_NON_CACHEABLE,
    MMU_PAGETABLE_NON_EXECUTABLE_REGION, },
    
  /* Last Region Marker */
  { MMU_LAST_ADDRESS, MMU_LAST_ADDRESS }
};
#endif

  /*TODO: _FIX_ for 8996: reconfirm this MMU setting */
/* MMU Pagetable Region  
   Page table region must be mapped as non-cachable to be consistent with 
   the setting in TTBR0(we set page table walk as non-cachable)
*/
struct mem_block sbl1_mmu_page_table_mem_block = 
{ 
  /* Pagetable 64KB + 32b */
  0, 0, 0,
  MMU_L3_NS_SECTION_MAPPING, MMU_PAGETABLE_MEM_READ_WRITE, 
  MMU_PAGETABLE_MEM_NON_CACHEABLE, MMU_PAGETABLE_NON_EXECUTABLE_REGION  
};

/* Memory block to describe DDR memory */
struct mem_block sbl1_ddr_mem_block = 
{
  0, 0, 0,
  MMU_L1_SECTION_MAPPING, MMU_PAGETABLE_MEM_READ_WRITE, 
  MMU_PAGETABLE_DEVICE_SHARED, MMU_PAGETABLE_NON_EXECUTABLE_REGION
};

#endif  /* BOOT_MMU_TABLE_H */
