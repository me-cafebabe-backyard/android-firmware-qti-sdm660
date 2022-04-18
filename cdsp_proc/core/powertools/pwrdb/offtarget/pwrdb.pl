############################################################################
#                            P W R D B 
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  This file contains the power debugger main script.  This file interacts with 
#  the DIAG interface and the power debugger driver.
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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb.pl#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 09/15/14   hl        Added SLPI support.
# 09/03/13   rs        Added ability to send PDS script over diag. 
# 03/12/10   jl        Dumped modem log and apps log seperately.
# 12/07/09   jl        Added from_elf support. Process pwrdb.o file to generate pwrdb.txt file.
#                      Build the enum hash from this pwrdb.txt file.
# 07/30/09   jl/ck     Created this file
###############################################################################
use Win32::OLE;
use Win32::OLE::Variant;
use IO::File;
use Getopt::Long;


use strict;
use warnings;

use PWRDB_DIAG;
use PWRDB_APEC;
use PWRDB_LOG;
use PWRDB_PEC;
#use PWRDB_FROMELF;

# AppId for the Automation server.
my $prod_id = "QPSTAtmnServer.Application";

# Variables to track command line options
# default values should be set here
my $apps_pec_filename  = '';                    # filename for apps proc .pec file
my $delay              = 0;                     # delay between RUN and STOP
my $log_filename       = '';                    # filename for log, use stdout if not blank
                                                # this is used when users want to log both modem and apps log 
                                                # in the same file
my $modem_pec_filename = '';                    # filename for modem proc .pec file
my $lpass_pec_filename = '';                    # filename for adsp proc .pec file
my $slpi_pec_filename = '';                     # filename for slpi proc .pec file
my $modem_pds_filename = '';
my $lpass_pds_filename = '';
my $slpi_pds_filename = '';
my $apps_pds_filename = '';
my $port_name          = '';                    # port name for connecting to SURF/FFA
my $C_header_file_path = "../../pwrdb/src/pwrdb_diag.h"; # path of the C header file
my $modem_log_filename = '';                    # filename for modem log only, use stdout if not blank
my $apps_log_filename  = '';                    # filename for apps log only, use stdout if not blank
my $lpass_log_filename  = '';                    # filename for lpass log only, use stdout if not blank
my $slpi_log_filename  = '';                    # filename for slpi log only, use stdout if not blank

my $enum_valid=0;             # Set enum_valid to false
my %enum_HoH=();              # Empty enum hash
my @enum_t;                   # Array of the types that we want to read as human readable text in the logs.
                              # These types are currently hard coded %pwrdb_log_templates
my $elf_file="pwrdb.o";       # Default object file that needs to be processed to pwrdb.txt 
my $from_elf_file="pwrdb.txt";# Default .txt file that contains all the enum information 
                              # which we are insterested in converting to human readable text string
my $testclock_reg_value = 0;
###############################################################################
#
# S U B R O U T I N E S
#
###############################################################################
sub usage
{
   print
"
usage: perl pwrdb.pl [-option_name=value]

Performs the following steps:
1) connects to PWRDB running on the target on the COM port specified in the
   -port option
2) resets PWRDB on the target
3) sends PWRDB event/command scripts to the modem and/or the apps processor
   -app_pec and -mod_pec options
4) waits for a timeout or the user to press the enter key
   -delay option
5) retrieves the logs and writes then to stdout or a file
   -log option

Option_name may be truncated as long as enogh characters are given to make 
the name unique.

options:
-app_pec   Filename of the .pec file to send to the apps processor.
-delay     Amount of time in seconds to wait between issuing RUN packet 
             and issuing STOP packet. If this is 0 or is omitted then the 
             user will be prompted to press enter before issuing the STOP 
             packet.
-mod_pec   Filename of the .pec file to send to the modem processor.
-mod_pds   Filename of the .pds file to send to the modem processor.
-lpass_pec   Filename of the .pec file to send to the lpass processor.
-lpass_pds   Filename of the .pds file to send to the lpass processor.
-slpi_pec   Filename of the .pec file to send to the slpi processor.
-slpi_pds   Filename of the .pds file to send to the slpi processor.
-app_pec   Filename of the .pec file to send to the apps processor.
-app_pds   Filename of the .pds file to send to the apps processor.
-port      COM port for QPST to use to connect to target.
-log       Name of file to write log to, stdout if omitted.
-fpath     Path to the C header file that you need to process to generate 
           format hash and constant hash for perl script

example:
Send PEC Script:
perl pwrdb.pl -port=COM38 -mod_pec=data/modem.pec -log=log.txt -fpath=\"../../../src/pwrdb_diag.h\"

Send PDS Script:
perl pwrdb.pl -port=COM38 -mod_pds=data/8974_full_gpio_dump.pds -log=log.txt

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

my $result = GetOptions('app_pec=s'    => \$apps_pec_filename,
                        'delay=i'      => \$delay,
                        'log=s'        => \$log_filename,
                        'mod_pec=s'    => \$modem_pec_filename,
                        'lpass_pec=s'  => \$lpass_pec_filename,
                        'slpi_pec=s'  => \$slpi_pec_filename,
						            'mod_pds=s'    => \$modem_pds_filename,
                        'lpass_pds=s'    => \$lpass_pds_filename,
                        'slpi_pds=s'    => \$lpass_pds_filename,
                        'app_pds=s'    => \$apps_pds_filename,
                        'port=s'       => \$port_name, 
                        'fpath=s'      => \$C_header_file_path,
                        'alog=s'       => \$apps_log_filename,
                        'mlog=s'       => \$modem_log_filename,
			'reg_value=i'  => \$testclock_reg_value );

# Attempt to use a running instance of QPST
my $qpst;

eval
{
  $qpst = Win32::OLE->GetActiveObject($prod_id)
};

die "$prod_id not installed" if $@;

# Start a new instance. Call Quit when $qpst set to undef or script exits.
unless (defined $qpst)
{
  $qpst = Win32::OLE->new($prod_id, sub {$_[0]->Quit;}) or die "Oops, cannot start $prod_id";
}

# Open a port
my $port = $qpst->GetPort($port_name);

if (!defined $port)
{
   # Release the automation server.
   undef $qpst;
   die "Can't open port $port_name.\n";
}

# Check that we can write the log file (also make sure file is empty).
# Don't want to spend a bunch of time running things and then lose the log.
if ($log_filename)
{
   open(LOGFILE, ">", $log_filename, ) || die "Can't open log file: $log_filename.\n";
   close(LOGFILE);
}

# If a PEC file is provided, the header file must be provided. 
# PDS Scripts don't need header files.
if ($apps_pec_filename || $modem_pec_filename || $lpass_pec_filename || $slpi_pec_filename) {
  if ($C_header_file_path) 
  {
     process_C_header($C_header_file_path);
  }
  else
  {
     die "Did you assign the C header file? (e.g pwrdb_diag.h)$!";
  }
}

#@enum_t=log_find_types();
# %enum_HoH=get_enum_hash(\@enum_t,\$from_elf_file,\$elf_file);

# is_enum_valid() can only be called after get_enum_hash after $enum_HoH_valid is determined
#if (is_enum_valid())
#{
   #add_fromelf_symbol(\%enum_HoH);
#}

my $script_apps  = '';
my $script_modem = '';
my $script_lpass = '';
my $script_slpi  = '';
my $status;
my $log_apps     = '';
my $log_modem    = '';
my $log_lpass    = '';
my $log_slpi     = '';

if ($apps_pec_filename)  { $script_apps  = build_script( $apps_pec_filename ); }
if ($modem_pec_filename) { $script_modem = build_script( $modem_pec_filename ); }
if ($lpass_pec_filename) { $script_lpass = build_script( $lpass_pec_filename ); }
if ($slpi_pec_filename)  { $script_slpi  = build_script( $slpi_pec_filename ); }
if ($modem_pds_filename) { $script_modem = read_pds( $modem_pds_filename ); }
if ($lpass_pds_filename) { $script_lpass = read_pds( $lpass_pds_filename ); }
if ($slpi_pds_filename)  { $script_slpi  = read_pds( $slpi_pds_filename ); }
if ($apps_pds_filename)  { $script_apps = read_pds( $apps_pds_filename ); }

## Reset
if ($script_modem)
{
  $status = send_pwrdb_diag_pkt_reset( $port, PWRDB_DIAG_PKT_MODEM_ID);
  print "reset: $status\n";
}
if ($script_apps)
{
  $status = send_pwrdb_diag_pkt_reset( $port, PWRDB_DIAG_PKT_APPS_ID);
  print "reset: $status\n";
}
if ($script_lpass)
{
  $status = send_pwrdb_diag_pkt_reset( $port, PWRDB_DIAG_PKT_LPASS_ID);
  print "reset: $status\n";
}
if ($script_slpi)
{
  $status = send_pwrdb_diag_pkt_reset( $port, PWRDB_DIAG_PKT_SLPI_ID);
  print "reset: $status\n";
}
## Send pwrdb event/command scripts
if ($script_modem)
{
  $status = send_pwrdb_diag_pkt_script( $port, $script_modem, PWRDB_DIAG_PKT_MODEM_ID );
  print "Send script: $status\n";
}
if ($script_apps)
{
  $status = send_pwrdb_diag_pkt_script( $port, $script_apps, PWRDB_DIAG_PKT_APPS_ID );
  print "script: $status\n";
}
if ($script_lpass)
{
  $status = send_pwrdb_diag_pkt_script( $port, $script_lpass, PWRDB_DIAG_PKT_LPASS_ID );
  print "script: $status\n";
}
if ($script_slpi)
{
  $status = send_pwrdb_diag_pkt_script( $port, $script_slpi, PWRDB_DIAG_PKT_SLPI_ID );
  print "script: $status\n";
}
## Send START
if ($script_modem)
{
  $status = send_pwrdb_diag_pkt_run ( $port, PWRDB_DIAG_PKT_MODEM_ID );
  print "Start script: $status\n";
}
if ($script_apps)
{
  $status = send_pwrdb_diag_pkt_run ( $port, PWRDB_DIAG_PKT_APPS_ID );
  print "script: $status\n";
}
if ($script_lpass)
{
  $status = send_pwrdb_diag_pkt_run ( $port, PWRDB_DIAG_PKT_LPASS_ID );
  print "script: $status\n";
}
if ($script_slpi)
{
  $status = send_pwrdb_diag_pkt_run ( $port, PWRDB_DIAG_PKT_SLPI_ID );
  print "script: $status\n";
}
## Send pwrdb testclock command
if ($testclock_reg_value)
{
  $status = send_pwrdb_diag_pkt_testclock( $port, $testclock_reg_value, PWRDB_DIAG_PKT_MODEM_ID );
  print "Send testclock: $status\n";
}

if ($delay)
{
   sleep( $delay );
}
else
{
  print "Press <ENTER> to issue STOP packet and gather logs.\n";
  <STDIN>;
}

## Send STOP
if ($script_modem)
{
  $status = send_pwrdb_diag_pkt_stop ( $port, PWRDB_DIAG_PKT_MODEM_ID );
  print "stop: $status\n";
}
if ($script_apps)
{
  $status = send_pwrdb_diag_pkt_stop ( $port, PWRDB_DIAG_PKT_APPS_ID );
  print "stop: $status\n";
}
if ($script_lpass)
{
  $status = send_pwrdb_diag_pkt_stop ( $port, PWRDB_DIAG_PKT_LPASS_ID );
  print "stop: $status\n";
}
if ($script_slpi)
{
  $status = send_pwrdb_diag_pkt_stop ( $port, PWRDB_DIAG_PKT_SLPI_ID );
  print "stop: $status\n";
}
sleep( 1 );

## Get logs
if ($script_modem)
{
  $log_modem = send_pwrdb_diag_pkt_log( $port, PWRDB_DIAG_PKT_MODEM_ID );
}


if ($script_apps)
{
  $log_apps = send_pwrdb_diag_pkt_log( $port, PWRDB_DIAG_PKT_APPS_ID );
}

if ($script_lpass)
{
  $log_lpass = send_pwrdb_diag_pkt_log( $port, PWRDB_DIAG_PKT_LPASS_ID );
}

if ($script_slpi)
{
  $log_slpi = send_pwrdb_diag_pkt_log( $port, PWRDB_DIAG_PKT_SLPI_ID );
}

## Print / Save logs
if ($log_modem)
{  
   print "\n\n--begin modem log--\n\n";
   if ($modem_log_filename) 
   {
      print_log( \%enum_HoH,\$log_modem, \$modem_log_filename );
   }
   else
   {
      print_log( \%enum_HoH,\$log_modem, \$log_filename );
   }
   print "\n--end modem log--\n";
}


if ($log_apps)
{
   print "\n\n--begin apps log--\n\n";
   if ($apps_log_filename)
   {
     print_log( \%enum_HoH,\$log_apps, \$apps_log_filename );
   }
   else
   {
     print_log( \%enum_HoH,\$log_apps, \$log_filename );
   }
   print "\n--end apps log--\n";
}

if ($log_lpass)
{
   print "\n\n--begin lpass log--\n\n";
   if ($lpass_log_filename)
   {
     print_log( \%enum_HoH,\$log_lpass, \$lpass_log_filename );
   }
   else
   {
     print_log( \%enum_HoH,\$log_lpass, \$log_filename );
   }
   print "\n--end lpass log--\n";
}

if ($log_slpi)
{
   print "\n\n--begin slpi log--\n\n";
   if ($slpi_log_filename)
   {
     print_log( \%enum_HoH,\$log_slpi, \$slpi_log_filename );
   }
   else
   {
     print_log( \%enum_HoH,\$log_slpi, \$log_filename );
   }
   print "\n--end slpi log--\n";
}

# Release the automation server.
undef $qpst;

print "\nDone!\n";
