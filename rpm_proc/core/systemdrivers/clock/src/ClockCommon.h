#ifndef __CLOCKCOMMON_H__
#define __CLOCKCOMMON_H__

/*=========================================================================

        C O M M O N    C O D E    D E F I N I T I O N S

 GENERAL DESCRIPTION
   This file contains the common feature between multiple hardwares

 Copyright (c) 2013 by QUALCOMM Technologies, Inc.  All Rights Reserved.

==========================================================================*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
 
$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/src/ClockCommon.h#1 $

when       who     what, where, why 
--------   ---     --------------------------------------------------------- 
03/04/13   vph     Initial release.

==========================================================================*/ 

/*=========================================================================
      Includes
==========================================================================*/


/*=========================================================================
      Constants & Macros & Typedefs
==========================================================================*/

#define CLK_FLAG_ON(nFlags, nBit)       (((nFlags) & (nBit))? TRUE : FALSE)

#define CLK_ELEM_SIZE(array)            sizeof((array)[0])
#define CLK_NUM_ELEM(array)             (sizeof(array) / CLK_ELEM_SIZE(array))
#define CLK_LAST_IDX(array)             (CLK_NUM_ELEM(array) - 1)

#define CLK_MAX_UINT32                  0xFFFFFFFF
#define CLK_MAX_FREQ_KHZ_UINT32         (CLK_MAX_UINT32 / 1000)

#define CLK_KHZ_TO_HZ_UINT32(nFreqKHz)  ( ((nFreqKHz) < CLK_MAX_FREQ_KHZ_UINT32)? \
                                          ((nFreqKHz) * 1000) :                   \
                                          CLK_MAX_UINT32 )

// Clock Software Event for Processor Sleep
typedef enum
{
  CLOCK_SWE_SLEEP_ENTER = 0,
  CLOCK_SWE_SLEEP_DONE,
} ClockSWEventProcessorSleep;


// Clock Software Event for Processor Sleep
typedef enum
{
  CLOCK_SWE_PROCESSOR_ENTER = 0,
  CLOCK_SWE_PROCESSOR_DONE,
  CLOCK_SWE_PROCESSOR_GFX_RAIL_UP,
  CLOCK_SWE_PROCESSOR_CPU_CLK_RESTORED,
  CLOCK_SWE_PROCESSOR_CNOC_RESTORED,
  CLOCK_SWE_PROCESSOR_BIMC_RESTORED,
  CLOCK_SWE_PROCESSOR_SNOC_RESTORED,
  CLOCK_SWE_PROCESSOR_PNOC_RESTORED,

} ClockSWEventProcessor;


// Software Event for BIMC power collapsed
typedef enum
{
  CLOCK_SWE_BIMC_ENTER                = 0,
  CLOCK_SWE_BIMC_ENTER_SF             = 1,
  CLOCK_SWE_BIMC_ENTER_PC             = 2,
  CLOCK_SWE_BIMC_DONE                 = 3,
  CLOCK_SWE_BIMC_DDR                  = 4,
  CLOCK_SWE_BIMC_DDR_DONE             = 5,
  CLOCK_SWE_BIMC_PWR_DM_ENABLE        = 6,
  CLOCK_SWE_BIMC_PWR_DM_DISABLE       = 7,
  CLOCK_SWE_BIMC_DEHR_SAVE            = 8,
  CLOCK_SWE_BIMC_DEHR_RESTORE         = 9,
  CLOCK_SWE_BIMC_DEHR_DONE            = 10,
  CLOCK_SWE_BIMC_SAVING               = 11,
  CLOCK_SWE_BIMC_SAVING_DONE          = 12,
  CLOCK_SWE_BIMC_RESTORING            = 13,
  CLOCK_SWE_BIMC_RESTORING_DONE       = 14,
  CLOCK_SWE_BIMC_ENTER_SF_DONE        = 15,
  CLOCK_SWE_BIMC_ENTER_PC_DONE        = 16,
  CLOCK_SWE_BIMC_EXIT_SF              = 17,
  CLOCK_SWE_BIMC_EXIT_PC              = 18,
  CLOCK_SWE_BIMC_EXIT_SF_DONE         = 19,
  CLOCK_SWE_BIMC_EXIT_PC_DONE         = 20
} ClockSWEventBIMC;

/*=========================================================================
      Functions
==========================================================================*/


#endif  /* __CLOCKCOMMON_H__ */ 
