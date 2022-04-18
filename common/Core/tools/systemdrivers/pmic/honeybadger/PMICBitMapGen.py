#===========================================================================
#
#  @file PMICBitMapGen.py
#  @brief Python script for parsing PMIC register list and creating a 
#         bitmap for SW to read only valid peripherals during init.
#
#  This file can be invoked directly by calling:
#
#  PMICBitMapGen.py pmic_names [pmic_names ...] [-h]
#  examples: PMICBitMapGen.py pm8994 pmi8994
#            PMICBitMapGen.py pmd9645 none none pmk8001
#
#  ===========================================================================
#
#  Copyright (c) 2015 QUALCOMM Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.glue/1.2.1/tools/tools/systemdrivers/pmic/honeybadger/PMICBitMapGen.py#1 $
#  $DateTime: 2017/01/19 09:08:15 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

# ============================================================================
# Imports
# ============================================================================

import re
import os
import sys
import argparse

# ============================================================================
# CreateBitMap
#
# Creates and returns a bit map list for given peripheral ids list
# ============================================================================

def CreateBitMap(peripheral_list):
  bitmap_list = []

  for i in range(32):
    bitmap_list.append(0)

  for periph in peripheral_list:
    if periph > 256:
      print('Invalid peripheral id %d detected' %periph)
      sys.exit(1)
    bitmap_mask=periph%8
    bitmap_index=int((periph - bitmap_mask)/8)
    bitmap_list[bitmap_index] = bitmap_list[bitmap_index] | (1<<bitmap_mask)

  return bitmap_list

# ============================================================================
# ParseRegisterList
#
# Parses the register list and returns a dictionary of {slave id:peripheral bitmaps}
# ============================================================================

def ParseRegisterList(register_list):
  peripheral_list = []
  peripheral_list_sid0 = []
  peripheral_list_sid1 = []
  peripheral_bitmap = {}

  # Parse peripheral list from register list
  for reg in register_list:
    periph = (int(reg,base=16)>>8)&0xFFF
    if periph not in peripheral_list:
      peripheral_list.append(periph)

  for periph in peripheral_list:
    slave_id = (periph>>8)&0xF
    if slave_id == 0:
      periph_id = periph&0xFF
      peripheral_list_sid0.append(periph_id)
    elif slave_id == 1:
      periph_id = periph&0xFF
      peripheral_list_sid1.append(periph_id)

  peripheral_list_sid0 = sorted(peripheral_list_sid0)
  peripheral_list_sid1 = sorted(peripheral_list_sid1)

  peripheral_bitmap.update({0:CreateBitMap(peripheral_list_sid0)})
  peripheral_bitmap.update({1:CreateBitMap(peripheral_list_sid1)})

  return peripheral_bitmap

# ============================================================================
# ReadInputFile
#
# Reads the input register list file and updates the pmic_bitmap dictionary
# ============================================================================

def ReadInputFile(config):

  for pmic in config['pmic_names']:
    pmic = pmic.lower()
    if (pmic == 'none') | (pmic == 'null'):
      continue

    if os.path.isdir(pmic):
      dirs = os.listdir(pmic)
      if len(dirs) != 0:
        file = pmic + '\\' + dirs[-1] + '\\PMICRegisterList.txt'
      else:
        print('Cannot find "%s" version folder' % pmic)
        sys.exit(1)
    else:
      print('Cannot find "%s" folder' % pmic)
      sys.exit(1)

    try:
      input = open(file, 'r')
      print('RegisterList:' + file)
    except:
      print('Cannot open "%s"' % file)
      sys.exit(1)
    register_list = input.read().splitlines()
    config['pmic_bitmap'].update({pmic:ParseRegisterList(register_list)})

# ============================================================================
# WriteOutputFile
#
# Creates an output file and writes the bit map to output file.
# ============================================================================

def WriteOutputFile(config):
  output_flag = False
  
  if config['std_output']:
    output = sys.stdout
  elif 'output_file' in config:
    try:
      # Create and open an output file.
      output = open(config['output_file'], 'w+')
      output_flag = True
    except:
      print('Unable to create and open output file so diverting output to cmd prompt')
      output = sys.stdout
  else:
    print('Unable to create and open output file so diverting output to cmd prompt')
    output = sys.stdout

  # Print generated bitmap
  output.write('const uint8 pm_periph_bitmap[][PM_MAX_NUM_SLAVE_IDS_PER_PMIC][PM_MAX_BITMAP_ENTRIES] =\n')
  output.write('{\n')
  for pmic in config['pmic_names']:
    if pmic in config['pmic_bitmap'].keys():
      output.write('  /* %s */\n' % pmic)
      output.write('  {\n')
      for sid in range(0, 2) :
        count = 0
        output.write('    {\n')
        output.write('      ')
        for bitmap in config['pmic_bitmap'][pmic][sid]:
          output.write('%s, ' % format(bitmap, '#04x'))
          count = count + 1
          if count == 4:
            output.write('\n')
            output.write('      ')
            count = 0
        output.write('\n')
        output.write('    },\n')
      output.write('  },\n')
    else:
      output.write('  {\n')
      output.write('    {NULL},\n')
      output.write('    {NULL}\n')
      output.write('  },\n')

  output.write('};\n')

  if output_flag ==  True:
    print('Bitmap generated to "%s" file' % config['output_file'])

  if 'output_file' in config:
    output.close()

# ============================================================================
# ParseCommandLine
#
# Parse command line arguments.
# ============================================================================

def ParseCommandLine (argv, config):
  parser = argparse.ArgumentParser(description='Generates bit map for given pmics e.g PMICBitMapGen.py pm8994 pmi8994')
  parser.add_argument('pmic_names', type=str, nargs='+', help='pmic names to generate bit map e.g PMICBitMapGen.py pmd9645 none pmk8001')
  parser.add_argument('--output', type=str, help='optional argument to provide bitmap text file output location')
  args = parser.parse_args()
  config['pmic_names'] = args.pmic_names
  if (args.output != None):
    if (args.output == 'std') | (args.output == 'cmd'):
      config['std_output'] = True
    else:
      # Check for // or \\ or [A-Z]: to make sure current dir is not used
      matches = re.match('(^[A-Za-z]:)|(^\\\\)|(^\/\/)', args.output)
      if matches != None:
        config['output_file'] = args.output
      else:
        print('Cannot use the given output location so using default output location!')

# ============================================================================
# Main
#
# Entry point.
# ============================================================================

if __name__ == "__main__":

  config = {
    'pmic_names': [],
    'pmic_bitmap': {},
    'output_file': 'C:\\Temp\\bitmap.txt',
    'std_output': False,
  }

  # Parse the command line
  ParseCommandLine(sys.argv[1:], config)

  # Read the input file
  ReadInputFile(config)

  # Write to output file
  WriteOutputFile(config)

