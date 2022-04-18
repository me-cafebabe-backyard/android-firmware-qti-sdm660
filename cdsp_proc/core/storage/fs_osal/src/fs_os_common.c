/***********************************************************************
 * fs_os_common.c
 *
 * OS common functionality
 * Copyright (C) 2015 QUALCOMM Technologies, Inc.
 *
 * Verbose Description
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.qdsp6/1.0.c2/storage/fs_osal/src/fs_os_common.c#1 $ $DateTime: 2020/02/10 01:57:30 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-03-13   dks   Create

===========================================================================*/

#include "fs_os_config_i.h"
#include "fs_os_timetick.h"
#include "fs_public.h"

void
fs_os_init (void)
{
  fs_os_timetick_init();
}

#ifndef FEATURE_FS_OS_EFS_FULL_LIB

static int fs_os_qurt_efs_errno = 0;

int*
efs_get_errno_address (void)
{
  return &fs_os_qurt_efs_errno;
}

#endif
