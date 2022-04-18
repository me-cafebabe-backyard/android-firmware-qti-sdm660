/** @file \UsbConfigUsbCores.c

  Function and structure definitions for each USB core supported by this
  platform.

  Copyright (c) 2015 - 2017 QUALCOMM Technologies Inc. All rights reserved.
**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 01/18/17   pm       Do not set PIPE3 freq to XO
 12/01/16   ak       Porting from Boot.xf.1.2
 12/01/16   pm       Removed PMIC index from Pmic USB Protocal API calls
 10/05/16   arung    Add UsbSharedLib
 05/06/16   ck       Temp workaround by enable VBUS asap
 04/29/16   ck       Update HS PHY init for host mode
 03/31/16   ck       Disable SS PHY init for BU and correct HS PHY init
 02/23/16   ck       Isolate UsbCore data within the module
 01/22/16   ck       Fix the USB debug message usages
 01/14/16   ck       Enable host mode support in Virtio
 11/24/15   ck       Virtio FBC support
 10/26/15   ck       Init Sdm660 Pre-Si support
=============================================================================*/

#include "UsbConfigUsbCoresPrivate.h"
#include "UsbSharedLib.h"

#define FREQ_MHZ(f)     (f * 1000 * 1000)
#define FREQ_KHZ(f)     (f * 1000)

/*
 * USB 3.0 Clock definitions
 */

#define USB3_PIPE_CLK_MIN_FREQ_HZ             FREQ_MHZ(125)

#define USB3_MASTER_CLK_MIN_FREQ_HZ           FREQ_MHZ(120)
#define USB3_AXI_CLK_MIN_FREQ_HZ              FREQ_MHZ(120)
#define USB3_PHY_AUX_CLK_MIN_FREQ_HZ          FREQ_KHZ(1200)

// Mock CLK needs to be set at 19.2 Mhz for Gandalf
#define USB3_MOCK_CLK_MIN_FREQ_HZ             FREQ_KHZ(19200)

#define MICRO_STALL_UNITS(x)  ((x) * 10)
#define MILLI_STALL_UNITS(x)  ((x) * 10000)

#define QUSB_PHY_MAX_STATUS_VERIFY_ATTEMPTS   50


/* Power Domain list */
const CHAR8 USB30_PowerDomain[] = "VDD_USB_30";


#define QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_EN   (HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_BMSK)
#define QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_FS   (0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_SHFT)
#define QUSB2PHY_PORT_UTMI_CTRL1_OP_NON_MODE      (0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OP_MODE_SHFT)


/*******************************************************************************
 * USB core structures
 ******************************************************************************/

/*
 * USB core enable clock configuration arrays
 */

QCOM_USB_CLOCK Usb30EnCoreClocks[] =
{
  //{ "clock name",                     frequency,                    divider }
  {"gcc_cfg_noc_usb3_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre2_usb3_axi_clk",      USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_sleep_clk",          0,                             1 },
  {"gcc_usb30_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb_phy_cfg_ahb2phy_clk",  0,                             1 },
  {"gcc_usb3_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_phy_pipe_clk",        0,                             1 }
};

/*
 * USB core disable clock configuration arrays
 */

QCOM_USB_CLOCK Usb30DisCoreClocks[] =
{
  {"gcc_cfg_noc_usb3_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre2_usb3_axi_clk",      USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_sleep_clk",          0,                             1 },
  {"gcc_usb30_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb_phy_cfg_ahb2phy_clk",  0,                             1 },
  {"gcc_usb3_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_phy_pipe_clk",        0,                             1 }
};


/*
 * Static Variables
 */
// TLMMProtocol to enable USB HUB
EFI_TLMM_PROTOCOL                             *TLMMProtocol = NULL;

// PMIC GPIO protocol
EFI_QCOM_PMIC_GPIO_PROTOCOL                   *PmicGpioProtocol = NULL;

// NPA Client Handle for SS1 and SS2 Cores
STATIC npa_client_handle                      gPmicNpaClientSS1 = NULL;

//NPA client handles for SNOC - required for all cores
STATIC npa_client_handle                      gNpaClientSS1Snoc = NULL;

//busses required for primary core
STATIC npa_client_handle                      gNpaClientAggre1 = NULL;

EFI_CLOCK_PROTOCOL                            *ClockProtocol = NULL;
EFI_QCOM_PMIC_USB_PROTOCOL                    *gPmicUsbProtocol = NULL;

extern EFI_GUID                               gQcomTokenSpaceGuid;
extern EFI_PLATFORMINFO_PLATFORM_INFO_TYPE    PlatformInfo;


/*******************************************************************************
 * Core initialization function implementations
 ******************************************************************************/

/*
 * See UsbConfigLibPrivate.h
 */
STATIC
EFI_STATUS
UsbConfigLibOpenProtocols (
  VOID
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG();

  //TODO:CK:Temp. use WRN_CHK to avoid issues
  if (!ClockProtocol) {
    Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID**)&ClockProtocol);
    if (EFI_ERROR(Status)) {
      ClockProtocol = NULL;
      WRN_CHK("failed to locate CLOCK protocol");
    }
  }

  if (!gPmicUsbProtocol) {
    // Find the PMIC USB charger protocol
    Status = gBS->LocateProtocol(&gQcomPmicUsbProtocolGuid, NULL, (void**)&gPmicUsbProtocol);
    if (EFI_ERROR(Status))
    {
      gPmicUsbProtocol = NULL;
      WRN_CHK("Failed to open PMIC USB protocol Status =  (0x%x)", Status);
    }
  }

  if (!gPmicNpaClientSS1) {
    gPmicNpaClientSS1 = npa_create_sync_client(
      PMIC_NPA_GROUP_ID_USB_SS1, //PMIC_NPA_GROUP_ID_USB_SS1 - Connect to the usb ss1 resource
      "usb_ss1",                 //client name "usb_ss1"
      NPA_CLIENT_REQUIRED);      //NPA_CLIENT_REQUIRED: Request must honor request
    if (!gPmicNpaClientSS1)
    {
      WRN_CHK("gPmicNpaClientSS1 cannot be created");
    }
  }

  if (!gNpaClientSS1Snoc) {
    //Create NPA nodes for required buses requests
    gNpaClientSS1Snoc = npa_create_sync_client("/clk/snoc", "usb_ss1_snoc", NPA_CLIENT_REQUIRED);
    if (!gNpaClientSS1Snoc)
    {
      WRN_CHK("gNpaClientSS1Snoc cannot be created");
    }
  }

  if (!gNpaClientAggre1) {
    gNpaClientAggre1 = npa_create_sync_client("/clk/agr1", "usb_ss1_agr1", NPA_CLIENT_REQUIRED);

    if (!gNpaClientAggre1)
    {
      WRN_CHK("gNpaClientAggre1 cannot be created");
    }
  }

  if (!PmicGpioProtocol) {
    Status = gBS->LocateProtocol(&gQcomPmicGpioProtocolGuid, NULL, (void **)&PmicGpioProtocol);
    if (EFI_ERROR(Status))
    {
      PmicGpioProtocol = NULL;
      WRN_CHK("Failed to open PMIC GPIO protocol Status =  (0x%x)", Status);
    }
  }

//TODO:CK:Temp. use ON_EXIT, remove Status = EFI_SUCCESS later
//ON_EXIT:
  FNC_LEAVE_MSG();
  Status = EFI_SUCCESS;
  return Status;
}

/**
  Initializes power domains for USB.

  @retval EFI_SUCCESS            USB clocks initialized successfully.
  @retval EFI_NOT_FOUND          Unable to locate clock protocol.

**/
STATIC
EFI_STATUS
EFIAPI
ConfigPowerDomain(
  IN BOOLEAN       bEnable,
  IN CONST CHAR8   *szDomain
  )
{
  EFI_STATUS   Status = EFI_SUCCESS;
  UINTN        uClockPowerDomainId;

  FNC_ENTER_MSG ();

  if (ClockProtocol)
  {
      Status = ClockProtocol->GetClockPowerDomainID(ClockProtocol, szDomain, &uClockPowerDomainId);
      WRN_CHK ("USBConfigLib:GetClockPowerDomainID failed!");

      if (TRUE == bEnable)
      {
        Status =  ClockProtocol->EnableClockPowerDomain(ClockProtocol, uClockPowerDomainId);
        WRN_CHK ("USBConfigLib:EnableClockPowerDomain failed!");
      }
      else if (FALSE == bEnable)
      {
        Status =  ClockProtocol->DisableClockPowerDomain(ClockProtocol, uClockPowerDomainId);
        WRN_CHK ("USBConfigLib:DisableClockPowerDomain failed!");
      }
  }
  else
  {
      WRN_CHK ("failed to locate Clock Protocol ");
      WRN_CHK ("failed to initialize PowerDomain");
  }

  FNC_LEAVE_MSG ();
  return Status;
}



/**
  Initializes all clocks for a USB core.

  @param [in]  Clocks       Clock array
  @param [in]  ClockCount   Number of clocks in array

  @retval EFI_SUCCESS       USB clocks enabled successfully
  @retval Others            Error enabling at least 1 clock
**/
STATIC
EFI_STATUS
InitUsbClocks (
  IN  UINTN                 ClockCount,
  IN  QCOM_USB_CLOCK        *Clocks
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       ClkIdx;

  FNC_ENTER_MSG ();

  // validate parameters
  if ((NULL == Clocks) || (0 == ClockCount)) {
    Status = EFI_INVALID_PARAMETER;
    DBG(EFI_D_ERROR, "invalid parameter");
    goto ON_EXIT;
  }

  if (NULL == ClockProtocol) {
    DBG(EFI_D_ERROR, "ClockProtocol unavailable");
    Status = EFI_NOT_FOUND;
    goto ON_EXIT;
  }

  // enable each clock
  for (ClkIdx = 0; ClkIdx < ClockCount; ClkIdx++) {
    Status = EnableClock (
                Clocks[ClkIdx].Name,
                Clocks[ClkIdx].Frequency,
                Clocks[ClkIdx].Divider
                );
    if (EFI_ERROR (Status)) {
      DBG(EFI_D_ERROR, "failed to enable clock '%a'", Clocks[ClkIdx].Name);
    }
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end InitUsbClocks



/**
  Disables all clocks for a USB core.

  @param [in]  Clocks       Clock array
  @param [in]  ClockCount   Number of clocks in array

  @retval EFI_SUCCESS       USB clocks disabled successfully
  @retval Others            Error disabling at least 1 clock
**/
STATIC
EFI_STATUS
DisableUsbClocks (
  IN  UINTN                 ClockCount,
  IN  QCOM_USB_CLOCK        *Clocks
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       ClkIdx;

  FNC_ENTER_MSG ();

  // validate parameters
  if ((NULL == Clocks) || (0 == ClockCount)) {
    Status = EFI_INVALID_PARAMETER;
    DBG(EFI_D_ERROR, "invalid parameter");
    goto ON_EXIT;
  }

  if (NULL == ClockProtocol) {
    DBG(EFI_D_ERROR, "ClockProtocol unavailable");
    Status = EFI_NOT_FOUND;
    goto ON_EXIT;
  }
  // disable each clock
  for (ClkIdx = 0; ClkIdx < ClockCount; ClkIdx++) {
    Status = DisableClock (Clocks[ClkIdx].Name);
    if (EFI_ERROR (Status)) {
      DBG(EFI_D_ERROR, "failed to disable clock '%a'", Clocks[ClkIdx].Name);
    }
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}



/**
  Enable vbus for primary port (SuperSpeed Port)

  @retval EFI_SUCCESS            Success

**/
EFI_STATUS
EFIAPI
EnableVbusSS1 (
  VOID
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;

  FNC_ENTER_MSG ();

  if (NULL == gPmicUsbProtocol) {
    // Find the PMIC USB charger protocol
    Status = gBS->LocateProtocol(&gQcomPmicUsbProtocolGuid, NULL, (void**)&gPmicUsbProtocol);
    if (EFI_ERROR(Status))
    {
      gPmicUsbProtocol = NULL;
      WRN_CHK("Failed to open PMIC USB protocol Status =  (0x%x)", Status);
      goto ON_EXIT;
    }
  }

  Status = gPmicUsbProtocol->EnableOtg(TRUE);
  WRN_CHK ("failed to enable Vbus, Status = 0x%x", Status);

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}


/**
  This API is used for resetting the Link and PHYs using clock control

  @param None

**/
VOID
SynopsysGccReset(
  IN  QCOM_USB_CORE         *UsbCore
)
{
  FNC_ENTER_MSG ();

  if (UsbCore->CoreType == USB_CONFIG_SSUSB1)
  {
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB_30_BCR_OFFS, HWIO_GCC_USB_30_BCR_BLK_ARES_BMSK);
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_BCR_OFFS, HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK);
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_BCR_OFFS, HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK);
    gBS->Stall (100);

    HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_BCR_OFFS, ~HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK);
    HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_BCR_OFFS, ~HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK);
    HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, ~HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB_30_BCR_OFFS, ~HWIO_GCC_USB_30_BCR_BLK_ARES_BMSK);
    gBS->Stall (100);
  }

  FNC_LEAVE_MSG ();
  return;
}



/**
  Update HSTX_TRIM in TUNE2 

**/
VOID
QcUsbUpdateHstxTrim (
  IN QCOM_USB_CONFIG_CORE_TYPE  CoreId
  )
{
  // not needed for Sdm660 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass QcUsbUpdateHstxTrim");
    goto ON_EXIT;
  }

  DBG(EFI_D_WARN, "Stub QcUsbUpdateHstxTrim. Wait for QMP USB3-DP PHY Starlord 14LPE HPG update");
  
  UINT32 hstx_trim_val = 0;

  hstx_trim_val = HWIO_QFPROM_CORR_CALIB_ROW11_LSB_INM(SECURITY_CONTROL_BASE,
            HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_BMSK) 
            >> HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_SHFT;
  DBG(EFI_D_INFO, "hstx_trim_val= 0x%x", hstx_trim_val);

  if(hstx_trim_val)
  {
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_OUTM(PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_UTM_HSTX_TRIM_BMSK,
        (hstx_trim_val - QUSB_HSTX_TRIM_OFFSET) << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_UTM_HSTX_TRIM_SHFT);
  }
  
ON_EXIT:
  return;
}


/**
  Initializes High Speed USB SNPS Pico phy when connected to SNPS Core

  @retval EFI_SUCCESS            High Speed USB phy  initialized
                                 successfully.

**/
EFI_STATUS
InitHSUSBPhy (
  IN QCOM_USB_CONFIG_CORE_TYPE  CoreId,
  IN UINTN                      BaseAddr
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINT8 UefiVar;
  UINTN UefiVarSize;

  FNC_ENTER_MSG ();

  // Sdm660 RUMI PHY init sequence. 
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    UINT32 Calibration = 0x1A0;
    UINT32 Clkfreq = 0;
    UINT32 SeBits = HAL_SSUSB_SNPS_R3PC_DCM_CMD_RESET;
    
    /* Emulation initialization */
    //d.s (hs2Addr+0x04)  %LE %Long 0x7F
    HAL_USB_WRITE(HS2ADDR, 0x04, 0x7F);
    //d.s (hs2Addr+0x04)  %LE %Long 0x00
    HAL_USB_WRITE(HS2ADDR, 0x04, 0x00);
    //d.s (hs2Addr+0x28)  %LE %Long 0x3FF
    HAL_USB_WRITE(HS2ADDR, 0x28, 0x3FF);
    //d.s (hs2Addr+0x2C)  %LE %Long 0x1F
    HAL_USB_WRITE(HS2ADDR, 0x2C, 0x1F);

    /* Initialization code for QRBTC Rev2*/
    /*d.s QRBTC_USB2_PLL %long 0x00000019    //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
    d.s QRBTC_USB2_PLLCTRL2 %long 0x00000020 //[5,14]HWIO_USB2_PLLCTRL2_ADDR
    d.s QRBTC_USB2_PLLCTRL1 %long 0x00000079 //[4,10]HWIO_USB2_PLLCTRL1_ADDR
    d.s QRBTC_USB2_PLLCTRL3 %long 0x00000000 //[6,18]HWIO_USB2_PLLCTRL3_ADDR
    d.s QRBTC_USB2_PLL %long 0x00000099      //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
    d.s QRTBC_USB2_PLLTEST1 %long 0x00000004 //[2,8]HWIO_USB2_PLLTEST1_ADDR
    d.s QRBTC_USB2_PLL %long 0x000000D9      //[1,4]HWIO_QRBTC_USB2_PLL_ADDR*/

    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLL_OFF, 0x00000019);        //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
	gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLLCTRL2_OFF, 0x00000020);   //[5,14]HWIO_USB2_PLLCTRL2_ADDR
	gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLLCTRL1_OFF, 0x00000079);   //[4,10]HWIO_USB2_PLLCTRL1_ADDR
	gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLLCTRL3_OFF, 0x00000000);   //[6,18]HWIO_USB2_PLLCTRL3_ADDR
	gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLL_OFF, 0x00000099);        //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
	gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, QRTBC_USB2_PLLTEST1_OFF, 0x00000004);   //[2,8]HWIO_USB2_PLLTEST1_ADDR
	gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLL_OFF, 0x000000D9);        //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
	gBS->Stall(100);
	
    //RUMI: PLL_RESET
    /*HAL_USB_WRITE(QRBTC_BASE, 0x7500, 0x80000000);
    gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, 0x7500, 0);
    gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, 0x7500, 0x201e0);
    gBS->Stall(100);
    HAL_USB_WRITE(QRBTC_BASE, 0x7500, 0);*/

    /* DCM reset */
    HAL_USB_WRITE(HS2ADDR, 0x20, SeBits);
	gBS->Stall(100);
    HAL_USB_WRITE(HS2ADDR, 0x20, 0);
	gBS->Stall(100);
    //shift the DCM
    HAL_USB_WRITE(HS2ADDR, 0x20, Calibration);
	gBS->Stall(100);
    HAL_USB_WRITE(HS2ADDR, 0x14, 5);
	gBS->Stall(100);
    Clkfreq = HAL_USB_READ(HS2ADDR, 0x10);
	gBS->Stall(100);
  }

  if ((PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_RUMI)   &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    //Hard reset PHY
    HAL_USB_OR(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    gBS->Stall(100);
    HAL_USB_AND(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, ~HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    gBS->Stall(100);

    // TODO: Need to confirm whether the change is permanent. 
    // Currently, device and host mode has different phy config values

    //if UsbHostPrimaryPort is set to host override, force host mode
    UefiVarSize = sizeof(UefiVar);
    Status = gRT->GetVariable(L"UsbHostPrimaryPort", &gQcomTokenSpaceGuid, NULL, &UefiVarSize, &UefiVar);

	/*if (!EFI_ERROR(Status) && (UefiVar != 0)) {
      DBG(EFI_D_WARN, "Host Mode HS Phy Init");

      // Keep Port Power Down
      HAL_USB_WRITE(PERIPH_SS_AHB2PHY_WEST_BASE, HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PWR_CTRL1_OFFS, 0x63);
      gBS->Stall(100);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_ANALOG_CONTROLS_TWO_OFFS,
        0x13);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_CLOCK_INVERTERS_OFFS,
        0x7C);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_CMODE_OFFS,
        0x80);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_PLL_LOCK_DELAY_OFFS,
        0x0A);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_IMP_CTRL1_OFFS,
        0x8C);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_TUNE1_OFFS,
        0x05);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_TUNE2_OFFS,
        0x03);

      HAL_USB_WRITE(
        PERIPH_SS_AHB2PHY_WEST_BASE,
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_RESCODE_CTRL_OFFS,
        0xFF);

      gBS->Stall(100);
      HAL_USB_WRITE(PERIPH_SS_AHB2PHY_WEST_BASE, HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PWR_CTRL1_OFFS, 0x62);
    }
    else {*/
    DBG(EFI_D_WARN, "Device Mode HS Phy Init");
    usb_shared_hs_phy_init();
	//}

    gBS->Stall(200);

}
  FNC_LEAVE_MSG ();
  return EFI_SUCCESS;
}



/**
  Initializes super speed USB phy

  @retval EFI_SUCCESS            Super Speed USB phy  initialized
                                 successfully.

**/
STATIC
EFI_STATUS
InitSSUSBPhy (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT8 MaxSpeedUefiVar;
  UINTN VarSize;
  UINTN ClockId;
  FNC_ENTER_MSG ();

  // not needed for Sdm660 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass InitSSUSBPhy");
    goto ON_EXIT;
  }

  if (UsbCore->BaseAddr != USB30_PRIM_BASE) {
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  //Disable QMP PIPE3 clock branch: turn on the QMP PIPE3 clock output to the controller while the PHY is in 
  //the reset state (prior to releasing PHY_START and PHY_SW_RESET) since this clock also comes back to the 
  //PHY and needs to be sourced from the PHY pipe clock output when the PHY starts up.
  HAL_USB_AND(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_PIPE_CBCR_OFFS, ~(UINT32)HWIO_GCC_USB3_PHY_PIPE_CBCR_CLK_ENABLE_BMSK);

  // Reset the PHY block
  HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_BCR_OFFS, HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK);
  HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_BCR_OFFS, HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK);
  gBS->Stall (100);
  HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_BCR_OFFS, ~HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK);
  HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_BCR_OFFS, ~HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK);
  gBS->Stall (100);

  //Enable QMP PIPE3 clock branch
  HAL_USB_OR(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_PIPE_CBCR_OFFS, HWIO_GCC_USB3_PHY_PIPE_CBCR_CLK_ENABLE_BMSK);

  if(!usb_shared_ss_phy_init(UsbCore->LaneNum)) {
	  DBG(EFI_D_ERROR, "Init SSUSBPhy Enable Error");
	  Status = EFI_DEVICE_ERROR; 
	  goto ON_EXIT;
  }

  //On success, set UFN max speed to SS
  MaxSpeedUefiVar = HWIO_DCFG_DEVSPD_SUPERSPEED_FVAL;

  Status = ClockProtocol->GetClockID (ClockProtocol, "gcc_usb3_phy_pipe_clk", &ClockId);
  WRN_CHK ("failed get clock ID for gcc_usb3_phy_pipe_clk");
  
  if (!EFI_ERROR (Status))
  {
    // Select Source as QMP Phy for gcc_usb3_phy_pipe_clk
    Status = ClockProtocol->SelectExternalSource(ClockProtocol, 
                                                 ClockId, 
                                                 USB3_PIPE_CLK_MIN_FREQ_HZ, 
                                                 0x0,
                                                 0,
                                                 0,
                                                 0,
                                                 0);
    WRN_CHK ("failed to set source as QMP Phy for gcc_usb3_phy_pipe_clk");
  }
  gBS->Stall (100);

ON_EXIT:
  //Set the maximum speed supported by controller
  VarSize = sizeof(MaxSpeedUefiVar);
  gRT->SetVariable (L"UsbfnMaxSpeed", &gQcomTokenSpaceGuid,
                             EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                             VarSize, &MaxSpeedUefiVar);

  FNC_LEAVE_MSG ();
  return Status;
}


 /**
  Refer UsbConfigUsbCoresPrivate.h for the header description
 **/
STATIC
EFI_STATUS
Usb30InitCommon (
  IN  QCOM_USB_CORE_INTERFACE         *This,
  IN  BOOLEAN                          ResetUsbOnly
  )
{
  EFI_STATUS     Status   =  EFI_SUCCESS;
  BOOLEAN        bSsPhyFailed = FALSE;
  UINTN          BaseAddr;
  QCOM_USB_CORE  *UsbCore;

  FNC_ENTER_MSG ();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  if (!ClockProtocol) goto ON_EXIT;

  UsbCore = USB_CORE_FROM_IFC(This);
  
  BaseAddr = UsbCore->BaseAddr;

  if (!ResetUsbOnly) {
    // Init Dal Lib
    DALSYS_InitMod(NULL);
	
    //Turn on power rails
    if (UsbCore->CoreType == USB_CONFIG_SSUSB1)
    {
      if (NULL != gPmicNpaClientSS1)
      {
        npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_USB_PERPH_ACTIVE);   //Sends the request to RPM, no return
        DBG(EFI_D_INFO, "NPA Request to set SS1 PMIC_NPA_MODE_ID_USB_PERPH_ACTIVE");
      }
      else {
      Status = EFI_INVALID_PARAMETER;
      WRN_CHK("USB NPA SS1 Client unavailable.Aborting");
      }
    }

    //Enable USB power domain
    ConfigPowerDomain(TRUE, USB30_PowerDomain );

    if (UsbCore->CoreType == USB_CONFIG_SSUSB1)
    {
      //Vote for SNOC @ 200Mhz for both cores
      if (gNpaClientSS1Snoc) {
        npa_issue_required_request(gNpaClientSS1Snoc, 200000);
      }
      else {
        DBG (EFI_D_ERROR, "gNpaClientSS1Snoc is NULL)");
      }

      //Vote for aggr1 for primary @ 200Mhz
      if (gNpaClientAggre1) {
        npa_issue_required_request(gNpaClientAggre1, 200000);
      }
      else {
        DBG (EFI_D_ERROR, "gNpaClientSS1Snoc is NULL");
      }
    }

    if (0 == UsbCore->ClkRefCnt) {
      // Enable clocks first, without that disable clocks does not work
      Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
      WRN_CHK ("failed to initialize USB clocks");
    }

    // Disable clocks for super speed controller
    Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
    WRN_CHK ("failed to disable USB clocks");

    // Disable clocks for super speed controller
    Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
    WRN_CHK ("failed to disable USB clocks");

    // Enable clocks for super speed controller
    Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
    ERR_CHK ("failed to initialize USB clocks");
	
    //Increment reference count
    UsbCore->ClkRefCnt++;
  }

  /*3. 
    To avoid ambiguity in the initial state, put the core in power collapse, then bring the core out of power collapse
    Applies to primary core only
  */
  HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB_30_GDSCR_OFFS, HWIO_GCC_USB_30_GDSCR_SW_COLLAPSE_BMSK);
  gBS->Stall (100);
  HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB_30_GDSCR_OFFS, ~HWIO_GCC_USB_30_GDSCR_SW_COLLAPSE_BMSK);
  gBS->Stall (100);
  
  // Hard Reset the USB Link and PHYs using GCC control
  SynopsysGccReset (UsbCore);

  //GCC_USB_SS_PHY_LDO_EN is enabled by default

  //Write 0x11 to the AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG 
  //to enable one-wait-state writes and reads prior to writing or reading the QMP USB3 PHY CSRs.
  HAL_USB_WRITE (PERIPH_SS_AHB2PHY_WEST_BASE, HWIO_PERIPH_SS_AHB2PHY_TOP_CFG_OFFS, 0x11);

  Status = InitHSUSBPhy(UsbCore->CoreType, BaseAddr);
  WRN_CHK("InitHSUSBPhy failed: 0x%08x", Status);

  // Dont enable the SS USB Phy for the high speed only configuration
  if (!FeaturePcdGet(HighSpeedOnlySupported))
  {
    Status = InitSSUSBPhy(UsbCore);
    if (Status != EFI_SUCCESS)
    {
      bSsPhyFailed = TRUE;
      DBG( EFI_D_WARN, "InitSSUSBPhy failed: 0x%08x. Falling back to HS PHY only", Status);
      Status = EFI_SUCCESS;
    }
  }

  /*
     11. HS only: if operating without the SS PHY, follow this sequence to disable the pipe clock requirement.
    a. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x1
    b. Wait 1 µs.
    c. usb30_reg_general_cfg[PIPE_UTMI_CLK_SEL] = 0x1
    d. usb30_reg_general_cfg [PIPE3_PHYSTATUS_SW] = 0x1
    e. Wait 1 µs.
    f. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x0
    In this case, program the software to skip all SuperSpeed configurations in 
    the link controller and PHY, otherwise the core could get stuck.
  */
  if ((((UsbCore->CoreType == USB_CONFIG_SSUSB1) && bSsPhyFailed)) || (FeaturePcdGet(HighSpeedOnlySupported)))
  {
    DBG( EFI_D_INFO, "Disabling SS PHY");
    HAL_USB_OR (BaseAddr, HWIO_GENERAL_CFG_ADDR(USB30_QSCRATCH_REG_BASE_OFFS), HWIO_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_OR (BaseAddr, HWIO_GENERAL_CFG_ADDR(USB30_QSCRATCH_REG_BASE_OFFS), HWIO_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK);
    HAL_USB_OR (BaseAddr, HWIO_GENERAL_CFG_ADDR(USB30_QSCRATCH_REG_BASE_OFFS), HWIO_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK);
    //When PIPE3_PHYSTATUS is high, Setting the PIPE3_SET_PHYSTATUS_SW bit will assert the PIPE_PHYSTATUS controller input 
    //So clear PHY status here 
    HAL_USB_AND (BaseAddr, HWIO_GENERAL_CFG_ADDR(USB30_QSCRATCH_REG_BASE_OFFS), ~HWIO_GENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_AND (BaseAddr, HWIO_GENERAL_CFG_ADDR(USB30_QSCRATCH_REG_BASE_OFFS), ~HWIO_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK);
  }
  else
  {
    /* Set DELAYP1TRANS to 0 */
    HAL_USB_AND (BaseAddr, HWIO_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(BaseAddr, 0), ~HWIO_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_BMSK);
  }

  /*
    15. To save power, enable the hardware-based clock gating (not relevant for PBL):
    a. usb30_reg_cgctl[DBM_FSM_EN] = 0x1
  */
  HAL_USB_OR (BaseAddr, HWIO_CGCTL_REG_OFFS, HWIO_CGCTL_REG_DBM_FSM_EN_BMSK);
  
  
ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitCommon


/* Refer UsbConfigUsbCores.h for the header description*/
STATIC
EFI_STATUS
SynopsysInitHostConfig (
  IN  QCOM_USB_CORE         *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }
  
  BaseAddr = UsbCore->BaseAddr;
  
  //2. Set usb30_reg_gctl:[PRTCAPDIR] = 0x1 (host), [U2EXIT_LFPS] = 0x1
  HAL_USB_AND(BaseAddr,HWIO_GCTL_OFFS,~HWIO_GCTL_PRTCAPDIR_BMSK);
  HAL_USB_OR (BaseAddr, HWIO_GCTL_OFFS, HWIO_GCTL_U2EXIT_LFPS_BMSK | ( (1 << HWIO_GCTL_PRTCAPDIR_SHFT)) );

  //3. Enable the wake on connect event for the port:
  HAL_USB_OR (BaseAddr, HWIO_PORTSC_20_REGS_p_PORTSC_20_ADDR(0,0), HWIO_PORTSC_20_REGS_p_PORTSC_20_WCE_BMSK );
  HAL_USB_OR (BaseAddr, HWIO_PORTSC_30_REGS_p_PORTSC_30_ADDR(0,0), HWIO_PORTSC_30_REGS_p_PORTSC_30_WCE_BMSK );

  //4. Set GRXTHRCFG based on the case 8000615753 values
  HAL_USB_OR (BaseAddr, HWIO_GRXTHRCFG_ADDR(0),  (3 << HWIO_GRXTHRCFG_USBMAXRXBURSTSIZE_SHFT) |
  (3 << HWIO_GRXTHRCFG_USBRXPKTCNT_SHFT) | HWIO_GRXTHRCFG_USBRXPKTCNTSEL_BMSK);

  //5. Set the bus configuration 1K page pipe limit:
  //TODO:CK:HWIO_GSBUSCFG1_DESADRSPC_BMSK & HWIO_GSBUSCFG1_DATADRSPC_BMSK is not defined.

  //HAL_USB_AND(BaseAddr, HWIO_GSBUSCFG1_ADDR(0), ~HWIO_GSBUSCFG1_DESADRSPC_BMSK | ~HWIO_GSBUSCFG1_DATADRSPC_BMSK );
  HAL_USB_OR(BaseAddr, HWIO_GSBUSCFG1_ADDR(0), (0xE << HWIO_GSBUSCFG1_PIPETRANSLIMIT_SHFT) | HWIO_GSBUSCFG1_EN1KPAGE_BMSK );

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitHost



/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
**/
STATIC
EFI_STATUS
Usb30InitHost (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameters");
  }

  UsbCore = USB_CORE_FROM_IFC(This);
  
  /*if (UsbCore->CoreType == USB_CONFIG_SSUSB1) {
    Status = EnableVbusSS1();
    ERR_CHK("Failed to initialize VbusSS1");
  }*/

  Status = SynopsysInitHostConfig(UsbCore);
  
ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}



/**
  Performs device mode specific initialization on a Synopsys super speed USB core.

  @param [in]  UsbCore      The USB core instance

  @retval EFI_SUCCESS       USB core successfully initialized
  @retval EFI_UNSUPPORTED   USB core not supported
  @retval Others            Error encountered initializing USB core
**/
STATIC
EFI_STATUS
SynopsysInitDevice (
  IN  QCOM_USB_CORE         *UsbCore
  )
{

  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  BaseAddr = UsbCore->BaseAddr;
  USB_ASSERT_GOTO ((BaseAddr != 0), ON_EXIT);

  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    // Reset Device Core.
    HAL_USB_OR(BaseAddr, HWIO_DCTL_OFFS, HWIO_DCTL_CSFTRST_BMSK);
    while (HAL_USB_READ(BaseAddr, HWIO_DCTL_OFFS) & HWIO_DCTL_CSFTRST_BMSK) { ; }
    InitHSUSBPhy(UsbCore->CoreType, BaseAddr);
    goto ON_EXIT;
  }

  /*
    16. Enable the hardware LPM:
    usb30_reg_gusb2phycfg_regs_p_gusb2phycfg[ENBLSLPM] = 0x1
  */
  HAL_USB_OR( BaseAddr, HWIO_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS(BaseAddr, 0), HWIO_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);
  
ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
**/
STATIC
EFI_STATUS
Usb30InitDevicePrimary (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  Status = SynopsysInitDevice(UsbCore);

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
STATIC
EFI_STATUS
Usb30EnterLpm (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  // not needed for Sdm660 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass SynopsysPrimEnterLpm");
    goto ON_EXIT;
  }

  if (!UsbCore->IsCoreInLPM)
  {
    // Reference Count 0 implies that we have not enabled clocks
    if (UsbCore->ClkRefCnt == 0)
    {
      // Enable clocks first, without that disable clocks doesn't work
      Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
      WRN_CHK ("failed to enable USB clocks");
      // Increment reference count
      UsbCore->ClkRefCnt++;
    }
    
    //Assert controller & PHYs resets
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB_30_BCR_OFFS, HWIO_GCC_USB_30_BCR_BLK_ARES_BMSK);
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_BCR_OFFS, HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK);
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_BCR_OFFS, HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK);

    Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
    WRN_CHK ("failed to disable USB clocks");

    // Disable USB Foot Switch (Power domain)
    ConfigPowerDomain(FALSE, USB30_PowerDomain );

    //  Enable SW PowerCollapse for USB30 Controller
    HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB_30_GDSCR_OFFS, HWIO_GCC_USB_30_GDSCR_SW_COLLAPSE_BMSK);

    if (NULL != gPmicNpaClientSS1) 
    {
      npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_USB_PERPH_SUSPEND);   //Sends the request to RPM, no return
      DBG(EFI_D_INFO, "SynopsysPrimEnterLpm : NPA Request to set PMIC_NPA_MODE_ID_USB_PERPH_SUSPEND");
    }

    //Remove bus votes
    if (gNpaClientSS1Snoc)
    {
      npa_issue_required_request(gNpaClientSS1Snoc, 0);
    }
    if( gNpaClientAggre1)
    {
      npa_issue_required_request(gNpaClientAggre1, 0);
    }

    // Decrement reference count
    UsbCore->ClkRefCnt--;
    UsbCore->IsCoreInLPM = TRUE;

    // Unknown Reference Count, Faulty scenario
    if (UsbCore->ClkRefCnt > 1)
    {
      WRN_CHK ("SynopsysPrimEnterLPM: Wrong clock Reference count= 0x%x", UsbCore->ClkRefCnt);
    }
  }
  else
  {
    WRN_CHK ("SynopsysPrimEnterLPM: Synopsys Core already in LPM");
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
STATIC
EFI_STATUS
Usb30ExitLpm (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  // not needed for Sdm660 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass SynopsysExitLpm");
    goto ON_EXIT;
  }

  // Perform GCC reset for controller and PHYs
  SynopsysGccReset (UsbCore);

ON_EXIT:
  FNC_LEAVE_MSG();
  return EFI_SUCCESS;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
EFI_STATUS
Usb30Reset (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30SetPhyLane(
  IN QCOM_USB_CORE_INTERFACE           *This,
  IN UINT8                              LaneNum
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  UsbCore->LaneNum = LaneNum;

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30GetBaseAddr(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  OUT  UINTN                             *BaseAddr
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This || !BaseAddr) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  *BaseAddr = UsbCore->BaseAddr;

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30ResetSSPhy(
  IN   QCOM_USB_CORE_INTERFACE           *This
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  InitSSUSBPhy(UsbCore);

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30SetPhyNonDrivingMode(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  IN   BOOLEAN                            NonDrivingMode
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;
  uint32 enable_fs_xvr = 0x0;
  UINTN BaseAddr;

  FNC_ENTER_MSG();
  
  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);
  
  BaseAddr = UsbCore->BaseAddr;

  // power off the PHY for high-z
  if (NonDrivingMode)
  {

	//Disable the D+ Pull down
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
	  PERIPH_SS_AHB2PHY_WEST_BASE,
	  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DPPULLDOWN_BMSK,
      (0x0 <<HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DPPULLDOWN_SHFT));

    // Disable the D- Pull down
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
	  PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DMPULLDOWN_BMSK,
      (0x0 <<HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DMPULLDOWN_SHFT));
	
	// Select the FS transceiver and put into non-drive mode
    // Putting phy to suspend as SUSPEND_N = 0 (power on default)
    enable_fs_xvr = (QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_EN
                     | QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_FS
                     | QUSB2PHY_PORT_UTMI_CTRL1_OP_NON_MODE);

    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OUT(PERIPH_SS_AHB2PHY_WEST_BASE, enable_fs_xvr);
	
    // Enable UTMI_TEST_MUX_SEL
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
	  PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_BMSK,
      0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_SHFT);

    usb_shared_delay_us(10);

	// Keep PHY in power down
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_POWERDOWN_OUTM(
	PERIPH_SS_AHB2PHY_WEST_BASE,
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_BMSK,
    (0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_SHFT));

  }
  else
  {
    // in order to put the phy back to the NORMAL mode, we have to re-init the HS phy.
    InitHSUSBPhy(UsbCore->CoreType, BaseAddr);
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30InitHSUSBPhyKeepPwrDwn (
  IN QCOM_USB_CORE_INTERFACE           *This
  )
{
  EFI_STATUS                    Status = EFI_INVALID_PARAMETER;

  FNC_ENTER_MSG ();

  ERR_CHK("NOT EXPECTED TO REACH HERE IN STARLORD: %r", Status);
  /*
  // SDM660 RUMI PHY init sequence.
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    UINT32 Calibration = 0x1A0;
    UINT32 Clkfreq = 0;
    UINT32 SeBits = HAL_SSUSB_SNPS_R3PC_DCM_CMD_RESET;
  */

    /* Emulation initialization */
    /*//d.s (hs2Addr+0x04)  %LE %Long 0x7F
    HAL_USB_WRITE(HS2ADDR, 0x04, 0x7F);
    //d.s (hs2Addr+0x04)  %LE %Long 0x00
    HAL_USB_WRITE(HS2ADDR, 0x04, 0x00);
    //d.s (hs2Addr+0x28)  %LE %Long 0x3FF
    HAL_USB_WRITE(HS2ADDR, 0x28, 0x3FF);
    //d.s (hs2Addr+0x2C)  %LE %Long 0x1F
    HAL_USB_WRITE(HS2ADDR, 0x2C, 0x1F);
	*/

    /* Initialization code for QRBTC Rev2*/
    /*d.s QRBTC_USB2_PLL %long 0x00000019    //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
    d.s QRBTC_USB2_PLLCTRL2 %long 0x00000020 //[5,14]HWIO_USB2_PLLCTRL2_ADDR
    d.s QRBTC_USB2_PLLCTRL1 %long 0x00000079 //[4,10]HWIO_USB2_PLLCTRL1_ADDR
    d.s QRBTC_USB2_PLLCTRL3 %long 0x00000000 //[6,18]HWIO_USB2_PLLCTRL3_ADDR
    d.s QRBTC_USB2_PLL %long 0x00000099      //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
    d.s QRTBC_USB2_PLLTEST1 %long 0x00000004 //[2,8]HWIO_USB2_PLLTEST1_ADDR
    d.s QRBTC_USB2_PLL %long 0x000000D9      //[1,4]HWIO_QRBTC_USB2_PLL_ADDR*/

    /*HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLL_OFF, 0x00000019);        //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLLCTRL2_OFF, 0x00000020);   //[5,14]HWIO_USB2_PLLCTRL2_ADDR
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLLCTRL1_OFF, 0x00000079);   //[4,10]HWIO_USB2_PLLCTRL1_ADDR
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLLCTRL3_OFF, 0x00000000);   //[6,18]HWIO_USB2_PLLCTRL3_ADDR
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLL_OFF, 0x00000099);        //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
    HAL_USB_WRITE(QRBTC_BASE, QRTBC_USB2_PLLTEST1_OFF, 0x00000004);   //[2,8]HWIO_USB2_PLLTEST1_ADDR
    HAL_USB_WRITE(QRBTC_BASE, QRBTC_USB2_PLL_OFF, 0x000000D9);        //[1,4]HWIO_QRBTC_USB2_PLL_ADDR
	*/

    /* DCM reset */
    /*HAL_USB_WRITE(HS2ADDR, 0x20, SeBits);
    HAL_USB_WRITE(HS2ADDR, 0x20, 0);
    //shift the DCM
    HAL_USB_WRITE(HS2ADDR, 0x20, Calibration);
    HAL_USB_WRITE(HS2ADDR, 0x14, 5);
    Clkfreq = HAL_USB_READ(HS2ADDR, 0x10);
    gBS->Stall(100);
  }

  if ((PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_RUMI)   &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    //Hard reset PHY
    HAL_USB_OR(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    gBS->Stall(100);
    HAL_USB_AND(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_QUSB2PHY_PRIM_BCR_OFFS, ~HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK);
    gBS->Stall(100);

    DBG(EFI_D_INFO, "Device Mode HS Phy Init");

    // Keep Port Power Down
    HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PORT_POWERDOWN_OUTM(
		PERIPH_SS_AHB2PHY_WEST_BASE, HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_BMSK,
		0x1 << HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_SHFT);
    gBS->Stall(100);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_ANALOG_CONTROLS_TWO_OFFS,
      0x13);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_CLOCK_INVERTERS_OFFS,
      0x7C);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_CMODE_OFFS,
      0x80);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PLL_PLL_LOCK_DELAY_OFFS,
      0x0A);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_WEST_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_TUNE2_OFFS,
      0x00);
  }*/
  
ON_EXIT:
  FNC_LEAVE_MSG ();
  return EFI_SUCCESS;
}

/* Refer to UsbConfigUsbCoresPublic.h for header description*/
EFI_STATUS
UsbConfigCoresInit(
  IN  UINTN                      CoreNum,
  OUT QCOM_USB_CORE_INTERFACE  **UsbCoreInterface
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!UsbCoreInterface) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("Invalid Parameters: CoreNum %d, UsbCore %p", CoreNum, UsbCoreInterface);
  }

  UsbCore = AllocateZeroPool(sizeof(QCOM_USB_CORE));

  if (!UsbCore) {
    Status = EFI_OUT_OF_RESOURCES;
    ERR_CHK("Out of Resources");
  }

  if (CoreNum == USB_CORE_0_SDM_660) {
    UsbCore->CoreInterface.InitCommon = Usb30InitCommon;
    UsbCore->CoreInterface.InitDevice = Usb30InitDevicePrimary;
    UsbCore->CoreInterface.InitHost = Usb30InitHost;
    UsbCore->CoreInterface.Reset = Usb30Reset;
    UsbCore->CoreInterface.CoreEnterLPM = Usb30EnterLpm;
    UsbCore->CoreInterface.CoreExitLPM = Usb30ExitLpm;
    UsbCore->CoreInterface.SetPhyLane = Usb30SetPhyLane;
    UsbCore->CoreInterface.GetBaseAddress = Usb30GetBaseAddr;
    UsbCore->CoreInterface.ResetSSPhy = Usb30ResetSSPhy;
    UsbCore->CoreInterface.SetNonDrivingMode = Usb30SetPhyNonDrivingMode;
    UsbCore->CoreInterface.InitHsPhyPwrDwn = Usb30InitHSUSBPhyKeepPwrDwn;

    *UsbCoreInterface = &UsbCore->CoreInterface;

    UsbCore->CoreType = USB_CONFIG_SSUSB1;
    UsbCore->BaseAddr = USB30_PRIM_BASE;
    UsbCore->EnClockCount = sizeof(Usb30EnCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->EnClocks = Usb30EnCoreClocks;
    UsbCore->DisClockCount = sizeof(Usb30DisCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->DisClocks = Usb30DisCoreClocks;
    UsbCore->ClkRefCnt = 0;
    UsbCore->IsCoreInLPM = FALSE;
    UsbCore->LaneNum = 0;

    Status = UsbConfigLibOpenProtocols();
    ERR_CHK("UsbConfigLibOpenProtocols failed %r",Status);
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer to UsbConfigUsbCoresPublic.h for header description*/
EFI_STATUS
UsbConfigCoresDeinit(
  IN QCOM_USB_CORE_INTERFACE  *UsbCoreInterface
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!UsbCoreInterface) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("Invalid Parameters: CoreNum %d, UsbCore %p", UsbCoreInterface);
  }

  UsbCore = USB_CORE_FROM_IFC(UsbCoreInterface);

  if (UsbCore)
    FreePool(UsbCore);

ON_EXIT:
  return Status;
}
