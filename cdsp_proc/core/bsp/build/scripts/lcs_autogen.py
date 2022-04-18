#============================================================================
#
# LCS Builder
#
# GENERAL DESCRIPTION
#    Contains a builder that will take a LCS template file, and autogenerate
#    an appropriate linker file.  This builder needed to be separated from
#    the island_builder.py, as there will be instances where we would like to
#    autogenerate the LCS file when it isn't an island build.
#
# Copyright (c) 2009-2014 by Qualcomm Technologies Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#  $Header: //components/rel/core.qdsp6/1.0.c2/bsp/build/scripts/lcs_autogen.py#1 $
#  $DateTime: 2020/02/10 01:57:30 $
#  $Author: pwbldsvc $
#  $Change: 22511909 $
# 
#                      EDIT HISTORY FOR FILE
#                      
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#  
# YYYY-MM-DD   who     what, where, why
# ----------   ---     ---------------------------------------------------------
# 2014-08-29   sm      Initial revision.  Ported from island_builder.py.
# 
#============================================================================
import os
import re

#----------------------------------------------------------------------------
# Global values
#----------------------------------------------------------------------------
LCS_AUTOGEN_USES_FLAG = 'USES_LCS_AUTOGEN'

qurt_linker_script = 'qurt_linker_script'

#----------------------------------------------------------------------------
# Hooks for SCons
#----------------------------------------------------------------------------
def exists(env):
   return env.Detect('lcs_autogen')

def generate(env):
   env.AddUsesFlags(LCS_AUTOGEN_USES_FLAG)
   
   # Generate the builder.
   lcs_autogen_generate(env)

#============================================================================
# Linker Build Rules
#============================================================================
def lcs_autogen_generate(env):
   # Kernel provided linker script generator.
   rootenv = env.get('IMAGE_ENV')
   qurt_script = env.RealPath('${COREBSP_ROOT}/kernel/qurt/scripts/qurt-island-link.py')
   rootenv[qurt_linker_script] = qurt_script

   # Define a method to indirectly invoke the builder.
   env.AddMethod(lcs_linker_generate_lcs, "GenerateLCSFileFromTemplate")
   
   # Added on the action_source = None in the case that no source files are 
   # provided.  The builder will generate a .lcs file.
   lcs_link_act = env.GetBuilderAction(lcs_linker_builder,action_source=None)
   lcs_link_bld = env.Builder(action = lcs_link_act,suffix = '.lcs')

   
   # Add this builder to the list of builders.
   env.Append(BUILDERS = {'GenerateLCSFileFromTemplateInternal' : lcs_link_bld})


#-----------------------------------------------------------------------------
# Function:    lcs_linker_generate_lcs
# Description: This method invokes the GenerateLCSFileFromTemplateInternal.  It passes the
#              linker template path, generated linker output path, the island 
#              specifications, and the kernel script.
#              It installs the generated linker file in the root of the image
#              being build.
# Inputs:      linker_script - The destination location of the generated linker
#              script.
#              template - The linker template file, that is annotated with the 
#              appropriate anchors.
#              island_spec - The island specification file(s), passed as an array.  
#              This is the generated output from the previous call to the 
#              IslandInternalBuilder, or can be passed directly to the builder.  
#              Each line should have three values.  We can pass in multiple files.
#              If we don't pass anything in, it will not generate anything.
#              qurt_script - The kernel script that parses the island specification
#              and the template file.
# Outputs:     lcs_linker - The autogenerated file.
#-----------------------------------------------------------------------------
def lcs_linker_generate_lcs(env, linker_script, template, island_spec=[]):
   rootenv = env.get('IMAGE_ENV')
   lcs_linker = env.GenerateLCSFileFromTemplateInternal(linker_script, [template, rootenv[qurt_linker_script], island_spec])
   return lcs_linker

#-----------------------------------------------------------------------------
# Function:    lcs_linker_builder
# Description: This is the builder abstraction.
# Inputs:      None.
# Outputs:     None.
#-----------------------------------------------------------------------------
def lcs_linker_builder(target, source, env):
   # Declare an array to store the Island Specification Files, if any.
   ispecs = []
   # This is the target file.
   linker_script = str(target[0])
   # This is the source template file.
   linker_script_template = str(source[0])
   # This is the Kernel Script to parse the Island Specification files.
   qurt_script = str(source[1])
   # The remainder of the sources are Island Specification Files.  Save them
   # as their own array.
   for nodes in source[2:len(source)]:
      ispecs += [str(nodes)]
   
   # Generate the LCS file.
   generate_lcs_file(env, linker_script, linker_script_template, qurt_script, ispecs)

   
#-----------------------------------------------------------------------------
# Function:    generate_lcs_file
# Description: This builder will generate the linker file from the template.
#              It installs the generated linker file in the root of the image
#              being build.
# Inputs:      linker_script_template - The linker template file, that is annotated with the 
#              appropriate anchors.
#              ispecs - The island specification file(s) that are potentially saved as an array.  
#              This is the generated output from the previous calls to the IslandInternalBuilder.  
#              Each line should have three values.
#              qurt_script - The kernel script that parses the island specification
#              and the template file.
# Outputs:     linker_script - The autogenerated file.
#-----------------------------------------------------------------------------
def generate_lcs_file(env, linker_script, linker_script_template, qurt_script, ispecs):
   import imp
   # Attempt to load the QuRT linker script generator.
   try:
      qurt_island = imp.load_source('qurtisland', qurt_script)
   except:
      print "Failed to load the kernel linker script generator."
      raise Exception()
   # Call the QuRT supplied linker script generator.  Keep in mind 'ispecs' can potentially
   # be an array!
   qurt_island.create_lcs(linker_script, linker_script_template, None, *ispecs)
   

