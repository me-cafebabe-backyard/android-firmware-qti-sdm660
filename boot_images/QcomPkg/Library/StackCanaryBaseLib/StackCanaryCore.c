/******************************************************************//**
 * @file StackCanryCore.c
 *
 * @brief StackCanryCore functions
 *
 * Copyright (c) 2016 by Qualcomm Technologies, Inc.
 * All Rights Reserved.
 *
 *********************************************************************/
/*=======================================================================
                        Edit History

when       who     what, where, why
--------   ----    --------------------------------------------------- 
07/06/16   vk      Initial version
========================================================================*/
#include <Library/RandomStackCanaryLib.h>

extern void* __stack_chk_guard;

VOID InitStackCanary (VOID);

/**
 * Initialize stack check canary
 */
VOID InitStackCanary (VOID)
{
#ifndef PRE_SIL
  __stack_chk_guard = (VOID*) GetRandomStackCanary();
#endif
}
