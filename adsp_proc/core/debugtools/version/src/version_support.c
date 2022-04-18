/** vi: tw=128 ts=3 sw=3 et
@file version_support.c
@brief This file contains the API for the IMAGE VERSION, API 1.0.1
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/version/src/version_support.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "version.h"

VERSION_HANDLE version_map_name(VERSION_NAME name)
{
   return (VERSION_NULL);
}

VERSION_NAME version_map_handle(VERSION_HANDLE handle)
{
   return (VERSION_NULL);
}

VERSION_HANDLE version_create_name(VERSION_NAME name)
{
   return (VERSION_NULL);
}

VERSION_BOOL version_search_name(VERSION_NAME name)
{
   return (VERSION_FALSE);
}

VERSION_HANDLE version_register_name(VERSION_NAME name, VERSION_P ver)
{
   return (VERSION_NULL);
}

VERSION_HANDLE version_register_name_ex(VERSION_NAME name, VERSION_BUF buffer, VERSION_BUFLEN len)
{
   return (VERSION_NULL);
}
