# ===================================================================================
# Copyright QUALCOMM (C) 2010-2015, All Rights Reserved.
#
# SAMPostProcess.pl -l log_file -old
#
# Read and parse sensor SAM internal algorithm log packets from an input QXDM DLF log file.
# The -old option generates an output file named using the legacy "_prssamqmd.csv" extension.
#
# Revision History
#
# 11-10-2010   Kaushik  fix process_qmd_result() by using accel? = get_int32();
# 11-11-2010   df       correct die( function names)
# 01-03-2011   df       added LOG_SNS_DSPS_PWR_C packet type.
# 04-08-2011   df       added LOG_SNS_GYRO_SIMP_CAL_RESULT/REPORT
# 07-13-2011   df       added LOG_SNS_GRAVITY_RESULT_C
# 07-25-2011   df       added LOG_SNS_QUAT_RESULT_C 
# 08-26-2011   df       changed QUATERNION for Qfusion: values change from  Q16 to float.  
# 08-29-2011   df       added Qfusion LOG_SNS_MAG_CAL_RESULT_C. 
# 09-08-2001   df       added Filtered Magnetic Vector - FMV - packets
# 09-14-2011   df       added LOG_SNS_ROTATION_VECTOR_CONFIG/RESULT/REPORT_C.
# 09-15-2011   df       updated most Qfusion packet numbers: FMV, ROTV
# 09-23-2011   df       added most Qfusion _CONFIG packets
# 09-30-2011   df       Correct parse for process_fmv_mag_update()
# 10-28-2011   Kaushik  added LOG_SNS_QUAT_REPORT_C
# 03-07-2012   df       added Gestures support
# 04-05-2012   df       Corrected quaternion_report to use float quat[4]
#                       + also fixed fmv_report to use correct x, y, z axes 
# 07-10-2012   df       Added accel auto calibration log packets
# 08-10-2012   df       Updated accel auto calibration REPORT packet
# 10-25-2012   df       Added PED and PAM support 
# 04-09-2013   df       Added SMD support 
# 04-17-2013   df       Correct SMD packet numbers.
# 04-26-2013   df       Add support for Coarse Motion Classifier and Distance Bound services
# 05-07-2013   dfelnhof Fixed a bug in process_fmv_quat_update()
# 07-12-2103   df       Fix process_db_result, process_db_config
# 07-23-2013   hw       Added support for latency measurement log packet
# 07-24-2013   dfelnhof Added support for FIFO
# 08-07-2013   df       Added GAME_ROTATION_VECTOR support
# 08-22-2013   dfelnhof Fixed the incrementing line counter
# 02-11-2014   dfelnhof Added support for MD IRQ packet
# 03-18-2014   dfelnhof Added support for QMAG Cal (but not tested because SW implementation is not done)
#                       Added support for Geomagnetic Rotation Vector
# 04-21-2014   dfelnhof Added support for Pedestrian Alignment (PALN).
# 06-12-2014   dfelnhof Added support for CMC2.0.
# 06-13-2014   dfelnhof Modified the PALN result2 and report packets to support the relative turn angle fields.
# 06-20-2014   dfelnhof Added temporary support for QMAG Cal packets (config, result, and report) to Gyro Simple Cal packets (version 255).
# 06-24-2014   dfelnhof Added support for version 2 distance bound config and result packets.
# 07-15-2014   df       Added support for LOG_SNS_UIMAGE packet
# 07-31-2014   dfelnhof Needed to disable the version check temporarily for 0x1540 Gravity packet for 8994 bringup.
# 07-31-2014   dfelnhof Version checking for 0x1540 Gravity packet updated.
# 09-11-2014   dfelnhof Updated LOG_SNS_DB_RESULT_C packet parser for version 2.
#                       Added support for DPC (Device Position Classifier).
# 09-16-2014   df       Updated to support uimage version 3 packets.
# 02-02-2015   dfelnhof Added support for Tilt wearable detector and QHeart.
# 02-13-2015   dfelnhof Added support for LOG_SNS_SYNC_PROXY_CLIENT_C.
# 03-03-2015   df       Adding work around overrun from CR762807 for LOG_SNS_FMV_REPORT
#                       + fix sns_smd_config and sns_smd_result
# 07-21-2015   dfelnhof  Fixed LOG_SNS_QMAG_CAL_RESULT_C packet parsing.
# 07-29-2015   dfelnhof  Fixed LOG_SNS_FMV_REPORT_C packet parsing to support 32-bit timestamp (it should be 64-bit). Removed workaround for SMD and CR762807.
# 09-09-2015   dfelnhof  Wearables support added for hijacking GRV packets (version 255) for QHeart.
# 09-23-2015   dfelnhof  Added support for DPC version 2 packets.
# 09-30-2015   dfelnhof  Added support for IOD and IODA packets.
# 10-05-2015   dfelnhof  Fixed some bugs with the IOD and IODA packets.
# 01-29-2015   dfelnhof  Updated DPC version 2 packets. Added decimal packet type to packet count stdout.
# ===================================================================================

use strict;
use warnings;
use Data::Dumper;

my $old = 0;
my $logFileName;
my $packet_len    = 0;
my $isEOF         = 0;
my $lineno        = 0;                                       
my $num_csv_lines = 0; 

our %packet_counts = ();

use constant ISAGNAV_TS_PACKET => 0x150B; 
use constant LOG_SNS_DSPS_PWR_C   => 0x151B;
use constant LOG_SNS_QMD_CONFIG_C => 0x151D;
use constant LOG_SNS_QMD_RESULT_C => 0x151E;
use constant LOG_SNS_QMD_REPORT_C => 0x151F;

#use constant LOG_SNS_FNS_CONFIG_C   => 0x1523;    # Not supported
#use constant LOG_SNS_FNS_RESULT_C   => 0x1524;    # Not supported
#use constant LOG_SNS_FNS_REPORT_C   => 0x1525;    # Not supported
#use constant LOG_SNS_BTE_CONFIG_C   => 0x1528;    # Not supported
#use constant LOG_SNS_BTE_RESULT_C   => 0x1529;    # Not supported
#use constant LOG_SNS_BTE_REPORT_C   => 0x152A;    # Not supported
    
use constant LOG_SNS_GYRO_SIMP_CAL_CONFIG_C => 0x152B;
use constant LOG_SNS_GYRO_SIMP_CAL_RESULT_C => 0x152C;
use constant LOG_SNS_GYRO_SIMP_CAL_REPORT_C => 0x152D;

use constant LOG_SNS_QUAT_CONFIG_C          => 0x153C;        
use constant LOG_SNS_QUAT_RESULT_C          => 0x153D;
use constant LOG_SNS_QUAT_REPORT_C          => 0x153E;

use constant LOG_SNS_GRAVITY_CONFIG_C       => 0x153F;        
use constant LOG_SNS_GRAVITY_RESULT_C       => 0x1540;        
use constant LOG_SNS_GRAVITY_REPORT_C       => 0x1541;

#use constant LOG_SNS_FULL_CALIBRATION_C   => 0x1542;    # Not supported
use constant LOG_SNS_DRV_MD_IRQ_C      => 0x1559;

use constant LOG_SNS_MAG_CAL_CONFIG_C           => 0x155A;    
use constant LOG_SNS_MAG_CAL_RESULT_C           => 0x155B; 
use constant LOG_SNS_MAG_CAL_REPORT_C           => 0x155C; 

use constant LOG_SNS_ROTATION_VECTOR_CONFIG_C   => 0x155F;    
use constant LOG_SNS_ROTATION_VECTOR_RESULT_C   => 0x1560;     
use constant LOG_SNS_ROTATION_VECTOR_REPORT_C   => 0x1561;     

use constant LOG_SNS_FMV_CONFIG_C               => 0x1562;    
use constant LOG_SNS_FMV_QUAT_UPDATE_C          => 0x1563;     
use constant LOG_SNS_FMV_MAG_UPDATE_C           => 0x1564;     
use constant LOG_SNS_FMV_GYRO_UPDATE_C          => 0x1565;     
use constant LOG_SNS_FMV_REPORT_C               => 0x1566;     

#use constant LOG_SNS_TIME_SERVICE_OFFSETS_C   => 0x158F;    # Not supported
    
use constant LOG_SNS_INTEG_ANGLE_CONFIG_C       => 0x159B; 
use constant LOG_SNS_INTEG_ANGLE_RESULT_C       => 0x159C; 
use constant LOG_SNS_INTEG_ANGLE_REPORT_C       => 0x159D; 
                                     
use constant LOG_SNS_GYRO_TAP_CONFIG_C          => 0x159E; 
use constant LOG_SNS_GYRO_TAP_RESULT_C          => 0x159F; 
use constant LOG_SNS_GYRO_TAP_REPORT_C          => 0x15A0; 
                                     
use constant LOG_SNS_BASIC_GESTURES_CONFIG_C    => 0x15A1; 
use constant LOG_SNS_BASIC_GESTURES_RESULT_C    => 0x15A2; 
use constant LOG_SNS_BASIC_GESTURES_REPORT_C    => 0x15A3; 
                                     
use constant LOG_SNS_FACING_CONFIG_C            => 0x15A4; 
use constant LOG_SNS_FACING_RESULT_C            => 0x15A5; 
use constant LOG_SNS_FACING_REPORT_C            => 0x15A6; 

#use constant LOG_SNS_ALGO_INPUT_C              => 0x15A9;    # Not supported
#use constant LOG_SNS_GYROINT_CONFIG_C          => 0x15AA;    # Not supported
#use constant LOG_SNS_GYROINT_UPDATE_C          => 0x15AB;    # Not supported
#use constant LOG_SNS_GYROINT_REPORT_C          => 0x15AC;    # Not supported
#use constant LOG_SNS_GYROINT_REPORT_REQUEST_C  => 0x15AD;    # Not supported
#use constant LOG_SNS_GYROBUF_CONFIG_C          => 0x15AE;    # Not supported
#use constant LOG_SNS_GYROBUF_REPORT_REQUEST_C  => 0x15AF;    # Not supported
#use constant LOG_SNS_GYROBUF_REPORT_C          => 0x15B0;    # Not supported
    
use constant LOG_SNS_ACCEL_CAL_CONFIG_C         => 0x15B8;
use constant LOG_SNS_ACCEL_CAL_RESULT_C         => 0x15B9; 
use constant LOG_SNS_ACCEL_CAL_REPORT_C         => 0x15BA; 

use constant LOG_SNS_PED_CONFIG_C               => 0x1637;
use constant LOG_SNS_PED_RESULT_C               => 0x1638;
use constant LOG_SNS_PED_REPORT_C               => 0x1639;

use constant LOG_SNS_QMAG_CAL_CONFIG_C          => 0x163A;    # SNS QMAG Cal Config  NOT TESTED!
use constant LOG_SNS_QMAG_CAL_RESULT_C          => 0x163B;    # SNS QMAG Cal Result  NOT TESTED!
use constant LOG_SNS_QMAG_CAL_REPORT_C          => 0x163C;    # SNS QMAG Cal Report  NOT TESTED!
    
use constant LOG_SNS_PAM_CONFIG_C               => 0x1640;
use constant LOG_SNS_PAM_RESULT_C               => 0x1641;
use constant LOG_SNS_PAM_REPORT_C               => 0x1642;

use constant LOG_SNS_SMD_CONFIG_C               => 0x17F8;
use constant LOG_SNS_SMD_RESULT_C               => 0x17F9;
use constant LOG_SNS_SMD_REPORT_C               => 0x17FA;

use constant LOG_SENSOR_FIFO_EVENT_C            => 0x17F3;

use constant LOG_SNS_CMC_CONFIG_C               => 0x17EA;
use constant LOG_SNS_CMC_RESULT_C               => 0x17EB;
use constant LOG_SNS_CMC_REPORT_C               => 0x17EC;
use constant LOG_SNS_DB_CONFIG_C                => 0x17ED;
use constant LOG_SNS_DB_RESULT_C                => 0x17EE;
use constant LOG_SNS_DB_REPORT_C                => 0x17EF;
use constant LOG_SNS_CMC_RESULT2_C              => 0x17F0;

use constant LOG_SNS_LATENCY_SAMPLING_POLL_C    => 0x17FB;
use constant LOG_SNS_LATENCY_SAMPLING_DRI_C     => 0x17FC;
use constant LOG_SNS_LATENCY_DELIVERY_C         => 0x17FD;

use constant LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C => 0x17FE;       # For Wearables, version 255 of this packet is hijacked for QHeart
use constant LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C => 0x17FF;       # For Wearables, version 255 of this packet is hijacked for QHeart
use constant LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C => 0x1800;       # For Wearables, version 255 of this packet is hijacked for QHeart

#use constant   => 0x1834;   # SNS Run-Time Tuning Request              # Not supported - obsolete
#use constant   => 0x1835;   # SNS Run-Time Tuning Response             # Not supported - obsolete
#use constant   => 0x1836;   # SNS BMA2X2 Tune Double-Tap               # Not supported - obsolete

use constant LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C  => 0x183A;   # SNS Geomagnetic Rotation Vector Config   
use constant LOG_SNS_GEOMAG_ROT_VEC_RESULT_C  => 0x183B;   # SNS Geomagnetic Rotation Vector Result   
use constant LOG_SNS_GEOMAG_ROT_VEC_REPORT_C  => 0x183C;   # SNS Geomagnetic Rotation Vector Report   

use constant LOG_SNS_PED_ALIGN_CONFIG_C       => 0x186C;
use constant LOG_SNS_PED_ALIGN_RESULT1_C      => 0x186D;
use constant LOG_SNS_PED_ALIGN_RESULT2_C      => 0x186E;
use constant LOG_SNS_PED_ALIGN_REPORT_C       => 0x186F;

use constant LOG_SNS_TILT_DETECTOR_CONFIG_C   => 0x1887;   
use constant LOG_SNS_TILT_DETECTOR_RESULT_C   => 0x1888;
use constant LOG_SNS_TILT_DETECTOR_REPORT_C   => 0x1889;

use constant LOG_SNS_UIMAGE                     => 0x188D;

use constant LOG_SNS_DPC_CONFIG_C               => 0x189B;
use constant LOG_SNS_DPC_RESULT_C               => 0x189C;
use constant LOG_SNS_DPC_REPORT_C               => 0x189D;

use constant LOG_SNS_TILT_W_DETECTOR_CONFIG_C   => 0x18B7;
use constant LOG_SNS_TILT_W_DETECTOR_RESULT_C   => 0x18B8;
use constant LOG_SNS_TILT_W_DETECTOR_REPORT_C   => 0x18B9;

use constant LOG_SNS_QHEART_CONFIG_C            => 0x18BA;
use constant LOG_SNS_QHEART_RESULT_C            => 0x18BB;
use constant LOG_SNS_QHEART_REPORT_C            => 0x18BC;

use constant LOG_SNS_SYNC_PROXY_CLIENT_C        => 0x18C2;

use constant LOG_SNS_IOD_CONFIG_C             => 0x1918;
use constant LOG_SNS_IOD_RESULT_C             => 0x1919;
use constant LOG_SNS_IOD_REPORT_C             => 0x191A;
use constant LOG_SNS_IOD_AUTOCAL_CONFIG_C     => 0x191B;
use constant LOG_SNS_IOD_AUTOCAL_RESULT_C     => 0x191C;
use constant LOG_SNS_IOD_AUTOCAL_REPORT_C     => 0x191D;


#########################################################################################

sub skip_bytes {
   my $num_bytes = shift;

   if ( $num_bytes) {
      my $buffer;
      my $bytes_read =  read( INFILE, $buffer, $num_bytes, 0);
      if ( $bytes_read <= 0) {
        $isEOF = 1;
      }
      $packet_len -= $num_bytes;
   }
}

sub get_bytes {
  my $num_bytes = shift;

  my @ret_array;
  my ($i, $buffer);

  for( $i = 0; $i < $num_bytes; $i++) {
    if ( read( INFILE, $buffer, 1, 0) <= 0) {
      $isEOF = 1;
      last;
    }
    $packet_len -= 1;
    $ret_array[$i] = ord($buffer);
  }

  return( @ret_array);
}

sub get_uint8 {
  my @rv = get_bytes(1);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x", $rv[0]);
  my $uint8 = unpack "C", reverse pack "H*", $hex_string;
  return $uint8;
}

sub get_int8 {
  my @rv = get_bytes(1);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x", $rv[0]);
  my $int8 = unpack "c", reverse pack "H*", $hex_string;
  return $int8;
}

sub get_uint16 {
  my @rv = get_bytes(2);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x%02x", $rv[1], $rv[0]);
  my $uint16 = unpack "S", reverse pack "H*", $hex_string;  
  return $uint16;
}

sub get_int16 {
  my @rv = get_bytes(2);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x%02x", $rv[1], $rv[0]);
  my $int16 = unpack "s", reverse pack "H*", $hex_string;  
  return $int16;
}

sub get_uint32 {
  my @rv = get_bytes(4);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x%02x%02x%02x", $rv[3], $rv[2], $rv[1], $rv[0]);
  my $uint32 = unpack "L", reverse pack "H*", $hex_string;    
  return $uint32;
}

sub get_int32 {
  my @rv = get_bytes(4);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x%02x%02x%02x", $rv[3], $rv[2], $rv[1], $rv[0]);
  my $int32 = unpack "l", reverse pack "H*", $hex_string;  
  return $int32;
}

sub get_uint64 {
  my @rv = get_bytes(8);
  if ( $isEOF) { return 0; }
  my $uint64 = 0;

  for (my $i = 7; $i >= 0; $i--) {
    $uint64 = 256*$uint64 + $rv[$i];
  }

  return $uint64;
}

sub get_float32 {
  my @b = get_bytes(4);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x%02x%02x%02x", $b[3], $b[2], $b[1], $b[0]); 
  return unpack "f", reverse pack "H*", $hex_string;
}

sub get_double64 {
  my @b = get_bytes(8);
  if ( $isEOF) { return 0; }
  my $hex_string = sprintf("%02x%02x%02x%02x%02x%02x%02x%02x", $b[7], $b[6], $b[5], $b[4], $b[3], $b[2], $b[1], $b[0]);
  return unpack "d", reverse pack "H*", $hex_string;
}

sub get_string {
  my $len = shift;

  if ( $len == 0) {              
     return "";                  
  }                              

  my @rv = get_bytes($len);
  if ( $isEOF) { return ""; }

  my $C;
  for (my $i = 0; $i < $len; $i++) {
    $C = $C."C";
  }

  return pack($C, @rv);
}

#########################################################################################

# -------------------------------------
# LOG_SNS_DSPS_PWR_C
# Version 2
# -------------------------------------
sub process_dsps_pwr{
   my $packet_type   = shift;

   my $version     = get_uint8();
   if ( $version > 2) {
      die "\nprocess_dsps_power() \$version > 2, got $version";
   }

   my $ts          = get_uint64(); 
   my $power_state = get_uint32();

   my $csvline = "$packet_type, $version, $ts, $power_state\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_QMD_CONFIG_C
# Version 2
# -------------------------------------
sub process_qmd_config {
   my $packet_type   = shift;

   my $version    = get_uint8();
   if ( $version > 2) {
      die "\nprocess_qmd_config() \$version > 2, got $version";
   }
   my $ts            = get_uint64();            
   my $sample_rate   = get_uint32();
   my $enable_amd    = get_uint8();
   my $enable_vmd    = get_uint8();
   my $enable_rmd    = get_uint8();
   my $instance_id   = get_uint8();

   my $csvline = "$packet_type, $version, $ts, $sample_rate, $enable_amd, $enable_vmd, $enable_rmd, $instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_QMD_RESULT_C
# Version 2
# -------------------------------------
sub process_qmd_result {
   my $packet_type   = shift;

   my $version    = get_uint8();
   if ( $version > 2) {
      die "\nprocess_qmd_result() \$version > 2, got $version";
   }
   my $ts            = get_uint64();            
   my $accelX        = get_int32();                   # changed to int per Kaushik
   my $accelY        = get_int32();                   # changed to int per Kaushik 
   my $accelZ        = get_int32();                   # changed to int per Kaushik 
   my $amd_result    = get_uint8();
   my $vmd_result    = get_uint8();
   my $rmd_result    = get_uint8();
   my $instance_id   = get_uint8();

   my $csvline = "$packet_type, $version, $ts, $accelX, $accelY, $accelZ, $amd_result, $vmd_result, $rmd_result, $instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_QMD_REPORT_C
# Version 2
# -------------------------------------
sub process_qmd_report {
   my $packet_type   = shift;

   my $version    = get_uint8();
   if ( $version > 2) {
      die "\nprocess_qmd_report() \$version > 2, got $version";
   }
   my $ts            = get_uint64();            
   my $report_id     = get_uint32();
   my $report_type   = get_uint8();
   my $client_id     = get_uint8();
   my $qmd_result    = get_uint8();
   my $service_id    = get_uint8();
   my $instance_id   = get_uint8();

   my $csvline = "$packet_type, $version, $ts, $report_id, $report_type, $client_id, $qmd_result, $service_id, $instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GYRO_SIMP_CAL_CONFIG_C
# Version Unknown
# -------------------------------------
sub process_gyro_simp_cal_config {

   my $packet_type      = shift;
   my $version          = get_uint8();
   
   my $csvline;
   
   if ($version < 255) {
      
      my $timestamp     = get_uint64();
      my $sample_rate   = get_uint32();      # sampling rate of gyro data Hz in Q16
      my $instance      = get_uint8();       # algorithm instance id
      
      $csvline = "$packet_type,$version,$timestamp,$sample_rate,$instance\n";
   }
   else {
   
      # -------------------------------------
      # LOG_SNS_QMAG_CAL_CONFIG_C  This is temporary!!!!  Need to use the actual QMAG packet!!!
      # -------------------------------------
 
      my $timestamp_type   = get_uint8();          
      my $timestamp        = get_uint64();
   
      my $sample_rate_mag            = get_uint32();
      my $sample_rate_accel          = get_uint32();
      my $cal_algo_type              = get_uint8();
      my $cal_cycle_rate             = get_uint32();
   
      $csvline = "5690,255,$timestamp_type,$timestamp,$sample_rate_mag,$sample_rate_accel,$cal_algo_type,$cal_cycle_rate\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GYRO_SIMP_CAL_RESULT_C
# Version Unknown
# -------------------------------------
sub process_gyro_simp_cal_result {

   my $packet_type   = shift;
   my $version    = get_uint8();
   my $csvline ;
   
   if ($version < 255) {
      
      my $timestamp     = get_uint64();

      my $gyro_x        = get_int32();
      my $gyro_y        = get_int32();
      my $gyro_z        = get_int32();
   
      my $gyro_zbx      = get_int32();
      my $gyro_zby      = get_int32();
      my $gyro_zbz      = get_int32();
   
      my $instance_id   = get_uint8();
   
      $csvline = "$packet_type,$version,$timestamp,$gyro_x,$gyro_y,$gyro_z,$gyro_zbx,$gyro_zby,$gyro_zbz,$instance_id\n";
   }
   else {
   
      # -------------------------------------
      # LOG_SNS_QMAG_CAL_RESULT_C  This is temporary!!!!  Need to use the actual QMAG packet!!!
      # -------------------------------------
      my $timestamp_type   = get_uint8();          
      my $timestamp        = get_uint64();
   
      my $input_type                   = get_uint8();
      my $input_mag_x                  = get_int32();
      my $input_mag_y                  = get_int32();
      my $input_mag_z                  = get_int32();   
      my $input_accel_x                = get_int32();     
      my $input_accel_y                = get_int32();
      my $input_accel_z                = get_int32();        
      my $accel_input_variance         = get_double64();        
      my $mag_input_variance           = get_double64();        
      my $offset_hi_unfiltered_x       = get_float32();        
      my $offset_hi_unfiltered_y       = get_float32();     
      my $offset_hi_unfiltered_z       = get_float32();        
      my $radius_hi                    = get_float32();        
      my $unfiltered_accuracy          = get_uint8();        
      my $accuracy_published           = get_uint8();        
      my $cal_algo_type                = get_uint8();      
      my $mag_zero_bias_published_x    = get_int32();     
      my $mag_zero_bias_published_y    = get_int32();
      my $mag_zero_bias_published_z    = get_int32();
      my $offset_time                  = get_uint32();
      my $hard_reset                   = get_uint8();        
      my $soft_reset                   = get_uint8();
   
      $csvline = "5691,255,$timestamp_type,$timestamp,";
      $csvline .= "$input_type,$input_mag_x,$input_mag_y,$input_mag_z,$input_accel_x,$input_accel_y,$input_accel_z,";
      $csvline .= "$accel_input_variance,$mag_input_variance,$offset_hi_unfiltered_x,$offset_hi_unfiltered_y,$offset_hi_unfiltered_z,";
      $csvline .= "$radius_hi,$unfiltered_accuracy,$accuracy_published,$cal_algo_type,$mag_zero_bias_published_x,$mag_zero_bias_published_y,";
      $csvline .= "$mag_zero_bias_published_z,$offset_time,$hard_reset,$soft_reset\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GYRO_SIMP_CAL_REPORT_C
# Version Unknown
# -------------------------------------
sub process_gyro_simp_cal_report {
   
   my $packet_type   = shift;
   my $version    = get_uint8();
   my $csvline;
   
   if ($version < 255) {
      
      my $timestamp     = get_uint64();
      my $gyro_x        = get_int32();
      my $gyro_y        = get_int32();
      my $gyro_z        = get_int32();
   
      my $gyro_zbx      = get_int32();
      my $gyro_zby      = get_int32();
      my $gyro_zbz      = get_int32();
   
      $csvline = "$packet_type,$version,$timestamp,$gyro_x,$gyro_y,$gyro_z,$gyro_zbx,$gyro_zby,$gyro_zbz\n";
   }
   else {
      # -------------------------------------
      # LOG_SNS_QMAG_CAL_REPORT_C  This is temporary!!!!  Need to use the actual QMAG packet!!!
      # -------------------------------------
      my $timestamp_type   = get_uint8();          
      my $timestamp        = get_uint64();
   
      my $qmag_x                    = get_int32();
      my $qmag_y                    = get_int32();
      my $qmag_z                    = get_int32();
      my $qmag_zero_bias_corr_x     = get_int32();
      my $qmag_zero_bias_corr_y     = get_int32();
      my $qmag_zero_bias_corr_z     = get_int32();
   
      $csvline = "5692,255,$timestamp_type,$timestamp,$qmag_x,$qmag_y,$qmag_z,$qmag_zero_bias_corr_x,$qmag_zero_bias_corr_y,$qmag_zero_bias_corr_z\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GRAVITY_CONFIG_C
#
# The gravity config log is shared between 2 different algorithms: 
#     Algorithm 1:  Version 1    -> 9-axis QFusion Algo - Rotation Vector & Gravity 
#     Algorithm 2:  Version 100  -> 6-axis QFusion Algo - Orientation 
# -------------------------------------
sub process_gravity_config {
   my $packet_type   = shift;
   my $version       = get_uint8();
   my $ts_type       = get_uint8();
   my $ts            = get_uint64();            

   my $report_period = get_uint32();
   my $sample_rate   = get_uint32();

   my $time_cons_abs = get_uint8();
   my $time_cons_rel = get_uint8();
   my $time_cons_mot = get_uint8();

   my $instance_id   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_period,$sample_rate,$time_cons_abs,$time_cons_rel,$time_cons_mot,$instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GRAVITY_RESULT_C
#
# The gravity result log is shared between 2 different algorithms: 
#     Algorithm 1:  Version 1    -> 9-axis QFusion Algo - Rotation Vector & Gravity 
#     Algorithm 2:  Version 100  -> 6-axis QFusion Algo - Orientation 
# -------------------------------------
sub process_gravity_result {
   my $packet_type = shift;

   my $version    = get_uint8();
   my $ts_type       = get_uint8();
   my $ts            = get_uint64();

   my $gyro_x        = get_float32();    # actually quaternion x/y/z
   my $gyro_y        = get_float32();
   my $gyro_z        = get_float32();

   my $accel_x       = get_int32();                   
   my $accel_y       = get_int32();                   
   my $accel_z       = get_int32();                                           

   my $abs_state     = get_uint8();
   my $rel_state     = get_uint8();

   my $grav_est_x    = get_float32();                   
   my $grav_est_y    = get_float32();                   
   my $grav_est_z    = get_float32();                   

   my $linacc_x      = get_float32();                   
   my $linacc_y      = get_float32();                   
   my $linacc_z      = get_float32();                   

   my $delta_t       = get_int32();                   
   my $alpha         = get_int32();                   

   my $instance_id   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$gyro_x,$gyro_y,$gyro_z,$accel_x, $accel_y, $accel_z,";
   $csvline   .= "$abs_state,$rel_state,$grav_est_x,$grav_est_y,$grav_est_z,$linacc_x,$linacc_y,$linacc_z,";
   $csvline   .= "$delta_t,$alpha,$instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GRAVITY_REPORT_C
#
# The gravity report log is shared between 2 different algorithms: 
#     Algorithm 1:  Version 1    -> 9-axis QFusion Algo - Rotation Vector & Gravity 
#     Algorithm 2:  Version 100  -> 6-axis QFusion Algo - Orientation 
# -------------------------------------
sub process_gravity_report {
   my $packet_type = shift;

   my $version    = get_uint8();
   my $ts_type       = get_uint8();
   my $ts            = get_uint64();

   my $report_id     = get_int32();
   my $report_type   = get_uint8();
   my $client_id     = get_uint8();

   my $grav_x        = get_float32();                   
   my $grav_y        = get_float32();                   
   my $grav_z        = get_float32();                   

   my $linacc_x      = get_float32();                   
   my $linacc_y      = get_float32();                   
   my $linacc_z      = get_float32();                   

   my $instance_id   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,";
   $csvline   .= "$grav_x,$grav_y,$grav_z,$linacc_x,$linacc_y,$linacc_z,$instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------
# LOG_SNS_QUAT_CONFIG_C
# Version Unknown
# ----------------------------
sub process_quat_config {
   my $packet_type   = shift;
   my $version       = get_uint8();
   my $ts_type       = get_uint8();
   my $ts            = get_uint64();            

   my $report_period = get_uint32();
   my $sample_rate   = get_uint32();

   my $instance_id   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_period,$sample_rate,$instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}
   
# ----------------------------
# LOG_SNS_QUAT_RESULT_C
# Version Unknown
# ----------------------------   
sub process_quat_result {
    my $packet_type = shift;
    
    my $version  = get_uint8();
    my $ts_type  = get_uint8();
    my $ts       = get_uint64();
    
    my $gyro_x   = get_int32();
    my $gyro_y   = get_int32();
    my $gyro_z   = get_int32();
    
    my $quat0    = get_float32();            # Qfusion
    my $quat1    = get_float32();            # +
    my $quat2    = get_float32();            # + 
    my $quat3    = get_float32();            # + 
    
    my $delta_t  = get_int32(); 
 
    my $instance_id = get_uint8();

    my $csvline  = sprintf( "%d,%d,%d,$ts,%d,%d,%d,%f,%f,%f,%f,%d,%d\n",      # Qfusion
                            $packet_type,
                            $version,
                            $ts_type,
                            $gyro_x, $gyro_y, $gyro_z,       
                            $quat0, $quat1, $quat2, $quat3,
                            $delta_t,
                            $instance_id);
    print CSV_FILE $csvline;
    $num_csv_lines++;
}

# ----------------------------
# LOG_SNS_QUAT_REPORT_C
# Version Unknown
# ----------------------------
sub process_quat_report {
    my $packet_type = shift;
    
    my $version  = get_uint8();
    my $ts_type  = get_uint8();
    my $ts       = get_uint64();
    
    my $rpt_id   = get_int32();
    my $rpt_typ   = get_int8();
    my $clnt_id   = get_int8();
    
    my $quat_rslt1    = get_float32();       # Qfusion
    my $quat_rslt2    = get_float32();       # Qfusion
    my $quat_rslt3    = get_float32();       # Qfusion
    my $quat_rslt4    = get_float32();       # Qfusion
       
     my $instance_id = get_uint8();

    my $csvline  = sprintf( "%d,%d,%d,$ts,%d,%d,%d,%f,%f,%f,%f,%d\n",      # Qfusion
                            $packet_type,
                            $version,
                            $ts_type,
                            $rpt_id, $rpt_typ, $clnt_id,       
                            $quat_rslt1, $quat_rslt2,$quat_rslt3,$quat_rslt4,                            
                            $instance_id);
    print CSV_FILE $csvline;
    $num_csv_lines++;
}


# -----------------------------------
#  LOG_SNS_MAG_CAL_CONFIG Qfusion
# Version Unknown
# -----------------------------------
sub process_mag_cal_config {
   my $packet_type   = shift;
   my $version       = get_uint8();
   my $ts_type       = get_uint8();
   my $ts            = get_uint64();            

   my $report_period = get_uint32();
   my $sample_rate   = get_uint32();

   my $instance_id   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_period,$sample_rate,$instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}


# -----------------------------------
#  LOG_SNS_MAG_CAL_RESULT Qfusion
# Version Unknown
# -----------------------------------
sub process_mag_cal_result {
    my $packet_type = shift;
    
    my $version      = get_uint8();
    my $ts_type      = get_uint8();
    my $ts           = get_uint64();
    
    my $mag_x        = get_int32();
    my $mag_y        = get_int32();
    my $mag_z        = get_int32();
    
    my $magcal_x     = get_int32();
    my $magcal_y     = get_int32();
    my $magcal_z     = get_int32();
    
    my $magcalbias_x = get_int32();
    my $magcalbias_y = get_int32();
    my $magcalbias_z = get_int32();

    my $accuracy     = get_uint8();
    my $instance_id  = get_uint8();

    my $csvline  = sprintf( "%d,%d,%d,$ts,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",      # Qfusion
                            $packet_type,
                            $version,
                            $ts_type,
                            $mag_x, $mag_y, $mag_z,
                            $magcal_x, $magcal_y, $magcal_z,
                            $magcalbias_x, $magcalbias_y, $magcalbias_z,
                            $accuracy,
                            $instance_id);
    print CSV_FILE $csvline;
    $num_csv_lines++;
}

# -------------------
#  LOG_SNS_FMV_CONFIG
# Version Unknown
# -------------------
sub process_fmv_config {
   my $packet_type   = shift;
   my $version       = get_uint8();
   my $ts_type       = get_uint8();
   my $ts            = get_uint64();            

   my $report_period = get_uint32();
   my $sample_rate   = get_uint32();

   my $num_accuracy_bins   = get_uint8();

   my $accuracy_bin_tcs0   = get_float32();  # is this right or dynamic $num_accuracy_bins ?
   my $accuracy_bin_tcs1   = get_float32(); 
   my $accuracy_bin_tcs2   = get_float32(); 
   my $accuracy_bin_tcs3   = get_float32(); 

   my $gyro_gap_thresh     = get_float32();
   my $mag_gap_thresh      = get_float32(); 
   my $min_turn_rate       = get_float32(); 
   my $max_mag_innovation  = get_float32(); 

   my $instance_id   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_period,$sample_rate,$num_accuracy_bins,";
   $csvline   .= "$accuracy_bin_tcs0,$accuracy_bin_tcs1,$accuracy_bin_tcs2,$accuracy_bin_tcs3,";
   $csvline   .= "$gyro_gap_thresh,$mag_gap_thresh,$min_turn_rate,$max_mag_innovation,$instance_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------------
#  LOG_SNS_FMV_QUAT_UPDATE_C
# Version Unknown
# --------------------------
sub process_fmv_quat_update {
   my $packet_type = shift;

   my $version      = get_uint8();
   my $ts_type      = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS

   my $quat_ts      = get_uint64();
   my $fmv_ts       = get_uint64();

   my $q0           = get_float32();
   my $q1           = get_float32();
   my $q2           = get_float32();
   my $q3           = get_float32();

   my $bx           = get_float32();
   my $by           = get_float32();
   my $bz           = get_float32();

   my $accuracy     = get_uint8();
   my $instance     = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$quat_ts,$fmv_ts,$q0,$q1,$q2,$q3,$bx,$by,$bz,$accuracy,$instance\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------
#  LOG_SNS_FMV_MAG_UPDATE_C
# Version Unknown
# -------------------------
sub process_fmv_mag_update {
   my $packet_type = shift;

   my $version      = get_uint8();
   my $ts_type      = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts_mag       = get_uint64();
   my $ts_quat      = get_uint64();

   my $gyrox        = get_float32();  
   my $gyroy        = get_float32();
   my $gyroz        = get_float32();

   my $bx           = get_float32();
   my $by           = get_float32();
   my $bz           = get_float32();

   my $fbx          = get_float32();  
   my $fby          = get_float32();
   my $fbz          = get_float32();

   my $accuracy     = get_uint8();
   my $instance     = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts_mag,$ts_quat,$gyrox,$gyroy,$gyroz,$bx,$by,$bz,$fbx,$fby,$fbz,$accuracy,$instance\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------------
#  LOG_SNS_FMV_GYRO_UPDATE_C
# Version Unknown
# --------------------------
sub process_fmv_gyro_update {
   my $packet_type = shift;

   my $version      = get_uint8();
   my $ts_type      = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts           = get_uint64();

   my $gyroX        = get_float32();
   my $gyroY        = get_float32();
   my $gyroZ        = get_float32();

   my $instance     = get_uint8();  # stub missing algo_instance???
   
   my $csvline = "$packet_type,$version,$ts_type,$ts,$gyroX,$gyroY,$gyroZ,$instance\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ---------------------
#  LOG_SNS_FMV_REPORT_C
# Version 1
# ---------------------
sub process_fmv_report {
   my $packet_type = shift;

   my $version      = get_uint8();
   my $ts_type      = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   
   my $ts;
   if ($packet_len < 30) {    # This is a workaround because the timestamp should be 64bit, but SW implemented as 32bit
      $ts = get_uint32();
   } else {
      $ts = get_uint64();
   }

   my $report_id    = get_int32();
   my $report_type  = get_uint8();     # 0 unknown, 1 periodic, 2 asynchronous, 3 synchronous
   my $client_id    = get_uint8();

   my $fbx          = get_float32();
   my $fby          = get_float32();
   my $fbz          = get_float32();

   my $accuracy     = get_uint8();
   my $instance     = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,$fbx,$fby,$fbz,$accuracy,$instance\n"; 
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------------
#  LOG_SNS_ROTATION_VECTOR_CONFIG_C
# Version Unknown
# ----------------------------------
sub process_rotv_config {
   my $packet_type  = shift;

   my $version       = get_uint8();
   my $ts_type       = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts            = get_uint64();

   my $report_period = get_uint32();
   my $sample_rate   = get_uint32();

   my $coord_sys     = get_uint8();
   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_period,$sample_rate,$coord_sys,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------------
#  LOG_SNS_ROTATION_VECTOR_RESULT_C
# Version Unknown
# ----------------------------------
sub process_rotv_result {
   my $packet_type  = shift;

   my $version      = get_uint8();
   my $ts_type      = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts           = get_uint64();

   my $gravx        = get_float32();
   my $gravy        = get_float32();
   my $gravz        = get_float32();
   my $grav_ts      = get_uint64();
   my $grav_acc     = get_uint8();

   my $fmx          = get_float32();
   my $fmy          = get_float32();
   my $fmz          = get_float32();
   my $fm_ts        = get_uint64();
   my $fm_acc       = get_uint8();

   my $rotva        = get_float32();
   my $rotvb        = get_float32();
   my $rotvc        = get_float32();
   my $rotvd        = get_float32();

   my $accuracy     = get_uint8();
   my $coord_sys    = get_uint8();
   my $instance     = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$gravx,$gravy,$gravz,$grav_ts,$grav_acc,";
   $csvline   .= "$fmx,$fmy,$fmz,$fm_ts,$fm_acc,$rotva,$rotvb,$rotvc,$rotvd,$accuracy,$coord_sys,$instance\n"; 

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------------
#  LOG_SNS_ROTATION_VECTOR_REPORT_C
# Version Unknown
# ----------------------------------
sub process_rotv_report {
   my $packet_type  = shift;

   my $version       = get_uint8();
   my $ts_type       = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts            = get_uint64();

   my $report_id     = get_int32();
   my $report_type   = get_uint8();
   my $client_id     = get_uint8();

   my $rotva        = get_float32();
   my $rotvb        = get_float32();
   my $rotvc        = get_float32();
   my $rotvd        = get_float32();

   my $accuracy     = get_uint8();
   my $coord_sys    = get_uint8();
   my $instance     = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,";
   $csvline   .= "$rotva,$rotvb,$rotvc,$rotvd,$accuracy,$coord_sys,$instance\n"; 

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------------
#  ISAGNAV_TS_PACKET
# Version Unknown
# ----------------------------------
sub process_isagnav_ts {
  
   my $packet_type = shift;
   my $ver  = get_uint8(); 
   my $pe_InfoValid = get_uint8();
   my $pe_TTValid = get_uint8(); 
   my $pe_ComputeValid = get_uint8(); 

   my $q_TimeTickAtGpsTOA = get_uint32();         
   my $w_GpsWeek = get_bytes(2);         
   my $q_GpsMs = get_uint32();         

   my $q_OurTxMs = get_bytes(4);     
   my $q_TheirRxMs = get_uint32();   
   my $q_TheirTxMs = get_uint32();  
   my $q_OurRxMs = get_bytes(4);            

   my $w_Rtt = get_bytes(2);        
   my $gps_week_offset = get_uint16; 
   my $gps_ms_in_week_offset = get_uint32;
   #my $w_UncPpm = get_bytes(2);
   #my $q_TimingJitter = get_bytes(4);
   #my $remain = get_bytes($packet_len);

  
   my $csvline = "$packet_type,$ver,$pe_InfoValid,$pe_TTValid,$pe_ComputeValid,$q_TimeTickAtGpsTOA,$w_GpsWeek,$q_GpsMs,$q_OurTxMs,";
   $csvline   .= "$q_TheirRxMs,$q_TheirTxMs,$q_OurRxMs,$w_Rtt,$gps_week_offset,$gps_ms_in_week_offset\n"; 

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------
# LOG_SNS_INTEG_ANGLE_CONFIG_C
# Version Unknown
# ----------------------------
sub process_integ_angle_config {
   my $packet_type  = shift;

   my $version       = get_uint8();
   my $ts_type       = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts            = get_uint64();

   my $sample_rate      = get_int32();
   my $clip_threshold   = get_int32();
   my $instance         = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$sample_rate,$clip_threshold,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------
# LOG_SNS_INTEG_ANGLE_RESULT_C
# Version Unknown
# ----------------------------
sub process_integ_angle_result {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $g0         = get_int32();
   my $g1         = get_int32();
   my $g2         = get_int32();

   my $ia0        = get_int32();
   my $ia1        = get_int32();
   my $ia2        = get_int32();

   my $instance   = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$g0,$g1,$g2,$ia0,$ia1,$ia2,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ----------------------------
# LOG_SNS_INTEG_ANGLE_REPORT_C
# Version Unknown
# ----------------------------
sub process_integ_angle_report {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $report_id     = get_int32();
   my $report_type   = get_uint8();
   my $client_id     = get_uint8();

   my $ia0           = get_int32();
   my $ia1           = get_int32();
   my $ia2           = get_int32();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,$ia0,$ia1,$ia2,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------
# LOG_SNS_GYRO_TAP_CONFIG_C
# Version Unknown
# -------------------------
sub process_gyro_tap_config {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   print "gyro tap config not yet implemented\n";

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,...,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------
# LOG_SNS_GYRO_TAP_RESULT_C
# Version Unknown
# -------------------------
sub process_gyro_tap_result {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $g0         = get_int32();
   my $g1         = get_int32();
   my $g2         = get_int32();

   my $a0         = get_int32();
   my $a1         = get_int32();
   my $a2         = get_int32();

   my $tap_event  = get_int32();
   my $algo_state = get_int32();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$g0,$g1,$g2,$a0,$a1,$a2,$tap_event,$algo_state,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------
# LOG_SNS_GYRO_TAP_REPORT_C
# Version Unknown
# -------------------------
sub process_gyro_tap_report {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $report_id  = get_int32();
   my $report_type= get_uint8();
   my $client_id  = get_uint8();
   my $tap_event  = get_int32();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,$tap_event,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------
# LOG_SNS_BASIC_GESTURES_CONFIG_C
# Version Unknown
# -------------------------------
sub process_basic_gestures_config {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $sample_rate   = get_uint32();
   my $sleep         = get_int32();
   my $push_thresh   = get_uint32();
   my $pull_thresh   = get_uint32();
   my $shake_thresh  = get_uint32();

   my $config1       = get_int32();
   my $config2       = get_int32();
   my $config3       = get_int32();
   my $config4       = get_int32();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$sample_rate,$sleep,$push_thresh,$pull_thresh,$shake_thresh";
   $csvline   .= ",$config1,$config2,$config3,$config4,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------
# LOG_SNS_BASIC_GESTURES_RESULT_C
# Version Unknown
# -------------------------------
sub process_basic_gestures_result {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $accel_x    = get_int32();
   my $accel_y    = get_int32();
   my $accel_z    = get_int32();

   my $motion_state  = get_uint8();
   my $basic_state   = get_uint8();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$accel_x,$accel_y,$accel_z,$motion_state,$basic_state,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------
# LOG_SNS_BASIC_GESTURES_REPORT_C
# Version Unknown
# -------------------------------
sub process_basic_gestures_report {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $report_id     = get_int32();
   my $report_type   = get_uint8();
   my $client_id     = get_uint8();
   my $basic_state   = get_uint8();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,$basic_state,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}


# -----------------------
# LOG_SNS_FACING_CONFIG_C
# Version Unknown
# -----------------------
sub process_facing_config {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $sample_rate   = get_uint32();
   my $threshold     = get_int32();
   my $report_neutral= get_int32();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$sample_rate,$threshold,$report_neutral,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -----------------------
# LOG_SNS_FACING_RESULT_C
# Version Unknown
# -----------------------
sub process_facing_result {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $accel_x    = get_int32();
   my $accel_y    = get_int32();
   my $accel_z    = get_int32();

   my $motion_state  = get_uint8();
   my $facing_state  = get_uint8();
   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$accel_x,$accel_y,$accel_z,$motion_state,$facing_state,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -----------------------
# LOG_SNS_FACING_REPORT_C
# Version Unknown
# -----------------------
sub process_facing_report {
   my $packet_type  = shift;

   my $version    = get_uint8();
   my $ts_type    = get_uint8();     # 0 DSPS, 1 APPS, 2 MODEM, 3 GPS
   my $ts         = get_uint64();

   my $report_id     = get_int32();
   my $report_type   = get_uint8();
   my $client_id     = get_uint8();
   my $facing_state  = get_uint8();

   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts_type,$ts,$report_id,$report_type,$client_id,$facing_state,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------------
# LOG_SNS_ACCEL_CAL_CONFIG_C
# Version Unknown
# --------------------------
sub process_accel_cal_config {
   my $packet_type   = shift;

   my $version       = get_uint8();
   my $ts            = get_uint64();

   my $sample_rate   = get_uint32();
   my $instance      = get_uint8();

   my $csvline = "$packet_type,$version,$ts,$sample_rate,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ---------------------------
# LOG_SNS_ACCEL_CAL_RESULT_C
# Version Unknown
# ---------------------------
sub process_accel_cal_result {
   my $packet_type            = shift;

   my $version                = get_uint8();
   my $ts                     = get_uint64();   # DSPS timer ticks

   my $accel_x                = get_int32();
   my $accel_y                = get_int32();
   my $accel_z                = get_int32();
   my $temp                   = get_int32();

   my $accel_zero_bias_x      = get_int32();
   my $accel_zero_bias_y      = get_int32();
   my $accel_zero_bias_z      = get_int32();

   my $accel_scale_factor_x   = get_int32();
   my $accel_scale_factor_y   = get_int32();
   my $accel_scale_factor_z   = get_int32();

   my $instance               = get_uint8();

   my $csvline = "$packet_type,$version,$ts,$accel_x,$accel_y,$accel_z,$temp,";
   $csvline   .= "$accel_zero_bias_x,$accel_zero_bias_y,$accel_zero_bias_z,"; 
   $csvline   .= "$accel_scale_factor_x,$accel_scale_factor_y,$accel_scale_factor_z,$instance\n"; 

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------------
# LOG_SNS_ACCEL_CAL_REPORT_C
# Version Unknown
# --------------------------
sub process_accel_cal_report {
   my $packet_type            = shift;

   my $version                = get_uint8();
   my $ts                     = get_uint64();   # DSPS timer ticks

   my $accel_x                = get_int32();
   my $accel_y                = get_int32();
   my $accel_z                = get_int32();
   my $temp                   = get_int32();

   my $accel_zero_bias_x      = get_int32();
   my $accel_zero_bias_y      = get_int32();
   my $accel_zero_bias_z      = get_int32();

   my $accel_scale_factor_x   = get_int32();
   my $accel_scale_factor_y   = get_int32();
   my $accel_scale_factor_z   = get_int32();

   my $cal_report_decision    = get_uint8();
   my $temp_op_min            = get_uint32();
   my $count_kf_update        = get_uint64();

   my $covar_accel_x_bias     = get_double64();
   my $covar_accel_y_bias     = get_double64();
   my $covar_accel_z_bias     = get_double64();
   my $covar_accel_x_sf       = get_double64();
   my $covar_accel_y_sf       = get_double64();
   my $covar_accel_z_sf       = get_double64();

   my $kf_accel_x_bias        = get_double64();
   my $kf_accel_y_bias        = get_double64();
   my $kf_accel_z_bias        = get_double64();
   my $kf_accel_x_sf          = get_double64();
   my $kf_accel_y_sf          = get_double64();
   my $kf_accel_z_sf          = get_double64();
###   my $instance               = get_uint8();

   my $csvline = "$packet_type,$version,$ts,$accel_x,$accel_y,$accel_z,$temp,";
   $csvline   .= "$accel_zero_bias_x,$accel_zero_bias_y,$accel_zero_bias_z,"; 
   $csvline   .= "$accel_scale_factor_x,$accel_scale_factor_y,$accel_scale_factor_z,";

   $csvline   .= "$cal_report_decision,$temp_op_min,$count_kf_update,";
   $csvline   .= "$covar_accel_x_bias,$covar_accel_y_bias,$covar_accel_z_bias,$covar_accel_x_sf,$covar_accel_y_sf,$covar_accel_z_sf,";
   $csvline   .= "$kf_accel_x_bias,$kf_accel_y_bias,$kf_accel_z_bias,$kf_accel_x_sf,$kf_accel_y_sf,$kf_accel_z_sf\n";
###   $instance\n"; 

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_CONFIG_C
# Version Unknown
# --------------------
sub process_ped_config {
   my $packet_type   = shift;

   my $version       = get_uint8();
   my $ts            = get_uint64();

   my $sample_rate            = get_uint32();
   my $step_count_threshold   = get_uint32();

   my $step_threshold         = get_float32();
   my $swing_threshold        = get_float32();
   my $step_prob_threshold    = get_float32();

   my $instance      = get_uint8();

   my $csvline  = "$packet_type,$version,$ts,$sample_rate,$step_count_threshold,";
   $csvline    .= "$step_threshold,$swing_threshold,$step_prob_threshold,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_RESULT_C
# Version Unknown
# --------------------
sub process_ped_result {
   my $packet_type   = shift;

   my $version       = get_uint8();
   my $ts            = get_uint64();

   my $accel_x       = get_int32();          
   my $accel_y       = get_int32();
   my $accel_z       = get_int32();

   my $sample_rate      = get_float32();     

   my $client_id        = get_uint8();
   my $reset_stats      = get_uint8();
   my $step_event       = get_uint8();
   my $step_confidence  = get_uint8();

   my $step_count       = get_uint32();
   my $step_count_error = get_int32();
   my $swing_step_count = get_uint32();

   my $step_rate        = get_float32();

   my $instance         = get_uint8();

   my $csvline  = "$packet_type,$version,$ts,$accel_x,$accel_y,$accel_z,$sample_rate,$client_id,$reset_stats,$step_event,";
   $csvline    .= "$step_confidence,$step_count,$step_count_error,$swing_step_count,$step_rate,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_REPORT_C
# Version Unknown
# --------------------
sub process_ped_report {
   my $packet_type   = shift;

   my $version       = get_uint8();
   my $ts            = get_uint64();

   my $report_id        = get_int32();          
   my $report_type      = get_uint8();

   my $client_id        = get_uint8();
   my $step_event       = get_uint8();
   my $step_confidence  = get_uint8();

   my $step_count       = get_uint32();
   my $step_count_error = get_int32();

   my $step_rate        = get_float32();

   my $instance         = get_uint8();

   my $csvline  = "$packet_type,$version,$ts,$report_id,$report_type,$client_id,$step_event,";
   $csvline    .= "$step_confidence,$step_count,$step_count_error,$step_rate,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# #### ## ######## ##### #######

# --------------------
# LOG_SNS_PAM_CONFIG_C
# Version Unknown
# --------------------
sub process_pam_config {
   my $packet_type   = shift;
   my $version       = get_uint8();
   
   my $timestamp_type         = get_uint8();          
   my $timestamp              = get_uint64();
   my $measurement_period     = get_uint32(); 
   my $step_count_threshold   = get_uint32(); 
   my $sample_rate            = get_uint32();  
   my $duty_cycle_on_percent  = get_uint8();  

   my $instance      = get_uint8();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$measurement_period,";
   $csvline    .= "$step_count_threshold,$sample_rate,$duty_cycle_on_percent,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PAM_RESULT_C
# Version Unknown
# --------------------
sub process_pam_result {
   my $packet_type   = shift;
   my $version       = get_uint8();
   
   my $timestamp_type         = get_uint8();          
   my $timestamp              = get_uint64();

   
   my $pedometer_step_count         = get_int32();
   my $motion_state                 = get_uint8();
   my $data_type                    = get_uint8(); 
   my $pedometer_last_step_count    = get_int32(); 
   my $pam_current_step_count       = get_int32();  
   my $pam_last_reported_step_count = get_int32();  
   my $pam_report_decision          = get_uint8();  

   my $instance      = get_uint8();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$pedometer_step_count,";
   $csvline    .= "$motion_state,$data_type,$pedometer_last_step_count,$pam_current_step_count,";
   $csvline    .= "$pam_last_reported_step_count,$pam_report_decision,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PAM_REPORT_C
# Version Unknown
# --------------------
sub process_pam_report {
   my $packet_type   = shift;
   my $version       = get_uint8();
   
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   my $step_count       = get_int32(); 

   my $instance      = get_uint8();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$step_count,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_SMD_CONFIG_C
# Version 1
# --------------------
sub process_smd_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint32();             # sns_sam_timestamp

   my $sample_rate             = get_int32(); 
   my $accel_window_time       = get_int32();       # /* accel window time, sec                         */
   my $detect_threshold        = get_int32();;	    # /* accel detect threshold, m/s/s, Q16             */
   my $self_transition_prob_nm = get_int32();       # /* Self transition probability of no motion, Q16  */
   my $variable_latency_flag   = get_uint8();       # /* Flag to indicate variable latency, 0 or 1      */                      
   my $max_latency             = get_uint8();       # /* Maximum latency if fixed latency is used, sec  */ 
   my $algo_inst_id            = get_uint8();       # /* algo instance id                               */

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$sample_rate,$accel_window_time,";
   $csvline    .= "$detect_threshold,$self_transition_prob_nm,$variable_latency_flag,$max_latency,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_SMD_RESULT_C
# Version 1
# --------------------
sub process_smd_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint32();             # sns_sam_timestamp

   my $ax                 = get_int32();            # /* accel samples, m/s/s   Q16             */
   my $ay                 = get_int32();            # /* accel samples, m/s/s   Q16             */
   my $az                 = get_int32();            # /* accel samples, m/s/s   Q16             */
   my $sample_cnt         = get_uint16();           # /* sample count                           */
   my $variance		  = get_int32();    	    # /* variance, Q16                          */
   my $eigenvaluesx       = get_int32();            # /* eigenvalues, Q16                       */
   my $eigenvaluesy       = get_int32();            # /* eigenvalues, Q16                       */
   my $eigenvaluesz       = get_int32();            # /* eigenvalues, Q16                       */
   my $xcor		  = get_int32();    	    # /* auto correlation, Q16                  */
   my $spread_mag	  = get_int32();    	    # /* spread magnitude, Q16                  */
   my $rm		  = get_int32();    	    # /* RM Ratio feature, Q16                  */
   my $sa		  = get_int32();    	    # /* SA feature (Std dev of norm), Q16      */
   my $pstate0  	  = get_int32();    	    # /* HMM states, Q16                        */
   my $pstate1  	  = get_int32();    	    # /* HMM states, Q16                        */
   my $filter_delay_cnt	  = get_uint16();   	    # /* filter delay count                     */
   my $filter_delay_time  = get_uint16();   	    # /* filter delay time, in sec              */
   my $motion_state	  = get_int8();     	    # /* trasient motion state, 0, 1 or 2       */
   my $final_motion_state = get_int8();     	    # /* final motion state, reported to client */
   my $algo_inst_id       = get_uint8();            # /* algo instance id                       */

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$ax,$ay,$az,$sample_cnt,$variance,";
   $csvline    .= "$eigenvaluesx,$eigenvaluesy,$eigenvaluesz,$xcor,$spread_mag,$rm,$sa,$pstate0,$pstate1,";
   $csvline    .= "$filter_delay_cnt,$filter_delay_time,$motion_state,$final_motion_state,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_SMD_REPORT_C
# Version 1
# --------------------
sub process_smd_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $report_id                 = get_int32();      # /* report id                                */
   my $report_type               = get_uint8();      # /* report type                              */
   my $client_id                 = get_uint8();      # /* client id                                */
   my $motion_state		 = get_int8();       # /* motion state                             */
   my $motion_state_probability	 = get_uint8();      # /* probability of the motion state (0-100)  */
   my $algo_inst_id              = get_uint8();      # /* algo instance id                         */

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$client_id,";
   $csvline    .= "$motion_state,$motion_state_probability,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_CMC_CONFIG_C
# Version Unknown
# --------------------
sub process_cmc_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   print "UNKNOWN LOG_SNS_CMC_CONFIG_C packet format\n";

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_CMC_RESULT_C
# Version Unknown
# --------------------
sub  process_cmc_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $input_type         = get_uint8();                  
   my $accelX             = get_int32();                  
   my $accelY             = get_int32();                  
   my $accelZ             = get_int32();
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$input_type,$accelX,$accelY,$accelZ,";
      
   if ($version == 1) {
      my $sample_count       = get_uint16();
      my $accel_prevX        = get_float32();                
      my $accel_prevY        = get_float32();                
      my $accel_prevZ        = get_float32();                
      my $accel_sumX         = get_float32();                
      my $accel_sumY         = get_float32();                
      my $accel_sumZ         = get_float32();                
      my $accel_norm_sum     = get_float32();                
      my $accel_norm_sq_sum  = get_float32();                
      my $algo_inst_id       = get_uint8();                  
   
      $csvline    .= "$sample_count,$accel_prevX,$accel_prevY,$accel_prevZ,$accel_sumX,$accel_sumY,$accel_sumZ,";
      $csvline    .= "$accel_norm_sum,$accel_norm_sq_sum,$algo_inst_id\n";
   }
   else {  # version 2
      my $qmd_motion_state       = get_uint8();
      my $report_motion_state    = get_uint8();
      my $report_event_type      = get_uint8();
      my $algo_inst_id           = get_uint8();                  
   
      $csvline .= "$qmd_motion_state,$report_motion_state,$report_event_type,$algo_inst_id\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_CMC_RESULT2_C
# Version Unknown
# --------------------
sub  process_cmc_result2 {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp";

   if ($version == 1) {
      
      my $sa                               = get_float32();  #   /* sum of accel norm square in current measurement period m^2/s^4*/
      my $rm                               = get_float32();  #   /* sum of accel norm square in current measurement period m^2/s^4*/
      my $unfilp0                          = get_float32();  #   /* unfiltered motion state marginal probabilities*/
      my $unfilp1                          = get_float32();  #   /* unfiltered motion state marginal probabilities*/
      my $unfilp2                          = get_float32();  #   /* unfiltered motion state marginal probabilities*/
      my $unfilp3                          = get_float32();  #   /* unfiltered motion state marginal probabilities*/
      my $unfilp4                          = get_float32();  #   /* unfiltered motion state marginal probabilities*/
      my $alpha0                           = get_float32();  #   /* hmm forward algorithm parameters*/
      my $alpha1                           = get_float32();  #   /* hmm forward algorithm parameters*/
      my $alpha2                           = get_float32();  #   /* hmm forward algorithm parameters*/
      my $alpha3                           = get_float32();  #   /* hmm forward algorithm parameters*/
      my $alpha4                           = get_float32();  #   /* hmm forward algorithm parameters*/
      my $beta0                            = get_float32();  #   /* hmm backward algorithm parameters*/
      my $beta1                            = get_float32();  #   /* hmm backward algorithm parameters*/
      my $beta2                            = get_float32();  #   /* hmm backward algorithm parameters*/
      my $beta3                            = get_float32();  #   /* hmm backward algorithm parameters*/
      my $beta4                            = get_float32();  #   /* hmm backward algorithm parameters*/
      my $filprob0                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob1                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob2                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob3                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob4                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob5                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob6                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $filprob7                         = get_float32();  #   /* filtered motion state marginal probabilities*/
      my $motion_state_curr                = get_uint8();    #   /* current motion state of the device*/
      my $motion_state_prev                = get_uint8();    #   /* previous motion state of the device*/
      my $motion_state_persist_time        = get_uint8();    #   /* time for which current motion state has persisted, sec*/
      my $motion_state_curr_probability    = get_float32();  #   /* probability of current motion state*/
      my $algo_inst_id                     = get_uint8();    #   /* algorithm instance id   */
   
      $csvline    .= ",$sa,$rm,$unfilp0,$unfilp1,$unfilp2,$unfilp3,$unfilp4,";
      $csvline    .= "$alpha0,$alpha1,$alpha2,$alpha3,$alpha4,";
      $csvline    .= "$beta0,$beta1,$beta2,$beta3,$beta4,";
      $csvline    .= "$filprob0,$filprob1,$filprob2,$filprob3,$filprob4,$filprob5,$filprob6,$filprob7,";
      $csvline    .= "$motion_state_curr,$motion_state_prev,$motion_state_persist_time,$motion_state_curr_probability,$algo_inst_id\n";
   }
   else {   # version 2

      my $i;      
      for ($i = 0; $i < 53; $i++) { $csvline .= ",".get_float32(); }
      for ($i = 0; $i < 3; $i++) { $csvline .= ",".get_uint8(); }
      $csvline .= ",".get_uint16();                                  # hyst_transition_count
      for ($i = 0; $i < 12; $i++) { $csvline .= ",".get_uint8(); }   # event_report_types, motion_event
      for ($i = 0; $i < 6; $i++) { $csvline .= ",".get_uint32(); }   # ms_timestamp
      for ($i = 0; $i < 6; $i++) { $csvline .= ",".get_float32(); }  # ms_probability
      for ($i = 0; $i < 6; $i++) { $csvline .= ",".get_uint8(); }    # op_motion_event
      for ($i = 0; $i < 6; $i++) { $csvline .= ",".get_uint32(); }   # op_ms_timestamp
      for ($i = 0; $i < 6; $i++) { $csvline .= ",".get_float32(); }  # op_ms_probability
      $csvline .= ",".get_uint8()."\n";                              # algorithm instance id
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_CMC_REPORT_C
# Version Unknown
# --------------------
sub  process_cmc_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp";

   if ($version == 1) {
      my $motion_state             = get_uint8();          # /* final reported motion state of the device */
      my $motion_state_probability = get_float32();        # /* probability of the reported motion state*/
      my $algo_inst_id             = get_uint8();          # /* algo instance id */
      $csvline .= ",$motion_state,$motion_state_probability,$algo_inst_id\n";
   }
   else {   # version 2      
      my $motion_state             = get_uint8();          # /* final reported motion state of the device */
      my $motion_state_event       = get_uint8();          # /* motion state event */
      my $motion_state_probability = get_float32();        # /* probability of the reported motion state*/
      my $algo_inst_id             = get_uint8();          # /* algo instance id */

      $csvline  .= ",$motion_state,$motion_state_event,$motion_state_probability,$algo_inst_id\n";
   }
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ------------------------------------
# LOG_SNS_DB_CONFIG_C - distance bound
# Version Unknown
# ------------------------------------
sub  process_db_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $client_req_id                = get_uint8();    # /**< ID of client requesting for service            */
   my $ms_unknown_speedbound        = get_float32();  # /**< speed bound for unknown state                  */
   my $ms_stationary_speedbound     = get_float32();  # /**< speed bound for stationary state               */
   my $ms_inmotion_speedbound       = get_float32();  # /**< speed bound for inmotion state                 */
   my $ms_fiddle_speedbound         = get_float32();  # /**< speed bound for fiddle state                   */
   my $ms_pedestrian_speedbound     = get_float32();  # /**< speed bound for pedestrian state               */
   my $ms_vehicle_speedbound        = get_float32();  # /**< speed bound for vehicle state                  */
   my $ms_walk_speedbound           = get_float32();  # /**< speed bound for walk state                     */
   my $ms_run_speedbound            = get_float32();  # /**< speed bound for run state                      */
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$client_req_id,$ms_unknown_speedbound,$ms_stationary_speedbound,$ms_inmotion_speedbound,$ms_fiddle_speedbound,";
   $csvline    .= "$ms_pedestrian_speedbound,$ms_vehicle_speedbound,$ms_walk_speedbound,$ms_run_speedbound";

   if ($version == 2) {
      my $ms_bike_speedbound        = get_float32();  # /**< speed bound for bike state                     */
      $csvline    .= ",$ms_bike_speedbound";
   }

   my $algo_inst_id                 = get_uint8();    # /**< Algorithm instance id                          */
   $csvline    .= ",$algo_inst_id\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ------------------------------------
# LOG_SNS_DB_RESULT_C - distance bound
# Version 2
# ------------------------------------
sub  process_db_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $input_type                = get_uint8();   #  /**< 0: set distance bound 1: cmc input             */
   my $input_distance_bound      = get_float32(); #  /**< distance bound setting from client             */
   my $input_cmc_motion_state    = get_uint8();   #  /**< Motion State input from CMC                    */
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$input_type,$input_distance_bound,$input_cmc_motion_state";
   
   if ($version == 1) {
      my $algo_state                = get_uint8();   #  /**< 0: inactive 1: active                          */
      my $prev_timestamp            = get_uint64();  #  /**< Time stamp at last distance bound computation  */
      my $prev_speed                = get_float32(); #  /**< Speed at last distance bound computation       */
      my $prev_distance_bound       = get_float32(); #  /**< Distance to bound                              */
      my $time_to_breach            = get_float32(); #  /**< Time to breach of client set bound             */
      my $session_key               = get_uint8();   #  /**< uinque session identifier provided by client   */
      my $algo_inst_id              = get_uint8();   #  /**< Algorithm instance id                          */
      $csvline    .= ",$algo_state,$prev_timestamp,$prev_speed,$prev_distance_bound,$time_to_breach,$session_key,$algo_inst_id\n";
   }
   #else {   # version 2
   #   my $input_cmc_motion_event       = get_uint8();   #  /**< Motion Event input from CMC                    */
   #   my $algo_state                   = get_uint8();   #  /**< 0: inactive 1: active                          */
   #   my $prev_cmc_motion_state        = get_uint8();   #  /**< MS used at last distance bound computation     */
   #   my $prev_timestamp               = get_uint64();  #  /**< Time stamp at last distance bound computation  */
   #   my $prev_speed                   = get_float32(); #  /**< Speed at last distance bound computation       */
   #   my $prev_distance_bound          = get_float32(); #  /**< Distance to bound                              */
   #   my $is_simultaneous_state        = get_uint8();   #  /**< true: CMC last reported simultaneous states; false: CMC did not last report simultaneous states  */
   #   my $prev_simultaneous_cmc_state  = get_uint8();   #  /**< Simultaneous state reported by CMC along with previous_cmc_motion_state */
   #   my $time_to_breach               = get_float32(); #  /**< Time to breach of client set bound             */
   #   my $session_key                  = get_uint8();   #  /**< uinque session identifier provided by client   */
   #   my $algo_inst_id                 = get_uint8();   #  /**< Algorithm instance id                          */
   #   $csvline .= ",$input_cmc_motion_event,$algo_state,$prev_cmc_motion_state,$prev_timestamp,$prev_speed,$prev_distance_bound";
   #   $csvline .= ",$is_simultaneous_state,$prev_simultaneous_cmc_state,$time_to_breach,$session_key,$algo_inst_id\n";
   #}
   else {   # version 2
      my $algo_state                   = get_uint8();   #  /**< 0: inactive 1: active                          */
      my $prev_timestamp               = get_uint64();  #  /**< Time stamp at last distance bound computation  */
      my $prev_speed                   = get_float32(); #  /**< Speed at last distance bound computation       */
      my $prev_distance_bound          = get_float32(); #  /**< Distance to bound                              */
      my $time_to_breach               = get_float32(); #  /**< Time to breach of client set bound             */
      my $session_key                  = get_uint8();   #  /**< uinque session identifier provided by client   */
      my $algo_inst_id                 = get_uint8();   #  /**< Algorithm instance id                          */
      $csvline .= ",$algo_state,$prev_timestamp,$prev_speed,$prev_distance_bound";
      $csvline .= ",$time_to_breach,$session_key,$algo_inst_id\n";
   }   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ------------------------------------
# LOG_SNS_DB_REPORT_C - distance bound
# Version Unknown
# ------------------------------------
sub  process_db_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $distance_bound_breach_event = get_uint8();  # /**< 1: breach occurred 0: breach not occurred      */
   my $session_key                 = get_uint8();  # /**< uinque session identifier provided by client   */
   my $algo_inst_id                = get_uint8();  # /**< Algorithm instance id                          */

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$distance_bound_breach_event,$session_key,$algo_inst_id\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ------------------------------------
# LOG_SNS_FIFO_EVENT_C - FIFO event
# Version Unknown
# ------------------------------------
sub process_fifo_event {
   my $packet_type      = shift;
   my $version          = get_uint8();    # /**< version of the log packet                        */
   my $timestamp        = get_uint64();   # /**< Time in SSC ticks when the sensor event happened */

   my $sensor_id                 = get_int32();    # /**< smgr sensor id of the sensor being logged        */
   my $fifo_event                   = get_uint8();    # /**< FIFO Event as specified in sns_fifo_event_e      */
   my $watermark_depth              = get_uint8();    # /**< water mark (num of samples )                     */
   my $odr                          = get_uint16();   # /**< current ODR                                      */
   my $hw_watermark_int_supported   = get_uint8();    # /**< if hardware watermark is supported               */
   my $max_watermark                = get_uint16();   # /**< maximum watermark supported by the sensor        */

   my $csvline  = "$packet_type,$version,$timestamp,$sensor_id,$fifo_event,$watermark_depth,$odr,$hw_watermark_int_supported,$max_watermark\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------
# LOG_SNS_LATENCY_SAMPLING_POLL_C
# Version Unknown
# -------------------------------
sub process_ltcy_sampling_poll {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp        = get_uint64();                  
   my $sensor_id                 = get_int32();      # /* sensor id                                */
   my $data_ts                   = get_uint64();     # /* data timestamp                           */
   my $sampling_latency          = get_uint64();      # /* sampling latency                         */
   my $polling_latecny           = get_uint64();      # /* polling latency                          */

   my $csvline  = "$packet_type,$version,$timestamp,$sensor_id,$data_ts,$sampling_latency,$polling_latecny\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ------------------------------
# LOG_SNS_LATENCY_SAMPLING_DRI_C
# Version Unknown
# ------------------------------
sub process_ltcy_sampling_dri {
   my $packet_type      = shift;
   my $version          = get_uint8();          
   my $timestamp        = get_uint64();
   my $sensor_id                 = get_int32();      # /* sensor id                                */
   my $data_ts                   = get_uint64();     # /* data timestamp                           */
   my $sampling_latency          = get_uint64();      # /* sampling latency                         */
   my $dri_get_data_latecny      = get_uint64();      # /* getting dta latency                      */

   my $csvline  = "$packet_type,$version,$timestamp,$sensor_id,$data_ts,$sampling_latency,$dri_get_data_latecny\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------------
# LOG_SNS_LATENCY_DELIVERY_C
# Version Unknown
# --------------------------
sub process_ltcy_delivery {
   my $packet_type      = shift;
   my $version          = get_uint8();          
   my $timestamp        = get_uint64();

   my $sensor_id                 = get_int32();      # /* sensor id                                */
   my $data_ts                   = get_uint64();     # /* data timestamp                           */
   my $delivery_latency          = get_uint64();      # /* delivery latency                         */

   my $csvline  = "$packet_type,$version,$timestamp,$sensor_id,$data_ts,$delivery_latency\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C
# Version 1
# -------------------------------------
sub  process_grv_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   my $csvline;
   
   if ($version < 255) {
    # GRV packet
        my $report_period              = get_uint32();
        my $sample_rate                = get_uint32();
        my $coordinate_sys             = get_uint8();
        my $abs_rest_gyro_az_tilt_tc   = get_float32();
        my $rel_rest_gyro_az_tilt_tc   = get_float32();
        my $motion_gyro_az_tilt_tc     = get_float32();
        my $gyro_noise_threshold       = get_float32();
        my $max_gyro_az_tilt_freeze    = get_float32();
        my $max_gyro_az_tilt_reset     = get_float32();
        my $algo_inst_id               = get_uint8();      
                
        $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
        $csvline    .= "$report_period,$sample_rate,$coordinate_sys,$abs_rest_gyro_az_tilt_tc,$rel_rest_gyro_az_tilt_tc,";
        $csvline    .= "$motion_gyro_az_tilt_tc,$gyro_noise_threshold,$max_gyro_az_tilt_freeze,$max_gyro_az_tilt_reset,$algo_inst_id\n";
   }
   else {
    # QHEART Config packet
        $packet_type                        = LOG_SNS_QHEART_CONFIG_C;
        my $sample_rate_ppg                 = get_int32();       # Requested PPG sensor sample rate (Q16)
        my $sample_rate_accel               = get_int32();       # Requested accelerometer sensor sample rate (Q16)
        my $update_interval_in_fft_samples  = get_uint32();    
        my $max_alpha                       = get_float32();    
        my $min_alpha                       = get_float32();    
        my $min_oh                          = get_float32();    
        my $max_oh                          = get_float32();    
        my $max_del_b                       = get_float32();    
        my $acc_peak_distance               = get_uint32(); 
        my $ppg_peak_distance               = get_uint32(); 
        my $num_ppg_peaks                   = get_uint32(); 
        my $num_acc_peaks                   = get_uint32(); 
        my $peak_width_ppg                  = get_uint32(); 
        my $peak_thresh_ppg                 = get_float32(); 
        my $peak_thresh_acc                 = get_float32(); 
        my $max_ind_diff                    = get_uint32();  
        my $max_acc_thr                     = get_float32(); 
        my $harm_acc_thr                    = get_float32(); 
        my $globalminhr                     = get_float32(); 
        my $globalmaxhr                     = get_float32(); 
        my $noaccel_thresh                  = get_float32(); 
        my $accuracy_decay_alpha            = get_float32(); 
        my $android_accuracy_low_thresh     = get_float32(); 
        my $android_accuracy_high_thresh    = get_float32(); 
        my $android_accuracy_medium_thresh  = get_float32(); 
        my $do_minppg                       = get_uint8();  
        my $do_mingoodppgtrack              = get_uint8();  
        my $do_width_harm                   = get_uint8();  
        my $do_stride_is_hr_processing      = get_uint8();  
        my $is_one_shot                     = get_uint8();  
        my $report_interval                 = get_uint32();  
        
        my $algo_inst_id        	= get_uint8();
        
        $csvline = "$packet_type,$version,$timestamp_type,$timestamp,$sample_rate_ppg,$sample_rate_accel,$update_interval_in_fft_samples";
        $csvline .= ",$max_alpha,$min_alpha,$min_oh,$max_oh,$max_del_b,$acc_peak_distance,$ppg_peak_distance,$num_ppg_peaks,$num_acc_peaks,$peak_width_ppg";
        $csvline .= ",$peak_thresh_ppg,$peak_thresh_acc,$max_ind_diff,$max_acc_thr,$harm_acc_thr,$globalminhr,$globalmaxhr,$noaccel_thresh,$accuracy_decay_alpha";
        $csvline .= ",$android_accuracy_low_thresh,$android_accuracy_high_thresh,$android_accuracy_medium_thresh,$do_minppg,$do_mingoodppgtrack,$do_width_harm";
        $csvline .= ",$do_stride_is_hr_processing,$is_one_shot,$report_interval,$algo_inst_id\n";
   }   
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C
# Version 1
# -------------------------------------
sub  process_grv_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   my $csvline;
   
   if ($version < 255) {
    # GRV packet
        my $grav_x                       = get_float32();
        my $grav_y                       = get_float32();
        my $grav_z                       = get_float32();
        my $gravity_accuracy             = get_uint8();   
        my $gravity_timestamp            = get_uint64();     
        my $gravity_dev_mot_state        = get_uint8();
        my $gyro_quat0                   = get_float32();        
        my $gyro_quat1                   = get_float32();        
        my $gyro_quat2                   = get_float32();        
        my $gyro_quat3                   = get_float32();        
        my $gyro_quat_timestamp          = get_uint64();     
        my $grv0                         = get_float32();        
        my $grv1                         = get_float32();        
        my $grv2                         = get_float32();        
        my $grv3                         = get_float32();        
        my $accuracy                     = get_uint8();      
        my $coordinate_sys               = get_uint8();     
        my $algo_inst_id                 = get_uint8();     
        
        $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
        $csvline    .= "$grav_x,$grav_y,$grav_z,$gravity_accuracy,$gravity_timestamp,$gravity_dev_mot_state,";
        $csvline    .= "$gyro_quat0,$gyro_quat1,$gyro_quat2,$gyro_quat3,$gyro_quat_timestamp,";
        $csvline    .= "$grv0,$grv1,$grv2,$grv3,$accuracy,$coordinate_sys,$algo_inst_id\n";
   }
   else {
    # QHEART Result packet
        $packet_type                        = LOG_SNS_QHEART_RESULT_C;
        my $input_type             = get_uint8();    # Input; 0 indicates raw ppg input data, 1 indicates acell input data.  
        my $sensor_data0           = get_int32();    # Input; Input sensor data. Position 0 is PPG value when INPUT_TYPE=0, Positions 0,1,2 are accel x,y,z values when INPUT_TYPE=1              
        my $sensor_data1           = get_int32();             
        my $sensor_data2           = get_int32();    
        my $sensor_time            = get_uint32();   # Input; timestamp in SSC ticks of input sensor data.
        my $bpm                    = get_float32();    # Output; Reported heart rate in beats per minute
        my $bpm_time               = get_uint32();   # Output; Timestamp of last sensor report that resulted in updated BPM value.
        my $bpm_updated            = get_uint8();    # Output; 0=BPM not updated this iteration, 1=BPM was updated this iteration.
        my $bpm_quality            = get_uint8();    # Output; One of: NO_CONTACT = -1, UNRELIABLE = 0, ACCURACY_LOW = 1, ACCURACY_MEDIUM = 2, ACCURACY_HIGH = 3
        my $num_found_ppg_peaks    = get_uint32();
        my $num_found_acc_peaks    = get_uint32();
        my $prior_smooth_bpm       = get_float32(); 
        my $prior_smooth_harmppg   = get_float32(); 
        my $harmacc                = get_float32(); 
        my $harmpow                = get_float32(); 
        my $acc_pow_fft            = get_float32(); 
        my $locspeak               = get_uint32();
        my $harmppg                = get_float32(); 
        my $smooth_harmppg         = get_float32(); 
        my $harmppg_save           = get_float32(); 
        my $raw_bpm                = get_float32(); 
        my $smooth_bpm             = get_float32(); 
        my $state_bpm_quality      = get_uint8();
        
        my $algo_inst_id	      = get_uint8();
        
        $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$input_type,$sensor_data0,$sensor_data1,$sensor_data2,$sensor_time";
        $csvline .= ",$bpm,$bpm_time,$bpm_updated,$bpm_quality,$num_found_ppg_peaks,$num_found_acc_peaks,$prior_smooth_bpm,$prior_smooth_harmppg";
        $csvline .= ",$harmacc,$harmpow,$acc_pow_fft,$locspeak,$harmppg,$smooth_harmppg,$harmppg_save,$raw_bpm,$smooth_bpm,$state_bpm_quality,$algo_inst_id\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C
# Version 1
# -------------------------------------
sub  process_grv_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   my $csvline;
   
   if ($version < 255) {
    # GRV packet
        my $report_id        = get_int32();
        my $report_type      = get_uint8();
        my $client_id        = get_uint8();
        my $grv0             = get_float32();
        my $grv1             = get_float32();
        my $grv2             = get_float32();
        my $grv3             = get_float32();
        my $accuracy         = get_uint8();
        my $coordinate_sys   = get_uint8();
        my $algo_inst_id     = get_uint8();
     
        $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
        $csvline    .= "$report_id,$report_type,$client_id,$grv0,$grv1,$grv2,$grv3,$accuracy,$coordinate_sys,$algo_inst_id\n";
   }
   else {
    # QHEART Report packet
        $packet_type         = LOG_SNS_QHEART_REPORT_C;
        my $report_id        = get_uint32();   # Report id 
        my $report_type      = get_uint8();    # Report type: 0 – unknown, 1 – periodic, 2 - asynchronous, 3 - synchronous
        my $client_id        = get_uint8();    # Client id 
        my $bpm                    = get_float32();    # Output; Reported heart rate in beats per minute
        my $bpm_time               = get_uint32();   # Output; Timestamp of last sensor report that resulted in updated BPM value.
        my $bpm_updated            = get_uint8();    # Output; 0=BPM not updated this iteration, 1=BPM was updated this iteration.
        my $bpm_quality            = get_uint8();    # Output; One of: NO_CONTACT = -1, UNRELIABLE = 0, ACCURACY_LOW = 1, ACCURACY_MEDIUM = 2, ACCURACY_HIGH = 3
        my $algo_inst_id	   = get_uint8();

        $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$client_id";
        $csvline .= ",$bpm,$bpm_time,$bpm_updated,$bpm_quality,$algo_inst_id\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# ------------------------------------
# LOG_SNS_DRV_MD_IRQ_C - Motion Detect Interrupt packet
# Version Unknown
# ------------------------------------
sub  process_md_irq {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp        = get_uint64();
   my $threshold        = get_int16();

   my $csvline  = "$packet_type,$version,$timestamp,$threshold\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_QMAG_CAL_CONFIG_C
# Version Unknown
# -------------------------------------
sub  process_qmag_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $sample_rate_mag            = get_uint32();
   my $sample_rate_accel          = get_uint32();
   my $cal_algo_type              = get_uint8();
   my $cal_cycle_rate             = get_uint32();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$sample_rate_mag,$sample_rate_accel,$cal_algo_type,$cal_cycle_rate\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_QMAG_CAL_RESULT_C
# Version 1
# -------------------------------------
sub  process_qmag_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $input_type                   = get_uint8();
   my $input_mag_x                  = get_int32();
   my $input_mag_y                  = get_int32();
   my $input_mag_z                  = get_int32();   
   my $input_accel_x                = get_int32();     
   my $input_accel_y                = get_int32();
   my $input_accel_z                = get_int32();        
   my $accel_input_variance         = get_double64();        
   my $mag_input_variance           = get_double64();        
   my $offset_hi_unfiltered_x       = get_float32();        
   my $offset_hi_unfiltered_y       = get_float32();     
   my $offset_hi_unfiltered_z       = get_float32();        
   my $radius_hi                    = get_float32();        
   my $unfiltered_accuracy          = get_uint8();        
   my $accuracy_published           = get_uint8();        
   my $cal_algo_type                = get_uint8();      
   my $mag_zero_bias_published_x    = get_int32();     
   my $mag_zero_bias_published_y    = get_int32();
   my $mag_zero_bias_published_z    = get_int32();
   my $offset_time                  = get_uint32();
   my $hard_reset                   = get_uint8();        
   my $soft_reset                   = get_uint8();
      
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$input_type,$input_mag_x,$input_mag_y,$input_mag_z,$input_accel_x,$input_accel_y,$input_accel_z,";
   $csvline    .= "$accel_input_variance,$mag_input_variance,$offset_hi_unfiltered_x,$offset_hi_unfiltered_y,$offset_hi_unfiltered_z,";
   $csvline    .= "$radius_hi,$unfiltered_accuracy,$accuracy_published,$cal_algo_type,$mag_zero_bias_published_x,$mag_zero_bias_published_y,";
   $csvline    .= "$mag_zero_bias_published_z,$offset_time,$hard_reset,$soft_reset\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_QMAG_CAL_REPORT_C
# Version Unknown
# -------------------------------------
sub  process_qmag_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $qmag_x                    = get_int32();
   my $qmag_y                    = get_int32();
   my $qmag_z                    = get_int32();
   my $qmag_zero_bias_corr_x     = get_int32();
   my $qmag_zero_bias_corr_y     = get_int32();
   my $qmag_zero_bias_corr_z     = get_int32();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$qmag_x,$qmag_y,$qmag_z,$qmag_zero_bias_corr_x,$qmag_zero_bias_corr_y,$qmag_zero_bias_corr_z\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C
# Version Unknown
# -------------------------------------
sub  process_geomagrv_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $report_period        = get_uint32();
   my $sample_rate          = get_uint32();
   my $accel_filter_tc      = get_uint32();
   my $mag_filter_tc        = get_uint32();
   my $motion_detect_period = get_float32();
   my $abs_rest_var_thresh  = get_float32();
   my $coord_sys            = get_uint8();
   my $instance             = get_uint8();
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$report_period,$sample_rate,$accel_filter_tc,$mag_filter_tc,$motion_detect_period,$abs_rest_var_thresh,$coord_sys,$instance";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GEOMAG_ROT_VEC_RESULT_C
# Version Unknown
# -------------------------------------
sub  process_geomagrv_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $accel_x                  = get_uint32();
   my $accel_y                  = get_uint32();
   my $accel_z                  = get_uint32();   
   my $gravity_x                = get_float32();     
   my $gravity_y                = get_float32();
   my $gravity_z                = get_float32();        
   my $lin_accel_x              = get_float32();        
   my $lin_accel_y              = get_float32();        
   my $lin_accel_z              = get_float32();        
   my $gravity_accuracy       = get_uint8();     
   my $gravity_timestamp      = get_uint64();        
   my $fmv_x                  = get_float32();        
   my $fmv_y                  = get_float32();        
   my $fmv_z                  = get_float32();        
   my $fmv_accuracy           = get_uint8();      
   my $fmv_timestamp          = get_uint64();     
   my $rotva                  = get_float32();
   my $rotvb                  = get_float32();
   my $rotvc                  = get_float32();
   my $rotvd                  = get_float32();        
   my $rotv_accuracy          = get_uint8();
   my $coord_sys              = get_uint8();
   my $instance               = get_uint8();
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$accel_x,$accel_y,$accel_z,$gravity_x,$gravity_y,$gravity_z,$lin_accel_x,$lin_accel_y,$lin_accel_z,";
   $csvline    .= "$gravity_accuracy,$gravity_timestamp,$fmv_x,$fmv_y,$fmv_z,$fmv_accuracy,$fmv_timestamp,";
   $csvline    .= "$rotva,$rotvb,$rotvc,$rotvd,$rotv_accuracy,$coord_sys,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# -------------------------------------
# LOG_SNS_GEOMAG_ROT_VEC_REPORT_C
# Version Unknown
# -------------------------------------
sub  process_geomagrv_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $report_id              = get_uint32();
   my $report_type            = get_uint8();
   my $client_id              = get_uint8();   
   my $rotva                  = get_float32();
   my $rotvb                  = get_float32();
   my $rotvc                  = get_float32();
   my $rotvd                  = get_float32();        
   my $gravity_x              = get_float32();     
   my $gravity_y              = get_float32();
   my $gravity_z              = get_float32();        
   my $lin_accel_x            = get_float32();        
   my $lin_accel_y            = get_float32();        
   my $lin_accel_z            = get_float32();        
   my $rotv_accuracy          = get_uint8();
   my $gravity_accuracy       = get_uint8();     
   my $coord_sys              = get_uint8();
   my $instance               = get_uint8();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   $csvline    .= "$report_id,$report_type,$client_id,$rotva,$rotvb,$rotvc,$rotvd,";
   $csvline    .= "$gravity_x,$gravity_y,$gravity_z,$lin_accel_x,$lin_accel_y,$lin_accel_z,";
   $csvline    .= "$rotv_accuracy,$gravity_accuracy,$coord_sys,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_ALIGN_CONFIG_C       => 0x186C;
# Version Unknown
# --------------------
sub process_paln_config {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          # Type of timestamp  
   my $timestamp        = get_uint32();         # Time in SSC ticks when algorithm is configured
   
   my $rv_input               = get_int32();    # Type of RV algorithm used as input: 0 - Rotation vector; 1 - Game RV; 2 - Orientation
   my $cog_sample_rate        = get_int32();    # Accel and Pedometer sample rate in Hz (Q16)
   my $rv_sample_rate         = get_int32();    # Rotation vector sample rate in Hz (Q16)
   my $sensor_report_rate     = get_int32();    # SMGR buffering rate in Hz (Q16)
   my $cog_averaging_interval = get_uint8();    # Course-over-ground averaging interval, in steps
   
   my $instance               = get_uint8();    # Algorithm instance id 

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$rv_input,$cog_sample_rate,$rv_sample_rate,$sensor_report_rate,$cog_averaging_interval,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_ALIGN_RESULT1_C       => 0x186D;
# Version Unknown
# --------------------
sub process_paln_result1 {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $input_type       = get_uint8();          # Type of input: 0 - Accel; 1 -RV
   my $timestamp        = get_uint32();         # Timestamp of input, in SSC ticks
   
   my $accel_x       = get_int32();             # Accel input X, m/s^2, Q16
   my $accel_y       = get_int32();             # Accel input Y, m/s^2, Q16      
   my $accel_z       = get_int32();             # Accel input Z, m/s^2, Q16
   
   my $rotva        = get_float32();            # Rotation vector values, unitless 
   my $rotvb        = get_float32();            # Rotation vector values, unitless 
   my $rotvc        = get_float32();            # Rotation vector values, unitless 
   my $rotvd        = get_float32();            # Rotation vector values, unitless 
   my $rv_accuracy            = get_uint8();    # Rotation vector accuracy
   
   my $instance               = get_uint8();    # Algorithm instance id 

   my $csvline  = "$packet_type,$version,$input_type,$timestamp,$accel_x,$accel_y,$accel_z,$rotva,$rotvb,$rotvc,$rotvd,$rv_accuracy,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_ALIGN_RESULT2_C       => 0x186E;
# Version 1 & 2
# --------------------
sub process_paln_result2 {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $timestamp        = get_uint32();         # Step timestamp from Pedometer, in SSC ticks   
   my $unfiltered_cog_angle   = get_float32();     # Instantaneous CoG angle, in radians 
   my $cog_angle              = get_float32();     # Smoothed CoG angle, in radians   
   my $cog_accuracy           = get_float32();     # Predicted standard deviation of computed CoG, in radians     
   my $relative_turn_angle       = get_float32();     # Estimated relative turn angle since last alignment change, in radians 
   my $last_alignment_change_ts  = get_uint32();   # Timestamp of step at which alignment change was last detected, in SSC ticks
   my $events                    = get_int32();    # Pedestrian events detected since the last step:
                                                      # 0 - No events detected since the last step
                                                      # 1 - Pedestrian turn detected
                                                      # 2 - Device alignment change detected
                                                      # 3 - Turn and alignment change detected
   my $instance               = get_uint8();       # Algorithm instance id 

   my $csvline  = "$packet_type,$version,$timestamp,$unfiltered_cog_angle,$cog_angle,$cog_accuracy,$relative_turn_angle,$last_alignment_change_ts,$events,$instance";

   if ($version > 1)
   {
      my $rta_accuracy           = get_float32();     # Accuracy of estimated relative turn angle, in radians
      my $csvline .= $rta_accuracy;
   } 
   
   print CSV_FILE $csvline."\n";
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_PED_ALIGN_REPORT_C       => 0x186F;
# Version 1 & 2
# --------------------
sub process_paln_report {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $timestamp        = get_uint32();   # Timestamp of sample with which latest step was detected, in SSC ticks   
   my $instance         = get_uint8();    # Algorithm instance id 
   my $client_id        = get_uint8();    # Client id 
   my $report_id        = get_int32();    # Report id 
   my $cog_angle              = get_float32();     # CoG angle, in radians  
   my $cog_accuracy           = get_float32();     # Predicted standard deviation of computed CoG, in radians    
   my $relative_turn_angle       = get_float32();     # Estimated relative turn angle since last alignment change, in radians 
   my $last_alignment_change_ts  = get_uint32();   # Timestamp of step at which alignment change was last detected, in SSC ticks
   my $events                    = get_int32();    # Pedestrian events detected since the last step:
                                                      # 0 - No events detected since the last step
                                                      # 1 - Pedestrian turn detected
                                                      # 2 - Device alignment change detected
                                                      # 3 - Turn and alignment change detected
   
   my $csvline  = "$packet_type,$version,$timestamp,$instance,$client_id,$report_id,$cog_angle,$cog_accuracy,$relative_turn_angle,$last_alignment_change_ts,$events";

   if ($version > 1)
   {
      my $rta_accuracy           = get_float32();     # Accuracy of estimated relative turn angle, in radians
      my $csvline .= $rta_accuracy;
   }
   
   print CSV_FILE $csvline."\n";
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_TILT_DETECTOR_CONFIG_C
# Version Unknown
# --------------------
sub process_tilt_config {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          # Type of timestamp  
   my $timestamp        = get_uint64();         # Time in SSC ticks when algorithm is configured
   
   my $sample_rate             = get_float32();    # sample rate in Hz
   my $angle_threshold         = get_float32();    # angle threshold in radians
   my $init_accel_window_time  = get_float32();    # time window in seconds to average accel for the initial gravity vector
   my $accel_window_time       = get_float32();    # time window in seconds to average accel for the current gravity vector
   
   my $instance               = get_uint8();    # Algorithm instance id 

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$sample_rate,$angle_threshold,$init_accel_window_time,$accel_window_time,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_TILT_DETECTOR_RESULT_C
# Version Unknown
# --------------------
sub process_tilt_result {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          # Type of timestamp  
   my $timestamp        = get_uint64();         # Timestamp of input, in SSC ticks
   
   my $accel_x          = get_int32();          # Accel input X, m/s^2, Q16
   my $accel_y          = get_int32();          # Accel input Y, m/s^2, Q16      
   my $accel_z          = get_int32();          # Accel input Z, m/s^2, Q16
   my $accel_timestamp  = get_uint64();         # Timestamp of accel input, in SSC ticks
   my $dprod_threshold  = get_float32();        # dot product threshold 
   my $gravity_x        = get_float32();        # reference gravity vector X, m/s/s
   my $gravity_y        = get_float32();        # reference gravity vector Y, m/s/s
   my $gravity_z        = get_float32();        # reference gravity vector Z, m/s/s
   
   my $instance         = get_uint8();          # Algorithm instance id 

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$accel_x,$accel_y,$accel_z,$accel_timestamp,$dprod_threshold,$gravity_x,$gravity_y,$gravity_z,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_TILT_DETECTOR_REPORT_C
# Version Unknown
# --------------------
sub process_tilt_report {
   my $packet_type   = shift;

   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();    # Type of timestamp: 0-DSPS, 1-APPS, 2-MODEM, 3-GPS
   my $timestamp        = get_uint64();   # Timestamp of sample with which latest step was detected, in SSC ticks   

   my $report_id        = get_uint32();   # Report id 
   my $report_type      = get_uint8();    # Report type: 0 – unknown, 1 – periodic, 2 - asynchronous, 3 - synchronous
   my $client_id        = get_uint8();    # Client id 
   my $event_timestamp  = get_uint32();   # Reported event timestamp, in SSC ticks   

   my $gravity_x        = get_float32();  # reference gravity vector X, m/s/s
   my $gravity_y        = get_float32();  # reference gravity vector Y, m/s/s
   my $gravity_z        = get_float32();  # reference gravity vector Z, m/s/s

   my $instance         = get_uint8();    # Algorithm instance id

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$client_id,$event_timestamp,$gravity_x,$gravity_y,$gravity_z,$instance\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------
# SNS_LOG_UIMAGE
# Version 1
# --------------
sub process_uimage_packet{
   my $packet_type      = shift;

   my $version          = get_uint8();    # SNS_LOG_UIMG_MODE_VERSION 1 
   if ( $version == 2) {
      my $uimg_enter_ts    = get_uint64();   # uimg enter timestamp in SSC ticks
      my $uimg_enter_vote  = get_uint32();   # enter vote status bits: (001) Micro Image, (010) Big Image, (100) No Client
      my $uimg_exit_ts     = get_uint64();   # uimg exit timestamp in SSC ticks 
      my $uimg_exit_vote   = get_uint32();   # exit vote status bits: (001) Micro Image, (010) Big Image, (100) No Client 

      my $csvline  = "$packet_type,$version,$uimg_enter_ts,$uimg_enter_vote,$uimg_exit_ts,$uimg_exit_vote\n";
      print CSV_FILE $csvline;
      $num_csv_lines++;
   }
   elsif ( $version == 3) {
      my $client_vote         = get_uint32(); # client vote status nibbles: 1==uimage, 2==big_image, 4==no_client
      my $state_vote_ts       = get_uint64(); # timestamp in dsps ticks of this vote
                                              # following defined only for nibble 0 is system_vote == big_image
      my $bigimage_entry_ts   = get_uint64(); # timestamp of entry into big_image
      my $last_uimg_vote_ts   = get_uint64(); # time we actually voted for uimage
      my $first_uimg_entry_ts = get_uint64(); # time when system entered uimage
      my $time_spent_in_uimg  = get_uint64(); # this occurrence duration in uimage 
      my $num_exits_from_uimg = get_uint32(); # in the period, number of times we did exit uimage 

      my $csvline = "$packet_type,$version,$client_vote,$state_vote_ts,$bigimage_entry_ts,$last_uimg_vote_ts,$first_uimg_entry_ts,$time_spent_in_uimg,$num_exits_from_uimg\n";
      print CSV_FILE $csvline;
      $num_csv_lines++;
   }
}

# --------------------
# LOG_SNS_DPC_CONFIG_C
# Version 1 & 2
# --------------------
sub process_dpc_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,";
   
   if ($version == 1) {
    
      my $accel_sample_rate        = get_uint32();
      my $proximity_sample_rate    = get_uint32();   
      my $sensor_report_rate       = get_uint32();
      my $algo_inst_id        	= get_uint8();
      
      $csvline  .= "$accel_sample_rate,$proximity_sample_rate,$sensor_report_rate,$algo_inst_id\n";
   }
   else {
      
      my $accel_sample_rate                = get_uint32();           # accel sample rate, Hz, Q16
      my $proximity_sample_rate            = get_uint32();           # proximity sample rate, Hz, Q16
      my $mdIntAvailable                   = get_uint8();            # Motion interrupt is available
      my $suppress_samps                   = get_uint32();
      my $hidden_hidden_hyst_time          = get_uint32();
      my $angle_static_alpha               = get_float32();
      my $proximity_check_window_length    = get_uint32();
      my $tiltparams_pickup_margin         = get_float32();
      my $tiltparams_pickup_min            = get_float32();
      my $tiltparams_stable_t              = get_float32();
      my $max_tilt_facing_sep              = get_uint64();
      my $face_position_detection_tau      = get_float32();
  
      $csvline .= "$accel_sample_rate,$proximity_sample_rate,$mdIntAvailable,$suppress_samps,$hidden_hidden_hyst_time,$angle_static_alpha,".
         "$proximity_check_window_length,$tiltparams_pickup_margin,$tiltparams_pickup_min,$tiltparams_stable_t,".
         "$max_tilt_facing_sep,$face_position_detection_tau\n";
   }
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_DPC_RESULT_C
# Version 1 & 2
# --------------------
sub  process_dpc_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $csvline = "$packet_type,$version,";
   
   if ($version == 1) {
   
      my $timestamp_type   = get_uint8();          
      my $timestamp        = get_uint32();
      my $input_type       = get_uint8();                      # input type, 1:accel input, 2: proximity, 3: motion interrupt
      $csvline .= "$timestamp_type,$timestamp,$input_type,";
      
      my $accelX             = get_int32();                    # accel input x, m/s^2, Q16
      my $accelY             = get_int32();                    # accel input y, m/s^2, Q16
      my $accelZ             = get_int32();                    # accel input z, m/s^2, Q16
      my $proximity          = get_int32();                    # proximity input: DPC_PROXIMITY_NEAR: 65536, DPC_PROXIMITY_FAR: 0
   
      if ($input_type == 1) { # accel
        $csvline  .= "$accelX,$accelY,$accelZ,,";
      } elsif ($input_type == 2) { # prox
        $csvline  .= ",,,$proximity,";
      } elsif ($input_type == 3) { # motion interrupt
        $csvline  .= ",,,,";
      } else {
        print "LOG_SNS_DPC_RESULT_C: Unknown input_type: $input_type\n"
      }
      my $device_position				    = get_uint8(); 
      my $desk_entry_detector_op_state			    = get_uint8();
      my $desk_entry_detector_state			    = get_uint8();
      my $desk_entry_detector_on_desk_entry_time	    = get_uint32();
      my $desk_entry_detector_unknown_entry_time            = get_uint32();
      my $desk_exit_detector_op_state			    = get_uint8();
      my $pocket_entry_detector_op_state		    = get_uint8();
      my $pocket_entry_detector_state			    = get_uint8();
      my $pocket_entry_detector_in_pocket_entry_time	    = get_uint32();
      my $pocket_entry_detector_unknown_entry_time	    = get_uint32();
      my $pocket_entry_detector_prev_proximity		    = get_int32();
      my $pocket_exit_detector_op_state			    = get_uint8();
      my $pocket_exit_detector_state			    = get_uint8();
      my $pocket_exit_detector_prev_proximity		    = get_int32();
      my $pocket_exit_detector_prox_near_to_far_trans_time  = get_uint32();
      my $pocket_exit_detector_unknown_entry_time	    = get_uint32();
      my $algo_inst_id					    = get_uint8();
   
      $csvline .= "$device_position,$desk_entry_detector_op_state,$desk_entry_detector_state,$desk_entry_detector_on_desk_entry_time,";
      $csvline .= "$desk_entry_detector_unknown_entry_time,$desk_exit_detector_op_state,$pocket_entry_detector_op_state,$pocket_entry_detector_state,";
      $csvline .= "$pocket_entry_detector_in_pocket_entry_time,$pocket_entry_detector_unknown_entry_time,$pocket_entry_detector_prev_proximity,";
      $csvline .= "$pocket_exit_detector_op_state,$pocket_exit_detector_state,$pocket_exit_detector_prev_proximity,";
      $csvline .= "$pocket_exit_detector_prox_near_to_far_trans_time,$pocket_exit_detector_unknown_entry_time,$algo_inst_id\n";
   }
   else {
      
      my $timestamp_type   = get_uint8();          
      my $timestamp        = get_uint64();
      my $input_type       = get_uint8();                      # input type, 1:accel input, 2: proximity, 3: motion interrupt, 4: amd
      $csvline .= "$timestamp_type,$timestamp,$input_type,";
      
      my $accelX             = get_int32();                  
      my $accelY             = get_int32();                  
      my $accelZ             = get_int32();
      my $proximity          = get_int32();
      my $amd_motion_status  = get_uint8();
   
      if ($input_type == 1) { # accel
        $csvline  .= "$accelX,$accelY,$accelZ,,,";
      } elsif ($input_type == 2) { # prox
        $csvline  .= ",,,$proximity,,";
      } elsif ($input_type == 3) { # motion interrupt
        $csvline  .= ",,,,,";
      } elsif ($input_type == 4) { # amd
        $csvline  .= ",,,,,$amd_motion_status";
      } else {
        print "LOG_SNS_DPC_RESULT_C: Unknown input_type: $input_type\n"
      }
      my $device_position			 = get_uint8();    # Current support position below
      my $device_position_timestamp              = get_uint64();   # Time in SSC ticks when device position was set
      my $face_position                          = get_uint8();
      my $face_position_timestamp                = get_uint64();
      my $tilt                                   = get_uint8();
      my $tilt_timestamp                         = get_uint64();
      my $tilt_suppress_ctr                      = get_int32();
      my $proximity_last_go_far_time             = get_uint64();
      my $proximity_last_go_near_time            = get_uint64();
      my $accelStatus                            = get_uint8();
      my $dpc_output                             = get_uint8();
      my $dpc_output_timestamp                   = get_uint64();
      my $prox_state                             = get_uint8();    #1: FAR, 0: NEAR
      my $dpc_ready                              = get_uint8();
      my $tilt_last_go_one_timestamp             = get_uint64();
      my $facing_algo_last_go_one_timestamp      = get_uint64();
      my $hidden_last_seen_timestamp             = get_uint64();
      my $compute_on_this_samp                   = get_uint8();
      my $is_stable                              = get_uint8();
      my $buff_idx                               = get_uint32();
      my $samp_count                             = get_uint32();
      my $dpc_event_generated                    = get_uint8();
      my $motion_status                          = get_uint8();
      my $static_angle_count                     = get_uint32();
      my $stream_period                          = get_uint32();   # streaming for this number of sample then turn to buffered stream
      my $flat_static_flag                       = get_uint8();
      my $proxStatus                             = get_uint8();
      my $algo_inst_id                           = get_uint8();
   
      $csvline .= "$device_position,$device_position_timestamp,$face_position,$face_position_timestamp,$tilt,$tilt_timestamp,$tilt_suppress_ctr,".
         "$proximity_last_go_far_time,$proximity_last_go_near_time,$accelStatus,$dpc_output,$dpc_output_timestamp,$prox_state,$dpc_ready,".
         "$tilt_last_go_one_timestamp,$facing_algo_last_go_one_timestamp,$hidden_last_seen_timestamp,$compute_on_this_samp,$is_stable,$buff_idx,".
         "$samp_count,$dpc_event_generated,$motion_status,$static_angle_count,$stream_period,$flat_static_flag,$proxStatus,$algo_inst_id\n";
   }
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_DPC_REPORT_C
# Version 1 & 2
# --------------------
sub  process_dpc_report {
   my $packet_type      = shift;
   my $version          = get_uint8();       # version of the log packet
   my $csvline = "$packet_type,$version,";
   
   if ($version == 1) {
      
      my $timestamp_type   = get_uint8();          
      my $timestamp        = get_uint32();
      my $dpc_event        = get_int32();
      my $algo_inst_id     = get_uint8();
      $csvline .= "$timestamp_type,$timestamp,$dpc_event,$algo_inst_id\n";
   }
   else {
      
      my $timestamp_type   = get_uint8();        # type of timestamp
      my $timestamp        = get_uint64();       # timestamp in SSC ticks
      my $dpc_event        = get_int32();        # Current DPC Event
      my $algo_inst_id     = get_uint8();        # algo instance id
      $csvline .= "$timestamp_type,$timestamp,$dpc_event,$algo_inst_id\n";
   }
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_TILT_W_DETECTOR_CONFIG_C
# Version 1
# --------------------
sub process_tilt_wearables_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();   # time stamp in SSC clock ticks (32768hz) when the report was generated. Only 32bits used.
   my $sample_rate      = get_uint32();   # Requested sensor sample rate.
   
   my $filter_window_seconds                          = get_float32();    # Number of seconds worth of filtered accel samples that are stored in to filtered sample buffer.
   my $accel_window_seconds                           = get_float32();    # Number of seconds worth of accel samples that are stored in raw sample buffer.
   my $window_for_end_accel_stability_check_seconds   = get_float32();    # Number of seconds worth of filtered accel samples to look backwards to check for sufficient stability at end of tilt motion.
   my $min_delta_pitch_threshold_deg                  = get_float32();    # Threshold for minimum pitch change in filter window for a valid tilt event.
   my $min_end_pitch_threshold_deg                    = get_float32();    # Threshold for the minimum final pitch for a valid tilt event.
   my $max_end_roll_threshold_deg                     = get_float32();    # Threshold for the maximum final roll for a valid tilt event.
   my $max_end_accel_spread_threshold                 = get_float32();    # Maximum norm of the delta between the final accel sample and the one that occurred WINDOW_FOR_END_ACCEL_STABILITY_CHECK_SECONDS ago for a valid tilt event.
   my $max_end_accel_norm_deviation_from_g_threshold  = get_float32();    # Maximum norm of the the final accel sample and gravity for a valid tilt event.
   my $adaptive_filter_tc_seconds                     = get_float32();
   my $tilt_threshold_motion_noise_coeff              = get_float32();    # Value 0 disables adaptive threshold.

   my $algo_inst_id        	= get_uint8();

   my $csvline = "$packet_type,$version,$timestamp_type,$timestamp,$sample_rate,$filter_window_seconds,$accel_window_seconds,";
   $csvline .= "$window_for_end_accel_stability_check_seconds,$min_delta_pitch_threshold_deg,$min_end_pitch_threshold_deg,$max_end_roll_threshold_deg,";
   $csvline .= "$max_end_accel_spread_threshold,$max_end_accel_norm_deviation_from_g_threshold,$adaptive_filter_tc_seconds,$tilt_threshold_motion_noise_coeff,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_TILT_W_DETECTOR_RESULT_C
# Version 1
# --------------------
sub  process_tilt_wearables_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   my $input_type       = get_uint8();       # 0 indicates accel input data, 1 indicates AMD input data.

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$input_type,";
   
   my $accelX             = get_int32();     # Accel sample input values in. Only valid if INPUT_TYPE = 0.             
   my $accelY             = get_int32();                  
   my $accelZ             = get_int32();
   my $amd_state          = get_uint32();    # AMD state input value. Only valid if INPUT_TYPE = 1. 0 = SNS_SAM_MOTION_UNKNOWN_V01  1 = SNS_SAM_MOTION_REST_V01  2 = SNS_SAM_MOTION_MOVE_V01
   
   if ($input_type == 0) { # accel
     $csvline  .= "$accelX,$accelY,$accelZ,,";
   } elsif ($input_type == 1) { # amd
     $csvline  .= ",,,$amd_state,";
   } else {
     print "LOG_SNS_TILT_W_DETECTOR_RESULT_C: Unknown input_type: $input_type"
   }
   
   my $input_ts                        = get_uint32();    # timestamp in SSC ticks (32768hz) of input (AMD_STATE or ACCEL[3].
   my $event_ts                        = get_uint32();    # Reported tilt event time stamp (32768hz clock). 0 = No tilt_w event occurred, >0 = time stamp of valid tilt event.
   my $delta_acc_squared_filtered      = get_float32();    
   my $cur_roll_in_range               = get_uint8();    
   my $cur_pitch_in_range              = get_uint8();    
   my $cur_accel_norm_in_range         = get_uint8();    
   my $cur_pos_is_stable               = get_uint8();    
   my $is_sufficient_tilt              = get_uint8();    
   my $algo_inst_id		       = get_uint8();

   $csvline .= "$input_ts,$event_ts,$delta_acc_squared_filtered,$cur_roll_in_range,$cur_pitch_in_range,";
   $csvline .= "$cur_accel_norm_in_range,$cur_pos_is_stable,$is_sufficient_tilt,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_TILT_W_DETECTOR_REPORT_C
# Version 1
# --------------------
sub  process_tilt_wearables_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   
   my $report_id        = get_uint32();   # Report id 
   my $report_type      = get_uint8();    # Report type: 0 – unknown, 1 – periodic, 2 - asynchronous, 3 - synchronous
   my $client_id        = get_uint8();    # Client id 
   my $event_timestamp  = get_uint32();   # Reported event timestamp, in SSC ticks   
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$client_id,$event_timestamp";

   my $accelX              = get_int32();   # Accel sample input values at time of tilt event.
   my $accelY              = get_int32();                  
   my $accelZ              = get_int32();
   my $algo_inst_id        = get_uint8();
   
   $csvline .= ",$accelX,$accelY,$accelZ,$algo_inst_id\n";
   
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_QHEART_CONFIG_C
# Version 1
# --------------------
sub process_qheart_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          # Always 0- SSC clock (32768hz)
   my $timestamp        = get_uint64();

   my $sample_rate_ppg                 = get_int32();       # Requested PPG sensor sample rate (Q16)
   my $sample_rate_accel               = get_int32();       # Requested accelerometer sensor sample rate (Q16)
   my $update_interval_in_fft_samples  = get_uint32();    
   my $max_alpha                       = get_float32();    
   my $min_alpha                       = get_float32();    
   my $min_oh                          = get_float32();    
   my $max_oh                          = get_float32();    
   my $max_del_b                       = get_float32();    
   my $acc_peak_distance               = get_uint32(); 
   my $ppg_peak_distance               = get_uint32(); 
   my $num_ppg_peaks                   = get_uint32(); 
   my $num_acc_peaks                   = get_uint32(); 
   my $peak_width_ppg                  = get_uint32(); 
   my $peak_thresh_ppg                 = get_float32(); 
   my $peak_thresh_acc                 = get_float32(); 
   my $max_ind_diff                    = get_uint32();  
   my $max_acc_thr                     = get_float32(); 
   my $harm_acc_thr                    = get_float32(); 
   my $globalminhr                     = get_float32(); 
   my $globalmaxhr                     = get_float32(); 
   my $noaccel_thresh                  = get_float32(); 
   my $accuracy_decay_alpha            = get_float32(); 
   my $android_accuracy_low_thresh     = get_float32(); 
   my $android_accuracy_high_thresh    = get_float32(); 
   my $android_accuracy_medium_thresh  = get_float32(); 
   my $do_minppg                       = get_uint8();  
   my $do_mingoodppgtrack              = get_uint8();  
   my $do_width_harm                   = get_uint8();  
   my $do_stride_is_hr_processing      = get_uint8();  
   my $is_one_shot                     = get_uint8();  
   my $report_interval                 = get_uint32();  

   my $algo_inst_id        	= get_uint8();

   my $csvline = "$packet_type,$version,$timestamp_type,$timestamp,$sample_rate_ppg,$sample_rate_accel,$update_interval_in_fft_samples";
   $csvline .= ",$max_alpha,$min_alpha,$min_oh,$max_oh,$max_del_b,$acc_peak_distance,$ppg_peak_distance,$num_ppg_peaks,$num_acc_peaks,$peak_width_ppg";
   $csvline .= ",$peak_thresh_ppg,$peak_thresh_acc,$max_ind_diff,$max_acc_thr,$harm_acc_thr,$globalminhr,$globalmaxhr,$noaccel_thresh,$accuracy_decay_alpha";
   $csvline .= ",$android_accuracy_low_thresh,$android_accuracy_high_thresh,$android_accuracy_medium_thresh,$do_minppg,$do_mingoodppgtrack,$do_width_harm";
   $csvline .= ",$do_stride_is_hr_processing,$is_one_shot,$report_interval,$algo_inst_id\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_QHEART_RESULT_C
# Version 1
# --------------------
sub  process_qheart_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   
   my $input_type             = get_uint8();    # Input; 0 indicates raw ppg input data, 1 indicates acell input data.  
   my $sensor_data0           = get_int32();    # Input; Input sensor data. Position 0 is PPG value when INPUT_TYPE=0, Positions 0,1,2 are accel x,y,z values when INPUT_TYPE=1              
   my $sensor_data1           = get_int32();             
   my $sensor_data2           = get_int32();    
   my $sensor_time            = get_uint32();   # Input; timestamp in SSC ticks of input sensor data.
   my $bpm                    = get_float32();    # Output; Reported heart rate in beats per minute
   my $bpm_time               = get_uint32();   # Output; Timestamp of last sensor report that resulted in updated BPM value.
   my $bpm_updated            = get_uint8();    # Output; 0=BPM not updated this iteration, 1=BPM was updated this iteration.
   my $bpm_quality            = get_uint8();    # Output; One of: NO_CONTACT = -1, UNRELIABLE = 0, ACCURACY_LOW = 1, ACCURACY_MEDIUM = 2, ACCURACY_HIGH = 3
   my $num_found_ppg_peaks    = get_uint32();
   my $num_found_acc_peaks    = get_uint32();
   my $prior_smooth_bpm       = get_float32(); 
   my $prior_smooth_harmppg   = get_float32(); 
   my $harmacc                = get_float32(); 
   my $harmpow                = get_float32(); 
   my $acc_pow_fft            = get_float32(); 
   my $locspeak               = get_uint32();
   my $harmppg                = get_float32(); 
   my $smooth_harmppg         = get_float32(); 
   my $harmppg_save           = get_float32(); 
   my $raw_bpm                = get_float32(); 
   my $smooth_bpm             = get_float32(); 
   my $state_bpm_quality      = get_uint8();

   my $algo_inst_id	      = get_uint8();

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$input_type,$sensor_data0,$sensor_data1,$sensor_data2,$sensor_time";
   $csvline .= ",$bpm,$bpm_time,$bpm_updated,$bpm_quality,$num_found_ppg_peaks,$num_found_acc_peaks,$prior_smooth_bpm,$prior_smooth_harmppg";
   $csvline .= ",$harmacc,$harmpow,$acc_pow_fft,$locspeak,$harmppg,$smooth_harmppg,$harmppg_save,$raw_bpm,$smooth_bpm,$state_bpm_quality,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_QHEART_REPORT_C
# Version 1
# --------------------
sub  process_qheart_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $report_id        = get_uint32();   # Report id 
   my $report_type      = get_uint8();    # Report type: 0 – unknown, 1 – periodic, 2 - asynchronous, 3 - synchronous
   my $client_id        = get_uint8();    # Client id 
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$client_id";

   my $bpm                    = get_float32();    # Output; Reported heart rate in beats per minute
   my $bpm_time               = get_uint32();   # Output; Timestamp of last sensor report that resulted in updated BPM value.
   my $bpm_updated            = get_uint8();    # Output; 0=BPM not updated this iteration, 1=BPM was updated this iteration.
   my $bpm_quality            = get_uint8();    # Output; One of: NO_CONTACT = -1, UNRELIABLE = 0, ACCURACY_LOW = 1, ACCURACY_MEDIUM = 2, ACCURACY_HIGH = 3
   my $algo_inst_id	      = get_uint8();
      
   $csvline .= ",$bpm,$bpm_time,$bpm_updated,$bpm_quality,$algo_inst_id\n";
      
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_SYNC_PROXY_CLIENT_C
# Version 1
# --------------------
sub  process_sync_proxy_client {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $qtimer_freq                  = get_uint64();          
   my $req_num_sync_schedules       = get_uint8();
   my $supported_num_sync_schedules = get_uint8();
   
   my $csvline = "$packet_type,$version,$qtimer_freq,$req_num_sync_schedules,$supported_num_sync_schedules";
   
   # Read in 10 sync schedules:  abs qtimer value and qtimer interval
   for my $i (1..10) {
      $csvline += ",".get_uint64().",".get_uint32();
   }
   
   my $req_rest_to_motion_latency   = get_uint32();
   my $req_motion_to_rest_latency   = get_uint32();
   my $client_time                  = get_uint64();
   my $client_state                 = get_uint8();
   my $motion_state_time            = get_uint32();
   my $motion_state                 = get_uint8();
   
   $csvline += ",$req_rest_to_motion_latency,$req_motion_to_rest_latency,$client_time,$client_state,$motion_state_time,$motion_state\n";
}

# --------------------
# LOG_SNS_IOD_CONFIG_C
# Version 1
# --------------------
sub process_iod_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          # Always 0- SSC clock (32768hz)
   my $timestamp        = get_uint64();

   my $confidence_threshold1           = get_float32();    # Threshold for indoor/outdoor detection
   my $confidence_threshold2           = get_float32();    # Threshold for indoor/outdoor detection
   my $time_of_day                     = get_uint64();     # Current time of day in the timezone where the UE is located
   my $sunset_timestamps               = get_uint32();     # UTC sunset timestamps in seconds from epoch
   my $sunrise_timestamps              = get_uint32();     # UTC sunrise timestamps in seconds from epoch
   my $iod_calibration_value           = get_float32();    # Calibration value for ALS scaling
   my $algo_inst_id        	       = get_uint8();      # Algorithm instance id

   my $csvline = "$packet_type,$version,$timestamp_type,$timestamp";
   $csvline .= ",$confidence_threshold1,$confidence_threshold2,$time_of_day,$sunset_timestamps,$sunrise_timestamps,$iod_calibration_value,$algo_inst_id\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_IOD_RESULT_C
# Version 1
# --------------------
sub  process_iod_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   
   my $gmm_likelihood1                 = get_float32();    # GMM likelihood
   my $gmm_likelihood2                 = get_float32();    # GMM likelihood
   my $hmm_parameter_selection_priors1 = get_float32();    # HMM parameter selection priorities
   my $hmm_parameter_selection_priors2 = get_float32();    # HMM parameter selection priorities
   my $hmm_transition_state            = get_uint8();      # HMM transition state (NORMAL_TRANSITION = 0, FAST_TRANSITION = 1, UNKNOWN_STABLE_TRANSITION = 2)
   my $hmm_transition_matrix1          = get_float32();    # HMM transition matrix
   my $hmm_transition_matrix2          = get_float32();    # HMM transition matrix
   my $hmm_transition_matrix3          = get_float32();    # HMM transition matrix
   my $hmm_transition_matrix4          = get_float32();    # HMM transition matrix
   my $previous_time_of_day            = get_uint32();     # Previous time of IOD execution, in seconds since epoch
   my $posterior_probability1          = get_float32();    # Posterior probabilities
   my $posterior_probability2          = get_float32();    # Posterior probabilities
   my $prior_iod_state_probability1    = get_float32();    # Prior IOD state probabilities
   my $prior_iod_state_probability2    = get_float32();    # Prior IOD state probabilities
   my $als_data                        = get_float32();    # ALS feature computed from ALS samples
   my $proximity_data                  = get_float32();    # Proximity feature – 1 phone not concealed, 0 phone concealed
   my $als_calibration_value           = get_float32();    # ALS calibration value
   my $sunset_timestamps               = get_uint32();     # UTC sunset timestamps in seconds from epoch
   my $sunrise_timestamps              = get_uint32();     # UTC sunrise timestamps in seconds from epoch
   my $confidence_threshold1           = get_float32();    # Threshold for indoor/outdoor detection
   my $confidence_threshold2           = get_float32();    # Threshold for indoor/outdoor detection
   my $timer_value                     = get_uint32();     # Request for new data after the specified amount of seconds
   my $iod_unknown_bitmask             = get_uint32();     # IOD reason bitmask (UNKNOWN_LOW_CONFIDENCE = 1, UNKNOWN_NIGHT = 2, UNKNOWN_CONCEALED = 4, UNKNOWN_ALS_LOW = 8)
   my $algo_inst_id	               = get_uint8();      # Algorithm instance id

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp";
   $csvline .= ",$gmm_likelihood1,$gmm_likelihood2,$hmm_parameter_selection_priors1,$hmm_parameter_selection_priors2,$hmm_transition_state";
   $csvline .= ",$hmm_transition_matrix1,$hmm_transition_matrix2,$hmm_transition_matrix3,$hmm_transition_matrix4,$previous_time_of_day";
   $csvline .= ",$posterior_probability1,$posterior_probability2,$prior_iod_state_probability1,$prior_iod_state_probability2,$als_data";
   $csvline .= ",$proximity_data,$als_calibration_value,$sunset_timestamps,$sunrise_timestamps,$confidence_threshold1,$confidence_threshold2";
   $csvline .= ",$timer_value,$iod_unknown_bitmask,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_IOD_REPORT_C
# Version 1
# --------------------
sub  process_iod_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $report_id           = get_uint32();   # Report id 
   my $report_type         = get_uint8();    # Report type: 0 – unknown, 1 – periodic, 2 - asynchronous, 3 - synchronous
   my $iod_output_state    = get_uint8();    # IOD output state (IOD_UNKNOWN = 0, IOD_INDOOR = 1, IOD_OUTDOOR = 2)
   my $confidence          = get_float32();  # Confidence for output state when indoor or outdoor, confidence for class indoor when output state is unknown
   my $iod_unknown_bitmask = get_uint32();   # IOD reason bitmask (UNKNOWN_LOW_CONFIDENCE = 1, UNKNOWN_NIGHT = 2, UNKNOWN_CONCEALED = 4, UNKNOWN_ALS_LOW = 8, UNKNOWN_PARAMETER_NOT_INITIALIZED = 0x10)
   my $iod_timer_value     = get_uint32();   # Internal execution request timer in seconds
   my $algo_inst_id	   = get_uint8();    # Algorithm instance id
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$iod_output_state";
   $csvline .= ",$confidence,$iod_unknown_bitmask,$iod_timer_value,$algo_inst_id\n";
      
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_IOD_AUTOCAL_CONFIG_C
# Version 1
# --------------------
sub process_ioda_config {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          # Always 0- SSC clock (32768hz)
   my $timestamp        = get_uint64();

   my $time_of_day                     = get_uint64();     # Current time of day in the timezone where the UE is located
   my $sunset_timestamps               = get_uint32();     # UTC sunset timestamps in seconds from epoch
   my $sunrise_timestamps              = get_uint32();     # UTC sunrise timestamps in seconds from epoch
   my $algo_inst_id        	       = get_uint8();      # Algorithm instance id

   my $csvline = "$packet_type,$version,$timestamp_type,$timestamp";
   $csvline .= ",$time_of_day,$sunset_timestamps,$sunrise_timestamps,$algo_inst_id\n";
   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_IOD_AUTOCAL_RESULT_C
# Version 1
# --------------------
sub  process_ioda_result {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();
   
   my $first_mom                    = get_float32();    # First moment of the logarithms (base e) of useful ALS samples obtained
   my $second_mom                   = get_float32();    # Second moment of the logarithms (base e) of useful ALS samples obtained
   my $num_samples                  = get_float32();    # Number of useful ALS samples obtained
   my $isdiscrete                   = get_uint8();      # Current decision about the range of ALS values (ISDISCRETE=1 for discrete, ISDISCRETE=0 for continuous)
   
   my @als_values;
   for my $i (0..15) {
      push(@als_values, get_float32());      # Array storing different ALS values to determine whether the range of values is discrete or continuous
   }
   
   my $current_calibration_value    = get_float32();    # Calibration value obtained from current state
   my $als_data                     = get_float32();    # Current logarithm (base e) of ALS sample
   my $proximity_data               = get_float32();    # Proximity feature – 1 phone not concealed, 0 phone concealed
   my $test_convergence             = get_uint8();      # Convergence check: (SUCCESS = 0, INVALID_AUTOCALIBRATION_COEFF = 4, INVALID_AUTOCALIBRATION_RESET =5, INVALID_AUTOCALIBRATION_CLIP2TOP = 6, INVALID_AUTOCALIBRATION_CLIP2BOTTOM = 7)
   my $sunset_timestamps            = get_uint32();     # UTC sunset timestamps in seconds from epoch
   my $sunrise_timestamps           = get_uint32();     # UTC sunrise timestamps in seconds from epoch
   my $algo_inst_id	            = get_uint8();      # Algorithm instance id

   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$first_mom,$second_mom,$num_samples,$isdiscrete";
   for my $als_value (@als_values) {
      $csvline .= ",$als_value";
   }
   $csvline .= ",$current_calibration_value,$als_data,$proximity_data,$test_convergence,$sunset_timestamps,$sunrise_timestamps,$algo_inst_id\n";

   print CSV_FILE $csvline;
   $num_csv_lines++;
}

# --------------------
# LOG_SNS_IOD_AUTOCAL_REPORT_C
# Version 1
# --------------------
sub  process_ioda_report {
   my $packet_type      = shift;
   my $version          = get_uint8();
   my $timestamp_type   = get_uint8();          
   my $timestamp        = get_uint64();

   my $report_id                       = get_uint32();   # Report id 
   my $report_type                     = get_uint8();    # Report type: 0 – unknown, 1 – periodic, 2 - asynchronous, 3 - synchronous
   my $iod_calibration_return_status   = get_uint8();    # AUTOCAL output state (NOT_ENOUGH_DATA = 0, CALIBRATION_VALID = 1)
   my $iod_calibration_value           = get_float32();  # Current calibration parameter
   
   # AUTOCAL current state:  FIRST_MOM, SECOND_MOM, NUM_SAMPLES,ISDISCRETE,VALUES
   my $first_mom                    = get_float32();    # First moment of the logarithms (base e) of useful ALS samples obtained
   my $second_mom                   = get_float32();    # Second moment of the logarithms (base e) of useful ALS samples obtained
   my $num_samples                  = get_float32();    # Number of useful ALS samples obtained
   my $isdiscrete                   = get_float32();    # Current decision about the range of ALS values (ISDISCRETE=1 for discrete, ISDISCRETE=0 for continuous)
   my @als_values;
   for my $i (0..15) {
      push(@als_values, get_float32());      # Array storing different ALS values to determine whether the range of values is discrete or continuous
   }
   
   my $algo_inst_id	   = get_uint8();    # Algorithm instance id
   
   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$report_id,$report_type,$iod_calibration_return_status,$iod_calibration_value";
   $csvline  .= ",$first_mom,$second_mom,$num_samples,$isdiscrete";
   for my $als_value (@als_values) {
      $csvline .= ",$als_value";
   }
   $csvline .= ",$algo_inst_id\n";
      
   print CSV_FILE $csvline;
   $num_csv_lines++;
}



# --------------------
# SNS_LOG_IFMC_RESULT_VERSION
# Version Unknown
# --------------------
#sub process_ifmc_result {
#   my $packet_type   = shift;
#
#   my $version          = get_uint8();
#   my $timestamp_type   = get_uint8();    # Type of timestamp
#   my $timestamp        = get_uint64();   # Timestamp in SSC ticks   
#
#   my $input_type                = get_uint8();    
#   my $input_smd_motion_state    = get_uint8();
#   my $input_ped_step_event       = get_uint8();
#   my $input_qmd_motion_state     = get_uint8();
#   
#   my $accel_x       = get_int32();             # Accel input X, m/s^2, Q16
#   my $accel_y       = get_int32();             # Accel input Y, m/s^2, Q16      
#   my $accel_z       = get_int32();             # Accel input Z, m/s^2, Q16
#   my $gyro_x        = get_int32();             # gyro input X, rad/s, Q16
#   my $gyro_y        = get_int32();             # gyro input Y, rad/s, Q16
#   my $gyro_z        = get_int32();             # gyro input Z, rad/s, Q16
#
#   my $state_accel_var         = get_float32();
#   my $state_cmc_motion_state  = get_uint8();
#   my $state_smd_motion_state  = get_uint8();
#   my $state_cum_num_turns     = get_uint64();
#   my $state_may_be_walking    = get_uint8();
#   my $state_step_count        = get_uint8();
#   my @state_obs_prob;
#   for (1..7) {
#      push(@state_obs_prob, get_float32());
#   }
#   my @state_belief;
#   for (1..7) {
#      push(@state_belief, get_float32());
#   }
#   
#   my $state_ifmc_label        = get_uint8();
#   my $state_run_autocorr      = get_uint8();   
#   
#   my $output_timestamp                   = get_uint32();   # Timestamp in SSC ticks   
#   my $output_motion_state                = get_uint8();    
#   my $output_motion_state_probability    = get_float32();    
#   my $output_gyro_on                     = get_uint8();  
#
#   my $instance         = get_uint8();    # Algorithm instance id 
#   my $accel_on         = get_uint8();    
#
#   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$input_type,$input_smd_motion_state,$input_ped_step_event,$input_qmd_motion_state";
#   $csvline .= ",$accel_x,$accel_y,$accel_z,$gyro_x,$gyro_y,$gyro_z,$state_accel_var,$state_cmc_motion_state,$state_smd_motion_state\n";
#   $csvline .= ",$state_cum_num_turns,$state_may_be_walking,$state_step_count,".join(',', @state_obs_prob).",".join(',', @state_belief)."\n";
#   $csvline .= ",$state_ifmc_label,$state_run_autocorr,$output_timestamp,$output_motion_state,$output_motion_state_probability,$output_gyro_on\n";
#   $csvline .= ",$instance,$accel_on\n";
#  
#   print CSV_FILE $csvline;
#   $num_csv_lines++;
#}

# --------------------
# SNS_LOG_IFMC_REPORT_VERSION
# Version Unknown
# --------------------
#sub process_ifmc_report {
#   my $packet_type   = shift;
#
#   my $version          = get_uint8();
#   my $timestamp_type   = get_uint8();    # Type of timestamp
#   my $timestamp        = get_uint64();   # Timestamp in SSC ticks   
#
#   my $output_motion_state                = get_uint8();    
#   my $output_motion_state_probability    = get_float32();    
#   my $output_gyro_on                     = get_uint8();  
#
#   my $instance         = get_uint8();    # Algorithm instance id 
#
#   my $csvline  = "$packet_type,$version,$timestamp_type,$timestamp,$output_motion_state,$output_motion_state_probability,$output_gyro_on,$instance\n";
#
#   print CSV_FILE $csvline;
#   $num_csv_lines++;
#}



sub process_packet
{
   # ---------------------------
   # read the QXDM packet header
   # ---------------------------
   my $real_packet_len = get_uint16();
   $packet_len     = $real_packet_len - 2;            # subtract off 2 because we got uint16
   my $packet_type = get_uint16() & 0x7FFF;
   my $ts          = get_uint64();

   if ( $isEOF) { 
      print "Log line #: $lineno   \r";
      return; 
   }
   
   $lineno++;                                         
   if (($lineno % 5000) == 0) {
      print "Log line #: $lineno               \r";     # show running DLF log line number.
   }

   # ===================================== 
   # maintain packet counts by packet type
   # ===================================== 
   
   my $packet_id = sprintf( "0x%X (%d)", $packet_type, $packet_type);
   if ( !defined( $packet_counts{ $packet_id} )) {
      $packet_counts{ $packet_id} = 0;
   }   
   $packet_counts{ $packet_id}++;


   if ( $packet_type == LOG_SNS_QMD_RESULT_C) {
      process_qmd_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QMD_CONFIG_C) {
      process_qmd_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QMD_REPORT_C) {
      process_qmd_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DSPS_PWR_C) {
      process_dsps_pwr( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GYRO_SIMP_CAL_RESULT_C) {     
      process_gyro_simp_cal_result( $packet_type);               
   }                                                              
   elsif ( $packet_type == LOG_SNS_GYRO_SIMP_CAL_REPORT_C) {
      process_gyro_simp_cal_report( $packet_type);          
   }                                                        
   elsif ( $packet_type == LOG_SNS_GRAVITY_CONFIG_C) {      
      process_gravity_config( $packet_type);                
   }                                                       
   elsif ( $packet_type == LOG_SNS_GRAVITY_RESULT_C) {
      process_gravity_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GRAVITY_REPORT_C) {
      process_gravity_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QUAT_CONFIG_C) {
      process_quat_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QUAT_RESULT_C) {
      process_quat_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QUAT_REPORT_C) {
      process_quat_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_MAG_CAL_CONFIG_C) {
      process_mag_cal_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_MAG_CAL_RESULT_C) {
      process_mag_cal_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FMV_CONFIG_C) {
      process_fmv_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FMV_QUAT_UPDATE_C) {
      process_fmv_quat_update( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FMV_MAG_UPDATE_C) {
      process_fmv_mag_update( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FMV_GYRO_UPDATE_C) {
      process_fmv_gyro_update( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FMV_REPORT_C) {
      process_fmv_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_ROTATION_VECTOR_CONFIG_C) {
      process_rotv_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_ROTATION_VECTOR_RESULT_C) {
      process_rotv_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_ROTATION_VECTOR_REPORT_C) {
      process_rotv_report( $packet_type);
   }
   elsif ( $packet_type == ISAGNAV_TS_PACKET) {
      process_isagnav_ts( $packet_type);        
   }
   elsif ( $packet_type == LOG_SNS_INTEG_ANGLE_CONFIG_C ) {
      process_integ_angle_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_INTEG_ANGLE_RESULT_C ) {
      process_integ_angle_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_INTEG_ANGLE_REPORT_C ) {
      process_integ_angle_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GYRO_TAP_CONFIG_C ) {
      process_gyro_tap_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GYRO_TAP_RESULT_C ) {
      process_gyro_tap_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GYRO_TAP_REPORT_C ) {
      process_gyro_tap_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_BASIC_GESTURES_CONFIG_C ) {
   process_basic_gestures_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_BASIC_GESTURES_RESULT_C ) {
      process_basic_gestures_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_BASIC_GESTURES_REPORT_C ) {
      process_basic_gestures_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FACING_CONFIG_C ) {
      process_facing_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FACING_RESULT_C ) {
      process_facing_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_FACING_REPORT_C ) {
      process_facing_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_ACCEL_CAL_CONFIG_C) {
      process_accel_cal_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_ACCEL_CAL_RESULT_C) {
      process_accel_cal_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_ACCEL_CAL_REPORT_C) {
      process_accel_cal_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PED_CONFIG_C) {
      process_ped_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PED_RESULT_C) {
      process_ped_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PED_REPORT_C) {
      process_ped_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PAM_CONFIG_C) {
      process_pam_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PAM_RESULT_C) {
      process_pam_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PAM_REPORT_C) {
      process_pam_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_SMD_CONFIG_C) {
      process_smd_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_SMD_RESULT_C) {
      process_smd_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_SMD_REPORT_C) {
      process_smd_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_CMC_CONFIG_C) {
      process_cmc_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_CMC_RESULT_C) {
      process_cmc_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_CMC_RESULT2_C) {
      process_cmc_result2( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_CMC_REPORT_C) {
      process_cmc_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DB_CONFIG_C) {        
      process_db_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DB_RESULT_C) {
      process_db_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DB_REPORT_C) {
      process_db_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SENSOR_FIFO_EVENT_C) {
      process_fifo_event( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_LATENCY_SAMPLING_POLL_C) {
      process_ltcy_sampling_poll( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_LATENCY_SAMPLING_DRI_C) {
      process_ltcy_sampling_dri( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_LATENCY_DELIVERY_C) {
      process_ltcy_delivery( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C) {      
      process_grv_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C) {
      process_grv_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C) {
      process_grv_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DRV_MD_IRQ_C) {
      process_md_irq( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QMAG_CAL_CONFIG_C) {      
      process_qmag_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QMAG_CAL_RESULT_C) {
      process_qmag_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QMAG_CAL_REPORT_C) {
      process_qmag_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C) {      
      process_geomagrv_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GEOMAG_ROT_VEC_RESULT_C) {
      process_geomagrv_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_GEOMAG_ROT_VEC_REPORT_C) {
      process_geomagrv_report( $packet_type);
   }   
   elsif ( $packet_type == LOG_SNS_PED_ALIGN_CONFIG_C) {      
      process_paln_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PED_ALIGN_RESULT1_C) {
      process_paln_result1( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PED_ALIGN_RESULT2_C) {
      process_paln_result2( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_PED_ALIGN_REPORT_C) {      
      process_paln_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_TILT_DETECTOR_CONFIG_C) {      
      process_tilt_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_TILT_DETECTOR_RESULT_C) {
      process_tilt_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_TILT_DETECTOR_REPORT_C) {      
      process_tilt_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_UIMAGE) {      
      process_uimage_packet( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DPC_CONFIG_C) {
      process_dpc_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DPC_RESULT_C) {
      process_dpc_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_DPC_REPORT_C) {
      process_dpc_report( $packet_type);
   }   
   elsif ( $packet_type == LOG_SNS_TILT_W_DETECTOR_CONFIG_C) {
      process_tilt_wearables_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_TILT_W_DETECTOR_RESULT_C) {
      process_tilt_wearables_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_TILT_W_DETECTOR_REPORT_C) {
      process_tilt_wearables_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QHEART_CONFIG_C) {
      process_qheart_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QHEART_RESULT_C) {
      process_qheart_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_QHEART_REPORT_C) {
      process_qheart_report( $packet_type);
   }      
   elsif ( $packet_type == LOG_SNS_SYNC_PROXY_CLIENT_C) {
      process_sync_proxy_client( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_IOD_CONFIG_C) {
      process_iod_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_IOD_RESULT_C) {
      process_iod_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_IOD_REPORT_C) {
      process_iod_report( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_IOD_AUTOCAL_CONFIG_C) {
      process_ioda_config( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_IOD_AUTOCAL_RESULT_C) {
      process_ioda_result( $packet_type);
   }
   elsif ( $packet_type == LOG_SNS_IOD_AUTOCAL_REPORT_C) {
      process_ioda_report( $packet_type);
   }            

   # ---------------------------------------
   # skip the packet, or skip to next packet
   # ---------------------------------------
   if ( $packet_len < 0) {
      my $output = sprintf( "\nprocess_packet() overrun: type 0x%x, lineno %d, \$packet_len %d\n",
                            $packet_type, $lineno, $packet_len);
      die $output;
   }
   skip_bytes( $packet_len);
}

sub ParseCmdLine {

   for ( my $i = 0; $i <= $#ARGV; $i++) {
      if ( $ARGV[ $i] eq "-l") {
         $i++;
         if ( $i > $#ARGV) {
            print "missing -l\'s log_filename\n";
         }
         else {
            $logFileName = $ARGV[ $i];
         }
      }
      elsif ( $ARGV[ $i] eq "-old") {
         $old = 1;
      }
   }
}

sub main {

   ParseCmdLine();

   if ( !defined( $logFileName)) {
      die "usage: $0 -l log_file_name\n";
   }

   open( INFILE, "<$logFileName") or die "Can\'t open $logFileName\n";
   binmode( INFILE);

   my ( $trimmedFileName) = ( $logFileName =~ /(.*)\.dlf/i );

   my $csvFileName = $trimmedFileName.($old ? "_prssamqmd.csv" : "_SAMPostProcess.csv");
   
   open( CSV_FILE, ">$csvFileName") or die "Can\'t open $csvFileName\n";

   while( !$isEOF) {
      process_packet();
   }

   print "\n";
   # ------------------------------------ 
   # display packet counts by packet type
   # ------------------------------------ 
   my @sorted = sort keys %packet_counts;
   while ( my $packet_id = shift @sorted) {
        my $value = $packet_counts{ $packet_id}; 

        my $outline   = sprintf( "$packet_id occurs $value\n");    
        print $outline
   } 
   
   print "\nNumber of CSV lines: $num_csv_lines\n";

   close( CSV_FILE);
   close( INFILE);
}


main();

