/*=============================================================================
 
  File: MDPPlatformLib.c
 
  MDP platform specific functions
  
  Copyright (c) 2011-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIPmicLpg.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicVreg.h>
#include <Protocol/EFIPmicWled.h>
#include <Protocol/EFIPmicLcdb.h>
#include "DDIChipInfo.h"
#include "MDPTypes.h"
#include "MDPPlatformLib.h"
#include "MDPSystem.h"
#include "OEMPlatformLib.h"
#include "DisplayABLInterface.h"
#include "npa.h"
#include "pmapp_npa.h"
#include "DDITlmm.h"
#include "HALDSILib.h"
#include <Protocol/EFIPmicOledb.h>
#include <Protocol/EFIPmicLab.h>
#include <Protocol/EFIPmicVersion.h>
//#include <Protocol/EFIPmicIbb.h>


/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */

#define PCD_PANEL_TYPE_OEM                1

#define DSI_READ_ADDRESS_SIZE             2
#define DSI_READ_READBACK_SIZE            8
#define DSI_WRITE_BACKLIGHT_SIZE          2

#define PLATFORM_PANEL_ID_MAX_COMMANDS    3       // maximum panel ID read commands

#define PANEL_LIST_MAX_COUNT              16      // maximum number of panels supported

// PMIC Device Indices
#define PMIC_DEV_INDEX                    0       // PMIC device (Vreg, LDO, ect)
#define PMIC_PMI_DEV_INDEX                1       // PMIC interface device (LCD / OLED)

/* SDM660 Main Panel CDP specific defines
*/
#define CDP_DISP_RESET_GPIO               53      //GPIO number for LCD0_RESET_N
#define CDP_DISP_TE_GPIO                  59      //GPIO number for TE

/* Helper macro for supported panels table entry PanelInfoType */
#define PANEL_CREATE_ENTRY(_name_,_id_,_dtlable_,_interface_,_xml_,_cfg_,_pll_, _top0_, _top1_, _top2_)     \
                                          {(_name_),                            \
                                           (_id_),                              \
                                           (_dtlable_),                         \
                                           (_interface_),                       \
                                           (int8*)(_xml_),                      \
                                           (NULL == (_xml_)?0:sizeof((_xml_))), \
                                           (_cfg_),                             \
                                           (_pll_),                             \
                                           {(_top0_), (_top1_), (_top2_)}}

#define PANEL_INFOLIST_LENGTH   (sizeof(gPanelList)/sizeof(PanelInfoType))

/* Macro to do round up of (x / y) to nearest integer */
#define DISP_DIV_ROUND_UP(x, y) (((x) + (y/2)) / (y))

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* Panel backlight DCS command
*/
typedef struct {
  uint8      command[DSI_WRITE_BACKLIGHT_SIZE];                                       // DCS command for backlight control
} PlatformPanelBacklightControl;

/* Panel command ID list for dynamic panel detection
*/

typedef struct {
  uint8      address[DSI_READ_ADDRESS_SIZE];                                          // DCS command for panel ID
  uint8      expectedReadback[DSI_READ_READBACK_SIZE];                                // expected readback
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
  MDPPlatformPanelType          eSelectedPanel;                                       // index of the selected panel
  uint32                        uFlags;                                               // flags to set clock config for now, can set other config in future
} PlatformDSIDetectParams;

/* Power configuration 
 */
typedef struct
{
  npa_client_handle             sNPAClient[MDP_DISPLAY_MAX];                          // NPA client handles for power control of panels.
  MDP_PmicModuleControlType     ePMICSecondaryPower[MDP_DISPLAY_MAX];                 // Configuration for PMIC based secondary power source
  uint32                        uWledStringsPrimary;                                  // Set of WLED strings needed for this platform
  uint32                        bOledPostInitDone;                                    // OLED post init is done
} Panel_PowerCtrlParams;

/* NPA Client info
*/
typedef struct
{
  char*                         cResourceName;
  char*                         cClientName;
}NPAClientName;


/* Panel support map type
*/
typedef struct
{
  MDPPlatformPanelType     ePanel;          /* Panel ID */  
  int8                    *pPanelXMLConfig; /* Matching XML configuration */
  uint32                   uConfigSize;     /* Size of XML configuration */
  uint32                   uOverrideFlags;  /* Panel config flags from DisplayOverideFlagType */
} PanelMappingType;


/* -----------------------------------------------------------------------
** Local functions
** ----------------------------------------------------------------------- */

/* Platform detection 
*/
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChiSetFamily);
static MDP_Status DynamicDSIPanelDetection(MDPPlatformParams *pPlatformParams, uint32 *puPanelID, uint32 uOverrideId);


/* SDM660 Main Panel CDP Functions
*/
static MDP_Status Panel_CDP_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
static MDP_Status Panel_CDP_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);
static MDP_Status Panel_CDP_Reset(void);

static MDP_Status Panel_CDP_BacklightLevel(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, BacklightConfigType *pBacklightConfig);
static MDP_Status Panel_CDP_PeripheralPower(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, bool32 bPowerUp);
static MDP_Status Panel_CDP_PmicOledPostInit(MDP_Display_IDType eDisplayId);


/* Main Panel CDP/MTP Functions
*/

/* General helper functions */
MDP_Status SetDefaultGPIOState(GpioStateType *pGPIOList);

/*===========================================================================
 Local Configuration Definitions
 ===========================================================================*/


/******************************************************************
 *                   Sharp 6.17" WQXGA                            *
 *                                                                *
 *                   1600x2560                                    *
 *                   Dual-DSI                                     *
 *                   Video mode                                   *
 ******************************************************************/
const static int8 Sharp_LS062R1SX01_DSI_xmldata[] = 
  "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
  "<PanelName>LS062R1SX01</PanelName>\n"
  " <PanelDescription>Sharp Dual DSI Panel (1600x2560 24bpp)</PanelDescription>\n"
  "<Group id='Active Timing'>\n"
  " <HorizontalActive units='Dot Clocks'>1600</HorizontalActive>\n" 
  " <HorizontalFrontPorch units='Dot Clocks'>76</HorizontalFrontPorch>\n"
  " <HorizontalBackPorch units='Dot Clocks'>32</HorizontalBackPorch>\n"
  " <HorizontalSyncPulse units='Dot Clocks'>16</HorizontalSyncPulse>\n"
  " <VerticalActive units='Dot Clocks'>2560</VerticalActive>\n"
  " <VerticalFrontPorch units='Lines'>4</VerticalFrontPorch>\n"
  " <VerticalBackPorch units='Lines'>2</VerticalBackPorch>\n"
  " <VerticalSyncPulse units='Lines'>2</VerticalSyncPulse>\n"
  "</Group>\n"
  "<Group id='Display Interface'>\n"
  " <InterfaceType units='QDI_DisplayConnectType'>8</InterfaceType>\n"
  " <InterfaceColorFormat units='QDI_PixelFormatType'>3</InterfaceColorFormat>\n"
  "</Group>\n"
  "<Group id='DSI Interface'>\n"
  " <DSIChannelId units='DSI_Channel_IDType'>1</DSIChannelId>\n"
  " <DSIVirtualId units='DSI_Display_VCType'>0</DSIVirtualId>\n"
  " <DSIColorFormat units='DSI_ColorFormatType'>36</DSIColorFormat>\n"
  " <DSITrafficMode units='DSI_TrafficModeType'>1</DSITrafficMode>\n"
  " <DSILanes units='integer'>4</DSILanes>\n"
  " <DSIHsaHseAfterVsVe units='Bool'>False</DSIHsaHseAfterVsVe>\n"
  " <DSILowPowerModeInHFP units='Bool'>False</DSILowPowerModeInHFP>\n"
  " <DSILowPowerModeInHBP units='Bool'>False</DSILowPowerModeInHBP>\n"
  " <DSILowPowerModeInHSA units='Bool'>False</DSILowPowerModeInHSA>\n"
  " <DSILowPowerModeInBLLPEOF units='Bool'>True</DSILowPowerModeInBLLPEOF>\n"
  " <DSILowPowerModeInBLLP units='Bool'>True</DSILowPowerModeInBLLP>\n"
  " <DSIRefreshRate units='integer Q16.16'>0x3C0000</DSIRefreshRate>\n"
  " <DSIInitMasterTime units='integer'>32</DSIInitMasterTime>\n"  
  " <DSIControllerMapping>\n"
  "  00 01\n"
  " </DSIControllerMapping>\n" 
  "</Group>\n"
  "<DSIInitsequence>\n"
  " 05 11 00\n"
  " FF 08 \n"
  " 05 29 00\n"
  "</DSIInitSequence>\n"
  "<DSITermSequence>\n"
  " 05 28 00\n"
  " FF 08 \n"
  " 05 10 00\n"
  "</DSITermSequence>\n"
  "<Group id='Backlight Configuration'>"
  " <BacklightType units='MDP_Panel_BacklightType'>1</BacklightType>\n"
  " <BacklightPmicControlType units='MDP_PmicBacklightControlType'>2</BacklightPmicControlType>\n"  
  "</Group>\n";

/******************************************************************
 *           Truly 5.5in 2k  TFT2P2827-E                          *
 *                                                                *
 *                   1440x2560                                    *
 *                   Dual-DSI                                     *
 *                   Video mode                                   *
 ******************************************************************/
const static int8 Truly_TFT2P2827_E_video_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>TFT2P2827-E</PanelName>"
"<PanelDescription>Truly Dual DSI Video Mode Panel (1440x2560 24bpp)</PanelDescription>"
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
" <InterfaceType units=\"QDI_DisplayConnectType\">8</InterfaceType>"
" <InterfaceColorFormat units=\"QDI_PixelFormatType\">3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <DSIChannelId units=\"DSI_Channel_IDType\">1</DSIChannelId>"
" <DSIVirtualId units=\"DSI_Display_VCType\">0</DSIVirtualId>"
" <DSIColorFormat units=\"DSI_ColorFormatType\">36</DSIColorFormat>"
" <DSITrafficMode units=\"DSI_TrafficModeType\">1</DSITrafficMode>"
" <DSILanes units=\"integer\">4</DSILanes>"
" <DSILowPowerModeInBLLPEOF units='Bool'>True</DSILowPowerModeInBLLPEOF>\n"
" <DSILowPowerModeInBLLP units='Bool'>True</DSILowPowerModeInBLLP>\n"
" <DSIRefreshRate units='integer Q16.16'>0x3C0000</DSIRefreshRate>\n"
" <DSIDynamicRefreshRates units='integer Q16.16'>0x3B8000 0x3BC000 0x3C0000 0x3C4000 0x3C8000</DSIDynamicRefreshRates>\n"
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
" 15 72 11\n"
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
" 15 BB 03\n"
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
 *           Truly 5.5in 2k  TFT2P2827-E                          *
 *                                                                *
 *                   1440x2560                                    *
 *                      DSC                                       *
 *                   Video mode                                   *
 ******************************************************************/
const static int8 Truly_TFT2P2827_E_video_dsc_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>TFT2P2827-E</PanelName>"
"<PanelDescription>Truly Dual DSI Video Mode Panel (1440x2560 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive units=\"Dot Clocks\">1440</HorizontalActive>"
" <HorizontalFrontPorch units=\"Dot Clocks\">100</HorizontalFrontPorch>"
" <HorizontalBackPorch units=\"Dot Clocks\">32</HorizontalBackPorch>"
" <HorizontalSyncPulse units=\"Dot Clocks\">16</HorizontalSyncPulse>"
" <VerticalActive units=\"Dot Clocks\">2560</VerticalActive>"
" <VerticalFrontPorch units=\"Lines\">10</VerticalFrontPorch>"
" <VerticalBackPorch units=\"Lines\">8</VerticalBackPorch>"
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
" <DSITrafficMode units=\"DSI_TrafficModeType\">1</DSITrafficMode>"
" <DSIDSCEnable>True</DSIDSCEnable>"
" <DSIDSCMajor>1</DSIDSCMajor>"
" <DSIDSCMinor>1</DSIDSCMinor>"
" <DSIDSCScr>0</DSIDSCScr>"
" <DSIDSCProfileID>7</DSIDSCProfileID>"
" <DSIDSCSliceWidth>720</DSIDSCSliceWidth>"
" <DSIDSCSliceHeight>16</DSIDSCSliceHeight>"
" <DSILanes units=\"integer\">4</DSILanes>"
" <DSILowPowerModeInBLLPEOF units='Bool'>True</DSILowPowerModeInBLLPEOF>\n"
" <DSILowPowerModeInBLLP units='Bool'>True</DSILowPowerModeInBLLP>\n"
" <DSIRefreshRate units='integer Q16.16'>0x3C0000</DSIRefreshRate>\n"
" <DSIDynamicRefreshRates units='integer Q16.16'>0x280000 0x3C0000 0x320000</DSIDynamicRefreshRates>\n"
" <DSIInitMasterTime units='integer'>32</DSIInitMasterTime>\n"  
" <DSIControllerMapping>\n"
"  01\n"
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
" 15 72 11\n"
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
" 39 C1 09 20 00 10 02 00 02 68 01 BB 00 0A 06 67 04 C5\n"
" 39 C2 10 F0\n"
" 15 C0 03\n"
" 39 3B 03 0A 0A\n"
" 15 35 00\n"
" 15 E5 01\n"
" 15 BB 03\n"
" 15 FB 01\n"
" 05 11 00\n"
" ff 64\n"
" 05 29 00\n"
"</DSIInitSequence>"
"<DSITermSequence>\n"
" 05 28 00\n"
" FF 78\n"
" 05 10 00\n"
" FF 78\n"
"</DSITermSequence>\n"
"<Group id='Backlight Configuration'>"
" <BacklightType units='MDP_Panel_BacklightType'>1</BacklightType>\n"
" <BacklightPmicControlType units='MDP_PmicBacklightControlType'>2</BacklightPmicControlType>\n"  
"</Group>\n";


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
" <DSITECheckEnable>True</DSITECheckEnable>"
" <DSITEUsingDedicatedTEPin>True</DSITEUsingDedicatedTEPin>"
" <DSITEvSyncStartPos>2560</DSITEvSyncStartPos>"
" <DSITEvSyncInitVal>2560</DSITEvSyncInitVal>"
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
" 15 72 11\n"
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
 *           Truly 5.5in 2k  TFT2P2827-E                          *
 *                                                                *
 *                   1440x2560                                    *
 *                      DSC                                       *
 *                   Cmd mode                                     *
 ******************************************************************/
const static int8 Truly_TFT2P2827_E_cmd_dsc_xmldata[] =
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
" <DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
" <DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
" <DSIClockHSForceRequest>1</DSIClockHSForceRequest>"
" <DSIDSCEnable>True</DSIDSCEnable>"
" <DSIDSCMajor>1</DSIDSCMajor>"
" <DSIDSCMinor>1</DSIDSCMinor>"
" <DSIDSCScr>0</DSIDSCScr>"
" <DSIDSCProfileID>7</DSIDSCProfileID>"
" <DSIDSCSliceWidth>720</DSIDSCSliceWidth>"
" <DSIDSCSliceHeight>16</DSIDSCSliceHeight>"
" <DSIRefreshRate units='integer Q16.16'>0x3C0000</DSIRefreshRate>\n"
" <DSIInitMasterTime units='integer'>32</DSIInitMasterTime>\n"  
" <DSIControllerMapping>\n"
" 01\n"
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
" 15 72 11\n"
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
" 39 C1 09 20 00 10 02 00 02 68 01 BB 00 0A 06 67 04 C5\n"
" 39 C2 10 F0\n"
" 15 C0 03\n"
" 39 3B 03 0A 0A\n"
" 15 35 00\n"
" 15 E5 01\n"
" 15 BB 10\n"
" 15 FB 01\n"
" 05 11 00\n"
" ff 64\n"
" 05 29 00\n"
"</DSIInitSequence>"
"<DSITermSequence>\n"
" 05 28 00\n"
" FF 78\n"
" 05 10 00\n"
" FF 78\n"
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


/******************************************************************
 *           Truly FHD (1080 x 1920) Command mode                 *
 *                                                                *
 ******************************************************************/
const static int8 Truly_NT35695b_FHD_cmd_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>TFT2P2827-E</PanelName>"
"<PanelDescription>Truly FHD DSI Command Mode Panel (1080x1920 24bpp)</PanelDescription>"
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
" <InterfaceType units=\"QDI_DisplayConnectType\">9</InterfaceType>"
" <InterfaceColorFormat units=\"QDI_PixelFormatType\">3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <DSIChannelId units=\"DSI_Channel_IDType\">2</DSIChannelId>"
" <DSIVirtualId units=\"DSI_Display_VCType\">0</DSIVirtualId>"
" <DSIColorFormat units=\"DSI_ColorFormatType\">36</DSIColorFormat>"
" <DSITrafficMode units=\"DSI_TrafficModeType\">2</DSITrafficMode>"
" <DSILanes units=\"integer\">4</DSILanes>"
" <DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
" <DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
" <DSITECheckEnable>True</DSITECheckEnable>"
" <DSITEUsingDedicatedTEPin>True</DSITEUsingDedicatedTEPin>"
" <DSITEvSyncStartPos>480</DSITEvSyncStartPos>"
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
" 15 bb 10\n"
" 15 35 02\n"
" 05 11 00\n"
" ff 78\n"
" fe 00 00 00\n"
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

/******************************************************************
 *           RM67195 5.7in 1080p AMOLED PANEL                     *
 *                                                                *
 *                   1080x1920                                    *
 *                   Single-DSI                                   *
 *                   Command mode                                 *
 ******************************************************************/
const static int8 RM67195_AMOLED_cmd_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>TDO-BD0568U40236</PanelName>"
"<PanelDescription>RM67195 Single DSI Command Mode Panel (1080x1920 24bpp)</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive>1080</HorizontalActive>"
" <HorizontalFrontPorch>120</HorizontalFrontPorch>"
" <HorizontalBackPorch>60</HorizontalBackPorch>"
" <HorizontalSyncPulse>12</HorizontalSyncPulse>"
" <VerticalActive>1920</VerticalActive>"
" <VerticalFrontPorch>8</VerticalFrontPorch>"
" <VerticalBackPorch>12</VerticalBackPorch>"
" <VerticalSyncPulse>4</VerticalSyncPulse>"
"</Group>"
"<Group id=\"Display Interface\">"
" <InterfaceType>9</InterfaceType>"
" <InterfaceColorFormat>3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <PanelOrientation>2</PanelOrientation>"
" <DSIChannelId>2</DSIChannelId>"
" <DSIVirtualId>0</DSIVirtualId>"
" <DSIColorFormat>36</DSIColorFormat>"
" <DSITrafficMode>1</DSITrafficMode>"
" <DSILanes>4</DSILanes>"
" <DSILP11AtInit>True</DSILP11AtInit>\n"
" <DSILowPowerModeInBLLPEOF units='Bool'>True</DSILowPowerModeInBLLPEOF>\n"
" <DSILowPowerModeInBLLP units='Bool'>True</DSILowPowerModeInBLLP>\n"
" <DSIRefreshRate>0x3C0000</DSIRefreshRate>"
" <DSIEnableAutoRefresh>True</DSIEnableAutoRefresh>"
" <DSIAutoRefreshFrameNumDiv>1</DSIAutoRefreshFrameNumDiv>"
" <DSIControllerMapping>\n"
"  00\n"
" </DSIControllerMapping>\n" 
"</Group>"
"<DSIInitSequence>"
" 15 FE 0D\n"
" 15 0B C0\n"
" 15 42 00\n"
" 15 18 08\n"
" 15 08 41\n"
" 15 46 02\n"
" 15 1E 04\n"
" 15 1E 00\n"
" FF 02\n"
" 15 FE 0A\n"
" 15 24 17\n"
" 15 04 07\n"
" 15 1A 0C\n"
" 15 0F 44\n"
" FF 02\n"
" 15 FE 0B\n"
" 15 28 40\n"
" 15 29 4F\n"
" FF 02\n"
" 15 FE 04\n"
" 15 0A D8\n"
" 15 0C E6\n"
" 15 4E 20\n"
" 15 4F 1B\n"
" 15 50 2F\n"
" 15 51 08\n"
" FF 02\n"
" 15 FE 09\n"
" 15 00 08\n"
" 15 01 08\n"
" 15 02 00\n"
" 15 03 00\n"
" 15 04 10\n"
" 15 05 00\n"
" 15 06 08\n"
" 15 07 08\n"
" 15 08 00\n"
" 15 12 24\n"
" 15 13 49\n"
" 15 14 92\n"
" 15 15 49\n"
" 15 16 92\n"
" 15 17 24\n"
" 15 18 24\n"
" 15 19 49\n"
" 15 1A 92\n"
" 15 1B 49\n"
" 15 1C 92\n"
" 15 1D 24\n"
" 15 1E 24\n"
" 15 1F 49\n"
" 15 20 92\n"
" 15 21 49\n"
" 15 22 92\n"
" 15 23 24\n"
" 15 9B 07\n"
" 15 9C a5\n"
" FF 02\n"
" 15 FE 00\n"
" 15 C2 08\n"
" 15 35 00\n"
" FF 02\n"
" 39 44 03 E8\n"
" FF 02\n"
" 15 51 80\n"
" FF 02\n"
" 05 11 00\n"
" FF 82\n"
" 05 29 00\n"
" FF 14\n"
"</DSIInitSequence>"
"<DSITermSequence>\n"
" 05 28 00\n"
" FF 14\n"
" 05 10 00\n"
" FF 82\n"
"</DSITermSequence>\n"
"<Group id='Backlight Configuration'>"
" <BacklightType>3</BacklightType>\n"
"</Group>\n";

 /******************************************************************
 *                Truly FHD HX8399                                 *
 *                                                                 *
 *                   1080x2160                                     *
 *                   Single-DSI                                    *
 *                   Video mode                                    *
 *******************************************************************/
const static int8 Truly_HX8399_FHD_video_xmldata[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<PanelName>HX8399</PanelName>"
"<PanelDescription>HX8399 video mode dsi truly panel</PanelDescription>"
"<Group id=\"Active Timing\">"
" <HorizontalActive>1080</HorizontalActive>"
" <HorizontalFrontPorch>42</HorizontalFrontPorch>"
" <HorizontalBackPorch>42</HorizontalBackPorch>"
" <HorizontalSyncPulse>10</HorizontalSyncPulse>"
" <HorizontalSyncSkew>0</HorizontalSyncSkew>"
" <HorizontalLeftBorder>0</HorizontalLeftBorder>"
" <HorizontalRightBorder>0</HorizontalRightBorder>"
" <VerticalActive>2160</VerticalActive>"
" <VerticalFrontPorch>10</VerticalFrontPorch>"
" <VerticalBackPorch>15</VerticalBackPorch>"
" <VerticalSyncPulse>3</VerticalSyncPulse>"
" <VerticalSyncSkew>0</VerticalSyncSkew>"
" <VerticalTopBorder>0</VerticalTopBorder>"
" <VerticalBottomBorder>0</VerticalBottomBorder>"
"</Group>"
"<Group id=\"Display Interface\">"
" <InterfaceType>8</InterfaceType>"
" <InterfaceColorFormat>3</InterfaceColorFormat>"
"</Group>"
"<Group id=\"DSI Interface\">"
" <DSIChannelId>1</DSIChannelId>"
" <DSIVirtualId>0</DSIVirtualId>"
" <DSIColorFormat>36</DSIColorFormat>"
" <DSITrafficMode>1</DSITrafficMode>"
" <DSILanes>4</DSILanes>"
" <DSILowPowerModeInBLLPEOF>True</DSILowPowerModeInBLLPEOF>"
" <DSILowPowerModeInBLLP>True</DSILowPowerModeInBLLP>"
" <DSIRefreshRate>0x3C0000</DSIRefreshRate>"
" <DSICmdSwapInterface>False</DSICmdSwapInterface>"
" <DSICmdUsingTrigger>False</DSICmdUsingTrigger>"
" <DSIControllerMapping>\n"
"  00\n"
" </DSIControllerMapping>\n"
"</Group>"
"<DSIInitSequence>"
" 39 B9 FF 83 99\n"
" 39 D2 88\n"
" 39 B1 02 04 72 92 01 32 AA 11 11 52 57\n"
" 39 B2 00 80 80 CC 05 07 5A 11 10 10 00 1E 70 03 D4\n"
" 39 B4 00 FF 59 59 01 AB 00 00 09 00 03 05 00 28 03 0B 0D 21 03 02 00 0C A3 80 59 59 02 AB 00 00 09 00 03 05 00 28 03 0B 0D 02 00 0C A3 01\n"
" 39 D3 00 0C 03 03 00 00 10 10 00 00 03 00 03 00 08 78 08 78 00 00 00 00 00 24 02 05 05 03 00 00 00 05 40\n"
" 39 D5 20 20 19 19 18 18 02 03 00 01 24 24 18 18 18 18 24 24 00 00 00 00 00 00 00 00 2F 2F 30 30 31 31\n"
" 39 D6 24 24 18 18 19 19 01 00 03 02 24 24 18 18 18 18 20 20 40 40 40 40 40 40 40 40 2F 2F 30 30 31 31\n"
" 39 BD 00\n"
" 39 D8 AA AA AA AA AA AA AA AA AA BA AA AA AA BA AA AA\n"
" 39 BD 01\n"
" 39 D8 00 00 00 00 00 00 00 00 82 EA AA AA 82 EA AA AA\n"
" 39 BD 02\n"
" 39 D8 FF FF C0 3F FF FF C0 3F\n"
" 39 BD 00\n"
" 39 E0 01 21 31 2D 66 6F 7B 75 7A 81 86 89 8C 90 95 97 9A A1 A2 AA 9E AD B0 5B 57 63 7A 01 21 31 2D 66 6F 7B 75 7A 81 86 89 8C 90 95 97 9A A1 A2 AA 9E AD B0 5B 57 63 7A\n"
" 39 B6 7E 7E\n"
" 39 CC 08\n"
" 05 11 00\n"
" FF 96\n"
" 05 29 00\n"
" FF 32\n"
"</DSIInitSequence>"
"<TLMMGPIODefaultLow>4C</TLMMGPIODefaultHigh>"
"<Group id='Backlight Configuration'>"
" <BacklightType>1</BacklightType>\n"
" <BacklightPmicControlType>2</BacklightPmicControlType>\n"
" <DisplayResetInfo>0 10 10000 10000 0</DisplayResetInfo>\n"
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
"        <HorizontalActive>640</HorizontalActive>"
"        <HorizontalFrontPorch>13</HorizontalFrontPorch>"
"        <HorizontalBackPorch>14</HorizontalBackPorch>"
"        <HorizontalSyncPulse>15</HorizontalSyncPulse>"
"        <HorizontalSyncSkew>0</HorizontalSyncSkew>"
"        <HorizontalLeftBorder>0</HorizontalLeftBorder>"
"        <HorizontalRightBorder>0</HorizontalRightBorder>"
"        <VerticalActive>480</VerticalActive>"
"        <VerticalFrontPorch>11</VerticalFrontPorch>"
"        <VerticalBackPorch>12</VerticalBackPorch>"
"        <VerticalSyncPulse>13</VerticalSyncPulse>"
"        <VerticalSyncSkew>0</VerticalSyncSkew>"
"        <VerticalTopBorder>0</VerticalTopBorder>"
"        <VerticalBottomBorder>0</VerticalBottomBorder>"
"        <InvertDataPolarity>False</InvertDataPolarity>"
"        <InvertVsyncPolairty>False</InvertVsyncPolairty>"
"        <InvertHsyncPolarity>False</InvertHsyncPolarity>"
"        <BorderColor>0x0</BorderColor>"   
"    </Group>"
"    <Group id=\"Display Interface\">"
"        <InterfaceType>8</InterfaceType>"
"        <InterfaceColorFormat>3</InterfaceColorFormat>"
"    </Group>"
"    <Group id=\"DSI Interface\">"
"        <DSIChannelId>1</DSIChannelId>"     
"        <DSIVirtualId>0</DSIVirtualId>"     
"        <DSIColorFormat>36</DSIColorFormat>"     
"        <DSITrafficMode>0</DSITrafficMode>"
"        <DSILanes>2</DSILanes>"
"        <DSIHsaHseAfterVsVe>False</DSIHsaHseAfterVsVe>"
"        <DSILowPowerModeInHFP>False</DSILowPowerModeInHFP>"
"        <DSILowPowerModeInHBP>False</DSILowPowerModeInHBP>"
"        <DSILowPowerModeInHSA>False</DSILowPowerModeInHSA>"
"        <DSILowPowerModeInBLLPEOF>False</DSILowPowerModeInBLLPEOF>"
"        <DSILowPowerModeInBLLP>False</DSILowPowerModeInBLLP>"
"        <DSIRefreshRate>0x3c0000</DSIRefreshRate>" 
"    </Group>"
"        <DisplayPrimaryFlags>0x2</DisplayPrimaryFlags>"
"    <DSIInitSequence>"
"    32 00 00\n"
"    </DSIInitSequence>";

/*
* List of supported panels. The ones with XML data have UEFI support and the rest are only supported by kernel.
*
*/
/*
DT info for panels
*/
const PanelInfoType gPanelList[] =
{
  /*Supported Panels*/  
  /*Truly 2k NT35597 video*/
  PANEL_CREATE_ENTRY("truly_wqxga_dualdsi_video",  MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_VIDEO,  "qcom,mdss_dsi_nt35597_wqxga_video_truly",      DISP_INTF_DSI, Truly_TFT2P2827_E_video_xmldata,       DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI,                                DISP_MODE_DUAL_DSI | DISP_MODE_PING_PONG_SPLIT,  DISP_MODE_DUAL_DSI),
  /*Truly 2k NT35597 cmd */
  PANEL_CREATE_ENTRY("truly_wqxga_dualdsi_cmd",    MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_CMD,    "qcom,mdss_dsi_nt35597_truly_wqxga_cmd",        DISP_INTF_DSI, Truly_TFT2P2827_E_cmd_xmldata,         DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI,                                DISP_MODE_DUAL_DSI | DISP_MODE_PING_PONG_SPLIT,  DISP_MODE_DUAL_DSI),
  /*Truly 2k NT35597 DSC video */
  PANEL_CREATE_ENTRY("truly_wqxga_dsc_video",      MDPPLATFORM_PANEL_TRULY_WQXGA_DSC_VIDEO,      "qcom,mdss_dsi_nt35597_dsc_video_truly",        DISP_INTF_DSI, Truly_TFT2P2827_E_video_dsc_xmldata,   DISP_TOPOLOGY_CONFIG_2,    PLL_OVERRIDE_PLL1, DISP_MODE_SINGLE_DSI | DISP_MODE_USE_DSI1,         DISP_MODE_SINGLE_DSI | DISP_MODE_USE_DSI1,       DISP_MODE_SINGLE_DSI | DISP_MODE_USE_DSI1 | DISP_MODE_DSC_MERGE),
  /*Truly 2k NT35597 DSC cmd */
  PANEL_CREATE_ENTRY("truly_wqxga_dsc_cmd",        MDPPLATFORM_PANEL_TRULY_WQXGA_DSC_CMD,        "qcom,mdss_dsi_nt35597_dsc_cmd_truly",          DISP_INTF_DSI, Truly_TFT2P2827_E_cmd_dsc_xmldata,     DISP_TOPOLOGY_CONFIG_2,    PLL_OVERRIDE_PLL1, DISP_MODE_SINGLE_DSI | DISP_MODE_USE_DSI1,         DISP_MODE_SINGLE_DSI | DISP_MODE_USE_DSI1,       DISP_MODE_SINGLE_DSI | DISP_MODE_USE_DSI1 | DISP_MODE_DSC_MERGE),    
  /*Truly 1080p video */
  PANEL_CREATE_ENTRY("nt35695b_truly_1080p_video", MDPPLATFORM_PANEL_TRULY_1080P_VIDEO,          "qcom,mdss_dsi_nt35695b_truly_fhd_video",       DISP_INTF_DSI, Truly_NT35695b_FHD_video_xmldata,      DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI,                              DISP_MODE_SINGLE_DSI,                            DISP_MODE_SINGLE_DSI),
  /*Truly 1080p cmd */
  PANEL_CREATE_ENTRY("nt35695b_truly_1080p_cmd",   MDPPLATFORM_PANEL_TRULY_1080P_CMD,            "qcom,mdss_dsi_nt35695b_truly_fhd_cmd",         DISP_INTF_DSI, Truly_NT35695b_FHD_cmd_xmldata,        DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI,                              DISP_MODE_SINGLE_DSI,                            DISP_MODE_SINGLE_DSI),
  /*Sharp 2k video */
  PANEL_CREATE_ENTRY("sharp_wqxga_dualdsi_video",  MDPPLATFORM_PANEL_NT35597_WQXGA_DUALDSI_VIDEO, "qcom,mdss_dsi_sharp_wqxga_video",             DISP_INTF_DSI, Sharp_LS062R1SX01_DSI_xmldata,         DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI,                                DISP_MODE_DUAL_DSI | DISP_MODE_PING_PONG_SPLIT,  DISP_MODE_NONE),
  /*RM67195 AMOLED FHD CMD */
  PANEL_CREATE_ENTRY("rm67195_amoled_fhd_cmd",     MDPPLATFORM_PANEL_RM67195_AMOLED_FHD_CMD,      "qcom,mdss_dsi_rm67195_amoled_fhd_cmd",        DISP_INTF_DSI, RM67195_AMOLED_cmd_xmldata,       	   DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI,                              DISP_MODE_SINGLE_DSI,                            DISP_MODE_SINGLE_DSI),

   /* Truly HX8399 fhd video */
  PANEL_CREATE_ENTRY("hx8399_truly_fhd_video",     MDPPLATFORM_PANEL_HX8399_TRULY_FHD_VIDEO,      "qcom,mdss_dsi_hx8399_truly_fhd_video",        DISP_INTF_DSI, Truly_HX8399_FHD_video_xmldata,        DISP_TOPOLOGY_CONFIG_0,    PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI,                              DISP_MODE_SINGLE_DSI,                            DISP_MODE_SINGLE_DSI),

  /*Simulation panels */
  /*sim video*/
  PANEL_CREATE_ENTRY("sim_video_panel",             MDPPLATFORM_PANEL_SIM_VIDEO_PANEL,             "qcom,mdss_dsi_sim_video",                DISP_INTF_DSI, NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  /*sim dualdsi video*/
  PANEL_CREATE_ENTRY("sim_dualdsi_video_panel",     MDPPLATFORM_PANEL_SIM_DUALDSI_VIDEO_PANEL,     "qcom,mdss_dsi_dual_sim_video",           DISP_INTF_DSI, NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER),
  /*sim CMD*/
  PANEL_CREATE_ENTRY("sim_cmd_panel",               MDPPLATFORM_PANEL_SIM_CMD_PANEL,               "qcom,mdss_dsi_sim_cmd",                  DISP_INTF_DSI, NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  /*sim dualdsi CMD*/
  PANEL_CREATE_ENTRY("sim_dualdsi_cmd_panel",       MDPPLATFORM_PANEL_SIM_DUALDSI_CMD_PANEL,       "qcom,mdss_dsi_dual_sim_cmd",             DISP_INTF_DSI, NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER),

  /*Skip mode only panels, SW render in UEFI*/
  /*Sharp 2k video*/
  PANEL_CREATE_ENTRY("nt35597_wqxga_dualdsi_video", MDPPLATFORM_PANEL_NT35597_WQHD_DUALDSI_VIDEO,   "qcom,mdss_dsi_nt35597_wqxga_video",     DISP_INTF_DSI, NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER),
  /*Sharp 2k cmd */
  PANEL_CREATE_ENTRY("nt35597_wqxga_dualdsi_cmd",   MDPPLATFORM_PANEL_NT35597_WQHD_DUALDSI_CMD,     "qcom,mdss_dsi_nt35597_wqxga_cmd",       DISP_INTF_DSI, NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER),
  /*Truly R63417 1080p video */
  PANEL_CREATE_ENTRY("r63417_truly_1080p_video",    MDPPLATFORM_PANEL_R63417_TRULY_1080P_VIDEO,     "qcom,mdss_dsi_truly_1080p_video",        DISP_INTF_DSI, NULL,                                 DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  /*Truly R63417 1080p cmd */
  PANEL_CREATE_ENTRY("r63417_truly_1080p_cmd",      MDPPLATFORM_PANEL_R63417_TRULY_1080P_CMD,       "qcom,mdss_dsi_truly_1080p_cmd",          DISP_INTF_DSI, NULL,                                 DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  /*Amoled 2k */
  PANEL_CREATE_ENTRY("amoled_2k",                   MDPPLATFORM_PANEL_AMOLED_2K,                    "qcom,mdss_dsi_amoled_2k",                DISP_INTF_DSI, NULL,                                 DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  /*Sharp split link video */
  PANEL_CREATE_ENTRY("sharp_split_link_video",      MDPPLATFORM_PANEL_SHARP_SPLIT_LINK_VIDEO, "qcom,mdss_dsi_sharp_split_link_wuxga_video",   DISP_INTF_DSI, NULL,                                 DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  
  PANEL_CREATE_ENTRY("lgd_incell_sw49106_fhd_video", MDPPLATFORM_PANEL_LGDINCELL_SW49106_FHD_VIDEO, "qcom,mdss_dsi_lgd_incell_sw49106_fhd_video", DISP_INTF_DSI, NULL,                                DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,  DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_SINGLE_DSI | DISP_MODE_SKIP_BOOTLOADER),
  /*End of Table, DO NOT ADD PANEL BELOW THIS*/
  PANEL_CREATE_ENTRY("",                            MDPPLATFORM_PANEL_NONE,                         "",                                      DISP_INTF_NONE,NULL,                                  DISP_TOPOLOGY_CONFIG_NONE, PLL_OVERRIDE_NONE, DISP_MODE_NONE,                                    DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER,     DISP_MODE_DUAL_DSI   | DISP_MODE_SKIP_BOOTLOADER),
};
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
**/
static MDP_Status PlatformClientInit(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status    Status = MDP_STATUS_OK;

  NPAClientName aNPAClientName[MDP_DISPLAY_MAX] =
  {
    {PMIC_NPA_GROUP_ID_DISP_PRIM,     "DisplayPrim"},  // Note: OLED panel should use PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED
    {PMIC_NPA_GROUP_ID_DISP_SEC,      "DisplaySec"},
    {PMIC_NPA_GROUP_ID_DISP_EXT_HDMI, "DisplayHDMI"},
  };

  if (MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED == pPowerParams->ePMICSecondaryPower[eDisplayId])
  {
    /* Use PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED for OLED Panel */
    aNPAClientName[MDP_DISPLAY_PRIMARY].cResourceName = PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED;
    aNPAClientName[MDP_DISPLAY_PRIMARY].cClientName   = "DisplayPrimAmoled";
  }

  if (eDisplayId >= MDP_DISPLAY_MAX )
  {
    DEBUG ((EFI_D_ERROR, "DisplayDxe: Unsupported Display ID for power init.\n"));
    Status =  MDP_STATUS_FAILED;
  }
  else if (NULL == pPowerParams->sNPAClient[eDisplayId])
  {
    pPowerParams->sNPAClient[eDisplayId] = npa_create_sync_client( aNPAClientName[eDisplayId].cResourceName, aNPAClientName[eDisplayId].cClientName, NPA_CLIENT_REQUIRED); 

    if (NULL == pPowerParams->sNPAClient[eDisplayId])
    {
      DEBUG ((EFI_D_ERROR, "DisplayDxe: Failed to retrieve NPA Display Handle for Display ID %x.\n", eDisplayId ));
      Status =  MDP_STATUS_FAILED;
    }
  }

  return Status;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PowerUp()
** 
** DESCRIPTION:
**        Panel power up sequence for CDP
**
**/
static MDP_Status Panel_CDP_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status        Status        = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL *TLMMProtocol = NULL;

  if (MDP_STATUS_OK != (Status =  PlatformClientInit(eDisplayId, pPowerParams)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to initialize handle for Primary display NPA node.\n"));
  }
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /*
    * Voting for Display NPA node to be ON
    */
    npa_issue_required_request(pPowerParams->sNPAClient[eDisplayId], PMIC_NPA_MODE_ID_GENERIC_ACTIVE);

    MDP_OSAL_DELAYMS(10);   /* delay 10ms to allow power grid to settle */
      
    /* Setup Reset Pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_2MA), TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for Reset_N line Failed!\n", CDP_DISP_RESET_GPIO));
    }

    /* Set Reset_N line HIGH */
    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), GPIO_HIGH_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line HIGH failed!\n"));
    }
    MDP_OSAL_DELAYUS(10);

    /* Pull Reset_N Low */
    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), GPIO_LOW_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Pull Reset_N Low Failed!\n"));
    }

    // Wait 10us, Reset_N(RESX) Need to be at least 10us to really trigger the (as per the panel spec)
    MDP_OSAL_DELAYUS(10);

    /* Set Reset_N line HIGH */
    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), GPIO_HIGH_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line HIGH failed!\n"));
    }

    MDP_OSAL_DELAYMS(10);   /* delay 10ms for panel to reset (from panel spec) */

    /* Display TE pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio(EFI_GPIO_CFG(CDP_DISP_TE_GPIO, 1, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA), TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for TE line failed %d\n", CDP_DISP_TE_GPIO));
    }
  }

  return Status;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PowerDown()
** 
** DESCRIPTION:
**        Panel power down sequence for CDP
**
**/
static MDP_Status Panel_CDP_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                    Status           = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL            *TLMMProtocol     = NULL;

  if (NULL == pPowerParams->sNPAClient[eDisplayId])
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: NULL Handle for Primary display NPA node.\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /* 
     * GPIOs & VRegs
     */
    /* Display RESET_N pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_16MA), TLMM_GPIO_DISABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Failed to disable GPIO %d for Reset_N line\n", CDP_DISP_RESET_GPIO));
    }

    /* Display TE pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio(EFI_GPIO_CFG(CDP_DISP_TE_GPIO, 1, GPIO_INPUT, GPIO_PULL_DOWN, GPIO_2MA), TLMM_GPIO_DISABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Failed to disable GPIO %d for TE pin\n", CDP_DISP_TE_GPIO));
    }

    /*
    * Voltage Regulators
    */
    npa_complete_request(pPowerParams->sNPAClient[eDisplayId]);           //Complete the request to power rails
  }

  return Status;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_Reset()
** 
** DESCRIPTION:
**        Panel reset sequence for CDP
**
**/
MDP_Status Panel_CDP_Reset(void)
{
  MDP_Status                    Status           = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL            *TLMMProtocol     = NULL;

  if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /* 
     * Toggle Reset
     */

    /* Enable Display Reset pin*/
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_16MA), TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for Reset_N line Failed!\n", CDP_DISP_RESET_GPIO));
    }

    /* Set Reset_N line HIGH */
    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), GPIO_HIGH_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line HIGH failed!\n"));
    }
    MDP_OSAL_DELAYUS(10);

    /* Pull Reset_N Low */
    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), GPIO_LOW_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Pull Reset_N Low Failed!\n"));
    }

    // Wait 10us, Reset_N(RESX) Need to be at least 10us to really trigger the (as per the panel spec)
    MDP_OSAL_DELAYUS(10);

    /* Set Reset_N line HIGH */
    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(CDP_DISP_RESET_GPIO, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), GPIO_HIGH_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line HIGH failed!\n"));
    }

    // 10ms to allow power grid to settle and allow panel to initialize after the reset
    MDP_OSAL_DELAYMS(10);
  }

  return Status;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PmicOledPostInit()
** 
** DESCRIPTION:
**        Any Oledb initialization needed after panel init sequence is sent & OLEDB is enabled
**
**/
static MDP_Status Panel_CDP_PmicOledPostInit(MDP_Display_IDType eDisplayId)
{ 
  MDP_Status                    Status           = MDP_STATUS_OK;
  EFI_QCOM_PMIC_OLEDB_PROTOCOL *PmicOledProtocol = NULL;
  EFI_QCOM_PMIC_LAB_PROTOCOL   *PmicLABProtocol  = NULL; 
        
  if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicOledbProtocolGuid, NULL, (VOID **)&PmicOledProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate OLED Protocol Failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicLabProtocolGuid, NULL, (VOID **)&PmicLABProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate PMIC LAB Protocol Failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else 
  {
    EFI_PM_LAB_STATUS_TYPE   sLabStatus;
    uint32                   uI;
     
    // LAB config
    
    MDP_OSAL_MEMZERO((void *) &sLabStatus, sizeof(EFI_PM_LAB_STATUS_TYPE));

    /* Check Lab Status in a Loop as the SWIRE signal generation time is not consistent
	   after sending panel init commands */
    for (uI = 0; uI < 30; ++uI)
    {
      if (EFI_SUCCESS != PmicLABProtocol->GetStatus(PMIC_PMI_DEV_INDEX, &sLabStatus))
      {
        DEBUG((EFI_D_ERROR, "DisplayDxe: Error getting LAB status\n"));
        break;
      }
      else if (sLabStatus.LabVregOk)
      {
        break;
      }

      MDP_OSAL_DELAYMS(5);
    }

    if (!sLabStatus.LabVregOk)
    {    
      DEBUG((EFI_D_ERROR, "DisplayDxe: LAB_VREG_OK is not TRUE - Disabling oled module\n"));  

      /* LAB VREG is not ok - Disable modules to avoid short circuit or other issues */
      
      if (EFI_SUCCESS != PmicLABProtocol->ModuleRdy(PMIC_PMI_DEV_INDEX, FALSE))
      {
        DEBUG((EFI_D_WARN, "DisplayDxe: Error disabling LAB \n"));
      } 
      
      MDP_OSAL_DELAYUS(100);
  
      if (EFI_SUCCESS != PmicOledProtocol->OledbSetModuleRdy(PMIC_PMI_DEV_INDEX, FALSE))
      {
        DEBUG((EFI_D_WARN, "DisplayDxe: Error disabling OLEDB\n"));
      }      
    }
    else
    {  
      // OLEDB config
  
      /* Do not listen to SWIRE for pulldown feature */
      if (EFI_SUCCESS != PmicOledProtocol->OledbSwireCtl(PMIC_PMI_DEV_INDEX, EFI_PM_OLEDB_SWIRE_CONTROL__PD_EN, FALSE))
      {
        DEBUG((EFI_D_ERROR, "DisplayDxe: Error configuring Oledb Swire Ctrl \n"));
      }
  
      /* Enable Discharge resistor */
      if (EFI_SUCCESS != PmicOledProtocol->OledbPdCtrl(PMIC_PMI_DEV_INDEX, TRUE))
      {
        DEBUG((EFI_D_ERROR, "DisplayDxe: Error to enable OLEDB\n"));
      } 
    }
  }

  return Status;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_PeripheralPower()
** 
** DESCRIPTION:
**        Secondary power sequence for other PMIC modules such as PM WLED / OLED
**
**/
static MDP_Status Panel_CDP_PeripheralPower(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, bool32 bPowerUp)
{
  MDP_Status                      Status              = MDP_STATUS_OK;
  
  switch (pPowerParams->ePMICSecondaryPower[eDisplayId])
  {
    case MDP_PMIC_MODULE_CONTROLTYPE_PM_LCD_WLED:
      {
        // TODO : Add PMIC support check (different PMIC devices are needed for LCD vs. OLED)
        
        EFI_QCOM_PMIC_WLED_PROTOCOL  *PmicWledProtocol = NULL;
        EFI_QCOM_PMIC_LCDB_PROTOCOL  *PmicLcdbProtocol = NULL;    
    
        if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicWledProtocolGuid, NULL, (VOID **)&PmicWledProtocol))
        {
          DEBUG((EFI_D_ERROR, "DisplayDxe: Locate WLED Protocol Failed!\n"));
          Status = MDP_STATUS_NO_RESOURCES;
        }
        else if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicLcdbProtocolGuid, NULL, (VOID **)&PmicLcdbProtocol))
        {
          DEBUG((EFI_D_ERROR, "DisplayDxe: Locate PMIC LCDB Protocol Failed!\n"));
          Status = MDP_STATUS_NO_RESOURCES;
        }
        else if (TRUE == bPowerUp)
        {
          // Power up
    
          /************************************************************************/
          /* Turn On + and - Bias for LCD                                         */
          /************************************************************************/
          //Enable LCDB module
          if (EFI_SUCCESS != PmicLcdbProtocol->LcdbModuleEnable(PMIC_PMI_DEV_INDEX, TRUE))
          {
            DEBUG((EFI_D_ERROR, "DisplayDxe: Error to config LCDB to LCD mode\n"));
          }
    
          /************************************************************************
           *  Enable secondary power source
           ************************************************************************/
    
          //0xD84F             EN_CURRENT_SINK         0xE0       Enable all 3 strings
          if (EFI_SUCCESS != PmicWledProtocol->EnableCurrentSink(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol EnableCurrentSink failed\n"));
          }
    
          if (EFI_SUCCESS != PmicWledProtocol->EnableModulator(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary, TRUE))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol EnableModulator failed\n"));
          }
    
          if (EFI_SUCCESS != PmicWledProtocol->EnableSync(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary, TRUE))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol EnableSync failed\n"));
          }
    
          //0xD846             MODULE_EN      0x80       Enable the entire module
          if (EFI_SUCCESS != PmicWledProtocol->EnableWled(PMIC_PMI_DEV_INDEX, 0, TRUE))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol EnableWled failed\n"));
          }
        }
        else
        {
          // Power down
          if (EFI_SUCCESS != PmicLcdbProtocol->LcdbModuleEnable(PMIC_PMI_DEV_INDEX, FALSE))
          {
            DEBUG((EFI_D_ERROR, "DisplayDxe: Error to config LCDB to LCD mode\n"));
          }
  
          if (EFI_SUCCESS != PmicWledProtocol->EnableWled(PMIC_PMI_DEV_INDEX, 0, FALSE))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol EnableWled failed\n"));
          }
        }
      }
      break;

    case MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED:
      {
        if (FALSE == bPowerUp)
        {
          // Power down case - execute PBS sequence
          
          EFI_QCOM_PMIC_OLEDB_PROTOCOL *PmicOledProtocol = NULL;
          
          if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicOledbProtocolGuid, NULL, (VOID **)&PmicOledProtocol))
          {
            DEBUG((EFI_D_ERROR, "DisplayDxe: Locate OLED Protocol Failed!\n"));
            Status = MDP_STATUS_NO_RESOURCES;
          }           
          else if (EFI_SUCCESS != PmicOledProtocol->OledbDispOffPbsTrigger(PMIC_PMI_DEV_INDEX))
          {
            DEBUG((EFI_D_ERROR, "DisplayDxe: Error triggering PBS sequence\n"));
          }
        }
        
        // For Power up, All OLED config will be triggered based on hardware pin signal
        // No configuration is needed        
      }
      break;

    default:
      break;
  }
  
  return Status;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CDP_BacklightLevel()
**
** DESCRIPTION:
**
**/
static MDP_Status Panel_CDP_BacklightLevel(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams, BacklightConfigType *pBacklightConfig)
{
  MDP_Status                    Status = MDP_STATUS_OK;

  if (MDP_PANEL_BACKLIGHTTYPE_PMIC == pBacklightConfig->eBacklightType)
  {
    // Configure the power grid based on the module type
    switch (pBacklightConfig->uBacklightCntrl.eBacklightCtrl)
    {
    case MDP_PMIC_BACKLIGHT_CONTROLTYPE_WLED:
      {
        EFI_QCOM_PMIC_WLED_PROTOCOL  *PmicWledProtocol = NULL;

        if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicWledProtocolGuid, NULL, (VOID **)&PmicWledProtocol))
        {
          DEBUG((EFI_D_ERROR, "DisplayDxe: Locate WLED Protocol Failed!\n"));
          Status = MDP_STATUS_NO_RESOURCES;
        }
        else
        {
          uint32 uWLEDValue = (0xFFF * pBacklightConfig->uLevel) / 100; // Calculate duty cycle based on 12 bit mode

          if (EFI_SUCCESS != PmicWledProtocol->SetLedDutyCycle(PMIC_PMI_DEV_INDEX, pPowerParams->uWledStringsPrimary, uWLEDValue))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol SetLedDutyCycle failed\n"));
          }
        }
      }
      break;
    default:
      break;
    }
  }
  else if (MDP_PANEL_BACKLIGHTTYPE_DSI == pBacklightConfig->eBacklightType)
  {
    PlatformPanelBacklightControl panelBacklightControl = {
      {0x51, 0x80}, // Using standard MIPI DCS commands to control brightness
    };

    // Calculate brightness based on 8 bit mode
    panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(0xFF * pBacklightConfig->uLevel, 100);

    Status = DSIDriver_Write(0x15,
                 panelBacklightControl.command,
                 sizeof(panelBacklightControl.command));
    if (MDP_STATUS_OK != Status)
    {
      DEBUG((EFI_D_ERROR, "Backlight brightness DCS command send failed\n"));
    }
  }
  else
  {
    // Nothing to do for other configurations
  }

  return Status;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: Panel_CheckOverride()
** 
** DESCRIPTION:
**  Check if the panel was overridden by ABL (apps boot loader) and if so check 
**  if the overridden panel is supported by this platform.
**
**  This function has 1 of 3 outcomes
**  1. panel is supported by both bootloader & kernel 
**     - Set matching xmlconfig
**  2. panel is only supported in kernel 
**     - Return dummyconfig, since sw rendering was already selected during initialization in this scenario
**  3. panel override is not set or the panel is not supported by bootloader & kernel
**     - Return FALSE to trigger panel detection
**/
static bool32 Panel_CheckOverride(MDP_Display_IDType eDisplayId, MDPPlatformParams *pPlatformParams)
{
  Display_ABLParamsType* pDisplayOverride = Display_ABL_GetParams();
  bool32                 bRet             = FALSE;

  if ((NULL != pDisplayOverride)                           && 
      (NULL != pDisplayOverride->sPrimary.psDTInfo)        &&
      (MDPPLATFORM_PANEL_NONE < pDisplayOverride->sPrimary.psDTInfo->ePanel))
  {
    // Lookup panel
    int32 i = PANEL_INFOLIST_LENGTH - 1;
    
    while (0 <= i)
    {
      if (pDisplayOverride->sPrimary.psDTInfo->ePanel == gPanelList[i].ePanel)
      {
        // Match found
        bRet = TRUE;

        /* Save panel id - this is used to send panel specific config to the kernel */
        pPlatformParams->sPlatformPanel.eSelectedPanel    = gPanelList[i].ePanel;

        if (pDisplayOverride->uFlags & DISP_MODE_SKIP_BOOTLOADER)
        {
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(dummy_xmldata);
          pPlatformParams->sPlatformInfo.bSWRender        = TRUE;
          
          DEBUG((EFI_D_ERROR, "DisplayDxe: Panel override <%a> in skip mode\n", pDisplayOverride->sPrimary.shortName));
        }
        else if (NULL != gPanelList[i].pPanelXMLConfig)
        {
          // panel is supported in boot loader
          pPlatformParams->sPlatformPanel.pPanelXMLConfig  = gPanelList[i].pPanelXMLConfig;
          pPlatformParams->sPlatformPanel.uConfigSize      = gPanelList[i].uConfigSize;

          DEBUG((EFI_D_ERROR, "DisplayDxe: Panel override <%a>\n", pDisplayOverride->sPrimary.shortName));
        }
        else
        {
          // panel is supported at kernel but not supported in bootloader
          pPlatformParams->sPlatformPanel.pPanelXMLConfig  = (int8 *)dummy_xmldata;
          pPlatformParams->sPlatformPanel.uConfigSize      = sizeof(dummy_xmldata);

          DEBUG((EFI_D_ERROR, "DisplayDxe: overridden panel <%a> is not supported\n", pDisplayOverride->sPrimary.shortName));
        }
        break;
      }
      i--;
    }
  }
  
  return bRet;
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
**/
static MDP_Status DynamicDSIPanelDetection(MDPPlatformParams *pPlatformParams, uint32 *puPanelID, uint32 uOverrideId)
{
  MDP_Status             Status                = MDP_STATUS_NOT_SUPPORTED;
  bool32                 bDumpPanelId          = FALSE;
  
  // Table to be filled once list of all panels is known (post bring-up)
  PlatformDSIDetectParams panelDetectionList[] = {

  };
  uint32                 uNumPanels            = sizeof(panelDetectionList)/sizeof(PlatformDSIDetectParams);

  if (0 == uNumPanels)
  {
    // Skip dynamic detection as there are no panels in the list
  }
  // If override is used, search for the panel that matches the override
  else if (uOverrideId)
  {
    uint32      uPanelIndex;
    
    for (uPanelIndex = 0; uPanelIndex < uNumPanels; uPanelIndex++)
    {
        uint32 uPanelId = (panelDetectionList[uPanelIndex].panelIdCommands[0].expectedReadback[0] << 16) |
                          (panelDetectionList[uPanelIndex].panelIdCommands[1].expectedReadback[0] << 8)  |
                          (panelDetectionList[uPanelIndex].panelIdCommands[2].expectedReadback[0]);

        if (uPanelId == uOverrideId)
        {
          // store matched panel configuration xml data
          pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*) panelDetectionList[uPanelIndex].psPanelCfg;
          pPlatformParams->sPlatformPanel.uConfigSize     = panelDetectionList[uPanelIndex].uPanelCfgSize;
          pPlatformParams->sPlatformPanel.eSelectedPanel  = panelDetectionList[uPanelIndex].eSelectedPanel;
        
          *puPanelID = uPanelId;
          Status     = MDP_STATUS_OK;
          break;
        }
    }  

    if (MDP_STATUS_OK != Status)
    {
      DEBUG((EFI_D_ERROR, "Display: Panel override failed to find a matching panel ID.\n"));      
    }
    
  }
  else if (MDP_STATUS_OK == DSIDriver_MinimalInit())          // do minimal DSI init
  {
    uint8       panelID[PLATFORM_PANEL_ID_MAX_COMMANDS];
    uint32      uPanelIndex;
    bool32      bMatch         = FALSE;
    uint32      uPrevClkConfig = 0; 

    // go through all possible panels
    for (uPanelIndex = 0; uPanelIndex < uNumPanels; uPanelIndex++)
    {
      uint8     readback[DSI_READ_READBACK_SIZE];
      uint32    readSize                          = sizeof(readback);
      int       iCommandIndex                     = 0;
      uint32    uClkConfig                        = (MDPPLATFORM_PANEL_DETECT_FLAG_CLOCK_FORCEHS & 
                                                     panelDetectionList[uPanelIndex].uFlags);
    
      // Check if there is any change in the clock config and set it accordingly
      if (uPrevClkConfig != uClkConfig)
      {
        if (MDP_STATUS_OK != DSIDriver_ConfigClockLane(uClkConfig))
        {
          DEBUG((EFI_D_ERROR, "Display: DSIDriver_ConfigClockLane failed\n"));
        }
        
        uPrevClkConfig = uClkConfig;
      }

      // Reprogram the DSI lane swap based on remap order
      if (MDP_STATUS_OK != DSIDriver_RemapLane(panelDetectionList[uPanelIndex].uLaneRemapOrder))
      {
        DEBUG((EFI_D_WARN, "Display: DSIDriver_RemapLane failed\n"));
      }

      // Allow debug option to scan panel registers (used to help generate a uniquie panel ID for detection)
      if (TRUE == bDumpPanelId)
      {
        DsiPanelDumpRegisters();
        // Dump just once
        bDumpPanelId = FALSE;
      }

      // clear the panel ID
      MDP_OSAL_MEMZERO(panelID, PLATFORM_PANEL_ID_MAX_COMMANDS);

      // for each possible panel ID read
      for(iCommandIndex = 0; iCommandIndex<PLATFORM_PANEL_ID_MAX_COMMANDS; iCommandIndex++)
      {
        uint32         uRetryCount = 0;

        // if read command is 0, then stop reading panel ID
        if ((0 == panelDetectionList[uPanelIndex].panelIdCommands[iCommandIndex].address[0]) &&
            (0 == panelDetectionList[uPanelIndex].panelIdCommands[iCommandIndex].address[1]) )
        {
          break;
        }
        // DSI read
        bMatch = FALSE;

        uRetryCount = 0;
        do
        {
          // clear the readback buffer
          MDP_OSAL_MEMZERO(&readback[0], readSize);
          readSize = sizeof(readback);
          Status = DSIDriver_Read(panelDetectionList[uPanelIndex].uCmdType, 
                                  panelDetectionList[uPanelIndex].panelIdCommands[iCommandIndex].address, 
                                  sizeof(panelDetectionList[uPanelIndex].panelIdCommands[iCommandIndex].address), 
                                  readback, 
                                  &readSize);
          uRetryCount++;
        } while((uRetryCount < panelDetectionList[uPanelIndex].uTotalRetry) && 
                ((MDP_STATUS_OK != Status)                                  || 
                 (0 == readSize)));

        if ((uRetryCount <= panelDetectionList[uPanelIndex].uTotalRetry) &&
            (0 != readSize))
        {
          // Read was successful, now check the data is what we expect
          if (0 == CompareMem(readback, panelDetectionList[uPanelIndex].panelIdCommands[iCommandIndex].expectedReadback, readSize))
          {
            panelID[iCommandIndex] = readback[0];    // store the first byte of readback as panel ID
            bMatch                 = TRUE;                       // mark one panel ID matched
          }
        }

        // if any panel ID is not matched, then go to detect next panel in the list
        if(FALSE == bMatch)
        {
          break;
        }
      }

      // if all panel IDs are matched for a specific panel, store settings and stop
      if(TRUE == bMatch)
      {
        // store matched panel configuration xml data
        pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8*) panelDetectionList[uPanelIndex].psPanelCfg;
        pPlatformParams->sPlatformPanel.uConfigSize     = panelDetectionList[uPanelIndex].uPanelCfgSize;
        pPlatformParams->sPlatformPanel.eSelectedPanel  = panelDetectionList[uPanelIndex].eSelectedPanel;

        // return the final combined panel ID
        *puPanelID = (panelID[0]<<16) | (panelID[1]<<8) | (panelID[2]);
        Status     = MDP_STATUS_OK;
        DEBUG((EFI_D_INFO, "Detected panel id:%08x\n", *puPanelID));
        break;
      }
      else
      {
        Status = MDP_STATUS_FAILED;
      }
    }

    // Close the DSI context opened in DSIDriver_MinimalInit()
    DSIDriver_Close();
  }

  return Status;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: PlatformConfigRemap()
** 
** DESCRIPTION:
**  Remapping of the platform configuration enumeration based on platform properties
**
**
**/
static MDPPlatformConfigType PlatformConfigRemap(MDPPlatformInfo *pPlatformConfig, MDPPlatformConfigType eConfig)
{
  MDPPlatformConfigType eRemappedConfig;

  // In SW render mode bypass all configuration that manipulate the hardware
  if ((NULL !=  pPlatformConfig) && 
      (TRUE == pPlatformConfig->bSWRender))
  {
    switch (eConfig)
    {
      case MDPPLATFORM_CONFIG_POWERUP:
      case MDPPLATFORM_CONFIG_POWERDOWN:
      case MDPPLATFORM_CONFIG_SETBACKLIGHT:
      case MDPPLATFORM_CONFIG_RESETPANEL:
      case MDPPLATFORM_CONFIG_SETGPIOSTATE:
        
        // In SW render mode don't execute these hardware configurations
        eRemappedConfig = MDPPLATFORM_CONFIG_BYPASS;
        
        break;
     default:
      
        // Default mapping (output = input)
        eRemappedConfig = eConfig;
        
        break;
   }
 }
 else
 {
    // Default mapping (output = input)
    eRemappedConfig = eConfig;
 }

 return eRemappedConfig;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: panel_ConfigGPIO()
** 
** DESCRIPTION:
**   Initialize LCD panel GPIOs and PMICs
**
**/
MDP_Status MDPPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams)
{
  MDP_Status  eStatus               = MDP_STATUS_OK;
  uint32      uPanelID              = 0;
  uint32      uPlatformSubtype      = 0;
  uint32      uHardwareVersionMajor = 0;

  /* Static information, initial once during the first call */
  static bool32                 bInitFlag           = FALSE;
  static MDPPlatformInfo        sPlatformInfo;
  static Panel_PowerCtrlParams  sPanelPowerCtrl;

  if (FALSE == bInitFlag)
  {
    MDP_OSAL_MEMZERO(&sPlatformInfo,    sizeof(MDPPlatformInfo));
    MDP_OSAL_MEMZERO(&sPanelPowerCtrl,  sizeof(Panel_PowerCtrlParams));
    bInitFlag = TRUE;
  }

  // If PCD is configured for OEM then defer all calls to OEM function
  if (PCD_PANEL_TYPE_OEM == PcdGet32(PcdPanelType))
  {
    eStatus = OEMPlatformConfigure(eDisplayId, eConfig, pPlatformParams);
  }
  else
  {
    MDPPlatformConfigType ePlatformConfig = PlatformConfigRemap(&sPlatformInfo, eConfig);
      
    // Read the platform ID once
    if (FALSE == sPlatformInfo.bPlatformDetected)
    {
      if (MDP_STATUS_OK == ReadPlatformIDAndChipID(&sPlatformInfo.sEFIPlatformType, &sPlatformInfo.sEFIChipSetId, &sPlatformInfo.sEFIChipSetFamily))
      {
        uint32 uTemp = 0;

        sPlatformInfo.bPlatformDetected = TRUE;

        // Read display config variables
        if (MDP_STATUS_OK == MDP_Display_GetVariable_Integer(L"DISPLAYCONFIG", &uTemp))
        {
          if (DISPLAY_FLAG_AMOLED & uTemp)
          {
            sPlatformInfo.uPowerCfgOverride = MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED;
          }
        }

        // Read the display panel ID override
        if (MDP_STATUS_OK == MDP_Display_GetVariable_Integer(L"DISPLAYID", &uTemp))
        {
          if (uTemp > 0)
          {
            DEBUG((EFI_D_ERROR, "DisplayDxe: Panel override enabled (ID:0x%x)\n", uTemp));
            sPlatformInfo.uPanelIdOverride =  uTemp;
          }
        }
      }

      // Parse sub-revision specific info to determine the QRD platform type
      uPlatformSubtype      = sPlatformInfo.sEFIPlatformType.subtype         & 0xFF;
      uHardwareVersionMajor = (sPlatformInfo.sEFIPlatformType.version >> 16) & 0xFF;

      switch (sPlatformInfo.sEFIPlatformType.platform)
      {
      case EFI_PLATFORMINFO_TYPE_QRD:

        sPlatformInfo.ePlatformQRDType = MDPPLATFORM_QRDTYPE_DEFAULT;

        switch (sPlatformInfo.sEFIChipSetId)
        {
        case EFICHIPINFO_ID_SDM660:
          if ((0x00                 == uPlatformSubtype)            &&
             (uHardwareVersionMajor >  0x00)                        &&
             (uHardwareVersionMajor <  0x10))
          {
            sPlatformInfo.ePlatformQRDType = MDPPLATFORM_QRDTYPE_SDM660QRD;
          }
          else
          {
            sPlatformInfo.ePlatformQRDType = MDPPLATFORM_QRDTYPE_SDM660QRD_PM660A;
          }
        break;

        case EFICHIPINFO_ID_SDM630:
		case EFICHIPINFO_ID_SDA630:	
          /* Remap SDM630 PM660A QRD type to SDM660 PM660A QRD as they uses the same display panel */
          sPlatformInfo.ePlatformQRDType = MDPPLATFORM_QRDTYPE_SDM660QRD_PM660A;
        break;

        default:
          sPlatformInfo.ePlatformQRDType = MDPPLATFORM_QRDTYPE_DEFAULT;
          break;
  
        }
        break;

      case EFI_PLATFORMINFO_TYPE_CDP:
      case EFI_PLATFORMINFO_TYPE_MTP:
      default:
        break;
      }
    }

    switch (ePlatformConfig)
    {
    case MDPPLATFORM_CONFIG_SW_RENDERER:

      if (NULL == pPlatformParams)
      {
        eStatus = MDP_STATUS_BAD_PARAM;
      }
      else if (TRUE == sPlatformInfo.bSWRender)
      {
        // SW Render mode is enabled already, just return the status
        pPlatformParams->sPlatformInfo.bSWRender = TRUE;
      }
      else if ((TRUE == pPlatformParams->sPlatformInfo.bSWRenderOverrride) ||
               (TRUE == PcdGetBool(PcdDisplayForceSwRenderer)))
      {
        // Force SW render mode for emulation and unknown platforms
        pPlatformParams->sPlatformInfo.bSWRender = TRUE;
        // Store that an override has been requested by the caller
        sPlatformInfo.bSWRenderOverrride         = pPlatformParams->sPlatformInfo.bSWRenderOverrride;
        // Cache that SW Rendering is enabled
        sPlatformInfo.bSWRender                  = TRUE;
        DEBUG((EFI_D_ERROR, "DisplayDxe: SW renderer mode enabled!\n"));
      }
      else
      {
        switch (sPlatformInfo.sEFIPlatformType.platform)
        {
        case EFI_PLATFORMINFO_TYPE_QRD:
          switch (sPlatformInfo.ePlatformQRDType)
          {
          /* Skip uefi display for SDM660 QRD as its display panel swapped dsi interfaces,
             and current xbl version can't support mixer swap. */
          case MDPPLATFORM_QRDTYPE_SDM660QRD:
            sPlatformInfo.bSWRender = TRUE;
            break;

          default:
            break;
          }
          break;

        // Force SW render mode for emulation and unknown platforms
        case EFI_PLATFORMINFO_TYPE_UNKNOWN:
        case EFI_PLATFORMINFO_TYPE_VIRTIO:
        case EFI_PLATFORMINFO_TYPE_RUMI:
          sPlatformInfo.bSWRender = TRUE;
          break;

        default:
          break;
        }

        if (TRUE == sPlatformInfo.bSWRender)
        {
          // Force SW render mode for emulation and unknown platforms
          pPlatformParams->sPlatformInfo.bSWRender = TRUE;
          // Store that an override has been requested by the caller
          sPlatformInfo.bSWRenderOverrride         = pPlatformParams->sPlatformInfo.bSWRenderOverrride;
          DEBUG((EFI_D_ERROR, "DisplayDxe: SW renderer mode enabled!\n"));
        }
        else
        {
          // Report SW render mode is disabled
          pPlatformParams->sPlatformInfo.bSWRender = FALSE;
        }
      }
      break;

    case MDPPLATFORM_CONFIG_GETPANELCONFIG:
      {
        if (NULL == pPlatformParams)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          // Retrieve panel configuration (could be dependent on the interface)
          switch (eDisplayId)
          {
          case MDP_DISPLAY_PRIMARY:
            
            pPlatformParams->sPlatformPanel.uDefaultVendor   = 0;
            pPlatformParams->sPlatformPanel.uDefaultRevision = 0;
            pPlatformParams->sPlatformPanel.uPanelId         = 0;
            pPlatformParams->sPlatformPanel.uPowerGridId     = sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId];
            pPlatformParams->sPlatformPanel.pPanelXMLConfig  = NULL;

            if (TRUE == Panel_CheckOverride(eDisplayId, pPlatformParams))
            {
              //Use configuration set by panel override
            }
            else if (TRUE == sPlatformInfo.bSWRender)
            {
              //use dummy panel for sw rendering
              pPlatformParams->sPlatformPanel.pPanelXMLConfig  = (int8 *)dummy_xmldata;
              pPlatformParams->sPlatformPanel.uConfigSize      = sizeof(dummy_xmldata);
              pPlatformParams->sPlatformPanel.eSelectedPanel   = MDPPLATFORM_PANEL_NONE;
            }
            else
            {
              // Report the proper information depending on the display.
              switch (sPlatformInfo.sEFIPlatformType.platform)
              {
              case EFI_PLATFORMINFO_TYPE_CDP:                
              case EFI_PLATFORMINFO_TYPE_RCM:
                // Dynamic panel detection
                if (MDP_STATUS_OK != DynamicDSIPanelDetection(pPlatformParams, &uPanelID, sPlatformInfo.uPanelIdOverride))
                {
    		  	  if ((EFICHIPINFO_ID_SDM630 == sPlatformInfo.sEFIChipSetId) || 
				      (EFICHIPINFO_ID_SDA630 == sPlatformInfo.sEFIChipSetId) || // SDM630
					  (EFICHIPINFO_ID_SDM636 == sPlatformInfo.sEFIChipSetId) ||
                      (EFICHIPINFO_ID_SDA636 == sPlatformInfo.sEFIChipSetId) || // SDM636
                      (EFICHIPINFO_ID_SDM455 == sPlatformInfo.sEFIChipSetId))   // SDM455/Taha
                  {
                    /* Truly 1080p with NT35695B - Video Mode */
                    pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_NT35695b_FHD_video_xmldata;
                    pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_NT35695b_FHD_video_xmldata);
                    pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_1080P_VIDEO;
                  }
                  else if ((EFI_PLATFORMINFO_TYPE_CDP == sPlatformInfo.sEFIPlatformType.platform) && 
                           (EFICHIPINFO_ID_SDM660 == sPlatformInfo.sEFIChipSetId) && 
                           (0x03 == sPlatformInfo.sEFIPlatformType.subtype))
                  {
                    /* SDM660 New SKU with Truly 1080p with NT35695B - Video Mode */
                    pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_NT35695b_FHD_video_xmldata;
                    pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_NT35695b_FHD_video_xmldata);
                    pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_1080P_VIDEO;
                  }
                  else    // default to SDM660
                  {
                    /* Truly 2k with NT35597 - Video Mode */
                    pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_TFT2P2827_E_video_xmldata;
                    pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_TFT2P2827_E_video_xmldata);
                    pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_VIDEO;
                  }
                  break;
                }
                break;
              case EFI_PLATFORMINFO_TYPE_MTP:
			    if ((EFICHIPINFO_ID_SDM630 == sPlatformInfo.sEFIChipSetId) ||
				    (EFICHIPINFO_ID_SDA630 == sPlatformInfo.sEFIChipSetId) || // SDM630
					(EFICHIPINFO_ID_SDM636 == sPlatformInfo.sEFIChipSetId) ||
				    (EFICHIPINFO_ID_SDA636 == sPlatformInfo.sEFIChipSetId) || // SDM636
				    (EFICHIPINFO_ID_SDM455 == sPlatformInfo.sEFIChipSetId))   // SDM455/Taha
                {
                  /* Truly 1080p with NT35695B - Video Mode */
                  pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_NT35695b_FHD_video_xmldata;
                  pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_NT35695b_FHD_video_xmldata);
                  pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_1080P_VIDEO;
                }
                else    // default to SDM660
                {
                  /* Truly 2k with NT35597 - Video Mode */
                  pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)Truly_TFT2P2827_E_video_xmldata;
                  pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(Truly_TFT2P2827_E_video_xmldata);
                  pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_VIDEO;
                }
                break;
              case EFI_PLATFORMINFO_TYPE_QRD:
                switch (sPlatformInfo.ePlatformQRDType)
                {
                /* Skip uefi display for SDM660 QRD as its display panel swapped dsi interfaces,
                   and current xbl version can't support mixer swap. */
                case MDPPLATFORM_QRDTYPE_SDM660QRD:
                  pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)dummy_xmldata;
                  pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(dummy_xmldata);
                  pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_NONE;
                  break;
                case MDPPLATFORM_QRDTYPE_SDM660QRD_PM660A:
                case MDPPLATFORM_QRDTYPE_DEFAULT:
                default:
                  pPlatformParams->sPlatformPanel.pPanelXMLConfig = (int8 *)RM67195_AMOLED_cmd_xmldata;
                  pPlatformParams->sPlatformPanel.uConfigSize     = sizeof(RM67195_AMOLED_cmd_xmldata);
                  pPlatformParams->sPlatformPanel.eSelectedPanel  = MDPPLATFORM_PANEL_RM67195_AMOLED_FHD_CMD;
                  break;
                }
                break;
              default:
                pPlatformParams->sPlatformPanel.pPanelXMLConfig    = (int8 *)dummy_xmldata;
                pPlatformParams->sPlatformPanel.uConfigSize        = sizeof(dummy_xmldata);
                pPlatformParams->sPlatformPanel.eSelectedPanel     = MDPPLATFORM_PANEL_NONE;
                break;
              }
            }
            break;
  
          case MDP_DISPLAY_EXTERNAL: 
            break;
          default:
            break;
          }
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
          case EFI_PLATFORMINFO_TYPE_MTP:
          case EFI_PLATFORMINFO_TYPE_QRD:
          case EFI_PLATFORMINFO_TYPE_RCM:

            // Panel power configuration override (set through the environment variable)
            if (sPlatformInfo.uPowerCfgOverride)
            {
              sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = sPlatformInfo.uPowerCfgOverride;
            }
            else
            {
              EFI_QCOM_PMIC_VERSION_PROTOCOL *PmicVersionProtocol = NULL;  
              EFI_PM_DEVICE_INFO_EXT_TYPE     PmicDeviceInfo      = {0xFF};

              // Populate the local power configuration (Force to PM_LCD_WLED for LCD)
              //
              // Note: OLED users configure this as 
              //         MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED - if using QCOM PMIC power solution
              //         MDP_PMIC_MODULE_CONTROLTYPE_NONE      - if using their own power solution

              /* LCD Power Configuration */
              sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = MDP_PMIC_MODULE_CONTROLTYPE_PM_LCD_WLED;

              if ((EFI_SUCCESS == gBS->LocateProtocol(&gQcomPmicVersionProtocolGuid, NULL, (VOID **)&PmicVersionProtocol)) &&
                  (EFI_SUCCESS == PmicVersionProtocol->GetPmicInfoExt(PMIC_PMI_DEV_INDEX, &PmicDeviceInfo)))
              {
                if ((0 == PmicDeviceInfo.PmicVariantRevision) ||
					((2 == PmicDeviceInfo.PmicVariantRevision) && (2 == PmicDeviceInfo.PmicAllLayerRevision)))
                {
                  /* OLED Power Configuration, PmicVariantRevision is 0x0 for PM660A */
                  sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED;
                }
              }
              else
              {
                DEBUG((EFI_D_WARN, "DisplayDxe: Get Pmic Variant Revision Failed\n"));
              }

              // Configure power to MDP_PMIC_MODULE_CONTROLTYPE_NONE here if not using QCOM PMIC power solution
              // sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId] = MDP_PMIC_MODULE_CONTROLTYPE_NONE;
            }

            // Populate the WLED strings used on the platform
            if (EFI_PLATFORMINFO_TYPE_QRD == sPlatformInfo.sEFIPlatformType.platform)
            {            
              sPanelPowerCtrl.uWledStringsPrimary = (EFI_PM_WLED_LED1 | EFI_PM_WLED_LED2);
            }
            else
            {
              sPanelPowerCtrl.uWledStringsPrimary = (EFI_PM_WLED_LED2 | EFI_PM_WLED_LED3);
            }

            // Primary Power Sequence
            if (MDP_STATUS_OK != (eStatus = Panel_CDP_PowerUp(eDisplayId, &sPanelPowerCtrl)))
            {
              DEBUG((EFI_D_WARN, "DisplayDxe: Primary Power Up Sequence Failed (%d)\n", eStatus));
            }
            else if (MDP_STATUS_OK != (eStatus = Panel_CDP_PeripheralPower(eDisplayId, &sPanelPowerCtrl, TRUE)))  // Secondary Power Sequence
            {
              DEBUG((EFI_D_WARN, "DisplayDxe: Secondary Power Up Sequence Failed (%d)\n", eStatus));
            }
            break;

          default:
            break;
          }

          break;

        case MDP_DISPLAY_EXTERNAL:
          break;

        default:
          break;

        }

      }
      break;
      case MDPPLATFORM_CONFIG_GETPANELDTINFO:
      {
        if (NULL == pPlatformParams)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          pPlatformParams->psPanelDTInfo = (PanelInfoType*)&gPanelList;
        }
        break;

      }
      case MDPPLATFORM_CONFIG_GETPANELLIST:
        {
          if (NULL == pPlatformParams)
          {
            eStatus = MDP_STATUS_BAD_PARAM;
          }
          else
          {
            uint32 i = 0;
            
            while (MDPPLATFORM_PANEL_NONE != gPanelList[i].ePanel)
            {
              //Copy Panel ID
              pPlatformParams->sPanelList.ePanel[i] = gPanelList[i].ePanel;
              i++; 
            }

            pPlatformParams->sPanelList.uCount = i;
          }
        }
        break;
      
    case MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS:
      {
        if (NULL == pPlatformParams)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          //Lookup panel
          int32 i = PANEL_INFOLIST_LENGTH - 1;
          while (0 <= i)
          {
            if (pPlatformParams->sPanelSupport.ePanel == gPanelList[i].ePanel)
            {
              if ((DISP_TOPOLOGY_CONFIG_NONE == pPlatformParams->sPanelSupport.uModeIndex) ||
                  (pPlatformParams->sPanelSupport.uModeIndex > DISPLAY_MODE_MAX))
              {
                pPlatformParams->sPanelSupport.uFlags = gPanelList[i].uModeFlags[0];
              }
              else
              {
                pPlatformParams->sPanelSupport.uFlags = gPanelList[i].uModeFlags[pPlatformParams->sPanelSupport.uModeIndex-1];
              }
              break;
            }
            i--;
          }
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
          case EFI_PLATFORMINFO_TYPE_MTP:
          case EFI_PLATFORMINFO_TYPE_QRD:
          case EFI_PLATFORMINFO_TYPE_RCM:
            if (MDP_STATUS_OK != (eStatus = Panel_CDP_PowerDown(eDisplayId, &sPanelPowerCtrl)))
            {
              DEBUG((EFI_D_WARN, "DisplayDxe: Primary Power Down Sequence Failed (%d)\n", eStatus));
            }
            else if (MDP_STATUS_OK != (eStatus = Panel_CDP_PeripheralPower(eDisplayId, &sPanelPowerCtrl, FALSE)))  // Secondary Power Sequence
            {
              DEBUG((EFI_D_WARN, "DisplayDxe: Secondary Power Down Sequence Failed (%d)\n", eStatus));
            }

            break;
          default:
            break;
          }

          break;
        case MDP_DISPLAY_EXTERNAL:
          break;
        default:
          break;
        }
      }
      break;
    case MDPPLATFORM_CONFIG_SETBACKLIGHT:
      {
        if (NULL == pPlatformParams)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          // Handle backlight level
          switch (eDisplayId)
          {
          case MDP_DISPLAY_PRIMARY:
            switch (sPlatformInfo.sEFIPlatformType.platform)
            {
            case EFI_PLATFORMINFO_TYPE_CDP:
            case EFI_PLATFORMINFO_TYPE_MTP:
            case EFI_PLATFORMINFO_TYPE_QRD:
            case EFI_PLATFORMINFO_TYPE_RCM:
              if ((MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED == sPanelPowerCtrl.ePMICSecondaryPower[eDisplayId]) &&
                  (FALSE == sPanelPowerCtrl.bOledPostInitDone))
              {
                eStatus = Panel_CDP_PmicOledPostInit(eDisplayId);
                sPanelPowerCtrl.bOledPostInitDone = TRUE;
              }
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
      }
      break;
    case MDPPLATFORM_CONFIG_GETPANELID:
      {
      }
      break;
    case MDPPLATFORM_CONFIG_GETPLATFORMINFO:
      {
        if (NULL == pPlatformParams)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          //
          // Return platform information
          //
          MDP_OSAL_MEMCPY(&pPlatformParams->sPlatformInfo, &sPlatformInfo, sizeof(MDPPlatformInfo));
        }
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
          case EFI_PLATFORMINFO_TYPE_MTP:
          case EFI_PLATFORMINFO_TYPE_QRD:
          case EFI_PLATFORMINFO_TYPE_RCM:
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
        if (NULL == pPlatformParams)
        {
          eStatus = MDP_STATUS_BAD_PARAM;
        }
        else
        {
          eStatus = SetDefaultGPIOState(&pPlatformParams->sGPIOState);
        }
      }
      break;
    case  MDPPLATFORM_CONFIG_BYPASS:
      {
          // SW Render Bypass mode
          eStatus = MDP_STATUS_OK;
      }
      break;
    default:
      eStatus = MDP_STATUS_BAD_PARAM;
      break;
    }
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
**/
static MDP_Status ReadPlatformIDAndChipID(EFI_PLATFORMINFO_PLATFORM_INFO_TYPE *pPlatformInfo, EFIChipInfoIdType *pChipSetId, EFIChipInfoFamilyType *pChipSetFamily)
{
  MDP_Status                           eStatus                = MDP_STATUS_OK;
  EFI_PLATFORMINFO_PROTOCOL            *hPlatformInfoProtocol;
  EFI_CHIPINFO_PROTOCOL                *hChipInfoProtocol;

  if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiPlatformInfoProtocolGuid,
                                         NULL,
                                         (VOID **)&hPlatformInfoProtocol))
  {
    if (EFI_SUCCESS != hPlatformInfoProtocol->GetPlatformInfo(hPlatformInfoProtocol, pPlatformInfo))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: gEfiPlatformInfoProtocolGuid->GetPlatformInfo() Failed.\n"));

      eStatus = MDP_STATUS_FAILED;
    }
  }
  else
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: gEfiPlatformInfoProtocolGuid protocol Failed.\n"));

    eStatus = MDP_STATUS_FAILED;
  }

  if (EFI_PLATFORMINFO_TYPE_UNKNOWN == pPlatformInfo->platform)
  {
    pPlatformInfo->platform = EFI_PLATFORMINFO_TYPE_VIRTIO;
  }

  // Read the chipset ID
  if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiChipInfoProtocolGuid,
                                         NULL,
                                         (VOID **)&hChipInfoProtocol))
  {
    if (EFI_SUCCESS != hChipInfoProtocol->GetChipId(hChipInfoProtocol, pChipSetId))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: gEfiChipInfoProtocolGuid->GetChipId() Failed. \n"));

      eStatus = MDP_STATUS_FAILED;
    }
    if (EFI_SUCCESS != hChipInfoProtocol->GetChipFamily(hChipInfoProtocol, pChipSetFamily))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: gEfiChipInfoProtocolGuid->GetChipFamily() Failed. \n"));

      eStatus = MDP_STATUS_FAILED;
    }

  }
  else
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: gEfiChipInfoProtocolGuid protocol Failed.\n"));

    eStatus = MDP_STATUS_FAILED;
  }

  return eStatus;
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
           EFI_TLMM_PROTOCOL   *TLMMProtocol;        

           if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void**)&TLMMProtocol))
           {
             uint32 uCount;          

             // Loop the list to configure all GPIOs.
             for (uCount=0;uCount<pGPIOList->uListSize;uCount++)
             {
                // Only try to program GPIOs that are within range, TLMM Macro (EFI_GPIO_CFG) supports up to 0x3FF
                if (pGPIOList->pGPIOList[uCount] < 0x3FF) 
                {
                  uint32 uValue = (pGPIOList->uState>0)?GPIO_HIGH_VALUE:GPIO_LOW_VALUE;
                  
                  // Setup GPIO
                  if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(pGPIOList->pGPIOList[uCount], 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), TLMM_GPIO_ENABLE))
                  {
                    DEBUG((EFI_D_ERROR, "DisplayDxe: Error configuring TLMM GPIO%d\n", uCount));

                  }
                  
                  // Setup Output
                  if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(pGPIOList->pGPIOList[uCount], 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), uValue))
                  {
                    DEBUG((EFI_D_ERROR, "DisplayDxe: Error configuring TLMM GPIO%d\n", uCount));
                  }              
                }
             }
           }
           else
           {
             eStatus = MDP_STATUS_NO_RESOURCES;
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
