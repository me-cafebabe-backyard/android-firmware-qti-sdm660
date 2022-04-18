#ifndef _BOOT_TARGET_H
#define _BOOT_TARGET_H

/*===========================================================================

                                boot_target
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/XBLLoaderLib/boot_target.h#7 $
  $DateTime: 2017/05/29 07:16:35 $ 
  $Author: pwbldsvc $

when       who          what, where, why
--------   --------     ----------------------------------------------------------
05/11/17   bd           Macros for PMIC WDG timeout values
05/05/17   bd           Secure minidump changes
03/08/17    sj          Added Api to qurey the battery status in XBL ramdump
11/09/16   digant       Use IMAGE_SIZE instead of TOTAL_SIZE
04/18/16   digants      Added WHITELIST_REGION5 with WP base address for XBL_CORE_WHITELIST_REGION_TABLE
03/09/16   kpa          Update IPA region dumps.
09/01/15   plc          Move pImem add logic to dload_target_mem_debug.c, and 
                        update FUSE_DISABLE apis to 8996 tip
06/25/15   as           Add Loader whitelist area
04/01/15   kpa          Dump minimum configured pimem size of two mb.
03/04/15   kpa          Add pImem region dumps.
02/27/15   kpa          Add RPM message ram ramdump region.
02/13/15   ck           Added MPM_PS_HOLD definition
02/09/15   kpa          Add IPA ramdump regions.
01/31/15   kpa          Updates to zero initialize OCIMEM ZI buffer.
01/21/15   kpa          Reduce pre-DDR page table size.
01/14/15   ck           MMU page table values are now target specific
10/29/14   kpa          Support 64 bit memory map
10/27/14   kedara       Increase BOOT_IMAGES_NUM_ENTRIES to 8.
09/24/14   kedara       Add XBL core segment whitelist, relocate some defines to
                        Target_cust.h, remove SBL1_DISABLE_D_CACHE
09/08/14   ck           Added XBL ELF_SEG whitelist regions
08/15/14   ck           Removed unneeded linker variables and defines
08/12/14   ck           Renamed DLOAD_ZI
08/07/14   ck           Removed RPM_MSG_RAM from MEMORY_REGION_TABLE until valid address is available
06/20/14   kedara       Add linker symbol externs
05/02/14   kedara       Initial version
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#ifndef _ARM_ASM_
#include "boot_comdef.h"
#endif /* _ARM_ASM_ */

/*===========================================================================
              DEFINES FOR TARGET (equivalent to <target>.builds src)
===========================================================================*/

/*===========================================================================
                   DEFINES FOR MEMORY MAP, COMMON FEATURE DEFINES
===========================================================================*/
#include "Target_cust.h"

/*===========================================================================
                      DEFINES FOR RAMDUMPS / FEATURE ENABLE 
===========================================================================*/
#define FEATURE_DLOAD_MEM_DEBUG
#define FEATURE_BOOT_RAMDUMPS_TO_SD_CARD
#define CONVERT_TO_MB_SHIFT 20
#define SD_PATH "/mmc1/"
#define SD_RAM_DUMP_PATH SD_PATH "ram_dump/"
#define MEMORY_REGION1 {SCL_IMEM_BASE, SCL_IMEM_SIZE, "OCIMEM", "OCIMEM.BIN"}
#define MEMORY_REGION2 {SCL_RPM_CODE_RAM_BASE, SCL_RPM_CODE_RAM_SIZE, "RPM Code RAM region", "CODERAM.BIN"}
#define MEMORY_REGION3 {SCL_RPM_DATA_RAM_BASE, SCL_RPM_DATA_RAM_SIZE, "RPM Data RAM region", "DATARAM.BIN"}
#define MEMORY_REGION4 {SCL_RPM_MSG_RAM_BASE, SCL_RPM_MSG_RAM_SIZE, "RPM MSG RAM region", "MSGRAM.BIN"}

/* TODO: _FIX_ for 8996 V2
  IPA Region ramdumps to be enabled for V2 version onwards. V1 does not have IPA block 
*/
#define MEMORY_REGION5 {SCL_IPA_IRAM_BASE, SCL_IPA_IRAM_SIZE, "IPA IRAM region", "IPA_IRAM.BIN"}
#define MEMORY_REGION6 {SCL_IPA_DRAM_BASE, SCL_IPA_DRAM_SIZE, "IPA DRAM region", "IPA_DRAM.BIN"}
#define MEMORY_REGION7 {SCL_IPA_SRAM_BASE, SCL_IPA_SRAM_SIZE, "IPA SRAM region", "IPA_SRAM.BIN"}
#define MEMORY_REGION8 {SCL_IPA_HRAM_BASE, SCL_IPA_HRAM_SIZE, "IPA HRAM region", "IPA_HRAM.BIN"}
#define MEMORY_REGION9 {SCL_IPA_MBOX_BASE, SCL_IPA_MBOX_SIZE, "IPA MBOX region", "IPA_MBOX.BIN"}
#define MEMORY_REGION10 {SCL_IPA_DICT_BASE, SCL_IPA_DICT_SIZE, "IPA DICT region", "IPA_DICT.BIN"}

#define MEMORY_REGION_LAST {0, 0, NULL, NULL}
#define MEMORY_REGION_TABLE MEMORY_REGION1,MEMORY_REGION2,MEMORY_REGION3,MEMORY_REGION4,MEMORY_REGION_LAST

#define IPA_MEMORY_REGION_TABLE MEMORY_REGION5,MEMORY_REGION6,MEMORY_REGION7,MEMORY_REGION8,MEMORY_REGION9,MEMORY_REGION10,MEMORY_REGION_LAST  


#define MD_MEMORY_REGION1 {SCL_RPM_CODE_RAM_BASE, SCL_RPM_CODE_RAM_SIZE, "RPM Code RAM region", "md_rpm_coderam.BIN"}
#define MD_MEMORY_REGION2 {SCL_RPM_DATA_RAM_BASE, SCL_RPM_DATA_RAM_SIZE, "RPM Data RAM region", "md_rpm_dataram.BIN"}
#define MD_MEMORY_REGION3 {SCL_RPM_MSG_RAM_BASE, SCL_RPM_MSG_RAM_SIZE, "RPM MSG RAM region", "md_rpm_msgram.BIN"}
#define MD_MEMORY_REGION4 {SCL_RAMDUMP_DLOAD_BUFFERS_BASE, SCL_RAMDUMP_DLOAD_BUFFERS_SIZE, "Debug table addr", "md_dbg_table.BIN"}
#define MD_MEMORY_REGION5 {SHARED_IMEM_BASE, SHARED_IMEM_SIZE, "Shared IMEM", "md_shared_imem.BIN"}

#define MD_MEMORY_REGION_TABLE MD_MEMORY_REGION1,MD_MEMORY_REGION2,MD_MEMORY_REGION3,MD_MEMORY_REGION5,MEMORY_REGION_LAST

/* ELF Segment Element format: {"Region Base Address","Region Size in Bytes"} */
#define WHITELIST_REGION1   {SCL_XBL_CORE_CODE_BASE, SCL_XBL_CORE_TOTAL_SIZE} 
#define WHITELIST_REGION2   {SCL_RAMDUMP_CODE_BASE, SCL_RAMDUMP_TOTAL_SIZE}
#define WHITELIST_REGION3   {SCL_SBL1_CODE_BASE, SCL_SBL1_IMAGE_SIZE}
#define WHITELIST_REGION4	{SCL_DDR_TRAINING_CODE_BASE, SCL_DDR_TRAINING_SIZE}
#define WHITELIST_REGION5   {SCL_XBL_CORE_CODE_BASE2, SCL_XBL_CORE_TOTAL_SIZE}
#define WHITELIST_REGION_LAST {0, 0}

/* Whitelist Table note: Must be on one line as '\' operator not defined in .builds environment */
#define XBL_CORE_WHITELIST_REGION_TABLE WHITELIST_REGION1,WHITELIST_REGION5,WHITELIST_REGION_LAST
#define XBL_RAMDUMP_WHITELIST_REGION_TABLE WHITELIST_REGION2,WHITELIST_REGION_LAST
#define XBL_LOADER_WHITELIST_REGION_TABLE WHITELIST_REGION3,WHITELIST_REGION_LAST
#define DDR_TRAINING_WHITELIST_REGION_TABLE WHITELIST_REGION4,WHITELIST_REGION_LAST

#define BOOT_IMAGES_NUM_ENTRIES 11

#define FEATURE_QFUSE_PROGRAMMING
#define FEATURE_DLOAD_MEM_DEBUG
#define IMAGE_KEY_SBL1_IMG_DEST_ADDR SCL_SBL1_CODE_BASE
#define FEATURE_TPM_HASH_POPULATE

#define PMIC_DEVICE_INDEX      0x0

#define DLOAD_PMIC_WDG_S1_VALUE      110
#define DLOAD_PMIC_WDG_S2_VALUE      120

/*===========================================================================
                      SBL1 SCL DEFINES
===========================================================================*/

#define SBL1_WDOG_RESET_VALUE   0x1

/*---------------------------------------------------------------------------
  Define the destination address and size of the SBL1.
---------------------------------------------------------------------------*/
#define SBL1_CODE_BASE       SCL_SBL1_CODE_BASE
#define SBL1_MAX_IMAGE_SIZE  SCL_SBL1_IMAGE_SIZE


#ifndef _ARM_ASM_
/*---------------------------------------------------------------------------
  Symbols generated by linker with "$" instead of "_".  Symbols are renamed
  in an assembler file to have "_" to make them valid "C" identifiers and
  the symbols are located in the boot ROM.  These symbols define the
  Read/Write data area in boot ROM and RAM, and the Zero Init data area in
  RAM.  Base addresses and length in bytes are given.
---------------------------------------------------------------------------*/
extern uintnt  Load$$SBL1_INDIRECT_VEC_TBL$$Base;
extern uintnt  Image$$SBL1_INDIRECT_VEC_TBL$$Base;
extern uintnt  Image$$SBL1_INDIRECT_VEC_TBL$$Length;
extern uintnt  Load$$SBL1_DATA_RW$$Base;
extern uintnt  Image$$SBL1_DATA_RW$$Base;
extern uintnt  Image$$SBL1_DATA_RW$$Length;
extern uintnt  Image$$SBL1_DATA_ZI$$Base;
extern uintnt  Image$$SBL1_DATA_ZI$$ZI$$Length;
extern uintnt  Image$$SBL1_DDR_ZI$$Base;
extern uintnt  Image$$SBL1_DDR_ZI$$ZI$$Length;

extern uintnt  Image$$SBL1_DDR_UNCACHED_ZI$$Base;
extern uintnt  Image$$SBL1_DDR_UNCACHED_ZI$$ZI$$Length;

extern uintnt  Image$$SBL1_OCIMEM_DATA$$Base;
extern uintnt  Image$$SBL1_OCIMEM_DATA$$ZI$$Length;

extern uintnt  Image$$SYSTEM_DEBUG_QSEE_INFO$$Base;

#endif /* _ARM_ASM_ */


#define BOOT_FLASH_TRANS_MAX_INSTANCES 1

/*---------------------------------------------------------------------------
  Define the SBL page table base address and size, it's used by both SBL2 and 3  
---------------------------------------------------------------------------*/
//#define SCL_SBL_PAGE_TABLE_BASE  (SCL_SBL2_STACK_BASE-SCL_SBL2_STACK_SIZE)
//#define SCL_SBL_PAGE_TABLE_SIZE  0x6000


/*===========================================================================
                      QDST DEFINES
===========================================================================*/ 
/*Use chip hw id for MSM part value. This would simply preparation for OEM pk
  hash auth Test case. With the change, the same QDST signed image can be used
  to verify OEM pk hash authentication*/
#define BOOT_MSM_PART  0x006B20E1
#define BOOT_MSM_HW_ID  (((uint64)BOOT_MSM_PART) << 32)


/*===========================================================================
  Definitions of address range where IMEM exists on the MSM.
===========================================================================*/
#define IMEM_RANGE_START_ADDR SCL_IMEM_BASE
#define IMEM_RANGE_END_ADDR   (SCL_IMEM_BASE+SCL_IMEM_SIZE)


/*===========================================================================
  Definition for the end address of SDRAM on the MSM.
  MAX value for 48 bits (2^48) -1
===========================================================================*/
#define RANGE_END_ADDR        0xFFFFFFFFFFFFUL


/*===========================================================================
                      BOOT LOGGER DEFINES
===========================================================================*/

/**
 * Time out value for outputing a single char to jtag terminal.
 * 
 * Value used by rpm jtag. moved it to this target specific file
 * from common boot_arm7.c Existing value does not ensure proper
 * output to jtag and has to be updated for 8960
 * JTAG_TERM_TIME_OUT renamed to RPM_JTAG_TERM_TIME_OUT as krait
 * uses similar define.
 */
#define RPM_JTAG_TERM_TIME_OUT       0x500

/*=========================================================================== 
  The clock that is used to track time passing.
===========================================================================*/
#define TIMETICK_CLK  MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL 

/*=========================================================================== 
  Clock frequency is 32.768 KHz
  The number of microseconds per cycle is:
  1 / (32.768 KHz) = 30.52ms
  The int part is 30
===========================================================================*/
#define TIMETICK_CLK_SPEED_INT       30

/*=========================================================================== 
  MPM Sleep Clock frequency is 32.768 KHz
  The number of microseconds per cycle is:
  1 / (32.768 KHz) = 30.52ms
  we round 0.52 to 1/2.
  Timestamp is calculated as : count*int + count/2
  Floating point arithmetic should not be used to avoid error and speed penalty
===========================================================================*/
#define CALCULATE_TIMESTAMP(COUNT) \
  ((COUNT)*TIMETICK_CLK_SPEED_INT + (COUNT)/2)

/*=========================================================================== 
  Qtimer Clock frequency is CXO 19.2MHz
  The number of microseconds per cycle 1/19.2
===========================================================================*/
#define CALCULATE_QTIMER_TIMESTAMP(COUNT) \
  ((COUNT)/19.2)
  
/*
  we are using 32 bits timestamp, the max counter value is:
  0xFFFFFFFF/31 = 138547732
  after this value the timestamp will overflow
*/
#define LOG_MAX_COUNT_VAL  138547732


/*TODO: _FIX_ for 8996.*/
/*OEM fuse All jtag debug disable status
  1 if OEM all jtag debug is disabled, 0 otherwise*/
#define FUSE0_DISABLE  (HWIO_INM(OEM_CONFIG0,  \
                              HWIO_FMSK(OEM_CONFIG0, ALL_DEBUG_DISABLE)))

/*QC fuse RPM jtag debug disable status
  1 if QC RPM jtag debug is disabled, 0 otherwise
  */
#define FUSE1_DISABLE  (HWIO_INM(FEATURE_CONFIG2, \
                                 HWIO_FMSK(FEATURE_CONFIG2, RPM_DBGEN_DISABLE)))

/*OEM fuse RPM jtag debug disable status
  1 if OEM RPM jtag debug is disabled, 0 otherwise*/
#define FUSE2_DISABLE  (HWIO_INM(OEM_CONFIG0, \
                                 HWIO_FMSK(OEM_CONFIG0, RPM_DBGEN_DISABLE)))

/*QC fuse APPS jtag debug disable status     
  1 if QC APPS jtag debug is disabled, 0 otherwise*/
#define FUSE3_DISABLE  (HWIO_INM(FEATURE_CONFIG4, \
                               HWIO_FMSK(FEATURE_CONFIG4, QC_APPS_DBGEN_DISABLE)))

/*OEM fuse APPS jtag debug disable status
  1 if OEM APPS jtag debug is disabled, 0 otherwise*/
#define FUSE4_DISABLE  (HWIO_INM(OEM_CONFIG1, \
                                HWIO_FMSK(OEM_CONFIG1, APPS_DBGEN_DISABLE)))

/*QC fuse APPS secure jtag debug disable status
  1 if QC APPS secure jtag debug is disabled, 0 otherwise*/
#define FUSE5_DISABLE  (HWIO_INM(FEATURE_CONFIG5, \
                               HWIO_FMSK(FEATURE_CONFIG5, QC_APPS_SPIDEN_DISABLE)))

/*OEM fuse APPS secure jtag debug disable status
  1 if OEM APPS secure jtag debug is disabled, 0 otherwise*/
#define FUSE6_DISABLE  (HWIO_INM(OEM_CONFIG1,  \
                             HWIO_FMSK(OEM_CONFIG1, APPS_SPNIDEN_DISABLE)))

/*QC fuse APPS 1 jtag debug disable status     
  1 if QC APPS 1 jtag debug is disabled, 0 otherwise*/
#define FUSE7_DISABLE  (HWIO_INM(FEATURE_CONFIG4, \
                               HWIO_FMSK(FEATURE_CONFIG4, QC_APPS_DBGEN_DISABLE)))

#define FUSE8_DISABLE  (HWIO_INM(FEATURE_CONFIG5, \
                                HWIO_FMSK(FEATURE_CONFIG5, QC_APPS_SPIDEN_DISABLE)))
                                
#define FUSE9_DISABLE  (HWIO_INM(OEM_CONFIG1, \
                                HWIO_FMSK(OEM_CONFIG1, APPS_DBGEN_DISABLE)))

/*OEM fuse APPS secure jtag debug disable status
  1 if OEM APPS secure jtag debug is disabled, 0 otherwise*/
#define FUSE10_DISABLE  (HWIO_INM(OEM_CONFIG2,  \
                             HWIO_FMSK(OEM_CONFIG1, APPS_SPNIDEN_DISABLE)))

/* OEM fuse disables the DAP non-invasive debug capabilities */                                
#define DAP_FUSE0_DISABLE  (HWIO_INM(OEM_CONFIG1,  \
                                 HWIO_FMSK(OEM_CONFIG1, DAP_NIDEN_DISABLE)))   
                                 
/* QC fuse disables the DAP non-invasive debug capabilities */                                
#define DAP_FUSE1_DISABLE  (HWIO_INM(FEATURE_CONFIG2,  \
                                 HWIO_FMSK(FEATURE_CONFIG2, QC_DAP_NIDEN_DISABLE)))   
                                 
/* OEM fuse disables the DAP Secure non-invasive debug capabilities.*/                              
#define DAP_FUSE2_DISABLE  (HWIO_INM(OEM_CONFIG1,  \
                                 HWIO_FMSK(OEM_CONFIG1, DAP_SPNIDEN_DISABLE)))
                                 
/* QC fuse disables the DAP Secure non-invasive debug capabilities.*/                              
#define DAP_FUSE3_DISABLE  (HWIO_INM(FEATURE_CONFIG2,  \
                                 HWIO_FMSK(FEATURE_CONFIG2, QC_DAP_SPNIDEN_DISABLE)))   
                                 
/* OEM fuse disables the Disables the DAP invasive debug capabilities.*/
#define DAP_FUSE4_DISABLE  (HWIO_INM(OEM_CONFIG1,  \
                                 HWIO_FMSK(OEM_CONFIG1, DAP_DBGEN_DISABLE))) 
                                 
/* QC fuse disables the Disables the DAP invasive debug capabilities.*/
#define DAP_FUSE5_DISABLE  (HWIO_INM(FEATURE_CONFIG2,  \
                                 HWIO_FMSK(FEATURE_CONFIG2, QC_DAP_DBGEN_DISABLE)))                                  
                             
                                 
/*Macro to check if any RPM jtag debug feature is disabled
  return 1 if any RPM jtag debug is disabled.
  return 0 if it is enabled
*/
#define DEBUG_DISABLED_RPM (FUSE0_DISABLE| \
                            FUSE1_DISABLE| \
                            FUSE2_DISABLE)

/*Macro to check if any apps jtag debug feature is disabled
  return 1 if any apps jtag debug is disabled.
  return 0 if it is enabled*/
#define DEBUG_DISABLED_APPS (FUSE0_DISABLE|  \
                             FUSE3_DISABLE|  \
                             FUSE4_DISABLE|  \
                             FUSE5_DISABLE|  \
                             FUSE6_DISABLE|  \
                             FUSE7_DISABLE|  \
                             FUSE8_DISABLE|  \
                             FUSE9_DISABLE|  \
                             FUSE10_DISABLE)
                             
/* Macro to check if wdog debug image disable fuses are blown 
   return 1 if any one is blown thus disable wdog debug image loading
   return 0 if none is blown thus enable wdog debug image loading */                            
#define DEBUG_DISABLE_WDT  (DAP_FUSE0_DISABLE | \
                            DAP_FUSE1_DISABLE | \
                            DAP_FUSE2_DISABLE | \
                            DAP_FUSE3_DISABLE | \
                            DAP_FUSE4_DISABLE | \
                            DAP_FUSE5_DISABLE)


/*===========================================================================
                      QFPROM DRIVER DEFINES
===========================================================================*/ 
/* Mark QFPROM region as read only: 24KB from SECURITY_CONTROL_BASE */
#define QFPROM_READONLY_BLOCK_SIZE  0x6000


/* SFPB clock defines for Qfprom Driver in khz.
   Clock runs at 64Mhz in sbl3 for 8960. This clock is used
   in Qfprom driver to compute correct timer value.
*/
#define BOOT_QFPROM_SFPB_CLOCK  (0x40 * 1000)


/* EEPROM' DAL device ID */                             
#define EEPROM_DEVICE_ID DALDEVICEID_FLASH_DEVICE_2

/* Macro for EEPROM CDT parsing error action, in this target we go to error handler*/
#define CDT_BL_ERROR(BL_ERR_CODE) \
        BL_VERIFY( FALSE, BL_ERR_CODE );

/* In RPM elf image the entry point is in RPM address space so offset is set to 0 */  
#define APPS_RPM_ADDR_VIEW_OFFSET 0x0

/* Define the SD Ram Dump Indicator LED */
#define RAM_DUMP_LED  PM_RGB_SEGMENT_B

/* Define the DDR training Indicator LED */
#define DDR_TRAINING_LED PM_RGB_SEGMENT_G

/* Define PS_HOLD */
#define MPM_PS_HOLD MPM2_MPM_PS_HOLD


/*=============================================================================
                       MMU TARGET SPECIFIC DEFINES
=============================================================================*/
#define MMU_NUM_L1_PT                    8 /* max number of L1 pagetables */
#define MMU_L2_PT_SIZE                 512 /* L2 resolves bits [29:21], 2^9=512 entries. And 1GB/2MB = 512 */
#define MMU_NUM_L2_PT                    1 /* max number of L2 pagetables=4, 1 set of 512 per GB           */
#define MMU_L3_PT_SIZE                 512 /* L3 resolves bits [20:12], 2^9=512 entries. And 2MB/4KB = 512 */
#define MMU_NUM_L3_PT                    3 /* max number of L3 pagetables allocated in boot loader */

#define MMU_NUM_DDR_L1_PT                    8 /* max number of L1 pagetables */
#define MMU_NUM_DDR_L2_PT                    3 /* max number of L2 pagetables=4, 1 set of 512 per GB           */
#define MMU_NUM_DDR_L3_PT                   12 /* max number of L3 pagetables allocated in boot loader */


#endif  /* _BOOT_TARGET_H */
