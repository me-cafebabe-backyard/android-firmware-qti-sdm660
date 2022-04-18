############################################################################
#                            PWRDB_DIAG
#                      
# DESCRIPTION
#
# GENERAL DESCRIPTION
#
#  This file contains the helper subs to allow communication to PWRDB via diag
#   
# EXTERNALIZED FUNCTIONS
# 
#  send_generic_pkt
#  send_pwrdb_diag_pkt_ver
#  send_pwrdb_diag_pkt_reset
#  send_pwrdb_diag_pkt_script
#  send_pwrdb_diag_pkt_log
#  send_pwrdb_diag_pkt_run
#  send_pwrdb_diag_pkt_stop
#  send_pwrdb_diag_pkt_test_event
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
# $Header: //components/rel/core.qdsp6/1.0.c2/powertools/pwrdb/offtarget/pwrdb_diag.pm#1 $
# 
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 08/10/09   jl/sg     Changed max diag packet size
# 07/30/09   jl/ck     Created this file
###############################################################################

use Win32::OLE;
use Win32::OLE::Variant;

use strict;
use warnings;

###############################################################################
# Constants
###############################################################################

## ------------------------------------------------------------------------
## Diag Packet Processor IDs
##
##  In multi-processor systems there may be pwrdb tasks running on more
##  than one processor. The processor ID is ORed with the commands below
##  to create a unique command code that identifies the processor that the
## command is intended for.
##
##  Diag defines a command as 32 bits. We used the top 4 bits for the ID
##  and the remianing bits for the actual command.
## ------------------------------------------------------------------------
use constant PWRDB_DIAG_PKT_MODEM_ID         => 0x0000;
use constant PWRDB_DIAG_PKT_APPS_ID          => 0x1000;
use constant PWRDB_DIAG_PKT_LPASS_ID         => 0x2000;
##
# Diag constants
use constant DIAG_SUBSYS_CMD_F               => 75;
use constant DIAG_SUBSYS_PWRDB               => 70;

# Diag packet IDs
use constant PWRDB_DIAG_PKT_VER              => 0x0000;
use constant PWRDB_DIAG_PKT_RESET            => 0x0001;
use constant PWRDB_DIAG_PKT_SCRIPT           => 0x0002;
use constant PWRDB_DIAG_PKT_LOG              => 0x0003;
use constant PWRDB_DIAG_PKT_LOG_TO_FS        => 0x0004;
use constant PWRDB_DIAG_PKT_RUN              => 0x0005;
use constant PWRDB_DIAG_PKT_STOP             => 0x0006;
use constant PWRDB_DIAG_PKT_TEST_EVENT       => 0x0007;
use constant PWRDB_DIAG_PKT_READ_FILE        => 0x0008;
use constant PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO  => 0x0009;

# Generic defines for status values in response packets
use constant PWRDB_RSP_SUCCESS               => 0;
use constant PWRDB_RSP_ERROR                 => 1;
use constant PWRDB_RSP_OK_PARTIAL            => 2;

# Time out for QPST commands
my $timeout_in_ms = 5000;

###############################################################################
# Sending / receiving diag packets
###############################################################################

# send_generic_pkt
# parameters: port, pkt id
# returns: status from response pkt, -1 if error
sub send_generic_pkt
{
  my $p   = $_[0];
  my $pkt = $_[1];

  my $diag_cmd = pack("CCS", DIAG_SUBSYS_CMD_F, DIAG_SUBSYS_PWRDB, $pkt );

  my $diag_request_var = Variant(VT_ARRAY | VT_UI1, length $diag_cmd);
  $diag_request_var->Put($diag_cmd);
   
  my $reply = $p->SendCommand($diag_request_var, $timeout_in_ms);

  if (defined $reply)
  {
     # use the unpack command to turn $reply into an list of
     # fields using $unpack_mask
#orig     my ($pkt, $ss, $cmd, $rsp) = unpack("CCSV", $reply);
     my ($pkt, $rsp) = unpack("VV", $reply);

     return $rsp;
  }
  else
  {
     print "No reply to pwrdb_diag_pkt_XXX $pkt\n";
     return -1;
  }
}

# SEND_PWRDB_DIAG_PKT_VER
# parameters: $port
# returns: version as string
sub send_pwrdb_diag_pkt_ver
{
   my $p = $_[0];
   my $processor_select = $_[1];

   my $diag_cmd = pack("CCS", DIAG_SUBSYS_CMD_F, DIAG_SUBSYS_PWRDB, (PWRDB_DIAG_PKT_VER | $processor_select) );

   my $diag_request_var = Variant(VT_ARRAY | VT_UI1, length $diag_cmd);
   $diag_request_var->Put($diag_cmd);

   my $reply = $p->SendCommand($diag_request_var, $timeout_in_ms);

   if (defined $reply)
   {
      # use the unpack command to turn $reply into an list of
      # fields using $unpack_mask
      my ($pkt, $ss, $cmd, $major, $minor, $msm) = unpack("CCSvvV", $reply);

      my $s = "Major: $major. Minor: $minor. HW ID: $msm.";
      return $s;
   }
   else
   {
      print "No reply to pwrdb_diag_pkt_script.\n";
      return -1;
   }

}

# PWRDB_DIAG_PKT_RESET
# parameters: port
sub send_pwrdb_diag_pkt_reset
{

   my $proc_id = $_[1];
   return send_generic_pkt( $_[0], PWRDB_DIAG_PKT_RESET | $proc_id );
}

# SEND_PWRDB_DIAG_PKT_SCRIPT
# parameters: port, script
# returns: status field from response packet, -1 if error
# If the script is too long for one packet then it will
# be sent in multiple packets.
sub send_pwrdb_diag_pkt_script
{
  my $p = $_[0];
  my $s = $_[1];
  my $processor_select = $_[2];
  my $done = 0;
  my $s_part;
  my ($pkt, $ss, $cmd, $rsp);
  my ($id, $len);
  my $diag_cmd;
  my $diag_request_var;
  my $reply;
   
  my $MAX_PKT_SIZE = 500;

  do {
     if (length($s) < $MAX_PKT_SIZE)
     {
        # everything will fit in one packet
        $s_part = $s;
        $done   = 1;
     }
     else
     {
        # too much for one packet, fit in as much as we can
        $s_part = undef;

        ($id, $len) = unpack("vv", $s);
        if ($len >= $MAX_PKT_SIZE) { die "Single command is too large for packet.\n"; }
        while ( !$s_part || ((length($s_part)+$len) < $MAX_PKT_SIZE) )
        {
           $s_part    .= substr( $s, 0, $len );
           $s          = substr( $s, $len );
           ($id, $len) = unpack("vv", $s);
        }
     }

     $diag_cmd = pack("CCSV", DIAG_SUBSYS_CMD_F, DIAG_SUBSYS_PWRDB, PWRDB_DIAG_PKT_SCRIPT | $processor_select, length($s_part)) . $s_part;

     $diag_request_var = Variant(VT_ARRAY | VT_UI1, length $diag_cmd);
  $diag_request_var->Put($diag_cmd);
     
     $reply = $p->SendCommand($diag_request_var, $timeout_in_ms);

  if (defined $reply)
  {
     # use the unpack command to turn $reply into an list of
     # fields using $unpack_mask

#orig     ($pkt, $ss, $cmd, $rsp) = unpack("CCSV", $reply);
     ($pkt, $rsp) = unpack("VV", $reply);

        if ($rsp != 0) { $done = 1}

        if (!$done) { print "script: $rsp\n"; }
  }
  else
  {
     print "No reply to pwrdb_diag_pkt_script.\n";
        $rsp  = -1;
        $done = 1;
  }

  } until $done;

  return $rsp
}

# PWRDB_DIAG_PKT_LOG
# parameters: port
# returns: log as binary string, undef if error
sub send_pwrdb_diag_pkt_log
{
  my $p    = $_[0];
  my $processor_select = $_[1];
  my $done = 0;
  my $log = undef;

  do {
     my $diag_cmd = pack("CCS", DIAG_SUBSYS_CMD_F, DIAG_SUBSYS_PWRDB, PWRDB_DIAG_PKT_LOG | $processor_select);

     my $diag_request_var = Variant(VT_ARRAY | VT_UI1, length $diag_cmd);
     $diag_request_var->Put($diag_cmd);
   
     my $reply = $p->SendCommand($diag_request_var, $timeout_in_ms);

     if (defined $reply)
     {
        # use the unpack command to turn $reply into an list of
        # fields using $unpack_mask
#orig        my ($pkt, $ss, $cmd, $rsp) = unpack("CCSV", $reply);
        my ($pkt, $ss, $rsp) = unpack("VVV", $reply);

#orig        if ($rsp == PWRDB_RSP_SUCCESS)
        if ($ss == PWRDB_RSP_SUCCESS)
        {
#orig           $log  .= substr( $reply, 10 );
           $log  .= substr( $reply, 12 );
           $done  = 1;
        }
#orig        elsif ($rsp == PWRDB_RSP_OK_PARTIAL)
        elsif ($ss == PWRDB_RSP_OK_PARTIAL)
        {
#orig           $log  .= substr( $reply, 10 );
           $log  .= substr( $reply, 12 );
        }
        else
        {
           # TO DO: handle PWRDB_RSP_OK_PARTIAL
           print "Bad status in reply to pwrdb_diag_pkt_log.\n";
           $done = 1;
        }
     }
     else
     {
        print "No reply to pwrdb_diag_pkt_log.\n";
        $done = 1;
     }

  } until ($done);

  return $log;
}

# PWRDB_DIAG_PKT_RUN
# parameters: port
# returns: status field from response packet, -1 if error
sub send_pwrdb_diag_pkt_run
{
  my $proc_id = $_[1];
  return send_generic_pkt( $_[0], PWRDB_DIAG_PKT_RUN | $proc_id);
}

# PWRDB_DIAG_PKT_STOP
# parameters: port
# returns: status field from response packet, -1 if error
sub send_pwrdb_diag_pkt_stop
{
   my $proc_id = $_[1];
  return send_generic_pkt( $_[0], PWRDB_DIAG_PKT_STOP | $proc_id);
}

# PWRDB_DIAG_PKT_TEST_EVENT
# parameters: port, event source, event id
# returns: status from response pkt, -1 if error
sub send_pwrdb_diag_pkt_test_event
{
  my $p   = $_[0];
  my $src = $_[1];
  my $id  = $_[2];

  my $diag_cmd = pack("CCSVV", DIAG_SUBSYS_CMD_F, DIAG_SUBSYS_PWRDB, PWRDB_DIAG_PKT_TEST_EVENT, $src, $id );

  my $diag_request_var = Variant(VT_ARRAY | VT_UI1, length $diag_cmd);
  $diag_request_var->Put($diag_cmd);
   
  my $reply = $p->SendCommand($diag_request_var, $timeout_in_ms);

  if (defined $reply)
  {
     # use the unpack command to turn $reply into an list of
     # fields using $unpack_mask
     my ($pkt, $ss, $cmd, $rsp) = unpack("CCSV", $reply);

     return $rsp;
  }
  else
  {
     print "No reply to pwrdb_diag_pkt_test_event\n";
     return -1;
  }
}

sub send_pwrdb_diag_pkt_testclock
{
  my $p = $_[0];
  my $s = $_[1];
  my $processor_select = $_[2];

  my $done = 0;
  my ($pkt, $ss, $cmd, $rsp);
  my $diag_cmd;
  my $diag_request_var;
  my $reply;
   
  do {
     $diag_cmd = pack("CCSV", DIAG_SUBSYS_CMD_F, DIAG_SUBSYS_PWRDB, PWRDB_DIAG_PKT_CLK_OUTPUT_GPIO | $processor_select, $s) ;

     $diag_request_var = Variant(VT_ARRAY | VT_UI1, length $diag_cmd);
  $diag_request_var->Put($diag_cmd);
   
     $reply = $p->SendCommand($diag_request_var, $timeout_in_ms);

  if (defined $reply)
  {
     # use the unpack command to turn $reply into an list of
     # fields using $unpack_mask

#orig     ($pkt, $ss, $cmd, $rsp) = unpack("CCSV", $reply);
     ($pkt, $rsp) = unpack("VV", $reply);

        if ($rsp != 0) { $done = 1}

        if (!$done) { print "testclock: $rsp\n"; }
  }
  else
  {
     print "No reply to send_pwrdb_diag_pkt_testclock.\n";
        $rsp  = -1;
        $done = 1;
  }

  } until $done;

  return $rsp
}
