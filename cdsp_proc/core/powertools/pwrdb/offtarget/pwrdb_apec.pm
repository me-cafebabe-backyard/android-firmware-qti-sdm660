############################################################################
#                            PWRDB_APEC 
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  This file contains the "advanced" stuff that can only be resolved 
#  by processing other files. For example, to include all the command files
#  and expand macros defined in those files.
# 
# EXTERNALIZED FUNCTIONS
#   
#  process_includes
#  process_macros
#  build_script
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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_apec.pm#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 08/29/13   rs        Added API for reading a PDS script
# 01/23/10   jl        Removed include files().
# 08/10/09   jl        Added error handling for no pec string input
# 07/30/09   jl/ck     Created this file
###############################################################################

use Win32::OLE;
use Win32::OLE::Variant;
use IO::File;

use strict;
use warnings;

#Debugging file
#my $FILE_EXPAND = IO::File->new("> pwrdb_cmd_all.pec") or die "Opening file: $!";

sub build_include_files 
{
   my $FILE_I = IO::File->new("$_[0]") or die "Opening file: $!";
   my $output_s;

   while (<$FILE_I>) 
   {
      if ($_ =~ /^\s*INCLUDE\s*"(.*)"/) 
      {
         print "Include file:$1\n";
         $output_s .= build_include_files ($1);
      }
      else 
      {
         $output_s .= $_;
      }
   }
   return $output_s;
}

###############################################################################
# pec_string process_includes( filename )
###############################################################################
# Find include files and read them in
# no include directives in output
sub process_includes 
{ 
  
   my $FILE_I = IO::File->new($_[0]) or die "Opening $_[0] failed: $!";
   my $s;
   while (<$FILE_I>) 
   {  
      #Replace comments with whitespace
      $_=~s/#.*//;

      #If this line contains non-space character
      if(/\S/x)
      { 
         my @cmd_list=split(/,/);
         my $inc_s;
         if($cmd_list[0]=~/\s*INCLUDE\s*"(.*)"/x)
         {  
            print "Include file:$1\n";
            $inc_s=build_include_files($1);
            #print $FILE_EXPAND $inc_s;
            $s.=$inc_s;         
         }
         #This line is comment line
         elsif($cmd_list[0]=~/\s*#\s*(.*)/)
         {
            #print $FILE_EXPAND "comment:$1\n"
         }
         else
         {  
            #print $FILE_EXPAND $_;
            $s.=$_;
         }
      }
      else
      {
         #print "white space line\n"
      }
   }
   return $s;
}

###############################################################################
# pec_string process_macros( pec_string )
###############################################################################
# process macro definitions and substitute references
# no macro definitions or references in output
sub process_macros 
{
   #input is a long string, manually seperate each line by "\n"
   my @cmd=split(/\n/,$_[0]);

   my $macro_begin=0;
   my @macro_AoH;        #array of hash
   my $macro_AoH_HoA_k;  #macro hash key
   my %macro_AoH_HoA=();
# Start building macro hash
   foreach(@cmd)
   {  
      if(/\S/x)
      {
         if($_=~/END_MACRO/)
         {
            $macro_begin=0;
            push @macro_AoH,{%macro_AoH_HoA};
         }
         elsif(($_=~/MACRO\s+(.+)/) && (!$macro_begin))
         {
            $macro_AoH_HoA_k=$1;
            $macro_begin=1;

         }
         elsif($macro_begin)
         {
            if($_=~/\s*#\s*(.*)/)
            {
               #if the comment is made within the macro definition, skip the line
            }
            else
            {
               push(@{$macro_AoH_HoA{$macro_AoH_HoA_k}},$_);
            }

         }
         elsif($_=~/\s*#\s*(.*)/)
         {
            #comment line, skip
         }
         else
         {
            #if not seeing macro, skip
            next;
         }

      }
      else
      {  #Right trim function to remove trailing whitespace
         $_=~s/^\s+//;
      }
   }

 # Start substituding references for the macro 
   $macro_begin=0;
   my $MACRO_REPLACE_FILE = IO::File->new("> pwrdb_macro_exp.pec") or die "Opening file: $!";
   my $pm_s;
   foreach (@cmd)
   {  
      #Replace comments with whitespace
      $_=~s/#.*//;

      #Right trim function to remove trailing whitespace
      $_=~s/\s+$//;

      #if this line contains non-space character
      if(/\S/x)
      { 
         my @cmd_list=split(/,/);
         my $inc_s;

         #MACRO defination has been taken cared of in subroutine:build_macro_hash
         #So skip these commands if seeing MACRO definition
         if($cmd_list[0]=~/END_MACRO/)
         {
            $macro_begin=0;
         }
         elsif(($cmd_list[0]=~/MACRO\s+(.+)/) && (!$macro_begin))
         {
            $macro_begin=1;
            #print "macro begins\n";

         }
         elsif($macro_begin)
         {
            next;
         }
         elsif($cmd_list[0]=~/\s*(PWRDB_.*)\s*/x)
         {
            $pm_s.=$_ . "\n";  #append the next line to the list
            print $MACRO_REPLACE_FILE $_ ."\n";

         }
         elsif($cmd_list[0]=~/\s*#\s*(.*)/)
         {
           #This line is comment line
         }
         elsif(exists $macro_AoH_HoA{$cmd_list[0]})
         {
            foreach (@{$macro_AoH_HoA{$cmd_list[0]}}) 
            {
               $pm_s.=$_ . "\n";
               print $MACRO_REPLACE_FILE $_ ."\n";
            }
         }
         else
         {  
            print "Your srcipt command:$_ is invalid.\n";
            print "Use one of the formats below. \n";
            print "1.To include other command files. Example:INCLUDE \"filename\"\n";
            print "2.To use single command. Example:PWRDB_XXX where XXX represents your PWRDB command."; 
            print "  (No space should be put before PWRDB)\n";
            print "3.To call the macro. Example:BL_ON (BL_ON is the macro name for backlight on)\n";
            print "4.To define a macro. \n";
            print "  Example:\n";
            print "  MACRO MACRO_NAME\n";
            print "  #put macro definitition, should contain a list of PWRDB commands\n";
            print "  END_MACRO\n";
            die "Invalid scripts command $!\n "            

         }
      }
      else
      {
         #This line is white space
      }
   }
   return $pm_s;
}


###############################################################################
# bin_string read_pds( filename )
###############################################################################
# returns: script as binary string
sub read_pds
{
   my $bin_s;
   my $input_pds_file = $_[0];
  open(my $fh, '<', $input_pds_file) or die "cannot open file $input_pds_file";
  {
    local $/;
    $bin_s = <$fh>;
  }
  close($fh);
  return $bin_s;
}

###############################################################################
# bin_string build_script( filename )
###############################################################################
# calls process_includes(), process_macros(), process_pec_string() to
# do whole process in one go
# returns: script as binary string
sub build_script
{
   my $pinc_pec_str;
   my $pm_pec_str;
   my $bin_s;

   $pinc_pec_str=process_includes($_[0]);
   $pm_pec_str=process_macros($pinc_pec_str);
   if($pm_pec_str)
   {
      $bin_s=process_pec_string($pm_pec_str);
   }
   else
   {
      print "No input pec string $! \n";
   }

   return $bin_s;
}
1
