/*==================================================================
 *
 * FILE:        deviceprogrammer_initialize.c
 *
 * DESCRIPTION:
 *
 *
 *        Copyright (c) 2008-2015,2017 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 2017-02-28   sb      Enable crypto BAM.
 * 2015-07-10   wek     Move a variable out of the stack to enable VIP.
 * 2015-05-18   wek     Change header file inclusion.
 * 2015-03-26   wek     Test DDR if fails use Lite buffers to communicate.
 * 2014-12-02   wek     8996/XBL Compilation.
 * 2014-10-02   ah      Major code clean up
 * 2013-06-03   ah      Added legal header
 * 2013-05-31   ab      Initial checkin
 */

//LOCALE_remove_comment_when_ready#include <locale.h>
#include "deviceprogrammer_utils.h"
#include "deviceprogrammer_initialize.h"
#include "boot_msm.h"
#include "ClockBoot.h"
#include "pm.h"
#include "SpmiBus.h"
#include "SpmiCfg.h"
#include "ddr_drivers.h"
#include "deviceprogrammer_firehose.h"
#include "deviceprogrammer_security.h"
#include "deviceprogrammer_bsp.h"
#include "deviceprogrammer_storage.h"

#include "pm_rgb.h"

extern void main_firehose(void);
//Clock_remove_comment_when_readyextern boolean Clock_PreDDRInitEx(uint32 ddr_type);

extern firehose_protocol_t fh;

boot_pbl_shared_data_type *pbl_shared_global;

// This variable is only used in deviceprogrammer_init_hw, it could be
// declared in the stack, but the stack is very small, therefore declare
// this outside of the stack to create extra space for other things
// For example authentication of images that allocate 2K in the stack.
static char err_log[128] = {0};

// NOTE: Storage device is initialized later when handling <configure> tag,
// since it specifies which storage device to use
static void deviceprogrammer_init_hw()
{
    int i;
    memset (err_log, 0, sizeof(err_log));

#ifndef FEATURE_FIREHOSE_SKIP_CLOCK
#ifndef FEATURE_BOOT_EXTERN_DEVICEPROGRAMMER_DDR_COMPLETED
    // This needs to be called before calling Clock_Init()
    if (TRUE != Clock_PreDDRInitEx(DDR_TYPE_LPDDR2))                     { strlcat(err_log, "Clock_PreDDRInitEx(DDR_TYPE_LPDDR2) clock pre ddr:fail ", sizeof(err_log)); }
#endif
    // Lower clocks for HW init
    if (FALSE == Clock_Init(CLOCK_BOOT_PERF_MIN, CLOCK_BOOT_PERF_MIN)) { strlcat(err_log, "init clock:fail ", sizeof(err_log)); }
#endif

    // Call setlocale to set the locale to the default values
    // for string functions such as strncasecmp to work properly
//LOCALE_remove_comment_when_ready    setlocale(LC_ALL, "C");

    if (SPMI_CFG_SUCCESS != SpmiCfg_Init(TRUE))                        { strlcat(err_log, "init spmi_cfg:fail ", sizeof(err_log)); }
    delaySeconds(1);
    if (SPMI_BUS_SUCCESS != SpmiBus_Init())                            { strlcat(err_log, "init spmi_bus:fail ", sizeof(err_log)); }
//    if (PM_ERR_FLAG__SUCCESS != pm_pon_wdog_enable(
//                                    0,
//                                    PM_OFF))                           { strlcat(err_log, "init wdog:fail ", sizeof(err_log)); }

    
    
// This variable is in SCONS environment, i.e. b8994.cmd deviceprogrammer DEVICEPROGRAMMER_VIP_MODE=1
#if DEVICEPROGRAMMER_VIP_MODE == 1
    fh.validation_enabled = TRUE;
#else
    fh.validation_enabled = FALSE;  // By default we don't use VIP
#endif

// This variable is *not* in SCONS environment - Intentionally making this a MANUAL EFFORT to NOT USE VIP
// Any OEM is free to disable this
#ifndef SKIP_SECBOOT_CHECK_NOT_RECOMMENDED_BY_QUALCOMM
    // This check below is to ensure that only VIP programmer is run on secure boot devices
    // In otherwords, signing the non VIP programmer is highly not recommended
    if( isSecureBootEnabled()==TRUE )
    {
        // To be here means Secure Boot Fuses are blown, therefore must use VIP
        fh.validation_enabled = TRUE;
    }
#endif


    // These PMIC calls were added to have long key power off to be
    // working from flash programmer so that device can be powered off in
    // factory for devices that do not have removable battery
    pm_pon_reset_source_cfg(0,PM_PON_RESET_SOURCE_KPDPWR,904,500,
    PM_PON_RESET_CFG_NORMAL_SHUTDOWN);
    pm_pon_reset_source_ctl(0, PM_PON_RESET_SOURCE_KPDPWR,PM_ON);

    initFirehoseTransport();    // Initialize USB transport

#ifndef FEATURE_FIREHOSE_SKIP_CLOCK
    // This calls the Clock API to bump up clocks. USB hangs if clock is not set to max.
    //
    // Before doing this, we need support for it in the Clock SCons
    // env.AddLibsToImage(['CLOCK_BOOT_DRIVER', 'EMMCBLD_IMAGE'],
    // ClockChipsetSBL_lib)
    // in file core\systemdrivers\clock\hw\msm8974\build\clock_sbl.scons
    if (FALSE == Clock_Init(CLOCK_BOOT_PERF_MAX, CLOCK_BOOT_PERF_MAX)) { strlcat(err_log, "Clock_Init(CLOCK_BOOT_PERF_MAX):fail ", sizeof(err_log)); }
#endif

    if (strlen((const char *)err_log) > 0) {
        for (i = 0; i < 20; i++) {
            logMessage(err_log);
            delaySeconds(2);
        }
        logMessage("Now resetting to EDL...");
        delaySeconds(2);
        bsp_target_reset_edl();
    }

    // Everything is wonderful, call main_firehose() next.
}

extern void crypto_bam_enable(void);
extern uint32 crypto_bam_check(void);
extern void boot_log_message(char *var);

// The entry point from SBL.
void deviceprogrammer_entry(boot_pbl_shared_data_type *pbl_shared)
{
    pbl_shared_global = pbl_shared;

    storage_device_init_hotplug();  // this just initializes hotplug library, not storage devices
    deviceprogrammer_zi_buffers ();
    initFirehoseProtocol(); // initializes default values for fh structure
    deviceprogrammer_init_hw();

#ifdef FEATURE_DEVICEPROGRAMMER_DDR
	uint32 res_bam;

    /* Enable crypto BAM post-DDR init */
    crypto_bam_enable();
    res_bam = crypto_bam_check();
    if (res_bam == 0)
      boot_log_message("Cryto Bam Disabled in DevPrg");
    else
      boot_log_message("Cryto Bam Enabled in DevPrg");
#endif

    main_firehose();
}
