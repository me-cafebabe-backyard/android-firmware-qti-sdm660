/*==============================================================================
  @file LoaderAptLib.h

  APT LoaderTest Lib api's .

  Copyright (c) 2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary


when       who          what, where, why
--------   ---          -------------------------------------------------- 
06/18/15   kedara       Initial version  

============================================================================*/ 


#ifndef LOADER_APT_LIB_H
#define LOADER_APT_LIB_H

#include "com_dtypes.h"

/* ============================================================================
**  Function : apt_sti_init
** ============================================================================
*/
/*!
 * @brief Api to initialize STI image shared function table and jump to it.
 *  Note: Function does not return
 *
 * @param[in] sti_entry_point  Entry point for STI image 
 *
 * @return None
 *
 */
void apt_sti_init(uintnt sti_entry_point);

#endif /* LOADER_APT_LIB_H */
