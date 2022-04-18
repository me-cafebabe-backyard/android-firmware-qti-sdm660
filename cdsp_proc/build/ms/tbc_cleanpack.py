#============================================================================
#  Name:                                                                     
#    tbc_cleanpack.py 
#
#  Description:                                                              
#    None 
#                                                                            
# Copyright (c) 2020 by QUALCOMM, Incorporated.  All Rights Reserved.        
#============================================================================
#                                                                            
# *** AUTO GENERATED FILE - DO NOT EDIT                                      
#                                                                            
# GENERATED: Wed Mar 11 22:33:33 2020 
#============================================================================
def exists(env):
   return env.Detect('tcfg_cleanpack')

def generate(env):
   env.AddUsesFlags('USES_CLEAN_PACK',  True)
