############################################################################
#                            P W R D B 
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  This file contains the power debugger script to convert the logs from 
#  EFS to human readable text.  
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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_read_pdl.pl#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 07/23/10   jl        Fixed the issue when reading the logs from EFS (.pdl file), it cannot find corresponding strings that map to the enum.
#                      Used PWRDB_FROMELF and PWRDB_PEC to build enum hash as in pwrdb.pl.
# 01/22/10   jl        Fixed print_log to accomodate the changes from pwrdb_log.pm
# 10/02/09   jl        Created this file
###############################################################################
use strict;
use warnings;

use IO::File;
use Getopt::Long;
use PWRDB_DIAG;
use PWRDB_FROMELF;
use PWRDB_LOG;
use PWRDB_PEC;

my $mlog='';
my $alog='';
my $mlog_filename='mlog.txt';  # Filename of the log text file for modem proc
my $alog_filename='alog.txt';  # Filename of the log text file for apps proc

my $mpdl_filename =''; # Filename of the .pdl file for modem proc
my $apdl_filename =''; # Filename of the .pdl file for apps proc


my %enum_HoH=();              # Empty enum hash
my @enum_t;                   # Array of the types that we want to read as human readable text in the logs.
                              # These types are currently hard coded %pwrdb_log_templates
my $elf_file="pwrdb.o";       # Default object file that needs to be processed to pwrdb.txt 
my $from_elf_file="pwrdb.txt";# Default .txt file that contains all the enum information 
                              # which we are insterested in converting to human readable text string
###############################################################################
#
# S U B R O U T I N E S
#
###############################################################################
sub usage
{
   print
"
usage: perl pwrdb_read_pdl.pl [-option_name=value]

Option_name may be truncated as long as enogh characters are given to make 
the name unique.

options:
-mpdl        Filename of the .pdl file for modem proc
-apdl        Filename of the .pdl file for apps proc
-mlog        Filename of the log text file for modem proc
-alog        Filename of the log text file for apps proc

example:
perl pwrdb_read_pdl.pl -mpdl=pwrdb_modem_log.pdl -apdl= pwrdb_apps_log.pdl -mlog=mlog.txt
     -alog=alog.txt
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

my $result = GetOptions('-mpdl=s'    => \$mpdl_filename,
                        '-apdl=s'    => \$apdl_filename,
                        '-mlog=s'    => \$mlog_filename,
                        '-alog=s'    => \$alog_filename );
my $mdata;
my $adata;
my $n;
#my %m_enum_HoH=();
#my %a_enum_HoH=();

# For now assume modem and apps are sharing the same object file (pwrdb.o), hence same enum hash.
@enum_t=log_find_types();
%enum_HoH=get_enum_hash(\@enum_t,\$from_elf_file,\$elf_file);

# is_enum_valid() can only be called after get_enum_hash after $enum_HoH_valid is determined
if (is_enum_valid())
{
   add_fromelf_symbol(\%enum_HoH);
}


if($mpdl_filename)
{
   open(mFD, $mpdl_filename);
   binmode(mFD);

   while (($n = read mFD, $mdata, 10000) != 0) #Read 10000 bytes each time until 0(end of file)
   {
     $mlog .= $mdata; #$n bytes read
   }
   if($mlog)
   { 
     print_log( \%enum_HoH,\$mlog, \$mlog_filename );
   }
   
}
else
{
   print "No modem file is open $!\n";
}

if($apdl_filename)
{  
   open(aFD, $apdl_filename);
   binmode(aFD);

   while (($n = read aFD, $adata, 10000) != 0) #Read 10000 bytes each time until 0(end of file)
   {
     $alog .= $adata; #$n bytes read
   }
   if($alog)
   { 
     print_log( \%enum_HoH,\$alog, \$alog_filename );
   }
   
}
else
{
   print "No apps file is open $!\n";
}
close(mFD);
close(aFD);


