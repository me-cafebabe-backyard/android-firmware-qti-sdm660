#!/usr/bin/env python
#============================================================================
#  Name:                                                                     
#    RootCMMBuilder.py
#
#  Description:                                                              
#    Main script generator for all scripts registered under core\tools\tools
#
#  Usage
#      'python RootCMMBuilder.py'
#      You should see logs printed out to core\tools\tools\logs\
#      If success, a file called 'SuccessLog.txt' will appear in this same directory
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
# 06/23/2016 JBILLING     Most filetypes moved to std_utils (exe,bat,py,pl)
# 04/12/2016 JBILLING     Menu button utility added
# 04/07/2016 JBILLING     More file extensions added
# 03/31/2016 JBILLING     Help menu generation added
# 02/17/2016 JBILLING     Created
#
import os,sys
import subprocess 
import string
import re
import glob
import fnmatch
import stat
Targets = ['MSM8996','MSM8998','MDM9655','MDM9645','SDM660','SDM630']
global TargetConfigDict
TargetConfigDict={'MSM8996':'MSM8996',
                  'MSM8998':'MSM8998',
                  'MDM9650':'MDM9655',
                  'MDM9655':'MDM9655',
                  'MDM9645':'MDM9645',
                  'SDM660' :'SDM660',
                  'SDM630' :'SDM630',
				  }
#Enable this to exercise menu building logic
global TestsEnable
TestsEnable=False

global CurrentTarget


global SpecialOptionKeywords
global SpecialOptionSatisfiedFlag
SpecialOptionKeywords={'attach':"AttachManager-Attach" ,'break':"AttachManager-Break",'halt':"AttachManager-Break",'symbols':"SymbolManager-Loadsyms",'hwio':"MainHWIOScript"}
SpecialOptionSatisfiedFlag={'attach':False,'break':False,'halt':False,'symbols':False,'hwio':False}
global MenuScriptSubroutines
MenuScriptSubroutines=["CREATEMENU","ADDMENUBUTTONS","HELP"]

global MenuConfigSriptName
MenuConfigSriptName='std_rootcmm_menu'
global PostMortemScript
PostMortemScript='std_rootpostmortem'
global InitScript
InitScript='std_rootinit.cmm'

global BuildLog
global SuccessLog
BuildLog="CMMBuilderLog_"
#Package Warehouse will look for this file for success case
SuccessLog="SuccessLog.txt"
    
    
global ScriptDictTemplate
ScriptDictTemplate={
    "Template" :
             {'dropdown menu name'  : "Template",
              'description'         : "description",
              'scriptname'          : "template.cmm", #Make sure to include the extension here
              'arguments'           : [],
              'abspath'             : None,
              'submenu'             : None,
              'user-interactive?'   : False,             #Mainly for cmmbuilder to know if this can be used without user prompt
              'subsystems'          : "all",
              'prerequisites'       : None,       #Prerequisites. Attached=> proc will attach first. Also can put Tags from other scripts
              'show in menu'        : False, #Show this script in the menu? (Not all scripts show in menu - some post-scripts only to be run after an initial script)
              'tags'                : None,
              'menubutton'          : None, #Use SPARINGLY! Use bitmap code from T32. This will put a menu button on T32 GUI. We only have so much room...
              'target'              : "All",             #target specific or not
              'outputfiles'         : [], #Needs to be an array
              'returnarguments'     : ["arg1","arg2","arg3"],
              'postscripts'         : [], #Other scripts to be run immediately after this one. Use top dictionary name for this one
              'postscriptarguments' : ["arg1","arg2"], #arguments to pass to postscripts being called. 
              'postscript prompt'   : False, #Will prompt user before running postscript.
              'liveorsim?'          : "Live", #Live,Sim or Both. Determines if script is run on a live T32 window, Simulator/ramdump T32 window, or on both
              'runonpostmortem'     : False,
              'runoninit'           : False,  #Run script as soon as the window opens. Used more for sim scripts
              'externalrelease'     : False,
             }
}
############################# Globals ############################
default_indent="\t"
DEBUGMODE=False

FILEPATTERNS_ICONS={'.cmm':':FLASH','.per':':CHIP', '.men':':ACONFIG','.t32':':ACONFIG','.opt':':ACONFIG','.py':':ACONFIG','.exe':':ACONFIG'}

#most file types simply handled in std_utils now
#OS_FILETYPES=['.py','.pl','.exe','.exe','.sh','.bat']
OS_FILETYPES=['.sh']
FILEPATTERNS_CMDS={'.cmm':'do std_utils EXECUTESCRIPT ERRORHANDLE','.per':'per.view', '.men':'do std_utils EXECUTESCRIPT ERRORHANDLE', '.t32':'do std_utils EXECUTESCRIPT ERRORHANDLE', '.opt':'task.option','.py':'do std_utils EXECUTESCRIPT ERRORHANDLE','.pl':'do std_utils EXECUTESCRIPT ERRORHANDLE','.exe':'do std_utils EXECUTESCRIPT ERRORHANDLE','.sh':'','.bat':'do std_utils EXECUTESCRIPT ERRORHANDLE'}
##########################################################################
############################ Subroutines #################################
##########################################################################




##########################################################################
##
##      importscripts
##      Private function
##      Description:
##          This method traverses the file structure for files with <script_subarea>_cmm.py
##          Those files are assumed to have script dictionary entries, which are imported
##          and then filtered out via target and subsystem.
##          The completed dictionary, which is target and subsystem specific,
##          is returned for use in generating scripts
##########################################################################
def importscripts(targetconfigs,subsystem):
    #Walk directory for all *_cmm.py files.
    

    SubFileDict={}
    
    for root, dirs, files in os.walk(RootDirectory):
        for scriptfile in files:
            if scriptfile.endswith('_cmm.py'):
                #Testing handle
                if (TestsEnable is False) and ('tester' in scriptfile):
                    continue
                
                print "Processing for "+subsystem+": "+scriptfile
                
                #########################################
                ## Get the filename we're under and assemble
                ## the basics of the dictionary
                #########################################
                sys.path.append(root)
                #Nest subscripts by subsystem, which we get from directory structure
                script_subarea=os.path.basename(os.path.abspath(os.path.join(root,'..')))
                if script_subarea in 'tools':
                    script_subarea=os.path.basename(root)
                if script_subarea not in SubFileDict.keys():
                    #This entry may have to be cleaned up at end of function
                    SubFileDict.update({script_subarea:{}})
                #Get script info from the subsystem
                filename=scriptfile[:-3] #trim off suffix
                
                #########################################
                ## Import the specific file's dictionary entries
                #########################################
                #import the tech team's dictionary
                scriptdictgenerator=__import__(filename)
                currentdict=scriptdictgenerator.CreateDictionary(targetconfigs)
                
                
                
                #########################################
                ## Filter out the dictionary per target and subsystem
                #########################################
                subsystem_dictionary=FilterDictBySubsystem(currentdict,subsystem,targetconfigs)
                #Now clean up any remaining empty dictionaries
                add_dictionaryflag=True
                
                if len(subsystem_dictionary.keys()) is 1:
                    #If the entry is only a title entry (AreaName) or if it's empty, don't add it.
                    if 'AreaName' in subsystem_dictionary.keys():
                        add_dictionaryflag=False
                    #Also if the dictionary right below it is empty, don't add it
                    #firstentry=subsystem_dictionary.keys()[0]
                    #if len(subsystem_dictionary[firstentry]) is 0:
                    #    add_dictionaryflag=False
                    
                if len(subsystem_dictionary) is 0:
                    add_dictionaryflag=False
                
                #Add the dictionary if applicable
                if add_dictionaryflag is True:
                    SubFileDict[script_subarea].update({filename:subsystem_dictionary})
    
                #Remove any empty dict entries remaining from adding them at the beginning of the function
                for key in SubFileDict.keys():
                    if len(SubFileDict[key]) is 0:
                        del SubFileDict[key]
                
    return SubFileDict
    
    
def FilterDictBySubsystem(givendict,subsystem,targetconfigs):

    #Keywords: 
    
    #subsystems={'MSS-Q6':'MSS-Q6','APPS':'APPS','APSS','APPS'}
    #This is what will come in via subsystem argument
    #subsystems=['MSS-Q6','MPSS','WLAN','LPASS-Q6','ADSP','SSC-Q6','SLPI','LA','WP','APPS']
    #This is what the script dictionary entry has to match to
    #subsystemmap={'MPSS':'MSS-Q6','WLAN':'MSS-Q6','ADSP':'LPASS-Q6','SLPI':'SSC-Q6'}
    
    subsystemmap=targetconfigs['image_aliases']
    #sequence:
    #   come through for subsystems (lpass,mpss etc)
    #   come through for images (tz,mpss,wlan,adsp etc.)
    
    
    for newkey in givendict.keys():
        if newkey is 'AreaName':
            continue
        #check if subsystem and target matches. if not, remove that dictionary entry
        if 'subsystems' in givendict[newkey].keys():
            
            
            ################################################
            ##### strip out entries based on subsystem #####
            ################################################
            subsys_entries=givendict[newkey]['subsystems']
            if subsys_entries is None:
                scriptdictfailure(newkey,givendict[newkey],"Error! Subsystem not found for target "+targetconfigs['Target']+". Script Identifier: "+newkey)
            if len(subsys_entries) is 0:
                print "Warning: Length of 'subsystems' entry for script dictionary"+newkey+"is 0"
                del givendict[newkey]
                continue
            ################################################
            ##### strip out entries if external build  #####
            ################################################
            if 'external' in targetconfigs['Flavor']:
                if givendict[newkey]['externalrelease'] is False:
                    print "Removing "+newkey+" for external release build flavor"
                    del givendict[newkey]
                    continue
                
            #subsys_entries is a list. Go through it and check if there's a match
            #check if there are shared entries between that and targetcfg entries
            #we basically need to process through two lists to find if there are overlapping matches
            
            #If script should be in all subsystems, then don't delete
            if 'ALL' not in str(subsys_entries).upper():
                    
                    #dict entry gives, say ['mpss',adsp,rpm]
                    #'LPASS-Q6':         ['LPASS-Q6','ADSP','LPASS','AUDIO',...],
                    matchfound=False
                    for givensubsystem in givendict[newkey]['subsystems']:
                        for image in targetconfigs['subsystemprofile_map'][subsystem]:
                            if (givensubsystem.upper() in image.upper()) and (image.upper() in givensubsystem.upper()):
                                matchfound=True
                    if matchfound is False:
                        del givendict[newkey]
                        continue
                    
                    
                    
            ######################################
            ##### Now do the same for target #####
            ######################################
            subsys_targets=givendict[newkey]["target"]
            if subsys_targets is None:
                scriptdictfailure(newkey,givendict[newkey],"Error! Target not found for target "+targetconfigs['Target']+". Script Identifier: "+newkey)
            if len(subsys_targets) is 0:
                print "Warning: Length of 'targets' entry for script dictionary"+newkey+"is 0"
                del givendict[newkey]
                continue

            #If script should be in all targets, then don't delete
            if 'ALL' not in str(subsys_targets).upper():
                        
                    if type(subsys_targets) is str:
                        subsys_targets=[subsys_targets]
                        #scriptdictfailure(newkey,givendict[newkey],"Error! Target is not a string")
                    #later need to turn all 'target' entries into list
                    
                    clean_target_entries=[]
                    
                    for subsys_target in subsys_targets:
                        if subsys_target.upper() in targetconfigs['Target'].upper():
                            clean_target_entries.append(subsys_target.upper())
                    #then isolate to target - check if target is in given dict        
                    if len(clean_target_entries) > 0:
                        matchfound=False
                        for target_entry in clean_target_entries:
                            if targetconfigs['Target'].upper() in str(target_entry).upper():
                                matchfound=True
                        if matchfound is False:
                            del givendict[newkey]
                            continue
                    else:
                        del givendict[newkey]
                        continue
        
        #Call recursively to go to next level
        else:
            #call recursively: filter out lower level dictionary, then replace entry with return value
            filtered_entry=FilterDictBySubsystem(givendict[newkey],subsystem,targetconfigs)
            del givendict[newkey]
            #Don't add dictionary back in if it's empty or if the only entry is 'AreaName'
            if not ((len(givendict.keys()) is 1) and ('AreaName' in givendict.keys())):
                givendict.update(filtered_entry)

    return givendict
            
def getpath():
    
    global RootDirectory
    if os.path.exists(os.path.dirname(sys.argv[0])):
        RootDirectory=os.path.abspath(os.path.dirname(sys.argv[0]))
    elif os.path.exists(os.path.join(os.getcwd(),os.path.dirname(sys.argv[0]))):
        RootDirectory=os.path.join(os.getcwd(),os.path.dirname(sys.argv[0]))
    else:
        RootDirectory=os.path.abspath(os.getcwd())
        
def macro_incr_indent(string):
    return (string +"\t")
    
def macro_decr_indent(string):
    return string[:-1]

    
def buildmenubuttons(SubFileDict,menuheading,targetconfigs):
    indent = default_indent
    writetextline(" \n")
    writetextline(" \n")
    writetextline("////////////////////////////////////////                               \n")
    writetextline("//                                                                     \n")
    writetextline("//            ADDMENUBUTTONS                                                     \n")
    writetextline("//            Creates dropdown menu for "+menuheading+"                  \n")
    writetextline("//                                                                     \n")
    writetextline("/////////////////////////////////////////                              \n")
    writetextline("ADDMENUBUTTONS:                                                            \n")
    writetextline(indent+" \n")
    indent=macro_incr_indent(indent)
    writetextline(indent+" \n")
    
    #Bulk of subroutine
    ScriptMenuButtonDictionary={}
    #search recursively through dictionary to get valid menu button entries
    sorted_list=sorted(SubFileDict.keys())
    for subsystem in sorted_list:
        subsystemdict=SubFileDict[subsystem]
        for areakey in subsystemdict.keys():
            if type(subsystemdict[areakey]) is not dict:
                kill("Error! subsystem dictionary "+subsystem+" is not properly nested")

            ScriptMenuButtonDictionary.update(getsubdictmenubottons(subsystemdict[areakey],areakey,ScriptMenuButtonDictionary))
            
    
    #writetextline(indent+"MENU.PROGRAM\n")
    #writetextline(indent+"(\n")
    #indent=macro_incr_indent(indent)
    #writetextline(indent+"ADD \n")
    #writetextline(indent+"TOOLBAR \n")
    #writetextline(indent+"( \n")
    indent=macro_incr_indent(indent)
    
    for key in ScriptMenuButtonDictionary.keys():
        
        buttonsymbol=ScriptMenuButtonDictionary[key]['menubutton']
        if "[" in buttonsymbol[0]:
            buttonsymbol=buttonsymbol[1:]
        if "]" in buttonsymbol[-1]:
            buttonsymbol=buttonsymbol[0:-1]
        if "," not in buttonsymbol:
            buttonsymbol="_,X,"+buttonsymbol
        
        name=ScriptMenuButtonDictionary[key]['dropdown menu name']
        subroutine=key.upper().replace(" ","_")
        thisscriptname=os.path.join(targetconfigs['RootDir'],targetconfigs['Target'],os.path.basename(targetconfigs['thisscriptname']))
        #writetextline(indent + "TOOLITEM \""+name+"\" \""+buttonsymbol+"\" \"DO std_utils EXECUTESCRIPT ERRORHANDLE "+thisscriptname+" "+subroutine+" BUTTONPROMPT\""+"\n\n")   
        writetextline(indent + "MENU.ADDTOOL \""+name+"\" \""+buttonsymbol+"\" \"DO std_utils EXECUTESCRIPT ERRORHANDLE "+thisscriptname+" "+subroutine+" BUTTONPROMPT\""+"\n\n")   
    #menu.addtool "thing" "_,X,:time" "do std_utils"
    
    #indent = macro_decr_indent(indent)
    #writetextline(indent+")\n")
    #indent = macro_decr_indent(indent)
    #writetextline(indent+")\n")
    
    writetextline(indent+"\n")
    writetextline(indent+"RETURN                                                            \n")
    indent = macro_decr_indent(indent)
    writetextline(" \n")
    indent = default_indent
    writetextline("\n")
    writetextline("\n")
    writetextline("\n")
    
    
    return
    
def getsubdictmenubottons(dictentry,areakey,descriptiondictionary):

        
            if 'AreaName' in dictentry.keys():
                    submenuname=dictentry['AreaName']
            elif '_cmm' in areakey:
                    submenuname=areakey[:-4]
            else:
                    submenuname=areakey
            for newkey in dictentry.keys():
            
                #Don't write an entry if it's just menu name entry
                if newkey is 'AreaName':
                    continue
                
                #If we're at the lowest level, just add descriptor to the dictionary
                if 'menubutton' in dictentry[newkey].keys():
                    if dictentry[newkey]['menubutton'] is not None:
                        descriptiondictionary.update({newkey:dictentry[newkey]})
                    
                #If it's another dictionary, call function recursively
                else:
                    descriptiondictionary=getsubdictmenubottons(dictentry[newkey],newkey,descriptiondictionary)
                    
            
            return descriptiondictionary
            
            
def buildhelpsubroutine(SubFileDict,menuheading):
    indent = default_indent
    writetextline(" \n")
    writetextline(" \n")
    writetextline("////////////////////////////////////////                               \n")
    writetextline("//                                                                     \n")
    writetextline("//            HELP                                                     \n")
    writetextline("//            Displays available tools for "+menuheading+"                  \n")
    writetextline("//                                                                     \n")
    writetextline("/////////////////////////////////////////                              \n")
    writetextline("HELP:                                                            \n")
    writetextline(" \n")
    indent=macro_incr_indent(indent)
    writetextline(indent+" \n")
    
    #Bulk of subroutine
    
    ScriptDescriptionDictionary={}
    #search recursively through dictionary to get descriptions
    sorted_list=sorted(SubFileDict.keys())
    for subsystem in sorted_list:
        subsystemdict=SubFileDict[subsystem]
        for areakey in subsystemdict.keys():
            if type(subsystemdict[areakey]) is not dict:
                kill("Error! subsystem dictionary "+subsystem+" is not properly nested")

            ScriptDescriptionDictionary.update(getsubdictdescriptors(subsystemdict[areakey],areakey,ScriptDescriptionDictionary))
            
    ########################################        
    ### Calculate text formatting numbers
    numentries=len(ScriptDescriptionDictionary.keys())
    areaheight=str(numentries+12)
    keylist=ScriptDescriptionDictionary.keys()
    longestkey_textlength=0
    
    for key in keylist:
        if len(str(key))>longestkey_textlength:
            longestkey_textlength=len(str(key))
    longestkey_textlength=longestkey_textlength+1
    
    #Get the max possible width of the window
    longestfulltextlength=0
    for key in keylist:
        descriptionlength=len(str(ScriptDescriptionDictionary[key]))
        fulltextlength=5+longestkey_textlength+descriptionlength+8
        if fulltextlength>longestfulltextlength:
            longestfulltextlength=fulltextlength
    
    ##################################################
    ### Now write the print message
    areaname=menuheading.replace(" ","")
                                                                                              
    
    writetextline(indent+"AREA.CREATE "+areaname+" "+str(longestfulltextlength)+". "+areaheight+".                        \n")
    writetextline(indent+"AREA.SELECT "+areaname+"                                             \n")
    writetextline(indent+"WINPOS 60% 29. "+str(longestfulltextlength)+". "+areaheight+".                               \n")
    writetextline(indent+"AREA.VIEW "+areaname+"                                               \n")
    writetextline(indent+"                                                                 \n")
    writetextline(indent+"//HEADER \""+menuheading+" Help window\"                         \n")
    writetextline(indent+"                                                                 \n")
    writetextline(indent+"                                                                 \n")
    writetextline(indent+"PRINT \" ///////////////////////////////////////////////////////////////////\"\n")
    writetextline(indent+"PRINT \" /////////////////// "+menuheading+" Help //////////////////////////\"\n")
    writetextline(indent+"PRINT \" ///////////////////////////////////////////////////////////////////\"\n")
    writetextline(indent+"PRINT \" //\" \n")
    writetextline(indent+"PRINT \" // The following are the available tools. \" \n")
    writetextline(indent+"PRINT \" // Use the dropdown menu labeled "+menuheading+" \" \n")
    writetextline(indent+"PRINT \" // To navigate to your desired script \" \n")
    writetextline(indent+"PRINT \" //\" \n")
    writetextline(indent+"PRINT \" ///////////////////////////////////////////////////////////////////\"\n")
    writetextline(indent+"PRINT \" //\" \n")
    sorted_list=sorted(ScriptDescriptionDictionary.keys())
    
    for entry in sorted_list:
        writetextline(indent+"PRINT \" //  "+str(entry))
        #calculate and write out text for a formatted look
        entrylength=len(str(entry))
        spacelength=longestkey_textlength-entrylength
        description=ScriptDescriptionDictionary[entry]
        for idx in range(spacelength):
            writetextline(" ")
        writetextline(": "+str(description)+"\" \n")
    writetextline(indent+"PRINT \" //\" \n")
    writetextline(indent+"PRINT \" ///////////////////////////////////////////////////////////////////\"\n")
    
    

    writetextline("\n")
    writetextline("\n")
    writetextline(indent+"RETURN                                                            \n")
    indent = macro_decr_indent(indent)
    writetextline(" \n")
    indent = default_indent
    writetextline("\n")
    writetextline("\n")
    writetextline("\n")
    return
    
def getsubdictdescriptors(dictentry,areakey,descriptiondictionary):

        
            if 'AreaName' in dictentry.keys():
                    submenuname=dictentry['AreaName']
            elif '_cmm' in areakey:
                    submenuname=areakey[:-4]
            else:
                    submenuname=areakey
            for newkey in dictentry.keys():
            
                #Don't write an entry if it's just menu name entry
                if newkey is 'AreaName':
                    continue
                
                #If we're at the lowest level, just add descriptor to the dictionary
                if 'description' in dictentry[newkey].keys():
                    descriptiondictionary.update({newkey:dictentry[newkey]['description']})
                    
                #If it's another dictionary, call function recursively
                else:
                    descriptiondictionary=getsubdictdescriptors(dictentry[newkey],newkey,descriptiondictionary)
                    
            
            return descriptiondictionary
    
    
def buildmenus(SubFileDict,menuheading,targetconfigs):
    
    
    
    indent = default_indent
    writetextline(" \n")
    writetextline(" \n")
    writetextline("////////////////////////////////////////                               \n")
    writetextline("//                                                                     \n")
    writetextline("//            CREATEMENU                                                     \n")
    writetextline("//            Creates dropdown menu for "+menuheading+"                  \n")
    writetextline("//                                                                     \n")
    writetextline("/////////////////////////////////////////                              \n")
    writetextline("CREATEMENU:                                                            \n")
    writetextline(" \n")
    indent=macro_incr_indent(indent)
    writetextline(indent+"MENU.REPROGRAM\n")
    writetextline(indent+"(\n")
    indent=macro_incr_indent(indent)
    writetextline(indent+"ADD \n")
    writetextline(indent+"MENU \n")
    writetextline(indent+"( \n")
    indent=macro_incr_indent(indent)
    writetextline(indent + "POPUP \"[:CORRELATE]&"+menuheading+"\" \n")
    writetextline(indent + "( \n")
    indent=macro_incr_indent(indent)
    
    
    
    #fptr = open(filename, 'w')
    #indent = default_indent
    sorted_list=sorted(SubFileDict.keys())
    for subsystem in sorted_list:
        #print the subsystem menu
        
        

        writetextline(indent + "POPUP \"[:PSTEP]&" + subsystem + "\" \n")
        writetextline(indent + "( \n")
        indent=macro_incr_indent(indent)
        subsystemdict=SubFileDict[subsystem]
        
        #recursively print submenus within that
        #within each menu print out the script command.
        for areakey in subsystemdict.keys():
            if type(subsystemdict[areakey]) is not dict:
                kill("Error! subsystem dictionary "+subsystem+" is not properly nested")

            indent=printsubmenu(subsystemdict[areakey],areakey,indent,targetconfigs)

            
            
        indent=macro_decr_indent(indent)
        writetextline(indent + ") \n")
        
            
            
    #There were 2 indents incremented before all the for loops
    #Decrement indents twice to get back to 0.
    indent = macro_decr_indent(indent)
    writetextline(indent + ") \n")
    indent = macro_decr_indent(indent)
    writetextline(indent + ") \n")
    indent = macro_decr_indent(indent)
    writetextline(indent + ") \n")
    indent = macro_decr_indent(indent)
    writetextline(indent+"\n")
    writetextline(indent+"RETURN SUCCESS")
    
    indent = default_indent
    writetextline("\n")
    writetextline("\n")
    writetextline("\n")
    
    
    
    
def buildpostmortemscript(SubFileDict,filename,targetconfigs):

    sorted_list=sorted(SubFileDict.keys())
    opennewfile(filename)
    indent = default_indent
    
    import datetime
    writetextline("////////////////////////////////////////\n")
    writetextline("//\n")
    writetextline("//   Dump analysis script\n")
    writetextline("//   Autogenerated - DO NOT MODIFY\n")
    writetextline("//   Date: "+str(datetime.datetime.now())+" \n")
    writetextline("//   COPYRIGHT QUALCOMM INC 2016\n")
    writetextline("//\n")
    writetextline("////////////////////////////////////////\n")
    writetextline("\n")
    writetextline("\n")

    #indent = macro_incr_indent(indent)
    
    
    for subsystem in sorted_list:
        subsystemdict=SubFileDict[subsystem]
        for areakey in subsystemdict.keys():
            if type(subsystemdict[areakey]) is not dict:
                kill("Error! subsystem dictionary "+subsystem+" is not properly nested")
            
            indent=printpostmortemscript(subsystemdict[areakey],areakey,indent,targetconfigs)
        indent=macro_decr_indent(indent)
    writetextline("\n")
    writetextline("\n")
    closefile()
    
def printpostmortemscript(dictentry,areakey,indent,targetconfigs):

            if 'AreaName' in dictentry.keys():
                    submenuname=dictentry['AreaName']
            elif '_cmm' in areakey:
                    submenuname=areakey[:-4]
            else:
                    submenuname=areakey
                    
            indent=macro_incr_indent(indent)
            
            for newkey in dictentry.keys():
                
                #Don't write an entry if it's just menu name entry
                if newkey is 'AreaName':
                    continue
                #We're nested as far as we need. start writing entries
                if 'scriptname' in dictentry[newkey].keys():
                    #If we're at the lowest level, just give the identifier and printscriptentry 
                    #will traverse the parent dictionary for the entry
                    
                    #These are possible prerequisites. 
                    #Since script searching is recursive, set a value at the top
                    #so that we don't, for example, try and attach between every prereq script
                    for keyword in SpecialOptionSatisfiedFlag.keys():
                        SpecialOptionSatisfiedFlag[keyword]=False
                    indent=printscriptentry(newkey,indent,'postmortem',None,targetconfigs)

                    #print indent+"\nFound a low level script dict\n"
                #If it's another dictionary, call function recursively
                else:
                    indent=printpostmortemscript(dictentry[newkey],newkey,indent,targetconfigs)
                    
                    
            indent=macro_decr_indent(indent)
            writetextline(indent +"\n")
                
            return indent
                
                
def printsubmenu(dictentry,areakey,indent,targetconfigs):

            
           
            if 'AreaName' in dictentry.keys():
                    submenuname=dictentry['AreaName']
            elif '_cmm' in areakey:
                    submenuname=areakey[:-4]
            else:
                    submenuname=areakey
                    
                    
            writetextline(indent + "POPUP \"[:PSTEP]&" + submenuname + "\" \n")
            writetextline(indent + "( \n")
            
            indent=macro_incr_indent(indent)
            
            for newkey in dictentry.keys():
                
                #Don't write an entry if it's just menu name entry
                if newkey is 'AreaName':
                    continue
                #We're nested as far as we need. start writing entries
                if 'scriptname' in dictentry[newkey].keys():

                    #indent=printscriptentry(dictentry[newkey],indent)
                    #newkey should be the unique script identifier
                    #If we're at the lowest level, just give the identifier and printscriptentry 
                    #will traverse the parent dictionary for the entry
                    
                    #These are possible prerequisites. 
                    #Since script searching is recursive, set a value at the top
                    #so that we don't, for example, try and attach between every prereq script
                    for keyword in SpecialOptionSatisfiedFlag.keys():
                        SpecialOptionSatisfiedFlag[keyword]=False
                    #indent=printscriptentry(newkey,indent,None,'dontwritemenu')
                    indent=printscriptentry(newkey,indent,"printmenu",None,targetconfigs)
                    #indent=printscriptentry(newkey,indent,'dontwritemenu',None)

                    #print indent+"\nFound a low level script dict\n"
                #If it's another dictionary, call function recursively
                else:
                    indent=printsubmenu(dictentry[newkey],newkey,indent,targetconfigs)
                    
            
            
            indent=macro_decr_indent(indent)
            
            
            writetextline(indent + ") \n")
            
                    
            return indent
            


#////////////////////////////////////////////
#//     
#//     Function:   printscriptentry
#//     Description: Where the rubber meets the road. This prints out the entry to menu file
#//     Expected Input: 
#//             scriptdict (must be lowest level, not a nested dictionary)
#//             indent - current indentation value
#//
#////////////////////////////////////////////
#def printscriptentry(scriptdict,indent):
def printscriptentry(identifier,indent,options,args,targetconfigs):
    
            #indent = macro_incr_indent(indent)
            scriptdict=findscriptidentifier(SubFileDict,identifier)
            #Check our arguments
            if scriptdict is None:
                scriptdictfailure(identifier,scriptdict,"Error! Script identifier: "+identifier+" not found in master dictionary. \n #### It was listed as a prerequisite or postscript of some other script but wasn't found. \n #### You may see this error if:\n#### --->Doesn't share same 'subsystems' entries as the depending entry.\n#### --->It isn't listed as an externally releasable script but the depending entry is releasable\n#### --->Also CHECK FOR TYPOS in your identifiers!\n\n")
            
            #if type(args) is not str:
            #    scriptdictfailure(identifier,scriptdict,"Error! in printscriptentry - expected input-'args' to be str. args:"+args)
                
                
            #Need to check dictionary validity here
            validatedictentry(identifier,scriptdict,targetconfigs)
            
            
            #By default don't write scritps which don't specify to show in menu
            #However, other scripts may be called as prerequisite or postscripts
            #Which are not menu scripts. These should be called recursively from this same 
            #Function with 'dontwritemenu' in the options argument
            
            
            #The different types of scripts to be printed:
                #runonpostmortem
                    #if we're in postmortem  mode, print all the postmortem scripts
                #Show in menu
                #Run on init
                
            #recursion or other mode
            if 'recursion' in str(options):
                menubracketflag=False
                writescriptflag=True
            elif 'dontwritemenu' in str(options):
                menubracketflag=False
                writescriptflag=True
            #Postmortem mode
            elif 'postmortem' in str(options):
                if scriptdict['runonpostmortem'] is True:
                    menubracketflag=False
                    writescriptflag=True
                else:
                    menubracketflag=False
                    writescriptflag=False 
            #menu print mode
            elif 'printmenu' in str(options):
                if scriptdict['show in menu'] is True:
                    menubracketflag=True
                    writescriptflag=True
                else:
                    menubracketflag=False
                    writescriptflag=False
            else:
                
                menubracketflag=False
                writescriptflag=False
                
            #if CurrentTarget not in 'MSM8996':
                #import pdb; pdb.set_trace()
            if 'all' not in str(scriptdict['target']).lower():
                
                if str(CurrentTarget).lower() not in str(scriptdict['target']).lower():
                    return indent
            
            
            #If we're not writing anything, then nothing to do here
            if writescriptflag is False:
                return indent
        
            
            #Else let's write out the entry
            filename=scriptdict['scriptname']
            (title,extension)= os.path.splitext(filename)
            abspath=scriptdict['abspath']
            fullpath=os.path.join(abspath,scriptdict['scriptname'])
            displayname=scriptdict['dropdown menu name']
            
            #If arguments are specified, use those
            if 'default' in str(args) or (args is None):
                #arguments should be a list
                arguments=""
                #symbolmanager is a special case
                if 'SymbolManager-Loadsyms' in identifier:
                    arguments=targetconfigs['Subsystem']+" "
                    for arg in scriptdict['subsystems']:
                        arguments=arguments+arg+" "
                elif len(scriptdict['arguments']) is not 0:
                    for arg in scriptdict['arguments']:
                        arguments=arguments+arg+" "

            else:
                arguments=args


            #Don't write opening/closing brackets if specified
            #Allows us to call this function recursively for prereq's and postscripts
            if menubracketflag is True:
                    #Open bracket and menu item
                    writetextline(indent + "MENUITEM \"[" + FILEPATTERNS_ICONS[extension] + "]&" + displayname + " " + "\" \n")
                    writetextline(indent + "( \n")
                    buttonsymbol=scriptdict['menubutton']
                    name=scriptdict['menubutton']
                    subroutine=identifier.upper().replace(" ","_")
                    writetextline(subroutine+":\n")
                    indent = macro_incr_indent(indent)
                    writetextline(indent+"LOCAL &invocationtype\n")
                    writetextline(indent+"ENTRY &invocationtype\n")
                    
            
            ############################################
            ## Handle all special prerequisite keywords
            ############################################
            for prerequisiteoption in SpecialOptionKeywords.keys():
                if prerequisiteoption in str(scriptdict['prerequisites']).lower():
                    if SpecialOptionSatisfiedFlag[prerequisiteoption] is False:
                        SpecialOptionSatisfiedFlag[prerequisiteoption]=True
                        printscriptentry(SpecialOptionKeywords[prerequisiteoption],indent,'recursion',None,targetconfigs)
                
            ###############################################
            ## Now print out all the prerequisite scripts
            ###############################################
            for prerequisite in scriptdict['prerequisites']:
                if not prerequisite in SpecialOptionKeywords.keys():
                    printscriptentry(prerequisite,indent,'recursion',None,targetconfigs)
                        
            ############################################
            ## Finally, write the actual script
            ############################################
            if extension in OS_FILETYPES:
                writetextline(indent + "OS.AREA pushd "+scriptdict['abspath']+" && "+FILEPATTERNS_CMDS[extension]+" "+filename+" "+arguments+"\n")
                ## catch returns. This is also to be passed to postscripts
                #FIXME - add an error handler if too many arguents are returned
                if len(scriptdict['returnarguments']) is not 0:
                    returnstring=""
                    #Can only take the first argument for OS commands
                    if len(scriptdict['returnarguments'])>1:
                        scriptdictfailure(identifier,scriptdict,"Error! file extension is os type (.py,.pl,.exe,.sh etc.) but multiple return arguments given. Only one argument can be returned from os type extension")
                    argument=scriptdict['returnarguments'][0]
                    writetextline(indent+"LOCAL &"+argument+"\n")
                    writetextline(indent+argument+"=OS.RETURN()\n")
                else:
                    returnstring=None

            else:
                writetextline(indent + FILEPATTERNS_CMDS[extension] + " " + fullpath + " "  + arguments + "\n")
                ## catch returns. This is also to be passed to postscripts
                #FIXME - add an error handler if too many arguents are returned
                if len(scriptdict['returnarguments']) is not 0:
                    returnstring=""
                    for argument in scriptdict['returnarguments']:
                        returnstring=returnstring+" &"+argument
                    returnstring=returnstring+"\n"
                    writetextline(indent+"LOCAL"+returnstring)
                    writetextline(indent+"ENTRY"+returnstring)
                else:
                    returnstring=None
                
                    
            ###############################################
            ## Prompt before giving postscript? 
            ## Pass display name for the prompt text
            ###############################################
            if scriptdict['postscript prompt'] is True:
                printscriptentry('PostScriptPrompt',indent,'recursion',displayname,targetconfigs)
            
            ###############################################
            ## Now write out the postscripts
            ## Pass any returns from original script to postscript
            ###############################################
            if type(scriptdict['postscripts']) is list:
                for postscript in scriptdict['postscripts']:
                    postscriptargs=""
                    for arg in scriptdict['postscriptarguments']:
                        postscriptargs=postscriptargs+arg+" "
                    printscriptentry(postscript,indent,'recursion',postscriptargs,targetconfigs)
                        
                        
            ############################################
            #Don't write opening/closing brackets if specified
            #Allows us to call this function recursively for prereq's and postscripts
            if menubracketflag is True:
                    
                    #Write out return for button prompt
                    writetextline("\n"+indent+"IF (\"&invocationtype\"==\"BUTTONPROMPT\")\n")
                    writetextline(indent+"(\n")
                    indent=macro_incr_indent(indent)
                    writetextline(indent+"RETURN\n")
                    indent=macro_decr_indent(indent)
                    writetextline(indent+")\n\n")
                    #Close bracket and menu item
                    indent = macro_decr_indent(indent)
                    writetextline(indent + ")" + "\n")

                    
                
            return indent
                    
#////////////////////////////////////////////
#//     
#//     Function:   findscriptidentifier
#//     Description: Recursively searches through dictionarytosearch and returns dictionary entry that matches
#//                  the dictionary specified by the identifier
#//     Expected Input: dictionarytosearch 
#//                     identifier
#//
#////////////////////////////////////////////
def findscriptidentifier(dictionarytosearch,identifier):
    
    if type(dictionarytosearch) is not dict:
        return None
        
    keylist=dictionarytosearch.keys()
    rvalue=None
    if identifier in keylist:
        return dictionarytosearch[identifier]
    else:
        for subdictkey in keylist:
            subsystemdict=dictionarytosearch[subdictkey]
            #the key may be an area identifier. Continue if that's the case
            if subdictkey in "AreaName":
                continue
            #Probably at lowest level of a non-matching script entry
            elif type(subsystemdict) is not dict:
                return None
            #Have found  the script dictionary
            #elif identifier in subsystemdict.keys():
            #    return subsystemdict[identifier]
            #Call it recursively
            else:
                rvalue=findscriptidentifier(subsystemdict,identifier)
                if type(rvalue) is dict:
                    return rvalue

    return None
#////////////////////////////////////////////
#//     
#//     Function:   validatedictentry
#//     Description: Validates the low level script dictionary for validity and dependencies 
#//     Expected Input: scriptdict (must be lowest level, not a nested dictionary)
#//
#////////////////////////////////////////////
def validatedictentry(identifier,scriptdict,targetconfigs):
            
            import pprint
            pp = pprint.PrettyPrinter(indent=4)
            
            
                
            
            #Make sure all needed entries are present
            for key in ScriptDictTemplate['Template'].keys():
                try:
                    if not key in scriptdict.keys():
                        scriptdictfailure(identifier,scriptdict,"Error! "+key+" not specified in dictionary entry")
                except:
                    import pdb; pdb.set_trace()
            
            
            
            #Now make sure that conditionals are met
            if scriptdict['show in menu'] is True:
                if scriptdict['dropdown menu name'] is None:
                    scriptdictfailure(identifier,scriptdict,"Error! Show in menu is specified as true but dropdown menu name not specified!")
            elif scriptdict['show in menu'] is not False:
                scriptdictfailure(identifier,scriptdict,"Error! 'show in menu' entry must be either True or False")
                
            #if not 'dropdown menu name'  in scriptdict.keys() :
            #if not 'scriptname'          in scriptdict.keys() :
            #if not 'arguments'           in scriptdict.keys() :
            if type(scriptdict['arguments']) is not list:
                scriptdictfailure(identifier,scriptdict,"Error! 'arguments' entry must be a list (at least an empty list - [])")
            #if not 'abspath'             in scriptdict.keys() :
            #if not 'submenu'             in scriptdict.keys() :
            #if not 'user-interactive?'   in scriptdict.keys() :
            #if not 'subsystems'          :in scriptdict.keys() :
            if type(scriptdict['subsystems']) is not list:
                scriptdictfailure(identifier,scriptdict,"Error! 'subsystems' entry must be a list (at least an empty list - [])")
            
            if type(scriptdict['prerequisites']) is not list:
                scriptdictfailure(identifier,scriptdict,"Error! 'prerequisites' entry must be a list (at least an empty list - [])")
            if 'SYMBOL' in str(scriptdict['prerequisites']).upper():
                matchfound=False
                #import pdb; pdb.set_trace()
                for software_image in targetconfigs['software_images']:
                    for given_subsystem in scriptdict['subsystems']:
                        if re.match(given_subsystem.upper(),software_image.upper()):
                            matchfound=True
                if matchfound is False:
                    scriptdictfailure(identifier,scriptdict,"Error! In order to define 'symbols' as a prerequisite, your subsystem must be a software subsystem (e.g. RPM, TZ, MPSS), instead of a hardware subsystem (i.e. APPS-ARMV8)")
            
            if identifier in scriptdict['prerequisites']:
                scriptdictfailure(identifier,scriptdict,"Error! script entry: '"+identifier+"' listed as one of its own prerequisites. Are you trying to stack overflow?")
            
            #if not 'show in menu'        in scriptdict.keys() :
            #if not 'Tags'                in scriptdict.keys() :
            #if not 'MenuButton'          in scriptdict.keys() :
            #if not 'target'              in scriptdict.keys() :
            #if not 'OutputFiles'         in scriptdict.keys() :
            #if not 'Postscripts'         in scriptdict.keys() :
            #if not 'Postscript prompt'   in scriptdict.keys() :
            
            
            if type(scriptdict['postscriptarguments']) is not list:
                scriptdictfailure(identifier,scriptdict,"Error! 'postscriptarguments' entry must be a list (at least an empty list - [])")
            #I expect folks will forget to add the '&' onto their arguments
            #Check that here
            returnstring=""
            for arg in scriptdict['returnarguments']:
                returnstring=returnstring+arg+" "
            for postarg in scriptdict['postscriptarguments']:
                if postarg in returnstring:
                    if '&' not in postarg:
                        scriptdictfailure(identifier,scriptdict,"Error! No ampersand ('&') on argument: "+postarg+" from postscriptargs, which was found in returnstring: "+returnstring)
                        
                    
            if not ((scriptdict['liveorsim?'] in 'Live') or (scriptdict['liveorsim?']  in 'Sim') or (scriptdict['liveorsim?']  in 'Both')):
                scriptdictfailure(identifier,scriptdict,"Error! 'liveorsim' option must be either 'Live' or 'Sim' or 'Both'")
                
            if type(scriptdict['postscripts']) is not list:
                scriptdictfailure(identifier,scriptdict,"Error! 'postscripts' entry must be a list (at least an empty list - [])")
                
            if identifier in scriptdict['postscripts']:
                scriptdictfailure(identifier,scriptdict,"Error! script entry '"+identifier+"' listed as one of its own postscripts. Are you trying to stack overflow?")
            #if not 'RunOnInit'           in scriptdict.keys() :
            #if not 'ExternalRelease'     in scriptdict.keys() :
            
            
            

def scriptdictfailure(identifier,scriptdict, failurestring):
    import pprint
    pp = pprint.PrettyPrinter(indent=4)
    print " "
    print " ############################################ "
    print " #### Failure found in dictionary entry ##### "
    print " ####                                   ##### "
    print " #### Entry Identifier: "+identifier
    print " ####                                   ##### "
    print " ############################################ "
    print " ####                                    "
    print " #### Failure: "+str(failurestring)
    print " ####                                    "
    print " ############################################ "
    print " #### Dictionary entry:"
    pp.pprint(scriptdict)
    kill("Dictionary Parsing Failure: "+failurestring)
            
            

        
        
    #print "stuff"
def writetextline(text):
    if DEBUGMODE:
        print str(text)
    else:
        fptr.write(text)
        
def opennewfile(filename):
    if DEBUGMODE:
        print "Open file: "+filename
    else:
        menufiledirectory=os.path.dirname(filename)
        basename=os.path.basename(filename)
        
        # Make directory if necessary, delete file if it's already there
        if os.path.exists(menufiledirectory):
            if os.path.isfile(filename):
                os.remove(filename)
            #else open() will write the file
        else:
            os.makedirs( menufiledirectory )

        #add these after debug
        global fptr
        fptr = open(filename, 'w')
    
def closefile():
    if DEBUGMODE:
        print "Open file: "+filename
    else:
        fptr.close()
    
def writeheader(filename,heading):
    filename=os.path.basename(filename)
    writetextline("////////////////////////////////////////////////////////////////////\n")
    writetextline("//                                                                //\n")
    writetextline("//  File: "+filename+"     \n")
    writetextline("//  Contains T32 script set-up for "+heading+"     \n")
    writetextline("//  Autogenerated - Do not edit!                                  //\n")
    writetextline("//  Created: "+time.strftime("%d-%m-%Y,%H.%M.%S")+"                                  //\n")
    writetextline("//                                                                //\n")
    writetextline("////////////////////////////////////////////////////////////////////\n")
    writetextline("\n")
    writetextline("//###################Arguments passed #####################            \n")
    writetextline("LOCAL &ArgumentLine                                                    \n")
    writetextline("ENTRY %LINE &ArgumentLine                                              \n")
    writetextline("LOCAL &UTILITY &therest                                                \n")
    writetextline("ENTRY &UTILITY %LINE &therest                                          \n")
    writetextline("                                                                       \n")
    writetextline("                                                                       \n")
    writetextline("//#####################Select Subroutine###################            \n")
    writetextline("// Name of the utility we are calling                                  \n")
    writetextline("// Input Argument 0 is the name of the utility                         \n")
    writetextline("LOCAL &SUBROUTINE                                                      \n")
    writetextline("&SUBROUTINE=\"&UTILITY\"                                                 \n")
    
    #write out all possible subroutines
    writetextline("IF !(")
    for subroutine in MenuScriptSubroutines:
        writetextline("(\"&SUBROUTINE\"==\""+subroutine+"\")||")
    #help is the last subroutine
    writetextline("(\"&SUBROUTINE\"==\"help\")) \n")
    
    writetextline("(                                                                      \n")
    writetextline("    &SUBROUTINE=\"MAIN\"                                                 \n")
    writetextline("    GOSUB MAIN &ArgumentLine                                           \n")
    writetextline(")                                                                      \n")
    writetextline("ELSE                                                                   \n")
    writetextline("(                                                                      \n")
    writetextline("    // Call the required utility                                       \n")
    writetextline("    GOSUB &SUBROUTINE &therest                                         \n")
    writetextline(")                                                                      \n")
    writetextline("                                                                       \n")
    writetextline("    LOCAL &rvalue                                                      \n")
    writetextline("    ENTRY %LINE &rvalue                                                \n")
    writetextline("                                                                       \n")
    writetextline("    //Remove error handler if it was set                               \n")
    writetextline("    ON ERROR                                                           \n")
    writetextline("                                                                       \n")
    writetextline("    GOSUB EXIT &rvalue                                                 \n")
    writetextline("                                                                       \n")
    writetextline("////////////////////////////////////////                               \n")
    writetextline("//                                                                     \n")
    writetextline("//            MAIN                                                     \n")
    writetextline("//            Main "+filename+" logic                                  \n")
    writetextline("//                                                                     \n")
    writetextline("/////////////////////////////////////////                              \n")
    writetextline("MAIN:                                                                  \n")
    writetextline("     LOCAL &arg0 &therest                                               \n")
    writetextline("     ENTRY &arg0 %LINE &therest                                       \n")
    writetextline("                                                                       \n")
    writetextline("     ON ERROR GOSUB HELP                                                \n")
    writetextline("     GOSUB &arg0 &therest                                                \n")
    writetextline("     ON ERROR                                                          \n")
    writetextline("     LOCAL &rvalue                                                     \n")
    writetextline("     ENTRY &rvalue                                                      \n")
    writetextline("     IF (\"&rvalue\"==\"\")                                             \n")
    writetextline("     (                                                                  \n")
    writetextline("         &rvalue=\"SUCCESS\"                                           \n")
    writetextline("     )                                                                 \n")
    writetextline("     RETURN &rvalue                                                    \n")
    writetextline("                                                                       \n")

    return
    
def writefooter(filename):

    writetextline("//In case a return was missed from above                                    \n")
    writetextline("    RETURN                                                                  \n")
    writetextline("                                                                            \n")
    writetextline("EXIT:                                                                       \n")
    writetextline("    LOCAL &rvalue                                                           \n")
    writetextline("    ENTRY %LINE &rvalue                                                     \n")
    writetextline("                                                                            \n")
    writetextline("    //Clear any persistent variables needed                                 \n")
    writetextline("    do std_cti_&CHIPSET CLEARSENTINELS                                      \n")
    writetextline("                                                                            \n")
    writetextline("    ENDDO &rvalue                                                           \n")
    writetextline("                                                                            \n")
    writetextline("                                                                            \n")
    writetextline("//Should never get here.                                                    \n")
    writetextline("FATALEXIT:                                                                  \n")
    writetextline("    LOCAL &rvalue                                                           \n")
    writetextline("    ENTRY %LINE &rvalue                                                     \n")
    writetextline("    IF STRING.SCAN(\"&FAILUREKEYWORD\",\"FAILUREKEYWORD\",0)==-1                \n")
    writetextline("    (                                                                       \n")
    writetextline("        GOSUB EXIT &FAILUREKEYWORD - &rvalue                                \n")
    writetextline("    )                                                                       \n")
    writetextline("    ELSE                                                                    \n")
    writetextline("    (                                                                       \n")
    writetextline("        GOSUB EXIT &rvalue                                                  \n")
    writetextline("    )                                                                       \n")
    writetextline("                                                                            \n")
    writetextline("//Should never get here                                                     \n")
    writetextline("    END                                                                     \n")

    return

    
    

        
        
        
       
def kill(msg):
    if msg:
        print msg
        
    #Close log file if it's open
    if LogFileFlag is True:
        
        #sys.stdout=OldStdOut
        sys.stdout=sys.__stdout__
        
        LogFile.close()
        
        
        
    sys.exit(1)

        
if __name__ == '__main__':


    getpath()
    import sys 
    import time
    
    if len(sys.argv) > 1:
        if 'test' in sys.argv[1]:
            TestsEnable=True
            
    ##############################################################
    ##   Set up logging. 
    ##   If we're in test mode, print things out to console
    ##############################################################
    global LogFileFlag 
    global OldStdOut
    global LogFile
    if TestsEnable is False:
        #Create the directory if needed
        logdirectory=os.path.join(RootDirectory,"logs")
        if not os.path.exists(logdirectory):
            os.makedirs( logdirectory )
        #Create the file
        OldStdOut=sys.stdout
        LogFileFlag=True
        LOGFILE=os.path.abspath(os.path.join(logdirectory,BuildLog+time.strftime("%d-%m-%Y,%H.%M.%S")+".txt"))
        LogFile=open(LOGFILE,"w")
        LogFile.write("###########################################\n")
        LogFile.write("##  CMMBuilder - BringupTool Build Log   ##\n")
        LogFile.write("###########################################\n")
        LogFile.write("\n\n\n")
        sys.stdout = LogFile
    else:
        LogFileFlag=False
        
    #Remove success log if it's there
    resultsfilename=os.path.join(RootDirectory,SuccessLog)
    if os.path.isfile(resultsfilename):
        os.remove(resultsfilename)
        

    ###############################################################
    ##    Start making scripts!
    ###############################################################
    for target in Targets:
        
        
        
        cfgfile=os.path.join(RootDirectory,'configs',TargetConfigDict[target]+'.py')
        sys.path.append(RootDirectory)
        os.environ.update({'CHIPSET':TargetConfigDict[target]})
        
        if not os.path.isfile(cfgfile):
            continue
        print "Processing for target "+target
        sys.path.append(os.path.abspath(os.path.join(RootDirectory,'configs')))
        tgtcfg=__import__(TargetConfigDict[target])
        cfgsettings=tgtcfg.targetconfigs()
        
        ####################################################
        #This is for flavors (e.g. internal vs external)
        ####################################################
        for flavor in cfgsettings['flavors'].keys():
            
            
            
            ####################################################
            #This is for subsystems, which are hardware-focused
            ####################################################
            for subsystem in cfgsettings['subsystemprofile_map'].keys():
                print "Processing for subsystem "+subsystem
                flavorname=cfgsettings['flavors'][flavor]
                menu_scriptname=str(MenuConfigSriptName+"_"+subsystem+"_"+flavorname+".cmm")
                postmortem_scriptname=str(PostMortemScript+"_"+subsystem+".cmm")
                menuheading="Qualcomm Scripts"
                hwconfigs=cfgsettings
                
                hwconfigs.update({'Subsystem':subsystem})
                hwconfigs.update({'Image':subsystem})
                hwconfigs.update({'Flavor':flavorname})
                
                SubFileDict=importscripts(hwconfigs,subsystem)
                if SubFileDict is not None:
                    CurrentTarget=hwconfigs['Target']
                    menufilename=os.path.abspath(os.path.join(RootDirectory,hwconfigs['Target'],menu_scriptname))
                    hwconfigs.update({'thisscriptname':menufilename})
                    opennewfile(menufilename)
                    writeheader(menufilename,subsystem+" subsystem ")
                    buildmenus(SubFileDict,menuheading,hwconfigs)
                    buildmenubuttons(SubFileDict,menuheading,hwconfigs)
                    buildhelpsubroutine(SubFileDict,menuheading)
                    writefooter(menufilename)
                    closefile()
                    
                    postmortemfilename=os.path.abspath(os.path.join(RootDirectory,hwconfigs['Target'],postmortem_scriptname))
                    buildpostmortemscript(SubFileDict,postmortemfilename,hwconfigs)
                    
        ####################################################
        #This is for software images, multiple of which can reside on one hardware subsystem       
        ####################################################
        #for software_image in cfgsettings['software_images']:
        #    print "Processing for image "+software_image 
        #    menu_scriptname=str(MenuConfigSriptName+"_"+software_image+".cmm")
        #    postmortem_scriptname=str(PostMortemScript+"_"+software_image+".cmm")
        #    menuheading=str(software_image).upper()+" Scripts"
        #    imageconfigs=cfgsettings
        #    
        #    imageconfigs.update({'Image':software_image})
        #    
        #    SubFileDict=importscripts(imageconfigs,software_image)
        #    if SubFileDict is not None:
        #        CurrentTarget=imageconfigs['Target']
        #        menufilename=os.path.abspath(os.path.join(RootDirectory,imageconfigs['Target'],menu_scriptname))
        #        imageconfigs.update({'thisscriptname':menufilename})
        #        opennewfile(menufilename)
        #        writeheader(menufilename,software_image+" subsystem ")
        #        buildmenus(SubFileDict,menuheading)
        #        buildmenubuttons(SubFileDict,menuheading,imageconfigs)
        #        buildhelpsubroutine(SubFileDict,menuheading)
        #        writefooter(menufilename)
        #        closefile()
        #        
        #        postmortemfilename=os.path.abspath(os.path.join(RootDirectory,imageconfigs['Target'],postmortem_scriptname))
        #        buildpostmortemscript(SubFileDict,postmortemfilename)
                
    if LogFileFlag is True:
        LogFile.close()
        sys.stdout=OldStdOut
    
    #If we got here, assume successful
    #Write out the success log. Defined above
    opennewfile(resultsfilename)
    writetextline("SUCCESS\n")
    closefile()
    
    
        
        
        
        
