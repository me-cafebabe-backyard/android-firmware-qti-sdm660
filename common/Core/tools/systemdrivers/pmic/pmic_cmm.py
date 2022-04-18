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


    CMMBuilderDict.update( 
            {"PMIC Dashboard" :                                     #Script Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PMIC Dashboard",     #What appears in the T32 menu
                      'description'         : "Displays PMIC power rails, clocks and GPIOs status",
                      'scriptname'          : "PMICDashBoard.cmm",  #Make sure to include the extension here
                      'arguments'           : [], #Pass arguments as a list. various config settings availabe (target, temppath etc)
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic",targetconfigs['TargetFamily']), #Necessary
                      'submenu'             : 'PMIC',           #Optional
                      'user-interactive?'   : True,             #Let's the builder know if user interactive
                      'subsystems'          : ["all"],       #Will only show on listed processor T32 windows. 'all' is also an option
                      'prerequisites'       : ["attach"],       #Name any script identifier, 
                                                                #or special keywords: 
                                                                    #attach=> T32 will attach first. 
                                                                    #break-> T32 will break proc first. 
                                                                    #symbols-> load symbols first
                      'show in menu'        : True, #Show this script in the menu? 
                                                    #(Not all scripts show in menu - some are pre or post-scripts only to be run after an initial script)
                      'tags'                : "PMIC Dashboard", #For future functionality
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",    #target specific or not
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


    CMMBuilderDict.update( 
            {"PMIC Dump" :                                     #Script Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PMIC Dump",     #What appears in the T32 menu
                      'description'         : "Collects PMIC register dump",
                      'scriptname'          : "PMICDump.cmm",  #Make sure to include the extension here
                      'arguments'           : [], #Pass arguments as a list. various config settings availabe (target, temppath etc)
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic",targetconfigs['TargetFamily']), #Necessary
                      'submenu'             : 'PMIC',           #Optional
                      'user-interactive?'   : True,             #Let's the builder know if user interactive
                      'subsystems'          : ["all"],       #Will only show on listed processor T32 windows. 'all' is also an option
                      'prerequisites'       : ["attach"],       #Name any script identifier, 
                                                                #or special keywords: 
                                                                    #attach=> T32 will attach first. 
                                                                    #break-> T32 will break proc first. 
                                                                    #symbols-> load symbols first
                      'show in menu'        : True, #Show this script in the menu? 
                                                    #(Not all scripts show in menu - some are pre or post-scripts only to be run after an initial script)
                      'tags'                : "PMIC Dump", #For future functionality
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",    #target specific or not
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


    CMMBuilderDict.update( 
            {"PMIC Peek" :                                     #Script Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PMIC Peek",     #What appears in the T32 menu
                      'description'         : "Peek/poke PMIC registers",
                      'scriptname'          : "PMICPeek.cmm",  #Make sure to include the extension here
                      'arguments'           : [], #Pass arguments as a list. various config settings availabe (target, temppath etc)
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic",targetconfigs['TargetFamily']), #Necessary
                      'submenu'             : 'PMIC',           #Optional
                      'user-interactive?'   : True,             #Let's the builder know if user interactive
                      'subsystems'          : ["all"],       #Will only show on listed processor T32 windows. 'all' is also an option
                      'prerequisites'       : ["attach"],       #Name any script identifier, 
                                                                #or special keywords: 
                                                                    #attach=> T32 will attach first. 
                                                                    #break-> T32 will break proc first. 
                                                                    #symbols-> load symbols first
                      'show in menu'        : True, #Show this script in the menu? 
                                                    #(Not all scripts show in menu - some are pre or post-scripts only to be run after an initial script)
                      'tags'                : "PMIC Peek", #For future functionality
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",    #target specific or not
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


    CMMBuilderDict.update( 
            {"PBUS Logger" :                                     #Script Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "PBUS Logger",     #What appears in the T32 menu
                      'description'         : "Logs and displays the SPMI/PBS transactions",
                      'scriptname'          : "PBUSLogger.cmm",  #Make sure to include the extension here
                      'arguments'           : [], #Pass arguments as a list. various config settings availabe (target, temppath etc)
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic",targetconfigs['TargetFamily']), #Necessary
                      'submenu'             : 'PMIC',           #Optional
                      'user-interactive?'   : True,             #Let's the builder know if user interactive
                      'subsystems'          : ["all"],       #Will only show on listed processor T32 windows. 'all' is also an option
                      'prerequisites'       : ["attach"],       #Name any script identifier, 
                                                                #or special keywords: 
                                                                    #attach=> T32 will attach first. 
                                                                    #break-> T32 will break proc first. 
                                                                    #symbols-> load symbols first
                      'show in menu'        : True, #Show this script in the menu? 
                                                    #(Not all scripts show in menu - some are pre or post-scripts only to be run after an initial script)
                      'tags'                : "PBUS Logger", #For future functionality
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",    #target specific or not
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


    CMMBuilderDict.update( 
            {"PMIC HARD RESET" :
                     {'dropdown menu name'  : "PMIC Hard Reset",
                      'description'         : "Does a PMIC Hard Reset",
                      'scriptname'          : "PMICReset.cmm", #Make sure to include the extension here
                      'arguments'           : ["HARDRESET"],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic"),
                      'submenu'             : 'PMIC',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : ["attach"],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "PMIC",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",             #target specific or not
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
                

    CMMBuilderDict.update( 
            {"PMIC WARM RESET" :
                     {'dropdown menu name'  : "PMIC Warm Reset",
                      'description'         : "Does a PMIC Warm Reset",
                      'scriptname'          : "PMICReset.cmm", #Make sure to include the extension here
                      'arguments'           : ["WARMRESET"],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic"),
                      'submenu'             : 'PMIC',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : ["attach"],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "PMIC",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",             #target specific or not
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

    CMMBuilderDict.update( 
            {"PMIC Registers" :
                     {'dropdown menu name'  : "PMIC Registers",
                      'description'         : "PMIC Registers",
                      'scriptname'          : "PMICRegisters.cmm", #Make sure to include the extension here
                      'arguments'           : [""],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","pmic",targetconfigs['TargetFamily']), #Necessary
                      'submenu'             : 'PMIC',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : ["attach"],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "PMIC",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",             #target specific or not
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
