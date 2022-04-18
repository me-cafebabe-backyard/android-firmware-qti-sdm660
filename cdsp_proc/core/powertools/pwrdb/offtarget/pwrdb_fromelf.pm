############################################################################
#                            PWRDB_PEC
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  This file contains the subroutines that will process pwrdb_diag.h or 
#  subroutines that will use the hash that is resolved by processing pwrdb_diag.h
# 
# EXTERNALIZED FUNCTIONS
# 
#  process_C_header
#  pc
#  add_symbol
#  process_pec_file (This has not been called in other modules yet)
#  process_pec_string
# 
# INITIALIZATION AND SEQUENCING REQUIREMENTS
# 
#   None
#   
# 
#   Copyright (c) 2009 by QUALCOMM, Incorporated.  All Rights Reserved.
#   
# 
###############################################################################
# 
#                       EDIT HISTORY FOR FILE
# 
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_fromelf.pm#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 10/28/10   jl        Added support to build the enum hash from a text file that 
#                      is generated using different compilers.
# 08/10/09   jl/sg     Added support for poke32 range command and string command
# 07/30/09   jl/ck     Created this file
###############################################################################

use Win32::OLE;
use Win32::OLE::Variant;

#package PWRDB_PEC;

use strict;
use warnings;

my %pwrdb_enum_types=();


sub find_enum_fromelf 
{
   my $FILE_I = IO::File->new($_[0]) or die "You tried to open $_[0]:$!";
   my $enum_begin=0;
   my $enum_type;
   my $temp_enum='';
   my $find_typedef=0;
   my $n=$#_+1;
   my @find_types=();
   my $compiler_version=0;
   my $pwrdb_enum_key;
   my $pwrdb_enum_value;
   my $pwrdb_type_key;
   my $pwrdb_type_value;

   for (my $i=1; $i<$n;$i++)
   {
      push (@find_types,$_[$i])
   }
   while (<$FILE_I>)
   {
     if($_=~/Compiler,\s*(.+)/)
     {
       $compiler_version=$1;
       print "Compiler:$compiler_version\n";
       last;
     }
   }
   while (<$FILE_I>)
   {
         # Reading lines betwen enumeration    
         if ($enum_begin==1) 
         {
            $temp_enum .= $_;
            if($_=~/DW_TAG_typedef/)
            {
               $find_typedef=1;
               next;
            }

            if($find_typedef==1)
            {
               if($_=~/DW_AT_name\s*(.+)/)
               {
                  $enum_begin=0;
                  $enum_type=$1;
                  $find_typedef=0;
                  #print "$enum_type\n";

                  foreach my $type(@find_types) 
                  {
                     #print "$type ";
                     if ($enum_type eq $type) 
                     {
                        # RVCT4.0 and RVCT2.0 are sharing the same function for now
                        if ($compiler_version =~/RVCT4./ ) 
                        {
                           build_enum_hash_rvct22($temp_enum,$type);
                        }
                        elsif ($compiler_version =~/RVCT2./) 
                        {  
                           build_enum_hash_rvct22($temp_enum,$type);
                        }
                        else
                        {
                           print "Warning: Compiler $compiler_version is not supported.";
                        }
                     }
                  }
                  
                  #print "end\n";
                  $temp_enum=();
               }
            }
         }
    
          if (/DW_TAG_enumeration_type/) 
          {
            $enum_begin=1;
            $temp_enum .= $_; #Need to pass the string that contains DW_TAG_enumeration_type as the first string so that
                              #build_enum_hash() can see this pattern and start building hash 
            next;
          }
    }
    
    return %pwrdb_enum_types;
}
sub build_enum_hash_rvct22 
{
   my @line=split(/\n/,$_[0]); #input is a long string, manually seperate each line by "\n"
   my %enum_type;
   my $pwrdb_enum_key=$_[1];
   my $enum_begin=0;
   my $find_name=0;
   my $enum_value_hex2dec;
   my $enum_name;

   #print "@line!!";
   foreach (@line)
   {  
      #print "$_\n";
      if ($enum_begin==1) 
      {  
         if($_=~/DW_AT_name\s*(.+)/)
         {
               $enum_name=$1;
               #print "$enum_name:";
               $find_name=1;
               next;
         }
         else
         {
            if($find_name==1)
            {
               $find_name=0;
               if(/DW_FORM_data1\s*0x(\w+)/)
               {
                  $enum_value_hex2dec=hex($1);
                  #$pwrdb_enum_types{$pwrdb_enum_key}{$enum_name}=$enum_value_hex2dec;
                  $pwrdb_enum_types{$pwrdb_enum_key}{$enum_value_hex2dec}=$enum_name;
               }
               elsif (/DW_FORM_data1\s*(\d+)/) 
               {

                  $pwrdb_enum_types{$pwrdb_enum_key}{$1}=$enum_name;
               }
             
               elsif(/DW_FORM_data4\s*0x(\w+)/)
               {
                  $enum_value_hex2dec=hex($1);
                  $pwrdb_enum_types{$pwrdb_enum_key}{$enum_value_hex2dec}=$enum_name;
               }
               elsif (/DW_FORM_data4\s*(\d+)/) 
               {
                  $pwrdb_enum_types{$pwrdb_enum_key}{$1}=$enum_name;
             
               }
               elsif(/DW_FORM_data2\s*0x(\w+)/)
               {
                  $enum_value_hex2dec=hex($1);
                  $pwrdb_enum_types{$pwrdb_enum_key}{$enum_value_hex2dec}=$enum_name;
               }
               elsif (/DW_FORM_data2\s*(\d+)/) 
               {
                  $pwrdb_enum_types{$pwrdb_enum_key}{$1}=$enum_name;
             
               } #Do that have DW_AT_const_value indirect DW_FORM_data3 though?
               elsif(/DW_FORM_data3\s*0x(\w+)/)
               {
                  $enum_value_hex2dec=hex($1);
                  $pwrdb_enum_types{$pwrdb_enum_key}{$enum_value_hex2dec}=$enum_name;
               }
               elsif (/DW_FORM_data3\s*(\d+)/) 
               {
                  $pwrdb_enum_types{$pwrdb_enum_key}{$1}=$enum_name;
               }
               #The following format for enum is added to cover compiler rcvt4.0 cases, but rvct4.0 will also have above elsif cases
               elsif(/DW_AT_const_value\s*0x(\w+)/)
               {
                  $enum_value_hex2dec=hex($1);
                  $pwrdb_enum_types{$pwrdb_enum_key}{$enum_value_hex2dec}=$enum_name;
               }
               elsif (/DW_AT_const_value\s*(\d+)/) 
               {
                  $pwrdb_enum_types{$pwrdb_enum_key}{$1}=$enum_name;
               }             
               #end rvct4.0 format match
               else
               {
                  next;
               }
            }
         }
      }
      if (/DW_TAG_enumeration_type/) 
      {
         $enum_begin=1;
         next;
      }
   } 
}

my $enum_HoH_valid=0;

sub get_enum_hash 
{
   my ($aref,$sref1,$sref2)=@_;
   my @et=@$aref;
   my $file_out=$$sref1;
   my $file_in=$$sref2;

   my %enum_HoH;

   # If pwrdb.txt file is not generated yet, process the .o file to generate the .txt file
   if (!(-e $file_out)) 
   {  
      print "Processing $file_in file ...\n";
      system("Fromelf --text -g $file_in > $file_out") ==0  or print "system 'Fromelf --text -g $file_in > $file_out' failed. Log will just show enum constans. ";
   }

   # Check if .txt file exist again
   if (-e $file_out)
   {
      if (@et)
      {
         %enum_HoH=find_enum_fromelf($file_out,@et);
         if (!keys %enum_HoH) 
         {  
            # Right now we only consider the case that processes pwrdb.o file. 
            # However, get_enum_hash cannot be used to process other .o files.
            # So the debug msg might not suitable for other situation.
            print "Warning:Failed to build enum hash, possible reasons are\n\n";
            print "1.$file_in does not exist.\n";
            print "2.$file_out exists but not valid.\n";
            print "3.Cannot find the types specified in %pwrdb_log_templates in pwrdb_log.pm\n\n";
            print "PWRDB is still running, but output log will just show enum constant instead of human readable text.\n";
            print "If you want to run again, please delete $file_out and make sure your pwrdb.o exists.\n";
            %enum_HoH=();
            $enum_HoH_valid=0;
         }
         else
         {  
            $enum_HoH_valid=1;
          }
      }
      else
      {
         # No enum types are selected to be printed in text format in logs
         %enum_HoH=();
         $enum_HoH_valid=0;
      }
   }
   else
   {
      %enum_HoH=();
      $enum_HoH_valid=0;
   } 
      return %enum_HoH;
}
# This can only be called after get_enum_hash after $enum_HoH_valid is changed
sub is_enum_valid 
{
   return $enum_HoH_valid;
}

1
