#  ===========================================================================
#
#  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================

import struct

'''
Notes:
  - Does not handle overlapping memory sections
  - Does not handle read requests that cross sections
'''
class DDRMemory(object):
  def __init__(self):
    self._ddr_data = {}
  
  def add_ddr(self, path, base, size):
    self._ddr_data[base] =  {
                              'file' : open(path, 'rb'),
                              'base' : base,
                              'size' : size,
                            }
  
  def read(self, addr, size):
    offset = 0
    output = ''
    while offset < size:
      l_addr = addr+offset
      for base in self._ddr_data:
        data = self._ddr_data[base]
        if l_addr >= data['base'] and l_addr < (data['base']+data['size']):
          #assert( (addr+size) < (data['base']+data['size']) )
          data['file'].seek(l_addr-data['base'])
          output += data['file'].read(1)
      offset += 1
    return output
  
  def read_4_bytes(self, addr):
    return struct.unpack('<I',self.read(addr, 0x4))[0]
  
  def read_8_bytes(self, addr):
    return struct.unpack('<Q',self.read(addr, 0x8))[0]
  
  def close_all(self):
    for base in self._ddr_data:
      data = self._ddr_data[base]
      data['file'].close()
      
      
class DumpTable(object):
  def __init__(self, config, base_addr, ddr):
    self._error = ''
    self._ddr = ddr
    self._base_addr = base_addr
    self._version = config['version']
    #self._config = config
    self._data_struct =   {
                            'size'        : config['data']['size'],
                            'version'     : config['data']['version'],
                            'magic'       : config['data']['magic'],
                            'magic_value' : config['data']['magic_value'],
                            'name'        : config['data']['name'],
                            'name_size'   : config['data']['name_size'],
                            'addr'        : config['data']['addr'],
                            'len'         : config['data']['len'],
                            'reserved'    : config['data']['reserved'],
                          }
    self._entry_struct =  {
                            'size'        : config['entry']['size'],
                            'id'          : config['entry']['id'],
                            'name'        : config['entry']['name'],
                            'name_size'   : config['entry']['name_size'],
                            'type'        : config['entry']['type'],
                            'addr'        : config['entry']['addr'],
                          }
    self._table_struct =  {
                            'size'        : config['table']['size'],
                            'version'     : config['table']['version'],
                            'num_entries' : config['table']['num_entries'],
                            'entries'     : config['table']['entries'],
                          }
    # Validate that dumptable is the correct version
    ver = ddr.read_4_bytes(self._base_addr+self._table_struct['version'])
    if ver != self._version:
      self._error = "Incorrect table version (found {0}, expected {1})".format(hex(ver), hex(self._version))
  
  def get_error(self):
    return self._error
  
  def find_dump_entry(self, id):
    num_entries = [self._ddr.read_4_bytes(self._base_addr+self._table_struct['num_entries'])]
    count = [0]
    ptr = [self._base_addr+self._table_struct['entries']]
    entry_found = 0
    level = 0
    while not entry_found:
      if count[level] < num_entries[level]:
        # Explore current level
        local_id = self._ddr.read_4_bytes(ptr[level]+self._entry_struct['id'])
        local_type = self._ddr.read_4_bytes(ptr[level]+self._entry_struct['type'])
        local_addr = self._ddr.read_8_bytes(ptr[level]+self._entry_struct['addr'])
        if local_type == 0x0 and local_id == id:
          # type 0 entries point to final data
          return ptr[level]
        elif local_type == 0x1:
          # type 1 entries point to other table
          level = level+1
          num_entries += [self._ddr.read_4_bytes(local_addr+self._table_struct['num_entries'])]
          ptr += [local_addr+self._table_struct['entries']]
          count += [0]
        else:
          count[level] += 1
          ptr[level] += self._entry_struct['size']
      elif level == 0:
        # We ran out of entries without finding anything, return 0x0 as error
        self._error = "Entry not found"
        return 0x0
      else:
        # Move back up the stack
        count.pop(level)
        ptr.pop(level)
        num_entries.pop(level)
        level -= 1
        count[level] += 1
    # END find_dump_entry
    
  def read_entry_data(self, addr):
    # will return [name, data, len]
    local_addr_ptr = self._ddr.read_8_bytes(addr+self._entry_struct['addr'])
    local_addr = self._ddr.read_8_bytes(local_addr_ptr+self._data_struct['addr'])
    local_len  = self._ddr.read_8_bytes(local_addr_ptr+self._data_struct['len'])
    local_name = self._ddr.read(local_addr_ptr+self._data_struct['name'], self._data_struct['name_size'])
    local_data = self._ddr.read(local_addr, local_len)
    return [local_name, local_addr, local_len, local_data]
        
    
