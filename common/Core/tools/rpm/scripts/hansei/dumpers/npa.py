#  ===========================================================================
#
#  Copyright (c) 2011 Qualcomm Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================


from __future__ import print_function

import logging
logger = logging.getLogger(__name__)

import os
import itertools
from locators.core_dump import locate as locate_core_dump
from dwarf import decode_object
from hansei_utils import *

dump_error = 0 # should only be used for error that indicate dump corruption

#
# Similar to the ULog dump scripts, this is copied directly from the rpm_npadump.cmm.
#
def dump(debug_data): #dump_path, memory, debug_info):
    global dump_error
    dump_error = 0
    memory = debug_data['rpm_memory']
    debug_info = debug_data['debug_info']
    dump_path = debug_data['dump_path']
    reclaim = debug_data['reclaim_pool']
    
    debug_data['printer'].p("Dumping NPA state...")

    address = locate_core_dump(memory, debug_info)
    dump_type = debug_info.variables['rpm_core_dump'].vartype
    rpm_core_dump = decode_object('rpm_core_dump', address, dump_type, memory, debug_info)

    npa_type = debug_info.variables['npa'].vartype
    npa_state = rpm_core_dump.npa_state.address
    npa = decode_object('npa', npa_state, npa_type, memory, debug_info)

    dump_file = open(os.path.join(dump_path, 'npa-dump.txt'), 'w')

    link = npa.resources
    while link.address != 0:
        dump_link(dump_file, link, reclaim)
        link = link.next
    
    if dump_error != 0:
      debug_data['printer'].p("\t...Non-critical errors occured in processing dump, continuing")
    else:
      debug_data['printer'].p("\t...DONE")

def get_name(item, mem):
  if item.address > mem['start_addr'] and item.address < mem['start_addr']+mem['size']:
    name = pointer_to_str(mem['memory'].read(item.address), 100) #assume there are no names with more than 100 characters
    #name += "== recovered =="
  else:
    name  = ''.join(itertools.takewhile(lambda c: c != '\0', (chr(c) for c in item)))
  return name
        
def dump_link(dump_file, link, reclaim):
    #import pdb; pdb.set_trace()
    #link_name  = ''.join(itertools.takewhile(lambda c: c != '\0', (chr(c) for c in link.name)))
    link_name = get_name(link.name, reclaim)
    resource   = link.resource
    definition = resource.definition

    if definition.address == 0:
        dump_placeholder(dump_file, link_name)
    else:
        #resource_name = ''.join(itertools.takewhile(lambda c: c != '\0', (chr(c) for c in definition.name)))
        resource_name = get_name(definition.name, reclaim)
        if resource_name == link_name:
            dump_resource(dump_file, resource, resource_name, reclaim)
        elif resource_name == 'marker resource':
            dump_marker(dump_file, link_name)
        else:
            dump_alias(dump_file, link_name, resource_name)

def dump_placeholder(dump_file, link_name):
    print('npa_placeholder (name: "%s")' % link_name, file=dump_file)

def dump_marker(dump_file, link_name):
    print('npa_marker (name: "%s")' % link_name, file=dump_file)

def dump_alias(dump_file, link_name, resource_name):
    print('npa_alias (alias_name: "%s") (resource_name: "%s")' % (link_name, resource_name), file=dump_file)

def dump_resource(dump_file, resource, resource_name, reclaim):
    dump_resource_state(dump_file, resource, resource_name, reclaim)
    dump_resource_clients(dump_file, resource, reclaim)
    dump_resource_events(dump_file, resource, reclaim)

    print('        end npa_resource (handle: 0x%x)' % resource.address, file=dump_file)

def dump_resource_state(dump_file, resource, resource_name, reclaim):
    global dump_error
    try:
      #units = ''.join(itertools.takewhile(lambda c: c != '\0', (chr(c) for c in resource.definition.units)))
      units           = get_name(resource.definition.units, reclaim)
      resource_max    = resource.definition.max
      active_state    = resource.active_state
      active_max      = resource.active_max
      active_headroom = resource.active_headroom
      request_state   = resource.request_state
      error           = ""
    except:
      error = "\n\tAn error occured processing this resource"
      dump_error += 1
      #import pdb; pdb.set_trace()

    dumpstr = 'npa_resource (name: "{0}") (handle: {1}) (units: {2}) (resource max: {3}) (active max: {4}) (active state: {5}) (active headroom: {6}) (request state: {7}){8}'
    dumpdat = [resource_name, hex(resource.address), units, resource_max, active_max, active_state, active_headroom, request_state, error]
    print(dumpstr.format(*dumpdat), file=dump_file)

def dump_resource_clients(dump_file, resource, reclaim):
    global dump_error
    client = resource.clients

    while client.address != 0:
        try:
          #client_name = ''.join(itertools.takewhile(lambda c: c != '\0', (chr(c) for c in client.name)))
          client_name = get_name(client.name, reclaim)
        except:
          #import pdb; pdb.set_trace()
          client_name = "[ERROR: INVALID POINTER]"
          dump_error += 1
        try:
          client_type = client.type
          if client.index > client.work._upper_bound:
            request = "[ERROR: INVALID INDEX]"
          else:
            try:
              request = client.work[client.index].state
            except:
              #import pdb; pdb.set_trace()
              request = "[ERROR: UNKNOWN EXCEPTION]"
              dump_error += 1

          #string = '        npa_client (name: %s) (handle: 0x%x) (resource: 0x%x) (type: %s) (request: %d)'
          #dat = (client_name, client.address, resource.address, client_type, request)
          #print(string % dat, file=dump_file)
          
          string = '        npa_client (name: {0[0]}) (handle: {0[1]}) (resource: {0[2]}) (type: {0[3]}) (request: {0[4]})'
          dat = (client_name, hex(client.address), hex(resource.address), client_type, request)
          print(string.format(dat), file=dump_file)
          #print(string.format(client_name, hex(client.address), hex(resource.address), client.type, request), file=dump_file)
          client = client.next
        except:
          print("        ERROR: CLIENT IS CORRUPT, SKIPPING", file=dump_file)
          dump_error += 1
          break

def dump_resource_events(dump_file, resource, reclaim):
    event = resource.events

    while event.address != 0:
        #event_name = ''.join(itertools.takewhile(lambda c: c != '\0', (chr(c) for c in event.name)))
        event_name = get_name(event.name, reclaim)
        trigger_type = event.trigger_type

        if trigger_type == 'NPA_TRIGGER_RESERVED_EVENT':
            dumpstr = '        npa_reserved_event (name: "%s") (handle: 0x%x) (resource: 0x%x)'
            dumpdat = (event_name, event.address, resource.address)
        elif trigger_type == 'NPA_TRIGGER_CHANGE_EVENT':
            dumpstr = '        npa_change_event (name: "%s") (handle: 0x%x) (resource: 0x%x)'
            dumpdat = (event_name, event.address, resource.address)
        elif trigger_type == 'NPA_TRIGGER_WATERMARK_EVENT':
            lo = event.lo.watermark
            hi = event.hi.watermark
            dumpstr  = '        npa_watermark_event (name: "%s") (handle: 0x%x) (resource: 0x%x)'
            dumpstr += ' (lo_watermark: %d) (hi_watermark: %d)'
            dumpdat  = (event_name, event.address, resource.address, lo, hi)
        elif trigger_type == 'NPA_TRIGGER_THRESHOLD_EVENT':
            lo = event.lo.threshold
            hi = event.hi.threshold
            dumpstr  = '        npa_threshold_event (name: "%s") (handle: 0x%x) (resource: 0x%x)'
            dumpstr += ' (lo_threshold: %d) (hi_threshold: %d)'
            dumpdat  = (event_name, event.address, resource.address, lo, hi)

        print(dumpstr % dumpdat, file=dump_file)
        event = event.next

