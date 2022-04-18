############################################################################
#                            P W R D B 
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  Run this file to view a description for each PEC file in the data directory.
#   
# EXTERNALIZED FUNCTIONS
#   
#  None
# 
# INITIALIZATION AND SEQUENCING REQUIREMENTS
# 
#  None
#   
# 
#  Copyright (c) 2009 by QUALCOMM, Incorporated.  All Rights Reserved.
#   
# 
###############################################################################
# 
#                       EDIT HISTORY FOR FILE
# 
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/readme.pl#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 08/21/13   rs         Created this file
###############################################################################
@files = <data/*.pec>;
 print "Here is the description of each PEC file in the data directory \n";
 print "Format : File Path - Description \n \n";
 foreach $pecfile (@files)
 {
	open my $file, '<', $pecfile; 
	my $firstLine = <$file>; 
  close $file; 	
  print $pecfile . " - " . $firstLine . " \n";
} 