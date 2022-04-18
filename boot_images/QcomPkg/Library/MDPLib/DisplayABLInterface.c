/*=============================================================================
 
  File: DisplayABLInterface.c
 
  Source file for MDP ABL interface functions

   
  Copyright (c) 2016, 2019 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  * Neither the name of The Linux Foundation nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/RamPartitionTableLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIDisplayABL.h>
#include <Include/scm_sip_interface.h>
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "MDPPlatformLib.h"
#include "DisplayABLInterface.h"
#include "HALDSILib.h"

/*=========================================================================
     Default Defines
==========================================================================*/

#define PANEL_LIST_STR_LEN_MAX          1024                   // maximum length for the panel list string
#define PANEL_CONFIG_STR_LEN_MAX        256                    // maximum length for panel configuration string
#define PANEL_OVERRIDE_STR_LEN_MAX      256                    // maximum length for panel override string

#define PANEL_CMD_MARKER_PRIM           "prim:"                // Panel override: primary panel marker
#define PANEL_CMD_MARKER_PRIM_LEN       5                      //.Length

#define PANEL_CMD_MARKER_SEC            "sec:"                 // Panel override: secondary panel marker
#define PANEL_CMD_MARKER_SEC_LEN        4                      // Length 

#define PANEL_CMD_MARKER_CONFIG         ":cfg"                 // Panel override: topology selection marker
#define PANEL_CMD_MARKER_CONFIG_LEN     4                      // Length

#define PANEL_CMD_MARKER_SKIP           ":skip"                // Panel override: skip override in bootloader
#define PANEL_CMD_MARKER_DISABLE        ":disable"             // Panel override: disable continuous splash
#define PANEL_CMD_MARKER_SWAP           ":swap"                // Panel override: swap DSI controllers
#define PANEL_CMD_MARKER_PLL0           ":pll0"                // Panel override: use pll0
#define PANEL_CMD_MARKER_PLL1           ":pll1"                // Panel override: use pll1

#define PANEL_CMD_MARKER_SIM            "#sim"                 // Panel override: simulator panel
#define PANEL_CMD_MARKER_SIM_SWTE       "#sim-swte"            // Panel override: software tear check
#define PANEL_CMD_MARKER_SIM_HWTE       "#sim-hwte"            // Panel override: hardware tear check

#define NO_PANEL_CONFIG                 "none"                 // Panel override: skip display in bootloader


#define DISPLAY_CMDLINE_PREFIX          " mdss_mdp.panel=1:"   //Panel config prefix
#define DISPLAY_CMDLINE_BYPASS_PREFIX   " mdss_mdp.panel=0:"   //Panel config prefix for bypass

#define SIM_OVERRIDE                    "#override:"           // Panel config: override marker
#define DSI_0_STRING                    ":0:"                  // Panel config: dsi controller 0
#define DSI_1_STRING                    ":1:"                  // Panel config: dsi controller 1
#define DSI_CFG_STRING                  ":cfg:"                // Panel config: topology selection marker

#define HDMI_CONTROLLER_STRING          "hdmi:0"               // Panel config: HDMI controller marker
#define DSI_CONTROLLER_0_STRING         "dsi:0:"               // Panel config: DSI0 controller marker
#define DSI_CONTROLLER_1_STRING         "dsi:1:"               // Panel config: DSI1 controller marker

#define SPLIT_DSI_STRING                "split_dsi"            // Panel config: ping pong split mode 
#define DUAL_DSI_STRING                 "dual_dsi"             // Panel config: dual dsi mode
#define SINGLE_DSI_STRING               "single_dsi"           // Panel config: single dsi_mode

#define SIM_MODE_STRING                 "sim"                  // Panel config: simulator panel
#define SIM_HWTE_STRING                 "sim-hwte"             // Panel config: software tear check
#define SIM_SWTE_STRING                 "sim-swte"             // Panel config: hardware tear check

/* Helper to get display params struct*/
#define GET_ABL_CONTEXT()     (&gsABLContext)

// The display panel configuration file macro definition
#define DISP_FILE_EXT                         L".cfg"
#define DISP_FILE_NAME_MAX_SIZE               64
#define DISP_VARIABLE_VALUE_MAX_SIZE          256
#define DISP_LOGFS                            L"logfs"

/* -----------------------------------------------------------------------
** Local Types
** ----------------------------------------------------------------------- */

/* Display ABL Context
*/
typedef struct
{
  Display_ABLParamsType   sABLParams;                           /* Params parsed from override command */
  bool32                  bOverride;                            /* Flag panel override */
  const PanelInfoType    *pDTInfoArray;                         /* DT info for all supported panels */
  CHAR8                   pPanelConfig[PANEL_CONFIG_STR_LEN_MAX];  /* Panel configuration command to kernel */
  uint32                  uDynamicRefreshDataAddress;              /* Memory address for PLL calibration data */
  uint32                  uContinuousSplashAddress;                /* Memory address for continuous splash buffer */
  uint32                  uContinuousSplashDataSize;               /* Size of data in the continous splash buffer */
  CHAR8                   pSupportedPanels[PANEL_LIST_STR_LEN_MAX];/* concatenated list of supported panels*/
} Display_ABLContextType;


/*=========================================================================
     Global Variables
==========================================================================*/
/*
* Display override parameters
*/
Display_ABLContextType gsABLContext;

/*=========================================================================
     Local Static Functions
==========================================================================*/

/****************************************************************************
*
** FUNCTION: LocalAsciiStrnCat()
*/
/*!
* \brief
*   Helper function to concatenate strings upto limit and ignore further
*   characters.
*
* \param [in] pDest          - Destination string
*        [in] uLimit         - Max length for dest
*        [in] pSrc           - Source string
*
* \retval available chars in dest
*
****************************************************************************/

static uint32 LocalAsciiStrnCat(CHAR8 *pDest, uint32 uLimit, CHAR8 *pSrc)
{
  uint32 uSize  = AsciiStrLen(pSrc);
  uint32 uStart = AsciiStrLen(pDest);
  uint32 uAvail = 0;

  if (uLimit > (uStart + 1))
  {
    uAvail = uLimit - (uStart + 1); // 1 termination char
  }

  /* Check if there is enough size available */
  if ( uSize > uAvail )
  {
    //pSrc too big - will be truncated
    DEBUG((EFI_D_WARN, "DisplayABLInterface: Not enough room available for strcat: will truncate <%a> avail %d reqd %d\n",
           pSrc, uAvail, uSize));

    uSize = uAvail;
  }

  if (0 < uAvail)
  {
    /* AsciiStnCpy will copy pSrc and the fill the next byte with zero */
    AsciiStrnCpy(pDest+uStart, pSrc, uSize+1);
    
    uAvail -= uSize;
  }
  
  return uAvail;
}

/****************************************************************************
*
** FUNCTION: LocalAsciiPrintConfig()
*/
/*!
* \brief
*   Helper function to append configuration string. Converts num to ascii and
*   then concatenates to pDest
*
* \param [in] pDest          - Destination string
*        [in] uLimit         - Max length for pDest
*        [in] iNum           - configuration index
*
* \retval None
*
****************************************************************************/
static void LocalAsciiPrintConfig(CHAR8 *pDest, uint32 uLimit, int32 iNum)
{
  /* config ranges from 0 - 99 */
  if ((0 <= iNum)  && 
      (100 > iNum)) 
  {
    uint32 i       = 0;
    uint32 uDigit;
    CHAR8  str[3];

    MDP_OSAL_MEMZERO(str, sizeof(str));
    
    uDigit = iNum / 10;
    
    if (0 < uDigit)
    {
      str[i++] = '0'+uDigit;
    }
    
    uDigit   = iNum - (10 * uDigit);
    str[i++] = '0' + uDigit;
    str[i]   = 0;

    LocalAsciiStrnCat(pDest, uLimit, ":config");
    LocalAsciiStrnCat(pDest, uLimit, str);
  } 
}

/****************************************************************************
*
** FUNCTION: LocalAsciiTrim()
*/
/*!
* \brief
*   Helper function to remove leading spaces in ascii string
*
* \param [in] pSrc     - pointer to string
*
* \retval Trimmed ascii string or NULL if input is NULL
*
****************************************************************************/
static CHAR8* LocalAsciiTrim(CHAR8* pStr)
{
  if (NULL != pStr)
  {
    /* remove leading spaces, if any */
    while (' ' == *pStr)
    {
      pStr++;
    }
  }
  
  return pStr;
}

/****************************************************************************
*
** FUNCTION: GetTokenEnd()
*/
/*!
* \brief
*   Helper function to find the index of specific tokens inside string
*
* \param [in] pString        - input string to look for delimiters
*
* \retval pointer to delimiter or NULL if not found
*
****************************************************************************/
static CHAR8* GetTokenEnd(const CHAR8 *pString)
{
  CHAR8 *pHash  = NULL;
  CHAR8 *pColon = NULL;
  CHAR8 *pOut   = NULL;

  /* ':' and '#' are delimiters in the string */
  pColon = AsciiStrStr((CHAR8 *) pString, ":");
  pHash  = AsciiStrStr((CHAR8 *) pString, "#");

  if ((NULL != pColon) && 
      (NULL != pHash))
  {
    pOut = ((pColon < pHash) ? pColon : pHash);
  }
  else if (NULL != pColon)
  {
    pOut = pColon;
  }
  else if (NULL != pHash)
  {
    pOut = pHash;
  }
  
  return pOut;
}

/****************************************************************************
*
** FUNCTION: LookupPanelByName()
*/
/*!
* \brief
*   Helper function to look up panel name inside the global DT array 
*
* \param [in] pShortName   - short name of the panel
*
* \retval pointer to DT info struct or NULL if not found
*
****************************************************************************/
static const PanelInfoType* LookupPanelByName(CHAR8 *pShortName)
{
  const PanelInfoType    *pDT            = NULL;
  Display_ABLContextType *pABLContext    = GET_ABL_CONTEXT();
    
  if ((NULL != pShortName) &&
      (NULL != pABLContext->pDTInfoArray))
  {
    uint32      i     = 0;
    uint32      uLen  = AsciiStrLen(pShortName);

    while (MDPPLATFORM_PANEL_NONE != pABLContext->pDTInfoArray[i].ePanel)
    {
      if((uLen == AsciiStrLen( pABLContext->pDTInfoArray[i].name)) &&
         (0    == AsciiStrnCmp(pABLContext->pDTInfoArray[i].name, pShortName, uLen)))
      {
        /* match found */
        pDT = &(pABLContext->pDTInfoArray[i]);
        break;
      }
      i++;
    }
  }
 
  return pDT;
}


/****************************************************************************
*
** FUNCTION: UpdateDisplayParams()
*/
/*!
* \brief
*   Helper function to update display params struct with selected panel info
*
* \param Index of selected panel
*
* \retval None
*
****************************************************************************/
static void UpdateDisplayParams(MDPPlatformPanelType  eSelected)
{
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();
  uint32                  i           = 0;
    
  if (NULL == pABLContext->pDTInfoArray)
  {
    //This is NULL during XBL RAMDUMP. So just ignore and return.
    MDP_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DT info is null pointer\n");
  }
  else
  {
    while (MDPPLATFORM_PANEL_NONE != pABLContext->pDTInfoArray[i].ePanel)
    {
      if (eSelected == pABLContext->pDTInfoArray[i].ePanel)
      {
        MDPPlatformParams    sPlatformParams;
        MDP_Status           eMDPStatus;

        /* match found */
        pABLContext->sABLParams.sPrimary.psDTInfo = &(pABLContext->pDTInfoArray[i]);
        AsciiStrnCpy(pABLContext->sABLParams.sPrimary.shortName, pABLContext->pDTInfoArray[i].name, DISPLAY_PANEL_NAME_MAX_LEN);

        MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
        //get panel support flags
        sPlatformParams.sPanelSupport.ePanel     = pABLContext->sABLParams.sPrimary.psDTInfo->ePanel;
        sPlatformParams.sPanelSupport.uModeIndex = pABLContext->sABLParams.sPrimary.eTopologyCfg;

        if (MDP_STATUS_OK != (eMDPStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY,
                                                                MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS,
                                                                &sPlatformParams)))
        {
          DEBUG((EFI_D_ERROR, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS) failed with returned error %d\n",
            eMDPStatus));
        }
        else
        {
          pABLContext->sABLParams.uFlags                      |= sPlatformParams.sPanelSupport.uFlags;
          pABLContext->sABLParams.sPrimary.uSelectedModeFlags |= sPlatformParams.sPanelSupport.uFlags;
        }
        break;
      }
      i++;
    }
  }

}

/****************************************************************************
*
** FUNCTION: ParsePanelOverrideCommand()
*/
/*!
* \brief
*   Helper function to parse and extract params from panel override string
*
* \param [in]  pPanelOverrideCmd - panel override command from ABL
*        [out] pABLParams        - display override params
*
* \retval bool32 - TRUE: panel override enabled, FALSE: disable panel override, using default panel
*
****************************************************************************/
static bool32 ParsePanelOverrideCommand(const char *pPanelOverrideCmd, Display_ABLParamsType *pABLParams)
{
  char    *pStr           = NULL;
  char    *pStrTmp        = NULL;
  char    *pOverride      = (char*) pPanelOverrideCmd;
  bool32   bPanelOverride = FALSE;
  int32 len;

  if ((NULL == pABLParams) ||
      (NULL == (pOverride = LocalAsciiTrim(pOverride))))
  {
    DEBUG((EFI_D_ERROR, "DisplayABLInterface: Invalid arguments\n"));
  }
  /* check for special configuration */
  else if(0 == AsciiStrnCmp(pOverride, NO_PANEL_CONFIG, AsciiStrLen(NO_PANEL_CONFIG)))
  {
    /* special case: if fastboot oem panel name is "none" then enable SW render and pass empty string to kernel */
    bPanelOverride      = TRUE;
    pABLParams->uFlags |= DISP_MODE_SKIP_BOOTLOADER|DISP_MODE_PANEL_NONE;
  }
  else
  {
    MDP_OSAL_MEMZERO(pABLParams, sizeof(Display_ABLParamsType));

    /* Primary panel string */
    pStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_PRIM);
    if (NULL != pStr) 
    {
      /*
       * Parse the primary panel for cases where 'prim' prefix
       * is present in the fastboot oem command before primary
       * panel string.
       * Examples:
       * 1.) fastboot oem select-display-panel prim:jdi_1080p_video:sec:sharp_1080p_cmd
       * 2.) fastboot oem select-display-panel prim:jdi_1080p_video:skip:sec:sharp_1080p_cmd
       * 3.) fastboot oem select-display-panel prim:jdi_1080p_video:disable:sec:sharp_1080p_cmd
       * 4.) fastboot oem select-display-panel prim:jdi_1080p_video:skip#sim:sec:sharp_1080p_cmd
       */
      pStr += PANEL_CMD_MARKER_PRIM_LEN;
      pStrTmp = GetTokenEnd((const char*) pStr);
      if (NULL == pStrTmp)
      {
        pStrTmp = pStr + AsciiStrLen(pStr);
      }
      len = pStrTmp - pStr;
      if (len > (DISPLAY_PANEL_NAME_MAX_LEN - 1) )
      {
        DEBUG((EFI_D_WARN, "DisplayABLInterface: Panel name is too long %d vs max %d\n", len, DISPLAY_PANEL_NAME_MAX_LEN - 1)); 
        len = DISPLAY_PANEL_NAME_MAX_LEN - 1;
      }
      
      AsciiStrnCpy(pABLParams->sPrimary.shortName,pStr, len);
      
      pABLParams->sPrimary.shortName[DISPLAY_PANEL_NAME_MAX_LEN-1] = 0;
      
    } 
    else 
    {
      /*
       * Check if secondary panel string is present.
       * The 'prim' prefix definitely needs to be present
       * to specify primary panel for cases where secondary panel
       * is also specified in fastboot oem command. Otherwise, it
       * becomes tough to parse the fastboot oem command for primary
       * panel. If 'sec' prefix is used without 'prim' prefix, it
       * means the default panel needs to be picked as primary panel.
       * Example:
       * fastboot oem select-display-panel sec:sharp_1080p_cmd
       */
      pStr = AsciiStrStr((char *) pOverride, PANEL_CMD_MARKER_SEC);
      if (NULL == pStr) 
      {
        /*
         * This code will be executed for cases where the
         * secondary panel is not specified i.e., single/split
         * DSI cases.
         * Examples:
         * 1.) fastboot oem select-display-panel jdi_1080p_video
         * 2.) fastboot oem select-display-panel sharp_1080p_cmd:skip
         * 3.) fastboot oem select-display-panel sharp_1080p_cmd:disable
         * 4.) fastboot oem select-display-panel sim_cmd_panel#sim-swte
         */
        pStr = GetTokenEnd(pOverride);
        if (NULL != pStr) 
        {
          len = pStr - pOverride;
        }
        else
        {
          len = AsciiStrLen(pOverride);
        }
        
        if (len > (DISPLAY_PANEL_NAME_MAX_LEN - 1) )
        {
          DEBUG((EFI_D_WARN, "DisplayABLInterface: Panel name is too long %d vs max %d\n", len, DISPLAY_PANEL_NAME_MAX_LEN - 1));
          len = DISPLAY_PANEL_NAME_MAX_LEN - 1;
        }
        AsciiStrnCpy(pABLParams->sPrimary.shortName, pOverride, len);
      }
    }

    /* Use short names to look up DT info params */
    pABLParams->sPrimary.psDTInfo = LookupPanelByName(pABLParams->sPrimary.shortName);

    if (NULL == pABLParams->sPrimary.psDTInfo)
    {
      /* Cannot find such a panel name, disable panel override and fall back to default panel*/
      DEBUG((EFI_D_WARN, "Panel specified for overrride cannot be found. Falling back to default panel\n"));
      bPanelOverride = FALSE;
    }
    else
    {
      /*
       * Secondary panel string.
       * This is relatively simple. The secondary panel string gets
       * parsed if the 'sec' prefix is present.
       */
      pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SEC);
      if (NULL != pStr)
      {

        pStr += PANEL_CMD_MARKER_SEC_LEN;
        pStrTmp = GetTokenEnd((const char*)pStr);
        if (NULL == pStrTmp)
        {
          pStrTmp = pStr + AsciiStrLen(pStr);
        }
        len = pStrTmp - pStr;
        if (len > (DISPLAY_PANEL_NAME_MAX_LEN - 1))
        {
          DEBUG((EFI_D_WARN, "DisplayABLInterface: Panel name is too long %d vs max %d\n", len, DISPLAY_PANEL_NAME_MAX_LEN - 1));
          len = DISPLAY_PANEL_NAME_MAX_LEN - 1;
        }
        AsciiStrnCpy(pABLParams->sSecondary.shortName, pStr, len);
        pABLParams->sSecondary.shortName[DISPLAY_PANEL_NAME_MAX_LEN - 1] = 0;
        
        /* Use short names to look up DT info params */
        pABLParams->sSecondary.psDTInfo = LookupPanelByName(pABLParams->sSecondary.shortName);

        /* Topology configuration for secondary panel */
        pABLParams->sSecondary.eTopologyCfg = DISP_TOPOLOGY_CONFIG_NONE;

        pStrTmp = AsciiStrStr((char *)pStr, PANEL_CMD_MARKER_CONFIG);
        if (NULL != pStrTmp)
        {
          pABLParams->sSecondary.eTopologyCfg = AsciiStrDecimalToUintn((const char*)(pStrTmp + PANEL_CMD_MARKER_CONFIG_LEN)) + 1;
        }
      }
      else
      {
        pABLParams->sSecondary.shortName[0] = '\0';
      }

      /* Topology configuration for primary panel */
      pABLParams->sPrimary.eTopologyCfg = DISP_TOPOLOGY_CONFIG_NONE;

      pStrTmp = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_CONFIG);
      if ((NULL != pStrTmp) &&
         ((NULL == pStr) ||
         ((NULL != pStr) &&
         (pStrTmp < pStr))))
      {
        pABLParams->sPrimary.eTopologyCfg = AsciiStrDecimalToUintn((const char*)(pStrTmp + PANEL_CMD_MARKER_CONFIG_LEN)) + 1;
      }

      /* Skip LK configuration */
      pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SKIP);
      if (NULL != pStr)
      {
        pABLParams->uFlags |= DISP_MODE_SKIP_BOOTLOADER;
      }

      /* Cont. splash status */
      pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_DISABLE);
      if (NULL != pStr)
      {
        pABLParams->uFlags |= DISP_MODE_DISABLE_CONTINUOUS_SPLASH;
      }

      /* Interposer card to swap DSI0 and DSI1 lanes */
      pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SWAP);
      if (NULL != pStr)
      {
        pABLParams->uFlags |= DISP_MODE_SWAP_DSI_CONTROLLER;
      }

      /* DSI PLL source */
      pABLParams->ePllOverride = PLL_OVERRIDE_NONE;
      pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_PLL0);
      if (NULL != pStr)
      {
        pABLParams->ePllOverride = PLL_OVERRIDE_PLL0;
      }
      else
      {
        pStr = AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_PLL1);
        if (NULL != pStr)
        {
          pABLParams->ePllOverride = PLL_OVERRIDE_PLL1;
        }
      }

      /* Simulator status */
      pABLParams->eSimMode = PANELSIM_NONE;
      if (NULL != AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SIM_HWTE))
      {
        pABLParams->eSimMode = PANELSIM_HWTE;
      }
      else if (NULL != AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SIM_SWTE))
      {
        pABLParams->eSimMode = PANELSIM_SWTE;
      }
      else if (NULL != AsciiStrStr((char *)pOverride, PANEL_CMD_MARKER_SIM))
      {
        pABLParams->eSimMode = PANELSIM_MODE;
      }

      /* disable cont splash when booting in simulator mode */
      if (PANELSIM_NONE != pABLParams->eSimMode)
      {
        pABLParams->uFlags |= DISP_MODE_DISABLE_CONTINUOUS_SPLASH;
      }

      bPanelOverride = TRUE;
    }
  }

  return bPanelOverride;
}
/****************************************************************************
*
** FUNCTION: UpdatePanelConfiguration()
*/
/*!
* \brief
*   Helper to build panel configuration string
*
* \param [in]  eSelected  - ID of panel selected by Display driver
*        [out] pConfigStr - Panel configuration string
*
* \retval None
*
****************************************************************************/
static void UpdatePanelConfiguration(MDPPlatformPanelType  eSelected, CHAR8 *pConfigStr)
{
  CHAR8                    *pDsiIdStr            = DSI_CONTROLLER_0_STRING;
  CHAR8                    *pPanelNodeStr        = NULL;
  CHAR8                    *pSlavePanelNodeStr   = NULL;
  CHAR8                    *pSimModeStr          = NULL;
  uint32                    panelMode            = 0;
  CHAR8                    *pSecCtrlString       = NULL;
  CHAR8                    *pPllSrcStr           = NULL;
  CHAR8                     primCfgName[10]      = "\0";
  CHAR8                     slaveCfgName[10]     = "\0";      /* config[0-99]   */
  Display_ABLContextType   *pABLContext          = GET_ABL_CONTEXT();
  Display_ABLParamsType    *pABLParams           = &pABLContext->sABLParams;
  
  /* Get updated display params */
  UpdateDisplayParams(eSelected);
  
  if (DISP_MODE_PANEL_NONE & pABLParams->uFlags)
  {
    /* Panel override with NONE, no string will be generated */
  }
  else if ((NULL != pABLParams->sPrimary.psDTInfo) && 
      (DISP_INTF_HDMI == pABLParams->sPrimary.psDTInfo->eInterface))
  {
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, DISPLAY_CMDLINE_PREFIX);
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, HDMI_CONTROLLER_STRING);
  }
  else if((NULL == pABLParams->sPrimary.psDTInfo)   &&
          (NULL == pABLParams->sSecondary.psDTInfo))
  {
    /* both primary & secondary are not present */
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, DISPLAY_CMDLINE_BYPASS_PREFIX);
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, DSI_CONTROLLER_0_STRING);
  }
  else
  {
  
    /* String format 0:<intf>:<intf_config>[:<topology_cfg>]
    
    intf: 
      dsi:<id> or
      hdmi
      Ex: dsi:0
      
    intf_config:
      for DSI: <dt_label>
      Ex: qcom,mdss_dsi_nt35597_wqxga_video
    
    topology_config(optional):
      select one of many variants available for the intf_config
      Ex: config0 
      
    Complete ex:
      0:dsi:0:qcom,mdss_dsi_nt35597_wqxga_video:dsi:1:qcom,mdss_dsi_nt35597_wqxga_video:config0
    
    */
    
    if (NULL != pABLParams->sPrimary.psDTInfo)
    {
      pPanelNodeStr = (CHAR8*) pABLParams->sPrimary.psDTInfo->DTLabel;
      
      if(pABLParams->sPrimary.uSelectedModeFlags & DISP_MODE_DUAL_DSI)
      {
        pSlavePanelNodeStr = (CHAR8*) pABLParams->sPrimary.psDTInfo->DTLabel;
        panelMode       = DISP_MODE_DUAL_DSI;
      }
      else
      {
        panelMode = 0;
      }
    }
    else if (NULL != pABLParams->sSecondary.psDTInfo)
    {
      /* Set primary to None */
      pPanelNodeStr = NO_PANEL_CONFIG;
      panelMode = 0;
    }
    
    if (0 < AsciiStrLen(pABLParams->sSecondary.shortName))
    {
      if (panelMode & (DISP_MODE_DUAL_DSI | DISP_MODE_SPLIT_DISPLAY | DISP_MODE_PING_PONG_SPLIT))
      {
        DEBUG((EFI_D_WARN, "Invalid config: Primary panel is split DSI and still secondary panel passed\n"));
        /* ignore secondary */
      }
      else if ((NULL != pABLParams->sSecondary.psDTInfo)     && 
               (pABLParams->sSecondary.uSelectedModeFlags & DISP_MODE_DUAL_DSI))
      {
        DEBUG((EFI_D_WARN, "Invalid Config: secondary panel can't be split DSI.Continue with primary panel\n"));
        /* ignore secondary */
      } 
      else if(NULL != pABLParams->sSecondary.psDTInfo)
      {
        pSlavePanelNodeStr = (CHAR8*) pABLParams->sSecondary.psDTInfo->DTLabel;
      }
    }
    
    MDP_OSAL_MEMZERO(pABLParams->dsiConfigStr, sizeof(pABLParams->dsiConfigStr));

    /* Check for the DSI configuration */
    if ((NULL != pSlavePanelNodeStr) &&
        (panelMode & (DISP_MODE_DUAL_DSI | DISP_MODE_SPLIT_DISPLAY | DISP_MODE_PING_PONG_SPLIT)))
    {
      LocalAsciiStrnCat(pABLParams->dsiConfigStr, DISPLAY_DSI_CONFIG_MAX_LEN, SPLIT_DSI_STRING);
    }
    else if (NULL != pSlavePanelNodeStr)
    {
      LocalAsciiStrnCat(pABLParams->dsiConfigStr, DISPLAY_DSI_CONFIG_MAX_LEN, DUAL_DSI_STRING);
    }
    else
    {
      LocalAsciiStrnCat(pABLParams->dsiConfigStr, DISPLAY_DSI_CONFIG_MAX_LEN, SINGLE_DSI_STRING);
      pSlavePanelNodeStr = NO_PANEL_CONFIG;
    }
    
    pSecCtrlString = DSI_1_STRING;
    
    if ((pABLParams->uFlags & DISP_MODE_SKIP_BOOTLOADER)                                         &&
        (0 == AsciiStrnCmp(DUAL_DSI_STRING, pABLParams->dsiConfigStr, AsciiStrLen(DUAL_DSI_STRING))) &&
        (PLL_OVERRIDE_NONE != pABLParams->ePllOverride)) 
    {
      DEBUG((EFI_D_WARN, "Dual DSI config detected! Use default PLL\n"));
      pABLParams->ePllOverride = PLL_OVERRIDE_NONE;
    }
    
    if ((PLL_OVERRIDE_NONE == pABLParams->ePllOverride) &&
        (NULL != pABLParams->sPrimary.psDTInfo))
    {
      pABLParams->ePllOverride = pABLParams->sPrimary.psDTInfo->uPLLOverride;
    }

    if (PLL_OVERRIDE_NONE != pABLParams->ePllOverride)
    {
      if (PLL_OVERRIDE_PLL0 == pABLParams->ePllOverride)
      {
        pPllSrcStr = PANEL_CMD_MARKER_PLL0;
      }
      else
      {
        pPllSrcStr = PANEL_CMD_MARKER_PLL1;
      }
    }
    

    if (pABLParams->uFlags & DISP_MODE_USE_DSI1)
    {
      //Special case: Use DSI1 for primary panel & set DSI0 to none
      //eg 2k DSC panel is connected to DSI1
      pDsiIdStr          = DSI_CONTROLLER_1_STRING;
      pSecCtrlString     = DSI_0_STRING;
      pSlavePanelNodeStr = NO_PANEL_CONFIG;
    }
    
    switch(pABLParams->eSimMode)
    {
    case PANELSIM_MODE:
      pSimModeStr = SIM_MODE_STRING;
      break;
    case PANELSIM_HWTE:
      pSimModeStr = SIM_HWTE_STRING;
      break;
    case PANELSIM_SWTE:
      pSimModeStr = SIM_SWTE_STRING;
      break;
    case PANELSIM_NONE:
    default:
      pSimModeStr = NULL;
      break;
    }

    /* Update the topology if the config has been specified */
    if ((DISP_TOPOLOGY_CONFIG_NONE == pABLParams->sPrimary.eTopologyCfg ) &&
        (NULL != pABLParams->sPrimary.psDTInfo))
    {
      pABLParams->sPrimary.eTopologyCfg = pABLParams->sPrimary.psDTInfo->uConfigNum ;
    }
    LocalAsciiPrintConfig(primCfgName, 10, pABLParams->sPrimary.eTopologyCfg -1);
    
    /*Update panel attribute for PP Split info */
    if(DISP_MODE_PING_PONG_SPLIT & pABLParams->sPrimary.uSelectedModeFlags)
    {
      MDP_Panel_AttrType *pDisplayInfo = MDP_GET_DISPLAYINFO(MDP_DISPLAY_PRIMARY);

      pDisplayInfo->eDisplayFlags |= MDP_PANEL_FLAG_ENABLE_PINGPONG_SPLIT;
    }
    
    /* in split-dsi, primary and slave panel share same topology config */
    if (0 == AsciiStrnCmp(SPLIT_DSI_STRING, pABLParams->dsiConfigStr, AsciiStrLen(SPLIT_DSI_STRING)))
    {
      LocalAsciiStrnCat(slaveCfgName, 10, primCfgName);
    }

    if (0 == AsciiStrnCmp(DUAL_DSI_STRING, pABLParams->dsiConfigStr, AsciiStrLen(DUAL_DSI_STRING)))
    {
      LocalAsciiPrintConfig(slaveCfgName, 10, pABLParams->sSecondary.eTopologyCfg -1);
    }
    
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, DISPLAY_CMDLINE_PREFIX);
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pDsiIdStr);
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pPanelNodeStr);
    /* writeout primary topology config */
    if (0 < AsciiStrLen(primCfgName)) 
    {
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, primCfgName);
    }
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pSecCtrlString);
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pSlavePanelNodeStr);
    
    /* writeout slave panel, split-dsi, or secondary panel, dual-dsi, topology config */
    if (0 < AsciiStrLen(slaveCfgName)) 
    {
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, slaveCfgName);
    }
    
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, DSI_CFG_STRING);
    LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pABLParams->dsiConfigStr);
    if (NULL != pPllSrcStr) 
    {
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pPllSrcStr);
    }
    
    if (NULL != pSimModeStr) 
    {
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, SIM_OVERRIDE);
      LocalAsciiStrnCat(pConfigStr, PANEL_CONFIG_STR_LEN_MAX, pSimModeStr);
    }
  }
}



/****************************************************************************
*
** FUNCTION: CheckTargetPanelSupport()
*/
/*!
* \brief
*   Helper function to query Platform Lib for a list of supported panels and
*   set boot service variables to inform ABL
*
* \param None
*
* \retval None
*
****************************************************************************/
static void CheckTargetPanelSupport()
{
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();
  EFI_STATUS              eStatus;
  MDP_Status              eMDPStatus;
  MDPPlatformParams       sPlatformParams;
  
  
  MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
 
  if (MDP_STATUS_OK != (eMDPStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_GETPANELDTINFO, &sPlatformParams)))
  {
    DEBUG((EFI_D_WARN, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_GETPANELDTINFO) failed! Returned %d\n", eMDPStatus));
  }
  else
  {
    CHAR8 *pPanels     = pABLContext->pSupportedPanels;
    CHAR8 *szSeparator = ",";
    uint32 uPanelCount = 0;
    PanelInfoType *psPanelDTInfo = sPlatformParams.psPanelDTInfo;
    /*
    The received panel list is sorted by panel IDs
    Go through the panel mapping to lookup names.
    */
    if (NULL != psPanelDTInfo)
    {
      /* Initialize to Zero */
      MDP_OSAL_MEMZERO(pPanels, PANEL_LIST_STR_LEN_MAX);

      while (MDPPLATFORM_PANEL_NONE != psPanelDTInfo[uPanelCount].ePanel)
      {
        if (0 < uPanelCount)
        {
          /* separator */
          LocalAsciiStrnCat(pPanels, PANEL_LIST_STR_LEN_MAX, szSeparator);
        }

        /* append it to string */
        LocalAsciiStrnCat(pPanels, PANEL_LIST_STR_LEN_MAX, (CHAR8*)psPanelDTInfo[uPanelCount].name);
        uPanelCount++;
      }

      /* Save Panel DT info to ABL Context */
      pABLContext->pDTInfoArray = psPanelDTInfo;
    }

    if (EFI_SUCCESS != (eStatus = MDP_SetBootServiceVariable(DISPVAR_SUPPORTED_PANEL_COUNT, &uPanelCount, sizeof(uPanelCount), 0)))
    {
      DEBUG((EFI_D_WARN,"MDPLib: Failed to set boot service variable <%s>. Returned %d\n", DISPVAR_SUPPORTED_PANEL_COUNT, eStatus));
    }
    
    if (EFI_SUCCESS != (eStatus = MDP_SetBootServiceVariable(DISPVAR_SUPPORTED_PANEL_LIST, pPanels, AsciiStrSize(pPanels), 0)))
    {
      DEBUG((EFI_D_WARN,"MDPLib: Failed to set boot service variable <%s>. Returned %d\n", DISPVAR_SUPPORTED_PANEL_LIST, eStatus));
    }
  }
}

/****************************************************************************
*
** FUNCTION: CheckPanelOverride()
*/
/*!
* \brief
*   Helper function to check if panel override is set and parse the override
*   string, if set.
*
* \param  None
*
* \retval None
*
****************************************************************************/
static void CheckPanelOverride()
{

  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();
  UINTN                   uLength     = 0;
  CHAR8                   panelOverrideStr[PANEL_OVERRIDE_STR_LEN_MAX];

  MDP_OSAL_MEMZERO(panelOverrideStr, sizeof(panelOverrideStr));
  
  uLength = sizeof(panelOverrideStr);

  /* Check Panel Override
  */
    DEBUG((EFI_D_ERROR, "CheckPanelOverride\n"));
  if (EFI_SUCCESS == MDP_Display_GetVariable(DISPVAR_PANEL_OVERRIDE, (UINT8 *)panelOverrideStr, &uLength, 0))
  {
    /* Parse String - Since this is an override scenario print the command to log*/
    DEBUG((EFI_D_ERROR, "Panel override command: <%a>\n", panelOverrideStr));
    
    /*Panel override string */
    pABLContext->bOverride  = ParsePanelOverrideCommand(panelOverrideStr, &pABLContext->sABLParams);
  }
}


/*=========================================================================
      Public APIs
==========================================================================*/


/****************************************************************************
*
** FUNCTION: Display_ABL_Initialize()
*/
/*!
* \brief
*   Initialize ABL interface
*
* \param None
*
* \retval None
*
****************************************************************************/
void Display_ABL_Initialize(void)
{ 
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();

  MDP_OSAL_DELAYMS(100);
  /* initialize override flag */
  MDP_OSAL_MEMZERO(pABLContext, sizeof(Display_ABLContextType));

  /* get list of supported panels & build DT info array */
  CheckTargetPanelSupport();
  
  /* Check panel override */
  CheckPanelOverride();

}

/****************************************************************************
*
** FUNCTION: Display_ABL_GetParams()
*/
/*!
* \brief
*   Helper to get display override params
*
* \param None
*
* \retval pointer to Display_ABLParamsType or NULL if not set
*
****************************************************************************/
Display_ABLParamsType* Display_ABL_GetParams(void)
{
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();
  Display_ABLParamsType  *pABLParams  = NULL;

  if (pABLContext->bOverride)
  {
    pABLParams = &pABLContext->sABLParams;
  }
  return pABLParams;
}


/****************************************************************************
*
** FUNCTION: Display_ABL_SetPanelConfiguration()
*/
/*!
* \brief
*   Send panel configuration string to ABL
*
* \param Index of selected panel
*
* \retval None
*
****************************************************************************/
void Display_ABL_SetPanelConfiguration(MDPPlatformPanelType  eSelected)
{

  EFI_STATUS  eStatus;
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();
  CHAR8*                  pConfigStr  = pABLContext->pPanelConfig;

  MDP_OSAL_MEMZERO(pConfigStr, sizeof(pABLContext->pPanelConfig));

  UpdatePanelConfiguration(eSelected, pConfigStr);

  /* Set panel configuration variable */
  if (EFI_SUCCESS != (eStatus = MDP_SetBootServiceVariable(DISPVAR_PANEL_CONFIGURATION, pConfigStr, AsciiStrLen(pConfigStr)+1, 0)))
  {
    DEBUG((EFI_D_WARN,"MDPLib: Failed to set boot service variable <%s>. Returned %d\n", DISPVAR_PANEL_CONFIGURATION, eStatus));
  }
}

/****************************************************************************
*
** FUNCTION: Display_ABL_CheckPanelSkip()
*/
/*!
* \brief
*   Check for panel override and if the overridden panel is supported in 
*   bootloader
*
* \param None
*
* \retval TRUE if panel configuration is to be skipped in bootloader
*
****************************************************************************/
bool32 Display_ABL_CheckPanelSkip()
{
  bool32                  bSkip       = FALSE;
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();

  if (TRUE == pABLContext->bOverride)
  {
    if (pABLContext->sABLParams.uFlags & DISP_MODE_SKIP_BOOTLOADER)
    {
      bSkip = TRUE;
    }
    else if (NULL != pABLContext->sABLParams.sPrimary.psDTInfo)
    {
      MDPPlatformParams    sPlatformParams;
      MDP_Status           eMDPStatus;
      
      MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

      // skip = FALSE only if a valid panel is found and is supported by bootloader
      // check if skip is forced by the panel override command

      //get panel support flags
      sPlatformParams.sPanelSupport.ePanel = pABLContext->sABLParams.sPrimary.psDTInfo->ePanel;
      sPlatformParams.sPanelSupport.uModeIndex = pABLContext->sABLParams.sPrimary.eTopologyCfg;

      if (MDP_STATUS_OK != (eMDPStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, 
                                                              MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS,
                                                              &sPlatformParams)))
      {
        DEBUG ((EFI_D_ERROR, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS) failed! Returned %d\n", 
                eMDPStatus)); 
      }
      else
      {

        /* set override flags if any */
        pABLContext->sABLParams.uFlags |= sPlatformParams.sPanelSupport.uFlags;
        if (DISP_MODE_SKIP_BOOTLOADER & pABLContext->sABLParams.uFlags)
        {
          bSkip = TRUE;
        }
      }
    }
  }
  return bSkip;
}


/****************************************************************************
*
** FUNCTION: Display_ABL_GetDisplayCommandLine()
*/
/*!
* \brief
*   Gets the pointer to the panel configuration string & string length 
*
* \param [out] ppCmdLine - pointer to command line string
*        [out] pLen      - Ascii length of the string
*
* \retval None
*
****************************************************************************/
void Display_ABL_GetDisplayCommandLine(CHAR8 **ppCmdLine, UINT32 *pLen)
{
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();

  /* To make sure we dont go overrun the string */
  pABLContext->pPanelConfig[PANEL_CONFIG_STR_LEN_MAX - 1] = '\0';

  /* Set command line & len */
  *ppCmdLine = pABLContext->pPanelConfig;
  *pLen      = AsciiStrLen(pABLContext->pPanelConfig);
  
}

/****************************************************************************
*
** FUNCTION: Display_ABL_SetContinuousSplashInfo()
*/
/*!
* \brief
*   Saves the continuous splash address in ABL context
*
* \param [in] uAddr - Splash buffer address
*        [in] uSize - Splash buffer size in bytes
*
* \retval None
*
****************************************************************************/
void Display_ABL_SetContinuousSplashInfo(UINT32 uAddr, UINT32 uSize)
{
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();

  pABLContext->uContinuousSplashAddress  = uAddr;
  pABLContext->uContinuousSplashDataSize = uSize;
}

/****************************************************************************
*
** FUNCTION: Display_ABL_GetContinuousSplashInfo()
*/
/*!
* \brief
*   Retrieves the continuous splash buffer info
*
* \param [out] pAddr - Splash buffer address
*        [out] pSize - Splash buffer size in bytes
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_ABL_GetContinuousSplashInfo(UINT32 *pAddr, UINT32 *pSize)
{
  EFI_STATUS              eStatus     = EFI_SUCCESS;
  Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();

  if ((NULL == pAddr) ||
      (NULL == pSize))
  {
    DEBUG((EFI_D_WARN, "Display_ABL_GetContinuousSplashInfo: Invalid arguments\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    *pAddr = pABLContext->uContinuousSplashAddress;
    *pSize = pABLContext->uContinuousSplashDataSize;
  }
  
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: Display_ABL_SetProperty()
*/
/*!
* \brief
*   Set a property on Display UEFI
*
* \param [in] PropertyType - Property identifier
*        [in] Data         - Pointer to data buffer
*        [in] Size         - Size of valid data in bytes
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_ABL_SetProperty (EFI_DISPLAY_ABL_PROPERTY_TYPE   ePropertyType,
                                    void                           *pData,
                                    UINT32                          uDataSize )
{
  EFI_STATUS eStatus = EFI_SUCCESS;
  switch(ePropertyType)
  {
  case EFI_DISPLAY_ABL_DEVICE_TREE_ADDR:
    {
      /* Locate device tree at the address provided and update display specific nodes */
      if ((NULL == pData) ||
          (uDataSize != sizeof(void*)))
      {
        DEBUG((EFI_D_WARN, "Display: ABL set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else if(EFI_SUCCESS != (eStatus = MDP_UpdateDeviceTree(pData)))
      {
        DEBUG((EFI_D_WARN, "Display: Device tree update failed with %d\n", eStatus));
      }
    }
    break;

  case EFI_DISPLAY_ABL_PANEL_OVERRIDE:
    {
      if ((NULL == pData) ||
          (0 == uDataSize))
      {
        DEBUG((EFI_D_WARN, "Display: ABL set property (id=%d) with invalid parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else if ( uDataSize > (PANEL_OVERRIDE_STR_LEN_MAX *sizeof(CHAR8)))
      {
        DEBUG((EFI_D_WARN,"Display: Panel override string is too long. Input %d, Max allowed %d\n", 
              uDataSize/sizeof(CHAR8), PANEL_OVERRIDE_STR_LEN_MAX));

        eStatus = EFI_INVALID_PARAMETER;
      }
      else if (EFI_SUCCESS != (eStatus = MDP_Display_SetVariable(DISPVAR_PANEL_OVERRIDE, 
                                                                 (UINT8 *)pData, 
                                                                 (uDataSize / (sizeof(CHAR8))),
                                                                 0)))
      {
        DEBUG((EFI_D_WARN,"Display: Failed to set boot service variable <%s>. Returned %d\n", DISPVAR_PANEL_OVERRIDE, eStatus));
      }
      else
      {
        eStatus = EFI_SUCCESS;
      }
    }
    break;

  default:
    eStatus = EFI_UNSUPPORTED;
  }
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: Display_ABL_GetProperty()
*/
/*!
* \brief
*   Set a property on Display UEFI
*
* \param [in]     Type            Property type
*        [out]    Data            Pointer to data structure
*        [in/out] DataSize        [in] Max size of data 
*                                 [out] Actual size of data 
*
* \retval EFI_STATUS
* EFI_SUCCESS              : Function returned successfully.
* EFI_INVALID_PARAMETER    : Parameter passed is incorrect.  
* EFI_UNSUPPORTED          : Parameter passed is not supported. 
* EFI_DEVICE_ERROR         : Physical device reported an error.
* EFI_BUFFER_TOO_SMALL     : Buffer to small to copy data into
*
****************************************************************************/
EFI_STATUS Display_ABL_GetProperty (EFI_DISPLAY_ABL_PROPERTY_TYPE   ePropertyType,
                                    void                           *pData,
                                    UINT32                         *pDataSize)
{
  EFI_STATUS eStatus = EFI_SUCCESS;
  switch(ePropertyType)
  {
  case EFI_DISPLAY_ABL_SUPPORTED_PANELS:
    {
      Display_ABLContextType *pABLContext = GET_ABL_CONTEXT();
      UINT32 Size                         = 0;

      if (NULL == pDataSize)
      {
        DEBUG((EFI_D_WARN, "Display: ABL get property (id=%d) with Null parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else if ( *pDataSize < (Size = AsciiStrSize(pABLContext->pSupportedPanels)))
      {
        *pDataSize = Size;
        eStatus   = EFI_BUFFER_TOO_SMALL;
      }
      else if (NULL == pData)
      {
        DEBUG((EFI_D_WARN, "Display: ABL get property (id=%d) with Null parameter!\n", ePropertyType));
        eStatus = EFI_INVALID_PARAMETER;
      }
      else 
      {
        MDP_OSAL_MEMCPY(pData, pABLContext->pSupportedPanels, Size);

        *pDataSize = Size;
        eStatus   = EFI_SUCCESS;
      }
    }
    break;

  default:
    eStatus = EFI_UNSUPPORTED;
  }
  return eStatus;
}


/****************************************************************************
*
** FUNCTION: Display_ABL_StorePLLCodes()
*/
/*!
* \brief
*   Display ABL to store pll codes
*
  @param  None
*
* \retval None
*
****************************************************************************/
void
Display_ABL_StorePLLCodes(void)
{
  UINT32               uSplashAddr          = 0;
  UINT32               uSplashSize          = 0;
  uintPtr              uPllCodesAddr        = 0;
  UINT32               uPllCodesMaxSize     = MDP_MAX_PLLCODES_SIZE;
  void                *pBuffer              = NULL;
  MDP_Status           eStatus              = MDP_STATUS_FAILED;
  MDP_PLLCodesInfo     sPllCodesInfo[MDP_MAX_NUM_DSI_DEVICE];
  
  /* Save PLL codes to last 4K of framebuffer for kernel to read */
  if((EFI_SUCCESS == Display_ABL_GetContinuousSplashInfo(&uSplashAddr, &uSplashSize)) &&
    (uSplashSize   > uPllCodesMaxSize))
  {
    uPllCodesAddr = uSplashAddr + uSplashSize;
    pBuffer       = (void*)uPllCodesAddr;

    if (sizeof(sPllCodesInfo) > uPllCodesMaxSize)
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "Error: Not enough splash memory to store pll codes\n");
    }
    else
    {
      uint32 i;
    
      MDP_OSAL_MEMSET(&sPllCodesInfo[0], 0, sizeof(sPllCodesInfo));
    
      for (i = 0; i < MDP_MAX_NUM_DSI_DEVICE; i++)
      {
        if (MDP_STATUS_OK == DSIDriver_GetCalibrationCodes(i, &sPllCodesInfo[i]))
        {
          eStatus = MDP_STATUS_OK;
        }
      }

      if (MDP_STATUS_OK == eStatus)
      {
        /* copy pll codes to begining of splash memory*/
        MDP_OSAL_MEMCPY((void *) pBuffer, sPllCodesInfo, sizeof(sPllCodesInfo));
      }
      else
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "Error: fail to get DSI pll codes\n");
      }
    }
  }
}

/****************************************************************************
*
** FUNCTION: Display_ABL_SetMode()
*/
/*!
* \brief
*   Render logo function implementation.
*   **NOTE** Adding this to have same EFI_QCOM_DISPLAY_UTILS_PROTOCOL protocol APIs as on ABL side. 
*
  @param[in]  psRenderLogoConfig        Config of clearing screen & overriding position.
*
* \retval EFI_STATUS
* EFI_SUCCESS                   : Function returned successfully.
* EFI_INVALID_PARAMETER         : Parameter passed is incorrect.  
* EFI_UNSUPPORTED               : Parameter passed is not supported. 
* EFI_DEVICE_ERROR              : Physical device reported an error.
*
****************************************************************************/
EFI_STATUS
Display_ABL_RenderLogo(
  IN EFI_DISPLAY_ABL_RENDERLOGO_CONFIG *psRenderLogoConfig)
{
  return EFI_NOT_FOUND;
}


/****************************************************************************
*
** FUNCTION: Display_ABL_SetMode()
*/
/*!
* \brief
*   Display ABL Protocol to set display mode: 
*   **NOTE** Adding this to have same EFI_QCOM_DISPLAY_UTILS_PROTOCOL protocol APIs as on ABL side. 
*
  @param[in]  DisplayId                 display id, can be either primary, secondary or external
  @param[in]  ModeNumber                Abstraction that defines the current video mode.
  @param[in]  Flags                     More info
*
* \retval EFI_STATUS
* EFI_SUCCESS                   : Function returned successfully.
* EFI_INVALID_PARAMETER         : Parameter passed is incorrect.  
* EFI_UNSUPPORTED               : Parameter passed is not supported. 
* EFI_DEVICE_ERROR              : Physical device reported an error.
*
****************************************************************************/
EFI_STATUS
Display_ABL_SetMode(
  IN  UINT32           DisplayId,
  IN  UINT32           ModeNum,
  IN  UINT32           Flags)
{
  return EFI_NOT_FOUND;
}

/**
  Display ABL Protocol implementation
 */

EFI_QCOM_DISPLAY_ABL_PROTOCOL  gQcomDisplayABLProtocolImplementation = 
{
  DISPLAY_ABL_REVISION,
  Display_ABL_SetProperty,
  Display_ABL_GetProperty,
  Display_ABL_RenderLogo,   //NOTE: Adding this to have same EFI_QCOM_DISPLAY_UTILS_PROTOCOL protocol APIs as on ABL side. 
  Display_ABL_SetMode,      //NOTE: Adding this to have same EFI_QCOM_DISPLAY_UTILS_PROTOCOL protocol APIs as on ABL side. 
  Display_ABL_SetVariable,
  Display_ABL_GetVariable
};


/****************************************************************************
*
** FUNCTION: Display_ABL_SetVariable()
*/
/*!
* \brief
*   Display ABL Protocol to set the variable value
*
  @param[in]  pVariableName              The variable name that need to set.
  @param[in]  pVariableValue             The variable value.
  @param[in]  uDataLength                The length of the variable value.
  @param[in]  uFlags                     The flag to set variable.
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_ABL_SetVariable (CHAR16 *pVariableName, UINT8 *pVariableValue, UINTN uDataLength, UINTN uFlags)
{
  EFI_STATUS  eStatus         = EFI_SUCCESS;
  CHAR16      DisplayConfigFile[DISP_FILE_NAME_MAX_SIZE];
  UINT32      uFileNameSize   = 0;
  UINTN       uWriteDataSize  = uDataLength * sizeof (UINT8);

  if ((NULL == pVariableName) ||
      (NULL == pVariableValue))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name or value buffer is NULL!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if ((StrLen(pVariableName) > (DISP_FILE_NAME_MAX_SIZE - StrLen(DISP_FILE_EXT) - 1)) ||
           (uDataLength           >  DISP_VARIABLE_VALUE_MAX_SIZE))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name or value size is out of limit!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (EFI_SUCCESS != (eStatus = MountFatPartition(DISP_LOGFS)))
  {
    // MountFatPartition can fail, if it is alredy mounted.
    DEBUG((EFI_D_INFO, "DisplayUtils: mount logfs system failed with status %d!\n", eStatus));	
  }
  else 
  {
    uFileNameSize = StrLen(pVariableName) * sizeof (CHAR16);
  
    MDP_OSAL_MEMZERO(DisplayConfigFile, sizeof(DisplayConfigFile));
    MDP_OSAL_MEMCPY(DisplayConfigFile, pVariableName, uFileNameSize);
  
    StrCat(DisplayConfigFile, DISP_FILE_EXT);
  
    /* Clear the configuration file before writing it if already exists */
    DeleteFile (DisplayConfigFile,
                NULL,
                NULL,
                DISP_LOGFS,
                TRUE,
                NULL);
  
    if ((NULL != pVariableValue) &&
        (0    != uWriteDataSize))
    {  
      eStatus = WriteFile (DisplayConfigFile,
                           NULL,
                           NULL,
                           DISP_LOGFS,
                           TRUE,
                           NULL,
                           &uWriteDataSize,
                           0,
                           pVariableValue,
                           uWriteDataSize);
  
      if(eStatus != EFI_SUCCESS)
      {
        DEBUG((EFI_D_WARN, "DisplayUtils: Saving variable(%s) failed (status:%d)\n", pVariableName, eStatus));
      }
    }
  }  

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: Display_ABL_GetVariable()
*/
/*!
* \brief
*   Display ABL Protocol to get the variable value
*
  @param[in]   pVariableName              The variable name that need to get.
  @param[out]  pVariableValue             The variable value.
  @param[out]  pDataLength                The length of the variable value.
  @param[in]   uFlags                     The flag to get variable.
*
* \retval EFI_STATUS
*
****************************************************************************/
EFI_STATUS Display_ABL_GetVariable(CHAR16 *pVariableName, UINT8 *pVariableValue, UINTN *pDataLength, UINTN uFlags)
{
  EFI_STATUS  eStatus        = EFI_SUCCESS;
  CHAR16      DisplayConfigFile[DISP_FILE_NAME_MAX_SIZE];
  UINT32      uFileNameSize  = 0;
  UINTN       uReadDataSize  = 0;

  if ((NULL == pVariableName)  ||
      (NULL == pVariableValue) ||
      (NULL == pDataLength))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name or value buffer is NULL!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (StrLen(pVariableName) > (DISP_FILE_NAME_MAX_SIZE - StrLen(DISP_FILE_EXT) - 1))
  {
    DEBUG((EFI_D_WARN, "DisplayUtils: variable name is too long!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (EFI_SUCCESS != (eStatus = MountFatPartition(DISP_LOGFS)))
  {
    // MountFatPartition can fail if it is already mounted. 
    DEBUG((EFI_D_WARN, "DisplayUtils: mount logfs system failed with status %d!\n", eStatus));
  }
  else
  {
    uFileNameSize = StrLen(pVariableName) * sizeof (CHAR16);
    uReadDataSize  = (*pDataLength) * sizeof (UINT8);
  
    MDP_OSAL_MEMZERO(DisplayConfigFile, sizeof(DisplayConfigFile));
    MDP_OSAL_MEMCPY(DisplayConfigFile, pVariableName, uFileNameSize);
  
    StrCat(DisplayConfigFile, DISP_FILE_EXT);
  
    eStatus = ReadFile (DisplayConfigFile,
                        NULL,
                        NULL,
                        DISP_LOGFS,
                        TRUE,
                        NULL,
                        &uReadDataSize,
                        0,
                        pVariableValue,
                        uReadDataSize);
  
    *pDataLength = AsciiStrLen((CHAR8 *)pVariableValue);
  
    if ((EFI_NOT_FOUND == eStatus)     ||
        (0             == *pDataLength))
    {
      // Variable not found
      eStatus = EFI_NOT_FOUND;
      DEBUG((EFI_D_ERROR, "DisplayUtils: Reading variable(%s) failed not found (status:%d)\n", pVariableName, eStatus));
    }
    else if(EFI_SUCCESS != eStatus)
    {
      DEBUG((EFI_D_ERROR, "DisplayUtils: Reading variable(%s) failed (status:%d)\n", pVariableName, eStatus));
    }
    else
    {
      DEBUG((EFI_D_ERROR, "DisplayUtils: Reading variable(%s) value:(%s)\n", pVariableName, pVariableValue));
    }
  }

  return eStatus;
}

