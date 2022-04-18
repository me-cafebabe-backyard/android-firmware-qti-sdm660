import sys, re, os
from base_parser import Parser

class DDRSelfRefreshIdleEntry:
    __metaclass__ = Parser
    id = 0x2
    def parse(self, data):
        return 'ddr driver:enter self refresh idle for (channel: %d) (rank: %d)' % (data[0], data[1])

class DDRSelfRefreshASAPEntry:
    __metaclass__ = Parser
    id = 0x3
    def parse(self, data):
        return 'ddr driver:enter self refresh asap for (channel: %d) (rank: %d)' % (data[0], data[1])

class DDRSelfRefreshExit:
    __metaclass__ = Parser
    id = 0x4
    def parse(self, data):
        return 'ddr driver:exit self refresh for (channel: %d) (rank: %d)' % (data[0], data[1])
        
class DDRDPDEntry:
    __metaclass__ = Parser
    id = 0x5
    def parse(self, data):
        return 'ddr driver:Enter deep power down for (channel: %d) (rank: %d)' % (data[0], data[1])

class DDRDPDExit:
    __metaclass__ = Parser
    id = 0x6
    def parse(self, data):
        return 'ddr driver:exit deep power down for (channel: %d) (rank: %d)' % (data[0], data[1])        

class DDRPASRUpdate:
    __metaclass__ = Parser
    id = 0x7
    def parse(self, data):
        return 'ddr driver:partial array self refresh update for (channel: %d) (rank: %d) (pasr: %d)' % (data[0], data[1], data[2])                

class DDRBIMCPowerCollapseEntry:
    __metaclass__ = Parser
    id = 0x8
    def parse(self, data):
        return 'ddr driver:bimc power collapse entry for (channel: %d) (rank: %d)' % (data[0], data[1])           

class DDRBIMCPowerCollapseExit:
    __metaclass__ = Parser
    id = 0x9
    def parse(self, data):
        return 'ddr driver:bimc power collapse exit for (channel: %d) (rank: %d)' % (data[0], data[1])             

class DDRPreClockSwitch:
    __metaclass__ = Parser
    id = 0xA
    def parse(self, data):
        return 'ddr driver:pre clock switch for (channel: %d) (current clock: %d) (new clock: %d)' % (data[0], data[1], data[2])           

class DDRPostClockSwitch:
    __metaclass__ = Parser
    id = 0xB
    def parse(self, data):
        return 'ddr driver:post clock switch for (channel: %d) (current clock: %d) (new clock: %d)' % (data[0], data[1], data[2])      

class DDRErrFatal:
    __metaclass__ = Parser
    id = 0xC
    def parse(self, data):
        return 'ddr driver:Error Fatal (%d) (%d) (%d) (%d)' % (data[0], data[1], data[2], data[3])              

