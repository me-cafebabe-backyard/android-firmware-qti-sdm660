#ifndef SLEEP_PMI_H
#define SLEEP_PMI_H

/*==============================================================================
  FILE:         sleep_pmi.h

  OVERVIEW:     This file contains PMI handler functions and types 
                declarations for a given processor.

  DEPENDENCIES: None

                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/sleep_pmi.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                            TYPE DEFINITIONS
 =============================================================================*/
/**
 * sleep_PMI_handler_ptr_type
 *
 * @brief PMI ISR function pointer that is called durring APCR exiting. The 
 *        pointer will be modified to point to the correct handler based on if
 *        the system is in uImage or normal operational modes. 
 */
typedef void (*sleep_PMI_handler_ptr_type)(void);

/*==============================================================================
                           GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepPMI_setHandlerFunctionPTR
 *
 * @brief This function sets the PMI handler that will be called from the ISR        
 *  
 * @param newPMIPtr:  Pointer to the function to call when the PMI ISR is 
 *                    invoked.
 */
void sleepPMI_setHandlerFunctionPTR(sleep_PMI_handler_ptr_type newPMIPtr);

#endif /* SLEEP_PMI_H */
