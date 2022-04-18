from sys import argv
import binascii
import struct
import math
import re
import sys

script, txtFile, binFile = argv

byteCount = 0
checkSum = 0
wordVal = 0
wordCheck = 0
seekVal = 0

total_bytes = 0

def checksumCal(typeVal, checksumVal, byteSize, num):
    global byteCount
    global checkSum
    global wordVal
    global wordCheck
    lenVal = (typeVal[(len(typeVal)-2):])
    res = 0
    if(lenVal == "t8"):
        res = (int(math.pow(2, 8)) + num) if((num < 0) and (typeVal[0] == 'i')) else num
    if(lenVal == "16"):
        res = (int(math.pow(2, 16)) + num) if((num < 0) and (typeVal[0] == 'i')) else num
    if(lenVal == "32"):
        res = (int(math.pow(2, 32)) + num) if((num < 0) and (typeVal[0] == 'i')) else num
    if(lenVal == "64"):
        res = (int(math.pow(2, 64)) + num) if((num < 0) and (typeVal[0] == 'i')) else num

    if checksumVal.find("checksum") != -1: 
        byteCount = byteCount + 2
        workCheck = byteCount % 2
        checkSum = (checkSum + 0) & 65535
    else:
	    while (byteSize != 0):
	        byteCount += 1
	        wordCheck = byteCount % 2
	        wordVal = res % 256 if(wordCheck == 1) else (int (wordVal) | int((res % 256)*256))
	        if(wordCheck == 0):
	            checkSum = checkSum ^ wordVal
	        res = res / 256
	        byteSize -= 1
            
def num_bytes(typeVal):
    lenVal = (typeVal[(len(typeVal)-2):])
    if(lenVal == "t8" or lenVal[0] == '_'):
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

def data_type(typeVal):
    lenVal = (typeVal[(len(typeVal)-2):])
    res = 'n'
    if(lenVal == "t8"):
        res = 'b' if(typeVal[0] == 'i') else 'B'
    elif(lenVal == "16"):
        res = 'h' if(typeVal[0] == 'i') else 'H'
    elif(lenVal == "32"):
        res = 'l' if(typeVal[0] == 'i') else 'L'
    elif(lenVal == "64"):
        res = 'q' if(typeVal[0] == 'i') else 'Q'
    else:
        print('Error')
        res = 'b'
    return res

def bit_pack(a, txtLines):
    s = 1
    byt = 0
    num = 0
    while s:
        txtLines[a] = txtLines[a].strip()
        lineSet = txtLines[a].split(' ')
 
        if lineSet[2][0] == ' ':
            val = lineSet[2].split(' ')
            val = val[1]
        else:
            val = lineSet[2]
        if val.find("0x") != -1:
            if val.find("beamforming") != -1:
                val = 1
            else:
            	val = str(int(val, 0))
        else:
            val = val
        byteOffset = lineSet[0][(len(lineSet[0])-3):]
        #print(val)
        #print(byteOffset)
        num = num | ((int(val)*(int(math.pow(2, int(byteOffset[0]))))))
        byt += int(byteOffset[2])
        if byt == 8:
            s = 0
        else:
            a += 1
    return a, num

def Genrate_hex(a, txtLines,lineSet,value):
    global  total_bytes

    f.write(struct.pack(order + data_type(lineSet[0]), int(value)))
    checksumCal(lineSet[0], lineSet[1], num_bytes(lineSet[0]), int(value))
    
    total_bytes += num_bytes(lineSet[0])            
    return a, value

txt = open(txtFile, "r")
txtLines = txt.readlines()
f = open(binFile, "wb")
f.truncate
seekVal = 0
a = 0

if(sys.byteorder == "little"):
    order = '<'
else:
    order = '>'

while (a < len(txtLines)):
    txtLines[a] = txtLines[a].strip()
    lineSet = list(filter(lambda x : x, re.split(' |\t', txtLines[a])))
   
    if(a == 2):
        CtlLen = lineSet[2]
		
   	# deal with the field  -> bf_reg
    if lineSet[1].find("bf_reg") != -1: 
        if (lineSet[2].find("beamforming") != -1) and (lineSet[3].find("regDmn") != -1) and (lineSet[4].find("reserved") != -1):
            value = int(lineSet[2][-1])+(int(lineSet[3][-1])<<1)
        else:
            print('Error')

        Genrate_hex(a, txtLines,lineSet,value)
    else:
        length = len(lineSet)
            
        for i in range(2,length):
            value = int(eval(lineSet[i]))
            Genrate_hex(a, txtLines,lineSet,value)
    a += 1

checkSum = 65535 ^ checkSum
seekVal = 0
a = 0

#write the checksum
while (a < len(txtLines)):
    txtLines[a] = txtLines[a].strip()
    lineSet = list(filter(lambda x : x, re.split(' |\t', txtLines[a])))
    
    f.seek(seekVal)
    seekVal += num_bytes(lineSet[0]) * (len(lineSet)-2)
    
    if lineSet[1].find("checksum") != -1:
        f.write(struct.pack(order + 'H', int(checkSum)))
        break
        
    a += 1
#end

seekVal = 0
#write the total_len
while (a < len(txtLines)):
    txtLines[a] = txtLines[a].strip()
    lineSet = list(filter(lambda x : x, re.split(' |\t', txtLines[a])))
    
    f.seek(seekVal)
    seekVal += num_bytes(lineSet[0]) * (len(lineSet)-2)
    
    if lineSet[1].find("total_len") != -1:
        f.write(struct.pack(order + 'H', int(total_bytes)))
        print(total_bytes)
        break
        
    a += 1
#end

print('total_bytes =',int(total_bytes))
#if total_bytes != int(CtlLen) + 2:
#    print('Total bytes error, please check the nvCtlLen filed in BDF ')

f.close
txt.close
