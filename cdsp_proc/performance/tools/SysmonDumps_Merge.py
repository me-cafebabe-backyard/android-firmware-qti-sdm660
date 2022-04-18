import sys

global ip_loc

ip_loc=sys.argv[1]
file(ip_loc+'\sysmon_dump.bin','wb').write(file(ip_loc+'\sysmon_dump1.bin','rb').read()+file(ip_loc+'\sysmon_dump2.bin','rb').read())
