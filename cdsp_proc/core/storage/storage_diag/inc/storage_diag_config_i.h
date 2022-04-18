/***********************************************************************
 * storage_diag_config_i.h
 *
 * Internal configs for Storage diag
 * Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 *
 * Internal configs for Storage diag
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.qdsp6/1.0.c2/storage/storage_diag/inc/storage_diag_config_i.h#1 $ $DateTime: 2020/02/10 01:57:30 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-01-05   dks   Build cpp flags
2014-09-19   dks   Add hooks to extract performance numbers.
2014-08-04   rp    Create

===========================================================================*/

#ifndef  __STORAGE_DIAG_CONFIG_I_H__
#define  __STORAGE_DIAG_CONFIG_I_H__


#include "storage_diag_config.h"

#if defined (STORAGE_DIAG_MPSS_BUILD)
  #define STORAGE_DIAG_CMD_OFFSET           (0)
#elif defined (STORAGE_DIAG_ADSP_BUILD)
  #define STORAGE_DIAG_CMD_OFFSET           (100)
#elif defined (STORAGE_DIAG_SENSORS_BUILD)
  #define STORAGE_DIAG_CMD_OFFSET           (200)
#elif defined (STORAGE_DIAG_SPARROW_BUILD)
  #define STORAGE_DIAG_CMD_OFFSET           (300)
#else
  #error  "Unknown build-config. Configure the build correctly."
#endif



#endif /*  __STORAGE_DIAG_CONFIG_I_H__ */
