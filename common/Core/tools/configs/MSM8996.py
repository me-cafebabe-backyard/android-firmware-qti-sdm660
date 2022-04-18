"""
===============================================================================

 MSM8996.py

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
    #Target = 'MSM8996'
    #TempPath = '&TEMP'
    #RootDir = '&CMMBUILDER_ROOT'
    targetconfigs.update({'T32Installation':'C:\T32'})
    targetconfigs.update({'T32TempFolder':'C:\T32work'})
    targetconfigs.update({'Target':'MSM8996'})
    targetconfigs.update({'TempPath' : '&TEMP'})
    targetconfigs.update({'RootDir' : '&METATOOLSDIR'})
    targetconfigs.update({'TargetFamily' : 'honeybadger'})
    #For release vs internal flavors
    flavors   = { 'internal' : 'internal', 'external' : 'external'}
    targetconfigs.update({'flavors':flavors})
    
    #T32ConfigFile    = os.environ['METABUILD'] + '\\common\\Core\\t32\\msm8996.ts2'
    #T32Container     = '\"//Root/DAP/Podbus Device Chain/Power Trace Ethernet/'
    #T32SimContainer = '\"//Root/Simulator/'
    #
    ## Target related setup options
    #defaultstart = ['APPS0', 'RPM']
    #
    ## Configuration for all cores
    #RPMConfig =   { 'IC' : 'NETASSIST', 'PORT' : '25400', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #APPS0Config = { 'IC' : 'NETASSIST', 'PORT' : '25370', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #APPS1Config = { 'IC' : 'NETASSIST', 'PORT' : '25372', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #APPS2Config = { 'IC' : 'NETASSIST', 'PORT' : '25373', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #APPS3Config = { 'IC' : 'NETASSIST', 'PORT' : '25374', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #MPSSConfig  = { 'IC' : 'NETASSIST', 'PORT' : '25401', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #ADSPConfig  = { 'IC' : 'NETASSIST', 'PORT' : '25402', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #SLPIConfig  = { 'IC' : 'NETASSIST', 'PORT' : '25403', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #ARM32SimConfig  = { 'IC' : 'NETASSIST', 'PORT' : '10000', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #ARM64SimConfig  = { 'IC' : 'NETASSIST', 'PORT' : '10001', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #QDSPSimConfig   = { 'IC' : 'NETASSIST', 'PORT' : '10002', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
    #
    #CoreConfigs = { 'RPM' : RPMConfig, 'APPS0' : APPS0Config, 'APPS1' : APPS1Config, 'APPS2' : APPS2Config, 'APPS3' : APPS3Config, 'MPSS' : MPSSConfig, 'ADSP' : ADSPConfig, 'SLPI' : SLPIConfig, 'ARM32Sim' : ARM32SimConfig, 'ARM64Sim' : ARM64SimConfig, 'QDSP6Sim' : QDSPSimConfig }
    CoreNames   = { 'RPM' : 'RPM', 'APPS0' : 'APPS0', 'APPS1' : 'APPS1', 'APPS2' : 'APPS2', 'APPS3' : 'APPS3', 'MPSS' : 'MPSS', 'ADSP' : 'ADSP', 'SLPI' : 'SLPI', 'ARM32Sim' : 'ARM32Sim', 'ARM64Sim' : 'ARM64Sim', 'QDSP6Sim' : 'QDSPSim' }
    targetconfigs.update({'corenames':CoreNames})
    
    Cores = ['RPM-CORTEXM3','MSS-Q6','LPASS-Q6','SSC-Q6','APPS-HYDRA']
    targetconfigs.update({'cores':Cores})

    #Scripts will be made from each of these
    subsystems = ['RPM-CORTEXM3','MSS-Q6','LPASS-Q6','SSC-Q6','APPS-HYDRA']
    targetconfigs.update({'subsystems':subsystems})
    
    #Scripts will be made from each of these too
    software_images=['RPM','MPSS','LA','WP','SLPI','ADSP','TZ','XBL','VSS']
    targetconfigs.update({'software_images':software_images})
    
    #What s/w runs on what hardware
    swimage_to_hwsubsystem_map={
                    'RPM':'RPM-CORTEXM3',
                    'MPSS':'MSS-Q6',
                    'ADSP':'LPASS-Q6',
                    'LPASS':'ADSP',
                    'SLPI':'SLPI',
                    'SSC':'SLPI',
                    'APSS':'HYDRA',
                    'APPS':'HYDRA',
                    'LA':'LA',
                    'WP':'WP',
                    'XBL':'XBL',
                    'RPM':'RPM'
                    }
    subsystemprofile_map={
                    'RPM-CORTEXM3':     ['RPM','RPM-CORTEXM3'],
                    'MSS-Q6':           ['MSS-Q6','MPSS','MODEM'],
                    'LPASS-Q6':         ['LPASS-Q6','ADSP','LPASS'],
                    'SSC-Q6':           ['SSC-Q6','SLPI','SENSOR','SENSORS'],
                    'APPS-ARMV8-LA':    ['APPS-ARMV8-LA','LA','XBL','TZ','APPS','APSS'],
                    'APPS-ARMV8-WP':    ['APPS-ARMV8-WP','WP','XBL','TZ','APPS','APSS'],
                    }
    targetconfigs.update({'subsystemprofile_map':subsystemprofile_map})
    
    
    targetconfigs.update({'swimage_to_hwsubsystem_map':swimage_to_hwsubsystem_map})
    #Other terms that folks may use to label images in their dictionary entries
    image_aliases={
            'RPM':'RPM',
            'RPM-CORTEXM3':'RPM-CORTEXM3',
            'LA':'LA',
            'LINUX':'LA',
            'WP':'WP',
            'WINDOWS':'WP',
            'LPASS':'LPASS-Q6',
            'ADSP':'ADSP',
            'LPASS':'LPASS-Q6',
            'LPASS-Q6':'LPASS-Q6',
            'MSS-Q6':'MSS-Q6',
            'MSS':'MPSS',
            'MPSS':'MPSS',
            'SSC':'SLPI',
            'SSC-Q6':'SSC-Q6',
            'SLPI':'SLPI',
            'XBL':'XBL',
            'APSS':'HYDRA',
            'APPS':'HYDRA',
            'TZ':'TZ',
            }
    
    targetconfigs.update({'image_aliases':image_aliases})
    #Images= ['TZ','XBL','PBL','RPM','LA','APPSBOOT','ADSP','MPSS','SLPI']
    #targetconfigs.update({'images':Images})

    # Emulation machine names
    #EmulationTarget = '10.46.163.10'
    #SessionStartDelay = 10
    
    return targetconfigs

