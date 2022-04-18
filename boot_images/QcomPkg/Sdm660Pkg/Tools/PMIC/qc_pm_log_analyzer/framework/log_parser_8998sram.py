#!/usr/bin/python
# ===== Py 2/3 Compatibility Layer =====
from __future__ import absolute_import, division, print_function
from future.builtins import (ascii, bytes, chr, dict, filter, hex, input,
                             int, map, next, oct, open, pow, range, round,
                             str, super, zip)
from future.builtins.disabled import *
# ======================================
import os
import re
import array
import clr
import sys

sys.path.append(os.getcwd() + '\sram_log_analyzer\encoding_dll')
clr.AddReference('FGEncoding8998')
import System
from System import Array
from FGEncoding8998.ViLibPMx8998 import FG_Encoding_Parsing_Globals
from FGEncoding8998 import clsParser


class LogParser_8998Sram:
    """
    Parser for 8998 SRAM dumps.
    """
    def __init__(self, reg_enc_map_path, dump_path):
        """
        Constructor.

        :param reg_enc_map_path: path string to the Register Encoding Map CSV
        :param dump_path: path string to the SRAM dump file
        """
        self.reg_enc_map_path = reg_enc_map_path
        self.dump_path = dump_path
        self.byte_array_list = []
        self.addr_regex = re.compile(r'[0-9]{3}(?=[\s]+(\w\w\s*){3}(\w\w)\b)')
        self.data_regex = re.compile(r'(?<=[0-9]{3})\s*(\w\w\s*){3}(\w\w)\b')
        # Do not include 'FG' in the regular expression (search string) because some customer 
        #    SRAM dumps do not include it.
        self.timestamp_regex = re.compile(r'(?<=SRAM\sDump\sdone\sat\s)[0-9]+(\.[0-9]+)?')

    def _get_dict(self, byte_arr):
        """
        Call the functions in FGEncoding8998 DLL to get the register_name-value dictionary

        :param byte_arr: formatted SRAM dump, Int32 array with 1 byte per element
        :return: register_name-value dictionary
        """
        head, tail = os.path.split(os.path.abspath(self.reg_enc_map_path))
        FG_Encoding_Parsing_Globals.InitFGEncoding(head, tail)
        reg_dict = FG_Encoding_Parsing_Globals.objParser.GetParsedData(byte_arr)
        return reg_dict

    def _parse_dump(self):
        """
        Parse a contiguous SRAM dump as a list of byte array.

        - Format: [ Int32 array with 1 byte per element, ...]
        """
        dump_array = array.array('I') # create a long type array
        with open(self.dump_path, 'r') as dump_file:
            for i, line in enumerate(dump_file, 1):
                timestamp_match = re.search(self.timestamp_regex, line)
                if timestamp_match is not None:
                    self.byte_array_list.append((i, timestamp_match.group(), Array[System.Int32](dump_array)))
                else:
                    addr_match = re.search(self.addr_regex, line)
                    data_match = re.search(self.data_regex, line)
                    if addr_match is not None and data_match is not None:
                        addr = int(addr_match.group())
                        data = data_match.group().replace(' ', '')
                        # Put place holder
                        if len(dump_array) < addr * 4 + 4:
                            for j in range(addr * 4 + 4 - len(dump_array)):
                                dump_array.append(0)
                        # Insert/replace data
                        dump_array[addr * 4 + 3] = int(data[6:8], 16)
                        dump_array[addr * 4 + 2] = int(data[4:6], 16)
                        dump_array[addr * 4 + 1] = int(data[2:4], 16)
                        dump_array[addr * 4 + 0] = int(data[0:2], 16)

    def to_csv_file(self, path):
        """
        Output the parsed SRAM dump as a CSV file.

        :param path: path to store the parsed CSV file
        """
        self._parse_dump()
        
        # Open CSV output file. TODO: Add try
        with open(path, 'w') as csv_out:
            csv_out.write(u'LINE#,TIMESTAMP,LABEL,PARAMETER,VALUE,UNIT\n')
                
            # For each by array dump (self.byte_array_list)           
            for line_num, timestamp, byte_arr in self.byte_array_list:
                #Used to determine if we are using an internal or external version of the enc file.
                encVersion = None 
                # Decode array                
                reg_dict = self._get_dict(byte_arr)
                
                # Open encoder file. TODO: Add try
                with open(self.reg_enc_map_path, 'r') as reg_enc:                                                         
                    #for each item in the encoder file, get a value and write it to the output CSV.
                    for i, line in enumerate(reg_enc):
                        if i > 0:
                            line_split = line[:-1].split(',')
                            unit = line_split[9] if line_split[9] != 'N/A' else ''
                            reg_name = line_split[0]
                            
                            # TODO: Break into its own function
                            # Check if this internal or external enc file format. Note: Internal file format has '.'
                            firstIndex = reg_name.find('.')
                            
                            if firstIndex != -1:
                                index = reg_name.find('.', firstIndex + 1)
                                
                            if (firstIndex != -1) and (index != -1):
                                encVersion = 'Internal'
                                label = reg_name[:index]
                                param = reg_name[index + 1:]
                            else:
                                encVersion = 'External'
                                label = ''
                                param = reg_name                                
                            
                            #TODO: What if the key is not present?
                            value = reg_dict[reg_name][:-len(unit)] if len(unit) > 0 else reg_dict[reg_name]

                            # Convert "true/false" to "1/0"
                            if value.lower() == 'true' or value.lower() == 't':
                                value = '1'
                            elif value.lower() == 'false' or value.lower() == 'f':
                                value = '0'
                            # Convert Kelvin to Celsius
                            if unit == 'K':
                                value = str(float(value) - 273.15)
                                unit = 'deg C'

                            # Write CSV line
                            csv_out.write(str(line_num) + ',' +
                                          str(timestamp) + ',' +
                                          label + ',' +
                                          param + ',' +
                                          value + ',' +
                                          unit + '\n')
                            
                # Add new item: wk.esr+wk.rSlwBt
                # TODO: Does this code need to be enhanced?
                # TODO: What if the key is not present?
                # Check if this internal or external enc file format. Note: Internal file format has 'RAM.'
                if encVersion == 'Internal':
                    csv_out.write(str(line_num) + ',' +
                                  str(timestamp) + ',' +
                                  'RAM.wk' + ',' +
                                  'esr+rSlwBt' + ',' +
                                  str(float(reg_dict['RAM.wk.esr'][:-len('Ohm')]) + float(reg_dict['RAM.wk.rSlwBt'][:-len('Ohm')])) + ',' +
                                  'Ohm' + '\n')
                elif encVersion == 'External':
                    csv_out.write(str(line_num) + ',' +
                                  str(timestamp) + ',' +
                                  '' + ',' +
                                  'ESR+Rslow' + ',' +
                                  str(float(reg_dict['ESR'][:-len('Ohm')]) + float(reg_dict['Rslow'][:-len('Ohm')])) + ',' +
                                  'Ohm' + '\n')
                else:
                    raise ValueError('Unknown encoder file version')                    
