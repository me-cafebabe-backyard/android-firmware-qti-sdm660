/***********************************************************************
 * tftp_os_modem.h
 *
 * NON_HLOS build related OS defines
 * Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.qdsp6/1.0.c2/storage/tftp/os/inc/tftp_os_modem.h#1 $ $DateTime: 2020/02/10 01:57:30 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-05-06   dks   Add OS abstraction layer
2015-01-05   dks   Compile server for TN Apps
2014-12-30   dks   Fixes to config and log module.
2014-06-04   rp    Create

===========================================================================*/

#ifndef __TFTP_OS_MODEM_H__
#define __TFTP_OS_MODEM_H__


#include "tftp_config_i.h"
#include "tftp_comdef.h"

#if !defined (TFTP_NHLOS_BUILD)
  #error "This file should be included only for NHLOS Builds"
#endif

#include "fs_os.h"
#include "fs_errno.h"
#include "fs_fcntl.h"

#define MAIN_TYPE

#define TFTP_SHARED_GID 0

#endif /* not __TFTP_OS_MODEM_H__ */
