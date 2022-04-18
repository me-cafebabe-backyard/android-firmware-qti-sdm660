#============================================================================
#  Name:                                                                     
#    general_cmm.py
#
#  Description:                                                              
#    CMMBuilder configurations for wlan scripts
#
#  Usage
#      Intended to be called from rootcmmbuilder
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
# 03/30/2016 JBILLING     Created
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
    CMMBuilderDict={}



    CMMBuilderDict.update( 
            {"Debug WLAN Low Power Mode" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Debug WLAN Low Power Mode",
                      'description'         : "Debug WLAN Low Power Mode",
                      'scriptname'          : "sr_force_wakeup.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"wlan"),
                      'submenu'             : 'wlan',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['MSS-Q6'],
                      'prerequisites'       : ["attach","hwio"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "attach",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "MSM8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : None, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : True,
                     }
                } )

    return CMMBuilderDict