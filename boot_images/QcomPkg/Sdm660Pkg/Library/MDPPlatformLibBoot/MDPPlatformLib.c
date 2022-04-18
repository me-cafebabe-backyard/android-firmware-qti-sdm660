/*=============================================================================
 
  File: MDPPlatformLib.c
 
  MDP platform specific functions
  
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Library/PcdLib.h>
#include <api/systemdrivers/pmic/pm_lcdb.h>
#include <api/systemdrivers/pmic/pm_wled.h>
#include <api/systemdrivers/pmic/pm_ldo.h>
#include <api/systemdrivers/pmic/pm_boot.h>
#include "MDPTypes.h"
#include "MDPPlatformLib.h"
#include "MDPSystem.h"
#include "DDITlmm.h"
#include "pmapp_npa.h"
#include "npa.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */
#define HDMI_CEC_DATA_GPIO                31
#define HDMI_DDC_CLK_GPIO                 32
#define HDMI_DDC_DATA_GPIO                33
#define HDMI_HPD_GPIO                     34

#define PCD_PANEL_TYPE_OEM                1

#define DSI_READ_ADDRESS_SIZE             2
#define DSI_READ_READBACK_SIZE            8

#define PLATFORM_PANEL_ID_MAX_COMMANDS    3       // maximum panel ID read commands

// PMIC Device Indices
#define PMIC_DEV_INDEX                    0       // PMIC device (Vreg, LDO, ect)
#define PMIC_PMI_DEV_INDEX                1       // PMIC interface device (IBB/LAB, GPIO,  WLED)

#define PMIC_IBBLAB_READYTIME             25      // Maximum of milliseconds to wait for IBB/LAB to stabilize (Can be up to 8.8ms +/-16%)

/* SDM660 Main Panel CDP specific defines
*/
#define CDP_DISP_RESET_GPIO               53      //GPIO number for LCD0_RESET_N
#define CDP_DISP_TE_GPIO                  59      //GPIO number for TE


/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* Panel command ID list for dynamic panel detection
*/

typedef struct {
  uint8      address[DSI_READ_ADDRESS_SIZE];                                        // DCS command for panel ID
  uint8      expectedReadback[DSI_READ_READBACK_SIZE];                              // expected readback
} PlatformPanelIDCommandInfo;

/* Dynamic panel ID detection entry 
 */
typedef struct {
  uint8                         uCmdType;                                             // data type for panel ID DSI read
  uint32                        uTotalRetry;                                          // number of retry if DSI read fails
  PlatformPanelIDCommandInfo    panelIdCommands[PLATFORM_PANEL_ID_MAX_COMMANDS];      // commands for panel ID and expected readback
  uint32                        uLaneRemapOrder;                                      // Lane remap order
  const int8                   *psPanelCfg;                                           // pointer to the panel configuration
  uint32                        uPanelCfgSize;                                        // size of panel configuration data
  uint32                        uFlags;                                               // flags to set clock config for now, can set other config in future
} PlatformDSIDetectParams;

/* Power configuration 
 */
typedef struct
{
  MDP_PmicModuleControlType     ePMICSecondaryPower[MDP_DISPLAY_MAX];                 // Configuration for PMIC based secondary power source
  uint32                        uWledStringsPrimary;                                  // Set of WLED strings needed for this platform
} Panel_PowerCtrlParams;
/* NPA Client info
*/
typedef struct
{
  char*                         cResourceName;
  char*                         cClientName;
}NPAClientName;

/* -----------------------------------------------------------------------
** Local functions
** ----------------------------------------------------------------------- */

/* Platform detection 
*/
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChiSetFamily);
static MDP_Status DynamicDSIPanelDetection(MDPPlatformParams *pPlatformParams, uint32 *puPanelID, uint32 uOverrideId);


/* 8998 Main Panel CDP Functions
*/
static MDP_Status Panel_CDP_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
static MDP_Status Panel_CDP_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
static MDP_Status Panel_CDP_Reset(void);

static MDP_Status Panel_CDP_BacklightLevel(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, BacklightConfigType *pBacklightConfig);
static MDP_Status Panel_CDP_PeripheralPower(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, bool32 bPowerUp);

/* Main Panel CDP/MTP Functions
*/

/* 8996 HDMI Panel Functions
*/
static MDP_Status HDMI_CDP_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
static MDP_Status HDMI_CDP_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
MDP_Status HDMI_EnableTLMM_DDC_HPD(void);
MDP_Status HDMI_DisableTLMM_DDC_HPD(void);

/* General helper functions */
MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList);

/*===========================================================================
 Local Configuration Definitions
 ===========================================================================*/
 
/******************************************************************
 *           Truly 5.5in 2k  TFT2P2827-E                          *
 *                                                                *
 *                   1440x2560                                    *
 *                   Dual-DSI                                     *
 *                   Cmd mode                                     *
 ******************************************************************/
const static int8 Truly_TFT2P2827_E_cmd_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>TFT2P2827-E</PanelName>"
"<PanelDescription>Truly Dual DSI Command Mode Panel (1440x2560 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive units=\"Dot Clocks\">1440</HorizontalActive>"
" <HorizontalFrontPorch units=\"Dot Clocks\">100</HorizontalFrontPorch>"
" <HorizontalBackPorch units=\"Dot Clocks\">32</HorizontalBackPorch>"
" <HorizontalSyncPulse units=\"Dot Clocks\">16</HorizontalSyncPulse>"
" <VerticalActive units=\"Dot Clocks\">2560</VerticalActive>"
" <VerticalFrontPorch units=\"Lines\">8</VerticalFrontPorch>"
" <VerticalBackPorch units=\"Lines\">7</VerticalBackPorch>"
" <VerticalSyncPulse units=\"Lines\">1</VerticalSyncPulse>"
"</Group>"
"<Group id=\"Display Interface\">"
" <InterfaceType units=\"QDI_DisplayConnectType\">9</InterfaceType>"
" <InterfaceColorFormat units=\"QDI_PixelFormatType\">3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <DSIChannelId units=\"DSI_Channel_IDType\">2</DSIChannelId>"
" <DSIVirtualId units=\"DSI_Display_VCType\">0</DSIVirtualId>"
" <DSIColorFormat units=\"DSI_ColorFormatType\">36</DSIColorFormat>"
" <DSITrafficMode units=\"DSI_TrafficModeType\">2</DSITrafficMode>"
" <DSILanes units=\"integer\">4</DSILanes>"
" <DSICMDSwapInterface>False</DSICMDSwapInterface>"
" <DSICMDUsingTrigger>False</DSICMDUsingTrigger>"
" <DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
" <DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
" <DSIClockHSForceRequest>1</DSIClockHSForceRequest>"
" <DSIRefreshRate units='integer Q16.16'>0x3C0000</DSIRefreshRate>\n"
" <DSIInitMasterTime units='integer'>32</DSIInitMasterTime>\n"  
" <DSIControllerMapping>\n"
"  00 01\n"
" </DSIControllerMapping>\n" 
"</Group>"
"<DSIInitSequence>"
" FF 20\n"
" 15 FF 20\n"
" 15 FB 01\n"
" 15 00 01\n"
" 15 01 55\n"
" 15 02 45\n"
" 15 05 40\n"
" 15 06 19\n"
" 15 07 1E\n"
" 15 0B 73\n"
" 15 0C 73\n"
" 15 0E B0\n"
" 15 0F AE\n"
" 15 11 B8\n"
" 15 13 00\n"
" 15 58 80\n"
" 15 59 01\n"
" 15 5A 00\n"
" 15 5B 01\n"
" 15 5C 80\n"
" 15 5D 81\n"
" 15 5E 00\n"
" 15 5F 01\n"
" 15 72 31\n"
" 15 68 03\n"
" 15 FF 24\n"
" 15 FB 01\n"
" 15 00 1C\n"
" 15 01 0B\n"
" 15 02 0C\n"
" 15 03 01\n"
" 15 04 0F\n"
" 15 05 10\n"
" 15 06 10\n"
" 15 07 10\n"
" 15 08 89\n"
" 15 09 8A\n"
" 15 0A 13\n"
" 15 0B 13\n"
" 15 0C 15\n"
" 15 0D 15\n"
" 15 0E 17\n"
" 15 0F 17\n"
" 15 10 1C\n"
" 15 11 0B\n"
" 15 12 0C\n"
" 15 13 01\n"
" 15 14 0F\n"
" 15 15 10\n"
" 15 16 10\n"
" 15 17 10\n"
" 15 18 89\n"
" 15 19 8A\n"
" 15 1A 13\n"
" 15 1B 13\n"
" 15 1C 15\n"
" 15 1D 15\n"
" 15 1E 17\n"
" 15 1F 17\n"
" 15 20 40\n"
" 15 21 01\n"
" 15 22 00\n"
" 15 23 40\n"
" 15 24 40\n"
" 15 25 6D\n"
" 15 26 40\n"
" 15 27 40\n"
" 15 E0 00\n"
" 15 DC 21\n"
" 15 DD 22\n"
" 15 DE 07\n"
" 15 DF 07\n"
" 15 E3 6D\n"
" 15 E1 07\n"
" 15 E2 07\n"
" 15 29 D8\n"
" 15 2A 2A\n"
" 15 4B 03\n"
" 15 4C 11\n"
" 15 4D 10\n"
" 15 4E 01\n"
" 15 4F 01\n"
" 15 50 10\n"
" 15 51 00\n"
" 15 52 80\n"
" 15 53 00\n"
" 15 56 00\n"
" 15 54 07\n"
" 15 58 07\n"
" 15 55 25\n"
" 15 5B 43\n"
" 15 5C 00\n"
" 15 5F 73\n"
" 15 60 73\n"
" 15 63 22\n"
" 15 64 00\n"
" 15 67 08\n"
" 15 68 04\n"
" 15 72 02\n"
" 15 7A 80\n"
" 15 7B 91\n"
" 15 7C D8\n"
" 15 7D 60\n"
" 15 7F 15\n"
" 15 75 15\n"
" 15 B3 C0\n"
" 15 B4 00\n"
" 15 B5 00\n"
" 15 78 00\n"
" 15 79 00\n"
" 15 80 00\n"
" 15 83 00\n"
" 15 93 0A\n"
" 15 94 0A\n"
" 15 8A 00\n"
" 15 9B FF\n"
" 15 9D B0\n"
" 15 9F 63\n"
" 15 98 10\n"
" 15 EC 00\n"
" 15 FF 10\n"
" 15 3B 03 0A 0A\n"
" 15 35 00\n"
" 15 E5 01\n"
" 15 BB 10\n"
" 15 c0 00\n"  
" 39 c9 01 01 70 00 0a 06 67 04 c5 12 18\n" 
" 15 FB 01\n"
" 05 11 00\n"
" ff 64\n"
" 05 29 00\n"
"</DSIInitSequence>"
"<DSITermSequence>\n"
" 05 28 00\n"
" FF 0A\n"
" 05 10 00\n"
" FF 3C\n"
"</DSITermSequence>\n"
"<Group id='Backlight Configuration'>"
" <BacklightType units='MDP_Panel_BacklightType'>1</BacklightType>\n"
" <BacklightPmicControlType units='MDP_PmicBacklightControlType'>2</BacklightPmicControlType>\n"  
"</Group>\n";

/******************************************************************
 *           Truly FHD (1080 x 1920) Video mode                   *
 *                                                                *
 ******************************************************************/
const static int8 Truly_NT35695b_FHD_video_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>NT35695b</PanelName>"
"<PanelDescription>Truly FHD DSI Video Mode Panel (1080x1920 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive units=\"Dot Clocks\">1080</HorizontalActive>"
" <HorizontalFrontPorch units=\"Dot Clocks\">120</HorizontalFrontPorch>"
" <HorizontalBackPorch units=\"Dot Clocks\">60</HorizontalBackPorch>"
" <HorizontalSyncPulse units=\"Dot Clocks\">12</HorizontalSyncPulse>"
" <VerticalActive units=\"Dot Clocks\">1920</VerticalActive>"
" <VerticalFrontPorch units=\"Lines\">12</VerticalFrontPorch>"
" <VerticalBackPorch units=\"Lines\">2</VerticalBackPorch>"
" <VerticalSyncPulse units=\"Lines\">2</VerticalSyncPulse>"
"</Group>"
"<Group id=\"Display Interface\">"
" <InterfaceType units=\"QDI_DisplayConnectType\">8</InterfaceType>"
" <InterfaceColorFormat units=\"QDI_PixelFormatType\">3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <DSIChannelId units=\"DSI_Channel_IDType\">1</DSIChannelId>"
" <DSIVirtualId units=\"DSI_Display_VCType\">0</DSIVirtualId>"
" <DSIColorFormat units=\"DSI_ColorFormatType\">36</DSIColorFormat>"
" <DSITrafficMode units=\"DSI_TrafficModeType\">2</DSITrafficMode>"
" <DSILanes units=\"integer\">4</DSILanes>"
" <DSILowPowerModeInBLLPEOF units='Bool'>True</DSILowPowerModeInBLLPEOF>\n"
" <DSILowPowerModeInBLLP units='Bool'>True</DSILowPowerModeInBLLP>\n"
" <DSIRefreshRate units='integer Q16.16'>0x3C0000</DSIRefreshRate>\n"
" <DSIInitMasterTime units='integer'>1</DSIInitMasterTime>\n"  
" <DSIControllerMapping>\n"
"  00\n"
" </DSIControllerMapping>\n" 
"</Group>"
"<DSIInitSequence>"
" 15 ff 20\n" 
" ff 10\n"
" 15 fb 01\n"
" 15 00 01\n"
" 15 01 55\n"
" 15 02 45\n"
" 15 03 55\n"
" 15 05 50\n"
" 15 06 a8\n"
" 15 07 ad\n"
" 15 08 0c\n"
" 15 0b aa\n"
" 15 0c aa\n"
" 15 0e b0\n"
" 15 0f b3\n"
" 15 11 28\n"
" 15 12 10\n"
" 15 13 01\n"
" 15 14 4a\n"
" 15 15 12\n"
" 15 16 12\n"
" 15 30 01\n"
" 15 72 11\n"
" 15 58 82\n"
" 15 59 00\n"
" 15 5a 02\n"
" 15 5b 00\n"
" 15 5c 82\n"
" 15 5d 80\n"
" 15 5e 02\n"
" 15 5f 00\n"
" 15 ff 24\n"
" 15 fb 01\n"
" 15 00 01\n"
" 15 01 0b\n"
" 15 02 0c\n"
" 15 03 89\n"
" 15 04 8a\n"
" 15 05 0f\n"
" 15 06 10\n"
" 15 07 10\n"
" 15 08 1c\n"
" 15 09 00\n"
" 15 0a 00\n"
" 15 0b 00\n"
" 15 0c 00\n"
" 15 0d 13\n"
" 15 0e 15\n"
" 15 0f 17\n"
" 15 10 01\n"
" 15 11 0b\n"
" 15 12 0c\n"
" 15 13 89\n"
" 15 14 8a\n"
" 15 15 0f\n"
" 15 16 10\n"
" 15 17 10\n"
" 15 18 1c\n"
" 15 19 00\n"
" 15 1a 00\n"
" 15 1b 00\n"
" 15 1c 00\n"
" 15 1d 13\n"
" 15 1e 15\n"
" 15 1f 17\n"
" 15 20 00\n"
" 15 21 01\n"
" 15 22 00\n"
" 15 23 40\n"
" 15 24 40\n"
" 15 25 6d\n"
" 15 26 40\n"
" 15 27 40\n"
" 15 29 d8\n"
" 15 2a 2a\n"
" 15 4b 03\n"
" 15 4c 11\n"
" 15 4d 10\n"
" 15 4e 01\n"
" 15 4f 01\n"
" 15 50 10\n"
" 15 51 00\n"
" 15 52 80\n"
" 15 53 00\n"
" 15 54 07\n"
" 15 55 25\n"
" 15 56 00\n"
" 15 58 07\n"
" 15 5b 43\n"
" 15 5c 00\n"
" 15 5f 73\n"
" 15 60 73\n"
" 15 63 22\n"
" 15 64 00\n"
" 15 67 08\n"
" 15 68 04\n"
" 15 7a 80\n"
" 15 7b 91\n"
" 15 7c d8\n"
" 15 7d 60\n"
" 15 93 06\n"
" 15 94 06\n"
" 15 8a 00\n"
" 15 9b 0f\n"
" 15 b3 c0\n"
" 15 b4 00\n"
" 15 b5 00\n"
" 15 b6 21\n"
" 15 b7 22\n"
" 15 b8 07\n"
" 15 b9 07\n"
" 15 ba 22\n"
" 15 bd 20\n"
" 15 be 07\n"
" 15 bf 07\n"
" 15 c1 6d\n"
" 15 c4 24\n"
" 15 e3 00\n"
" 15 ec 00\n"
" 15 ff 10\n"
" 15 bb 03\n"
" 05 11 00\n"
" ff 78\n"
" 05 29 00\n"           
" ff 78\n"
"</DSIInitSequence>"
"<DSITermSequence>\n"
" 05 28 00\n"
" FF 14\n"
" 05 10 00\n"
" FF 78\n"
"</DSITermSequence>\n"
"<Group id='Backlight Configuration'>"
" <BacklightType units='MDP_Panel_BacklightType'>1</BacklightType>\n"
" <BacklightPmicControlType units='MDP_PmicBacklightControlType'>2</BacklightPmicControlType>\n"  
"</Group>\n";


/*
* Dummy panel configuration, default fallback mode.
*
*/
const static int8 dummy_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"    <PanelName>VirtioDSI</PanelName>"
"    <PanelDescription>DSI Model (640x480 24bpp)</PanelDescription>"
"    <Group id=\"Active Timing\">"
"        <HorizontalActive units=\"Dot Clocks\">640</HorizontalActive>"
"        <HorizontalFrontPorch units=\"Dot Clocks\">13</HorizontalFrontPorch>"
"        <HorizontalBackPorch units=\"Dot Clocks\">14</HorizontalBackPorch>"
"        <HorizontalSyncPulse units=\"Dot Clocks\">15</HorizontalSyncPulse>"
"        <HorizontalSyncSkew units=\"Dot Clocks\">0</HorizontalSyncSkew>"
"        <HorizontalLeftBorder units=\"Dot Clocks\">0</HorizontalLeftBorder>"
"        <HorizontalRightBorder units=\"Dot Clocks\">0</HorizontalRightBorder>"
"        <VerticalActive units=\"Dot Clocks\">480</VerticalActive>"
"        <VerticalFrontPorch units=\"Lines\">11</VerticalFrontPorch>"
"        <VerticalBackPorch units=\"Lines\">12</VerticalBackPorch>"
"        <VerticalSyncPulse units=\"Lines\">13</VerticalSyncPulse>"
"        <VerticalSyncSkew units=\"Lines\">0</VerticalSyncSkew>"
"        <VerticalTopBorder units=\"Lines\">0</VerticalTopBorder>"
"        <VerticalBottomBorder units=\"Lines\">0</VerticalBottomBorder>"
"        <InvertDataPolarity>False</InvertDataPolarity>"
"        <InvertVsyncPolairty>False</InvertVsyncPolairty>"
"        <InvertHsyncPolarity>False</InvertHsyncPolarity>"
"        <BorderColor>0x0</BorderColor>"   
"    </Group>"
"    <Group id=\"Display Interface\">"
"        <InterfaceType units=\"QDI_DisplayConnectType\">8</InterfaceType>"
"        <InterfaceColorFormat units=\"QDI_PixelFormatType\">3</InterfaceColorFormat>"
"    </Group>"
"    <Group id=\"DSI Interface\">"
"        <DSIChannelId units=\"DSI_Channel_IDType\">1</DSIChannelId>"     
"        <DSIVirtualId units=\"DSI_Display_VCType\">0</DSIVirtualId>"     
"        <DSIColorFormat units=\"DSI_ColorFormatType\">36</DSIColorFormat>"     
"        <DSITrafficMode units=\"DSI_TrafficModeType\">0</DSITrafficMode>"
"        <DSILanes units=\"integer\">2</DSILanes>"
"        <DSIHsaHseAfterVsVe units=\"Bool\">False</DSIHsaHseAfterVsVe>"
"        <DSILowPowerModeInHFP units=\"Bool\">False</DSILowPowerModeInHFP>"
"        <DSILowPowerModeInHBP units=\"Bool\">False</DSILowPowerModeInHBP>"
"        <DSILowPowerModeInHSA units=\"Bool\">False</DSILowPowerModeInHSA>"
"        <DSILowPowerModeInBLLPEOF units=\"Bool\">False</DSILowPowerModeInBLLPEOF>"
"        <DSILowPowerModeInBLLP units=\"Bool\">False</DSILowPowerModeInBLLP>"
"        <DSIRefreshRate>0x3c0000</DSIRefreshRate>" 
"    </Group>"
"        <DisplayPrimaryFlags>0x2</DisplayPrimaryFlags>"
"    <DSIInitSequence>"
"    32 00 00\n"
"    </DSIInitSequence>";

/*===========================================================================
Function Definitions
===========================================================================*/

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: PlatformClientInit()
** 
** DESCRIPTION:
**        Initialize NPA client
**
*//* -------------------------------------------------------------------- */
static MDP_Status PlatformClientInit(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status    eStatus = MDP_STATUS_OK;

  return eStatus;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PowerUp()
** 
** DESCRIPTION:
**        Panel power up sequence for CDP
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status        eStatus        = MDP_STATUS_OK;
 
  if (MDP_STATUS_OK != (eStatus =  PlatformClientInit(eDisplayId, pPowerParams)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Failed to initialize handle for Primary display NPA node.\n");
  }
  else
  {
    DALGpioSignalType uGPIOCfg = 0;

    /* LDOs 1A & 1B for DSI PHY/PLL are already turned on by system driver.*/

    /*Turn on LDO14 for V_LCD_VDDI_1P8 which is used by panel */
    if (PM_ERR_FLAG__SUCCESS != pm_ldo_volt_level(PMIC_DEV_INDEX, PM_LDO_11, 1800000))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error configuring LDO11 to 1.8V\n");
    }

    if (PM_ERR_FLAG__SUCCESS != pm_ldo_sw_enable(PMIC_DEV_INDEX, PM_LDO_11, PM_ON))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO11\n");
    }

    MDP_OSAL_DELAYMS(10);   /* delay 10ms to allow power grid to settle */      
      
    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
 
    MDP_OSAL_DELAYUS(10);
    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

    MDP_OSAL_DELAYUS(10);
      
    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
    
    MDP_OSAL_DELAYMS(10);   /* delay 10ms for panel to reset (from panel spec) */

  }

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PowerDown()
** 
** DESCRIPTION:
**        Panel power down sequence for CDP
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status          eStatus      = MDP_STATUS_OK;
  DALGpioSignalType   uGPIOCfg     = 0;
  /*Turn OFF LDO14 for V_LCD_VDDI_1P8 which is used by panel */
  if (PM_ERR_FLAG__SUCCESS != pm_ldo_sw_enable(PMIC_DEV_INDEX, PM_LDO_14, PM_OFF))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Error enabling LDO2\n");
  }

  
  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_Reset()
** 
** DESCRIPTION:
**        Panel reset sequence for CDP
**
*/ /* -------------------------------------------------------------------- */
MDP_Status Panel_CDP_Reset(void)
{
  MDP_Status          eStatus     = MDP_STATUS_OK;
  DALGpioSignalType   uGPIOCfg    = 0;
    
  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

  MDP_OSAL_DELAYUS(10);
  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_LOW_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

  MDP_OSAL_DELAYUS(10);
    
  uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(CDP_DISP_RESET_GPIO, 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_16MA, DAL_GPIO_HIGH_VALUE);
  Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
  
  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PeripheralPower()
** 
** DESCRIPTION:
**        Secondary power sequence for other PMIC modules such as IBB/LAB
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_PeripheralPower(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, bool32 bPowerUp)
{
  MDP_Status                    eStatus = MDP_STATUS_OK;

  if (TRUE == bPowerUp)
  {
    // ********** Brightness Power-up Sequence **********
    // Power up
    /************************************************************************/
    /* LCDB                                                                 */
    /************************************************************************/
    
    if (PM_ERR_FLAG__SUCCESS != pm_lcdb_set_module_rdy(PMIC_PMI_DEV_INDEX, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Error to config LCDB to ready\n");
    }
    if (PM_ERR_FLAG__SUCCESS != pm_lcdb_module_enable(PMIC_PMI_DEV_INDEX, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Error to enable LCDB module\n");
    }
    
    /************************************************************************/
    /*  WLED                                                                */
    /************************************************************************/

    //0xD84F             EN_CURRENT_SINK         0xE0       Enable all 3 strings
    if (PM_ERR_FLAG__SUCCESS != pm_wled_enable_current_sink(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Wled EnableCurrentSink failed\n");
    }

    if (PM_ERR_FLAG__SUCCESS != pm_wled_enable_modulator(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Wled EnableModulator failed\n");
    }

    if (PM_ERR_FLAG__SUCCESS != pm_wled_en_sync(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Wled EnableSync failed\n");
    }

    //0xD846             MODULE_EN      0x80       Enable the entire module
    if (PM_ERR_FLAG__SUCCESS != pm_wled_enable_module(PMIC_PMI_DEV_INDEX, 0, TRUE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Wled EnableWled failed\n");
    }
  }
  else
  {
    // ********** Brightness Power-down Sequence **********
    if (PM_ERR_FLAG__SUCCESS != pm_lcdb_module_enable(PMIC_PMI_DEV_INDEX, FALSE))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Error to disable LCDB\n");
    }

  }
  
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_BacklightLevel()
**
** DESCRIPTION:
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status Panel_CDP_BacklightLevel(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, BacklightConfigType *pBacklightConfig)
{
  MDP_Status                    eStatus = MDP_STATUS_OK;


  if (MDP_PANEL_BACKLIGHTTYPE_PMIC == pBacklightConfig->eBacklightType)
  {
    // Configure the power grid based on the module type
    switch (pBacklightConfig->uBacklightCntrl.eBacklightCtrl)
    {
    case MDP_PMIC_BACKLIGHT_CONTROLTYPE_WLED:
      {

        uint32 uWLEDValue = (0xFFF * pBacklightConfig->uLevel) / 100; // Calculate duty cycle based on 12 bit mode

        if (PM_ERR_FLAG__SUCCESS != pm_wled_set_led_duty_cycle(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary, uWLEDValue))
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Wled pm_wled_set_led_duty_cycle failed\n");
        }
      }
      break;
    default:
      break;
    }
  }
  else
  {
    // Nothing to do for other configurations
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DynamicDSIPanelDetection()
** 
** DESCRIPTION:
**  Detect DSI panels by doing a DSI read specific to each panels.
**  This function could be used as sample for OEM to detect DSI panels, 
**  it is not a complete implementation of all possible combinations of read
**  commands that could be needed for this detection.
**   
**  Return success only if a DSI panel was correctly detected and the information 
**  is updated in pPlatformParams->sPlatformPanel
*//* -------------------------------------------------------------------- */
static MDP_Status DynamicDSIPanelDetection(MDPPlatformParams *pPlatformParams, uint32 *puPanelID, uint32 uOverrideId)
{
  MDP_Status             eStatus       = MDP_STATUS_NOT_SUPPORTED;

  /* Placeholder */

  pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_TFT2P2827_E_cmd_xmldata;
  pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_TFT2P2827_E_cmd_xmldata);
  pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_CMD;

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: panel_ConfigGPIO()

** 
** DESCRIPTION:
**   Initialize LCD panel GPIOs and PMICs
**
*/ /* -------------------------------------------------------------------- */
MDP_Status MDPPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams)
{
  MDP_Status  eStatus  = MDP_STATUS_OK;
  uint32      uPanelID = 0;

  /* Static information, initial once during the first call */
  static bool32                 bInitFlag           = FALSE;
  static MDPPlatformInfo        sPlatformInfo;
  static Panel_PowerCtrlParams  sPanelPowerCtrl;

  if (FALSE == bInitFlag)
  {
    MDP_OSAL_MEMZERO(&sPlatformInfo,    sizeof(MDPPlatformInfo));
    MDP_OSAL_MEMZERO(&sPanelPowerCtrl,  sizeof(Panel_PowerCtrlParams));
    bInitFlag = TRUE;
    pm_driver_init();
  }

  // Read the platform ID once
  if (FALSE == sPlatformInfo.bPlatformDetected)
  {
    if (MDP_STATUS_OK == ReadPlatformIDAndChipID(&sPlatformInfo.sEFIPlatformType, &sPlatformInfo.sEFIChipSetId, &sPlatformInfo.sEFIChipSetFamily))
    {
      uint32 uTemp = 0;

      sPlatformInfo.bPlatformDetected = TRUE;

      // Read display config variables
      if (MDP_STATUS_OK == MDP_GetEnvironmentVariable(L"DISPLAYCONFIG", &uTemp, sizeof(uTemp)))
      {
        if (DISPLAY_FLAG_AMOLED & uTemp)
        {
          sPlatformInfo.uPowerCfgOverride = MDP_PMIC_MODULE_CONTROLTYPE_IBB_LAB_OLED;
        }
      }

      // Read the display panel ID override
      if (MDP_STATUS_OK == MDP_GetEnvironmentVariable(L"DISPLAYID", &uTemp, sizeof(uTemp)))
      {
        if (uTemp > 0)
        {
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayLib: Panel override enabled (ID:0x%x)\n", uTemp);
          sPlatformInfo.uPanelIdOverride = uTemp;
        }
      }
    }
  }

  switch (eConfig)
  {
  case MDPPLATFORM_CONFIG_SW_RENDERER:

    if ((EFI_PLATFORMINFO_TYPE_UNKNOWN == sPlatformInfo.sEFIPlatformType.platform) ||
        (EFI_PLATFORMINFO_TYPE_VIRTIO  == sPlatformInfo.sEFIPlatformType.platform) ||
        (EFI_PLATFORMINFO_TYPE_RUMI    == sPlatformInfo.sEFIPlatformType.platform) ||
        (TRUE == PcdGetBool(PcdDisplayForceSwRenderer)))
    {
      // Treat unknown platforms as a SW model only
      pPlatformParams->sPlatformInfo.bSWRender = TRUE;
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: SW renderer only\n");
    }
    else
    {
      pPlatformParams->sPlatformInfo.bSWRender = FALSE;
    }
    break;
  case MDPPLATFORM_CONFIG_GETPANELCONFIG:
    {
      pPlatformParams->sPlatformPanel.uDefaultVendor   = 0;
      pPlatformParams->sPlatformPanel.uDefaultRevision = 0;
      pPlatformParams->sPlatformPanel.uPanelId         = 0;

      // Retrieve panel configuration (could be dependent on the interface)
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:

        // Report the proper information depending on the display.
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          // Dynamic panel detection
          if (MDP_STATUS_OK != DynamicDSIPanelDetection(pPlatformParams, &uPanelID, sPlatformInfo.uPanelIdOverride))
          {
            if ((EFI_PLATFORMINFO_TYPE_CDP == sPlatformInfo.sEFIPlatformType.platform) && 
                (EFICHIPINFO_ID_SDM660 == sPlatformInfo.sEFIChipSetId) && 
                (0x03 == sPlatformInfo.sEFIPlatformType.subtype))
            {
              /* SDM660 New SKU with Truly 1080p with NT35695B - Video Mode */
              pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_NT35695b_FHD_video_xmldata;
              pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_NT35695b_FHD_video_xmldata);
              pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_1080P_VIDEO;
            }
            else
            {
              /* Default to Sharp 2k Panel */
              pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_TFT2P2827_E_cmd_xmldata;
              pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_TFT2P2827_E_cmd_xmldata);
              pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_CMD;
            }
          }
          break;
        default:            
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_TFT2P2827_E_cmd_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_TFT2P2827_E_cmd_xmldata);
          pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_CMD;
          break;
        }
        break;

      case MDP_DISPLAY_EXTERNAL:
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(dummy_xmldata);

          pPlatformParams->sHDMIPinConfig.uCecDataGpio    = HDMI_CEC_DATA_GPIO;
          pPlatformParams->sHDMIPinConfig.uDDDClkGpio     = HDMI_DDC_CLK_GPIO;
          pPlatformParams->sHDMIPinConfig.uDDCDataGpio    = HDMI_DDC_DATA_GPIO;  
          pPlatformParams->sHDMIPinConfig.uHPDGpio        = HDMI_HPD_GPIO;
          break;
      default:
        break;
      }
    }
    break;
  case MDPPLATFORM_CONFIG_POWERUP:
    {
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:            
          // Panel power configuration override (set through the environment variable)
          if (sPlatformInfo.uPowerCfgOverride)
          {
            sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = sPlatformInfo.uPowerCfgOverride;
          }
          else
          {
            // Populate the local power configuration (Force to IBB/LAB for LCD)
            //
            // Note: OLED users configure this as MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED
            //          An incorrect configuration can damage the panel.
            //
            sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = MDP_PMIC_MODULE_CONTROLTYPE_PM_LCD_WLED;   // LCD Power Configuration (IBB/LAB)
                                                                                                          // sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = MDP_PMIC_MODULE_CONTROLTYPE_IBB_LAB_OLED;   // OLED Power Configuration (IBB/LAB)
          }

          // CDP/MTP platforms use strings 2 & 3 while QRD uses 1 & 2
          // Since there is no dynamic platform detection in ramdump mode, we only enable string 2 so 
          // as to avoid damaging the hardware
          sPanelPowerCtrl.uWledStringsPrimary = PM_WLED_LED2;

          // Primary Power Sequence
          if (MDP_STATUS_OK != (eStatus = Panel_CDP_PowerUp(eDisplayId, &sPanelPowerCtrl)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Primary Power Up Sequence Failed (%d)\n", eStatus);
          }
          else if (MDP_STATUS_OK != (eStatus = Panel_CDP_PeripheralPower(eDisplayId, &sPanelPowerCtrl, TRUE)))  // Secondary Power Sequence
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Secondary Power Up Sequence Failed (%d)\n", eStatus);
          }
          break;

        default:
          break;
        }

        break;

      case MDP_DISPLAY_EXTERNAL:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          eStatus = HDMI_CDP_PowerUp(eDisplayId, &sPanelPowerCtrl);
          break;
        default:
          break;
        }
        break;

      default:
        break;

      }

    }
    break;

  case MDPPLATFORM_CONFIG_POWERDOWN:
    {
      // Handle power down
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          if (MDP_STATUS_OK != (eStatus = Panel_CDP_PowerDown(eDisplayId, &sPanelPowerCtrl)))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Primary Power Down Sequence Failed (%d)\n", eStatus);
          }
          else if (MDP_STATUS_OK != (eStatus = Panel_CDP_PeripheralPower(eDisplayId, &sPanelPowerCtrl, FALSE)))  // Secondary Power Sequence
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Secondary Power Down Sequence Failed (%d)\n", eStatus);
          }

          break;
        default:
          break;
        }

        break;
      case MDP_DISPLAY_EXTERNAL:
        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          eStatus = HDMI_CDP_PowerDown(eDisplayId, &sPanelPowerCtrl);
          break;
        default:
          break;
        }
        break;
      default:
        break;
      }
    }
    break;
  case MDPPLATFORM_CONFIG_SETBACKLIGHT:
    {
      // Handle backlight level
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          eStatus = Panel_CDP_BacklightLevel(eDisplayId, &sPanelPowerCtrl, &pPlatformParams->sBacklightConfig);
        default:
          break;
        }
        break;
      case MDP_DISPLAY_EXTERNAL:
        eStatus = MDP_STATUS_NOT_SUPPORTED;
        break;
      default:
        break;
      }
    }
    break;
  case MDPPLATFORM_CONFIG_GETPANELID:
    {
    }
    break;
  case MDPPLATFORM_CONFIG_GETPLATFORMINFO:
    {
      //
      // Return platform information
      //
      MDP_OSAL_MEMCPY(&pPlatformParams->sPlatformInfo, &sPlatformInfo, sizeof(MDPPlatformInfo));
    }
    break;
  case MDPPLATFORM_CONFIG_RESETPANEL:
    {
      // Handle power down
      switch (eDisplayId)
      {
      case MDP_DISPLAY_PRIMARY:

        // Config based on the platform
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_CDP:
          eStatus = Panel_CDP_Reset();
        default:
          break;
        }

        break;
      case MDP_DISPLAY_EXTERNAL:
        eStatus = MDP_STATUS_NOT_SUPPORTED;
        break;
      default:
        break;
      }
    }
    break;

  case MDPPLATFORM_CONFIG_SETGPIOSTATE:
    {
      eStatus = SetDefaultGPIOState(&pPlatformParams->sGPIOState);
    }
    break;
      
  default:
    eStatus = MDP_STATUS_BAD_PARAM;
    break;
  }
  
  return eStatus;
}



/*===========================================================================
Private Function Definitions
===========================================================================*/

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ReadPlatformIDAndChipID()
** 
** DESCRIPTION:
**
*/ /* -------------------------------------------------------------------- */
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChipSetFamily)
{
  MDP_Status                           eStatus                = MDP_STATUS_OK;

  /* As the current xbl version can't fully support platform detection for SDM660 RAM dump mode,
   * so change the platform ID to OEM to skip the power config in RAM dump mode for OLED panels.
   */
  pPlatformInfo->platform = EFI_PLATFORMINFO_TYPE_OEM;
  *pChipSetId             = EFICHIPINFO_ID_MSM8998;
  *pChipSetFamily         = EFICHIPINFO_FAMILY_MSM8998;

  return eStatus;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HDMI_CDP_Powerup()
** 
** DESCRIPTION:
**  
**
*//* -------------------------------------------------------------------- */
static MDP_Status HDMI_CDP_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                    eStatus            = MDP_STATUS_OK;

  HDMI_EnableTLMM_DDC_HPD();
  
  return eStatus;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: HDMI_CDP_PowerDown()
** 
** DESCRIPTION:
** 
**
*//* -------------------------------------------------------------------- */
static MDP_Status HDMI_CDP_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                    eStatus            = MDP_STATUS_OK;

  HDMI_DisableTLMM_DDC_HPD();

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HDMI_EnableTLMM_DDC_HPD()
*/
/*!
* \brief
*   The \b HDMI_EnableTLMM_DDC_HPD Initializes the GPIO configuration for the
*   DDC lines and enables the HPD GPIO configurations.
**
* \retval MDP_Status
*
****************************************************************************/
MDP_Status HDMI_EnableTLMM_DDC_HPD(void)
{
  MDP_Status                 eRetStatus = MDP_STATUS_OK;
  MDPPlatformParams          ePlatformParam;

  MDP_OSAL_MEMSET(&ePlatformParam, 0x0, sizeof(MDPPlatformParams));

  if (MDP_STATUS_OK != (eRetStatus = MDPPlatformConfigure(MDP_DISPLAY_EXTERNAL, MDPPLATFORM_CONFIG_GETPANELCONFIG, &ePlatformParam)))
  {
    // Do nothing
  }
  else
  {

    DALGpioSignalType   uGPIOCfg = 0;

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(ePlatformParam.sHDMIPinConfig.uHPDGpio,     1, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_16MA);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(ePlatformParam.sHDMIPinConfig.uDDDClkGpio,  1, DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_16MA);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(ePlatformParam.sHDMIPinConfig.uDDCDataGpio, 1, DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_16MA);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
  }

  return eRetStatus;
}


/****************************************************************************
*
** FUNCTION: HDMI_DisableTLMM_DDC()
*/
/*!
* \brief
*   The \b HDMI_DisableTLMM_DDC disable the GPIO configuration for the
*   DDC lines.
**
* \retval MDP_Status
*
****************************************************************************/
MDP_Status HDMI_DisableTLMM_DDC_HPD(void)
{
  MDP_Status                 eRetStatus = MDP_STATUS_OK;
  MDPPlatformParams          ePlatformParam;

  MDP_OSAL_MEMSET(&ePlatformParam, 0x0, sizeof(MDPPlatformParams));

  if (MDP_STATUS_OK != (eRetStatus = MDPPlatformConfigure(MDP_DISPLAY_EXTERNAL, MDPPLATFORM_CONFIG_GETPANELCONFIG, &ePlatformParam)))
  {
    // Do nothing
  }
  else
  {
    DALGpioSignalType   uGPIOCfg = 0;

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(ePlatformParam.sHDMIPinConfig.uHPDGpio,      1, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_16MA);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_DISABLE, &uGPIOCfg, 1);

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(ePlatformParam.sHDMIPinConfig.uDDDClkGpio,   1, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_16MA);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_DISABLE, &uGPIOCfg, 1);

    uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG(ePlatformParam.sHDMIPinConfig.uDDCDataGpio,  1, DAL_GPIO_INPUT, DAL_GPIO_PULL_DOWN, DAL_GPIO_16MA);
    Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_DISABLE, &uGPIOCfg, 1);
  }

  return eRetStatus;
}



/****************************************************************************
*
** FUNCTION: SetDefaultGPIOState()
*/
/*!
* \brief
*   The \b SetDefaultGPIOState function toggles a list of GPIO's based on the requested configuration
**
* \retval MDP_Status
*
****************************************************************************/
MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList)
{
  MDP_Status          eStatus = MDP_STATUS_OK;

  if ((NULL == pGPIOList) ||
      (NULL == pGPIOList->pGPIOList))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    // Handle each type of GPIO differently
    switch (pGPIOList->eGPIOType)
    {
    case MDPPLATFORM_GPIOTYPE_TLMM:
    {
      uint32              uCount;

      // Loop the list to configure all GPIOs.
      for (uCount = 0;uCount < pGPIOList->uListSize;uCount++)
      {
        // Only try to program GPIOs that are within range, TLMM Macro (EFI_GPIO_CFG) supports up to 0x3FF
        if (pGPIOList->pGPIOList[uCount] < 0x3FF)
        {

          DALGpioSignalType   uGPIOCfg = 0;
          uint32              uValue  = (pGPIOList->uState > 0) ? DAL_GPIO_HIGH_VALUE : DAL_GPIO_LOW_VALUE;

          uGPIOCfg = (DALGpioSignalType)DAL_GPIO_CFG_OUT(pGPIOList->pGPIOList[uCount], 0, DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA, uValue);
          Tlmm_ConfigGpioGroup(DAL_TLMM_GPIO_ENABLE, &uGPIOCfg, 1);
        }
      }
    }
    break;
    default:
      // Others (PMIC, PMI) not supported
      break;
    }
  }

  return eStatus;
}


#ifdef __cplusplus
}
#endif
