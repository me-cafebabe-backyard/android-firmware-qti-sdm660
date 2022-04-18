/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                   Diagnostic Communications for Diag Control Channel

General Description

Copyright (c) 2010-2017 by QUALCOMM Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.qdsp6/1.0.c2/services/diag/DCM/common/src/diagcomm_ctrl.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/21/17   ph      Tag DIAG ID header to all the diag packets sent out.
07/22/16   gn      Removal of pointer passing from peripheral processors to APPS processor
05/12/16   ph      SMD references removal and code clean up.
03/10/16   sa      Fixed the PD user table fwding.
08/21/15   as      Resolved Diag signal conflicts
07/16/14   sr      Resolved KW errors
04/10/14   sr      Support for peripheral buffering mode
04/01/14   rs      Added support for build mask centralization.
11/27/13   ph      Updated MSG 1.0 API references to MSG.2.0.
11/22/13   sr      Removed PACK from pointer references
08/02/13   rh      Added flow control logic for control channel pools
06/03/13   ph      Fixed a corner case where diagpkt_table_fwd_status was not updated.
04/18/13   ph      Replace memcpy() and memmove() with memscpy() and memsmove()
02/11/13   sr      Mainling Diag central routing
01/03/13   sg      Command Response Channel separation
11/15/12   is      Support for preset masks
07/05/12   sg      Changes to bring up diag Multi PD
03/02/12   sg      Added function to return the channel connected status
                   for the ctrl port, call diagcomm_io_detection() while
                   opening the ctrl channel to register with dtr changes
                   for the ctrl port
10/07/11   is      Support sending log mask per equipment id
09/19/11   is      Optimized sending F3 "set mask" requests from Master Diag
09/12/11   is      Master Diag forwards "set mask" requests via CTRL msgs
08/11/11   wjg     Added function to handle processing DIAG_CTRL_MSG_SIG
04/27/11   is      Resolve compiler warnings
04/18/11   is      Ensure CTRL msg sizes are constant
03/29/11   sg      Central Routing changes for Q6
03/04/11   is      Support for Diag over SMD-Lite
03/02/11   hm      Support SIO control channel on single processor for
                   dual-mask feature
12/20/10   mad     Changes for dual mask: Open SIO control port in MASTER DIAG
12/08/10   mad     do not open CTRL port if already open: do not reset
                   diagcomm_ctrl_conn
10/14/10   mad     Diag now blocks until control port finishes closing
10/20/10   is      Resolve compilation issue in Apps only Diag
09/28/10   mad     Closing control port in diagcomm_ctrl_close
09/14/10   is      New control channel and central routing features

===========================================================================*/

#include "diag_v.h"
#if defined (DIAG_QDSP6_APPS_PROC)
#include "diagstub.h"
#else
#include "assert.h" /* For assert */
#endif

#include "diagbuf.h"         // For diagbuf_drain()
#include "diagcomm_ctrl.h"
#include "diagi_v.h"         // For DIAG_TX_SLAVE_SIG, diagpkt_process_ctrl_msg()
#include "diagpkt.h"         // For DIAGPKT_DISPATCH_TABLE_REGISTER_SLAVE()
#include "msg.h"             // For MSG_1, MSG_2 etc.
#include "osal.h"            // For osal* functions
#include "feature.h"         // For DIAG_INT_FEATURE_MASK_LEN
#include "stringl.h"
#include "diagdiag_v.h"
#include "memheap.h"
#include "queue.h"

extern osal_tcb_t diag_tcb;
extern diagcomm_io_conn_type diagcomm_io_ctrl_conn[NUM_PORT_TYPES][NUM_REMOTE_PORTS]; /* From diagcomm_io.c */

// Data structures to enable resending of CTRL packets in case of flow control
static q_type diagcomm_ctrl_resend_q;
static char diag_ctrl_heap_buf[DIAG_CTRL_RESEND_BUF_SIZE];
mem_heap_type diag_ctrl_heap;
static uint32 diag_ctrl_heap_malloc_count, diag_ctrl_heap_free_count;

static uint8 diagbuf_send_ctrl[NUM_REMOTE_PORTS][DIAG_CTRL_SEND_BUF_SIZE]; /*Buffer used to send out ctrl channel data */
static uint16 diag_send_buf_ctrl_index[NUM_REMOTE_PORTS] = {0, 0}; /*Current ctrl buffer index*/

typedef struct
{
   q_link_type qlink;
   void* buf;
   uint32 length;
}ctrl_resend_pkt_type;

typedef struct
{
	word cmd_code_lo; /*!<  Minimum Command code value  */
	word cmd_code_hi; /*!< Maximum Command code value   */
	uint32 data;
}
diag_ctrl_user_tbl_type;
/*-------------------------------------------------------------------------
                   Local function prototype
 ------------------------------------------------------------------------- */
static int diagcomm_ctrl_heap_init();
static void * diag_ctrl_malloc (uint32 num_bytes);
static void diag_ctrl_free(void *mem_ptr);
void diagcomm_process_inbound_ctrl_msg( diagcomm_port_type port_type, diagcomm_enum_port_type ctrl_channel );


char diag_ctrl_pkt_inbound[DIAG_CTRL_READ_BUF_SIZE];

/*===========================================================================

FUNCTION DIAGCOMM_PROCESS_CTRL

DESCRIPTION
  Process control traffic when DIAG_CTRL_MSG_SIG received.

PARAMETERS
  None

RETURN VALUE
  None

===========================================================================*/
void
diagcomm_process_ctrl( void )
{
  diagcomm_process_inbound_ctrl_msg (DIAGCOMM_PORT_REMOTE_PROC, DIAGCOMM_PORT_1);

}

/*===========================================================================

FUNCTION DIAGCOMM_PROCESS_INBOUND_CTRL_MSG

DESCRIPTION
  Process inbound traffic recieved via control channel.

PARAMETERS
  port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel

RETURN VALUE
  None

===========================================================================*/

void
diagcomm_process_inbound_ctrl_msg( diagcomm_port_type port_type,
                                   diagcomm_enum_port_type ctrl_channel )
{
  diagcomm_io_conn_type * conn = &diagcomm_io_ctrl_conn[DIAGCOMM_PORT_REMOTE_PROC][ctrl_channel];
  uint32 num_used = 0;

  osal_lock_mutex(&conn->buf_mutex);
  num_used = conn->used;
  memscpy(&diag_ctrl_pkt_inbound[0], sizeof(diag_ctrl_pkt_inbound), conn->buf,conn->used);
  //Reset used to zero to read in more data
  conn->used = 0;
  osal_unlock_mutex(&conn->buf_mutex);

  diagpkt_process_ctrl_msg( &diag_ctrl_pkt_inbound[0], num_used, port_type, ctrl_channel );
  }

/*===========================================================================

FUNCTION DIAGCOMM_CTRL_STATUS

DESCRIPTION
  This function returns TRUE if the communications layer has an open port.

PARAMETERS
  port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel

RETURN VALUE
  True if the logical control stream is connected.
  False otherwise.

===========================================================================*/
boolean
diagcomm_ctrl_status ( diagcomm_port_type port_type,
                       diagcomm_enum_port_type ctrl_channel )
{
  return (diagcomm_io_ctrl_conn[port_type][ctrl_channel].connected &&
          diagcomm_io_ctrl_conn[port_type][ctrl_channel].channel_connected);

} /* diagcomm_ctrl_status */

/*===========================================================================

FUNCTION DIAGCOMM_CTRL_CHANNEL_STATUS

DESCRIPTION
  This function returns TRUE if the communications layer has an open port
  and the port is opened on the remote processor.

PARAMETERS
  port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel

RETURN VALUE
  True if the logical control stream is connected.
  False otherwise.

===========================================================================*/
boolean
diagcomm_ctrl_channel_status( diagcomm_port_type port_type,
                              diagcomm_enum_port_type ctrl_channel )
{
  return (diagcomm_io_ctrl_conn[port_type][ctrl_channel].connected &&
          diagcomm_io_ctrl_conn[port_type][ctrl_channel].channel_connected);
} /* diagcomm_ctrl_channel_status */

/*===========================================================================

FUNCTION DIAGCOMM_CTRL_OPEN

DESCRIPTION
  Opens the communcications stream.

PARAMETERS
  ctrl_port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel to open

RETURN VALUE
  True if control port opened successfully.
  False otherwise.

===========================================================================*/
boolean
diagcomm_ctrl_open( diagcomm_port_type port_type, diagcomm_enum_port_type ctrl_channel )
{
  diagcomm_io_conn_type * conn = &diagcomm_io_ctrl_conn[port_type][ctrl_channel];


  if( !conn->connected )
  {
    if( diagcomm_io_open(conn) == TRUE )
    {
      conn->connected = TRUE;
    }
    else
    {
      MSG(MSG_SSID_DIAG, MSG_LEGACY_LOW,"diagcomm_ctrl_open - Couldn't get stream.");
    }
  }

  return conn->connected;

} /* diagcomm_ctrl_open */

/*===========================================================================

FUNCTION diagcomm_ctrl_add_to_queue

DESCRIPTION
  This function adds the ctrl packet that was not sent to a queue to be sent later

PARAMETERS
  tx_params -The tx parameters which include the buffer and length.

RETURN VALUE
  DIAG_EOK - if adding to the queue succeeds.
  DIAG_EMEM - if the available memory on the heap is exhausted.
  DIAG_EPARAM - if the parameters passed are invalid.

===========================================================================*/
int diagcomm_ctrl_add_to_queue(  diagcomm_io_tx_params_type *tx_params)
{
   ctrl_resend_pkt_type *q_item;

   if(NULL == tx_params) return DIAG_EPARAM;
   q_item = (ctrl_resend_pkt_type *)diag_ctrl_malloc(sizeof(ctrl_resend_pkt_type));

   if(NULL == q_item)
   {
      MSG_1(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"diag_ctrl_malloc failed for item length %d",sizeof(ctrl_resend_pkt_type));
      return DIAG_EMEM;
   }
   memset(q_item,0,sizeof(ctrl_resend_pkt_type));
   (void) q_link(q_item,&q_item->qlink);
   q_item->buf = (void *)diag_ctrl_malloc(tx_params->len);

   if(NULL == q_item->buf)
   {
      MSG_1(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"diag_ctrl_malloc failed for buffer length: %d",tx_params->len);
      //Free the item pointer allocated earlier.
      diag_ctrl_free(q_item);
      return DIAG_EMEM;
   }
   //Copy the buffer and set the queue links
   memscpy(q_item->buf,tx_params->len, tx_params->buffer,tx_params->len);
   q_item->length = tx_params->len;
   //Put the q_item in the resend queue.
   q_put(&diagcomm_ctrl_resend_q, &(q_item->qlink));
   return DIAG_EOK;

}

/*===========================================================================

FUNCTION DIAGCOMM_CTRL_SEND_MULT_PKT

DESCRIPTION
  This function aggregates multiple ctrl packets to be sent in one buffer and
  transmits it via 'ctrl_channel' when it's full. Client may also opt to send
  the packet immediately by setting 'send_now' to True.

PARAMETERS
  ctrl_pkt - The data packet to aggregate into the send buffer
  ctrl_pktlen - The length of 'ctrl_pkt'
  user_pkt - Additional data packet to aggregate into the buffer.
             Used for additional variable length data appended to 'ctrl_pkt'.
  user_pktlen - The length of 'user_pktlen'
  port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel to transmit the data to
  send_now - If True, aggregate 'ctrl_pkt' into the buffer (if any) and transmit
               immediately.
             If False, aggregate 'ctrl_pkt' into the send buffer and transmit only
               when full.
  is_sent [out] - Returns True if the buffer was sent. False otherwise.

RETURN VALUE
  The number of bytes newly aggregated into the existing buffer.

 WARNING
  This function may only be called by the diag task.  It is not re-entrant!

===========================================================================*/
uint32
diagcomm_ctrl_send_mult_pkt( PACK(void *) ctrl_pkt,
                             uint32 ctrl_pktlen,
                             PACK(const void *) user_pkt,
                             uint32 user_pktlen,
                             diag_ctrl_user_pkt_type user_pkt_type,
                             diagcomm_port_type port_type,
                             diagcomm_enum_port_type ctrl_channel,
                             boolean send_now,
                             boolean * is_sent )
{
  uint32 added_pkt_len = 0;
  uint8 * cur_data_ptr = NULL;
  boolean retry = FALSE;
  diagcomm_io_tx_params_type tx_params;
  diag_ctrl_user_tbl_type user_tbl;
  diag_ctrl_user_tbl_type * usertbl_ptr = NULL;
  int k = 0;
  uint8 usertbl_count = 0;
  uint8 usertbl_len = 0;
  diagcomm_ctrl_lsm_cmd_reg_type* user_pkt_id_1 = NULL;
  /* Sanity check */
  if(( !is_sent) || (ctrl_pktlen > DIAG_CTRL_SEND_BUF_SIZE))
  {
    MSG(MSG_SSID_DIAG, MSG_LEGACY_LOW,"diagcomm_ctrl_send_mult_pkt - Sanity check failed");
    return added_pkt_len;
  }
  *is_sent = FALSE;

  if( !ctrl_pkt || (ctrl_pktlen <= 0))
  {
    if( send_now && (diag_send_buf_ctrl_index[ctrl_channel] != 0) )
    {
      /* Just send immediately if there's no pkt to write */
      tx_params.buffer = diagbuf_send_ctrl[port_type];
      tx_params.len = diag_send_buf_ctrl_index[ctrl_channel];
      if(DIAG_EOK != diagcomm_io_transmit(&diagcomm_io_ctrl_conn[port_type][ctrl_channel], &tx_params))
      {
         diagcomm_ctrl_add_to_queue(&tx_params);
      }
      *is_sent = TRUE;
      diag_send_buf_ctrl_index[ctrl_channel] = 0;
    }
    else
    {
      MSG_2(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"diagcomm_ctrl_send_mult_pkt - No pkt to write 0x%x %d", ctrl_pkt, ctrl_pktlen);
    }
    return added_pkt_len;
  }

  if( !diagcomm_io_ctrl_conn[DIAGCOMM_PORT_REMOTE_PROC][DIAGCOMM_PORT_1].allow_flow )
  {
    return added_pkt_len;
  }
  do
  {
    retry = FALSE;

     /*If the data to be sent does not fit in the buffer then send the current buffer*/
     if ((ctrl_pktlen +  user_pktlen + diag_send_buf_ctrl_index[ctrl_channel]) > (DIAG_CTRL_SEND_BUF_SIZE))
    {
        if (diag_send_buf_ctrl_index[ctrl_channel] != 0)
        {
            /* Send the buffer immediately */
           tx_params.buffer = diagbuf_send_ctrl[port_type];
           tx_params.len = diag_send_buf_ctrl_index[ctrl_channel];
           if (DIAG_EOK != diagcomm_io_transmit(&diagcomm_io_ctrl_conn[port_type][ctrl_channel], &tx_params)) {
              diagcomm_ctrl_add_to_queue(&tx_params);
           }
            *is_sent = TRUE;
           diag_send_buf_ctrl_index[ctrl_channel] = 0;
        }
    }

     if ((diag_send_buf_ctrl_index[ctrl_channel] + ctrl_pktlen + user_pktlen) <= DIAG_CTRL_SEND_BUF_SIZE)
    {
        // Append ctrl_pkt
        cur_data_ptr = &diagbuf_send_ctrl[port_type][diag_send_buf_ctrl_index[ctrl_channel]];
        memscpy((void *)cur_data_ptr, (DIAG_CTRL_SEND_BUF_SIZE - diag_send_buf_ctrl_index[ctrl_channel]), (void *)ctrl_pkt, ctrl_pktlen);
        diag_send_buf_ctrl_index[ctrl_channel] += ctrl_pktlen;
        added_pkt_len = ctrl_pktlen;

        // Append user_pkt if any
        if ((user_pkt != NULL) && (user_pktlen > 0))
        {
           switch (user_pkt_type)
           {
            case DIAG_CTRL_USER_PKT_ID_0:
            {
                 cur_data_ptr = &diagbuf_send_ctrl[port_type][diag_send_buf_ctrl_index[ctrl_channel]];
                 memscpy((void *)cur_data_ptr, (DIAG_CTRL_SEND_BUF_SIZE - diag_send_buf_ctrl_index[ctrl_channel]),
                         (void *)user_pkt, user_pktlen);
                 diag_send_buf_ctrl_index[ctrl_channel] += user_pktlen;
                 added_pkt_len += user_pktlen;
                 break;
              }
           case DIAG_CTRL_PKT_USER_CMD_REG:
              {
                 user_pkt_id_1 = (diagcomm_ctrl_lsm_cmd_reg_type*) user_pkt;

                 for (k = 0; k < user_pkt_id_1->count; k++)
                 {
                    user_tbl.cmd_code_lo = user_pkt_id_1->q_item->master_tbl_entry[k].cmd_code_lo;
                    user_tbl.cmd_code_hi = user_pkt_id_1->q_item->master_tbl_entry[k].cmd_code_hi;
                    user_tbl.data = 0;
                    cur_data_ptr = &diagbuf_send_ctrl[port_type][diag_send_buf_ctrl_index[ctrl_channel]];
                    memscpy(cur_data_ptr, (DIAG_CTRL_SEND_BUF_SIZE - diag_send_buf_ctrl_index[ctrl_channel]), &user_tbl, sizeof(user_tbl));
                    diag_send_buf_ctrl_index[ctrl_channel] += sizeof(user_tbl);
				 }
                    added_pkt_len += user_pktlen;
                    break;
                 }
		   case DIAG_CTRL_PKT_CORE_CMD_REG:
			  {
			     //cur_data_ptr = dsm_item_ptr_sav->data_ptr + dsm_item_ptr_sav->used;
				 usertbl_ptr = (diag_ctrl_user_tbl_type *) user_pkt;	
				 usertbl_len = sizeof(user_tbl);
				 usertbl_count = user_pktlen/sizeof(diagpkt_user_table_entry_type);
				 for(;usertbl_count > 0;usertbl_count--)
				 {
	                 user_tbl.cmd_code_lo = usertbl_ptr->cmd_code_lo;
					 user_tbl.cmd_code_hi = usertbl_ptr->cmd_code_hi;
					 user_tbl.data = 0;
					 cur_data_ptr = &diagbuf_send_ctrl[port_type][diag_send_buf_ctrl_index[ctrl_channel]];
					 memscpy((void *)cur_data_ptr, (DIAG_CTRL_SEND_BUF_SIZE - diag_send_buf_ctrl_index[ctrl_channel]),
                         &user_tbl, usertbl_len);
					 diag_send_buf_ctrl_index[ctrl_channel] += usertbl_len;
					 usertbl_ptr++;
				 }
				 added_pkt_len += user_pktlen;
                 break;
		      }
           default:
              break;
        }
        }

        if( send_now )
        {
           // Send the current DSM immediately
           tx_params.buffer = diagbuf_send_ctrl[port_type];
           tx_params.len = diag_send_buf_ctrl_index[ctrl_channel];
           if (DIAG_EOK != diagcomm_io_transmit(&diagcomm_io_ctrl_conn[port_type][ctrl_channel], &tx_params))
        {
              diagcomm_ctrl_add_to_queue(&tx_params);
        }
           diag_send_buf_ctrl_index[ctrl_channel] = 0;
          *is_sent = TRUE;
        }
      }
      else
      {
        // Error case; the data recieved is greater than the maximum size;
        ASSERT(0);
      }
    }
  while (retry);

  return added_pkt_len;

} /* diagcomm_ctrl_send_mult_pkt */
/*===========================================================================

FUNCTION DIAGCOMM_CTRL_CLOSE

DESCRIPTION
  Closes the current control channel connection, if any.

PARAMETERS
  *close_func_ptr - Pointer to function to execute
  port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel to close

RETURN VALUE
  None

===========================================================================*/
void
diagcomm_ctrl_close( diagcomm_port_type port_type, diagcomm_enum_port_type ctrl_channel )
{
  diagcomm_io_conn_type * conn = &diagcomm_io_ctrl_conn[port_type][ctrl_channel];

  /* Got a command to close the connection. */
  if( conn->connected )
  {
    diagcomm_io_close( conn );
  }

  /* success or not, consider close operation successful  */
  conn->connected = FALSE;

} /* diagcomm_ctrl_close */

/*===========================================================================

FUNCTION DIAGCOMM_CTRL_INIT

DESCRIPTION
  This function initializes the diagnostic subsystem's communcations layer.

PARAMETERS
  port_type - Control channel port type (SIO/SMD)
  ctrl_channel - Control channel

RETURN VALUE
  None

===========================================================================*/
void
diagcomm_ctrl_init( diagcomm_port_type port_type, diagcomm_enum_port_type port_num )
{
  /* Make sure we are closed */
  diagcomm_ctrl_close( port_type, port_num );

  (void) q_init (&diagcomm_ctrl_resend_q);
  diagcomm_ctrl_heap_init();


} /* diagcomm_ctrl_init */

/*===========================================================================

FUNCTION DIAGCOMM_CTRL_SEND_NUM_PRESETS

DESCRIPTION

PARAMETERS
  None

DEPENDENCIES
  None

RETURN VALUE
  None

===========================================================================*/
void diagcomm_ctrl_send_num_presets( void )
{
  diag_ctrl_msg_type ctrl_msg;
  boolean is_sent = FALSE;

  /* Compose DIAG_CTRL_MSG_NUM_PRESETS */
  ctrl_msg.cmd_type = DIAG_CTRL_MSG_NUM_PRESETS;
  ctrl_msg.data_len = sizeof(diag_ctrl_msg_num_presets_type);
  ctrl_msg.data.ctrl_msg_num_presets.num_presets = DIAG_MAX_PRESET_ID;

  (void)diagcomm_ctrl_send_mult_pkt( (void *)&ctrl_msg, DIAGCOMM_CTRL_MSG_HDR_SIZE + sizeof(diag_ctrl_msg_num_presets_type),
                                      NULL, 0, DIAG_CTRL_USER_PKT_ID_0, DIAGCOMM_PORT_REMOTE_PROC, DIAGCOMM_PORT_1, TRUE, &is_sent );

} /* diagcomm_ctrl_send_num_presets */

/*===========================================================================
FUNCTION diagcomm_ctrl_send_buf_retry

DESCRIPTION
   This function is used to retry sending of the control packets that were not sent earlier due to
   flow control on control channel. The CTRL packets are added to the CTRL queue and dequeued here.

RETURN
   TRUE if flow is enabled.
   FALSE if flow is disabled.

===========================================================================*/
void diagcomm_ctrl_send_buf_retry(diagcomm_enum_port_type port_type)
{
   diagcomm_io_tx_params_type tx_params;
   ctrl_resend_pkt_type *q_item;

   q_item = (ctrl_resend_pkt_type *)q_check(&diagcomm_ctrl_resend_q);

   if(NULL == q_item)
   {
      MSG(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"q_get returned NULL");
      return;
   }
   while(q_item!=NULL)
   {
      tx_params.buffer = q_item->buf;
      tx_params.len = q_item->length;

      if(DIAG_EOK != diagcomm_io_transmit( &diagcomm_io_ctrl_conn[DIAGCOMM_PORT_REMOTE_PROC][port_type], &tx_params ))
      {
         MSG(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"q_get returned NULL");
         break;
      }
      diag_ctrl_free(q_item->buf);
      q_delete(&diagcomm_ctrl_resend_q,&q_item->qlink);
      diag_ctrl_free(q_item);
      q_item = (ctrl_resend_pkt_type *)q_check(&diagcomm_ctrl_resend_q);
   }
   if(NULL == q_item)
   {
      diagcomm_io_ctrl_conn[DIAGCOMM_PORT_REMOTE_PROC][port_type].diag_prev_tx_pending = FALSE;
      diagcomm_io_ctrl_conn[DIAGCOMM_PORT_REMOTE_PROC][port_type].diag_resend_data = FALSE;
   }
} /* diagcomm_ctrl_send_buf_retry */



/*===========================================================================
FUNCTION diagcomm_ctrl_heap_init

DESCRIPTION
   .

RETURN
   DIAG_EOK: If successful

===========================================================================*/
static int diagcomm_ctrl_heap_init()
{
   mem_init_heap (&diag_ctrl_heap, diag_ctrl_heap_buf, sizeof (diag_ctrl_heap_buf), NULL);
   return DIAG_EOK;

} /* static int diagcomm_ctrl_heap_init()*/

/*===================================================================*/
static void * diag_ctrl_malloc (uint32 num_bytes)
{
   void *buf = NULL;
   buf = mem_malloc (&diag_ctrl_heap, num_bytes);

   if (buf == NULL)
   {
      MSG_1(MSG_SSID_DIAG, MSG_LEGACY_ERROR,"diag_ctrl_malloc allocation failed: %d",num_bytes);
   }
   else
   {
      diag_ctrl_heap_malloc_count++;
   }
  return buf;
} /* diag_ctrl_malloc */

/*===================================================================*/
static void diag_ctrl_free(void *mem_ptr)
{
   mem_free (&diag_ctrl_heap, mem_ptr);
   diag_ctrl_heap_free_count++;
   return;
} /* END diag_ctrl_free */


