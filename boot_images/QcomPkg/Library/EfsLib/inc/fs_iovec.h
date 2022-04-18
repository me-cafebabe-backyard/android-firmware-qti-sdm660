/***********************************************************************
 * fs_iovec.h
 *
 * I/O-Vec data type.
 * Copyright (C) 2008, 2010 QUALCOMM Technologies, Inc.
 *
 * I/O-Vec data type.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2010-10-12   vr    Change fs_iovec parameter from num_sector to size.
2010-08-20   vr    Added logic to load efs partitions in EFS for rmts targets.
2008-12-12   rp    Create

===========================================================================*/

#ifndef __FS_IOVEC_H__
#define __FS_IOVEC_H__


#include "comdef.h"

/* same as FS_DATA_TAG_DATA */
#define FS_IOVEC_DATA_TYPE_PERMENANT_DATA           (0)

struct fs_iovec
{
  uint8                       *buff_base;
  uint32                      cluster_id;
  uint32                      sector_id;
  uint32                      size;
  uint16                      data_type;
};
typedef struct fs_iovec* fs_iovec_t;



#endif /* not __FS_IOVEC_H__ */
