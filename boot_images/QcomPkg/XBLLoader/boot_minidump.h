 #ifndef BOOT_MINIDUMP_H
#define BOOT_MINIDUMP_H
/*=============================================================================

                               Boot minidump
                               Header File
GENERAL DESCRIPTION
  This file provides the APIs for minidump feature
  
EXTERNALIZED FUNCTIONS
  
INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
01/17/17   bd      Initial version

=============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "comdef.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

#define MD_TOTAL_SMEM_SIZE                (10*1024)
#define MD_REGION_NAME_LENGTH             (16)

#define MD_REVISION                       (1)    // 1st revision of SMEM

#define struct_member_offset(type, m)     (&((( type *)0)->m))

#ifndef SBL_MINIDUMP_MODE_BIT_MASK
#define SBL_MINIDUMP_MODE_BIT_MASK        (0x00000020)
#endif

#define SBL_MINIDUMP_SMEM_ID               (602) //use from smem_type.h once its available

typedef struct
{
  char      region_name[MD_REGION_NAME_LENGTH];
  uintnt    region_base_address;
  uintnt    region_size;  
} boot_minidump_smem_region;

typedef struct
{
  uint32                        md_revision;
  uint32                        total_smem_length;
  uintnt                        next_available_offset;
  char                          reserved[MD_REGION_NAME_LENGTH]; //padding to start region details on 32byte boundary
  boot_minidump_smem_region     region_info[1]; /* since LLVM does not support extensible array,
                           using size-1, Actual array length depends on total smem size */
} boot_minindump_smem_area;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
void add_minidump_regions(void);

#endif  /* BOOT_MINIDUMP_H */
