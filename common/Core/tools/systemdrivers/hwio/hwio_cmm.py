#============================================================================
#  Name:                                                                     
#    hwio_cmm.py
#
#  Description:                                                              
#    CMMBuilder configurations for hwio systemdrivers scripts
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

    #CHIPSET=os.environ['CHIPSET']
    #chipset file (e.g. MSM8996.py) should be available from system path
    #import chipset
    #targetconfigs=chipset.targetconfigs()
    #targetconfigs=__import__(chipset)


    CMMBuilderDict={}



    CMMBuilderDict.update( 
            {"View HWIO Registers" :
                     {'dropdown menu name'  : "View HWIO Registers",
                      'description'         : "View HWIO Registers - Register Tree view (per file)",
                      'scriptname'          : "HWIORegisters.cmm", #Make sure to include the extension here
                      'arguments'           : [targetconfigs['Target']],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","hwio"),
                      'submenu'             : 'HWIO',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["all"],
                      #'prerequisites'       : ['attach',"Load HWIO Menus"],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
                      'prerequisites'       : [],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "HWIOPER",
                      'menubutton'          : "[:chip]", #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : None, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
    return CMMBuilderDict
