
#ifndef DIAGCOMM_CMD_H 
#define DIAGCOMM_CMD_H
/*==========================================================================

              Diagnostic Communications for Diag Command/Response Channel

General Description
  
Copyright (c) 2013,2016 by QUALCOMM Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.qdsp6/1.0.c2/services/diag/DCM/common/src/diagcomm_cmd.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/12/16   ph      SMD references removal and code clean up.
08/08/13   sg      Command/response separation

===========================================================================*/

#include "diagcomm_io.h"     /* For diagcomm_io_conn_type, diagcomm_enum_port_type */


/* ------------------------------------------------------------------------
** Function prototypes
** ------------------------------------------------------------------------ */

boolean diagcomm_cmd_open( diagcomm_port_type port_type, diagcomm_enum_port_type channel );
void diagcomm_cmd_close( diagcomm_port_type port_type, diagcomm_enum_port_type channel );
void diagcomm_cmd_init( diagcomm_port_type port_type, diagcomm_enum_port_type channel );

#endif //DIAGCOMM_CMD_H
