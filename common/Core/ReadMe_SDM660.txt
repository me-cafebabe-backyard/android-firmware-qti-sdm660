//====================================================================================================//
//================================ Meta-Scripts ReadMe.txt ===========================================//
//====================================================================================================//
//
//  Name:                                                                     
//    ReadMe_MSM8996.txt 
//
//  Description:                                                              
//    Basic script intro ReadMe.txt
//                                                                            
// Copyright (c) 2012 - 2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.        
//
//
//
//
//                      EDIT HISTORY FOR FILE
//  This section contains comments describing changes made to the module.
//  Notice that changes are listed in reverse chronological order.
//
// when       who             what, where, why
// --------   ---             ---------------------------------------------------------
// 08/16/2016 JBILLING        VTLB notes added
// 08/12/2016 JBILLING        WLAN PD updates for T32 sim loader
// 04/15/2016 JBILLING        Initial release for 8998
// 03/10/2016 JBILLING        Created for 8998


This document describes the following:
    - Release notes, limitations, fixes, Lauterbach T32 approved versions.
    - Basic instructions for using features available for JTag on Qualcomm MSM chipsets.
    
Release Notes
    Date: 01/16/2017 
	Recommended T32 software
    T32 version (2016.07) S.2016.07.000075439
    T32 version (2016.12)
    
    
Existing limitations
    Some MTP devices may experience long reset due to PMIC reset script.
        This can cause scripts to not execute properly (whether build loading scripts or debug scripts)
        If you get a confusing error line during reset, enter command
            &STDRESETPMIC="FALSE"
        This will disable PMIC reset scripts. Side affect is that when reset occurs, PMIC will not be 
        put to reset state, resulting in strange pmic behavior. 
        Therefore, when resetting the device via scripts in this mode, 
        first power cycle the device and then run your scripts.
		
		Build loading working fine.
		MPSS/ADSP/CDSP/RPM debug working.
		XBL-Debug not working. Reason for this is doing hardreset in std_reset.
    
Release:

This document assumes the following:
    An up to date Lauterbach Trace32 license and (for live debugging) working JTag pod.
    Python 2.7 or later is installed and  available to system path
    MSM target is properly powered. In the case of using std_Debug scripts
    target has software and successfully boots to subsystem of choice.
    Trace32 is installed and computer is successfully connected to Trace32 pod
    Using Windows for computer OS.
    See chipset help pdf for further details
    
A note on T32 path
    All the scripts described are embedded into t32 path, so they do not require absolute accessing.
    I.E. a simple "do std_debug" will invoke the std_debug script. 
    It is not necessary to call it directly (i.e. "do common\std_debug.cmm" is not necessary)
    
Help menus
    Many of the scripts have help menus to describe functionality and usage. 
    These can be accessed in the following way
    do std_debug help
    do std_cti help
    do std_loadsim help
    do std_loadsyms_adsp help 
    do std_loadsyms_mpss help 
    do std_loadsyms_cdsp help 
    do std_loadsyms_rpm help 
    do std_loadsyms_wlan help
    
    
std_loadbuild
    This is primarily a GUI which allows loading the a build via JTag to the target.
    It has some other features such as individually swapping out images (such as tz or xbl based images)
    You can also set T32's paths for the different image builds here. Pressing the 'map' button
    will intercom to other open T32 windows to change their paths as well.
    Deviceprogrammer is for internal use only.
    
std_debug
    std_debug is a suite of scripts intended to facilitate JTag attach to the core of choice.
    There are two primary features within std_debug:
    std_debug boot up debug
        This is designed to get the user attached to desired subsystem with specified breakpoints and options.
        If 'main' is specified as breakpoint, the subsystem will halt at entry. Otherwise the subsystem
        will go immediately from main(), setting all error breakpoints, which preserves system sync
        This is offered through the primary GUI (obtained by typing 'do std_debug' in the APPS0 T32 window) or
        by command line (type 'do std_debug help' in the APPS0 T32 window for command line instructions)
        
        There is an option to enable JTag to be attached when SLPI is in island mode. This will keep on
        certain clocks (such as ddr, qdss) by voting for them from SLPI core software. If std_debug command line
        is invoked with extraoption=island_debug, then this variable will be set at main function of SLPI, resulting
        in island debug feature being enabled. Note that this is only available from command line at this time.
        e.g.: do std_debug Img=slpi Bkpts=some_brkpt extraoption=island_debug,silent
        
    hotattach menus
        These menus are present on most T32 windows and they offer live debug without needing to restart the system.
        Q6 based processors (ADSP,MPSS,SLPI) have functionality to wakeup, attach, set breakpoints, and start ETM tracing 
        without halting the processor
        APPS processors menus provide basic features to facilitate multicore debug. Entering commands in
        command area will apply desired command to all open Apps t32 windows (note that this GUI text box
        is simply an invocation of 'do std_apps <your_command>', which does the same thing). Using ELF load
        buttons from this menu will likewise load desired elf to all apps windows.
        Note that Cluster apps view is also useful for multicore apps debug, as it is Lauterbach's own implementation
        to debug all apps at once. Please note that not all features (such as some std_debug subsystems) work properly
        when using Apps cluster T32.
        
    Plusvm option has been added to all symbol loading scripts. This is invoked only via command line at this time, via the 'extraoption' option.
        Plusvm is intended for faster ETM trace processig (After a trace is captured, JTag searches DDR to correlate traces with actual memory.
        With Plusvm, ELF gets loaded onto JTag pod and so this second time consuming and invasive step doesn't have to be performed. 
        However, the ELF will take up room on the jtag pod and so tracing room can be limited.
        e.g.: do std_loadsyms_adsp NULL NULL NULL loadsecondelf NULL extraoption=plusvm,silent
        
    - Additional note: For Android targets, make sure to set the 'persist' bit via adb commands: "adb wait-for-devices shell setprop persist.sys.ssr.enable_debug 1"
      This will keep apps' Peripheral Image Loader (PIL) from timing out on peripheral subsystem when it's booting up. This is only needed if user 
      desires to break processor during its initialization. If this is not set, and user has set a breakpoint that occurs prior to when peripheral 
      processor sends ACK back to apps' PIL, you'll see peripheral processor get reset (T32 will show 'RES/PWR DWN' soon after halt).

std_loadsim
    std_loadsim is the suite of scripts designed to open a post-mortem T32 simulator session from a crash dump.
    GUI - the GUI will open automatically when opening a session. If you want to open another GUI, simply type 'do std_loadsim'
    Command line - command line options are available. For more information, type 'do std_loadsim help'
    
    
    
    
    
    
    
    
    
    
    
    
