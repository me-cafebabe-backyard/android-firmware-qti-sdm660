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


    CMMBuilderDict={}

 
#mpss_to_rpm_cnoc_probe
    CMMBuilderDict.update( 
            {"RPM Scripts" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Setup RPM Debug",
                      'description'         : "Sets up RPM debug session within T32",
                      'scriptname'          : "rpm_debug.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"rpm","scripts"),
                      'submenu'             : None,
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["rpm"],
                      'prerequisites'       : ["attach","symbols"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "RPM",
                      'menubutton'          : "[:afind]", #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "all",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Both", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    
    return CMMBuilderDict