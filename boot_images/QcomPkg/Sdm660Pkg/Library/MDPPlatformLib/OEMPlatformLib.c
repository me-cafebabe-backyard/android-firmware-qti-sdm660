/*=============================================================================

File: OEMPlatformLib.c

OEM platforms specific. This file is to be modified by the OEM only. No Qualcomm
platform specifics or other Qualcomm code should be here.

This file contains all the platform specific configuration that OEM needs to
provide in order to setup OEM specific platforms. The file MDPPlatformLib.c
could be used as sample.

     Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
     Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "OEMPlatformLib.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Global Variables
** ----------------------------------------------------------------------- */


/*===========================================================================
Function Definitions
===========================================================================*/


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: OEMPlatformConfigure()
** 
** DESCRIPTION:
**   Detect, configure, power up, initialize of platform panels
**
*//* -------------------------------------------------------------------- */
MDP_Status OEMPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams)
{
  MDP_Status  eStatus = MDP_STATUS_OK;

  switch (eConfig)
  {
  case MDPPLATFORM_CONFIG_SW_RENDERER:
      pPlatformParams->sPlatformInfo.bSWRender = FALSE;
      break;
      
  case MDPPLATFORM_CONFIG_GETPANELCONFIG:
      {

      }
      break;
      
  case MDPPLATFORM_CONFIG_POWERUP:
      {

      }
      break;

  case MDPPLATFORM_CONFIG_POWERDOWN:
      {

      }
      break;
      
  case MDPPLATFORM_CONFIG_SETBACKLIGHT:
      {

      }
      break;
      
  case MDPPLATFORM_CONFIG_GETPANELID:
      {
        
      }
      break;
      
  case MDPPLATFORM_CONFIG_GETPLATFORMINFO:
      {

      }
      break;

  default:
      eStatus = MDP_STATUS_BAD_PARAM;
      break;
  }
  
  return eStatus;
}



#ifdef __cplusplus
}
#endif
