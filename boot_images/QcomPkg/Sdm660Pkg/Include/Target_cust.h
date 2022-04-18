#ifndef _TARGET_CUST_H
#define _TARGET_CUST_H

/*===========================================================================

                                Target_cust
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2014 - 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ----------------------------------------------------------
05/05/17   bd           XBL Loader code area increase for crypto lib
03/01/17   kpa          Added SCL_SBL1_VECTOR_TABLE_SIZE
01/26/17   bd           Set RAW_PARTITION_BUF_ADDR to reserved area
12/07/16   sj			Added BUILD_ASIC for SDM660 target
10/10/16   digant       define FEATURE_USE_PBL_SECBOOT_API
09/23/16   digant       define first 128K for unmapping
08/26/16   digant       define 0x114000000 -- 0x114100000
08/25/16   digant       define tz sdi region address mapped by pbl
08/01/16   yps          Add GSI1 region dump
07/13/16   digants      Increase log buffer size and sbl1 code region
07/08/16   rp           Added DDI support
06/23/16   kpa          Increase ramdump Image size to support display
06/20/16   rp           Added DTTS SRAM address and size info
06/02/16   rp           Remove DDR_TRAINING_DATA_BUF from L2TCM data region
05/10/16   wkimberl     Decrease QSEE size to account for larger XBL Sec.
05/02/16   kpa          Increase HASH_SEGMENT_SIZE to 20 kb
04/18/16   digants      Added XBL_CORE_CODE_BASE2 for WP
04/06/16   kpa          relocate pmic image base to rpm coderam from ocimem
03/29/16   kpa          Increase xbl data ZI to be 52 kb
03/25/16   kpa          Update pimem size define.
03/25/16   kpa          Revert updates to reuse bootrom stack address space
03/22/16   kpa          Reuse bootrom stack region, added DDR-DSF segment.
03/09/16   kpa          Update IPA ramdump and rpm message ram regions
03/02/16   kpa          Update XBL Core image base address
11/09/15   plc          Update PIMEM base and size info
10/27/15   elt          Added SCL_SBL1_BOOT_TIME_MARKER_BUF to size buffer for 
                        boot logging time markers
10/13/15   plc          Update IMEM usage to only use 52KB dedicated space for XBL
10/07/15   plc          Update L2 TCM base address as per PBL whitelist table
08/18/15   elt          Added BOOT_ASYNC_UART_FEATURE
08/07/15   plc          Update 8998 addresses
06/24/15   ck           Added defines to support enhanced boot logging
04/19/15   kedara       Increase XBL loader code size.
04/13/15   kedara       Increase Pmic elf buffer size to 70KB.
04/13/15   ck           Adjusted SCL_SBL1_CODE_SIZE to be 4KB aligned
04/01/15   kedara       Added SCL_pIMEM_MINIMUM_SIZE.
02/20/15   kedara       Update RPM code ram buffer sizes
02/19/15   kedara       Added SCL_SYSTEM_DEBUG_QSEE_INFO_BASE
02/18/15   wkimberl     Move device programmer buffers to OCIMEM.
02/12/15   kedara       Increase XBL region RPM code ram buffer size.
02/09/15   kedara       Added IPA region defines.
02/03/15   wkimberl     Add section for DeviceProgrammer FH Buffers.
02/02/15   wkimberl     Add section for DeviceProgrammer USB Buffers.
01/29/15   kedara       update memory map for sec.dat image base update.
01/21/15   kedara       Reduce pre-DDR init Page table size, increase code size
01/14/15   kedara       update SCL_RAMDUMP_DLOAD_BUFFERS_SIZE
01/08/15   bhsriniv     Add Deviceprogrammer variables 
01/08/15   vphan        Increase Deviceprogrammer data size to 32KB
01/08/15   kedara       Increase Deviceprogrammer image size, to accomodate secImg lib
01/05/15   kedara       Increase Loader image size to 402KB to accomodate security libs.
12/11/14   ck           Added FEATURE_EMPTY_L1_PAGE_TABLE for targets that cannot use PBL's
12/04/14   kedara       Increase Loader image size to 386KB.
12/04/14   kedara       Increase DDR size.
11/26/14   ck           Added FEATURE_USE_PBL_SECBOOT_API
11/20/14   ck           Increased RamDump size.
10/24/14   kedara       Increase XBL Loader size.
10/03/14   kedara       Add base address, size defines for loading PMIC image.
05/02/14   kedara       Initial version
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/

/*===========================================================================
              DEFINES FOR TARGET (equivalent to <target>.builds src)
===========================================================================*/


/*===========================================================================
                      DEFINES FOR 8998 MEMORY MAP
===========================================================================*/
#define   SIZE_128B  0x00000080
#define  SIZE_256B  0x00000100
#define  SIZE_1KB   0x00000400
#define  SIZE_2KB   0x00000800
#define  SIZE_4KB   0x00001000
#define  SIZE_6KB   0x00001800
#define  SIZE_8KB   0x00002000
#define  SIZE_10KB  0x00002800
#define  SIZE_12KB  0x00003000
#define  SIZE_16KB  0x00004000
#define  SIZE_18KB  0x00004800
#define  SIZE_20KB  0x00005000
#define  SIZE_22KB  0x00005800
#define  SIZE_24KB  0x00006000
#define  SIZE_28KB  0x00007000
#define  SIZE_30KB  0x00007800
#define  SIZE_32KB  0x00008000
#define  SIZE_36KB  0x00009000
#define  SIZE_34KB  0x00008800
#define  SIZE_38KB  0x00009800
#define  SIZE_36KB  0x00009000
#define  SIZE_40KB  0x0000A000
#define  SIZE_42KB  0x0000A800
#define  SIZE_44KB  0x0000B000
#define  SIZE_46KB  0x0000B800
#define  SIZE_48KB  0x0000C000
#define  SIZE_52KB  0x0000D000
#define  SIZE_56KB  0x0000E000
#define  SIZE_60KB  0x0000F000
#define  SIZE_64KB  0x00010000
#define  SIZE_66KB  0x00010800
#define  SIZE_68KB  0x00011000
#define  SIZE_70KB  0x00011800
#define  SIZE_76KB  0x00013000
#define  SIZE_80KB  0x00014000
#define  SIZE_82KB  0x00014800
#define  SIZE_84KB  0x00015000
#define  SIZE_88KB  0x00016000
#define  SIZE_92KB  0x00017000
#define  SIZE_94KB  0x00017800
#define SIZE_100KB  0x00019000
#define SIZE_116KB  0x0001D000
#define SIZE_120KB  0x0001E000
#define SIZE_128KB  0x00020000
#define SIZE_140KB  0x00023000
#define SIZE_144KB  0x00024000
#define SIZE_148KB  0x00025000
#define SIZE_160KB  0x00028000
#define SIZE_184KB  0x0002E000
#define SIZE_192KB  0x00030000
#define SIZE_212KB  0x00035000
#define SIZE_216KB  0x00036000
#define SIZE_232KB  0x0003A000
#define SIZE_256KB  0x00040000
#define SIZE_294KB  0x00049800
#define SIZE_298KB  0x0004A800
#define SIZE_300KB  0x0004B000
#define SIZE_312KB  0x0004E000
#define SIZE_320KB  0x00050000
#define SIZE_324KB  0x00051000
#define SIZE_328KB  0x00052000
#define SIZE_332KB  0x00053000
#define SIZE_340KB  0x00055000
#define SIZE_344KB  0x00056000
#define SIZE_350KB  0x00057800
#define SIZE_370KB  0x0005C800
#define SIZE_392KB  0x00062000
#define SIZE_400KB  0x00064000
#define SIZE_402KB  0x00064800
#define SIZE_416KB  0x00068000
#define SIZE_436KB  0x0006D000
#define SIZE_452KB  0x00071000
#define SIZE_456KB  0x00072000
#define SIZE_472KB  0x00076000
#define SIZE_506KB  0x0007D800
#define SIZE_512KB  0x00080000
#define SIZE_524KB  0x00083000
#define   SIZE_1MB  0x00100000
#define   SIZE_2MB  0x00200000
#define   SIZE_6MB  0x00600000
#define  SIZE_16MB  0x01000000
#define  SIZE_17MB  0x01100000
#define  SIZE_68MB  0x04400000
#define  SIZE_72MB  0x04800000
#define   SIZE_1GB  0x40000000
#define SIZE_1_5GB  0x60000000
#define   SIZE_2GB  0x80000000
#define   SIZE_6GB  0x180000000

#define SIZE_1GB_MASK           (SIZE_1GB -1)

#define SCL_L2_TCM_BASE_ADDR    0x14000000

#define SCL_RPM_CODE_RAM_BASE   0x00200000
#define SCL_RPM_CODE_RAM_SIZE   SIZE_160KB

#define BUILD_ASIC "660"

/* XBL rpm code ram buffer to span across [0x0021E000 to 0x00224000] */
#define SCL_RPM_CODE_RAM_XBL_BASE  (SCL_RPM_CODE_RAM_BASE + SIZE_120KB)
#define SCL_RPM_CODE_RAM_XBL_SIZE  SIZE_24KB

#define SCL_RPM_DATA_RAM_BASE   0x00290000
#define SCL_RPM_DATA_RAM_SIZE   SIZE_80KB
#define SCL_RPM_MSG_RAM_BASE    0x778000
#define SCL_RPM_MSG_RAM_SIZE    SIZE_28KB
#define SCL_IMEM_BASE           0x14680000
#define SCL_IMEM_SIZE           SIZE_256KB
#define EXCEPTION_HANDLER_SIZE            SIZE_128B
#define EXCEPTION_HANDLER_NUM             16
#define SCL_SBL1_VECTOR_TABLE_SIZE       (EXCEPTION_HANDLER_NUM * EXCEPTION_HANDLER_SIZE)

#define SCL_BOOTROM_MEMORY_REGION     SIZE_36KB
#define SCL_PRE_DDR_PAGE_TABLE_SIZE   SIZE_48KB
#define SCL_SBL1_IMAGE_BASE           (SCL_L2_TCM_BASE_ADDR + SCL_BOOTROM_MEMORY_REGION + SCL_PRE_DDR_PAGE_TABLE_SIZE)
#define SCL_SBL1_IMAGE_SIZE           SIZE_524KB

/* XBL Loader DDR DSF Driver memory map defines */
#define SCL_SBL1_DDR_DSF_ROM_BASE     (SCL_SBL1_IMAGE_BASE + SCL_SBL1_IMAGE_SIZE )
#define SCL_SBL1_DDR_DSF_ROM_SIZE     SIZE_92KB
#define SCL_SBL1_DDR_DSF_DATA_BASE    (SCL_SBL1_DDR_DSF_ROM_BASE + SCL_SBL1_DDR_DSF_ROM_SIZE)
#define SCL_SBL1_DDR_DSF_DATA_SIZE     SIZE_24KB
#define SCL_SBL1_DDR_DSF_SEGMENT_SIZE  SIZE_116KB

/* Training data size needs to be defined to be used during ramdump */
#define SCL_DDR_TRAINING_DATA_BUF_SIZE SIZE_8KB

/* Address and size of DTTS_SRAM region */
#define SCL_DDR0_DTTS_SRAM_BASE		  0x01037000
#define SCL_DDR1_DTTS_SRAM_BASE		  0x01043000
#define SCL_DDR_DTTS_SRAM_SIZE		  SIZE_16KB

/* XBL Loader L2 TCM memory map defines */
#define SCL_SBL1_CODE_BASE            SCL_SBL1_IMAGE_BASE
#define SCL_SBL1_CODE_SIZE            SIZE_392KB
                                      
#define SCL_SBL1_VECTOR_BASE          SCL_SBL1_CODE_BASE
#define SCL_SBL1_VECTOR_SIZE          0x00000020
                                      
#define SCL_SBL1_STACK_BASE           (SCL_SBL1_CODE_BASE + SCL_SBL1_CODE_SIZE)
#define SCL_SBL1_STACK_SIZE           SIZE_12KB
//Base address of stack is higher end-address of stack region
#define SBL1_STACK_BASE (SCL_SBL1_STACK_BASE + SCL_SBL1_STACK_SIZE)

#define SCL_SBL1_DATA_BASE            (SCL_SBL1_STACK_BASE + SCL_SBL1_STACK_SIZE)
#define SCL_SBL1_DATA_SIZE            SIZE_42KB
#define SCL_SBL1_DATA_ZI_BASE         (SCL_SBL1_DATA_BASE + SCL_SBL1_DATA_SIZE)
#define SCL_SBL1_DATA_ZI_SIZE         SIZE_56KB

#define SCL_SBL1_PAGE_TABLE_BASE 	 (SCL_SBL1_DATA_ZI_BASE + SCL_SBL1_DATA_ZI_SIZE)
#define SCL_SBL1_PAGE_TABLE_SIZE 	  SIZE_20KB

#define SCL_SBL1_SHARED_FUNCTIONS_TABLE_BASE (SCL_SBL1_PAGE_TABLE_BASE + SCL_SBL1_PAGE_TABLE_SIZE)
#define SCL_SBL1_SHARED_FUNCTIONS_TABLE_SIZE  SIZE_1KB


/*RPM Code Ram memory map defines */
#define SCL_SBL1_RPM_CODE_BASE  SCL_RPM_CODE_RAM_XBL_BASE
#define SCL_SBL1_RPM_CODE_SIZE  SIZE_24KB

/* RPM Code RAM memory map defines for DDR training image */
#define SCL_DDR_TRAINING_CODE_BASE      0x00207000
#define SCL_DDR_TRAINING_CODE_SIZE      SIZE_66KB
#define SCL_DDR_TRAINING_DATA_BASE      (SCL_DDR_TRAINING_CODE_BASE + SCL_DDR_TRAINING_CODE_SIZE)
#define SCL_DDR_TRAINING_DATA_SIZE      SIZE_8KB
#define SCL_DDR_TRAINING_DATA_ZI_BASE   (SCL_DDR_TRAINING_DATA_BASE + SCL_DDR_TRAINING_DATA_SIZE)
#define SCL_DDR_TRAINING_DATA_ZI_SIZE   SIZE_6KB
#define SCL_DDR_TRAINING_SIZE           SIZE_80KB 

#define SCL_TZ_OCIMEM_BUFFER            SIZE_184KB

#define SCL_SYSTEM_DEBUG_BASE           (SCL_IMEM_BASE + SCL_TZ_OCIMEM_BUFFER)
#define SCL_SYSTEM_DEBUG_SIZE           SIZE_16KB
#define SCL_SYSTEM_DEBUG_CO_RO_BASE     (SCL_SYSTEM_DEBUG_BASE)
#define SCL_SYSTEM_DEBUG_CO_RO_SIZE     SIZE_12KB
#define SCL_SYSTEM_DEBUG_DATA_BASE      (SCL_SYSTEM_DEBUG_BASE + SCL_SYSTEM_DEBUG_CO_RO_SIZE)
#define SCL_SYSTEM_DEBUG_QSEE_INFO_SIZE SIZE_1KB
#define SCL_SYSTEM_DEBUG_DATA_SIZE      (SCL_SYSTEM_DEBUG_SIZE - SCL_SYSTEM_DEBUG_CO_RO_SIZE - SCL_SYSTEM_DEBUG_QSEE_INFO_SIZE )
#define SCL_SYSTEM_DEBUG_QSEE_INFO_BASE (SCL_SYSTEM_DEBUG_DATA_BASE + SCL_SYSTEM_DEBUG_DATA_SIZE)

#define SCL_SBL1_OCIMEM_DATA_BASE       (SCL_IMEM_BASE + SCL_TZ_OCIMEM_BUFFER + SCL_SYSTEM_DEBUG_SIZE)
#define SCL_SBL1_OCIMEM_DATA_SIZE       SIZE_36KB

#define SCL_TZ_SDI_MAPPED_REGION         0x146A9000
#define SCL_TZ_SDI_MAPPED_REGION_SIZE    0x5000

#define SCL_UNUSED_ADDRESS_BASE          0x00000000
#define SCL_UNUSED_ADDRESS_SIZE          SIZE_128KB

#define MMU_POST_RPM_MEM_REGION_BASE (SCL_SYSTEM_DEBUG_BASE + SCL_SYSTEM_DEBUG_SIZE)
#define MMU_POST_RPM_MEM_REGION_SIZE (0x0100000 - SCL_RPM_CODE_RAM_SIZE - SCL_SYSTEM_DEBUG_SIZE)
#define SHARED_IMEM_SIZE SIZE_4KB
#define SHARED_IMEM_BASE (SCL_IMEM_BASE + SCL_IMEM_SIZE - SHARED_IMEM_SIZE)
#define SHARED_IMEM_BOOT_BASE SHARED_IMEM_BASE
#define SHARED_IMEM_BOOT_SIZE 200
#define SHARED_IMEM_USB_BASE (SHARED_IMEM_BOOT_BASE + SHARED_IMEM_BOOT_SIZE)
#define SHARED_IMEM_USB_SIZE 200
#define SHARED_IMEM_BOOT_CDT_BASE (SHARED_IMEM_USB_BASE + SHARED_IMEM_USB_SIZE)
#define SHARED_IMEM_BOOT_CDT_SIZE 0x0000400
#define SHARED_IMEM_DDR_BASE (SHARED_IMEM_BOOT_CDT_BASE + SHARED_IMEM_BOOT_CDT_SIZE)
#define SHARED_IMEM_DDR_SIZE 200
#define SHARED_IMEM_HLOS_BASE (SHARED_IMEM_DDR_BASE + SHARED_IMEM_DDR_SIZE)
#define SHARED_IMEM_HLOS_SIZE 200
#define SHARED_IMEM_RPM_BASE (SHARED_IMEM_HLOS_BASE + SHARED_IMEM_HLOS_SIZE)
#define SHARED_IMEM_RPM_SIZE 8
#define SHARED_IMEM_QDSS_BASE (SHARED_IMEM_RPM_BASE + SHARED_IMEM_RPM_SIZE)
#define SHARED_IMEM_QDSS_SIZE 12
#define SHARED_IMEM_SECUREMSM_BASE (SHARED_IMEM_QDSS_BASE + SHARED_IMEM_QDSS_SIZE)
#define SHARED_IMEM_SECUREMSM_SIZE 512
#define SHARED_IMEM_PERIPHERAL_DEBUG_BASE (SHARED_IMEM_SECUREMSM_BASE + SHARED_IMEM_SECUREMSM_SIZE)
#define SHARED_IMEM_PERIPHERAL_DEBUG_SIZE 24
#define SHARED_IMEM_PIL_BASE (SHARED_IMEM_PERIPHERAL_DEBUG_BASE + SHARED_IMEM_PERIPHERAL_DEBUG_SIZE)
#define SHARED_IMEM_PIL_SIZE 200
#define SHARED_IMEM_TZ_BASE (SHARED_IMEM_PIL_BASE + SHARED_IMEM_PIL_SIZE)
#define SHARED_IMEM_TZ_SIZE 128
#define SHARED_IMEM_OEM_BASE (SHARED_IMEM_TZ_BASE + SHARED_IMEM_TZ_SIZE)
#define SHARED_IMEM_OEM_SIZE 100
#define SHARED_IMEM_SDI_BASE (SHARED_IMEM_OEM_BASE + SHARED_IMEM_OEM_SIZE)
#define SHARED_IMEM_SDI_SIZE 32
#define SHARED_IMEM_MODEM_BASE (SHARED_IMEM_SDI_BASE + SHARED_IMEM_SDI_SIZE)
#define SHARED_IMEM_MODEM_SIZE 4
#define SHARED_IMEM_UNUSED_SPACE_BASE (SHARED_IMEM_MODEM_BASE + SHARED_IMEM_MODEM_SIZE)
#define SHARED_IMEM_UNUSED_SPACE_SIZE 1152
#define SHARED_IMEM_BOOTROM_BASE (SHARED_IMEM_UNUSED_SPACE_BASE + SHARED_IMEM_UNUSED_SPACE_SIZE)
#define SHARED_IMEM_BOOTROM_SIZE 100
#define DDR_MEM_BASE 0x80000000
#define DDR_MEM_SIZE SIZE_8GB
#define DDR_MEM_LOWER_BASE 0x40000000
#define DDR_MEM_LOWER_SIZE SIZE_1GB 

#define DDR_MEM_RANK1_BASE 0x100000000
#define DDR_MEM_RANK1_SIZE SIZE_2GB
#define DDR_RANK1_L2_REDIRECT_BASE (DDR_MEM_RANK1_BASE + SCL_L2_TCM_BASE_ADDR)
#define DDR_RANK1_L2_REDIRECT_SIZE SIZE_1MB

//#define DDR_MEM_LOWER_BASE 0x40000000
//#define DDR_MEM_LOWER_SIZE SIZE_1GB                      
#define SCL_DDR_pIMEM_BASE 0x86300000
#define SCL_DDR_pIMEM_SIZE SIZE_72MB
#define SCL_pIMEM_BASE 0x1C000000
#define SCL_pIMEM_SIZE SIZE_16MB
#define SCL_pIMEM_MINIMUM_SIZE SIZE_2MB

/* SBL's DDR section is shared by Loader DDR Data and Ramdump */
#define SCL_SBL1_DDR_BASE 0x85E00000
#define SCL_SBL1_DDR_SIZE SIZE_1MB

#define SCL_SBL1_DDR_DATA_BASE SCL_SBL1_DDR_BASE
#define SCL_SBL1_DDR_DATA_SIZE SIZE_212KB
#define SCL_SBL1_DDR_PAGE_TABLE_BASE SCL_SBL1_DDR_DATA_BASE
#define SCL_SBL1_DDR_PAGE_TABLE_SIZE SIZE_64KB
#define SCL_SBL1_DDR_UNCACHED_ZI_BASE (SCL_SBL1_DDR_PAGE_TABLE_BASE + SCL_SBL1_DDR_PAGE_TABLE_SIZE)
#define SCL_SBL1_DDR_UNCACHED_ZI_SIZE SIZE_4KB
#define SCL_SBL1_DDR_ZI_BASE (SCL_SBL1_DDR_UNCACHED_ZI_BASE + SCL_SBL1_DDR_UNCACHED_ZI_SIZE)
#define SCL_SBL1_DDR_ZI_SIZE (SCL_SBL1_DDR_DATA_SIZE - SCL_SBL1_DDR_PAGE_TABLE_SIZE - SCL_SBL1_DDR_UNCACHED_ZI_SIZE)

#define SCL_RAMDUMP_TOTAL_SIZE (SCL_SBL1_DDR_SIZE - SCL_SBL1_DDR_DATA_SIZE)
#define SCL_RAMDUMP_CODE_BASE (SCL_SBL1_DDR_BASE + SCL_SBL1_DDR_DATA_SIZE)
#define SCL_RAMDUMP_CODE_SIZE SIZE_392KB
#define SCL_RAMDUMP_DLOAD_BUFFERS_BASE (SCL_RAMDUMP_CODE_BASE + SCL_RAMDUMP_CODE_SIZE)
#define SCL_RAMDUMP_DLOAD_BUFFERS_SIZE SIZE_68KB
#define SCL_RAMDUMP_DATA_BASE (SCL_RAMDUMP_DLOAD_BUFFERS_BASE + SCL_RAMDUMP_DLOAD_BUFFERS_SIZE)
#define SCL_RAMDUMP_DATA_SIZE (SCL_RAMDUMP_TOTAL_SIZE - SCL_RAMDUMP_CODE_SIZE - SCL_RAMDUMP_DLOAD_BUFFERS_SIZE)
#define SCL_LOADERTEST_TOTAL_SIZE  (SCL_LOADERTEST_CODE_SIZE + SCL_LOADERTEST_DATA_SIZE)
#define SCL_LOADERTEST_CODE_BASE   SCL_XBL_CORE_CODE_BASE
#define SCL_LOADERTEST_CODE_SIZE   SIZE_2MB
#define SCL_LOADERTEST_DATA_BASE   (SCL_XBL_CORE_CODE_BASE + SCL_LOADERTEST_CODE_SIZE)
#define SCL_LOADERTEST_DATA_SIZE   SIZE_2MB
/* Only boot log size is needed as base addresses are automatically placed
   in DDR_ZI */
#define SCL_SBL1_DDR_BOOT_LOG_META_INFO_SIZE SCL_SBL1_BOOT_LOG_META_INFO_SIZE
#define SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE SIZE_4KB
#define SCL_SBL1_DDR_BOOT_TIME_MARKER_BUF_SIZE SIZE_256B

#define SCL_SHARED_RAM_BASE 0x86000000
#define SCL_SHARED_RAM_SIZE SIZE_2MB
#define SCL_QSEE_CODE_BASE SCL_IMEM_BASE
#define SCL_QSEE_TOTAL_SIZE SIZE_100KB
#define SCL_TZ_STAT_BASE  0x86200000
#define SCL_TZ_STAT_BASE_SIZE SIZE_1MB

#define SCL_DEVICEPROG_ZI_BASE SCL_QSEE_CODE_BASE
#define SCL_DEVICEPROG_ZI_SIZE SCL_QSEE_TOTAL_SIZE

#define SCL_DDI_ZI_BASE SCL_QSEE_CODE_BASE
#define SCL_DDI_ZI_SIZE SCL_QSEE_TOTAL_SIZE

#define SCL_QHEE_CODE_BASE 0x85800000
#define SCL_QHEE_TOTAL_SIZE SIZE_6MB
#define SCL_APPSBL_CODE_BASE 0x8EC00000
#define SCL_APPSBL_TOTAL_SIZE 0x0F00000
#define SCL_XBL_CORE_CODE_BASE 0x9FC00000
#define SCL_XBL_CORE_CODE_BASE2 0x80200000
#define SCL_XBL_CORE_TOTAL_SIZE 0x0F00000
#define SCL_SBL1_BOOT_LOG_META_INFO_SIZE 64
#define SCL_SBL1_BOOT_TIME_MARKER_BUF_SIZE 64
#define SCL_SBL1_BOOT_LOG_BUF_SIZE 0x00000C00
#define PBL_APPS_ROM_BASE 0x00100000
#define PBL_APPS_ROM_SIZE SIZE_144KB
#define SBL1_DEBUG_COOKIE_ADDR (SHARED_IMEM_PERIPHERAL_DEBUG_BASE + 0x10)
#define SBL1_DEBUG_COOKIE_VAL 0x53444247

#define SCL_IRAM_BASE SCL_RPM_CODE_RAM_BASE
#define SCL_IRAM_SIZE SCL_RPM_CODE_RAM_SIZE
#define SCL_MODEM_EFS_RAM_SIZE 0x0300000

#define IMAGE_KEY_EMMCBLD_IMG_DEST_ADDR SCL_SBL1_CODE_BASE+80
#define IMAGE_KEY_DEVICEPROGRAMMER_IMG_DEST_ADDR SCL_SBL1_CODE_BASE+80

/* IPA Ramdump memory regions */
#define SCL_IPA_IRAM_BASE  0x147D0000
#define SCL_IPA_IRAM_SIZE  0x00004000
#define SCL_IPA_DRAM_BASE  0x147D4000
#define SCL_IPA_DRAM_SIZE  0x00003F00
#define SCL_IPA_SRAM_BASE  0x147C5000
#define SCL_IPA_SRAM_SIZE  0x00002000
#define SCL_IPA_HRAM_BASE  0x147C9000
#define SCL_IPA_HRAM_SIZE  0x00002F00
#define SCL_IPA_MBOX_BASE  0x147E2000
#define SCL_IPA_MBOX_SIZE  0x00000100
#define SCL_IPA_DICT_BASE  0x147CF000
#define SCL_IPA_DICT_SIZE  0x00001000


#define RAW_PARTITION_BUF_ADDR  0x20000000
#define RAW_PARTITION_BUF_SIZE  0x1000

/*===========================================================================
                Defines to support PMIC image loading 
===========================================================================*/

/*   PMIC config base (0x207000) and size  */
#define SCL_PMIC_CONFIG_BUF_BASE (SCL_RPM_CODE_RAM_BASE + SIZE_28KB)
#define SCL_PMIC_CONFIG_BUF_BASE_DDI  (SCL_SBL1_DDR_DSF_ROM_BASE + SCL_SBL1_DDR_DSF_SEGMENT_SIZE)
#define SCL_PMIC_CONFIG_BUF_SIZE  SIZE_64KB

/*  DDI VMEM base addresses and sizes */
#define SCL_L2_TCM_DDI_BASE_ADDR SCL_PMIC_CONFIG_BUF_BASE_DDI+SCL_PMIC_CONFIG_BUF_SIZE
#define SCL_L2_TCM_DDI_TCM_SIZE SIZE_160KB
#define SCL_L2_TCM_DDI_ZI_BASE_ADDR SCL_PMIC_CONFIG_BUF_BASE_DDI+SCL_PMIC_CONFIG_BUF_SIZE+SCL_L2_TCM_DDI_TCM_SIZE
#define SCL_L2_TCM_DDI_ZI_SIZE SIZE_76KB
#define SCL_VMEM_DDI_DATA_BASE 0x14800000
#define SCL_VMEM_DDI_DATA_SIZE SIZE_140KB

/*  Below is temp buffer base for hash segment used by ELF loader in loading images
    before DDR init 
    Location: 92KB from 0x207000 are reclaimed from bootrom for use by XblLoader. Pmic elf 
    has max size of 64KB. Out of remaining space 10KB is used for hash buffer.
    If DDR training segment gets loaded it will occupy 80KB. hash table segment
    not needed for DDR training load but just a note that it will get overwritten.
*/
#define HASH_SEGMENT_TEMP_BASE (SCL_PMIC_CONFIG_BUF_BASE + SCL_PMIC_CONFIG_BUF_SIZE)
#define HASH_SEGMENT_SIZE SIZE_20KB

/*===========================================================================
                 Defines to support enhanced boot logging
============================================================================*/
#define BOOT_LOGGER_BOOT_CONFIG_FUSE_ADDRESS           HWIO_BOOT_CONFIG_ADDR
#define BOOT_LOGGER_JTAG_ID_FUSE_ADDRESS               HWIO_JTAG_ID_ADDR
#define BOOT_LOGGER_OEM_ID_FUSE_ADDRESS                HWIO_OEM_ID_ADDR
#define BOOT_LOGGER_SERIAL_NUM_FUSE_ADDRESS            HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR
#define BOOT_LOGGER_OEM_CONFIG_ROW_0_FUSE_ADDRESS      HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR
#define BOOT_LOGGER_OEM_CONFIG_ROW_1_FUSE_ADDRESS      HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR 
#define BOOT_LOGGER_FEATURE_CONFIG_ROW_0_FUSE_ADDRESS  HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR
#define BOOT_LOGGER_FEATURE_CONFIG_ROW_1_FUSE_ADDRESS  HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR


/*===========================================================================
                      FEATURE DEFINES USED ACROSS DRIVERS
===========================================================================*/
#define FEATURE_EFS_EFS2_ON_RMTS
#define DDR_XO_SPEED_IN_KHZ 19200
#define BOOT_TEMP_CHECK_THRESHOLD_DEGC
#define FEATURE_USE_PBL_SECBOOT_API
#undef  FEATURE_EMPTY_L1_PAGE_TABLE

/* Enablement flag for asynchronous uart output */
#define BOOT_ASYNC_UART_FEATURE

/* Enablement flags for boot profiler feature below */
#define BOOT_PROFILER_FEATURE  /* Enable boot profiler overall feature can
                                  remove/comment out to completely disable */

/* Set current profiler level
   0 - Profiling messges only
   1 - High level debug messages and level 0
   2 - Low level debug messages and levels 1 and 0 */
#define BOOT_PROFILER_LEVEL 0

/* Enable boot profiler for boot code
   Uncomment the following to enable */
//#define SBL_PROFILER_FEATURE

/* Driver team must define macros which map to boot_profiler* macros. 
   These driver-defined macros to be defined in "[driver]_profile.h".
   After driver has defined and placed these, uncomment the following
   lines to enable for any particular driver(commented out by default) */
//#define EFS_PROFILER_FEATURE

//#define DAL_PROFILER_FEATURE

//#define TLMM_PROFILER_FEATURE

//#define APT_PROFILER_FEATURE

//#define HOTPLUG_PROFILER_FEATURE

//#define SMEM_PROFILER_FEATURE

//#define PLATFORMINFO_PROFILER_FEATURE

//#define PMIC_PROFILER_FEATURE

//#define CLK_PROFILER_FEATURE

//#define VSENSE_PROFILER_FEATURE

//#define HSUSB_PROFILER_FEATURE

//#define BUSYWAIT_PROFILER_FEATURE

//#define BUS_PROFILER_FEATURE

//#define DDR_PROFILER_FEATURE

//#define FLASH_PROFILER_FEATURE

//#define CRYPTO_PROFILER_FEATURE

//#define SECBOOT_PROFILER_FEATURE

//#define UART_PROFILER_FEATURE

//#define POWER_PROFILER_FEATURE

//#define LIMITS_PROFILER_FEATURE

//#define SECIMG_AUTH_PROFILER_FEATURE

#endif  /* _TARGET_CUST_H */
