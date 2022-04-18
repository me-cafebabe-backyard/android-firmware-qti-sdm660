#============================================================================
#  Name:                                                                     
#    general_cmm.py
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
# 05/03/2016 JBILLING     Scripts made externally releasable
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
            {"AttachManager-Attach" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Attach to Processor",
                      'description'         : "Attach to a running"+targetconfigs['Target']+" "+targetconfigs['Image'],
                      'scriptname'          : "attachmanager.cmm", #Make sure to include the extension here
                      'arguments'           : ["attach",targetconfigs['Target']],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"general"),
                      'submenu'             : 'general',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "attach",
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
            {"AttachManager-Break" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Attach And Break Processor",
                      'description'         : "Attach and break on a "+targetconfigs['Target']+" "+targetconfigs['Image'],
                      'scriptname'          : "attachmanager.cmm", #Make sure to include the extension here
                      'arguments'           : ["break",targetconfigs['Target']],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"general"),
                      'submenu'             : 'general',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "attach",
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
            {"SymbolManager-Loadsyms" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Load Symbols",
                      'description'         : "Load symbols for "+targetconfigs['Image'],
                      'scriptname'          : "symbolmanager.cmm", #Make sure to include the extension here
                      'arguments'           : [targetconfigs['Image']],
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"general"),
                      'submenu'             : 'general',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "attach,utility",
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
            {"PostScriptPrompt" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "postscriptprompt.cmm", #Make sure to include the extension here
                      'arguments'           : [], #This normally does take a string arg, but is passed from prescripts
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"general"),
                      'submenu'             : None,
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "utility",
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
            {"MainHWIOScript" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Load HWIO Symbols",
                      'description'         : "Load HWIO Symbols",
                      'scriptname'          : "hwio.cmm", #Make sure to include the extension here
                      'arguments'           : [], #This normally does take a string arg, but is passed from prescripts
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"..","cmm","common",targetconfigs['Target']),
                      'submenu'             : None,
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['all'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "utility",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "All",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : None, #Will prompt user before running postscript.
                      'liveorsim?'          : "Both", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : True,
                     }
                } )
    CMMBuilderDict.update( 
            {"stddebug" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : 'Debug Menu',
                      'description'         : "Main debug menu for debugging various subsystems",
                      'scriptname'          : "std_debug.cmm", #Make sure to include the extension here
                      'arguments'           : [], #This normally does take a string arg, but is passed from prescripts
                      'abspath'             : os.path.join(targetconfigs['RootDir'],'..','cmm','common'),
                      'submenu'             : None,
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['apps'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "stddebug",
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
            {"stdloadbuild" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : 'Build Options',
                      'description'         : "Main build loading routine for cleaning and loading a build onto device",
                      'scriptname'          : "std_buildoptions.cmm", #Make sure to include the extension here
                      'arguments'           : [], #This normally does take a string arg, but is passed from prescripts
                      'abspath'             : os.path.join(targetconfigs['RootDir'],'..','cmm','common',targetconfigs['Target']),
                      'submenu'             : None,
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ['apps'],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "stddebug",
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