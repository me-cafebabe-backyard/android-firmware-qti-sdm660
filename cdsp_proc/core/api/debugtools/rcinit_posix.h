#ifndef RCINIT_POSIX_H
#define RCINIT_POSIX_H
/** vi: tw=128 ts=3 sw=3 et :
@file rcinit_posix.h
@brief This file contains the API for the Run Control Framework, API 2.1
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/api/debugtools/rcinit_posix.h#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "tms_dll_api.h"                                                         /**< MUST PRECEDE CLIENT DEFINITION OF DLL_API_EXPORT */


// USE THE APPROPRIATE NHLOS HEADER FILE TO ACCESS THE API AS DEPENDENCY.

// #include "rcinit_dal.h"     // NHLOS DAL
// #include "rcinit_posix.h"   // NHLOS POSIX
// #include "rcinit_qurt.h"    // NHLOS QURT
// #include "rcinit_rex.h"     // NHLOS REX

#include "pthread.h"
#include "sched.h"

#include "rcxh.h"
#include "rcecb.h"
#include "rcevt_posix.h"
#include "rcinit.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcinit_api @{ */

/**
API, Routine maps NHLOS task context identifier to RCINIT_INFO Opaque handle
@param[in] tid NHLOS task context identifier
@returns
NULL -- Error
RCINIT_INFO -- Opaque handle representing an RCINIT_INFO object
*/
RCINIT_INFO rcinit_lookup_info_posix(pthread_t tid);

/**
API, Routine maps NHLOS task context identifier to RCINIT_INFO Opaque handle
@param[in] tid NHLOS task context identifier
@returns
RCINIT_GROUP -- Enumeration represents startup group for NHLOS tid
*/
RCINIT_GROUP rcinit_lookup_group_posix(pthread_t tid);

/**
API, Routine maps NHLOS task name to RCINIT_INFO Opaque handle
@param[in] name NULL terminated string, string identifier for task context
@returns
pthread_t -- NHLOS task context identifier
*/
pthread_t rcinit_lookup_posix(RCINIT_NAME name);

/**
API, Routine maps RCINIT_INFO Opaque handle to NHLOS task context identifier
@param[in] info Opaque handle representing an RCINIT_INFO object
@returns
pthread_t -- NHLOS task context identifier
*/
pthread_t rcinit_lookup_posix_info(RCINIT_INFO info);

/** @} end_addtogroup rcinit_api */

#if defined(__cplusplus)
}
#endif

#endif
