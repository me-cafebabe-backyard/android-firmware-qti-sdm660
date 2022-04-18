/*=======================================================================*//**
 * @file        qusb_phy_settings.c
 * @author:     kameya
 * @date        19-Jan-2016
 *
 * @brief       QUSB (Qualcomm High-Speed USB) High Speed(HS) and 
 *              Super Speed (SS) PHY settings.
 *
 * @details     This file contains settings of the HS PHY.
 *
 * @note        
 *
 *              Copyright 2016 Qualcomm Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/


// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 2016-10-05	 arung   Update for SDM660
// 2016-01-19    kameya  First Draft
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h" // basic types as byte word uint32 etc
#include "Sdm660Pkg/Library/QusbDciCommonLib/qusb_dci_common_hwio_Sdm660.h"
#include "qusb_dci_common.h"

//----------------------------------------------------------------------------
// Static Variable Definitions
//----------------------------------------------------------------------------

//============================================================================
// QUSB High-Speed PHY Configuration Array
//============================================================================

static const uint32 qusb_dci_hs_phy_cfg_address[QUSB_DCI_HS_PHY_CFG_ARRAY_ENTRY_CNT] = 
{
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE1_ADDR,                       // 0  : (0xF8)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_ADDR,                       // 1  : (0xB3)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE3_ADDR,                       // 2  : (0x83)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE4_ADDR,                       // 3  : (0xC0)
  //---------------------------------------------------------------------------
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TEST2_ADDR,                       // 4  : (0x14)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_TUNE_ADDR,                         // 5  : (0x30)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_USER_CTL1_ADDR,                    // 6  : (0x79)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_USER_CTL2_ADDR,                    // 7  : (0x21)
  //---------------------------------------------------------------------------
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE5_ADDR,                       // 8  : (0x00)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_PWR_CTL_ADDR,                      // 9  : (0x00)
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_AUTOPGM_CTL1_ADDR,                 // 10 : (0x9F)
  QUSB_HWIO_ADDR_END,                                                          // 11 : (0x00)
};

static const uint8 qusb_dci_hs_phy_cfg_value[QUSB_DCI_HS_PHY_CFG_ARRAY_ENTRY_CNT] = 
{
  /*HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE1_ADDR,                      0  */ (0xF8),
  /*HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_ADDR,                      1  */ (0xB3),
  /*HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE3_ADDR,                      2  */ (0x83),
  /*HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE4_ADDR,                      3  */ (0xC0),
  //---------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TEST2_ADDR,                     4  */ (0x14),
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_TUNE_ADDR,                       5  */ (0x30),
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_USER_CTL1_ADDR,                  6  */ (0x79),
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_USER_CTL2_ADDR,                  7  */ (0x21),
  //----------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE5_ADDR,                     8  */ (0x00),
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_PWR_CTL_ADDR,                    9  */ (0x00),
  /* HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_AUTOPGM_CTL1_ADDR,               10 */ (0x9F),
  /* QUSB_HWIO_ADDR_END,                                                        11 */ (0x00),
};

//============================================================================
// QUSB Super-Speed PHY Configuration Array
//============================================================================

// Values according to SS QMP PHY spec. given out by PHY Team Oct 2015
static const uint32 qusb_dci_ss_phy_cfg_address_common[QUSB_DCI_SS_PHY_COMMON_CFG_ARRAY_ENTRY_CNT] =
{
  QUSB_HWIO_ADDR_EMPTY,                                                   // 000 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 001 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 002 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BG_TRIM_ADDR,                        // 003 : (0x0F),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SYSCLK_EN_SEL_ADDR,                  // 004 : (0x14),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_ADDR,            // 005 : (0x08),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CLK_SELECT_ADDR,                     // 006 : (0x30),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SYS_CLK_CTRL_ADDR,                   // 007 : (0x06),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_EMPTY,                                                   // 008 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_RESETSM_CNTRL_ADDR,                  // 009 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_RESETSM_CNTRL2_ADDR,                 // 010 : (0x08),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 011 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CMN_CONFIG_ADDR,                     // 012 : (0x06),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 013 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SVS_MODE_CLK_SEL_ADDR,               // 014 : (0x01),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_HSCLK_SEL_ADDR,                      // 015 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_EMPTY,                                                   // 016 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DEC_START_MODE0_ADDR,                // 017 : (0x82),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_MODE_00_ADDR,                     // 018 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_MODE_00_ADDR,                     // 019 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DIV_FRAC_START1_MODE0_ADDR,          // 020 : (0x55),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DIV_FRAC_START2_MODE0_ADDR,          // 021 : (0x55),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DIV_FRAC_START3_MODE0_ADDR,          // 022 : (0x03),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 023 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CP_CTRL_MODE0_ADDR,                  // 024 : (0x0b),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_PLL_RCTRL_MODE0_ADDR,                // 025 : (0x16),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_PLL_CCTRL_MODE0_ADDR,                // 026 : (0x28),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 027 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_INTEGLOOP_GAIN0_MODE0_ADDR,          // 028 : (0x80),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_INTEGLOOP_GAIN1_MODE0_ADDR,          // 029 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CORECLK_DIV_ADDR,                    // 030 : (0x0A),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 031 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP1_MODE0_ADDR,                // 032 : (0x15),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP2_MODE0_ADDR,                // 033 : (0x34),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP3_MODE0_ADDR,                // 034 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 035 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP_EN_ADDR,                    // 036 : (0x00), 
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CORE_CLK_EN_ADDR,                    // 037 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 039 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP_CFG_ADDR,                   // 040 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_VCO_TUNE_MAP_ADDR,                   // 041 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BG_TIMER_ADDR,                       // 042 : (0x0A),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_EN_CENTER_ADDR,                  // 043 : (0x01),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_PER1_ADDR,                       // 044 : (0x31),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_PER2_ADDR,                       // 045 : (0x01),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_ADJ_PER1_ADDR,                   // 046 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_ADJ_PER2_ADDR,                   // 047 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_EMPTY,                                                   // 048 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 049 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_STEP_SIZE1_ADDR,                 // 050 : (0xDE),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_STEP_SIZE2_ADDR,                 // 051 : (0x07),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_PLL_IVCO_ADDR,                       // 052 : (0x0F),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 053 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_INTEGLOOP_INITVAL_ADDR,              // 054 : (0x80),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BIAS_EN_CTRL_BY_PSM_ADDR,            // 055 : (0x01),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FASTLOCK_FO_GAIN_ADDR,          // 056 : (0x0B),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FASTLOCK_FO_GAIN_ADDR,          // 057 : (0x0B),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_PI_CONTROLS_ADDR,               // 058 : (0x80),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_PI_CONTROLS_ADDR,               // 059 : (0x80),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FASTLOCK_COUNT_LOW_ADDR,        // 060 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FASTLOCK_COUNT_LOW_ADDR,        // 061 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FASTLOCK_COUNT_HIGH_ADDR,       // 062 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FASTLOCK_COUNT_HIGH_ADDR,       // 063 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FO_GAIN_ADDR,                   // 064 : (0x0A),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FO_GAIN_ADDR,                   // 065 : (0x0A),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_SO_GAIN_ADDR,                   // 066 : (0x06),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_SO_GAIN_ADDR,                   // 067 : (0x06),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_EMPTY,                                                   // 068 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 069 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_SO_SATURATION_AND_ENABLE_ADDR,  // 070 : (0x75),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_SO_SATURATION_AND_ENABLE_ADDR,  // 071 : (0x75),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL2_ADDR,          // 072 : (0x02),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL2_ADDR,          // 073 : (0x02),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL3_ADDR,          // 074 : (0x4E),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL3_ADDR,          // 075 : (0x4E),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_EMPTY,                                                   // 076 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 077 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL4_ADDR,          // 078 : (0x18),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL4_ADDR,          // 079 : (0x18),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR,    // 080 : (0x77),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR,    // 081 : (0x77),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_OFFSET_ADAPTOR_CNTRL2_ADDR,       // 082 : (0x80),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_OFFSET_ADAPTOR_CNTRL2_ADDR,       // 083 : (0x80),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_VGA_CAL_CNTRL2_ADDR,                 // 084 : (0x0A),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_VGA_CAL_CNTRL2_ADDR,                 // 085 : (0x0A),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_SIGDET_CNTRL_ADDR,                   // 086 : (0x03),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_SIGDET_CNTRL_ADDR,                   // 087 : (0x03),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_SIGDET_DEGLITCH_CNTRL_ADDR,          // 089 : (0x16),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_SIGDET_DEGLITCH_CNTRL_ADDR,          // 089 : (0x16),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_SIGDET_ENABLES_ADDR,                 // 090 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_SIGDET_ENABLES_ADDR,                 // 091 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,                  // 092 : (0x10),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,                  // 093 : (0x10),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR,               // 094 : (0x12),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR,               // 095 : (0x12),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_LANE_MODE_1_ADDR,                    // 096 : (0xC6),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_LANE_MODE_1_ADDR,                    // 097 : (0xC6),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 098 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 099 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR,        // 100 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR,        // 101 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR,        // 102 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR,        // 103 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_PCS_TXMGN_V0_ADDR,                               // 104 : (0x9F),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 105 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_PCS_TXDEEMPH_M6DB_V0_ADDR,                       // 106 : (0x17),
  HWIO_PERIPH_SS_USB3PHY_PCS_TXDEEMPH_M3P5DB_V0_ADDR,                     // 107 : (0x0F),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNTRL2_ADDR,                             // 108 : (0x83),
  HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNTRL1_ADDR,                             // 109 : (0x02),
  HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNT_VAL_L_ADDR,                          // 110 : (0x09),
  HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNT_VAL_H_TOL_ADDR,                      // 111 : (0xA2),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_PCS_FLL_MAN_CODE_ADDR,                           // 112 : (0x85),
  HWIO_PERIPH_SS_USB3PHY_PCS_LOCK_DETECT_CONFIG1_ADDR,                    // 113 : (0xD1),
  HWIO_PERIPH_SS_USB3PHY_PCS_LOCK_DETECT_CONFIG2_ADDR,                    // 114 : (0x1F),
  HWIO_PERIPH_SS_USB3PHY_PCS_LOCK_DETECT_CONFIG3_ADDR,                    // 115 : (0x47),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_PCS_RXEQTRAINING_WAIT_TIME_ADDR,                 // 116 : (0x75),
  HWIO_PERIPH_SS_USB3PHY_PCS_RXEQTRAINING_RUN_TIME_ADDR,                  // 117 : (0x13),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 118 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 119 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_PCS_LFPS_TX_ECSTART_EQTLOCK_ADDR,                // 120 : (0x86),
  HWIO_PERIPH_SS_USB3PHY_PCS_PWRUP_RESET_DLY_TIME_AUXCLK_ADDR,            // 121 : (0x04),
  HWIO_PERIPH_SS_USB3PHY_PCS_TSYNC_RSYNC_TIME_ADDR,                       // 122 : (0x44),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 123 : (0x00),
  //--------------------------------------------------------------------------------------
  HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_P1U2_L_ADDR,                   // 124 : (0xE7),
  HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_P1U2_H_ADDR,                   // 125 : (0x03),
  HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_U3_L_ADDR,                     // 126 : (0x40),
  HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_U3_H_ADDR,                     // 127 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_EMPTY,                                                   // 128 : (0x00),
  HWIO_PERIPH_SS_USB3PHY_PCS_RX_SIGDET_LVL_ADDR,                          // 129 : (0x88),
  HWIO_PERIPH_SS_USB3PHY_PCS_MISC_TYPEC_CTRL_ADDR,                        // 130 : (0x00),
  QUSB_HWIO_ADDR_EMPTY,                                                   // 131 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_END,                                                     // 132 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 133 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 134 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 135 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_END,                                                     // 136 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 137 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 138 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 139 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_END,                                                     // 140 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 141 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 142 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 143 : (0x00),
  //--------------------------------------------------------------------------------------
  QUSB_HWIO_ADDR_END,                                                     // 144 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 145 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 146 : (0x00),
  QUSB_HWIO_ADDR_END,                                                     // 147 : (0x00),

};

ALIGN(4)
static const uint8 qusb_dci_ss_phy_cfg_value_common[QUSB_DCI_SS_PHY_COMMON_CFG_ARRAY_ENTRY_CNT] =
{
  /* QUSB_HWIO_ADDR_EMPTY,                                                       000  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       001  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       002  */(0x00),
  /*HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BG_TRIM_ADDR,                             003  */(0x0F),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SYSCLK_EN_SEL_ADDR,                      004  */(0x14),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_ADDR,                005  */(0x08),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CLK_SELECT_ADDR,                         006  */(0x30),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SYS_CLK_CTRL_ADDR,                       007  */(0x06),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_EMPTY,                                                       008  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_RESETSM_CNTRL_ADDR,                      009  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_RESETSM_CNTRL2_ADDR,                     010  */(0x08),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       011  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CMN_CONFIG_ADDR,                         012  */(0x06),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       013  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SVS_MODE_CLK_SEL_ADDR,                   014  */(0x01),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_HSCLK_SEL_ADDR,                          015  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_EMPTY,                                                       016  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DEC_START_MODE0_ADDR,                    017  */(0x82),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_MODE_00_ADDR,                         018  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_MODE_00_ADDR,                         019  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DIV_FRAC_START1_MODE0_ADDR,              020  */(0x55),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DIV_FRAC_START2_MODE0_ADDR,              021  */(0x55),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_DIV_FRAC_START3_MODE0_ADDR,              022  */(0x03),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       023  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CP_CTRL_MODE0_ADDR,                      024  */(0x0b),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_PLL_RCTRL_MODE0_ADDR,                    025  */(0x16),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_PLL_CCTRL_MODE0_ADDR,                    026  */(0x28),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       027  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_INTEGLOOP_GAIN0_MODE0_ADDR,              028  */(0x80),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_INTEGLOOP_GAIN1_MODE0_ADDR,              029  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CORECLK_DIV_ADDR,                        030  */(0x0A),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       031  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP1_MODE0_ADDR,                    032  */(0x15),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP2_MODE0_ADDR,                    033  */(0x34),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP3_MODE0_ADDR,                    034  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       035  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP_EN_ADDR,                        036  */(0x00), 
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_CORE_CLK_EN_ADDR,                        037  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       039  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_LOCK_CMP_CFG_ADDR,                       040  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_VCO_TUNE_MAP_ADDR,                       041  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BG_TIMER_ADDR,                           042  */(0x0A),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_EN_CENTER_ADDR,                      043  */(0x01),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_PER1_ADDR,                           044  */(0x31),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_PER2_ADDR,                           045  */(0x01),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_ADJ_PER1_ADDR,                       046  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_ADJ_PER2_ADDR,                       047  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_EMPTY,                                                       048  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       049  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_STEP_SIZE1_ADDR,                     050  */(0xDE),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_SSC_STEP_SIZE2_ADDR,                     051  */(0x07),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_PLL_IVCO_ADDR,                           052  */(0x0F),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       053  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_INTEGLOOP_INITVAL_ADDR,                  054  */(0x80),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_COM_BIAS_EN_CTRL_BY_PSM_ADDR,                055  */(0x01),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FASTLOCK_FO_GAIN_ADDR,              056  */(0x0B),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FASTLOCK_FO_GAIN_ADDR,              057  */(0x0B),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_PI_CONTROLS_ADDR,                   058  */(0x80),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_PI_CONTROLS_ADDR,                   059  */(0x80),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FASTLOCK_COUNT_LOW_ADDR,            060  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FASTLOCK_COUNT_LOW_ADDR,            061  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FASTLOCK_COUNT_HIGH_ADDR,           062  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FASTLOCK_COUNT_HIGH_ADDR,           063  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_FO_GAIN_ADDR,                       064  */(0x0A),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_FO_GAIN_ADDR,                       065  */(0x0A),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_SO_GAIN_ADDR,                       066  */(0x06),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_SO_GAIN_ADDR,                       067  */(0x06),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_EMPTY,                                                       068  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       069  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_UCDR_SO_SATURATION_AND_ENABLE_ADDR,      070  */(0x75),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_UCDR_SO_SATURATION_AND_ENABLE_ADDR,      071  */(0x75),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL2_ADDR,              072  */(0x02),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL2_ADDR,              073  */(0x02),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL3_ADDR,              074  */(0x4E),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL3_ADDR,              075  */(0x4E),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_EMPTY,                                                       076  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       077  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQU_ADAPTOR_CNTRL4_ADDR,              078  */(0x18),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQU_ADAPTOR_CNTRL4_ADDR,              079  */(0x18),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR,        080  */(0x77),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_EQ_OFFSET_ADAPTOR_CNTRL1_ADDR,        081  */(0x77),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_RX_OFFSET_ADAPTOR_CNTRL2_ADDR,           082  */(0x80),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_RX_OFFSET_ADAPTOR_CNTRL2_ADDR,           083  */(0x80),
  //--------------------------------------------------------------------------------------
  /*HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_VGA_CAL_CNTRL2_ADDR,                      084  */(0x0A),
  /*HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_VGA_CAL_CNTRL2_ADDR,                      085  */(0x0A),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_SIGDET_CNTRL_ADDR,                       086  */(0x03),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_SIGDET_CNTRL_ADDR,                       087  */(0x03),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_SIGDET_DEGLITCH_CNTRL_ADDR,              088  */(0x16),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_SIGDET_DEGLITCH_CNTRL_ADDR,              089  */(0x16),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXA_SIGDET_ENABLES_ADDR,                     090  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_RXB_SIGDET_ENABLES_ADDR,                     091  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,                      092  */(0x10),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,                      093  */(0x10),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR,                   094  */(0x12),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR,                   095  */(0x12),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_LANE_MODE_1_ADDR,                        096  */(0xC6),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_LANE_MODE_1_ADDR,                        097  */(0xC6),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       098  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       099  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR,            100  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR,            101  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR,            102  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR,            103  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_PCS_TXMGN_V0_ADDR,                                   104  */(0x9F),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       105  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_TXDEEMPH_M6DB_V0_ADDR,                           106  */(0x17),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_TXDEEMPH_M3P5DB_V0_ADDR,                         107  */(0x0F),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNTRL2_ADDR,                                 108  */(0x83),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNTRL1_ADDR,                                 109  */(0x02),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNT_VAL_L_ADDR,                              110  */(0x09),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_FLL_CNT_VAL_H_TOL_ADDR,                          111  */(0xA2),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_PCS_FLL_MAN_CODE_ADDR,                               112  */(0x85),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_LOCK_DETECT_CONFIG1_ADDR,                        113  */(0xD1),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_LOCK_DETECT_CONFIG2_ADDR,                        114  */(0x1F),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_LOCK_DETECT_CONFIG3_ADDR,                        115  */(0x47),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RXEQTRAINING_WAIT_TIME_ADDR,                     116  */(0x75),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RXEQTRAINING_RUN_TIME_ADDR,                      117  */(0x13),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       118  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       119  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_PCS_LFPS_TX_ECSTART_EQTLOCK_ADDR,                    120  */(0x86),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_PWRUP_RESET_DLY_TIME_AUXCLK_ADDR,                121  */(0x04),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_TSYNC_RSYNC_TIME_ADDR,                           122  */(0x44),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       123  */(0x00),
  //--------------------------------------------------------------------------------------
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_P1U2_L_ADDR,                       124  */(0xE7),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_P1U2_H_ADDR,                       125  */(0x03),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_U3_L_ADDR,                         126  */(0x40),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RCVR_DTCT_DLY_U3_H_ADDR,                         127  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_EMPTY,                                                       128  */(0x00),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_RX_SIGDET_LVL_ADDR,                              129  */(0x88),
  /* HWIO_PERIPH_SS_USB3PHY_PCS_MISC_TYPEC_CTRL_ADDR,                            130  */(0x00),
  /* QUSB_HWIO_ADDR_EMPTY,                                                       131  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_END,                                                         132  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         133  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         134  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         135  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_END,                                                         136  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         137  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         138  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         139  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_END,                                                         140  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         141  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         142  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         143  */(0x00),
  //--------------------------------------------------------------------------------------
  /* QUSB_HWIO_ADDR_END,                                                         144  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         145  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         146  */(0x00),
  /* QUSB_HWIO_ADDR_END,                                                         147  */(0x00),
};



