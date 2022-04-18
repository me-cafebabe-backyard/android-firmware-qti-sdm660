/*=============================================================================
 
  File: HALHDMIDriver.c
 
  Stubbed HDMI driver library
  
 
 Copyright (c) 2011-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 =============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include <Uefi.h>
#include <Library/BaseLib.h>

#include "MDPLib_i.h"
#include "MDPSystem.h"
#include <Library/PcdLib.h> 

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Enum Types 
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Structure Types 
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Global Variables
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Forward Declaration of Private Functions.
** ----------------------------------------------------------------------- */


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HAL_HDMI_Init()
** 
** DESCRIPTION:
**   Initialize LCD panel to use display.
**
*//* -------------------------------------------------------------------- */
MDP_Status HAL_HDMI_Init()
{
  return MDP_STATUS_NOT_SUPPORTED;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HAL_HDMI_Init()
** 
** DESCRIPTION:
**   Initialize LCD panel to use display.
**
*//* -------------------------------------------------------------------- */
bool32 HAL_HDMI_DetectHPD(void)
{
  return FALSE;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HAL_HDMI_Term()
** 
** DESCRIPTION:
**   Unload panel.
**
*//* -------------------------------------------------------------------- */
MDP_Status HAL_HDMI_Term()
{
  return MDP_STATUS_NOT_SUPPORTED;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HAL_HDMI_SetMode()
** 
** DESCRIPTION:
**   Set Display Mode.
**
*//* -------------------------------------------------------------------- */
MDP_Status HAL_HDMI_SetMode(uint32  uModeIndex)
{
  return MDP_STATUS_NOT_SUPPORTED;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HAL_HDMI_GetInfo()
** 
** DESCRIPTION:
**   Get display info.
**   HAL_HDMI_Init MUST be called before calling this func
**
*//* -------------------------------------------------------------------- */
MDP_Status HAL_HDMI_GetInfo(uint32 uModeIndex, MDP_Panel_AttrType *psDisplayAttr)
{
  MDP_Status  eStatus = MDP_STATUS_NOT_SUPPORTED;


  if (PCD_EXTERNAL_DISPLAY_HDMI == PcdGet32(PcdExtDisplayType))
  {
    eStatus = MDP_STATUS_OK;
  }

  return eStatus;
}


/* -----------------------------------------------------------------------
** Private Functions
** ----------------------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

