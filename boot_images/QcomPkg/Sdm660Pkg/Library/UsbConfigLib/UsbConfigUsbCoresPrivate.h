/** @file \UsbConfigUsbCoresPrivate.h

  The private header file for UsbConfigUsbCore.c
  Copyright (c) 2016 QUALCOMM Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 11/30/16   ak       Porting from Boot.xf.1.2
 02/18/16   ck       Init Check-In
=============================================================================*/

#ifndef _USB_CONFIG_USB_CORES_PRIV_H_
#define _USB_CONFIG_USB_CORES_PRIV_H_

#include "UsbConfigUsbCoresPublic.h"
#include "comdef.h"
#include "qusb_dci_common.h"

#include <Protocol/EFIClock.h>

#include <Protocol/EFIPmicVreg.h>
#include <Protocol/EFIPmicMpp.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicClkBuff.h>

#include <Protocol/EFII2C.h>
#include <Protocol/EFITlmm.h>

#include <Protocol/EFIChipInfo.h>

#include <Library/IoLib.h>
#include "HALhwio.h"
#include "HalusbHWIO.h"

#include <Library/npa.h>
#include <Library/pmapp_npa.h>

#define QMP_PHY_MAX_RW_VERIFY_ATTEMPTS    1000

//
// USB Core Offset Wrappers
//
#define HAL_USB_READ(BaseAddr, RegAddr) \
  MmioRead32 ((BaseAddr) + (RegAddr))
#define HAL_USB_WRITE(BaseAddr, RegAddr, Data) \
  MmioWrite32 ((BaseAddr) + (RegAddr), Data)
#define HAL_USB_OR(BaseAddr, RegAddr, Data) \
  MmioOr32 ((BaseAddr) + (RegAddr), Data)
#define HAL_USB_AND(BaseAddr, RegAddr, Data) \
  MmioAnd32 ((BaseAddr) + (RegAddr), Data)
#define HAL_USB_OUTM(BaseAddr, RegAddr,Mask, Data) \
  MmioAndThenOr32 ((BaseAddr) + (RegAddr), (~Mask), Data)

//
// Max trial to cheick QMP PHY lock up.
//
#define QMP_PHY_MAX_RW_VERIFY_ATTEMPTS    1000

//
// Sdm660 RUMI USB HS PHY definition.
//
#define HS2ADDR (0x0A920000)
#define QRBTC_BASE (0x0A928000)

#undef HAL_SSUSB_SNPS_R3PC_DCM_CMD_RESET
#define HAL_SSUSB_SNPS_R3PC_DCM_CMD_RESET (0x1<<20)

#define QRBTC_USB2_PLL_OFF      0x1404
#define QRTBC_USB2_PLLTEST1_OFF 0x1408
#define QRBTC_USB2_PLLCTRL1_OFF 0x1410
#define QRBTC_USB2_PLLCTRL2_OFF 0x1414
#define QRBTC_USB2_PLLCTRL3_OFF 0x1418

//
// Get QCOM_USB_CORE from QCOM_USB_CORE_INTERFACE
// 
#define USB_CORE_FROM_IFC(Entry)    BASE_CR(Entry, QCOM_USB_CORE, CoreInterface)

//
// VSTATUS Bit Mask
//
#define VSEL_4_VSTS_PLL_LOCK_BMSK       0x1
#define VSEL_4_VSTS_AFE_CDR_DATAIN_BMSK 0x2
#define VSEL_4_VSTS_AFE_SQLT120_BMSK    0x4
#define VSEL_4_VSTS_CORE_SQUELCH_BMSK   0x8

/*******************************************************************************
 * USB core initialization functions for core structures
 ******************************************************************************/

/**
Performs initialization common to host and device mode on a Synopsys
super speed USB core.

@param [in]  This         The USB core interface instance
@param [in]  ResetUsbOnly If TRUE, only reset the USB link and PHY
                           If FALSE, in addition to the USB link and PHY reset
                           Enable clocks and power rails

@retval EFI_SUCCESS       USB core successfully initialized
@retval EFI_UNSUPPORTED   USB core not supported
@retval Others            Error encountered initializing USB core

@see QCOM_USB_CORE_INIT_COMMON
**/
STATIC
EFI_STATUS
Usb30InitCommon(
  IN  QCOM_USB_CORE_INTERFACE         *This,
  IN  BOOLEAN                          ResetUsbOnly
  );

/**
Performs host mode specific initialization on a Synopsys super speed USB core.

@param [in]  This         The USB core interface instance

@retval EFI_SUCCESS       USB core successfully initialized
@retval EFI_UNSUPPORTED   USB core not supported
@retval Others            Error encountered initializing USB core

@see QCOM_USB_CORE_INIT_HOST
**/
STATIC
EFI_STATUS
Usb30InitHost(
  IN  QCOM_USB_CORE_INTERFACE         *This
  );

/**
Performs device mode specific initialization on the primary Synopsys SuperSpeed
USB core.

@param [in]  This         The USB core interface instance

@retval EFI_SUCCESS       USB core successfully initialized
@retval EFI_UNSUPPORTED   USB core not supported
@retval Others            Error encountered initializing USB core

@see QCOM_USB_CORE_INIT_DEVICE
**/
STATIC
EFI_STATUS
Usb30InitDevicePrimary(
  IN  QCOM_USB_CORE_INTERFACE         *This
  );

/**
Perform a hardware reset on a Synopsys USB core.

@param [in]  This         The USB core interface instance

@retval EFI_SUCCESS       USB core successfully reset
@retval Others            Error encountered resetting USB core

@see QCOM_USB_CORE_RESET
**/
STATIC
EFI_STATUS
Usb30Reset(
  IN  QCOM_USB_CORE_INTERFACE         *This
  );

/**
Performs low power mode for the USB hardware
Disable USB clocks

@param [in]  This         The USB core interface instance

@retval EFI_SUCCESS       USB core successfully disabled USB SNPS Core clocks
@retval EFI_UNSUPPORTED   USB core not supported
@retval Others            Error encountered while disabling USB SNPS Core clocks

@see QCOM_USB_CORE_LPM
**/
STATIC
EFI_STATUS
Usb30EnterLpm(
  IN  QCOM_USB_CORE_INTERFACE         *This
  );

/**
Exits low power mode for the USB hardware

@param [in]  This         The USB core interface instance

@retval EFI_SUCCESS       The operation succeeded.
@retval Others            The operation failed.

@see QCOM_USB_CORE_LPM
**/
STATIC
EFI_STATUS
Usb30ExitLpm(
  IN  QCOM_USB_CORE_INTERFACE         *This
  );

/**
Set which CC line (CC1 or CC2) to be used for SS connection.

LaneNum 0 indicates that CC1 is used for USB.
LaneNum 1 indicates that CC2 is used for USB.

@param [in]  This         The USB core interface instance
@param [in]  CcStatus     CC out status

@retval EFI_SUCCESS       The operation succeeded.
@retval Others            The operation failed.
**/
STATIC
EFI_STATUS
Usb30SetPhyLane(
  IN QCOM_USB_CORE_INTERFACE           *This,
  IN UINT8                              LaneNum
  );

/**
Get the base address of the USB core

@param [in]  This         The USB core interface instance
@param [out] BaseAddr     The base address of the USB core

@retval EFI_SUCCESS       The operation succeeded.
@retval Others            The operation failed.

@see QCOM_USB_CORE_GET_BASE_ADDR

**/
STATIC
EFI_STATUS
Usb30GetBaseAddr(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  OUT  UINTN                             *BaseAddr
  );

/**
Reset SS USB PHY

@param [in]  This         The USB core interface instance

@retval EFI_SUCCESS       The operation succeeded.
@retval Others            The operation failed.

@see QCOM_USB_CORE_RESET_SS_USB_PHY

**/
STATIC
EFI_STATUS
Usb30ResetSSPhy(
  IN   QCOM_USB_CORE_INTERFACE           *This
  );

/**
Put the PHY in or out of the Non-driving mode

@param [in]  This           The USB core interface instance
@param [in]  NonDrivingMode TRUE  - Put the PHY in the Non-Driving mode
                            FALSE - Put the PHY out of the Non-Driving mode

@retval EFI_SUCCESS       The operation succeeded.
@retval Others            The operation failed.

**/
STATIC
EFI_STATUS
Usb30SetPhyNonDrivingMode(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  IN   BOOLEAN                            NonDrivingMode
  );
  
/**
Structure describing a clock supported by EfiClockProtocol. Clocks not
supported by this protocol (e.x. clocks enabled through PMIC interface)
must be handled separately. This structure is intended to be used as a
statically defined array of clocks per core.
**/
typedef struct QCOM_USB_CLOCK {
  CONST CHAR8                   *Name;
  CONST UINT32                  Frequency;
  CONST UINT32                  Divider;
} QCOM_USB_CLOCK;

/**
Structure encapsulating a USB core. Contains core specific initialization
function pointers and data. The function pointers defined in CoreInterface
are the only public interface which can be accessed outside the USB Core
module. No data outside this structure should be required
by the initialization functions.
**/
typedef struct _QCOM_USB_CORE {
  QCOM_USB_CORE_INTERFACE       CoreInterface;
  QCOM_USB_CONFIG_CORE_TYPE     CoreType;
  UINTN                         BaseAddr;
  UINTN                         EnClockCount;
  QCOM_USB_CLOCK                *EnClocks;
  UINTN                         DisClockCount;
  QCOM_USB_CLOCK                *DisClocks;
  UINTN                         ClkRefCnt;    // This reference count is not per clock and is only to keep tracks of enabling/disabling all USB clocks per core
  BOOLEAN                       IsCoreInLPM;
  UINTN                         LaneNum;
} QCOM_USB_CORE;

#endif /* _USB_CONFIG_USB_CORES_PRIV_H_ */
