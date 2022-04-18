
Script convert separete CTL values between BIN and text files.
NOTE: openpyxl module is required.

Please refer to the L0 announcement document for FR59035 more details about the tool 
FR59035 separate separate CTL tables from BDF

To convert text to bin
----------------------
Usage: python bdwlctl_txt2bin.py <input bdftxt> <output bdf.bin> 
Example:
python bdwlctl_txt2bin.py bdwlctl.txt bdwlctl.bin


To convert bin to text
----------------------
Usage: python bdfwlctl_bin2txt.py <input bdf.bin> <output bdf.txt>
Example:
python bdfwlctl_bin2txt.py bdwlctl.bin bdwlctl.txt
