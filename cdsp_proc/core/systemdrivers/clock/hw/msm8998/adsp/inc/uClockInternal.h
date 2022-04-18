#ifndef UCLOCKINTERNAL_H
#define UCLOCKINTERNAL_H
/*
===========================================================================
*/
/**
  @file uClockInternal.h 
  
  Internal header file for the micro clock settings.
*/
/*  
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/adsp/inc/uClockInternal.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  12/03/14   dcf     Created.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/


/*=========================================================================
      Macro Definitions
==========================================================================*/

#define UCLOCK_QDI_CLOCK_CMD_ROUTER                 (1011+QDI_PRIVATE)
//#define UCLOCK_QDI_SET_ENABLE_CLOCK               (1011+QDI_PRIVATE)
//#define UCLOCK_QDI_SET_DISABLE_CLOCK              (1012+QDI_PRIVATE)
//#define UCLOCK_QDI_SET_CLOCK_DIVIDER              (1013+QDI_PRIVATE)


/*=========================================================================
      Type Definitions
==========================================================================*/

typedef enum
{
  UCLOCK_CMD_ENABLE_CLOCK,
  UCLOCK_CMD_DISABLE_CLOCK,
  UCLOCK_CMD_IS_CLOCK_ON,
  UCLOCK_CMD_SET_DIVIDER,
  UCLOCK_CMD_SET_FREQUENCY,
}uClockCmdType;


typedef struct
{
  uint32       nRCGCmdAddr;
  uint32       nRCGCfgAddr;
  uint32       nMAddr;
  uint32       nNAddr;
  uint32       nDAddr;
}uClockFreqCfgRegType;


/*
 * Clock Register Type
 * Parameters:
 *   nEnableAddr  - The register that is used to enable/disable a clock.
 *   nDividerAddr - The register that is used to apply a clock divider.
 *   pRCG         - Pointer to an RCG Register structure where supported.
 */
typedef struct
{
  uint32 nEnableAddr;
  uint32 nDividerAddr;
  uint32 nDividerShft;
  uint32 nDividerBmsk;
  uClockFreqCfgRegType* pRCG;
}uClockRegType;


typedef struct
{
  uint32 nFreqHz;
  uint32 n2Div;
  uint32 nM;
  uint32 nN;
  
}uClockFreqConfigType;


/*
 * Micro uClock QDI layer driver name.
 */
#define uClockQDIName                            "/dev/uClockQDI"


/*=========================================================================
      Function Definitions
==========================================================================*/


#endif /* !UCLOCKINTERNAL_H */

