#============================================================================
#  Name:                                                                     
#    systemdrivers.cmm
#
#  Description:                                                              
#    CMMBuilder configurations for systemdriver scripts
#
#  Usage
#      Intended to be called from cmmbuilder
#                                                                     
# Copyright (c) 2012 - 2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.        
#
#
#
#
#                      EDIT HISTORY FOR FILE
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when         who         what, where, why
# --------     ---        --------------------------------------------------------
# 02/17/2016 JBILLING     Created
#


#Macros available for use:
# Target: &CHIPSET (e.g. msm8996)
# Target: &CHIP (e.g. 8996)
# Subsystem: &TargetProcessor
# Image: &Image
#
import os
import sys

def CreateDictionary(targetconfigs):
#"35. APB"

    CMMBuilderDict={}

    ############################################
    ######### PIMEM APB usecase#################
    ############################################
    CMMBuilderDict.update(
            {"PIMEM Trace BC - APB" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PIMEM Trace BC - APB",
                      'description'         : "Trace PIMEM TPDM - APB mode",
                      'scriptname'          : "trace_tpdm_wrapper.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'pimemTrace',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "pimemTrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ["traceID"],
                      'postscripts'         : ["PIMEM Trace BC - APB - postscript"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["&traceID","APB"], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    #This is the postscript to the wrapper, but is the core usecase
    CMMBuilderDict.update(
            {"PIMEM Trace BC - APB - postscript" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PIMEM Trace BC - APB",
                      'description'         : None,
                      'scriptname'          : "trace_tpdmBC_pimem.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'pimemTrace',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "pimemTrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["Dump ETB"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [os.path.join(targetconfigs['TempPath'],"Pimem_BC_APB_ETB_Dump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
    ############################################
    ######### PIMEM ATB usecase#################
    ############################################
    CMMBuilderDict.update(
            {"PIMEM Trace BC - ATB" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PIMEM Trace BC - ATB",
                      'description'         : "Trace PIMEM TPDM - ATB mode",
                      'scriptname'          : "trace_tpdm_wrapper.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'pimemTrace',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "pimemTrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ["traceID"],
                      'postscripts'         : ["PIMEM Trace BC - ATB - postscript"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["&traceID","ATB"], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    CMMBuilderDict.update( 
            {"PIMEM Trace BC - ATB - postscript" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PIMEM Trace BC - ATB",
                      'description'         : None,
                      'scriptname'          : "trace_tpdmBC_pimem.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'pimemTrace',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "pimemTrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["Dump ETB"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [os.path.join(targetconfigs['TempPath'],"Pimem_BC_ATB_ETB_Dump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
                
                
                
                
                
                
    ############################################
    ######### PIMEM CMB usecase#################
    ############################################
    CMMBuilderDict.update(
            {"PIMEM Trace CMB" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PIMEM Trace CMB",
                      'description'         : "Trace PIMEM CMB",
                      'scriptname'          : "trace_tpdm_wrapper.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'pimemTrace',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "pimemTrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ["traceID"],
                      'postscripts'         : ["PIMEM Trace CMB - postscript"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["&traceID","0xF0F"], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    CMMBuilderDict.update( 
            {"PIMEM Trace CMB - postscript" :      #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PIMEM Trace CMB",
                      'description'         : None,
                      'scriptname'          : "trace_tpdmCMB_pimem.cmm", #Make sure to include the extension here
                      'arguments'           : ["35. 0xF0F"],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'pimemTrace',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "pimemTrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["Dump ETB"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["Pimem_CMB_ETB_Dump.bin"], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    return CMMBuilderDict