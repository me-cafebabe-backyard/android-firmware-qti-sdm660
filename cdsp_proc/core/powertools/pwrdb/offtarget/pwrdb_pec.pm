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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_pec.pm#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 04/01/10   jl        Added support for NPA commands
# 08/10/09   jl/sg     Added support for poke32 range command and string command
# 07/30/09   jl/ck     Created this file
###############################################################################

use Win32::OLE;
use Win32::OLE::Variant;

#package PWRDB_PEC;

use strict;
use warnings;

my %pwrdb_constant=();
my %pwrdb_cmd_format=();


###############################################################################
# process_C_header( filename )
###############################################################################
# Input:Usually pwrdb_diag.h
# Map the string to constant value and also the format for PACK command
sub process_C_header 
{
   my $FILE_I = IO::File->new($_[0]) or die "You tried to open $_[0]:$!";
   
   while (<$FILE_I>)
   {
      #Build constant hash, look for "#define PWRDB_XX hex_number (0xXXXX)"
      if (/^#define\s+(\bPWRDB.+?\b)\s.*?(\w+)/)
      {  
         my $hex2dec=undef;
         if ($2=~/^\D/) 
         {  #If the word begins with non-digit, then wrong. 
            #0x1234 and 1234 will work because the leading charater is a digit
            print " Format is #define PWRDB_XX hex_number (0xXXXX)!";
         }
         else
         {
            $hex2dec=hex($2);
            $pwrdb_constant{$1}=$hex2dec;
         }

      }
      #Build format hash 
      #When adding a new command, need to add the comment in the following format after "#" sign
      #/*<space>cmd:<command name><space>format:<format ID,a.k.a pack template><space>*/
      #Example :
      #/* cmd:PWRDB_CMD_POKE16_M format:vvVvv */
      elsif (/\/\*\s*cmd\s*:\s*(\w+)\s*format\s*:\s*(.+\S)\s*\*\//)
      {
         $pwrdb_cmd_format{$1}=$2;
      }
      else
      {
         #do nothing when no match string
      }

   }
   my $format_key;
   my $format_value;

   while (($format_key, $format_value) = each(%pwrdb_cmd_format))
   {  
      #check if the command format exists
      if (exists $pwrdb_constant{$format_key}) 
      {
         #Test next PWRDB_CMD_XXX
      }
      elsif ($format_key=~/\bPWRDB_CMD_HDR\b/) 
      {
         #If format key is PWRDB_CMD_HDR, don't print the error msg because this is not an error.
         #It is just the command header.
      }
      else
      {
         print "$format_key is not a hashkey for %pwrdb_constant \n";
      }  
   }
}


###############################################################################
# bin_string pc(  )
###############################################################################
# Building individual script commands (short for PWRDB_CMD)
sub pc
{
   my $cmd = shift(@_);            #command is treated as string
   my $t=$pwrdb_cmd_format{$cmd};  # get pack format from input command
   my $c=$pwrdb_constant{$cmd};    # convert command to constant 

   if (!$t) { die "Undefined template for $cmd. This command might not exist or the pack template is wrong.\n"; }
   my $l = length( pack( $t ) ); # length of command in bytes
   my $m = length( $t )-2; # number of fields in command (not counting id and len)
   my $n = scalar(@_);     # number of parameters we were passed
   my $i;
   my $numval;
   my $strlen;
   my $strmod; #string modulus
   my $strmod_i;

   if($cmd eq "PWRDB_CMD_POKE32_RANGE")
   {
      # Since reading the command as string, the numeric value needs to be extracted in case
      # the command is typed as PWRDB_CMD_POKE32_RANGE, 0x0F2E5890, 5, 0x11, 0x22, 0x33, 0x44, 0x99
      # where " 5" is not "5". Need to eliminate the white space.
      if ($_[1]=~/\s*\b(\d+)\b\s*/) 
      {
         $numval=$1; #number of values that are to be written into memory
      }
      elsif ($_[1]=~/\s*0x(\w+)\b\s*/)
      {
         $numval=hex($1); #convert hexidecimal value to decidmal value
      }
      else
      {
         print "Wrong number of values:\"$_[1]\"";
      }

      $m = $m -1 + ($numval -1); #extra -1 is due to "*" in template for POKE32_RANGE
      #we are counting here numval instead of (numval - 1) since, for a string like "vvVVV*", length(pack()) will give only size of
      #"vvVV", it wont give count for "V*"
      $l = $l + ($numval * length(pack("V")));   #Counting size of variable arguments along with size of command structure

   }
   
   if($cmd eq "PWRDB_CMD_DALSBI_READWRITE")
   {
      #Getting the count of Readwrite Structures are present in input arguments
      if ($_[1]=~/\s*\b(\d+)\b\s*/)
      {
         $numval=$1; #If given as decimal value
      }
      elsif ($_[1]=~/\s*0x(\w+)\b\s*/)
      {
         $numval=hex($1); #convert hexidecimal value to decidmal value
      }
      else
      {
         print "Wrong number of values:\"$_[1]\"";
      }

      $m = $m -1 + ($numval * 3 -1); #extra -1 is due to "*" in template for DALSBI_READWRITE
      #we are counting here numval instead of (numval - 1) since, for a string like "vvVVV*", length(pack()) will give only size of
      #"vvVV", it wont give count for "V*"
      $l = $l + ($numval * 3 * length(pack("V")));   #Counting size of variable arguments along with size of command structure
   }
   
   if($cmd eq "PWRDB_CMD_I2C_DEV_WRITE")
   {
      # Since reading the command as string, the numeric value needs to be extracted in case
      # the command is typed as PWRDB_CMD_POKE32_RANGE, 0x0F2E5890, 5, 0x11, 0x22, 0x33, 0x44, 0x99
      # where " 5" is not "5". Need to eliminate the white space.
      if ($_[3]=~/\s*\b(\d+)\b\s*/)
      {
         $numval=$1; #number of values that are to be written into memory
      }
      elsif ($_[3]=~/\s*0x(\w+)\b\s*/)
      {
         $numval=hex($1); #convert hexidecimal value to decidmal value
      }
      else
      {
         print "Wrong number of values:\"$_[3]\"";
      }

      $m = $m -1 + ($numval -1); #extra -1 is due to "*" in template for I2C_DEV_WRITE
      #we are counting here numval instead of (numval - 1) since, for a string like "vvVCvvC*", length(pack()) will give only size of
      #"vvVCvv", it wont give count for "C*"
      $l = $l + ($numval * length(pack("C")));   #Counting size of variable arguments along with size of command structure
   }
  
   if($cmd eq "PWRDB_CMD_STRING")
   {  
      $_[1] =~ s/\s+$//; #right trim of whitespace
      $_[1] =~ s/^\s+//; #left trim of whitespace

      if($_[1]=~/\s*\"(.*)\"\s*/)
      {
         $strlen=length($1);
         #chihning
         $strmod=$strlen % 4; # Changes for Q6 long word alighment. Needs to pad null charater
                              # to make sure when passing the strings struct, it is multiple of 4 bytes
      }
      else
      {
         print "Wrong string:$_[1]. Do you put double quote? Example:\"ABCDE\"\n";
      }

      $m = $m -2; #Given string will be counted as one argument only, removing count for "*" in template.        
                  #The struct of PWRDB_CMD_STRING includes the string length, but we don't want the user to 
                  #pass in the parameter manually, instead we just calculate here, so we need to remove the count
                  #for "v" of the string length in case PWRDB thinks that string command pass wrong number of params to pc
                  
      #we are counting here numchar instead of (numchar - 1) since, for a string like "vvCC*", length(pack()) will give only size of
      #"vvC", it wont give count for "C*"
      $l = $l + ($strlen * length(pack("C")))+ (4-$strmod);   #Counting size of variable arguments along with size of command structure
   }

   if($cmd eq "PWRDB_CMD_DATA3_STRING")
   {
      $_[4] =~ s/\s+$//; #right trim of whitespace
      $_[4] =~ s/^\s+//; #left trim of whitespace

      if($_[4]=~/\s*\"(.*)\"\s*/)
      {
         $strlen=length($1);
      }
      else
      {
         print "Wrong string:$_[4]. Do you put double quote? Example:\"ABCDE\"\n";
      }

      $m = $m -2; #Given string will be counted as one argument only, removing count for "*" in template.        
                  #The struct of PWRDB_CMD_STRING includes the string length, but we don't want the user to 
                  #pass in the parameter manually, instead we just calculate here, so we need to remove the count
                  #for "v" of the string length in case PWRDB thinks that string command pass wrong number of params to pc
                  
      #we are counting here numchar instead of (numchar - 1) since, for a string like "vvCC*", length(pack()) will give only size of
      #"vvC", it wont give count for "C*"
      $l = $l + ($strlen * length(pack("C")));   #Counting size of variable arguments along with size of command structure
   }
   
   if($cmd eq "PWRDB_CMD_CLK_SET_CLK_EN")
   {
      $_[1] =~ s/\s+$//; #right trim of whitespace
      $_[1] =~ s/^\s+//; #left trim of whitespace

      if($_[1]=~/\s*\"(.*)\"\s*/)
      {
         $strlen=length($1);
         print" starting string $1 \n";
         print "starting str length $strlen \n";
         #chihning
         $strmod=$strlen % 4; # Changes for Q6 long word alighment. Needs to pad null charater
                              # to make sure when passing the strings struct, it is multiple of 4 bytes
      }
      else
      {
         print "Wrong string:$_[1]. Do you put double quote? Example:\"ABCDE\"\n";
      }

      $m = $m -2; #Given string will be counted as one argument only, removing count for "*" in template.        
                  #The struct of PWRDB_CMD_STRING includes the string length, but we don't want the user to 
                  #pass in the parameter manually, instead we just calculate here, so we need to remove the count
                  #for "v" of the string length in case PWRDB thinks that string command pass wrong number of params to pc
                  
      #we are counting here numchar instead of (numchar - 1) since, for a string like "vvCC*", length(pack()) will give only size of
      #"vvC", it wont give count for "C*"
      $l = $l + ($strlen * length(pack("C")));   #Counting size of variable arguments along with size of command structure
      $l = ($l + (4-$strmod))if($strmod gt 0);
   }
   
    if( $cmd eq "PWRDB_CMD_CLK_GET_CLK_EN" || $cmd eq "PWRDB_CMD_CLK_GET_CLK_FREQ" )
   {
      $_[0] =~ s/\s+$//; #right trim of whitespace
      $_[0] =~ s/^\s+//; #left trim of whitespace

      if($_[0]=~/\s*\"(.*)\"\s*/)
      {
         #print "$_[0]";
         $strlen=length($1);
         print" starting string $1 \n";
         print "starting str length $strlen \n";
         #chihning
         $strmod=$strlen % 4; # Changes for Q6 long word alighment. Needs to pad null charater
                              # to make sure when passing the strings struct, it is multiple of 4 bytes
          print "starting mod $strmod \n";      
      }
      else
      {
         print "Wrong string:$_[0]. Do you put double quote? Example:\"ABCDE\"\n";
      }

      $m = $m -2; #Given string will be counted as one argument only, removing count for "*" in template.        
                  #The struct of PWRDB_CMD_STRING includes the string length, but we don't want the user to 
                  #pass in the parameter manually, instead we just calculate here, so we need to remove the count
                  #for "v" of the string length in case PWRDB thinks that string command pass wrong number of params to pc
                  
      #we are counting here numchar instead of (numchar - 1) since, for a string like "vvCC*", length(pack()) will give only size of
      #"vvC", it wont give count for "C*"
      $l = $l + ($strlen * length(pack("C")));   #Counting size of variable arguments along with size of command structure
      $l = ($l + (4-$strmod))if($strmod gt 0);
	 # $1 = $1.("/0" x (4-$strmod))if($strmod gt 0);
      #print" my computation $str \n ";
      #$str = ($str + (4-$strmod))if($strmod gt 0);
      #print"computed string is $1";
  }
   
   if($cmd eq "PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST" || $cmd eq "PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST" || $cmd eq "PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST"
       || $cmd eq "PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST" || $cmd eq "PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST" || $cmd eq "PWRDB_CMD_NPA_COMPLETE_REQUEST"
       || $cmd eq "PWRDB_CMD_NPA_QUERY_BY_NAME" )
   {
      my $npa_resource_str;
      if ($cmd eq "PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST" || $cmd eq "PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST") 
      {
        $npa_resource_str = $_[3];   
      }
      elsif ($cmd eq "PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST") 
      {
        $npa_resource_str = $_[2];   
      }
      elsif ($cmd eq "PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST") 
      {
        $npa_resource_str = $_[4];   
      }
      elsif ($cmd eq "PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST") 
      {
        $npa_resource_str = $_[3];   
      }
      elsif ($cmd eq "PWRDB_CMD_NPA_COMPLETE_REQUEST") 
      {
        $npa_resource_str = $_[2];   
      }
      elsif ($cmd eq "PWRDB_CMD_NPA_QUERY_BY_NAME" )
      {
        $npa_resource_str = $_[1];
      }
      $npa_resource_str =~ s/\s+$//; #right trim of whitespace
      $npa_resource_str =~ s/^\s+//; #left trim of whitespace
      if($npa_resource_str =~/\s*\"(.*)\"\s*/)
      {
         $strlen=length($1);
      }
      else
      {
         print "Wrong string:$npa_resource_str. Do you put double quote? Example:\"ABCDE\"\n";
      }

      $m = $m -2; #Given string will be counted as one argument only, removing count for "*" in template.        
                  #The struct of PWRDB_CMD_STRING includes the string length, but we don't want the user to 
                  #pass in the parameter manually, instead we just calculate here, so we need to remove the count
                  #for "v" of the string length in case PWRDB thinks that string command pass wrong number of params to pc
                  
      #we are counting here numchar instead of (numchar - 1) since, for a string like "vvCC*", length(pack()) will give only size of
      #"vvC", it wont give count for "C*"
      $l = $l + ($strlen * length(pack("C")));   #Counting size of variable arguments along with size of command structure
   }

   if ($m != $n) { die "Wrong number of params to pc(). Command: $cmd with $n params, expected $m.\n $!"; }

   my @tmp_arr;
   if($n)
   { 
      my $par_next;
      my $cmd_next;
      for (my $parameter_num=$n;$parameter_num>0;$parameter_num-- )  
      {
        
         $par_next = shift(@_);

         # Capture the command into $1, in case that he input command 
         # string has white space and could not be recognized
         if($par_next=~/\s*(PWRDB_.*)\s*/) 
         {  
            # Temporary solution to have an exception for the pwrdb_message_type 
            if ($1 =~/\s*(.*_MESSAGE)\s*/) 

            {
              if (exists $pwrdb_constant{$1})
              {
                $cmd_next=$pwrdb_constant{$1};
                push(@tmp_arr,$cmd_next);
              }
              else
              {
                print "The cammand you send:$cmd with parameter $1 is invalid.";
                print "Do you pass in the enum types to convert $1 to constant?";
                die   "Or you are missing pwrdb.txt file. $!";
              }
            }
            else
            {
              $cmd_next=$pwrdb_constant{$1};
              push(@tmp_arr,$cmd_next);
            }
         }
         elsif ($par_next=~/\s*\b(\d+)\b\s*/) #input parameter is a decimal number
         {
            push(@tmp_arr,$1);
         }
         elsif ($par_next=~/\s*0x(\w+)\b\s*/)
         {
            my $hex_tmp=hex($1);
            push(@tmp_arr,$hex_tmp);
         }         
         elsif ($cmd eq "PWRDB_CMD_STRING" 
                || $cmd eq "PWRDB_CMD_DATA3_STRING"
                || $cmd	eq "PWRDB_CMD_CLK_SET_CLK_EN"
                || $cmd eq "PWRDB_CMD_CLK_GET_CLK_EN"
                || $cmd eq "PWRDB_CMD_CLK_GET_CLK_FREQ") 
         {
            #PWRDB_CMD_STRING will pass string as input, and it doesn't have other contants parameters that need to be convert
            #from the hash table.
            if($par_next=~/\s*\"(.*)\"\s*/)
            {  
               $strmod = ($strlen%4);
               my $str = $1;
               $str .= ("\0"x(4-$strmod)) if ($strmod gt 0) ;
               # We don't want the user to manually pass the string length, so after calculate the string length 
               # in the previous step, don't forget to manually pass the paramter in case the pack doesn't 
               # match the pack format.
               $strlen = length($str);
               push(@tmp_arr,$strlen);
               push(@tmp_arr,$str);
            }
            }
         elsif (   $cmd eq "PWRDB_CMD_NPA_ISSUE_REQUIRED_REQUEST" 
                || $cmd eq "PWRDB_CMD_NPA_MODIFY_REQUIRED_REQUEST" 
                || $cmd eq "PWRDB_CMD_NPA_ISSUE_IMPULSE_REQUEST"
                || $cmd eq "PWRDB_CMD_NPA_ISSUE_ISOC_REQUEST" 
                || $cmd eq "PWRDB_CMD_NPA_ISSUE_LIMIT_MAX_REQUEST" 
                || $cmd eq "PWRDB_CMD_NPA_COMPLETE_REQUEST"
                || $cmd eq "PWRDB_CMD_NPA_QUERY_BY_NAME" ) 
         {  #PWRDB_CMD_NPA_XXXXX will pass "string" as input, and different from CMD_STRING, it also has other contant parameters that need to 
            #be converted from the hash table,i.e.,SYNC.
                     
            if($par_next=~/\s*\"(.*)\"\s*/)
            {  
               # We don't want the user to manually pass the string length, so after calculate the string length 
               # in the previous step, don't forget to manually pass the paramter in case the pack doesn't 
               # match the pack format.
               push(@tmp_arr,$strlen);
               push(@tmp_arr,$1);
            }
            elsif ($par_next=~/\s*(\w+)\s*/)
            {
              if (exists $pwrdb_constant{$1})
              {
                $cmd_next=$pwrdb_constant{$1};
                push(@tmp_arr,$cmd_next);
              }
              else
              {
                print "The cammand you send:$cmd with parameter $1 is invalid.";
                print "Do you pass in the enum types to convert $1 to constant?";
                die   "Or you are missing pwrdb.txt file. $!";
              }
            }
            else
            {
              print "The cammand you send:$cmd with parameter $1 is invalid.";
              die   "Or you are missing pwrdb.txt file. $!";
            }
          
         }
         # The parameter can be a symbol which extracts from the elf file (or .o file).
         # And these symbols are not beginning with PWRDB
         elsif($par_next=~/\s*(\w+)\s*/) 
         {  
            # Check if the constant for that enum exists, if not, shows error.
            if (exists $pwrdb_constant{$1})
            {
               $cmd_next=$pwrdb_constant{$1};
               push(@tmp_arr,$cmd_next);
            }
            else
            {
               print "The cammand you send:$cmd with parameter $1 is invalid.";
               print "Do you pass in the enum types to convert $1 to constant?";
               die   "Or you are missing pwrdb.txt file. $!";
            }

            
         }
         else
         {
           die "Invalid input paramter for $cmd $!\n";
         }
       
      }
   }
   else
   {
      @tmp_arr=@_; #no command parameter
   }
   return pack( $t, $c, $l, @tmp_arr );
}

###############################################################################
# add_symbol ( string, value )
###############################################################################
# Ability to add "symbols" (mapping of string to a hexidecimal numeric value)
# just add an entry in %pwrdb_constant
# Dependencies: Need to be called after process_C_header() in case of empty constant hash.
# Example : add_symbol("PWRDB_INT_EVT_ID_TEST_EVENT_A",3);
# Right now assusme only add the constants to PWRDB constants (So the string needs to begin
# with PWRDB_XXX in order to meet the requiremente of %pwrdb_constant, but this subroutine should
# apply for other constant assignment later on.
# 
sub add_symbol
{
   my $add_string=$_[0];
   my $add_value=$_[1];
   my $hex2dec=hex($add_value);  #add value needs to be hexidecimal value
   $pwrdb_constant{$add_string}=$hex2dec;

}

###############################################################################
# add_fromelf_symbol ( string, value )
###############################################################################
#
sub add_fromelf_symbol
{  
   my $add_href=$_[0];
   my %enum_HoH=%$add_href;
   my $enum_types_hkey;
   my $enum_types_hh;
   my %text2const;
   my $const_hvlaue;
   my $text_hkey;

   while ( ($enum_types_hkey, $enum_types_hh) = each %enum_HoH ) 
   {  
      # The key of the main hash of hash are different enum types.(e.g clkrgm_msm_clk_type)
      # Each enum type maps to another hash with constant as key, and text as value.
      # Now we also want to build a hash with text as key, and constant as value,
      # so we do a reverse, and then further added these symbols to %pwrdb_constant hash
      %text2const = reverse %{$enum_HoH{$enum_types_hkey}};

      while ( ($text_hkey, $const_hvlaue) = each %text2const ) 
      {    
           #Const_hvale is already decimal number, don't have to consider hex number case
           $pwrdb_constant{$text_hkey}=$const_hvlaue;
      }
         
   }
   

}

###############################################################################
# bin_string process_pec_file ( filename )
###############################################################################
# Created for AST team. Do not plan to use INCLUDE MACRO, then directly call process_pec_file.
# However, each line should use PWRDB_command format.Can have blank lines, comments
# Dependencies: Need to be called after process_C_header() in case of empty constant hash.
#               add_symbol can be called after process_C_header() and before process_pec_file if needed 
sub process_pec_file
{
   my $FILE_I = IO::File->new($_[0]) or die "Opening file: $!";
   my $ppf_s;
   while (<$FILE_I>)
   {  
      $_=~s/#.*//;    #Replace comments with whitespace
      $_ =~ s/\s+$//; #Right trim function to remove trailing whitespace
      
      #if this line contains non-space character
      if(/\S/x)
      { 
         my @cmd_list=split(/,/);

         if($cmd_list[0]=~/\s*(PWRDB_.*)\s*/x)
         {
            #Command list starts with PWRDB_CMD_XXX
            $ppf_s.=pc(@cmd_list);

         }
         elsif($cmd_list[0]=~/\s*#\s*(.*)/)
         {
             #This line is comment line
         }
         else
         {
            print "Your srcipt command:$_ is invalid\n";
            print "Each line should use the following formats:\n";
            print "PWRDB_XXX where XXX represents your PWRDB command\n";
            print "Example:PWRDB_CMD_START_TIMER, 1000, 2, 0, 1\n";
            die "Invalid scripts command $!\n "
         }
      }
      else
      {
         #This line is whitespace line
      }
   }
   return $ppf_s;
}


###############################################################################
# bin_string process_pec_string( pec_string )
###############################################################################
# Input:pec command string, and sent to pc()
# Output:binary string
# no blank lines, no comments
sub  process_pec_string
{
   my $pc_s;
   my $macro_begin=0;
   my @cmd_line=split(/\n/,$_[0]); #input is a long string, manually seperate each line by "\n"

   foreach (@cmd_line)
   {  
      $_=~s/#.*//;  #Replace comments with whitespace
      $_=~s/\s+$//; #Right trim function to remove trailing whitespace
      
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

         }
         elsif($macro_begin)
         {
            next;
         }
         elsif($cmd_list[0]=~/\s*(PWRDB_.*)\s*/x)
         {
            #Command list starts with PWRDB_CMD_XXX
            $pc_s.=pc(@cmd_list);
            
         }
         elsif($cmd_list[0]=~/\s*#\s*(.*)/)
         {
            #This line is comment line
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
        #This line is whitespace line
      }
   }
   return $pc_s;

}
1
