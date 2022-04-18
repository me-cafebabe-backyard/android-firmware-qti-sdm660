#ifndef _UART_SETTINGS_H_
#define _UART_SETTINGS_H_
/*===========================================================================

  Header defining UART settings/properties structure and its API

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who        what, where, why
--------   --------   ----------------------------------------------------------
12/16/16   AG         Fix issue with GPIO config on different Tiles
10/27/16   PR         Initial version
============================================================================*/

#include <Library/BaseLib.h>

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

typedef enum
{
   LEGACY,
   BADGER,
   BEAR,
   HONEYBADGER,
   DRAGONFLY,
} CHIPSET_FAMILY;

typedef struct
{
  CHIPSET_FAMILY family;
  UINT32 platform;
  UINT32 uart_instance;
  UINT32 gsbi_base;
  UINT32 uart_base;
  UINT32 clock_base;
  UINT32 rts_tlmm_base;
  UINT32 rts;
  UINT32 cts_tlmm_base;
  UINT32 cts;
  UINT32 rx_tlmm_base;
  UINT32 rx;
  UINT32 tx_tlmm_base;
  UINT32 tx;
} UART_PROPS;

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

UART_PROPS* uart_get_properties(void);
#endif
