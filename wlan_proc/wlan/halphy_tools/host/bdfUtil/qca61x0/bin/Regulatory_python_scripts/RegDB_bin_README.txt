Run the tool as below: 
	
	python RegDB_excel2bin.py

-Script will generate RegDB.bin and RegDB_new.txt in the local location. It uses RegDB_txt2bin.py and RegDB_bin2txt.py.
-By default, RegDB BDF will be enabled via flag regDbEnable (i.e. regulatory database values will be taken from RegDB BDF values). To disable, change the enable flag(regDbEnable) to 0 in txt and convert txt<->bin.

NOTE: Runs with Python 2.7.6 and above. openpyxl 2.4.5 module is required. 