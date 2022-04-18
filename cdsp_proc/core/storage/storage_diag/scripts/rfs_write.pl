use strict;
use Win32::OLE;
use Win32::OLE::Variant;

my $qpst;
my $port_selected;
my $port_list;
my $global_seq = 0;

my @storage_diag_subcmd = (0x4b,105);
my $storage_diag_cmd_start = 0;

my ($test_name, @mainargs) = @ARGV;

my $gui = 0;
my @cmd_hdl = 0;
my $state = 0;

sub get_phone
{
   my $show_gui = shift;
   my $prod_id = "QPSTAtmnServer.Application";

   eval
   {
     $qpst = Win32::OLE->GetActiveObject($prod_id);
   };

   die "$prod_id not installed" if $@;

   # Start a new instance. Call Quit when $qpst set to undef or script exits.
   unless (defined $qpst)
   {
     $qpst = Win32::OLE->new($prod_id, sub {$_[0]->Quit;}) or die "Oops, cannot start $prod_id";
   }

   if($show_gui)
   {
      $qpst->ShowWindow();
      print "press enter to continue";
      <STDIN>;

      $port_selected = $qpst->GetSelectedPort() or die "Selected port unavailable" if(!$port_selected);
   }
   else
   {
      my $port_list = $qpst->GetPortList();

      $port_selected = &pick_a_port($port_list, $qpst);
      if($port_selected == -1)
      {
         die "\nNo phone found!!";
      }
   }
   return $port_selected;
}


###############################################################################
##### Subroutine PICK_A_PORT - returns an available port to which phone
#is connected #####
sub pick_a_port
{
   $port_list = $qpst->GetPortList();
   my $phone_count = $port_list->PhoneCount;

   # Translate phone mode to string.
   my %phone_mode_list = qw (
           0 modeNone
           1 modeDataServices
           2 modeDownload
           3 modeDiagnostic
           4 modeDiagnosticOffline
           5 modeReset
           6 modeStreamDownload) ;

   # Translate phone status to string.
   my %phone_status_list = qw (
     0 phoneStatusNone
     1 phoneStatusInitializationInProgress
     2 phoneStatusPortNotPresent
     3 phoneStatusPhoneNotPresent
     4 phoneStatusPhoneNotSupported
     5 phoneStatusReady) ;

   my $count;

   foreach $count (0..$phone_count)
   {
      my $port_id = $port_list->PortId($count);
      my $mode = $phone_mode_list{$port_list->PhoneMode($count)};

      my $qpst_port = $qpst->GetPort($port_id);

      # For all ports that have a running phone get the port object.
      if (($mode eq "modeDiagnostic" || $mode eq "modeDiagnosticOffline") && (defined $qpst_port))
      {
          # Get live data from the port object.
          my $port_name_2 = $qpst_port->PortName;
          my $port_label_2 = $qpst_port->PortLabel;
          my $is_usb_2 = $qpst_port->IsUSB;
          my $port_id_2 = $qpst_port->PortId;
          my $mode_2 = $phone_mode_list{$qpst_port->PhoneMode};
          my $status_2 = $phone_status_list{$qpst_port->PhoneStatus};
          my $hex_esn_2 = sprintf("0x%08X", $qpst_port->ESN);

          # Display the state of the port.
          #print "\nPicking phone: $port_id_2 $port_name_2 $is_usb_2 $hex_esn_2 \042$port_label_2\042 $mode_2 $status_2\n\n";
          print "\nPicking phone on port $port_name_2;\nPortID: $port_id_2\nHEX ESN # $hex_esn_2\nPort Label: $port_label_2\n\n";

          return $qpst_port;
      }
   }
}

############################ rfs_write-cmd-q #################################
sub storage_rfs_write_cmd_q
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;

  my $run_in_thread = $_[0];
  my $run_later = $_[1];
  my $num_files = $_[2];
  my $file_size = $_[3];
  my $file_size_incr = $_[4];
  my $write_size = $_[5];
  my $write_size_incr = $_[6];
  my $seed_val = $_[7];
  my $verify_after_each_write = $_[8];
  my $file_name = $_[9];

  my $reserved = 0;
  my $sub_cmd_id = 2; # rfs_write-cmd
  my $sub_cmd_req_pkt_len = 4;
  my $cmd_q_hdl = 0;

  $RequestString = pack ("CCSIIIIIIIIIIIIa256",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x1), #S, Add-Cmd-q
                         $run_in_thread,
                         $run_later,
                         $reserved,
                         $sub_cmd_id, # rfs_write-cmd
                         $sub_cmd_req_pkt_len,
                         $num_files,
                         $file_size,
                         $file_size_incr,
                         $write_size,
                         $write_size_incr,
                         $seed_val,
                         $verify_after_each_write,
                         $file_name
                         );

  $variant = Variant(VT_ARRAY | VT_UI1, 308);
  $variant->Put($RequestString);

  printf "Sending rfs_write-cmd-q Request: %s : %d : %d\n", $file_name, $file_size, $num_files;
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "Received response for rfs_write-cmd-q!\n";
  @Rsp = unpack "CCSIIIIII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "rfs_write-cmd-q FAILED : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    printf "rfs_write-cmd-q response details:\n";
    printf "rfs_write-cmd-q : state: %d\n",$Rsp[4];
    printf "rfs_write-cmd-q : cmd_q_handle: %d\n",$Rsp[5];
    printf "rfs_write-cmd-q : sub_cmd_rsp_id: %d\n",$Rsp[6];
    printf "rfs_write-cmd-q : sub_cmd_rsp_len: %d\n",$Rsp[7];
    printf "rfs_write-cmd-q : num_files_created: %d\n",$Rsp[8];
    $cmd_q_hdl = $Rsp[5];
  }

  return $cmd_q_hdl;
}

sub storage_rfs_write_cmd_q_get_results
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;
  my ($cmd_q_hdl) =  @_;
  my $state = -1;

  $RequestString = pack ("CCSI",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x02), # S, Get-Results cmd
                         $cmd_q_hdl);

  $variant = Variant(VT_ARRAY | VT_UI1, 8);
  $variant->Put($RequestString);

  printf "Sending cmd-q-get-results Request:\n";
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "Received response for cmd-q-get-results!\n";
  @Rsp = unpack "CCSIIIIIQQQQQQQQQQQII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "cmd-q-get-results FAILED : %d\n", $Rsp[3];
    die;
  }
  else
  {
    print "response details:\n";
    print "state = $Rsp[4]\n";
    print "cmd_q_handle = $Rsp[5]\n";
    print "sub_cmd_rsp_id = $Rsp[6]\n";
    print "block_size = $Rsp[7]\n";
    print "total_blocks = $Rsp[8]\n";
    print "total_api_time = $Rsp[9]\n";
    print "sock_open_time = $Rsp[10]\n";
    print "req_time = $Rsp[11]\n";
    print "data_xfer_time = $Rsp[12]\n";
    print "total_tx_time = $Rsp[13]\n";
    print "total_rx_time = $Rsp[14]\n";
    print "min_tx_time = $Rsp[15]\n";
    print "max_tx_time = $Rsp[16]\n";
    print "min_rx_time = $Rsp[17]\n";
    print "max_rx_time = $Rsp[18]\n";
    print "rsp_pkt_len = $Rsp[19]\n";
    print "num_files_created = $Rsp[20]\n";

    $state = $Rsp[4];
  }
  return $state;
}

############################ cmd-q run #################################
sub cmd_q_run
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;

  $RequestString = pack ("CCSI",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x03), # S, cmd-q-run
                         $result, #I
                         );

  $variant = Variant(VT_ARRAY | VT_UI1, 8);
  $variant->Put($RequestString);

  printf "Sending cmd-q-run\n";
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "Received response for cmd-q-run!\n";
  @Rsp = unpack "CCSIIII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "cmd-q-run FAILED : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    printf "Response : Total-req : %d  Success-req : %d  Failed-req : %d\n", $Rsp[4], $Rsp[5], $Rsp[6];
  }

  return $result;
}

###################  rfs_write-cmd-q-direct ##############################
sub rfs_write_cmd_q_direct
{
  printf "==========================================================\n";
  printf "rfs_write_cmd_q_direct : start ....\n";
  
  my $run_in_thread = 0;
  my $run_later = 0;
  my $num_files = 5;
  my $file_size = 2048;
  my $file_size_incr = 512;
  my $write_size = 1024;
  my $write_size_incr = 0;
  my $seed_val = 97;
  my $verify_after_each_write = 0;
  my $file_name = "/readwrite/solar/earth";
  
  $cmd_hdl[0] = storage_rfs_write_cmd_q($run_in_thread, $run_later,
                   $num_files, $file_size,
                   $file_size_incr, $write_size, $write_size_incr,
                   $seed_val, $verify_after_each_write, $file_name);

  printf "rfs_write_cmd_q_direct : end ....\n\n\n";
  printf "==========================================================\n";
}

###################  rfs_write-cmd-q-run-now ##############################
sub rfs_write_cmd_q_run_now
{
  printf "==========================================================\n";
  printf "rfs_write_cmd_q_run_now : start ....\n";
  printf "rfs_write_cmd_q_run_now : queueing requests to be run now\n";

  my $run_in_thread = 1;
  my $run_later = 0;
  my $num_files = 5;
  my $file_size = 3000;
  my $file_size_incr = 512;
  my $write_size = 1024;
  my $write_size_incr = 0;
  my $seed_val = 108;
  my $verify_after_each_write = 0;
  my $file_name = "/readwrite/solar/mars";

  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $cmd_hdl[$i] = storage_rfs_write_cmd_q($run_in_thread, $run_later,
                   $num_files, $file_size,
                   $file_size_incr, $write_size, $write_size_incr,
                   $seed_val, $verify_after_each_write, $file_name);
    ++$num_files;
    $file_size += 100;
    printf "-----------------------------------\n";
  }

  printf "rfs_write_cmd_q_run_now : queueing is success. Sleeping 20 seconds\n";
  sleep(20);

  printf "rfs_write_cmd_q_run_now : verifying queued requests\n";

  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $state = storage_rfs_write_cmd_q_get_results($cmd_hdl[$i]);
    $state == 2 or die "\n\nInvalid state : $state\n\n";
    printf "-----------------------------------\n";
  }

  printf "rfs_write_cmd_q_run_now : verification done. all good\n";

  printf "rfs_write_cmd_q_run_now :  end ....\n\n\n";
  printf "==========================================================\n";
}

###################  rfs_write-cmd-q-run-later ##############################
sub rfs_write_cmd_q_run_later
{
  printf "==========================================================\n";
  printf "rfs_write_cmd_q_run_later : start ....\n";
  printf "rfs_write_cmd_q_run_later : queueing requests to be run later\n";

  my $run_in_thread = 1;
  my $run_later = 1;
  my $num_files = 1;
  my $file_size = (4*1024);
  my $file_size_incr = 0;
  my $write_size = (4*1024);
  my $write_size_incr = 0;
  my $seed_val = 108;
  my $verify_after_each_write = 0;
  my $file_name_base = "/readwrite/solar/tn_server_t1n1_#1";
  my $loop_count = 1;
  my $file_name;
  
  for (my $i=0; $i < $loop_count; $i++)
  {
    printf "-----------------------------------\n";

    $file_name = $file_name_base."_".$i;
    printf "filename = %s", $file_name;
    
    $cmd_hdl[$i] = storage_rfs_write_cmd_q($run_in_thread, $run_later,
                   $num_files, $file_size,
                   $file_size_incr, $write_size, $write_size_incr,
                   $seed_val, $verify_after_each_write, $file_name);
    $num_files += 3;
    $file_size += 300;
    $file_size_incr += 10;

    $state = storage_rfs_write_cmd_q_get_results($cmd_hdl[$i]);
    $state == 0 or die "\n\nInvalid state : $state \n\n";
    printf "-----------------------------------\n";
  }

  printf "rfs_write_cmd_q_run_later : queueing is success. Sleeping 20 seconds\n";
  sleep(5);

  printf "rfs_write_cmd_q_run_later : checking no request has started yet.\n";

  for (my $i=0; $i < $loop_count; $i++)
  {
    printf "-----------------------------------\n";
    $state = storage_rfs_write_cmd_q_get_results($cmd_hdl[$i]);
    $state == 0 or die "\n\nInvalid state : $state \n\n";
    printf "-----------------------------------\n"
  }

  printf "rfs_write_cmd_q_run_later :  no request has started yet.  All good\n";

  printf "rfs_write_cmd_q_run_later : sending run-cmd-q request\n";
  cmd_q_run();

  printf "rfs_write_cmd_q_run_later : Sleeping 20 seconds to let the queued requests complete\n";
  sleep(10);

  for (my $i=0; $i < $loop_count; $i++)
  {
    printf "-----------------------------------\n";
    $state = storage_rfs_write_cmd_q_get_results($cmd_hdl[$i]);
    $state == 2 or die "\n\nInvalid state : %d \n\n", $state;
    printf "-----------------------------------\n";
  }

  printf "rfs_write_cmd_q_run_later : verification done. all good\n";

  printf "rfs_write_cmd_q_run_later : complete ....\n\n\n";
  printf "==========================================================\n";
}

###############################################################################
#################################### Main Script ##############################
get_phone($gui);
rfs_write_cmd_q_direct();
rfs_write_cmd_q_run_now();
rfs_write_cmd_q_run_later();
