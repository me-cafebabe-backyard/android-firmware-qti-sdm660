import sys

tempFileName = ".\\temp.log"

def reverseLines(fin, fout):
    outFile = open(fout, 'w')
    with open(fin) as f1:
       for line in reversed(f1.readlines()):
          outFile.write(line)
    outFile.close()
    
def parseHlosLog(fin, fout):
    #tempFilename = ".\\temp.log"
    #tempFile = open(tempFilename, 'w')
    #with open(fin) as f1:
    #   for line in reversed(f1.readlines()):
    #      tempFile.write(line)
    #tempFile.close()
    
    outFile = open(fout, 'w')
    outFile.write("Starting dumps!\n")
    outFile.write("Dump path = .\\")
    outFile.write(fout + ", pause time = 30\n")
    bGetTime = False
    bTimestartFound = False
    bDumping = False
    timestamp = 0
    with open(fin) as f1:
       for line in (f1.readlines()):
          startIndex = line.find("::")
          #outFile.write(line[startIndex:])
          #words = line[startIndex+2:].split(" ")
          words = line[startIndex:].split(" ")
          for i in words:
             if (i.find("=") == 0):
                if (bTimestartFound): #or bTimedoneFound ):
                   bGetTime = True
             elif (i.find("Timestamp") == 0):
                if (bDumping):
                   outFile.write(("FG SRAM Dump done at ") + timestamp)
                   bDumping = False
                outFile.write("FG SRAM Dump started at ")
                bTimestartFound = True
             elif (bGetTime):
                timestamp = i
                outFile.write(i)          
                bGetTime = False
                bTimestartFound = False
                bDumping = True             
             #elif (i.find("Done") == 0):
                #outFile.write("FG SRAM Dump done at ")
             elif (i.find(":") == 0):
                bPrintData = False
             elif (i.find(",") == 0):
                #outFile.write(printAddr.zfill(3) + " ")
                outFile.write(str((int(printAddr, 16))).zfill(3) + " ")             
                bPrintData = True;  
                count = 4
             elif (i.find("0x") == 0):
                if (bPrintData):
                   if (count == 1):
                      outFile.write((i[2:].zfill(3).upper()))       
                   else:
                      outFile.write((i[2:].zfill(2).upper()) + " ")
                   count = count-1                
                else:
                   printAddr = i[2:]
                #print(i[2:] + "\n")
                #outFile.write((i[2:].zfill(3)) + " ")
       outFile.write(("FG SRAM Dump done at ") + timestamp)
    outFile.close()
    
def parseUefiLog(fin, fout):
    outFile = open(fout, 'w')
    outFile.write("Starting dumps!\n")
    outFile.write("Dump path = .\\")
    outFile.write(fout + ", pause time = 30\n")
   
    with open(fin) as f1:
       bDumpDataFound = False
       for line in (f1.readlines()):
          if (not bDumpDataFound):
             startIndex = line.find("PmicFgSram_Dump")
             if (startIndex != -1):
                words = line.split(" ")
                timestamp = (words[0][:-1])
                if ((words[3] == "SRAM") & (words[5] == "Start")):
                   bDumpDataFound = True
                   outFile.write("FG SRAM Dump started at ")
                   outFile.write(timestamp)
                   outFile.write("\n")                
          else:
             words = line.split(" ")
             if ((words[0][-1:] != ",") & (len(words) == 6)):
                outFile.write(line)
             else:
                timestamp = (words[0][:-1])
                if ((words[3] == "SRAM") & (words[5] == "End")):
                   bDumpDataFound = False
                   outFile.write("FG SRAM Dump done at ")
                   outFile.write(timestamp)
                   outFile.write("\n")    
    outFile.close()
          

if __name__ == "__main__":
    filename = sys.argv[1]
    logtype = sys.argv[2]
    outfile = sys.argv[3]
    if ((logtype == "-AHLOS") | (logtype == "-aHLOS")):
       parseHlosLog(filename, outfile)     
    elif ((logtype =="-DHLOS") | (logtype == "dHLOS")):
       reverseLines(filename, tempFileName)
       parseHlosLog(tempFileName, outfile)
    elif ((logtype == "-U") | (logtype == "-u")):
       parseUefiLog(filename, outfile)
    else:
       print("\nInvalid syntax!")
       print("Usage: python formatFgSramDump.py  <INPUTLOG_PATH> <-AHLOS/-aHLOS/-DHLOS/-dHLOS/-U/-u> <OUTPUT_PATH>")

