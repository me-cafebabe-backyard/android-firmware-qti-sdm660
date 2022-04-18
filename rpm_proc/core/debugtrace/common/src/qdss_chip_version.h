#ifndef QDSS_CHIP_VERSION_H
#define QDSS_CHIP_VERSION_H

/*=============================================================================

FILE:         qdss_chip_version.h

DESCRIPTION:  

================================================================================
            Copyright (c) 2015 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/
#include "Chipinfo.h"

static __inline boolean qdss_is_8996_v1(void)
{
   ChipInfoFamilyType chip_family=Chipinfo_GetFamily();

   if (CHIPINFO_FAMILY_MSM8996 == chip_family) {
      ChipInfoVersionType chip_version = Chipinfo_GetVersion();
      if (chip_version < CHIPINFO_VERSION(2,0)) {
         return TRUE;
      }
   }
   return FALSE;
}


#endif //QDSS_CHIP_VERSION_H
