/** @file ChargerLibDisplay.c

  Helper functions for displaying images on screen

  Copyright (c) 2016, Qualcomm Technologies Inc. All rights reserved.

**/

/*===========================================================================

                        EDIT HISTORY

when        who     what, where, why
--------    ---     ---------------------------------------------------------
07/06/16    sm      Enabled all the APIs
                    Replaced RenderBGRTImage() with DrawBmpFile()
05/26/16    va      Update for Profile load and struct mis match
05/24/16    sm      Removed unused global variables.
01/27/16    sm      Initial revision
===========================================================================*/

/*===========================================================================
                     INCLUDE FILES
===========================================================================*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <Library/BMPLib.h>
#include "Library/SerialPortShLib.h"
#include <Library/QcomTargetLib.h>
#include <Library/FuseControlLib.h>
#include <api/systemdrivers/pmic/pm_uefi.h>
#include <api/systemdrivers/charger/ChargerLibCommon.h>

/**
  Protocol Dependencies
*/
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicFg.h>
#include <Protocol/EFIPmicVersion.h>
#include <Protocol/EFIPmicPwrOn.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFITsens.h>
#include <Protocol/EFIPmicRTC.h>

#include <Protocol/EFIDisplayPwr.h>
#include <Protocol/EFIDisplayPwrCtrl.h>
#include <Protocol/EFIClock.h>

#include <Protocol/GraphicsOutput.h>

#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ParserLib.h>
#include <Library/BaseMemoryLib.h>
#include <Guid/FileSystemInfo.h>
#include <Guid/FileInfo.h>
#include <api/systemdrivers/pmic/pm_uefi.h>

#include "DDIPlatformInfo.h"
#include <Protocol/SimpleFileSystem.h>

/*===========================================================================
                     TYPEDEF AND MACRO DEFINATIONS
===========================================================================*/
/*
This file will implement the functions to setup timer and implment the timer callback,
also it implement functions to register for key and LPM events and callback functions for key events and LPM events.
It also implement functions to turn display on/off, and render charging/battery images.
*/

#define CHARGER_BATTERY_SYMBOL_NOBATTERY            "fv1:\\battery_symbol_NoBattery.bmp"
#define CHARGER_BATTERY_SYMBOL_NOCHARGER            "fv1:\\battery_symbol_Nocharger.bmp"
#define CHARGER_BATTERY_SYMBOL_ABOVE_THRESHOLD      "fv1:\\battery_symbol_Soc10.bmp"
#define CHARGER_BATTERY_SYMBOL_LOWBATTERYCHARGING   "fv1:\\battery_symbol_LowBatteryCharging.bmp"
#define CHARGER_BATTERY_SYMBOL_LOWBATTERY           "fv1:\\battery_symbol_LowBattery.bmp"
#define CHARGER_TSENS_THERMAL_SYMBOL                "fv1:\\tsens_thermal_symbol.bmp"

#define ANIM_TIMER_DURATION           5000000 /*500 milli sec*/
#define SEVEN_SEC_WAIT                70000000 /*tick is 100ns; 100 * 70000000 = 7sec*/
#define SEVEN_SEC                     7
#define ENTER_LPM                     TRUE
#define EXIT_LPM                      FALSE

typedef enum _CHGAPP_DISP_ANIM_IMG{
  CHGAPP_DISP_ANIM_IMG_LOW_BATTERY,
  CHGAPP_DISP_ANIM_IMG_LOW_BATT_CHARGING,
  CHGAPP_DISP_ANIM_IMG_NUM_MAX = 0x7fffffff
} CHGAPP_DISP_ANIM_IMG_NUM;

/*===========================================================================
                     FUNCTIONS PROTOTYPES
===========================================================================*/
extern EFI_STATUS
LoadFromFV(IN   CHAR8 *Name,
           OUT  UINT8 **FileBuffer,
           OUT  UINTN *FileSize);

VOID EFIAPI DisplayOffTimer(IN EFI_EVENT Event, IN VOID *Context);
VOID EFIAPI ChargerLibEvent_AnimImgTimer(IN EFI_EVENT Event, IN VOID *Context);
STATIC EFI_STATUS ChargerLibEvent_RenderImage(char   *str);
STATIC EFI_STATUS ChargerLibEvent_ClearScreen( void );

/**
  Duplicates ASCII string

  @param  Source  Null Terminated string of characters
  @param  Length  source String length
  @return  Duplicated String  if successful otherwise return NULL

  note: Caller responsibility to Free returned String
**/
static CHAR8 * ChargerLibEvent_AsciiStrNDup(
  CONST CHAR8               *Source,
  UINTN                     Length
)
{
  CHAR8 *Dest = NULL;
  if(NULL == Source || 0 == Length)
    return NULL;

  Dest = AllocatePool (Length + 1);
  if (NULL == Dest)
  {
    return NULL;
  }

  AsciiStrnCpy(Dest, Source, Length + 1);

  return Dest;
}

/*===========================================================================
                     FUNCTION DEFINATIONS
===========================================================================*/
/* API to clear the display screen */
EFI_STATUS ChargerLibEvent_ClearScreen( void )
{
  EFI_STATUS                              Status = EFI_SUCCESS;
  STATIC EFI_GRAPHICS_OUTPUT_PROTOCOL    *pGfxProtocol = NULL;
  EFI_GUID                                sGfxOutputGUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION   *pModeInfo = NULL;
  UINTN                                   nModeInfoSize = 0;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           bgPixel = {0, 0, 0, 0};
  UINT32                                  mode = 0;

  if(!pGfxProtocol)
  {
    Status = gBS->LocateProtocol ( &sGfxOutputGUID,
                                   NULL,
                                   (VOID **)&pGfxProtocol);
  }

  if (EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_ERROR, "ChargerLib:: %a ChgAppClearScreen LocateProtocol(pGfxProtocol) failed. Status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  if (EFI_SUCCESS != (Status = pGfxProtocol->SetMode(pGfxProtocol, mode)))
  {
    DEBUG((EFI_D_ERROR, "ChargerLib:: %a ChgAppClearScreen SetMode() failed. Status = %r \r\n",__FUNCTION__, Status));
    return Status;
  }

  if (EFI_SUCCESS != (Status = pGfxProtocol->QueryMode(pGfxProtocol, 0, &nModeInfoSize, &pModeInfo)))
  {
    DEBUG((EFI_D_ERROR, "ChargerLib:: %a ChgAppClearScreen QueryMode() failed.Status = %r  \r\n",__FUNCTION__, Status));
    return Status;
  }

  /* Fill background as black */
  bgPixel.Blue     = 0x00;
  bgPixel.Green    = 0x00;
  bgPixel.Red      = 0x00;
  bgPixel.Reserved = 0x00;

  Status = pGfxProtocol->Blt( pGfxProtocol,
                              (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&bgPixel,
                              EfiBltVideoFill,
                              0, 0,
                              0, 0,
                              pModeInfo->HorizontalResolution,
                              pModeInfo->VerticalResolution,
                              0);

  if (EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_ERROR, "ChargerLib:: %a ChgAppClearScreen Blt(EfiBltVideoFill)  failed.Status = %r \r\n",__FUNCTION__, Status));
    return Status;
  }

  return Status;
}

EFI_STATUS ChargerLibEvent_RenderImage(char *str)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN  FileSizeFv = 0;
  UINT8  *FileBuffer = NULL;

  if(!str)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = LoadFromFV(str, &FileBuffer, &FileSizeFv);
  if (EFI_SUCCESS == Status)
  {
    Status = RenderBGRTImage(FileBuffer, (UINT32)FileSizeFv);
    if(EFI_SUCCESS != Status){
      DEBUG((EFI_D_ERROR, "ChargerLib:: %a Error from RenderBGRTImage Status = %r \r\n",__FUNCTION__, Status));
    }
  }
  else
  {
     DEBUG((EFI_D_ERROR, "ChargerLib:: %a Error from LoadFromFV Status = %r \r\n",__FUNCTION__, Status));
  }

  if (FileBuffer){
    FreePool(FileBuffer);
    FileBuffer = NULL;
  }

  return Status;
}

EFI_STATUS ChargerLibEvent_DispBattSymbol(CHARGERLIB_EVENT_DISP_IMAGE_TYPE DispImage, BOOLEAN ClearScreen)
{
  EFI_STATUS Status = EFI_SUCCESS;
  char   *str = NULL;

  switch (DispImage)
  {
  case CHARGERLIB_EVENT_DISP_IMAGE_ABOVE_THRESHOLD:
    str = ChargerLibEvent_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_ABOVE_THRESHOLD, AsciiStrLen(CHARGER_BATTERY_SYMBOL_ABOVE_THRESHOLD));
    break;
  case CHARGERLIB_EVENT_DISP_IMAGE_NOBATTERY:
    str = ChargerLibEvent_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_NOBATTERY, AsciiStrLen(CHARGER_BATTERY_SYMBOL_NOBATTERY));
    break;
  case CHARGERLIB_EVENT_DISP_IMAGE_NOCHARGER:
    str = ChargerLibEvent_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_NOCHARGER, AsciiStrLen(CHARGER_BATTERY_SYMBOL_NOCHARGER));
    break;
  case CHARGERLIB_EVENT_DISP_IMAGE_LOWBATTERYCHARGING:
    str = ChargerLibEvent_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_LOWBATTERYCHARGING, AsciiStrLen(CHARGER_BATTERY_SYMBOL_LOWBATTERYCHARGING));
    break;
  case CHARGERLIB_EVENT_DISP_IMAGE_LOWBATTERY:
    str = ChargerLibEvent_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_LOWBATTERY, AsciiStrLen(CHARGER_BATTERY_SYMBOL_LOWBATTERY));
    break;
  case CHARGERLIB_EVENT_DISP_IMAGE_TSENS_THERMAL_SYMBOL:
    str = ChargerLibEvent_AsciiStrNDup(CHARGER_TSENS_THERMAL_SYMBOL, AsciiStrLen(CHARGER_TSENS_THERMAL_SYMBOL));
    break;
  default:
    break;
  }

  /*Clear Screen when requested*/
  if(TRUE == ClearScreen)
  {
    if (EFI_SUCCESS != (Status = ChargerLibEvent_ClearScreen()))
    {
      DEBUG((EFI_D_ERROR, "ChargerLib:: %a ChgAppClearScreen() returned error = %r\n\r", __FUNCTION__,Status));
    }
    /* CHARGER_DEBUG((EFI_D_ERROR, "ChargerLib: ChargerLibEvent_DispBattSymbol ChgAppClearScreen Cleared: %d\n\r", Status)); */
  }

  /* Draw BMP image with default options, the screen will be cleared and the image
     will be drawn at the center of the screen*/
  Status = DrawBmpFile(str, NULL, 0);

  if(NULL != str )
  {
    FreePool(str);
    str = NULL;
  }

  return Status;
}

