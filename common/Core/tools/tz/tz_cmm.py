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
# 04/15/2016 JBILLING     More scripts added
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
    CMMBuilderDict={}


    #CMMBuilderDict.update( 
    #        {"AreaName":"SMMU Debug"} #This is the name which will appear in the drop down menu. 
    #                                  #If it's not specified, will use the filename (e.g. dragonlink)
    #        )

    CMMBuilderDict.update( 
            {"SMMU Fault parser" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "SMMU Fault parser",
                      'description'         : "SMMU Fault parser - Parse SMMU fault",
                      'scriptname'          : "smmu_debug_fault.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"tz","smmu",targetconfigs['Target']),
                      'submenu'             : 'SMMU',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "smmu",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : targetconfigs['Target'],             #target specific or not
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
                

   
                
    CMMBuilderDict.update( 
            {"Stage 2 Pagetable Walker" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Stage 2 pagetable walker",
                      'description'         : "Stage 2 pagetable walker for SMMU",
                      'scriptname'          : "dump_pt.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"tz","smmu",targetconfigs['Target']),
                      'submenu'             : 'SMMU',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "smmu",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : targetconfigs['Target'],             #target specific or not
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
                
    CMMBuilderDict.update( 
            {"Print TZ Log" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Print TZ Log",
                      'description'         : "Print TZ Logs",
                      'scriptname'          : "print_tz_log.cmm", #Make sure to include the extension here
                      'arguments'           : ["&TZ_BUILDROOT",targetconfigs['Target']],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"tz","tzlogs"),
                      'submenu'             : 'TZ',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "tz",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : targetconfigs['Target'],             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : None, #Will prompt user before running postscript.
                      'liveorsim?'          : "Both", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    CMMBuilderDict.update( 
            {"Load TZ elfs" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Load TZ elfs",
                      'description'         : "Load TZ elfs",
                      'scriptname'          : "load_qsee_elf.cmm", #Make sure to include the extension here
                      'arguments'           : ["&TZ_BUILDROOT","&TZ_BUILDID"],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"tz"),
                      'submenu'             : 'TZ',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "tz",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : targetconfigs['Target'],             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : None, #Will prompt user before running postscript.
                      'liveorsim?'          : "Both", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                

                
    return CMMBuilderDict