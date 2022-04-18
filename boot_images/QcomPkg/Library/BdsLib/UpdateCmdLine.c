/** @file UpdateCmdLine.c
*  
* Copyright (c) 2014, 2016 Qualcomm Technologies, Inc. All rights reserved.
*
* Copyright (c) 2009, Google Inc.
* All rights reserved.
*
* Copyright (c) 2009-2013, The Linux Foundation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of The Linux Foundation nor
*       the names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior written
*       permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/13/16   jt      Change SdccCardInfo to MemCardInfo
 01/20/14   niting  Initial revision

=============================================================================*/
#include "UpdateCmdLine.h"
#include "BdsInternal.h"
#include <Library/PrintLib.h>
#include <Protocol/EFICardInfo.h>
#include <Protocol/Print2.h>

STATIC CHAR8 *emmc_cmdline = " androidboot.emmc=true";
STATIC CHAR8 *usb_sn_cmdline = " androidboot.serialno=";
STATIC CHAR8 *androidboot_mode = " androidboot.mode=";
STATIC CHAR8 *loglevel         = " earlyprintk";
STATIC CHAR8 *battchg_pause = " androidboot.mode=charger";
STATIC CHAR8 *auth_kernel = " androidboot.authorized_kernel=true";

STATIC CHAR8 *baseband_apq     = " androidboot.baseband=apq";
STATIC CHAR8 *baseband_msm     = " androidboot.baseband=msm";
STATIC CHAR8 *baseband_csfb    = " androidboot.baseband=csfb";
STATIC CHAR8 *baseband_svlte2a = " androidboot.baseband=svlte2a";
STATIC CHAR8 *baseband_mdm     = " androidboot.baseband=mdm";
STATIC CHAR8 *baseband_sglte   = " androidboot.baseband=sglte";
STATIC CHAR8 *baseband_dsda    = " androidboot.baseband=dsda";
STATIC CHAR8 *baseband_dsda2   = " androidboot.baseband=dsda2";
STATIC CHAR8 *baseband_sglte2  = " androidboot.baseband=sglte2";

//STATIC CHAR8 *display = " mdss_mdp.panel=1:dsi:0:qcom,mdss_dsi_toshiba_720p_video";
//STATIC CHAR8 *display = " mdss_mdp.panel=0:dsi:0:";
STATIC CHAR8 *display = " mdss_mdp.panel=0:dsi:0:qcom,mdss_dsi_toshiba_720p_video";

STATIC CHAR8 *watchdog = " msm_watchdog_v2.enable=0";

/*Function that returns value of boolean boot_into_ffbm
 *A condition at update_cmdline( ) function
 *Serves performance purpose only, hard-coded to return zero */
BOOLEAN get_ffbm(CHAR8 *ffbm, UINT32 size)
{
  return 0;
}


/*Function that returns whether the boot is emmc boot
 *Assumes always eMMC boot, hard-coded to return 1*/
INT32 target_is_emmc_boot(VOID)
{
  return 1;
}


/*Function that returns whether the kernel is signed
 *Currently assumed to be signed*/
BOOLEAN target_use_signed_kernel(VOID)
{
  return 1;
}


/*Determine correct androidboot.baseband to use
 *Currently assumed to always be MSM*/
UINT32 target_baseband()
{
  return BASEBAND_MSM;
}


/*Determines whether to pause for batter charge,
 *Serves only performance purposes, defaults to return zero*/
UINT32 target_pause_for_battery_charge(VOID)
{
	return 0;
}


/*Returns the length of a string*/
INT32 strlen(CONST CHAR8* cmdline)
{
  return AsciiStrLen(cmdline);
}


/*Update command line: appends boot information to the original commandline
 *that is taken from boot image header*/
UINT8 *update_cmdline(CONST CHAR8 * cmdline)
{
  EFI_STATUS                    Status;
	UINT32                        cmdline_len = 0;
	UINT32                        have_cmdline = 0;
	UINT32                        pause_at_bootup = 0;
  UINT8                        *cmdline_final = NULL;
	CHAR8                         ffbm[10];
	UINTN                         boot_into_ffbm = get_ffbm(ffbm, sizeof(ffbm));
  MEM_CARD_INFO                card_info;
  EFI_MEM_CARDINFO_PROTOCOL   *pCardInfoProtocol=NULL;


  /*Init MemCardInfoProtocol in order to get product serial number*/
  Status = gBS->LocateProtocol(&gEfiMemCardInfoProtocolGuid, NULL, (VOID**)&pCardInfoProtocol);
  if (EFI_ERROR(Status) || (&pCardInfoProtocol == NULL))
  {
    DEBUG((EFI_D_ERROR, "Locate EFI_CARD_INFO_Protocol failed, Status =  (0x%x)\r\n", Status));
  }

  Status = pCardInfoProtocol->GetCardInfo(pCardInfoProtocol,&card_info);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Get card info failed, Status =  (0x%x)\r\n", Status));
  }

  /*Init Print2Protocol in order to convert psn from a HEX to a string*/
  EFI_PRINT2_PROTOCOL          *pPrintProtocol;
  Status = gBS->LocateProtocol (&gEfiPrint2ProtocolGuid, NULL, (VOID**)&pPrintProtocol);
  if (EFI_ERROR(Status) || (&pPrintProtocol == NULL))
  {
    DEBUG((EFI_D_ERROR, "Locate Print2 Protocol failed, Status =  (0x%x)\r\n", Status));
  }

  CHAR8 sn_buf[20];

  UINTN ret = pPrintProtocol->AsciiValueToString (sn_buf,
                                                  RADIX_HEX,
                                                  card_info.product_serial_num,
                                                  8);//Product serial number always has width of 8 char
  
  if (cmdline && cmdline[0])
  {
    cmdline_len = strlen(cmdline);
    have_cmdline = 1;
  }

  if (target_is_emmc_boot()) 
  {
    cmdline_len += strlen(emmc_cmdline);
  }

  cmdline_len += strlen(usb_sn_cmdline);
  cmdline_len += strlen(sn_buf);

  if (boot_into_ffbm) 
  {
    cmdline_len += strlen(androidboot_mode);
    cmdline_len += strlen(ffbm);
    /* reduce kernel console messages to speed-up boot */
    cmdline_len += strlen(loglevel);
  } 
  else if (target_pause_for_battery_charge()) 
  {
    pause_at_bootup = 1;
    cmdline_len += strlen(battchg_pause);
  }

  if(target_use_signed_kernel() && auth_kernel_img) 
  {
    cmdline_len += strlen(auth_kernel);
  }

  /* Determine correct androidboot.baseband to use */
  switch(target_baseband())
  {
      case BASEBAND_APQ:
          cmdline_len += strlen(baseband_apq);
          break;

      case BASEBAND_MSM:
          cmdline_len += strlen(baseband_msm);
          break;

      case BASEBAND_CSFB:
          cmdline_len += strlen(baseband_csfb);
          break;

      case BASEBAND_SVLTE2A:
          cmdline_len += strlen(baseband_svlte2a);
          break;

      case BASEBAND_MDM:
          cmdline_len += strlen(baseband_mdm);
          break;

      case BASEBAND_SGLTE:
          cmdline_len += strlen(baseband_sglte);
          break;

      case BASEBAND_SGLTE2:
          cmdline_len += strlen(baseband_sglte2);
          break;

      case BASEBAND_DSDA:
          cmdline_len += strlen(baseband_dsda);
          break;

      case BASEBAND_DSDA2:
          cmdline_len += strlen(baseband_dsda2);
          break;
  }

  cmdline_len += strlen(display);

#define STR_COPY(dst,src)  {while (*src){*dst = *src; ++src; ++dst; } *dst = 0; ++dst;}
  if (cmdline_len > 0) 
  {
    CONST CHAR8 *src;
    
    UINT8* dst;
    dst = AllocatePool (cmdline_len + 4);
    //ASSERT(dst != NULL);

    /* Save start ptr for debug print */
    cmdline_final = dst;
    if (have_cmdline) 
    {
      src = cmdline;
      STR_COPY(dst,src);
    }
    if (target_is_emmc_boot()) 
    {
      src = emmc_cmdline;
      if (have_cmdline) --dst;
      have_cmdline = 1;
      STR_COPY(dst,src);
    }

    src = usb_sn_cmdline;
    if (have_cmdline) --dst;
    have_cmdline = 1;
    STR_COPY(dst,src);
    if (have_cmdline) --dst;
    have_cmdline = 1;
    src = sn_buf;
    STR_COPY(dst,src);

    src = loglevel;
    if (have_cmdline) --dst;
    STR_COPY(dst,src);

    if (boot_into_ffbm) {
      src = androidboot_mode;
      if (have_cmdline) --dst;
      STR_COPY(dst,src);
      src = ffbm;
      if (have_cmdline) --dst;
      STR_COPY(dst,src);
      src = loglevel;
      if (have_cmdline) --dst;
      STR_COPY(dst,src);
    } else if (pause_at_bootup) {
      src = battchg_pause;
      if (have_cmdline) --dst;
      STR_COPY(dst,src);
    }

    if(target_use_signed_kernel() && auth_kernel_img) 
    {
      src = auth_kernel;
      if (have_cmdline) --dst;
      STR_COPY(dst,src);
    }

    switch(target_baseband())
    {
      case BASEBAND_APQ:
        src = baseband_apq;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_MSM:
        src = baseband_msm;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_CSFB:
        src = baseband_csfb;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_SVLTE2A:
        src = baseband_svlte2a;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_MDM:
        src = baseband_mdm;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_SGLTE:
        src = baseband_sglte;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_SGLTE2:
        src = baseband_sglte2;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_DSDA:
        src = baseband_dsda;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;

      case BASEBAND_DSDA2:
        src = baseband_dsda2;
        if (have_cmdline) --dst;
        STR_COPY(dst,src);
        break;
    }

    src = display;
    if (have_cmdline) --dst;
    STR_COPY(dst,src);

    src = watchdog;
    if (have_cmdline) --dst;
    STR_COPY(dst,src);

  }

  extern VOID LogMsg (CHAR8*);

  LogMsg ((CHAR8*)cmdline_final);

  return cmdline_final;
}







