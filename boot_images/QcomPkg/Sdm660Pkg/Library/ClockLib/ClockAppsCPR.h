#ifndef __CLOCKAPPSCPR_H__
#define __CLOCKAPPSCPR_H__
/*
===========================================================================
*/
/**
  @file ClockAppsCPR.h

  Header description for the apps clock driver Core Power Reduction (CPR)
  hardware block support.
*/
/*
  ====================================================================

  Copyright (c) 2013 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  02/06/13   sr      Derived from MSS CPR implementation.

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/ClockDxe/ClockBSP.h"
#include "Drivers/ClockDxe/ClockDriver.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/

/*
 * NPA Node Names
 */
#define CLOCK_NPA_NODE_NAME_VDD_APC               "/vdd/apc"
#define NPA_NODE_NAME_CORE_CPU_VDD                "/core/cpu/vdd"

#define CLOCK_NPA_NODE_NAME_VDD_APC0              "/vdd/apc0"
#define NPA_NODE_NAME_CORE_CPU0_VDD               "/core/cpu0/vdd"

#define CLOCK_NPA_NODE_NAME_VDD_APC1              "/vdd/apc1"
#define NPA_NODE_NAME_CORE_CPU1_VDD               "/core/cpu1/vdd"

#define CLOCK_VREG_APC_CORNER_MAX CLOCK_VREG_LEVEL_HIGH

/*
 * MAX definition
 */
#ifndef MAX
   #define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#endif

#ifndef MIN
  #define   MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * VDDAPC Context.
 */
typedef struct
{
  DALSYSSyncHandle   hLock;
  DALSYSSyncObj      LockObj;
  npa_client_handle  hNPACoreCpuVdd;
  uint32             nDisableAPCVDD;
  ClockVRegLevelType eVRegAPCCornerCPU;
  uint32             nRawVoltageUV;
  void              *pContext;
  void              *pClientContext[2];
} ClockVDDAPCCtxtType;

/*
 * CPR Context.
 */
typedef struct
{
  CPR_PreSwitchFuncPtr   fpPreSwitch;
  CPR_PostSwitchFuncPtr  fpPostSwitch;
  CPR_GetVoltageFuncPtr  fpGetVoltage;
} ClockCPRCtxtType;

/*
 * Open-loop CPR voltage.
 */
typedef struct
{
  uint32  nMaxCornerFreq;             /* Highest frequency supported by the corresponding corner. */
  uint32  nMaxCornerInitialVoltage;   /* Initial voltage to support the nMaxCornerFreq. */
  uint32  nMaxCornerMinVoltage;       /* Minimal voltage to support the nMaxCornerFreq. */
  uint32  nMaxCornerMaxVoltage;       /* Maximal voltage to support the nMaxCornerFreq. */
  uint32  nVoltageOffset;             /* Number of 10mV steps to offset from the standard voltage. */
  boolean bSubtract;                  /* 1: subtract,
                                         0: add the nVoltageOffset from/to the standard voltage. */
} ClockOLCPRVoltageType;

/*
 * Open-loop CPR e-fuse data.
 */
typedef struct
{
  ClockOLCPRVoltageType mSVS;         /* Open-loop CPR SVS Corner e-fuse data */
  ClockOLCPRVoltageType mNOMINAL;     /* Open-loop CPR NOMINAL Corner e-fuse data */
  ClockOLCPRVoltageType mTURBO;       /* Open-loop CPR TURBO Corner e-fuse data */
  ClockOLCPRVoltageType mSUPERTURBO;  /* Open-loop CPR SUPER TURBO Corner e-fuse data */
} ClockOLCPReFuseDataType;

#endif  /* __CLOCKAPPSCPR_H__ */

