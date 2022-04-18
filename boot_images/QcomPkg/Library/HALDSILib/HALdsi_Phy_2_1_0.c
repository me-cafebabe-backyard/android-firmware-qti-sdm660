/*=============================================================================

  File: HALdsi_Phy_2_1_0.c
  
  

  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*============================================================================
*                         INCLUDE FILES
============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "HALdsi.h"
#include "HALdsi_Phy.h"
#include "HALdsi_Pll.h"
#include "dsiHostSystem.h"
#include "HALdsi_Phy_2_1_0.h"
#include "hal_mdp.h"


/* -----------------------------------------------------------------------
** Local defines
** ----------------------------------------------------------------------- */
#define HAL_DSI_PHY_PLL_READY_TIMEOUT           150           /* ~15 ms */
    
#define HAL_DSI_PHY_PLL_PRE_EMPHASIS_BOTTOM_DEFAULT                    0x0
#define HAL_DSI_PHY_PLL_PRE_EMPHASIS_TOP_DEFAULT                       0x0
    
/* Generic parameters that applies to all parameter calculations */
#define HAL_DSI_PHY_GENERIC_SHIFT_OFFSET        0x02
#define HAL_DSI_PHY_GENERIC_TIMING_MAX          0xFF
#define HAL_DSI_PHY_TIPX_NUMERATOR              1000000000.0f                    /* numerator for the TIPX formula */
#define HAL_DSI_PHY_PERCENT_DENOMENATOR         100.0f
#define HAL_DSI_PHY_TREOT                       20                               /* t_reot */
    
/* Range factor applied */
#define HAL_DSI_PHY_RANGEFACTOR_1               1.0f
#define HAL_DSI_PHY_RANGEFACTOR_5               5.0f
#define HAL_DSI_PHY_RANGEFACTOR_10              10.0f
#define HAL_DSI_PHY_RANGEFACTOR_15              15.0f
#define HAL_DSI_PHY_RANGEFACTOR_40              40.0f
#define HAL_DSI_PHY_RANGEFACTOR_50              50.0f
#define HAL_DSI_PHY_RANGEFACTOR_90              90.0f
#define HAL_DSI_PHY_BITCLK_RANGE_FREQ_1         180000000                        /* bit clk frequency in the unit of Hz */
#define HAL_DSI_PHY_BITCLK_RANGE_FREQ_2         1200000000                       /* bit clk frequency in the unit of Hz */
    
#define HAL_DSI_PHY_TREOT                       20
    
/* Recommended values for TCLK_PREPARE formula */
#define HAL_DSI_PHY_TCLK_PREPARE_PHY_MIN        38.0f
#define HAL_DSI_PHY_TCLK_PREPARE_PHY_MAX        95.0f
#define HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM1     0x04
#define HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM2     0x08
#define HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM3     0x04
#define HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM4     0x02
    
/* Recommended Values for TCLK_ZERO formula */
#define HAL_DSI_PHY_TCLK_ZERO_PARAM1            300.0f
#define HAL_DSI_PHY_TCLK_ZERO_PARAM2            0x0B
#define HAL_DSI_PHY_TCLK_ZERO_PARAM3            8.0f
#define HAL_DSI_PHY_TCLK_ZERO_PARAM4            0x03
#define HAL_DSI_PHY_TCLK_ZERO_PARAM5            255
#define HAL_DSI_PHY_TCLK_ZERO_PARAM6            511
    
/* Recommended Values for TCLK_TRAIL formula */
#define HAL_DSI_PHY_TCLK_TRAIL_MIN              60.0f
    
/* Recommended Values for T_HS_PREPARE formula */
#define HAL_DSI_PHY_T_HS_PREPARE_PARAM1         0x28
#define HAL_DSI_PHY_T_HS_PREPARE_PARAM2         0x04
#define HAL_DSI_PHY_T_HS_PREPARE_PARAM3         0x55
#define HAL_DSI_PHY_T_HS_PREPARE_PARAM4         0x06
#define HAL_DSI_PHY_T_HS_PREPARE_PARAM5         0x04
#define HAL_DSI_PHY_T_HS_PREPARE_PARAM6         0x08
    
/* Recommended Values for T_HS_ZERO formula */
#define HAL_DSI_PHY_T_HS_ZERO_PARAM1            0x91
#define HAL_DSI_PHY_T_HS_ZERO_PARAM2            0x0A
#define HAL_DSI_PHY_T_HS_ZERO_PARAM3            0x0B
#define HAL_DSI_PHY_T_HS_ZERO_PARAM4            0x08
#define HAL_DSI_PHY_T_HS_ZERO_PARAM5            0x03
#define HAL_DSI_PHY_T_HS_ZERO_PARAM6            0xFF
    
/* Recommended Values for T_XX_TRAIL formula */
#define HAL_DSI_PHY_T_T_TRAIL_PARAM1            0x3C
#define HAL_DSI_PHY_T_T_TRAIL_PARAM2            0x04
#define HAL_DSI_PHY_T_T_TRAIL_PARAM3            0x03
#define HAL_DSI_PHY_T_T_TRAIL_PARAM4            0x08
    
/* Recommended Values for TEOT formula */
#define HAL_DSI_PHY_TEOT_PARAM1                 0x69
#define HAL_DSI_PHY_TEOT_PARAM2                 0x0C
    
/* Recommended Values for T_HS_EXIT formula */
#define HAL_DSI_PHY_T_HS_EXIT_MIN               100.0f
#define HAL_DSI_PHY_T_HS_EXIT_MAX               255
#define HAL_DSI_PHY_T_HS_EXIT_PARAM1            0x08
#define HAL_DSI_PHY_T_HS_EXIT_PARAM2            0x01
    
/* Recommended Values for T_HS_RQST formula */
#define HAL_DSI_PHY_T_HS_RQST_PARAM1            0x08
#define HAL_DSI_PHY_T_HS_RQST_PARAM2            0x01
    
/* Recommended Values for T_TA_GO formula */
#define HAL_DSI_PHY_T_TA_GO_PARAM1              0x03
    
/* Recommended Values for T_TA_SURE formula */
#define HAL_DSI_PHY_T_TA_SURE_PARAM1            0x00
    
/* Recommended Values for T_TA_GET formula */
#define HAL_DSI_PHY_T_TA_GET_PARAM1             0x04
    
/* Recommended Values for T_CLK_PRE formula */
#define HAL_DSI_PHY_T_CLK_PRE_PARAM1            0x08
#define HAL_DSI_PHY_T_CLK_PRE_PARAM2            0x08
#define HAL_DSI_PHY_T_CLK_PRE_PARAM3            0x02
#define HAL_DSI_PHY_T_CLK_PRE_MAX               0x3F
    
/* Recommended Values for T_CLK_POST formula */
#define HAL_DSI_PHY_T_CLK_POST_PARAM1           0x3C
#define HAL_DSI_PHY_T_CLK_POST_PARAM2           0x34
#define HAL_DSI_PHY_T_CLK_POST_PARAM3           0x2B
#define HAL_DSI_PHY_T_CLK_POST_PARAM4           0x08
#define HAL_DSI_PHY_T_CLK_POST_PARAM5           0x01
#define HAL_DSI_PHY_T_CLK_POST_MAX              0x3F
    
/* Recommended Values for PLL */
#define HAL_DSI_PLL_SSC_FREQ                    31.5f               /* 31.5 Khz */
#define HAL_DSI_PLL_SSC_ADJ_PER                 37                  /* Reference cycles per SSC step */
#define HAL_DSI_PLL_SSC_SPREAD                  0.005f              /* 0.005 == 5kppm */
#define HAL_DSI_PLL_PLLLOCK_CNT                 1
#define HAL_DSI_PLL_PLLLOCK_RNG                 0
#define HAL_DSI_PLL_PLL_WAKEUP_TIMER            5
#define HAL_DSI_PLL_PLLLOCK_CYCLE_1024          1024
#define HAL_DSI_PLL_PLLLOCK_CYCLE_256           256
#define HAL_DSI_PLL_PLLLOCK_CYCLE_128           128
#define HAL_DSI_PLL_PLLLOCK_CYCLE_32            32
#define HAL_DSI_PLL_VCO_MEASURE_TIME            5.0f                /* us per  VCO code bit (max-53us, min-0.05us) */
#define HAL_DSI_PLL_KVCO_MEASURE_TIME           5.0f                /* us per KVCO code bit (max-53us, min-0.05us) */
#define HAL_DSI_PLL_BITCLK_THRESHOLD            86.67f              /* Mbps */
#define HAL_DSI_PLL_MISC_CONSTANT               16
#define HAL_DSI_PLL_LPF_RES1                    3
#define HAL_DSI_PLL_LPF_CAP1                    11
#define HAL_DSI_PLL_LPF_CAP2                    1
#define HAL_DSI_PLL_BANDGAP_TIMER               4
#define HAL_DSI_PLL_LPF2_POSTDIV_CONSTANT       16
#define HAL_DSI_PLL_KVCO_CODE_DEFAULT           40
#define HAL_DSI_PLL_IETRIM                      4
#define HAL_DSI_PLL_IPTRIM                      4
#define HAL_DSI_PLL_CPCSET_CUR                  1
#define HAL_DSI_PLL_CPMSET_CUR                  1
#define HAL_DSI_PLL_ICPMSET                     4
#define HAL_DSI_PLL_ICPCSET                     4
#define HAL_DSI_PLL_ICPMSET_P                   0
#define HAL_DSI_PLL_ICPCSET_P                   0
#define HAL_DSI_PLL_ICPMSET_M                   0
#define HAL_DSI_PLL_ICPCSET_M                   0
#define HAL_DSI_PLL_IPTAT_TRIM                  7
#define HAL_DSI_PLL_C3CTRL                      2
#define HAL_DSI_PLL_R3CTRL                      1
    
#define HAL_DSI_PLL_PARAM_16                    16
#define HAL_DSI_PLL_PARAM_10                    10
#define HAL_DSI_PLL_PARAM_8                     8
#define HAL_DSI_PLL_PARAM_2                     2
#define HAL_DSI_PLL_PARAM_0_2F                  0.2f
#define HAL_DSI_PLL_PARAM_1                     1
#define HAL_DSI_PLL_PARAM_1300F                 1300.0f
#define HAL_DSI_PLL_PARAM_15                    15
#define HAL_DSI_PLL_PARAM_1M                    0x100000
#define HAL_DSI_PLL_PARAM_500F                  500.0f

/*!
 * \struct _HAL_DSI_PHY_PllConfigType
 *
 * PLL configuration parameters
 */
typedef struct _HAL_DSI_PHY_PllConfigType
{
  bool32           bClkBufRightEnable;        /* Right side clock buffer enable */
  bool32           bClkBufLeftEnable;         /* Left side clock buffer enable */
  uint32           uDsiclk_sel;               /* Indicate use VCO clk or VCO/2 clk as source for n2div divider */
  uint32           uN2Div;                    /* n2div divider */
  uint32           uN1Div;                    /* n1div divider */
  uint32           bSSCEnable;                /* Indicate whether or not SSC is enabled */
  uint32           uLDOOutput;                /* LDO output control: 0-low LDO output, 1-high LDO output */
  bool32           bPllTxClkEnable;           /* PLL_TXCLK_EN */
  bool32           bDoubleRefFreqEnable;      /* Indicate whether or not doubled reference clock frequency is used */
  uint32           uDecStart;                 /* DEC_START */
  uint32           uDivFracStart;             /* DIV_FRAC_START */
  uint32           uSscPer;                   /* SSC_PER */
  uint32           uSscStepSize;              /* SSC_STEP_SIZE */
  bool32           bCenterSpread;             /* Center spread */
  uint32           uSscAdjPer;                /* SSC_ADJ_PER */
  uint32           uPlllockRng;               /* PLLLOCK_RNG */
  uint32           uPlllockCnt;               /* PLLLOCK_CNT */
  uint32           uPlllockCmp;               /* PLLLOCK_CMP */
  uint32           uVcoDivRef;                /* VCO_DIV_REF */
  uint32           uKvcoDivRef;               /* KVCO_DIV_REF */
  uint32           uVcoCount;                 /* VCO_COUNT */
  uint32           uKvcoCount;                /* KVCO_COUNT */
  uint32           uPllLdoCtrl;               /* PLL_LDO_CTRL */
  uint32           uPllLpfRes1;               /* PLL_LPF_RES1 */
  uint32           uTxBand;                   /* TX_BAND: post divider 1/2/4/8 */
  uint32           uBandGapTimer;             /* BANDGAP_TIMER */
  uint32           uPllWakeupTimer;           /* PLL_WAKEUP_TIMER  */
  uint32           uKvcoCode;                 /* KVCO_CODE */
  uint32           uIeTrim;                   /* IE_TRIM */
  uint32           uIpTrim;                   /* IP_TRIM */
  uint32           uCpmSetCur;                /* CPMSET_CUR */
  uint32           uCpcSetCur;                /* CPCSET_CUR */
  uint32           uIcpmSet;                  /* ICPMSET */
  uint32           uIcpcSet;                  /* ICPCSET */
  uint32           uIcpmSet_P;                /* ICPMSET_P */
  uint32           uIcpcSet_P;                /* ICPCSET_P */
  uint32           uIcpmSet_M;                /* ICPMSET_M */
  uint32           uIcpcSet_M;                /* ICPCSET_M */
  uint32           uLpfCap1;                  /* LPF_CAP1 */
  uint32           uLpfCap2;                  /* LPF_CAP2 */
  uint32           uIptatTrim;                /* IPTAT_TRIM */
  uint32           uRCtrl;                    /* PLL_RCTRL */
  uint32           uCCtrl;                    /* PLL_CCTRL */
} HAL_DSI_PHY_PllConfigType;

/*!
 * \struct _HAL_DSI_PHY_LaneConfigType_
 *
 * PHY configuration parameters
 */
typedef struct _HAL_DSI_PHY_LaneConfigType_
{
  uint32           uDataStrengthLP_P;         /* Data strength LP_P */
  uint32           uDataStrengthLP_N;         /* Data strength LP_N */
  uint32           uDataStrengthHS;           /* Data strength HS */
  uint32           uClockStrengthHS;          /* Clock Strength HS */
  uint32           uPemphBottom;              /* Determines how many pre-emphasis branches for bottom termination */
  uint32           uPemphTop;                 /* Determines how many pre-emphasis branches for top termination */
  bool32           bPemphEnable;              /* Enable driver pre-emphasis */
  bool32           bStrengthOverride;         /* Strength override to use DSIPHY_LNn_TEST_STR */
} HAL_DSI_PHY_LaneConfigType;


/*!
 * \struct _HAL_DSI_PHY_TimingConfigType_
 *
 * PHY timing parameters
 */
typedef struct _HAL_DSI_PHY_TimingConfigType_
{
  bool32           bHSTX_HalfByteClk_En;      /* DSI timing parameter: HSTX_HALFBYTECLK_EN */
  uint32           uT_CLK_PREPARE_DLY;        /* DSI timing parameter: HSTX_PREPARE_DLY */
  uint32           uT_CLK_ZERO;               /* DSI timing parameter: t_CLK_ZERO */
  uint32           uT_CLK_PREPARE;            /* DSI timing parameter: t_CLK_PREPARE */
  uint32           uT_CLK_TRAIL;              /* DSI timing parameter: t_CLK_TRAIL */
  uint32           uT_HS_EXIT;                /* DSI timing parameter: t_HS_EXIT */
  uint32           uT_HS_ZERO;                /* DSI timing parameter: t_HS_ZERO */
  uint32           uT_HS_PREPARE;             /* DSI timing parameter: t_HS_PREPARE */
  uint32           uT_HS_TRAIL;               /* DSI timing parameter: t_HS_TRAIL */
  uint32           uT_HS_RQST;                /* DSI timing parameter: t_HS_RQST */
  uint32           uT_TA_SURE;                /* DSI timing parameter: t_TA_SURE */
  uint32           uT_TA_GO;                  /* DSI timing parameter: t_TA_GO */
  uint32           uT_TA_GET;                 /* DSI timing parameter: t_TA_GET */
  uint32           uT_CLK_PRE;                /* DSI timing parameter: t_CLK_PRE */
  uint32           uT_CLK_POST;               /* DSI timing parameter: t_CLK_POST */
  bool32           bT_CLK_PRE_INC_BY_2;       /* DSI timing parameter: t_CLK_PRE_INC_BY_2 */
} HAL_DSI_PHY_TimingConfigType;

/*!
 * \struct _HAL_DSI_PHY_PhySettingsType
 *
 * PHY configuration parameters
 */
typedef struct _HAL_DSI_PHY_PhySettingsType
{
  uint32                       uDivCtrl;
  uint32                       uPhyPostDiv;
  bool32                       bSlave;
  HAL_DSI_PHY_TimingConfigType sTimingConfig;
  HAL_DSI_PHY_LaneConfigType   sLaneConfig;
} HAL_DSI_PHY_PhySettingsType;


/*!
 * \struct _HAL_DSI_PHY_PLL_KVCO_RANGE_TYPE_
 *
 * DSI KVCO range settings
 */
typedef struct _HAL_DSI_PHY_PLL_KVCO_RANGE_TYPE_
{
  uint32           uLow;                      /* KVCO lower bound  */
  uint32           uHigh;                     /* KVCO higher bound */
  uint32           uKvcoSlope;                /* KVCO slope        */
  uint32           uKvcoCode;                 /* KVCO code         */
} HAL_DSI_PHY_PLL_KVCORangeType;


static void HAL_DSI_Phy_ResetPhy(DSI_Device_IDType eDeviceId);
static HAL_MDSS_ErrorType HAL_DSI_Phy_SetupLanePhy(DSI_Device_IDType eDeviceId, DSI_LaneIDType eLaneId, HAL_DSI_PHY_LaneConfigType *pConfig);


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_GetLaneOffset()
*/
/*!
* \brief
*     Gets register offset for the specific Phy Lane.
*
*
* \param [in]  eLainId - Lane id;
*
* \retval  Register offset value for the specified lane;
*
****************************************************************************/
static uintPtr HAL_DSI_Phy_GetLaneOffset(DSI_LaneIDType eLaneId)
{
  uintPtr uLaneBlockOffset[DSI_LaneID_Max];
  uintPtr uOffset                           = 0;

  uLaneBlockOffset[DSI_LaneID_0]   = 0;
  uLaneBlockOffset[DSI_LaneID_1]   = HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN1_CFG0_ADDR - HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG0_ADDR;
  uLaneBlockOffset[DSI_LaneID_2]   = HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN2_CFG0_ADDR - HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG0_ADDR;
  uLaneBlockOffset[DSI_LaneID_3]   = HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN3_CFG0_ADDR - HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG0_ADDR;
  uLaneBlockOffset[DSI_LaneID_CLK] = HWIO_MMSS_DSI_0_PHY_DSIPHY_CKLN_CFG0_ADDR - HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG0_ADDR;

  if (eLaneId < DSI_LaneID_Max)
  {
    uOffset = uLaneBlockOffset[eLaneId];
  }
  return uOffset;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_CheckNegative()
*/
/*!
* \brief
*     If the integer is negative, set it to zero
*
*
* \param [in]  iVal - integer value to be processed;
*
* \retval  0 or positive value as integer;
*
****************************************************************************/
static int32 HAL_DSI_Phy_CheckNegative(int32 iVal)
{
  if (iVal < 0)
  {
    iVal = 0;
  }
  return iVal;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_Round()
*/
/*!
* \brief
*     Rounds to the nearest integer.
*
*
* \param [in]  fFloatVal - float number to be processed;
*
* \retval  rounded integer;
*
****************************************************************************/
static int32 HAL_DSI_Phy_Round(float fFloatVal)
{
  int32  iRoundupVal = (int32)fFloatVal;
  if (fFloatVal - iRoundupVal > 0.5) iRoundupVal++;

  return iRoundupVal;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_Roundup()
*/
/*!
* \brief
*     Rounds up to the nearest integer.
*
*
* \param [in]  fFloatVal - float number to be processed;
*
* \retval  rounded up integer;
*
****************************************************************************/
static int32 HAL_DSI_Phy_Roundup(float fFloatVal)
{
  int32  iRoundupVal = (int32)fFloatVal;

  if (fFloatVal - iRoundupVal > 0) iRoundupVal++;
  else if (fFloatVal - iRoundupVal < 0) iRoundupVal--;

  return iRoundupVal;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_Rounddown()
*/
/*!
* \brief
*     Rounds down to the nearest integer for positive number, 0 if it is negative number.
*
*
* \param [in]  fFloatVal - float number to be processed;
*
* \retval  rounded down integer;
*
****************************************************************************/
static uint32 HAL_DSI_Phy_Rounddown(double pFloatValue)
{
  uint32     roundupValue;

  if (pFloatValue > 0)
  {
    roundupValue = (uint32)pFloatValue;
  }
  else
  {
    roundupValue = 0;
  }

  return roundupValue;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_PllEnable()
*/
/*!
* \brief
*     Enable/Disable Phy PLL
*
* \param [in]  eDeviceId         - DSI core ID
* \param [in]  bEnable           - Enable/disable PLL
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_PllEnable(DSI_Device_IDType eDeviceId, bool32 bEnable)
{
  HAL_MDSS_ErrorType   eStatus = HAL_MDSS_STATUS_SUCCESS;
  uintPtr              uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId);
  uint32               uRegVal = 0;

  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_CMN_PLL_CNTRL, PLL_START, bEnable);
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_PLL_CNTRL_ADDR, uRegVal);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_PllSetSource()
*/
/*!
* \brief
*     Set byte clock source for PLL
*
* \param [in]  eDeviceId              - DSI core ID
* \param [in]  psDsiPhyConfig         - PHY Configruation 
*
* \retval void
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_PllSetSource(DSI_Device_IDType eDeviceId, HAL_DSI_PLLConfigSourceType  ePLLConfigSource)
{
    HAL_MDSS_ErrorType   eStatus     = HAL_MDSS_STATUS_SUCCESS;
    uintPtr              uOffset     = HAL_DSI_GetRegBaseOffset(eDeviceId);
    uint32               uGlobalTest = 0;
    uint32               uBufLR      = 0;

    uGlobalTest = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_GLBL_TEST_CTRL_ADDR);

    if(HAL_DSI_PLL_CONFIG_INDEPENDENT_SOURCE == ePLLConfigSource)
    {
        // Enable right buffer
        uBufLR = 0x01;
        // PLL source from left
        uGlobalTest &= ~HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_GLBL_TEST_CTRL_DSIPHY_BITCLK_HS_SEL_BMSK;   
    }
    else if(HAL_DSI_PLL_CONFIG_SPLIT_SOURCE == ePLLConfigSource)
    {
        if(DSI_DeviceID_0 == eDeviceId)
        {
            // Enable left and right buffer
            uBufLR = 0x03;
            // PLL source from left
            uGlobalTest &= ~HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_GLBL_TEST_CTRL_DSIPHY_BITCLK_HS_SEL_BMSK;
        }
        else
        {
            // Disable left and right buffer
            uBufLR = 0x0;
            // PLL source from right
            uGlobalTest |= HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_GLBL_TEST_CTRL_DSIPHY_BITCLK_HS_SEL_BMSK;
        }
    }
    else 
    {
    }

    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_CLKBUFLR_EN_ADDR, uBufLR);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_GLBL_TEST_CTRL_ADDR, uGlobalTest);
    
    return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_Power()
*/
/*!
* \brief
*     Remove PLL, DIG and lanes from power down
*
* \param [in]  eDeviceId    - DSI core ID
* \param [in]  bPllPowerUp  - TRUE: power up, FALSE: power down;
*
* \retval None
*
****************************************************************************/
static void HAL_DSI_Phy_Power(DSI_Device_IDType eDeviceId,  bool32 bPllPowerUp)
{
  uintPtr            uOffset     = HAL_DSI_GetRegBaseOffset(eDeviceId);
  HAL_HW_VersionType sVersion;

  HAL_MDP_ReadVersionInfo(&sVersion, NULL);
  
  /* Remove PLL, DIG and all lanes from pwrdn */

  if ((0x03 == sVersion.uMajorVersion) &&
      (0x03 == sVersion.uMinorVersion))        // Starhawk
  {
    if (bPllPowerUp)
    {
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_0_ADDR, 0x000000DF);
    }
    else
    {
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_0_ADDR, 0x0000005F);
    }
  }
  else        // Starlord / Istari
  {
    if (bPllPowerUp)
    {
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_0_ADDR, 0x000000FF);
    }
    else
    {
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_0_ADDR, 0x0000007F);
    }     
  }
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_PllLockDetect()
*/
/*!
* \brief
*     Wait and check if PLL locked.
*
* \param [in]  eDeviceId - DSI core ID
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_PllLock(DSI_Device_IDType eDeviceId)
{
  HAL_MDSS_ErrorType   eStatus  = HAL_MDSS_STATUS_SUCCESS;
  uintPtr              uOffset  = HAL_DSI_GetRegBaseOffset(eDeviceId);  
  uint32               uRegVal  = 0;
  uint32               uTimeout = HAL_DSI_PHY_PLL_READY_TIMEOUT;
  uint32               uPllStatus;

  /* Reset voltage selection to default value */
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VREF_CFG1_ADDR, 0x10);

  /* Enable PLL */
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_CMN_PLL_CNTRL, PLL_START, 1);
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_PLL_CNTRL_ADDR, uRegVal);

  /* Wait for Lock */
  uPllStatus = (in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESET_SM_READY_STATUS_ADDR) &
                HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESET_SM_READY_STATUS_CORE_READY_BMSK);
  while ((0 == uPllStatus) && (uTimeout))
  {
    DSI_OSAL_SleepUs(100);  /*delay ~100us*/
    uPllStatus = (in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESET_SM_READY_STATUS_ADDR) &
                  HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESET_SM_READY_STATUS_CORE_READY_BMSK);
    uTimeout--;
  }
  
  if (0 == (uPllStatus & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESET_SM_READY_STATUS_CORE_READY_BMSK))
  {
    /* timeout while polling the lock status */
    eStatus = HAL_MDSS_DSI_FAILED_UNABLE_TO_INIT_HW;
  }
  
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_CalculateTimingParams()
*/
/*!
* \brief
*     Calculate timing parameters
*
* \param [in]  pTimingParameters - DSI core ID
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_CalculateTimingParams(HAL_DSI_TimingSettingType *pTimingParameters,
                                                            HAL_DSI_PHY_TimingConfigType *psTimingConfig)
{
  HAL_MDSS_ErrorType        eStatus            = HAL_MDSS_STATUS_SUCCESS;
  DSI_TimingOverrideType   *pPreDefinedTimings = pTimingParameters->pPreDefinedTimings;
  float                     fMin;
  float                     fMax;
  float                     fT_clk_prepare_actual;
  float                     fT_clk_zero_actual;
  float                     fT_hs_prepare_actual;
  float                     fTEOT_data;
  float                     fTEOT_clock;
  float                     fRangeFactor = HAL_DSI_PHY_RANGEFACTOR_10;
  float                     fEscclk      = (pTimingParameters->uEscapeFreq <= 1000000) ? (HAL_DSI_ESCCLK_SRC * 1000000) : (pTimingParameters->uEscapeFreq);  /* in Hz */
  float                     fTlpx        = HAL_DSI_PHY_TIPX_NUMERATOR / fEscclk;
  float                     fUiBitclk    = HAL_DSI_PHY_TIPX_NUMERATOR / (float)pTimingParameters->uBitclock;
  float                     fTemp1;
  int32                     iMin;
  int32                     iMax;
  int32                     iVal;
  uint32                    uT_clk_prepare;
  uint32                    uT_clk_prepare_dly;
  uint32                    uT_clk_zero;
  uint32                    uT_clk_trail;
  uint32                    uT_hs_prepare;
  uint32                    uT_hs_zero;
  uint32                    uT_hs_trail;
  uint32                    uT_hs_rqst;
  uint32                    uHalfByteClkEn;
  uint32                    uT_hs_exit;
  uint32                    uT_ta_go;
  uint32                    uT_ta_sure;
  uint32                    uT_ta_get;
  uint32                    uT_clk_post;
  uint32                    uT_clk_pre;
  bool32                    bT_clk_pre_inc_by_2 = FALSE;

  fTEOT_data  = HAL_DSI_PHY_TEOT_PARAM1 + HAL_DSI_PHY_TEOT_PARAM2 * fUiBitclk;
  fTEOT_clock = HAL_DSI_PHY_TEOT_PARAM1 + HAL_DSI_PHY_TEOT_PARAM2 * fUiBitclk;
  
  /**********************************************************************************/
  // HSTX_HALFBYTECLK_EN calculation
  uHalfByteClkEn = ((8 * fUiBitclk) > ((1.5f)*fTlpx)) ? 1 : 0;
  fTemp1 = (6 + 4 * uHalfByteClkEn)*fUiBitclk;
  
  /**********************************************************************************/
  // T_CLK_PREPARE calculation
  if (pPreDefinedTimings->bTimingCLKPrepareOverride)
  {
    uT_clk_prepare = pPreDefinedTimings->uTimingCLKPrepareValue;
  }
  else
  {
    fMin = 0;
    fMax = 0;
    if (HAL_DSI_PHY_TCLK_PREPARE_PHY_MAX > fTemp1)
    {
        /* calculate the min and max in float */
        fMin = (float)HAL_DSI_Phy_Roundup  ((HAL_DSI_PHY_TCLK_PREPARE_PHY_MIN / fUiBitclk - HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM1 * uHalfByteClkEn) / HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM2);
        fMax = (float)HAL_DSI_Phy_Rounddown((HAL_DSI_PHY_TCLK_PREPARE_PHY_MAX / fUiBitclk - HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM1 * uHalfByteClkEn) / HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM2);
    }
    /* interpolate the value at 10% between min and max */
    iVal = HAL_DSI_Phy_Roundup((fMax - fMin) * (fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + fMin);
    uT_clk_prepare = (iVal > 0) ? iVal : 0;
  }
  
  /**********************************************************************************/
  // HSTX_PREPARE_DLY calculation
  fMin = 0;
  fMax = 0;
  if (HAL_DSI_PHY_TCLK_PREPARE_PHY_MAX <= fTemp1)
  {
    fMin = (float)HAL_DSI_Phy_Roundup  ((HAL_DSI_PHY_TCLK_PREPARE_PHY_MIN / fUiBitclk - HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM3 * uHalfByteClkEn) / HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM4);
    fMax = (float)HAL_DSI_Phy_Rounddown((HAL_DSI_PHY_TCLK_PREPARE_PHY_MAX / fUiBitclk - HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM3 * uHalfByteClkEn) / HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM4);
  }
  iVal = HAL_DSI_Phy_Roundup((fMax - fMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + fMin);
  uT_clk_prepare_dly = (iVal > 0) ? iVal : 0;
  
  fT_clk_prepare_actual = ((uT_clk_prepare * HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM2) + 
                           (uT_clk_prepare_dly*HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM4) + 
                           (uHalfByteClkEn * HAL_DSI_PHY_TCLK_PREPARE_PHY_PARAM3))*fUiBitclk;
  
  /**********************************************************************************/
  // T_CLK_ZERO calculation
  if (pPreDefinedTimings->bTimingCLKZeroOverride)
  {
    uT_clk_zero = pPreDefinedTimings->uTimingCLKZeroValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_TCLK_ZERO_PARAM1 - fT_clk_prepare_actual;
    iMin = HAL_DSI_Phy_Roundup((fMin / fUiBitclk - HAL_DSI_PHY_TCLK_ZERO_PARAM2) / HAL_DSI_PHY_TCLK_ZERO_PARAM3) - HAL_DSI_PHY_TCLK_ZERO_PARAM4;
    iMax = (iMin > HAL_DSI_PHY_TCLK_ZERO_PARAM5) ? HAL_DSI_PHY_TCLK_ZERO_PARAM6 : HAL_DSI_PHY_TCLK_ZERO_PARAM5;
    iVal = HAL_DSI_Phy_Roundup((iMax - iMin) * (fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_clk_zero = (iVal > 0) ? iVal : 0;
  }
  fT_clk_zero_actual = ((uT_clk_zero + HAL_DSI_PHY_TCLK_ZERO_PARAM4) * HAL_DSI_PHY_TCLK_ZERO_PARAM3 + HAL_DSI_PHY_TCLK_ZERO_PARAM2 - uT_clk_prepare_dly * 2) * fUiBitclk;
  
  /**********************************************************************************/
  // T_CLK_TRAIL calculation
  if (pPreDefinedTimings->bTimingCLKTrailOverride)
  {
    uT_clk_trail = pPreDefinedTimings->uTimingCLKTrailValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_TCLK_TRAIL_MIN;
    fMax = fTEOT_clock - HAL_DSI_PHY_TREOT;
    iMin = HAL_DSI_Phy_Roundup  ((fMin / fUiBitclk + HAL_DSI_PHY_T_T_TRAIL_PARAM3) / HAL_DSI_PHY_T_T_TRAIL_PARAM4);
    iMax = HAL_DSI_Phy_Rounddown((fMax / fUiBitclk + HAL_DSI_PHY_T_T_TRAIL_PARAM3) / HAL_DSI_PHY_T_T_TRAIL_PARAM4);
    iVal = HAL_DSI_Phy_Roundup  ((iMax - iMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_clk_trail = (iVal > 0) ? iVal : 0;
  }
  
  /**********************************************************************************/
  // T_HS_PREPARE calculation
  if (pPreDefinedTimings->bTimingHSPrepareOverride)
  {
    uT_hs_prepare = pPreDefinedTimings->uTimingHSPrepareValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_T_HS_PREPARE_PARAM1 + HAL_DSI_PHY_T_HS_PREPARE_PARAM2 * fUiBitclk;
    fMax = HAL_DSI_PHY_T_HS_PREPARE_PARAM3 + HAL_DSI_PHY_T_HS_PREPARE_PARAM4 * fUiBitclk;
    iMin = HAL_DSI_Phy_Roundup  (((fMin / fUiBitclk) - HAL_DSI_PHY_T_HS_PREPARE_PARAM5 * uHalfByteClkEn) / HAL_DSI_PHY_T_HS_PREPARE_PARAM6);
    iMax = HAL_DSI_Phy_Rounddown(((fMax / fUiBitclk) - HAL_DSI_PHY_T_HS_PREPARE_PARAM5 * uHalfByteClkEn) / HAL_DSI_PHY_T_HS_PREPARE_PARAM6);
    iVal = HAL_DSI_Phy_Roundup  ((iMax - iMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_hs_prepare = (iVal > 0) ? iVal : 0;
  }
  fT_hs_prepare_actual = (uT_hs_prepare * HAL_DSI_PHY_T_HS_PREPARE_PARAM6 + uHalfByteClkEn * HAL_DSI_PHY_T_HS_PREPARE_PARAM5) * fUiBitclk;
  
  /**********************************************************************************/
  // T_HS_ZERO calculation
  if (pPreDefinedTimings->bTimingHSZeroOverride)
  {
    uT_hs_zero = pPreDefinedTimings->uTimingHSZeroValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_T_HS_ZERO_PARAM1 + HAL_DSI_PHY_T_HS_ZERO_PARAM2 * fUiBitclk - fT_hs_prepare_actual;
    iMin = HAL_DSI_Phy_Roundup((fMin / fUiBitclk - HAL_DSI_PHY_T_HS_ZERO_PARAM3) / HAL_DSI_PHY_T_HS_ZERO_PARAM4) - HAL_DSI_PHY_T_HS_ZERO_PARAM5;
    iMax = HAL_DSI_PHY_T_HS_ZERO_PARAM6;
    iVal = HAL_DSI_Phy_Roundup((iMax - iMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_hs_zero = (iVal > 0) ? iVal : 0;
  }
  
  /**********************************************************************************/
  // T_HS_TRAIL calculation
  if (pPreDefinedTimings->bTimingHSTrailOverride)
  {
    uT_hs_trail = pPreDefinedTimings->uTimingHSTrailValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_T_T_TRAIL_PARAM1 + HAL_DSI_PHY_T_T_TRAIL_PARAM2 * fUiBitclk;
    fMax = fTEOT_data - HAL_DSI_PHY_TREOT;
    iMin = HAL_DSI_Phy_Roundup  ((fMin / fUiBitclk + HAL_DSI_PHY_T_T_TRAIL_PARAM3) / HAL_DSI_PHY_T_T_TRAIL_PARAM4);
    iMax = HAL_DSI_Phy_Rounddown((fMax / fUiBitclk + HAL_DSI_PHY_T_T_TRAIL_PARAM3) / HAL_DSI_PHY_T_T_TRAIL_PARAM4);
    iVal = HAL_DSI_Phy_Roundup  ((iMax - iMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_hs_trail = (iVal > 0) ? iVal : 0;
  }
  
  /**********************************************************************************/
  // T_HS_RQST is user entry based on UI/ESCCLK
  uT_hs_rqst = 0;
  if (pPreDefinedTimings->bTimingHSRequestOverride)
  {
    uT_hs_rqst = pPreDefinedTimings->uTimingHSRequestValue;
  }
  else
  {
    if (uHalfByteClkEn == 0)
    {
        uT_hs_rqst = HAL_DSI_Phy_Round(fTlpx / fUiBitclk / HAL_DSI_PHY_T_HS_RQST_PARAM1) - HAL_DSI_PHY_T_HS_RQST_PARAM2;
    }
  }
  
  /**********************************************************************************/
  // T_HS_EXIT calculation
  if (pPreDefinedTimings->bTimingHSExitOverride)
  {
    uT_hs_exit = pPreDefinedTimings->uTimingHSExitValue;
  }
  else
  {
    iMin = HAL_DSI_Phy_Roundup(HAL_DSI_PHY_T_HS_EXIT_MIN / fUiBitclk / HAL_DSI_PHY_T_HS_EXIT_PARAM1) - HAL_DSI_PHY_T_HS_EXIT_PARAM2;
    iMax = HAL_DSI_PHY_T_HS_EXIT_MAX;
    iVal = HAL_DSI_Phy_Roundup((iMax - iMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_hs_exit = (iVal > 0) ? iVal : 0;
  }
  
  /**********************************************************************************/
  // T_TA_GO calculation (Hard coded value)
  uT_ta_go = HAL_DSI_PHY_T_TA_GO_PARAM1;
  if (pPreDefinedTimings->bTimingTAGoOverride)
  {
    uT_ta_go = pPreDefinedTimings->uTimingTAGoValue;
  }
  
  /**********************************************************************************/
  // T_TA_SURE calculation (Hard coded value)
  uT_ta_sure = HAL_DSI_PHY_T_TA_SURE_PARAM1;
  if (pPreDefinedTimings->bTimingTASureOverride)
  {
    uT_ta_sure = pPreDefinedTimings->uTimingTASureValue;
  }
  
  /**********************************************************************************/
  // T_TA_GET calculation (Hard coded value)
  uT_ta_get = HAL_DSI_PHY_T_TA_GET_PARAM1;
  if (pPreDefinedTimings->bTimingTAGetOverride)
  {
    uT_ta_get = pPreDefinedTimings->uTimingTAGetValue;
  }
  
  /**********************************************************************************/
  // T_CLK_POST calculation
  if (pPreDefinedTimings->bTimingCLKPostOverride)
  {
    uT_clk_post = pPreDefinedTimings->uTimingCLKPostValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_T_CLK_POST_PARAM1 + HAL_DSI_PHY_T_CLK_POST_PARAM2 * fUiBitclk;
    iMin = HAL_DSI_Phy_Roundup((fMin - HAL_DSI_PHY_T_CLK_POST_PARAM3*fUiBitclk) / (HAL_DSI_PHY_T_CLK_POST_PARAM4 * fUiBitclk)) - 1;
    iMax = HAL_DSI_PHY_T_CLK_POST_MAX;
    iVal = HAL_DSI_Phy_Roundup((iMax - iMin)*(fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
    uT_clk_post = (iVal > 0) ? iVal : 0;
  }
  
  /**********************************************************************************/
  // T_CLK_PRE calculation
  if (pPreDefinedTimings->bTimingCLKPreOverride)
  {
    uT_clk_pre = pPreDefinedTimings->uTimingCLKPreValue;
  }
  else
  {
    fMin = HAL_DSI_PHY_T_CLK_PRE_PARAM1 * fUiBitclk;
    iMin = HAL_DSI_Phy_Roundup((fMin + fT_clk_prepare_actual + fT_clk_zero_actual + fTlpx) / (HAL_DSI_PHY_T_CLK_PRE_PARAM2 * fUiBitclk)) - 1;
    iMax = HAL_DSI_PHY_T_CLK_PRE_MAX;
    if (iMin > iMax)
    {
      iVal = HAL_DSI_Phy_Roundup(((iMax * HAL_DSI_PHY_T_CLK_PRE_PARAM3) - iMin) * (fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
      iVal = HAL_DSI_Phy_Rounddown(iVal / HAL_DSI_PHY_T_CLK_PRE_PARAM3);
      bT_clk_pre_inc_by_2 = TRUE;
    }
    else
    {
      iVal = HAL_DSI_Phy_Roundup((iMax - iMin) * (fRangeFactor / HAL_DSI_PHY_PERCENT_DENOMENATOR) + iMin);
      bT_clk_pre_inc_by_2 = FALSE;
    }
    uT_clk_pre = (iVal < 0) ? 0 : iVal;
  }
  
  /**********************************************************************************/
  /*   up to here, all DSI timing parameters have been calculated                   */
  /*   now, assign the parameters and program the HW                                */
  /**********************************************************************************/
  
  /* assign lane timing parameters */
  psTimingConfig->bHSTX_HalfByteClk_En = (uHalfByteClkEn > 0) ? TRUE : FALSE;
  psTimingConfig->uT_CLK_PREPARE_DLY   = uT_clk_prepare_dly;
  psTimingConfig->uT_HS_PREPARE        = uT_hs_prepare;
  psTimingConfig->uT_HS_EXIT           = uT_hs_exit;
  psTimingConfig->uT_HS_RQST           = uT_hs_rqst;
  psTimingConfig->uT_HS_TRAIL          = uT_hs_trail;
  psTimingConfig->uT_HS_ZERO           = uT_hs_zero;
  psTimingConfig->uT_TA_GET            = uT_ta_get;
  psTimingConfig->uT_TA_GO             = uT_ta_go;
  psTimingConfig->uT_TA_SURE           = uT_ta_sure;
  psTimingConfig->uT_CLK_PREPARE       = uT_clk_prepare;
  psTimingConfig->uT_CLK_ZERO          = uT_clk_zero;
  psTimingConfig->uT_CLK_TRAIL         = uT_clk_trail;
  psTimingConfig->uT_CLK_PRE           = uT_clk_pre;
  psTimingConfig->uT_CLK_POST          = uT_clk_post;
  psTimingConfig->bT_CLK_PRE_INC_BY_2  = bT_clk_pre_inc_by_2;

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_SetupLaneTimingParams()
*/
/*!
* \brief
*     Config lane timing parameters
*
* \param [in]  eDeviceId     - DSI core ID
* \param [in]  eLaneId       - DSI lane ID
* \param [in]  pTimingConfig - pointer to lane timing parameter structure
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_SetupLaneTimingParams(DSI_Device_IDType eDeviceId, DSI_LaneIDType eLaneId, HAL_DSI_PHY_TimingConfigType *pTimingConfig)
{
    HAL_MDSS_ErrorType   eStatus = HAL_MDSS_STATUS_SUCCESS;
    uint32               uRegVal = 0;
    uintPtr              uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId) + HAL_DSI_Phy_GetLaneOffset(eLaneId);

    /* HSTX_PREPARE_DLY */
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG0_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG0, DSIPHY_HSTX_PREPARE_DLY, pTimingConfig->uT_CLK_PREPARE_DLY);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG0_ADDR, uRegVal);

    /* HSTX_HALFBYTECLK_EN*/
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG1_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG1, DSIPHY_HSTX_HALFBYTECLK_EN, pTimingConfig->bHSTX_HalfByteClk_En);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG1_ADDR, uRegVal);

    /* T_HS_EXIT */
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_4_ADDR, pTimingConfig->uT_HS_EXIT);

    if (DSI_LaneID_CLK == eLaneId)
    {
      /* T_CLK_ZERO */
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_5_ADDR, pTimingConfig->uT_CLK_ZERO);
      /* T_CLK_PREPARE */
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_6_ADDR, pTimingConfig->uT_CLK_PREPARE);
      /* T_CLK_TRAIL */
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_7_ADDR, pTimingConfig->uT_CLK_TRAIL);
    }
    else
    {
      /* T_HS_ZERO */
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_5_ADDR, pTimingConfig->uT_HS_ZERO);
      /* T_HS_PREPARE */
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_6_ADDR, pTimingConfig->uT_HS_PREPARE);
      /* T_HS_TRAIL */
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_7_ADDR, pTimingConfig->uT_HS_TRAIL);
    }
    
    /* T_HS_RQST */
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_8_ADDR, pTimingConfig->uT_HS_RQST);

    /* T_TA_GO & T_TA_SURE */
    uRegVal = HWIO_OUT_FLD(0, DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_9, DSIPHY_T_TA_SURE, pTimingConfig->uT_TA_SURE);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_9, DSIPHY_T_TA_GO, pTimingConfig->uT_TA_GO);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_9_ADDR, uRegVal);

    /* T_TA_GET */
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_10_ADDR, pTimingConfig->uT_TA_GET);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TIMING_CTRL_11_ADDR, 0x000000A0);

    return eStatus;
}



/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_CommitTimingParams()
*/
/*!
* \brief
*     Config lane timing parameters
*
* \param [in]  eDeviceId     - DSI core ID
* \param [in]  pTimingConfig - pointer to lane timing parameter structure
*
* \retval None
*
****************************************************************************/
static void HAL_DSI_Phy_CommitTimingParams(DSI_Device_IDType eDeviceId, HAL_DSI_PHY_TimingConfigType *pTimingConfig)
{
  uint32               uRegVal = 0;
  uintPtr              uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId);

  HAL_DSI_Phy_SetupLaneTimingParams(eDeviceId, DSI_LaneID_0,   pTimingConfig);
  HAL_DSI_Phy_SetupLaneTimingParams(eDeviceId, DSI_LaneID_1,   pTimingConfig);
  HAL_DSI_Phy_SetupLaneTimingParams(eDeviceId, DSI_LaneID_2,   pTimingConfig);
  HAL_DSI_Phy_SetupLaneTimingParams(eDeviceId, DSI_LaneID_3,   pTimingConfig);
  HAL_DSI_Phy_SetupLaneTimingParams(eDeviceId, DSI_LaneID_CLK, pTimingConfig);

  /* DSI clock out timing control */
  uRegVal = 0;
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_CLKOUT_TIMING_CTRL, T_CLK_POST, pTimingConfig->uT_CLK_POST);
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_CLKOUT_TIMING_CTRL, T_CLK_PRE,  pTimingConfig->uT_CLK_PRE);
  out_dword(uOffset + HWIO_MMSS_DSI_0_CLKOUT_TIMING_CTRL_ADDR, uRegVal);
  
  /* T_CLK_PRE counter increment control */
  uRegVal = (pTimingConfig->bT_CLK_PRE_INC_BY_2) ? 1 : 0;
  out_dword(uOffset + HWIO_MMSS_DSI_0_TEST_PATTERN_GEN_VIDEO_ENABLE_ADDR, uRegVal);
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_CommitPhy()
*/
/*!
* \brief
*     Configures the PHY hardware registers.
*
*
* \param [in]  eDeviceId     - DSI core ID
* \param [in]  pSettings     - pointer to phy settings structure
*
* \retval None
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_CommitPhy(DSI_Device_IDType             eDeviceId,
                                                HAL_DSI_PHY_PhySettingsType  *pSettings)
{
  HAL_MDSS_ErrorType eStatus       = HAL_MDSS_STATUS_SUCCESS;

  // Remove DIG and all lanes from pwrdn (keep PLL powered down)
  HAL_DSI_Phy_Power(eDeviceId, FALSE);

  /* Lane Settings */
  HAL_DSI_Phy_SetupLanePhy(eDeviceId, DSI_LaneID_0,   &pSettings->sLaneConfig);    // Setup PHY for data lane 0
  HAL_DSI_Phy_SetupLanePhy(eDeviceId, DSI_LaneID_1,   &pSettings->sLaneConfig);    // Setup PHY for data lane 1
  HAL_DSI_Phy_SetupLanePhy(eDeviceId, DSI_LaneID_2,   &pSettings->sLaneConfig);    // Setup PHY for data lane 2
  HAL_DSI_Phy_SetupLanePhy(eDeviceId, DSI_LaneID_3,   &pSettings->sLaneConfig);    // Setup PHY for data lane 3
  HAL_DSI_Phy_SetupLanePhy(eDeviceId, DSI_LaneID_CLK, &pSettings->sLaneConfig);    // Setup PHY for data lane 3

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_CommitPll()
*/
/*!
* \brief
*     Setup DSI PLL
*
* \param [in]  eDeviceId         - DSI core ID
* \param [in]  ePLLConfigSource  - PLL source
* \param [in]  pPllConfig        - pointer to PLL config data structure
*
* \retval None
*
****************************************************************************/
static void HAL_DSI_Phy_CommitPll(DSI_Device_IDType            eDeviceId,
                                  HAL_DSI_PLLConfigSourceType  ePLLConfigSource,
                                  HAL_DSI_PHY_PllConfigType   *pPllConfig)
{
  uintPtr              uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId);
  uint32               uRegVal = 0;
  
  // DIV_CTRL_7_4
  // DIV_CTRL_3_0
  uRegVal = 0;
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_CMN_CLK_CFG0, DIV_CTRL_7_4, pPllConfig->uN2Div);
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_CMN_CLK_CFG0, DIV_CTRL_3_0, pPllConfig->uN1Div);
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CLK_CFG0_ADDR, uRegVal);
  
  // DSICLK_SEL
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CLK_CFG1_ADDR, pPllConfig->uDsiclk_sel);
  
  // Remove PLL, DIG and all lanes from pwrdn
  HAL_DSI_Phy_Power(eDeviceId, TRUE);

  // Setup PLL source
  HAL_DSI_Phy_PllSetSource(eDeviceId, ePLLConfigSource);

  // Skip PLL programming if this is for DSI_Device_1 and PLL is shared
  if ((DSI_DeviceID_0                  == eDeviceId) ||
      (HAL_DSI_PLL_CONFIG_SPLIT_SOURCE != ePLLConfigSource))
  {
    //*************************************************************************************
    //*      Configure the non-frequency dependent PLL registers
    //*************************************************************************************
    // PLL CSR sw reset
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SYSCLK_EN_RESET_ADDR, 0);

    // PLLLOCK_RNG
    // PLLLOCK_CNT
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP_EN_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP_EN, PLLLOCK_RNG, pPllConfig->uPlllockRng);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP_EN, PLLLOCK_CNT, pPllConfig->uPlllockCnt);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP_EN_ADDR, uRegVal);
  
    // REFCLK_DBLER_EN
    // PLL_TXCLK_EN
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_TXCLK_EN_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_TXCLK_EN, REFCLK_DBLER_EN, pPllConfig->bDoubleRefFreqEnable);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_TXCLK_EN, PLL_TXCLK_EN, pPllConfig->bPllTxClkEnable);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_TXCLK_EN_ADDR, uRegVal);
  
    // RESETSM_CTRL
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL_ADDR, 0x00000030);
  
    // BANDGAP_TIMER
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL2_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL2, BANDGAP_TIMER, pPllConfig->uBandGapTimer);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL2_ADDR, uRegVal);
  
    // PLLWAKEUP_TIMER
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL5_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL5, PLLWAKEUP_TIMER, pPllConfig->uPllWakeupTimer);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_RESETSM_CNTRL5_ADDR, uRegVal);
  
    // VCO_DIV_REF_7_0
    uRegVal = pPllConfig->uVcoDivRef & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_DIV_REF1_VCO_DIV_REF_7_0_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_DIV_REF1_ADDR, uRegVal);
  
    // VCO_DIV_REF_9_8
    uRegVal = (pPllConfig->uVcoDivRef >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_DIV_REF2_VCO_DIV_REF_9_8_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_DIV_REF2_ADDR, uRegVal);

    // PLL_LDO_CTRL
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_MISC1_ADDR, pPllConfig->uPllLdoCtrl);
   
    // IE_TRIM
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_IE_TRIM_ADDR, pPllConfig->uIeTrim);
  
    // IP_TRIM
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_IP_TRIM_ADDR, pPllConfig->uIpTrim);
  
    // CPMSET_CUR
    // CPCSET_CUR
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_CP_SET_CUR_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_CP_SET_CUR, PLL_CPMSET_CUR, pPllConfig->uCpmSetCur);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_CP_SET_CUR, CPCSET_CUR, pPllConfig->uCpcSetCur);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_CP_SET_CUR_ADDR, uRegVal);
  
    // ICPMSET_P
    // ICPMSET_M
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_ICPMSET_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_ICPMSET, PLL_ICPMSET_P, pPllConfig->uIcpmSet_P);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_ICPMSET, ICPMSET_M, pPllConfig->uIcpmSet_M);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_ICPMSET_ADDR, uRegVal);
  
    // ICPCSET_P
    // ICPCSET_M
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_ICPCSET_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_ICPCSET, PLL_ICPCSET_P, pPllConfig->uIcpcSet_P);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_ICPCSET, PLL_ICPCSET_M, pPllConfig->uIcpcSet_M);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_ICPCSET_ADDR, uRegVal);
  
    // PLL_ICPMSET
    // PLL_ICPCSET
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_ICP_SET_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_ICP_SET, PLL_ICPMSET, pPllConfig->uIcpmSet);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_ICP_SET, PLL_ICPCSET, pPllConfig->uIcpcSet);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_ICP_SET_ADDR, uRegVal);
  
    // PLL_LPF_CAP1
    // PLL_LPF_CAP2
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_LPF1_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_LPF1, PLL_LPF_CAP2, pPllConfig->uLpfCap2);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_LPF1, PLL_LPF_CAP1, pPllConfig->uLpfCap1);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_LPF1_ADDR, uRegVal);
  
    // IPTAT_TRIM
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_IPTAT_TRIM_ADDR, pPllConfig->uIptatTrim);
  
    // PLL_RCTRL
    // PLL_CCTRL
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_CRCTRL_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_CRCTRL, PLL_RCTRL, pPllConfig->uRCtrl);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_CRCTRL, PLL_CCTRL, pPllConfig->uCCtrl);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_CRCTRL_ADDR, uRegVal);

#if 0
        // KVCO_DIV_REF_7_0
    uRegVal = pPllConfig->uKvcoDivRef & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_DIV_REF1_KVCO_DIV_REF_7_0_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_DIV_REF1_ADDR, uRegVal);
  
    // KVCO_DIV_REF_9_8
    uRegVal = (pPllConfig->uKvcoDivRef >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_DIV_REF2_KVCO_DIV_REF_9_8_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_DIV_REF2_ADDR, uRegVal);
#endif

    //*************************************************************************************
    //*      Configure the frequency dependent PLL registers
    //*************************************************************************************
    // DEC_START
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DEC_START_ADDR, pPllConfig->uDecStart);
  
    // DIV_FRAC_START_7_0
    uRegVal = pPllConfig->uDivFracStart & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DIV_FRAC_START1_DIV_FRAC_START_7_0_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DIV_FRAC_START1_ADDR, uRegVal);
  
    // DIV_FRAC_START_15_8
    uRegVal = (pPllConfig->uDivFracStart >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DIV_FRAC_START2_DIV_FRAC_START_15_8_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DIV_FRAC_START2_ADDR, uRegVal);
  
    // DIV_FRAC_START_19_16
    uRegVal = (pPllConfig->uDivFracStart >> 16) &  HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DIV_FRAC_START3_DIV_FRAC_START_19_16_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_DIV_FRAC_START3_ADDR, uRegVal);
  
    // PLLLOCK_CMP_7_0
    uRegVal = (pPllConfig->uPlllockCmp &  HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP1_PLLLOCK_CMP_7_0_BMSK);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP1_ADDR, uRegVal);
  
    // PLLLOCK_CMP_15_8
    uRegVal = (pPllConfig->uPlllockCmp >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP2_PLLLOCK_CMP_15_8_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP2_ADDR, uRegVal);
  
    // PLLLOCK_CMP_17_16
    uRegVal = (pPllConfig->uPlllockCmp >> 16) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP3_PLLLOCK_CMP_17_16_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLLLOCK_CMP3_ADDR, uRegVal);
  

  
    // VCO_COUNT_7_0
    uRegVal = pPllConfig->uVcoCount & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_COUNT1_VCO_COUNT_7_0_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_COUNT1_ADDR, uRegVal);
  
    // VCO_COUNT_9_8
    uRegVal = (pPllConfig->uVcoCount >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_COUNT2_VCO_COUNT_15_8_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_VCO_COUNT2_ADDR, uRegVal);
  
    // KVCO_COUNT_7_0
    uRegVal = pPllConfig->uKvcoCount & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_COUNT1_KVCO_COUNT_7_0_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_COUNT1_ADDR, uRegVal);
  
    // KVCO_COUNT_9_8
    uRegVal = (pPllConfig->uKvcoCount >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_COUNT2_KVCO_COUNT_9_8_BMSK;
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_COUNT2_ADDR, uRegVal);

    // TX_BAND
    // PLL_LPF_RES1
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_LPF2_POSTDIV_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_LPF2_POSTDIV, TX_BAND, pPllConfig->uTxBand);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_PLL_LPF2_POSTDIV, PLL_LPF_RES1, pPllConfig->uPllLpfRes1);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_LPF2_POSTDIV_ADDR, uRegVal);
  
    // KVCO_CODE
    uRegVal = in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_CODE_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_KVCO_CODE, KVCO_CODE, pPllConfig->uKvcoCode);
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_KVCO_CODE_ADDR, uRegVal);
    
    if (TRUE == pPllConfig->bSSCEnable)
    {
      // SSC_CENTER
      // SSC_EN
      uRegVal = 0;
      uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_SSC_EN_CENTER, SSC_CENTER, pPllConfig->bCenterSpread);
      uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_PLL_SSC_EN_CENTER, SSC_EN, pPllConfig->bSSCEnable);
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_EN_CENTER_ADDR, uRegVal);
    
      // SSC_ADJPER_7_0
      uRegVal = pPllConfig->uSscAdjPer & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_ADJ_PER1_SSC_ADJPER_7_0_BMSK;
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_ADJ_PER1_ADDR, uRegVal);
    
      // SSC_ADJPER_9_8
      uRegVal = (pPllConfig->uSscAdjPer >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_ADJ_PER2_SSC_ADJPER_9_8_BMSK;
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_ADJ_PER2_ADDR, uRegVal);
    
      // SSC_PER_7_0
      uRegVal = pPllConfig->uSscPer & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_PER1_SSC_PER_7_0_BMSK;
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_PER1_ADDR, uRegVal);
    
      // SSC_PER_9_8
      uRegVal = (pPllConfig->uSscPer >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_PER2_SSC_PER_15_8_BMSK;
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_PER2_ADDR, uRegVal);
    
      // SSC_STEPSIZE_7_0
      uRegVal = pPllConfig->uSscStepSize & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_STEP_SIZE1_SSC_STEPSIZE_7_0_BMSK;
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_STEP_SIZE1_ADDR, uRegVal);
    
      // SSC_STEPSIZE_15_8
      uRegVal = (pPllConfig->uSscStepSize >> 8) & HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_STEP_SIZE2_SSC_STEPSIZE_15_8_BMSK;
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_SSC_STEP_SIZE2_ADDR, uRegVal);
    }
  }
  else           // DSI_Device_1 and PLL is shared
  {
    // PLL_LDO_CTRL
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_MISC1_ADDR, pPllConfig->uPllLdoCtrl);
  
    // PLL_BANDGAP
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_PLL_BANDGAP_ADDR, 0x3);
  }
}



/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_SetupLanePhy()
*/
/*!
* \brief
*     Setup DSI PHY Lane parameters
*
* \param [in]  eDeviceId     - DSI core ID
* \param [in]  eLaneId       - DSI lane ID
* \param [in]  pConfig       - pointer to PHY config data structure
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_DSI_Phy_SetupLanePhy(DSI_Device_IDType eDeviceId, DSI_LaneIDType eLaneId, HAL_DSI_PHY_LaneConfigType *pConfig)
{
  HAL_MDSS_ErrorType   eStatus       = HAL_MDSS_STATUS_SUCCESS;
  uint32               uRegVal       = 0;
  uintPtr              uOffset       = HAL_DSI_GetRegBaseOffset(eDeviceId) + HAL_DSI_Phy_GetLaneOffset(eLaneId);
  uint32               uHSTxStrength = 0;
  uint32               uClkLane      = 0;
  
  if (DSI_LaneID_CLK == eLaneId)
  {
    uClkLane      = 1;
    uHSTxStrength = pConfig->uClockStrengthHS;
  }
  else
  {
    uClkLane      = 0;
    uHSTxStrength = pConfig->uDataStrengthHS;
  }
  
  // DSIPHY_STR_LP_N
  // DSIPHY_STR_LP_P
  uRegVal = 0;
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_STRENGTH_CTRL_0, DSIPHY_STR_LP_N, pConfig->uDataStrengthLP_N);
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_STRENGTH_CTRL_0, DSIPHY_STR_LP_P, pConfig->uDataStrengthLP_P);
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_STRENGTH_CTRL_0_ADDR, uRegVal);
  
  if(DSI_LaneID_CLK == eLaneId)
  {
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_STRENGTH_CTRL_1_ADDR, 0x00000000);
  }
  else
  {
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_STRENGTH_CTRL_1_ADDR, 0x00000006);
  }
  
  // DSIPHY_VREG_CTRL
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_VREG_CNTRL_ADDR, 0x0000001D);
  
  // DSIPHY_LPRX_DLY
  // IS_CKLANE
  uRegVal = 0x0000000F;
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG3, IS_CKLANE, uClkLane);
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG3_ADDR, uRegVal);
  
  // DLN0_CFG2
  uRegVal = 0;
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG2, DSIPHY_PEMPH_STRBOT, pConfig->uPemphBottom);
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG2, DSIPHY_PEMPH_STRTOP, pConfig->uPemphTop);
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG2, DSIPHY_PEMPH_EN, pConfig->bPemphEnable);
  uRegVal = HWIO_OUT_FLD(uRegVal, DSI_0_PHY_DSIPHY_DLN0_CFG2, DSIPHY_STR_VALUE_OVERRIDE, pConfig->bStrengthOverride);
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_CFG2_ADDR, uRegVal);
  
  // DLN0_TEST_DATAPATH
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TEST_DATAPATH_ADDR, 0x00000000);
  
  // DLN0_TEST_STR
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_DLN0_TEST_STR_ADDR, uHSTxStrength);
  
  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_Phy_ResetPhy()
*/
/*!
* \brief
* 
*
* \param [in]  eDeviceId - DSI core ID
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static void HAL_DSI_Phy_ResetPhy(DSI_Device_IDType eDeviceId)
{
  uintPtr uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId);

  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_1_ADDR, HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_1_DSIPHY_SW_RESET_BMSK);
  DSI_OSAL_SleepUs(1000);          /* delay ~1ms */
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_1_ADDR, 0x0);

  return;
}


/* -----------------------------------------------------------------------
** Public functions
** ----------------------------------------------------------------------- */

/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyDisable()
*/
/*!
* \brief
*     Disables DSI Phy.
*
* \param [in]   eDeviceId   - DSI core ID
*
* \retval None
*
****************************************************************************/
void HAL_DSI_2_1_0_PhyDisable(DSI_Device_IDType   eDeviceId)
{
  uintPtr uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId);

  // Disable PLL
  HAL_DSI_Phy_PllEnable(eDeviceId, FALSE);

  // PLL block power down
  out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_CTRL_0_ADDR, 0);
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyPllEnable()
*/
/*!
* \brief
*     Enable or Disable Pll
*
* \param [in]   eDeviceId   - DSI core ID
* \param [in]   bEnable     - true to enable pll and false to disable pll

*
* \retval None
*
****************************************************************************/
void HAL_DSI_2_1_0_PhyPllEnable(DSI_Device_IDType eDeviceId, bool32 bEnable)
{
  HAL_DSI_Phy_PllEnable(eDeviceId, bEnable);
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyPllPowerCtrl()
*/
/*!
* \brief
*     Power up/down PLL, LDO and powergen.
*
*
* \param [in]  eDeviceId    - DSI core ID
* \param [in]  bPllPowerUp  - TRUE: power up, FALSE: power down;
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhyPllPowerCtrl(DSI_Device_IDType   eDeviceId,
                                                 bool32              bPllPowerUp)
{
  HAL_MDSS_ErrorType   eStatus     = HAL_MDSS_STATUS_SUCCESS;
  /*
  * Moved the implementation to HAL_DSI_2_1_0_PhyPllSetup to enable programming PHY and PLL
  * together
  */

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhySetup()
*/
/*!
* \brief
*     Set up DSI Phy alone.
*
* \param [in]  eDeviceId          - DSI core ID
* \param [IN]  psDsiPhyConfig     - Phy configuration
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhySetup(DSI_Device_IDType          eDeviceId,
                                          HAL_DSI_PhyConfigType     *psDsiPhyConfig)
{
  HAL_MDSS_ErrorType          eStatus         = HAL_MDSS_STATUS_SUCCESS;
  
  if ((DSI_DeviceID_0 != eDeviceId) &&
      (DSI_DeviceID_1 != eDeviceId))
  {
      eStatus = HAL_MDSS_DSI_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uintPtr                      uOffset  = HAL_DSI_GetRegBaseOffset(eDeviceId);
    HAL_DSI_PHY_PhySettingsType  sPhySettings;

    // LDO settings
    if (HAL_DSI_PLL_CONFIG_SPLIT_SOURCE == psDsiPhyConfig->ePLLConfigSource)
    {
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_LDO_CNTRL_ADDR, 0x0000003C);
    }
    else
    {
      out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_LDO_CNTRL_ADDR, 0x0000001C);
    }

    // set global test control
    out_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_CMN_GLBL_TEST_CTRL_ADDR, 0x00000001);

    /* Lane Settings */
    DSI_OSAL_MemZero(&sPhySettings, sizeof(HAL_DSI_PHY_PhySettingsType));
    sPhySettings.sLaneConfig.uDataStrengthLP_N = 0xF;
    sPhySettings.sLaneConfig.uDataStrengthLP_P = 0xF;
    sPhySettings.sLaneConfig.uDataStrengthHS   = 0x88;
    sPhySettings.sLaneConfig.uClockStrengthHS  = 0x88;
    sPhySettings.sLaneConfig.uPemphBottom      = HAL_DSI_PHY_PLL_PRE_EMPHASIS_BOTTOM_DEFAULT;
    sPhySettings.sLaneConfig.uPemphTop         = HAL_DSI_PHY_PLL_PRE_EMPHASIS_TOP_DEFAULT;
    sPhySettings.sLaneConfig.bPemphEnable      = FALSE;
    sPhySettings.sLaneConfig.bStrengthOverride = TRUE;

    /* Program HW */
    eStatus = HAL_DSI_Phy_CommitPhy(eDeviceId, &sPhySettings);
  }
   
  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyPllSetup()
*/
/*!
* \brief
*     Set up DSI PLL, pass back some config parameters, such as VCO output frequency, 
*     PCLK divider ratio for CC in the form of numerator and denominator, etc.
*
* \param [in]   psDsiPhyConfig     - Phy config info
* \param [out]  psDsiPhyConfigInfo - Phy & PLL config pass back info
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhyPllSetup(HAL_DSI_PhyConfigType       *psDsiPhyConfig,
                                             HAL_DSI_PhyConfigInfoType   *psDsiPhyConfigInfo)
{
  HAL_MDSS_ErrorType        eStatus           = HAL_MDSS_STATUS_SUCCESS;
  DSI_Device_IDType         eDeviceId         = psDsiPhyConfig->eDeviceId;

  /* validate input parameters */
  if ((eDeviceId != DSI_DeviceID_0) &&
      (eDeviceId != DSI_DeviceID_1))
  {
    eStatus = HAL_MDSS_DSI_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if ((psDsiPhyConfig->uBitsPerPixel != 16) &&
           (psDsiPhyConfig->uBitsPerPixel != 18) &&
           (psDsiPhyConfig->uBitsPerPixel != 24))
  {
    /* unsupported pixel bit depth */
    eStatus = HAL_MDSS_DSI_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if ((psDsiPhyConfig->uNumOfDataLanes == 0) ||
           (psDsiPhyConfig->uNumOfDataLanes > 4))
  {
    /* illegal number of DSI data lanes */
    eStatus = HAL_MDSS_DSI_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    HAL_DSI_PHY_PllConfigType       sPllConfig;
    float                           fDoubleRefFreq;
    float                           fDesired_bitclock;
    float                           fFvco;
    float                           fTemp1;
    uint32                          uPll_postdiv;
    uint32                          uPlllockCntCycle;
    uint32                          uM_Val;
    uint32                          uN_Val;
    uint32                          uKvcoCode;
    HAL_DSI_PHY_PLL_KVCORangeType   aKvcoRangeTable[] = 
    {
        // low          high        kvco     kvco_code
        //---------------------------------------------
        { 1300,         1800,       600,      0x28 },
        { 1800,         2300,       400,      0x2C },
        { 2300,         2600,       280,      0x2F }
    };
    
    /***************************************************************************************
     * Notes:
     *    MMSS DSI PCLK MND
     *         = 2/9, if RGB666 packed and 2 lanes
     *         = 3/8, if RGB565 and 3 lanes
     *         = 4/9, if RGB666 packed and 4 lanes
     *         = 1/1, for other cases
     *   Bitclk_divider
     *         - Clock division ratio required for the divider controlled by DIV_CTRL_3_0
     *         - roundup(1300/full-rate-bitclk), if full-rate-bitclk >= 86.67Mhz
     *         - 15, if otherwise
     *   VCO clock = full-rate-bitclk * Bitclk_divider
     *   Dsiclk_sel
     *         = 0, if RGB111 and 3/4 lanes
     *         = 1, for other cases
     *   Dsiclk_divider
     *         - Clock division ratio required for the divider controlled by DIV_CTRL_7_4
     *         - (MND * 8 * byte_per_pixel/lane/(dsiclk_sel+1)), if byte_per_pixel >= 2
     *         - rounddown(MND * 8 * byte_per_pixel/lane/(dsiclk_sel+1)), for other cases
     ***************************************************************************************/
     // De-assert PLL start
     HAL_DSI_Phy_PllEnable(eDeviceId, FALSE);
    
     // PLL SW reset
     HAL_DSI_Phy_ResetPhy(eDeviceId);
  
    
    DSI_OSAL_MemZero(&sPllConfig, sizeof(HAL_DSI_PHY_PllConfigType));
    
    /* init numerator and denominator of divider ratio in CC to 1 */
    uM_Val = 1;
    uN_Val = 1;
    
    if (psDsiPhyConfig->uBitsPerPixel == 18)
    {
        switch (psDsiPhyConfig->uNumOfDataLanes)
        {
        case 1:
            uM_Val = 2;
            uN_Val = 9;
            break;
    
        case 2:
            uM_Val = 2;
            uN_Val = 9;
            break;
    
        case 4:
            uM_Val = 4;
            uN_Val = 9;
            break;
    
        default:
            break;
        }
    }
    else if ((psDsiPhyConfig->uBitsPerPixel == 16) && 
             (psDsiPhyConfig->uNumOfDataLanes == 3))
    {
        uM_Val = 3;
        uN_Val = 8;
    }
    psDsiPhyConfigInfo->uPClkDivNumerator   = uM_Val;
    psDsiPhyConfigInfo->uPClkDivDenominator = uN_Val;
    
    fDesired_bitclock = (float)psDsiPhyConfig->uDesiredBitClkFreq/1000000.0f;
    
    sPllConfig.uDsiclk_sel          = 1;
    sPllConfig.uN2Div               = 1;
    sPllConfig.bSSCEnable           = FALSE;
    sPllConfig.uLDOOutput           = 0;
    sPllConfig.bDoubleRefFreqEnable = FALSE;
    sPllConfig.bPllTxClkEnable      = TRUE;
    sPllConfig.bClkBufLeftEnable    = TRUE;
    sPllConfig.bClkBufRightEnable   = TRUE;
    
    /**********************************************************************************/
    // PLL POSTDIV
    uPll_postdiv = (fDesired_bitclock < HAL_DSI_PLL_BITCLK_THRESHOLD) ? HAL_DSI_PLL_PARAM_2 : HAL_DSI_PLL_PARAM_1;
    
    /**********************************************************************************/
    // N1DIV
    if (fDesired_bitclock >= HAL_DSI_PLL_BITCLK_THRESHOLD)
    {
        sPllConfig.uN1Div = HAL_DSI_Phy_Roundup(HAL_DSI_PLL_PARAM_1300F / (float)fDesired_bitclock);
    }
    else
    {
        sPllConfig.uN1Div = HAL_DSI_PLL_PARAM_15;
    }
    
    /**********************************************************************************/
    // Fvco
    fFvco = fDesired_bitclock * (float)uPll_postdiv * (float)sPllConfig.uN1Div;
    
    //Save Clock info, uDesiredBitClkFreq is in HZ unit
    psDsiPhyConfigInfo->uPllVcoOutputFreq = uPll_postdiv * sPllConfig.uN1Div * psDsiPhyConfig->uDesiredBitClkFreq;
    psDsiPhyConfigInfo->uBitClkFreq       = psDsiPhyConfig->uDesiredBitClkFreq;
    psDsiPhyConfigInfo->uByteClkFreq      = psDsiPhyConfig->uDesiredBitClkFreq / 8;
    fTemp1 = (float)psDsiPhyConfig->uDesiredBitClkFreq * (float)psDsiPhyConfig->uNumOfDataLanes / (float)psDsiPhyConfig->uBitsPerPixel;
    psDsiPhyConfigInfo->uPclkFreq         = (uint32)fTemp1;

    /**********************************************************************************/
    // n2div
    //
    fTemp1 = (1 == sPllConfig.uDsiclk_sel) ? 2.0f : 1.0f;
    fTemp1 = (float)uM_Val / (float)uN_Val * (float)psDsiPhyConfig->uBitsPerPixel / (float)psDsiPhyConfig->uNumOfDataLanes / fTemp1;
    if (psDsiPhyConfig->uBitsPerPixel >= 16)
    {
        sPllConfig.uN2Div = (uint32)fTemp1;
    }
    else
    {
        sPllConfig.uN2Div = HAL_DSI_Phy_Rounddown(fTemp1);
    }
    
    /**********************************************************************************/
    // DEC_START
    fDoubleRefFreq       = (sPllConfig.bDoubleRefFreqEnable) ? 2.0f : 1.0f;
    sPllConfig.uDecStart = HAL_DSI_Phy_Rounddown(fFvco / HAL_DSI_ESCCLK_SRC / fDoubleRefFreq);
    
    /**********************************************************************************/
    // DIV_FRAC_START
    sPllConfig.uDivFracStart = HAL_DSI_Phy_Round(((fFvco / HAL_DSI_ESCCLK_SRC / fDoubleRefFreq) - sPllConfig.uDecStart) * HAL_DSI_PLL_PARAM_1M);
    
    /**********************************************************************************/
    // SSC_PER, SSC_STEP_SIZE, SSC_EN_CENTER, SSC_ADJ_PER
    sPllConfig.uSscPer       = 0;
    sPllConfig.uSscStepSize  = 0;
    sPllConfig.bCenterSpread = FALSE;
    
    if (sPllConfig.bSSCEnable)
    {
        fTemp1 = HAL_DSI_ESCCLK_SRC / ((float)HAL_DSI_PLL_SSC_FREQ / HAL_DSI_PLL_PARAM_500F);
        sPllConfig.uSscPer = HAL_DSI_Phy_Round(fTemp1 - HAL_DSI_PLL_PARAM_1);
    
        fTemp1 = (fFvco / HAL_DSI_ESCCLK_SRC) * HAL_DSI_PLL_PARAM_1M * HAL_DSI_PLL_SSC_SPREAD *(HAL_DSI_PLL_SSC_ADJ_PER + HAL_DSI_PLL_PARAM_1) / (sPllConfig.uSscPer + HAL_DSI_PLL_PARAM_1);
        sPllConfig.uSscStepSize = HAL_DSI_Phy_Round(fTemp1);
    
        sPllConfig.uSscAdjPer = HAL_DSI_PLL_SSC_ADJ_PER;
    }
    
    /**********************************************************************************/
    // PLLLOCK_CNT & PLLLOCK_RNG
    sPllConfig.uPlllockCnt = HAL_DSI_PLL_PLLLOCK_CNT;
    sPllConfig.uPlllockRng = HAL_DSI_PLL_PLLLOCK_RNG;
    
    /**********************************************************************************/
    // PLLLOCK_CMP
    uPlllockCntCycle = HAL_DSI_PLL_PLLLOCK_CYCLE_32;
    switch (sPllConfig.uPlllockCnt)
    {
    case 0:
        uPlllockCntCycle = HAL_DSI_PLL_PLLLOCK_CYCLE_1024;
        break;
    case 1:
        uPlllockCntCycle = HAL_DSI_PLL_PLLLOCK_CYCLE_256;
        break;
    case 2:
        uPlllockCntCycle = HAL_DSI_PLL_PLLLOCK_CYCLE_128;
        break;
    default:
        uPlllockCntCycle = HAL_DSI_PLL_PLLLOCK_CYCLE_32;
        break;
    }
    fTemp1 = (float)uPlllockCntCycle * (sPllConfig.uDecStart + (float)sPllConfig.uDivFracStart / (float)HAL_DSI_PLL_PARAM_1M) / (float)HAL_DSI_PLL_PARAM_10;
    sPllConfig.uPlllockCmp = HAL_DSI_Phy_Round(fTemp1);
    
    /**********************************************************************************/
    // VCO_DIV_REF
    sPllConfig.uVcoDivRef = HAL_DSI_Phy_Rounddown(HAL_DSI_PLL_VCO_MEASURE_TIME * HAL_DSI_ESCCLK_SRC - HAL_DSI_PLL_PARAM_2);
    
    /**********************************************************************************/
    // KVCO_DIV_REF
    sPllConfig.uKvcoDivRef = HAL_DSI_Phy_Rounddown(HAL_DSI_PLL_KVCO_MEASURE_TIME * HAL_DSI_ESCCLK_SRC - HAL_DSI_PLL_PARAM_1);
    
    /**********************************************************************************/
    // VCO_COUNT
    sPllConfig.uVcoCount = HAL_DSI_Phy_Rounddown(HAL_DSI_PLL_VCO_MEASURE_TIME * fFvco / HAL_DSI_PLL_PARAM_10);
    
    /**********************************************************************************/
    // KVCO_COUNT
    {
        float          fKvcoSlope;
        uint32         i;
    
        fKvcoSlope = 0.0f;
        uKvcoCode  = 0x28;
        for (i = 0; i < sizeof(aKvcoRangeTable) / sizeof(HAL_DSI_PHY_PLL_KVCORangeType); i++)
        {
            if ((fFvco >= aKvcoRangeTable[i].uLow) &&
                (fFvco <= aKvcoRangeTable[i].uHigh))
            {
                fKvcoSlope = (float)aKvcoRangeTable[i].uKvcoSlope;
                uKvcoCode  = aKvcoRangeTable[i].uKvcoCode;
                break;
            }
        }
        sPllConfig.uKvcoCount = HAL_DSI_Phy_Rounddown(HAL_DSI_PLL_PARAM_0_2F * fKvcoSlope / (float)HAL_DSI_PLL_PARAM_10 * HAL_DSI_PLL_KVCO_MEASURE_TIME);
    }
    
    /**********************************************************************************/
    // PLL_LDO_CTRL
    sPllConfig.uPllLdoCtrl = sPllConfig.uLDOOutput * 2 + HAL_DSI_PLL_PARAM_16;
    
    /**********************************************************************************/
    // PLL_LPF_RES1
    sPllConfig.uPllLpfRes1 = HAL_DSI_PLL_LPF_RES1;
    
    /**********************************************************************************/
    // TX_BAND
    switch (uPll_postdiv)
    {
    case 1:
        sPllConfig.uTxBand = 0;
        break;
    case 2:
        sPllConfig.uTxBand = 1;
        break;
    case 4:
        sPllConfig.uTxBand = 2;
        break;
    case 8:
        sPllConfig.uTxBand = 3;
        break;
    default:
        sPllConfig.uTxBand = 0;
        break;
    }
    
    /**********************************************************************************/
    // BANDGAP_TIMER
    sPllConfig.uBandGapTimer = HAL_DSI_PLL_BANDGAP_TIMER;
    
    /**********************************************************************************/
    // PLL_WAKEUP_TIMER
    sPllConfig.uPllWakeupTimer = HAL_DSI_PLL_PLL_WAKEUP_TIMER;
    
    /**********************************************************************************/
    // KVCO_CODE
    sPllConfig.uKvcoCode = uKvcoCode;
    
    /**********************************************************************************/
    // IE_TRIM
    sPllConfig.uIeTrim = HAL_DSI_PLL_IETRIM;
    
    /**********************************************************************************/
    // IP_TRIM
    sPllConfig.uIpTrim = HAL_DSI_PLL_IPTRIM;
    
    /**********************************************************************************/
    // CPMSET_CRU
    sPllConfig.uCpmSetCur = HAL_DSI_PLL_CPMSET_CUR;
    
    /**********************************************************************************/
    // CPCSET_CRU
    sPllConfig.uCpcSetCur = HAL_DSI_PLL_CPCSET_CUR;
    
    /**********************************************************************************/
    // ICPCSET
    sPllConfig.uIcpcSet = HAL_DSI_PLL_ICPCSET;
    
    /**********************************************************************************/
    // ICPMSET
    sPllConfig.uIcpmSet = HAL_DSI_PLL_ICPMSET;
    
    /**********************************************************************************/
    // ICPCSET_P
    sPllConfig.uIcpcSet_P = HAL_DSI_PLL_ICPCSET_P;
    
    /**********************************************************************************/
    // ICPMSET_P
    sPllConfig.uIcpmSet_P = HAL_DSI_PLL_ICPMSET_P;
    
    /**********************************************************************************/
    // ICPCSET_M
    sPllConfig.uIcpcSet_M = HAL_DSI_PLL_ICPCSET_M;
    
    /**********************************************************************************/
    // ICPMSET_M
    sPllConfig.uIcpmSet_M = HAL_DSI_PLL_ICPMSET_M;
    
    /**********************************************************************************/
    // LPF_CAP1
    sPllConfig.uLpfCap1 = HAL_DSI_PLL_LPF_CAP1;
    
    /**********************************************************************************/
    // LPF_CAP2
    sPllConfig.uLpfCap2 = HAL_DSI_PLL_LPF_CAP2;
    
    /**********************************************************************************/
    // IPTAT_TRIM
    sPllConfig.uIptatTrim = HAL_DSI_PLL_IPTAT_TRIM;
    
    /**********************************************************************************/
    // PLL_RCTRL
    sPllConfig.uRCtrl = HAL_DSI_PLL_R3CTRL;
    
    /**********************************************************************************/
    // PLL_CCTRL
    sPllConfig.uCCtrl = HAL_DSI_PLL_C3CTRL;
    
    /* Program HW */
    HAL_DSI_Phy_CommitPll(psDsiPhyConfig->eDeviceId, psDsiPhyConfig->ePLLConfigSource, &sPllConfig);

    /* Enable PLL and detect lock 
     *    For split source, DSI_Device_0 PLL is shared between the two devices 
     */
    if ((HAL_DSI_PLL_CONFIG_SPLIT_SOURCE != psDsiPhyConfig->ePLLConfigSource) ||
        (DSI_DeviceID_0 == eDeviceId)) 
    {      
      eStatus = HAL_DSI_Phy_PllLock(eDeviceId);
    }
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhySetupTimingParams()
*/
/*!
* \brief
*     Calculate PHY timing parameters.
*
* \param [in]  pTimingParameters - DSI core ID
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhySetupTimingParams(HAL_DSI_TimingSettingType *pTimingParameters)
{
  HAL_MDSS_ErrorType           eStatus             = HAL_MDSS_STATUS_SUCCESS;
  HAL_DSI_PHY_TimingConfigType sTimingConfig;

  /* validate input parameters */
  if ((pTimingParameters->eDeviceId != DSI_DeviceID_0) &&
      (pTimingParameters->eDeviceId != DSI_DeviceID_1))
  {
    eStatus = HAL_MDSS_DSI_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {

    DSI_OSAL_MemZero(&sTimingConfig, sizeof(HAL_DSI_PHY_TimingConfigType));

    /* Calculate timing parameters */
    HAL_DSI_Phy_CalculateTimingParams(pTimingParameters, &sTimingConfig);

    /* config timing parameters */
    HAL_DSI_Phy_CommitTimingParams(pTimingParameters->eDeviceId, &sTimingConfig);

  }

  return eStatus;
}



/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyPllReConfigure()
*/
/*!
* \brief
*     Sets up the DSI PLL for dynamic refresh rate reconfiguration and passes
*     back the calculated DSI Phy and PLL information to the caller for the
*     requested refresh rate. Also allows the caller to poll the DSI PHY PLL
*     to ensure that the PLL is locked to the new refresh rate.
*
* \param [in]      psDsiPhyConfig        - Phy configuration information
* \param [in/out]  psDsiPhyPLLConfigInfo - Phy PLL configuration information
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhyReConfigure(DSI_Device_IDType eDeviceID, uint32 RefreshRate)
{
  // Reconfiguring PLL for new refresh rate - To be Implemented
  return HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyPllInitialize()
*/
/*!
* \brief
*     Initialize the phy in to a power-on reset state.
*
* \param 
*
* \retval 
*
****************************************************************************/
void HAL_DSI_2_1_0_PhyPllInitialize(void)
{
  uint32 uControllerIndex;

  // Inialize all phys
  for (uControllerIndex = 0; uControllerIndex < DSI_DeviceID_MAX; uControllerIndex++)
  {
    HAL_DSI_2_1_0_PhyPllPowerCtrl((DSI_Device_IDType)uControllerIndex, TRUE);
  }
}


/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhySetProperty()
*/
/*!
* \brief
*   Configure DSI Phy properties
*
* \param [in] eDeviceId     - DSI core ID
* \param [in] eProperty     - Property ID that requires update
* \param [in] pPropertyData - Contains the new parameters of the property 
*                             that will be applied.
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhySetProperty(DSI_Device_IDType              eDeviceId,
                                                HAL_DSI_PhyPropertyType        eProperty,
                                                HAL_DSI_PhyPropertyParamsType *pPropertyData)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;

  switch (eProperty)
  {

  default:
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
    break;
  }
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyGetProperty
*/
/*!
* \brief
*   Get DSI Phy properties
*
* \param [in] eDeviceId     - DSI core ID
* \param [in] eProperty     - Property ID that is being queried
* \param [in] pPropertyData - Contains the parameters of the property 
*                             that are being queried
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhyGetProperty(DSI_Device_IDType              eDeviceId,
                                                HAL_DSI_PhyPropertyType        eProperty,
                                                HAL_DSI_PhyPropertyParamsType *pPropertyData)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;

  switch (eProperty)
  {
  
  default:
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
    break;
  }
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DSI_2_1_0_PhyGetPllCodes
*/
/*!
* \brief
*   Get PLL codes
*
* \param [in] eDeviceId     - DSI core ID
* \param [in] pBuffer       - Pointer to buffer that stores pll codes
* \param [in] uSize         - Size of the buffer that stores pll codes 
*                             
****************************************************************************/
HAL_MDSS_ErrorType HAL_DSI_2_1_0_PhyGetPllCodes(DSI_Device_IDType               eDeviceId,
                                                HAL_DSI_PHY_Dynamic_Cal_Result *psPllCodes)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uintPtr            uOffset = HAL_DSI_GetRegBaseOffset(eDeviceId);  

  if (NULL == psPllCodes)
  {
    eStatus = HAL_MDSS_DSI_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    psPllCodes->uPllCodes[0] =in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_CORE_KVCO_CODE_STATUS_ADDR);
    psPllCodes->uPllCodes[1] =in_dword(uOffset + HWIO_MMSS_DSI_0_PHY_DSIPHY_PLL_CORE_VCO_TUNE_STATUS_ADDR);
  }
  return eStatus;
}

#ifdef __cplusplus
}
#endif
