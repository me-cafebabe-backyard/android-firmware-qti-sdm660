#=============================================================================
# FILE:         epm_cmm.py
#
# OVERVIEW:     CMMBuilder configurations for EPM scripts.
#
#               Copyright (c) 2016 Qualcomm Technologies, Inc.
#               All Rights Reserved.
#               Qualcomm Technologies Proprietary and Confidential.
#=============================================================================
#=============================================================================
# EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.  Please
# use ISO format for dates.
#
# $Header: //components/rel/core.glue/1.2.1/tools/tools/hwengines/epm/epm_cmm.py#1 $$DateTime: 2016/11/23 22:06:41 $$Author: pwbldsvc $
#
# when        who  what, where, why
# ----------  ---  -----------------------------------------------------------
# 2016-06-23  JB   Use direct executable instead of cmm wrapper
# 2016-03-31  jjo  Initial revision.
#
#===========================================================================*/
#-----------------------------------------------------------------------------
#  Include Files
#-----------------------------------------------------------------------------
import os
import sys

#Macros available for use:
# Target: &CHIPSET (e.g. msm8996)
# Target: &CHIP (e.g. 8996)
# Subsystem: &TargetProcessor
# Image: &Image

def CreateDictionary(targetconfigs):

   CMMBuilderDict={}

   CMMBuilderDict.update(
   {
      "ALPACA GUI" :                                       #Script Entry Identifier. This must be unique to every script entry
      {
         'dropdown menu name'  : "ALPACA GUI",             #What appears in the T32 menu
         'description'         : "ALPACA GUI",
         'scriptname'          : "alpaca.exe",             #Actual name of script that is called.
                                                           #Make sure to include the extension here as T32 will automatically prepend the script with the right command
                                                           #e.g. per <yourfile>.per, or cd.do <yourfile>.cmm or OS.COMMAND <your python file>.py

         'arguments'           : [],                       #you can pass a variety of things using targetconfigs
         'abspath'             : os.path.join(targetconfigs['RootDir'],"hwengines","epm"), #Needs to be the path to your script
         'submenu'             : 'ALPACA',                 #Not implemented yet
         'user-interactive?'   : True,                     #If this script doesn't require user interaction, put False, else True.

         'subsystems'          : ["all"],                  #'all' is special, as it will show up in every subsystem script
                                                           #Else put your particular subsystems, such as ['apps'], or ['rpm','apps']
                                                           #Note that there are hardware-oriented subsystems (such as RPM-CORTEXM3 or MSS-Q6)
                                                           #These will always be loaded on a t32 window
                                                           #as opposed to a software-oriented subsystem, such as ADSP or LA,
                                                           #Which will be loaded when that subsystem's image ELF file is set up.


         'prerequisites'       : [],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
         'show in menu'        : True,     #Show this script in the menu?
                                           #(Not all scripts show in dropdown menu - some post-scripts only to be run
                                           #after an initial script, or are for postmortem only)
         'tags'                : "ALPACAGUICMM", #For  future implementation
         'menubutton'          : None,     #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
         'target'              : "All",    #target specific or not. You can put 'all', or, say 'MSM8996' and it will show up only on that target.
                                                    #pop quiz: what happens you put targetconfigs['Target']??
         'outputfiles'         : None,     #If your script spits out something in a temp folder.
         'returnarguments'     : [],       #if at the end of your script, you
         'postscripts'         : [],       #Other scripts to be run immediately after this one. Use top dictionary name for this one
         'postscriptarguments' : [],       #arguments to pass to postscripts being called.
         'postscript prompt'   : None,     #Will prompt user before running postscript.
         'liveorsim?'          : "Live",   #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
         'runonpostmortem'     : False,    #There's a menu file and a postmortem file. The postmortem file is run on a T32 simulator setup.
                                           #If enough scripts are registered, it will give it a crashscope analysis type feel.
         'runoninit'           : False,    #Run script as soon as the window opens. To be implemented
         'externalrelease'     : False,    #IMPORTANT: Can your scripts be shipped to customer? If False, it will be stripped out.
      }
   })

   return CMMBuilderDict

