use strict;
use warnings;
use Win32::OLE;
use Win32::OLE::Variant;
use POSIX qw(strftime);

use File::Path qw(make_path remove_tree);

my $qpst;
my $port_selected;
my $port_list;
my $global_seq = 0;
my $key;


my @storage_diag_subcmd = (0x4b,105);

my $storage_diag_cmd_start = 0;
my $start_file_index = 7;
my $end_file_index = 25;
my $min_threads = 1;
my $max_threads = 1;
my $sleep_time = 10;
my $loop_count = 5;

# my $real_file_size_mb = $ARGV[0] * 1.0 / 2.0 ;
# my $start_file_size = ($real_file_size_mb * 1024 * 1024);
# my $end_file_size = ($real_file_size_mb * 1024 * 1024);


my $start_file_size = (1 * 1024 * 1024);
my $end_file_size = (25 * 1024 * 1024);
my $file_size_increment = (512 * 1024);

# my $start_file_size = (100 * 1024);
# my $end_file_size = (1025 * 1024);
# my $file_size_increment = (50 * 1024);


# my $start_file_size = (3 * 1024);
# my $end_file_size = (100 * 1024);
# my $file_size_increment = (3 * 1024);


my ($test_name, @mainargs) = @ARGV;

my $gui = 0;
my @cmd_hdl = 0;
my $state = 0;
my $out_fd;
my $out_fd_detail;
my $avg_bytes_written = 0;
my $avg_cmd_exe_time = 0;
my $run_count = 0;

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

############################ rfs_put-cmd-q #################################
sub storage_rfs_put_cmd_q
{
  my $RequestString;
  my $variant;
  my @Rsp;
  my $result = 0;

  my $run_in_thread = $_[0];
  my $run_later = $_[1];
  my $file_size = $_[2];
  my $oflag = $_[3];
  my $mode = $_[4];
  my $buf_seed = $_[5];
  my $verify_file = $_[6];
  my $file_name = $_[7];

  my $reserved = 0;
  my $sub_cmd_id = 3; # rfs_put cmd
  my $sub_cmd_req_pkt_len = 4;
  my $cmd_q_hdl = 0;
  

  $RequestString = pack ("CCSIIIIIIIIIIa256",
                         @storage_diag_subcmd, # CC
                         ($storage_diag_cmd_start + 0x1), #S, Add-Cmd-q
                         $run_in_thread, #I
                         $run_later, #I
                         $reserved, #I
                         $sub_cmd_id, # rfs_out-cmd #I
                         $sub_cmd_req_pkt_len, #I
                         $file_size, #I
                         $oflag, #I
                         $mode, #I
                         $buf_seed, #I
                         $verify_file, #I
                         $file_name #a256
                         );
                         
  $variant = Variant(VT_ARRAY | VT_UI1, 296);
  $variant->Put($RequestString);

  printf "\tSending rfs-put-cmd-q Request: %s : %d\n", $file_name, $file_size;
  my $Response = $port_selected->SendCommand($variant, 20000);
  printf "\tReceived response for rfs_put-cmd-q!\n";
  @Rsp = unpack "CCSIIIIII", $Response;

  if ($Rsp[3] != 0)
  {
    printf "rfs_put-cmd-q FAILED : %d\n", $Rsp[3];
    $result = $Rsp[3];
    die;
  }
  else
  {
    $cmd_q_hdl = $Rsp[5];
  }

  return $cmd_q_hdl;
}


sub add_data_to_results
{
    my $block_size = $_[0];
	my $total_bytes = $_[1];
	my $total_blocks  = $_[2];
	my $total_api_time = $_[3];
    my $sock_open_time = $_[4];
    my $req_time = $_[5];
    my $data_xfer_time = $_[6];
    my $total_tx_time = $_[7];
    my $total_rx_time = $_[8];
    my $min_tx_time = $_[9];
    my $max_tx_time = $_[10];
    my $min_rx_time = $_[11];
    my $max_rx_time = $_[12];
    
    printf ($out_fd_detail "%s,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.3f,%05.6f\n",
            $key, $block_size, $total_bytes, $total_blocks, $total_api_time, $sock_open_time, $req_time, $data_xfer_time,
            $total_tx_time, $total_rx_time, $min_tx_time, $max_tx_time, $min_rx_time, $max_rx_time, (($total_bytes * 8)/$total_api_time));
}

sub storage_rfs_put_cmd_q_get_results
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
    print "total_bytes = $Rsp[20]\n";
    print "error_num = $Rsp[21]\n";
    print "verify_check_passed = $Rsp[22]\n";


    $state = $Rsp[4];

    my $block_size = $Rsp[7];
    my $total_blocks = $Rsp[8];
    my $total_api_time = $Rsp[9];
    my $sock_open_time = $Rsp[10];
    my $req_time = $Rsp[11];
    my $data_xfer_time = $Rsp[12];
    my $total_tx_time = $Rsp[13];
    my $total_rx_time = $Rsp[14];
    my $min_tx_time = $Rsp[15];
    my $max_tx_time = $Rsp[16];
    my $min_rx_time = $Rsp[17];
    my $max_rx_time = $Rsp[18];
    my $total_bytes = $Rsp[20];
    $avg_cmd_exe_time += $total_api_time;

    if ($state == 2)
    {
       $Rsp[19] == 9 or die "\n\nInvalid rsp pkt size : \n\n", $Rsp[19];
       add_data_to_results ($block_size, $total_bytes, $total_blocks, $total_api_time,
                            $sock_open_time, $req_time, $data_xfer_time,
                            $total_tx_time, $total_rx_time, $min_tx_time,
                            $max_tx_time, $min_rx_time, $max_rx_time);
    }
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

sub rfs_put_cmd_q_run_later_in_threads
{
  my $file_size = $_[0];
  my $num_threads = $_[1];
  my $file_name = "/readwrite/solar/san_diego";
  my $block_size = 2048;

  printf "\n\n================================================================\n\n";
  printf "Starting performance test for File Size: $file_size for thread count : $num_threads\n";
  printf "\n================================================================\n";

  $avg_cmd_exe_time = 0.0;
  
  for (my $i = 1; $i <= $loop_count; $i++)
  {
    my $j;
    printf "\nStarting round : $i\n";

    #Q as many put requests as threads requested   
    for ($j = 1; $j <= $num_threads; $j++)
    {
        printf "Queueing thread $j\'s req\n";
        
        $cmd_hdl[$j] = storage_rfs_put_cmd_q(1, 1, $file_size, 514,0666,
                                             $j,0, $file_name);
        $state = storage_rfs_put_cmd_q_get_results($cmd_hdl[$j]);
        $state == 0 or die "\n\nInvalid state : \n\n", $state;        
    }

    printf "Starting all threads\n";

    sleep (2);
    
    cmd_q_run();

    sleep ($sleep_time);
    if ($file_size > (10*1024*1024))
    {
      sleep ($sleep_time);
      if ($file_size > (20*1024*1024))
      {
        sleep ($sleep_time);
      }
    }
    
    for ($j = 1; $j <= $num_threads; $j++)
    {
      printf "Verifying results for thread $j\'s req\n";
      $state = storage_rfs_put_cmd_q_get_results($cmd_hdl[$j]);
      $state == 2 or die "\n\nInvalid state : $state";
      printf "Successfully verified results for thread $j\'s req\n";
    }

    printf "--------------------------------------------------------------\n";
    printf "Round $i complete\n";
    printf "--------------------------------------------------------------\n";
  }
 
  $avg_cmd_exe_time = ((($avg_cmd_exe_time * 1.0) / $loop_count) / $num_threads);
  my $thput = ((($file_size * 8.0)/ $avg_cmd_exe_time));
  printf ($out_fd "%05.3f,", $thput);
}

sub rfs_put_cmd_q_run_threads
{
  print $out_fd "FileSize(MB),";
  for (my $i = $min_threads; $i <= $max_threads; $i++)
  {
    print $out_fd "Thpt(Mbps)-$i th,";  
  }
  print $out_fd "\n";
 
# uncomment required lines based on type of filesizes needed to be tested
# for (my $i = $start_file_index; $i++; $i <= $end_file_index)
  for (my $i = $start_file_size; $i <= $end_file_size; $i = $i + $file_size_increment)
  {
#   my $file_size = (2**$i);
#    printf ("File size %d\n", $i);
    my $file_size = ($i);
    printf ($out_fd "%05.3f,",($file_size/1024.0 /1024));
    for (my $j = $min_threads; $j <= $max_threads; $j++)
    {
      $key = "$j"."_"."$file_size";
      rfs_put_cmd_q_run_later_in_threads ($file_size, $j);
      sleep (2);
    }
    printf($out_fd "\n");
  }
}


sub rfs_put_setup_output_file
{
  my $time_str = strftime('%Y-%m-%d-%H-%M-%S',localtime);
  print $time_str;
  
  my $out_dir = 'results/'.$time_str;
  my $out_file= $out_dir."/tftp_put_stats_".$time_str.".csv";
  my $out_file_detail = $out_dir."/tftp_put_stat_details".$time_str.".csv";
  
  make_path($out_dir);
  open ($out_fd, '>>', $out_file) or die "Could not open output file $out_file $!";
  open ($out_fd_detail, '>>', $out_file_detail) or die "Could not open output file $out_file_detail $!";  
  
  printf $out_fd_detail "KEY, BLOCK_SIZE, TOTAL_BYTES, TOTAL_BLOCKS, TOTAL_API_TIME_micro_sec, SOCK_OPEN_TIME, REQ_TIME, DATA_XFER_TIME,";
  printf $out_fd_detail "TOTAL_TX_TIME, TOTAL_RX_TIME, MIN_TX_TIME, MAX_TX_TIME, MIN_RX_TIME, MAX_RX_TIME, THROUGHPUT Mbps\n";

}

sub rfs_put_cleanup
{
  close $out_fd;
  close $out_fd_detail;
}

###############################################################################
#################################### Main Script ##############################
get_phone($gui);
rfs_put_setup_output_file ();
rfs_put_cmd_q_run_threads ();
rfs_put_cleanup ();
