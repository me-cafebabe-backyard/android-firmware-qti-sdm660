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
# 04/06/2016 JBILLING     Mature usecases added
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
            {"AreaName":"DragonLink"} #This is the name which will appear in the drop down menu. 
                                      #If it's not specified, will use the filename (e.g. dragonlink)
            )
            
            
    #attach - done with temp script
    
    #copy to temp with timestamp <enter postscript as prompt user to edit>
    #prompt user to edit. OK
    
    #run temp script <prereq: copy to temp, attach> <postscript: ETB collect>
    #prompt 
    #etb collect
    
    #get ATID
    #etb->bin <prereq: get ATID>
    
    #wait 30seconds
    #parser <prereq: wait 15sec>
    
    

    ##Pass arguments from one to the other
    #Dragonlinkdict["DragonLink-scriptcopier"]['arguments']=[os.path.join(dragonlink_script_location,CMMBuilderDict["DragonLink"]['scriptname']),os.path.join(targetconfigs['TempPath'],str(CMMBuilderDict["DragonLink"]['scriptname'])+"_local.cmm")],
    ##These
    #
    #Dragonlinkdict["DragonLink-scriptcopier"]['prerequisites']=["attach"]
    #   <prereq of temp copier> do std_utils EXECUTESCRIPT ERRORHANDLE &METATOOLSDIR\general\attachmanager.cmm attach MSM8998 
    #   <entry is generic copier> copy to temp with a timestamp
    #   <run script as a prompt?> open for edit in temp (pedit)
    #   <actual script. run it from temp dir> do std_utils EXECUTESCRIPT ERRORHANDLE c:\temp\cpuss_dragonlink_local.cmm
    #   <just mark true as postscriptprompt> do std_utils EXECUTESCRIPT ERRORHANDLE &METATOOLSDIR\general\postscriptprompt.cmm dragonlink olc
    #
    #   <custom entry of generic dump_etb script since this needs a postscritp> do std_utils EXECUTESCRIPT ERRORHANDLE &METATOOLSDIR\qdss\MSM8998\dump_etb.cmm c:\temp\cpuss_dragonlink_asldkfjsa.bin 
    #   
    #    
    #   <put this as a postscript to etb dump> do std_utils EXECUTESCRIPT ERRORHANDLE &METATOOLSDIR\sve\pimem_TPDM\MSM8998\trace_tpdm_wrapper.cmm 
    #   LOCAL &traceID
    #   ENTRY &traceID
    #   <put this as a postscript to tpdmwrapper, with passed args> do python script: execute etb to bin script &traceID 
    #   <put this as a postscript to etb to bin script> wait30seconds             
    #   <put this as a postscript to wait30seconds> execute parser c:\temp\etbdump.bin <output from etb->bin script, should be in c:\temp>
    
    #This part actually just adds the wrapper whihc is to grab the ATID
    dragonlink_script_location=os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink",targetconfigs['Target'])
    CMMBuilderDict.update( 
            {"DragonLink copy and pedit utility" : #Enter script to menu via this entry, though teh actual script is listed later
                     {'dropdown menu name'  : "Dragonlink",
                      'description'         : "Dragonlink - Configure the CPUSS DragonLink TPDM/TPDA complex to collect hardware events",
                      'scriptname'          : "std_utils.cmm", #Make sure to include the extension here
                      #usage is: do scriptcopier source destination
                      'arguments'           : ["FILECOPIER",os.path.join(dragonlink_script_location,"cpuss_dragonlink.cmm"),os.path.join(targetconfigs['TempPath'],"cpuss_dragonlink_local.cmm")],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"..","cmm","common"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : "pedit",             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink-modify-message"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["DIALOGMESSAGE","A copy of dragonlink.cmm has been copied to "+os.path.join(targetconfigs['TempPath'],"cpuss_dragonlink_local.cmm")+". Open that file, modify it per instructions, and then press continue"], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )

    #####This actually adds the script, but it's now been copied to a local directory####
    CMMBuilderDict.update( 
            {"DragonLink-modify-message" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "generaldialog.cmm", #Make sure to include the extension here
                      'arguments'           : ["DIALOGMESSAGE","Delay specified. Press Continue button to Continue"],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"general"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink-actualscript"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
                
                
    #####This actually adds the script, but it's now been copied to a local directory####
    CMMBuilderDict.update( 
            {"DragonLink-actualscript" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "cpuss_dragonlink_local.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : targetconfigs['TempPath'],
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink-etbdump"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [os.path.join(targetconfigs['TempPath'],"etbdump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      #Definitely let user prompt before continuing execution
                      'postscript prompt'   : True, 
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
#This is a copy of dump_etb entry, but with postscript being the dragonlink etb->bin parser
    CMMBuilderDict.update( 
            {"DragonLink-etbdump" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "dump_etb.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(targetconfigs['TempPath'],"etb_dump.bin"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink get ATID"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  
                      'externalrelease'     : False,
                     }
                } )
                #####get ATID fro ETB dump parser###
    CMMBuilderDict.update(
            {"DragonLink get ATID" : #gets traceid from user and passes it to script
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "trace_tpdm_wrapper.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "Dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ["traceID"],
                      'postscripts'         : ["dragonlink etb to bin"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["&traceID",os.path.join(targetconfigs['TempPath'],"etb_dump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, 
                      'liveorsim?'          : "Live",
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  
                      'externalrelease'     : False,
                     }
                } )
    
    
                ####sve tool - ETB to bin###
                ###Takes a etb output file and parses it per given ATID###
    CMMBuilderDict.update( 
            {"dragonlink etb to bin" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "etb_to_bin.py", #Make sure to include the extension here
                      #These will get overwritten by preivous script, which lists this as a postscript, but list them anyway to avoid confusion
                      'arguments'           : ["&traceid",os.path.join(targetconfigs['TempPath'],"etb_dump.bin")],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["dragonlink parser"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [os.path.join(targetconfigs['TempPath'],"parsed_etbdump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                ####15 second delay###
                ###delay by a little bit for parser to be done###
    CMMBuilderDict.update( 
            {"dragonlink delay 15 seconds" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "std_utils.cmm", #Make sure to include the extension here
                      #These will get overwritten by preivous script, which lists this as a postscript, but list them anyway to avoid confusion
                      'arguments'           : ["DELAYSECONDS 15"],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"..","cmm","common"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["all"],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "general",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "all",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                ####dragonlinke parser ###
    CMMBuilderDict.update( 
            {"dragonlink parser" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "parse_cpuss_dsb.py", #Make sure to include the extension here
                      #These will get overwritten by preivous script, which lists this as a postscript, but list them anyway to avoid confusion
                      'arguments'           : [os.path.join(targetconfigs['TempPath'],"etb_dump.bin")],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["dragonlink delay 15 seconds"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [],
                      'postscriptarguments' : [], 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                

                
                
                
                
                
                
                
    ##########################################################################################################################################################
    ##########################################################################################################################################################
    #########################################                                                                #################################################
    #########################################                   DragonLink OLC Entry                         #################################################
    #########################################                                                                #################################################
    ##########################################################################################################################################################
    ##########################################################################################################################################################
                
                
#attach - done with temp script
    
    #copy to temp with timestamp <enter postscript as prompt user to edit>
    #prompt user to edit. OK
    
    #run temp script <prereq: copy to temp, attach> <postscript: ETB collect>
    #prompt 
    #etb collect
    
    #get ATID
    #etb->bin <prereq: get ATID>
    
    #wait 30seconds
    #parser <prereq: wait 15sec>
    
    
    #"DragonLink copy and pedit utility"
    #"DragonLink-actualscript"
    #"DragonLink-etbdump"
    #"DragonLink get ATID"
    #"dragonlink etb to bin"
    #"dragonlink delay 15 seconds"
    #"dragonlink parser"
    
    
    
    
    
    
    
    
                
                
    
    CMMBuilderDict.update( 
            {"DragonLink OLC" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "Dragonlink OLC",
                      'description'         : "Dragonlink OLC - Configure the CPUSS DragonLink TPDM/TPDA complex to collect hardware events",
                      'scriptname'          : "cpuss_dragonlink_olc.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink",targetconfigs['Target']),
                      'submenu'             : 'OLC',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink get ATID"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. 
                      'postscript prompt'   : True, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
                
                
                
    '''
    dragonlink_script_location=os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink",targetconfigs['Target'])
    CMMBuilderDict.update( 
            {"DragonLink copy and pedit utility" : #Enter script to menu via this entry, though teh actual script is listed later
                     {'dropdown menu name'  : "Dragonlink",
                      'description'         : "Dragonlink - Configure the CPUSS DragonLink TPDM/TPDA complex to collect hardware events",
                      'scriptname'          : "std_utils.cmm", #Make sure to include the extension here
                      #usage is: do scriptcopier source destination
                      'arguments'           : ["FILECOPIER",os.path.join(dragonlink_script_location,"cpuss_dragonlink.cmm"),os.path.join(targetconfigs['TempPath'],"cpuss_dragonlink_local.cmm")],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"..","cmm","common"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : "pedit",             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink-modify-message"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["DIALOGMESSAGE","A copy of dragonlink.cmm has been copied to "+os.path.join(targetconfigs['TempPath'],"cpuss_dragonlink_local.cmm")+". Open that file, modify it per instructions, and then press continue"], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )

    #####This actually adds the script, but it's now been copied to a local directory####
    CMMBuilderDict.update( 
            {"DragonLink-modify-message" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "generaldialog.cmm", #Make sure to include the extension here
                      'arguments'           : ["DIALOGMESSAGE","Delay specified. Press Continue button to Continue"],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"general"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink-actualscript"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
                
                
    #####This actually adds the script, but it's now been copied to a local directory####
    CMMBuilderDict.update( 
            {"DragonLink-actualscript" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "cpuss_dragonlink_local.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : targetconfigs['TempPath'],
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink-etbdump"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [os.path.join(targetconfigs['TempPath'],"etbdump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      #Definitely let user prompt before continuing execution
                      'postscript prompt'   : True, 
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
#This is a copy of dump_etb entry, but with postscript being the dragonlink etb->bin parser
    CMMBuilderDict.update( 
            {"DragonLink-etbdump" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "dump_etb.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(targetconfigs['TempPath'],"etb_dump.bin"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["DragonLink get ATID"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  
                      'externalrelease'     : False,
                     }
                } )
                #####get ATID fro ETB dump parser###
    CMMBuilderDict.update(
            {"DragonLink get ATID" : #gets traceid from user and passes it to script
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "trace_tpdm_wrapper.cmm", #Make sure to include the extension here
                      'arguments'           : [],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "Dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : ["traceID"],
                      'postscripts'         : ["dragonlink etb to bin"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : ["&traceID",os.path.join(targetconfigs['TempPath'],"etb_dump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, 
                      'liveorsim?'          : "Live",
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  
                      'externalrelease'     : False,
                     }
                } )
    
    
                ####sve tool - ETB to bin###
                ###Takes a etb output file and parses it per given ATID###
    CMMBuilderDict.update( 
            {"dragonlink etb to bin" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "etb_to_bin.py", #Make sure to include the extension here
                      #These will get overwritten by preivous script, which lists this as a postscript, but list them anyway to avoid confusion
                      'arguments'           : ["&traceid",os.path.join(targetconfigs['TempPath'],"etb_dump.bin")],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : ["dragonlink parser"], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [os.path.join(targetconfigs['TempPath'],"parsed_etbdump.bin")], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                ####15 second delay###
                ###delay by a little bit for parser to be done###
    CMMBuilderDict.update( 
            {"dragonlink delay 15 seconds" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "std_utils.cmm", #Make sure to include the extension here
                      #These will get overwritten by preivous script, which lists this as a postscript, but list them anyway to avoid confusion
                      'arguments'           : ["DELAYSECONDS 15"],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"..","cmm","common"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["all"],
                      'prerequisites'       : [],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "general",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "all",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
                      'postscriptarguments' : [], 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                ####dragonlinke parser ###
    CMMBuilderDict.update( 
            {"dragonlink parser" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : None,
                      'description'         : None,
                      'scriptname'          : "parse_cpuss_dsb.py", #Make sure to include the extension here
                      #These will get overwritten by preivous script, which lists this as a postscript, but list them anyway to avoid confusion
                      'arguments'           : [os.path.join(targetconfigs['TempPath'],"etb_dump.bin")],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","dragonlink"),
                      'submenu'             : 'Dragonlink',
                      'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
                      'subsystems'          : ["apps"],
                      'prerequisites'       : ["dragonlink delay 15 seconds"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
                      'tags'                : "dragonlink",
                      'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
                      'target'              : "msm8998",             #target specific or not
                      'outputfiles'         : None,
                      'returnarguments'     : [],
                      'postscripts'         : [],
                      'postscriptarguments' : [], 
                      'postscript prompt'   : False, #Will prompt user before running postscript.
                      'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,
                      'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
                      'externalrelease'     : False,
                     }
                } )
                
                
                
                
                
                
                
    '''
                
                
                
                
                
                
    return CMMBuilderDict
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    #genericdict={     #'dropdown menu name'  : "Dragonlink",
    #                  #'description'         : "Dragonlink - Configure the CPUSS DragonLink TPDM/TPDA complex to collect hardware events",
    #                  #'scriptname'          : "trace_tpdm_wrapper.cmm", #Make sure to include the extension here
    #                  'dropdown menu name'  : None,
    #                  'description'         : None,
    #                  'scriptname'          : "something.cmm", #Make sure to include the extension here
    #                  'arguments'           : [],
    #                  'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"sve","pimem_TPDM",targetconfigs['Target']),
    #                  'submenu'             : 'Dragonlink',
    #                  'user-interactive?'   : True,             #Mainly for cmmbuilder to know if this can be used without user prompt
    #                  'subsystems'          : ["apps"],
    #                  'prerequisites'       : ["attach"],       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
    #                  'show in menu'        : False,
    #                  'tags'                : "Dragonlink",
    #                  'menubutton'          : None, #Use SPARINGLY! This will put a menu button on T32 GUI. Only so much room available.
    #                  'target'              : "msm8998",             #target specific or not
    #                  'outputfiles'         : None,
    #                  'returnarguments'     : [],
    #                  'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
    #                  'postscriptarguments' : [], #arguments to pass to postscripts being called. Make sure to include the '&' if it's a pmacro. 
    #                  'postscript prompt'   : False, #Will prompt user before running postscript.
    #                  'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
    #                  'runonpostmortem'     : False,
    #                  'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
    #                  'externalrelease'     : False,
    #                 }
    #            } 
    #        
    #Dragonlinkdict={"DragonLink-scriptcopier":      genericdict,
    #                "DragonLink-modifyscriptprompt":genericdict,
    #                "DragonLink":                   genericdict, #Actual script. make sure to add postscriptprompt as true
    #                "DragonLink_dumpetb":           genericdict,
    #                "DragonLink_getATID":           genericdict,
    #                "DragonLink_python_etb_to_bin": genericdict,
    #                "DragonLink_wait30seconds":     genericdict,
    #                "DragonLink_parse_etb_output":  genericdict
    #                }
    #                
    ##These are teh paths and script names
    #Dragonlinkdict["DragonLink-scriptcopier"]['scriptname']="file_copier.cmm"
    #Dragonlinkdict["DragonLink-scriptcopier"]['abspath']=os.path.join(os.path.relpath(targetconfigs['RootDir']),"general")
    #
    #
    #####Fill out the name and filepath to all the scripts
    #Dragonlinkdict["DragonLink-modifyscriptprompt"]['scriptname']="cpuss_dragonlink.cmm"
    #Dragonlinkdict["DragonLink-modifyscriptprompt"]['abspath']=
    #
    #Dragonlinkdict["DragonLink"]['scriptname']=[]
    #Dragonlinkdict["DragonLink"]['abspath']=[]
    #
    #Dragonlinkdict["DragonLink_dumpetb"]['scriptname']=[]
    #Dragonlinkdict["DragonLink_dumpetb"]['abspath']=[]
    #
    #Dragonlinkdict["DragonLink_python_etb_to_bin"]['scriptname']=[]
    #Dragonlinkdict["DragonLink_python_etb_to_bin"]['abspath']=[]
    #
    #Dragonlinkdict["DragonLink_wait30seconds"]['scriptname']=[]
    #Dragonlinkdict["DragonLink_wait30seconds"]['abspath']=[]
    #
    #Dragonlinkdict["DragonLink_parse_etb_output"]['scriptname']=[]
    #Dragonlinkdict["DragonLink_parse_etb_output"]['abspath']=[]
    #
    
    