import sys, re, os
from base_parser import Parser
from target_data import *

class RAILWAYChangeVoltage:
    __metaclass__ = Parser
    id = 0x28A
    def parse(self, data):
        new_corner, old_corner = get_corner_name(0xffff & (data[3]>>16)), get_corner_name(0xffff & data[3])
        return 'railway_change_voltage (rail: %s) (new microvolts: %d) (old microvolts %d) (new corner %s) (old corner %s)' % \
                (get_rail_name(data[0]), data[1], data[2], new_corner, old_corner)
