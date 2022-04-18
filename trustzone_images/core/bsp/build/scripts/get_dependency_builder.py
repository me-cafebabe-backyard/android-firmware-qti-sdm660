#============================================================================
#
# CBSP Builders build rules
#
# GENERAL DESCRIPTION
#    Contains builder(s) to build a Secure App
#
# Copyright 2015 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#  $Header: //components/rel/core.tz/1.0.7.1/bsp/build/scripts/get_dependency_builder.py#1 $
#  $DateTime: 2020/01/14 12:35:09 $
#  $Author: pwbldsvc $
#  $Change: 22186835 $
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who       what, where, why
# --------   ---       ------------------------------------------------------
#
#============================================================================
import os

#----------------------------------------------------------------------------
# Global values
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Hooks for Scons
#----------------------------------------------------------------------------
def exists(env):
  return env.Detect('get_dependency_builder')

def generate(env):
  get_dependency(env)

#============================================================================
# Add the Dependency Builder
#============================================================================
def get_dependency(env):
  env.AddMethod(get_ta_dependency_builder, "GetTaDependency")
  env.AddMethod(get_tee_dependency_builder, "GetTeeDependency")

def get_common_dependencies(env, metadata):
  # Using this output until very commonly used libs in CORE
  # are added to commonlib or applib. After that TA libraries should be
  # linked directly by TAs and not across the CORE/APPS
  # component boundery using AddBinaryLibarary

  env = env.Clone()
  for path in env['CPPPATH']:
    if 'apps' in path:
      env['CPPPATH'].remove(path)
    if env.get('CPPDEFINES') != None:
      for flag in env['CPPDEFINES']:
        if '_DEBUG' in flag:
          env['CPPDEFINES'].remove(flag)
  libs = list()
  objs = list()

  clibs, cobjs = env.LoadAUSoftwareUnits('core')
  libs.extend(clibs)
  objs.extend(cobjs)

  alibs, aobjs = env.LoadAUSoftwareUnits('apps')
  libs.extend(alibs)
  objs.extend(aobjs)

  return (libs, objs)

def get_ta_dependency_builder(env, metadata):

  libs, objs = get_common_dependencies(env, metadata)

  if env['PROC'] == 'scorpion':
    libname = 'applib32'
  else:
    libname = 'applib64'

  applib = [env.File(env.subst('${BUILD_ROOT}/core/bsp/trustzone/qsapps/'
                               + libname
                               + '/build/${SHORT_BUILDPATH}/'
                               + libname
                               + '.lib'))]
  appobj = [env.File(env.subst('${BUILD_ROOT}/core/bsp/trustzone/qsapps/'
                               + libname
                               + '/build/${SHORT_BUILDPATH}/tzapp_entry.o'))]
  if 'privileges' not in metadata or 'GPServices' not in metadata['privileges']:
    appobj += [env.File(env.subst('${BUILD_ROOT}/core/bsp/trustzone/qsapps/'
                        + libname
                        + '/build/${SHORT_BUILDPATH}/tzapp_lib_main.o'))]

  libs.extend(applib)
  objs.extend(appobj)

  return (libs, objs)

def get_tee_dependency_builder(env, metadata):
  return get_common_dependencies(env, metadata)

