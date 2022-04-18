from sys import argv
import struct
import math

import sys

script, binFile, txtFile = argv
txtFile = txtFile[:(len(txtFile)-4)]
# Reading Binary values from .bin file as integer numbers

def numerical_val(val,nBits,signVal):
    a = nBits/8
    numVal = 0
    for b in range(a):
        numVal = numVal << 8
        if(sys.byteorder == "little"):
            numVal = numVal + ord(val[a-1-b])
        else:
            numVal = numVal + ord(val[b])
    if ((signVal == 'i') and (numVal > (1<< nBits)/2)):
        return ((1<<nBits)-numVal)*(-1)
    else:
        return numVal

def num_bytes(typeVal):
    lenVal = (typeVal[(len(typeVal)-2):])
    if(lenVal == "t8"):
        return 1
    if(lenVal == "16"):
        return 2
    if(lenVal == "32"):
        return 4
    if(lenVal == "64"):
        return 8
    return 1

txt = open(txtFile+".txt","r")
txtLines = txt.readlines()


f = open(binFile,"rb")
data = f.read()
seekVal = 0
i = 0
while (i < len(txtLines)):
    txtLines[i] = txtLines[i].strip()
    lineSet = txtLines[i].split('\t')
    if lineSet[0][(len(lineSet[0])-2):][0] == '_':
        f.seek(seekVal)
        seekVal += 1
        s = 1
        byt = 0
        num = 0
        val = f.read(1)
        val = numerical_val(val,8,'u')
        while s:
            txtLines[i] = txtLines[i].strip()
            lineSet = txtLines[i].split('\t')
            byteOffset = lineSet[0][(len(lineSet[0])-3):]
            num = (int(val) & (int(math.pow(2,(int(byteOffset[0]) + int(byteOffset[2])))) - 1))/(int(math.pow(2, int(byteOffset[0]))))
            if num >= 0:
                lineSet[2] = ' ' + str(num)
            else:
                lineSet[2] = str(num)
            txtLines[i] = '\t'. join(lineSet)
            byt += int(byteOffset[2])
            if byt == 8:
                s = 0
            else:
                i += 1  
    else:
        f.seek(seekVal)
        r = num_bytes(lineSet[0])
        seekVal = seekVal + r
        val = f.read(r)
        fin = numerical_val(val,r*8,lineSet[0][0])
        if fin >= 0:
            lineSet[2] = ' ' + str(fin)
        else:
            lineSet[2] = str(fin)
        txtLines[i] = '\t'. join(lineSet)
    i += 1
txt.close


txt = open(txtFile+"_new.txt","w")
txt.truncate
for line in txtLines:
    txt.writelines(line)
    txt.writelines(" \n")
f.close
txt.close
