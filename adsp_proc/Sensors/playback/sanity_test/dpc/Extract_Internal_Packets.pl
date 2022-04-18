# ===================================================================================
# Copyright QUALCOMM (C) 2013-2015, All Rights Reserved.
#
# Extract_Internal_Packets.pl [-l log_file] [-d destination_folder] [-p packet_numbers] [-n] [-nh] [-a] [-h]
#
# Extract internal packets from a) an input DLF log file, or b) an input CSV file created by SAMPostProcess.pl,
# and save to individual CSV file(s) based on packet type.  
# Depending on the selected options, the output CSV file(s) are used within the offline playback framework or by the Data Visualizer.  
# This script requires SAMPostProcess.pl for parsing internal packets if a DLF log file is provided.
# The exe application of this script requires an input CSV log file because SAMPostProcess.pl is not available.
# 
# Inputs:
#  -l log_file:  (required) DLF log file, or a CSV file created by SAMPostProcess.pl.
#  -p packet_numbers:  (optional) Packet numbers to extract, in decimal or hex, and comma-separated.  Default is to extract all known packet types.
#  -d destination_folder:  (optional) The destination folder to save the output CSV files.
#  -a:  (optional) The option to keep the data as it is in the log file.
#  -nh:  (optional) The no header option for the output CSV files.
#  -n:  (optional) New filename option, i.e., do not use the DLF log file name as a pre-fix for the new output CSV files.
#  -h:  (optional) Help command for the script.
#
# References:  
#
# Revision History
# 04-15-2013   dfelnhof    Initial version
# 05-24-2013   dfelnhof    Add support for Significant Motion Detect, Coarse Motion Classifier and Distance Bound services. 
#                          Updated to support v18 of QMDPostProcess.pl.
# 07-23-2013   dfelnhof    Added support for FIFO and Latency packets.
#                          Updated to support v19 of QMDPostProcess.pl.
# 08-12-2013   dfelnhof    Provided fix for QMDPostProcess.pl bug, in which data is separated by commas (with or without a space).
# 08-20-2013   dfelnhof    Added support for Game Rotation Vector.
#                          Updated to support v21 of QMDPostProcess.pl.
# 09-27-2013   dfelnhof    Fixed formatting issues with interpreting latency packets (including adding lookup tables for sensor IDs).
# 10-08-2013   dfelnhof    Improved CSV file handling and relocated the lookup hashes.
#                          Fixed the legend entry for the LOG_SNS_ROTATION_VECTOR_RESULT_C (0x1560) packet.
# 11-25-2013   dfelnhof    Updated documentation to be compatible with creating an executable version using perlapp.
# 02-11-2014   dfelnhof    Added support for MD IRQ packet.
# 03-14-2014   dfelnhof    Added support for QMAG Cal (but not tested because SW implementation is not done).
#                          Added support for GPS timestamp, but is it the same as DSPS?
# 04-21-2014   dfelnhof    Added support for Pedestrian Alignment (PALN).
# 04-28-2014   dfelnhof    Fixed the SMD log codes.
# 06-12-2014   dfelnhof    Added support for CMC2.0.
# 06-13-2014   dfelnhof    Added support for Tilt.  Added lookup values for Report Type in Report messages for QMD, Quat,
#                          Gravity, MagC, RotV, GyroTap, GyroInt, FMV, Facing, Basic Gestures, PED, and SMD.
#                          Modified the PALN result2 and report packets to support the relative turn angle fields.
# 06-19-2014   dfelnhof    Added the [-n] option for creating new file names that are not based on the log file.
# 06-24-2014   dfelnhof    Added support for version 2 distance bound config and result packets.
# 09-15-2014   dfelnhof    Updated LOG_SNS_DB_RESULT_C packet parser for version 2.
#                          Added support for DPC (Device Position Classifier).
# 10-01-2014   dfelnhof    Added support for uImage version 3 packet.
# 10-02-2014   dfelnhof    Added support for DPC.
#                          Updated CMC Motion Event enumeration to:  2 => "Exit", 1 => "Entry", 0 => "Out", 3 => "In".
# 01-28-2015   dfelnhof    Support was added for renaming QMDPostProcess.pl to SAMPostProcess.pl
# 02-02-2015   dfelnhof    Added support for Tilt wearable detector and QHeart.
# 02-13-2015   dfelnhof    Added support for Sync Proxy.
# 04-15-2015   dfelnhof    Supporting _SAMPostProcess.csv filename from SAMPostProcess.pl.
# 05-15-2015   dfelnhof    Changed timestamp precision from 2 decimal places to 3 decimal places.
# 10-20-2015   dfelnhof    Added support for DPC version 2 (still needs additional support), IOD and IOD Autocal packets.
# 01-29-2015   dfelnhof    Updated DPC version 2 packets.
#
#
# Notes:
# Need SAMPostProcess support before fully implementing: packet types commented out below.
#
# ===================================================================================

use strict;
use warnings;
use File::Path;
use File::Spec;
use File::Basename;
use IO::File;

use constant PI => 3.14159265358979;

my $flagN = 0;             # Optional input argument, do not use the DLF log file name as a pre-fix for the new output CSV files
my $flagNH = 0;            # The no header flag, default (0) is to have a header
my $flagA = 0;             # The no header flag, default (0) is to have a header
my %packetsToExtract;      # The user entered list of packet numbers to extract (in decimal format)
my $destination;           # The destination folder for the output files
my $logFileName;           # The user entered log file name (DLF or CSV)

my $logType;               # The type of log file, .dlf or .csv
my $csvFileName;           # The CSV log file

my $csvFiles;              # A hash for all the opened CSV output files
my $packetsProcessed = 0;  # The number of packets extracted
my $packetsTotal = 0;      # The total number of packets in the log

# Special consideration must be given to EXE applications of this script because SAMPostProcess.pl is unavailable.
my $isEXE = (substr(lc($0), -3, 3) eq "exe");
   
# Look-up values, see: SRTNativeConstants.pm
my %lit_PowerState = ();
$lit_PowerState{1}{0}  = 'Off';
$lit_PowerState{1}{1}  = 'On';
$lit_PowerState{2}{0}  = 'Hibernation';
$lit_PowerState{2}{1}  = 'Dormant';
$lit_PowerState{2}{2}  = 'Low';
$lit_PowerState{2}{3}  = 'High';
$lit_PowerState{2}{4}  = 'Unknown';
my %lit_TrueFalse = (1 => "True", 0 => "False");
my %lit_AlgoState = (1 => "Active", 0 => "InActive");
my %lit_qmdMotionStates = (0 => "Unknown", 1 => "Rest", 2 => "Motion");
my %lit_qmd_service_name = (4 => 'AMD', 5 => 'RMD', 6 => 'VMD', 9 => 'FNS', 10 => 'BTE');
my %lit_SamAccuracy = (0 => 'Unreliable', 1 => 'Low', 2 => 'Medium', 3 => 'High');
my %lit_gravMotionStates = (-1 => "Undefined", 0 => "Unknown", 1 => "AbsRest", 2 => "RelRest", 3 => "Motion");
my %lit_rotvCoordSys = (0 => 'SAE', 1 => 'ENU');
my %lit_gyro_tap_Gestures = (1 => "Left", 2 => "Right", 3 => "Top", 4 => "Bottom", 5 => "Front", 6 => "Back");
my %lit_basic_Gestures = (1 => "Push", 2 => "Pull", 3 => "Left", 4 => "Right", 5 => "Top", 6 => "Bottom", 7 => "Unknown");
my %lit_facing_Gestures = (1 => "Up", 2 => "Down", 3 => "Neutral");
my %lit_fifo_event = (0 => "Enabled", 1 => "Disabled", 2 => "Available", 3 => "WM_Int", 4 => "Overflow", 5 => "ODR_Changed", 6 => "Read_WM", 7 => "Read_Flush", 8 => "Drain");
my %lit_breach_event = (1 => "Breach", 0 => "No Breach");
my %lit_cmc_input_type = (0 => "Accel", 1 => "QMD", 2 => "Update Reporting Input");
my %lit_cmc_reporting_type = ( 0 => "None", 1 => "Exit Only", 2 => "Enter Only", 3 => "All");
my %lit_cmc_motion_state_event = ( 2 => "Exit", 1 => "Entry", 0 => "Out", 3 => "In");
my %lit_cmc_motion_states = (0 => "Unknown", 1 => "Stationary", 2 => "Move", 3 => "Fiddle", 4 => "Pedestrian", 5 => "Vehicle", 6 => "Walk", 7 => "Run", 8 => "Bike");
my %lit_SensorID  = (0 => "ACCEL", 1 => "ACCEL2", 10 => "GYRO", 20 => "MAG", 30 => "PRESSURE", 40 => "PROX-LIGHT", 50 => "HUMIDITY ", 220 => "ESP-SD", 222 => "ESP-SC", 224 => "ESP-SMD", 226 => "ESP-GRV", 228 => "ESP-IRG", 230 => "ESP-TAP" );
my %lit_Reset = (1 => "Reset Happens", 0 => "No Reset");
my %lit_CalAlgoType = (0 => 'HI', 1 => "SI", 2 => "HI & SI");
my %lit_QMagInputType = (0 => 'Mag Data', 1 => "Accel Data");
my %lit_ReportType = (0 => 'Unknown', 1 => 'Periodic', 2 => 'Asynchronous', 3 => 'Synchronous');
my %lit_rotv_algorithm = (0 => 'Rotation Vector', 1 => 'Game RV', 2 => 'Orientation');
my %lit_PALNInputType = (0 => 'Accel', 1 => 'RotV');
my %lit_PALN_Events = (0 => 'No Events', 1 => 'Pedestrian Turn', 2 => 'Device Alignment', 3 => 'Turn and Alignment');
my %lit_DPC_Events = (0 => 'Picked Up', 1 => 'Concealed', 2 => 'On Desk', 3 => 'State Changed');
my %lit_DPC_Events_v2 = (0 => 'Unknown', 1 => 'Flat Static', 2 => 'Hidden', 3 => 'In Hand', 4 => 'Facing');
my %lit_Proximity = (65536 => 'Near', 1 => 'Near', 0 => 'Far');
my %lit_DPC_InputTypes = (1 => 'Accelerometer', 2 => 'Proximity', 3 => 'Motion Interrupt', 4 => 'AMD');
my %lit_DPC_DevicePositions = (0 => 'On Desk', 1 => 'In Pocket', 2 => 'Unknown');
my %lit_DPC_DevicePositions_v2 = (0 => 'Unknown', 1 => 'Flat Static', 2 => 'Hidden', 3 => 'In Hand');
my %lit_DPC_DetectionStatus = (0 => 'Unknown', 1 => 'True', 2 => 'False');
my %lit_DPC_AccelStatus = (0 => 'Periodic', 1 => 'Buffered', 2 => 'Pause');
my %lit_DPC_ProxStatus = (0 => 'Turn ON', 1 => 'Turn OFF');
my %lit_DPC_DetectorOpState = (1 => 'Off', 2 => 'On');
my %lit_DPC_DetectorState = (1 => 'Initial', 2 => 'Wait for Stable', 3 => 'Wait for Stable Unknown');
my %lit_uImageVote = (1 => 'uImage', 2 => 'Big Image', 4 => 'No Client');
my %lit_Tilt_InputType = (0 => 'Accel', 1 => 'AMD');
my %lit_QHeart_InputType = (0 => 'PPG', 1 => 'Accel');
my %lit_BPM_Updated = (0 => 'BPM Not updated (0)', 1 => 'BPM Updated (1)');
my %lit_BPM_Quality = (-1 => 'NO_CONTACT', 0 => 'UNRELIABLE', 1 => 'ACCURACY_LOW', 2 => 'ACCURACY_MEDIUM', 3 => 'ACCURACY_HIGH');
my %lit_Processor_state = (0 => 'Unknown', 1 => 'Sleeping', 2 => 'Awake');
my %lit_IODHMMTransitionState = (0 => 'Normal Transition', 1 => 'Transition', 2 => 'Unkown Stable Transition');
my %lit_IODProximity = (0 => 'Phone Concealed', 1 => 'Phone Not Concealed');
my %lit_IODState = (0 => 'Unknown', 1 => 'Indoor', 2 => 'Outdoor');
my %lit_IODAIsDiscrete = (0 => 'Continuous', 1 => 'Discrete');
my %lit_IODATestConvergence = (0 => 'Success', 4 => 'Invalid Autocalibration Coeff', 5 => 'Invalid Autocalibration Reset', 6 => 'Invalid Autocalibration Clip2Top', 7 => 'Invalid Autocalibration Clip2Bottom');
my %lit_IODACalibrationStatus = (0 => 'Not Enough Data', 1 => 'Calibration Valid');

# The list of available sensor IDs for 0x14C1 packets, see: //source/qcom/qct/core/sensors/dsps/dsps/main/latest/ddf/inc/sns_ddf_common.h
my %lit_DriverSensorID = (0 => "NONE", 1 => "ACCEL", 2 => "MAG", 3 => "GYRO", 4 => "TEMP", 5 => "PROXIMITY", 6 => "AMBIENT", 7 => "PRESSURE", 8 => "MAG-6D", 9 => "GYRO-6D");


my %supportedPackets = (   # The supported packet number and the corresponding data legend
    oct("0x151B") => "LOG_SNS_DSPS_PWR_C",           
    #oct("0x151C") => "LOG_SNS_RAW_I2C_DATA_C",
    oct("0x151D") => "LOG_SNS_QMD_CONFIG_C",           
    oct("0x151E") => "LOG_SNS_QMD_RESULT_C",           
    oct("0x151F") => "LOG_SNS_QMD_REPORT_C",
    #oct("0x1523") => "LOG_SNS_FNS_CONFIG_C",           
    #oct("0x1524") => "LOG_SNS_FNS_RESULT_C",           
    #oct("0x1525") => "LOG_SNS_FNS_REPORT_C",
    #oct("0x1528") => "LOG_SNS_BTE_CONFIG_C",           
    #oct("0x1529") => "LOG_SNS_BTE_RESULT_C",           
    #oct("0x152A") => "LOG_SNS_BTE_REPORT_C", 
    oct("0x152B") => "LOG_SNS_GYRO_SIMP_CAL_CONFIG_C",           
    oct("0x152C") => "LOG_SNS_GYRO_SIMP_CAL_RESULT_C",           
    oct("0x152D") => "LOG_SNS_GYRO_SIMP_CAL_REPORT_C",           
    oct("0x153C") => "LOG_SNS_QUAT_CONFIG_C",           
    oct("0x153D") => "LOG_SNS_QUAT_RESULT_C",           
    oct("0x153E") => "LOG_SNS_QUAT_REPORT_C",           
    oct("0x153F") => "LOG_SNS_GRAVITY_CONFIG_C",           
    oct("0x1540") => "LOG_SNS_GRAVITY_RESULT_C",           
    oct("0x1541") => "LOG_SNS_GRAVITY_REPORT_C",
    #oct("0x1542") => "LOG_SNS_FULL_CALIBRATION_C",           
    oct("0x1559") => "LOG_SNS_DRV_MD_IRQ_C",           
    oct("0x155A") => "LOG_SNS_MAG_CAL_CONFIG_C",           
    oct("0x155B") => "LOG_SNS_MAG_CAL_RESULT_C",           
    oct("0x155C") => "LOG_SNS_MAG_CAL_REPORT_C",           
    oct("0x155F") => "LOG_SNS_ROTATION_VECTOR_CONFIG_C",           
    oct("0x1560") => "LOG_SNS_ROTATION_VECTOR_RESULT_C",           
    oct("0x1561") => "LOG_SNS_ROTATION_VECTOR_REPORT_C",           
    oct("0x1562") => "LOG_SNS_FMV_CONFIG_C",           
    oct("0x1563") => "LOG_SNS_FMV_QUAT_UPDATE_C",           
    oct("0x1564") => "LOG_SNS_FMV_MAG_UPDATE_C",           
    oct("0x1565") => "LOG_SNS_FMV_GYRO_UPDATE_C",           
    oct("0x1566") => "LOG_SNS_FMV_REPORT_C",
    #oct("0x158F") => "LOG_SNS_TIME_SERVICE_OFFSETS_C",           
    oct("0x150B") => "ISAGNAV_TS_PACKET",
    oct("0x159B") => "LOG_SNS_INTEG_ANGLE_CONFIG_C",         
    oct("0x159C") => "LOG_SNS_INTEG_ANGLE_RESULT_C",           
    oct("0x159D") => "LOG_SNS_INTEG_ANGLE_REPORT_C",           
    oct("0x159E") => "LOG_SNS_GYRO_TAP_CONFIG_C",           
    oct("0x159F") => "LOG_SNS_GYRO_TAP_RESULT_C",           
    oct("0x15A0") => "LOG_SNS_GYRO_TAP_REPORT_C",           
    oct("0x15A1") => "LOG_SNS_BASIC_GESTURES_CONFIG_C",           
    oct("0x15A2") => "LOG_SNS_BASIC_GESTURES_RESULT_C",           
    oct("0x15A3") => "LOG_SNS_BASIC_GESTURES_REPORT_C",           
    oct("0x15A4") => "LOG_SNS_FACING_CONFIG_C",           
    oct("0x15A5") => "LOG_SNS_FACING_RESULT_C",           
    oct("0x15A6") => "LOG_SNS_FACING_REPORT_C",
    #oct("0x15A9") => "LOG_SNS_ALGO_INPUT_C",           
    #oct("0x15AA") => "LOG_SNS_GYROINT_CONFIG_C",           
    #oct("0x15AB") => "LOG_SNS_GYROINT_UPDATE_C",           
    #oct("0x15AC") => "LOG_SNS_GYROINT_REPORT_C",
    #oct("0x15AD") => "LOG_SNS_GYROINT_REPORT_REQUEST_C",
    #oct("0x15AE") => "LOG_SNS_GYROBUF_CONFIG_C",           
    #oct("0x15AF") => "LOG_SNS_GYROBUF_REPORT_REQUEST_C",           
    #oct("0x15B0") => "LOG_SNS_GYROBUF_REPORT_C",
    oct("0x15B8") => "LOG_SNS_ACCEL_CAL_CONFIG_C",           
    oct("0x15B9") => "LOG_SNS_ACCEL_CAL_RESULT_C",           
    oct("0x15BA") => "LOG_SNS_ACCEL_CAL_REPORT_C",
    oct("0x1637") => "LOG_SNS_PED_CONFIG_C",
    oct("0x1638") => "LOG_SNS_PED_RESULT_C",           
    oct("0x1639") => "LOG_SNS_PED_REPORT_C",
    oct("0x163A") => "LOG_SNS_QMAG_CAL_CONFIG_C",  
    oct("0x163B") => "LOG_SNS_QMAG_CAL_RESULT_C",  
    oct("0x163C") => "LOG_SNS_QMAG_CAL_REPORT_C",  
    oct("0x1640") => "LOG_SNS_PAM_CONFIG_C",           
    oct("0x1641") => "LOG_SNS_PAM_RESULT_C",           
    oct("0x1642") => "LOG_SNS_PAM_REPORT_C",           
    oct("0x17EA") => "LOG_SNS_CMC_CONFIG_C",
    oct("0x17EB") => "LOG_SNS_CMC_RESULT_C",
    oct("0x17EC") => "LOG_SNS_CMC_REPORT_C",
    oct("0x17ED") => "LOG_SNS_DB_CONFIG_C",
    oct("0x17EE") => "LOG_SNS_DB_RESULT_C",
    oct("0x17EF") => "LOG_SNS_DB_REPORT_C",
    oct("0x17F0") => "LOG_SNS_CMC_RESULT2_C",           
    oct("0x17F3") => "LOG_SENSOR_FIFO_EVENT_C",
    oct("0x17F8") => "LOG_SNS_SMD_CONFIG_C",           
    oct("0x17F9") => "LOG_SNS_SMD_RESULT_C",           
    oct("0x17FA") => "LOG_SNS_SMD_REPORT_C",
    oct("0x17FB") => "LOG_SNS_LATENCY_SAMPLING_POLL_C",
    oct("0x17FC") => "LOG_SNS_LATENCY_SAMPLING_DRI_C",
    oct("0x17FD") => "LOG_SNS_LATENCY_DELIVERY_C",
    oct("0x17FE") => "LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C",
    oct("0x17FF") => "LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C",
    oct("0x1800") => "LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C",
    #oct("0x1834") => "",   # SNS Run-Time Tuning Request           # Obsolete
    #oct("0x1835") => "",   # SNS Run-Time Tuning Response          # Obsolete
    #oct("0x1836") => "",   # SNS BMA2X2 Tune Double-Tap            # Obsolete
    oct("0x183A") => "LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C",   
    oct("0x183B") => "LOG_SNS_GEOMAG_ROT_VEC_RESULT_C",   
    oct("0x183C") => "LOG_SNS_GEOMAG_ROT_VEC_REPORT_C",
    oct("0x186C") => "LOG_SNS_PED_ALIGN_CONFIG_C",
    oct("0x186D") => "LOG_SNS_PED_ALIGN_RESULT1_C",
    oct("0x186E") => "LOG_SNS_PED_ALIGN_RESULT2_C",
    oct("0x186F") => "LOG_SNS_PED_ALIGN_REPORT_C",
    oct("0x1887") => "LOG_SNS_TILT_DETECTOR_CONFIG_C",
    oct("0x1888") => "LOG_SNS_TILT_DETECTOR_RESULT_C",
    oct("0x1889") => "LOG_SNS_TILT_DETECTOR_REPORT_C",
    oct("0x188D") => "LOG_SNS_UIMAGE",
    oct("0x189B") => "LOG_SNS_DPC_CONFIG_C",
    oct("0x189C") => "LOG_SNS_DPC_RESULT_C",
    oct("0x189D") => "LOG_SNS_DPC_REPORT_C",
    oct("0x18B7") => "LOG_SNS_TILT_W_DETECTOR_CONFIG_C",
    oct("0x18B8") => "LOG_SNS_TILT_W_DETECTOR_RESULT_C",
    oct("0x18B9") => "LOG_SNS_TILT_W_DETECTOR_REPORT_C",
    oct("0x18BA") => "LOG_SNS_QHEART_CONFIG_C",
    oct("0x18BB") => "LOG_SNS_QHEART_RESULT_C",
    oct("0x18BC") => "LOG_SNS_QHEART_REPORT_C",
    oct("0x18C2") => "LOG_SNS_SYNC_PROXY_CLIENT_C",
    oct("0x1918") => "LOG_SNS_IOD_CONFIG_C",
    oct("0x1919") => "LOG_SNS_IOD_RESULT_C",
    oct("0x191A") => "LOG_SNS_IOD_REPORT_C",
    oct("0x191B") => "LOG_SNS_IOD_AUTOCAL_CONFIG_C",
    oct("0x191C") => "LOG_SNS_IOD_AUTOCAL_RESULT_C",
    oct("0x191D") => "LOG_SNS_IOD_AUTOCAL_REPORT_C",

);  # supportedPackets


my %legends = ();   # The legends for the supported packets
    #LOG_SNS_DSPS_PWR_C                 => 0x151B;
    $legends{oct("0x151B")}{"Original"} = "#packet_type,version,ts,power_state";
    $legends{oct("0x151B")}{"New"} = "#Packet,Version,Timestamp (ms),Power State";           
    #LOG_SNS_QMD_CONFIG_C               => 0x151D;
    $legends{oct("0x151D")}{"Original"} = "#packet_type,version,ts,sample_rate,enable_amd,enable_vmd,enable_rmd,instance_id";           
    $legends{oct("0x151D")}{"New"} = "#Packet,Version,Timestamp (ms),Sample Rate (Hz),Enable AMD,Enable VMD,Enable RMD,Instance";           
    #LOG_SNS_QMD_RESULT_C               => 0x151E;
    $legends{oct("0x151E")}{"Original"} = "#packet_type,version,ts,accelX,accelY,accelZ,amd_result,vmd_result,rmd_result,instance_id";           
    $legends{oct("0x151E")}{"New"} = "#Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),AMD Result,VMD Result,RMD Result,Instance";           
    #LOG_SNS_QMD_REPORT_C               => 0x151F;
    $legends{oct("0x151F")}{"Original"} = "#packet_type,version,ts,report_id,report_type,client_id,qmd_result,service_id,instance_id";           
    $legends{oct("0x151F")}{"New"} = "#Packet,Version,Timestamp (ms),Report ID,Report Type,Client ID,QMD Result,Service ID,Instance";           
    #LOG_SNS_GYRO_SIMP_CAL_CONFIG_C     => 0x152B;
    $legends{oct("0x152B")}{"Original"} = "#packet_type,version,ts,sample_rate,instance_id";           
    $legends{oct("0x152B")}{"New"} = "#Packet,Version,Timestamp (ms),Sample Rate (Hz),Instance";           
    #LOG_SNS_GYRO_SIMP_CAL_RESULT_C     => 0x152C;
    $legends{oct("0x152C")}{"Original"} = "#packet_type,version,ts,gyro_x,gyro_y,gyro_z,gyro_zbx,gyro_zby,gyro_zbz,instance_id";           
    $legends{oct("0x152C")}{"New"} = "#Packet,Version,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Zero Bias X (deg/s),Zero Bias Y (deg/s),Zero Bias Z (deg/s),Instance";           
    #LOG_SNS_GYRO_SIMP_CAL_REPORT_C     => 0x152D;
    $legends{oct("0x152D")}{"Original"} = "#packet_type,version,ts,gyro_x,gyro_y,gyro_z,gyro_zbx,gyro_zby,gyro_zbz";           
    $legends{oct("0x152D")}{"New"} = "#Packet,Version,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Zero Bias X (deg/s),Zero Bias Y (deg/s),Zero Bias Z (deg/s)";           
    #LOG_SNS_QUAT_CONFIG_C              => 0x153C;        
    $legends{oct("0x153C")}{"Original"} = "#packet_type,version,ts_type,ts,report_period,sample_rate,instance_id";           
    $legends{oct("0x153C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Instance";           
    #LOG_SNS_QUAT_RESULT_C              => 0x153D;
    $legends{oct("0x153D")}{"Original"} = "#packet_type,version,ts_type,ts,gyro_x,gyro_y,gyro_z,quat0,quat1,quat2,quat3,delta_t,instance_id";           
    $legends{oct("0x153D")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Quat0,Quat1,Quat2,Quat3,Delta Time,Instance";           
    #LOG_SNS_QUAT_REPORT_C              => 0x153E;
    $legends{oct("0x153E")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,quat1,quat2,quat3,quat4,instance_id";           
    $legends{oct("0x153E")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Quat0,Quat1,Quat2,Quat3,Instance";           
    #LOG_SNS_GRAVITY_CONFIG_C           => 0x153F;        
    $legends{oct("0x153F")}{"Original"} = "#packet_type,version,ts_type,ts,report_period,sample_rate,time_cons_abs,time_cons_rel,time_cons_mot,instance_id";           
    $legends{oct("0x153F")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Abs Rest Time Constant,Rel Rest Time Constant,Motion Time Constant,Instance";           
    #LOG_SNS_GRAVITY_RESULT_C           => 0x1540;        
    $legends{oct("0x1540")}{"Original"} = "#packet_type,version,ts_type,ts,gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z,abs_state,rel_state,grav_est_x,grav_est_y,grav_est_z,linacc_x,linacc_y,linacc_z,delta_t,alpha,instance_id";           
    $legends{oct("0x1540")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Absolute Rest State,Relative Rest State,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),Delta Time,Alpha,Instance";           
    #LOG_SNS_GRAVITY_REPORT_C           => 0x1541;        
    $legends{oct("0x1541")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,grav_x,grav_y,grav_z,linacc_x,linacc_y,linacc_z,instance_id";           
    $legends{oct("0x1541")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),Instance";
    #LOG_SNS_DRV_MD_IRQ_C               => 0x1559;  
    $legends{oct("0x1559")}{"Original"} = "#packet_type,version,ts,threshold";           
    $legends{oct("0x1559")}{"New"} = "#Packet,Version,Timestamp (ms),Threshold (milliG)";           
    #LOG_SNS_MAG_CAL_CONFIG_C           => 0x155A;    
    $legends{oct("0x155A")}{"Original"} = "#packet_type,version,ts_type,ts,report_period,sample_rate,instance_id";           
    $legends{oct("0x155A")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Instance";           
    #LOG_SNS_MAG_CAL_RESULT_C           => 0x155B; 
    $legends{oct("0x155B")}{"Original"} = "#packet_type,version,ts_type,ts,mag_x,mag_y,mag_z,magcal_x,magcal_y,magcal_z,magcalbias_x,magcalbias_y,magcalbias_z,accuracy,instance_id";           
    $legends{oct("0x155B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Mag X (Gs),Mag Y (Gs),Mag Z (Gs),MagCal X (Gs),MagCal Y (Gs),MagCal Z (Gs),MagCalBias X (Gs),MagCalBias Y (Gs),MagCalBias Z (Gs),Accuracy,Instance";           
    #LOG_SNS_MAG_CAL_REPORT_C           => 0x155C; 
    $legends{oct("0x155C")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,magcal_x,magcal_y,magcal_z,magcalbias_x,magcalbias_y,magcalbias_z,accuracy,instance_id";           
    $legends{oct("0x155C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,MagCal X (Gs),MagCal Y (Gs),MagCal Z (Gs),MagCalBias X (Gs),MagCalBias Y (Gs),MagCalBias Z (Gs),Accuracy,Instance";           
    #LOG_SNS_ROTATION_VECTOR_CONFIG_C   => 0x155F;    
    $legends{oct("0x155F")}{"Original"} = "#packet_type,version,ts_type,ts,report_period,sample_rate,coord_sys,instance";           
    $legends{oct("0x155F")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Coordinate System,Instance";           
    #LOG_SNS_ROTATION_VECTOR_RESULT_C   => 0x1560;     
    $legends{oct("0x1560")}{"Original"} = "#packet_type,version,ts_type,ts,grav_x,grav_y,grav_z,grav_ts,grav_acc,fm_x,fm_y,fm_z,fm_ts,fm_acc,rotv0,rotv1,rotv2,rotv3,accuracy,coord_sys,instance";           
    $legends{oct("0x1560")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Gravity Timestamp (ms),Gravity Accuracy,FMV X (Gs),FMV Y (Gs),FMV Z (Gs),FMV Timestamp (ms),FMV Accuracy,RotV0,RotV1,RotV2,RotV3,Accuracy,Coordinate System,Instance";           
    #LOG_SNS_ROTATION_VECTOR_REPORT_C   => 0x1561;     
    $legends{oct("0x1561")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,rotv0,rotv1,rotv2,rotv3,accuracy,coord_sys,instance";           
    $legends{oct("0x1561")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,RotV0,RotV1,RotV2,RotV3,Accuracy,Coordinate System,Instance";           
    #LOG_SNS_FMV_CONFIG_C               => 0x1562;    
    $legends{oct("0x1562")}{"Original"} = "#packet_type,version,ts_type,ts,report_period,sample_rate,num_accuracy_bins,accuracy_bin_tcs0,accuracy_bin_tcs1,accuracy_bin_tcs2,accuracy_bin_tcs3,gyro_gap_thresh,mag_gap_thresh,min_turn_rate,max_mag_innovation,instance_id";           
    $legends{oct("0x1562")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Accuracy Bin Count,Accuracy Bin tcs0,Accuracy Bin tcs1,Accuracy Bin tcs2,Accuracy Bin tcs3,Gyro Gap Threshold,Mag Gap Threshold,Min Turn Rate,Max Mag Innovation,Instance";           
    #LOG_SNS_FMV_QUAT_UPDATE_C          => 0x1563;     
    $legends{oct("0x1563")}{"Original"} = "#packet_type,version,ts_type,quat_ts,fmv_ts,quat0,quat1,quat2,quat3,fmv_x,fmv_y,fmv_z,accuracy,instance";           
    $legends{oct("0x1563")}{"New"} = "#Packet,Version,Timestamp Type,QUAT Timestamp (ms),FMV Timestamp (ms),Quat0,Quat1,Quat2,Quat3,FMV X (Gs),FMV Y (Gs),FMV Z (Gs),Accuracy,Instance";           
    #LOG_SNS_FMV_MAG_UPDATE_C           => 0x1564;     
    $legends{oct("0x1564")}{"Original"} = "#packet_type,version,ts_type,ts_mag,ts_fmv,gyrox,gyroy,gyroz,bx,by,bz,fmv_x,fmv_y,fmv_z,accuracy,instance";           
    $legends{oct("0x1564")}{"New"} = "#Packet,Version,Timestamp Type,Mag Timestamp (ms),FMV Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Mag X (Gs),Mag Y (Gs),Mag Z (Gs),FMV X (Gs),FMV Y (Gs),FMV Z (Gs),Accuracy,Instance";           
    #LOG_SNS_FMV_GYRO_UPDATE_C          => 0x1565;     
    $legends{oct("0x1565")}{"Original"} = "#packet_type,version,ts_type,ts,gyroX,gyroY,gyroZ";           
    $legends{oct("0x1565")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Instance";           
    #LOG_SNS_FMV_REPORT_C               => 0x1566;     
    $legends{oct("0x1566")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,fmv_x,fmv_y,fmv_z,accuracy,instance";           
    $legends{oct("0x1566")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,FMV X (Gs),FMV Y (Gs),FMV Z (Gs),Accuracy,Instance";           
    #ISAGNAV_TS_PACKET                  => 0x150B; 
    $legends{oct("0x150B")}{"Original"} = "#packet_type,version,pe_InfoValid,pe_TTValid,pe_ComputeValid,q_TimeTickAtGpsTOA,w_GpsWeek,q_GpsMs,q_OurTxMs,q_TheirRxMs,q_TheirTxMs,q_OurRxMs,w_Rtt,gps_week_offset,gps_ms_in_week_offset";
    $legends{oct("0x150B")}{"New"} = "#Packet,Version,pe InfoValid,pe TTValid,pe ComputeValid,q TimeTickAtGpsTOA,w GpsWeek,q GpsMs,q OurTxMs,q TheirRxMs,q TheirTxMs,q OurRxMs,w Rtt,gps week offset,gps ms in week offset";
    #LOG_SNS_INTEG_ANGLE_CONFIG_C       => 0x159B; 
    $legends{oct("0x159B")}{"Original"} = "#packet_type,version,ts_type,ts,sample_rate,clip_threshold,instance";         
    $legends{oct("0x159B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Clip Threshold (deg),Instance";         
    #LOG_SNS_INTEG_ANGLE_RESULT_C       => 0x159C;   
    $legends{oct("0x159C")}{"Original"} = "#packet_type,version,ts_type,ts,g0,g1,g2,ia0,ia1,ia2,instance";           
    $legends{oct("0x159C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Integ Angle X (deg),Integ Angle Y (deg),Integ Angle Z (deg),Instance";           
    #LOG_SNS_INTEG_ANGLE_REPORT_C       => 0x159D; 
    $legends{oct("0x159D")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,ia0,ia1,ia2,instance";           
    $legends{oct("0x159D")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Integ Angle X (deg),Integ Angle Y (deg),Integ Angle Z (deg),Instance";           
    #LOG_SNS_GYRO_TAP_CONFIG_C          => 0x159E; 
    $legends{oct("0x159E")}{"Original"} = "#packet_type,version,ts_type,ts,sample_rate,tap_time_win,tap_time_sleep,tap_dir_win,accel_tap_thr,lr_accel_jerk_min_thresh_min,lr_gyro_jerk_min_thresh_min,tb_accel_jerk_min_thr,tb_gyro_jerk_min_thr,jerk_win,lr_accel_rat_jerk_yx,lr_accel_rat_jerk_yz,lr_gyro_rat_jerk_zy,lr_gyro_rat_jerk_zx,tb_accel_rat_jerk_xy,tb_accel_rat_jerk_xz,tb_gyro_rat_jerk_yx,tb_gyro_rat_jerk_yz,tb_accel_z_thresh,tb_accel_z_rat_zx,tb_accel_z_rat_zy,ori_change_win,ori_check_win,ori_change_thr,z_axis_inc,loaded_axis_3_valid,lr_min_accel_jerk_thresh_min,lr_max_accel_jerk_thresh_min,lr_min_gyro_jerk_thresh_min,lr_max_gyro_jerk_thresh_min,mild_accel_tap_thresh,loaded_z_axis_anamoly,ori_change_reject_mode,stress_right_left,instance";           
    $legends{oct("0x159E")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Tap Time Win,Tap Time Sleep,Tap Dir Win,Accel Tap Thr,lr Accel Jerk Min Thresh,lr Gyro Jerk Min Thresh,tb Accel Jerk Min Thr,tb Gyro Jerk Min Thr,Jerk Win,lr Accel Rat Jerk yx,lr Accel Rat Jerk yz,lr Gyro Rat Jerk zy,lr Gyro Rat Jerk zx,tb Accel Rat Jerk xy,tb Accel Rat Jerk xz,tb Gyro Rat Jerk yx,tb Gyro Rat Jerk yz,tb Accel A Thresh,tb Accel Z Rat zx,tb Accel Z Rat zy,Ori Change Win,Ori Check Win,Ori Change Thr,Z Axis Inc,Loaded Axis 3 Valid,lr Min Accel Jerk Thresh Min,lr Max Accel Jerk Tresh Min,lr Min Gyro Jerk Thresh Min,lr Max Gyro Jerk Thresh Min,Mild Accel Tap Thresh,Loaded Z Axis Anamoly,Ori Change Reject Mode,Stress Right Left,Instance";           
    #LOG_SNS_GYRO_TAP_RESULT_C          => 0x159F; 
    $legends{oct("0x159F")}{"Original"} = "#packet_type,version,ts_type,ts,g0,g1,g2,a0,a1,a2,tap_event,algo_state,instance";           
    $legends{oct("0x159F")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Tap Event,State,Instance";           
    #LOG_SNS_GYRO_TAP_REPORT_C          => 0x15A0; 
    $legends{oct("0x15A0")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,tap_event,instance";           
    $legends{oct("0x15A0")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Tap Event,Instance";           
    #LOG_SNS_BASIC_GESTURES_CONFIG_C    => 0x15A1; 
    $legends{oct("0x15A1")}{"Original"} = "#packet_type,version,ts_type,ts,sample_rate,sleep,push_thresh,pull_thresh,shake_thresh,config1,config2,config3,config4,instance";           
    $legends{oct("0x15A1")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Sleep,Push Threshold,Pull Threshold,Shake Threshold,Config Param1,Config Param2,Config Param3,Config Param4,Instance";           
    #LOG_SNS_BASIC_GESTURES_RESULT_C    => 0x15A2; 
    $legends{oct("0x15A2")}{"Original"} = "#packet_type,version,ts_type,ts,accel_x,accel_y,accel_z,motion_state,basic_state,instance";           
    $legends{oct("0x15A2")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Motion State,Basic State,Instance";           
    #LOG_SNS_BASIC_GESTURES_REPORT_C    => 0x15A3; 
    $legends{oct("0x15A3")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,basic_state,instance";           
    $legends{oct("0x15A3")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Basic State,Instance";           
    #LOG_SNS_FACING_CONFIG_C            => 0x15A4; 
    $legends{oct("0x15A4")}{"Original"} = "#packet_type,version,ts_type,ts,sample_rate,threshold,report_neutral,instance";           
    $legends{oct("0x15A4")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Facing Angle Threshold (deg),Report Neutral,Instance";           
    #LOG_SNS_FACING_RESULT_C            => 0x15A5; 
    $legends{oct("0x15A5")}{"Original"} = "#packet_type,version,ts_type,ts,accel_x,accel_y,accel_z,motion_state,facing_state,instance";           
    $legends{oct("0x15A5")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Motion State,Facing State,Instance";           
    #LOG_SNS_FACING_REPORT_C            => 0x15A6; 
    $legends{oct("0x15A6")}{"Original"} = "#packet_type,version,ts_type,ts,report_id,report_type,client_id,facing_state,instance";           
    $legends{oct("0x15A6")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Facing State,Instance";           
    #LOG_SNS_ACCEL_CAL_CONFIG_C         => 0x15B8;
    $legends{oct("0x15B8")}{"Original"} = "#packet_type,version,ts,sample_rate,instance";           
    $legends{oct("0x15B8")}{"New"} = "#Packet,Version,Timestamp (ms),Sample Rate (Hz),Instance";           
    #LOG_SNS_ACCEL_CAL_RESULT_C         => 0x15B9; 
    $legends{oct("0x15B9")}{"Original"} = "#packet_type,version,ts,accel_x,accel_y,accel_z,temp,accel_zero_bias_x,accel_zero_bias_y,accel_zero_bias_z,accel_scale_factor_x,accel_scale_factor_y,accel_scale_factor_z,instance";           
    $legends{oct("0x15B9")}{"New"} = "#Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Temperature (C),Zero Bias X (m/s/s),Zero Bias Y (m/s/s),Zero Bias Z (m/s/s),Scale Factor X,Scale Factor Y,Scale Factor Z,Instance";           
    #LOG_SNS_ACCEL_CAL_REPORT_C         => 0x15BA; 
    $legends{oct("0x15BA")}{"Original"} = "#packet_type,version,ts,accel_x,accel_y,accel_z,temp,accel_zero_bias_x,accel_zero_bias_y,accel_zero_bias_z,accel_scale_factor_x,accel_scale_factor_y,accel_scale_factor_z,cal_report_decision,temp_op_min,count_kf_update,covar_accel_x_bias,covar_accel_y_bias,covar_accel_z_bias,covar_accel_x_sf,covar_accel_y_sf,covar_accel_z_sf,kf_accel_x_bias,kf_accel_y_bias,kf_accel_z_bias,kf_accel_x_sf,kf_accel_y_sf,kf_accel_z_sf";
    $legends{oct("0x15BA")}{"New"} = "#Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Temperature (C),Zero Bias X (m/s/s),Zero Bias Y (m/s/s),Zero Bias Z (m/s/s),Scale Factor X,Scale Factor Y,Scale Factor Z,Report Decision,Operational Temperature Min (C),KF Update Counts,KF Covariance Bias X (mG^2),KF Covariance Bias Y (mG^2),KF Covariance Bias Z (mG^2),KF Covariance SF X (mG^2),KF Covariance SF Y (mG^2),KF Covariance SF Z (mG^2),KF Bias X Est (mG),KF Bias Y Est (mG),KF Bias Z Est (mG),KF SF X Est (mG),KF SF Y Est (mG),KF SF Z Est (mG)";
    #LOG_SNS_QMAG_CAL_CONFIG_C          => 0x163A
    $legends{oct("0x163A")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,sample_rate_mag,sample_rate_accel,cal_algo_type,cal_cycle_rate";
    $legends{oct("0x163A")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate Mag (Hz),Sample Rate Accel (Hz),Cal Algo Type,Cal Cycle Rate";
    #LOG_SNS_QMAG_CAL_RESULT_C          => 0x163B
    $legends{oct("0x163B")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,input_mag_x,input_mag_y,input_mag_z,input_accel_x,input_accel_y,input_accel_z,accel_input_variance,mag_input_variance,offset_hi_unfiltered_x,offset_hi_unfiltered_y,offset_hi_unfiltered_z,radius_hi,unfiltered_accuracy,accuracy_published,cal_algo_type,mag_zero_bias_published_x,mag_zero_bias_published_y,mag_zero_bias_published_z,offset_time,hard_reset,soft_reset";
    $legends{oct("0x163B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Input Mag X (G),Input Mag Y (G),Input Mag Z (G),Input Accel X (m/s/s),Input Accel Y (m/s/s),Input Accel Z (m/s/s),Accel Input Variance,Mag Input Variance,Offset HI Unfiltered X (G),Offset HI Unfiltered Y (G),Offset HI Unfiltered Z (G),Radius HI (G),Unfiltered Accuracy,Accuracy Published,Cal Algo Type,Mag Zero Bias Published X (G),Mag Zero Bias Published Y (G),Mag Zero Bias Published Z (G),Offset Time (ms),Hard Reset,Soft Reset";
    #LOG_SNS_QMAG_CAL_REPORT_C          => 0x163C
    $legends{oct("0x163C")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,qmag_x,qmag_y,qmag_z,qmag_zero_bias_corr_x,qmag_zero_bias_corr_y,qmag_zero_bias_corr_z";
    $legends{oct("0x163C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),QMAG X (G),QMAG Y (G),QMAG Z (G),QMAG X Zero Bias Correction (G),QMAG Y Zero Bias Correction (G),QMAG Z Zero Bias Correction (G)";
    #LOG_SNS_PED_CONFIG_C               => 0x1637;
    $legends{oct("0x1637")}{"Original"} = "#packet_type,version,ts,sample_rate,step_count_threshold,step_threshold,swing_threshold,step_prob_threshold,instance";
    $legends{oct("0x1637")}{"New"} = "#Packet,Version,Timestamp (ms),Sample Rate (Hz),Step Count Threshold (steps),Step Threshold (m/s/s),Swing Threshold (m/s/s),Step Probability Threshold (%),Instance";
    #LOG_SNS_PED_RESULT_C               => 0x1638;
    $legends{oct("0x1638")}{"Original"} = "#packet_type,version,ts,accel_x,accel_y,accel_z,sample_rate,client_id,reset_stats,step_event,step_confidence,step_count,step_count_error,swing_step_count,step_rate,instance";           
    $legends{oct("0x1638")}{"New"} = "#Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Sample Rate (Hz),Client ID,Reset Stats,Step Event,Step Confidence (%),Step Count (steps),Step Count Error (steps),Swing Step Count (steps),Step Rate (steps/s),Instance";           
    #LOG_SNS_PED_REPORT_C               => 0x1639;
    $legends{oct("0x1639")}{"Original"} = "#packet_type,version,ts,report_id,report_type,client_id,step_event,step_confidence,step_count,step_count_error,step_rate,instance";           
    $legends{oct("0x1639")}{"New"} = "#Packet,Version,Timestamp (ms),Report ID,Report Type,Client ID,Step Event,Step Confidence (%),Step Count (steps),Step Count Error (steps),Step Rate (steps/s),Instance";           
    #LOG_SNS_PAM_CONFIG_C               => 0x1640;
    $legends{oct("0x1640")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,measurement_period,step_count_threshold,sample_rate,duty_cycle_on_percent,instance";           
    $legends{oct("0x1640")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Measurement Period (s),Step Count Threshold (steps),Sample Rate (Hz),Duty Cycle On (%),Instance";           
    #LOG_SNS_PAM_RESULT_C               => 0x1641;
    $legends{oct("0x1641")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,pedometer_step_count,motion_state,data_type,pedometer_last_step_count,pam_current_step_count,pam_last_reported_step_count,pam_report_decision,instance";           
    $legends{oct("0x1641")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Pedometer Step Count (steps),Motion State,Data Type,Pedometer Last Step Count (steps),PAM Current Step Count (steps),PAM Last Reported Step Count (steps),PAM Report Decision,Instance";           
    #LOG_SNS_PAM_REPORT_C               => 0x1642;
    $legends{oct("0x1642")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,step_count,instance";           
    $legends{oct("0x1642")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),State,Step Count (steps),Instance";           
    #LOG_SNS_CMC_CONFIG_C               => 0x17EA;
    $legends{oct("0x17EA")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,Unknown Legend for LOG_SNS_CMC_CONFIG_C => 0x17EA";           
    $legends{oct("0x17EA")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Unknown Legend for LOG_SNS_CMC_CONFIG_C => 0x17EA";           
    #LOG_SNS_CMC_RESULT_C               => 0x17EB;
        #Version 1: $legends{oct("0x17EB")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,sample_count,accel_prevX,accel_prevY,accel_prevZ,accel_sumX,accel_sumY,accel_sumZ,accel_norm_sum,accel_norm_sq_sum,algo_inst_id";           
        #Version 1: $legends{oct("0x17EB")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Sample Count,Accel Prev X (m/s/s),Accel Prev Y (m/s/s),Accel Prev Z (m/s/s),Accel Sum X (m/s/s),Accel Sum Y (m/s/s),Accel Sum Z (m/s/s),Accel Norm Sum,Accel Norm Sq Sum,Instance";
    $legends{oct("0x17EB")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,qmd_motion_state,update_reporting_motion_state,update_reporting_event_type,algo_inst_id";
    $legends{oct("0x17EB")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),QMD Motion State,Update Reporting Motion State,Update Reporting Event Type,Instance";
    #LOG_SNS_CMC_REPORT_C               => 0x17EC;
        #Version 1: $legends{oct("0x17EC")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,motion_state,motion_state_probability,algo_inst_id";           
        #Version 1: $legends{oct("0x17EC")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Motion State,Motion State Probability,Instance";           
    $legends{oct("0x17EC")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,motion_state,motion_state_event,motion_state_probability,algo_inst_id";           
    $legends{oct("0x17EC")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Motion State,Motion State Event,Motion State Probability (%),Instance";           
    #LOG_SNS_DB_CONFIG_C                => 0x17ED;
        #Version 1: $legends{oct("0x17ED")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,client_req_id,ms_unknown_speedbound,ms_stationary_speedbound,ms_inmotion_speedbound,ms_fiddle_speedbound,ms_pedestrian_speedbound,ms_vehicle_speedbound,ms_walk_speedbound,ms_run_speedbound,algo_inst_id";           
        #Version 1: $legends{oct("0x17ED")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Client ID,Unknown Speedbound,Stationary Speedbound,Inmotion Speedbound,Fiddle Speedbound,Pedestrian Speedbound,Vehicle Speedbound,Walk Speedbound,Run Speedbound,Instance";
    $legends{oct("0x17ED")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,client_req_id,ms_unknown_speedbound,ms_stationary_speedbound,ms_inmotion_speedbound,ms_fiddle_speedbound,ms_pedestrian_speedbound,ms_vehicle_speedbound,ms_walk_speedbound,ms_run_speedbound,ms_bike_speedbound,algo_inst_id";           
    $legends{oct("0x17ED")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Client ID,Unknown Speedbound,Stationary Speedbound,Inmotion Speedbound,Fiddle Speedbound,Pedestrian Speedbound,Vehicle Speedbound,Walk Speedbound,Run Speedbound,Bike Speedbound,Instance";
    #LOG_SNS_DB_RESULT_C                => 0x17EE;
        #Version 1: $legends{oct("0x17EE")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,input_distance_bound,input_cmc_motion_state,algo_state,prev_timestamp,prev_speed,prev_distance_bound,time_to_breach,session_key,algo_inst_id";           
        #Version 1: $legends{oct("0x17EE")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Input Distance Bound,Input CMC Motion State,Algorithm State,Previous Timestamp (ms),Previous Speed,Previous Distance Bound,Time to Breach,Session Key,Instance";
    $legends{oct("0x17EE")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,input_distance_bound,input_cmc_motion_state,input_cmc_motion_event,algo_state,prev_timestamp,prev_speed,prev_distance_bound,time_to_breach,session_key,algo_inst_id";
    $legends{oct("0x17EE")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Input Distance Bound,Input CMC Motion State,Input CMC Motion Event,Algorithm State,Previous Timestamp (ms),Previous Speed,Previous Distance Bound,Time to Breach,Session Key,Instance";
    #LOG_SNS_DB_REPORT_C                => 0x17EF;
    $legends{oct("0x17EF")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,distance_bound_breach_event,session_key,algo_inst_id";
    $legends{oct("0x17EF")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Distance Bound Breach Event,Session Key,Instance";           
    #LOG_SNS_CMC_RESULT2_C              => 0x17F0;
        #Version 1: $legends{oct("0x17F0")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,sa,rm,unfilp0,unfilp1,unfilp2,unfilp3,unfilp4,alpha0,alpha1,alpha2,alpha3,alpha4,beta0,beta1,beta2,beta3,beta4,filprob0,filprob1,filprob2,filprob3,filprob4,filprob5,filprob6,filprob7,motion_state_curr,motion_state_prev,motion_state_persist_time,motion_state_curr_probability,algo_inst_id";           
        #Version 1: $legends{oct("0x17F0")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),SA,RM,unfilp0,unfilp1,unfilp2,unfilp3,unfilp4,alpha0,alpha1,alpha2,alpha3,alpha4,beta0,beta1,beta2,beta3,beta4,filprob0,filprob1,filprob2,filprob3,filprob4,filprob5,filprob6,filprob7,Current Motion State,Previous Motion State,Motion State Persist Time (s),Motion State Probability,Instance";
    $legends{oct("0x17F0")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,IQR,MODRM,MM3,DIFFSUM,DIFF10P,SA,SADIFF,LINACC[1],LINACC[2],LINACC[3],LINACCDIFF[1],LINACCDIFF[2],LINACCDIFF[3],SE 0 2 B[1],SE 0 2 B[2],SE 0 2 B[3],SE 2 4 B[1],SE 2 4 B[2],SE 2 4 B[3],SE 5 10 B[1],SE 5 10 B[2],SE 5 10 B[3],HIGHPEAKMAG B[1],HIGHPEAKMAG B[2],HIGHPEAKMAG B[3],HIGHPEAKLOC B[1],HIGHPEAKLOC B[2],HIGHPEAKLOC B[3],SPECENT B[1],SPECENT B[2],SPECENT B[3],MEANCROSSINGS B[1],MEANCROSSINGS B[2],MEANCROSSINGS B[3],GMM PROBABILITY[Walk],GMM PROBABILITY[Run],GMM PROBABILITY[Stationary],GMM PROBABILITY[Vehicle],GMM PROBABILITY[Bike],LR STAT DRIVE PROBABILITY[Stationary],LR STAT DRIVE PROBABILITY[Vehicle],LR WALK BIKE PROBABILITY[Walk],LR WALK BIKE PROBABILITY[Run],UNFILT GMM PROBABILITY[Walk],UNFILT GMM PROBABILITY[Run],UNFILT GMM PROBABILITY[Stationary],UNFILT GMM PROBABILITY[Vehicle],UNFILT GMM PROBABILITY[Bike],FILTERED PROBABILITY[Walk],FILTERED PROBABILITY[Run],FILTERED PROBABILITY[Stationary],FILTERED PROBABILITY[Vehicle],FILTERED PROBABILITY[Bike],HYST STABLE STATE,HYST TRANSITION STATE,HYST IS TRANSITION,HYST TRANSITION COUNT,EVENT REPORT TYPES[Walk],EVENT REPORT TYPES[Run],EVENT REPORT TYPES[Stationary],EVENT REPORT TYPES[Vehicle],EVENT REPORT TYPES[Bike],EVENT REPORT TYPES[Unknown],MOTION STATE EVENT[Walk],MOTION STATE EVENT[Run],MOTION STATE EVENT[Stationary],MOTION STATE EVENT[Vehicle],MOTION STATE EVENT[Bike],MOTION STATE EVENT[Unknown],MOTION STATE TIMESTAMP[Walk],MOTION STATE TIMESTAMP[Run],MOTION STATE TIMESTAMP[Stationary],MOTION STATE TIMESTAMP[Vehicle],MOTION STATE TIMESTAMP[Bike],MOTION STATE TIMESTAMP[Unknown],MOTION STATE PROBABILITY[Walk],MOTION STATE PROBABILITY[Run],MOTION STATE PROBABILITY[Stationary],MOTION STATE PROBABILITY[Vehicle],MOTION STATE PROBABILITY[Bike],MOTION STATE PROBABILITY[Unknown],OUTPUT MOTION STATE EVENT[Walk],OUTPUT MOTION STATE EVENT[Run],OUTPUT MOTION STATE EVENT[Stationary],OUTPUT MOTION STATE EVENT[Vehicle],OUTPUT MOTION STATE EVENT[Bike],OUTPUT MOTION STATE EVENT[Unknown],OUTPUT MOTION STATE TIMESTAMP[Walk],OUTPUT MOTION STATE TIMESTAMP[Run],OUTPUT MOTION STATE TIMESTAMP[Stationary],OUTPUT MOTION STATE TIMESTAMP[Vehicle],OUTPUT MOTION STATE TIMESTAMP[Bike],OUTPUT MOTION STATE TIMESTAMP[Unknown],OUTPUT MOTION STATE PROBABILITY[Walk],OUTPUT MOTION STATE PROBABILITY[Run],OUTPUT MOTION STATE PROBABILITY[Stationary],OUTPUT MOTION STATE PROBABILITY[Vehicle],OUTPUT MOTION STATE PROBABILITY[Bike],OUTPUT MOTION STATE PROBABILITY[Unknown],Instance";
    $legends{oct("0x17F0")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),IQR,MODRM,MM3,DIFFSUM,DIFF10P,SA,SADIFF,LINACC[1],LINACC[2],LINACC[3],LINACCDIFF[1],LINACCDIFF[2],LINACCDIFF[3],SE 0 2 B[1],SE 0 2 B[2],SE 0 2 B[3],SE 2 4 B[1],SE 2 4 B[2],SE 2 4 B[3],SE 5 10 B[1],SE 5 10 B[2],SE 5 10 B[3],HIGHPEAKMAG B[1],HIGHPEAKMAG B[2],HIGHPEAKMAG B[3],HIGHPEAKLOC B[1],HIGHPEAKLOC B[2],HIGHPEAKLOC B[3],SPECENT B[1],SPECENT B[2],SPECENT B[3],MEANCROSSINGS B[1],MEANCROSSINGS B[2],MEANCROSSINGS B[3],GMM PROBABILITY[Walk],GMM PROBABILITY[Run],GMM PROBABILITY[Stationary],GMM PROBABILITY[Vehicle],GMM PROBABILITY[Bike],LR STAT DRIVE PROBABILITY[Stationary],LR STAT DRIVE PROBABILITY[Vehicle],LR WALK BIKE PROBABILITY[Walk],LR WALK BIKE PROBABILITY[Run],UNFILT GMM PROBABILITY[Walk],UNFILT GMM PROBABILITY[Run],UNFILT GMM PROBABILITY[Stationary],UNFILT GMM PROBABILITY[Vehicle],UNFILT GMM PROBABILITY[Bike],FILTERED PROBABILITY[Walk],FILTERED PROBABILITY[Run],FILTERED PROBABILITY[Stationary],FILTERED PROBABILITY[Vehicle],FILTERED PROBABILITY[Bike],HYST STABLE STATE,HYST TRANSITION STATE,HYST IS TRANSITION,HYST TRANSITION COUNT,EVENT REPORT TYPES[Walk],EVENT REPORT TYPES[Run],EVENT REPORT TYPES[Stationary],EVENT REPORT TYPES[Vehicle],EVENT REPORT TYPES[Bike],EVENT REPORT TYPES[Unknown],MOTION STATE EVENT[Walk],MOTION STATE EVENT[Run],MOTION STATE EVENT[Stationary],MOTION STATE EVENT[Vehicle],MOTION STATE EVENT[Bike],MOTION STATE EVENT[Unknown],MOTION STATE TIMESTAMP[Walk] (ms),MOTION STATE TIMESTAMP[Run] (ms),MOTION STATE TIMESTAMP[Stationary] (ms),MOTION STATE TIMESTAMP[Vehicle] (ms),MOTION STATE TIMESTAMP[Bike] (ms),MOTION STATE TIMESTAMP[Unknown] (ms),MOTION STATE PROBABILITY[Walk] (%),MOTION STATE PROBABILITY[Run] (%),MOTION STATE PROBABILITY[Stationary] (%),MOTION STATE PROBABILITY[Vehicle] (%),MOTION STATE PROBABILITY[Bike] (%),MOTION STATE PROBABILITY[Unknown] (%),OUTPUT MOTION STATE EVENT[Walk],OUTPUT MOTION STATE EVENT[Run],OUTPUT MOTION STATE EVENT[Stationary],OUTPUT MOTION STATE EVENT[Vehicle],OUTPUT MOTION STATE EVENT[Bike],OUTPUT MOTION STATE EVENT[Unknown],OUTPUT MOTION STATE TIMESTAMP[Walk] (ms),OUTPUT MOTION STATE TIMESTAMP[Run] (ms),OUTPUT MOTION STATE TIMESTAMP[Stationary] (ms),OUTPUT MOTION STATE TIMESTAMP[Vehicle] (ms),OUTPUT MOTION STATE TIMESTAMP[Bike] (ms),OUTPUT MOTION STATE TIMESTAMP[Unknown] (ms),OUTPUT MOTION STATE PROBABILITY[Walk] (%),OUTPUT MOTION STATE PROBABILITY[Run] (%),OUTPUT MOTION STATE PROBABILITY[Stationary] (%),OUTPUT MOTION STATE PROBABILITY[Vehicle] (%),OUTPUT MOTION STATE PROBABILITY[Bike] (%),OUTPUT MOTION STATE PROBABILITY[Unknown] (%),Instance";
    #LOG_SENSOR_FIFO_EVENT_C            => 0x17F3;
    $legends{oct("0x17F3")}{"Original"} = "#packet_type,version,timestamp,sensor_id,fifo_event,watermark_depth,odr,hw_watermark_int_supported,max_watermark";           
    $legends{oct("0x17F3")}{"New"} = "#Packet,Version,Timestamp (ms),Sensor ID,FIFO Event,Watermark Depth (samples),ODR,HW Watermark INT Supported,Max Watermark (samples)";           
    #LOG_SNS_SMD_CONFIG_C               => 0x17F8;
    $legends{oct("0x17F8")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,sample_rate,accel_window_time,detect_threshold,self_transition_prob_nm,variable_latency_flag,max_latency,algo_inst_id";           
    $legends{oct("0x17F8")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Accel Window Time,Detect Threshold,Self Transition Prob nm,Variable Latency Flag,Max Latency,Instance";           
    #LOG_SNS_SMD_RESULT_C               => 0x17F9;
    $legends{oct("0x17F9")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,ax,ay,az,sample_cnt,variance,eigenvaluesx,eigenvaluesy,eigenvaluesz,xcor,spread_mag,rm,sa,pstate0,pstate1,filter_delay_cnt,filter_delay_time,motion_state,final_motion_state,algo_inst_id";           
    $legends{oct("0x17F9")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Sample Count,Variance,Eigenvalues X,Eigenvalues Y,Eigenvalues Z,Auto Correlation,Spread Magnitue,RM Ratio Feature,SA Feature,pstate0,pstate1,Filter Delay Count,Filter Delay Time (s),Motion State,Final Motion State,Instance";           
    #LOG_SNS_SMD_REPORT_C               => 0x17FA;
    $legends{oct("0x17FA")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,motion_state,motion_state_probability,algo_inst_id";           
    $legends{oct("0x17FA")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Motion State,Motion State Probability (%),Instance";           
    #LOG_SNS_LATENCY_SAMPLING_POLL_C    => 0x17FB;
    $legends{oct("0x17FB")}{"Original"} = "#packet_type,version,timestamp,sensor_id,data_timestamp,sampling_latency,polling_latency";
    $legends{oct("0x17FB")}{"New"} = "#Packet,Version,Timestamp (ms),Sensor ID,Data Timestamp (ms),Sampling Latency (ms),Polling Latency (ms)";
    #LOG_SNS_LATENCY_SAMPLING_DRI_C     => 0x17FC;
    $legends{oct("0x17FC")}{"Original"} = "#packet_type,version,timestamp,sensor_id,data_timestamp,sampling_latency,dri_get_data_latency";
    $legends{oct("0x17FC")}{"New"} = "#Packet,Version,Timestamp (ms),Sensor ID,Data Timestamp (ms),Sampling Latency (ms),DRI Get Data Latency (ms)";
    #LOG_SNS_LATENCY_DELIVERY_C         => 0x17FD;
    $legends{oct("0x17FD")}{"Original"} = "#packet_type,version,timestamp,sensor_id,data_timestamp,delivery_latency";
    $legends{oct("0x17FD")}{"New"} = "#Packet,Version,Timestamp (ms),Sensor ID,Data Timestamp (ms),Delivery Latency (ms)";
    #LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C   => 0x17FE;
    $legends{oct("0x17FE")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_period,sample_rate,coordinate_sys,abs_rest_gyro_az_tilt_tc,rel_rest_gyro_az_tilt_tc,motion_gyro_az_tilt_tc,gyro_noise_threshold,max_gyro_az_tilt_freeze,max_gyro_az_tilt_reset,algo_inst_id";
    $legends{oct("0x17FE")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Coordinate System,Abs Rest Gyro AZ Tilt,Rel Rest Gyro AZ Tilt,Motion Gyro AZ Tilt,Gyro Noise Threshold,Max Gyro AZ Tilt Freeze,Max Gyro AZ Tilt Reset,Instance";
    #LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C   => 0x17FF;
    $legends{oct("0x17FF")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,grav_x,grav_y,grav_z,gravity_accuracy,gravity_timestamp,gravity_dev_mot_state,gyro_quat0,gyro_quat1,gyro_quat2,gyro_quat3,gyro_quat_timestamp,grv0,grv1,grv2,grv3,accuracy,coordinate_sys,algo_inst_id";
    $legends{oct("0x17FF")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Gravity Accuracy,Gravity Timestamp (ms),Gravity Motion State,Quat0,Quat1,Quat2,Quat3,Quat Timestamp (ms),GRV0,GRV1,GRV2,GRV3,Accuracy,Coordinate System,Instance";
    #LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C   => 0x1800;
    $legends{oct("0x1800")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,grv0,grv1,grv2,grv3,accuracy,coordinate_sys,algo_inst_id";
    $legends{oct("0x1800")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,GRV0,GRV1,GRV2,GRV3,Accuracy,Coordinate System,Instance";
    #LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C    => 0x183A;
    $legends{oct("0x183A")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_period,sample_rate,accel_filter_tc,mag_filter_tc,motion_detect_period,abs_rest_var_thresh,coord_sys,instance";
    $legends{oct("0x183A")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Accel Filter Time Const (ms),Mag Filter Time Const (ms),Motion Detect Period (s),Abs Rest Variance Threshold (m/s/s)^2,Coordinate System,Instance";
    #LOG_SNS_GEOMAG_ROT_VEC_RESULT_C    => 0x183B;
    $legends{oct("0x183B")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,accel_x,accel_y,accel_z,gravity_x,gravity_y,gravity_z,lin_accel_x,lin_accel_y,lin_accel_z,gravity_accuracy,gravity_timestamp,fmv_x,fmv_y,fmv_z,fmv_accuracy,fmv_timestamp,rotva,rotvb,rotvc,rotvd,rotv_accuracy,coord_sys,instance";
    $legends{oct("0x183B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),Gravity Accuracy,Gravity Timestamp (ms),FMV X (Gs),FMV Y (Gs),FMV Z (Gs),FMV Accuracy,FMV Timestamp (ms),RotV0,RotV1,RotV2,RotV3,RotV Accuracy,Coordinate System,Instance";  
    #LOG_SNS_GEOMAG_ROT_VEC_REPORT_C    => 0x183C;
    $legends{oct("0x183C")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,rotva,rotvb,rotvc,rotvd,gravity_x,gravity_y,gravity_z,lin_accel_x,lin_accel_y,lin_accel_z,rotv_accuracy,gravity_accuracy,coord_sys,instance";
    $legends{oct("0x183C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,RotV0,RotV1,RotV2,RotV3,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),RotV Accuracy,Gravity Accuracy,Coordinate System,Instance";
    #LOG_SNS_PED_ALIGN_CONFIG_C       => 0x186C;
    $legends{oct("0x186C")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,rv_input,cog_sample_rate,rv_sample_rate,sensor_report_rate,cog_averaging_interval,instance";
    $legends{oct("0x186C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),RotV Input,Course-over-Ground (COG) Sample Rate (Hz),RotV Sample Rate (Hz),Sensor Repot Rate (Hz),Course-over-Ground (COG) Averaging Interval (Steps),Instance";
    #LOG_SNS_PED_ALIGN_RESULT1_C      => 0x186D;
    $legends{oct("0x186D")}{"Original"} = "#packet_type,version,input_type,timestamp,accel_x,accel_y,accel_z,rotva,rotvb,rotvc,rotvd,rv_accuracy,instance";
    $legends{oct("0x186D")}{"New"} = "#Packet,Version,Input Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),RotV0,RotV1,RotV2,RotV3,RotV Accuracy,Instance";
    #LOG_SNS_PED_ALIGN_RESULT2_C      => 0x186E;
    $legends{oct("0x186E")}{"Original"} = "#packet_type,version,timestamp,unfiltered_cog_angle,cog_angle,cog_accuracy,relative_turn_angle,last_alignment_change_ts,events,instance,rta_accuracy";
    $legends{oct("0x186E")}{"New"} = "#Packet,Version,Timestamp (ms),Unfiltered CoG Angle (Deg),CoG Angle (Deg),CoG Accuracy (Deg),Relative Turn Angle (Deg),Last Alignment Change Timestamp (ms),Events,Instance,RTA Accuracy (Deg)";    
    #LOG_SNS_PED_ALIGN_REPORT_C       => 0x186F;
    $legends{oct("0x186F")}{"Original"} = "#packet_type,version,timestamp,instance,client_id,report_id,cog_angle,cog_accuracy,relative_turn_angle,last_alignment_change_ts,events,rta_accuracy";
    $legends{oct("0x186F")}{"New"} = "#Packet,Version,Timestamp (ms),Instance,Client ID,Report ID,CoG Angle (Deg),CoG Accuracy (Deg),Relative Turn Angle (Deg),Last Alignment Change Timestamp (ms),Events,RTA Accuracy (Deg)";
    #LOG_SNS_TILT_DETECTOR_CONFIG_C
    $legends{oct("0x1887")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,sample_rate,angle_threshold,init_accel_window_time,accel_window_time,instance";
    $legends{oct("0x1887")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Angle Threshold (Deg),Initial Accel Window Time (s),Current Accel Window Time (s),Instance";
    #LOG_SNS_TILT_DETECTOR_RESULT_C
    $legends{oct("0x1888")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,accel_x,accel_y,accel_z,accel_timestamp,dprod_threshold,gravity_x,gravity_y,gravity_z,instance";
    $legends{oct("0x1888")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Accel Timestamp (ms),Dot-Product Threshold,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Instance";
    #LOG_SNS_TILT_DETECTOR_REPORT_C
    $legends{oct("0x1889")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,event_timestamp,ref_gravity_x,ref_gravity_y,ref_gravity_z,instance";
    $legends{oct("0x1889")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Event Timestamp (ms),New Reference Gravity X (m/s/s),New Reference Gravity Y (m/s/s),New Reference Gravity Z (m/s/s),Instance";
    #LOG_SNS_UIMAGE
    $legends{oct("0x188D")}{"Original"} = "#packet_type,version,client_vote,state_vote_ts,bigimage_entry_ts,last_uimg_vote_ts,first_uimg_entry_ts,time_spent_in_uimg,num_exits_from_uimg";
    $legends{oct("0x188D")}{"New"} = "#Packet,Version,Client Vote,State Vote Timestamp (ms),Big Image Entry Timestamp (ms),Last uImage Vote Timestamp (ms),First uImage Entry Timestamp (ms),Time Spent in uImage (ms),Number of Exits from uImage,System Vote,Client 0 Vote (Utils?),Client 1 Vote (SMGR?),Client 2 Vote (RH?),Client 3 Vote (SAM?),uImage Entry Latency (ms)";
    #LOG_SNS_DPC_CONFIG_C
        #Version 1: $legends{oct("0x189B")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,accel_sample_rate,proximity_sample_rate,sensor_report_rate,algo_inst_id";
        #Version 1: $legends{oct("0x189B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel Sample Rate (Hz),Proximity Sample Rate (Hz),Sensor Sample Rate (Hz),Instance";
    $legends{oct("0x189B")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,accel_sample_rate,proximity_sample_rate,mdIntAvailable,suppress_samps,hidden_hidden_hyst_time,angle_static_alpha,proximity_check_window_length,tiltparams_pickup_margin,tiltparams_pickup_min,tiltparams_stable_t,max_tilt_facing_sep,face_position_detection_tau";
    $legends{oct("0x189B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Accel Sample Rate (Hz),Proximity Sample Rate (Hz),Motion Detect Interrupt Available,Suppress Samples (# of samples),Hidden Hidden Hyst Time (# of samples),Angle Static Alpha,Proximity Check Window Length (# of samples),Tiltparams Pickup Margin,Tiltparams Pickup Min,Tiltparams Stable t,Max Tilt Facing Sep (# of samples),Face Position Detection Tau";
    #LOG_SNS_DPC_RESULT_C
        #Version 1: $legends{oct("0x189C")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,proximity,device_position,desk_entry_detector_op_state,desk_entry_detector_state,desk_entry_detector_on_desk_entry_time,desk_entry_detector_unknown_entry_time,desk_exit_detector_op_state,pocket_entry_detector_op_state,pocket_entry_detector_state,pocket_entry_detector_in_pocket_entry_time,pocket_entry_detector_unknown_entry_time,pocket_entry_detector_prev_proximity,pocket_exit_detector_op_state,pocket_exit_detector_state,pocket_exit_detector_prev_proximity,pocket_exit_detector_prox_near_to_far_trans_time,pocket_exit_detector_unknown_entry_time,algo_inst_id";
        #Version 1: $legends{oct("0x189C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Proximity,Device Position,Desk Entry Detector Op State,Desk Entry Detector State,Desk Entry Detector on Desk Entry Time,Desk Entry Detector Unknown Entry Time,Desk Exit Detector Op State,Pocket Entry Detector Op State,Pocket Entry Detector State,Pocket Entry Detector in Pocket Entry Time,Pocket Entry Detector Unknown Entry Time,Pocket Entry Detector Prev Proximity,Pocket Exit Detector Op State,Pocket Exit Detector State,Pocket Exit Detector Prev Proximity,Pocket Exit Detector Prox Near to Far Trans Time,Pocket Exit Detector Unknown Entry Time,Instance";
    $legends{oct("0x189C")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,proximity,amd_motion_status,device_position,device_position_timestamp,face_position,face_position_timestamp,tilt,tilt_timestamp,tilt_suppress_ctr,proximity_last_go_far_time,proximity_last_go_near_time,accelStatus,dpc_output,dpc_output_timestamp,prox_state,dpc_ready,tilt_last_go_one_timestamp,facing_algo_last_go_one_timestamp,hidden_last_seen_timestamp,compute_on_this_samp,is_stable,buff_idx,samp_count,dpc_event_generated,motion_status,static_angle_count,stream_period,flat_static_flag,proxStatus,algo_inst_id";
    $legends{oct("0x189C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Proximity,AMD State,Device Position,Device Position Timestamp (ms),Face Position,Face Position Timestamp (ms),Tilt,Tilt Timestamp (ms),Tilt Suppress Ctr,Proximity Last Go Far Time (ms),Proximity Last Go Near Time (ms),Accel Status,DPC Output,DPC Output Timestamp (ms),Proximity State,DPC Ready,Tilt Last Go One Timestamp (ms),Facing Algo Last Go One Timestamp (ms),Hidden Last Seen Timestamp (ms),Compute on this Sample,Is Stable,Buff idx,Sample Count,DPC Event Generated,Motion Status,Static Angle Count,Stream Period,Flat Static Flag,Proximity Status,Instance";
    #LOG_SNS_DPC_REPORT_C
        #Version 1: $legends{oct("0x189D")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,dpc_event,algo_inst_id";
        #Version 1: $legends{oct("0x189D")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),DPC Event,Instance";
    $legends{oct("0x189D")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,dpc_event,algo_inst_id";
    $legends{oct("0x189D")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),DPC Event,Instance";
    #LOG_SNS_TILT_W_DETECTOR_CONFIG_C
    $legends{oct("0x18B7")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,sample_rate,filter_window_seconds,accel_window_seconds,window_for_end_accel_stability_check_seconds,min_delta_pitch_threshold_deg,min_end_pitch_threshold_deg,max_end_roll_threshold_deg,max_end_accel_spread_threshold,max_end_accel_norm_deviation_from_g_threshold,adaptive_filter_tc_seconds,tilt_threshold_motion_noise_coeff,algo_inst_id";
    $legends{oct("0x18B7")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Filter Window (s,Accel Window (s),Window for End Accel Stability Check (s),Min Delta Pitch Threshold (deg),Min End Pitch Threshold (deg),Max End Roll Threshold (deg),Max End Accel Spread Threshold,Max End Accel Norm Deviation from g Threshold,Adaptive Filter TC (s),Tilt Threshold Motion Noise Coeff,Instance";
    #LOG_SNS_TILT_W_DETECTOR_RESULT_C
    $legends{oct("0x18B8")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,amd_state,input_ts,event_ts,delta_acc_squared_filtered,cur_roll_in_range,cur_pitch_in_range,cur_accel_norm_in_range,cur_pos_is_stable,is_sufficient_tilt,algo_inst_id";
    $legends{oct("0x18B8")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),AMD State,Input Timestamp (ms),Event Timestamp (ms),Delta ACC Squared Filtered,Cur Roll in Range,Cur Pitch in Range,Cur Accel Norm in Range,Cur Pos is Stable,Is Sufficient Tilt,Instance";
    #LOG_SNS_TILT_W_DETECTOR_REPORT_C
    $legends{oct("0x18B9")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,event_timestamp,accelX,accelY,accelZ,algo_inst_id";
    $legends{oct("0x18B9")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Event Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Instance";
    #LOG_SNS_QHEART_CONFIG_C
    $legends{oct("0x18BA")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,sample_rate_ppg,sample_rate_accel,update_interval_in_fft_samples,max_alpha,min_alpha,min_oh,max_oh,max_del_b,acc_peak_distance,ppg_peak_distance,num_ppg_peaks,num_acc_peaks,peak_width_ppg,peak_thresh_ppg,peak_thresh_acc,max_ind_diff,max_acc_thr,harm_acc_thr,globalminhr,globalmaxhr,noaccel_thresh,accuracy_decay_alpha,android_accuracy_low_thresh,android_accuracy_high_thresh,android_accuracy_medium_thresh,do_minppg,do_mingoodppgtrack,do_width_harm,do_stride_is_hr_processing,is_one_shot,report_interval,algo_inst_id";
    $legends{oct("0x18BA")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate PPG (Hz),Sample Rate Accel (Hz),Update Interval in FFT Samples,Max Alpha,Min Alpha,Min OH,Max OH,Max Del B,Acc Peak Distance,PPG Peak Distance,Num PPG Peaks,Num Acc Peaks,Peak Width PPG,Peak Thresh PPG,Peak Thresh Acc,Max Ind Diff,Max Acc Thr,Harm Acc Thr,Globalminhr,Globalmaxhr,NoAccel Thresh,Accuracy Decay Alpha,Android Accuracy Low Thresh,Android Accuracy High Thresh,Android Accuracy Medium Thresh,Do Minppg,Do Mingoodppgtrack,Do Width Harm,Do Stride is HR Processing,Is One Shot,Report Interval,Instance";
    #LOG_SNS_QHEART_RESULT_C
    $legends{oct("0x18BB")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,input_type,sensor_data0,sensor_data1,sensor_data2,sensor_time,bpm,bpm_time,bpm_updated,bpm_quality,num_found_ppg_peaks,num_found_acc_peaks,prior_smooth_bpm,prior_smooth_harmppg,harmacc,harmpow,acc_pow_fft,locspeak,harmppg,smooth_harmppg,harmppg_save,raw_bpm,smooth_bpm,state_bpm_quality,algo_inst_id";
    $legends{oct("0x18BB")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Sensor Data X,Sensor Data Y, Sensor Data Z,Sensor Timestamp (ms),BPM,BPM Timestamp (ms),BPM Updated,BPM Quality,Num Found PPG Peaks,Num Found Acc Peaks,Prior Smooth BPM,Prior Smooth Harmppg,Harmacc,Harmpow,Acc Pow FFT,Locspeak,Harmppg,Smooth Harmppg,Harmppg Save,Raw BPM,Smooth BPM,State BPM Quality,Instance";
    #LOG_SNS_QHEART_REPORT_C
    $legends{oct("0x18BC")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,bpm,bpm_time,bpm_updated,bpm_quality,algo_inst_id";
    $legends{oct("0x18BC")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,BPM,BPM Timestamp (ms),BPM Updated,BPM Quality,Instance";
    #LOG_SNS_SYNC_PROXY_CLIENT_C",
    $legends{oct("0x18C2")}{"Original"} = "#packet_type,version,qtimer_freq,req_num_sync_schedules,supported_num_sync_schedules,schedule1_time,schedule1_interval,schedule2_time,schedule2_interval,schedule3_time,schedule3_interval,schedule4_time,schedule4_interval,schedule5_time,schedule5_interval,schedule6_time,schedule6_interval,schedule7_time,schedule7_interval,schedule8_time,schedule8_interval,schedule9_time,schedule9_interval,schedule10_time,schedule10_interval,req_rest_to_motion_latency,req_motion_to_rest_latency,client_time,client_state,motion_state_time,motion_state";
    $legends{oct("0x18C2")}{"New"} = "#Packet,Version,QTimer Frequency (Hz),Request Num Sync Schedules,Supported Num Sync Schedules,Schedule 1 Wakeup (s),Schedule 1 Interval (s),Schedule 2 Wakeup (s),Schedule 2 Interval (s),Schedule 3 Wakeup (s),Schedule 3 Interval (s),Schedule 4 Wakeup (s),Schedule 4 Interval (s),Schedule 5 Wakeup (s),Schedule 5 Interval (s),Schedule 6 Wakeup (s),Schedule 6 Interval (s),Schedule 7 Wakeup (s),Schedule 7 Interval (s),Schedule 8 Wakeup (s),Schedule 8 Interval (s),Schedule 9 Wakeup (s),Schedule 9 Interval (s),Schedule 10 Wakeup (s),Schedule 10 Interval (s),Requested Rest to Motion Latency (s),Requested Motion to Rest Latency (s),Client Receives Motion Indication (s),Client State When Recieving Ind,Motion State Timestamp (ms),Motion State";
    #LOG_SNS_IOD_CONFIG_C
    $legends{oct("0x1918")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,confidence_threshold1,confidence_threshold2,time_of_day,sunset_timestamps,sunrise_timestamps,iod_calibration_value,algo_inst_id";
    $legends{oct("0x1918")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Confidence Threshold 0,Confidence Threshold 1,Time of Day (s),Sunset Timestamp (s),Sunrise Timestamp(s),IOD Calibration Value,Instance";
    #LOG_SNS_IOD_RESULT_C
    $legends{oct("0x1919")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,gmm_likelihood1,gmm_likelihood2,hmm_parameter_selection_priors1,hmm_parameter_selection_priors2,hmm_transition_state,hmm_transition_matrix1,hmm_transition_matrix2,hmm_transition_matrix3,hmm_transition_matrix4,previous_time_of_day,posterior_probability1,posterior_probability2,prior_iod_state_probability1,prior_iod_state_probability2,als_data,proximity_data,als_calibration_value,sunset_timestamps,sunrise_timestamps,confidence_threshold1,confidence_threshold2,timer_value,iod_unknown_bitmask,algo_inst_id";
    $legends{oct("0x1919")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),GMM Likelihood 0,GMM Likelihood 1,HMM Parameter Selection Priors 0,HMM Parameter Selection Priors 1,HMM Transition State,HMM Transition Matrix 0,HMM Transition Matrix 1,HMM Transition Matrix 2,HMM Transition Matrix 3,Previous Time of Day (s),Posterior Probability 0,Posterior Probability 1,Prior IOD State Probability 0,Prior IOD State Probability 1,ALS Data,Proximity Data,ALS Calibration Value,Sunset Timestamp (s),Sunrise Timestamp (s),Confidence Threshold 0,Confidence Threshold 1,Timer Value (s),IOD Unknown Bitmask,Instance";
    #LOG_SNS_IOD_REPORT_C
    $legends{oct("0x191A")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,iod_output_state,confidence,iod_unknown_bitmask,iod_timer_value,algo_inst_id";
    $legends{oct("0x191A")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,IOD Output State,Confidence,IOD Unknown Bitmask,IOD Timer Value (s),Instance";
    #LOG_SNS_IOD_AUTOCAL_CONFIG_C
    $legends{oct("0x191B")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,time_of_day,sunset_timestamps,sunrise_timestamps,algo_inst_id";
    $legends{oct("0x191B")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Time of Day (s),Sunset Timestamp (s),Sunrise Timestamp (s),Instance";
    #LOG_SNS_IOD_AUTOCAL_RESULT_C
    $legends{oct("0x191C")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,first_mom,second_mom,num_samples,isdiscrete,als_value0,als_value1,als_value2,als_value3,als_value4,als_value5,als_value6,als_value7,als_value8,als_value9,als_value10,als_value11,als_value12,als_value13,als_value14,als_value15,current_calibration_value,als_data,proximity_data,test_convergence,sunset_timestamps,sunrise_timestamps,algo_inst_id";
    $legends{oct("0x191C")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),First Moment,Second Moment,Num Samples,Is Discrete,ALS Value 0 (lux),ALS Value 1 (lux),ALS Value 2 (lux),ALS Value 3 (lux),ALS Value 4 (lux),ALS Value 5 (lux),ALS Value 6 (lux),ALS Value 7 (lux),ALS Value 8 (lux),ALS Value 9 (lux),ALS Value 10 (lux),ALS Value 11 (lux),ALS Value 12 (lux),ALS Value 13 (lux),ALS Value 14 (lux),ALS Value 15 (lux),Current Calibration Value,ALS Data,Proximity Data,Test Convergence,Sunset Timestamp (s),Sunrise Timestamp (s),Instance";
    #LOG_SNS_IOD_AUTOCAL_REPORT_C
    $legends{oct("0x191D")}{"Original"} = "#packet_type,version,timestamp_type,timestamp,report_id,report_type,iod_calibration_return_status,iod_calibration_value,first_mom,second_mom,num_samples,isdiscrete,als_value0,als_value1,als_value2,als_value3,als_value4,als_value5,als_value6,als_value7,als_value8,als_value9,als_value10,als_value11,als_value12,als_value13,als_value14,als_value15,algo_inst_id";
    $legends{oct("0x191D")}{"New"} = "#Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,IOD Calibration Return Status,IOD Calibration Value,First Moment,Second Moment,Num Samples,Is Discrete,ALS Value 0 (lux),ALS Value 1 (lux),ALS Value 2 (lux),ALS Value 3 (lux),ALS Value 4 (lux),ALS Value 5 (lux),ALS Value 6 (lux),ALS Value 7 (lux),ALS Value 8 (lux),ALS Value 9 (lux),ALS Value 10 (lux),ALS Value 11 (lux),ALS Value 12 (lux),ALS Value 13 (lux),ALS Value 14 (lux),ALS Value 15 (lux),Instance";
    
    
    
# ---------------------------------------------------------------------------------------
# Parse the IOD reason bitmask in string representation.
# Usage:  $result = ParseIODReasonBitmask($bitmask)
# ---------------------------------------------------------------------------------------
sub ParseIODReasonBitmask {
    
    my ($bitmask) = @_;
    
    my @values;
    if ( $bitmask) {
        push(@values, "UNKNOWN_LOW_CONFIDENCE") if ( $bitmask & 0x01 );
        push(@values, "UNKNOWN_NIGHT") if ( $bitmask & 0x02 );
        push(@values, "UNKNOWN_CONCEALED") if ( $bitmask & 0x04 );
        push(@values, "UNKNOWN_ALS_LOW") if ( $bitmask & 0x08 );
        push(@values, "UNKNOWN_PARAMETER_NOT_INITIALIZED") if ( $bitmask & 0x10 );
    }   
    return join(', ', @values);

} # ParseIODReasonBitmask

    
# ---------------------------------------------------------------------------------------
# Locate a perl script in the current or parent directory, if it exists.
# Usage:  locate_script($script)
# ---------------------------------------------------------------------------------------
sub locate_script {

   my ($script) = @_;

   use FindBin qw($Bin);
   # print "Bin=".$Bin."\n";

   my $parent = dirname($Bin);
   # print "Parent=".$parent."\n";

   if (-f File::Spec->catfile($Bin, $script)) {
      return File::Spec->catfile($Bin, $script);
   }
   elsif (-f File::Spec->catfile($parent, $script)) {
      return File::Spec->catfile($parent, $script);
   }
   die "Unable to locate %script in the current or parent directory of $Bin";

} # locate_script


# ---------------------------------------------------------------------------------------
# Convert Q16 format in decimal format.
# Usage:  convert_Q16_to_decimal($Q16)
# ---------------------------------------------------------------------------------------
sub convert_Q16_to_decimal
{
   my ($Q16) = @_;
   return sprintf( "%.6f", $Q16 / 65536);

} # convert_Q16_to_decimal


# ---------------------------------------------------------------------------------------
# Convert radians to degrees.
# Usage:  convert_rad_to_deg($rad)
# ---------------------------------------------------------------------------------------
sub convert_rad_to_deg
{
   my ($rad) = @_;
   return sprintf( "%.6f", $rad * 180 / PI);

} # convert_rad_to_deg


# ---------------------------------------------------------------------------------------
# Format the entered timestamp based on type into milliseconds, either DSPS timer ticks, APPS usec timer, NANO (nanosecond) timer.
# Usage:  format_timestamp($timestamp, $type)
# ---------------------------------------------------------------------------------------
sub format_timestamp
{
   my ($timestamp, $type) = @_;

   my %types = (
       -1 => "NANO",
       0 => "DSPS",
       1 => "APPS",
       2 => "MODEM",
       3 => "GPS");     # GPS is the same as DSPS???

   if (!defined($type)) {
      $type = "Unknown";
   } elsif (defined $types{$type}) {
      $type = $types{$type};
   }

   if (($type eq "DSPS") || ($type eq "MODEM") || ($type eq "GPS")) {
      $timestamp = sprintf( "%.3f", $timestamp * ( 1000/ 32768));
   } elsif ($type eq "APPS") {
      $timestamp = sprintf( "%.3f", $timestamp / 1000);
   } elsif ($type eq "NANO") {
      $timestamp = sprintf( "%.3f", $timestamp / 1000000);
   }
   return ($timestamp, $type);

} # format_timestamp


# ------------------------------------------------------------------------------
# Get the header line for the file for the specified packet
# Usage:  GetHeader($key)
# ------------------------------------------------------------------------------
sub GetHeader {

   my ($key) = @_;
   my $line = "";

   if (!$flagNH) {

      $line = "#Framework,Extract_Internal_Packets\n";
      $line .= "#Version,1.0\n";
      $line .= "#Key,0x".sprintf("%X\n", $key);
      $line .= "#PacketType,0x".sprintf("%X\n", $key);
      $line .= "#PacketNumber,$key\n";
      
      if (defined($supportedPackets{$key})) {       
         my $name = $supportedPackets{$key};
         $name =~ s/_/-/gi;
         $line .= "#Name,".$name."\n";
      } else {                
         $line .= "#Name,Unknown Packet\n";                        
      }

      my $version = "New";
      $version = "Original" if ($flagA);
      
      if (defined($legends{$key}{$version})) {       
         $line .= $legends{$key}{$version}."\n";
      } else {                
         $line .= "#Unknown Legend\n";          
      }                                             
   }
   #print "Debug: $line";
   return $line;

} # GetHeader


# ------------------------------------------------------------------------------
# Return the properly formatted packet based on the known packet
# Usage:  FormatPacket(@packet)
# ------------------------------------------------------------------------------
sub FormatPacket {

   my (@packet) = @_;

   if (!$flagA) {

        # Get the packet type
        my $type = $packet[0];
    
        #LOG_SNS_DSPS_PWR_C                 => 0x151B;
        if ($type == oct("0x151B")) {
    
           #packet_type,version,ts,power_state
           #Packet,Version,Timestamp (ms),Power State
           if ($#packet >= 3) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              $packet[3] = $lit_PowerState{$packet[1]}{$packet[3]} if (defined($lit_PowerState{$packet[1]}{$packet[3]}));
           }
        }
        #LOG_SNS_QMD_CONFIG_C               => 0x151D;
        elsif ($type == oct("0x151D")) {
    
           #packet_type,version,ts,sample_rate,enable_amd,enable_vmd,enable_rmd,instance_id
           #Packet,Version,Timestamp (ms),Sample Rate (Hz),Enable AMD,Enable VMD,Enable RMD,Instance
           if ($#packet >= 6) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              $packet[3] = convert_Q16_to_decimal($packet[3]);
              $packet[4] = $lit_TrueFalse{$packet[4]} if (defined($lit_TrueFalse{$packet[4]}));
              $packet[5] = $lit_TrueFalse{$packet[5]} if (defined($lit_TrueFalse{$packet[5]}));
              $packet[6] = $lit_TrueFalse{$packet[6]} if (defined($lit_TrueFalse{$packet[6]}));
           }
        }
        #LOG_SNS_QMD_RESULT_C               => 0x151E;
        elsif ($type == oct("0x151E")) {
    
           #packet_type,version,ts,accelX,accelY,accelZ,amd_result,vmd_result,rmd_result,instance_id
           #Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),AMD Result,VMD Result,RMD Result,Instance
           if ($#packet >= 8) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              foreach my $i (3..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[6] = $lit_qmdMotionStates{$packet[6]} if (defined($lit_qmdMotionStates{$packet[6]}));
              $packet[7] = $lit_qmdMotionStates{$packet[7]} if (defined($lit_qmdMotionStates{$packet[7]}));
              $packet[8] = $lit_qmdMotionStates{$packet[8]} if (defined($lit_qmdMotionStates{$packet[8]}));
           }
        }
        #LOG_SNS_QMD_REPORT_C               => 0x151F;
        elsif ($type == oct("0x151F")) {
    
           #packet_type,version,ts,report_id,report_type,client_id,qmd_result,service_id,instance_id
           #Packet,Version,Timestamp (ms),Report ID,Report Type,Client ID,QMD Result,Service ID,Instance
           if ($#packet >= 7) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              $packet[4] = $lit_ReportType{$packet[4]} if (defined($lit_ReportType{$packet[4]}));
              $packet[6] = $lit_qmdMotionStates{$packet[6]} if (defined($lit_qmdMotionStates{$packet[6]}));
              $packet[7] = $lit_qmd_service_name{$packet[7]} if (defined($lit_qmd_service_name{$packet[7]}));
           }
        }
        #LOG_SNS_GYRO_SIMP_CAL_CONFIG_C     => 0x152B;
        elsif ($type == oct("0x152B")) {
    
           #packet_type,version,ts,sample_rate,instance_id
           #Packet,Version,Timestamp (ms),Sample Rate (Hz),Instance
           if ($#packet >= 3) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              $packet[3] = convert_Q16_to_decimal($packet[3]);
           }
        }
        #LOG_SNS_GYRO_SIMP_CAL_RESULT_C     => 0x152C;
        elsif ($type == oct("0x152C")) {
    
           #packet_type,version,ts,gyro_x,gyro_y,gyro_z,gyro_zbx,gyro_zby,gyro_zbz,instance_id
           #Packet,Version,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Zero Bias X (deg/s),Zero Bias Y (deg/s),Zero Bias Z (deg/s),Instance
           if ($#packet >= 8) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              foreach my $i (3..8) {
                 $packet[$i] = convert_rad_to_deg(convert_Q16_to_decimal($packet[$i]));
              }
           }
        }
        #LOG_SNS_GYRO_SIMP_CAL_REPORT_C     => 0x152D;
        elsif ($type == oct("0x152D")) {
    
           #packet_type,version,ts,gyro_x,gyro_y,gyro_z,gyro_zbx,gyro_zby,gyro_zbz
           #Packet,Version,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Zero Bias X (deg/s),Zero Bias Y (deg/s),Zero Bias Z (deg/s)
           if ($#packet >= 8) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              foreach my $i (3..8) {
                 $packet[$i] = convert_rad_to_deg(convert_Q16_to_decimal($packet[$i]));
              }
           }
        }
        #LOG_SNS_QUAT_CONFIG_C              => 0x153C;        
        elsif ($type == oct("0x153C")) {
    
           #packet_type,version,ts_type,ts,report_period,sample_rate,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Instance
           if ($#packet >= 5) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_QUAT_RESULT_C              => 0x153D;
        elsif ($type == oct("0x153D")) {
    
           #packet_type,version,ts_type,ts,gyro_x,gyro_y,gyro_z,quat0,quat1,quat2,quat3,delta_t,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Quat0,Quat1,Quat2,Quat3,Delta Time,Instance
           if ($#packet >= 11) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[11] = convert_Q16_to_decimal($packet[11]);
           }
        }
        #LOG_SNS_QUAT_REPORT_C              => 0x153E;
        elsif ($type == oct("0x153E")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,quat0,quat1,quat2,quat3,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Quat0,Quat1,Quat2,Quat3,Instance
           if ($#packet >= 3) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
           }
        }
        #LOG_SNS_GRAVITY_CONFIG_C           => 0x153F;        
        elsif ($type == oct("0x153F")) {
    
           #packet_type,version,ts_type,ts,report_period,sample_rate,time_cons_abs,time_cons_rel,time_cons_mot,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Abs Rest Time Constant,Rel Rest Time Constant,Motion Time Constant,Instance
           if ($#packet >= 8) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..8) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_GRAVITY_RESULT_C           => 0x1540;        
        elsif ($type == oct("0x1540")) {
    
           #packet_type,version,ts_type,ts,gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z,abs_state,rel_state,grav_est_x,grav_est_y,grav_est_z,linacc_x,linacc_y,linacc_z,delta_t,alpha,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Absolute Rest State,Relative Rest State,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),Delta Time,Alpha,Instance
    
           if ($#packet >= 19) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6) {
                 $packet[$i] = convert_rad_to_deg($packet[$i]);
              }
              foreach my $i (7..9) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[10] = $lit_gravMotionStates{$packet[10]} if (defined($lit_gravMotionStates{$packet[10]}));
              $packet[11] = $lit_gravMotionStates{$packet[11]} if (defined($lit_gravMotionStates{$packet[11]}));
              $packet[18] = convert_Q16_to_decimal($packet[18]);
              $packet[19] = convert_Q16_to_decimal($packet[19]);
           }
        }
        #LOG_SNS_GRAVITY_REPORT_C           => 0x1541;        
        elsif ($type == oct("0x1541")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,grav_x,grav_y,grav_z,linacc_x,linacc_y,linacc_z,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),Instance
           if ($#packet >= 3) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
           }
        }
        #LOG_SNS_DRV_MD_IRQ_C               => 0x1559;  
        elsif ($type == oct("0x1559")) {
           #packet_type,version,ts,threshold
           #Packet,Version,Timestamp (ms),Threshold (milliG)
           if ($#packet >= 3) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              # Assume threshold is in mG units of int
           }         
        }
        #LOG_SNS_MAG_CAL_CONFIG_C           => 0x155A;    
        elsif ($type == oct("0x155A")) {
    
           #packet_type,version,ts_type,ts,report_period,sample_rate,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Instance
           if ($#packet >= 5) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_MAG_CAL_RESULT_C           => 0x155B; 
        elsif ($type == oct("0x155B")) {
    
           #packet_type,version,ts_type,ts,mag_x,mag_y,mag_z,magcal_x,magcal_y,magcal_z,magcalbias_x,magcalbias_y,magcalbias_z,accuracy,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Mag X (Gs),Mag Y (Gs),Mag Z (Gs),MagCal X (Gs),MagCal Y (Gs),MagCal Z (Gs),MagCalBias X (Gs),MagCalBias Y (Gs),MagCalBias Z (Gs),Accuracy,Instance
           if ($#packet >= 13) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..12) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[13] = $lit_SamAccuracy{$packet[13]} if (defined($lit_SamAccuracy{$packet[13]}));
           }
        }
        #LOG_SNS_MAG_CAL_REPORT_C           => 0x155C; 
        elsif ($type == oct("0x155C")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,magcal_x,magcal_y,magcal_z,magcalbias_x,magcalbias_y,magcalbias_z,accuracy,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,MagCal X (Gs),MagCal Y (Gs),MagCal Z (Gs),MagCalBias X (Gs),MagCalBias Y (Gs),MagCalBias Z (Gs),Accuracy,Instance
           if ($#packet >= 13) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              foreach my $i (7..12) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[13] = $lit_SamAccuracy{$packet[13]} if (defined($lit_SamAccuracy{$packet[13]}));
           }
        }
        #LOG_SNS_ROTATION_VECTOR_CONFIG_C   => 0x155F;    
        elsif ($type == oct("0x155F")) {
    
           #packet_type,version,ts_type,ts,report_period,sample_rate,coord_sys,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Coordinate System,Instance
           if ($#packet >= 6) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[6] = $lit_rotvCoordSys{$packet[6]} if (defined($lit_rotvCoordSys{$packet[6]}));
           }
        }
        #LOG_SNS_ROTATION_VECTOR_RESULT_C   => 0x1560;     
        elsif ($type == oct("0x1560")) {
    
           #packet_type,version,ts_type,ts,grav_x,grav_y,grav_z,grav_ts,grav_acc,fm_x,fm_y,fm_z,fm_ts,fm_acc,rotv0,rotv1,rotv2,rotv3,accuracy,coord_sys,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Gravity Timestamp (ms),Gravity Accuracy,FMV X (Gs),FMV Y (Gs),FMV Z (Gs),FMV Timestamp (ms),FMV Accuracy,RotV0,RotV1,RotV2,RotV3,Accuracy,Coordinate System,Instance
           if ($#packet >= 19) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              ($packet[7], $packet[2]) = format_timestamp($packet[7], $packet[2]);
              $packet[8] = $lit_SamAccuracy{$packet[8]} if (defined($lit_SamAccuracy{$packet[8]}));
              ($packet[12], $packet[2]) = format_timestamp($packet[12], $packet[2]);
              $packet[13] = $lit_SamAccuracy{$packet[13]} if (defined($lit_SamAccuracy{$packet[13]}));
              $packet[18] = $lit_SamAccuracy{$packet[18]} if (defined($lit_SamAccuracy{$packet[18]}));
              $packet[19] = $lit_rotvCoordSys{$packet[19]} if (defined($lit_rotvCoordSys{$packet[19]}));
           }
        }
        #LOG_SNS_ROTATION_VECTOR_REPORT_C   => 0x1561;     
        elsif ($type == oct("0x1561")) { 
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,rotv0,rotv1,rotv2,rotv3,accuracy,coord_sys,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,RotV0,RotV1,RotV2,RotV3,Accuracy,Coordinate System,Instance
           if ($#packet >= 12) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[11] = $lit_SamAccuracy{$packet[11]} if (defined($lit_SamAccuracy{$packet[11]}));
              $packet[12] = $lit_rotvCoordSys{$packet[12]} if (defined($lit_rotvCoordSys{$packet[12]}));
           }
        }
        #LOG_SNS_FMV_CONFIG_C               => 0x1562;    
        elsif ($type == oct("0x1562")) {
    
           #packet_type,version,ts_type,ts,report_period,sample_rate,num_accuracy_bins,accuracy_bin_tcs0,accuracy_bin_tcs1,accuracy_bin_tcs2,accuracy_bin_tcs3,gyro_gap_thresh,mag_gap_thresh,min_turn_rate,max_mag_innovation,instance_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Accuracy Bin Count,Accuracy Bin tcs0,Accuracy Bin tcs1,Accuracy Bin tcs2,Accuracy Bin tcs3,Gyro Gap Threshold,Mag Gap Threshold,Min Turn Rate,Max Mag Innovation,Instance
           if ($#packet >= 5) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_FMV_QUAT_UPDATE_C          => 0x1563;     
        elsif ($type == oct("0x1563")) {
    
           #packet_type,version,ts_type,quat_ts,fmv_ts,quat0,quat1,quat2,quat3,fmv_x,fmv_y,fmv_z,accuracy,instance
           #Packet,Version,Timestamp Type,QUAT Timestamp (ms),FMV Timestamp (ms),Quat0,Quat1,Quat2,Quat3,FMV X (Gs),FMV Y (Gs),FMV Z (Gs),Accuracy,Instance
           if ($#packet >= 12) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              ($packet[4], $packet[2]) = format_timestamp($packet[4], $packet[2]);
              $packet[12] = $lit_SamAccuracy{$packet[12]} if (defined($lit_SamAccuracy{$packet[12]}));
           }
        }
        #LOG_SNS_FMV_MAG_UPDATE_C           => 0x1564;     
        elsif ($type == oct("0x1564")) {
    
           #packet_type,version,ts_type,ts_mag,ts_fmv,gyrox,gyroy,gyroz,bx,by,bz,fmv_x,fmv_y,fmv_z,accuracy,instance
           #Packet,Version,Timestamp Type,Mag Timestamp (ms),FMV Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Mag X (Gs),Mag Y (Gs),Mag Z (Gs),FMV X (Gs),FMV Y (Gs),FMV Z (Gs),Accuracy,Instance
           if ($#packet >= 14) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              ($packet[4], $packet[2]) = format_timestamp($packet[4], $packet[2]);
              foreach my $i (5..7) {
                 $packet[$i] = convert_rad_to_deg($packet[$i]);
              }
              $packet[14] = $lit_SamAccuracy{$packet[14]} if (defined($lit_SamAccuracy{$packet[14]}));
           }
        }
        #LOG_SNS_FMV_GYRO_UPDATE_C          => 0x1565;     
        elsif ($type == oct("0x1565")) {
    
           #packet_type,version,ts_type,ts,gyroX,gyroY,gyroZ,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Instance
           if ($#packet >= 6) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6) {
                 $packet[$i] = convert_rad_to_deg($packet[$i]);
              }
           }
        }
        #LOG_SNS_FMV_REPORT_C               => 0x1566;     
        elsif ($type == oct("0x1566")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,fmv_x,fmv_y,fmv_z,accuracy,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,FMV X (Gs),FMV Y (Gs),FMV Z (Gs),Accuracy,Instance
           if ($#packet >= 10) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[10] = $lit_SamAccuracy{$packet[10]} if (defined($lit_SamAccuracy{$packet[10]}));
           }
        }
        #ISAGNAV_TS_PACKET                  => 0x150B; 
        elsif ($type == oct("0x150B")) {
    
           #packet_type,version,pe_InfoValid,pe_TTValid,pe_ComputeValid,q_TimeTickAtGpsTOA,w_GpsWeek,q_GpsMs,q_OurTxMs,q_TheirRxMs,q_TheirTxMs,q_OurRxMs,w_Rtt,gps_week_offset,gps_ms_in_week_offset
           #Packet,Version,pe InfoValid,pe TTValid,pe ComputeValid,q TimeTickAtGpsTOA,w GpsWeek,q GpsMs,q OurTxMs,q TheirRxMs,q TheirTxMs,q OurRxMs,w Rtt,gps week offset,gps ms in week offset
    
        }
        #LOG_SNS_INTEG_ANGLE_CONFIG_C       => 0x159B; 
        elsif ($type == oct("0x159B")) {
    
           #packet_type,version,ts_type,ts,sample_rate(Hz in Q16),clip_threshold(rad in Q16),instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Clip Threshold (deg),Instance
           if ($#packet >= 5) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = convert_Q16_to_decimal($packet[4]);
              $packet[5] = convert_rad_to_deg(convert_Q16_to_decimal($packet[5]));
           }
        }
        #LOG_SNS_INTEG_ANGLE_RESULT_C       => 0x159C;   
        elsif ($type == oct("0x159C")) {
    
           #packet_type,version,ts_type,ts,g0(rad/s in Q16),g1(rad/s in Q16),g2(rad/s in Q16),ia0(rad in Q16),ia1(rad in Q16),ia2(rad in Q16),instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Integ Angle X (deg),Integ Angle Y (deg),Integ Angle Z (deg),Instance
           if ($#packet >= 9) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..9) {
                 $packet[$i] = convert_rad_to_deg(convert_Q16_to_decimal($packet[$i]));
              }
           }
        }
        #LOG_SNS_INTEG_ANGLE_REPORT_C       => 0x159D; 
        elsif ($type == oct("0x159D")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,ia0(rad in Q16),ia1(rad in Q16),ia2(rad in Q16),instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Integ Angle X (deg),Integ Angle Y (deg),Integ Angle Z (deg),Instance
           if ($#packet >= 9) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              foreach my $i (7..9) {
                 $packet[$i] = convert_rad_to_deg(convert_Q16_to_decimal($packet[$i]));
              }
           }
        }
        #LOG_SNS_GYRO_TAP_CONFIG_C          => 0x159E; 
        elsif ($type == oct("0x159E")) {
    
           #packet_type,version,ts_type,ts,sample_rate,tap_time_win,tap_time_sleep,tap_dir_win,accel_tap_thr,lr_accel_jerk_min_thresh_min,lr_gyro_jerk_min_thresh_min,tb_accel_jerk_min_thr,tb_gyro_jerk_min_thr,jerk_win,lr_accel_rat_jerk_yx,lr_accel_rat_jerk_yz,lr_gyro_rat_jerk_zy,lr_gyro_rat_jerk_zx,tb_accel_rat_jerk_xy,tb_accel_rat_jerk_xz,tb_gyro_rat_jerk_yx,tb_gyro_rat_jerk_yz,tb_accel_z_thresh,tb_accel_z_rat_zx,tb_accel_z_rat_zy,ori_change_win,ori_check_win,ori_change_thr,z_axis_inc,loaded_axis_3_valid,lr_min_accel_jerk_thresh_min,lr_max_accel_jerk_thresh_min,lr_min_gyro_jerk_thresh_min,lr_max_gyro_jerk_thresh_min,mild_accel_tap_thresh,loaded_z_axis_anamoly,ori_change_reject_mode,stress_right_left,instance"
           #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Tap Time Win,Tap Time Sleep,Tap Dir Win,Accel Tap Thr,lr Accel Jerk Min Thresh,lr Gyro Jerk Min Thresh,tb Accel Jerk Min Thr,tb Gyro Jerk Min Thr,Jerk Win,lr Accel Rat Jerk yx,lr Accel Rat Jerk yz,lr Gyro Rat Jerk zy,lr Gyro Rat Jerk zx,tb Accel Rat Jerk xy,tb Accel Rat Jerk xz,tb Gyro Rat Jerk yx,tb Gyro Rat Jerk yz,tb Accel A Thresh,tb Accel Z Rat zx,tb Accel Z Rat zy,Ori Change Win,Ori Check Win,Ori Change Thr,Z Axis Inc,Loaded Axis 3 Valid,lr Min Accel Jerk Thresh Min,lr Max Accel Jerk Tresh Min,lr Min Gyro Jerk Thresh Min,lr Max Gyro Jerk Thresh Min,Mild Accel Tap Thresh,Loaded Z Axis Anamoly,Ori Change Reject Mode,Stress Right Left,Instance"
           if ($#packet >= 3) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = convert_Q16_to_decimal($packet[4]);
              # All other values are not interpreted (likely in Q16 format)
           }
        }
        #LOG_SNS_GYRO_TAP_RESULT_C          => 0x159F; 
        elsif ($type == oct("0x159F")) {
    
           #packet_type,version,ts_type,ts,g0,g1,g2,a0,a1,a2,tap_event,algo_state,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Gyro X (deg/s),Gyro Y (deg/s),Gyro Z (deg/s),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Tap Event,State,Instance
           if ($#packet >= 10) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..9) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              foreach my $i (4..6) {
                 $packet[$i] = convert_rad_to_deg($packet[$i]);
              }
              $packet[10] = $lit_gyro_tap_Gestures{$packet[10]} if (defined($lit_gyro_tap_Gestures{$packet[10]}));
           }
        }
        #LOG_SNS_GYRO_TAP_REPORT_C          => 0x15A0; 
        elsif ($type == oct("0x15A0")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,tap_event,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Tap Event,Instance
           if ($#packet >= 7) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[7] = $lit_gyro_tap_Gestures{$packet[7]} if (defined($lit_gyro_tap_Gestures{$packet[7]}));
           }
        }
        #LOG_SNS_BASIC_GESTURES_CONFIG_C    => 0x15A1; 
        elsif ($type == oct("0x15A1")) {
    
           #packet_type,version,ts_type,ts,sample_rate(Hz in Q16),sleep,push_thresh,pull_thresh,shake_thresh,config1,config2,config3,config4,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Sleep,Push Threshold,Pull Threshold,Shake Threshold,Config Param1,Config Param2,Config Param3,Config Param4,Instance
           if ($#packet >= 4) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = convert_Q16_to_decimal($packet[4]);
           }
        }
        #LOG_SNS_BASIC_GESTURES_RESULT_C    => 0x15A2; 
        elsif ($type == oct("0x15A2")) {
    
           #packet_type,version,ts_type,ts,accel_x,accel_y,accel_z,motion_state,basic_state,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Motion State,Basic State,Instance
           if ($#packet >= 8) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[8] = $lit_basic_Gestures{$packet[8]} if (defined($lit_basic_Gestures{$packet[8]}));
           }
        }
        #LOG_SNS_BASIC_GESTURES_REPORT_C    => 0x15A3; 
        elsif ($type == oct("0x15A3")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,basic_state,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Basic State,Instance
           if ($#packet >= 7) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[7] = $lit_basic_Gestures{$packet[7]} if (defined($lit_basic_Gestures{$packet[7]}));
           }
        }
        #LOG_SNS_FACING_CONFIG_C            => 0x15A4; 
        elsif ($type == oct("0x15A4")) {
    
           #packet_type,version,ts_type,ts,sample_rate,facing_angle_threshold(rad in Q16),report_neutral,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Facing Angle Threshold (deg),Report Neutral,Instance
           if ($#packet >= 5) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = convert_Q16_to_decimal($packet[4]);
              $packet[5] = convert_rad_to_deg(convert_Q16_to_decimal($packet[5]));
           }
        }
        #LOG_SNS_FACING_RESULT_C            => 0x15A5; 
        elsif ($type == oct("0x15A5")) {
    
           #packet_type,version,ts_type,ts,accel_x,accel_y,accel_z,motion_state,facing_state,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Motion State,Facing State,Instance
           if ($#packet >= 8) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[8] = $lit_facing_Gestures{$packet[8]} if (defined($lit_facing_Gestures{$packet[8]}));
           }
        }
        #LOG_SNS_FACING_REPORT_C            => 0x15A6; 
        elsif ($type == oct("0x15A6")) {
    
           #packet_type,version,ts_type,ts,report_id,report_type,client_id,facing_state,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Facing State,Instance
           if ($#packet >= 7) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[7] = $lit_facing_Gestures{$packet[7]} if (defined($lit_facing_Gestures{$packet[7]}));
           }
        }
        #LOG_SNS_ACCEL_CAL_CONFIG_C         => 0x15B8;
        elsif ($type == oct("0x15B8")) {
    
           #packet_type,version,ts,sample_rate(Hz in Q16),instance
           #Packet,Version,Timestamp (ms),Sample Rate (Hz),Instance
           if ($#packet >= 3) {
              ($packet[2], my $tmp) = format_timestamp($packet[2], "DSPS");
              $packet[3] = convert_Q16_to_decimal($packet[3]);
           }
        }
        #LOG_SNS_ACCEL_CAL_RESULT_C         => 0x15B9; 
        elsif ($type == oct("0x15B9")) {
    
           #packet_type,version,ts,accel_x,accel_y,accel_z,temp,accel_zero_bias_x,accel_zero_bias_y,accel_zero_bias_z,accel_scale_factor_x,accel_scale_factor_y,accel_scale_factor_z,instance
           #Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Temperature (C),Zero Bias X (m/s/s),Zero Bias Y (m/s/s),Zero Bias Z (m/s/s),Scale Factor X,Scale Factor Y,Scale Factor Z,Instance
           if ($#packet >= 12) {
              ($packet[2], my $tmp) = format_timestamp($packet[2], "DSPS");
              foreach my $i (3..12) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_ACCEL_CAL_REPORT_C         => 0x15BA; 
        elsif ($type == oct("0x15BA")) {
    
           #packet_type,version,ts,accel_x,accel_y,accel_z,temp,accel_zero_bias_x,accel_zero_bias_y,accel_zero_bias_z,accel_scale_factor_x,accel_scale_factor_y,accel_scale_factor_z,cal_report_decision,temp_op_min,count_kf_update,covar_accel_x_bias,covar_accel_y_bias,covar_accel_z_bias,covar_accel_x_sf,covar_accel_y_sf,covar_accel_z_sf,kf_accel_x_bias,kf_accel_y_bias,kf_accel_z_bias,kf_accel_x_sf,kf_accel_y_sf,kf_accel_z_sf
           #Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Temperature (C),Zero Bias X (m/s/s),Zero Bias Y (m/s/s),Zero Bias Z (m/s/s),Scale Factor X,Scale Factor Y,Scale Factor Z,Report Decision,Operational Temperature Min (C),KF Update Counts,KF Covariance Bias X (mG^2),KF Covariance Bias Y (mG^2),KF Covariance Bias Z (mG^2),KF Covariance SF X (mG^2),KF Covariance SF Y (mG^2),KF Covariance SF Z (mG^2),KF Bias X Est (mG),KF Bias Y Est (mG),KF Bias Z Est (mG),KF SF X Est (mG),KF SF Y Est (mG),KF SF Z Est (mG)
           if ($#packet >= 12) {
              ($packet[2], my $tmp) = format_timestamp($packet[2], "DSPS");
              foreach my $i (3..12) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_QMAG_CAL_CONFIG_C          => 0x163A
        elsif ($type == oct("0x163A")) {
      
           #packet_type,version,timestamp_type,timestamp,sample_rate_mag,sample_rate_accel,cal_algo_type,cal_cycle_rate
           #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate Mag (Hz),Sample Rate Accel (Hz),Cal Algo Type,Cal Cycle Rate
           if ($#packet >= 6) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = convert_Q16_to_decimal($packet[4]);
              $packet[5] = convert_Q16_to_decimal($packet[5]);            
              $packet[6] = $lit_CalAlgoType{$packet[6]} if (defined($lit_CalAlgoType{$packet[6]}));
           }         
        }
        #LOG_SNS_QMAG_CAL_RESULT_C          => 0x163B
        elsif ($type == oct("0x163B")) {
      
           #packet_type,version,timestamp_type,timestamp,input_type,input_mag_x,input_mag_y,input_mag_z,input_accel_x,input_accel_y,input_accel_z,accel_input_variance,mag_input_variance,offset_hi_unfiltered_x,offset_hi_unfiltered_y,offset_hi_unfiltered_z,radius_hi,unfiltered_accuracy,accuracy_published,cal_algo_type,mag_zero_bias_published_x,mag_zero_bias_published_y,mag_zero_bias_published_z,offset_time,hard_reset,soft_reset
           #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Input Mag X (G),Input Mag Y (G),Input Mag Z (G),Input Accel X (m/s/s),Input Accel Y (m/s/s),Input Accel Z (m/s/s),Accel Input Variance,Mag Input Variance,Offset HI Unfiltered X (G),Offset HI Unfiltered Y (G),Offset HI Unfiltered Z (G),Radius HI (G),Unfiltered Accuracy,Accuracy Published,Cal Algo Type,Mag Zero Bias Published X (G),Mag Zero Bias Published Y (G),Mag Zero Bias Published Z (G),Offset Time (ms),Hard Reset,Soft Reset
           if ($#packet >= 25) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = $lit_QMagInputType{$packet[4]} if (defined($lit_QMagInputType{$packet[4]}));
              foreach my $i (5..10, 20..22) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }            
              $packet[17] = $lit_SamAccuracy{$packet[17]} if (defined($lit_SamAccuracy{$packet[17]}));
              $packet[18] = $lit_SamAccuracy{$packet[18]} if (defined($lit_SamAccuracy{$packet[18]}));
              $packet[19] = $lit_CalAlgoType{$packet[19]} if (defined($lit_CalAlgoType{$packet[19]}));
              ($packet[23], my $tmp) = format_timestamp($packet[23], "DSPS");
              $packet[24] = $lit_Reset{$packet[24]} if (defined($lit_Reset{$packet[24]}));
              $packet[25] = $lit_Reset{$packet[25]} if (defined($lit_Reset{$packet[25]}));            
           }
        }
        #LOG_SNS_QMAG_CAL_REPORT_C          => 0x163C
        elsif ($type == oct("0x163C")) {
          
           #packet_type,version,timestamp_type,timestamp,qmag_x,qmag_y,qmag_z,qmag_zero_bias_corr_x,qmag_zero_bias_corr_y,qmag_zero_bias_corr_z
           #Packet,Version,Timestamp Type,Timestamp (ms),QMAG X (G),QMAG Y (G),QMAG Z (G),QMAG X Zero Bias Correction (G),QMAG Y Zero Bias Correction (G),QMAG Z Zero Bias Correction (G)
           if ($#packet >= 9) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..9) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }            
           }
        }
        #LOG_SNS_PED_CONFIG_C               => 0x1637;
        elsif ($type == oct("0x1637")) {
    
           #packet_type,version,ts,sample_rate,step_count_threshold,step_threshold,swing_threshold,step_prob_threshold,instance
           #Packet,Version,Timestamp (ms),Sample Rate (Hz),Step Count Threshold (steps),Step Threshold (m/s/s),Swing Threshold (m/s/s),Step Probability Threshold (%),Instance
           if ($#packet >= 3) {
              ($packet[2], my $tmp) = format_timestamp($packet[2], "DSPS");
              $packet[3] = convert_Q16_to_decimal($packet[3]);
           }
        }
        #LOG_SNS_PED_RESULT_C               => 0x1638;
        elsif ($type == oct("0x1638")) {
    
           #packet_type,version,ts,accel_x(in Q16),accel_y(in Q16),accel_z(in Q16),sample_rate,client_id,reset_stats,step_event,step_confidence,step_count,step_count_error,swing_step_count,step_rate,instance
           #Packet,Version,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Sample Rate (Hz),Client ID,Reset Stats,Step Event,Step Confidence (%),Step Count (steps),Step Count Error (steps),Swing Step Count (steps),Step Rate (steps/s),Instance
           if ($#packet >= 9) {
              ($packet[2], my $tmp) = format_timestamp($packet[2], "DSPS");
              foreach my $i (3..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[8] = $lit_TrueFalse{$packet[8]} if (defined($lit_TrueFalse{$packet[8]}));
              $packet[9] = $lit_TrueFalse{$packet[9]} if (defined($lit_TrueFalse{$packet[9]}));
           }
        }
        #LOG_SNS_PED_REPORT_C               => 0x1639;
        elsif ($type == oct("0x1639")) {
    
           #packet_type,version,ts,report_id,report_type,client_id,step_event,step_confidence,step_count,step_count_error,step_rate,instance
           #Packet,Version,Timestamp (ms),Report ID,Report Type,Client ID,Step Event,Step Confidence (%),Step Count (steps),Step Count Error (steps),Step Rate (steps/s),Instance
           if ($#packet >= 6) {
              ($packet[2], my $tmp) = format_timestamp($packet[2], "DSPS");
              $packet[4] = $lit_ReportType{$packet[4]} if (defined($lit_ReportType{$packet[4]}));
              $packet[6] = $lit_TrueFalse{$packet[6]} if (defined($lit_TrueFalse{$packet[6]}));
           }
        }
        #LOG_SNS_PAM_CONFIG_C               => 0x1640;
        elsif ($type == oct("0x1640")) {
    
           #packet_type,version,timestamp_type,timestamp,measurement_period,step_count_threshold,sample_rate,duty_cycle_on_percent,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Measurement Period (s),Step Count Threshold (steps),Sample Rate (Hz),Duty Cycle On (%),Instance
           if ($#packet >= 6) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[6] = convert_Q16_to_decimal($packet[6]);
           }
        }
        #LOG_SNS_PAM_RESULT_C               => 0x1641;
        elsif ($type == oct("0x1641")) {
    
           #packet_type,version,timestamp_type,timestamp,pedometer_step_count,motion_state,data_type,pedometer_last_step_count,pam_current_step_count,pam_last_reported_step_count,pam_report_decision,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Pedometer Step Count (steps),Motion State,Data Type,Pedometer Last Step Count (steps),PAM Current Step Count (steps),PAM Last Reported Step Count (steps),PAM Report Decision,Instance
           if ($#packet >= 10) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_qmdMotionStates{$packet[5]} if (defined($lit_qmdMotionStates{$packet[5]}));
              $packet[10] = $lit_TrueFalse{$packet[10]} if (defined($lit_TrueFalse{$packet[10]}));
           }
        }
        #LOG_SNS_PAM_REPORT_C               => 0x1642;
        elsif ($type == oct("0x1642")) {
    
           #packet_type,version,timestamp_type,timestamp,step_count,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),State,Step Count (steps),Instance  #### Added state because of overloading!!!
           if ($#packet == 5) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
    
              # Needed to add state because of overloading!!!
              my $lit_state;
              my $step_count = 0;
              if ($packet[4] == -2) {
                 $lit_state = "Unknown";
              }
              elsif ($packet[4] == -1) {
                 $lit_state = "Stationary";
              }
              elsif ($packet[4] >= 0 ) {
                 $lit_state = "Motion";
                 $step_count = $packet[4];
              }
              $packet[6] = $packet[5];
              $packet[5] = $step_count;
              $packet[4] = $lit_state;
           }
        }
        #LOG_SNS_SMD_CONFIG_C               => 0x17F8;
        elsif ($type == oct("0x17F8")) {
    
           #packet_type,version,timestamp_type,timestamp,sample_rate,accel_window_time,detect_threshold,self_transition_prob_nm,variable_latency_flag,max_latency,algo_inst_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Accel Window Time,Detect Threshold,Self Transition Prob nm,Variable Latency Flag,Max Latency,Instance
           if ($#packet >= 8) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..7) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[8] = $lit_TrueFalse{$packet[8]} if (defined($lit_TrueFalse{$packet[8]}));
           }
        }
        #LOG_SNS_SMD_RESULT_C               => 0x17F9;
        elsif ($type == oct("0x17F9")) {
    
           #packet_type,version,timestamp_type,timestamp,ax,ay,az,sample_cnt,variance,eigenvaluesx,eigenvaluesy,eigenvaluesz,xcor,spread_mag,rm,sa,pstate0,pstate1,filter_delay_cnt,filter_delay_time,motion_state,final_motion_state,algo_inst_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Sample Count,Variance,Eigenvalues X,Eigenvalues Y,Eigenvalues Z,Auto Correlation,Spread Magnitue,RM Ratio Feature,SA Feature,pstate0,pstate1,Filter Delay Count,Filter Delay Time (s),Motion State,Final Motion State,Instance
           if ($#packet >= 21) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6, 8..17) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[20] = $lit_qmdMotionStates{$packet[20]} if (defined($lit_qmdMotionStates{$packet[20]}));
              $packet[21] = $lit_qmdMotionStates{$packet[21]} if (defined($lit_qmdMotionStates{$packet[21]}));
           }
        }
        #LOG_SNS_SMD_REPORT_C               => 0x17FA;
        elsif ($type == oct("0x17FA")) {
    
           #packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,motion_state,motion_state_probability,algo_inst_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Motion State,Motion State Probability (%),Instance
           if ($#packet >= 7) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[7] = $lit_qmdMotionStates{$packet[7]} if (defined($lit_qmdMotionStates{$packet[7]}));
           }
        }
        #LOG_SENSOR_FIFO_EVENT_C            => 0x17F3;
        elsif ($type == oct("0x17F3")) {
    
           #packet_type,version,timestamp,sensor_id,fifo_event,watermark_depth,odr,hw_watermark_int_supported,max_watermark";           
           #Packet,Version,Timestamp (ms),Sensor ID,FIFO Event,Watermark Depth (samples),ODR,HW Watermark INT Supported,Max Watermark (samples)";           
           if ($#packet >= 4) {
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
              $packet[4] = $lit_fifo_event{$packet[4]} if (defined($lit_fifo_event{$packet[4]}));
           }
        }
        #LOG_SNS_CMC_CONFIG_C               => 0x17EA;
        elsif ($type == oct("0x17EA")) {
    
           #packet_type,version,timestamp_type,timestamp,Unknown Legend for LOG_SNS_CMC_CONFIG_C => 0x17EA
           #Packet,Version,Timestamp Type,Timestamp (ms),Unknown Legend for LOG_SNS_CMC_CONFIG_C => 0x17EA
           if ($#packet >= 3) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
           }
        }
        #LOG_SNS_CMC_RESULT_C               => 0x17EB;
        elsif ($type == oct("0x17EB")) {
    
            # Version 1:
            #packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,sample_count,accel_prevX,accel_prevY,accel_prevZ,accel_sumX,accel_sumY,accel_sumZ,accel_norm_sum,accel_norm_sq_sum,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Sample Count,Accel Prev X (m/s/s),Accel Prev Y (m/s/s),Accel Prev Z (m/s/s),Accel Sum X (m/s/s),Accel Sum Y (m/s/s),Accel Sum Z (m/s/s),Accel Norm Sum,Accel Norm Sq Sum,Instance
            # Version 2:
            #packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,qmd_motion_state,update_reporting_motion_state,update_reporting_event_type,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),QMD Motion State,Update Reporting Motion State,Update Reporting Event Type,Instance
            if ($#packet >= 10 ) {
               ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
               foreach my $i (5..7) {
                  $packet[$i] = convert_Q16_to_decimal($packet[$i]);
               }
               if ($packet[1] == 2) {
                    $packet[4] = $lit_cmc_input_type{$packet[4]} if (defined($lit_cmc_input_type{$packet[4]}));
                    $packet[8] = $lit_qmdMotionStates{$packet[8]} if (defined($lit_qmdMotionStates{$packet[8]}));
                    $packet[9] = $lit_cmc_motion_states{$packet[9]} if (defined($lit_cmc_motion_states{$packet[9]}));
                    $packet[10] = $lit_cmc_reporting_type{$packet[10]} if (defined($lit_cmc_reporting_type{$packet[10]}));
               }               
            }
        }
        #LOG_SNS_CMC_REPORT_C               => 0x17EC;
        elsif ($type == oct("0x17EC")) {
    
            # Version 1:
            #packet_type,version,timestamp_type,timestamp,motion_state,motion_state_probability,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Motion State,Motion State Probability,Instance
            # Version 2:
            #packet_type,version,timestamp_type,timestamp,motion_state,motion_state_event,motion_state_probability,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Motion State,Motion State Event,Motion State Probability (%),Instance
            if ($#packet >= 6) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[4] = $lit_cmc_motion_states{$packet[4]} if (defined($lit_cmc_motion_states{$packet[4]}));
                if ($packet[1] == 2) {  # Version 2 packet
                    $packet[5] = $lit_cmc_motion_state_event{$packet[5]} if (defined($lit_cmc_motion_state_event{$packet[5]}));
                    $packet[6] = 100 * $packet[6];   # Probability
                }
            }
        }
        #LOG_SNS_DB_CONFIG_C                => 0x17ED;
        elsif ($type == oct("0x17ED")) {
        
            #Version 1: 
            #packet_type,version,timestamp_type,timestamp,client_req_id,ms_unknown_speedbound,ms_stationary_speedbound,ms_inmotion_speedbound,ms_fiddle_speedbound,ms_pedestrian_speedbound,ms_vehicle_speedbound,ms_walk_speedbound,ms_run_speedbound,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Client ID,Unknown Speedbound,Stationary Speedbound,Inmotion Speedbound,Fiddle Speedbound,Pedestrian Speedbound,Vehicle Speedbound,Walk Speedbound,Run Speedbound,Instance
            #Version 2: 
            #packet_type,version,timestamp_type,timestamp,client_req_id,ms_unknown_speedbound,ms_stationary_speedbound,ms_inmotion_speedbound,ms_fiddle_speedbound,ms_pedestrian_speedbound,ms_vehicle_speedbound,ms_walk_speedbound,ms_run_speedbound,ms_bike_speedbound,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Client ID,Unknown Speedbound,Stationary Speedbound,Inmotion Speedbound,Fiddle Speedbound,Pedestrian Speedbound,Vehicle Speedbound,Walk Speedbound,Run Speedbound,Bike Speedbound,Instance
            if ($#packet >= 3) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
            }
        }
        #LOG_SNS_DB_RESULT_C                => 0x17EE;
        elsif ($type == oct("0x17EE")) {
    
            #Version 1:
            #packet_type,version,timestamp_type,timestamp,input_type,input_distance_bound,input_cmc_motion_state,algo_state,prev_timestamp,prev_speed,prev_distance_bound,time_to_breach,session_key,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Input Distance Bound,Input CMC Motion State,Algorithm State,Previous Timestamp (ms),Previous Speed,Previous Distance Bound,Time to Breach,Session Key,Instance
            #Version 2:
            #packet_type,version,timestamp_type,timestamp,input_type,input_distance_bound,input_cmc_motion_state,input_cmc_motion_event,algo_state,prev_timestamp,prev_speed,prev_distance_bound,time_to_breach,session_key,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Input Distance Bound,Input CMC Motion State,Input CMC Motion Event,Algorithm State,Previous Timestamp (ms),Previous Speed,Previous Distance Bound,Time to Breach,Session Key,Instance
            if (($#packet >= 8) && ($packet[1] == 1)) {
               ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
               ($packet[8], $packet[2]) = format_timestamp($packet[8], $packet[2]);
               # Algorithm State => 0: inactive 1: active 
               $packet[7] = $lit_AlgoState{$packet[7]} if (defined($lit_AlgoState{$packet[7]}));
            }
            elsif (($#packet >= 9) && ($packet[1] == 2)) {
               ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
               ($packet[9], $packet[2]) = format_timestamp($packet[9], $packet[2]);
               # Algorithm State => 0: inactive 1: active 
               $packet[8] = $lit_AlgoState{$packet[8]} if (defined($lit_AlgoState{$packet[8]}));
               $packet[6] = $lit_cmc_motion_states{$packet[6]} if (defined($lit_cmc_motion_states{$packet[6]}));
               $packet[7] = $lit_cmc_motion_state_event{$packet[7]} if (defined($lit_cmc_motion_state_event{$packet[7]}));
            }
        }
        #LOG_SNS_DB_REPORT_C                => 0x17EF;
        elsif ($type == oct("0x17EF")) {
    
           #packet_type,version,timestamp_type,timestamp,distance_bound_breach_event,session_key,algo_inst_id
           #Packet,Version,Timestamp Type,Timestamp (ms),Distance Bound Breach Event,Session Key,Instance         
           if ($#packet >= 4) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = $lit_breach_event{$packet[4]} if (defined($lit_breach_event{$packet[4]}));
           }
        }
        #LOG_SNS_CMC_RESULT2_C              => 0x17F0;
        elsif ($type == oct("0x17F0")) {
    
            # Version 1:
            #packet_type,version,timestamp_type,timestamp,sa,rm,unfilp0,unfilp1,unfilp2,unfilp3,unfilp4,alpha0,alpha1,alpha2,alpha3,alpha4,beta0,beta1,beta2,beta3,beta4,filprob0,filprob1,filprob2,filprob3,filprob4,filprob5,filprob6,filprob7,motion_state_curr,motion_state_prev,motion_state_persist_time,motion_state_curr_probability,algo_inst_id           
            #Packet,Version,Timestamp Type,Timestamp (ms),SA,RM,unfilp0,unfilp1,unfilp2,unfilp3,unfilp4,alpha0,alpha1,alpha2,alpha3,alpha4,beta0,beta1,beta2,beta3,beta4,filprob0,filprob1,filprob2,filprob3,filprob4,filprob5,filprob6,filprob7,Current Motion State,Previous Motion State,Motion State Persist Time (s),Motion State Probability,Instance
            # Version 2:
            #packet_type,version,timestamp_type,timestamp,IQR,MODRM,MM3,DIFFSUM,DIFF10P,SA,SADIFF,LINACC[1],LINACC[2],LINACC[3],LINACCDIFF[1],LINACCDIFF[2],LINACCDIFF[3],SE 0 2 B[1],SE 0 2 B[2],SE 0 2 B[3],SE 2 4 B[1],SE 2 4 B[2],SE 2 4 B[3],SE 5 10 B[1],SE 5 10 B[2],SE 5 10 B[3],HIGHPEAKMAG B[1],HIGHPEAKMAG B[2],HIGHPEAKMAG B[3],HIGHPEAKLOC B[1],HIGHPEAKLOC B[2],HIGHPEAKLOC B[3],SPECENT B[1],SPECENT B[2],SPECENT B[3],MEANCROSSINGS B[1],MEANCROSSINGS B[2],MEANCROSSINGS B[3],GMM PROBABILITY[Walk],GMM PROBABILITY[Run],GMM PROBABILITY[Stationary],GMM PROBABILITY[Vehicle],GMM PROBABILITY[Bike],LR STAT DRIVE PROBABILITY[Stationary],LR STAT DRIVE PROBABILITY[Vehicle],LR WALK BIKE PROBABILITY[Walk],LR WALK BIKE PROBABILITY[Run],UNFILT GMM PROBABILITY[Walk],UNFILT GMM PROBABILITY[Run],UNFILT GMM PROBABILITY[Stationary],UNFILT GMM PROBABILITY[Vehicle],UNFILT GMM PROBABILITY[Bike],FILTERED PROBABILITY[Walk],FILTERED PROBABILITY[Run],FILTERED PROBABILITY[Stationary],FILTERED PROBABILITY[Vehicle],FILTERED PROBABILITY[Bike],HYST STABLE STATE,HYST TRANSITION STATE,HYST IS TRANSITION,HYST TRANSITION COUNT,EVENT REPORT TYPES[Walk],EVENT REPORT TYPES[Run],EVENT REPORT TYPES[Stationary],EVENT REPORT TYPES[Vehicle],EVENT REPORT TYPES[Bike],EVENT REPORT TYPES[Unknown],MOTION STATE EVENT[Walk],MOTION STATE EVENT[Run],MOTION STATE EVENT[Stationary],MOTION STATE EVENT[Vehicle],MOTION STATE EVENT[Bike],MOTION STATE EVENT[Unknown],MOTION STATE TIMESTAMP[Walk],MOTION STATE TIMESTAMP[Run],MOTION STATE TIMESTAMP[Stationary],MOTION STATE TIMESTAMP[Vehicle],MOTION STATE TIMESTAMP[Bike],MOTION STATE TIMESTAMP[Unknown],MOTION STATE PROBABILITY[Walk],MOTION STATE PROBABILITY[Run],MOTION STATE PROBABILITY[Stationary],MOTION STATE PROBABILITY[Vehicle],MOTION STATE PROBABILITY[Bike],MOTION STATE PROBABILITY[Unknown],OUTPUT MOTION STATE EVENT[Walk],OUTPUT MOTION STATE EVENT[Run],OUTPUT MOTION STATE EVENT[Stationary],OUTPUT MOTION STATE EVENT[Vehicle],OUTPUT MOTION STATE EVENT[Bike],OUTPUT MOTION STATE EVENT[Unknown],OUTPUT MOTION STATE TIMESTAMP[Walk],OUTPUT MOTION STATE TIMESTAMP[Run],OUTPUT MOTION STATE TIMESTAMP[Stationary],OUTPUT MOTION STATE TIMESTAMP[Vehicle],OUTPUT MOTION STATE TIMESTAMP[Bike],OUTPUT MOTION STATE TIMESTAMP[Unknown],OUTPUT MOTION STATE PROBABILITY[Walk],OUTPUT MOTION STATE PROBABILITY[Run],OUTPUT MOTION STATE PROBABILITY[Stationary],OUTPUT MOTION STATE PROBABILITY[Vehicle],OUTPUT MOTION STATE PROBABILITY[Bike],OUTPUT MOTION STATE PROBABILITY[Unknown],Instance
            #Packet,Version,Timestamp Type,Timestamp (ms),IQR,MODRM,MM3,DIFFSUM,DIFF10P,SA,SADIFF,LINACC[1],LINACC[2],LINACC[3],LINACCDIFF[1],LINACCDIFF[2],LINACCDIFF[3],SE 0 2 B[1],SE 0 2 B[2],SE 0 2 B[3],SE 2 4 B[1],SE 2 4 B[2],SE 2 4 B[3],SE 5 10 B[1],SE 5 10 B[2],SE 5 10 B[3],HIGHPEAKMAG B[1],HIGHPEAKMAG B[2],HIGHPEAKMAG B[3],HIGHPEAKLOC B[1],HIGHPEAKLOC B[2],HIGHPEAKLOC B[3],SPECENT B[1],SPECENT B[2],SPECENT B[3],MEANCROSSINGS B[1],MEANCROSSINGS B[2],MEANCROSSINGS B[3],GMM PROBABILITY[Walk],GMM PROBABILITY[Run],GMM PROBABILITY[Stationary],GMM PROBABILITY[Vehicle],GMM PROBABILITY[Bike],LR STAT DRIVE PROBABILITY[Stationary],LR STAT DRIVE PROBABILITY[Vehicle],LR WALK BIKE PROBABILITY[Walk],LR WALK BIKE PROBABILITY[Run],UNFILT GMM PROBABILITY[Walk],UNFILT GMM PROBABILITY[Run],UNFILT GMM PROBABILITY[Stationary],UNFILT GMM PROBABILITY[Vehicle],UNFILT GMM PROBABILITY[Bike],FILTERED PROBABILITY[Walk],FILTERED PROBABILITY[Run],FILTERED PROBABILITY[Stationary],FILTERED PROBABILITY[Vehicle],FILTERED PROBABILITY[Bike],HYST STABLE STATE,HYST TRANSITION STATE,HYST IS TRANSITION,HYST TRANSITION COUNT,EVENT REPORT TYPES[Walk],EVENT REPORT TYPES[Run],EVENT REPORT TYPES[Stationary],EVENT REPORT TYPES[Vehicle],EVENT REPORT TYPES[Bike],EVENT REPORT TYPES[Unknown],MOTION STATE EVENT[Walk],MOTION STATE EVENT[Run],MOTION STATE EVENT[Stationary],MOTION STATE EVENT[Vehicle],MOTION STATE EVENT[Bike],MOTION STATE EVENT[Unknown],MOTION STATE TIMESTAMP[Walk] (ms),MOTION STATE TIMESTAMP[Run] (ms),MOTION STATE TIMESTAMP[Stationary] (ms),MOTION STATE TIMESTAMP[Vehicle] (ms),MOTION STATE TIMESTAMP[Bike] (ms),MOTION STATE TIMESTAMP[Unknown] (ms),MOTION STATE PROBABILITY[Walk] (%),MOTION STATE PROBABILITY[Run] (%),MOTION STATE PROBABILITY[Stationary] (%),MOTION STATE PROBABILITY[Vehicle] (%),MOTION STATE PROBABILITY[Bike] (%),MOTION STATE PROBABILITY[Unknown] (%),OUTPUT MOTION STATE EVENT[Walk],OUTPUT MOTION STATE EVENT[Run],OUTPUT MOTION STATE EVENT[Stationary],OUTPUT MOTION STATE EVENT[Vehicle],OUTPUT MOTION STATE EVENT[Bike],OUTPUT MOTION STATE EVENT[Unknown],OUTPUT MOTION STATE TIMESTAMP[Walk] (ms),OUTPUT MOTION STATE TIMESTAMP[Run] (ms),OUTPUT MOTION STATE TIMESTAMP[Stationary] (ms),OUTPUT MOTION STATE TIMESTAMP[Vehicle] (ms),OUTPUT MOTION STATE TIMESTAMP[Bike] (ms),OUTPUT MOTION STATE TIMESTAMP[Unknown] (ms),OUTPUT MOTION STATE PROBABILITY[Walk] (%),OUTPUT MOTION STATE PROBABILITY[Run] (%),OUTPUT MOTION STATE PROBABILITY[Stationary] (%),OUTPUT MOTION STATE PROBABILITY[Vehicle] (%),OUTPUT MOTION STATE PROBABILITY[Bike] (%),OUTPUT MOTION STATE PROBABILITY[Unknown] (%),Instance
            if (($#packet >= 30) && ($packet[1] == 1)) {  # Version 1
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[29] = $lit_cmc_motion_states{$packet[29]} if (defined($lit_cmc_motion_states{$packet[29]}));
                $packet[30] = $lit_cmc_motion_states{$packet[30]} if (defined($lit_cmc_motion_states{$packet[30]}));
            }
            elsif (($#packet >= 102) && ($packet[1] == 2)) {  # Version 2
                $packet[59] = $lit_TrueFalse{$packet[59]} if (defined($lit_TrueFalse{$packet[59]}));
                foreach my $i (67..72, 85..90) {
                    $packet[$i] = $lit_cmc_motion_state_event{$packet[$i]} if (defined($lit_cmc_motion_state_event{$packet[$i]}));
                }
                foreach my $i (61..66) {
                    $packet[$i] = $lit_cmc_reporting_type{$packet[$i]} if (defined($lit_cmc_reporting_type{$packet[$i]}));
                }                    
                foreach my $i (57, 58) {
                    $packet[$i] = $lit_cmc_motion_states{$packet[$i]} if (defined($lit_cmc_motion_states{$packet[$i]}));
                }
                foreach my $i (73..78, 91..96) {
                    ($packet[$i], my $t) = format_timestamp($packet[$i], "DSPS");
                }
                foreach my $i (79..84, 97..102) {
                    $packet[$i] = 100 * $packet[$i];   # Probability
                }                    
            }
        }
        #LOG_SNS_LATENCY_SAMPLING_POLL_C    => 0x17FB;
        elsif ($type == oct("0x17FB")) {
    
           #packet_type,version,timestamp,sensor_id,data_timestamp,sampling_latency,polling_latency
           #Packet,Version,Timestamp (ms),Sensor ID,Data Timestamp (ms),Sampling Latency (ms),Polling Latency (ms)
           if ($#packet >= 6) {
                 # Time stamp in clock ticks when log packet is configured
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");    
                 # Sensor providing the data
              $packet[3] = $lit_DriverSensorID{$packet[3]} if (defined($lit_DriverSensorID{$packet[3]}));
                 # Time stamp in clock ticks when first sample received
              ($packet[4], $t) = format_timestamp($packet[4], "DSPS");       
                 # Sampling latency under polling mode in unit of sclk ticks(32KHz), defined as time between Device driver receiving a 
                 # request from SMGR and device driver time stamping the sample received from the physical sensor
              ($packet[5], $t) = format_timestamp($packet[5], "DSPS");   
                 # Whole latency in unit of sclk ticks (32KHz) from timer interrupt to sensors’ data gets generated and timestamped 
              ($packet[6], $t) = format_timestamp($packet[6], "DSPS");
           }
        }
        #LOG_SNS_LATENCY_SAMPLING_DRI_C     => 0x17FC;
        elsif ($type == oct("0x17FC")) {
    
           #packet_type,version,timestamp,sensor_id,data_timestamp,sampling_latency,dri_get_data_latency
           #Packet,Version,Timestamp (ms),Sensor ID,Data Timestamp (ms),Sampling Latency (ms),DRI Get Data Latency (ms)
           if ($#packet >= 6) {
                 # Time stamp in clock ticks when log packet is configured
              ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
                 # Sensor providing the data 
              $packet[3] = $lit_DriverSensorID{$packet[3]} if (defined($lit_DriverSensorID{$packet[3]}));
                 # Time stamp in clock ticks when first sample received
              ($packet[4], $t) = format_timestamp($packet[4], "DSPS");
                 # Sampling latency under DRI mode in unit of sclk ticks (32KHz), defined as time between SMGR receiving a
                 # data ready interrupt and device driver time stamping the sample received from the physical sensor
              ($packet[5], $t) = format_timestamp($packet[5], "DSPS");
                 # Latency in unit of sclk ticks (32KHz) from smgr calling get_data under DRI mode to sensors’ data gets generated and timestamped
              ($packet[6], $t) = format_timestamp($packet[6], "DSPS");
           }
        }
        #LOG_SNS_LATENCY_DELIVERY_C         => 0x17FD;
        elsif ($type == oct("0x17FD")) {
    
           #packet_type,version,timestamp,sensor_id,data_timestamp,delivery_latency
           #Packet,Version,Timestamp (ms),Sensor ID,Data Timestamp (ms),Delivery Latency (ms)
           if ($#packet >= 5) {
                 # Timestamp in apps nanosecond clock ticks when log packet is configured
              ($packet[2], my $t) = format_timestamp($packet[2], "NANO");
                 # Sensor providing the data 
              $packet[3] = $lit_SensorID{$packet[3]} if (defined($lit_SensorID{$packet[3]}));
                 # Timestamp in DSPS clock ticks when first sample received (NOTE! Currently, the packets report data timestamp in nanoseconds, this must change!!!)
              ($packet[4], $t) = format_timestamp($packet[4], "NANO");
                 # Delivery latency from sensor driver time stamping the sample to the moment HAL sends SensorEvent containing the sample in unit of nanosecond
              ($packet[5], $t) = format_timestamp($packet[5], "NANO");
           }
        }
        #LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C   => 0x17FE;
        elsif ($type == oct("0x17FE")) {
    
           #packet_type,version,timestamp_type,timestamp,report_period,sample_rate,coordinate_sys,abs_rest_gyro_az_tilt_tc,rel_rest_gyro_az_tilt_tc,motion_gyro_az_tilt_tc,gyro_noise_threshold,max_gyro_az_tilt_freeze,max_gyro_az_tilt_reset,algo_inst_id";
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Coordinate System,Abs Rest Gyro AZ Tilt,Rel Rest Gyro AZ Tilt,Motion Gyro AZ Tilt,Gyro Noise Threshold,Max Gyro AZ Tilt Freeze,Max Gyro AZ Tilt Reset,Instance";
           if ($#packet >= 6) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..5) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[6] = $lit_rotvCoordSys{$packet[6]} if (defined($lit_rotvCoordSys{$packet[6]}));
           }
        }
        #LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C   => 0x17FF;
        elsif ($type == oct("0x17FF")) {
    
           #packet_type,version,timestamp_type,timestamp,grav_x,grav_y,grav_z,gravity_accuracy,gravity_timestamp,gravity_dev_mot_state,gyro_quat0,gyro_quat1,gyro_quat2,gyro_quat3,gyro_quat_timestamp,grv0,grv1,grv2,grv3,accuracy,coordinate_sys,algo_inst_id";
           #Packet,Version,Timestamp Type,Timestamp (ms),Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Gravity Accuracy,Gravity Timestamp (ms),Gravity Motion State,Quat0,Quat1,Quat2,Quat3,Quat Timestamp (ms),GRV0,GRV1,GRV2,GRV3,Accuracy,Coordinate System,Instance";
           if ($#packet >= 20) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[7] = $lit_SamAccuracy{$packet[7]} if (defined($lit_SamAccuracy{$packet[7]}));
              ($packet[8], $packet[2]) = format_timestamp($packet[8], $packet[2]);
              $packet[9] = $lit_gravMotionStates{$packet[9]} if (defined($lit_gravMotionStates{$packet[9]}));
              ($packet[14], $packet[2]) = format_timestamp($packet[14], $packet[2]);
              $packet[19] = $lit_SamAccuracy{$packet[19]} if (defined($lit_SamAccuracy{$packet[19]}));
              $packet[20] = $lit_rotvCoordSys{$packet[20]} if (defined($lit_rotvCoordSys{$packet[20]}));
           }
        }
        #LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C   => 0x1800;
        elsif ($type == oct("0x1800")) {
    
           #packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,grv0,grv1,grv2,grv3,accuracy,coordinate_sys,algo_inst_id";
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,GRV0,GRV1,GRV2,GRV3,Accuracy,Coordinate System,Instance";
           if ($#packet >= 12) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[11] = $lit_SamAccuracy{$packet[11]} if (defined($lit_SamAccuracy{$packet[11]}));
              $packet[12] = $lit_rotvCoordSys{$packet[12]} if (defined($lit_rotvCoordSys{$packet[12]}));
           }
        }
        #LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C    => 0x183A;
        elsif ($type == oct("0x183A")) {
      
           #packet_type,version,timestamp_type,timestamp,report_period,sample_rate,accel_filter_tc,mag_filter_tc,motion_detect_period,abs_rest_var_thresh,coord_sys,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report Period (s),Sample Rate (Hz),Accel Filter Time Const (ms),Mag Filter Time Const (ms),Motion Detect Period (s),Abs Rest Variance Threshold (m/s/s)^2,Coordinate System,Instance
           if ($#packet >= 10) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = convert_Q16_to_decimal($packet[4]);
              $packet[5] = convert_Q16_to_decimal($packet[5]);
              $packet[10] = $lit_rotvCoordSys{$packet[10]} if (defined($lit_rotvCoordSys{$packet[10]}));
           }
        }
        #LOG_SNS_GEOMAG_ROT_VEC_RESULT_C    => 0x183B;
        elsif ($type == oct("0x183B")) {
          
           #packet_type,version,timestamp_type,timestamp,accel_x,accel_y,accel_z,gravity_x,gravity_y,gravity_z,lin_accel_x,lin_accel_y,lin_accel_z,gravity_accuracy,gravity_timestamp,fmv_x,fmv_y,fmv_z,fmv_accuracy,fmv_timestamp,rotva,rotvb,rotvc,rotvd,rotv_accuracy,coord_sys,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),Gravity Accuracy,Gravity Timestamp (ms),FMV X (Gs),FMV Y (Gs),FMV Z (Gs),FMV Accuracy,FMV Timestamp (ms),RotV0,RotV1,RotV2,RotV3,RotV Accuracy,Coordinate System,Instance
           if ($#packet >= 25) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              foreach my $i (4..6) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[13] = $lit_SamAccuracy{$packet[13]} if (defined($lit_SamAccuracy{$packet[13]}));
              ($packet[14], $packet[2]) = format_timestamp($packet[14], $packet[2]);
              $packet[18] = $lit_SamAccuracy{$packet[18]} if (defined($lit_SamAccuracy{$packet[18]}));
              ($packet[19], $packet[2]) = format_timestamp($packet[19], $packet[2]);
              $packet[24] = $lit_SamAccuracy{$packet[24]} if (defined($lit_SamAccuracy{$packet[24]}));
              $packet[25] = $lit_rotvCoordSys{$packet[25]} if (defined($lit_rotvCoordSys{$packet[25]}));
           }
        }
        #LOG_SNS_GEOMAG_ROT_VEC_REPORT_C    => 0x183C;
        elsif ($type == oct("0x183C")) {
      
           #packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,rotva,rotvb,rotvc,rotvd,gravity_x,gravity_y,gravity_z,lin_accel_x,lin_accel_y,lin_accel_z,rotv_accuracy,gravity_accuracy,coord_sys,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,RotV0,RotV1,RotV2,RotV3,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Linear Accel X (m/s/s),Linear Accel Y (m/s/s),Linear Accel Z (m/s/s),RotV Accuracy,Gravity Accuracy,Coordinate System,Instance
           if ($#packet >= 19) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
              $packet[17] = $lit_SamAccuracy{$packet[17]} if (defined($lit_SamAccuracy{$packet[17]}));
              $packet[18] = $lit_SamAccuracy{$packet[18]} if (defined($lit_SamAccuracy{$packet[18]}));
              $packet[19] = $lit_rotvCoordSys{$packet[19]} if (defined($lit_rotvCoordSys{$packet[19]}));
           }
        }
        #LOG_SNS_PED_ALIGN_CONFIG_C       => 0x186C;
        elsif ($type == oct("0x186C")) {
      
           #packet_type,version,timestamp_type,timestamp,rv_input,cog_sample_rate,rv_sample_rate,sensor_report_rate,cog_averaging_interval,instance
           #Packet,Version,Timestamp Type,Timestamp (ms),RotV Input,Course-over-Ground (COG) Sample Rate (Hz),RotV Sample Rate (Hz),Sensor Repot Rate (Hz),Course-over-Ground (COG) Averaging Interval (Steps),Instance
           if ($#packet >= 7) {
              ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
              $packet[4] = $lit_rotv_algorithm{$packet[4]} if (defined($lit_rotv_algorithm{$packet[4]}));
              foreach my $i (5..7) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
           }
        }
        #LOG_SNS_PED_ALIGN_RESULT1_C      => 0x186D;
        elsif ($type == oct("0x186D")) {
      
           #packet_type,version,input_type,timestamp,accel_x,accel_y,accel_z,rotva,rotvb,rotvc,rotvd,rv_accuracy,instance
           #Packet,Version,Input Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),RotV0,RotV1,RotV2,RotV3,RotV Accuracy,Instance
           if ($#packet >= 11) {
              $packet[2] = $lit_PALNInputType{$packet[2]} if (defined($lit_PALNInputType{$packet[2]}));
              ($packet[3], my $t) = format_timestamp($packet[3], "DSPS");
              foreach my $i (4..6) {
                 $packet[$i] = convert_Q16_to_decimal($packet[$i]);
              }
              $packet[11] = $lit_SamAccuracy{$packet[11]} if (defined($lit_SamAccuracy{$packet[11]}));
           }         
        }
        #LOG_SNS_PED_ALIGN_RESULT2_C      => 0x186E;
        elsif ($type == oct("0x186E")) {
      
           #packet_type,version,timestamp,unfiltered_cog_angle,cog_angle,cog_accuracy,relative_turn_angle,last_alignment_change_ts,events,instance,rta_accuracy
           #Packet,Version,Timestamp (ms),Unfiltered CoG Angle (Deg),CoG Angle (Deg),CoG Accuracy (Deg),Relative Turn Angle (Deg),Last Alignment Change Timestamp (ms),Events,Instance,RTA Accuracy (Deg)
            if ($#packet >= 9) {  # Version 1 & 2 packets
                ($packet[3], my $t) = format_timestamp($packet[3], "DSPS");
                foreach my $i (3..6) {
                   $packet[$i] = convert_rad_to_deg($packet[$i]);
                }
                ($packet[7], $t) = format_timestamp($packet[7], "DSPS");
                $packet[8] = $lit_PALN_Events{$packet[8]} if (defined($lit_PALN_Events{$packet[8]}));
            }
            if ($#packet >= 10) {       # Version 2 packets
                $packet[10] = convert_rad_to_deg($packet[10]);
            }  
        }
        #LOG_SNS_PED_ALIGN_REPORT_C       => 0x186F;
        elsif ($type == oct("0x186F")) {
      
           #packet_type,version,timestamp,instance,client_id,report_id,cog_angle,cog_accuracy,relative_turn_angle,last_alignment_change_ts,events,rta_accuracy
           #Packet,Version,Timestamp (ms),Instance,Client ID,Report ID,CoG Angle (Deg),CoG Accuracy (Deg),Relative Turn Angle (Deg),Last Alignment Change Timestamp (ms),Events,RTA Accuracy (Deg)
            if ($#packet >= 10) {    # Version 1 & 2 packets
                ($packet[2], my $t) = format_timestamp($packet[2], "DSPS");
                foreach my $i (6..8) {
                    $packet[$i] = convert_rad_to_deg($packet[$i]);
                }
                ($packet[9], $t) = format_timestamp($packet[9], "DSPS");
                $packet[10] = $lit_PALN_Events{$packet[10]} if (defined($lit_PALN_Events{$packet[10]}));
            }
            if ($#packet >= 11) {       # Version 2 packets has RTA accuracy field
                $packet[11] = convert_rad_to_deg($packet[11]);
            }             
        }
        #LOG_SNS_TILT_DETECTOR_CONFIG_C
        elsif ($type == oct("0x1887")) {
      
            #packet_type,version,timestamp_type,timestamp,sample_rate,angle_threshold,init_accel_window_time,accel_window_time,instance
            #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Angle Threshold (Deg),Initial Accel Window Time (s),Current Accel Window Time (s),Instance
            if ($#packet >= 5) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[5] = convert_rad_to_deg($packet[5]);
            }   
        }
        #LOG_SNS_TILT_DETECTOR_RESULT_C
        elsif ($type == oct("0x1888")) {
      
            #packet_type,version,timestamp_type,timestamp,accel_x,accel_y,accel_z,accel_timestamp,dprod_threshold,gravity_x,gravity_y,gravity_z,instance
            #Packet,Version,Timestamp Type,Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Accel Timestamp (ms),Dot-Product Threshold,Gravity X (m/s/s),Gravity Y (m/s/s),Gravity Z (m/s/s),Instance
            if ($#packet >= 7) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                foreach my $i (4..6) {
                    $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                }
                ($packet[7], my $t) = format_timestamp($packet[7], "DSPS");
            }   
        }
        #LOG_SNS_TILT_DETECTOR_REPORT_C
        elsif ($type == oct("0x1889")) {
    
            #packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,event_timestamp,ref_gravity_x,ref_gravity_y,ref_gravity_z,instance
            #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Event Timestamp (ms),New Reference Gravity X (m/s/s),New Reference Gravity Y (m/s/s),New Reference Gravity Z (m/s/s),Instance  
            if ($#packet >= 7) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                ($packet[7], my $t) = format_timestamp($packet[7], "DSPS");
                $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
            }   
        }
        #LOG_SNS_UIMAGE
        elsif ($type == oct("0x188D")) {
            
            #packet_type,version,client_vote,state_vote_ts,bigimage_entry_ts,last_uimg_vote_ts,first_uimg_entry_ts,time_spent_in_uimg,num_exits_from_uimg
            #Packet,Version,Client Vote,State Vote Timestamp (ms),Big Image Entry Timestamp (ms),Last uImage Vote Timestamp (ms),First uImage Entry Timestamp (ms),Time Spent in uImage (ms),Number of Exits from uImage,System Vote,Client 0 Vote (Utils?),Client 1 Vote (SMGR?),Client 2 Vote (RH?),Client 3 Vote (SAM?),uImage Entry Latency (ms)
            if ($#packet >= 8) {
                foreach my $i (3..7) {
                    ($packet[$i], my $t) = format_timestamp($packet[$i], "DSPS");
                }
                $packet[9] = $packet[2] & 0xf;
                $packet[10] = ($packet[2] >> 4) & 0xf;
                $packet[11] = ($packet[2] >> 8) & 0xf;
                $packet[12] = ($packet[2] >> 12) & 0xf;
                $packet[13] = ($packet[2] >> 16) & 0xf;
                $packet[2] = sprintf("0x%x",$packet[2]);  # Convert decimal to hex
                
                $packet[14] = 0;
                if ($packet[9] == 2) {      # uImage entry latency
                    $packet[14] = $packet[6] - $packet[5] if (($packet[6] - $packet[5]) > 0);
                }                
                
                foreach my $i (9..13) {
                    $packet[$i] = $lit_uImageVote{$packet[$i]} if (defined($lit_uImageVote{$packet[$i]}));
                }
            }            
        }
        #LOG_SNS_DPC_CONFIG_C
        elsif ($type == oct("0x189B")) {
            
            # Version 1 packet
            ##packet_type,version,timestamp_type,timestamp,accel_sample_rate,proximity_sample_rate,sensor_report_rate,algo_inst_id
            ##Packet,Version,Timestamp Type,Timestamp (ms),Accel Sample Rate (Hz),Proximity Sample Rate (Hz),Sensor Sample Rate (Hz),Instance
            #if ($#packet >= 7) {
            #    ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
            #    foreach my $i (4..6) {
            #        $packet[$i] = convert_Q16_to_decimal($packet[$i]);
            #    }
            #}
            
            #packet_type,version,timestamp_type,timestamp,accel_sample_rate,proximity_sample_rate,mdIntAvailable,suppress_samps,hidden_hidden_hyst_time,angle_static_alpha,proximity_check_window_length,tiltparams_pickup_margin,tiltparams_pickup_min,tiltparams_stable_t,max_tilt_facing_sep,face_position_detection_tau
            #Packet,Version,Timestamp Type,Timestamp (ms),Accel Sample Rate (Hz),Proximity Sample Rate (Hz),Motion Detect Interrupt Available,Suppress Samples (# of samples),Hidden Hidden Hyst Time (# of samples),Angle Static Alpha,Proximity Check Window Length (# of samples),Tiltparams Pickup Margin,Tiltparams Pickup Min,Tiltparams Stable t,Max Tilt Facing Sep (# of samples),Face Position Detection Tau
            if ($#packet >= 15) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                foreach my $i (4..5) {
                    $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                }
            }
        }
        #LOG_SNS_DPC_RESULT_C
        elsif ($type == oct("0x189C")) {

            ## Version 1 packet
            ##packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,proximity,device_position,desk_entry_detector_op_state,desk_entry_detector_state,desk_entry_detector_on_desk_entry_time,desk_entry_detector_unknown_entry_time,desk_exit_detector_op_state,pocket_entry_detector_op_state,pocket_entry_detector_state,pocket_entry_detector_in_pocket_entry_time,pocket_entry_detector_unknown_entry_time,pocket_entry_detector_prev_proximity,pocket_exit_detector_op_state,pocket_exit_detector_state,pocket_exit_detector_prev_proximity,pocket_exit_detector_prox_near_to_far_trans_time,pocket_exit_detector_unknown_entry_time,algo_inst_id
            ##Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Proximity,Device Position,Desk Entry Detector Op State,Desk Entry Detector State,Desk Entry Detector on Desk Entry Time,Desk Entry Detector Unknown Entry Time,Desk Exit Detector Op State,Pocket Entry Detector Op State,Pocket Entry Detector State,Pocket Entry Detector in Pocket Entry Time,Pocket Entry Detector Unknown Entry Time,Pocket Entry Detector Prev Proximity,Pocket Exit Detector Op State,Pocket Exit Detector State,Pocket Exit Detector Prev Proximity,Pocket Exit Detector Prox Near to Far Trans Time,Pocket Exit Detector Unknown Entry Time,Instance
            #if ($#packet >= 25) {
            #    ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
            #    $packet[4] = $lit_DPC_InputTypes{$packet[4]} if (defined($lit_DPC_InputTypes{$packet[4]}));
            #    $packet[9] = $lit_DPC_DevicePositions{$packet[9]} if (defined($lit_DPC_DevicePositions{$packet[9]}));
            #    foreach my $i (5..7) {
            #        if (length($packet[$i]) == 0) {
            #            $packet[$i] = 0;
            #        } else {
            #            $packet[$i] = convert_Q16_to_decimal($packet[$i]);
            #        }
            #    }
            #    foreach my $i (8,19,22) {
            #        if (length($packet[$i]) == 0) {
            #            $packet[$i] = "N/A";
            #        } else {
            #            $packet[$i] = $lit_Proximity{$packet[$i]} if (defined($lit_Proximity{$packet[$i]}));
            #        }
            #    }
            #    foreach my $i (12,13,17,18,23,24) {
            #        ($packet[12], my $t) = format_timestamp($packet[12], "DSPS");
            #    }
            #    foreach my $i (10,14,15,20) {
            #        $packet[$i] = $lit_DPC_DetectorOpState{$packet[$i]} if (defined($lit_DPC_DetectorOpState{$packet[$i]}));
            #    }
            #    foreach my $i (11,16,21) {
            #        $packet[$i] = $lit_DPC_DetectorState{$packet[$i]} if (defined($lit_DPC_DetectorState{$packet[$i]}));
            #    }
            #}
            
            #packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,proximity,amd_motion_status,device_position,device_position_timestamp,face_position,face_position_timestamp,tilt,tilt_timestamp,tilt_suppress_ctr,proximity_last_go_far_time,proximity_last_go_near_time,accelStatus,dpc_output,dpc_output_timestamp,prox_state,dpc_ready,tilt_last_go_one_timestamp,facing_algo_last_go_one_timestamp,hidden_last_seen_timestamp,compute_on_this_samp,is_stable,buff_idx,samp_count,dpc_event_generated,motion_status,static_angle_count,stream_period,flat_static_flag,proxStatus,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Proximity,AMD State,Device Position,Device Position Timestamp (ms),Face Position,Face Position Timestamp (ms),Tilt,Tilt Timestamp (ms),Tilt Suppress Ctr,Proximity Last Go Far Time (ms),Proximity Last Go Near Time (ms),Accel Status,DPC Output,DPC Output Timestamp (ms),Proximity State,DPC Ready,Tilt Last Go One Timestamp (ms),Facing Algo Last Go One Timestamp (ms),Hidden Last Seen Timestamp (ms),Compute on this Sample,Is Stable,Buff idx,Sample Count,DPC Event Generated,Motion Status,Static Angle Count,Stream Period,Flat Static Flag,Proximity Status,Instance
            if ($#packet >= 37) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[4] = $lit_DPC_InputTypes{$packet[4]} if (defined($lit_DPC_InputTypes{$packet[4]}));
                $packet[10] = $lit_DPC_DevicePositions_v2{$packet[10]} if (defined($lit_DPC_DevicePositions_v2{$packet[10]}));
                $packet[12] = $lit_DPC_DetectionStatus{$packet[12]} if (defined($lit_DPC_DetectionStatus{$packet[12]})); # Face
                $packet[14] = $lit_DPC_DetectionStatus{$packet[14]} if (defined($lit_DPC_DetectionStatus{$packet[14]})); # TILT
                $packet[19] = $lit_DPC_AccelStatus{$packet[19]} if (defined($lit_DPC_AccelStatus{$packet[19]}));
                $packet[36] = $lit_DPC_ProxStatus{$packet[36]} if (defined($lit_DPC_ProxStatus{$packet[36]}));
                foreach my $i (5..7) {
                    if (length($packet[$i]) == 0) {
                        $packet[$i] = 0;
                    } else {
                        $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                    }
                }
                foreach my $i (8,22) {
                    if (length($packet[$i]) == 0) {
                        $packet[$i] = "N/A";
                    } else {
                        $packet[$i] = $lit_Proximity{$packet[$i]} if (defined($lit_Proximity{$packet[$i]}));
                    }
                }
                foreach my $i (9,32) {
                    if (length($packet[$i]) == 0) {
                        $packet[$i] = "N/A";
                    } else {
                        $packet[$i] = $lit_qmdMotionStates{$packet[$i]} if (defined($lit_qmdMotionStates{$packet[$i]}));
                    }
                }
                foreach my $i (23,27,28,31,35) {
                    $packet[$i] = $lit_TrueFalse{$packet[$i]} if (defined($lit_TrueFalse{$packet[$i]}));
                }
                foreach my $i (11,13,15,17,18,21,24,25,26) {
                    ($packet[$i], my $t) = format_timestamp($packet[$i], "DSPS");
                }
            }
        }
        #LOG_SNS_DPC_REPORT_C
        elsif ($type == oct("0x189D")) {
            
            # Version 1 & 2
            #packet_type,version,timestamp_type,timestamp,dpc_event,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),DPC Event,Instance
            if ($#packet >= 5) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                # Different DPC events for v1 and v2
                if ($packet[1] == 1) {
                    $packet[4] = $lit_DPC_Events{$packet[4]} if (defined($lit_DPC_Events{$packet[4]}));
                } else {
                    $packet[4] = $lit_DPC_Events_v2{$packet[4]} if (defined($lit_DPC_Events_v2{$packet[4]}));
                }
            }   
        }
        
        #LOG_SNS_TILT_W_DETECTOR_CONFIG_C
        elsif ($type == oct("0x18B7")) {
            
            #packet_type,version,timestamp_type,timestamp,sample_rate,filter_window_seconds,accel_window_seconds,window_for_end_accel_stability_check_seconds,min_delta_pitch_threshold_deg,min_end_pitch_threshold_deg,max_end_roll_threshold_deg,max_end_accel_spread_threshold,max_end_accel_norm_deviation_from_g_threshold,adaptive_filter_tc_seconds,tilt_threshold_motion_noise_coeff,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate (Hz),Filter Window (s),Accel Window (s),Window for End Accel Stability Check (s),Min Delta Pitch Threshold (deg),Min End Pitch Threshold (deg),Max End Roll Threshold (deg),Max End Accel Spread Threshold,Max End Accel Norm Deviation from g Threshold,Adaptive Filter TC (s),Tilt Threshold Motion Noise Coeff,Instance
            if ($#packet >= 4) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[4] = convert_Q16_to_decimal($packet[4]);
            } 
        }
        #LOG_SNS_TILT_W_DETECTOR_RESULT_C
        elsif ($type == oct("0x18B8")) {
            
            #packet_type,version,timestamp_type,timestamp,input_type,accelX,accelY,accelZ,amd_state,input_ts,event_ts,delta_acc_squared_filtered,cur_roll_in_range,cur_pitch_in_range,cur_accel_norm_in_range,cur_pos_is_stable,is_sufficient_tilt,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),AMD State,Input Timestamp (ms),Event Timestamp (ms),Delta ACC Squared Filtered,Cur Roll in Range,Cur Pitch in Range,Cur Accel Norm in Range,Cur Pos is Stable,Is Sufficient Tilt,Instance
            if ($#packet >= 10) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[4] = $lit_Tilt_InputType{$packet[4]} if (defined($lit_Tilt_InputType{$packet[4]}));
                foreach my $i (5..7) {
                    if (length($packet[$i]) == 0) {
                        $packet[$i] = 0;
                    } else {
                        $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                    }
                }
                $packet[8] = $lit_qmdMotionStates{$packet[8]} if (defined($lit_qmdMotionStates{$packet[8]}));
                foreach my $i (9..10) {
                    ($packet[$i], my $t) = format_timestamp($packet[$i], "DSPS");
                }                
            }  
        }
        #LOG_SNS_TILT_W_DETECTOR_REPORT_C
        elsif ($type == oct("0x18B9")) {
            
            #packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,event_timestamp,accelX,accelY,accelZ,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,Event Timestamp (ms),Accel X (m/s/s),Accel Y (m/s/s),Accel Z (m/s/s),Instance
            if ($#packet >= 10) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
                ($packet[7], my $t) = format_timestamp($packet[7], "DSPS");
                foreach my $i (8..10) {
                    $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                }                
            }  
        }
        #LOG_SNS_QHEART_CONFIG_C
        elsif ($type == oct("0x18BA")) {
            
            #packet_type,version,timestamp_type,timestamp,sample_rate_ppg,sample_rate_accel,update_interval_in_fft_samples,max_alpha,min_alpha,min_oh,max_oh,max_del_b,acc_peak_distance,ppg_peak_distance,num_ppg_peaks,num_acc_peaks,peak_width_ppg,peak_thresh_ppg,peak_thresh_acc,max_ind_diff,max_acc_thr,harm_acc_thr,globalminhr,globalmaxhr,noaccel_thresh,accuracy_decay_alpha,android_accuracy_low_thresh,android_accuracy_high_thresh,android_accuracy_medium_thresh,do_minppg,do_mingoodppgtrack,do_width_harm,do_stride_is_hr_processing,is_one_shot,report_interval,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Sample Rate PPG (Hz),Sample Rate Accel (Hz),Update Interval in FFT Samples,Max Alpha,Min Alpha,Min OH,Max OH,Max Del B,Acc Peak Distance,PPG Peak Distance,Num PPG Peaks,Num Acc Peaks,Peak Width PPG,Peak Thresh PPG,Peak Thresh Acc,Max Ind Diff,Max Acc Thr,Harm Acc Thr,Globalminhr,Globalmaxhr,NoAccel Thresh,Accuracy Decay Alpha,Android Accuracy Low Thresh,Android Accuracy High Thresh,Android Accuracy Medium Thresh,Do Minppg,Do Mingoodppgtrack,Do Width Harm,Do Stride is HR Processing,Is One Shot,Report Interval (ms),Instance
            if ($#packet >= 34) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                foreach my $i (4..5) {
                    $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                }
                ($packet[34], my $t) = format_timestamp($packet[34], "DSPS");
            } 
        }
        #LOG_SNS_QHEART_RESULT_C
        elsif ($type == oct("0x18BB")) {
            
            #packet_type,version,timestamp_type,timestamp,input_type,sensor_data0,sensor_data1,sensor_data2,sensor_time,bpm,bpm_time,bpm_updated,bpm_quality,num_found_ppg_peaks,num_found_acc_peaks,prior_smooth_bpm,prior_smooth_harmppg,harmacc,harmpow,acc_pow_fft,locspeak,harmppg,smooth_harmppg,harmppg_save,raw_bpm,smooth_bpm,state_bpm_quality,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Input Type,Sensor Data X,Sensor Data Y, Sensor Data Z,Sensor Timestamp (ms),BPM,BPM Timestamp (ms),BPM Updated,BPM Quality,Num Found PPG Peaks,Num Found Acc Peaks,Prior Smooth BPM,Prior Smooth Harmppg,Harmacc,Harmpow,Acc Pow FFT,Locspeak,Harmppg,Smooth Harmppg,Harmppg Save,Raw BPM,Smooth BPM,State BPM Quality,Instance
            if ($#packet >= 12) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[4] = $lit_QHeart_InputType{$packet[4]} if (defined($lit_QHeart_InputType{$packet[4]}));
                foreach my $i (5..7) {
                    $packet[$i] = convert_Q16_to_decimal($packet[$i]);
                }
                ($packet[8], my $t) = format_timestamp($packet[8], "DSPS");
                ($packet[10], $t) = format_timestamp($packet[10], "DSPS");
                $packet[11] = $lit_BPM_Updated{$packet[11]} if (defined($lit_BPM_Updated{$packet[11]}));
                $packet[12] = $lit_BPM_Quality{$packet[12]} if (defined($lit_BPM_Quality{$packet[12]}));
            } 
        }
        #LOG_SNS_QHEART_REPORT_C
        elsif ($type == oct("0x18BC")) {
            
            #packet_type,version,timestamp_type,timestamp,report_id,report_type,client_id,bpm,bpm_time,bpm_updated,bpm_quality,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,Client ID,BPM,BPM Timestamp (ms),BPM Updated,BPM Quality,Instance
            if ($#packet >= 10) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
                ($packet[8], my $t) = format_timestamp($packet[8], "DSPS");
                $packet[9] = $lit_BPM_Updated{$packet[9]} if (defined($lit_BPM_Updated{$packet[9]}));
                $packet[10] = $lit_BPM_Quality{$packet[10]} if (defined($lit_BPM_Quality{$packet[10]}));
            }   
        }
        #LOG_SNS_SYNC_PROXY_CLIENT_C"
        elsif ($type == oct("0x18C2")) {
            
            #packet_type,version,qtimer_freq,req_num_sync_schedules,supported_num_sync_schedules,schedule1_time,schedule1_interval,schedule2_time,schedule2_interval,schedule3_time,schedule3_interval,schedule4_time,schedule4_interval,schedule5_time,schedule5_interval,schedule6_time,schedule6_interval,schedule7_time,schedule7_interval,schedule8_time,schedule8_interval,schedule9_time,schedule9_interval,schedule10_time,schedule10_interval,req_rest_to_motion_latency,req_motion_to_rest_latency,client_time,client_state,motion_state_time,motion_state
            #Packet,Version,QTimer Frequency (Hz),Request Num Sync Schedules,Supported Num Sync Schedules,Schedule 1 Wakeup (s),Schedule 1 Interval (s),Schedule 2 Wakeup (s),Schedule 2 Interval (s),Schedule 3 Wakeup (s),Schedule 3 Interval (s),Schedule 4 Wakeup (s),Schedule 4 Interval (s),Schedule 5 Wakeup (s),Schedule 5 Interval (s),Schedule 6 Wakeup (s),Schedule 6 Interval (s),Schedule 7 Wakeup (s),Schedule 7 Interval (s),Schedule 8 Wakeup (s),Schedule 8 Interval (s),Schedule 9 Wakeup (s),Schedule 9 Interval (s),Schedule 10 Wakeup (s),Schedule 10 Interval (s),Requested Rest to Motion Latency (s),Requested Motion to Rest Latency (s),Client Receives Motion Indication (s),Client State When Recieving Ind,Motion State Timestamp (ms),Motion State
            if ($#packet >= 30) {
                foreach my $i (5..27) { 
                    $packet[$i] = $packet[$i] / $packet[2];     # Convert QTimer ticks into seconds.
                }
                $packet[28] = $lit_Processor_state{$packet[28]} if (defined($lit_Processor_state{$packet[28]}));
                ($packet[29], my $t) = format_timestamp($packet[29], "DSPS");
                $packet[30] = $lit_qmdMotionStates{$packet[30]} if (defined($lit_qmdMotionStates{$packet[30]}));
            }  
        }
        #LOG_SNS_IOD_CONFIG_C
        elsif ($type == oct("0x1918")) {
            
            #packet_type,version,timestamp_type,timestamp,confidence_threshold1,confidence_threshold2,time_of_day,sunset_timestamps,sunrise_timestamps,iod_calibration_value,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Confidence Threshold 0,Confidence Threshold 1,Time of Day (s),Sunset Timestamp (s),Sunrise Timestamp(s),IOD Calibration Value,Instance
            if ($#packet >= 10) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);                
            }   
        }
        #LOG_SNS_IOD_RESULT_C
        elsif ($type == oct("0x1919")) {
            
            #packet_type,version,timestamp_type,timestamp,gmm_likelihood1,gmm_likelihood2,hmm_parameter_selection_priors1,hmm_parameter_selection_priors2,hmm_transition_state,hmm_transition_matrix1,hmm_transition_matrix2,hmm_transition_matrix3,hmm_transition_matrix4,previous_time_of_day,posterior_probability1,posterior_probability2,prior_iod_state_probability1,prior_iod_state_probability2,als_data,proximity_data,als_calibration_value,sunset_timestamps,sunrise_timestamps,confidence_threshold1,confidence_threshold2,timer_value,iod_unknown_bitmask,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),GMM Likelihood 0,GMM Likelihood 1,HMM Parameter Selection Priors 0,HMM Parameter Selection Priors 1,HMM Transition State,HMM Transition Matrix 0,HMM Transition Matrix 1,HMM Transition Matrix 2,HMM Transition Matrix 3,Previous Time of Day (s),Posterior Probability 0,Posterior Probability 1,Prior IOD State Probability 0,Prior IOD State Probability 1,ALS Data,Proximity Data,ALS Calibration Value,Sunset Timestamp (s),Sunrise Timestamp (s),Confidence Threshold 0,Confidence Threshold 1,Timer Value (s),IOD Unknown Bitmask,Instance
            if ($#packet >= 27) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[8] = $lit_IODHMMTransitionState{$packet[8]} if (defined($lit_IODHMMTransitionState{$packet[8]}));
                $packet[19] = $lit_IODProximity{$packet[19]} if (defined($lit_IODProximity{$packet[19]}));
                $packet[26] = ParseIODReasonBitmask($packet[26]);
            }               
        }
        #LOG_SNS_IOD_REPORT_C
        elsif ($type == oct("0x191A")) {
            
            #packet_type,version,timestamp_type,timestamp,report_id,report_type,iod_output_state,confidence,iod_unknown_bitmask,iod_timer_value,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,IOD Output State,Confidence,IOD Unknown Bitmask,IOD Timer Value (s),Instance
            if ($#packet >= 10) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
                $packet[6] = $lit_IODState{$packet[6]} if (defined($lit_IODState{$packet[6]}));
                $packet[8] = ParseIODReasonBitmask($packet[8]);
            }             
        }
        #LOG_SNS_IOD_AUTOCAL_CONFIG_C
        elsif ($type == oct("0x191B")) {
            
            #packet_type,version,timestamp_type,timestamp,time_of_day,sunset_timestamps,sunrise_timestamps,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Time of Day (s),Sunset Timestamp (s),Sunrise Timestamp (s),Instance
            if ($#packet >= 7) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
            }
        }
        #LOG_SNS_IOD_AUTOCAL_RESULT_C
        elsif ($type == oct("0x191C")) {
            
            #packet_type,version,timestamp_type,timestamp,first_mom,second_mom,num_samples,isdiscrete,als_value0,als_value1,als_value2,als_value3,als_value4,als_value5,als_value6,als_value7,als_value8,als_value9,als_value10,als_value11,als_value12,als_value13,als_value14,als_value15,current_calibration_value,als_data,proximity_data,test_convergence,sunset_timestamps,sunrise_timestamps,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),First Moment,Second Moment,Num Samples,Is Discrete,ALS Value 0 (lux),ALS Value 1 (lux),ALS Value 2 (lux),ALS Value 3 (lux),ALS Value 4 (lux),ALS Value 5 (lux),ALS Value 6 (lux),ALS Value 7 (lux),ALS Value 8 (lux),ALS Value 9 (lux),ALS Value 10 (lux),ALS Value 11 (lux),ALS Value 12 (lux),ALS Value 13 (lux),ALS Value 14 (lux),ALS Value 15 (lux),Current Calibration Value,ALS Data,Proximity Data,Test Convergence,Sunset Timestamp (s),Sunrise Timestamp (s),Instance
            if ($#packet >= 30) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[7] = $lit_IODAIsDiscrete{$packet[7]} if (defined($lit_IODAIsDiscrete{$packet[7]}));
                $packet[26] = $lit_IODProximity{$packet[26]} if (defined($lit_IODProximity{$packet[26]}));
                $packet[27] = $lit_IODATestConvergence{$packet[27]} if (defined($lit_IODATestConvergence{$packet[27]}));
            }    
        }
        #LOG_SNS_IOD_AUTOCAL_REPORT_C
        elsif ($type == oct("0x191D")) {
            
            #packet_type,version,timestamp_type,timestamp,report_id,report_type,iod_calibration_return_status,iod_calibration_value,first_mom,second_mom,num_samples,isdiscrete,als_value0,als_value1,als_value2,als_value3,als_value4,als_value5,als_value6,als_value7,als_value8,als_value9,als_value10,als_value11,als_value12,als_value13,als_value14,als_value15,algo_inst_id
            #Packet,Version,Timestamp Type,Timestamp (ms),Report ID,Report Type,IOD Calibration Return Status,IOD Calibration Value,First Moment,Second Moment,Num Samples,Is Discrete,ALS Value 0 (lux),ALS Value 1 (lux),ALS Value 2 (lux),ALS Value 3 (lux),ALS Value 4 (lux),ALS Value 5 (lux),ALS Value 6 (lux),ALS Value 7 (lux),ALS Value 8 (lux),ALS Value 9 (lux),ALS Value 10 (lux),ALS Value 11 (lux),ALS Value 12 (lux),ALS Value 13 (lux),ALS Value 14 (lux),ALS Value 15 (lux),Instance
            if ($#packet >= 28) {
                ($packet[3], $packet[2]) = format_timestamp($packet[3], $packet[2]);
                $packet[5] = $lit_ReportType{$packet[5]} if (defined($lit_ReportType{$packet[5]}));
                $packet[6] = $lit_IODACalibrationStatus{$packet[6]} if (defined($lit_IODACalibrationStatus{$packet[6]}));
                $packet[11] = $lit_IODAIsDiscrete{$packet[11]} if (defined($lit_IODAIsDiscrete{$packet[11]}));
            }
        }        
   }
   return @packet;

} # FormatPacket


# ------------------------------------------------------------------------------
# Save the specified packet to a dedicated CSV file
# Usage:  SavePacket(@packet)
# ------------------------------------------------------------------------------
sub SavePacket {

   my (@packet) = @_;

   #print "Debug: ",$packet[0],"\n";

   # Determine key
   my $key = "Unknown";
   if (defined($supportedPackets{$packet[0]})) {
      $key = $packet[0];
   }

   # If output CSV file is not open, create it and save header
   if (!defined($csvFiles->{$key})) {

      # Parse the DLF file name
      my($filename, $directory, $extension) = fileparse($logFileName, qr/\.[^.]*/);

      # Use the destination folder if needed
      if (defined($destination)) {
          $directory = $destination;
      }

      # Compose the actual output filename
      if ($flagN) {
        $filename = File::Spec->catfile($directory, ($key eq "Unknown") ? "Unknown.csv" : ("0x".sprintf("%X", $key)."_".$key.".csv"));
      } else {     
        $filename = File::Spec->catfile($directory, $filename."_".(($key eq "Unknown") ? "Unknown.csv" : ("0x".sprintf("%X", $key)."_".$key.".csv")));
      }
      
      # Create the file and save the header
      $csvFiles->{$key} = IO::File->new($filename, 'w' );
      $csvFiles->{$key}->print(&GetHeader($key));
   }

   # Save packet data
   $csvFiles->{$key}->print(join(',', FormatPacket(@packet))."\n");

   # Increment processed packet count
   $packetsProcessed++;

   # NOTE: This functions opens file handles, but does not close them!  Need to call CloseCSVFiles()!

} # SavePacket


# ------------------------------------------------------------------------------
# Close all output CSV files
# Usage:  CloseCSVFiles()
# ------------------------------------------------------------------------------
sub CloseCSVFiles {

   # Close all the files in the csv files IO hash
   foreach my $key(keys(%{$csvFiles})) {
      $csvFiles->{$key}->close();
   }

} # CloseCSVFiles


# ------------------------------------------------------------------------------
# Process the current packet, i.e., line of the log file
# Usage:  ProcessPacket($line)
# ------------------------------------------------------------------------------
sub ProcessPacket {

   # Remove spaces from the string (some values are not strictly comma separated, but also have whitespace)
   $_ =~ s/ //g;

   # Get the all the values within the packet (comma separated string of values)
   my @packet = split(',', $_);

   # Increment total packet count
   $packetsTotal++;

   #print "Debug: " join(':', @packet), "\n";

   # Analyze packet only if more than 1 field is present
   if ($#packet > 0) {

      # Save the packet if a) no specific packets were entered (i.e., save all), or b) packet matches one that was specified
      if ( (0 == scalar(keys(%packetsToExtract))) || defined($packetsToExtract{$packet[0]}) ) {

         # Save the packet
         SavePacket(@packet);
      }
   }
} # ProcessPacket


# ------------------------------------------------------------------------------
# Parse the command line arguments for the script (@ARGV). See the comments above.
# Usage:  ParseCmdLine
# ------------------------------------------------------------------------------
sub ParseCmdLine {

   for (my $i = 0; $i <= $#ARGV; $i++) {
      if ($ARGV[ $i] eq "-l") {
         $i++;
         if ($i <= $#ARGV) {
            $logFileName = $ARGV[ $i];
         }
      }
      elsif ($ARGV[ $i] eq "-p") {
         $i++;
         if ($i > $#ARGV) {
            print "\n\tMissing -p\'s packet numbers! Defaulting to all known packet types.\n";
         }
         else {
            # Get all the packet numbers from the argument (comma-separated string)
            my @packetNums = split(',', $ARGV[$i]);

            # Convert all the packet numbers to decimal format (could be hex) and save to a hash if they're supported
            for (my $i = 0; $i <= $#packetNums; $i++) {

               my $packetNum = $packetNums[$i];
               $packetNum = oct($packetNum) if $packetNum =~ /^0/;

               if (!exists($supportedPackets{$packetNum})) {
                     die "\n\tUnsupported packet number, ".$packetNums[$i]."!\n";
               }
               $packetsToExtract{$packetNum} = 1; 
            }
            #print Dumper(\%packets);
         }
      }
      elsif ($ARGV[ $i] eq "-d") {
         $i++;
         if ($i > $#ARGV) {
            print "\n\tMissing -d\'s destination folder! Defaulting to same location as the log file.\n";
         }
         else {
            $destination = $ARGV[$i];
         }
      }
      elsif ($ARGV[ $i] eq "-nh") {
         $flagNH = 1;
      }
      elsif ($ARGV[ $i] eq "-a") {
         $flagA = 1;
      }
      elsif ( $ARGV[ $i] eq "-n") {
         $flagN = 1;
      }      
      elsif ($ARGV[ $i] eq "-h") {

        if ($isEXE) {
           print "\nDescription:\n\tThis script extracts internal packets from a CSV file created by SAMPostProcess.exe.\n";
           print "\tDepending on selected options, the output CSV file(s) can be used within the offline playback framework or by the Data Visualizer.\n\n";
           print "Usage:\n\t$0 [-l log_file] [-d destination_folder] [-p packet_numbers] [-a] [-nh] [-n] [-h] \n\n";
           print "Input Options:\n";
           print "\t-l log_file:  (required)  CSV file created by SAMPostProcess.exe.\n";
        }
        else {
           print "\nDescription:\n\tThis script extracts internal packets from a) an input DLF log file, or b) an input CSV file created by SAMPostProcess.pl, and saves the interpreted packet data to individual CSV file(s).\n";
           print "\tDepending on selected options, the output CSV file(s) can be used within the offline playback framework or by the Data Visualizer.\n";
           print "\tThis script requires SAMPostProcess.pl for parsing internal packets if the input is a DLF log file.\n\n";
           print "Usage:\n\t$0 [-l log_file] [-d destination_folder] [-p packet_numbers] [-nh] [-a] [-h] \n\n";
           print "Input Options:\n";
           print "\t-l log_file:  (required)  DLF log file, or a CSV file created by SAMPostProcess.pl.\n";
        }
        print "\t-d destination_folder:  (optional)  Destination folder for the CSV output file(s).\n";
        print "\t-p packet_numbers:  (optional) Packet numbers to extract, in decimal or hex, and comma-separated.  Default is to extract all known packet types.\n";
        print "\t-a:  (optional) The option to keep the data as it is in the log file.\n";
        print "\t-nh:  (optional) The no header option for the output CSV files.\n";
        print "\t-n:  (optional)  New filename option, i.e., do not use the log file name as a pre-fix for the new output CSV file(s).\n";
        print "\t-h:  (optional) Help switch, show the command usage.\n\n";
        print "Copyright QUALCOMM (C) 2013-2015, All Rights Reserved.\n\n";
        exit;           
      }
   }

   # Validate the a log file was entered
   if (!defined($logFileName)) {
      die "\n\tError!  Must specify a log file.  See usage: $0 [-l log_file] [-d destination_folder] [-p packet_numbers] [-a] [-nh] [-n] [-h]\n";
   }

   if (rindex(lc($logFileName), ".csv") >= 0) {
      $logType = ".csv";
   }
   elsif (rindex(lc($logFileName), ".dlf") >= 0) {
      $logType = ".dlf";
   }

   if (!defined($logType)) {
      die "\n\tError!  The log file name must be either a *.CSV or a *.DLF file!\n";
   }
   elsif (($isEXE) && ($logType eq ".dlf")) {
         die "\n\tError!  The log file name must be a *.CSV file when using $0!\n";
   }

   # Make sure the output destination is available if defined
   if (defined($destination)) {
      mkpath($destination) or die "\n\tError!  Could not make path, $destination!\n" if (!(-d $destination));
   }

} # ParseCmdLine


# ------------------------------------------------------------------------------
# The main function of the script.
# Usage:  Main
# ------------------------------------------------------------------------------
sub Main {

   # Parse the command line arguments
   ParseCmdLine();

   # Get the CSV file
   if ($logType eq ".csv") {
      $csvFileName = $logFileName;
   }
   elsif ($logType eq ".dlf") {

      # The name of the output file generated by SAMPostProcess.pl
      $csvFileName = substr( $logFileName, 0, rindex( $logFileName, q{.} ))."_SAMPostProcess.csv";

      my $script = locate_script("SAMPostProcess.pl");  
      print "\n\tCalling $script to create the CSV file: $csvFileName ";
      system("perl $script -l $logFileName");
      
      if (!(-f $csvFileName)) {
        $csvFileName = substr( $logFileName, 0, rindex( $logFileName, q{.} ))."_prssamqmd.csv";
        die "\n\tError!  The *.CSV file generated by SAMPostProcess.pl is not found!\n" if (!(-f $csvFileName));
      }
   }

   print "\n\tExtracting packets from the CSV file ($csvFileName)... ";

   # Open the log CSV file
   open(INFILE, "<$csvFileName") or die "Can\'t open $csvFileName!\n";
   
   # Read in the whole file one packet (line) at a time   
   while (<INFILE>) {
      # print "Debug: $_\n";
      ProcessPacket(chomp($_));
   }
   
   print "\n\tDone extracting packets! Processed $packetsProcessed packets out of $packetsTotal total packets. There were ".scalar(keys(%{$csvFiles}))." known packet types.\n\n";

   # Close the log and csv files
   close(INFILE);
   CloseCSVFiles();

} # Main


Main();

