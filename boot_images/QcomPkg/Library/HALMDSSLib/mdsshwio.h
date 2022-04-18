/*! \file */

/*
===========================================================================

FILE:        mdsshwio.h

DESCRIPTION:  
  Top level MDSS HW Access Definition file.  It includes:
  [1] MDSS Register file
  [2] HW Access Macros
  [3] Additionally Defined Fields for HW Access

===========================================================================

                             Edit History
$Header: //components/rel/boot.xf/1.4/QcomPkg/Library/HALMDSSLib/mdsshwio.h#2 $
$DateTime: 2016/08/19 05:58:45 $


===========================================================================
  Copyright (c) 2010-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/
#ifndef MDSSHWIO_H
#define MDSSHWIO_H



/* -----------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------- */

// Basic Register Access Macros
#include "mdsshalhwio.h"

// Database Header file of all MDSS Registers: MDP, DSI, HDMI and eDP
// Static MDP Base Defined Here

extern uintPtr MDSS_BASE_PTR;

/* HW module register base */
extern uintPtr MMSS_MDSS_HW_REG_BASE;
extern uintPtr MMSS_MDP_REG_BASE;                                          //  Register base of module MMSS_MDP
extern uintPtr MMSS_MDP_SSPP_TOP0_REG_BASE;                                //  Register base of module MMSS_MDP_SSPP_TOP0
extern uintPtr MMSS_MDP_SMP_TOP0_REG_BASE;                                 //  Register base of module MMSS_MDP_SMP_TOP0
extern uintPtr MMSS_MDP_SSPP_TOP1_REG_BASE;                                //  Register base of module MMSS_MDP_SSPP_TOP1
extern uintPtr MMSS_MDP_SMP_TOP1_REG_BASE;                                 //  Register base of module MMSS_MDP_SMP_TOP1
extern uintPtr MMSS_MDP_DSPP_TOP0_REG_BASE;                                //  Register base of module MMSS_MDP_DSPP_TOP0
extern uintPtr MMSS_MDP_PERIPH_TOP0_REG_BASE;                              //  Register base of module MMSS_MDP_PERIPH_TOP0
extern uintPtr MMSS_MDP_SSPP_TOP2_REG_BASE;                                //  Register base of module MMSS_MDP_SSPP_TOP2
extern uintPtr MMSS_MDP_PERIPH_TOP1_REG_BASE;                              //  Register base of module MMSS_MDP_PERIPH_TOP1
extern uintPtr MMSS_MDP_CTL_0_REG_BASE;                                    //  Register base of module MMSS_MDP_CTL_0
extern uintPtr MMSS_MDP_VP_0_CURSOR_0_REG_BASE;                            //  Register base of module MMSS_MDP_VP_0_CURSOR_0
extern uintPtr MMSS_MDP_VP_0_CURSOR_0_SSPP_REG_BASE;                       //  Register base of module MMSS_MDP_VP_0_CURSOR_0_SSPP
extern uintPtr MMSS_MDP_VP_0_CURSOR_1_SSPP_REG_BASE;                       //  Register base of module MMSS_MDP_VP_0_CURSOR_1_SSPP
extern uintPtr MMSS_MDP_SSPP_IGC_LUT_REG_BASE;                             //  Register base of module MMSS_MDP_SSPP_IGC_LUT
extern uintPtr MMSS_MDP_VP_0_VIG_0_SSPP_REG_BASE;                          //  Register base of module MMSS_MDP_VP_0_VIG_0_SSPP
extern uintPtr MMSS_MDP_VP_0_VIG_0_REG_BASE;                               //  Register base of module MMSS_MDP_VP_0_VIG_0
extern uintPtr MMSS_MDP_VP_0_VIG_0_QSEED3_REG_BASE;                        //  Register base of module MMSS_MDP_VP_0_VIG_0_QSEED3      
extern uintPtr MMSS_MDP_VP_0_VIG_0_QSEED3_COEF_LUT_REG_BASE;               //  Register base of module MMSS_MDP_VP_0_VIG_0_QSEED3_COEF_LUT           
extern uintPtr MMSS_MDP_VP_0_VIG_0_PA_HIST_REG_BASE;                       //  Register base of module MMSS_MDP_VP_0_VIG_0_PA_HIST       
extern uintPtr MMSS_MDP_VP_0_VIG_0_PA_MEMCOL_REG_BASE;                     //  Register base of module MMSS_MDP_VP_0_VIG_0_PA_MEMCOL     
extern uintPtr MMSS_MDP_VP_0_VIG_0_PA_SZONE_REG_BASE;                      //  Register base of module MMSS_MDP_VP_0_VIG_0_PA_SZONE   
extern uintPtr MMSS_MDP_VP_0_VIG_0_LUTV_RAM_REG_BASE;                      //  Register base of module MMSS_MDP_VP_0_VIG_0_LUTV_RAM        
extern uintPtr MMSS_MDP_VP_0_VIG_0_HIST_RAM_REG_BASE;                      //  Register base of module MMSS_MDP_VP_0_VIG_0_HIST_RAM        
extern uintPtr MMSS_MDP_VP_0_VIG_0_CSC_1_REG_BASE;                         //  Register base of module MMSS_MDP_VP_0_VIG_0_CSC_1 
extern uintPtr MMSS_MDP_VP_0_VIG_0_PCC_REG_BASE;                           //  Register base of module MMSS_MDP_VP_0_VIG_0_PCC
extern uintPtr MMSS_MDP_VP_0_VIG_1_SSPP_REG_BASE;                          //  Register base of module MMSS_MDP_VP_0_VIG_1_SSPP
extern uintPtr MMSS_MDP_VP_0_DMA_0_SSPP_REG_BASE;                          //  Register base of module MMSS_MDP_VP_0_DMA_0_SSPP
extern uintPtr MMSS_MDP_VP_0_DMA_0_REG_BASE;                               //  Register base of module MMSS_MDP_VP_0_DMA_0
extern uintPtr MMSS_MDP_VP_0_DMA_0_PCC_REG_BASE;                           //  Register base of module MMSS_MDP_VP_0_DMA_0_PCC
extern uintPtr MMSS_MDP_VP_0_DMA_1_SSPP_REG_BASE;                          //  Register base of module MMSS_MDP_VP_0_DMA_1_SSPP
extern uintPtr MMSS_MDP_VP_0_LAYER_0_REG_BASE;                             //  Register base of module MMSS_MDP_VP_0_LAYER_0
extern uintPtr MMSS_MDP_VP_0_LAYER_0_PGC_REG_BASE;                         //  Register base of module MMSS_MDP_VP_0_LAYER_0_PGC
extern uintPtr MMSS_MDP_VP_0_DSPP_0_REG_BASE;                              //  Register base of module MMSS_MDP_VP_0_DSPP_0
extern uintPtr MMSS_MDP_VP_0_DSPP_0_GAMUT_REG_BASE;                        //  Register base of module MMSS_MDP_VP_0_DSPP_0_GAMUT
extern uintPtr MMSS_MDP_VP_0_DSPP_0_PA_HIST_REG_BASE;                      //  Register base of module MMSS_MDP_VP_0_DSPP_0_PA_HIST
extern uintPtr MMSS_MDP_VP_0_DSPP_0_HIST_RAM_REG_BASE;                     //  Register base of module MMSS_MDP_VP_0_DSPP_0_HIST_RAM
extern uintPtr MMSS_MDP_VP_0_DSPP_0_LUTV_RAM_REG_BASE;                     //  Register base of module MMSS_MDP_VP_0_DSPP_0_LUTV_RAM
extern uintPtr MMSS_MDP_VP_0_DSPP_0_PA_MEMCOL_REG_BASE;                    //  Register base of module MMSS_MDP_VP_0_DSPP_0_PA_MEMCOL
extern uintPtr MMSS_MDP_VP_0_DSPP_0_PA_SZONE_REG_BASE;                     //  Register base of module MMSS_MDP_VP_0_DSPP_0_PA_SZONE
extern uintPtr MMSS_MDP_VP_0_DSPP_0_PCC_REG_BASE;                          //  Register base of module MMSS_MDP_VP_0_DSPP_0_PCC 
extern uintPtr MMSS_MDP_VP_0_DSPP_0_PGC_REG_BASE;                          //  Register base of module MMSS_MDP_VP_0_DSPP_0_PGC
extern uintPtr MMSS_MDP_DEST_SCALER_0_REG_BASE;                            //  Register base of module MMSS_MDP_DEST_SCALER_0
extern uintPtr MMSS_MDP_DEST_SCALER_0_DEST_SCL0_REG_BASE;                  //  Register base of module MMSS_MDP_DEST_SCALER_0_DEST_SCL0
extern uintPtr MMSS_MDP_WB_2_REG_BASE;                                     //  Register base of module MMSS_MDP_WB_2
extern uintPtr MMSS_MDP_INTF_0_REG_BASE;                                   //  Register base of module MMSS_MDP_INTF_0
extern uintPtr MMSS_MDP_PP_0_REG_BASE;                                     //  Register base of module MMSS_MDP_PP_0
extern uintPtr MMSS_MDP_PPB_0_REG_BASE;                                    //  Register base of module MMSS_MDP_PPB_0
extern uintPtr MMSS_MDP_PPB_0_DITHER_REG_BASE;                             //  Register base of module MMSS_MDP_PPB_0_DITHER
extern uintPtr MMSS_MDP_CDM_0_REG_BASE;                                    //  Register base of module MMSS_MDP_CDM_0
extern uintPtr MMSS_MDP_CDM_0_CSC_10_REG_BASE;                             //  Register base of module MMSS_MDP_CDM_0_CSC_10
extern uintPtr MMSS_MDP_CDM_0_CDWN2_REG_BASE;                              //  Register base of module MMSS_MDP_CDM_0_CDWN2
extern uintPtr MMSS_MDP_CDM_0_HDMI_PACK_REG_BASE;                          //  Register base of module MMSS_MDP_CDM_0_HDMI_PACK
extern uintPtr MMSS_MDP_DSC_0_REG_BASE;                                    //  Register base of module MMSS_MDP_DSC_0
extern uintPtr MMSS_MDP_QDSS_REG_BASE;                                     //  Register base of module MMSS_MDP_QDSS
extern uintPtr MMSS_ROT_REG_BASE;                                          //  Register base of module MMSS_ROT 
extern uintPtr MMSS_ROT_ROTTOP_REG_BASE;                                   //  Register base of module MMSS_ROT_ROTTOP
extern uintPtr MMSS_ROT_SSPP_REG_BASE;                                     //  Register base of module MMSS_ROT_SSPP
extern uintPtr MMSS_ROT_QDSS_REG_BASE;                                     //  Register base of module MMSS_ROT_QDSS 
extern uintPtr MMSS_ROT_REGDMA_REG_BASE;                                   //  Register base of module MMSS_ROT_REGDMA
extern uintPtr MMSS_ROT_REGDMA_RAM_REG_BASE;                               //  Register base of module MMSS_ROT_REGDMA_RAM
extern uintPtr MMSS_ROT_REGDMA_CSR_REG_BASE;                               //  Register base of module MMSS_ROT_REGDMA_CSR
extern uintPtr MMSS_ROT_WB_REG_BASE;                                       //  Register base of module MMSS_ROT_WB
extern uintPtr MMSS_MDP_AADC_0_REG_BASE;                                   //  Register base of module MMSS_MDP_AADC_0
extern uintPtr MMSS_MDP_ENCR_NS_0_REG_BASE;                                //  Register base of module MMSS_MDP_ENCR_NS_0
extern uintPtr MMSS_MDP_ENCR_S_0_REG_BASE;                                 //  Register base of module MMSS_MDP_ENCR_S_0
extern uintPtr MMSS_DP_REG_BASE;                                           //  Register base of module MMSS_DP
extern uintPtr MMSS_HDMI_REG_BASE;                                         //  Register base of module MMSS_HDMI
extern uintPtr HDMI_PHY_REG_BASE;                                          //  Register base of module HDMI_PHY
extern uintPtr MMSS_HDMI_PHY_QSERDES_COM_QSERDES_COM_HDMI_COM_REG_BASE;    //  Register base of module HDMI_PHY_QSERDES_COM_QSERDES_COM_HDMI_COM
extern uintPtr MMSS_HDMI_PHY_QSERDES_TX_L0_QSERDES_TX_L0_HDMI_TX_REG_BASE; //  Register base of module HDMI_PHY_QSERDES_TX_L0_QSERDES_TX_L0_HDMI_TX
extern uintPtr MMSS_HDMI_PHY_QSERDES_TX_L1_QSERDES_TX_L1_HDMI_TX_REG_BASE; //  Register base of module HDMI_PHY_QSERDES_TX_L1_QSERDES_TX_L1_HDMI_TX
extern uintPtr MMSS_HDMI_PHY_QSERDES_TX_L2_QSERDES_TX_L2_HDMI_TX_REG_BASE; //  Register base of module HDMI_PHY_QSERDES_TX_L2_QSERDES_TX_L2_HDMI_TX
extern uintPtr MMSS_HDMI_PHY_QSERDES_TX_L3_QSERDES_TX_L3_HDMI_TX_REG_BASE; //  Register base of module HDMI_PHY_QSERDES_TX_L3_QSERDES_TX_L3_HDMI_TX
extern uintPtr VBIF_SDE_REG_BASE;                                          //  Register base of module VBIF_SDE
extern uintPtr VBIF_NRT_REG_BASE;                                          //  Register base of module VBIF_NRT
extern uintPtr VBIF_NRT_VBIF_ROT_REG_BASE;                                 //  Register base of module VBIF_NRT_VBIF_ROT
extern uintPtr XPU_REG_BASE;                                               //  Register base of module XPU
extern uintPtr MDSS_SEC_HDCP_SEC_TZ_ONLY_REG_BASE;                         //  Register base of module MDSS_SEC_HDCP_SEC_TZ
extern uintPtr MDSS_SEC_HDCP_SEC_TZ_HV_REG_BASE;                           //  Register base of module MDSS_SEC_HDCP_SEC_TZ_HV
extern uintPtr MDSS_SEC_DSI_0_SEC_REG_BASE;                                //  Register base of module MDSS_SEC_DSI_0_SEC
extern uintPtr MDSS_SEC_DSI_1_SEC_REG_BASE;                                //  Register base of module MDSS_SEC_DSI_1_SEC
extern uintPtr MDSS_SEC_DP_HDCP_SEC_TZ_HV_REG_BASE;                        //  Register base of module MDSS_SEC_DP_HDCP_SEC_TZ_HV
extern uintPtr MDSS_SEC_HDCP_SEC_TZ_HV_HLOS_REG_BASE;                      //  Register base of module MDSS_SEC_HDCP_SEC_TZ_HV_HLOS
extern uintPtr MDSS_SEC_DP_HDCP_SEC_TZ_HV_HLOS_REG_BASE;                   //  Register base of module MDSS_SEC_DP_HDCP_SEC_TZ_HV_HLOS
extern uintPtr MDSS_SEC_HDCP_SEC_DBG_REG_BASE;                             //  Register base of module MDSS_SEC_HDCP_SEC_DBG
extern uintPtr MDSS_SEC_DP_HDCP_SEC_DBG_REG_BASE;                          //  Register base of module MDSS_SEC_DP_HDCP_SEC_DBG
extern uintPtr DSI_0_DSI_REG_BASE;                                         //  Register base of module DSI_0_DSI
extern uintPtr DSI_0_DSI_PHY_REG_BASE;                                     //  Register base of module DSI_0_DSI_PHY
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_CKLN_DSIPHY_CKLN_DSI_DATALN_REG_BASE; //  Register base of module DSI_0_DSI_PHY_CKLN_DSI_DATALN
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_CMN_DSIPHY_CMN_DSI_COMMON_REG_BASE;   //  Register base of module DSI_0_DSI_PHY_CMN_DSI_COMMON
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN0_DSIPHY_DLN0_DSI_DATALN_REG_BASE; //  Register base of module DSI_0_DSI_PHY_DLN0_DSI_DATALN
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN1_DSIPHY_DLN1_DSI_DATALN_REG_BASE; //  Register base of module DSI_0_DSI_PHY_DLN1_DSI_DATALN
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN2_DSIPHY_DLN2_DSI_DATALN_REG_BASE; //  Register base of module DSI_0_DSI_PHY_DLN2_DSI_DATALN
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_DLN3_DSIPHY_DLN3_DSI_DATALN_REG_BASE; //  Register base of module DSI_0_DSI_PHY_DLN3_DSI_DATALN
extern uintPtr MMSS_DSI_0_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE_REG_BASE; //  Register base of module DSI_0_DSI_PHY_PLL_DSI_QLINK_COM
extern uintPtr MMSS_DSI_0_PHY_REG_REG_BASE;                                //  Register base of module DSI_0_PHY_REG
extern uintPtr DSI_1_DSI_REG_BASE;                                         //  Register base of module DSI_1_DSI
extern uintPtr DSI_1_DSI_PHY_REG_BASE;                                     //  Register base of module DSI_1_DSI_PHY
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_CKLN_DSIPHY_CKLN_DSI_DATALN_REG_BASE; //  Register base of module DSI_1_DSI_PHY_CKLN_DSI_DATALN
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_CMN_DSIPHY_CMN_DSI_COMMON_REG_BASE;   //  Register base of module DSI_1_DSI_PHY_CMN_DSI_COMMON
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN0_DSIPHY_DLN0_DSI_DATALN_REG_BASE; //  Register base of module DSI_1_DSI_PHY_DLN0_DSI_DATALN
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN1_DSIPHY_DLN1_DSI_DATALN_REG_BASE; //  Register base of module DSI_1_DSI_PHY_DLN1_DSI_DATALN
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN2_DSIPHY_DLN2_DSI_DATALN_REG_BASE; //  Register base of module DSI_1_DSI_PHY_DLN2_DSI_DATALN
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_DLN3_DSIPHY_DLN3_DSI_DATALN_REG_BASE; //  Register base of module DSI_1_DSI_PHY_DLN3_DSI_DATALN
extern uintPtr MMSS_DSI_1_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE_REG_BASE; //  Register base of module DSI_1_DSI_PHY_PLL_DSI_QLINK_COM
extern uintPtr MMSS_DSI_1_PHY_REG_REG_BASE;                                //  Register base of module DSI_1_PHY_REG

/* HW register offset */
extern uintPtr MMSS_DSI_ULPS_CLAMP_CTRL_OFFSET;                            // DSI ULPS clamp controller register offset

#define        MMSS_MDSS_REG_BASE                              (MDSS_BASE_PTR)

#define        MMSS_DSI_0_PHY_REG_BASE                         (DSI_0_DSI_PHY_REG_BASE)
#define        MMSS_DSI_0_PHY_PLL_REG_BASE                     (MMSS_DSI_0_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE_REG_BASE)
#define        MMSS_DSI_1_PHY_REG_BASE                         (DSI_1_DSI_PHY_REG_BASE)
#define        MMSS_DSI_1_PHY_PLL_REG_BASE                     (MMSS_DSI_1_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE_REG_BASE)
#define        MMSS_HDMI_PHY_REG_BASE                          (HDMI_PHY_REG_BASE)

#define        MMSS_BASE                                       ((uint32)0xFD800000)


#include "mdssreg.h"

#endif // MDSSHWIO_H
