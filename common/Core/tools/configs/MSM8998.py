"""
===============================================================================

 MSM8998.py

 GENERAL DESCRIPTION
    Target specific configuration data

 Copyright (c) 2015 - 2016 by QUALCOMM Technologies Incorporated.
 All Rights Reserved.

 QUALCOMM Proprietary

-------------------------------------------------------------------------------

  
                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

 when       who         what, where, why
 --------   ---         ---------------------------------------------------------
 2/26/2016  JBILLING    Created for rootcmmbuilder
==============================================================================
"""
import os, sys
global RootDirectory


def targetconfigs():

    targetconfigs={}
    if os.path.exists(os.path.dirname(sys.argv[0])):
        RootDirectory=os.path.abspath(os.path.dirname(sys.argv[0]))
    elif os.path.exists(os.path.join(os.getcwd(),os.path.dirname(sys.argv[0]))):
        RootDirectory=os.path.join(os.getcwd(),os.path.dirname(sys.argv[0]))
    else:
        RootDirectory=os.path.abspath(os.getcwd())
    # Setup related configurable params
    #T32Installation  = 'C:\T32'
    #T32TempFolder    = 'C:\T32work'
    #
    #Target = 'MSM8998'
    #TempPath = '&TEMP'
    #RootDir = '&CMMBUILDER_ROOT'
    targetconfigs.update({'T32Installation':'C:\T32'})
    targetconfigs.update({'T32TempFolder':'C:\T32work'})
    targetconfigs.update({'Target':'MSM8998'})
    targetconfigs.update({'TempPath' : '&TEMP'})
    targetconfigs.update({'RootDir' : '&METATOOLSDIR'})
    targetconfigs.update({'TargetFamily' : 'honeybadger'})
    
    #For release vs internal flavors
    flavors   = { 'internal' : 'internal', 'external' : 'external'}
    targetconfigs.update({'flavors':flavors})
    
    CoreNames   = { 'RPM' : 'RPM', 'APPS0' : 'APPS0', 'APPS1' : 'APPS1', 'APPS2' : 'APPS2', 'APPS3' : 'APPS3', 'MPSS' : 'MPSS', 'ADSP' : 'ADSP', 'SLPI' : 'SLPI', 'ARM32Sim' : 'ARM32Sim', 'ARM64Sim' : 'ARM64Sim', 'QDSP6Sim' : 'QDSPSim' }
    targetconfigs.update({'corenames':CoreNames})
    
    Cores = ['RPM-CORTEXM3','MSS-Q6','LPASS-Q6','SSC-Q6','APPS-ARMV8']
    targetconfigs.update({'cores':Cores})

    #Scripts will be made from each of these
    subsystems = ['RPM-CORTEXM3','MSS-Q6','LPASS-Q6','SSC-Q6','APPS-ARMV8']
    targetconfigs.update({'subsystems':subsystems})
    
    #images that each subsystem has in it
    subsystemprofiles = {'RPM-CORTEXM3':    ['RPM','RPM-CORTEXM3'],
                        'MSS-Q6':           ['MPSS','WLAN','MSS-Q6'],
                        'LPASS-Q6':         ['ADSP','LPASS-Q6'],
                        'SSC-Q6':           ['SLPI','SSC-Q6'],
                        'APPS-ARMV8-LA':    ['APPS-ARMV8','LA','XBL','TZ'],
                        'APPS-ARMV8-WP':    ['APPS-ARMV8','WP','XBL','TZ']
                        }
    
    #What keyword maps to what subsystemprofile(s)
    #image_to_subsystemprofile_map={
    #                'RPM':          ['RPM-CORTEXM3'],
    #                'RPM-CORTEXM3': ['RPM-CORTEXM3'],
    #                'MPSS':         ['MSS-Q6'],
    #                'MSS-Q6':       ['MSS-Q6'],
    #                'WLAN':         ['MSS-Q6'],
    #                'ADSP':         ['LPASS-Q6'],
    #                'LPASS':        ['LPASS-Q6'],
    #                'LPASS-Q6':     ['LPASS-Q6'],
    #                'SLPI':         ['SSC-Q6'],
    #                'SSC-Q6':       ['SSC-Q6'],
    #                'APSS':         ['APPS-ARMV8-WP','APPS-ARMV8-LA'],
    #                'APPS':         ['APPS-ARMV8-WP','APPS-ARMV8-LA'],
    #                'APPS-ARMV8':   ['APPS-ARMV8-WP','APPS-ARMV8-LA'],
    #                'LA':           ['APPS-ARMV8-LA'],
    #                'WP':           ['APPS-ARMV8-WP'],
    #                'APPS-ARMV8-LA':['APPS-ARMV8-LA'],
    #                'APPS-ARMV8-WP':['APPS-ARMV8-WP'],
    #                'TZ':           ['APPS-ARMV8-WP','APPS-ARMV8-LA'],
    #                'XBL':          ['APPS-ARMV8-WP','APPS-ARMV8-LA'],
    #                }
    
    subsystemprofile_map={
                    'RPM-CORTEXM3':     ['RPM','RPM-CORTEXM3'],
                    'MSS-Q6':           ['MSS-Q6','MPSS','WLAN','MODEM','GPSSS','GPS','GSS'],
                    'LPASS-Q6':         ['LPASS-Q6','ADSP','LPASS'],
                    'SSC-Q6':           ['SSC-Q6','SLPI','SENSOR','SENSORS'],
                    'APPS-ARMV8-LA':    ['APPS-ARMV8-LA','LA','XBL','TZ','APPS','APSS'],
                    'APPS-ARMV8-WP':    ['APPS-ARMV8-WP','WP','XBL','TZ','APPS','APSS'],
                    }
    targetconfigs.update({'subsystemprofile_map':subsystemprofile_map})
    #This is what the users will enter as subsystems. They map to the entries in the image_to_subsystemprofile_map
    image_aliases={
            'RPM':'RPM',
            'RPM-CORTEXM3':'RPM-CORTEXM3',
            'LA':'LA',
            'LINUX':'LA',
            'WP':'WP',
            'WINDOWS':'WP',
            'LPASS':'LPASS-Q6',
            'ADSP':'ADSP',
            'LPASS-Q6':'LPASS-Q6',
            'MSS-Q6':'MSS-Q6',
            'MSS':'MPSS',
            'MPSS':'MPSS',
            'SSC':'SLPI',
            'SSC-Q6':'SSC-Q6',
            'SLPI':'SLPI',
            'XBL':'XBL',
            'APSS':'APPS-ARMV8',
            'APPS':'APPS-ARMV8',
            'TZ':'TZ',
            'WLAN':'WLAN'
            }
    targetconfigs.update({'image_aliases':image_aliases})
    
    
    targetconfigs.update({'subsystemprofiles':subsystemprofiles})
    #Scripts will be made from each of these too
    software_images=['RPM','MPSS','LA','WP','SLPI','ADSP','TZ','XBL','VSS','WLAN']
    targetconfigs.update({'software_images':software_images})
    
    #What s/w runs on what hardware
    swimage_to_hwsubsystem_map={
                    'RPM':'RPM-CORTEXM3',
                    'MPSS':'MSS-Q6',
                    'WLAN':'MSS-Q6',
                    'ADSP':'LPASS-Q6',
                    'LPASS':'ADSP',
                    'SLPI':'SLPI',
                    'SSC':'SLPI',
                    'APSS':'APPS-ARMV8',
                    'APPS':'APPS-ARMV8',
                    'LA':'LA',
                    'WP':'WP',
                    'XBL':'XBL',
                    'RPM':'RPM'
                    }
                    
    targetconfigs.update({'swimage_to_hwsubsystem_map':swimage_to_hwsubsystem_map})
    #Other terms that folks may use to label images in their dictionary entries
    #image_aliases={
    #        'RPM':'RPM',
    #        'RPM-CORTEXM3':'RPM-CORTEXM3',
    #        'LA':'LA',
    #        'LINUX':'LA',
    #        'WP':'WP',
    #        'WINDOWS':'WP',
    #        'LPASS':'LPASS-Q6',
    #        'ADSP':'ADSP',
    #        'LPASS':'LPASS-Q6',
    #        'LPASS-Q6':'LPASS-Q6',
    #        'MSS-Q6':'MSS-Q6',
    #        'MSS':'MPSS',
    #        'MPSS':'MPSS',
    #        'SSC':'SLPI',
    #        'SSC-Q6':'SSC-Q6',
    #        'SLPI':'SLPI',
    #        'XBL':'XBL',
    #        'APSS':'APPS-ARMV8',
    #        'APPS':'APPS-ARMV8',
    #        'TZ':'TZ',
    #        'WLAN':'WLAN'
    #        }
    
    #targetconfigs.update({'image_aliases':image_aliases})
    #Images= ['TZ','XBL','PBL','RPM','LA','APPSBOOT','ADSP','MPSS','SLPI']
    #targetconfigs.update({'images':Images})

    # Emulation machine names
    #EmulationTarget = '10.46.163.10'
    #SessionStartDelay = 10
    
    return targetconfigs

