import sys, argparse, re, csv
import os

regDict = {
      'FCC'      : '1',
      'MKK'      : '4',
      'ETSI'     : '3',
      'SD_NO_CTL': 'E',
      'NO_CTL'   : 'F',
      'None'     : '0',
    }
Modes = ["2G_SARLimitsCck","2G_SARLimitsHT20","2G_SARLimitsHT40","5G_SARLimitsHT20","5G_SARLimitsHT40","5G_SARLimitsHT80","5G_SARLimitsHT160"]
#-----------------------------------------------------------------------------------------------------------------------------------
def setSARConfigValues(BdfFileStr, SARPwrStr):

	#--------Set SAR Version-------------------------------
	sarVer = re.findall("SARVersion,(\w+)", SARPwrStr)
	if sarVer[0] not in ['0','1','00','01','0x01','0x1']:
		print "Invalid SARVersion value "+ sarVer[0]
		sys.exit()
	else:
		if sarVer[0] in ['0x01','0x1']:
			op = re.sub("SARVersion__0_0 \w+", "SARVersion__0_0"+sarVer[0], BdfFileStr)
		else:
			op = re.sub("SARVersion__0_0 \w+", "SARVersion__0_0"+" 0x"+sarVer[0], BdfFileStr)
			
	#--------Set SAR Flags-------------------------------	
	sarFlags = re.findall("\(SARFlags\),(\w+)", SARPwrStr)
	flags = ['0','0','0']
	for x in range(len(sarFlags)):
		if sarFlags[x] not in ['0','1','00','01']:
			print "Invalid SARFlags value"
			sys.exit()
		else:
			flags[x] = int(sarFlags[x])<<x
	sarBdfFlag = flags[0] | flags[1] | flags[2]
	op = re.sub("SARFlags__0_0 \w+", "SARFlags__0_0"+" 0x"+str(sarBdfFlag),op)
	
	#--------Set SAR Channels-------------------------------	
	Channels2G = re.findall("SAR2GChannels \(\w+\),(\w+),(\w+),(\w+),(\w+)", SARPwrStr)
	Channels2GBdf = [255,255,255,255]
	Channels2GBdfStr = "SAR2GChannels__0_0"
	for x in range (len(Channels2G[0])):
		if Channels2G[0][x] is not '0':
			Channels2GBdf[x] = int(Channels2G[0][x]) - 2300
		Channels2GBdfStr = Channels2GBdfStr+" "+str(Channels2GBdf[x])
			
	op = re.sub("SAR2GChannels__0_0 (\w+) (\w+) (\w+) (\w+)",Channels2GBdfStr, op)
	
	Channels5G = re.findall("SAR5GChannels \(\w+\),(\w+),(\w+),(\w+),(\w+),(\w+)", SARPwrStr)
	Channels5GBdf = [255,255,255,255,255]
	Channels5GBdfStr = "SAR5GChannels__0_0"
	for x in range (len(Channels5G[0])):
		if Channels5G[0][x] is not '0':
			Channels5GBdf[x] = (int(Channels5G[0][x]) - 4800)/5
		Channels5GBdfStr = Channels5GBdfStr+" "+str(Channels5GBdf[x])
			
	op = re.sub("SAR5GChannels__0_0 (\w+) (\w+) (\w+) (\w+) (\w+)",Channels5GBdfStr, op)
	
	Channels5GVht160 = re.findall("SAR5GVHT160Channels \(\w+\),(\w+),(\w+)", SARPwrStr)
	Channels5GVht160Bdf = [255,255]
	Channels5GVht160BdfStr = "SAR5GVHT160Channels__0_0"
	for x in range (len(Channels5GVht160[0])):
		if Channels5GVht160[0][x] is not '0':
			Channels5GVht160Bdf[x] = (int(Channels5GVht160[0][x]) - 4800)/5
		Channels5GVht160BdfStr = Channels5GVht160BdfStr+" "+str(Channels5GVht160Bdf[x])
		
	op = re.sub("SAR5GVHT160Channels__0_0 (\w+) (\w+)",Channels5GVht160BdfStr, op)
	
	#--------Set SAR CTL List-------------------------------
	CtlList = re.findall("SARCtlList,(\w+),(\w+),(\w+)", SARPwrStr)
	CtlListBdfStr = "SARCtlList__0_0"
	CtlListBdf = ['1','4','3']
	for x in range(len(CtlList[0])):
		if CtlList[0][x] is not '0':
			CtlListBdf[x] = regDict[CtlList[0][x]]
		CtlListBdfStr = CtlListBdfStr + " "+ CtlListBdf[x]
	op = re.sub("SARCtlList__0_0 (\w+) (\w+) (\w+)",CtlListBdfStr, op)
	
	return op
	
#-----------------------------------------------------------------------------------------------------------------------------------
def setSARPwrValues(BdfFileStr, SARPwrStr):
	sarFlags = re.findall("\(SARFlags\),(\w+)", SARPwrStr)
	op = BdfFileStr
	for chanGrp in range(0,5):
		values = re.findall("ChanGrp"+str(chanGrp)+",(\w+),(\w+),(\w+),(\w+)", SARPwrStr)
		numValues = 0
		for ctl in range(0,3):
			for mode in range(len(Modes)):
				if chanGrp > 1 and Modes[mode] == "5G_SARLimitsHT160":
					continue
				if chanGrp == 4 and Modes[mode] not in ["5G_SARLimitsHT20","5G_SARLimitsHT40","5G_SARLimitsHT80"]:
					continue
				for sarSet in range(0,4):
					valuesChan = re.findall(Modes[mode]+".*B"+str(sarSet)+"_R"+str(ctl)+"_"+str(chanGrp)+"_0 \w+", BdfFileStr)
					for p in range(len(valuesChan)):
						if sarFlags[2] in ["1","01"]:
							op = re.sub(valuesChan[p] ,valuesChan[p].split('x')[0]+"x"+values[numValues][p],op)
						elif p not in [0,1,2]:
							op = re.sub(valuesChan[p] ,valuesChan[p].split(' ')[0]+" 0",op)
						else:
							op = re.sub(valuesChan[p] ,valuesChan[p].split('x')[0]+"x"+values[numValues][p],op)
					numValues+=1
		
	return op
	
	
#-----------------------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
	cmdParser = argparse.ArgumentParser(description="CSV to BDF text conversion tool for SAR powers")
	cmdParser.add_argument('-csv', action="store", dest="CsvFilePath", default="sarBDFTool.csv", help="CSV file name")
	cmdParser.add_argument('-bdf', action="store", dest="BdfFilePath", default="bdwlan.txt", help="BDF txt file name")
	args = cmdParser.parse_args()
	SARPwrFile = open(args.CsvFilePath,'r')
	if SARPwrFile is None:
		print "No input file %s found" % (args.CsvFilePath)
	else:
		SARPwrStr = SARPwrFile.read()
	
	newBDFFilePath = open(args.BdfFilePath,'r') #handle errono 2
	if newBDFFilePath is None:
		print "No input file %s found" % (args.BdfFilePath)
	else:
		BdfFileStr = newBDFFilePath.read()
	
	temp_file = open("getSarPwr_helium_temp.csv",'wb')
	writeCsv = csv.writer(temp_file)

	
	with open ("sarBDFTool.csv","rb") as f:
		readCsv = csv.reader(f)
		listVal = list(readCsv)
	
	for x in range(len(listVal)):
		for y in range(len(listVal[x])):
			listVal[x][y] = listVal[x][y].strip()
		writeCsv.writerow(listVal[x])
	temp_file.close()
	
	temp_file = open("getSarPwr_helium_temp.csv",'r')
	
	SARPwrStr = temp_file.read()
	
	op = setSARConfigValues(BdfFileStr, SARPwrStr)
	
	op = setSARPwrValues(op, SARPwrStr)
	
	i = 0
	while os.path.exists("setSarPwr_helium_op%s.txt" % i):
		i += 1
	output = open("setSarPwr_helium_op%s.txt" % i,'w+')
	output.write(op)
	
	temp_file.close()
	os.remove("getSarPwr_helium_temp.csv")


	
	
	
