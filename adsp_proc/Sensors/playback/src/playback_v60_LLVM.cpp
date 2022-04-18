/*=============================================================================
  @file fast_playback_v60_LLVM.cpp

  This file contains the playback harness implementation.

*******************************************************************************
*   Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
*   All Rights Reserved.
*   Confidential and Proprietary - Qualcomm Technologies, Inc.
*
*******************************************************************************

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-11-09  qm   Add SMGR client disable after finish processing samples for 
  2016-11-07  bd   Updated function call to sns_rh_sol_update_items_info
  2016-10-12  np   Added signal for qmag playback sample loss. 
  2016-08-10  np   Overhaul done of playback.
  1970-01-01  tc   File created.

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
extern "C" {
#include "qurt_thread.h"
#include "qurt_sem.h"
#include "qurt_consts.h"
#include "playback.h"
#include "playback_time_manager.h"
#include "playback_smgr.h"
#include "playback_registry.h"
#include "playback_parse.h"
#include "sns_init.h"
#include "sns_em.h"
#include "sns_usmr_priv.h"
#include "sns_sam.h"
#include "sns_sam_init.h"
#include "sns_sam_service.h"
#include "sns_sam_ind.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_common_v01.h"
#include "sns_smgr_api_v01.h"
#include "sns_rh_util.h"
#include "sns_smgr_depot.h"
#include "sns_smgr_util.h"
#include "sns_smgr.h"
}

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
// Number of vectors to test (i.e vector rows to process in file)
#define INPUT_VECTOR_HEIGHT 200000
#define QMI_VECTOR_HEIGHT 1000
#define NUM_AXES_ACCEL        3
#define NUM_AXES_PROXIMITY    1
#define MAX_ARGC_SUPPORTED    7


/*----------------------------------------------------------------------------
 *  Extern Variables
 * -------------------------------------------------------------------------*/
extern FILE * log_result;
extern sns_smgr_s sns_smgr;
extern void sns_smr_task_init(void);
extern void sns_rh_task(void* p_arg);

/*----------------------------------------------------------------------------
 * Structure Definitions
 * -------------------------------------------------------------------------*/

typedef struct
{
  uint8_t qmi_msg_type;
  uint8_t service_id;
  uint32_t timestamp;
  struct sns_sam_msg msg;
} sns_playback_qmi_msg_s;

typedef struct
{
  uint32_t conn_handle;
  sns_sam_sensor_uid suid;
  int32_t algo_instance_id;
} sns_algo_info_s;


/*----------------------------------------------------------------------------
 *  Global Variables
 * -------------------------------------------------------------------------*/

sns_ddf_sensor_data_s sensor_samples[INPUT_VECTOR_HEIGHT];
sns_playback_qmi_msg_s qmi_msgs[QMI_VECTOR_HEIGHT];


OS_FLAG_GRP * playback_sig_event;
OS_FLAG_GRP * playback_resume_sig_event;
OS_FLAG_GRP * playback_cal_sig_event;
OS_FLAG_GRP * playback_disable_sig_event;
OS_FLAG_GRP * playback_reg_sig_event;
OS_EVENT    * fpb_rh_mutex;
char registry_file_name[256];

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/


/*===========================================================================

  FUNCTION:   set_sensor_input_config

===========================================================================*/
/*!
  @brief Based on sensor id, updates the sensor rate

  @param sensor_suid - the sensor id interest
         mean_rate   - the stream rate this sensor will support.

  @return void
 */
/*=========================================================================*/

void set_sensor_input_config(
    uint64_t sensor_suid,
    uint32_t mean_rate)
{
  sns_ddf_odr_t *sensor_input_rate;

  switch( sensor_suid )
  {
    case SNS_SMGR_SUID_ACCEL_1_V01:
      sensor_input_rate = &accel_input_rate;
      break;

    case SNS_SMGR_SUID_GYRO_1_V01:
      sensor_input_rate = &gyro_input_rate;
      break;

    case SNS_SMGR_SUID_MAG_1_V01:
      sensor_input_rate = &mag_input_rate;
      break;

    case SNS_SMGR_SUID_PRESSURE_1_V01:
      sensor_input_rate = &pressure_input_rate;
      break;

    case SNS_SMGR_SUID_HEART_RATE_1_V01:
      sensor_input_rate = &ppg_input_rate;
      break;

    case SNS_SMGR_SUID_PROX_1_V01:
      sensor_input_rate = &prox_input_rate;
      break;

    default:
      printf("set_sensor_input_config - unknown SUID 0x%llx\n", sensor_suid);
      return;
  }

  *sensor_input_rate = (sns_ddf_odr_t) mean_rate;
}
/*===========================================================================

  FUNCTION:   playback_parse_event_sensor_sample

===========================================================================*/
/*!
  @brief Parses the input file and updates the samples structure array.

  @param sensor_type  - the sensor type being passed.
         event_data   - unused.
         samples      - the samples structure array.
         counter      - The previous samples written index.
  @return void
 */
/*=========================================================================*/

void playback_parse_event_sensor_sample(
    sns_ddf_sensor_e sensor_type,
    const char * event_data,
    sns_ddf_sensor_data_s * samples,
    int counter)
{
  // Accel Sample: ACCEL_SUID, <Timestamp>, <Accel X>, <Accel Y>, <Accel Z>
  // Mag Sample:   MAG_SUID, <Timestamp>, <Mag X>, <Mag Y>, <Mag Z>
  // Gyro Sample:  GYRO_SUID, <Timestamp>, <Gyro X>, <Gyro Y>, <Gyro Z>
  char *pch;
  int i, numAxes = 3;

  samples[counter].sensor = sensor_type;

  // Parse the timestamp
  pch = strtok_r(NULL, ",", &line_save);
  samples[counter].timestamp = strtoull(pch, 0, 10);
  // + (uint32_t)(4294967296-200000);

  samples[counter].samples =(sns_ddf_sensor_sample_s *)
                            malloc(numAxes*sizeof(sns_ddf_sensor_sample_s));
  for (i = 0; i < numAxes; i++)
  {
    pch = strtok_r(NULL, ",", &line_save);
    samples[counter].samples[i].sample = atol(pch);
    samples[counter].samples[i].status = SNS_DDF_SUCCESS;
  }
  //samples[counter].num_samples = 3;
  samples[counter].num_samples = 1;
  samples[counter].status = SNS_DDF_SUCCESS;
}
/*===========================================================================

  FUNCTION:   load_sensor_samples

===========================================================================*/
/*!
  @brief Load sensor samples from the sensor input CSV. The format of the CSV
         must follow this format:
         <sensor type>, <0>, <0>, <timestamp (SSC ticks)>, <# of axes>,
         <data[0]>, <data[1]>, <data[2]>
  @param vectors_directory        - Directory where the input file is present.
         sensor_data_input_file   - The data input file name.
         samples                  - the samples structure array.

  @return counter                 -  The last written sample.
 */
/*=========================================================================*/
int load_sensor_samples(
    const char *vectors_directory,
    const char *sensor_data_input_file,
    sns_ddf_sensor_data_s * samples )
{
  char fileStr[256] = "";
  FILE *fp;
  char *pch, tmp[256];
  int counter = 0;

  uint64_t event_suid;

  strlcat(fileStr, vectors_directory, sizeof(fileStr));
  strlcat(fileStr, sensor_data_input_file, sizeof(fileStr));

  printf("Input File: %s\n", fileStr);
  fflush(stdout);

  fp = fopen(fileStr, "r");
  assert(fp != NULL);

  while ((fgets(tmp, sizeof(tmp), fp) != NULL) && (counter < INPUT_VECTOR_HEIGHT))
  {
#ifdef OLD_CSV_FORMAT
    // FORMAT: <sensor type>, < 0? >, < 0? >, <timestamp (SSC ticks)>, <# of axes>, <data[0]>, <data[1]>, <data[2]>

    // Parse the Sensor Type
    pch = strtok_r(tmp, ",", &line_save);
    samples[counter].sensor = (sns_ddf_sensor_e) atoi(pch);

    // Parse the 0? but DO NOT use the data
    pch = strtok_r(NULL, ",", &line_save);
    // Parse the 0? but DO NOT use the data
    pch = strtok_r(NULL, ",", &line_save);

    // Parse the timestamp
    pch = strtok_r(NULL, ",", &line_save);
    samples[counter].timestamp = strtoul(pch, 0, 10); // + (uint32_t)(4294967296-200000);

    // Parse the # of axes but DO NOT use the data
    pch = strtok_r(NULL, ",", &line_save);

    if (SNS_DDF_SENSOR_ACCEL == samples[counter].sensor ||
        SNS_DDF_SENSOR_GYRO == samples[counter].sensor ||
        SNS_DDF_SENSOR_MAG == samples[counter].sensor)
    {
      numAxes = NUM_AXES_ACCEL;
    }
    else if (SNS_DDF_SENSOR_PROXIMITY == samples[counter].sensor)
    {
      numAxes = NUM_AXES_PROXIMITY;
    }
    else
    {
      continue;
    }

    // Parse the values
    for (i = 0; i < numAxes; i++)
    {
      pch = strtok_r(NULL, ",", &line_save);
      samples[counter].samples[i] = atol(pch);
    }
    counter++;
#else /* OLD_CSV_FORMAT */

    // FORMAT: <Event SUID>, <Event Data 0>, <Event Data 1>, ...
    // Accel Sample: 0x4b118d0883777081, <Timestamp>, <Accel X>, <Accel Y>, <Accel Z>
    // Gyro Sample:  0x35bcdb5f5574ab55, <Timestamp>, <Gyro X>, <Gyro Y>, <Gyro Z>
    // Mag Sample:   0x3ff4eb5fde2790a3, <Timestamp>, <Mag X>, <Mag Y>, <Mag Z>

    // Parse the Event Type
    pch = strtok_r(tmp, ",", &line_save);
    event_suid = strtoull(pch, NULL, 16);
    switch( event_suid )
    {
      case 0:
        // Quietly ignore Event SUID 0,
        //  this is sometimes used to comment the file
        break;

      case SNS_SMGR_SUID_ACCEL_1_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR_ACCEL,
                                           tmp, samples, counter);
        counter++;
        break;

      case SNS_SMGR_SUID_GYRO_1_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR_GYRO,
                                           tmp, samples, counter);
        counter++;
        break;

      case SNS_SMGR_SUID_MAG_1_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR_MAG,
                                           tmp, samples, counter);
        counter++;
        break;

      case SNS_SMGR_SUID_PRESSURE_1_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR_PRESSURE,
                                           tmp, samples, counter);
        counter++;
        break;

      case SNS_SMGR_SUID_HEART_RATE_1_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR_HEART_RATE_RAW,
                                           tmp, samples, counter);
        counter++;
        break;

      case SNS_SMGR_SUID_PROX_1_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR_PROXIMITY, tmp, samples, counter);
        counter++;
        break;

      case SNS_PLAYBACK_SENSOR_INPUT_CONFIG_V01:
        // Sensor Input Config: 0x3f39c7bfb4161880, <Sensor SUID>, <Mean Rate>, <Vendor>, <Model>
        uint64_t sensor_suid;
        int mean_rate;

        // Retrieve the Sensor SUID
        pch = strtok_r(NULL, ",", &line_save);
        sensor_suid = strtoull(pch, NULL, 16);

        // Get the Mean Rate for that sensor's stream
        pch = strtok_r(NULL, ",", &line_save);
        mean_rate = atoi(pch);

        // Apply the sensor's input config
        set_sensor_input_config(sensor_suid, (uint32_t) mean_rate);
        break;

      case SNS_PLAYBACK_SENSOR_RESET_EVENT_V01:
        playback_parse_event_sensor_sample(SNS_DDF_SENSOR__NONE,
                                           tmp, samples, counter);
        counter++;
        break;

      default:
        printf("ERROR: Unsupported event type %llx", event_suid);
        break;
    }
#endif /* OLD_CSV_FORMAT */
  }

  fclose(fp);

  return counter;
}

/*===========================================================================

  FUNCTION:   process_qmi_events

===========================================================================*/
/*!
  @brief Helper function to parse qmi events
  @param curr_index                -
         total_msgs                -

  @return void
 */
/*=========================================================================*/
void process_qmi_events(int *curr_index, int total_msgs)
{
  uint32_t timestamp = sns_tm_get_current_timestamp();

  while((*curr_index < total_msgs))
  {
    if(timestamp > qmi_msgs[*curr_index].timestamp)
    {
      sns_playback_qmi_msg_s qmi_msg = qmi_msgs[*curr_index];
      sns_tm_update_current_timestamp(qmi_msg.timestamp);
      (*curr_index)++;
    }
    else
    {
      break;
    }
  }

  sns_tm_update_current_timestamp(timestamp);
}

/*===========================================================================

  FUNCTION:   find_sensor_id

===========================================================================*/
/*!
  @brief Helper function to convert ddf sensor id to sensor id
  @param sensor                - DDF sensor id
                         -

  @return smgr_sensor_id_e
 */
/*=========================================================================*/
smgr_sensor_id_e          find_sensor_id(sns_ddf_sensor_e          sensor)
{
    smgr_sensor_id_e sensor_id;
    switch( sensor )
    {
      case SNS_DDF_SENSOR_ACCEL:
         sensor_id = SNS_SMGR_ID_ACCEL_V01;
        break;

      case SNS_DDF_SENSOR_GYRO:
           sensor_id = SNS_SMGR_ID_GYRO_V01;
        break;

      case SNS_DDF_SENSOR_MAG:
           sensor_id = SNS_SMGR_ID_MAG_V01;
        break;

      case SNS_DDF_SENSOR_PRESSURE:
           sensor_id = SNS_SMGR_ID_PRESSURE_V01;
        break;

      case SNS_DDF_SENSOR_HEART_RATE_RAW:
           sensor_id = SNS_SMGR_ID_HEART_RATE_V01;
        break;

      case SNS_DDF_SENSOR_PROXIMITY:
           sensor_id = SNS_SMGR_ID_PROX_LIGHT_V01;
        break;
      case SNS_DDF_SENSOR__NONE:
         sensor_id = SNS_SMGR_ID_CAL_RESET_V01;
         break;
      default:
        printf("ERROR: Unsupported sensor type %d\n", sensor);
        break;
    }
    return sensor_id;
}

/*===========================================================================

  FUNCTION:   main

===========================================================================*/
/*!
  @brief Main function.
  @param argc                 - Num of command line arguements.
         argv                 - Array of command line arguements.

  @return int                 - Exit code.
 */
/*=========================================================================*/
int main(int argc, char*argv[])
{
  printf("[PBK_T]Starting Fast Playback v%u.%u\n",
      FAST_PLAYBACK_MAJOR_VERSION, FAST_PLAYBACK_MINOR_VERSION);

  char vector_dir[256];
  char accel_input_file[256];
  char qmi_input_file[256];
  char out_file[256];
  char diag_req_file[256];
  char * line_parse;

  int num_sensor_samples;
  int num_qmi_msgs = 0;
  qurt_thread_t  pbMainThr = qurt_thread_get_id();
  qurt_thread_set_priority(pbMainThr,120);
  char buf[1024];
  char argvbuf[1024];
  uint8_t errOS,errOS1;
  int count = 0;
  struct sns_smgr_ddf_sensor_s*  ddf_sensor_ptr;

  fast_playback_sensor1_diag_req * diag_req = NULL;

  OS_FLAGS sigFlags;
  OS_FLAGS  pb_sig_mask = FPB_INIT_DONE |
                          FPB_CLIENT_CONNECT_DONE |
                          FPB_CAL_ENABLE_SIG |
                          FPB_REG_DEINIT_DONE;
  fpb_rh_mutex = sns_os_mutex_create( 0, &errOS );
  //------------- CMD LINE ARGUEMENTS ----------------//

  argv = (char**) argvbuf;
  argc = 0;

   // system call to retrieve the command line, supported by q6 simulator.
  qurt_process_cmdline_get(buf, sizeof(buf));
  // 1st argv is the program being run (i.e. "fastcv_test.ext") and its path
  argv[0] = strtok_r(buf, " ",&line_save);

  while ( NULL != ( argv[++argc] = strtok_r(NULL, " ",&line_save) ) ) {};

  printf("\n [PBK_T]No Of arguments supplied: %d",argc);

  /*if ( argc != MAX_ARGC_SUPPORTED )
  {
    printf("\nWe support 5 arguments: vector_director input_file_name "
            "output_file_name qmi_input_file ,reg file ,diag_req file");
    exit(0);
  }

  strlcpy( vector_dir, argv[1], sizeof(vector_dir) );
  strlcpy( accel_input_file, argv[2],sizeof(accel_input_file) );
  strlcpy( out_file, argv[3], sizeof(out_file) );
  strlcpy( qmi_input_file, argv[4], sizeof(qmi_input_file) );
  strlcpy( registry_file_name, argv[5], sizeof(registry_file_name) );
  strlcpy( diag_req_file, argv[6], sizeof(diag_req_file) );*/

  strlcpy( vector_dir, "", sizeof(vector_dir) );
  strlcpy( accel_input_file, "fast_playback_input.csv",sizeof(accel_input_file) );
  strlcpy( out_file, "fast_playback_output.dlf", sizeof(out_file) );
  strlcpy( qmi_input_file, "algoqmiinput.csv", sizeof(qmi_input_file) );
  strlcpy( registry_file_name, "sns.reg", sizeof(registry_file_name) );
  strlcpy( diag_req_file, "fast_playback_diag_input.txt", sizeof(diag_req_file) );
  
  
  printf("[PBK_T] Vector Dir: %s   Accel In: %s   QMI In: %s Registry: %s Out: %s\n",
          vector_dir, accel_input_file, qmi_input_file,
          registry_file_name, out_file);

  fflush(stdout);

  //------------- INIT SIGNALING STRUCTS ------------------------------------//

  playback_sig_event = sns_os_sigs_create( pb_sig_mask, &errOS );
  playback_cal_sig_event = sns_os_sigs_create( FPB_CAL_CONNECT_SIG, &errOS );
  playback_resume_sig_event = sns_os_sigs_create( FPB_SENSOR_DATA_RESUME, &errOS1 );
  playback_disable_sig_event = sns_os_sigs_create( FPB_CLIENT_DISABLE_DONE, &errOS );
  playback_reg_sig_event = sns_os_sigs_create(FPB_REG_SIG, &errOS);

  //------------- INITIALIZE FILE STUFF ----------------//

  num_sensor_samples = load_sensor_samples(vector_dir,
                                           accel_input_file, sensor_samples);

  printf("[PBK_T] Num sensor samples: %d, Num QMI msgs: %d\n",
          num_sensor_samples, num_qmi_msgs);

  log_result = fopen(out_file, "w");
  assert(log_result != NULL);
  printf("[PBK_T] Output File: %s\n", out_file);


  //------------- INITIALIZE SSC THREADS ----------------//

  sns_err_code_e errSNS;

  sns_tm_init();
  // Set the initial timestamp to be 1
  //tick less than the timestamp of the first sample
  sns_tm_update_current_timestamp(sensor_samples[0].timestamp - 10000);

  sns_smr_task_init();
  //sns_smr_init();
  sns_batchbuff_init();


  // Initialize Registry Service

  errSNS= sns_reg_init();
  if ( SAM_ENONE != errSNS )
  {
    printf("[PBK_T] Error initializing Registry service %d\n", errSNS);
  }
  else
  {
    printf("\n[PBK_T] Wating for REG to say init done");
    sigFlags = sns_os_sigs_pend( playback_sig_event,
                                 (OS_FLAGS) FPB_INIT_DONE,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                 0, &errOS );
    printf("[PBK_T] Done initializing REG service\n");
  }


  // Initialize SMGR service
  sns_smgr_sensor_init();
  create_dummy_sensor_data();


  errSNS=sns_rh_init();
  if ( SAM_ENONE != errSNS )
  {
    printf("[PBK_T] Error initializing SMGR service %d\n", errSNS);
  }
  else
  {
    printf("\n[PBK_T] Wating for RH to say init done");
    sigFlags = sns_os_sigs_pend( playback_sig_event,
                                 (OS_FLAGS) FPB_INIT_DONE,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                 0, &errOS );
    printf("[PBK_T] Done initializing RH service\n");
  }


  //------------- INITIALIZE USAM ----------------//
  printf("[PBK_T] Initializing uSAM Thread\n");
  errSNS = sns_usam_init();
  if ( SAM_ENONE != errSNS )
  {
    printf("[PBK_T] Error initializing uSAM Thread %d\n", errSNS);
  }
  else
  {
    printf("[PBK_T] Waiting on uSAM Thread init done\n");

    sigFlags = sns_os_sigs_pend( playback_sig_event,
          (OS_FLAGS) FPB_INIT_DONE,
          OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );

    printf("[PBK_T] Done initializing uSAM Thread\n");
  }
  printf("\n [PBK_T] Waiting on Cal Algo connect\n");
  sigFlags = sns_os_sigs_pend( playback_cal_sig_event,
       (OS_FLAGS) FPB_CAL_CONNECT_SIG,
       OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
  printf("\n[PBK_T] Cal ALgo connected\n");

  //------------- PREPARE DIAG REQUEST FROM DIAG INPUT AND SEND IT OUT  ----------------//
  fast_playback_parse_send_diag_req(diag_req_file, &diag_req);

  //------------- HANDLE THE SENSOR SAMPLES ----------------//

  printf("[PBK_T] Sending in sensor samples\n");
  smgr_sensor_id_e          sensor_id;
  for( int j=0; j<num_sensor_samples; j++)
  {
     sensor_id = find_sensor_id (sensor_samples[j].sensor);
    if(sensor_id == ( SNS_SMGR_ID_CAL_RESET_V01) )
    {
      if(SNS_SMGR_ID_CAL_MODE_SWITCH_V01 == sensor_samples[j].samples[1].sample )
      {
        printf("\n[PBK_T] Sending a CAL MODE SWITCH for sensor id %d, new mode: %d\n",
                sensor_samples[j].samples[0].sample,
                sensor_samples[j].samples[2].sample);
        printf("[PBK_T] MODE SWITCH THROUGH input sample currently not supported! using diag input instead!\n");

        //fast_playback_send_cal_mode_switch(
        //    (smgr_sensor_id_e)sensor_samples[j].samples[0].sample, sensor_samples[j].samples[2].sample);
      }
      else
      {
        printf("\n[PBK_T] Sending a CAL RESET for sensor id %d",sensor_samples[j].samples[0].sample);
        fast_playback_send_cal_reset(
                (smgr_sensor_id_e)sensor_samples[j].samples[0].sample);
    }
    }
    else
    {

        ddf_sensor_ptr =   sns_smgr_find_ddf_sensor(sensor_id,
                           SNS_SMGR_DATA_TYPE_PRIMARY_V01);
        if(ddf_sensor_ptr == NULL)
        {
            printf("\n[PBK_T] ERROR : No ddf pointer found for sensor %d\n",
                    sensor_samples[j].sensor);
            exit(-1);
        }
        //Put in sensor depot.
        sns_os_mutex_pend(ddf_sensor_ptr->depot_mutex_ptr, 0, NULL);
        sns_smgr_handle_new_sample(ddf_sensor_ptr,&sensor_samples[j]);
        sns_os_mutex_post(ddf_sensor_ptr->depot_mutex_ptr);

        //Update the linked rpt items
        sns_os_mutex_pend( fpb_rh_mutex, 0, &errOS );
        sns_rh_sol_playback_update_item(ddf_sensor_ptr, false);
        sns_os_mutex_post(fpb_rh_mutex);


        count++;
        if(count>=MAX_SENSOR_INPUT_SAMPLES)
        {
          printf("[PBK_T] Fast Playback progress : %3.2f%% \r",
                  100*(j/(float)num_sensor_samples));
          fflush(stdout);
          sns_rh_signal_me(SNS_RH_SAMPLE_READY_SIG);
          //Make pb wait till RH completes.
          sigFlags = sns_os_sigs_pend( playback_cal_sig_event,
               (OS_FLAGS) FPB_CAL_CONNECT_SIG,
               OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
          //Make PB wait till SAM signals
          if( diag_req->session_hdr.srvc_num != SNS_SMGR_SVC_ID_V01)
          {
             sigFlags = sns_os_sigs_pend( playback_resume_sig_event,
              (OS_FLAGS) FPB_SENSOR_DATA_RESUME,
              OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 1, &errOS );
          }
          count =0;
        }
    }
  }
  printf("[PBK_T] Processed %d samples.\n", num_sensor_samples);

  //Process the final sent samples.
  if(count !=0 )
  {
    sns_rh_signal_me(SNS_RH_SAMPLE_READY_SIG);
    //Make pb wait till RH completes.
    sigFlags = sns_os_sigs_pend( playback_cal_sig_event,
         (OS_FLAGS) FPB_CAL_CONNECT_SIG,
         OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
    //Make PB wait till SAM signals
    sigFlags = sns_os_sigs_pend( playback_resume_sig_event,
        (OS_FLAGS) FPB_SENSOR_DATA_RESUME,
        OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 1, &errOS );

  }

  printf("=====>\n[PBK_T] sample process completed, start disabling client.\n");
  fast_playback_disable_client(diag_req);


  sigFlags = sns_os_sigs_pend( playback_disable_sig_event,
      (OS_FLAGS) FPB_CLIENT_DISABLE_DONE,
      OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
  printf("=====>\n[PBK_T] client disable completed, start tear down sns_reg service.\n");


  //signal sns_reg service to tear down
  sns_os_sigs_post( playback_reg_sig_event,
          FPB_REG_SIG, OS_FLAG_SET, &errOS );

  //wait for reg service to tear down
  sigFlags = sns_os_sigs_pend( playback_sig_event,
        (OS_FLAGS) FPB_REG_DEINIT_DONE,
        OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &errOS );
  printf("=====>\n[PBK_T] sns_reg tear down completed, playback simulation about to terminated!!\n");


  return 0;
}
