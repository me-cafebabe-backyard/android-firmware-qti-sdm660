#ifndef DIAG_QDI_H
#define DIAG_QDI_H

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Diag Interface

GENERAL DESCRIPTION
  Contains diag qdi structure defination.

EXTERNALIZED FUNCTIONS 
None 

INITIALIZATION AND SEQUENCING REQUIREMENTS


Copyright (c) 2012-2015 Qualcomm Technologies Incorporated.  All Rights Reserved.
Qualcomm Confidential and Proprietary
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.qdsp6/1.0.c2/services/diag/platform/adsp/src/diag_qdi.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
11/11/15   as      File Created 
===========================================================================*/

#include "qurt_qdi_driver.h"
#include "qurt_signal.h"
#include "diagbuf_mpd_type.h"

typedef struct diag_qdi_opener_type
{
   qurt_qdi_obj_t    qdiobj;
   qurt_signal_t     signal;
   int               qdi_handle;
   diagbuf_mpd_type  *user_pd_node_ptr;
} diag_qdi_opener; 

#endif //DIAG_QDI_H
