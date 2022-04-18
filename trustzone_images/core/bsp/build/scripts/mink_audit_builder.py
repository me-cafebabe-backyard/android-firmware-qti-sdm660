# ============================================================================
#
# Mink Audit Builder build rules
#
# GENERAL DESCRIPTION
#    Contains builder(s) to process and audit Mink interface and syscall code to
#    detect and report changes, failing the build if necessary.
#
# Copyright (c) 2016 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
# ----------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('mink_audit_builder')

def generate(env):
   mink_audit_generate(env)

#===============================================================================
# Mink Audit build rules
#===============================================================================
def mink_audit_generate(env):
   #-------------------------------------------------------------------------------
   # def builder for Mink Interface/Syscall Audit
   #-------------------------------------------------------------------------------
   audit_bld = env.Builder( action = mink_audit_builder)
   env.Append(BUILDERS = {"MinkAuditBuilder" : audit_bld})

#-------------------------------------------------------------------------------
# mink audit builder action
#-------------------------------------------------------------------------------
def mink_audit_builder(env, target, source):
   import sys
   import os
   sys.path.insert(0, env.subst('${BUILD_ROOT}/core/bsp/build/scripts'))
   from mink_audit_cfgrw import ConfigReadWriter
   cr = ConfigReadWriter(str(source[0]), env.subst('${BUILD_ROOT}'))
   result = cr.read_and_dispatch()
   with open(str(target[0]), 'w') as rfile:
     if result:
       rfile.write('Mink Audit Succeeded\n')
     else:
       rfile.write('Mink Audit Failed\n')
       env.Exit(1)
   return None
