/***********************************************************************
 * fs_os_config_i.h
 *
 * OS abstraction Config file.
 * Copyright (C) 2015 QUALCOMM Technologies, Inc.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.qdsp6/1.0.c2/storage/fs_osal/inc/fs_os_config_i.h#1 $ $DateTime: 2020/02/10 01:57:30 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-02-06   dks   Create

===========================================================================*/

#ifndef __FS_OS_CONFIG_I_H__
#define __FS_OS_CONFIG_I_H__

#include "customer.h"

#if !defined (FEATURE_FS_OS_FOR_QURT)  && \
    !defined (FEATURE_FS_OS_FOR_POSIX)
    #error "Configure build for some OS. Neither of Qurt or Posix defined"
#endif

#endif /* __FS_OS_CONFIG_I_H__ */

