#ifndef SERVREG_TRACE_H
#define SERVREG_TRACE_H
/*
#============================================================================
#  Name:
#    servreg_trace.h 
#
#  Description:
#     Common header file for Service Registry feature
#
# Copyright (c) 2015-2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
#============================================================================
*/

#if defined(__cplusplus)
extern "C"
{
#endif

#ifdef SERVREG_TRACE_ENABLE

/* Type of events to log */
typedef enum
{
  SRT_NOEVENT,
  SRT_QMI_ENTER,          // no data
  SRT_QMI_EXIT,           // [qmi_client_handle, msg_id]
  SRT_QMI_MSG,            // [qmi_client_handle, msg_id]
  SRT_QMI_REG_NEW,        // [servreg_mon_node_p, qmi_client_handle]  // new service new client
  SRT_QMI_REG_ADD,        // [servreg_mon_node_p, qmi_client_handle]  // old service new client
  SRT_QMI_REG_DUP,        // [servreg_mon_node_p, qmi_client_handle]  // old service old client
  SRT_QMI_SEND,           // [servreg_mon_node_p, qmi_client_handle]
  SRT_QMI_ACK,            // [servreg_mon_node_p, qmi_client_handle]
  SRT_QMI_FALSE_ACK,      // [sr_qmi_s_proxy, qmi_client_handle] // [sr_qmi_s_proxy, transaction_id]
  SRT_QMI_ACK_ALL,        // [servreg_mon_node_p, transaction_id]
  SRT_QMI_ACK_DUP,        // no data
  SRT_QMI_BAD_TXID,       // [expected transaction_id, rx'd transaction_id]
  SRT_QMI_DEREG,          // [servreg_mon_node_p, qmi_client_handle]
  SRT_QMI_DEREG_ALL,      // [servreg_mon_node_p, 0]
  SRT_QMI_DEREG_ACK_MISS, // [service transaction_id, lask ack transaction_id]
  SRT_QMI_ACK_RESP_SUCCESS, // no data
  SRT_QMI_ACK_RESP_FAIL,    // no data
  SRT_COMMON_REG,         // [servreg_mon_node_p, thread id]
  SRT_COMMON_REG_R,       // no data
  SRT_COMMON_REG_RD,      // no data
  SRT_COMMON_REG_L,       // no data
  SRT_COMMON_REG_LS,      // no data
  SRT_COMMON_REG_EXIT,    // [servreg_mon_node_p, thread id]
  SRT_RCESN_PARMS,        // [rcesn_handle, SERVREG_MON_SIGQURT (or REX)]
  SRT_COMMON_DEREG,       // [servreg_mon_node_p, 0]
  SRT_QMI_IND_PROCESS,    // [servreg_mon_node_p, 0] 
  SRT_REMOTE_QMI_IND_SIG, // no data
  SRT_QMI_IND_CB,         // no data
  SRT_QMI_IND_TRANS_ID,   // [transaction_id, 0]
  SRT_COMMON_ACK,         // [servreg_mon_node_p, post ack pending count]
  SRT_COMMON_ACK_ALL,     // [servreg_mon_node_p, SERVREG_SERVICE_STATE]
  SRT_COMMON_ACK_REMOTE,  // [servreg_mon_node_p, transaction id]
  SRT_QDI_REG,            // [servnotif_qdi_device_data_p, QDI client handle]
  SRT_QDI_DEREG,          // [servnotif_qdi_device_data_p, QDI client handle]
  SRT_QDI_INVOKE,         // [tid, servreg qdi method]
  SRT_QDI_INVOKE_EXIT,    // [tid, servreg qdi method]
  SRT_SERVICE_Q,          // [servreg_mon_node_p, ack pending count]            
  SRT_SET_STATE,          // [servreg_mon_node_p, SERVREG_SERVICE_STATE] 
  SRT_NODE_CREATE,        // [servreg_mon_node_p, 1]
  SRT_NODE_CREATE_DUP,    // [servreg_mon_node_p, handle count]
  SRT_ACK_TIMER_CB,       // [servreg_mon_node_p, timeout count]
  SRT_SET_REMOTE_ACK_1,   // [servreg_mon_node_p, 0]
  SRT_STATE_CHANGE_IND,   // [servreg_mon_node_p, SERVREG_SERVICE_STATE]
  SRT_STATE_CHANGE_IND_E, // [servreg_mon_node_p, sr_q_entry]
  SRT_REMOTE_ACK_QMI_SEND,// [servreg_mon_node_p, transaction id]
  SRT_REMOTE_ACK_Q_GET,   // [servreg_mon_node_p, 0]
  SRT_REMOTE_ACK_QMI_SUCCESS,// no data
  SRT_RESULT,             // [servreg_result, 0]
  SRT_SUCCESS,            // no data
  SRT_FAIL                // no data
} srt_event_type;

/* A single event trace */
typedef struct
{
  srt_event_type  event;
  void* data0;
  void* data1;
} srt_data_type;


/* Structure of all timer log events */
#define SRT_LENGTH  200
typedef struct
{
  uint32                index;
  srt_data_type events[SRT_LENGTH];
} srt_type;

void srt_event(srt_event_type  event, void** data);

/* Macros to perform logging */
#define SERVREG_TRACE_0(event)               \
do {                                         \
     srt_event(SRT_##event, NULL);           \
} while(0)

#define SERVREG_TRACE_2(event, srt0, srt1)          \
do {                                                \
  void *srt[2] = {(void*)srt0, (void*)srt1};        \
  srt_event(SRT_##event, srt);                      \
} while(0)

#else //!SERVREG_TRACE_ENABLE
 
#define SERVREG_TRACE_0(event) do{}while(0)
#define SERVREG_TRACE_2(event, srt0, srt1) do{}while(0)

#endif //SERVREG_TRACE_ENABLE

#if defined(__cplusplus)
}
#endif

#endif
