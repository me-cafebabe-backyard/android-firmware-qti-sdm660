#!/usr/bin/env python
#-------------------------------------------------------------------------------
# Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#-------------------------------------------------------------------------------

import re
import os
import SCons.Action
import types

from datetime import datetime
from SCons.Script import *

#-------------------------------------------------------------------------------
#  Hooks for SCons
#-------------------------------------------------------------------------------

def exists(env):
   return env.Detect('secure_apps')

def generate(env):
   env.AddMethod(add_secure_app_metadata, "AddSecureAppMetadata")
   return None


def encode_c_str(str):
    str = re.sub(r'[?"\\]', lambda m: '\\' + m.group(0), str)
    str = re.sub(r'[\x00-\x1f]', lambda m: '\\%03o' % ord(m.group(0)), str)
    return '"' + str + '"'

#-------------------------------------------------------------------------------
#  add_secure_app_metadata
#-------------------------------------------------------------------------------

def add_secure_app_metadata(env, md):
   import sys
   sys.path.insert(0, env.subst('${BUILD_ROOT}/core/bsp/build/scripts'))
   import SecureAppMetadata
 
   filename = 'metadata.c'
   out_dir  = env.subst('${OUT_DIR}/' + '${SHORT_BUILDPATH}/') 
   out_path = os.path.join(out_dir, filename)
   print 'Generating module metadata file ' + out_path
   if not os.path.exists(out_dir):
      os.makedirs( out_dir )
   with file(out_path, 'w') as output:
      metadata_str = SecureAppMetadata.generate_metadata(md)
      metadata_appname = SecureAppMetadata.extractField(md, 'appName')
      when = datetime.now().strftime('%A, %x @ %X')
      output.write('''\
//-------------------------------------------------------------------------
// Auto-generated on %s.  Do not edit.
//-------------------------------------------------------------------------
#include <stddef.h>
const char __attribute__((section(".rodata.sentinel"))) TA_METADATA[] = %s;
const char* TA_APP_NAME = "%s";
''' % (when, encode_c_str(metadata_str), metadata_appname))
      metadata_uuid = SecureAppMetadata.extractField(md, 'UUID')
      # Add UUID if sepecified in metadata
      if metadata_uuid != None:
         metadata_uuid_components = re.split('-', metadata_uuid)
         # Treat the metadata as a set of bytes
         # Note: The bytes are in memory order not string order
         metadata_uuid_bytes = re.findall('[0-9a-fA-F]{2}', metadata_uuid)
         output.write('''\
const unsigned char TA_UUID[] = { 0x%s, 0x%s, 0x%s, 0x%s,
                                  0x%s, 0x%s, 0x%s, 0x%s,
                                  0x%s, 0x%s, 0x%s, 0x%s,
                                  0x%s, 0x%s, 0x%s, 0x%s };
''' % (metadata_uuid_bytes[0], metadata_uuid_bytes[1],
       metadata_uuid_bytes[2], metadata_uuid_bytes[3],
       metadata_uuid_bytes[4], metadata_uuid_bytes[5],
       metadata_uuid_bytes[6], metadata_uuid_bytes[7],
       metadata_uuid_bytes[8], metadata_uuid_bytes[9],
       metadata_uuid_bytes[10], metadata_uuid_bytes[11],
       metadata_uuid_bytes[12], metadata_uuid_bytes[13],
       metadata_uuid_bytes[14], metadata_uuid_bytes[15],
      ))
 
      metadata_abuf = SecureAppMetadata.extractField(md, 'acceptBufSize')
      output.write('''\
const unsigned int TA_ACCEPT_BUF_SIZE = %s;
char ta_acceptBuf[%s] = {0};
''' % (metadata_abuf, metadata_abuf))
      metadata_multiSession = SecureAppMetadata.extractField(md, 'multiSession')
      output.write('''\
#include <stdbool.h>
const bool ta_multiSession = %s;
''' % (metadata_multiSession))

      metadata_version = SecureAppMetadata.extractField(md, 'version')
      output.write('''\
const char * ta_version = "%s";
''' % (metadata_version))

      metadata_description = SecureAppMetadata.extractField(md, 'description')
      if metadata_description != None:
         output.write('''\
const char * ta_description = "%s";
''' % (metadata_description))
      else:
         output.write('''\
const char * ta_description = "";
''')

      metadata_properties = SecureAppMetadata.extractField(md, 'properties')
      if metadata_properties != None:
         output.write('''\
const struct TACustomProperty {
   char const * name;
   char const * value;
} ta_customProperties[] = {
''')
         for p in metadata_properties:
            output.write('''\
   {"%s", "%s" },
''' % (p, metadata_properties[p]))
         output.write('''\
};
''')
         output.write('''\
const unsigned int TA_CUSTOM_PROPERTIES_NUM = %s;
''' % (len (metadata_properties)))
      else:
         output.write('''\
const struct TACustomProperty {
   char const * name;
   char const * value;
} * const ta_customProperties = NULL;
const unsigned int TA_CUSTOM_PROPERTIES_NUM = 0;
''')
   mobj = Entry(out_path)
   return mobj
