#============================================================================
#  Name:                                                                     
#    clocks_cmm.py
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
# 09/06/2016 JBILLING     ClockDriver added
# 03/30/2016 JBILLING     8998 scripts added
# 02/17/2016 JBILLING     Created
#

#Macros available for use:
# Target: &CHIPSET (e.g. msm8996)
# Target: &CHIP (e.g. 8996)
# Subsystem: &TargetProcessor
# Image: &Image
#

import os

TESTCLOCK_TEMPLATE = {
  'dropdown menu name'  : "testclock",
  'description'         : "testclock - query clock frequencies and on/off state",
  'scriptname'          : "testclock.cmm", #Make sure to include the extension here
  'arguments'           : [],
  'abspath'             : os.path.join("{ROOTDIR}","systemdrivers","clock","{TARGET}"),
  'submenu'             : 'Clock',
  'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
  'subsystems'          : [],
  'prerequisites'       : [],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
  'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
  'tags'                : "TESTCLOCK",
  'menubutton'          : "[:time]", #Use SPARINGLY! Use bitmap code from T32. This will put a menu button on T32 GUI. We only have so much room...
  'target'              : "",             #target specific or not
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


TESTPLL_TEMPLATE = dict(TESTCLOCK_TEMPLATE, **{
  'dropdown menu name'  : "testpll",
  'description'         : "testpll - query pll status",
  'scriptname'          : "testpll.cmm",
  'tags'                : "TESTPLL",
  'menubutton'          : None, 
})

CLOCKDRIVER_TEMPLATE = dict(TESTCLOCK_TEMPLATE, **{
  'dropdown menu name'  : "Main Clock Script",
  'description'         : "Main Clock Script",
  'scriptname'          : "ClockDriver.cmm",
  'tags'                : "CLOCK",
  'menubutton'          : None, 
  #'menubutton'          : [], 
})

def CreateDictionary(targetconfigs):
  rootdir = targetconfigs['RootDir']
  target = targetconfigs['Target']

  testclock_template = dict(TESTCLOCK_TEMPLATE, **{
    'abspath':  TESTCLOCK_TEMPLATE['abspath'].format(ROOTDIR=rootdir, TARGET=target),
  })

  testpll_template = dict(TESTPLL_TEMPLATE, **{
    'abspath':  TESTPLL_TEMPLATE['abspath'].format(ROOTDIR=rootdir, TARGET=target),
  })
  
  clockdriver_template = dict(CLOCKDRIVER_TEMPLATE, **{
    'abspath'  : os.path.join(targetconfigs['RootDir'],"systemdrivers","clock"),
    
  })
  
  
  clock_scripts = {
  
  

    "clockdriver": {
    
      "clockdriver_8996": dict(clockdriver_template, **{
        'target'              : 'msm8996',
        'subsystems'          : ['all'],
        'dropdown menu name'  : "Clock Driver",
        'scriptname'          : "ClockDriver.cmm",
      }),

      "clockdriver_8998": dict(clockdriver_template, **{
        'target'              : 'msm8998',
        'subsystems'          : ['all'],
        'dropdown menu name'  : "Clock Driver",
        'scriptname'          : "ClockDriver.cmm",
      }),
    },
      
    "testclock": {
      "testclock_8996": dict(testclock_template, **{
        'target'      : 'msm8996',
        'subsystems'  : ['rpm', 'apps', 'adsp', 'slpi'],
      }),

      "testclock_8996_bimc": dict(testclock_template, **{
        'target'              : 'msm8996',
        'subsystems'          : ['rpm', 'apps', 'adsp', 'slpi'],
        'dropdown menu name'  : "testclock_bimc",
        'scriptname'          : "testbimc.cmm",
      }),

      "testclock_8998": dict(testclock_template, **{
        'target'      : 'msm8998',
        'subsystems'  : ['rpm', 'apps', 'adsp', 'slpi'],
      }),

      "testclock_8998_mpss": dict(testclock_template, **{
        'target'    : 'msm8998',
        'subsystems': ['mpss'],
        'scriptname': "testclock_mpss.cmm",
      }),
    },

    'testpll': {
      "testpll_8998": dict(testpll_template, **{
        'target'      : 'msm8998',
        'subsystems'  : ['rpm', 'apps', 'adsp', 'slpi'],
      }),

      "testpll_8998_mpss": dict(testpll_template, **{
        'target'      : 'msm8998',
        'subsystems'  : ['mpss'],
        'scriptname': "testpll_mpss.cmm",
      }),
    },
  }

  return clock_scripts

