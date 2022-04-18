/** vi: tw=128 ts=3 sw=3 et :
@file rcinit_qurt_tls.c
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
Copyright (c) 2015 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/rcinit/src/rcinit_qurt_tls.c#1 $
$Change: 22511909 $
$DateTime: 2020/02/10 01:57:30 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcinit_qurt.h"
#include "rcinit_internal.h"

int rcinit_internal_tls_create_key(int* x, void (*y)(void*))
{
   return qurt_tls_create_key(x, y);
}

int rcinit_internal_tls_set_specific(int x, void* y)
{
   return qurt_tls_set_specific(x, y);
}

void* rcinit_internal_tls_get_specific(int x)
{
   return qurt_tls_get_specific(x);
}
