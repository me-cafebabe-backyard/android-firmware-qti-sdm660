#ifndef __SPIDRIVERTYPES_H__
#define __SPIDRIVERTYPES_H__

/**
@file SpiDriverTypes.h
*/

/*===========================================================================
Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.qdsp6/1.0.c2/buses/spi/src/driver/inc/SpiDriverTypes.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

when         who      what, where, why
----------   ---      ------------------------------------
05/06/2014   vmk      Created

===========================================================================*/
#include "comdef.h"

#define SPI_DEVICE_OPEN              0x00000004
typedef void* SPIDEVICE_HANDLE;

typedef struct
{
   SPIDEVICE_HANDLE hSpiDev;
   uint32 qup_core_num;
   uint32 status;
} spiDevice;

#endif //multiple inclusion guard
