#ifndef __MDPPLATFORMLIB_H__
#define __MDPPLATFORMLIB_H__
/*=============================================================================
 
  File: MDPPlatformLib.h
 
  Header file for MDP platform functions
  
 
  Copyright (c) 2011-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Uefi.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIChipInfo.h>
#include "MDPTypes.h"


/*===========================================================================
                        Defines
===========================================================================*/


/* Bit fields for uFlags in PlatformDSIDetectParams structure. 
    Currently, it is used to define the clock lane config but this can be grown in future.
 */
#define MDPPLATFORM_PANEL_DETECT_FLAG_CLOCK_FORCEHS      0x00000001  /*Force clock lane in HS*/

/* Panel Reset related information
*/

/* Bit Fields for uFlags in the below structure */
#define MDDPLATFORM_PANEL_RESET_FLAG_USE_CUSTOM_DELAY    0x00000001  /* Wait for the specified delay instead of the default after reset */
#define MDDPLATFORM_PANEL_RESET_FLAG_FORCE_RESET         0x00000002  /* Force the panel reset */



/* Display Variable flags (DISPLAYCONFIG environment variable)
 */
#define   DISPLAY_FLAG_AMOLED                            0x80000000  /* Force AMOLED power configuration */

/* Maximum number of panels supported for a chip */
#define   MDPPLATFORM_PANELS_SUPPORTED_MAX               32

/* Maximum length of panel name
*/
#define DISPLAY_PANEL_NAME_MAX_LEN                       64

/* Maximum length of Device Tree tag
*/
#define DISPLAY_PANEL_DT_LABEL_MAX_LEN                   64

/* Maximum number of display topology
*/
#define DISPLAY_MODE_MAX                                 3

#define PANEL_OVERRIDE_STRINGNAME                        L"DISPLAYID"

/*===========================================================================
                        Enumerations
===========================================================================*/

typedef enum {
  MDPPLATFORM_PANEL_NONE =0x0,                            /* No panel specified                     */
  MDPPLATFORM_PANEL_HDMI,                                 /* HDMI panel                             */
  MDPPLATFORM_PANEL_SIM_VIDEO_PANEL,                      /* Single DSI video mode simulation panel */
  MDPPLATFORM_PANEL_SIM_DUALDSI_VIDEO_PANEL,              /* Dual DSI video mode simulation panel   */
  MDPPLATFORM_PANEL_SIM_CMD_PANEL,                        /* Single DSI CMD mode simulation panel   */
  MDPPLATFORM_PANEL_SIM_DUALDSI_CMD_PANEL,                /* Dual DSI CMD mode simulation panel     */
  MDPPLATFORM_PANEL_NT35597_WQHD_DUALDSI_CMD,             /* NT35597 2k command panel non-DSC mode  */
  MDPPLATFORM_PANEL_NT35597_WQHD_DUALDSI_VIDEO,           /* NT35597 2k video panel non-DSC mode    */
  MDPPLATFORM_PANEL_NT35597_WQHD_DSC_CMD,                 /* NT35597 2k command panel DSC mode      */
  MDPPLATFORM_PANEL_NT35597_WQHD_DSC_VIDEO,               /* NT35597 2k video panel DSC mode        */
  MDPPLATFORM_PANEL_SHARP_4K_DSC_CMD,                     /* NT35950 4k command panel DSC mode      */
  MDPPLATFORM_PANEL_SHARP_SPLIT_LINK_VIDEO,               /* Sharp split link video mode            */
  MDPPLATFORM_PANEL_R63417_TRULY_1080P_VIDEO,             /* R63417 1080p  dsi video mode           */
  MDPPLATFORM_PANEL_R63417_TRULY_1080P_CMD,               /* R63417 1080p dsi cmd mode              */
  MDPPLATFORM_PANEL_TRULY_1080P_VIDEO,                    /* Truly 1080P single dsi video mode      */
  MDPPLATFORM_PANEL_TRULY_1080P_CMD,                      /* Truly 1080P single dsi command mode    */
  MDPPLATFORM_PANEL_AMOLED_2K,                            /* Amoled 2k panel                        */
  MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_VIDEO,            /* Truly 2k video panel non-DSC mode      */
  MDPPLATFORM_PANEL_TRULY_WQXGA_DUALDSI_CMD,              /* Truly 2k command panel non-DSC mode    */  
  MDPPLATFORM_PANEL_TRULY_WQXGA_DSC_VIDEO,                /* Truly 2k video panel DSC mode          */
  MDPPLATFORM_PANEL_TRULY_WQXGA_DSC_CMD,                  /* Truly 2k video panel DSC mode          */
  MDPPLATFORM_PANEL_NT35597_WQXGA_DUALDSI_VIDEO,          /* NT35597 2k video panel non-DSC mode    */
  MDPPLATFORM_PANEL_RM67195_AMOLED_FHD_CMD,               /* RM67195 1080p AMOLED command panel     */
  MDPPLATFORM_PANEL_LGDINCELL_SW49106_FHD_VIDEO,          /* LGD INCELL FHD+ VIDEO mode panel       */
  MDPPLATFORM_PANEL_HX8399_TRULY_FHD_VIDEO,               /* Truly Hx8399 fhd single dsi video mode */
  MDPPLATFORM_PANEL_MAX
} MDPPlatformPanelType;


/* List of support platform specific configurations 
 */
typedef enum
{
  MDPPLATFORM_CONFIG_GETPANELCONFIG = 0x0,               /* Retrieve panel configuration */
  MDPPLATFORM_CONFIG_POWERUP,                            /* Power up power grid */
  MDPPLATFORM_CONFIG_POWERDOWN,                          /* Power down power grid */
  MDPPLATFORM_CONFIG_GETPANELID,                         /* Return the panel identifier */
  MDPPLATFORM_CONFIG_SETBACKLIGHT,                       /* Set a brightness or backlight level */
  MDPPLATFORM_CONFIG_GETPLATFORMINFO,                    /* Return platform configuration information */
  MDPPLATFORM_CONFIG_SW_RENDERER,                        /* Return SW render mode information */
  MDPPLATFORM_CONFIG_RESETPANEL,                         /* Physical reset of the panel */
  MDPPLATFORM_CONFIG_SETGPIOSTATE,                       /* Set the state of a GPIO */
  MDPPLATFORM_CONFIG_GETPANELLIST,                       /* Get list of supported panels */ 
  MDPPLATFORM_CONFIG_GETPANELDTINFO,                     /* Get list of panels DT Info*/
  MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS,               /* Check if a supplied panel is supported in bootloader */
  MDPPLATFORM_CONFIG_BYPASS,                             /* Configuration bypass */
  MDPPLATFORM_CONFIG_MAX
} MDPPlatformConfigType;

/* GPIO Types */
typedef enum
{
  MDPPLATFORM_GPIOTYPE_TLMM = 0x0,                        /* TLMM GPIO */
  MDPPLATFORM_GPIOTYPE_PMIC,                              /* PMIC GPIO */
  MDPPLATFORM_GPIOTYPE_PMI,                               /* PMI GPIO */
} MDPPlatformGPIOType;

typedef enum
{
  DISP_INTF_NONE                          = 0x0,          /* No interface specified */
  DISP_INTF_HDMI                          = 0x1,          /* HDMI */
  DISP_INTF_DSI                           = 0x2,          /* DSI */
  DISP_INTF_DP                            = 0x3           /* DisplayPort */
} DisplayInterfaceType;

/*===========================================================================
                        Structs
===========================================================================*/

/* QRD Type identification information
 */
typedef enum
{
  MDPPLATFORM_QRDTYPE_DEFAULT = 0x0,                      /* DEFAULT QRD Type */
  MDPPLATFORM_QRDTYPE_SDM660QRD,                          /* SDM660 QRD PM660L */
  MDPPLATFORM_QRDTYPE_SDM660QRD_PM660A,                   /* SDM660 QRD PM660A */
  MDPPLATFORM_QRDTYPE_MAX
} MDPPlatformQRDType;

/* Platform identification information
 */
typedef struct 
{
   bool32                               bPlatformDetected;      /* [out] Indicates if the palatform ID was successfully detected */
    
   EFI_PLATFORMINFO_PLATFORM_INFO_TYPE  sEFIPlatformType;       /* [out] EFI Platform information */
   EFIChipInfoIdType                    sEFIChipSetId;          /* [out] EFI Chipset information */
   EFIChipInfoFamilyType                sEFIChipSetFamily;      /* [out] EFI Chipset family information */ 
   
   uint32                               uPrimaryPanelId;        /* [out] Primary panel ID */
   bool32                               bSWRender;              /* [out] Indicates if the displayDxe is SW renderer only */
   uint32                               uPanelIdOverride;       /* [out] Panel ID Override configuration */
   MDP_PmicModuleControlType            uPowerCfgOverride;      /* [out] Power grid override */
   bool32                               bSWRenderOverrride;     /* [in]  Force SW render mode */
   MDPPlatformQRDType                   ePlatformQRDType;       /* [out] QRD Platform information */
} MDPPlatformInfo;


typedef struct
{
    uint32 uFlags;              /* reset options */
    uint32 uCustomDelayMs;      /* This field is valid only if USE_CUSTOM_DELAY is set in uFlags. A value of 0 -> no delay */
}MDPPlatformPanelResetInfo;

/* Panel XML configuration 
 */
typedef struct
{
    int8                   *pPanelXMLConfig;          /* xml configuration for panel */
    uint32                  uConfigSize;              /* size of the xml configuration data in bytes*/
    uint8                   uDefaultVendor;           /* vendor ID */
    uint8                   uDefaultRevision;         /* revision */ 
    uint32                  uPanelId;                 /* if set, find the panel that matches this panel ID */
    uint32                  uPowerGridId;             /* power grid id */
    MDPPlatformPanelType    eSelectedPanel;           /* index of the selected panel */
} MDPPlatformPanelInfo;


/* HDMI configuration*/
typedef struct
{
  uint32 uCecDataGpio;
  uint32 uDDCDataGpio;
  uint32 uDDDClkGpio;
  uint32 uHPDGpio;
} HDMI_PinInfo;


/* Backlight configuration */
typedef struct
{
    bool32                          bEnable;               /* Enable/disable the backlight/brightness power grid */
    uint32                          uLevel;                /* New brightness level in percentage, 0-100% */
    MDP_Panel_BacklightType         eBacklightType;        /* Configuration of the backlight interface module */
    union {
        MDP_PmicBacklightControlType  eBacklightCtrl;      /* PMIC module for backlight configuration  */
    } uBacklightCntrl;

} BacklightConfigType;

/* Power configuration */
typedef struct
{
    MDP_PmicModuleControlType       ePMICSecondaryPower;      /* Configuration for PMIC based secondary power source */
} PowerConfigType;


/* GPIO State */
typedef struct
{
    MDPPlatformGPIOType             eGPIOType;       /* Type of GPIO to be configured */
    uint32                         *pGPIOList;       /* Pointer to an list of GPIO's to be modified */
    uint32                          uListSize;       /* Number of entries in the list */
    uint32                          uState;          /* GPIO state */
} GpioStateType;


/* List of panels supported, sorted by Panel index */
typedef struct
{
  uint32                       uCount;                                     /* Number of panels */
  MDPPlatformPanelType         ePanel[MDPPLATFORM_PANELS_SUPPORTED_MAX];   /* Panel indices */
} PanelListType;

/* Panel support flags for the panel */
typedef struct
{
  MDPPlatformPanelType ePanel;                      /* [in]  Panel index */
  uint32               uModeIndex;                  /* [in]  panel mode index */
  uint32               uFlags;                      /* [out] associated flags */
} PanelSupportType;

typedef struct
{
  CHAR8                         name[DISPLAY_PANEL_NAME_MAX_LEN];        /* Name used by fastboot oem command */
  MDPPlatformPanelType          ePanel;                                  /* Panel ID */
  CHAR8                         DTLabel[DISPLAY_PANEL_DT_LABEL_MAX_LEN]; /* Device tree node name */
  DisplayInterfaceType          eInterface;                              /* Interface type */
  int8                         *pPanelXMLConfig;                         /* Panel XML configuration */
  uint32                        uConfigSize;                             /* Size of panel XML configuration */
  uint32                        uConfigNum;                              /* Topology configuration index */
  uint32                        uPLLOverride;                            /* PLL Override*/
  uint32                        uModeFlags[DISPLAY_MODE_MAX];            /* Display operating modes for the panel, refer DisplayModeType */
} PanelInfoType;

/* Union of panel properties passed to MDPPlatformConfigure() function
*/
typedef union
{
    MDPPlatformPanelInfo       sPlatformPanel;      /* MDPPLATFORM_CONFIG_GETPANELCONFIG(Primary) */
    HDMI_PinInfo               sHDMIPinConfig;      /* MDPPLATFORM_CONFIG_GETPANELCONFIG(HDMI) */
    BacklightConfigType        sBacklightConfig;    /* MDPPLATFORM_CONFIG_SETBACKLIGHT */
    MDPPlatformInfo            sPlatformInfo;       /* MDPPLATFORM_CONFIG_GETPLATFORMINFO */
    MDPPlatformPanelResetInfo  sPlatformPanelReset; /* MDPPLATFORM_CONFIG_RESETPANEL */
    PowerConfigType            sPowerConfig;        /* MDPPLATFORM_CONFIG_POWERUP/MDPPLATFORM_CONFIG_POWERDOWN */
    GpioStateType              sGPIOState;          /* MDPPLATFORM_CONFIG_SETGPIOSTATE */
    PanelListType              sPanelList;          /* MDPPLATFORM_CONFIG_GETPANELLIST */
    PanelInfoType             *psPanelDTInfo;       /* MDPPLATFORM_CONFIG_GETPANELDTINFO */
    PanelSupportType           sPanelSupport;       /* MDPPLATFORM_CONFIG_GETPANELSUPPORTFLAGS */
} MDPPlatformParams;


/*===========================================================================

                        Public Functions

===========================================================================*/

/* MDP platform specific configuration function 
 */
MDP_Status MDPPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams);


#endif // __MDPLIB_H__


