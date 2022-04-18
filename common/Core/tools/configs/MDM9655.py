"""
===============================================================================

 MDM9X55.py

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
    #Target = 'MDM9655'
    #TempPath = '&TEMP'
    #RootDir = '&CMMBUILDER_ROOT'
    targetconfigs.update({'T32Installation':'C:\T32'})
    targetconfigs.update({'T32TempFolder':'C:\T32work'})
    targetconfigs.update({'Target':'MDM9655'})
    targetconfigs.update({'TempPath' : '&TEMP'})
    targetconfigs.update({'RootDir' : '&METATOOLSDIR'})
    targetconfigs.update({'TargetFamily' : 'bear'})
    #For release vs internal flavors
    flavors   = { 'internal' : 'internal', 'external' : 'external'}
    targetconfigs.update({'flavors':flavors})
    
#T32ConfigFile    = os.environ['METABUILD'] + '\\common\\Core\\t32\\mdm9655.ts2'
#T32Container     = '\"//Root/DAP/Podbus Device Chain/Power Trace Ethernet/'
#T32SimContainer = '\"//Root/Simulator/'

# Target related setup options
#defaultstart = ['Apps0']
#
## Configuration for all cores
#Apps0Config = { 'IC' : 'NETASSIST', 'PORT' : '25360', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
#RPMConfig =   { 'IC' : 'NETASSIST', 'PORT' : '25400', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
#MPSSConfig  = { 'IC' : 'NETASSIST', 'PORT' : '25401', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
#IPAConfig  = { 'IC' : 'NETASSIST', 'PORT' : '25402', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
#ARM32SimConfig  = { 'IC' : 'NETASSIST', 'PORT' : '10000', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
#
#QDSPSimConfig   = { 'IC' : 'NETASSIST', 'PORT' : '10001', 'PACKLEN' : '1024', 'NODE' : 'LOCALHOST' }
#
#CoreConfigs = { 'RPM' : RPMConfig, 'APPS0' : Apps0Config, 'APSS' : Apps0Config, 'MPSS' : MPSSConfig, 'ARM32Sim' : ARM32SimConfig, 'QDSP6Sim' : QDSPSimConfig }

    CoreNames   = { 'RPM' : 'RPM', 'APPS0' : 'APSS','APPS0' : 'APPS0', 'MPSS' : 'MPSS', 'ARM32Sim' : 'ARM32Sim', 'ARM64Sim' : 'ARM64Sim', 'QDSP6Sim' : 'QDSPSim' }
    targetconfigs.update({'corenames':CoreNames})
    
    Cores = ['RPM','APPS','APPS0','MPSS','IPA']
    targetconfigs.update({'cores':Cores})
    
    #Scripts will be made from each of these
    subsystems = ['RPM-CORTEXM3','MSS-Q6','APPS-CORTEXA5']
    targetconfigs.update({'subsystems':subsystems})
    
    #Scripts will be made from each of these too
    software_images=['RPM','MPSS','TN','SBL1','LE','TZ']
    targetconfigs.update({'software_images':software_images})
    
    #What s/w runs on what hardware
    swimage_to_hwsubsystem_map={
            'RPM':'RPM-CORTEXM3',
            'TN':'APPS-CORTEXA5',
            'LE':'APPS-CORTEXA5',
            'SBL1':'APPS-CORTEXA5',
            'MPSS':'MSS-Q6'
            }
    targetconfigs.update({'swimage_to_hwsubsystem_map':swimage_to_hwsubsystem_map})
    
    
    subsystemprofile_map={
                    'RPM-CORTEXM3':     ['RPM','RPM-CORTEXM3'],
                    'MSS-Q6':           ['MSS-Q6','MPSS','MODEM','GPSSS','GSS'],
                    'APPS-CORTEXA5-MN':    ['APPS-CORTEXA5-MN','APPS-CORTEXA5','LE','SBL1','TZ','APPS','APSS'],
                    'APPS-CORTEXA5-LE':    ['APPS-CORTEXA5-LE','APPS-CORTEXA5','MN','SBL1','TZ','APPS','APSS'],
                    }
    targetconfigs.update({'subsystemprofile_map':subsystemprofile_map})
    
    
    #Other terms that folks may use to label images in their dictionary entries
    image_aliases={
        'RPM':'RPM',
        'RPM-CORTEXM3':'RPM-CORTEXM3',
        'MSS-Q6':'MSS-Q6',
        'MSS':'MPSS',
        'MPSS':'MPSS',
        'APSS':'APPS',
        'APPS':'APPS',
        'APPS-CORTEXA5':'APPS-CORTEXA5',
        'LE':'LE',
        'TN':'TN',
        'TZ':'TZ',
        'SBL1':'SBL1',
        }
        
    targetconfigs.update({'image_aliases':image_aliases})
    
    
    #Images= ['TZ','SBL1','PBL','RPM','LA','APPSBOOT','MPSS']
    #targetconfigs.update({'images':Images})

    # Emulation machine names
    #EmulationTarget = '10.46.163.10'
    #SessionStartDelay = 10
    
    return targetconfigs

