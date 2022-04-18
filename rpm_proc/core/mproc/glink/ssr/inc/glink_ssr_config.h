#ifndef GLINK_SSR_CONFIG_H
#define GLINK_SSR_CONFIG_H

/**
 * @file glink_ssr_config.h
 *
 * Declares the coomon functions and macros for the 
 * GLINK SSR component. 
 */

/** \defgroup glink_ssr GLINK SSR
 * \ingroup MPROC
 *
 * Provides functions, types and macros for the GLINK SSR 
 * component for subsystems.
 *
 */
/*@{*/

/*==============================================================================
     Copyright (c) 2014 - 2015 Qualcomm Technologies Incorporated. 
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/rpm.bf/1.8/core/mproc/glink/ssr/inc/glink_ssr_config.h#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/01/15   bc      Remove unnecessary header
10/22/14   rs      Initial revision
===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "glink.h"
#include "glink_internal.h"

/*===========================================================================

                      MACRO DECLARATIONS

===========================================================================*/
/** Defines the maximum number of connected subsystems */
#define GLINK_SSR_CONFIG_MAX_SUBSYSTEMS        GLINK_NUM_HOSTS


/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
typedef struct _glink_ssr_config_type
{
  const char *host;             /* Local host name  */
  const char *master;           /* Master host name */
  const char *channel;          /* SSR channel name */
  const char *transport;        /* Transport name   */
} glink_ssr_config_type;

/*===========================================================================

                        PUBLIC VARIABLE DECLARATIONS

===========================================================================*/


/*===========================================================================

                        PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================
  FUNCTION  glink_ssr_config_get
  ===========================================================================*/
/**
  This function initializes and returns configuration.

  @param  None.

  @return   Configuration.
*/
/*=========================================================================*/
const glink_ssr_config_type *glink_ssr_config_get(void);

#endif   /* GLINK_SSR_CONFIG_H */
