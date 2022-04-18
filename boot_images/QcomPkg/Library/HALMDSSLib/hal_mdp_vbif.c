/*! \file */

/*
===========================================================================

FILE:        hal_mdp_vbif.c

DESCRIPTION: Configures VBIF settings for MDSS.
  
===========================================================================
  Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

===========================================================================
*/

/* -----------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------- */

#include "hal_mdp_i.h"

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------------------------------------------------------------------
 * Local defines 
 * ------------------------------------------------------------------------------------ */



/* -------------------------------------------------------------------------------------
 * Static data declarations and functions
 * ------------------------------------------------------------------------------------ */
    
   
static HAL_MDSS_ErrorType HAL_MDP_VBif_QOSRemapper(HAL_MDP_VBIFQOSRemapperType *psTrfCtrlSetting,
                                                   uint32                       uFlags );

/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_Vbif_BaseOffset()
*/
/*!
* \brief
*     Returns offset of the VBIF
*
* \param [in] eVbifId         - VBIF block ID
*
* \retval uintPtr
*
****************************************************************************/
static uintPtr HAL_MDP_Get_Vbif_BaseOffset(HAL_MDP_VbifId  eVbifId)
{
    uintPtr   uRegOffset = 0x0;

    if ((uint32)eVbifId >= HAL_MDP_GET_VBIF_COUNT())
    {
        HAL_MDP_ASSERT();
    }
    else
    {
        uRegOffset = uMDPVbifRegBaseOffset[eVbifId];
    }
    return uRegOffset;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_Vbif_Config_ClockGating()
*/
/*!
* \brief
*     Configures clock gating on the VBIF
*
* \param [in] bEnableGating  - TRUE: enable clock gating AXI & Test Bus Domain; otherwise disable;
* \param [in] uFlags         - reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_Vbif_Config_ClockGating(
                              HAL_MDP_VbifId eVbifId,
                              bool32         bEnableGating,
                              uint32         uFlags )
{
   uint32  uRegValue       = 0;
   uint32  uAxiForceOn     = 0;
   uint32  uTestBusForceOn = 0;
   uintPtr uRegOffset      = 0;

   uRegOffset = HAL_MDP_Get_Vbif_BaseOffset(eVbifId);

   if (FALSE == bEnableGating)
   {
     uAxiForceOn     = 1;
     uTestBusForceOn = 1;
   }
   
   uRegValue = HWIO_OUT_FLD(uRegValue, VBIF, VBIF_CLKON_FORCE_ON, uAxiForceOn);
   uRegValue = HWIO_OUT_FLD(uRegValue, VBIF, VBIF_CLKON_FORCE_ON_TESTBUS, uTestBusForceOn);
   uRegValue = HWIO_OUT_FLD(uRegValue, VBIF, VBIF_CLKON_HYSTERESIS_VALUE, 0);
   
   out_dword(HWIO_MMSS_VBIF_VBIF_CLKON_ADDR + uRegOffset, uRegValue);

   return HAL_MDSS_STATUS_SUCCESS;
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_Vbif_BurstLimitsConfig()
*/
/*!
* \brief
*     Configures Vbif burst size limits
*
* \param [in] uReadBurst     - Maximum read burst size
* \param [in] uReadOT        - Maximum read outstanding transactions (OT)
* \param [in] uWriteBurst    - Maximum write burst size
* \param [in] uWriteOT       - Maximum write outstanding transition (OT)
* \param [in] uFlags         - reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_Vbif_BurstLimitsConfig(
                              HAL_MDP_VbifId eVbifId,
                              uint32         uReadBurst,
                              uint32         uReadOT,                              
                              uint32         uWriteBurst,
                              uint32         uWriteOT,
                              uint32         uFlags )
{
   uint32  uRegValue = 0;
   uintPtr uRegOffset = 0;

   uRegOffset = HAL_MDP_Get_Vbif_BaseOffset(eVbifId);

   // Configure VBIF max read/write burst size
   uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_DDR_OUT_MAX_BURST, DDR_OUT_MAX_WR_BURST, uWriteBurst);
   uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_DDR_OUT_MAX_BURST, DDR_OUT_MAX_RD_BURST, uReadBurst);

   out_dword(HWIO_MMSS_VBIF_VBIF_DDR_OUT_MAX_BURST_ADDR + uRegOffset, uRegValue);


   if (HAL_MDP_VBIF_0 == eVbifId)
   {
       // Configure VBIF RD OT
       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF0, IN_RD_LIM_C0, uReadOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF0, IN_RD_LIM_C1, uReadOT);   
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF0, IN_RD_LIM_C2, uReadOT);      
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF0, IN_RD_LIM_C3, uReadOT);         
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_RD_LIM_CONF0_ADDR + uRegOffset, uRegValue);

       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF1, IN_RD_LIM_C4, uReadOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF1, IN_RD_LIM_C5, uReadOT);   
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF1, IN_RD_LIM_C6, uReadOT);      
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF1, IN_RD_LIM_C7, uReadOT);         
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_RD_LIM_CONF1_ADDR + uRegOffset, uRegValue);

       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF2, IN_RD_LIM_C8,  uReadOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF2, IN_RD_LIM_C9,  uReadOT);   
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF2, IN_RD_LIM_C10, uReadOT);      
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF2, IN_RD_LIM_C11, uReadOT);            
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_RD_LIM_CONF2_ADDR + uRegOffset, uRegValue);

       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF3, IN_RD_LIM_C12, uReadOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF3, IN_RD_LIM_C13, uReadOT);   
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_RD_LIM_CONF3_ADDR + uRegOffset, uRegValue);   

       // Configure VBIF WR OT
       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF0, IN_WR_LIM_C0, uWriteOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF0, IN_WR_LIM_C1, uWriteOT);   
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF0, IN_WR_LIM_C2, uWriteOT);      
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF0, IN_WR_LIM_C3, uWriteOT);         
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_WR_LIM_CONF0_ADDR + uRegOffset, uRegValue);

       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF1, IN_WR_LIM_C4, uWriteOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF1, IN_WR_LIM_C5, uWriteOT);   
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF1, IN_WR_LIM_C6, uWriteOT);      
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF1, IN_WR_LIM_C7, uWriteOT);         
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_WR_LIM_CONF1_ADDR + uRegOffset, uRegValue);

       uRegValue = 0;
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF2, IN_WR_LIM_C8,  uWriteOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF2, IN_WR_LIM_C9,  uWriteOT);   
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF2, IN_WR_LIM_C10, uWriteOT);      
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF2, IN_WR_LIM_C11, uWriteOT);            
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_WR_LIM_CONF2_ADDR + uRegOffset, uRegValue);

       uRegValue = 0;
       uRegValue =  HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF3, IN_WR_LIM_C12, uWriteOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF3, IN_WR_LIM_C13, uWriteOT);   
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_WR_LIM_CONF3_ADDR + uRegOffset, uRegValue);   
    }   
    else 
    {
       // Configure VBIF RD OT
       uRegValue = 0;
       uRegValue =  HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF0, IN_RD_LIM_C0, uReadOT);
       uRegValue |= HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_RD_LIM_CONF0, IN_RD_LIM_C1, uReadOT);   
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_RD_LIM_CONF0_ADDR + uRegOffset, uRegValue);

       // Configure VBIF WR OT
       uRegValue = 0;
       uRegValue =  HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF0, IN_WR_LIM_C0, uWriteOT);
       uRegValue = HWIO_OUT_FLD(uRegValue, VBIF_VBIF_IN_WR_LIM_CONF0, IN_WR_LIM_C1, uWriteOT);   
       out_dword(HWIO_MMSS_VBIF_VBIF_IN_WR_LIM_CONF0_ADDR + uRegOffset, uRegValue);    
    }

   return HAL_MDSS_STATUS_SUCCESS;
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_Vbif_AoooCtrlConfig()
*/
/*!
* \brief
*     Enable/Disable SW controlling AOOOWR/RD signals on AXI protocol.
*
* \param [in] bEnable - TRUE: enable SW controlling AOOOWR/RD siganls; otherwise disable;
* \param [in] uFlags  - reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_Vbif_AoooCtrlConfig(
                              HAL_MDP_VbifId eVbifId,
                              bool32         bEnable,
                              uint32         uFlags )
{
    uintPtr uRegOffset = 0;

    uRegOffset = HAL_MDP_Get_Vbif_BaseOffset(eVbifId);

   if (TRUE == bEnable)
   {
       out_dword(HWIO_MMSS_VBIF_VBIF_OUT_AXI_AOOO_EN_ADDR + uRegOffset, HWIO_MMSS_VBIF_VBIF_OUT_AXI_AOOO_EN_RMSK);
       out_dword(HWIO_MMSS_VBIF_VBIF_OUT_AXI_AOOO_ADDR + uRegOffset, HWIO_MMSS_VBIF_VBIF_OUT_AXI_AOOO_RMSK);
   }
   else
   {
       out_dword(HWIO_MMSS_VBIF_VBIF_OUT_AXI_AOOO_EN_ADDR + uRegOffset, 0);
       out_dword(HWIO_MMSS_VBIF_VBIF_OUT_AXI_AOOO_ADDR + uRegOffset, 0);
   }
   
   return HAL_MDSS_STATUS_SUCCESS;
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_Vbif_RoundRobinQoSArbiConfig()
*/
/*!
* \brief
*     Enable/Disable Round-Robin Arbiter with QoS signal.
*
* \param [in] bEnable - TRUE: Round-Robin Arbiter with QoS signal; otherwise disable;
* \param [in] uFlags  - reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_Vbif_RoundRobinQoSArbiConfig(
                              HAL_MDP_VbifId eVbifId,
                              bool32         bEnable,
                              uint32         uFlags )
{
    uintPtr uRegOffset = 0;

    uRegOffset = HAL_MDP_Get_Vbif_BaseOffset(eVbifId);

   if (TRUE == bEnable)
   {
       out_dword(HWIO_MMSS_VBIF_VBIF_ROUND_ROBIN_QOS_ARB_ADDR + uRegOffset, (HWIO_MMSS_VBIF_VBIF_ROUND_ROBIN_QOS_ARB_RR_QOS_EN_BMSK |
                                                                             HWIO_MMSS_VBIF_VBIF_ROUND_ROBIN_QOS_ARB_MMU_RR_QOS_EN_BMSK) );
   }
   else
   {
       out_dword(HWIO_MMSS_VBIF_VBIF_ROUND_ROBIN_QOS_ARB_ADDR + uRegOffset, 0);
   }
   
   return HAL_MDSS_STATUS_SUCCESS;
}


/****************************************************************************
*
** FUNCTION: HAL_MDP_VBif_QOSSetup()
*/
/*!
* \brief
*     VBIF QOS setup
*
* \retval None
*
****************************************************************************/

HAL_MDSS_ErrorType HAL_MDP_VBif_QOSSetup(HAL_MDP_VBIF_ClientIDType eClientId,
                                         HAL_MDP_InterfaceId       eInterfaceId,
                                         uint32                    uFlags )
{
   HAL_MDSS_ErrorType            eStatus     = HAL_MDSS_STATUS_SUCCESS;
   
   if (NULL != pgsMdpHwInfo->pVBIFQOSRemappers) 
   {
      HAL_MDP_VBIFQOSRemapperType   sVBIFQOSRemapperSetting;   
      
      sVBIFQOSRemapperSetting.eClientId = eClientId;
      sVBIFQOSRemapperSetting.pVBIFQOSRemappers = (HAL_MDP_VBIFQOSRemappers *)&pgsMdpHwInfo->pVBIFQOSRemappers[eClientId];

      eStatus = HAL_MDP_VBif_QOSRemapper(&sVBIFQOSRemapperSetting, uFlags);
   }
   
   return eStatus;

}

/****************************************************************************
*
** FUNCTION: HAL_MDP_VBif_QOSRemapper()
*/
/*!
* \brief
*     Recommended HW default settings for VBIF QOS remappers.
*
* \retval None
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_VBif_QOSRemapper(
                       HAL_MDP_VBIFQOSRemapperType  *psTrfCtrlSetting,
                       uint32                        uFlags )
{
  HAL_MDSS_ErrorType      eStatus    = HAL_MDSS_STATUS_SUCCESS;
  HAL_MDP_VbifId          eVbifId    = HAL_MDP_VBIF_0;
  uintPtr                 uRegOffset = 0;

  if ((psTrfCtrlSetting->eClientId < HAL_MDP_VBIF_CLIENT_MAX) &&
      (NULL != pgsMdpHwInfo->pVBIFClientToHWIDMap))
  {
      eVbifId = pgsMdpHwInfo->pVBIFClientToHWIDMap[psTrfCtrlSetting->eClientId];
  }
  
  uRegOffset = HAL_MDP_Get_Vbif_BaseOffset(eVbifId);

  //Read existing values 
  if (HAL_MDP_VBIF_0 == eVbifId)
  {
    uint32 uVBIFQOSRemap_00L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_00_ADDR + uRegOffset);
    uint32 uVBIFQOSRemap_00H = in_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_00_ADDR + uRegOffset);  
    uint32 uVBIFQOSRemap_01L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_01_ADDR + uRegOffset);
    uint32 uVBIFQOSRemap_01H = in_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_01_ADDR + uRegOffset);  
    uint32 uVBIFQOSRemap_10L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_10_ADDR + uRegOffset);
    uint32 uVBIFQOSRemap_10H = in_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_10_ADDR + uRegOffset);  
    uint32 uVBIFQOSRemap_11L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_11_ADDR + uRegOffset);
    uint32 uVBIFQOSRemap_11H = in_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_11_ADDR + uRegOffset);  
   
    // Apply settings based on VBIF client ID..
    // Clients 0-7 are in the low tables, Clients 8-13 are in the high tables
    switch (psTrfCtrlSetting->eClientId)
    {
       case HAL_MDP_VBIF_CLIENT_VIG0:     
           uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                    VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                    QOS_REMAP_00_C0,
                                    psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
           uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                    VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                    QOS_REMAP_01_C0,
                                    psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
           uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                    VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                    QOS_REMAP_10_C0,
                                    psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
           uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                    VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                    QOS_REMAP_11_C0,
                                    psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_DMA0:
        uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C1,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C1,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C1,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C1,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_CURSOR0:
        uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C2,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C2,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C2,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C2,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_VIG1:
        uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C4,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C4,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C4,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C4,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_DMA1:
        uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C5,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C5,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C5,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C5,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_WB2:
        uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C6,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C6,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C6,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C6,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_DSIDMA:
        uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C7,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C7,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C7,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                 VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C7,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_VIG2:
        uVBIFQOSRemap_00H = HWIO_OUT_FLD(uVBIFQOSRemap_00H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C8,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01H = HWIO_OUT_FLD(uVBIFQOSRemap_01H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C8,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10H = HWIO_OUT_FLD(uVBIFQOSRemap_10H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C8,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11H = HWIO_OUT_FLD(uVBIFQOSRemap_11H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C8,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_DMA2:
        uVBIFQOSRemap_00H = HWIO_OUT_FLD(uVBIFQOSRemap_00H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C9,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01H = HWIO_OUT_FLD(uVBIFQOSRemap_01H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C9,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10H = HWIO_OUT_FLD(uVBIFQOSRemap_10H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C9,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11H = HWIO_OUT_FLD(uVBIFQOSRemap_11H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C9,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_CURSOR1:
        uVBIFQOSRemap_00H = HWIO_OUT_FLD(uVBIFQOSRemap_00H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C10,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01H = HWIO_OUT_FLD(uVBIFQOSRemap_01H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C10,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10H = HWIO_OUT_FLD(uVBIFQOSRemap_10H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C10,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11H = HWIO_OUT_FLD(uVBIFQOSRemap_11H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C10,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_VIG3:
        uVBIFQOSRemap_00H = HWIO_OUT_FLD(uVBIFQOSRemap_00H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C12,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01H = HWIO_OUT_FLD(uVBIFQOSRemap_01H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C12,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10H = HWIO_OUT_FLD(uVBIFQOSRemap_10H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C12,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11H = HWIO_OUT_FLD(uVBIFQOSRemap_11H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C12,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       case HAL_MDP_VBIF_CLIENT_DMA3:
        uVBIFQOSRemap_00H = HWIO_OUT_FLD(uVBIFQOSRemap_00H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_00,
                                 QOS_REMAP_00_C13,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
        uVBIFQOSRemap_01H = HWIO_OUT_FLD(uVBIFQOSRemap_01H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_01,
                                 QOS_REMAP_01_C13,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
        uVBIFQOSRemap_10H = HWIO_OUT_FLD(uVBIFQOSRemap_10H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_10,
                                 QOS_REMAP_10_C13,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
        uVBIFQOSRemap_11H = HWIO_OUT_FLD(uVBIFQOSRemap_11H,
                                 VBIF_VBIF_XINH_QOS_RP_REMAP_11,
                                 QOS_REMAP_11_C13,
                                 psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
       default:
       break; 
    }

    //write into the registers
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_00_ADDR + uRegOffset, uVBIFQOSRemap_00L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_00_ADDR + uRegOffset, uVBIFQOSRemap_00H);      
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_01_ADDR + uRegOffset, uVBIFQOSRemap_01L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_01_ADDR + uRegOffset, uVBIFQOSRemap_01H);    
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_10_ADDR + uRegOffset, uVBIFQOSRemap_10L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_10_ADDR + uRegOffset, uVBIFQOSRemap_10H);    
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_11_ADDR + uRegOffset, uVBIFQOSRemap_11L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINH_QOS_RP_REMAP_11_ADDR + uRegOffset, uVBIFQOSRemap_11H);    
 }
 else if (HAL_MDP_VBIF_1 == eVbifId)
 {
   // Rotator (NRT) clients
   uint32 uVBIFQOSRemap_00L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_00_ADDR + uRegOffset);
   uint32 uVBIFQOSRemap_01L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_01_ADDR + uRegOffset);
   uint32 uVBIFQOSRemap_10L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_10_ADDR + uRegOffset);
   uint32 uVBIFQOSRemap_11L = in_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_11_ADDR + uRegOffset);
   
   // Apply settings based on VBIF client ID..
   // Clients 0-7 are in the low tables, Clients 8-13 are in the high tables
   switch (psTrfCtrlSetting->eClientId)
   {
     case HAL_MDP_VBIF_CLIENT_ROT_RD:     
       uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                QOS_REMAP_00_C0,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
       uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                QOS_REMAP_01_C0,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
       uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                QOS_REMAP_10_C0,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
       uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                QOS_REMAP_11_C0,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
     break;
     case HAL_MDP_VBIF_CLIENT_ROT_WR:
       uVBIFQOSRemap_00L = HWIO_OUT_FLD(uVBIFQOSRemap_00L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_00,
                                QOS_REMAP_00_C1,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper00);
       uVBIFQOSRemap_01L = HWIO_OUT_FLD(uVBIFQOSRemap_01L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_01,
                                QOS_REMAP_01_C1,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper01);
       uVBIFQOSRemap_10L = HWIO_OUT_FLD(uVBIFQOSRemap_10L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_10,
                                QOS_REMAP_10_C1,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper10);
       uVBIFQOSRemap_11L = HWIO_OUT_FLD(uVBIFQOSRemap_11L,
                                VBIF_VBIF_XINL_QOS_RP_REMAP_11,
                                QOS_REMAP_11_C1,
                                psTrfCtrlSetting->pVBIFQOSRemappers->uVBIFQosRemapper11);
       break;
     default:
       break; 
    }

    //write into the registers
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_00_ADDR + uRegOffset, uVBIFQOSRemap_00L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_01_ADDR + uRegOffset, uVBIFQOSRemap_01L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_10_ADDR + uRegOffset, uVBIFQOSRemap_10L);
    out_dword(HWIO_MMSS_VBIF_VBIF_XINL_QOS_RP_REMAP_11_ADDR + uRegOffset, uVBIFQOSRemap_11L);
 }
  
 return eStatus; 
}

/* -------------------------------------------------------------------------------------
 * Public functions
 * ------------------------------------------------------------------------------------ */

/****************************************************************************
*
** FUNCTION: HAL_MDP_Vbif_Init()
*/
/*!
* \brief
*     Initializes VBIF settings.
*
* \param [in] eVbifId    - VBIF block ID
* \param [in] uFlags     - reserved flags
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_Vbif_Init(HAL_MDP_VbifId eVbifId, uint32 uFlags)
{

   /* configure VBIF clock gating */
   HAL_MDP_Vbif_Config_ClockGating(eVbifId, ((HAL_MDP_VBIF_ENABLE_CLOCKGATING & uFlags) ? TRUE : FALSE), 0);
   
   /* configure VBIF burst limits */
   HAL_MDP_Vbif_BurstLimitsConfig(eVbifId, 
                                  pgsMdpHwInfo->uVBIFMaxDdrRdBurstSize,
                                  pgsMdpHwInfo->uVBIFMaxRdOT,
                                  pgsMdpHwInfo->uVBIFMaxDdrWrBurstSize,
                                  pgsMdpHwInfo->uVBIFMaxWrOT,
                                  0);

   /* enable SW controlling AOOOWR/RD signals on AXI protocol */
   HAL_MDP_Vbif_AoooCtrlConfig(eVbifId, TRUE, 0);

   /* enable Round-Robin Arbiter with QoS signal */
   HAL_MDP_Vbif_RoundRobinQoSArbiConfig(eVbifId, TRUE, 0);

   // Recommended VBIF settings for Gandalf MDSS
   if(NULL != pgsMdpHwInfo->sIpFxnTbl.Vbif_HwDefaultConfig)
   {
       pgsMdpHwInfo->sIpFxnTbl.Vbif_HwDefaultConfig(eVbifId);
   }

   return HAL_MDSS_STATUS_SUCCESS;
}



#ifdef __cplusplus
}
#endif
