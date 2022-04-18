from sys import argv
import struct
import math
import re
import binascii
import sys

script, binFile, txtFile = argv
txtFile = txtFile[:(len(txtFile)-4)] #txtfile-array: read all the, except for the last 4bytes

def num_bytes(typeVal):
    lenVal = (typeVal[(len(typeVal)-2):])
    if(lenVal == "t8"):
        return 1
    elif(lenVal == "16"):
        return 2
    elif(lenVal == "32"):
        return 4
    elif(lenVal == "64"):
        return 8
    else:
        print('Error')
        return 0
        
def get_data(nbytes):
    global seekVal
    
    f.seek(seekVal)
    seekVal = seekVal + nbytes;
    
    if nbytes == 1:  
        val = list (struct.unpack('<B', f.read(nbytes)))[0]
    elif nbytes == 2:
        val = list (struct.unpack('<H', f.read(nbytes)))[0]
    elif nbytes == 4:
        val = list (struct.unpack('<I', f.read(nbytes)))[0]
    elif nbytes == 8:
        val = list (struct.unpack('<Q', f.read(nbytes)))[0]
    else:
        val= 0;
        print('Error')

    return val

txt = open(txtFile+".txt","r")
txtLines = txt.readlines()

f = open(binFile,"rb")
data = f.read()
seekVal = 0
i = 0

while (i < len(txtLines)):
    txtLines[i] = txtLines[i].strip()
    lineSet = list(filter(lambda x : x, re.split(' |\t', txtLines[i])))

    if lineSet[2].find("0x") != -1:
        is_Hex = 1
    else:
        is_Hex = 0
        
    if  lineSet[1].find("bf_reg") != -1:
        nbytes = 1 #dataType
        length = 1
    else: 
        nbytes = num_bytes(lineSet[0])
        length = (len(lineSet) -2) #should be not include the type and name
        
    lineSet[0] +='\t'
    
    for ptr in range(0,length):
        
        val = get_data(nbytes)
        
        if  lineSet[1].find("bf_reg") != -1:
            lineSet[ptr+2] = 'beamforming:' + str(hex((int(val))&0x01))
            lineSet[ptr+3] = 'regDmn:'+ str(hex((int(val))>>1&0x0f))
            lineSet[ptr+4] = 'reserved:'+str(hex(int(val)>>5&0x07))
        else :
            lineSet[ptr+2] = str(val)+''
                        
            if is_Hex:
                lineSet[ptr+2] = str(hex(val))+''

        txtLines[i] = ' '. join(lineSet)
      
        ptr += 1
                    
    i += 1
txt.close

txt = open(txtFile+"_new.txt","w")
txt.truncate
for line in txtLines:
    txt.writelines(line)
    txt.writelines(" \n")
f.close
txt.close
