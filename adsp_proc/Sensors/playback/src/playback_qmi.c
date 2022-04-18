#include "qmi_idl_lib_internal.h"
#include "qmi_idl_lib.h"

/*===========================================================================
  FUNCTION  qmi_idl_inherit_service_object
===========================================================================*/
/*!
@brief
  Returns a parent service object that was previously inherited.

@param[in] service    The service object that will be used with QCCI/QCSI

@retval inherited service object, or NULL

*/
/*=========================================================================*/
qmi_idl_service_object_type qmi_idl_get_inherited_service_object
(
  qmi_idl_service_object_type service
)
{
  if( !service || service->library_version < 5 )
  {
    return NULL;
  }
  return service->parent_service_obj;
}

#if 0
/***********************************************************************

FUNCTION qmi_idl_find_msg

DESCRIPTION
  Search list of messages for message with matching message ID.

ARGUMENTS p_service - pointer to service object
          message_type - Request/Response/Indication (different list for
              each message type.
          message_id - ID to search for
          out_type_table - Output param,Pointer to referenced type table object
                           in case the message is defined in the included IDL.
                           Pointer to local type table object in case the
                           message defined is local.

RETURN VALUE pointer to start of message table entry

***********************************************************************/
const qmi_idl_message_table_entry *qmi_idl_find_msg
(
  const qmi_idl_service_object_type p_service,
  qmi_idl_type_of_message_type message_type,
  uint16_t message_id,
  int *exc,
  const qmi_idl_type_table_object **out_type_table
)
{
  const qmi_idl_service_message_table_entry *p_srvmsg = NULL;
  const qmi_idl_message_table_entry *p_msg;
  qmi_idl_service_object_type inheritance_obj;
  uint32_t table_index;
  uint32_t type_index;
  uint32_t i = 0;
  int imin,imax,imid;

  if (!p_service)
  {
//    QMI_IDL_HANDLE_ERROR( exc, QMI_IDL_LIB_PARAMETER_ERROR, 0, 0, 0 );
  }
  inheritance_obj = p_service;
  while (inheritance_obj)
  {
    imin=0;
    /* Binary search for the table entry for the message ID */
    p_srvmsg = inheritance_obj->msgid_to_msg[message_type];
    imax = inheritance_obj->n_msgs[message_type] - 1;
    while (imax >= imin)
    {
      imid = (imax+imin) >> 1;
      if (p_srvmsg[imid].qmi_message_id < message_id)
      {
        imin = imid +1;
      }else if(p_srvmsg[imid].qmi_message_id > message_id)
      {
        imax = imid - 1;
      }else
      {
        i=1;
        p_srvmsg = &p_srvmsg[imid];
        break;
      }
    }
    if (i != 0)
    {
      break;
    }
    inheritance_obj = qmi_idl_get_inherited_service_object(inheritance_obj);
  }
  if (0 == i)
  {
//    QMI_IDL_HANDLE_ERROR( exc, QMI_IDL_LIB_MESSAGE_ID_NOT_FOUND,
//                          message_id, 0, 0 );
  }

  /* Found the service message table entry for this message ID.  Now
   * get the table and type index */
  table_index = QMI_IDL_MSG_TYPE_TABLE(p_srvmsg->message_table_message_id);
  type_index = QMI_IDL_MSG_TYPE_TYPE(p_srvmsg->message_table_message_id);
  if (out_type_table)
  {
    *out_type_table = inheritance_obj->p_type_table->
                      p_referenced_tables[table_index];
  }
  /* Use the table and type index to get the message table entry with
   * the actual data needed for decoding */
  p_msg = &(inheritance_obj->p_type_table->p_referenced_tables[table_index]->
            p_messages[type_index]);
return p_msg;
} /* qmi_idl_find_msg */
#endif

/*===========================================================================
  FUNCTION  qmi_idl_get_service_id
===========================================================================*/
/*!
@brief
  Accessor function for getting the service ID from a service object.

@param[in]  service        Pointer to service object, result from service
                           object accessor function from service header file.
@param[out] service_id     Pointer to return value, the service ID

@retval    QMI_IDL_LIB_NO_ERR     Success
@retval    QMI_IDL_...    Error, see error codes defined in qmi_idl_lib.h

*/
/*=========================================================================*/
int32_t qmi_idl_get_service_id
(
  const qmi_idl_service_object_type p_service,
  uint32_t *service_id
)
{
  int32_t ret = QMI_IDL_LIB_NO_ERR;

  if( p_service == NULL || service_id == NULL ) {
    return QMI_IDL_LIB_PARAMETER_ERROR;
  }
  switch( p_service->library_version ) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    *service_id = p_service->service_id;
    break;


  default:
    ret = QMI_IDL_LIB_UNRECOGNIZED_SERVICE_VERSION;
    break;
  }

  return ret;
} /* qmi_idl_get_service_id */


/*===========================================================================
  FUNCTION  qmi_idl_get_message_c_struct_len
===========================================================================*/
/*!
@brief
  Accessor function for getting the c struct size for a particular
  message.

@param[in]  service       Pointer to service object, result from service
                          object accessor function from service header file.
@param[in]  message_type  The type of message: request, response, or indication.
@param[in]  message_id    Message ID from IDL.
@param[out] c_struct_len  Pointer to the return value, the c struct size for
                          structure corresponding to the service,message type
                          and message_id.

@retval    QMI_IDL_LIB_NO_ERR     Success
@retval    QMI_IDL_...    Error, see error codes defined in qmi_idl_lib.h

*/
/*=========================================================================*/
int32_t qmi_idl_get_message_c_struct_len
(
  const qmi_idl_service_object_type p_service,
  qmi_idl_type_of_message_type message_type,
  uint16_t message_id,
  uint32_t *c_struct_len
)
{
  const qmi_idl_message_table_entry *p_srvmsg;

//  /* Exception handling variables */
//  qmi_idl_lib_exception_type exc;

  /* Set up exception handling */
//  QMI_IDL_LIB_TRY(&exc)
//  {
//    if( p_service == NULL ||
//        message_type >= QMI_IDL_NUM_MSG_TYPES ||
//        c_struct_len == NULL )
//    {
//      QMI_IDL_HANDLE_ERROR( &exc, QMI_IDL_LIB_PARAMETER_ERROR, 0, 0, 0 );
//    }

    switch( p_service->library_version )
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        /* Find the appropriate message to return the desired c struct size */
        p_srvmsg = qmi_idl_find_msg( p_service, message_type, message_id, NULL,
            NULL );

        *c_struct_len = (uint32_t) p_srvmsg->c_struct_sz;
        break;
    default:
//      QMI_IDL_HANDLE_ERROR( &exc, QMI_IDL_LIB_UNRECOGNIZED_SERVICE_VERSION,
//                            p_service->library_version, 0, 0 );
      break;
    }
//  } QMI_IDL_LIB_CATCH(&exc) {
//    return QMI_IDL_LIB_GET_ERROR(&exc);
//  }

  return QMI_IDL_LIB_NO_ERR;
}

/*===========================================================================
  FUNCTION  qmi_idl_get_idl_minor_version
===========================================================================*/
int32_t qmi_idl_get_idl_minor_version
(
  const qmi_idl_service_object_type p_service,
  uint32_t *idl_version
)
{
  int32_t ret = QMI_IDL_LIB_NO_ERR;
  if( p_service == NULL || idl_version == NULL ) {
    return QMI_IDL_LIB_PARAMETER_ERROR;
  }
  switch( p_service->library_version ) {
  case 1:
  case 2:
  case 3:
  case 4:
    ret = QMI_IDL_LIB_INCOMPATIBLE_SERVICE_VERSION;
    break;
  case 5:
  case 6:
    *idl_version = p_service->idl_minor_version;
    break;
  default:
    ret = QMI_IDL_LIB_UNRECOGNIZED_SERVICE_VERSION;
    break;
  }

  return ret;
} /* qmi_idl_get_idl_version */

/*===========================================================================
  FUNCTION  qmi_idl_get_max_message_len
===========================================================================*/
/*!
@brief
  Accessor function for getting the maximum message length for a particular
  message.

@param[in]  service       Pointer to service object, result from service
                          object accessor function from service header file.
@param[in]  message_type  The type of message: request, response, or indication.
@param[in]  message_id    Message ID from IDL.
@param[out] message_len   Pointer to the return value, the maximum message
                          length for the service, message type, and message ID.

@retval    QMI_IDL_LIB_NO_ERR     Success
@retval    QMI_IDL_...    Error, see error codes defined in qmi_idl_lib.h

*/
/*=========================================================================*/
int32_t qmi_idl_get_max_message_len
(
  const qmi_idl_service_object_type p_service,
  qmi_idl_type_of_message_type message_type,
  uint16_t message_id,
  uint32_t *message_len
)
{
  const qmi_idl_service_message_table_entry *p_srvmsg = NULL;
  qmi_idl_service_object_type inheritance_obj;
  uint32_t i = 0;

  /* Exception handling variables */
//  qmi_idl_lib_exception_type exc;

  /* Set up exception handling */
//  QMI_IDL_LIB_TRY(&exc) {
//    if( p_service == NULL ||
//        message_type >= QMI_IDL_NUM_MSG_TYPES ||
//        message_len == NULL )
//    {
//      QMI_IDL_HANDLE_ERROR(&exc, QMI_IDL_LIB_PARAMETER_ERROR, 0, 0, 0 );
//    }
    inheritance_obj = p_service;
    switch( p_service->library_version )
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      while (inheritance_obj)
      {
        /* Linear search for the table entry for the message ID */
        p_srvmsg = inheritance_obj->msgid_to_msg[message_type];
        i = inheritance_obj->n_msgs[message_type];
        while (i != 0 && p_srvmsg->qmi_message_id != message_id)
        {
          ++p_srvmsg;
          --i;
        }
        if (i != 0)
        {
          break;
        }
        inheritance_obj = qmi_idl_get_inherited_service_object(inheritance_obj);
      }
//      if (0 == i)
//      {
//        QMI_IDL_HANDLE_ERROR(&exc, QMI_IDL_LIB_MESSAGE_ID_NOT_FOUND,
//                             message_id, 0, 0 );
//      }
      *message_len = (uint32_t) p_srvmsg->max_msg_len;
      break;

      default:
//        QMI_IDL_HANDLE_ERROR(&exc, QMI_IDL_LIB_UNRECOGNIZED_SERVICE_VERSION,
//                             p_service->library_version, 0, 0 );
        break;
    }
//  } QMI_IDL_LIB_CATCH(&exc) {
//    return QMI_IDL_LIB_GET_ERROR(&exc);
//  }

  return QMI_IDL_LIB_NO_ERR;
} /* qmi_idl_get_max_message_len */
