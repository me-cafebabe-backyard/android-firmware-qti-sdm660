#ifndef MIHEADER_H
#define MIHEADER_H

/*===========================================================================

                          MULTI-IMAGE HEADER FILE

DESCRIPTION
  This header file contains declarations and type definitions for the
  Image Header Information.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

* Copyright (c) 2013-2016
* Qualcomm Technologies Incorporated.
* All Rights Reserved.
* Qualcomm Confidential and Proprietary
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who                      what, where, why
--------   -------       ----------------------------------------------------------
08/25/16   digants        change STI sec boot ID
10/15/15   wg             Added SECBOOT_ABL_SW_TYPE for Android LK Image
03/02/14   ka             Added SECBOOT_QSEE_DEVCFG_SW_TYPE
10/15/14   ka             Added SECBOOT_PMIC_SW_TYPE
04/15/14   wg             Update QSEE and QHEE sw_id
12/09/13   ck             Added SECBOOT_QSEE_SW_TYPE and SECBOOT_QHEE_SW_TYPE
12/03/13   ck             Added QSEE and QHEE to secboot_sw_type
04/17/12   kedara         Update sw type for MBA and Lpass image.
06/07/12   kedara         Added sw type for MBA, APPS, LPASS images 
04/05/11   dh     	  do not include customer.h
03/27/12   dh             Added secboot_sw_type define and SECBOOT_WDT_SW_TYPE
09/21/10   plc            Added in NAND Definitions for SB3.0
08/02/10   aus            Moved image_type to mibib.h
06/01/10   plc            Refactoring for SB3.0
03/12/10   plc            Reorder IMG enum's to keep consistent with previously 
                          built images
03/09/10   plc            Keep RPM_IMG at same location in array, so RPM image 
                          won't need to change it'd ID, since it builds remotely
03/03/10   plc            Added address for SBL1
01/05/10   aus            Changes for unified boot cookie and image type
                          APPS_KERNEL_IMG
03/11/09   msm            Added Q5 decoupling and removed offset for SCl_DBL_CODE_BASE
09/28/09   vtw            Added boot cookie header and RAMFS image types.
09/09/09   msm            Port for ehostdl.
06/12/09   mrunalm        Initial porting for msm7x30.

============================================================================*/


/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#ifndef _ARM_ASM_
#include "comdef.h"

#include "MIbib.h"
#endif  /* _ASM_ARM_ */


/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

/* ----------------------------------------------------- */
/*   Image Header Defintion                              */
/* ----------------------------------------------------- */

/*===========================================================================
 Image address constants used for MMC/SDRAM.
===========================================================================*/

#define MI_SDCC_SBL1_IMG_DEST_ADDR   SCL_SBL1_CODE_BASE

#define MI_SDCC_SBL2_IMG_DEST_ADDR     SCL_SBL2_CODE_BASE

#define MI_SDCC_SBL3_IMG_DEST_ADDR     SCL_SBL3_CODE_BASE

#define MI_SDCC_RPM_IMG_DEST_ADDR      SCL_RPM_CODE_BASE

#define MI_SDCC_TZ_IMG_DEST_ADDR       SCL_TZ_CODE_BASE

#define MI_SDCC_AMSS_IMG_DEST_ADDR     SCL_MODEM_CODE_BASE

#define MI_SDCC_APPSBL_IMG_DEST_ADDR   SCL_APPS_BOOT_BASE

#define MI_SDCC_APPS_IMG_DEST_ADDR     SCL_APPS_CODE_BASE

/*===========================================================================
 Image address constants used for NAND/SDRAM.
===========================================================================*/

#define MI_NAND_AMSS_IMG_DEST_ADDR     SCL_MODEM_CODE_BASE

#define MI_NAND_APPSBL_IMG_DEST_ADDR   SCL_APPS_BOOT_BASE

#define MI_NAND_APPS_IMG_DEST_ADDR     SCL_APPS_CODE_BASE

#define MI_NAND_ADSP_Q5_DEST_ADDR      SCL_ADSP_Q5_CODE_BASE

#define MI_NAND_SBL1_IMG_DEST_ADDR     SCL_SBL1_CODE_BASE

#define MI_NAND_SBL2_IMG_DEST_ADDR     SCL_SBL2_CODE_BASE

#define MI_NAND_SBL3_IMG_DEST_ADDR     SCL_SBL3_CODE_BASE

#define MI_NAND_RPM_IMG_DEST_ADDR      SCL_RPM_CODE_BASE

#define MI_NAND_TZ_IMG_DEST_ADDR       SCL_TZ_CODE_BASE

/* This is used to see the size of each hash value;20 bytes per hash result */
#define SECBOOT_SIGNATURE_SIZE  20   /* SHA-1 digest size  */

/* These are the PFLAG values for R,W,X in the ELF header (bits 0-3) as defined
 * in the latest ELF documentation is at
 * http://www.caldera.com/developers/gabi/latest/ch5.pheader.html
 * Used QCSBL to determine if a segment is writeable or not
 */
#define MI_ELF_PFLAGS_R            0x4
#define MI_ELF_PFLAGS_W            0x2
#define MI_ELF_PFLAGS_X            0x1

#ifndef _ARM_ASM_
/************************************************************/
/*      Image Type Enum definition is moved to mibib.h      */
/************************************************************/

/* Image component in order, code, signature, certificate */
typedef enum
{
  NONE_SEG =0,
  CODE_SEG,      /* Code        */
  SIGNATURE_SEG, /* Signature   */
  CERT_SEG,      /* Certificate */
  MAX_ITEM = 0x7FFFFFFF
}image_component_type;

/* enum for unified boot OS type */
typedef enum
{
  BMP_BOOT_OS= 0x0,
  WM_BOOT_OS = 0x1,
  ANDROID_BOOT_OS = 0x2,
  CHROME_BOOT_OS = 0x3,
  SYMBIAN_BOOT_OS = 0x4,
  LINUX_BOOT_OS = 0x5,
  MAX_OS = 0x7FFFFFFF
} boot_OS_type;

/*
*****************************************************************************
* @brief This structure is used as the header for the hash data segment in 
 *        signed ELF images.  The sec_img_auth component of secure boot 
 *        makes use of the image_size, code_size, signature_size and 
 *        cert_chain_size elements only.  The reserved structure elements are
*        from an earlier implementation that does not support ELF images.
*        The reserved elements are preserved to minimize the impact on code
*        signing and image creation tools.
*****************************************************************************
*/ 
typedef struct
{
  uint32 res1;            /* Reserved for compatibility: was image_id */
  uint32 res2;            /* Reserved for compatibility: was header_vsn_num */
  uint32 res3;            /* Reserved for compatibility: was image_src */
  uint32 res4;            /* Reserved for compatibility: was image_dest_ptr */
  uint32 image_size;      /* Size of complete hash segment in bytes */
  uint32 code_size;       /* Size of hash table in bytes */
  uint32 res5;            /* Reserved for compatibility: was signature_ptr */
  uint32 signature_size;  /* Size of the attestation signature in bytes */
  uint32 res6;            /* Reserved for compatibility: was cert_chain_ptr */
  uint32 cert_chain_size; /* Size of the attestation chain in bytes */

} mi_boot_image_header_type;

typedef struct
{
  image_type image_id;       /* Identifies the type of elf image this header
                                 represents (OEM SBL, AMSS, Apps boot loader,
                                 etc.). */
  uint32 image_src;          /* Location of elf image in flash: Address of
                                 image in NOR or page/sector offset to image
                                 from page/sector 0 in NAND/SUPERAND. */
} elf_image_info_type;

typedef struct
{
  uint32         magic_number1;         /* magic number 1 */
  uint32         version;               /* cookie version number */
  boot_OS_type   OS_type;               /* the OS type to boot into */
  uint32         boot_apps_parti_entry; /* start address in storage device of the APPS partition;
                                         NAND build from partition.c; eMMC build from MBR */
  uint32         boot_apps_size_entry;  /* Size in Bytes of APPS Kernel in APPS partition to be loaded */
  uint32         boot_apps_ram_loc;     /* location to copy APPS Kernel into RAM */
  void*          reserved_ptr;          /* reserve pointer */
  uint32         reserved_1;            /* reserve for future use */
  uint32         reserved_2;            /* reserve for future use */
  uint32         reserved_3;            /* reserve for future use */
} mi_boot_cookie_type;

typedef struct
{
    mi_boot_image_header_type image_header;
    mi_boot_cookie_type       boot_cookie;
}mi_boot_header_cookie_type;


/*---------------------------------------------------------------------------
  Software Type identifiying image being authenticated. These values
  correspond to the code signing tools (CSMS) Software ID field which has
  lower 32 bits for Software type and upper 32 bits for Software version.
---------------------------------------------------------------------------*/
typedef enum
{
  SECBOOT_SBL_SW_TYPE                = 0,
  SECBOOT_SBL1_SW_TYPE               = 0,
  SECBOOT_AMSS_SW_TYPE               = 1, 
  SECBOOT_DMSS_SW_TYPE               = 1,
  SECBOOT_MBA_SW_TYPE                = 1, /* Modem boot authenticator image */
  SECBOOT_AMSS_HASH_TABLE_SW_TYPE    = 2,
  SECBOOT_FLASH_PRG_SW_TYPE          = 3,
  SECBOOT_EHOSTD_SW_TYPE             = 3,
  SECBOOT_DSP_HASH_TABLE_SW_TYPE     = 4,
  SECBOOT_LPASS_HASH_TABLE_TYPE      = 4, /* Lpass hash table */
  SECBOOT_QSEE_DEVCFG_SW_TYPE        = 5, /* Qsee Dev Config Image */ 
  SECBOOT_SBL3_SW_TYPE               = 6,
  SECBOOT_TZ_KERNEL_SW_TYPE          = 7, /* TZBSP Image */
  SECBOOT_QSEE_SW_TYPE               = 7, /* TZ is now called QSEE */
  SECBOOT_HOSTDL_SW_TYPE             = 8,
  SECBOOT_APPSBL_SW_TYPE             = 9,
  SECBOOT_RPM_FW_SW_TYPE             = 10,
  SECBOOT_SPS_HASH_TABLE_TYPE        = 11,
  SECBOOT_TZ_EXEC_HASH_TABLE_TYPE    = 12, /* Playready or TZ Executive Image */
  SECBOOT_RIVA_HASH_TABLE_TYPE       = 13,
  SECBOOT_APPS_HASH_TABLE_TYPE       = 14, /* Apps Image */
  SECBOOT_STI_SW_TYPE                = 17, /* STI Image */
  SECBOOT_WDT_SW_TYPE                = 18, /* Wdog debug image */
  SECBOOT_QHEE_SW_TYPE               = 21,
  SECBOOT_PMIC_SW_TYPE               = 22, /* PMIC config Image */
  SECBOOT_ABL_SW_TYPE                = 28, /* Android LK Image */ 
  SECBOOT_APDP_SW_TYPE               = 0x200, /* debug policy Image */ 
  SECBOOT_MAX_SW_TYPE                = 0x7FFFFFFF /* force to 32 bits*/
} secboot_sw_type;


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/


#endif  /* _ASM_ARM_ */
#endif  /* MIHEADER_H */

