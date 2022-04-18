#===============================================================================
#
# RPM image build script
#
# GENERAL DESCRIPTION
#    build script
#
# Copyright (c) 2009-2011 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary and Confidential
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/build/RPM.py#9 $
#  $DateTime: 2018/08/10 07:09:32 $
#  $Author: pwbldsvc $
#  $Change: 16855347 $
#
#===============================================================================
import os
import glob
import imp
import string
from SCons.Script import *

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('RPM Image')

def generate(env):
   #------------------------------------------------------------------------------
   # Decide build steps
   #------------------------------------------------------------------------------
   # That is, if the user has asked for a filtered build, don't try to link.
   filter_opt = env.get('FILTER_OPT')
   do_link = False if filter_opt is not None else True
   do_local_files = False if not do_link and not env.FilterMatch(os.getcwd()) else True

   #-------------------------------------------------------------------------
   # Libs/Objs
   #-------------------------------------------------------------------------
   rpm_libs_path = env.get('INSTALL_LIBPATH')
   rpm_libs = env.get('RPM_LIBS')
   rpm_objs = env.get('RPM_OBJS')      

   rpm_units = [rpm_libs, rpm_objs]

   if do_local_files:
      #---------------------------------------------------------------------------
      # RPM image-level sources
      #---------------------------------------------------------------------------
      env = env.Clone()

      RPM_SRC = "../src"
      env.VariantDir("${BUILD_PATH}", RPM_SRC, duplicate=0)
      env.Append(CFLAGS = '${ARMCC_STDC99_CMD}')
      env.Append(CCFLAGS = '${ARMCC_DOLLAR_CMD}')

      if env['BUILD_VER'].isdigit():
        build_id = str(int(env['BUILD_VER']))
      else:
        build_id = str(zlib.adler32(env['BUILD_VER']) & 0xFFFFFFFF)
      env.Append(CPPDEFINES = [('RPM_BUILD_ID', build_id)])

      if env['MSM_ID'] == '8994':
          env.Append(CPPDEFINES = 'INIT_PRNG_NO_TZ')
          env.Append(CPPDEFINES = 'MSM8994_IMAGE_LAYOUT')
          env.Append(CPPDEFINES = 'MSM8994_PROXY_VOTES')
          env.Append(CPPDEFINES = 'DDR_ABORT_REG_DUMP')
      elif env['MSM_ID'] == '8996':
          env.Append(CPPDEFINES = 'MSM8996_STUBS')
          env.Append(CPPDEFINES = 'MSM8996_IMAGE_LAYOUT')
          env.Append(CPPDEFINES = 'MSM8996_PROXY_VOTES')
          env.Append(CPPDEFINES = 'DISABLE_XPUS')
          env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      elif env['MSM_ID'] == '8998':
          env.Append(CPPDEFINES = 'MSM8998_STUBS')
          env.Append(CPPDEFINES = 'MSM8998_IMAGE_LAYOUT')
          env.Append(CPPDEFINES = 'MSM8998_PROXY_VOTES')
          env.Append(CPPDEFINES = 'DISABLE_XPUS')
          env.Append(CPPDEFINES = 'NO_STACK_CHECK')
          env.Append(CPPDEFINES = 'DDR_ABORT_REG_DUMP')
      elif env['MSM_ID'] == '660':
          env.Append(CPPDEFINES = 'SDM660_STUBS')
          env.Append(CPPDEFINES = 'SDM660_IMAGE_LAYOUT')
          env.Append(CPPDEFINES = 'SDM660_PROXY_VOTES')
          env.Append(CPPDEFINES = 'DISABLE_XPUS')
          env.Append(CPPDEFINES = 'NO_STACK_CHECK')
          env.Append(CPPDEFINES = 'VIRTIO_WORKAROUND')
          env.Append(CPPDEFINES = 'SL_VIRTIO_WORKAROUND')
          env.Append(CPPDEFINES = 'DDR_ABORT_REG_DUMP')
#default vipertooth support using Starlord target specific files   
      elif env['MSM_ID'] == '405':
          env.Append(CPPDEFINES = 'SDM660_STUBS')
          env.Append(CPPDEFINES = 'QCS405_IMAGE_LAYOUT')
          env.Append(CPPDEFINES = 'SDM660_PROXY_VOTES')
          env.Append(CPPDEFINES = 'DISABLE_XPUS')
          env.Append(CPPDEFINES = 'NO_STACK_CHECK')
          env.Append(CPPDEFINES = 'VIRTIO_WORKAROUND')
          env.Append(CPPDEFINES = 'SL_VIRTIO_WORKAROUND')
          env.Append(CPPDEFINES = 'DDR_ABORT_REG_DUMP')
          env.Append(CPPDEFINES = 'QCS405_STUBS')
      elif env['MSM_ID'] == 'nicobar':
          env.Append(CPPDEFINES = 'SDM660_STUBS')
          env.Append(CPPDEFINES = 'SDM_NICOBAR_IMAGE_LAYOUT')
          env.Append(CPPDEFINES = 'SDM660_PROXY_VOTES')
          env.Append(CPPDEFINES = 'DISABLE_XPUS')
          env.Append(CPPDEFINES = 'NO_STACK_CHECK')
          env.Append(CPPDEFINES = 'VIRTIO_WORKAROUND')
          env.Append(CPPDEFINES = 'SL_VIRTIO_WORKAROUND')
          env.Append(CPPDEFINES = 'DDR_ABORT_REG_DUMP')
	  #----------------------------------------------------------------------------
      # Dependencies on CoreBSP code
      #----------------------------------------------------------------------------
      CBSP_API = [
         'BOOT',
         'BUSES',
         'DAL',
         'DEBUGTOOLS',
         'MPROC',
	     'PMIC',
         'POWER',
         'SYSTEMDRIVERS',
         'DEBUGTRACE',
         'PrngCL',
         'SERVICES',
         'KERNEL',
      ]

      env.RequirePublicApi(CBSP_API)
      env.RequireRestrictedApi(CBSP_API)

      #----------------------------------------------------------------------------
      # Sources, libraries
      #----------------------------------------------------------------------------

      # stubs and other qcore app files
      RPM_SOURCES = [
         'main.c',
         'retarget.c',
         'exceptions.c',
         'coredump.c',
         'time_service.c',
         'xpu_init.c',
         'image_layout.c',
         'stack_protect.c',
         'rpm_mpu.c',
         '../target/${MSM_ID}/rpm_target_init.c',
         '../target/${MSM_ID}/rpm_vector_table.c',
         '../target/${MSM_ID}/exception_isr.c',
      ]
      RPM_SPECIAL_SOURCES = [
         'datetime.c'
      ]
      RPM_STARTUP_SOURCES = [
         'startup.s',
      ]
      rpm_special_objs = env.Object(RPM_SPECIAL_SOURCES)
      rpm_startup_objs = env.Object(RPM_STARTUP_SOURCES)
      for so in rpm_special_objs:
         so.set_always_build ()
      rpm_objs.extend(env.Object(RPM_SOURCES))
      rpm_objs.extend(rpm_special_objs)
      if env['MSM_ID'] in ['8996', '8998', '660', '405', 'nicobar']:                 #default vipertooth support using Starlord target specific files   
         rpm_objs.extend(rpm_startup_objs)

   # Add CMM Scripts to the menu
   if env['IMAGE_NAME'] in ['RPM']:
	  SRCPATHSCRIPTS = env['BUILD_ROOT']+'/core/bsp/rpm/scripts'
	  env.AddCMMScripts ('RPM', [SRCPATHSCRIPTS], { 'rpm_dump.cmm' : 'RPM Core Dump'}, 'Kernel')


   if do_link:
      target_scl = env.SclBuilder('${TARGET_NAME}', [
         '../target/${MSM_ID}/rpm.scl', 
      ])

      rpm_elf = env.Program('${TARGET_NAME}', rpm_objs, LIBS=rpm_libs, LIBPATH=rpm_libs_path)
      rpm_elf_2 = env.RpmElfBuilder ('${TARGET_NAME}' + '_rpm', rpm_elf)

      env.Append(USE_MBN_TOOLS = 'True')
      env.AddUsesFlags('USES_MBNTOOLS')

      if env['MSM_ID'] in ['8998', '660', '405', 'nicobar']:       #default vipertooth support using Starlord target specific files   
          env.AddUsesFlags('USES_PLATFORM_IMAGE_INTEGRITY_CHECK')

      env.Replace(GLOBAL_DICT = {'IMAGE_KEY_RPM_IMG_DEST_ADDR' : 0xFC100080})
      rpm_mbn = env.MbnBuilder(
                            '${TARGET_NAME}', 
                            rpm_elf_2, 
                            IMAGE_TYPE="rpm", 
                            FLASH_TYPE="sdcc", 
                            MBN_TYPE="elf"
                        )

      env.Depends(rpm_elf, target_scl)
      env.Clean(rpm_elf, env.subst('${TARGET_NAME}.map'))
      env.Clean(rpm_elf, env.subst('${TARGET_NAME}.sym'))


      #----------------------------------------------------------------------------
      # Sectools signing
      #----------------------------------------------------------------------------
      
      install_base_dir = '${BUILD_ROOT}/build/rpm/bf/build/'
      install_unsigned_root = env.SectoolGetUnsignedInstallPath(install_base_dir)
      install_rpm_mbn = env.InstallAs(os.path.join(install_unsigned_root, 'rpm.mbn'), rpm_mbn)
      
      if env['MSM_ID'] in ['8998']:
          sectools_signed_mbn = env.SectoolBuilder(
                                    target_base_dir = '${TARGET_NAME}', 
                                    source=rpm_mbn,
                                    sign_id="rpm",
                                    #msmid = env.subst('${MSM_ID}'),
                                    sectools_install_base_dir = install_base_dir,
                                    install_file_name = "rpm.mbn",
                                    soc_hw_version="0x30020000",
                                    soc_vers="0x3005", # if we need to add more chip, format is soc_vers="0x3005 0x3004" for example.
                                                       # go/soc_hw_version has all the values, for soc_vers, you only need first 4
                                                       # for only family and device number
                                                       # Check line4 and 41 in rpm_proc\core\bsp\rpm\build\RPM_AAAAANAAR\sign\SecImage_log.txt
                                                       # to see if the value is passed to sectools and is in the signed image.
                                    config= '${BUILD_ROOT}/tools/build/scons/sectools/config/integration/secimagev2.xml',
                                )
      elif env['MSM_ID'] in ['660','405','nicobar']:   #default vipertooth support using Starlord target specific files   
          sectools_signed_mbn = env.SectoolBuilder(
                                    target_base_dir = '${TARGET_NAME}', 
                                    source=rpm_mbn,
                                    sign_id="rpm",
                                    #msmid = env.subst('${MSM_ID}'),
                                    sectools_install_base_dir = install_base_dir,
                                    install_file_name = "rpm.mbn",
                                    soc_hw_version="0x30060000",
                                    soc_vers="0x3007", # if we need to add more chip, format is soc_vers="0x3005 0x3004" for example.
                                                       # go/soc_hw_version has all the values, for soc_vers, you only need first 4
                                                       # for only family and device number
                                                       # Check line4 and 41 in rpm_proc\core\bsp\rpm\build\RPM_AAAAANAAR\sign\SecImage_log.txt
                                                       # to see if the value is passed to sectools and is in the signed image.
                                    config= '${BUILD_ROOT}/tools/build/scons/sectools/config/integration/secimagev2.xml',
                                )
      else:
          sectools_signed_mbn = env.SectoolBuilder(
                                    target_base_dir = '${TARGET_NAME}', 
                                    source=rpm_mbn,
                                    sign_id="rpm",
                                    msmid = env.subst('${MSM_ID}'),
                                    sectools_install_base_dir = install_base_dir,
                                    install_file_name = "rpm.mbn",
                                )

      rpm_units = env.Alias('rpm_units', [
          rpm_elf,
          rpm_elf_2,
          rpm_mbn,
          install_rpm_mbn,
          sectools_signed_mbn,
      ])

   # add aliases
   aliases = env.get('IMAGE_ALIASES')
   for alias in aliases:
      env.Alias(alias, rpm_units)
