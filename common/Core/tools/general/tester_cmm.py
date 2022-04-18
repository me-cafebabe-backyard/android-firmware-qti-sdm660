#============================================================================
#  Name:                                                                     
#    tester_cmm.py
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
# Target: &targetconfigs['Target'] (e.g. msm8996)
# Target: &CHIP (e.g. 8996)
# Subsystem: &TargetProcessor
# Image: &Image
#
import os
import sys


def CreateDictionary(targetconfigs):
    PMICTGT={'MSM8996':'PMI8996','MSM8994':'PMI8994','MSM8998':'PMI8996','MDM9655':'PMI8996'}


    CMMBuilderDict={}

    CMMBuilderDict.update( 
            {"AreaName":"DragonLink"} #This is the name which will appear in the drop down menu. 
                                      #If it's not specified, will use the filename (e.g. dragonlink)
            )

    CMMBuilderDict.update( 
            {"tester1" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "tester1",
                      'description'         : "tester!",
                      'scriptname'          : "cpuss_dragonlink.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink",targetconfigs['Target']),
                      'submenu'             : 'SVE',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['apps'],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : 'all',             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ['arg1','arg2','arg3'],
                      'postscripts'         : ['AttachManager-Break'], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ['&arg2','&arg3'], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    CMMBuilderDict.update( 
            {"tester 2" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "tester 2",
                      'description'         : "tester!",
                      'scriptname'          : "cpuss_dragonlink_olc.cmm", #Make sure to include the extension here
                      'arguments'           : ['stuff',os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink",targetconfigs['Target'])],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink",targetconfigs['Target']),
                      'submenu'             : 'SVE',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['apps'],
                      'prerequisites'       : ["attach","tester1"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : 'all',             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ['arg1','arg2','arg3'],
                      'postscripts'         : ['AttachManager-Break'], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ['&arg2','&arg3'], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : True,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    return CMMBuilderDict