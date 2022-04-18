#===========================================================================

#  Parse the sbl logs from the input file DDRCS0.bin

# REFERENCES

#  $Header: //components/rel/boot.xf/1.4/QcomPkg/Tools/sbl_log_parser.py#1 $
#  $DateTime: 2016/12/15 06:53:55 $ 
#  $Author: pwbldsvc $

# when          who     what, where, why 
# --------      ---     ------------------------------------------------------- 
# 09/01/16      lm      First Release

# Copyright (c) 2016
# Qualcomm Technologies Incorporated.
# All Rights Reserved.
# Qualcomm Confidential and Proprietary
# ===========================================================================*/

import sys

path= sys.argv[1]

#This is the string to hold parsed logs
parsed_sbl_log = ""
start_marker = "Format: Log Type - Time(microsec)" 
end_marker = "SBL1, End"
start_marker_found = 0
byte_count = 0

#Open a file with readbinary format and store the file content in "fo"
with open(path, "rb") as input_file:

# Searching the patern line by line in "input file" 
# once found the start marker, incrase the byte_count and search for the end marker.
# Once end marker also found, store the logs and again look for the start & end marker
# if end marker is not found within 4KB data then store the 4KB logs and again
# look for the start & end marker till the end of the file.
	for line in input_file:		
		if start_marker in line:
			start_marker_found = 1
		if start_marker_found == 1:
			byte_count = byte_count + len(line)
			if end_marker in line:
				byte_count = 0
				start_marker_found = 0
				parsed_sbl_log = parsed_sbl_log + line +"\n" + "\n" + "\n" + "\n"				
			elif byte_count <= 4096:		
				parsed_sbl_log = parsed_sbl_log + line
			else: 
				byte_count = 0
				start_marker_found = 0
				parsed_sbl_log = parsed_sbl_log + "\n" + "\n" + "\n" + "\n"
			
print parsed_sbl_log

#f1= open("SBL_parser.txt","w")
#f1.write(parsed_sbl_log)	
input_file.close()
#f1.close()	
