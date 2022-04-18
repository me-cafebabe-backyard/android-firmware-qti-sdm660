#ifndef DDR_HEALTH_MONITOR_H
#define DDR_HEALTH_MONITOR_H

/**
 * @file ddr_internal.h
 * @brief
 * Function headers of DDR drivers internal private API
 */

/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/common/ddr_health_monitor.h#1 $ 
$DateTime: 2016/11/03 00:13:13 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
12/06/12   tw      Added support for mx scaling
12/08/11   tw      Initial revision.
================================================================================
                  Copyright 2014-2015 Qualcomm Technologies Incorporated.
                            All Rights Reserved.
                    Qualcomm Confidential and Proprietary
==============================================================================*/
#include "ddr_common.h"

/* -----------------------------------------------------------------------
**                           DEFINES
** ----------------------------------------------------------------------- */


/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* ============================================================================
**  Function : ddr_health_monitor
** ============================================================================
*/
/*!
*   @brief
*   This function is called to perform a sanity test whenever a state change 
*   could possibly affect ddr stability
*   
*   @details
*   Target specific configurations such as override of timing registers and 
*   calling target specific init functions will be captured in this api
*   
*   @param 
*   None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_health_monitor( void );

/* ============================================================================
**  Function : ddr_health_monitor_rpm_msg_hdlr
** ============================================================================
*/
/*!
*   @brief
*   This function is called by rpm to respond to ddr health monitor messages
*   
*   @details
*   HLOS will talk to this api via rpm message, and pass relevent ddr health
*   monitor information
*   
*   @param 
*   None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
void ddr_health_monitor_rpm_msg_hdlr(uint64 address, uint32 size);
#endif
