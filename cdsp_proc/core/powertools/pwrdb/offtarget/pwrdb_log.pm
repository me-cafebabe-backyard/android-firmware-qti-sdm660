############################################################################
#                            PWRDB_LOG 
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  S U P P O R T   F O R   P W R D B   L O G   P R O C E S S I N G
#   
# EXTERNALIZED FUNCTIONS
#  check_templates
#  fixup_log_item
#  print_log
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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_log.pm#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 10/28/10   jl        Fixed the error when enum hash was not built.
# 05/17/10   jl        Added NPA query by name command.
# 03/10/10   jl        Added NPA support and update gpio logs.
# 01/25/10   jl        Added extended sleep voting support
# 10/19/19   jl        Added DALSBI read command
# 08/10/09   jl/sg     Added support for PEEK32_RANGE command and string command
#                      Added support for various log enum.
# 07/30/09   jl/ck     Created this file
###############################################################################

use strict;
use warnings;

# IDs for log items
use constant PWRDB_LOG_NULL                  => 0x0000;
use constant PWRDB_LOG_EVENT                 => 0x0001;

use constant PWRDB_LOG_TLMM_GET_CURR_CONFIG  => 0x0101;
use constant PWRDB_LOG_TLMM_GET_INACT_CONFIG => 0x0103;
use constant PWRDB_LOG_TLMM_INPUT            => 0x0105;
use constant PWRDB_LOG_TLMM_GET_PIN_STATUS   => 0x0107;
use constant PWRDB_LOG_TLMM_IS_LOCKED        => 0x010A;

use constant PWRDB_LOG_SBI_READ              => 0x0121;
use constant PWRDB_LOG_DALSBI_READ           => 0x0123;
use constant PWRDB_LOG_DALSBI_READWRITE      => 0x0124;

use constant PWRDB_LOG_I2C_DEV_READ          => 0x0132;

use constant PWRDB_LOG_CLK_GET_CLK_EN        => 0x0141;
use constant PWRDB_LOG_CLK_GET_CLK_FREQ      => 0x0143;
use constant PWRDB_LOG_CLK_GET_PLL_EN        => 0x0145;

use constant PWRDB_LOG_PEEK8                 => 0x0150;
use constant PWRDB_LOG_PEEK16                => 0x0151;
use constant PWRDB_LOG_PEEK32                => 0x0152;
use constant PWRDB_LOG_PEEK32_RANGE          => 0x0153;

use constant PWRDB_LOG_STRING                => 0x0160;
use constant PWRDB_LOG_DATA3_STRING          => 0x0161;
# This doesn't really log msg, it's just added so that 
# we can input text format for the resources in .pec file
use constant PWRDB_LOG_EXTENDED_SLEEP_VOTE   => 0x0171;

use constant PWRDB_LOG_NPA_ISSUE_REQUIRED_REQUEST   =>0x0180;
use constant PWRDB_LOG_NPA_MODIFY_REQUIRED_REQUEST  =>0x0181;
use constant PWRDB_LOG_NPA_ISSUE_IMPULSE_REQUEST    =>0x0182;
use constant PWRDB_LOG_NPA_ISSUE_ISOC_REQUEST       =>0x0183;
use constant PWRDB_LOG_NPA_ISSUE_LIMIT_MAX_REQUEST  =>0x0184;
use constant PWRDB_LOG_NPA_COMPLETE_REQUEST         =>0x0185;
use constant PWRDB_LOG_NPA_QUERY_BY_NAME            =>0x0186;

our $MSM_NUM_OF_GPIOS = 64;
# Question: I cannot find the typedef in DDITlmnm.h, do not how where these types come from?
# For other gpio types that were defined here, such as gpio direction, pull, and drive, I can find them
# from DDITlmm.h
our @gpio_func_type = (
  "PRIM_FUNC ",
  "ALT_FUNC_1",
  "ALT_FUNC_2",
  "ALT_FUNC_3",
  "ALT_FUNC_4",
  "ALT_FUNC_5"
);


our @message_type = (
  "INFORMATION",
  "ERROR  ",
  "WARNING"
);

our %pwrdb_log_templates = (
                           PWRDB_LOG_EVENT,                  ["EVENT",           "vvVVVVV",    ["id", "len", "time", "src", "id", "rsvd1", "rsvd2"], ["sleep_event"]],

                           PWRDB_LOG_TLMM_GET_CURR_CONFIG,   ["TLMM_CURR_CFG",   "vvVvCCCCCC", ["id", "len", "time", "gpio", "func", 
                                                                                                "dir", "pull", "drv", "outval", "status"],
                                                                                               ["DALGpioDirectionType","DALGpioPullType", "DALGpioDriveType"]],
                           PWRDB_LOG_TLMM_INPUT,             ["TLMM_IN",         "vvVvv",      ["id", "len", "time", "gpio", "inval"], []],
                           PWRDB_LOG_TLMM_GET_PIN_STATUS,    ["TLMM_PIN_ST",     "vvVvv",      ["id", "len", "time", "gpio", "status"], []],
                           PWRDB_LOG_TLMM_IS_LOCKED,         ["TLMM_LOCKED",     "vvVvv",      ["id", "len", "time", "gpio", "lock"], []],
                           
                           PWRDB_LOG_SBI_READ,               ["SBI_READ",        "vvVvCC",     ["id", "len", "time", "slave", "addr", "val"], []],
                           PWRDB_LOG_DALSBI_READ,            ["DALSBI_READ",     "vvVVVV",     ["id", "len", "time", "daldevice", "addr", "val"], []],
                           
                           PWRDB_LOG_I2C_DEV_READ,           ["I2C_READ",        "vvVVvvCC*",  ["id", "len", "time", "Device ID", "reg_mem_addr", "len", "Slave Addr", "data" ], []],
                           PWRDB_LOG_DALSBI_READWRITE,       ["DALSBI_RW",       "vvVVVV*",    ["id", "len", "time", "Device ID", "num_reads", "data"], []],

                           PWRDB_LOG_CLK_GET_CLK_EN,         ["CLK_EN",          "vvVva*",      ["id", "len", "time","en","clk"], []],
                           PWRDB_LOG_CLK_GET_CLK_FREQ,       ["CLK_FREQ",        "vvVva*",      ["id", "len", "time","freq","clk"], []],
                           PWRDB_LOG_CLK_GET_PLL_EN,         ["CLK_PLL_EN",      "vvVVV",      ["id", "len", "time", "pll", "en"], []],

                           PWRDB_LOG_PEEK8,                  ["PEEK8",           "vvVVVV",     ["id", "len", "time", "addr", "phys addr", "val"], []],
                           PWRDB_LOG_PEEK16,                 ["PEEK16",          "vvVVVV",     ["id", "len", "time", "addr", "phys addr", "val"], []],
                           PWRDB_LOG_PEEK32,                 ["PEEK32",          "vvVVVV",     ["id", "len", "time", "addr", "phys addr", "val"], []],
             # "*" is required here since we dont know before hand how many values we will be reading, 
             #"V*" will unpack all next coming values in "V" bytes until end of the string given to unpack function
                           PWRDB_LOG_PEEK32_RANGE,           ["PEEK32_RANGE",    "vvVVVVV*",   ["id", "len", "time", "addr", "phys addr", "numval", "values"], []],
                           PWRDB_LOG_STRING,                 ["STRING",          "vvVVva*",    ["id","len","time","Str_Type", "Str_Len", "String"], ["pwrdb_message_type"]],
                           PWRDB_LOG_DATA3_STRING,           ["STRING",          "vvVVVVVva*",      ["id","len","time","Str_Type","data1","data2","data3","Str_Len", "String"], ["pwrdb_message_type"]],
                           PWRDB_LOG_EXTENDED_SLEEP_VOTE,    ["EXT SLEEP VOTE",  "vvV",       ["id","len","time"], ["sleep_resources_type"]],
                           PWRDB_LOG_NPA_ISSUE_REQUIRED_REQUEST,   ["NPA ISSUE REQUIRED",   "vvV", ["id","len","time"], ["pwrdb_npa_client_sync_type"]],
                           PWRDB_LOG_NPA_MODIFY_REQUIRED_REQUEST,  ["NPA MODIFY REQUIRED",  "vvV", ["id","len","time"], ["pwrdb_npa_client_sync_type"]],
                           PWRDB_LOG_NPA_ISSUE_IMPULSE_REQUEST,    ["NPA ISSUE IMPULSE",    "vvV", ["id","len","time"], ["pwrdb_npa_client_sync_type"]],
                           PWRDB_LOG_NPA_ISSUE_ISOC_REQUEST,       ["NPA ISSUE ISOC",       "vvV", ["id","len","time"], ["pwrdb_npa_client_sync_type"]],
                           PWRDB_LOG_NPA_ISSUE_LIMIT_MAX_REQUEST,  ["NPA ISSUE LIMIT MAX",  "vvV", ["id","len","time"], ["pwrdb_npa_client_sync_type"]],
                           PWRDB_LOG_NPA_COMPLETE_REQUEST,         ["NPA COMPLETE",         "vvV", ["id","len","time"], ["pwrdb_npa_client_sync_type"]],
                           PWRDB_LOG_NPA_QUERY_BY_NAME,            ["NPA QUERY",         "vvVVVVVva*", ["id","len","time","qid","hdl","type","state","srclen", "src"], 
                                                                                                      ["npa_query_type_enum"]],
                           );


# check templates
sub check_templates
{
   my ($tp1, $tp);
   
   foreach my $k ( keys(%pwrdb_log_templates) )
   {
      if( scalar(@{$pwrdb_log_templates{$k}}) != 4 )
      {
         die "Bad template for log item $pwrdb_log_templates{$k}[0].\n";
      }

      # Checking if a template string has "*" atlast and removing it to check how many tags are present
      $tp = $tp1 = $pwrdb_log_templates{$k}[1];
      if(chop($tp1) eq '*')
      {
         $tp = $tp1;
      }   
      
      if ( scalar(@{$pwrdb_log_templates{$k}[2]}) != length($tp) )
      {
         die "Template does not match tags for log item $pwrdb_log_templates{$k}[0].\n";
      }

      
   }

   return(1);
}
# Find all the types that we want to read it as human readable text in the logs.
# These types are currently hard coded %pwrdb_log_templates
sub log_find_types
{  
   my @type;
   my $type_exists=0;
   foreach my $k ( keys(%pwrdb_log_templates) )
   {
      my @types_of_each_template=@{$pwrdb_log_templates{$k}[3]};
      
      if (@types_of_each_template)
      {  
         my $num=scalar( @types_of_each_template);
         for(my $i=0; $i<$num;$i++ )
         {  
            my $t=shift (@types_of_each_template);
            # Check if this type is already put on the @type
            for(my $j=0; $j<scalar(@type);$j++ )
            {
               if ($t eq $type[$j]) 
               {
                   $type_exists=1;
               }
            }
            if (!$type_exists) 
            {
               push (@type,$t);
            }
            $type_exists=0;
         }
         
      }
   }
   return @type;
}

###############################################################################
# Parsing logs
###############################################################################

# FIXUP_LOG_ITEM
# parameters: @_ - array of parameters extracted from item
#
# This function is intended to offer a chance to substitute values in a log
# item with more human readable alternatives. For example enums may be
# convverted from a number to a string representing the name of the particular
# value.
#
sub fixup_log_item
{
   my ($href,$aref)=@_;
   my %enum_types=%$href;
   my @log=@$aref;
   my $i;
   
   # time
#   $_[2] = sprintf("%.3f", $_[2]/32768);
   $log[2] = sprintf("%u", $log[2]);

   # PWRDB_LOG_CLK_GET_CLK_EN
  # if ($log[0] == PWRDB_LOG_CLK_GET_CLK_EN)
  # {  #Check if text enum hash exists, if not, just print numbers
  #    if (defined $enum_types{clkrgm_msm_clk_type})
  #    {
  #       $log[3]=$enum_types{clkrgm_msm_clk_type}{$log[3]};
  #    }
  # }
   # PWRDB_LOG_CLK_GET_CLK_FREQ
  # elsif ($log[0] == PWRDB_LOG_CLK_GET_CLK_FREQ)
  # {  
  #    if (defined $enum_types{clkrgm_msm_clk_type})
  #    {
  #       $log[3]=$enum_types{clkrgm_msm_clk_type}{$log[3]};
  #    }      
  # }
   # PWRDB_SBI_READ
   if ($log[0] == PWRDB_LOG_SBI_READ    ||
          $log[0] == PWRDB_LOG_DALSBI_READ )
   {
      $log[3] = sprintf("0x%lx", $log[3]);
      $log[4] = sprintf("0x%lx", $log[4]);
      $log[5] = sprintf("0x%lx", $log[5]);
   }
   elsif ($log[0] == PWRDB_LOG_DALSBI_READWRITE)
   {
      $log[3] = sprintf("0x%lx", $log[3]);
   }
   elsif ($log[0] == PWRDB_LOG_I2C_DEV_READ)
   {
       $log[3] = sprintf("0x%lx", $log[3]);
       $log[4] = sprintf("0x%lx", $log[4]);
       $log[5] = sprintf("0x%lx", $log[5]);
       for ($i = 0; $i < $log[6]; $i++)
       {
         $log[$i+7] = sprintf("0x%lx", $log[$i+7]);
       }
   }
  
   # PWRDB_LOG_PEEK8, PWRDB_LOG_PEEK16, PWRDB_LOG_PEEK32
   elsif ($log[0] == PWRDB_LOG_PEEK8  ||
          $log[0] == PWRDB_LOG_PEEK16 ||
          $log[0] == PWRDB_LOG_PEEK32 )
   {
      $log[3] = sprintf("0x%lx", $log[3]);
      $log[4] = sprintf("0x%lx", $log[4]);
      $log[5] = sprintf("0x%lx", $log[5]);
   }
    # PWRDB_LOG_PEEK32_RANGE
   elsif ($log[0] == PWRDB_LOG_PEEK32_RANGE )
   {
      for ($i = 0; $i < $log[5]; $i++)
      {
         $log[$i+6] = sprintf("0x%lx", $log[$i+6]);
      }
   }
   # PWRDB_LOG_TLMM_GET_CURR_CONFIG
   elsif ($log[0] == PWRDB_LOG_TLMM_GET_CURR_CONFIG)
   {
      if (defined $enum_types{DALGpioDirectionType})
      {
        $log[5] = $enum_types{DALGpioDirectionType}{$log[5]};
      }
      if (defined $enum_types{DALGpioPullType})
      {
        $log[6] = $enum_types{DALGpioPullType}{$log[6]};
      }      
      if (defined $enum_types{DALGpioDriveType})
      {
        $log[7] = $enum_types{DALGpioDriveType}{$log[7]};
      }
      #$log[8] = $enum_types{DALGpioValueType}{$log[8]};
   }
   # PWRDB_LOG_TLMM_GET_INACT_CONFIG
   elsif ($log[0] == PWRDB_LOG_TLMM_GET_INACT_CONFIG)
   {      
      $log[4] = sprintf("0x%lx", $log[4]);
      if (defined $enum_types{DALGpioDirectionType})
      {
        $log[5] = $enum_types{DALGpioDirectionType}{$log[5]};
      }
      if (defined $enum_types{DALGpioPullType})
      {
        $log[6] = $enum_types{DALGpioPullType}{$log[6]};
      }    
      if (defined $enum_types{DALGpioDriveType})
      {
        $log[7] = $enum_types{DALGpioDriveType}{$log[7]};
      }
      #$log[8] = $enum_types{DALGpioValueType}{$log[8]};
   }
   elsif ($log[0] == PWRDB_LOG_STRING)
   {
      #$_[3] = $COMMON::message_type[$_[3]];
   }
   elsif ($log[0] == PWRDB_LOG_DATA3_STRING)
   {
      #$_[3] = $COMMON::message_type[$_[3]];
      $log[4] = sprintf("0x%lx", $log[4]);
      $log[5] = sprintf("0x%lx", $log[5]);
      $log[6] = sprintf("0x%lx", $log[6]);
   }
   elsif ($log[0] == PWRDB_LOG_NPA_QUERY_BY_NAME)
   {
      $log[4] = sprintf("0x%lx", $log[4]);
      if (defined $enum_types{npa_query_type_enum})
      {
        $log[5] = $enum_types{npa_query_type_enum}{$log[5]};
      }
   }
   return @log;
 
}

# PRINT_LOG
# parameters: $log
sub print_log
{
   my ($href,$sref1,$sref2)=@_;
   #my $log = $_[0];
   #my $filename = $_[1];
   my $log = $$sref1;
   my $filename = $$sref2;
   my %types_enum = %$href;

   my $temp_log;
   my ($item, $len);
   my ($tp, @tags, $name);
   my (@data, @temp_data);
   my $i;
   my ($id, $time, $addr, $numval, $val, $len1);
   my @vals=();
#   my *LOGFILE;

   if ($filename)
   {
      open(LOGFILE, ">>", $filename, ) || die "Can't open log file.\n";
      print "writing log to $filename\n";
      select( LOGFILE );
   }

   while ($log)
   {
      ($item, $len) = unpack( "vv", $log );

      $name = $pwrdb_log_templates{$item}[0];
      $tp   = $pwrdb_log_templates{$item}[1];
      @tags = @{$pwrdb_log_templates{$item}[2]};

      if ($name)
      { 
         # check length
         if(   $item != PWRDB_LOG_PEEK32_RANGE && $item != PWRDB_LOG_STRING && $item != PWRDB_LOG_I2C_DEV_READ 
            && $item != PWRDB_LOG_DALSBI_READWRITE && $item != PWRDB_LOG_DATA3_STRING && $item != PWRDB_LOG_NPA_QUERY_BY_NAME  
	    && $item != PWRDB_LOG_CLK_GET_CLK_EN && $item != PWRDB_LOG_CLK_GET_CLK_FREQ)
         {
            if ($len != length( pack($tp) ))
            {
                die "Packet length different than expected for $item.\n";
            }
         }

         # go ahead and unpack
         #copying only current packet to temporary log variable
         $temp_log = substr($log, 0, $len);
         @temp_data = unpack( $tp, $temp_log );
         @data=fixup_log_item( \%types_enum,\@temp_data );

         # print time and log_id without tags (ignore len)
         print "$data[2] $name";
         if($item == PWRDB_LOG_PEEK32_RANGE)
         {  #Printing Peek32 log with formatting
            printf (" MemoryStartAddress : 0x%x, Physical address : 0x%x Number of values to be read:$data[5]\n", $data[3], $data[4]);
            printf("\t\tADDRESS      :\tVALUE\n");
            for($i = 0; $i<$data[5]; $i++)
            {   #Printing memory values in a readable format
                printf("\t\t[0x%x] :\t $data[($i + 6)]\n",($data[3]+(($i)*4)));
            }
         }
         elsif ($item == PWRDB_LOG_DALSBI_READWRITE)
         { #"vvVVVV*",  ["id", "len", "time", "device ID",  "num_trans", "data"]],
           print " Device ID: $data[3], Num_Reads: $data[4]";
           printf("\n\t\tADDRESS :VALUE\n");
           for($i = 0; $i < $data[4]; $i++)
           {   #Printing memory values in a readable format
              printf("\t\t[0x%x] : 0x%x\n", $data[5 + $i * 3 + 1], $data[5 + $i * 3 + 2]);
           }
         }
         elsif ($item == PWRDB_LOG_I2C_DEV_READ)
         { #"vvVVCvvC*",  ["id", "len", "time", "device ID",  "Slave Addr",  "reg_mem_addr", "len", "data"]],
             for ($i = 3; $i < 7; $i++)
             {
                print " $tags[$i]=$data[$i]";
             }
             printf("\n\t\tADDRESS \t:\tVALUE\n");
             for($i = 0; $i<$data[6]; $i++)
             {   #Printing memory values in a readable format
                printf("\t\t[0x%x] \t:\t $data[($i + 7)]\n",(hex($data[5])+$i));
             }
         }
         elsif ($item == PWRDB_LOG_STRING)
         {
             print " $data[3] : $data[5]\n";
         }
         elsif ($item == PWRDB_LOG_DATA3_STRING)
         {
             print " $data[3] : $data[8]\(related to data1 = $data[4], data2 = $data[5], data3 = $data[6]\)\n";
         }
         elsif ($item == PWRDB_LOG_NPA_QUERY_BY_NAME)
         {  
            print("\trsc:$data[8]\tqid:$data[3]\thdl:$data[4]\tresult:$data[5] = $data[6] \n");
         }
         elsif ($item == PWRDB_LOG_CLK_GET_CLK_EN)
         {  
            print("\t $data[4] : $data[3] \n");
         }	 
         elsif ($item == PWRDB_LOG_CLK_GET_CLK_FREQ)
         {  
            print("\t $data[4] : $data[3] \n");
         }	 
         else
         {
            for ($i=3; $i<scalar(@tags); $i++)
            {
                print " $tags[$i]=$data[$i]";
            }
                print "\n";
         }
      }
      else
      {
         print "Unrecognized log item: $item (length $len).\n";
      }

      # remove this item from the log and carry on
      $log = substr( $log, $len );
   }

   select( STDOUT );
}

###############################################################################
# Module Initialization
###############################################################################
check_templates();

