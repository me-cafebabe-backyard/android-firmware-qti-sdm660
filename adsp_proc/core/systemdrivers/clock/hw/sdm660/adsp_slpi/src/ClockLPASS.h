#ifndef CLOCKLPASS_H
#define CLOCKLPASS_H
/*
===========================================================================
*/
/**
  @file ClockLPASS.h
  
  Internal header file for the clock device driver on the LPASS image.
*/
/*  
  ====================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/sdm660/adsp_slpi/src/ClockLPASS.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  11/11/16   shm     Definitions for NPA BIST framework added.
  10/04/16   shm     First version for SDM660.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DDIClock.h"
#include "ClockBSP.h"
#include "ClockLPASSBSP.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/
/*
 * Resource scaling disable flags
 *   BY_USER
 *     Set: At init or runtime via debugger.
 *     Cleared: Never.
 *     Usage: Disable feature (at compile or runtime).
 *   BY_EFS
 *     Set: At init.
 *     Cleared: Clock_LoadNV().
 *     Usage: Disable feature until EFS is loaded.
 *   BY_EFUSE
 *     Set: When efuse reads feature not supported.
 *     Cleared: Never.
 *     Usage: Disable feature until efuse is read.
 *   BY_CPU_TEST:
 *     Set: When \clk\cpu.test is active.
 *     Cleared: When \clk\cpu.test transitions to inactive.
 *     Usage: Disable feature while \clk\cpu.test is active.
 *   BY_BSP:
 *     Set: When the BSP flag is set to disable the feature.
 *     Usage: Set when init reads the BSP data.
 *   HW_LOGIC:
 *     Set: At init or runtime via debugger.
 *     Cleared: Never.
 *     Usage: Disable HAL activity for resource.
 */
#define CLOCK_FLAG_DISABLED_BY_USER                (0x1 << 0)
#define CLOCK_FLAG_DISABLED_BY_EFS                 (0x1 << 1)
#define CLOCK_FLAG_DISABLED_BY_EFUSE               (0x1 << 2)
#define CLOCK_FLAG_DISABLED_BY_CPU_TEST            (0x1 << 3)
#define CLOCK_FLAG_DISABLED_BY_BSP                 (0x1 << 4)
//#define CLOCK_FLAG_DISABLED__x                   (0x1 << 5)
#define CLOCK_FLAG_DISABLED_HW_LOGIC               (0x1 << 31)

/*
 * Clock NPA Client Names
 */
#define CLOCK_NPA_CLIENT_NAME_CLK_CPU_IMPULSE     "/clk/cpu/impulse"


/*
 * Definitions for NPA BIST
 */

/*
 * The measured clock frequency must match the desired frequency within
 * the following error margin expressed in percent of the desired
 * frequency.
 */
#define CLOCK_NPA_BIST_ERROR_MARGIN_PERCENT  1

/*
 * Default size of the NPA BIST ULOG log buffer.
 *
 * NOTE: The log size should be specified in powers of 2.
 */
#define CLOCK_NPA_BIST_DEFAULT_LOG_SIZE      65536


/*
 * Macro to return absolute value of the difference between two values
 */
#define ABS_DIFF(v1, v2)  ((v1 >= v2) ? (v1 - v2) : (v2 - v1))


/*=========================================================================
      Type Definitions
==========================================================================*/


/*
 * QDSP6 saved configuration
 */
typedef struct
{
  ClockCPUConfigType *pCPUConfig;
  boolean             bDisableDVS;
}ClockQDSP6SavedConfigType;


/*
 * CPU context.
 *
 *  pClock            - Clock node.
 *  pConfig           - Clock domain configuration.
 *  pNASConfig        - Clock domain configuration for NAS.
 *  PerfConfig        - Active clock domain configuration.
 *  nDisableDCS       - Disable flag for clock scaling.
 *  nNASRequestCount  - Counter to track the number of NAS requests on the CPU entering sleep.
 *  hNPAClkCPUImpulse - NPA handle to impulse client on /clk/cpu.
 *  bNPABISTEnabled   - Flag used to enable the NPA BIST for CPU.
 */
typedef struct
{
  ClockNodeType          *pClock;
  ClockCPUConfigType     *pConfig;
  ClockCPUConfigType     *pNASConfig;
  ClockCPUPerfConfigType  PerfConfig;
  uint32                  nDisableDCS;
  uint32                  nNASRequestCount;
  npa_client_handle       hNPAClkCPUImpulse;
  npa_client_handle       bNPABISTEnabled;
} ClockCPUCtxtType;


/**
 * Clock driver image context.
 *
 *  CPUCtxt           - CPU context.
 *  pBSPConfig        - Image specific BSP data.
 *  hClockNPABISTLog  - Handle to our NPA BIST ULOG log.
 *  nNPABISTLogSize   - Size of the NPA BIST ULOG log.
 */
typedef struct
{
  ClockCPUCtxtType         CPUCtxt;
  ClockImageBSPConfigType *pBSPConfig;
  ULogHandle               hClockNPABISTLog;
  uint32                   nNPABISTLogSize;
} ClockImageCtxtType;


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitPLL
** =========================================================================*/
/**
  Initialize the modem PLL management subsystem.
 
  This function initializes NPA nodes and resources to control modem PLLs.
 
  @param *pDrvCtxt [in] -- The driver context.

  @return
  DAL_SUCCESS

  @dependencies
  None.
*/ 

DALResult Clock_InitPLL
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_InitXO
** =========================================================================*/
/**
  Initialize the XO management subsystem.
 
  This function initializes the XO LPR nodes required for communicating 
  resource requests to the RPM.
 
  @param *pDrvCtxt [in] -- The driver context.

  @return
  DAL_SUCCESS

  @dependencies
  None.
*/ 

DALResult Clock_InitXO
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_SetQDSP6Config
** =========================================================================*/
/**
  Set QDSP6 configuration.
 
  This function sets QDSP6 configuration based on input parameters.
 
  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  pConfig  [in] -- New configuration.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/ 

DALResult Clock_SetQDSP6Config
(
  ClockDrvCtxt          *pDrvCtxt,
  ClockCPUConfigType  *pConfig
);


/* =========================================================================
**  Function : Clock_QDSP6TriggerStateUpdate
** =========================================================================*/
/**
  Trigger function to update QDSP6 LPASS states.
 
  This function updates QDSP6 LPASS states (frequencies) and then
  synchronizes them with NPA framework.
 
  @param *pDrvCtxt [in] -- Pointer to the clock driver context.

  @return
  None.

  @dependencies
  None.
*/

void Clock_QDSP6TriggerStateUpdate
(
  ClockDrvCtxt *pDrvCtxt 
);


/* =========================================================================
**  Function : Clock_NPACPUResourceOverwriteActiveState
** =========================================================================*/
/**
  This Function overwrites the CPU resource's active state. It should ONLY
  be invoked during the Sleep sequence when in Single Threaded Mode (STM).

  We invoke this function after directly configuring the CPU without
  going through the NPA. This results in the CPU resource's active state
  being different from the requested state. Upon wake-up, Sleep must make
  an NPA Impulse request which will re-aggregate the CPU requests and
  trigger our driver function.

  @param nState [in] -- Active state of the CPU resource.

  @return
  DAL_SUCCESS -- Resource active state is set. \n
  DAL_ERROR  --  Resource handle is NULL.

  @dependencies
  None.
*/
DALResult Clock_NPACPUResourceOverwriteActiveState
(
  npa_resource_state nState
);


/* =========================================================================
**  Function : Clock_InitVdd
** =========================================================================*/
/**
  This Function overwrites the CPU resource's active state. It should ONLY
  be invoked during the Sleep sequence when in Single Threaded Mode (STM).

  We invoke this function after directly configuring the CPU without
  going through the NPA. This results in the CPU resource's active state
  being different from the requested state. Upon wake-up, Sleep must make
  an NPA Impulse request which will re-aggregate the CPU requests and
  trigger our driver function.

  @param nState [in] -- Active state of the CPU resource.

  @return
  DAL_SUCCESS -- Resource active state is set. \n
  DAL_ERROR  --  Resource handle is NULL.

  @dependencies
  None.
*/
DALResult Clock_InitVdd
(
  ClockDrvCtxt *pCtxt
);


/*=========================================================================
**  Function : Clock_GetImageCtxt
** =========================================================================*/
/**

  API to retrieve the static image context.

  @dependencies
  None.
*/

ClockImageCtxtType* Clock_GetImageCtxt
(
  void
);


/* =========================================================================
**  Function : Clock_NPA_BIST
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on Q6 clock

  @param *pDrvCtxt[in] -- Pointer to driver context.
  
  @dependencies
  Core and image initialization must be complete prior to running the BIST.

*/

void Clock_NPA_BIST
(
  ClockDrvCtxt    *pDrvCtxt
);

#endif /* !CLOCKLPASS_H */
