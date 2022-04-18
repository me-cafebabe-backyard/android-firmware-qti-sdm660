#  ===========================================================================
#
#  Copyright (c) 2011-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================

from __future__ import print_function
import argparse
import glob
import itertools
import sys
import os
import logging
import shutil
import struct
import time
import traceback
from importlib import import_module

# custom modules
from hansei_utils import print_p
from ddr_memory import DDRMemory, DumpTable
from pretty_print import PrettyPrint
from hansei_config import dump_file_types
from hansei_config import known_targets
from hansei_config import known_families
from hansei_config import default_target_family
from hansei_config import dumptable_config
from hansei_config import dumptable_version_map

'''
Setup arguments parser
'''

parser = argparse.ArgumentParser(description='Generate introspective RPM logs.')
parser.add_argument('files', metavar='dumpfile', nargs='+', type=str, help='dumped ram files (*.bin, *.lst) [required]')
parser.add_argument('--elf', metavar='rpm.elf', default='', help='.elf with (at least closely) matching symbols. Defaults to elf in current build [required]')
parser.add_argument('--output', '-o', metavar='logs_path', default='./output', help='location to place output logs [optional]')
parser.add_argument('--verbose', '-v', action='count', default=0, help='verbosity (more v\'s == more messages) [optional]')
parser.add_argument('--parser', '-p', metavar='parse_path', default='', help='absolute path to folder containing rpm_log_bfam.py [optional]')
parser.add_argument('--parser_rel', '-r', action='count', default=0, help='notes that the path given for the --parser argument is a relative path to folder containing rpm_log_bfam.py from folder containing hansei.py [optional]')
parser.add_argument('--target', '-t', metavar='target', default='', help='Target dumps are being parsed for. ex 8974 [optional]')
parser.add_argument('--family', '-f', metavar='family', default='', help='Target family dumps are being parsed for. May be one of (b)adger, bear/bagheera, or ((h)oney)badger) [optional]')
parser.add_argument('--no_mangle', action='count', default=0, help='Disable overwriting RPM coderam with code from elf')
parser.add_argument('--no_ddr', action='count', default=0, help='Prevent recovering RPM CODERAM from DDR')
parser.add_argument('--use_recovery', action='count', default=0, help='Prevents recovering RPM CODERAM from DDR, uses already recovered CODERAM_RECOVERED.BIN from <output dir>/binaries')
parser.add_argument('--fill_char', metavar='fill_char', default='space', help='Fill character for dumpers that use a fill, avaliable options are: underscore, dot, space, zero, or any single character [optional]')
parser.add_argument('--show_trace', action='count', default=0, help='Show traceback, used to help with debugging script issues')
parser.add_argument('--coderam_name', default='', help='Specify CODERAM file name')
parser.add_argument('--dataram_name', default='', help='Specify DATARAM file name')
parser.add_argument('--msgram_name', default='', help='Specify MSGRAM file name')
parser.add_argument('--ocimem_name', default='', help='Specify OCIMEM file name')
parser.add_argument('--ddr0_name', default='', help='Specify DDRCS0 file name')
parser.add_argument('--ddr1_name', default='', help='Specify DDRCS1 file name')

# Parse arguments
args = parser.parse_args(sys.argv[1:])

# Create output directories
binary_output=args.output+"/binaries"
if not os.path.exists(args.output):
    os.makedirs(args.output)
if not os.path.exists(binary_output):
    os.makedirs(binary_output)

#Setup pretty printer
pretty = PrettyPrint()
pretty.set_log_output(args.output+"/hansei_log.txt")

#Record arguments used
pretty.p("Hansei agruments:", display=False)
pretty.set_min_tab(1)
for item in sys.argv:
  pretty.p(item, display=False)
pretty.set_min_tab(0)

'''
Setup debugging
'''
verbosity = [logging.ERROR, logging.WARNING, logging.INFO, logging.DEBUG]
logging.basicConfig(format='%(levelname)-8s | %(name)-20s | %(message)s', level=verbosity[min(len(verbosity)-1, args.verbose)])
#logging.basicConfig(format='%(levelname)-8s | %(name)-20s | %(message)s', level=logging.DEBUG)
logger = logging.getLogger(__name__)

'''
Begin Hansei
'''
pretty.p("")
pretty.p(" Start Time: "+time.ctime())
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"
pretty.p("")                                      # "#                                                                              #"
pretty.p("Welcome to RPM Hansei",format="center") # "#                            Welcome to RPM Hansei                             #"
pretty.p("")                                      # "#                                                                              #"
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"
pretty.p("\tChecking for required tools:")
try:
  error_msg = '\tERROR: Failed to find pyelftools. Please ensure you have this package.    '
  from elftools.elf.elffile import ELFFile
  pretty.p('\t\tpyelftools... found')
except:
  pretty.p(error_msg)
  pretty.p("",fill="-")                           # "#------------------------------------------------------------------------------#"
  exit(1)
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"

from memory import Memory
from dwarf import DebugInfo, decode_object
from elftools.common.py3compat import (ifilter, byte2int, bytes2str, itervalues, str2bytes)

'''
Find and read ELF file
'''
if args.elf == '':
  elf_dir = os.path.realpath(__file__).split('rpm_proc')[0]+'rpm_proc\\core\\bsp\\rpm\\build'
  elf_file = '';
  for file in os.listdir(elf_dir):
    if file.endswith(".elf"):
      elf_file = file
  if elf_file != '':
    args.elf = elf_dir+"\\"+elf_file
  

if args.elf == '':
  pretty.p("ERROR FATAL: No .elf file given and no .elf file found in current build... Aborting")
  pretty.p("",fill="-")                           # "#------------------------------------------------------------------------------#"
  sys.exit(-1)

pretty.p('\tReading ELF from {0} ... '.format(args.elf))
di = DebugInfo(args.elf)
shutil.copy(args.elf,binary_output+"/"+os.path.basename(args.elf))
system = Memory()
#system2 is for Non-RPM memories that need to be loaded
system2 = Memory()

elf_target = ''

for nsec, section in enumerate(di.elf.iter_sections()):
  name=bytes2str(section.name)
  if "_xml_DEVCONFIG_DATA" in name:
    elf_target = name.split('_')[0]
    pretty.p("\t\tELF for "+elf_target)
    break
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"

'''
Determine target and family
'''
if elf_target != '' and args.target != elf_target:
  if args.target == '':
    pretty.p("\tWARNING: No target specified, using target from elf")
  else:
    pretty.p("\tWARNING: elf target and provided target do not match")
    pretty.p("\t\tUsing elf target")
  args.target = elf_target

target_family = known_families.get(args.family.lower(), "UNKNOWN FAMILY")
target_family = known_targets.get(args.target, target_family)
hansei_target = known_targets.get(args.target, '????')
if hansei_target != '????':
  hansei_target = args.target
if target_family == "UNKNOWN FAMILY":
  pretty.p("\WARNING: UNKNOWN FAMILY, using default")
  target_family = default_target_family['family']
pretty.p("\tSelected family: %s"%target_family)
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"
'''
Collect and load binary files
'''
temp_files = [f if not os.path.isdir(f) else os.path.join(f, '*.bin') for f in args.files] # if a directory is specified, look for dumps *in* it
#hack for when .lst files are given
args.files = temp_files + [f if not os.path.isdir(f) else os.path.join(f, '*.lst') for f in args.files]
args.files = set(itertools.chain(*[glob.glob(f) for f in args.files]))

#add file name if given
for dft in dump_file_types:
    if dft['display_name'] == 'CODERAM' and args.coderam_name:
        dft['name'].add(args.coderam_name)
    if dft['display_name'] == 'DATARAM' and args.dataram_name:
        dft['name'].add(args.dataram_name)
    if dft['display_name'] == 'MSGRAM' and args.msgram_name:
        dft['name'].add(args.msgram_name)
    if dft['display_name'] == 'OCIMEM' and args.ocimem_name:
        dft['name'].add(args.ocimem_name)
    if dft['display_name'] == 'DDRCS0' and args.ddr0_name:
        dft['name'].add(args.ddr0_name)
    if dft['display_name'] == 'DDRCS1' and args.ddr1_name:
        dft['name'].add(args.ddr1_name)

pretty.p("\tReading dump files...")
required = set()
for dft in dump_file_types:
    if not dft.get('required'):
        continue
    if type(dft['base'][target_family])==dict:
        required.add(dft['base'][target_family][hansei_target])
    else:
        required.add(dft['base'][target_family])

read_bases = {-1}
store_bases = {}
for dumpfile in args.files:
  dfn = os.path.basename(dumpfile)                        # File name + extension
  dfs = os.path.getsize(dumpfile)                         # File size
  dfe = os.path.splitext(dumpfile)[1]                     # File extension
  dfne = os.path.basename(os.path.splitext(dumpfile)[0])  # File name (no extension)
  #import pdb; pdb.set_trace()

  for dft in dump_file_types:
    #try for known names or for combinations of known base names and extensions
    if (dfn in dft['name']) or ((dfe.upper() in dft['ext']) and (dfne.upper() in dft['basename'])):
      if dft.get('no_load',False) == True:
        dft['path'] = dumpfile
        if dft.get('update',False) == True:
          dft['size'] = os.path.getsize(dumpfile)
          #pretty.p("\t\tUpdating {0} size:{1}".format(dft['display_name'],hex(dft['size'])))
      else:
        if type(dft['base'][target_family])==dict:
            base = dft['base'][target_family][hansei_target]
        else:
            base = dft['base'][target_family]
        if base not in read_bases:
          with open(dumpfile, 'rb') as data:
            read_bases.add(base)
            system.load_hunk(base, data.read())
            required -= {base}
            shutil.copy(dumpfile, binary_output+"/"+dfn)
            dft['size'] = os.path.getsize(dumpfile)
            store_bases[dft.get('display_name',"None")] = base
            pretty.p("\t\tLoading {0} at 0x{1:0>8x} from {2} ".format(dft['display_name'], base, dumpfile))
            try:
              logger.debug("Reading %s into 0x%0.8x" % (dumpfile, base))
            except:
              logger.debug("Reading %s into a variable address" % (dumpfile))

if required:
  pretty.p("ERROR FATAL: Did not find all required RAM dumps!")
  pretty.p("\t(Missing dumps for regions starting at [%s].)" % (' '.join(hex(base) for base in required)))
  pretty.p("ABORTING")
  pretty.p("",fill="-")                           # "#------------------------------------------------------------------------------#"
  sys.exit(-1)

pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"

'''
Recover RPM CODERAM from DDR
'''
ddr = DDRMemory()
while args.no_ddr==0 and args.use_recovery==0:
  loaded=0
  dumptable_ptr=0x0
  pretty.p("\tRecovering CODERAM...")
  for dft in dump_file_types:
    if dft.get('display_name',"None") == "OCIMEM":
      if dft['path'] != '':
        with open(dft['path'], 'rb') as data:
          if type(dft['base'][target_family])==dict:
              base = dft['base'][target_family][hansei_target]
          else:
              base = dft['base'][target_family][hansei_target]
          system2.load_hunk(base, data.read())
          pretty.p("\t\tLoading {0} at 0x{1:0>8x} from {2} ".format(dft['display_name'], base, dft['path']))
          dumptable_ptr=dft['data']['dumptable'][hansei_target]
          loaded=1
        break
  if loaded:
    try:
        #import pdb; pdb.set_trace()
        dt_addr = struct.unpack('<Q', system2.read(dumptable_ptr,8))[0]
        pretty.p("\t\tPrimay dumptable address is: "+hex(dt_addr))
        ddr_info = {}
        for dft in dump_file_types:
          if dft.get('no_load',False) == True:
            if "DDRCS" in dft.get('display_name',''):
              #import pdb; pdb.set_trace()
              if dft['path'] != '':
                path = dft['path']
                base = dft['base'][target_family][dft['size']]
                size = dft['size']
                pretty.p("\t\tLoading {0} at 0x{1:0>9x} from {2} ".format(dft['display_name'], base, path))
                ddr.add_ddr(path, base, size)
              else:
                pretty.p("\t\tWARNING: Missing {0} file".format(dft.get('display_name', 'unknown')))

        dt_ver = dumptable_version_map.get(hansei_target,dumptable_version_map['default'])
        dumpT = DumpTable(dumptable_config[dt_ver], dt_addr, ddr)
        if dumpT.get_error() != '':
          pretty.p("\t\tWARNING: "+dumpT.get_error())
          pretty.p("\t\tWARNING: Skipping DDR CODERAM RECOVERY")
          break

        # 0xEA is the magic identifier for RPM dumps.
        cr_struct_addr = dumpT.find_dump_entry(0xEA)
        if cr_struct_addr == 0x0:
          pretty.p("\t\tWARNING: No RPM CODERAM recovery found in DDR")
          break
        else:
          pretty.p("\t\tFound RPM CODERAM recovery in DDR")
        [cr_name, cr_addr, cr_len, cr_data] = dumpT.read_entry_data(cr_struct_addr)
        pretty.p("\t\tRPM CODERAM Recovered by {0}".format(cr_name))
        coderam_base = 0x0
        for l_dft in dump_file_types:
          if l_dft.get('display_name', '') == "CODERAM":
            coderam_base = l_dft['base'][target_family]
            break
        # Write recovered coderam to 'CODERAM_RECOVERED.BIN'
        with open(binary_output+"/CODERAM_RECOVERED.BIN", 'wb') as cr_recover:
          #import pdb; pdb.set_trace()
          cr_recover.write(cr_data)
          # Load 'CODERAM_RECOVERED.BIN' into memory
          pretty.p("\t\tLoaded recovered RPM CODERAM [{0}-{1}] from 0x{2:x}".format( hex(coderam_base), hex(cr_len), cr_addr ) )
          system.overwrite(coderam_base, cr_data)
        break
    except:
      pretty.p("\t\tWARNING: No RPM CODERAM recovery found in DDR")
  else:
    pretty.p("\t\tWARNING: No OCIMEM binary, skipping CODERAM recovery")
  break
#ensure all files are closed
ddr.close_all()

'''
Load recovered CODERAM
'''
if args.use_recovery==1:
  pretty.p("\tLoading previouly recovered CODERAM...")
  if os.path.exists(binary_output+"/CODERAM_RECOVERED.BIN"):
    coderam_base = 0x0
    for l_dft in dump_file_types:
      if l_dft.get('display_name', '') == "CODERAM":
        coderam_base = l_dft['base'][target_family]
        break
    with open(binary_output+"/CODERAM_RECOVERED.BIN", 'rb') as data:
      system.overwrite(coderam_base, data.read())
      pretty.p("\t\t...done")
  else:
    pretty.p("\t\tWARNING: <output dir>/binaries/CODERAM_RECOVERED.BIN does not exist")
    pretty.p("\t\t\tSkipping loading")

'''
Mangle RAM CODERAM if needed
'''
if args.no_mangle==0:
  pretty.p("\tValidating code ram...")
  rgn_names = [
    'CODE_RAM',
    'CODE_RAM_DAL',
    'CODE_RAM_DEBUGTOOLS',
    'CODE_RAM_DEBUGTRACE',
    'CODE_RAM_KERNEL',
    'CODE_RAM_MPROC',
    'CODE_RAM_MPROC_GLINK',
    'CODE_RAM_POWER',
    'CODE_RAM_POWER_ACC',
    'CODE_RAM_POWER_CPR',
    'CODE_RAM_POWER_MPM',
    'CODE_RAM_POWER_NPA',
    'CODE_RAM_POWER_RAILWAY',
    'CODE_RAM_POWER_RPM',
    'CODE_RAM_POWER_SLEEP',
    'CODE_RAM_POWER_ULOG',
    'CODE_RAM_SYSDRV',
    'CODE_RAM_SYSDRV_CLOCK',
    'CODE_RAM_SYSDRV_ICB',
    'CODE_RAM_SYSDRV_PMIC',
    'CODE_RAM_SYSDRV_SPMI',
    'CODE_RAM_DDR',
  ]
  for rgn_name in rgn_names:
      try:
          [addr, data, size] = di.get_section_data(rgn_name)
      except:
          continue

      pretty.p("\t\tValidating %s ..." % rgn_name)

      # Validate RAM CODERAM, if existing Code is ok, leave it alone, otherwise overwrite
      match=1
      for i in range(size):
        if data[i] != system.read(addr+i,1):
          match=0
          #pretty.p("\t\t\tELF--{0} mismatch at offset {1}".format(rgn_name, i))
          hex_data = hex(struct.unpack('<I', data[i:i+4])[0])
          hex_sys = hex(struct.unpack('<I', system.read(addr+i,4))[0])
          #pretty.p("\t\t\t\t '{0}' <> '{1}'".format( hex_data, hex_sys ))
          break
      if match==0:
        pretty.p("\t\t\t%s does not match elf, recovering from elf." % rgn_name)
        system.overwrite(addr, data)
      else:
        pretty.p("\t\t\t%s matches elf, continuing." % rgn_name)

'''
Create loading scripts
'''
with open(binary_output+"/load_core_rpm_binaries.cmm", 'w') as cmm:
  print(";Load script for binaries collected with hansei", file=cmm)
  print("", file=cmm)
  print("; Store current working directory", file=cmm)
  print("&cwd=OS.PWD()", file=cmm)
  print("cd {0}".format(binary_output), file=cmm)
  print("", file=cmm)
  print("; Setup T32", file=cmm)
  print("sys.cpu CORTEXM3", file=cmm)
  print("sys.u", file=cmm)
  print("", file=cmm)
  print("; Load Binaries", file=cmm)
  print("d.load.binary ./MSGRAM.BIN {0} /noclear".format(hex(store_bases['MSGRAM'])), file=cmm)
  print("d.load.binary ./DATARAM.BIN {0} /noclear".format(hex(store_bases['DATARAM'])), file=cmm)
  print("d.load.binary ./CODERAM.BIN {0} /noclear".format(hex(store_bases['CODERAM'])), file=cmm)
  print("", file=cmm)
  print("; Load ELF", file=cmm)
  print("d.load.elf {0} /nocode /noclear".format("./"+os.path.basename(args.elf)), file=cmm)
  print("", file=cmm)
  print("; Restore directory", file=cmm)
  print("cd &cwd", file=cmm)
cmm_re = open(binary_output+"/load_core_rpm_binaries_recovered.cmm", 'w')
with open(binary_output+"/load_core_rpm_binaries.cmm", 'r') as cmm:
  for line in cmm.readlines():
    if "./CODERAM.BIN" in line:
      edit = line.split("./CODERAM.BIN")
      line = edit[0] + "./CODERAM_RECOVERED.BIN" + edit[1]
    cmm_re.write(line)
cmm_re.close()
  
  

pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"

'''
Find ulog parsers
'''
if (args.parser != '' and args.parser_rel != 0):
    args.parser = os.path.realpath(__file__).split(os.path.basename(__file__))[0]+args.parser
if (args.parser == ''):
    args.parser = os.path.realpath(__file__).split('rpm_proc')[0]+'rpm_proc/core/power/rpm/debug/scripts/'
    #try server location if build path doesn't work
    if (os.path.isfile(args.parser+'rpm_log_bfam.py')==False):
        args.parser=os.path.realpath(__file__).split(os.path.basename(__file__))[0]+'../bfam_log_parser/'
    if (os.path.isfile(args.parser+'rpm_log_bfam.py')==False):
        pretty.p('\t\t-Failed to find ulog parser, please specifiy location with --parser(-p).')
        pretty.p('\t\t\tFor path relative to location of hansei.py, also include -r.')
if (args.parser[len(args.parser)-1] != '/'):
    args.parser = args.parser+'/'

pmic_mem = Memory()
ocimem_mem = Memory()
if target_family == 'badger':
    for dumpfile in args.files:
        dfn = os.path.basename(dumpfile)
        #import pdb; pdb.set_trace()
        
        if dfn in ['OCIMEM.BIN','ocimem.bin']:
            pretty.p('\t\tAttemping to load OCIMEM at 0x0...')
            logger.debug("Reading %s into 0x%0.8x" % (dumpfile, 0x0))
            with open(dumpfile, 'rb') as data:
                ocimem_mem.load_hunk(0x0, data.read())
            pretty.p('\t\t...done')
        if dfn in ['PMIC_RTC.BIN']:
            pretty.p('\t\tAttemping to load PMIC_RTC at 0x0...')
            logger.debug("Reading %s into 0x%0.8x" % (dumpfile, 0x0))
            with open(dumpfile, 'rb') as data:
                pmic_mem.load_hunk(0x0, data.read())
            pretty.p('\t\t...done')

'''
Parse dumps
'''

# Generic data struct
debug_data = {}
debug_data['dump_path'] = args.output
debug_data['rpm_memory'] = system
debug_data['sys_memory'] = system2
debug_data['pmic_memory'] = pmic_mem
debug_data['ocimem_memory'] = ocimem_mem
[addr, data, size] = di.get_section_data("CODE_RAM_RECLAIM_POOL")
if addr != None:
  reclaim_mem = Memory()
  reclaim_mem.load_hunk(addr, data)
  debug_data['reclaim_pool'] = {'start_addr':addr, 'memory':reclaim_mem, 'size':size}
debug_data['debug_info'] = di
debug_data['args'] = args
debug_data['target'] = hansei_target
debug_data['family'] = target_family
[i_s_addr, i_s_data, i_s_size] = di.get_section_data("RPM_IMAGE_ID")
if i_s_addr != None:
  debug_data['image_strings_addr'] = i_s_addr
else:
  debug_data['image_strings_addr'] = dump_file_types[1]['base'][target_family] #start of data_ram

# Summary is special and needs to be dumpped first
pretty.p('\tDumping summary...')
import dumpers.summary as summary
try:
  [temp_target, branch] = summary.dump(debug_data) #args.output, system, di, dump_file_types[1]['base'][target_family])
except:
  pretty.p("\t...WARNING: Critical error occured, dumps may not match elf")
  temp_target = hansei_target
  branch = default_target_family['branch']
if temp_target != hansei_target:
  if temp_target != '8974 Pro' and hansei_target != '????':
    pretty.p('\t\t...WARNING!!! TARGET MISMATCH, SPECIFIED TARGET %s'%hansei_target)
  hansei_target = temp_target
debug_data['target'] = hansei_target
debug_data['branch'] = branch
pretty.p('\t\t...Discovered target: %s'%hansei_target)
dumps_run = ['summary.py']

# Configure pretty printer to add a tab
pretty.set_min_tab(1)
debug_data['printer'] = pretty

for file in os.listdir(os.path.dirname(__file__)+'/dumpers'):
  if not ('init' in file) and not (file in dumps_run) and not ('.pyc' in file):
    dumps_run += [file]
    mod = import_module('.'+file.split('.')[0], 'dumpers')
    try:
      mod.dump(debug_data)
    except:
      pretty.p("\tCritical error occured in running dump, continuing...")
      #if args.show_trace:
      pretty.p(traceback.format_exc())

pretty.set_min_tab(0)

pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"
pretty.p('\tNote: If errors were reported, dumps may be corrupt.')
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"
pretty.p('\tHansei finished')
pretty.p("",fill="-")                             # "#------------------------------------------------------------------------------#"
pretty.p(" End Time: "+time.ctime())
pretty.p(" Files/directories used during processing:")
pretty.p( "\tElf: "+args.elf)
pretty.p( "\tUlog parser Directory: "+args.parser)
pretty.p( "\tOutput Directory: %s"%args.output)

