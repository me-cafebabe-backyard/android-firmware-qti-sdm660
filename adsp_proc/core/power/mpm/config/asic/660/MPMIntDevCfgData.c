/*==============================================================================
   FILE:        MPMIntDevCfgData.c

  OVERVIEW:     MPM hardware to local interrupt/gpio mapping info. This
                mapping is target specific and may change for different 
                targets. Even mapping could change between masters within a
                same target as some master may want a mapped irq as wakeup
                interrupt while other may not.
 
  DEPENDENCIES: None

                Copyright (c) 2014-2017 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/config/asic/660/MPMIntDevCfgData.c#1 $
$DateTime: 2020/02/10 01:57:30 $
=============================================================================*/ 

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "vmpm_internal.h"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/**
 * Table mapping the MPM Pin number to the GPIO and/or IRQ pin 
 * number per the IP Catalog. 
 */
mpm_int_pin_mapping_type devcfg_MpmInterruptPinNum_Mapping[] =
{
  /* Trigger                 Local Pin#         Pin Type   */
  /* -------                 -------------      --------   */
  /*0*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, 1               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 5               , MPM_GPIO },
  /*5*/
  { MPM_TRIGGER_RISING_EDGE, 9               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 10              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 66              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 22              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 25              , MPM_GPIO },
  /*10*/
  { MPM_TRIGGER_RISING_EDGE, 28              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 58              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, 41              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 43              , MPM_GPIO },
  /*15*/
  { MPM_TRIGGER_RISING_EDGE, 40              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 42              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 46              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 50              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 44              , MPM_GPIO },
  /*20*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, 56              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 45              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 68              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 69              , MPM_GPIO },
  /*25*/
  { MPM_TRIGGER_RISING_EDGE, 70              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 71              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 72              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 73              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 64              , MPM_GPIO },
  /*30*/
  { MPM_TRIGGER_RISING_EDGE, 2               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 13              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 111             , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 74              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 75              , MPM_GPIO },
  /*35*/
  { MPM_TRIGGER_RISING_EDGE, 76              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 82              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 17              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 77              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 47              , MPM_GPIO },
  /*40*/
  { MPM_TRIGGER_RISING_EDGE, 54              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 48              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 101             , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 49              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 51              , MPM_GPIO },
  /*45*/
  { MPM_TRIGGER_RISING_EDGE, 86              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 90              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 91              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 52              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  /*50*/
  { MPM_TRIGGER_RISING_EDGE, 55              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 6               , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  65              , MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  /*55*/
  { MPM_TRIGGER_RISING_EDGE, 67              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 83              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 84              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 85              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 87              , MPM_GPIO },
  /*60*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, 21              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 78              , MPM_GPIO },
  /*65*/
  { MPM_TRIGGER_RISING_EDGE, 113             , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 60              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 98              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 30              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  /*70*/
  { MPM_TRIGGER_RISING_EDGE, 31              , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  29              , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  /*75*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  107             , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  /*80*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  109             , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  103             , MPM_GPIO },
  /*85*/
  { MPM_TRIGGER_LEVEL_HIGH,  105             , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  /*90*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_LEVEL_HIGH,  305             , MPM_IRQ  },
  /*95*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  
  /* End of the table entry */
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_EOT  },
};
