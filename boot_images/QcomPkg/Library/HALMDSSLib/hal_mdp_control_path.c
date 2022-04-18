/*! \file */

/*
===========================================================================

FILE:         hal_mdp_control_path.c

DESCRIPTION: Connects the blocks of the MDP (Source, Mixer and Display Interface) 
  

===========================================================================
  Copyright (c) 2010-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/

#include "hal_mdp_i.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_ControlPath_BaseOffset()
*/
/*!
* \brief
*     Returns offset of the layer mixer register
*
* \param [in] eControlPath         - Control Path ID (0, 1, 2, 3, 4)
*
* \retval uintPtr
*
****************************************************************************/
static uintPtr HAL_MDP_Get_ControlPath_BaseOffset(HAL_MDP_ControlPathId  eControlPath)
{
   uintPtr      uRegOffset     = 0x0;

   if((HAL_MDP_CONTROL_PATH_NONE           == eControlPath)         || 
      (HAL_MDP_GET_CONTROL_PATHS_COUNT()   <  (uint32)eControlPath) ||
      (HAL_MDP_CONTROL_PATH_MAX            <=  eControlPath))
   {
      HAL_MDP_ASSERT();
   }
   else
   {
      uRegOffset = uMDPControlPathRegBaseOffset[eControlPath];
   }
   return uRegOffset;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_MixerConfig()
*/
/*!
* \brief
*     Control path configuration
*
* \param [in] eControlPath                - Control Path ID (0, 1, 2, 3, 4)
* \param [in] pControlPathMixerConfig     - Control path mixer configuration information
* \param [in] uFlags                      - Reserved flags
*
* \retval NONE
*
****************************************************************************/
static void  HAL_MDP_ControlPath_MixerConfig(HAL_MDP_ControlPathId                 eControlPath,
                                             HAL_MDP_ControlPath_MixerConfigType  *pControlPathMixerConfig,
                                             uint32                                uFlags)
{
   uintPtr                 uRegOffset              = 0x00;
   uint32                  uRegValue               = 0x00;
   uint32                  uRegValueEx             = 0x00;
   uint32                  uBlendOrderIndex        = 0x00;
   uint32                  uLayerBlendOrder        = 0x00;
   bool32                  bLayerBlendOrderEx      = FALSE;
   uint32                  uCursorBlendOrder       = 0x00;
   uintPtr                 uLayerMixerRegAddr      = 0x00;
   uintPtr                 uLayerMixerExtRegAddr   = 0x00;
   uint32                  uMixerId                = (pControlPathMixerConfig->eMixerId<HAL_MDP_LAYER_MIXER_MAX)?(uint32)pControlPathMixerConfig->eMixerId:(uint32)HAL_MDP_LAYER_MIXER_NONE;
   uint32                  uLayerMixerRegOffsets[HAL_MDP_LAYER_MIXER_MAX]    = { 0x00, 0x00, 0x04, 0x08, 0x0C, 0x10, 0x24, 0x00 };
   uint32                  uLayerMixerExtRegOffsets[HAL_MDP_LAYER_MIXER_MAX] = { 0x00, 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x00 };

   uRegOffset  = HAL_MDP_Get_ControlPath_BaseOffset(eControlPath);

   /*
    * Note: layer mixer register address offset:
    *     MMSS_MDP_CTL_0_LAYER_0            0x00902000
    *     MMSS_MDP_CTL_0_LAYER_1            0x00902004
    *     MMSS_MDP_CTL_0_LAYER_2            0x00902008
    *     MMSS_MDP_CTL_0_LAYER_3            0x0090200C
    *     MMSS_MDP_CTL_0_LAYER_4            0x00902010
    *     MMSS_MDP_CTL_0_LAYER_5            0x00902024
    */
   uLayerMixerRegAddr    = HWIO_MMSS_MDP_CTL_0_LAYER_0_ADDR     + uRegOffset + uLayerMixerRegOffsets[uMixerId];
   uLayerMixerExtRegAddr = HWIO_MMSS_MDP_CTL_0_LAYER_0_EXT_ADDR + uRegOffset + uLayerMixerExtRegOffsets[uMixerId];

   uRegValue      = in_dword(uLayerMixerRegAddr);
   uRegValueEx    = in_dword(uLayerMixerExtRegAddr);

   // Cursor Configuration
   if(NULL != pControlPathMixerConfig->psMixerCursorConfig)
   {
      if(HAL_MDP_LAYER_TYPE_LAYERMIXER_CURSOR == pgsMdpHwInfo->eCursorIntLayerType)
      {
         uRegValue = HWIO_OUT_FLD(uRegValue,
                                  MDP_CTL_0_LAYER_0,
                                  CURSOR_OUT,
                                  pControlPathMixerConfig->psMixerCursorConfig->bCursorEnable);
      }
      else // SSPP
      {
         /* Use the cursor layer blend id defined by the HAL user */
         uCursorBlendOrder = ((TRUE == pControlPathMixerConfig->psMixerCursorConfig->bCursorEnable)?
          (pgsMdpHwInfo->uCursorBlendOrderIndex):(0x00));

         switch(pControlPathMixerConfig->psMixerCursorConfig->eCursorId)
         {
         case HAL_MDP_SOURCE_PIPE_CURSOR_0:
            uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, CURSOR_0_OUT, uCursorBlendOrder);
            break;

         case HAL_MDP_SOURCE_PIPE_CURSOR_1:
            uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, CURSOR_1_OUT, uCursorBlendOrder);
            break;

         case HAL_MDP_SOURCE_PIPE_CURSOR_2:
         case HAL_MDP_SOURCE_PIPE_CURSOR_3:
         case HAL_MDP_SOURCE_PIPE_CURSOR_4:
         default:
            break;
         }
      }
   }

   // Border Color Configuration
   if(NULL != pControlPathMixerConfig->psMixerBorderColorConfig)
   {
      uRegValue = HWIO_OUT_FLD(uRegValue,
                               MDP_CTL_0_LAYER_0, 
                               BORDER_OUT,
                               pControlPathMixerConfig->psMixerBorderColorConfig->bBorderColorEnable);
   }

   // Blend Stage Z-ORDER configuration
   if (NULL != pControlPathMixerConfig->psMixerZOrderConfig)
   {
       // Clear all layer attach information
       uRegValue = uRegValue & (HWIO_MMSS_MDP_CTL_0_LAYER_0_BORDER_OUT_BMSK |
                                HWIO_MMSS_MDP_CTL_0_LAYER_0_CURSOR_OUT_BMSK);

       // Clear all layer attach information
       uRegValueEx = uRegValueEx & (HWIO_MMSS_MDP_CTL_0_LAYER_0_EXT_CURSOR_0_OUT_BMSK |
                                    HWIO_MMSS_MDP_CTL_0_LAYER_0_EXT_CURSOR_1_OUT_BMSK);

       for (uBlendOrderIndex = HAL_MDP_BLEND_ORDER_STAGE_0_BASE_LAYER;
           uBlendOrderIndex < HAL_MDP_BLEND_ORDER_STAGE_MAX;
           uBlendOrderIndex++)
       {
           uint32 uI;

           uLayerBlendOrder = ((uBlendOrderIndex > HAL_MDP_BLEND_ORDER_STAGE_5_FG_LAYER) ? (0x00) : (uBlendOrderIndex));
           bLayerBlendOrderEx = ((uBlendOrderIndex > HAL_MDP_BLEND_ORDER_STAGE_5_FG_LAYER) ? (TRUE) : (FALSE));

           for (uI = 0; uI < HAL_MDP_MAX_SSPP_IN_DUALPIPE_MODE; uI++)
           {
               switch (pControlPathMixerConfig->psMixerZOrderConfig->eSourcePipe[uBlendOrderIndex][uI])
               {
               case HAL_MDP_SOURCE_PIPE_VIG_0:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, VIG_0_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, VIG_0_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_VIG_1:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, VIG_1_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, VIG_1_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_VIG_2:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, VIG_2_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, VIG_2_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_VIG_3:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, VIG_3_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, VIG_3_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_RGB_0:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, RGB_0_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, RGB_0_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_RGB_1:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, RGB_1_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, RGB_1_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_RGB_2:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, RGB_2_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, RGB_2_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_RGB_3:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, RGB_3_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, RGB_3_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_DMA_0:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, DMA_0_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, DMA_0_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_DMA_1:
                   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_LAYER_0, DMA_1_OUT, uLayerBlendOrder);
                   uRegValueEx = HWIO_OUT_FLD(uRegValueEx, MDP_CTL_0_LAYER_0_EXT, DMA_1_OUT_BIT3, bLayerBlendOrderEx);
                   break;

               case HAL_MDP_SOURCE_PIPE_VIG_4:
               case HAL_MDP_SOURCE_PIPE_RGB_4:
               case HAL_MDP_SOURCE_PIPE_DMA_2:
               case HAL_MDP_SOURCE_PIPE_DMA_3:
               case HAL_MDP_SOURCE_PIPE_DMA_4:
               case HAL_MDP_SOURCE_PIPE_NONE:
               case HAL_MDP_SOURCE_PIPE_MAX:
               case HAL_MDP_SOURCE_PIPE_FORCE_32BIT:
               default:
                   break;
               }
           }
       }
   }
  out_dword(uLayerMixerRegAddr, uRegValue);
  out_dword(uLayerMixerExtRegAddr, uRegValueEx);
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_InterfaceConfig()
*/
/*!
* \brief
*     Control path configuration
*
* \param [in] eControlPath                - Control Path ID (0, 1, 2, 3, 4)
* \param [in] pInterfaceConfig            - Control path interface configuration
* \param [in] uFlags                      - Reserved flags
*
* \retval NONE
*
****************************************************************************/
static void  HAL_MDP_ControlPath_InterfaceConfig(HAL_MDP_ControlPathId                     eControlPath,
                                                 HAL_MDP_ControlPath_InterfaceConfigType  *pInterfaceConfig,
                                                 uint32                                    uFlags)
{
   uintPtr                 uRegOffset        = 0x0;
   uint32                  uRegValue         = 0x00;

   uRegOffset  = HAL_MDP_Get_ControlPath_BaseOffset(eControlPath);

   if(HAL_MDP_INTERFACE_WRITEBACK_TYPE_BASE > pInterfaceConfig->eInterfaceId) // Physical interface connection
   {
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, OUT_SEL, pInterfaceConfig->eInterfaceId);
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, MODE_SEL, pInterfaceConfig->eInterfaceModeType);
   }
   else // Write-Back Path
   {
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, MEM_SEL, (pInterfaceConfig->eInterfaceId - HAL_MDP_INTERFACE_WRITEBACK_TYPE_BASE));
   }

   // Common configurations for both physical and write-back interface
   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, DSPP_SEL, 0x00);
   uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, PING_PONG_SEL, 0x00);

   // 3D/Dualpipe configuration
   if(TRUE == pInterfaceConfig->b3DMuxEnable)   // 3D Mux enable
   {
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, PACK_3D_MODE, pInterfaceConfig->eMuxPackerModeConfig);   // 3D Muxer mode configuartion
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, PACK_3D_OUT, 0x01);
   }
   else  // 3D Mux disable
   {
      uRegValue = HWIO_OUT_FLD(uRegValue, MDP_CTL_0_TOP, PACK_3D_OUT, 0x00);
   }

   out_dword(HWIO_MMSS_MDP_CTL_0_TOP_ADDR + uRegOffset, uRegValue);
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_Interface_Status()
*/
/*!
* \brief
*     Control path configuration
*
* \param [in] eControlPath                - Control Path ID (0, 1, 2, 3, 4)
* \param [in] pInterfaceInfoData          - Interface data configuration
* \param [in] uFlags                      - Reserved flags
*
* \retval NONE
*
****************************************************************************/
static void HAL_MDP_ControlPath_Interface_Status( HAL_MDP_ControlPathId                     eControlPath,
                                                  HAL_MDP_ControlPath_InterfaceConfigType  *pInterfaceInfoData,
                                                  uint32                                    uFlags)
{
  
  if ((eControlPath > HAL_MDP_CONTROL_PATH_NONE) &&  (eControlPath < HAL_MDP_CONTROL_PATH_MAX))
  {
    uintPtr uRegOffset         = 0x0;
    uint32  uControlPathTopCfg = 0x00;
    uint32  uMemSel;

    uRegOffset  = HAL_MDP_Get_ControlPath_BaseOffset(eControlPath) ;

    // Read in register value
    uControlPathTopCfg = in_dword(HWIO_MMSS_MDP_CTL_0_TOP_ADDR + uRegOffset); 
    pInterfaceInfoData->eInterfaceId         = (HAL_MDP_InterfaceId)HWIO_GETVAL(MDP_CTL_0_TOP, uControlPathTopCfg, OUT_SEL);
    uMemSel                                  = HWIO_GETVAL(MDP_CTL_0_TOP, uControlPathTopCfg, MEM_SEL);
    if ((HAL_MDP_INTERFACE_NONE == pInterfaceInfoData->eInterfaceId) &&
        (uMemSel > 0))
    {
        // If interface is not selected decode the writeback configuration          
      pInterfaceInfoData->eInterfaceId = (HAL_MDP_InterfaceId)(HAL_MDP_INTERFACE_WRITEBACK_TYPE_BASE + uMemSel);
    }
    pInterfaceInfoData->eInterfaceModeType   = (HAL_MDP_InterfaceModeType)HWIO_GETVAL(MDP_CTL_0_TOP, uControlPathTopCfg, MODE_SEL);
    pInterfaceInfoData->b3DMuxEnable         = (bool32)HWIO_GETVAL(MDP_CTL_0_TOP, uControlPathTopCfg, PACK_3D_OUT);
    pInterfaceInfoData->eMuxPackerModeConfig = (HAL_MDP_3DMUXPackerModeType)HWIO_GETVAL(MDP_CTL_0_TOP, uControlPathTopCfg, PACK_3D_MODE);

  }
  else
  {
    pInterfaceInfoData->eInterfaceId       = HAL_MDP_INTERFACE_NONE;
    pInterfaceInfoData->eInterfaceModeType = HAL_MDP_INTERFACE_MODE_NONE;
  }
}



/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_Setup()
*/
/*!
* \brief
*     Set up control path configuration
*
* \param [in] eControlPath          - Control Path ID (0, 1, 2, 3, 4)
* \param [in] pControlPathConfig    - Control path configuration information
* \param [in] uFlags                - Reserved flags
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_ControlPath_Setup(HAL_MDP_ControlPathId           eControlPath,
                                             HAL_MDP_ControlPathConfigType  *pControlPathConfig,
                                             uint32                          uFlags)
{
   HAL_MDSS_ErrorType      eStatus  = HAL_MDSS_STATUS_SUCCESS;

   // Control Path Layer Mixer Z-Order Configuration
   if(NULL != pControlPathConfig->psMixerConfig)
   {
      HAL_MDP_ControlPath_MixerConfig(eControlPath, pControlPathConfig->psMixerConfig, 0x00);
   }

   // Control Path Interface Cross Bar (or) Memory Type Selection
   if(NULL != pControlPathConfig->psInterfaceConfig)
   {
      HAL_MDP_ControlPath_InterfaceConfig(eControlPath, pControlPathConfig->psInterfaceConfig, 0x00);
   }

   // Mixer Configuration
   if(NULL != pControlPathConfig->psLayerMixerConfig)
   {
      HAL_MDP_LayerMixer_Config(pControlPathConfig->psLayerMixerConfig->eLayerMixerId,
                                pControlPathConfig->psLayerMixerConfig,
                                uFlags);
   }

   return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_Commit()
*/
/*!
* \brief
*     Control path flush and triggers the write-back path
*
* \param [in] eControlPath          - Control Path ID (0, 1, 2, 3, 4)
* \param [in] pControlPathFlush     - Modules to Flush
* \param [in] eInterfaceConnectType - Mainly for write-back paths
* \param [in] uFlags                - Reserved flags
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_ControlPath_Commit(HAL_MDP_ControlPathId         eControlPath,
                                              HAL_MDP_ControlPathFlushType  *pControlPathFlush,
                                              HAL_MDP_InterfaceConnectType  eInterfaceConnectType,
                                              uint32                        uFlags)
{
   HAL_MDSS_ErrorType      eStatus     = HAL_MDSS_STATUS_SUCCESS;
   uintPtr                 uRegOffset  = 0x0;
   uint32                  uRegValue   = 0x00;

   uRegOffset  = HAL_MDP_Get_ControlPath_BaseOffset(eControlPath);

   // Flush the modules
   uRegValue  = pControlPathFlush->uFlushModules;

   out_dword(HWIO_MMSS_MDP_CTL_0_FLUSH_ADDR + uRegOffset, uRegValue);

   // Only if write-back path or dsi command mode. Trigger the write back operation only after flush
   if((HAL_MDP_INTERFACE_TYPE_WRITE_BACK == eInterfaceConnectType) ||
      (HAL_MDP_FLAGS_COMMIT_FORCE_UPDATE & uFlags))
   {
      out_dword(HWIO_MMSS_MDP_CTL_0_CTL_START_ADDR + uRegOffset, 0x01);
   }
   return eStatus;
}




/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_GetProperty()
*/
/*!
* \brief
*     Retrieve information about an existing control path
*
* \param [in] eControlPath          - Control Path ID (0, 1, 2, 3, 4)
* \param [in] pControlInfoData      - Configuration for the current control path
* \param [in] uFlags                - Reserved flags
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_ControlPath_GetProperty(HAL_MDP_ControlPathId           eControlPath,
                                                   HAL_MDP_ControlPathConfigType  *pControlInfoData,
                                                   uint32                          uFlags)
{
   HAL_MDSS_ErrorType      eStatus     = HAL_MDSS_STATUS_SUCCESS;

   // Interface configuration
   if (NULL != pControlInfoData->psInterfaceConfig)
   {
      HAL_MDP_ControlPath_Interface_Status(eControlPath, pControlInfoData->psInterfaceConfig, 0x00);
   }


   return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_ControlPath_Reset()
*/
/*!
* \brief
*     Triggers a soft reset for a given control path
*
* \param [in] eControlPath          - Control Path ID (0, 1, 2, 3, 4)
* \param [in] uFlags                - Reserved flags
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_ControlPath_Reset(HAL_MDP_ControlPathId           eControlPath,
                                             uint32                          uFlags)
{
   HAL_MDSS_ErrorType      eStatus     = HAL_MDSS_MDP_STATUS_FAILED;
   uintPtr                 uRegOffset  = 0x0;
   uint32                  uResetVal   = 0x00;
   uint32                  uCnt        = 0x00;

   uRegOffset  = HAL_MDP_Get_ControlPath_BaseOffset(eControlPath);

   // Trigger soft reset
   out_dword(HWIO_MMSS_MDP_CTL_0_SW_RESET_ADDR + uRegOffset, 0x01);

   // Poll for reset completion
   for(uCnt = 0; uCnt < HAL_MDP_MAX_RETRIES_FOR_CTRL_PATH_RESET_COMPLETE; uCnt++)
   {
      uResetVal = in_dword(HWIO_MMSS_MDP_CTL_0_SW_RESET_ADDR + uRegOffset);
      if(0x00 == uResetVal)
      {
         eStatus = HAL_MDSS_STATUS_SUCCESS;
         break;
      }
   }

  return eStatus;
}

#ifdef __cplusplus
}
#endif
