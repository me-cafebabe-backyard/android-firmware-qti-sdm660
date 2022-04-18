/** vi: tw=128 ts=3 sw=3 et
@file servreg_wrapper_domain_service.h
@brief This file contains the API details for the Protection Domain Monitor, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Confidential and Proprietary
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/api/debugtools/servreg_wrapper_domain_service.h#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "com_dtypes.h"

typedef struct sr_wrapper_cb_data_s sr_wrapper_cb_data_t;

typedef void (*sr_wrapper_cb_type)
(
  boolean service_located,
  sr_wrapper_cb_data_t *  wrapper_data  
);

typedef struct sr_wrapper_cb_data_s
{
  char *             domain;
  char *             service;
  sr_wrapper_cb_type cb;
  void *             data;
} sr_wrapper_cb_data_t;


/**
Looks for a particular service and domain once service locator becomes available
@return
None
*/

void servreg_wrapper_domain_service(sr_wrapper_cb_data_t * wrapper_data );

