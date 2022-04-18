#===============================================================================
#
# BUILDSPEC file builder
#
# GENERAL DESCRIPTION
#    build rules script
#
# Copyright (c) 2009-2009 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header:
#  $DateTime: 2020/01/14 12:33:12 $
#  $Author: pwbldsvc $
#  $Change: 22186812 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 2015/13/06 pdosi   initail version
#===============================================================================
import collections
import os.path
import shutil
from SCons.Script import *

TZBSP_MODULE_BASE_RSVD=0
TZ_MSK_RSVD_BIT_SHFT  = 28
TZ_MSK_MODULE_BIT_SHFT =24
TZ_MSK_RSVD_MSK  = (0xF<<TZ_MSK_RSVD_BIT_SHFT)
TZ_MSK_MODULE_MSK =(0xF<<TZ_MSK_MODULE_BIT_SHFT)
TZ_MSK_CODE_MSK  = 0xFFFFFF
prevLine = ""
#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('errorcodedict_builder')

def generate(env):
   dict_generate(env)

#===============================================================================
# build rules
#===============================================================================
def dict_generate(env):
   #-------------------------------------------------------------------------------
   # def builder for  error codes dictionary generation 
   #-------------------------------------------------------------------------------
   build_root=env.get('BUILD_ROOT')
   if not SCons.Script.COMMAND_LINE_TARGETS[0]:
      env.PrintError("Cannot execute errorcodedict builder option without a build Target!! ")
   errorCodesDictBkp =os.path.join(build_root, 'core','bsp','qsee','errorCodesDict_1.txt') 	  
   backupExistingDict(build_root)
   generateDictionary(build_root)
   if os.path.exists(errorCodesDictBkp) :
      os.remove(errorCodesDictBkp)
   
#===============================================================================
# method to calculate error codes, from module name and error code.

"""Macro to create error code.
 31*****************27*********************23***********************0
+-------------------+---------------------+------------------------+
|      4 bits for   |                     |               24 bits  |
|      future use   |          4 bit      |               error code
|                   |          module name|                        +
|                   |                     |                        |
+-------------------+---------------------+------------------------+
"""
#===============================================================================  
def backupExistingDict(build_root) :
	errorCodesDict = os.path.join(build_root, 'core','bsp','qsee','errorCodesDict.txt') 	 
	errorCodesDictBkp =os.path.join(build_root, 'core','bsp','qsee','errorCodesDict_1.txt') 	 
	if os.path.exists(errorCodesDict) :
		shutil.copyfile(errorCodesDict, errorCodesDictBkp)

#===============================================================================  

#===============================================================================  

def TZBSP_ERR_CODE(tz_module,code) :
	return (((TZ_MSK_MODULE_MSK&(tz_module<<TZ_MSK_MODULE_BIT_SHFT))|(TZ_MSK_CODE_MSK&(code)))|  (TZ_MSK_RSVD_MSK&(TZBSP_MODULE_BASE_RSVD<<TZ_MSK_RSVD_BIT_SHFT)))
		
#===============================================================================
# method to generate the Dictionary 
#===============================================================================
  
def generateDictionary(build_root) : 
	tzbsp_errno = os.path.join(build_root, 'core','securemsm','trustzone','qsee','include','tzbsp_errno.h')
	dict_txt=os.path.join(build_root, 'core','bsp','qsee','errorCodesDict.txt') 	 
	dic = open(dict_txt, 'a')
	dic.truncate()
	module = dict()
	module = collections.defaultdict(list)
	moduleName=None
	moduleNumber=None

	with  open(tzbsp_errno, 'r') as errno :
	   
		for line in errno:
			# get the list of modules and relevant module number and create a dict	
			if (("TZBSP_DEF_MODULE" in line) and ( "TZBSP_MODULE_BASE_RSVD" not in line )) : 
				if (line.split("TZBSP_DEF_MODULE")[0] ) :
					moduleName =line.split("TZBSP_DEF_MODULE")[0].split("#define")[1]
					moduleName=moduleName.strip()
				if (line.split("TZBSP_DEF_MODULE")[1]) :
					moduleNumber=line.split("TZBSP_DEF_MODULE")[1].replace('(', '').replace(')', '')
					moduleNumber=moduleNumber.strip()
				if (moduleName) :
					module[moduleName].append(moduleNumber)
			#Generate a dictionary	
			if (("TZBSP_ERR_CODE" in line) and ( "TZ_MODULE" not in line ) and ("," in line)) : 
				errorCodeVal=None
				moduleDec=None
				errNum=None
				moduleNameEC=None
				if ((line.split("TZBSP_ERR_CODE")[0]) and  ("#define" in line.split("TZBSP_ERR_CODE")[0])) :
					errorCodeVal=(line.split("TZBSP_ERR_CODE")[0]).split("#define")[1]
					errorCodeVal=errorCodeVal.strip()
				if ((line.split("TZBSP_ERR_CODE")[1]) and ( "," in line.split("TZBSP_ERR_CODE")[1] )) :
					moduleNameEC = line.split("TZBSP_ERR_CODE")[1].split(',')[0].replace('(', '')
					moduleNameEC =moduleNameEC.strip()
					errNum=line.split("TZBSP_ERR_CODE")[1].split(',')[1].split(')')[0].strip()
					
				if ((moduleNameEC) and (moduleNameEC in module)):
					moduleDec = int(module[moduleNameEC][0],16)
					
				if (errNum) and (moduleNameEC) and (errorCodeVal) and (moduleDec):	
					if ('0x' in errNum ) :
						errNum =int(errNum,16)
					else:
						errNum =int(errNum)
					if ("/*" in prevLine) and  ("TZBSP_ERR_CODE" not in prevLine) and ("Error codes for logging only." not in prevLine) :
						val=prevLine.split('/*')[1].split('*/')[0].replace('*', '')
					else:
						val=" "
					dic.write( format(TZBSP_ERR_CODE(moduleDec,errNum), '02x')+":"+errorCodeVal + ":"+ val +'\n')
			prevLine = line
				
	errno.close()		
	dic.close()
