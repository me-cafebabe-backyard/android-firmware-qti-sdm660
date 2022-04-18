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

  $Header: //components/rel/rpm.bf/1.8/core/debugtools/version/src/version_init.c#2 $

=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/

#include "version.h"

#include "comdef.h"
#include "image_version.h"

extern void image_uuid(void);

void version_init(void)
{
   if (0 != image_version_populate_version(IMAGE_INDEX_RPM))
   {
      //ERR("unable to populate version", 0, 0, 0);
   }
   image_uuid();
}

