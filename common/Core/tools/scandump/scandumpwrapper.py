"""===============================================================================
 scandumpwrapper.py

 GENERAL DESCRIPTION
    Scan dump data parser for a given SoC

 Copyright (c) 2016 by QUALCOMM Technologies Incorporated.
 All Rights Reserved.

 QUALCOMM Proprietary

-------------------------------------------------------------------------------

  $Header: //components/rel/core.glue/1.2.1/tools/scandump/scandumpwrapper.py#2 $
  $DateTime: 2017/02/02 08:57:34 $
  $Author: pwbldsvc $
  $Change: 12358241 $
                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

 when       who         what, where, why
 --------   ---         ---------------------------------------------------------
 10/17/2016 AJCheriyan  Fixed issues with Unix
 12/11/2015 AJCheriyan  Created v1.0 for Nazgul
=============================================================================="""



import glob, itertools, os, string, sys, subprocess, re, platform, shutil, fnmatch, time, tempfile
from optparse import OptionParser
from ctypes import *
from helper import *
import binascii
import struct

# Function to parse input options
def parseoptions():
    global options
    argparser = OptionParser(usage = 'scandumpwrapper.py -d <binary>', version='%prog 1.0')
    argparser.add_option('-d', '--data', dest='data', help='scandump data with header info', metavar='bin', default=None)
    argparser.add_option('-o', '--outpfile', dest='ofile', help='output filename prefix', metavar='file', default='registers')
    argparser.add_option('-f', '--mapfmt', dest='mapfmt', help='Output architecture format. aarch64, aarch32, armv8 (both)', default='armv8')

    (options, args) = argparser.parse_args()

    if not options.data:
        kill('Please provide binary data file')

""" @brief : Function to retrieve the binary header data.
    @param datafile : Input scandump file to parser
    @param start_addr: Start of the header data
    @param chunksize: Chunk size for file reads (optional)
    @return Returns a one dimensional array of boolean values represented as strings
"""
def getscandump_header(datafile, start_addr = 0, chunksize = 64):
    fptr = open(datafile, 'rb+')

    if (chunksize%4 !=0):
        kill('Error: Integral number of 32 bit entries expected for chunksize. Provided: ' + str(chunksize))

    fptr.seek(start_addr, 0)
    header = fptr.read(chunksize)
    fptr.close()
    intrep = struct.unpack('<%dL' % int(chunksize/4), header)
    return [hex(intrep[i]).rstrip('L').lstrip('0x').upper().zfill(8) for i in range(0, len(intrep))]

""" @brief : Function to parse the header and determine chipset
    @param header: Extracted header from the binary data
    @return Returns a dictionary equivalent of the header structure with parsed information appended
"""
def parse_header(header):
    header_attrib = {'chipid' : header[0], 'jtagid' : header[1], 'ipinfo' : header[2], 'instances' : header[3] }

    if (header_attrib['chipid'] == '30020100'):
        header_attrib['chip'] = 'msm8998_v1'
    elif (header_attrib['chipid'] == '30020200'):
        header_attrib['chip'] = 'msm8998_v2'
    elif (header_attrib['chipid'] == '30060100'):
        header_attrib['chip'] = 'sdm660_v1'
    elif (header_attrib['chipid'] == '30060101'):
        header_attrib['chip'] = 'sdm660_v1'
    else:
        kill('Error: Coud not find chipset information for chipid ' + header_attrib['chipid'])

    return header_attrib


""" @brief : Function to parse the header and determine chipset
    @param header: Extracted header from the binary data
    @return Returns a dictionary equivalent of the header structure with parsed information appended
"""

def exec_scandumpparser(parsed_header):
    #debug('Header Information : ' + str(parsed_header))
    # MSM8998 specific parsing
    if parsed_header['chip'] in ['msm8998_v1', 'msm8998_v2']:
        debug('Detected MSM8998: ' + parsed_header['chip'], True)
    if parsed_header['chip'] in ['sdm660_v1']:
        debug('Detected SDM660: ' + parsed_header['chip'], True)
    
    if (parsed_header['ipinfo'] in ['00000002', '00000003']):
		for instance in range(0, int(parsed_header['instances'])):
			registerxml = ('_').join(['register', parsed_header['chip']]) + '.xml'
			registerout = ('_').join([options.ofile, 'core%s.cmm' % (instance)])
			logfile = ('_').join([options.ofile, 'core%s.log' % (instance)])
			logfptr = open(logfile, 'w')
			curr_dir = os.path.abspath(__file__).rstrip(os.path.basename(__file__))
			script = '/'.join([curr_dir, 'scandumpparser.py'])
			registerxml = '/'.join([curr_dir, registerxml])
			signalsfile = 'signals'
			cmdline = 'python %s -x %s -m %s -d %s -p %s -o %s -f %s' % (script, registerxml, signalsfile, options.data, instance, registerout, options.mapfmt)
			scandump_proc = subprocess.Popen(cmdline.split(" "), stdout=logfptr, stderr=subprocess.PIPE)
			(output, error) = scandump_proc.communicate()
			logfptr.close()
			if error:
				kill('Encountered error in call ' + cmdline + ' Error: ' + error)
			else:
				debug('Scandump output generated for Core %s.' % (instance))









if __name__ == '__main__':

    # Parse all the options passed in
    parseoptions()

    # Extract the header
    header = getscandump_header(options.data, chunksize = 32)
    parsed_header = parse_header(header)

    # Parse the scandumps
    exec_scandumpparser(parsed_header)







