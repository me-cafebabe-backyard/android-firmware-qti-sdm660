/*=============================================================================
 
  File: hal_mdss_common.c
 
  Common mdss driver
  
 
  Copyright (c) 2011-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_mdss_common.h"


/*============================================================================
*       HAL Globals
============================================================================*/

/* These are mapped addresses to the register bases supplied by OS */
uintPtr MDSS_BASE_PTR = 0;

uintPtr SEC_CTRL_BASE_PTR = 0;

uintPtr MMSS_MISC_BASE_PTR = 0;

/* HW module register base */
uintPtr MMSS_MDSS_HW_REG_BASE                                      = 0; // Register base of module MMSS_MDSS_HW
uintPtr MMSS_MDP_REG_BASE                                          = 0; // Register base of module MMSS_MDP
uintPtr MMSS_MDP_SSPP_TOP0_REG_BASE                                = 0; // Register base of module MMSS_MDP_SSPP_TOP0
uintPtr MMSS_MDP_SMP_TOP0_REG_BASE                                 = 0; // Register base of module MMSS_MDP_SMP_TOP0
uintPtr MMSS_MDP_SSPP_TOP1_REG_BASE                                = 0; // Register base of module MMSS_MDP_SSPP_TOP1
uintPtr MMSS_MDP_SMP_TOP1_REG_BASE                                 = 0; // Register base of module MMSS_MDP_SMP_TOP1
uintPtr MMSS_MDP_DSPP_TOP0_REG_BASE                                = 0; // Register base of module MMSS_MDP_DSPP_TOP0
uintPtr MMSS_MDP_PERIPH_TOP0_REG_BASE                              = 0; // Register base of module MMSS_MDP_PERIPH_TOP0
uintPtr MMSS_MDP_SSPP_TOP2_REG_BASE                                = 0; // Register base of module MMSS_MDP_SSPP_TOP2
uintPtr MMSS_MDP_PERIPH_TOP1_REG_BASE                              = 0; // Register base of module MMSS_MDP_PERIPH_TOP1
uintPtr MMSS_MDP_CTL_0_REG_BASE                                    = 0; // Register base of module MMSS_MDP_CTL_0
uintPtr MMSS_MDP_VP_0_CURSOR_0_REG_BASE                            = 0; // Register base of module MMSS_MDP_VP_0_CURSOR_0
uintPtr MMSS_MDP_VP_0_CURSOR_0_SSPP_REG_BASE                       = 0; // Register base of module MMSS_MDP_VP_0_CURSOR_0_SSPP
uintPtr MMSS_MDP_VP_0_CURSOR_1_SSPP_REG_BASE                       = 0; // Register base of module MMSS_MDP_VP_0_CURSOR_1_SSPP
uintPtr MMSS_MDP_SSPP_IGC_LUT_REG_BASE                             = 0; // Register base of module MMSS_MDP_SSPP_IGC_LUT
uintPtr MMSS_MDP_VP_0_VIG_0_SSPP_REG_BASE                          = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_SSPP
uintPtr MMSS_MDP_VP_0_VIG_0_REG_BASE                               = 0; // Register base of module MMSS_MDP_VP_0_VIG_0
uintPtr MMSS_MDP_VP_0_VIG_0_QSEED3_REG_BASE                        = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_QSEED3
uintPtr MMSS_MDP_VP_0_VIG_0_QSEED3_COEF_LUT_REG_BASE               = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_QSEED3_COEF_LUT
uintPtr MMSS_MDP_VP_0_VIG_0_PA_HIST_REG_BASE                       = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_PA_HIST
uintPtr MMSS_MDP_VP_0_VIG_0_PA_MEMCOL_REG_BASE                     = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_PA_MEMCOL
uintPtr MMSS_MDP_VP_0_VIG_0_PA_SZONE_REG_BASE                      = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_PA_SZONE
uintPtr MMSS_MDP_VP_0_VIG_0_LUTV_RAM_REG_BASE                      = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_LUTV_RAM
uintPtr MMSS_MDP_VP_0_VIG_0_HIST_RAM_REG_BASE                      = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_HIST_RAM
uintPtr MMSS_MDP_VP_0_VIG_0_CSC_1_REG_BASE                         = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_CSC_1 
uintPtr MMSS_MDP_VP_0_VIG_0_PCC_REG_BASE                           = 0; // Register base of module MMSS_MDP_VP_0_VIG_0_PCC
uintPtr MMSS_MDP_VP_0_VIG_1_SSPP_REG_BASE                          = 0; // Register base of module MMSS_MDP_VP_0_VIG_1_SSPP
uintPtr MMSS_MDP_VP_0_DMA_0_SSPP_REG_BASE                          = 0; // Register base of module MMSS_MDP_VP_0_DMA_0_SSPP
uintPtr MMSS_MDP_VP_0_DMA_0_REG_BASE                               = 0; // Register base of module MMSS_MDP_VP_0_DMA_0
uintPtr MMSS_MDP_VP_0_DMA_0_PCC_REG_BASE                           = 0; // Register base of module MMSS_MDP_VP_0_DMA_0_PCC
uintPtr MMSS_MDP_VP_0_DMA_1_SSPP_REG_BASE                          = 0; // Register base of module MMSS_MDP_VP_0_DMA_1_SSPP
uintPtr MMSS_MDP_VP_0_LAYER_0_REG_BASE                             = 0; // Register base of module MMSS_MDP_VP_0_LAYER_0
uintPtr MMSS_MDP_VP_0_LAYER_0_PGC_REG_BASE                         = 0; // Register base of module MMSS_MDP_VP_0_LAYER_0_PGC
uintPtr MMSS_MDP_VP_0_DSPP_0_REG_BASE                              = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0
uintPtr MMSS_MDP_VP_0_DSPP_0_GAMUT_REG_BASE                        = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_GAMUT
uintPtr MMSS_MDP_VP_0_DSPP_0_PA_HIST_REG_BASE                      = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_PA_HIST 
uintPtr MMSS_MDP_VP_0_DSPP_0_HIST_RAM_REG_BASE                     = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_HIST_RAM 
uintPtr MMSS_MDP_VP_0_DSPP_0_LUTV_RAM_REG_BASE                     = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_LUTV_RAM
uintPtr MMSS_MDP_VP_0_DSPP_0_PA_MEMCOL_REG_BASE                    = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_PA_MEMCOL
uintPtr MMSS_MDP_VP_0_DSPP_0_PA_SZONE_REG_BASE                     = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_PA_SZONE
uintPtr MMSS_MDP_VP_0_DSPP_0_PCC_REG_BASE                          = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_PCC
uintPtr MMSS_MDP_VP_0_DSPP_0_PGC_REG_BASE                          = 0; // Register base of module MMSS_MDP_VP_0_DSPP_0_PGC
uintPtr MMSS_MDP_DEST_SCALER_0_REG_BASE                            = 0; // Register base of module MMSS_MDP_DEST_SCALER_0
uintPtr MMSS_MDP_DEST_SCALER_0_DEST_SCL0_REG_BASE                  = 0; // Register base of module MMSS_MDP_DEST_SCALER_0_DEST_SCL0
uintPtr MMSS_MDP_WB_2_REG_BASE                                     = 0; // Register base of module MMSS_MDP_WB_2
uintPtr MMSS_MDP_INTF_0_REG_BASE                                   = 0; // Register base of module MMSS_MDP_INTF_0
uintPtr MMSS_MDP_PP_0_REG_BASE                                     = 0; // Register base of module MMSS_MDP_PP_0
uintPtr MMSS_MDP_PPB_0_REG_BASE                                    = 0; // Register base of module MMSS_MDP_PPB_0
uintPtr MMSS_MDP_PPB_0_DITHER_REG_BASE                             = 0; // Register base of module MMSS_MDP_PPB_0_DITHER
uintPtr MMSS_MDP_CDM_0_REG_BASE                                    = 0; // Register base of module MMSS_MDP_CDM_0
uintPtr MMSS_MDP_CDM_0_CSC_10_REG_BASE                             = 0; // Register base of module MMSS_MDP_CDM_0_CSC_10
uintPtr MMSS_MDP_CDM_0_CDWN2_REG_BASE                              = 0; // Register base of module MMSS_MDP_CDM_0_CDWN2
uintPtr MMSS_MDP_CDM_0_HDMI_PACK_REG_BASE                          = 0; // Register base of module MMSS_MDP_CDM_0_HDMI_PACK
uintPtr MMSS_MDP_DSC_0_REG_BASE                                    = 0; // Register base of module MMSS_MDP_DSC_0
uintPtr MMSS_MDP_QDSS_REG_BASE                                     = 0; // Register base of module MMSS_MDP_QDSS
uintPtr MMSS_ROT_REG_BASE                                          = 0; // Register base of module MMSS_ROT
uintPtr MMSS_ROT_ROTTOP_REG_BASE                                   = 0; // Register base of module MMSS_ROT_ROTTOP
uintPtr MMSS_ROT_SSPP_REG_BASE                                     = 0; // Register base of module MMSS_ROT_SSPP
uintPtr MMSS_ROT_QDSS_REG_BASE                                     = 0; // Register base of module MMSS_ROT_QDSS
uintPtr MMSS_ROT_REGDMA_REG_BASE                                   = 0; // Register base of module MMSS_ROT_REGDMA
uintPtr MMSS_ROT_REGDMA_RAM_REG_BASE                               = 0; // Register base of module MMSS_ROT_REGDMA_RAM
uintPtr MMSS_ROT_REGDMA_CSR_REG_BASE                               = 0; // Register base of module MMSS_ROT_REGDMA_CSR
uintPtr MMSS_ROT_WB_REG_BASE                                       = 0; // Register base of module MMSS_ROT_WB
uintPtr MMSS_MDP_AADC_0_REG_BASE                                   = 0; // Register base of module MMSS_MDP_AADC_0
uintPtr MMSS_MDP_ENCR_NS_0_REG_BASE                                = 0; //  Register base of module MMSS_MDP_ENCR_NS_0
uintPtr MMSS_MDP_ENCR_S_0_REG_BASE                                 = 0; //  Register base of module MMSS_MDP_ENCR_S_0
uintPtr MMSS_DP_REG_BASE                                           = 0; // Register base of module MMSS_DP
uintPtr MMSS_HDMI_REG_BASE                                         = 0; // Register base of module MMSS_HDMI
uintPtr MMSS_HDMI_PHY_QSERDES_COM_QSERDES_COM_HDMI_COM_REG_BASE    = 0; // Register base of module HDMI_PHY_QSERDES_COM_QSERDES_COM_HDMI_COM
uintPtr MMSS_HDMI_PHY_QSERDES_TX_L0_QSERDES_TX_L0_HDMI_TX_REG_BASE = 0; // Register base of module HDMI_PHY_QSERDES_TX_L0_QSERDES_TX_L0_HDMI_TX
uintPtr MMSS_HDMI_PHY_QSERDES_TX_L1_QSERDES_TX_L1_HDMI_TX_REG_BASE = 0; // Register base of module HDMI_PHY_QSERDES_TX_L1_QSERDES_TX_L1_HDMI_TX
uintPtr MMSS_HDMI_PHY_QSERDES_TX_L2_QSERDES_TX_L2_HDMI_TX_REG_BASE = 0; // Register base of module HDMI_PHY_QSERDES_TX_L2_QSERDES_TX_L2_HDMI_TX
uintPtr MMSS_HDMI_PHY_QSERDES_TX_L3_QSERDES_TX_L3_HDMI_TX_REG_BASE = 0; // Register base of module HDMI_PHY_QSERDES_TX_L3_QSERDES_TX_L3_HDMI_TX
uintPtr HDMI_PHY_REG_BASE                                          = 0; // Register base of module HDMI_PHY
uintPtr VBIF_SDE_REG_BASE                                          = 0; // Register base of module VBIF_SDE
uintPtr VBIF_NRT_VBIF_ROT_REG_BASE                                 = 0; // Register base of module VBIF_NRT_VBIF_ROT 
uintPtr DSI_0_DSI_REG_BASE                                         = 0; // Register base of module DSI_0_DSI
uintPtr DSI_0_DSI_PHY_REG_BASE                                     = 0; // Register base of module DSI_0_DSI_PHY
uintPtr MMSS_DSI_0_PHY_DSIPHY_CKLN_DSIPHY_CKLN_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_0_DSI_PHY_CKLN_DSI_DATALN
uintPtr MMSS_DSI_0_PHY_DSIPHY_CMN_DSIPHY_CMN_DSI_COMMON_REG_BASE   = 0; // Register base of module DSI_0_DSI_PHY_CMN_DSI_COMMON
uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN0_DSIPHY_DLN0_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_0_DSI_PHY_DLN0_DSI_DATALN
uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN1_DSIPHY_DLN1_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_0_DSI_PHY_DLN1_DSI_DATALN
uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN2_DSIPHY_DLN2_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_0_DSI_PHY_DLN2_DSI_DATALN
uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN3_DSIPHY_DLN3_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_0_DSI_PHY_DLN3_DSI_DATALN
uintPtr MMSS_DSI_0_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE_REG_BASE = 0; // Register base of module DSI_0_DSI_PHY_PLL_DSI_QLINK_COM
uintPtr MMSS_DSI_0_PHY_REG_REG_BASE                                = 0; // Register base of module DSI_0_PHY_REG
uintPtr DSI_1_DSI_REG_BASE                                         = 0; // Register base of module DSI_1_DSI
uintPtr DSI_1_DSI_PHY_REG_BASE                                     = 0; // Register base of module DSI_1_DSI_PHY
uintPtr MMSS_DSI_1_PHY_DSIPHY_CKLN_DSIPHY_CKLN_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_1_DSI_PHY_CKLN_DSI_DATALN
uintPtr MMSS_DSI_1_PHY_DSIPHY_CMN_DSIPHY_CMN_DSI_COMMON_REG_BASE   = 0; // Register base of module DSI_1_DSI_PHY_CMN_DSI_COMMON
uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN0_DSIPHY_DLN0_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_1_DSI_PHY_DLN0_DSI_DATALN
uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN1_DSIPHY_DLN1_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_1_DSI_PHY_DLN1_DSI_DATALN
uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN2_DSIPHY_DLN2_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_1_DSI_PHY_DLN2_DSI_DATALN
uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN3_DSIPHY_DLN3_DSI_DATALN_REG_BASE = 0; // Register base of module DSI_1_DSI_PHY_DLN3_DSI_DATALN
uintPtr MMSS_DSI_1_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE_REG_BASE = 0; // Register base of module DSI_1_DSI_PHY_PLL_DSI_QLINK_COM
uintPtr MMSS_DSI_1_PHY_REG_REG_BASE                                = 0; //  egister base of module DSI_1_PHY_REG
uintPtr MMSS_DSI_ULPS_CLAMP_CTRL_OFFSET                            = 0; //  egister base of module MMSS_DSI_ULPS_CLAMP_CTRL



/*============================================================================
*       HAL Private Functions
============================================================================*/
      

/*============================================================================
*       HAL Public Functions
============================================================================*/


/****************************************************************************
HAL_MDSS_SetBaseAddress()

Description:
*
* Setups global register base address pointers
*/
void HAL_MDSS_SetBaseAddress(HAL_MDP_SWMappedHWBaseAddressesType *pMappedBaseAddress)
{

    if (0 != pMappedBaseAddress->uMdpAddress)
    {
        MDSS_BASE_PTR      = pMappedBaseAddress->uMdpAddress;
        SEC_CTRL_BASE_PTR  = pMappedBaseAddress->uSecCtrlAddress;
    }
}



#ifdef __cplusplus
}
#endif
