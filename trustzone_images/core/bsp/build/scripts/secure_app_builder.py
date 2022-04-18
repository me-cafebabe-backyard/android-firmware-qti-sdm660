
#
# CBSP Builders build rules
#
# GENERAL DESCRIPTION
#    Contains builder(s) to build a Secure App
#
# Copyright 2015,2016 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#  $Header: //components/rel/core.tz/1.0.7.1/bsp/build/scripts/secure_app_builder.py#1 $
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
import platform
import fnmatch
import hashlib
if __name__ != '__main__':
  import SCons.Script
#----------------------------------------------------------------------------
# Global values
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Hooks for Scons
#----------------------------------------------------------------------------
def exists(env):

  return env.Detect('secure_app_builder')

def generate(env):
  secure_app_generate(env)

#============================================================================
# Add the Secure App Builder to the environment. Also Load other builders
# that are needed for secure app compilation via LoadToolScript helper.
#============================================================================
def secure_app_generate(env):
  env.AddMethod(secure_app_builder, "SecureAppBuilder")
  env.AddMethod(get_object_file_name, "GetObjectFileName")
  env.AddMethod(secure_app_lib_builder, "SecureAppLibBuilder")

  split_bin_list_bld = env.Builder(action = get_split_bin_list_act)
  env.Append(BUILDERS = {'GetSplitBinList' : split_bin_list_bld})
  tools = [
    # load the llvm builder
    '${BUILD_ROOT}/tools/build/scons/scripts/llvm.py',
    # load the builder to add cust_h and other ASM_DFLAGS and CC_DFLAGS
    '${BUILD_ROOT}/tools/build/scons/scripts/apps_defs.py',
    # the builder to help sign the secure app image
    '${BUILD_ROOT}/sectools/sectools_builder.py',
    # the builder to generate mbn image
    '${BUILD_ROOT}/core/bsp/build/scripts/mbn_builder.py',
    # the builder to get the objects and libraries the app depends on
    '${BUILD_ROOT}/core/bsp/build/scripts/get_dependency_builder.py',
    # the builder that generate the scatter loader file to generate an image map to be used by linker
    '${BUILD_ROOT}/core/bsp/build/scripts/scl_builder.py',
    # the builder that creates multiple files from the image file
    '${BUILD_ROOT}/core/bsp/build/scripts/pil_splitter_builder.py',
    # the builder that generates the metadata.c file and add privileges as defined in metadata dictionary
    '${BUILD_ROOT}/core/bsp/build/scripts/secure_apps.py',
    # the builder that affects formatting and also has buildspec rules for klocwork
    '${BUILD_ROOT}/tools/build/scons/scripts/buildspec_builder.py'
  ]
# The tools get loaded as part of init_build_config. Loading them here could cause
# a race condition where these tools get loaded prior to init_build_config and may thus
# miss some of the env variables populated like the USES_* variables. MBN builder does
# reference USES_MBN* variables that get populated in init_build_config
  env.Replace(IMAGE_TOOLS = tools)

#============================================================================
# secure_app_builder:
# this builder takes in the list of source files, include file paths,
# the metadata dictionary and the desired image name to build the
# secure application. The builder takes key word arguments as optional
# parameters. The key word arguments currently processed are:
# stack_size, heap_size, sec_xml_config, user_libs
# The Node object of the final builder is returned
# back so that the caller can add it as a dependency if needed.
#============================================================================
def secure_app_builder(env, sources, includes, metadata, image, **kwargs):
  env = env.Clone()
  return_list = []
  if 'stack_size' in kwargs and kwargs['stack_size']:
    env['APP_STACK_SIZE'] = kwargs['stack_size']

  if 'heap_size' in kwargs and kwargs['heap_size']:
    env['APP_HEAP_SIZE'] = kwargs['heap_size']

  if 'sec_xml_config' in kwargs and kwargs['sec_xml_config']:
    env['SECIMAGE_XML_CONFIG'] = kwargs['sec_xml_config']

  env.Append(CPPPATH = includes)
  env.Append(CPPPATH = ['#../../core/api/services/',
                        '#../../core/securemsm/trustzone/qsee/mink/include/',
                        '#../../core/securemsm/secrsa/shared/inc',
                        '#../../core/api/securemsm/trustzone/qsee/',
                        '#../../core/securemsm/accesscontrol/api/',
                        '#../../core/securemsm/trustzone/qsee/include/',
                        '#../../core/securemsm/trustzone/qsapps/libs/applib/common_applib/inc',]
            )

  env.Replace(APP_IMAGE_NAME = image)
  env.Append(CFLAGS = '-fPIC')
  
  # Wrap malloc and free calls for all TAs (except TA with nowrap_malloc_free, 
  #                                         which uses its own internal
  #                                         implementation of malloc and free)
  if 'nowrap_malloc_free' not in kwargs or kwargs['nowrap_malloc_free'] == '0':
    env.Append(LINKFLAGS = " --wrap malloc --wrap free ")
    
  env.Append(LINKFLAGS = " -shared -Bsymbolic -e TZAPPENTRY ")
 
  #The app scons environment is expected to define the OUT_DIR path
  buildPath = env.subst('${OUT_DIR}/' + '${SHORT_BUILDPATH}/' + image)

  #Generate the metadata.c file
  metadataObject = env.AddSecureAppMetadata(metadata)

  #compile sources to objects first, so we can control where the .o files end up at
  sobjects = compile_sources(env, buildPath, sources)

  if image == 'teetest':
    libs, objs = env.GetTeeDependency(metadata)
    scl = env.SclBuilder(buildPath,
                         '${BUILD_ROOT}/core/securemsm/trustzone/qsapps/teetest/teetest/build/teetest.ld')
  else:
    libs, objs = env.GetTaDependency(metadata)
    # get the libs and scl for 32 bit or 64 bit based on PROC. scorpion => 32 bit
    if env['PROC'] == 'scorpion':
      scl = env.SclBuilder(buildPath,
                           '${BUILD_ROOT}/core/bsp/build/scripts/secureapp.ld')
    else:
      scl = env.SclBuilder(buildPath,
                           '${BUILD_ROOT}/core/bsp/build/scripts/secureapp64.ld')

  #Get Dependencies
  sobjects.extend(objs)

  # The libclang_rt.builtins-arm.a is common for both architectures.
  arm_libs = [
    env.File(env.SubstRealPath('${LLVMLIB}/libclang_rt.builtins-arm.a')),
  ]

  libs.extend(arm_libs)
  if 'user_libs' in kwargs and kwargs['user_libs']:
    libs.extend(kwargs['user_libs'])

  libs_path = env['INSTALL_LIBPATH']
  # ELF
  elf = env.Program( buildPath,
                     source=[sobjects, metadataObject],
                     LIBS=[libs], LIBPATH=libs_path
                   )
  env.Depends(elf, scl)

  image_map = env.subst(buildPath + '.map')
  image_sym = env.subst(buildPath + '.sym')

  env.Clean(elf, image_map)
  env.Clean(elf, image_sym)
  env.Clean(elf, metadataObject)

  pbn = env.InstallAs(buildPath + ".pbn", elf)
  env.Depends(pbn,elf)

  install_root = env.subst('${MBN_ROOT}')
  install_unsigned_root = env.SectoolGetUnsignedInstallPath(install_base_dir = install_root)
  env.Replace(MBN_FILE = os.path.join(install_unsigned_root, image))

  mbn = env.MbnBuilder( buildPath,
                        pbn, IMAGE_TYPE=image, MBN_TYPE="elf",
                        IMAGE_ID=4, FLASH_TYPE="sdcc")
  return_list.extend(mbn)
  env.Depends(mbn, pbn)
  #----------------------------------------------------------------------------
  # Sectools signing
  #----------------------------------------------------------------------------

  default_config = env.subst('${BUILD_ROOT}/sectools/config/integration/secimage.xml')
  soc_hw_version = None
  soc_vers = None

  if (SCons.Script.ARGUMENTS.get("SOC_HW_VERSION")):
    default_config = env.subst('${BUILD_ROOT}/sectools/config/integration/secimagev2.xml')
    soc_hw_version = SCons.Script.ARGUMENTS.get("SOC_HW_VERSION")
    soc_vers = SCons.Script.ARGUMENTS.get("SOC_VERS")

  secimage_xml_config = env.get('SECIMAGE_XML_CONFIG', default_config)
  #if the user passes his/her own secimage_xml_config file, the expectation here is that the
  #sign_id match the image name.
  if (default_config != secimage_xml_config):
    sign_id = image
  elif 'tee' in image:
    sign_id = 'tz_tee'
  else:
    sign_id = "tzapps"

  if ('user_app_id' in kwargs and kwargs['user_app_id']):
    app_id = kwargs['user_app_id']
  else:
    app_id='0x' + hashlib.sha256(image).hexdigest()[-16:]

  pil_base_dir = '${BUILD_ROOT}/build/ms/bin/PIL_IMAGES/SPLITBINS_${QC_SHORT_BUILDPATH}'

  sectools_signed_mbn = env.SectoolBuilder(
                            target_base_dir = '${OUT_DIR}/' + '${SHORT_BUILDPATH}',
                            source = mbn,
                            sign_id = sign_id,
                            app_id = app_id,
                            msmid = env.subst('${MSM_ID}'),
                            sectools_install_base_dir = install_root,
                            install_file_name = image + ".mbn",
                            config = secimage_xml_config,
                            pilsplitter_target_base_dir = pil_base_dir,
                            soc_hw_version = soc_hw_version,
                            soc_vers = soc_vers
                        )
  return_list.extend(sectools_signed_mbn)
  env.Depends(sectools_signed_mbn, mbn)
  #-------------------------------------------------------------------------
  # Build files for PIL driver
  #-------------------------------------------------------------------------
  unsigned_pil_dir = env.SectoolGetUnsignedInstallPath(install_base_dir = pil_base_dir)
  pil = env.PilSplitterBuilder(os.path.join(unsigned_pil_dir, image + '.mdt'), mbn)
  env.Depends(pil, sectools_signed_mbn)
  return_list.extend(pil)
  
  deployables = kwargs.get('deploy_sources', None)
  deploy_variants = kwargs.get('deploy_variants', None)
  if deployables:
    d = env.Deploy(deployables, deploy_variants = deploy_variants)
    env.Alias('deploy', d) #Dont add clean action for sources :-)
  else:
    env.Replace(DEPLOY_VARIANTS = deploy_variants)
    #logic to deploy binaries generated by sectools builder
    sectools_bin_list_file = os.path.join(env.subst(pil_base_dir), image + '.txt')
    if os.path.exists(sectools_bin_list_file):
      os.remove(sectools_bin_list_file)
    sectools_pil_images = env.GetSplitBinList(sectools_bin_list_file, sectools_signed_mbn)
    env.Depends('deploy', sectools_pil_images)
    env.Deploy([sectools_signed_mbn], deploy_variants = deploy_variants)
    #logic to deploy binaries generated by pil splitter builder 
    pil_bin_list_file = os.path.join(env.subst(pil_base_dir), image + '.pil')
    if os.path.exists(pil_bin_list_file):
      os.remove(pil_bin_list_file)
    pil_images = env.GetSplitBinList(pil_bin_list_file, pil)
    env.Depends('deploy', pil_images)
    env.Deploy(mbn, deploy_variants = deploy_variants)

  return return_list

def get_split_bin_list_act(target, source, env):
  target_str = target[0].get_abspath()
  pil_base_dir = os.path.dirname(target_str)
  print('target_str = {} pil_base_dir = {} \n'.format(target_str, pil_base_dir))
  image_name = os.path.splitext(os.path.basename(target_str))[0]

  for sname in source:
    sign_type = sname.get_abspath().split(os.sep)[-2]
    if 'signed' in sign_type: #either signed, unsigned or signed_encrypted
      target_dir_name = os.path.join(pil_base_dir, sign_type) + os.sep
    else:
      target_dir_name = pil_base_dir + os.sep
    print('Processing Glob in target_dir {}'.format(target_dir_name))
    mdt = env.Glob(os.path.join(target_dir_name, image_name + '.mdt'))
    sections = env.Glob(os.path.join(target_dir_name, image_name + '*.b*'))
    with open(target_str, 'a') as f:
      for name in mdt:
        f.write(name.get_abspath() + '\n')
      for name in sections:
        f.write(name.get_abspath() + '\n')
    d = env.Deploy([mdt,sections],deploy_variants = env.get('DEPLOY_VARIANTS'))
    env.Alias('deploy', d)
    env.Clean('deploy', d)
  return None
  
#this helper function helps return 3 parameters about the object file that is
#getting compiled. It determines the name and relative path of the object file
#from the path and name of source file being compiled. It also returns the
#extension of the source file name. Some apps include '.o' files in the list
#of sources. We want to add these object files directly to list of objects
#since SCons Object builder does not take an object file. Moreover, we also
#return back the status of presence of the source file, to determine if
#the file is stripped or not.
def get_object_file_name(env, spath):
  #source files can be of the form a.c, ../x/a.c, b/a.c.
  #in each of above cases, we want objects to be stored as
  #a.o, x/a.o, b/a.o
  if isinstance(spath, str):
    sstr = spath
    sourceNodeRepr = env.File(spath)
  elif isinstance(spath, list):
    print 'Error: get_object_file_name does not process list!! %s' % (str(spath))
    exit(1)
  else:
    sourceNodeRepr = spath

  spath_str = sourceNodeRepr.path
  split_pattern = env.subst('${BUILD_ROOT}/')
  if platform.system() == 'Windows':
    split_pattern = split_pattern.replace('/', '&').split(':')[-1]
    spath_str = spath_str.split(':')[-1].replace(os.sep, '&')
    sstr = spath_str.split(split_pattern)[-1]
    sstr = sstr.replace('&', os.sep)
  else:
    sstr = spath_str.split(split_pattern)[-1]

  #split at qsapps, otherwise path may become too long for windows to create object file
  sstr = sstr.split('qsapps' + os.sep)[-1]
  name, extension = os.path.splitext(sstr)
  node_exists = False
  if sourceNodeRepr.exists():
    node_exists = True
  #print 'Returning name and extension = %s %s from get_object_file_name' % (name, extension)
  #also return if the source file exists or we need to look for precompiled object file
  return (name, extension, node_exists)

#this is the helper function that helps build libraries that are used by
#apps to compose and link with their images. Using the secure app lib builder,
#we easily control the parameters like library name format, destination of libs and
#lib artifacts.
def secure_app_lib_builder(env, includes, sources, libname):
  env.Replace(LIBNAME = libname)
  env.Append(CFLAGS = '-fPIC')
  env.Append(CPPPATH = includes)

  install_dir = env.subst('${LIB_OUT_DIR}')
  objlist = compile_sources(env, install_dir, sources)
  lib = env.Library(os.path.join(install_dir, libname), objlist)
  if env.GetOption('cleanpack'):
    env.NoClean(lib)
  return lib

#this is the helper function that compiles the sources into object files.
#If the source files exist, they are always used for compilation.
#if the build is stripped of sources, the pre-built object files are
#used instead. To make the code and process easy, the list of prebuilt
#object files is gathered. If sources are present, then the the
#corresponding object file is removed from the list of prebuilt objects
#gathered earlier. The cummulative list of sources and objects is
#presented to the builder to use for compilation
def compile_sources(env, dest_dir, sources):
  sflatten = []
  sobjects = []

  #prepare a list of objects already built and existing in
  #out directory
  existing_objects = glob_objects_from_dest_dir(env, dest_dir)
  sflatten = env.Flatten(sources)

  for p in sflatten:
    objname, extension, exists = get_object_file_name(env,p)
    if exists: #The source file exists, compile using it
      if extension.lower() == '.o': #user has added .o file in list
        update_existing_object_list(env, existing_objects, objname)
        if env.GetOption('cleanpack'):
          env.NoClean(p)
        sobjects.append(p)
      else:
        o = env.Object(os.path.join(dest_dir,'objects',objname), p)
        sobjects.append(o)
        update_existing_object_list(env, existing_objects, objname)
        if env.GetOption('cleanpack'):
          env.NoClean(o)
  return [sobjects + existing_objects]

#this is a helper function. It takes the list of prebuilt object file
#artifacts and the name of object file artifact currently being
#considered for compilation. The idea is to remove the object file
#from existing list if it is being re-compiled since it's sources
#are present and are not stripped out.
def update_existing_object_list(env, existing_object_list, objname):
  tmp_list = existing_object_list
  for i in tmp_list:
    if i.rstr().split(os.sep)[-1].split('.o')[0] == objname.split(os.sep)[-1]:
      env.PrintDebugInfo('secappbldr', 'match found object_list = %s, objname = %s' % (i.rstr(), objname))
      existing_object_list.remove(i)
      return

#the helper function that globs the list of object files built for the target
#at give path. It is easy since the secure app builder controls the destination
#for the the object files, so we can do a straight glob. Return the list
#either empty or with matches
def glob_objects_from_dest_dir(env, pathname):
  matches = []
  for root, dirnames, filenames in os.walk(pathname):
    for filename in fnmatch.filter(filenames, '*.o'):
      matches.append(env.File(os.path.join(root, filename)))
  return matches

if __name__ == '__main__':
  import sys
  if (len(sys.argv) > 1) and (sys.argv[1] == '--help' or sys.argv[1] == '-h'):
    path = os.path.dirname(sys.argv[0])
    with open(os.path.join(path,'secure_app_builder_howto.txt'), 'r') as f:
      howto = f.read()
    print '%s' % howto
  else:
    print "Usage: python secure_app_builder.py --help|-h"
