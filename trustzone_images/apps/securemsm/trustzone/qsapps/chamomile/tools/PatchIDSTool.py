#
# Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
# Simple Python program to patch a 4kb binary IDS contained in a file into an executable file (Chamomile Tool or TA)

import os.path
import sys
import argparse

# Tool and TA must ensure that location in binary file of IDS is preceded by this magic number.
# This simple Python code searches for this string, and replaces the 4kb of data immediately following it
MAGIC_NUMBER = b'\xa5\x5a\xa5\x5a\xa5\x5a\xa5\x5a\x00\x01\x02\x03\x04\x05\x06\x07\xa5\x5a\xa5\x5a\xa5\x5a\xa5\x5a\x00\x01\x02\x03\x04\x05\x06\x07'

MAGIC_NUMBER_LEN = 32

IDS_LEN = 4096

#Hard coded filenames for testing purposes only
#TOOL_FILE = 'KeyObfuscation.exe'
#IDS_FILE = 'keyfile.dat'

parser = argparse.ArgumentParser()

parser.add_argument("ToolFile", help="File name of the Tool or TA executable to be patched")
parser.add_argument("IDSFile", help="File name containing the 4kb IDS")
parser.add_argument("--new", help="Create a new output file. (The original tool file remains untouched)")   

args = parser.parse_args()	# returns data from the options specified (echo)

if args.new:  
    print ("New file will be created:", args.new)
else:
    print ("Existing file will be patched:", args.ToolFile)

# Use this indirection for testing purposes
TOOL_FILE = args.ToolFile
IDS_FILE = args.IDSFile

sourceFile = open(TOOL_FILE, 'rb+')
source_data = sourceFile.read()
replace_data = open(IDS_FILE, 'rb').read()

ToolFileLen = len(source_data)

# Check that IDS is exactly 4kb in length
if (len(replace_data) != IDS_LEN):
    print("IDS Length must be 4k bytes. (Supplied IDS is", len(replace_data), "bytes)")
    quit()
    
#Find the magic number embedded in the Tool/TA File
file_offset = source_data.find(MAGIC_NUMBER)

if (file_offset == -1):
    print("Magic Number not found in file - aborting")
    quit()
    
#print ("Found magic number at Offset:", file_offset)

# Patch the file
file_offset += MAGIC_NUMBER_LEN
outData = source_data[0:file_offset] + replace_data + source_data[file_offset + IDS_LEN:]

OutFileLen = len(outData);

if (ToolFileLen != OutFileLen):
    print("Error: OutputFile has different size ", OutFileLen, " to Input file", ToolFileLen)    
else:
    if args.new:
        outFile = open(args.new, 'wb')
        outFile.write(outData)
        outFile.close
    else:
        sourceFile.seek(0,0);
        sourceFile.write(outData)
        sourceFile.close
    print ("Patch Completed Successfully")

