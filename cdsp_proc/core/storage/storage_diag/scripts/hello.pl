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

############################ hello-cmd-direct #################################
sub storage_hello_direct
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;
  my $echo_num = int(rand(20000));

  $RequestString = pack ("CCSI",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x0), # S, Hello-Command
                         $echo_num, #I
                         );

  $variant = Variant(VT_ARRAY | VT_UI1, 8);
  $variant->Put($RequestString);

  printf "Sending hello-cmd-direct Request: %d\n", $echo_num;
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "Received response for hello-cmd-direct!\n";
  @Rsp = unpack "CCSII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "hello-cmd-direct FAILED. : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    printf "hello-cmd-direct success. Response : %d\n", $Rsp[4];
  }

  return $result;
}

############################ hello-cmd-q #################################
sub storage_hello_cmd_q
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;
  my ($run_in_thread, $run_later) =  @_;
  my $reserved = 0;
  my $sub_cmd_id = 0; # Hello-cmd
  my $sub_cmd_req_pkt_len = 4;
  my $echo_num = int(rand(20000));
  my $cmd_q_hdl = 0;

  $RequestString = pack ("CCSIIIIII",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x1), #S, Add-Cmd-q
                         $run_in_thread,
                         $run_later,
                         $reserved,
                         $sub_cmd_id, # Hello-cmd
                         $sub_cmd_req_pkt_len,
                         $echo_num, #I
                         );

  $variant = Variant(VT_ARRAY | VT_UI1, 28);
  $variant->Put($RequestString);

  printf "Sending hello-cmd-q Request: %d\n", $echo_num;
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "Received response for hello-cmd-q!\n";
  @Rsp = unpack "CCSIIIIII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "hello-cmd-q FAILED : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    printf "hello-cmd-q response details:\n";
    printf "hello-cmd-q : state: %d\n",$Rsp[4];
    printf "hello-cmd-q : cmd_q_handle: %d\n",$Rsp[5];
    printf "hello-cmd-q : sub_cmd_rsp_id: %d\n",$Rsp[6];
    printf "hello-cmd-q : sub_cmd_rsp_len: %d\n",$Rsp[7];
    printf "hello-cmd-q : echo-num: %d\n",$Rsp[8];
    $cmd_q_hdl = $Rsp[5];
  }

  return $cmd_q_hdl;
}

sub storage_hello_cmd_q_get_results
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
    printf "cmd-q-get-results : response details:\n";
    printf "cmd-q-get-results : state: %d\n",$Rsp[4];
    printf "cmd-q-get-results : cmd_q_handle: %d\n",$Rsp[5];
    printf "cmd-q-get-results : sub_cmd_rsp_id: %d\n",$Rsp[6];
    printf "cmd-q-get-results : sub_cmd_rsp_len: %d\n",$Rsp[19];
    printf "cmd-q-get-results : echo-num: %d\n",$Rsp[21];
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
    printf "cmd-q-run : response details:\n";
    printf "cmd-q-run : Total-requests %d\n", $Rsp[4];
    printf "cmd-q-run : success-req %d\n", $Rsp[5];
    printf "cmd-q-run : failed-req %d\n", $Rsp[6];
  }

  return $result;
}

###################  hello-cmd-direct ##############################
sub hello_cmd_direct
{
  printf "==========================================================\n";
  printf "hello_cmd_direct : start ....\n";
  storage_hello_direct();
  printf "hello_cmd_direct : end ....\n\n\n";
  printf "==========================================================\n";
}

###################  hello-cmd-q-direct ##############################
sub hello_cmd_q_direct
{
  printf "==========================================================\n";
  printf "hello_cmd_q_direct : start ....\n";
  for (my $i=0; $i < 5; $i++)
  {
    $cmd_hdl[$i] = storage_hello_cmd_q(0, 0);
  }
  printf "hello_cmd_q_direct : end ....\n\n\n";
  printf "==========================================================\n";
}

###################  hello-cmd-q-run-now ##############################
sub hello_cmd_q_run_now
{
  printf "==========================================================\n";
  printf "hello_cmd_q_run_now : start ....\n";
  printf "hello_cmd_q_run_now : queueing requests to be run now\n";
  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $cmd_hdl[$i] = storage_hello_cmd_q(1, 0);
    printf "-----------------------------------\n";
  }

  printf "hello_cmd_q_run_now : queueing is success. Sleeping 5 seconds\n";
  sleep(5);

  printf "hello_cmd_q_run_now : verifying queued requests\n";

  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $state = storage_hello_cmd_q_get_results($cmd_hdl[$i]);
    $state == 2 or die "\n\nInvalid state :\n\n", $state;
    printf "-----------------------------------\n";
  }

  printf "hello_cmd_q_run_now : verification done. all good\n";

  printf "hello_cmd_q_run_now :  end ....\n\n\n";
  printf "==========================================================\n";
}

###################  hello-cmd-q-run-later ##############################
sub hello_cmd_q_run_later
{
  printf "==========================================================\n";
  printf "hello_cmd_q_run_later : start ....\n";
  printf "hello_cmd_q_run_later : queueing requests to be run later\n";
  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $cmd_hdl[$i] = storage_hello_cmd_q(1, 1);
    $state = storage_hello_cmd_q_get_results($cmd_hdl[$i]);
    $state == 0 or die "\n\nInvalid state : \n\n", $state;
    printf "-----------------------------------\n";
  }

  printf "hello_cmd_q_run_later : queueing is success. Sleeping 5 seconds\n";
  sleep(5);

  printf "hello_cmd_q_run_later : checking no request has started yet.\n";

  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $state = storage_hello_cmd_q_get_results($cmd_hdl[$i]);
    $state == 0 or die "\n\nInvalid state : \n\n", $state;
    printf "-----------------------------------\n"
  }

  printf "hello_cmd_q_run_later :  no request has started yet.  All good\n";

  printf "hello_cmd_q_run_later : sending run-cmd-q request\n";
  cmd_q_run();

  printf "hello_cmd_q_run_later : Sleeping 5 seconds to let the queued requests complete\n";
  sleep(5);

  for (my $i=0; $i < 5; $i++)
  {
    printf "-----------------------------------\n";
    $state = storage_hello_cmd_q_get_results($cmd_hdl[$i]);
    $state == 2 or die "\n\nInvalid state : %d \n\n", $state;
    printf "-----------------------------------\n";
  }

  printf "hello_cmd_q_run_later : verification done. all good\n";

  printf "hello_cmd_q_run_later : complete ....\n\n\n";
  printf "==========================================================\n";
}

###############################################################################
#################################### Main Script ##############################
get_phone($gui);
hello_cmd_direct();
hello_cmd_q_direct();
hello_cmd_q_run_now();
hello_cmd_q_run_later();
