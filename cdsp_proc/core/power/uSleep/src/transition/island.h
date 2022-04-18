#ifndef ISLAND_H
#define ISLAND_H
/*==============================================================================
  FILE:         island.h

  OVERVIEW:     Internal types & prototypes for island based transition routines

  DEPENDENCIES: None
  
                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/island.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                           FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleepTrans_islandEntryHandler
 *
 * @brief ISR for the interrupt generated at the completion of the hardware island entry
 */
void island_entryHandler(void);

/**
 * uSleepTrans_islandExitHandler
 *
 * @brief ISR for the interrupt generated at the completion of the hardware island exit
 */
void island_exitHandler(uint32 param);

/** 
 * uImage_transitionInitialize
 * 
 * @brief Initilized the uImage system.
 *        This should be called once at system init time.
 */
void island_transitionInitialize(void);

#endif /* ISLAND_H */

