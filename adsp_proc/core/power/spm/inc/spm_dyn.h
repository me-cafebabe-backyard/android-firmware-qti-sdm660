#ifndef _SPM_DYN_H_
#define _SPM_DYN_H_
/*==============================================================================
  FILE:         spm_dyn.h

  OVERVIEW:     This file provides the macros and definitions for dynamic sequence
                support

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/inc/spm_dyn.h#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef SPM_DYNAMIC_SEQ

#include "comdef.h"
#include "CoreMutex.h"
#include "CoreVerify.h"

/*==============================================================================
                            MACRO DEFINITIONS
 =============================================================================*/
#define SPM_SEQ_LOCK(handle)    Core_MutexLock((CoreMutex *)handle->lock)
#define SPM_SEQ_UNLOCK(handle)  Core_MutexUnlock((CoreMutex *)handle->lock)
#define SPM_MUTEX_CREATE(lock)  lock = (void *)Core_MutexCreate(CORE_MUTEXATTR_DEFAULT); \
                                CORE_VERIFY_PTR(lock)

#else /* SPM_DYNAMIC_SEQ */

#define SPM_SEQ_LOCK(handle) 
#define SPM_SEQ_UNLOCK(handle)
#define SPM_MUTEX_CREATE(lock)

#endif /* SPM_DYNAMIC_SEQ */

#ifdef __cplusplus
}
#endif

#endif /* _SPM_DYN_H_ */

