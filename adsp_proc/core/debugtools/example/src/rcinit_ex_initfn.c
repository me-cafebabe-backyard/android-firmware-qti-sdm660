/** vi: tw=128 ts=3 sw=3 et :
@file rcinit_ex_initfn.c
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
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/example/src/rcinit_ex_initfn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcinit.h"

/*===========================================================================

 FUNCTION rcinit_example_initfn

 DESCRIPTION
 example task boiler plate

 DEPENDENCIES
 none

 RETURN VALUE
 operation success

 SIDE EFFECTS
 none
 ===========================================================================*/

/*static*/ unsigned long rcinit_internal_initfn_count;

void rcinit_example_initfn(void)
{
   rcinit_internal_initfn_count++;
}
