#! /usr/bin/python

# init version: jbenis
#
# P4: $Author: pwbldsvc $
#     $Change: 11844661 $
#     $DateTime: 2016/11/23 22:06:41 $
#     $Id: //components/rel/core.glue/1.2.1/tools/tools/sve/dragonlink/etb_to_bin.py#1 $

import sys

#################
### functions ###
#################

######################
### parse cmd line ###
######################

import argparse
parser = argparse.ArgumentParser(description="Parse CPUSS HWE data")
parser.add_argument("INPUT_FILE", help="CPUSS HWE data, in JSON/txt format")
parser.add_argument("-c", "--cmm", help="CMM used to capture HWE")

args = parser.parse_args()

input_file  = args.INPUT_FILE
cmm_file    = args.cmm

##################
### open files ###
##################

input_file_object = open(input_file, "r")

#################
### main loop ###
#################

channel      = 0
prev_ts      = 0
count_events = {}

print ""
print "input file:", input_file
print "cmm file:  ", cmm_file
print ""
print "Note 1: ATID ignored"
print "Note 2: Assumes channel 192/193"

if cmm_file:
   cmm_file_object = open(cmm_file, "r")

   print ""
   print "enabled HW Events"
   print "-----------------"

   cmm_parse_active = 0
   enabled          = 0
   current_hwe      = -1
   hwe_list         = []

   for line in cmm_file_object:
      line = line.rstrip("\r\n")

      if "Enter Selections Below" in line:
         cmm_parse_active = 1
      elif "print some info" in line:
         cmm_parse_active = 0
      elif cmm_parse_active:
         if line.startswith("&selmux="):
            current_selmux = line[10]
            #print "current_hwe = ", current_hwe, ", current_selmux = ", current_selmux
         elif line.startswith("&selmsk="):
            current_hwe = current_hwe + 1
            if (line[:11] == "&selmsk=0x1"):
               enabled = 1
            else:
               enabled = 0

         if (line[11:14] == " //") and (not line.startswith("&selmsk=")):
            #temp_line = line[17:]
            #print temp_line
            #data = temp_line.split("   --   ")
            data0 = line[15]
            data1 = line[17:]
            if data0 == current_selmux:
               #print "current_hwe =", current_hwe, ", current_selmux =", current_selmux, "--->",
               #print data[0], "-", data[1]
               hwe_list.append(data1)
               if enabled:
                  print "HWE",
                  print "{0:2}" .format(current_hwe),
                  print "selmux", data0, "-", data1

   cmm_file_object.close()

print ""
print "atid  chan            timestamp   ts delta opcode     payload (Hex) hwe"
print "----  ----            ---------  --------- ------- ---------------- ---"

for line in input_file_object:
   atid      = 0
   opcode    = ""
   payload   = ""
   timestamp = 0

   line = line.rstrip("\r\n")
   line = line.strip("{}")
   line = line.replace("\"", "")

   fields = line.split(",")

   for field in fields:
      field = field.replace(" ", "")
      data = field.split(":")

      if data[0] == "ATID":      atid      = int(data[1], 10)
      if data[0] == "OpCode":    opcode    = data[1]
      if data[0] == "Payload":   payload   = int(data[1], 16)
      if data[0] == "Timestamp": timestamp = int(data[1], 10)

   if (opcode.lower().startswith("c")):
      channel = payload

   if (opcode.lower().startswith("d8")): # d8* implies data is the number of the single HWE
      hwe = payload
      if channel == 193: hwe = hwe + 32 # this channel is the higher bits

      print "{0:4} {1:5} {2:20} {3:10} {4:7} {5:16X} {6:3}" \
      .format(atid, channel, timestamp, (timestamp-prev_ts), opcode, payload, hwe),

      if cmm_file: print " -", hwe_list[hwe]
      else:        print ""

      prev_ts = timestamp
      
      if not count_events.has_key(hwe): count_events.setdefault(hwe, 1)
      else:                             count_events[hwe] = count_events[hwe] + 1
      
   if (opcode.lower().startswith("d32")): # d32* implies data is the bitmask for multiple events
      hwe = []

      payload_64b = payload
      if channel == 193: payload_64b = payload_64b << 32

      for i in range(0, 64):
         payload_shifted = payload_64b >> i
         if (payload_shifted & 0x1):
            hwe.append(i)
            if not count_events.has_key(i): count_events.setdefault(i, 1)
            else:                           count_events[i] = count_events[i] + 1
           
      print "{0:4} {1:5} {2:20} {3:10} {4:7} {5:16X} {6:3}" \
      .format(atid, channel, timestamp, (timestamp-prev_ts), opcode, payload, hwe[0]),

      if cmm_file: print " -", hwe_list[hwe[0]]
      else:        print ""

      for i in range(1, len(hwe)):
         print "                                                                    {0:3}".format(hwe[i]),

         if cmm_file: print " -", hwe_list[hwe[i]]
         else:        print ""

      prev_ts = timestamp

#####################
### print summary ###
#####################

print ""
print "-------"
print "Summary"
print "-------"
print ""

for event in count_events.keys():
   print "event {0:2} count {1:5}".format(event, count_events[event]),
   
   if cmm_file: print " -", hwe_list[event]
   else:        print ""
      
############################
### close files and exit ###
############################

input_file_object.close()
