############################################################################
#                            P W R D B 
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  This file contains the power debugger script to convert the pec file to 
#  binaray file (.pds file)  
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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_dump_pds.pl#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 10/02/09   jl        Created this file
###############################################################################
use strict;
use warnings;

use IO::File;
use Getopt::Long;

use PWRDB_DIAG;
use PWRDB_APEC;
use PWRDB_LOG;
use PWRDB_PEC;

# Variables to track command line options
# default values should be set here

my $pec_filename = '';        # .pec filename (generic for pec script on any processor).

my $pds_filename = ''; # Filename of the output pds script. 
                                                
my $C_header_file_path = "../src/pwrdb_diag.h"; # path of the C header file

my $output_filename = '';
###############################################################################
#
# S U B R O U T I N E S
#
###############################################################################
sub usage
{
   print
"
usage: perl pwrdb_dump_pds.pl [-option_name=value]

Option_name may be truncated as long as enogh characters are given to make 
the name unique.

options:
-pec       Filename of the .pec file which will be converted to a .pds script.
-fpath     Path to the C header file that you need to process to generate 
           format hash and constant hash for perl script 
-output    Name of the PDS output (example: output.pds). If no output parameter
           is given, the default output PDS will be named the same as the input PEC
           script in the 'data' directory. (example: pmic_dump.pec => pmic_dump.pds)

example:
perl pwrdb_dump_pds.pl -pec=data/modem.pec -output=get_pmic_dump.pds
-fpath=\"../src/pwrdb_diag.h\"
output: data/get_pmic_dump.pds

or

perl pwrdb_dump_pds.pl -pec=data/modem.pec -fpath=\"../src/pwrdb_diag.h\"
output: data/modem.pds

Warning: If you want to drop a PDS Script in EFS, the output parameter MUST be defined
as shown below depending on the processor: 

Modem: 'pwrdb_modem_startup.pds'
Apps: 'pwrdb_apps_startup.pds'

ADSP does not support EFS access at this time.

";
}

###############################################################################
#
# M A I N   S C R I P T   S T A R T S   H E R E
#
###############################################################################

# Process options
if (scalar(@ARGV) == 0)
{
   usage;
   exit;
}

my $result = GetOptions('pec=s'    => \$pec_filename,
                        'output=s'     => \$output_filename,
                        'fpath=s'      => \$C_header_file_path);

if ($C_header_file_path) 
{
   process_C_header($C_header_file_path);
}
else
{
   die "Did you assign the C header file? (e.g pwrdb_diag.h)$!";
}

my $pds_script = '';

print "\nWarning: If you want to drop a PDS Script in EFS, it must be named 
'pwrdb_modem_startup.pds' or 'pwrdb_apps_startup.pds' depending on the processor!\n";


if ($pec_filename)
{ 
   $pds_script = build_script( $pec_filename );
   if ($output_filename)
   {
      $pds_filename = 'data/' . $output_filename;     
   }
   else {
    $pds_filename = $pec_filename;
    $pds_filename =~ s{\.[^.]+$}{};
    $pds_filename .= '.pds';
   } 
   open( PDSFILE_M, ">", $pds_filename   ) || die "Can't open log file.\n";
   binmode ( PDSFILE_M );
   print( PDSFILE_M $pds_script );

   print "\nSuccessfully created $pds_filename in 'data' directory.\n";
   close( PDSFILE_M );
}







