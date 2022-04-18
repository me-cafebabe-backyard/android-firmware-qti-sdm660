#ifndef GLINK_LB_SERVER_CONFIG_H
#define GLINK_LB_SERVER_CONFIG_H

/**
 * @file glink_lb_server_config.h
 *
 * Internal definitions for GLink Loopback Server configurations
 */

/*==============================================================================
     Copyright (c) 2016 QUALCOMM Technologies Incorporated.
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/mproc/glink/lb_server/inc/glink_lb_server_config.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/20/14   an      Initial version
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "glink.h"

/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/
typedef struct
{
  const char *host;               /* This subsystem name  */
  const char *ctrl_channel;       /* Control channel name */
  const char *transport;          /* Transport name       */
  uint32      num_subsytems;      /* Number of Subsytems  */
  const char *subsytems[];        /* Subsytems names      */
} glink_lb_server_config_type;

/*===========================================================================
                      TYPE DECLARATIONS
===========================================================================*/


/*===========================================================================
                     FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
FUNCTION      glink_lb_server_config_get
===========================================================================*/
/**
  This function initializes and returns configuration.
  
  @param    None.

  @return   Configuration.
*/
/*=========================================================================*/
const glink_lb_server_config_type *glink_lb_server_config_get(void);

#endif //GLINK_LB_SERVER_CONFIG_H
