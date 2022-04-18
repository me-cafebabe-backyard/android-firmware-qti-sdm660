import struct, os, shutil, copy

# TODO : In the interest of avoiding globals, these constants should
# be encapsulated within a class
DEBUG                    = 0
PAGE_SIZE                = 4096
EMPTY_PT_MARKER          = (struct.pack('<Q', 0x2))
TZ_PA_SIZE               = 36
TZ_VAS_SIZE              = (1 << TZ_PA_SIZE)
TZ_VAS_LAST_ADDRESS      = (TZ_VAS_SIZE - 1)

def GB2MB(num_gb):
  return (num_gb * 1024)

def MB2KB(num_mb):
  return (num_mb * 1024)

def KB2B(num_kb):
  return (num_kb * 1024)

def B2KB(num_b):
  return (num_b / 1024)


######################################

mapping_sizes = [KB2B(MB2KB(GB2MB(1))), KB2B(MB2KB(2)), KB2B(4)]
ptables = [[], [], []]

######################################

def is_aligned(val, align_size):
  if 0 == (val & (align_size - 1)):
    return True
  else:
    return False

def is_valid_mapping(mapping):
  min_mapping_size = mapping_sizes[-1]

  if mapping['vaddr'] > TZ_VAS_LAST_ADDRESS or mapping['paddr'] > TZ_VAS_LAST_ADDRESS or (mapping['vaddr'] + KB2B(mapping['sz_in_kb'])) > (1 + TZ_VAS_LAST_ADDRESS) or (mapping['paddr'] + KB2B(mapping['sz_in_kb'])) > (1 + TZ_VAS_LAST_ADDRESS):
    return False

  # All parameters must be aligned to the minimum page size
  if (not is_aligned(mapping['vaddr'], min_mapping_size)) or (not is_aligned(mapping['paddr'], min_mapping_size)) or (not is_aligned(KB2B(mapping['sz_in_kb']), min_mapping_size)):
    return False

  return True

#def all_mapping_fields_are_aligned(mapping, align_size):
#  if is_aligned(mapping['vaddr'], align_size) and is_aligned(mapping['vaddr'], align_size) and is_aligned(mapping['vaddr'], align_size):
#    return True
#  else:
#    return False

def are_flags_same(flags1, flags2):
  flags1.sort()
  flags2.sort()
  return (flags1 == flags2)

def alloc_ptable(level, address=0):
  ptable = []
  ptable_len = 0
  if 0 == level:
    ptable_len = TZ_VAS_SIZE / mapping_sizes[level]
  else:
    ptable_len = mapping_sizes[level - 1] / mapping_sizes[level]

  for k in range(ptable_len):
    ptable.append({'type' : 'invalid', 'flags' : [], 'paddr' : address})
    address += mapping_sizes[level]

  global ptables
  ptables[level].append(ptable)
  return ptable

def mmu_map_helper(pt, level, vaddr, paddr, size, flags):
  if DEBUG: print "mmu_map_helper", level, hex(vaddr), hex(size)
  ret = True

  pt_entry = pt[vaddr / mapping_sizes[level]]
  if 'invalid' == pt_entry['type'] and 'TZ_TTE_INVALID' in flags:
    pass
  elif 'block' == pt_entry['type'] and are_flags_same(pt_entry['flags'], flags) and ((vaddr & ~mapping_sizes[level]) | pt_entry['paddr']) == paddr:
    pass
  else:
    if 'table' != pt_entry['type']:
      pt_entry['table'] = alloc_ptable(level + 1, pt_entry['paddr'])
      for entry in pt_entry['table']:
        entry['type'] = pt_entry['type']
        entry['flags'] = pt_entry['flags']
      pt_entry['type'] = 'table'
      pt_entry['flags'] = ''
    ret = mmu_map(pt_entry['table'], level + 1, vaddr & (mapping_sizes[level] - 1), paddr, size, flags)

  return ret

def mmu_map(pt, level, vaddr, paddr, size, flags):
  if DEBUG: print "mmu_map", level, hex(vaddr), hex(size)
  ret = True
  end_vaddr = vaddr + size
  next_level_mappings = []

  if is_aligned(vaddr, mapping_sizes[level]) and is_aligned(paddr, mapping_sizes[level]) and is_aligned(size, mapping_sizes[level]):
    pass
  else:
    if (vaddr / mapping_sizes[level]) != (end_vaddr / mapping_sizes[level]):
      pre_size = 0
      if not is_aligned(vaddr, mapping_sizes[level]):
        pre_size = mapping_sizes[level] - (vaddr & (mapping_sizes[level] - 1))
        next_level_mappings.append({'vaddr': vaddr, 'paddr': paddr, 'size': pre_size})

      post_size = 0
      if not is_aligned(end_vaddr, mapping_sizes[level]):
        post_size = end_vaddr & (mapping_sizes[level] - 1)
        next_level_mappings.append({'vaddr': end_vaddr - post_size, 'paddr': paddr + size - post_size, 'size': post_size})

      vaddr += pre_size
      paddr += pre_size
      size = size - (pre_size + post_size)
    else:
      next_level_mappings.append({'vaddr': vaddr, 'paddr': paddr, 'size': size})
      size = 0

  for m in next_level_mappings:
    ret = mmu_map_helper(pt, level, m['vaddr'], m['paddr'], m['size'], flags)
    if False == ret:
      return ret;

  while size > 0:
    if DEBUG: print hex(vaddr), level
    pt_entry = pt[vaddr / mapping_sizes[level]]
    if 'TZ_TTE_INVALID' in flags:
      pt_entry['type'] = 'invalid'
    else:
      pt_entry['type'] = 'block'
      pt_entry['paddr'] = paddr
      pt_entry['flags'] = flags

    vaddr += mapping_sizes[level]
    paddr += mapping_sizes[level]
    size  -= mapping_sizes[level]

  return ret

def print_pt_walk(pt, level):
  indent = " " * (level * 4)
  for entry in pt:
    entry_str = "%s[%s] %08X" % (indent, entry['type'], entry['paddr'])
    if 'block' == entry['type']:
      entry_str += " {%s}" % entry['flags']
    elif 'table' == entry['type']:
      entry_str += " %d" % (level + 1)

    print entry_str

    if 'table' == entry['type']:
      print_pt_walk(entry['table'], 1 + level)

def flags_to_armv8_blk_attrib(orig_flags, level):
  # make a copy so as not to disturb the original
  flags = [f for f in orig_flags]
  flags.append('BLK_G')
  flags.append('BLK_AF')
  if len(mapping_sizes) - 1 == level:
    flags.append('LAST_LVL_BLK_DESC')
  else:
    flags.append('NON_LAST_LVL_BLK_DESC')

  flags_dict = {
    # [54] Execute Never (XN)
    'TZ_NON_EXECUTABLE'       : (1 << 54),
    'TZ_EXECUTABLE'           : (0 << 54),

    # [53] Privledged Execute Never (PXN)
    'TZ_PL1_NON_EXECUTABLE'   : (1 << 53),
    'TZ_PL1_EXECUTABLE'       : (0 << 53),

    # [52] Contiguous Hint
    'BLK_CONTIGUOUS_HINT'     : (1 << 52),

    # [51:40] UNK/SBZP
    # [39:30] Physical Address
    # [29:12] UNK/SBZP

    # [11] Non Global (nG)
    'BLK_NG'                  : (1 << 11),
    'BLK_G'                   : (0 << 11),

    # [10] Access Flag (AF)
    'BLK_AF'                  : (1 << 10),

    # [9:8] Shareability Field (SH)
    'TZ_NON_SHAREABLE'        : (0 << 8),
    'TZ_OUT_SHAREABLE'        : (2 << 8),
    'TZ_INR_SHAREABLE'        : (3 << 8),

    # [7:6] Access Permissions (AP)
    'TZ_READ_WRITE_PL1'       : (0 << 6),
    'TZ_READ_WRITE_PL0'       : (1 << 6),
    'TZ_READ_ONLY_PL1'        : (2 << 6),
    'TZ_READ_ONLY_PL0'        : (3 << 6),

    # [5] Non Secure (NS)
    'TZ_NON_SECURE'           : (1 << 5),
    'TZ_SECURE'               : (0 << 5),

    # [4:2] Memory Attributes Index (AttrIndx)
    'TZ_MEM_STRONGLY_ORDERED' : (0 << 2),
    'TZ_MEM_DEVICE'           : (1 << 2),
    'TZ_MEM_NON_CACHEABLE'    : (2 << 2),
    'TZ_MEM_WRITE_THROUGH_WA' : (3 << 2),
    'TZ_MEM_WRITE_THROUGH_NWA': (4 << 2),
    'TZ_MEM_WRITE_BACK_WA'    : (5 << 2),
    'TZ_MEM_WRITE_BACK_NWA'   : (6 << 2),
    'TZ_MEM_NOT_USED'         : (7 << 2),

    # [1:0] Descriptor Type
    'NON_LAST_LVL_BLK_DESC'   : 1,
    'LAST_LVL_BLK_DESC'       : 3,
  }

  val = 0
  for f in flags:
    val |= flags_dict[f]
  return val

def generate_ptables_armv8_long_desc(pt, level, base_addresses, data):
  indent = " " * (level * 4)
  paddr_mask = ((1 << 40) - 1) ^ ((1 << 12) - 1)
  #entry_type_val = {'invalid': 0, 'block': 1, 'table': 3}

  for entry in pt:
    entry_val = 0
    addr = entry['paddr']

    entry_str = "%s[%s] %08X" % (indent, entry['type'], entry['paddr'])

    if 'block' == entry['type']:
      entry_str += " {%s}" % entry['flags']
      entry_val |= flags_to_armv8_blk_attrib(entry['flags'], level)
    elif 'table' == entry['type']:
      entry_str += " %d" % (level + 1)
      entry_val |= 3
      addr = base_addresses[level + 1]
      base_addresses[level + 1] += (len(entry['table']) * 8)
    elif 'invalid' == entry['type']:
      entry_val |= 0

    entry_val |= (addr & paddr_mask)
    data[level] += (struct.pack('<Q', entry_val))
    if DEBUG: print "%s 0x%016X" % (entry_str, entry_val)

    if 'table' == entry['type']:
      generate_ptables_armv8_long_desc(entry['table'], 1 + level, base_addresses, data)

def mmu_map_wrapper(pt, mapping):

  if not is_valid_mapping(mapping):
    print "Invalid mapping: ", mapping
    return False

  if DEBUG: print "mapping ", mapping
  return mmu_map(pt, 0, mapping['vaddr'], mapping['paddr'], KB2B(mapping['sz_in_kb']), mapping['flags'])

############################################################################

# ELF Definitions
ELF_HDR_COMMON_SIZE       = 24
ELF32_HDR_SIZE            = 52
ELF32_PHDR_SIZE           = 32
ELF64_HDR_SIZE            = 64
ELF64_PHDR_SIZE           = 56
ELFINFO_MAG0_INDEX        = 0
ELFINFO_MAG1_INDEX        = 1
ELFINFO_MAG2_INDEX        = 2
ELFINFO_MAG3_INDEX        = 3
ELFINFO_MAG0              = '\x7f'
ELFINFO_MAG1              = 'E'
ELFINFO_MAG2              = 'L'
ELFINFO_MAG3              = 'F'
ELFINFO_CLASS_INDEX       = 4
ELFINFO_CLASS_32          = 1 
ELFINFO_CLASS_64          = 2
ELFINFO_VERSION_INDEX     = 6
ELFINFO_VERSION_CURRENT   = '\x01'
ELF_BLOCK_ALIGN           = 0x1000

PT_NULL    = 0          # NULL Segment
PT_LOAD    = 1          # Load Segment
PT_DYNAMIC = 2          # Dynamic Segment

PF_X	= 0x1	# Execute
PF_W	= 0x2	# Write
PF_R	= 0x4	# Read

# Mask for bits 20-27 to parse program header p_flags
MI_PBT_FLAGS_MASK = 0x0FF00000

# Helper defines to help parse ELF program headers
MI_PBT_FLAG_SEGMENT_TYPE_MASK         = 0x07000000
MI_PBT_FLAG_SEGMENT_TYPE_SHIFT        = 0x18
MI_PBT_FLAG_PAGE_MODE_MASK            = 0x00100000
MI_PBT_FLAG_PAGE_MODE_SHIFT           = 0x14
MI_PBT_FLAG_ACCESS_TYPE_MASK          = 0x00E00000
MI_PBT_FLAG_ACCESS_TYPE_SHIFT         = 0x15
MI_PBT_FLAG_POOL_INDEX_MASK           = 0x08000000
MI_PBT_FLAG_POOL_INDEX_SHIFT          = 0x1B
MI_PBT_FLAG_PERMISSIONS_MASK          = 0x7
MI_PBT_FLAG_PERMISSIONS_SHIFT         = 0x0

# Segment Type
MI_PBT_HASH_SEGMENT                   = 0x2

# Page/Non-Page Type
MI_PBT_NON_PAGED_SEGMENT              = 0x0
MI_PBT_PAGED_SEGMENT                  = 0x1

# Access Type
MI_PBT_RW_SEGMENT                     = 0x0
MI_PBT_RO_SEGMENT                     = 0x1
MI_PBT_ZI_SEGMENT                     = 0x2
MI_PBT_NOTUSED_SEGMENT                = 0x3
MI_PBT_SHARED_SEGMENT                 = 0x4


#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf_Ehdr_common:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHI')

   def __init__(self, data):
      unpacked_data       = (Elf_Ehdr_common.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf32_Ehdr:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHIIIIIHHHHHH')

   def __init__(self, data):
      unpacked_data       = (Elf32_Ehdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]
      self.e_entry        = unpacked_data[4]
      self.e_phoff        = unpacked_data[5]
      self.e_shoff        = unpacked_data[6]
      self.e_flags        = unpacked_data[7]
      self.e_ehsize       = unpacked_data[8]
      self.e_phentsize    = unpacked_data[9]
      self.e_phnum        = unpacked_data[10]
      self.e_shentsize    = unpacked_data[11]
      self.e_shnum        = unpacked_data[12]
      self.e_shstrndx     = unpacked_data[13]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                self.e_shoff,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx
               ]

      return (Elf32_Ehdr.s).pack(*values)

#----------------------------------------------------------------------------
# ELF Program Header Class
#----------------------------------------------------------------------------
class Elf32_Phdr:

   # Structure object to align and package the ELF Program Header
   s = struct.Struct('I' * 8)

   def __init__(self, data):
      unpacked_data       = (Elf32_Phdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.p_type         = unpacked_data[0]
      self.p_offset       = unpacked_data[1]
      self.p_vaddr        = unpacked_data[2]
      self.p_paddr        = unpacked_data[3]
      self.p_filesz       = unpacked_data[4]
      self.p_memsz        = unpacked_data[5]
      self.p_flags        = unpacked_data[6]
      self.p_align        = unpacked_data[7]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.p_type,
                self.p_offset,
                self.p_vaddr,
                self.p_paddr,
                self.p_filesz,
                self.p_memsz,
                self.p_flags,
                self.p_align
               ]

      return (Elf32_Phdr.s).pack(*values)

#----------------------------------------------------------------------------
# ELF Header Class
#----------------------------------------------------------------------------
class Elf64_Ehdr:
   # Structure object to align and package the ELF Header
   s = struct.Struct('16sHHIQQQIHHHHHH')

   def __init__(self, data):
      unpacked_data       = (Elf64_Ehdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.e_ident        = unpacked_data[0]
      self.e_type         = unpacked_data[1]
      self.e_machine      = unpacked_data[2]
      self.e_version      = unpacked_data[3]
      self.e_entry        = unpacked_data[4]
      self.e_phoff        = unpacked_data[5]
      self.e_shoff        = unpacked_data[6]
      self.e_flags        = unpacked_data[7]
      self.e_ehsize       = unpacked_data[8]
      self.e_phentsize    = unpacked_data[9]
      self.e_phnum        = unpacked_data[10]
      self.e_shentsize    = unpacked_data[11]
      self.e_shnum        = unpacked_data[12]
      self.e_shstrndx     = unpacked_data[13]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.e_ident,
                self.e_type,
                self.e_machine,
                self.e_version,
                self.e_entry,
                self.e_phoff,
                self.e_shoff,
                self.e_flags,
                self.e_ehsize,
                self.e_phentsize,
                self.e_phnum,
                self.e_shentsize,
                self.e_shnum,
                self.e_shstrndx
               ]

      return (Elf64_Ehdr.s).pack(*values)

#----------------------------------------------------------------------------
# ELF Program Header Class
#----------------------------------------------------------------------------
class Elf64_Phdr:

   # Structure object to align and package the ELF Program Header
   s = struct.Struct('IIQQQQQQ')

   def __init__(self, data):
      unpacked_data       = (Elf64_Phdr.s).unpack(data)
      self.unpacked_data  = unpacked_data
      self.p_type         = unpacked_data[0]
      self.p_flags        = unpacked_data[1]
      self.p_offset       = unpacked_data[2]
      self.p_vaddr        = unpacked_data[3]
      self.p_paddr        = unpacked_data[4]
      self.p_filesz       = unpacked_data[5]
      self.p_memsz        = unpacked_data[6]
      self.p_align        = unpacked_data[7]

   def printValues(self):
      print "ATTRIBUTE / VALUE"
      for attr, value in self.__dict__.iteritems():
         print attr, value

   def getPackedData(self):
      values = [self.p_type,
                self.p_flags,
                self.p_offset,
                self.p_vaddr,
                self.p_paddr,
                self.p_filesz,
                self.p_memsz,
                self.p_align
               ]

      return (Elf64_Phdr.s).pack(*values)

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('elf_mapping_builder')

def generate(env):
   elf_mapping_generate(env)

def elf_mapping_generate(env):
  bld = env.Builder(action = env.GetBuilderAction(elf_mapping_builder),
                    suffix = '.elf')
  env.Append(BUILDERS = {'ElfMappingBuilder' : bld})

def getSymbolList(nmbin, elf_file):
  import subprocess
  symbol_list = []
  p = subprocess.Popen([nmbin, '-S', elf_file],
                       stdout=subprocess.PIPE, 
                       stderr=subprocess.PIPE)
  out, err = p.communicate()

  if 0 == len(err):
    symbol_list = [x.strip().split(' ') for x in out.split('\n')]
    symbol_list.sort()

  return symbol_list

def getSymbolAddress(symbols, symbol_list):
  symbol_info = [{} for x in symbols]
  for i in range(len(symbol_list)):
    if 4 != len(symbol_list[i]):
      continue
    for j in range(len(symbols)):
      s = symbols[j]
      if symbol_list[i][3] == s:
        symbol_info[j]['address'] = int(symbol_list[i][0], 16)
        symbol_info[j]['size'] = int(symbol_list[i][1], 16)
  return symbol_info

def MI_PBT_SEGMENT_PERMISSIONS_VALUE(x):
    return ( ((x) & MI_PBT_FLAG_PERMISSIONS_MASK) >> MI_PBT_FLAG_PERMISSIONS_SHIFT )

def MI_PBT_SEGMENT_TYPE_VALUE(x):
    return ( ((x) & MI_PBT_FLAG_SEGMENT_TYPE_MASK) >> MI_PBT_FLAG_SEGMENT_TYPE_SHIFT )

def MI_PBT_PAGE_MODE_VALUE(x):
    return ( ((x) & MI_PBT_FLAG_PAGE_MODE_MASK) >> MI_PBT_FLAG_PAGE_MODE_SHIFT )

def MI_PBT_ACCESS_TYPE_VALUE(x):
    return ( ((x) & MI_PBT_FLAG_ACCESS_TYPE_MASK) >> MI_PBT_FLAG_ACCESS_TYPE_SHIFT )

def MI_PBT_CHECK_FLAG_TYPE(x):
    return (MI_PBT_SEGMENT_TYPE_VALUE(x) != MI_PBT_HASH_SEGMENT) and \
           (MI_PBT_ACCESS_TYPE_VALUE(x) != MI_PBT_NOTUSED_SEGMENT) and \
           (MI_PBT_ACCESS_TYPE_VALUE(x) != MI_PBT_SHARED_SEGMENT)

def is_valid_segment(phdr_entry):
  if phdr_entry.p_type == PT_LOAD and MI_PBT_PAGE_MODE_VALUE(phdr_entry.p_flags) == MI_PBT_NON_PAGED_SEGMENT and MI_PBT_SEGMENT_TYPE_VALUE(phdr_entry.p_flags) != MI_PBT_HASH_SEGMENT and MI_PBT_ACCESS_TYPE_VALUE(phdr_entry.p_flags) != MI_PBT_NOTUSED_SEGMENT and MI_PBT_ACCESS_TYPE_VALUE(phdr_entry.p_flags) != MI_PBT_SHARED_SEGMENT:
    return True
  else:
    return False

def round_up(value, size):
  return (value + (size - 1)) & (~(size - 1))

def xml_text_to_list(val):
  return [x.strip() for x in val.split('\n') if len(x.strip()) > 0]

def get_pt_symbols_for_image(target_string):
  img_name = os.path.basename(target_string)
  if img_name.startswith('mon'):
    return ['mon_l1', 'mon_l2', 'mon_l3']
  elif img_name.startswith('qsee'):
    return ['qsee_l1', 'qsee_l2', 'qsee_l3']

def get_segment_permissions(target_string):
  img_name = os.path.basename(target_string)

  # Note that a segment with read-write-execute permissions should not really
  # be granted all 3 permissions, since that would violate the principle of
  # Data Execution Prevention
  if img_name.startswith('mon'):
    return {'common'       : ['TZ_INR_SHAREABLE', 'TZ_MEM_WRITE_BACK_WA'],
            'read_only'    : ['TZ_READ_ONLY_PL1', 'TZ_NON_EXECUTABLE'],
            'read_execute' : ['TZ_READ_ONLY_PL1', 'TZ_EXECUTABLE'],
            'read_write'   : ['TZ_READ_WRITE_PL1', 'TZ_NON_EXECUTABLE'],
            'read_write_execute' : ['TZ_READ_ONLY_PL1', 'TZ_EXECUTABLE']}
  elif img_name.startswith('qsee'):
    return {'common'       : ['TZ_INR_SHAREABLE', 'TZ_MEM_WRITE_BACK_WA'],
            'read_only'    : ['TZ_READ_ONLY_PL1', 'TZ_NON_EXECUTABLE', 'TZ_PL1_NON_EXECUTABLE'],
            'read_execute' : ['TZ_READ_ONLY_PL1', 'TZ_PL1_EXECUTABLE', 'TZ_NON_EXECUTABLE'],
            'read_write'   : ['TZ_READ_WRITE_PL1', 'TZ_NON_EXECUTABLE', 'TZ_PL1_NON_EXECUTABLE'],
            'read_write_execute' : ['TZ_PL1_EXECUTABLE', 'TZ_READ_ONLY_PL1', 'TZ_NON_EXECUTABLE']}

def get_builds_file_value(env, val_name, symbol_list):
  # Check if the value is a hexadecimal constant (currently integer (base 10)
  # constants are not supported!
  if val_name.lower().startswith("0x"):
    return int(val_name, 16)

  # Check if the value is present in the GLOBAL_DICT
  if val_name in env['GLOBAL_DICT']:
    val = str(env['GLOBAL_DICT'][val_name]).lower()
    if val.startswith("0x"):
      return int(val, 16)
    else:
      return int(val, 10)
  else:
    for i in range(len(symbol_list)):
      if symbol_list[i][-1] == val_name:
        return int(symbol_list[i][0], 16)
    return None

def elf_mapping_builder (target, source, env):
  source_elf_str = os.path.abspath(str(source[0]))
  source_xml_str = os.path.abspath(str(source[1]))
  target_str = os.path.abspath(str(target[0]))

  elf_file_name = source_elf_str

  import xml.etree.ElementTree as ET
  tree = ET.parse(source_xml_str)
  xml_root = tree.getroot()

  """
  Get the names of the symbols that will hold the page-tables
  This information can be extracted from the XML as shown here:
    pt_symbols = xml_text_to_list(xml_root.find('pt_symbols').text)

  but for now, let's just hardcode it in the script
  """
  pt_symbols = get_pt_symbols_for_image(target_str)
  symbol_list = getSymbolList(env.subst(env['NMBIN']), elf_file_name)
  symbol_info = getSymbolAddress(pt_symbols, symbol_list)

  """
  Get the permissions flags for the different types of segments. This info
  can be extracted from the XML too, as shown here:
    segment_root = xml_root.find('segment_permissions')
    flags = xml_text_to_list(segment_root.find('common').text)
  """
  segment_permissions = get_segment_permissions(target_str)

  # TODO: Check that addresses were found for all the symbols
  # Also, what's a good way to signal that a builder has failed?
  symbol_seek_offsets = [0 for x in pt_symbols]

  mappings = []

  # Static mappings
  for m in xml_root.findall('mapping'):
    temp = {
      'vaddr' : get_builds_file_value(env, m.attrib['vaddr'], symbol_list),
      'paddr' : get_builds_file_value(env, m.attrib['paddr'], symbol_list),
      'flags' : m.attrib['flags'].split(',')}
    if 'bytes' in m.attrib:
      temp['sz_in_kb'] = B2KB(round_up(get_builds_file_value(env, m.attrib['bytes'], symbol_list), PAGE_SIZE))
    else:
      temp['sz_in_kb'] = B2KB(round_up(get_builds_file_value(env, m.attrib['end_vaddr'], symbol_list) - temp['vaddr'], PAGE_SIZE))
    mappings.append(temp)

  # Open the ELF file (for reading), and read the list of segments
  elf_fp = open (elf_file_name, 'rb')
  elf_header_common = Elf_Ehdr_common(elf_fp.read (ELF_HDR_COMMON_SIZE))
  elf_fp.seek(0)
  elf_header = None
  if ELFINFO_CLASS_32 == elf_header_common.e_type:
    elf_header = Elf32_Ehdr(elf_fp.read(ELF32_HDR_SIZE))
  else:
    elf_header = Elf64_Ehdr(elf_fp.read(ELF64_HDR_SIZE))

  # Seek to the program header offset
  elf_fp.seek(elf_header.e_phoff)

  # Read in the program headers
  for i in range(elf_header.e_phnum):
    phdr_entry = None
    if ELFINFO_CLASS_32 == elf_header_common.e_type:
      phdr_entry = Elf32_Phdr(elf_fp.read(elf_header.e_phentsize))
    elif ELFINFO_CLASS_64 == elf_header_common.e_type:
      phdr_entry = Elf64_Phdr(elf_fp.read(elf_header.e_phentsize))
    if is_valid_segment(phdr_entry) and phdr_entry.p_memsz > 0:
      # Search for each of the symbols where the page table data needs to be
      # stored
      for i in range(len(pt_symbols)):
        addr = symbol_info[i]['address']
        if addr >= phdr_entry.p_vaddr and addr < (phdr_entry.p_vaddr + phdr_entry.p_memsz):
          symbol_seek_offsets[i] = (addr - phdr_entry.p_vaddr) + phdr_entry.p_offset;

      perms = MI_PBT_SEGMENT_PERMISSIONS_VALUE(phdr_entry.p_flags)
      """
      Note that we need to make a copy of the permissions list here because
      we will be modifying/extending it later, and without making a copy that
      would end up modifying the original list!
      """
      flags = copy.copy(segment_permissions['common'])
      if (PF_R) == perms:
        flags.extend(segment_permissions['read_only'])
      elif (PF_R | PF_X) == perms:
        flags.extend(segment_permissions['read_execute'])
      elif (PF_R | PF_W) == perms:
        flags.extend(segment_permissions['read_write'])
      elif (PF_R | PF_W | PF_X) == perms:
        flags.extend(segment_permissions['read_write_execute'])
      else:
        # TODO: Bail out here?
        pass
      mappings.append({
        'vaddr' : phdr_entry.p_vaddr,
        'paddr' : phdr_entry.p_paddr,
        'sz_in_kb' : B2KB(round_up(phdr_entry.p_memsz, PAGE_SIZE)),
        'flags': flags})

  elf_fp.close()

  # We need to sort in ascending order of vaddr, breaking ties in descending
  # order of size, breaking ties placing NON-CACHEABLE entries later
  # For now, instead of creating a comparator function, sorting based on the
  # last criterion onwards
  mappings.sort(key = lambda x: 'TZ_MEM_NON_CACHEABLE' in x['flags'])
  mappings.sort(key = lambda x: x['sz_in_kb'], reverse=True)
  mappings.sort(key = lambda x: x['vaddr'])

  pt = alloc_ptable(0, 0)
  for m in mappings:
    #print "mapping:", hex(m['vaddr']), hex(m['vaddr'] + KB2B(m['sz_in_kb'])), m['flags']
    mmu_map_wrapper(pt, m)
  pt_data = ['' for x in mapping_sizes]

  generate_ptables_armv8_long_desc(pt, 0,  [x['address'] for x in symbol_info], pt_data)

  # Make a copy of the original ELF
  shutil.copyfile(source_elf_str, target_str)

  #import pdb; pdb.set_trace()

  # Write the page table data
  elf_file_name = target_str
  elf_fp = open (elf_file_name, 'r+b')
  for i in range(len(pt_data)):
    elf_fp.seek(symbol_seek_offsets[i])
    # TODO: Add a check that the page-table data should not exceed the space
    # allocated for it in the image symbol
    diff = symbol_info[i]['size'] - len(pt_data[i])
    if diff > 0:
      pt_data[i] += ((diff / len(EMPTY_PT_MARKER)) * EMPTY_PT_MARKER)
    elf_fp.write(pt_data[i])
  elf_fp.close()

  return None

