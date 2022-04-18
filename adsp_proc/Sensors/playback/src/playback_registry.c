/*============================================================================
  Includes
  ===========================================================================*/
#include <stdio.h>
#include "playback_registry.h"
#include "sns_reg.h"
#include "sns_usmr.h"
#include "sns_debug_str.h"
#include "fixed_point.h"
#include "playback.h"

/*============================================================================
  Definitions
  ===========================================================================*/

#define SNS_DBG_MOD_APPS_FSA 0

/*! Meta-data about files */
typedef struct sns_fsa_stat_s {
  int64_t size; /*< Size of the file, in bytes */
} sns_fsa_stat_s;

/*============================================================================
  Global Data
  ===========================================================================*/
STATIC OS_STK sns_reg_task_stk[SNS_REG_MODULE_STK_SIZE];
/* Registry Input File */
FILE * reg_file_handle = NULL;

/* Registry SMR server interface */
smr_service_hndl        fpb_registry_service_handle;
uint32_t                fpb_registry_service_cookie;

/**
 * Table allowing quick conversion from data type to size
 */
const uint8_t sns_reg_item_size[ SNS_REG_TYPE_COUNT ] =
{
  sizeof( uint8_t ),  /* SNS_REG_TYPE_UINT8  */
  sizeof( uint16_t ), /* SNS_REG_TYPE_UINT16 */
  sizeof( uint32_t ), /* SNS_REG_TYPE_UINT32 */
  sizeof( uint64_t ), /* SNS_REG_TYPE_UINT64 */
  sizeof( int8_t ),   /* SNS_REG_TYPE_INT8   */
  sizeof( int16_t ),  /* SNS_REG_TYPE_INT16  */
  sizeof( int32_t ),  /* SNS_REG_TYPE_INT32  */
  sizeof( int64_t ),  /* SNS_REG_TYPE_INT64  */
  sizeof( q16_t ),    /* SNS_REG_TYPE_Q16    */
  sizeof( float ),    /* SNS_REG_TYPE_FLOAT  */
  sizeof( double )    /* SNS_REG_TYPE_COUNT  */
};
extern char registry_file_name[];
/*============================================================================
  Static Function Definitions
  ===========================================================================*/

/*============================================================================

  FUNCTION:   sns_fsa_open

  ============================================================================*/
void* sns_fsa_open( const char* pathname, const char* mode )
{
  void* rv = NULL;

  if (NULL != pathname)
  {
    rv = fopen(pathname, mode);
  }

  return rv;
}

/*============================================================================

  FUNCTION:   sns_fsa_close

  ============================================================================*/
/*!
  @brief Closes a file

  @return
  SNS_ERR_FAILED if operation failed; SNS_SUCCESS otherwise

  @sideeffects
  File will be closed
*/
/*============================================================================*/
sns_err_code_e sns_fsa_close ( void* file_handle )
{
  int32_t err;

  if(NULL == file_handle)
  {
    return SNS_ERR_BAD_PARM;
  }
  err = fclose( (FILE*)file_handle );
  if( SNS_SUCCESS != err )
  {
    SNS_PRINTF_STRING_HIGH_2( SNS_DBG_MOD_APPS_FSA,
                              "failed to close file, err = %d, err string = %s",
                              err, strerror(err) );
    return SNS_ERR_FAILED;
  }
  return SNS_SUCCESS;
}

/*============================================================================

  FUNCTION:   sns_fsa_seek (taken from <APPS sensorS>/dsps/sensordaemon/fsa/src/sns_fsa_la.c)
  TODO: EITHER PULL IN THE FSA FILES FROM THE APPS-SIDE OR TAKE FULL OWNERSHIP OVER THIS FUNCTION

  ============================================================================*/
sns_err_code_e sns_fsa_seek( void* file_handle, int64_t offset, int32_t origin )
{
  int err = SNS_SUCCESS;

  err = fseek( (FILE*)file_handle, offset, SEEK_SET );

  SNS_PRINTF_STRING_LOW_3( SNS_DBG_MOD_APPS_FSA,
                           "sns_fsa_seek: offset %d, origin %d, err: %d",
                           offset, origin, err );
  if( 0 != err )
  {
    return SNS_ERR_FAILED;
  }
  else
  {
    return SNS_SUCCESS;
  }
}

/*============================================================================

  FUNCTION:   sns_fsa_read (taken from <APPS sensorS>/dsps/sensordaemon/fsa/src/sns_fsa_la.c)
  TODO: EITHER PULL IN THE FSA FILES FROM THE APPS-SIDE OR TAKE FULL OWNERSHIP OVER THIS FUNCTION

  ============================================================================*/
sns_err_code_e sns_fsa_read( void* file_handle, uint8_t* buffer_ptr,
                             uint32_t num_bytes, uint32_t* bytes_read_ptr )
{
  size_t cnt;
  int    err;

  cnt = fread( (void*)buffer_ptr , sizeof(uint8_t), (size_t)num_bytes,
               (FILE*)file_handle );
  err = ferror( (FILE*)file_handle );

  SNS_PRINTF_STRING_LOW_2( SNS_DBG_MOD_APPS_FSA,
                           "sns_fsa_read: bytes read %d, err: %d", cnt, err );

  /* The bionic version of fread() returns EOF even though it is defined
     as (-1). This does not match the type of the return value, size_t
     which is unsigned. */
  if( ( 0 == cnt ) || ( (size_t)EOF == cnt ) || ( 0 != err ) )
  {
    *bytes_read_ptr = 0;
    return SNS_ERR_FAILED;
  }
  else
  {
    *bytes_read_ptr = (uint32_t)cnt;
    return SNS_SUCCESS;
  }
}

/*============================================================================

  FUNCTION:   sns_fsa_write

  ============================================================================*/
sns_err_code_e sns_fsa_write( void const *file_handle, uint8_t const *buffer_ptr,
                              uint32_t num_bytes, uint32_t* bytes_written_ptr )
{
  size_t cnt;
  int    err;

  cnt = fwrite( (void*)buffer_ptr, sizeof(uint8_t), (size_t)num_bytes,
                (FILE*)file_handle );
  err = ferror( (FILE*)file_handle );

  if(( cnt != num_bytes ) || ( 0 != err ))
  {
    SNS_PRINTF_STRING_ERROR_1( SNS_DBG_MOD_APPS_FSA, "fwrite failed, %d", err );
    *bytes_written_ptr = 0;
    return SNS_ERR_FAILED;
  }
  else
  {
    *bytes_written_ptr = (uint32_t)cnt;
    return SNS_SUCCESS;
  }
}

/*============================================================================

  FUNCTION:   sns_fsa_flush

  ============================================================================
sns_err_code_e sns_fsa_flush( void* file_handle )
{
  int err;
  int file_descriptor;

  if( NULL == file_handle ) {
    return SNS_ERR_BAD_PTR;
  }

  err = fflush( (FILE*)file_handle );
  if ( 0 != err )
  {
    return SNS_ERR_FAILED;
  }
  else
  {
    file_descriptor = fileno( (FILE*)file_handle );
    err = fsync( file_descriptor );
    if( 0 == err )
    {
      return SNS_SUCCESS;
    }
    else
    {
      return SNS_ERR_FAILED;
    }
  }
}
*/

/*============================================================================

  FUNCTION:   sns_fsa_stat (taken from <APPS sensorS>/dsps/sensordaemon/fsa/src/sns_fsa_la.c)
  TODO: EITHER PULL IN THE FSA FILES FROM THE APPS-SIDE OR TAKE FULL OWNERSHIP OVER THIS FUNCTION

  ============================================================================*/
sns_err_code_e sns_fsa_stat( const char* pathname, sns_fsa_stat_s *fsa_stat )
{
  sns_err_code_e err = SNS_ERR_FAILED;
//  struct stat linux_stat;
//
//  if( pathname != NULL &&
//      fsa_stat != NULL &&
//      0 == stat( pathname, &linux_stat ) )
//  {
//    fsa_stat->size = linux_stat.st_size;
//    err = SNS_SUCCESS;
//  }

  if( pathname != NULL &&
      fsa_stat != NULL )
  {
    fsa_stat->size = 1; // TODO: FIX THIS
    err = SNS_SUCCESS;
  }

  return err;
}

/*===========================================================================

  FUNCTION:   sns_reg_read (taken from <APPS sensorS>/dsps/sensordaemon/reg/src/sns_reg_la.c)
  TODO: EITHER PULL IN THE REG FILES FROM THE APPS-SIDE OR TAKE FULL OWNERSHIP OVER THIS FUNCTION

  ===========================================================================*/
/*!
  @brief Processs a registry read command

  @param[i] buffer_ptr: pointer to buffer where data read from file is stored
  @param[i] offset: offset from the beginning of the file where data should be
                    read
  @param[i] num_butes: number of bytes to be read

  @return
   - SNS_SUCCESS if read is successful.
   - All other values indicate an error has occurred.

  @sideeffects
  Reads data from the registry file.
  Data read from file will be written to memory pointed to by buffer_ptr.
*/
/*=========================================================================*/
sns_err_code_e
sns_reg_read( uint8_t* buffer_ptr,
              uint32_t offset,
              uint16_t num_bytes )
{
  sns_err_code_e err = SNS_ERR_FAILED;
  uint32_t        num_bytes_read = 0;
#ifdef SNS_REG_TEST
  uint16_t        i;
  uint8_t*        byte_ptr;
#endif

  SNS_PRINTF_STRING_LOW_2( SNS_MODULE_APPS_REG, "reg read: offset %d, num bytes: %d",
                           offset, num_bytes );

  if( NULL == reg_file_handle )
  {
//    SNS_PRINTF_STRING_ERROR_0( SNS_MODULE_APPS_REG,
//        "reg_read: reg file not open" );
    return SNS_ERR_FAILED;
  }

  /* start at offset bytes from the beginning of file */
  err = sns_fsa_seek( reg_file_handle, (int64_t)offset, 0 );

  if( SNS_ERR_FAILED != err )
  {
    err = sns_fsa_read( reg_file_handle, buffer_ptr, (uint32_t)num_bytes,
                        &num_bytes_read );
  }

#ifdef SNS_REG_TEST
  /* display data read */
  SNS_PRINTF_STRING_LOW_2( SNS_MODULE_APPS_REG,
                           "sns_reg_read: offset %d, num bytes: %d",
                           offset, num_bytes );
  byte_ptr = buffer_ptr;
  for( i = 0; i < num_bytes; i++ )
  {
    SNS_PRINTF_STRING_LOW_1( SNS_MODULE_APPS_REG, "data: 0x%x", *(byte_ptr) );
    byte_ptr++;
  }
#endif

  if(( SNS_SUCCESS != err ) || ( num_bytes_read != num_bytes ))
  {
    SNS_PRINTF_STRING_ERROR_3( SNS_MODULE_APPS_REG,
                               "read error, err:%d, attempted:%d, read:%d",
                               err, num_bytes, num_bytes_read );
    err = SNS_ERR_FAILED;
  }

  return err;
}

/*===========================================================================

  FUNCTION:   sns_reg_write

  ===========================================================================*/
/*!
  @brief Writes data to the registry file in response to a registry write
         command

  @param[i] buffer_ptr: pointer to buffer containing data to be written
  @param[i] offset: offset from the beginning of the file where data should be
                    written
  @param[i] num_butes: number of bytes to be written
  @param[i] do_flush: If a file flush should be done after the write.

  @return
   - SNS_SUCCESS if write is successful.
   - All other values indicate an error has occurred.

  @sideeffects
  Writes data to the registry file.
*/
/*=========================================================================*/
sns_err_code_e sns_reg_write( uint8_t const *buffer_ptr, uint32_t offset,
                              uint16_t num_bytes, bool do_flush )
{
  uint32_t        num_bytes_written = 0;
  sns_err_code_e  err;
#ifdef SNS_REG_TEST
  uint16_t        i;
  uint8_t*        byte_ptr;
#endif

  SNS_PRINTF_STRING_LOW_2( SNS_MODULE_APPS_REG, "reg write: offset %d, num bytes: %d",
                     offset, num_bytes );

  if( NULL == reg_file_handle )
  {
    SNS_PRINTF_STRING_ERROR_0( SNS_MODULE_APPS_REG,
        "reg write: reg file not open" );
    return SNS_ERR_FAILED;
  }

  /* start at offset bytes from the beginning of file */
  err = sns_fsa_seek( reg_file_handle, (int64_t)offset, 0 );

  if( SNS_SUCCESS == err )
  {
    SNS_PRINTF_STRING_LOW_0( SNS_MODULE_APPS_REG, "reg write: fsa_write");
    err = sns_fsa_write( reg_file_handle, buffer_ptr, (uint32_t)num_bytes,
                         &num_bytes_written );
  }
  /*
  if( true == do_flush )
  {
    err = sns_fsa_flush( reg_file_handle );
  }
  */
#ifdef SNS_REG_TEST
  /* display data written */
  SNS_PRINTF_STRING_LOW_2( SNS_MODULE_APPS_REG,
                           "sns_reg_write: offset %d, num bytes: %d",
                           offset, num_bytes );
  byte_ptr = buffer_ptr;
  for( i = 0; i < num_bytes; i++ )
  {
    SNS_PRINTF_STRING_LOW_1( SNS_MODULE_APPS_REG, "data: 0x%x", *(byte_ptr) );
    byte_ptr++;
  }
#endif

  if( ( SNS_SUCCESS != err ) || ( num_bytes_written != num_bytes ) )
  {
    SNS_PRINTF_STRING_ERROR_3( SNS_MODULE_APPS_REG,
                       "write error, err:%d, attempted:%d, written:%d",
                       err, num_bytes, num_bytes_written );
    err = SNS_ERR_FAILED;
  }
  return err;
}

/*===========================================================================

  FUNCTION:   sns_reg_lookup_item_index

  ===========================================================================*/
int
sns_reg_lookup_item_index( uint16_t item_id )
{
  int i = sns_reg_get_item_count() - 1;
  while( (i >= 0) && (item_id != sns_reg_item_info[i].item_id) )
  {
    i--;
  }
  return i;
}

/*===========================================================================

  FUNCTION:   sns_reg_lookup_group_index

  ===========================================================================*/
int
sns_reg_lookup_group_index( uint16_t group_id )
{
  int i = sns_reg_get_group_count() - 1;
  while( (i >= 0) && (group_id != sns_reg_group_info[i].group_id) )
  {
    i--;
  }
  return i;
}

/*===========================================================================

  FUNCTION:   sns_reg_handle_req

  ===========================================================================*/
sns_err_code_e
sns_reg_handle_req( int entry_id, bool is_read, bool is_item, uint16_t *req_data_len, void *data )
{
  int index;
  sns_err_code_e err = SNS_SUCCESS,
                 rv = SNS_SUCCESS;
  uint16_t offset = 0,
           data_len = 0;

  SNS_PRINTF_STRING_LOW_3( SNS_MODULE_APPS_REG,
                           "entry id: %d, is_read: %d, is_item: %d",
                           entry_id, is_read, is_item);

  if( is_item )
  {
    index = sns_reg_lookup_item_index( entry_id );
  }
  else
  {
    index = sns_reg_lookup_group_index( entry_id );
  }

  if( index < 0 )
  {
    SNS_PRINTF_STRING_ERROR_1( SNS_MODULE_APPS_REG, "Invalid ID: %i", entry_id );
    rv = SNS_ERR_BAD_PARM;
  }
  else
  {
    if( is_item )
    {
      offset = sns_reg_item_info[index].offset;
      data_len = sns_reg_item_size[ sns_reg_item_info[index].type ];
    }
    else
    {
      offset = sns_reg_group_info[index].offset;
      data_len = sns_reg_group_info[index].size;
    }

    if( is_read )
    {
      err = sns_reg_read( data, offset, data_len );
    }
    else if( data_len != *req_data_len )
    {
      SNS_PRINTF_STRING_ERROR_2( SNS_MODULE_APPS_REG,
                                 "invalid data len: %d (%d)",
                                 req_data_len, data_len );
      rv = SNS_ERR_BAD_PARM;
    }
    else
    {
      err = sns_reg_write( data, offset, data_len, true );
    }

    if( SNS_SUCCESS != err )
    {
      SNS_PRINTF_STRING_ERROR_1( SNS_MODULE_APPS_REG,
                                 "Received error from sns_reg_read/write %i",
                                 err );
      rv = SNS_ERR_FAILED;
    }
    else
    {
      *req_data_len = data_len;
    }
  }

  return rv;
}

/**
 * @brief Callback registered with SMR to receive connect requests
 */
static smr_cb_err fpb_registry_smr_connect_cb(
  smr_qmi_client_handle client_handle,
  void*                 service_cookie,
  void**                connection_handle)
{
  // Not much to do for the registry connect callback
  *connection_handle = reg_file_handle;
  //printf("fpb_registry_smr_connect_cb\n");
  return SMR_CB_NO_ERR;
}

/**
 * @brief Callback registered with SMR to receive disconnect requests
 */
static void fpb_registry_smr_disconnect_cb(
  void* connection_handle,
  void* service_cookie)
{
  // Nothing to do for the registry disconnect callback
  //printf("fpb_registry_smr_disconnect_cb\n");
}

/**
 * @brief Callback registered with SMR to receive service requests
 */
static smr_cb_err fpb_registry_smr_process_req_cb(
  void*          connection_handle,
  smr_req_handle req_handle,
  unsigned int   msg_id,
  void*          req_c_struct,
  unsigned int   req_c_struct_len,
  void*          service_cookie)
{
  printf("fpb_registry_smr_process_req_cb msg_id %d\n", msg_id);

  smr_err err;
  uint16_t data_len = 0;
  if( SNS_REG_CANCEL_REQ_V02 == msg_id )
  {
//    TODO: SUPPORT THIS MESSAGE
//    sns_common_cancel_resp_msg_v01 *resp_msg = (sns_common_cancel_resp_msg_v01*)resp_msg_ptr;
//
//    resp_msg->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
//    resp_msg->resp.sns_err_t = SNS_SUCCESS;
    return SMR_CB_NO_ERR;
  }
  else if( SNS_REG_VERSION_REQ_V02 == msg_id )
  {
    sns_common_version_resp_msg_v01 resp_msg;

    resp_msg.resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
    resp_msg.resp.sns_err_t = SNS_SUCCESS;
    resp_msg.interface_version_number = SNS_REG2_SVC_V02_IDL_MINOR_VERS;
    resp_msg.max_message_id = SNS_REG2_SVC_V02_MAX_MESSAGE_ID;

    err = smr_service_send_resp(req_handle, msg_id, &resp_msg, sizeof(resp_msg));
    if (SMR_NO_ERR != err)
    {
      printf("ERROR: Unable to send registry response %d\n", err);
    }

    return SMR_CB_NO_ERR;
  }
  else if( SNS_REG_SINGLE_READ_REQ_V02 == msg_id )
  {
    sns_reg_single_read_resp_msg_v02 resp_msg;

    resp_msg.item_id = ((sns_reg_single_read_req_msg_v02*)req_c_struct)->item_id;
    printf("registry single_read_req item_id %d\n", resp_msg.item_id);

    err = sns_reg_handle_req( resp_msg.item_id, true, true, &data_len, resp_msg.data );
    if( SNS_SUCCESS == err )
    {
      resp_msg.data_len = data_len;
      resp_msg.resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      resp_msg.resp.sns_err_t = SNS_SUCCESS;
    }
    else
    {
      /* If it was not successful, respond back with a data_len of 0. This
         should signify to the registry client that there was nothing read
         for the requested item/group. */
      resp_msg.data_len = 0;
      resp_msg.resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      resp_msg.resp.sns_err_t = SNS_SUCCESS;
    }

    err = smr_service_send_resp(req_handle, msg_id, &resp_msg, sizeof(resp_msg));
    if (SMR_NO_ERR != err)
    {
      printf("ERROR: Unable to send registry response %d\n", err);
    }
  }
  else if( SNS_REG_GROUP_READ_REQ_V02 == msg_id )
  {
    sns_reg_group_read_resp_msg_v02 resp_msg;


    resp_msg.group_id = ((sns_reg_group_read_req_msg_v02*)req_c_struct)->group_id;
    printf("registry group_read_req group_id %d\n", resp_msg.group_id);

    err= sns_reg_handle_req( resp_msg.group_id, true, false, &data_len, resp_msg.data );
    if( SNS_SUCCESS == err )
    {
      resp_msg.data_len = data_len;
      resp_msg.resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      resp_msg.resp.sns_err_t = SNS_SUCCESS;
    }
    else
    {
      /* If it was not successful, respond back with a data_len of 0. This
         should signify to the registry client that there was nothing read
         for the requested item/group. */
      resp_msg.data_len = 0;
      resp_msg.resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      resp_msg.resp.sns_err_t = SNS_SUCCESS;
    }

    err = smr_service_send_resp(req_handle, msg_id, &resp_msg, sizeof(resp_msg));
    if (SMR_NO_ERR != err)
    {
      printf("ERROR: Unable to send registry response %d\n", err);
    }
  }
  else if( SNS_REG_SINGLE_WRITE_REQ_V02 == msg_id )
  {
    sns_reg_group_write_resp_msg_v02 resp_msg;
    sns_reg_single_write_req_msg_v02 *req_msg = (sns_reg_single_write_req_msg_v02*)req_c_struct;
    data_len = req_msg->data_len;
    err = sns_reg_handle_req( req_msg->item_id, false, true, &data_len, req_msg->data );
    resp_msg.resp.sns_result_t =
       (SNS_SUCCESS == err) ? SNS_RESULT_SUCCESS_V01 : SNS_RESULT_FAILURE_V01;
    resp_msg.resp.sns_err_t = SNS_SUCCESS; //QTODO proper error handling
    err = smr_service_send_resp(req_handle, msg_id, &resp_msg, sizeof(resp_msg));
    if (SMR_NO_ERR != err)
    {
      printf("ERROR: Unable to send registry response %d\n", err);
    }
  }
  else if( SNS_REG_GROUP_WRITE_REQ_V02 == msg_id )
  {
    sns_reg_group_write_resp_msg_v02 resp_msg;
    sns_reg_group_write_req_msg_v02 *req_msg = (sns_reg_group_write_req_msg_v02*)req_c_struct;
    data_len = req_msg->data_len;
    err = sns_reg_handle_req( req_msg->group_id, false, false, &data_len, req_msg->data );
    resp_msg.resp.sns_result_t =
       (SNS_SUCCESS == err) ? SNS_RESULT_SUCCESS_V01 : SNS_RESULT_FAILURE_V01;
    resp_msg.resp.sns_err_t = SNS_SUCCESS;
    err = smr_service_send_resp(req_handle, msg_id, &resp_msg, sizeof(resp_msg));
    if (SMR_NO_ERR != err)
    {
      printf("ERROR: Unable to send registry response %d\n", err);
    }
  }
  else
  {
    SNS_PRINTF_STRING_ERROR_0( SNS_MODULE_APPS_REG, "Invalid msg id" );
    return SMR_CB_UNSUPPORTED_ERR;
  }

//  resp_msg_ptr->sns_result_t =
//    (SNS_SUCCESS == err) ? SNS_RESULT_SUCCESS_V01 : SNS_RESULT_FAILURE_V01;
//  resp_msg_ptr->sns_err_t = sns_reg_conv_err( err );

  return SMR_CB_NO_ERR;
}


/*============================================================================
  Public Function Definitions
  ===========================================================================*/

sns_err_code_e fpb_registry_storage_init( const char* sns_reg_filename )
{
  void*           group_ptr = NULL;
  uint16_t        group_count = sns_reg_get_group_count();
  int_fast16_t    i;
  sns_err_code_e  err = SNS_SUCCESS;
  sns_fsa_stat_s  stat;
  reg_file_handle = NULL;

#ifdef SNS_LA_SIM
  {
    /* For the LA Simulator, append the TID & a random number to the end of the filename */
    char postpend[80];
    snprintf( postpend, sizeof(postpend), ".%s", getlogin() );
    strlcat( sns_reg_filename, postpend, sizeof(sns_reg_filename) );
  }
#endif /* SNS_LA_SIM */

  stat.size = 0;
  err = sns_fsa_stat( sns_reg_filename, &stat );

  if( err != SNS_SUCCESS || stat.size == 0 )
  { /* file does not exist, or is size 0 */
    printf("WARNING: Unable to stat the registry. No registry input will be used.");
    return( SNS_ERR_FAILED );
  }
  else
  { /* If file already exists */
    reg_file_handle = sns_fsa_open( sns_reg_filename, "r+" );

    if( NULL == reg_file_handle )
    {
      SNS_PRINTF_STRING_ERROR_0( SNS_MODULE_APPS_REG,
          "ERROR: Error opening registry file" );
      return( SNS_ERR_FAILED );
    }
  }

  return SNS_SUCCESS;
}

sns_err_code_e fpb_registry_register_service(void)
{
  smr_err err;

  // Register the Registry Service
  err = smr_service_register(SNS_REG2_SVC_get_service_object_v02(),
                             SNS_SMR_SVC_PRI_MED,
                             fpb_registry_smr_connect_cb,
                             fpb_registry_smr_disconnect_cb,
                             NULL,
                             fpb_registry_smr_process_req_cb,
                             &fpb_registry_service_handle,
                             &fpb_registry_service_cookie);

  if (SMR_NO_ERR != err)
  {
    printf("Error registering Registry service smr_err %d\n", err);
    return SNS_ERR_FAILED;
  }

  return SNS_SUCCESS;
}
void
sns_reg_task( void *argPtr )
{
  UNREFERENCED_PARAMETER(argPtr);
  uint8_t errOS;
  OS_FLAGS sigFlags;
  fpb_registry_storage_init(registry_file_name);
  fpb_registry_register_service();

  sns_init_done();

  sigFlags = sns_os_sigs_pend( playback_reg_sig_event,
    (OS_FLAGS) FPB_REG_SIG,
     OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 5, &errOS );

  sns_fsa_close(reg_file_handle);

  sns_deinit_done();
}

sns_err_code_e
sns_reg_init( void )
{
  uint8_t errOS;
  uint32_t i;

  errOS = sns_os_task_create_ext( sns_reg_task, NULL,
      &sns_reg_task_stk[ SNS_REG_MODULE_STK_SIZE - 1 ], SNS_REG_MODULE_PRIORITY,
      SNS_REG_MODULE_PRIORITY, &sns_reg_task_stk[0], SNS_REG_MODULE_STK_SIZE,
      (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_ISLAND,
      (uint8_t*)("SNS_REG") );

  SNS_ASSERT( OS_ERR_NONE == errOS );
  return SNS_SUCCESS;
}

