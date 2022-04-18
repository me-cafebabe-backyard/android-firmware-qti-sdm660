//====================================================================================================//
//================================ Bringup Tool ReadMe.txt ===========================================//
//====================================================================================================//
//
//  Name:                                                                     
//    ReadMe_BringupTool.txt 
//
//  Description:                                                              
//    Instructions on using bringup tool a.k.a. RootCMMBuilder.py
//                                                                            
// Copyright (c) 2012 - 2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.        
//
//
//
//
//                      EDIT HISTORY FOR FILE
//  This section contains comments describing changes made to the module.
//  Notice that changes are listed in reverse chronological order.
//
// when       who             what, where, why
// --------   ---             ---------------------------------------------------------
// 03/16/2016 JBILLING        Created 


This document describes the following:
    - Creating your own cmm script workspace
    - Creating a python dictionary entry
    - Running the script generator
    - Checking the script generator output
    
Release Notes
    Date: 03/16/2016
    First Created.

    
    
Existing limitations
    Internal/External script differentiation not yet implemented
    Dictionary checker does not check that cmm scripts exist on the path given
    menu buttons not yet implemented (vs. menu dropdown, which is implemented)
    python files not yet implemented (can enter python files which get sent to from T32 to OS). coming soon


This document assumes the following:
    Python 2.6 or later is installed and  available to system path
    Should work for Windows, Linux, IOS, but only validated on Windows
    

- Creating your own cmm script workspace
    under the <MetabuildRoot>\common\core\tools\tools directory are different teams' workspaces.
    If you don't have one yet, create one. This can be your sandbox and you can create the directory structure as you choose.
    ****The generator will look for any python file named <somename>_cmm.py****
    Copy one of these files from elsewhere and fill out the dictionary as desired.
    When you run the generator, make sure your script pops up in the menu script in the subsystem specified
    Output menu scripts will be in <MetabuildRoot>\common\core\tools\tools\<TARGETNAME>\
        They will have a name something like std_rootcmm_menu_<SUBSYSTEM>, where <subsystem> is what you entered for 'subsystems' entry in the menu. 
        e.g. .../MSM8998/std_rootcmm_menu_APPS-ARMV8.men should have all the scripts whos 
        dictionary 'subsystems' entry had 'APPS-ARMV8' and were specified for MSM8998 target
    
    
##############################################
##############################################
##
## Creating a python dictionary entry
##
##############################################
##############################################
    your <somename>_cmm.py file is basically just adds a big dictionary to python.
    The generator comes and gets entries from it, filters it by target and subsystem, satisfies pre/post scripts, and spits out scripts
    A template is located at the top of the generator itself (RootCMMBuilder.py). You can use this or copy someone elses <somename>_cmm.py 
    
    ######################
    About script entries
        Script entries are basically objects that appear in the dropdown menu
        The entry's identifier must be unique, because this identifier is used to satisfy prerequisites and postscripts
        The generator will recursively search to satisfy pre/post scripts, so if there are identical script entry idenfiers, things will break.
        
        Note that multiple script entries can refer to the same script. 
        That's because the same script can be used for multiple usecases.
        Also, you may not want your script entry to appear in the menu - it may just be there for a pre/post script for another usecase.
        
    #######################
    About targetconfigs
        targetconfigs is a dictionary passed to each lower <somename>_cmm.py
        it's a list of all the configurations for that target,
        which you can use for arguments in your scripts
        
        These targetconfigs are in the <MetabuildRoot>\common\core\tools\tools\configs\<targetname>.py
        a snippet of some of the options here are: (e.g. from MSM8996.py file)
        
            targetconfigs.update({'T32Installation':'C:\T32'})
            targetconfigs.update({'T32TempFolder':'C:\T32work'})
            targetconfigs.update({'Target':'MSM8996'})
            targetconfigs.update({'TempPath' : '&TEMP'})
            targetconfigs.update({'RootDir' : '&CMMBUILDER_ROOT'})
            
            swimage_to_hwsubsystem_map={
                            'RPM':'RPM-CORTEXM3',
                            'MPSS':'MSS-Q6',
                            etc...
        
        ***you'll at least need to use it for your abspath argument:***
        'abspath'             : os.path.join(targetconfigs['RootDir']
        you can pass target names as arguments to your scripts:
        'arguments'           : [targetconfigs['Target']],
        or as a target specific path:
        'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","hwio",targetconfigs['Target'])
        
    ######################
    Okay, now to the actual entry
    Here's a basic one
    #######################

    CMMBuilderDict.update( 
            {"View HWIO Registers" :                                    #Script Entry Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "View HWIO Registers",    #What appears in the T32 menu
                      'scriptname'          : "hwioreg.per",            #Actual name of script that is called. 
                                                                        #Make sure to include the extension here as T32 will automatically prepend the script with the right command
                                                                        #e.g. per <yourfile>.per, or cd.do <yourfile>.cmm or OS.COMMAND <your python file>.py
                      
                      'arguments'           : [targetconfigs['Target']],#you can pass a variety of things  using targetconfigs
                      'abspath'             : os.path.join(targetconfigs['RootDir'],"systemdrivers","hwio",targetconfigs['Target']), #Needs to be the path to your script
                      'submenu'             : 'HWIO', #Not implemented yet
                      'user-interactive?'   : True,             #If this script doesn't require user interaction, put False, else True. 
                      
                      'subsystems'          : ["all"],          #'all' is special, as it will show up in every subsystem script
                                                                #Else put your particular subsystems, such as ['apps'], or ['rpm','apps']
                                                                #Note that there are hardware-oriented subsystems (such as RPM-CORTEXM3 or MSS-Q6)
                                                                    #These will always be loaded on a t32 window
                                                                    #as opposed to a software-oriented subsystem, such as ADSP or LA, 
                                                                    #Which will be loaded when that subsystem's image ELF file is set up.
                                                                

                      'prerequisites'       : [],       #Prerequisites. attach=> proc will attach first. Also can put Tags from other scripts
                      'show in menu'        : True,     #Show this script in the menu? 
                                                        #(Not all scripts show in dropdown menu - some post-scripts only to be run 
                                                        #after an initial script, or are for postmortem only)
                      'tags'                : "HWIOPER", #For  future implementation
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
                } )
                
                
    ######################
    Here's a more sophisticated entry:
    #######################
    CMMBuilderDict.update( 
            {"tester 2" : #Identifier. This must be unique to every script entry
                     {'dropdown menu name'  : "tester 2",
                      'scriptname'          : "cpuss_dragonlink_olc.cmm", 
                      'arguments'           : ['stuff',os.path.join(os.path.relpath(targetconfigs['RootDir']),"olc","dragonlink",targetconfigs['Target'])],
                      'abspath'             : os.path.join(os.path.relpath(targetconfigs['RootDir']),"olc","dragonlink",targetconfigs['Target']),
                      'submenu'             : 'OLC',
                      'user-interactive?'   : True,             
                      'subsystems'          : ['apps'],
                      'prerequisites'       : ["attach","tester1"],       #Prerequisites - there are several special prereq keywords:
                                                                          #     'attached','break','symbols'
                                                                          #These map to some general script entries, and are meant to guarantee that 
                                                                          #the target processor will be attached/halted/symbols loaded by the time your script runs.
                                                                          
                                                                          #Now, you can also put as many prerequisite script entries of your own in here.
                                                                          #The builder will recursively search through the available dictionary
                                                                          #And place your target script's entry before yours.
                                                                          #Again, it's recursive, so if your prerequisite has prerequisites, the builder will keep
                                                                          #populating until there are none left.
                                                                          #Note that your prerequisites must have the same target/image as your script entry
                                                                          
                                                                          #In the example here, 'tester1' is a prerequisite, but tester1 also has 'attach', so 
                                                                          #the sequence will be attach->tester1->tester 2
                                                                          
                      'show in menu'        : True, 
                      'tags'                : "dragonlink",
                      'menubutton'          : None, 
                      'target'              : 'MSM8998',             
                      'outputfiles'         : None,
                      'returnarguments'     : ['arg1','arg2','arg3'],  #If you specify this, after your script will appear 'ENTRY &arg1 &arg2 &arg3'...
                                                                       #IMPORTANT - these don't have '&' - the builder adds them. 
                                                                            #Juxtapose with postscriptarguemtns, to which the builder doesn't append '&'
                                                                       #These arguments can then be passed to a post script
                                                                       #Note: you can return arguments from your script with a 'ENDDO &arg1 &arg2 &arg3' at the end of your script
                      
                      'postscripts'         : ['AttachManager-Break'], #This works the same way as prerequisites. Scripts will line up after yours. 
                                                                       #Again, things are recursive so if your postscripts have postscripts, they'll keep showing up
                      
                      'postscriptarguments' : ['&arg2','printtolog'],  #Arguments to pass to your postscripts. These will override the default arguments that 
                                                                       #are normally present
                                                                       
                      'postscript prompt'   : True,     #Will prompt user before running postscript.
                                                        #This is a useful option if you want to run your script, then signal the user before the postscript runs
                                                        #Basically - there's another script entry which is the postscriptprompt which is called before your postscript runs
                                                        
                      'liveorsim?'          : "Live", #'Live','Sim' or 'Both'. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
                      'runonpostmortem'     : False,     
                      'runoninit'           : False,  #Run script as soon as the window opens. To be implemented
                      'externalrelease'     : False,
                     }
                } )
                
                
                
##############################################
##############################################
##
## Running the script generator
##
##############################################
##############################################
    Just run 'pythong RootCMMBUilder.py' and it should output things to your <metabuildroot>\common\core\tools\tools\<target>
    A time-stamped build log will be output to <metabuildroot>\common\core\tools\tools\logs
    
    
    
    
    
##############################################
##############################################
##
## Checking the script generator output
##
##############################################
##############################################
    Make sure your script entry got generated! Under the target folder, and in the file: std_rootcmm_menu_<subsystem>.men you should be able to see your usecase.
    If you're not seeing your script or it's not set up correctly, please contact John Billings (jbilling)
    
    
    If you want to put the menu directly in to a T32 window to see how it look - open a T32 window and use the command:
    menu.reprogram <metabuildroot>\common\core\tools\tools\<target>\<yourscript>.men
    
    
    

    
    
    
    
    
    
    
    
    
