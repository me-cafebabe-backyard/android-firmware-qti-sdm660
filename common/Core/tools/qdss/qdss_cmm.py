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
            {"MPSS to SNOC probe" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "MPSS to SNOC probe",
                      'description'         : "Trace packets originating from MPSS across SNOC",
                      'scriptname'          : "mpss_to_rpm_cnoc_probe.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"qdss",targetconfigs['Target']),
                      'submenu'             : None,
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach","openallfunnels"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "snoc",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["Dump ETB"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
    CMMBuilderDict.update( 
            {"openallfunnels" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "MPSS to SNOC probe",
                      'description'         : "Trace packets originating from MPSS across SNOC",
                      'scriptname'          : "funnel_config.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"qdss",targetconfigs['Target']),
                      'submenu'             : None,
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "QDSS",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )                
                
    CMMBuilderDict.update( 
            {"GladiatorTrace" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "GladiatorTrace",
                      'description'         : "Gladiator Cache Coherency Unit Trace Setup",
                      'scriptname'          : "Gladiator_Debug_Suite.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"qdss","gladiatortrace",targetconfigs['Target']),
                      'submenu'             : 'Gladiator',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "gladiatortrace",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
                
    #differentiate between RPM vs other images
    if 'RPM' in targetconfigs['Image']:
            CMMBuilderDict.update( 
                    {"Dump ETB" : #Identifier. This must be unique to every script entry
                             {'dropdown menu name'  : "Dump ETB",
                              'description'         : "Dump ETB",
                              'scriptname'          : "dump_etb_rpm.cmm", #Make sure to include the extension here
                              'arguments'           : [os.path.join(targetconfigs['TempPath'],"etb_dump.bin")],
                              'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"qdss",targetconfigs['Target']),
                              'submenu'             : 'QDSS',
                              'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                              'subsystems'          : ["RPM-CORTEXM3","RPM"],
                              'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                              'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                              'tags'                : "ETBDUMP",
                              'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                              'target'              : "all",             #target specific or not
                              'outputfiles'         : None,
                              'returnarguments'     : [],
                              'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                              'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                              'postscript prompt'   : False, #Will prompt user before running postscript.
                              'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                              'runonpostmortem'     : False,
                              'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                              'externalrelease'     : True,
                             }
                        } )

    else:                   
            CMMBuilderDict.update( 
                    {"Dump ETB" : #Identifier. This must be unique to every script entry
                             {'dropdown menu name'  : "Dump ETB",
                              'description'         : "Dump ETB",
                              'scriptname'          : "dump_etb.cmm", #Make sure to include the extension here
                              'arguments'           : [os.path.join(targetconfigs['TempPath'],"etb_dump.bin")],
                              'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"qdss",targetconfigs['Target']),
                              'submenu'             : 'QDSS',
                              'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                              'subsystems'          : ["all"],
                              'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                              'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                              'tags'                : "ETBDUMP",
                              'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                              'target'              : "all",             #target specific or not
                              'outputfiles'         : None,
                              'returnarguments'     : [],
                              'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                              'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                              'postscript prompt'   : False, #Will prompt user before running postscript.
                              'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                              'runonpostmortem'     : False,
                              'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                              'externalrelease'     : True,
                             }
                        } )
    return CMMBuilderDict