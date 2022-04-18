
import sys, argparse, re,csv 
import os

regDict = {
      '1'  : 'FCC',
      '4'  : 'MKK',
      '3'  : 'ETSI',
      'E'  : 'SD_NO_CTL',
      'F'  : 'NO_CTL',
      '0'  : 'None',
    }
Modes = ["2G_SARLimitsCck","2G_SARLimitsHT20","2G_SARLimitsHT40","5G_SARLimitsHT20","5G_SARLimitsHT40","5G_SARLimitsHT80","5G_SARLimitsHT160"]
PwrTableOffsets2GCsv = [16,54,92]
PwrTableOffsets5GCsv = [32,70,108]
#-----------------------------------------------------------------------------------------------------------------------------------
def getSARConfigValues(listVal,BdfFileStr):
	
	#--------Get SAR Version-------------------------------
	sarVer = re.findall("SARVersion__0_0 (\w+)", BdfFileStr)
	if not sarVer:
		print "SAR Version 1 values not found"
		sys.exit()
		
	if sarVer[0] not in ['0x0','0x00','0x1','0x01']:
		print "Invalid SARVersion value "+ sarVer[0]
		sys.exit()
	else:
		listVal[0][1] = sarVer[0].split("x")[1]
	
	#--------Get SAR Flags-------------------------------
	sarFlagsBdf = re.findall("SARFlags__0_0 (\w+)", BdfFileStr)
	sarFlags = sarFlagsBdf[0].split('x')
	flags = [1,2,4]
	if flags[0] & int(sarFlags[1]):
		listVal[1][1] = 1
	else:
		listVal[1][1] = 0
		
	if flags[1] & int(sarFlags[1]):
		listVal[3][1] = 1
	else:
		listVal[3][1] = 0
		
	if flags[2] & int(sarFlags[1]):
		listVal[5][1] = 1
	else:
		listVal[5][1] = 0
		
	#--------Get SAR Channels-------------------------------	
	sarChannels2GBdf = re.findall("SAR2GChannels__0_0.*", BdfFileStr)[0].split(" ")
	for x in range(1,5):
		if sarChannels2GBdf[x] not in ['0','00']:
			listVal[7][x] = int(sarChannels2GBdf[x]) + 2300
		else:
			listVal[7][x] = int(sarChannels2GBdf[x])
	
	sarChannels5GBdf = re.findall("SAR5GChannels__0_0.*", BdfFileStr)[0].split(" ")
	for x in range(1,6):
		if sarChannels5GBdf[x] not in ['0','00']:
			listVal[8][x] = int(sarChannels5GBdf[x])*5 + 4800
		else:
			listVal[8][x] = int(sarChannels5GBdf[x])
	
	sarChannels5GVht160Bdf = re.findall("SAR5GVHT160Channels__0_0.*", BdfFileStr)[0].split(" ")
	for x in range(1,3):
		if sarChannels5GVht160Bdf[x] not in ['0','00']:
			listVal[9][x] = int(sarChannels5GVht160Bdf[x])*5 + 4800
		else:
			listVal[9][x] = int(sarChannels5GVht160Bdf[x])

	#--------Get SAR CTL List-------------------------------	

	CtlListBdf = re.findall("SARCtlList__0_0 .*", BdfFileStr)[0].split(" ")
	for x in range(1,4):
		if CtlListBdf[x]in ["0","1","3","4","E","F"]:
			listVal[10][x] = regDict[CtlListBdf[x]]

	return listVal
	
#-----------------------------------------------------------------------------------------------------------------------------------
def getSARPwrValues(listVal, BdfFileStr):
	
	sarFlagsBdf = re.findall("SARFlags__0_0 (\w+)", BdfFileStr)
	sarFlags = sarFlagsBdf[0].split('x')
	flags = [1,2,4]
	for ctl in range(0,3):
		for sarSet in range(0,4):
			sarSetPwrBdfStr = re.findall("2G.*_B"+str(sarSet)+"_R"+str(ctl)+"_.*", BdfFileStr)
			for values in range(len(sarSetPwrBdfStr)):
				if flags[2] & int(sarFlags[1]):
					listVal[PwrTableOffsets2GCsv[ctl]+(values/4)][(sarSet*6)+2+(values%4)] = sarSetPwrBdfStr[values].split('x')[1]
				elif values%4 is not 3:
					listVal[PwrTableOffsets2GCsv[ctl]+(values/4)][(sarSet*6)+2+(values%4)] = sarSetPwrBdfStr[values].split('x')[1]
	

	for ctl in range(0,3):
		for sarSet in range(0,4):
			sarSetPwrBdfStr = re.findall("5G.*_B"+str(sarSet)+"_R"+str(ctl)+"_.*", BdfFileStr)
			for values in range(len(sarSetPwrBdfStr)):
				if flags[2] & int(sarFlags[1]):
					listVal[PwrTableOffsets5GCsv[ctl]+(values/4)][(sarSet*6)+2+(values%4)] = sarSetPwrBdfStr[values].split('x')[1]
				elif values%4 is not 3:
					listVal[PwrTableOffsets5GCsv[ctl]+(values/4)][(sarSet*6)+2+(values%4)] = sarSetPwrBdfStr[values].split('x')[1]
				
		
	return listVal
	
	
#-----------------------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
	cmdParser = argparse.ArgumentParser(description="CSV to BDF text conversion tool for SAR powers")
	cmdParser.add_argument('-csv', action="store", dest="CsvFilePath", default="sarBDFTool.csv", help="CSV file name")
	cmdParser.add_argument('-bdf', action="store", dest="BdfFilePath", default="bdwlan.txt", help="BDF txt file name")
	args = cmdParser.parse_args()
	SARPwrFile = open(args.CsvFilePath,'rb')
	if SARPwrFile is None:
		print "No input file %s found" % (args.CsvFilePath)
	else:
		SARPwrStr = SARPwrFile.read()
	
	newBDFFilePath = open(args.BdfFilePath,'r') #handle errono 2
	if newBDFFilePath is None:
		print "No input file %s found" % (args.BdfFilePath)
	else:
		BdfFileStr = newBDFFilePath.read()
		
	with open ("sarBDFTool.csv","rb") as f:
		readCsv = csv.reader(f)
		listVal = list(readCsv)


	listVal = getSARConfigValues(listVal,BdfFileStr)
	listVal = getSARPwrValues(listVal, BdfFileStr)
	
	i = 0
	while os.path.exists("getSarPwr_helium%s.csv" % i):
		i += 1
	op = open("getSarPwr_helium%s.csv" % i,'wb')
	writeCsv = csv.writer(op)
	for x in range(len(listVal)):
		writeCsv.writerow(listVal[x])
		
		
	
	
	
