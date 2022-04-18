/*===========================================================================

GENERAL DESCRIPTION
  This file contains functions and other defines used for
  image version reporting feature.

Copyright 2013 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/debugtools/version/src/image_uuid.c#1 $

=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/

#include "comdef.h"
#include "smem.h"
#include "string.h"
#include "image_version.h"

/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/

// Trace32 Accessible Instrumentation
//
// image_internal_uuid
//
// NULL  : Routine Has Not Run
// !NULL : Contents of OEM_IMAGE_UUID

const char *version_internal_uuid = NULL;

void image_uuid(void)
{
   version_internal_uuid = OEM_IMAGE_UUID_STRING_AUTO_UPDATED;
}
