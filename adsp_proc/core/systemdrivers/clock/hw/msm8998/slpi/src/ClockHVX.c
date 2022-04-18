/*
===========================================================================
*/
/**
  @file ClockLPASSHVX.c 
  
  The file contains the resource definitions for HVX management on the
  Low Power Audio Subsystem processor.
*/
/*  
  ====================================================================

  Copyright (c) 2014 - 2015 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/slpi/src/ClockHVX.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  11/06/14   dcf     Created for LPASS on 8996.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

/*
 * External header files.
 */
#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>

/*
 * Clock regime headers.
 */
#include "ClockDriver.h"
#include "ClockLPASS.h"
#include "ClockLPASSHWIO.h"

/*=========================================================================
      Externally defined functions
==========================================================================*/

extern ClockDrvCtxt *Clock_GetDrvCtxt(void);
extern uint32 Clock_nHWIOBaseLPASS;

/*=========================================================================
      Type Definitions
==========================================================================*/

static npa_client_handle hNPAeLDOHandle = NULL;

/*
 * Clock_HVXType
 *
 * Structure containing the HVX NPA node and resource data.
 *
 *  HVXNode       - HVX node data
 *  HVXResources  - HVX resource data: /clk/vdd_restrict
 */ 
typedef struct
{
  npa_resource_definition   HVXResource;
  npa_node_definition       HVXNode;
} ClockHVXType;


/*=========================================================================
      Prototypes
==========================================================================*/

static npa_resource_state Clock_HvxDriver
(
  npa_resource *pResource,
  npa_client   *pClient,
  npa_resource_state nState
);


/*=========================================================================
      Variables
==========================================================================*/


/*
 * Clock_HVX
 *
 * Low power resource data.
 */
static ClockHVXType Clock_HVX =
{
  /*
   * HVXResource
   */
  {
    "/clk/hvx", 
    "on/off",
    CLOCK_SOURCE_REQUIRED,      /* max state */
    &npa_max_plugin, 
    NPA_RESOURCE_DEFAULT,
    NULL
  },

  /*
   * HVXNode
   */
  { 
    "/node/clk/hvx",        /* name */
    Clock_HvxDriver,            /* driver_fcn */
    NPA_NODE_DEFAULT,           /* attributes */
    NULL,                       /* data */
    0,                          /* dependency count */
    NULL,                       /* dependency */
    1, &Clock_HVX.HVXResource   /* resource */
  }
};


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_HvxDriver
** =========================================================================*/
/**
  Handle voltage floor restrictions for low temperature extensions.
 
  @param pResource [in] -- The NPA resource being requested.
  @param pClient [in]   -- Pointer to the client making the request.
  @param nState [in]    -- New state of the resource.

  @return
  New state of the resource.

  @dependencies
  None.
*/

static npa_resource_state Clock_HvxDriver
(
  npa_resource      *pResource,
  npa_client        *pClient,
  npa_resource_state nState
)
{
  /*
   * Simply return for initialization states.
   */
  if(pClient != NULL)
  {
    if (pClient->type == NPA_CLIENT_INITIALIZE)
    {
      return nState;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Power up or down the HVX coprocessor based on required request.       */
  /*  0: HVX is not required.  It is safe to collapse the coprocessor.     */
  /*  1: HVX is required.  Power up the coprocessor.                       */
  /*-----------------------------------------------------------------------*/

  if (nState == CLOCK_SOURCE_REQUIRED)
  {
    /*
     * Power up the coprocessor.
     */

    /*
     * Disable the coprocessor clock.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_CLK_CTL, 0x0);

    /*
     * Apply coprocessor reset.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_RESET, 0x1);

    /*
     * Poll QDSP6SS_CP_PWR_STATUS bit ENF_ACK and ENR_ACK are both zero.
     */
    while(0 != (HWIO_INM(LPASS_QDSP6SS_CP_PWR_STATUS,
                   (HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ENR_ACK_BMSK| \
                    HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ENR_ACK_BMSK))))
    {
      DALSYS_BusyWait(2);
    }

    /*
     * Turn on coprocessor power and wait for status ACK.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_PWR_CTL, 0x3);

    while(HWIO_INF(LPASS_QDSP6SS_CP_PWR_STATUS, ENR_ACK) == 0)
    {
      DALSYS_BusyWait(2);
    }

    /*
     * Remove coprocessor I/O clamp.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_PWR_CTL, 0x2);

    /*
     * Release the coprocessor out of reset.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_RESET, 0x0);

    /*
     * Enable coprocessor clock.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_CLK_CTL, 0x1);
  }
  else
  {
    /*
     * Power down the coprocessor.  Assumption is that no thread is using
     * the coprocessor and all previously issued coprocessor instructions
     * are retired.
     */

    /*
     * Turn off coprocessor clock.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_CLK_CTL, 0x0);

    /*
     * Apply coprocessor I/O clamp.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_PWR_CTL, 0x3);

    /*
     * Turn off coprocessor powers.
     */
    HWIO_OUT(LPASS_QDSP6SS_CP_PWR_CTL, 0x1);

//    DALSYS_BusyWait(5);
  }

  return nState;

} /* END Clock_HvxDriver */


/* =========================================================================
**  Function : Clock_HvxCreateClientCB
** =========================================================================*/
/**
  Callback when an HVX node is created.
 
  This function is called by the NPA framework when the given HVX node is
  created.  The creation is delayed until all dependencies are also
  created.
 
  @param *pContext [in] -- Context passed in npa_define_node_cb
  @param nEventType [in] -- Zero.
  @param *pNodeName [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/ 

static void Clock_HvxCreateClientCB
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{
  npa_node_definition *pNode = (npa_node_definition *)pContext;
  uint32 nState;

  /*-----------------------------------------------------------------------*/
  /* Create the appropriate NPA client.                                    */
  /*-----------------------------------------------------------------------*/

  if (pNode == &Clock_HVX.HVXNode)
  {
    hNPAeLDOHandle = 
      npa_create_sync_client(
        Clock_HVX.HVXResource.name, "/clk/hvx", NPA_CLIENT_REQUIRED);
  }

  /*-----------------------------------------------------------------------*/
  /* Send current state info to HVX NPA driver function.                   */
  /*-----------------------------------------------------------------------*/

  nState = CLOCK_SOURCE_NOT_REQUIRED;

  npa_issue_scalar_request(hNPAeLDOHandle, nState); 

} /* END Clock_HvxCreateClientCB */


/* =========================================================================
**  Function : Clock_InitHvx
** =========================================================================*/
/*
  See ClockLPASS.h
*/

DALResult Clock_InitHvx
(
  ClockDrvCtxt *pCtxt
)
{
  npa_resource_state nInitialState;

  /*-----------------------------------------------------------------------*/
  /* Init HVX node.                                                        */
  /*-----------------------------------------------------------------------*/

  Clock_HVX.HVXNode.data = (npa_user_data)pCtxt;

  nInitialState = CLOCK_SOURCE_NOT_REQUIRED;

  npa_define_node_cb(
    &Clock_HVX.HVXNode, &nInitialState, Clock_HvxCreateClientCB,
    &Clock_HVX.HVXNode);


  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitHvx */

