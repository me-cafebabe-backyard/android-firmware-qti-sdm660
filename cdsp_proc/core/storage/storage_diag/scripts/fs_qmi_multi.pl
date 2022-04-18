use strict;
use warnings;
use Win32::OLE;
use Win32::OLE::Variant;
use POSIX qw(strftime);

my $qpst;
my $port_selected;
my $port_list;
my $global_seq = 0;
my $key;

my @storage_diag_subcmd = (0x4b,105);

my $storage_diag_cmd_start = 100;
my @cmd_hdl = 0;

my ($test_name, @mainargs) = @ARGV;

my $gui = 0;
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

############################ fs_qmi-cmd-q #################################
sub storage_fs_qmi_cmd_q
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;

  my $count = $_[0];

  my $run_in_thread = 1;
  my $run_later = 1;
  my $reserved = 0;
  my $sub_cmd_id = 5;
  my $sub_cmd_req_pkt_len = 4;
  
  my $op = 2;
  my $file_size = 128;
  my $oflag = 0x80042;
  my $mode = 0x176;
  my $buf_seed = 65+$count;
  my $fake_op = 0;
  my $file_name = "/nv/item_files/sleep/debug_time_".$count.".txt";
  my $cmd_q_hdl = 0;
  
  printf "\tSending fs-qmi-cmd-q Request: %s : %d\n", $file_name, $file_size;
  
  $RequestString = pack ("CCSIIIIICIIICCa256",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x1), #S, Add-Cmd-q
                         $run_in_thread, #I
                         $run_later, #I
                         $reserved, #I
                         $sub_cmd_id, # rfs_out-cmd #I
                         $sub_cmd_req_pkt_len, #I
                         $op, # C
                         $file_size, #I
                         $oflag, #I
                         $mode, #I
                         $buf_seed, #C
                         $fake_op, #C
                         $file_name #a256
                         );
  $variant = Variant(VT_ARRAY | VT_UI1, 294);
  $variant->Put($RequestString);

  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "\tReceived response for fs_qmi-cmd-q!\n";
  @Rsp = unpack "CCSIII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "fs_qmi-cmd-q FAILED : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    $cmd_q_hdl = $Rsp[5];
  }

  return $cmd_q_hdl;
}

sub storage_fs_qmi_cmd_q_get_results
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

  printf "\tSending cmd-q-get-results Request\n";
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "\tReceived response for cmd-q-get-results!\n";
  @Rsp = unpack "CCSIIIIIQQQQQQQQQQQIIIC", $Response;

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
    #print "block_size = $Rsp[7]\n";
    #print "total_blocks = $Rsp[8]\n";
    #print "total_api_time = $Rsp[9]\n";
    #print "sock_open_time = $Rsp[10]\n";
    #print "req_time = $Rsp[11]\n";
    #print "data_xfer_time = $Rsp[12]\n";
    #print "total_tx_time = $Rsp[13]\n";
    #print "total_rx_time = $Rsp[14]\n";
    #print "min_tx_time = $Rsp[15]\n";
    #print "max_tx_time = $Rsp[16]\n";
    #print "min_rx_time = $Rsp[17]\n";
    #print "max_rx_time = $Rsp[18]\n";
    print "rsp_pkt_len = $Rsp[19]\n";
    print "bytes_accessed = $Rsp[20]\n";
    print "error_num = $Rsp[21]\n";
    print "verify_check_passed = $Rsp[22]\n";
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

  printf "\tSending cmd-q-run\n";
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "\tReceived response for cmd-q-run!\n";
  @Rsp = unpack "CCSIIII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "cmd-q-run FAILED : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    printf "\tResponse : Total-req : %d  Success-req : %d  Failed-req : %d\n", $Rsp[4], $Rsp[5], $Rsp[6];
  }

  return $result;
}

sub fs_qmi_cmd_q_run_threads
{
  my $thread_count = 10;
  
  printf "\n\n================================================================\n\n";
  printf "Starting fs_qmi_req";
  printf "\n================================================================\n";
 
  for (my $i = 0; $i < $thread_count; $i++)
  { 
    $cmd_hdl[$i] = storage_fs_qmi_cmd_q($i);
    $state = storage_fs_qmi_cmd_q_get_results($cmd_hdl[$i]);
    $state == 0 or die "\n\nInvalid state : \n\n", $state;        
  }
  
  printf "Starting all threads\n";

  sleep (2);

  cmd_q_run();

  sleep (5);
  printf "Verifying results for req\n";
  for (my $i = 0; $i < $thread_count; $i++)
  {     
    $state = storage_fs_qmi_cmd_q_get_results($cmd_hdl[$i]);
    $state == 2 or die "\n\nInvalid state : $state";
    printf "Successfully verified results\n";
  }
}

###############################################################################
#################################### Main Script ##############################
get_phone($gui);
fs_qmi_cmd_q_run_threads ();
