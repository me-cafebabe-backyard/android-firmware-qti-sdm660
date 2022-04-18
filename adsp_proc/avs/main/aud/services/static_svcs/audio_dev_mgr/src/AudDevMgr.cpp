/**
@file AudDevMgr.cpp
@brief This file contains the implementation for AudioDevMgr.

 */

/*===========================================================================
Copyright (c) 2010-2017 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
 *//*====================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.8/aud/services/static_svcs/audio_dev_mgr/src/AudDevMgr.cpp#40 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
02/23/12   KR      Non-backward compatible API changes for Badger.
========================================================================== */

/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "EliteMsg_AfeCustom.h"
#include "Elite.h"
#include "EliteAprIf.h"
#include "AFEInterface.h"
#include "AudDynaPPSvc.h"
#include "EliteMsg_AdmCustom.h"
#include "AudDevMgr.h"
#include "AudDevMgr_DataBase.h"
#include "MixerSvc_Interface.h"
#include "AudDevMgr_CoppIf.h"
#include "AudDevMgr_MtMxIf.h"
#include "AudDevMgr_StRtrIf.h"
#include "AudDevMgr_AfeIf.h"
#include "AudDevMgr_AprIf.h"
#include "EliteAprIf.h"
#include "VoiceProcTx.h"
#include "adsp_adm_api.h"
#include "AudDevMgr_PrivateDefs.h"
#include "adsp_vpm_api.h"
#include "adsp_afe_service_commands.h"
#include "adsp_asm_session_commands.h"
#include "AudDevMgr_mmpm.h"
#include "AudDynaPPSvc.h"
#include "StreamRouterSvc.h"
#include "AudDevMgr_AsmIf.h"
#include "EliteTopology_db_if.h"
#include "EliteCmnTopology_db.h"
#include "adsp_asm_stream_commands.h"
#include "AudDevMgr_DirectConnect.h"
#include "aprv2_ids_services.h"
#include "qurt_elite_memory.h"

/* =======================================================================
TypeDefs
========================================================================== */

/* =======================================================================
Function Declarations
========================================================================== */
static  ADSPResult AdmSvc_CustomMsgHandler(void* pAudStatAdmSvc, elite_msg_any_t* pMsg);
static  ADSPResult AdmSvc_AprMsgHandler(void *pAudStatAdmSvc, elite_msg_any_t *pMsg);
static  ADSPResult AdmSvc_Start(void *pAudStatAdmSvc, elite_msg_any_t* pMsg);
static  ADSPResult AdmSvc_Destroy(void *pAudStatAdmSvc, elite_msg_any_t* pMsg);
static void AdmSvc_CheckHandleHelperThreads(AdmStatSvc_InfoType *pAdmStatSvc);

static ADSPResult AdmSvc_ProcessCmdQueue(void *pAudStatAdmSvc, int nChannelBit);
static ADSPResult AdmSvc_ProcessRspQueue(void *pAudStatAdmSvc, int nChannelBit);
static ADSPResult AdmSvc_ProcessReservedQueue(void *pAudStatAdmSvc, int nChannelBit);
static ADSPResult AdmSvc_ProcessDeviceCmdQ(void *pInstance, int nChannelBit);
static ADSPResult AdmSvc_ProcessAllQueues(void *pInstance, int nChannelMask);
static ADSPResult AdmSvc_RspHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg);
static ADSPResult Adm_HelperThreadResponseHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg);
static ADSPResult Adm_SetParamResponseHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg);
static ADSPResult Adm_GetParamResponseHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg);
static ADSPResult Adm_GetPPTopoModulesRspHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg);
static ADSPResult Adm_RegisterDeregisterAprEventRspHandler(void *pAudStatAdmSvc, elite_msg_any_t *pMsg);

static  ADSPResult Adm_MsgStreamConnect(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient);
static  ADSPResult Adm_MsgStreamDisconnect(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient);
static  ADSPResult Adm_MsgStreamDisable(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient);
static  ADSPResult Adm_MsgStreamMtMxReconfig(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient);

static void Adm_DeviceParseOpenPayload(elite_apr_packet_t *pPkt,
                                       adm_cmd_device_open_t *pDevOpenCmdPayload);
static void Adm_PrintChannelType(const uint8_t *channel_type, int32_t num_channels);
static  ADSPResult Adm_AprDeviceOpenCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprDeviceCloseCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_MsgGetDevicePathDelay(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient);
static  ADSPResult Adm_AprMtMxMapRoutingsHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt, adm_client_type_t eClient);
static ADSPResult Adm_SetParams(void *pAudStatAdmSvc, void *pParams, elite_svc_handle_t *pCoppHandle,
                                uint32_t unCoppID, uint32_t opCode,
                                DeviceCmdProcInfo_t *pDevCmd);
static  ADSPResult Adm_AprSetParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprGetPPParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprGetPPTopoModuleCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprMatrixRampGainsCmdHandler_v5 (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprMatrixRampGainsCmdHandler_v6 (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprMatrixRampGainsCmdHandler_v7 (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprMatrixMuteCmdHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static  ADSPResult Adm_AprAfeConnectCmdHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt, qurt_elite_queue_t *pRspQ);
static  ADSPResult Adm_AprAfeDisconnectCmdHandler (AdmStatSvc_InfoType *pAudStatAdmSvc, elite_apr_packet_t *pPkt, qurt_elite_queue_t *pRspQ);
static  ADSPResult Adm_AprAddTopologiesHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static ADSPResult Adm_AprSetPspdMtMxStrtrParamsCmdHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static ADSPResult Adm_RegisterDegisterPPEvents(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);

static  ADSPResult Adm_SendCmdDestroySvc(elite_svc_handle_t *pHandle);

static ADSPResult Adm_DeviceOpenCmdUnsupportedHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                      adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                      elite_apr_packet_t *pPkt,
                                                      NativeModeHook cbNativeMode,
                                                      uint16_t *unCreatedCoppID,
                                                      qurt_elite_queue_t *pRspQ);

static ADSPResult Adm_DeviceCloseCmdUnsupportedHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                       elite_apr_packet_t *pPkt,
                                                       qurt_elite_queue_t *pRspQ);

static ADSPResult Adm_DeviceOpenCmdLPCMHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                               adm_cmd_device_open_t *pDevOpenCmdPayload,
                                               elite_apr_packet_t *pPkt,
                                               NativeModeHook cbNativeMode,
                                               uint16_t *unCreatedCoppID,
                                               qurt_elite_queue_t *pRspQ);

static ADSPResult Adm_DeviceOpenCmdLPCMLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                       adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                       elite_apr_packet_t *pPkt,
                                                       NativeModeHook cbNativeMode,
                                                       uint16_t *unCreatedCoppID,
                                                       qurt_elite_queue_t *pRspQ);

static ADSPResult Adm_DeviceOpenCmdCompressedHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                     adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                     elite_apr_packet_t *pPkt,
                                                     NativeModeHook cbNativeMode,
                                                     uint16_t *unCreatedDeviceID,
                                                     qurt_elite_queue_t *pRspQ);

static ADSPResult Adm_DeviceOpenCmdLPCMDeviceLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                             adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                             elite_apr_packet_t *pPkt,
                                                             NativeModeHook cbNativeMode,
                                                             uint16_t *unCreatedCoppID,
                                                             qurt_elite_queue_t *pRspQ);

static ADSPResult Adm_SendHelperThrdEndMsg(AdmStatSvc_InfoType *pAdmStatSvc,uint16_t unCoppID, ADSPResult status, uint32_t opcode);
static ADSPResult Adm_DeviceOpenCmdHelperThread(AdmStatSvc_InfoType *pAdmStatSvc,
                                                uint16_t open_mode,
                                                elite_apr_packet_t *pPkt,
                                                NativeModeHook cbNativeMode,
                                                uint16_t *unCreatedCoppID);
static ADSPResult Adm_DeviceCloseCmdHelperThread(AdmStatSvc_InfoType *pAdmStatSvc,
                                                 elite_apr_packet_t *pPkt);

static ADSPResult Adm_DeviceCloseCmdLPCMHandler(AdmStatSvc_InfoType *pAdmStatSvc, elite_apr_packet_t *pPkt,
                                                qurt_elite_queue_t *pRspQ);
static ADSPResult Adm_DeviceCloseCmdLPCMLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc, elite_apr_packet_t *pPkt,
                                                        qurt_elite_queue_t *pRspQ);
static ADSPResult Adm_DeviceCloseCmdLPCMDeviceLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc, elite_apr_packet_t *pPkt,
                                                              qurt_elite_queue_t *pRspQ);
static ADSPResult Adm_CheckCompDevIDValidity(AdmStatSvc_InfoType *pAudStatAdmSvc, uint16_t unDevID);
static ADSPResult Adm_AprStreamDeviceMapRoutingsHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static ADSPResult Adm_ReCheckReCfgOfConnIpPorts(AdmStatSvc_InfoType *pAudStatAdmSvc, uint16_t unCoppIDRecfg, uint32_t unTargetSampleRate);
static  uint16_t Adm_CalculateCoppID(AdmStatSvc_InfoType *pAdmStatSvc,uint16_t direction);
static  int AdmWorkLoop(void *pInstance);
static uint16_t Adm_GetPrimaryDevicePcm(AdmStatSvc_InfoType *pAdmStatSvc, uint32_t unDeviceClusterMask);

static uint8_t Adm_NativeModeParamCallback(adm_cmd_device_open_t *pDevOpenCmdPayload);

static inline uint16_t ADM_GET_COPP_ID(elite_apr_port_t port)
{
  return (uint16_t) (port);
}

static ADSPResult Adm_AprSetMtMxStrtrDeviceParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static ADSPResult Adm_AprGetMtMxStrtrDeviceParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt);
static int Adm_HelperThreadEntryFunc(void *pArgs);
static void Adm_SendOpenCmdRspAprMsg(AdmStatSvc_InfoType *pAdmStatSvc, Adm_HelperThrd_t *pHelper);
static uint16_t Adm_GetDeviceModeFromID(AdmStatSvc_InfoType *pAdmStatSvc,
                                        uint16_t unCoppID);
static uint32_t Adm_GetDeviceCmdQIndex(uint16_t unCoppID);
static uint16_t Adm_GetDeviceIdFromChannelBit(uint32_t unChBit);
static void* Adm_GetCalPortStructFromCoppID(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t unCoppID, bool_t *isCompressed);

static ADSPResult AdmSvc_DeviceCmdQAprMsgHandler(void* pInstance, elite_msg_any_t* pMsg);
static ADSPResult AdmSvc_DeviceCmdQ_Unsupported(void* pInstance, elite_msg_any_t* pMsg);
static ADSPResult Adm_ValidateDeviceOpenPayload(elite_apr_packet_t *pPkt);

#define AUDIO_DEV_MGR_MAX_NUM_CHANNEL_BITS 32
//#define ADM_SVC_QUEUE_PROC_DBG
/* =======================================================================
Global Definitions
========================================================================== */

/* Function Pointer Lookup Table used by AdmSvc_ProcessAllQueues based on channel bit
      Entry point for processing the queues that ADM listens to */
static Adm_QueueHandler_f pAdmStatServQHandler[AUDIO_DEV_MGR_MAX_NUM_CHANNEL_BITS] =
{
    AdmSvc_ProcessCmdQueue,
    AdmSvc_ProcessRspQueue,
    AdmSvc_ProcessReservedQueue, //ADM Inline Response Q.
    AdmSvc_ProcessDeviceCmdQ,   // device 1
    AdmSvc_ProcessDeviceCmdQ,   // device 2
    AdmSvc_ProcessDeviceCmdQ,   // device 3
    AdmSvc_ProcessDeviceCmdQ,   // device 4
    AdmSvc_ProcessDeviceCmdQ,   // device 5
    AdmSvc_ProcessDeviceCmdQ,   // device 6
    AdmSvc_ProcessDeviceCmdQ,   // device 7
    AdmSvc_ProcessDeviceCmdQ,   // device 8
    AdmSvc_ProcessDeviceCmdQ,   // device 9
    AdmSvc_ProcessDeviceCmdQ,   // device 10
    AdmSvc_ProcessDeviceCmdQ,   // device 11
    AdmSvc_ProcessDeviceCmdQ,   // device 12
    AdmSvc_ProcessDeviceCmdQ,   // device 13
    AdmSvc_ProcessDeviceCmdQ,   // device 14
    AdmSvc_ProcessDeviceCmdQ,   // device 15
    AdmSvc_ProcessDeviceCmdQ,   // device 16
    AdmSvc_ProcessDeviceCmdQ,   // device 17
    AdmSvc_ProcessDeviceCmdQ,   // device 18
    AdmSvc_ProcessDeviceCmdQ,   // device 19
    AdmSvc_ProcessDeviceCmdQ,   // device 20
    AdmSvc_ProcessDeviceCmdQ,   // device 21
    AdmSvc_ProcessDeviceCmdQ,   // device 22
    AdmSvc_ProcessReservedQueue,
    AdmSvc_ProcessReservedQueue,
    AdmSvc_ProcessReservedQueue,
    AdmSvc_ProcessReservedQueue,
    AdmSvc_ProcessReservedQueue,
    AdmSvc_ProcessReservedQueue,
    AdmSvc_ProcessReservedQueue
};

/* Function Pointer Lookup Table used by AdmSvc_ProcessCmdQueue based on opcode
      Entry point for processing the ADM Svc Cmd Q Messages */
static elite_svc_msg_handler_func pAdmStatServHandler[] =
{
    AdmSvc_CustomMsgHandler,        //0 - ELITE_CUSTOM_MSG
    AdmSvc_Start,                   //1 - ELITE_CMD_START_SERVICE
    AdmSvc_Destroy,                 //2 - ELITE_CMD_DESTROY_SERVICE
    elite_svc_unsupported,          //3 - UNSUPPORTED CMD
    elite_svc_unsupported,          //4 - UNSUPPORTED CMD
    elite_svc_unsupported,          //5 - UNSUPPORTED CMD
    elite_svc_unsupported,          //6 - UNSUPPORTED CMD
    elite_svc_unsupported,          //7 - UNSUPPORTED CMD
    elite_svc_unsupported,          //8 - UNSUPPORTED CMD
    elite_svc_unsupported,          //9 - UNSUPPORTED CMD
    elite_svc_unsupported,          //A - UNSUPPORTED CMD
    elite_svc_unsupported,          //B - UNSUPPORTED CMD
    elite_svc_unsupported,          //C - UNSUPPORTED CMD
    elite_svc_unsupported,          //D - UNSUPPORTED CMD
    elite_svc_unsupported,          //E - UNSUPPORTED CMD
    AdmSvc_AprMsgHandler,           //F - ELITE_APR_PACKET
    elite_svc_unsupported,          //10 - ELITE_MIPS_CHANGE_EVENT
    elite_svc_unsupported,          //11 - ELITE_DATA_SET_PARAM
    elite_svc_unsupported,          //12 - ELITE_DML_CHANGE_EVENT
    elite_svc_unsupported           //13 - ELITE_BW_CHANGE_EVENT
};

/* Function Pointer Lookup Table used by AdmSvc_ProcessRspQueue based on opcode
      Entry point for processing the ADM Svc Rsp Q Messages */
static elite_svc_msg_handler_func pAdmStatServRspHandler[] =
{
    AdmSvc_RspHandler,              //0 - ELITE_CUSTOM_MSG
    elite_svc_unsupported,          //1 - ELITE_CMD_START_SERVICE
    elite_svc_unsupported,          //2 - ELITE_CMD_DESTROY_SERVICE
    elite_svc_unsupported,          //3 - ELITE_CMD_CONNECT
    elite_svc_unsupported,          //4 - ELITE_CMD_DISCONNECT
    elite_svc_unsupported,          //5 - ELITE_CMD_PAUSE
    elite_svc_unsupported,          //6 - ELITE_CMD_RESUME
    elite_svc_unsupported,          //7 - ELITE_CMD_FLUSH
    AdmSvc_RspHandler,              //8 - ELITE_CMD_SET_PARAM
    AdmSvc_RspHandler,              //9 - ELITE_CMD_GET_PARAM
    elite_svc_unsupported,          //A - ELITE_DATA_BUFFER
    elite_svc_unsupported,          //B - ELITE_DATA_MEDIA_TYPE
    elite_svc_unsupported,          //C - ELITE_DATA_EOS
    elite_svc_unsupported,          //D - ELITE_DATA_RAW_BUFFER
    elite_svc_unsupported,          //E - ELITE_CMD_STOP_SERVICE
    elite_svc_unsupported,          //F - ELITE_APR_PACKET
    elite_svc_unsupported,          //16 - ELITE_MIPS_CHANGE_EVENT
    elite_svc_unsupported,          //17 - ELITE_DATA_SET_PARAM
    elite_svc_unsupported,          //18 - DML change event
    elite_svc_unsupported,          //19 - ELITE_BW_CHANGE_EVENT
    elite_svc_unsupported,          //20 - ELITE_DATA_MARK_BUFFER
    elite_svc_unsupported,          //21 - ELITE_DATA_BUFFER_V2
    elite_svc_unsupported,          //22 - ELITE_CUSTOM_EVENT
    AdmSvc_RspHandler,              //23 - ELITE_CMD_REGISTER_APR_EVENT 0x17

};

/* Function Pointer Lookup Table used by AdmSvc_ProcessRspQueue based on opcode
      Entry point for processing the ADM Svc Rsp Q Messages */
static Adm_DeviceCmdQHandler_f pAdmStatServDeviceCmdQHandler[] =
{
    AdmSvc_DeviceCmdQ_Unsupported,  //0 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //1 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //2 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //3 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //4 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //5 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //6 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //7 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //8 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //9 - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //A - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //B - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //C - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //D - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQ_Unsupported,  //E - UNSUPPORTED CMD
    AdmSvc_DeviceCmdQAprMsgHandler, //F - ELITE_APR_PACKET
    AdmSvc_DeviceCmdQ_Unsupported,  //10 - ELITE_MIPS_CHANGE_EVENT
    AdmSvc_DeviceCmdQ_Unsupported,  //11 - ELITE_DATA_SET_PARAM
    AdmSvc_DeviceCmdQ_Unsupported,  //12 - ELITE_DML_CHANGE_EVENT
    AdmSvc_DeviceCmdQ_Unsupported   //13 - ELITE_BW_CHANGE_EVENT
};

/* Function Pointer Lookup Table used by Adm_DeviceOpenCmdHelperThread based on mode
      Entry point for processing the ADM Device Open Command */
static Adm_OpenDeviceCmdHandler_f pAdmOpenDeviceHandler[] =
{
    Adm_DeviceOpenCmdUnsupportedHandler,          //0 - Unsupported Mode
    Adm_DeviceOpenCmdLPCMHandler,                 //1 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP
    Adm_DeviceOpenCmdLPCMHandler,                 //2 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP
    Adm_DeviceOpenCmdLPCMHandler,                 //3 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP
    Adm_DeviceOpenCmdLPCMLoopBackHandler,         //4 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP
    Adm_DeviceOpenCmdCompressedHandler,           //5 - ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX
    Adm_DeviceOpenCmdCompressedHandler,           //6 - ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX
    Adm_DeviceOpenCmdLPCMDeviceLoopBackHandler    //7 - ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_DEVICE_LOOPBACK
};

/* Function Pointer Lookup Table used by Adm_DeviceOpenClosHelperThread based on mode
      Entry point for processing the ADM Device Close Command */
static Adm_CloseDeviceCmdHandler_f pAdmCloseDeviceHandler[] =
{
    Adm_DeviceCloseCmdUnsupportedHandler,          //0 - Unsupported Mode
    Adm_DeviceCloseCmdLPCMHandler,                 //1 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP
    Adm_DeviceCloseCmdLPCMHandler,                 //2 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP
    Adm_DeviceCloseCmdLPCMHandler,                 //3 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP
    Adm_DeviceCloseCmdLPCMLoopBackHandler,         //4 - ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP
    Adm_AprAfeDisconnectCmdHandler,                //5 - ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX
    Adm_AprAfeDisconnectCmdHandler,                //6 - ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX
    Adm_DeviceCloseCmdLPCMDeviceLoopBackHandler    //7 - ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_DEVICE_LOOPBACK
};


static char ADM_STATIC_THREAD_NAME[] = "ADM";

/* ADM Queues aligned to 8 bytes */
QURT_ELITE_ALIGN(static char admCmdQbuf[QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(ADM_MAX_CMD_Q_ELEMENTS)], 8);
QURT_ELITE_ALIGN(static char admRspQBuf[QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(ADM_MAX_RSP_Q_ELEMENTS)], 8);
QURT_ELITE_ALIGN(static char admInlineRspQBuf[QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(ADM_MAX_INLINE_RSP_Q_ELEMENTS)], 8);
QURT_ELITE_ALIGN(static char admDeviceCmdQ[ADM_MAX_DEVICE_SESSIONS][QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(ADM_DEVICE_CMD_Q_ELEMENTS)], 8);

/* ADM Stack Sizes */
#define ADM_THREAD_STACK_SIZE              12544
//The helper thread uses the same stack size as the static service
#define ADM_HELPER_THREAD_OPEN_STACK_SIZE  ADM_THREAD_STACK_SIZE
#define ADM_HELPER_THREAD_CLOSE_STACK_SIZE 4096

AdmStatSvc_InfoType *gpAdmStatSvc;

/* Channel Masks for ADM Service Queues*/
static const uint32_t admCmdQMask       = 0x00000001L;
static const uint32_t admRspQMask       = 0x00000002L;
static const uint32_t admInlineRspQMask = 0x00000004L;

#define ADM_SVC_Q_CHANNEL_NUM_BITS  3

/* Declaration of ADM object instance */
static AdmStatSvc_InfoType gAdmStatSvcObject;

/* Declaration of device session delay param structure */
static AdmDevSessionDelayParam_Type gAdmDevSessionDelayParam[ADM_MAX_COPPS];

/*qurt_elite MemoryMap Client */
uint32_t admMemoryMapClient;

/* =======================================================================
Function Definitions
========================================================================== */
ADSPResult adm_svc_get_api_version(avs_svc_api_info_t *svc_info_ptr)
{
  svc_info_ptr->service_id = APRV2_IDS_SERVICE_ID_ADSP_ADM_V;
  svc_info_ptr->api_version = ADM_API_VERSION;
  svc_info_ptr->api_branch_version = ADM_API_BRANCH_VERSION;

  return ADSP_EOK;
}

ADSPResult AudCreateStatAudDevMgr(uint32_t dummy, void **ppHAudDevMgr)
{
  int                             result;
  uint16_t                        unCoppID, unInPortID, unOutPortID, unIndex;
  AdmCalPort_Type                 *phCalPort;
  AdmDevSessionDelayParam_Type    *pSessionDelayParam;
  AdmStreamSessionInfo_Type       *pRxSessionInfo, *pTxSessionInfo;
  qurt_elite_queue_t              *pTemp;

  char admCmdQName[]       = AUD_DEV_MGR_CMDQ;
  char admRspQName[]       = AUD_DEV_MGR_RSPQ;
  char admInlineRspQName[] = AUD_DEV_MGR_INLINE_RSPQ;

  gpAdmStatSvc = &gAdmStatSvcObject;

  //pointer to device session delay param structure
  gpAdmStatSvc->pDevSessionDelayParam = &(gAdmDevSessionDelayParam[0]);

  //Create audio matrix instances for Tx and Rx paths
  // 1 more session reserved for output ports.

  MtMxParams_t mtMxParams;
  mtMxParams.maxInPorts  = MT_MX_MAX_INPUT_PORTS;
  mtMxParams.maxOutPorts = MT_MX_MAX_OUTPUT_PORTS + 1;
  mtMxParams.matrixID    = ADM_MATRIX_ID_AUDIO_TX;

  if (ADSP_FAILED(result = AudCreateMatrixMixerSvc (0, (void**)&(gpAdmStatSvc->hTxMatrix), &mtMxParams)))
  {
    MSG(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to create Tx Audio Matrix");
    return result;
  }

  mtMxParams.matrixID = ADM_MATRIX_ID_AUDIO_RX;
  if (ADSP_FAILED(result = AudCreateMatrixMixerSvc (0, (void**)&(gpAdmStatSvc->hRxMatrix), &mtMxParams)))
  {
    MSG(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to create Rx Audio Matrix");
    return result;
  }

  //Assign MtMxPortCfgParams for both input and output
  gpAdmStatSvc->cfgOutPortsPayload.pOutPortCfgParams = (MtMxOutPortCfgParams_t*)&(gpAdmStatSvc->admOutPortCfgParams);
  gpAdmStatSvc->cfgInPortsPayload.pInPortCfgParams   = (MtMxInPortCfgParams_t*)&(gpAdmStatSvc->admInPortCfgParams);


  streamRouterSvcInitParams_t stRtrInit;
  //Create Rx Stream Router
  memset(&gpAdmStatSvc->rxStRtrParams, 0, sizeof(StreamRouterParams_t));

  for(uint32_t i=0; i<STRTR_MAX_PORTS; i++)
  {
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].unCoppID         = ADM_COPP_ID_INVALID;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].unCoppTopologyID = AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].strtr_port_id    = STRTR_INVALID_PORT_ID;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].afe_port_id      = AFE_PORT_ID_INVALID;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].phDevCopp        = NULL;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].unCoppStatus     = 0;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].unCoppType       = 0;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].unCoppBufDelay   = 0;
    gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].unCoppAlgDelay   = 0;

    memset(&(gpAdmStatSvc->rxStRtrParams.compr_copp_info[i].helperThrdInfo), 0 , sizeof(Adm_HelperThrd_t));
  }
  for(unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    gpAdmStatSvc->rxStRtrParams.session_id_to_delay_ptr_idx[unIndex] = ADM_INVALID_DELAY_PTR_ID;
    gpAdmStatSvc->rxSessionIDToPrimCompressedDevIndexMap[unIndex]    = ADM_INVALID_PRIMARY_DEVICE;
  }
  stRtrInit.stream_router_id = RX_STRTR_ID;

  result = stream_router_svc_create(&stRtrInit, (void**)&gpAdmStatSvc->rxStRtrParams.hSvcHandle);
  if(ADSP_ENOTIMPL == result)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Rx Stream Router is stubbed as compressed playback is stubbed. Continuing as normal.");
    gpAdmStatSvc->rxStRtrParams.hSvcHandle = NULL;
    result = ADSP_EOK;
  }
  else if (ADSP_EOK != result)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error: Failed to create Rx Stream Router. Result = %d.", result);
    gpAdmStatSvc->rxStRtrParams.hSvcHandle = NULL;
    return result;
  }
  else
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Rx Stream Router created successfully.");
  }

  //Create Tx Stream Router
  memset(&gpAdmStatSvc->txStRtrParams, 0, sizeof(StreamRouterParams_t));

  for(uint32_t i=0; i<STRTR_MAX_PORTS; i++)
  {
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].unCoppID         = ADM_COPP_ID_INVALID;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].unCoppTopologyID = AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].strtr_port_id    = STRTR_INVALID_PORT_ID;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].afe_port_id      = AFE_PORT_ID_INVALID;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].phDevCopp        = NULL;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].unCoppStatus     = 0;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].unCoppType       = 0;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].unCoppBufDelay   = 0;
    gpAdmStatSvc->txStRtrParams.compr_copp_info[i].unCoppAlgDelay   = 0;
    memset(&(gpAdmStatSvc->txStRtrParams.compr_copp_info[i].helperThrdInfo), 0 , sizeof(Adm_HelperThrd_t));
  }
  for(unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    gpAdmStatSvc->txStRtrParams.session_id_to_delay_ptr_idx[unIndex] = ADM_INVALID_DELAY_PTR_ID;
    gpAdmStatSvc->txSessionIDToPrimCompressedDevIndexMap[unIndex] = ADM_INVALID_PRIMARY_DEVICE;
  }

  stRtrInit.stream_router_id = TX_STRTR_ID;
  result = stream_router_svc_create(&stRtrInit, (void**)&gpAdmStatSvc->txStRtrParams.hSvcHandle);
  if(ADSP_ENOTIMPL == result)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Tx Stream Router is stubbed as compressed record is stubbed. Continuing as normal.");
    gpAdmStatSvc->txStRtrParams.hSvcHandle = NULL;
    result = ADSP_EOK;
  }
  else if (ADSP_EOK != result)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error: Failed to create Tx Stream Router. Result = %d.", result);
    gpAdmStatSvc->txStRtrParams.hSvcHandle = NULL;
    return result;
  }
  else
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Tx Stream Router created successfully.");
  }

  //Create ADM command and response queues
  gpAdmStatSvc->cmdQName = admCmdQName;
  gpAdmStatSvc->rspQName = admRspQName;

  pTemp                       = (qurt_elite_queue_t *)admCmdQbuf;
  gpAdmStatSvc->admInlineRspQ = (qurt_elite_queue_t *)admInlineRspQBuf;
  gpAdmStatSvc->admRspQ       = (qurt_elite_queue_t *)(admRspQBuf);

  if(ADSP_FAILED(result = qurt_elite_queue_init(gpAdmStatSvc->cmdQName, ADM_MAX_CMD_Q_ELEMENTS, pTemp))
      ||ADSP_FAILED(result = qurt_elite_queue_init(admInlineRspQName, ADM_MAX_INLINE_RSP_Q_ELEMENTS, gpAdmStatSvc->admInlineRspQ))
      ||ADSP_FAILED(result = qurt_elite_queue_init(gpAdmStatSvc->rspQName, ADM_MAX_RSP_Q_ELEMENTS, gpAdmStatSvc->admRspQ)))
  {
    MSG(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to create ADM cmdQ and respQ");
    return result;
  }

  /////////////////////Command Q//////////////////////////////

  gpAdmStatSvc->hAdmSvc.cmdQ = pTemp;
  *((elite_svc_handle_t **)ppHAudDevMgr) = &gpAdmStatSvc->hAdmSvc;

  //Call this function to expose the cmdQueue for Adm_AprIf to push commands from client processor to this queue.
  AudDevMgr_SetCmdQueue(gpAdmStatSvc->hAdmSvc.cmdQ);

  qurt_elite_channel_init(&gpAdmStatSvc->admChannel);

  if (ADSP_FAILED(result = qurt_elite_channel_addq(&gpAdmStatSvc->admChannel,
                                                   gpAdmStatSvc->hAdmSvc.cmdQ,
                                                   admCmdQMask)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to add ADM cmdQ to channel, result = %d", result);
    return(result);
  }

  //After successful addition of the Q to channel, update global Q ptr.
  qurt_elite_globalstate.pAdmStatSvcCmdQ = pTemp;

  /////////////////////Command Q//////////////////////////////

  /////////////////////Response Q//////////////////////////////
  if (ADSP_FAILED(result = qurt_elite_channel_addq(&gpAdmStatSvc->admChannel,
                                                   gpAdmStatSvc->admRspQ,
                                                   admRspQMask)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to add responseQ to channel, result = %d", result);
    return(result);
  }

  if (ADSP_FAILED(result = qurt_elite_channel_addq(&gpAdmStatSvc->admChannel,
                                                   gpAdmStatSvc->admInlineRspQ,
                                                   admInlineRspQMask)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to add inline responseQ to channel, result = %d", result);
    return(result);
  }
  /////////////////////Response Q//////////////////////////////

  //Initialize the mutex for ADM static service variables
  qurt_elite_mutex_init(&gpAdmStatSvc->admLock);

  //Initialize COPP params
  for (unCoppID = 0; unCoppID < ADM_MAX_COPPS; unCoppID++)
  {
    phCalPort = &gpAdmStatSvc->deviceCalPort[unCoppID];
    pSessionDelayParam = &(gpAdmStatSvc->pDevSessionDelayParam[unCoppID]);

    phCalPort->unCoppStatus                    = ADM_COPP_STATUS_INACTIVE;
    phCalPort->unCoppType                      = ADM_COPP_TYPE_NONE;
    phCalPort->unCoppMode                      = 0;
    phCalPort->unMtMxSampleRate                = ADM_SAMPLING_RATE_48K;
    phCalPort->unEID1.unSampleRate             = ADM_SAMPLING_RATE_48K;
    phCalPort->unEID2.unSampleRate             = ADM_SAMPLING_RATE_48K;
    phCalPort->unEID3.unSampleRate             = ADM_SAMPLING_RATE_48K;
    phCalPort->unCoppNumAfeFrames              = ADM_LEGACY_NUM_AFE_FRAMES;
    phCalPort->unNumConnectedSessionsRx        = 0;
    phCalPort->unNumConnectedSessionsTx        = 0;
    pSessionDelayParam->unCoppBufDelay         = 0;
    pSessionDelayParam->unCoppAlgDelay         = 0;
    pSessionDelayParam->unAFEDelay_EP1         = 0;
    pSessionDelayParam->unAFEDelay_EP2         = 0;
    pSessionDelayParam->unAFEDelay_EP3         = 0;
    phCalPort->bIsCoppInLoopBackTopology       = FALSE;
    phCalPort->bIsCoppInDeviceLoopBackTopology = FALSE;
    phCalPort->bIsCoppConnectedToPseudoPort    = FALSE;
    phCalPort->unPrimaryDevice                 = ADM_INVALID_PRIMARY_DEVICE;
    phCalPort->unEID2.unAfePortID              = ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE;
    memset(&(phCalPort->unEID1.unChannelMap),0,(sizeof(phCalPort->unEID1.unChannelMap)));
    memset(&(phCalPort->unEID2.unChannelMap),0,(sizeof(phCalPort->unEID2.unChannelMap)));
    memset(&(phCalPort->unEID3.unChannelMap),0,(sizeof(phCalPort->unEID3.unChannelMap)));
    memset(&(phCalPort->helperThrdInfo), 0, sizeof(Adm_HelperThrd_t));
  }

  //Initialize the reverse look up (Port ID -> session) maps
  for (unInPortID = 0; unInPortID < MT_MX_MAX_INPUT_PORTS; unInPortID++)
  {
    gpAdmStatSvc->rxMtMxInPortIDToSessionIDMap[unInPortID] = 0;
  }
  for (unOutPortID = 0; unOutPortID < MT_MX_MAX_OUTPUT_PORTS; unOutPortID++)
  {
    gpAdmStatSvc->txMtMxOutPortIDToSessionIDMap[unOutPortID] = 0;
  }

  // Initialize stream session sampling rate information
  for(unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    pRxSessionInfo = &gpAdmStatSvc->rxStreamSessionInfo[unIndex];
    pTxSessionInfo = &gpAdmStatSvc->txStreamSessionInfo[unIndex];

    pRxSessionInfo->unSessionSampleRate               = ADM_SAMPLING_RATE_48K;
    pTxSessionInfo->unSessionSampleRate               = ADM_SAMPLING_RATE_48K;
    gpAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unIndex] = ADM_INVALID_PRIMARY_DEVICE;
    gpAdmStatSvc->rxIndexToSessionStreamID[unIndex]   = 0;
    gpAdmStatSvc->txIndexToSessionStreamID[unIndex]   = 0;
  }

  //Initialize the number of RX/TX/VPTX COPP opens issued
  gpAdmStatSvc->unNumRxAudioCoppOpenIssued = 0;
  gpAdmStatSvc->unNumTxAudioCoppOpenIssued = 0;
  gpAdmStatSvc->unNumVpTxCoppOpenIssued    = 0;

  //Launch ADM thread
  if (ADSP_FAILED (result = qurt_elite_thread_launch(&(gpAdmStatSvc->hAdmSvc.threadId),\
                                                     ADM_STATIC_THREAD_NAME , \
                                                     NULL, ADM_THREAD_STACK_SIZE, \
                                                     elite_get_thrd_prio(ELITETHREAD_STAT_AUDIO_DEV_SVC_PRIO_ID), \
                                                     AdmWorkLoop, (void*) gpAdmStatSvc,\
                                                     QURT_ELITE_HEAP_DEFAULT)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Thread launch failed, result = %d", result);
    return result;
  }

  //Register with qurt_elite memory map.
  qurt_elite_memorymap_register(&admMemoryMapClient);

  adm_database_init();

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Created, memorymapclient: %lx", admMemoryMapClient);
  return ADSP_EOK;
}

static int AdmWorkLoop(void *pInstance)
{
  AdmStatSvc_InfoType *pAdmSer = (AdmStatSvc_InfoType *) pInstance;

  uint32_t admCmdMask, channelBitMask, admRspMask, unCurrWaitMask = 0;
  ADSPResult result;

  //MMPM Registration.
  result = Adm_RegisterAdsppm(gpAdmStatSvc);
  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to register with ADSPPM %x",result);
    return result;
  }

  admCmdMask = qurt_elite_queue_get_channel_bit(pAdmSer->hAdmSvc.cmdQ);
  admRspMask = qurt_elite_queue_get_channel_bit(pAdmSer->admRspQ);
  memset(&pAdmSer->unChannelWaitMask, 0, sizeof(qurt_elite_atomic_word_t));

  /* Always listen to ADM Service CmdQ and ADM Service RspQ */
  qurt_elite_atomic_or(&pAdmSer->unChannelWaitMask, (admCmdMask | admRspMask));

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Entering ADM Workloop with mask %x",qurt_elite_atomic_get(&pAdmSer->unChannelWaitMask));
  while(1)
  {
    /* Before entering the workloop, atomically fetch the channel wait mask */
    unCurrWaitMask = qurt_elite_atomic_get(&pAdmSer->unChannelWaitMask);

    channelBitMask = qurt_elite_channel_wait(&pAdmSer->admChannel, unCurrWaitMask);

    /* Process Response Queue First */
    if(admRspMask & channelBitMask)
    {
      result = AdmSvc_ProcessRspQueue((void*)pAdmSer, 1);
      if (ADSP_ETERMINATED == result) return ADSP_EOK;
    }

    /* Process all Queues now including responses */
    unCurrWaitMask = qurt_elite_atomic_get(&pAdmSer->unChannelWaitMask);
    channelBitMask = qurt_elite_channel_poll(&pAdmSer->admChannel, unCurrWaitMask);

    result = AdmSvc_ProcessAllQueues(pAdmSer, (int)channelBitMask);

    /* If terminated exit immediately */
    if (ADSP_ETERMINATED == result) return ADSP_EOK;

  }
}

static ADSPResult AdmSvc_ProcessCmdQueue(void *pAudStatAdmSvc, int nChannelBit)
{
  ADSPResult result = ADSP_EOK;
  const uint32_t AdmHandlerTableSize = sizeof(pAdmStatServHandler)/sizeof(pAdmStatServHandler[0]);
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Process Cmd Q");
#endif
  result = elite_svc_process_cmd_queue(gpAdmStatSvc,
                                       &gpAdmStatSvc->hAdmSvc,
                                       pAdmStatServHandler,
                                       AdmHandlerTableSize);

  return result;

}

static ADSPResult AdmSvc_ProcessRspQueue(void *pAudStatAdmSvc, int nChannelBit)
{
  elite_msg_any_t msg;

  ADSPResult                 result             = ADSP_EOK;
  AdmStatSvc_InfoType        *pAdmStatSvc       = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  elite_svc_msg_handler_func *pHandler          = pAdmStatServRspHandler;
  uint32_t                   handler_table_size = (sizeof(pAdmStatServRspHandler)/sizeof(pAdmStatServRspHandler[0]));
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Process Rsp Q");
#endif

  /*  Process all commands in the queue */
  for (;;)
  {
    // Take next msg off the q
    result = qurt_elite_queue_pop_front(pAdmStatSvc->admRspQ, (uint64_t*) &msg);

    // Process the msg
    if (ADSP_EOK == result)
    {
      if (msg.unOpCode >= handler_table_size)
      {
        if (ADSP_FAILED(result = elite_svc_unsupported(pAudStatAdmSvc, &msg)))
        {
          // in case of errors, return them
          return result;
        }
      }

      // table lookup to call handling function, with FALSE to indicate processing of msg
      if (ADSP_FAILED(result = pHandler[msg.unOpCode](pAudStatAdmSvc, &msg)))
      {
        // in case of errors, return them
        return result;
      }
      // successfully processed msg, check for additional msgs
    }
    else if (ADSP_ENEEDMORE == result)
    {
      // if there are no more msgs in the q, return successfully
      return ADSP_EOK;
    }
    else
    {
      // all other results of QueuePopFront, return error code
      // actually QueuePopFront does not return other codes, keep it safe here
      return result;
    }

  } //for (;;)
  return result; //to keep compiler happy

}

static ADSPResult AdmSvc_ProcessDeviceCmdQ(void *pInstance, int nChannelBit)
{
  ADSPResult          result       = ADSP_EOK;
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pInstance;
  elite_msg_any_t     msg;
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Process DevCmd Q");
#endif

  uint16_t unCoppID     = Adm_GetDeviceIdFromChannelBit((uint32_t)nChannelBit);
  bool_t   isCompressed = FALSE;
  uint32_t unCmdQMask   = 0;

  void *pDevicePtr = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompressed);

  if(!pDevicePtr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ProcessDevCmdQ [%d] failed fetch calport struct", unCoppID);
    return ADSP_EFAILED;
  }

  DeviceCmdProcInfo_t *pDevCmd = NULL;
  qurt_elite_queue_t  *pCmdQ   = NULL;

  if(isCompressed)
  {
    ComprCoppInfo_t *pComprCoppInfo = (ComprCoppInfo_t*)pDevicePtr;

    pDevCmd    = &pComprCoppInfo->devCmd;
    unCmdQMask = pComprCoppInfo->devCmdQMask;
    pCmdQ      = pComprCoppInfo->pCmdQ;
  }
  else
  {
    AdmCalPort_Type *phCalPort = (AdmCalPort_Type*)pDevicePtr;

    pDevCmd    = &phCalPort->devCmd;
    unCmdQMask = phCalPort->devCmdQMask;
    pCmdQ      = phCalPort->pCmdQ;
  }

  Adm_RemoveDeviceCmdQFromMask(pAdmStatSvc, unCmdQMask);
  if(pDevCmd->unRespsNeeded)
  {
    /* If this is TRUE, then this command queue must stay off the mask */
    return ADSP_EOK;
  }

  memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));

  Adm_DeviceCmdQHandler_f *pHandler          = pAdmStatServDeviceCmdQHandler;
  uint32_t                handler_table_size = (sizeof(pAdmStatServDeviceCmdQHandler)/sizeof(pAdmStatServDeviceCmdQHandler[0]));

  do /* Pop a message atleast once */
  {
    /* Check if there are any messages available*/
    result = qurt_elite_queue_pop_front(pCmdQ, (uint64_t*) &msg);

    /* The loop exits under 2 conditions -
       *  The current command needs to wait on a response
       *  (or)
       *  there are no new commands
    */

    // Process the msg
    if (ADSP_EOK == result)
    {
      if (msg.unOpCode >= handler_table_size)
      {
        result = elite_svc_unsupported(pAdmStatSvc, &msg);
      }
      else
      {
        result = pHandler[msg.unOpCode](pAdmStatSvc, &msg);
      }

    }
    else if(ADSP_ENEEDMORE == result)
    {
      break;
    }

  }while(0 == pDevCmd->unRespsNeeded);

  if(0 == pDevCmd->unRespsNeeded)
  {
    Adm_AddDeviceCmdQToMask(pAdmStatSvc, unCmdQMask);
  }

  return result;

}

static ADSPResult AdmSvc_ProcessAllQueues(void* pInstance, int channelBitMask)
{
  ADSPResult result = ADSP_EOK;
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: channelBitMask to process all queues %x",channelBitMask);
#endif

  if(!channelBitMask)
  {
    return ADSP_EOK;
  }

  int32_t nEndBit, nStartBit, nMask;

  /* Identify the range of the set channel bits */

  nEndBit   = AUDIO_DEV_MGR_MAX_NUM_CHANNEL_BITS - s32_cl0_s32(channelBitMask);
  nStartBit = s32_get_lsb_s32(channelBitMask);
  nMask     = 0x1 << nStartBit;

#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: nStartBit %x, nEndBit %x",nStartBit,nEndBit);
#endif

  for ( int32_t i = nStartBit; i < nEndBit; i++ )
  {
    /* Process each ready channel bit once */
    if ( nMask & channelBitMask )
    {
      result = pAdmStatServQHandler[i](pInstance,i);
    }

    nMask <<= 1;

    /*Service is destroyed, return immediately */
    if(result == ADSP_ETERMINATED) break;
  } // LOOP over all channels.

  return result;

}

static ADSPResult AdmSvc_DeviceCmdQAprMsgHandler(void* pAudStatAdmSvc, elite_msg_any_t* pMsg)
{
  ADSPResult          result       = ADSP_EOK;
  elite_apr_packet_t  *pPkt;
  elite_apr_port_t    port;
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  DeviceCmdProcInfo_t *pDevCmd     = NULL;

  pPkt = (elite_apr_packet_t *)(pMsg->pPayload);
  port = elite_apr_if_get_dst_port(pPkt);

  bool_t isCompr;
  void *pCalPort = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, port, &isCompr);

  if(!pCalPort)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM; DeviceCmdQ [%d] failed to fetch calport struct", port);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle,pPkt,ADSP_EBADPARAM);
    return ADSP_EBADPARAM;
  }

  if(isCompr)
  {
    pDevCmd = &((ComprCoppInfo_t*)pCalPort)->devCmd;
  }
  else
  {
    pDevCmd = &((AdmCalPort_Type*)pCalPort)->devCmd;
  }

  pDevCmd->pCurrPkt = pPkt;
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: DeviceCmdQ [%d] rcvd APR msg [opcode] = [0x%08x]", port, pPkt->opcode);

  switch(pPkt->opcode)
  {
    case ADM_CMD_SET_PP_PARAMS_V5:
    case ADM_CMD_SET_PP_PARAMS_V6:
    {
      result = Adm_AprSetParamsCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_GET_PP_PARAMS_V5:
    case ADM_CMD_GET_PP_PARAMS_V6:
    {
      result = Adm_AprGetPPParamsCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_GET_PP_TOPO_MODULE_LIST:
    case ADM_CMD_GET_PP_TOPO_MODULE_LIST_V2:
    {
      result = Adm_AprGetPPTopoModuleCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_DEVICE_CLOSE_V5:
    {
      result = Adm_AprDeviceCloseCmdHandler(pAudStatAdmSvc, pPkt);
      break;
    }
    case ADM_CMD_REGISTER_PP_EVENTS:
    {
      result = Adm_RegisterDegisterPPEvents(pAudStatAdmSvc, pPkt);
      break;
    }
    default:
    {
      result = ADSP_EUNSUPPORTED;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd unsupported APR msg [%lu]", pPkt->opcode);
      break;
    }
  }
  return result;
}

static ADSPResult AdmSvc_ProcessReservedQueue(void *pAudStatAdmSvc, int nChannelBit)
{
  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: This channel bit %d is reserved. Returning",nChannelBit);
  return ADSP_EUNEXPECTED;
}

static  ADSPResult AdmSvc_AprMsgHandler(void *pAudStatAdmSvc, elite_msg_any_t *pMsg)
{
  int                    result;
  elite_apr_packet_t     *pPkt;
  elite_apr_port_t       port;

  pPkt = (elite_apr_packet_t *)(pMsg->pPayload);
  port = elite_apr_if_get_dst_port(pPkt);

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: rcvd APR msg [opcode, dst port] = [0x%08x, 0x%x]", pPkt->opcode, port);
  switch(pPkt->opcode)
  {
    case ADM_CMD_DEVICE_OPEN_V5:
    case ADM_CMD_DEVICE_OPEN_V6:
    case ADM_CMD_DEVICE_OPEN_V7:
    case ADM_CMD_DEVICE_OPEN_V8:
    {
      result = Adm_AprDeviceOpenCmdHandler(pAudStatAdmSvc, pPkt);
      break;
    }
    case ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5:
    case ADM_CMD_STREAM_DEVICE_UNMAP_ROUTINGS_V5:
    {
      result = Adm_AprStreamDeviceMapRoutingsHandler(pAudStatAdmSvc, pPkt);
      break;
    }

    case ADM_CMD_MATRIX_MAP_ROUTINGS_V5:
    {
      result = Adm_AprMtMxMapRoutingsHandler(pAudStatAdmSvc, pPkt, eASM_TYPE);
      break;
    }
    case ADM_CMD_MATRIX_RAMP_GAINS_V5:
    {
      result = Adm_AprMatrixRampGainsCmdHandler_v5(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_MATRIX_RAMP_GAINS_V6:
    {
      result = Adm_AprMatrixRampGainsCmdHandler_v6(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_MATRIX_RAMP_GAINS_V7:
    {
        result = Adm_AprMatrixRampGainsCmdHandler_v7(pAudStatAdmSvc,pPkt);
        break;
    }
    case ADM_CMD_MATRIX_MUTE_V5:
    case ADM_CMD_MATRIX_MUTE_V6:
    case ADM_CMD_MATRIX_MUTE_V7:
    {
      result = Adm_AprMatrixMuteCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_CONNECT_AFE_PORT_V5:
    {
      result = Adm_AprAfeConnectCmdHandler(pAudStatAdmSvc,pPkt, ((AdmStatSvc_InfoType*)pAudStatAdmSvc)->admInlineRspQ);
      break;
    }
    case ADM_CMD_DISCONNECT_AFE_PORT_V5:
    {
      result = Adm_AprAfeDisconnectCmdHandler((AdmStatSvc_InfoType*)pAudStatAdmSvc,pPkt,(((AdmStatSvc_InfoType*)pAudStatAdmSvc)->admInlineRspQ));
      break;
    }
    case ADM_CMD_SHARED_MEM_MAP_REGIONS:
    {
      result = elite_mem_shared_memory_map_regions_cmd_handler(admMemoryMapClient, ((AdmStatSvc_InfoType*)pAudStatAdmSvc)->admAprHandle,
                                                               pPkt, ADM_CMDRSP_SHARED_MEM_MAP_REGIONS);
      break;
    }
    case ADM_CMD_SHARED_MEM_UNMAP_REGIONS:
    {
      result = elite_mem_shared_memory_un_map_regions_cmd_handler(admMemoryMapClient, ((AdmStatSvc_InfoType*)pAudStatAdmSvc)->admAprHandle, pPkt);
      break;
    }
    case ADM_CMD_ADD_TOPOLOGIES_V5:
    {
      result = Adm_AprAddTopologiesHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_SET_PSPD_MTMX_STRTR_PARAMS_V5:
    case ADM_CMD_SET_PSPD_MTMX_STRTR_PARAMS_V6:
    {
      result = Adm_AprSetPspdMtMxStrtrParamsCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_REGISTER_IEC_61937_FMT_UPDATE:
    {
      result = Adm_RegisterIEC61937FmtUpdate(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_SET_MTMX_STRTR_DEV_PARAMS_V1:
    {
      result = Adm_AprSetMtMxStrtrDeviceParamsCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    case ADM_CMD_GET_MTMX_STRTR_DEV_PARAMS_V1:
    {
      result = Adm_AprGetMtMxStrtrDeviceParamsCmdHandler(pAudStatAdmSvc,pPkt);
      break;
    }
    default:
    {
      result = ADSP_EUNSUPPORTED;
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd unsupported APR msg [%lu]", pPkt->opcode);
      break;
    }
  }
  return result;
}

static  ADSPResult AdmSvc_CustomMsgHandler(void* pAudStatAdmSvc, elite_msg_any_t* pMsg)
{
  ADSPResult    result;

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: rcvd custom msg [opcode] = [0x%lx]", ((elite_msg_custom_header_t *)pMsg->pPayload)->unSecOpCode);
  switch (((elite_msg_custom_header_t *)pMsg->pPayload)->unSecOpCode)
  {
    case ELITEMSG_CUSTOM_ADM_STREAM_CONNECT:
    {
      result = Adm_MsgStreamConnect((AdmStatSvc_InfoType *) pAudStatAdmSvc,pMsg, eASM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_STREAM_DISCONNECT:
    {
      result = Adm_MsgStreamDisconnect((AdmStatSvc_InfoType *) pAudStatAdmSvc,pMsg, eASM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_STREAM_DISABLE:
    {
      result = Adm_MsgStreamDisable((AdmStatSvc_InfoType *) pAudStatAdmSvc, pMsg, eASM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_STREAM_MTMX_RECONFIG:
    {
      result = Adm_MsgStreamMtMxReconfig((AdmStatSvc_InfoType *) pAudStatAdmSvc, pMsg, eASM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_LSM_STREAM_CONNECT:
    {
      result = Adm_MsgStreamConnect((AdmStatSvc_InfoType *) pAudStatAdmSvc,pMsg, eLSM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_LSM_STREAM_DISCONNECT:
    {
      result = Adm_MsgStreamDisconnect((AdmStatSvc_InfoType *) pAudStatAdmSvc,pMsg, eLSM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_LSM_STREAM_DISABLE:
    {
      result = Adm_MsgStreamDisable((AdmStatSvc_InfoType *) pAudStatAdmSvc, pMsg, eLSM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_LSM_STREAM_MTMX_RECONFIG:
    {
      result = Adm_MsgStreamMtMxReconfig((AdmStatSvc_InfoType *) pAudStatAdmSvc, pMsg, eLSM_TYPE);
      break;
    }
    case ELITEMSG_CUSTOM_ADM_GET_DEVICE_PATH_DELAY:
    {
      result = Adm_MsgGetDevicePathDelay((AdmStatSvc_InfoType *) pAudStatAdmSvc, pMsg, eASM_TYPE);
      break;
    }
    default:
    {
      result = ADSP_EUNSUPPORTED;
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Error: ADM rcvd unsupported custom msg [%lu]",((elite_msg_custom_header_t *)pMsg->pPayload)->unSecOpCode);
      elite_msg_finish_msg(pMsg, result);
      break;
    }
  }
  return result;
}

static ADSPResult AdmSvc_RspHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg)
{

  ADSPResult result = ADSP_EOK;
  AdmStatSvc_InfoType* pAdmStatSvc = (AdmStatSvc_InfoType*) pAudStatAdmSvc;

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: Received Rsp Event/Opcode 0x%lx", pMsg->unOpCode);

  switch(pMsg->unOpCode)
  {
    case ELITE_CUSTOM_MSG:
    {
      elite_msg_custom_header_t *pMsgPayload = (elite_msg_custom_header_t*)pMsg->pPayload;

      switch(pMsgPayload->unSecOpCode)
      {
        case ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_OPEN_HELPER_THRD:
        case ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_CLOSE_HELPER_THRD:
        {
          MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: Received response for custom message sec opcode 0x%lx with result: 0x%lx",pMsgPayload->unSecOpCode,pMsgPayload->unResponseResult);
          result = Adm_HelperThreadResponseHandler(pAdmStatSvc,pMsg);
          break;
        }

        case ELITEMSG_CUSTOM_GET_PP_TOPOLOGY_MODULES:
        case ELITEMSG_CUSTOM_GET_PP_TOPOLOGY_MODULES_V2:
        {
          result = Adm_GetPPTopoModulesRspHandler(pAdmStatSvc,pMsg);
          break;
        }

        default:
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: Received invalid custom message sec opcode 0x%lx ",pMsgPayload->unSecOpCode);
          result = ADSP_EUNSUPPORTED;
          break;
        }
      }
      break;
    }

    case ELITE_CMD_SET_PARAM:
    {
      result = Adm_SetParamResponseHandler(pAdmStatSvc,pMsg);
      break;
    }

    case ELITE_CMD_GET_PARAM:
    {
      result = Adm_GetParamResponseHandler(pAdmStatSvc,pMsg);
      break;
    }
    case ELITE_CMD_REGISTER_APR_EVENT:
    {
      result = Adm_RegisterDeregisterAprEventRspHandler(pAdmStatSvc,pMsg);
      break;
    }
    default:
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: Received invalid rsp message opcode 0x%lx ",pMsg->unOpCode);
      result = ADSP_EUNSUPPORTED;
      break;
    }
  }

  elite_msg_release_msg(pMsg);
  return result;


}

static ADSPResult AdmSvc_Start (void *pAudStatAdmSvc, elite_msg_any_t* pMsg)
{
  ADSPResult          result;
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;

  // Register ADM's ISR callback function with APR
  char aAdmSvcName[] = "qcom.adsp.adm";
  uint32_t ulAdmNameSize = strlen( aAdmSvcName );
  uint16_t usRetAddr = 0;

  if (ADSP_FAILED( result = elite_apr_if_register_by_name( &(pAdmStatSvc->admAprHandle),
                                                           &usRetAddr, aAdmSvcName,
                                                           ulAdmNameSize,
                                                           &AudDevMgr_AprCallBackFct,
                                                           pAudStatAdmSvc)) )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM failed to register ISR callback function with APR 0x%x", result);
    elite_msg_finish_msg(pMsg, result);
    return result;
  }

  if (ADSP_FAILED( result = AudDevMgr_SetAprHandle(pAdmStatSvc->admAprHandle)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM failed to set ADM APR handle 0x%x", result);
    elite_msg_finish_msg(pMsg, result);
    return result;
  }
  elite_msg_finish_msg( pMsg, ADSP_EOK);
  return ADSP_EOK;
}

static ADSPResult AdmSvc_Destroy (void *pAudStatAdmSvc, elite_msg_any_t* pMsg)
{
  ADSPResult           result;
  AdmStatSvc_InfoType  *pAdmStatSvc = (AdmStatSvc_InfoType*) pAudStatAdmSvc;
  int                  joinResult;
  qurt_elite_thread_t  threadID;

  //Check and kill any active helper threads launched by ADM
  AdmSvc_CheckHandleHelperThreads(pAdmStatSvc);

  //Destory TX audio matrix
  threadID = pAdmStatSvc->hTxMatrix->threadId;
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of destroying ADM, issuing DESTROY_TX_MT_MX cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDestroySvc(pAdmStatSvc->hTxMatrix)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MXAT destroy failed, result = %d", result);
    return result;
  }

  qurt_elite_thread_join(threadID, &joinResult);
  if (ADSP_FAILED(joinResult))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MXAT thread join failed, result = %d", result);
    return joinResult;
  }
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MXAT thread joined successfully");

  //Destory RX audio matrix
  threadID = pAdmStatSvc->hRxMatrix->threadId;
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of destroying ADM, issuing DESTROY_RX_MT_MX cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDestroySvc(pAdmStatSvc->hRxMatrix)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MXAR destroy failed, result = %d", result);
    return result;
  }

  qurt_elite_thread_join(threadID, &joinResult);
  if (ADSP_FAILED(joinResult))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MXAR thread join failed, result = %d", result);
    return joinResult;
  }
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MXAR thread joined successfully");

  //Destroy RX router (only if applicable)
  if(NULL != pAdmStatSvc->rxStRtrParams.hSvcHandle)
  {
    threadID = pAdmStatSvc->rxStRtrParams.hSvcHandle->threadId;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of destroying ADM, issuing destroy Rx Stream Router");

    if (ADSP_FAILED(result = Adm_SendCmdDestroySvc(pAdmStatSvc->rxStRtrParams.hSvcHandle)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Rx Stream Router destroy failed, result = %d", result);
      return result;
    }

    qurt_elite_thread_join(threadID, &joinResult);
    if (ADSP_FAILED(joinResult))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Rx Stream Router thread join failed, result = %d", result);
      return joinResult;
    }
    pAdmStatSvc->rxStRtrParams.hSvcHandle = NULL;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Rx Stream Router thread joined successfully");
  }

  //Destroy TX router (only if applicable)
  if(NULL !=  pAdmStatSvc->txStRtrParams.hSvcHandle)
  {
    threadID = pAdmStatSvc->txStRtrParams.hSvcHandle->threadId;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of destroying ADM, issuing destroy Tx Stream Router");

    if (ADSP_FAILED(result = Adm_SendCmdDestroySvc(pAdmStatSvc->txStRtrParams.hSvcHandle)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Tx Stream Router destroy failed, result = %d", result);
      return result;
    }

    qurt_elite_thread_join(threadID, &joinResult);
    if (ADSP_FAILED(joinResult))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Tx Stream Router thread join failed, result = %d", result);
      return joinResult;
    }
    pAdmStatSvc->txStRtrParams.hSvcHandle = NULL;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Tx Stream Router thread joined successfully");
  }

  elite_svc_deinit_cmd_queue(gpAdmStatSvc->hAdmSvc.cmdQ);
  elite_svc_deinit_cmd_queue(gpAdmStatSvc->admInlineRspQ);
  elite_svc_deinit_cmd_queue(gpAdmStatSvc->admRspQ);

  qurt_elite_channel_destroy(&gpAdmStatSvc->admChannel);

  qurt_elite_mutex_destroy(&gpAdmStatSvc->admLock);

  adm_database_teardown();

  result = Adm_DeregisterAdsppm(gpAdmStatSvc);

  //Since AudDevMgr doesn't send a response for the ELITE_CMD_DESTROY_SERVICE,
  //it is responsible to return the payload buffer.
  elite_msg_return_payload_buffer( pMsg );
  return ADSP_ETERMINATED;
}

static void AdmSvc_CheckHandleHelperThreads(AdmStatSvc_InfoType *pAdmStatSvc)
{
  uint32_t num_wait = 0, num_finish = 0;
  elite_msg_any_t msg;

  /* Loop through calport structures and identify any active helper thread */
  for(uint32_t i = 0; i < ADM_MAX_COPPS; i++)
  {
    AdmCalPort_Type *phCalPort = &(pAdmStatSvc->deviceCalPort[i]);
    if(phCalPort->helperThrdInfo.tId != 0)
    {
      num_wait++;
    }
  }

  for(uint32_t i = 0; i < STRTR_MAX_PORTS; i++)
  {
    ComprCoppInfo_t *pComprCopp = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[i]);
    if(pComprCopp->helperThrdInfo.tId != 0)
    {
      num_wait++;
    }

    pComprCopp = &(pAdmStatSvc->txStRtrParams.compr_copp_info[i]);
    if(pComprCopp->helperThrdInfo.tId != 0)
    {
      num_wait++;
    }
  }

  if( 0 == num_wait)
  {
    return; //Nothing to be done
  }

  while(num_finish != num_wait)
  {
    int32_t res = qurt_elite_queue_pop_front(pAdmStatSvc->admRspQ, (uint64*)(&msg));

    /* Keep popping till the number of expected responses are received */
    if (res == ADSP_ENEEDMORE)
    {
      continue;
    }

    elite_msg_custom_header_t *p_msg_payload = (elite_msg_custom_header_t*)msg.pPayload;
    ADSPResult                result         = ADSP_EOK;

    if(ELITE_CUSTOM_MSG == msg.unOpCode)
    {
      if((ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_CLOSE_HELPER_THRD == p_msg_payload->unSecOpCode) ||
          (ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_OPEN_HELPER_THRD == p_msg_payload->unSecOpCode))
      {
        if (ADSP_FAILED(result = AdmSvc_RspHandler(pAdmStatSvc, &msg)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to handle the response with result 0x%x",result);
        }
        num_finish++;
      }
    }
    /* release msg back to qurt_elite_buf_mgr*/
    elite_msg_release_msg(&msg);
  }

}

static ADSPResult Adm_SendHelperThrdEndMsg(AdmStatSvc_InfoType *pAdmStatSvc,uint16_t unCoppID, ADSPResult status, uint32_t opcode)
{
  uint32_t                 client_token = 0;
  elite_msg_any_t          msg;
  int                      nActualSize;
  ADSPResult               result       = ADSP_EOK;
  qurt_elite_bufmgr_node_t bufMgrNode;

  client_token = Adm_GenerateToken(eHELPER,unCoppID);

  if ( ADSP_FAILED(result = elite_mem_get_buffer(sizeof(EliteMsg_CustomAdmRspHelperThread),
                                                 &bufMgrNode, &nActualSize)))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to create mesage to send helper thread rsp");
    return result;
  }

  EliteMsg_CustomAdmRspHelperThread *pHelperRsp = (EliteMsg_CustomAdmRspHelperThread*) bufMgrNode.pBuffer;

  pHelperRsp->pResponseQ     = pAdmStatSvc->admRspQ;
  pHelperRsp->unClientToken  = client_token;
  pHelperRsp->pBufferReturnQ = bufMgrNode.pReturnQ;
  pHelperRsp->unSecOpCode    = opcode;
  pHelperRsp->deviceId       = unCoppID;

  msg.unOpCode = ELITE_CUSTOM_MSG;
  msg.pPayload = (void*)pHelperRsp;
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Sending Rsp for coppID [%d] with status 0x%x",unCoppID,status);
#endif

  elite_svc_send_ack(&msg,status);

  return ADSP_EOK;

}

static ADSPResult Adm_MsgStreamDisable(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t *pMsg,
                                       adm_client_type_t eClient)
{
  uint16_t                               *pSnIDToPortIDMap;
  EliteMsg_CustomAdmStreamConnectType    *pPayload = (EliteMsg_CustomAdmStreamConnectType *) pMsg->pPayload;
  ADSPResult                             result = ADSP_EOK;
  uint16_t                                unIndex = ADM_INVALID_INDEX;
  qurt_elite_queue_t *pRspQ = pAudStatAdmSvc->admInlineRspQ;

  if (ADM_TX_DIR != pPayload->direction)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: Adm_MsgStreamDisable rcvd invalid dir [%lu]", pPayload->direction);
    result = ADSP_EBADPARAM;
    goto __bailoutStreamDisable;
  }

  if(pPayload->is_compressed)
  {
    if (eLSM_TYPE == eClient)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: Adm_MsgStreamDisable requested for LSM session on compressed path.");
      result = ADSP_EBADPARAM;
      goto __bailoutStreamDisable;
    }
    uint32_t output_port_id = STRTR_INVALID_PORT_ID;
    for(uint32_t i=0; i<STRTR_MAX_PORTS; i++)
    {
      if(pPayload->unSessionID == pAudStatAdmSvc->txStRtrParams.port_id_to_session[i])
      {
        output_port_id = i;
        break;
      }
    }
    if(STRTR_INVALID_PORT_ID == output_port_id)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: Adm_MsgStreamDisable requested for unconnected session");
      result = ADSP_EBADPARAM;
      goto __bailoutStreamDisable;
    }

    if(ADSP_FAILED(result = Adm_MsgStRtrDisableOutputPort(pAudStatAdmSvc, TX_STRTR_ID, output_port_id, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Adm_MsgStRtrDisableOutputPort failed, result = %d", result);
      goto __bailoutStreamDisable;
    }
  }
  else
  {
    unIndex = Adm_SessionStreamIDToIndex(pAudStatAdmSvc, ADM_TX_DIR, (uint16_t)(pPayload->unSessionID), eClient);
    if(ADM_INVALID_INDEX == unIndex)
    {
      result = ADSP_EBADPARAM;
      goto __bailoutStreamDisable;
    }

    if (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == pAudStatAdmSvc->txStreamSessionInfo[unIndex].stream_perf_mode)
    {
      if (eLSM_TYPE == eClient)
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Adm_MsgStreamDisable: LLNP perf mode used for LSM session. Unsupported");
        result = ADSP_EBADPARAM;
        goto __bailoutStreamDisable;
      }
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "Adm_MsgStreamDisable: LLNP Tx Session 0x%lx received stream disable",
            pPayload->unSessionID);
      result = Adm_LlnpStreamDisable(pAudStatAdmSvc, (uint16_t)pPayload->unSessionID, eClient);
      if (ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
              "Tx Adm_MsgStreamDisable: Failed to disable LLNP Tx Session 0x%lx.",
              pPayload->unSessionID);
        goto __bailoutStreamDisable;
      }
    }
    else
    {

      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
            "TX Adm_MsgStreamDisable, issuing Adm_SendCmdDisableMtMxOutPort. SessionID: 0x%lX, Index: %d",
            pPayload->unSessionID, unIndex);

      pSnIDToPortIDMap = &(pAudStatAdmSvc->sessionIDToTxMtMxOutPortIDMap[0]);
      elite_svc_handle_t *pMtMxHandle =  pAudStatAdmSvc->hTxMatrix;
      if (ADSP_FAILED(result = Adm_SendCmdDisableMtMxOutPort(pAudStatAdmSvc,
                                                             pSnIDToPortIDMap[unIndex],
                                                             pMtMxHandle, pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Adm_SendCmdDisableMtMxOutPort failed, result = %d", result);
        goto __bailoutStreamDisable;
      }
    }
  }

  __bailoutStreamDisable:
  elite_svc_send_ack(pMsg, result);
  return result;
}

static ADSPResult Adm_MsgStreamConnect(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient)
{
  ADSPResult                            result = ADSP_EOK;
  EliteMsg_CustomAdmStreamConnectType   *pPayload = (EliteMsg_CustomAdmStreamConnectType *) pMsg->pPayload;

  if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pPayload->stream_perf_mode)
      || (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pPayload->stream_perf_mode))
  {
    result = Adm_DirectStreamConnect(pAudStatAdmSvc, pPayload, eClient);
  }
  else if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pPayload->stream_perf_mode)
  {
    result = Adm_LlnpStreamConnect(pAudStatAdmSvc, pPayload, eClient);
  }
  else
  {
    if(pPayload->is_compressed)
    {
      result = Adm_MsgStRtrStreamConnect(pAudStatAdmSvc, pPayload, eClient);
    }
    else
    {
      result = Adm_MsgMtMxStreamConnect(pAudStatAdmSvc, pPayload, eClient);
    }
  }
  elite_svc_send_ack(pMsg, result);
  return result;
}

static ADSPResult Adm_MsgStreamDisconnect(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient)
{
  ADSPResult                            result = ADSP_EOK;
  EliteMsg_CustomAdmStreamConnectType   *pPayload = (EliteMsg_CustomAdmStreamConnectType *) pMsg->pPayload;
  uint16_t unStreamPerfMode = 0;
  uint16_t unIndex = Adm_SessionStreamIDToIndex(pAudStatAdmSvc, pPayload->direction, (uint16_t)(pPayload->unSessionID), eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    result = ADSP_EBADPARAM;
    goto __bailoutStreamDisconnect;
  }

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Adm_MsgStreamDisconnect, SessionID: 0x%lX, Index: %d", pPayload->unSessionID, unIndex);

  // Find stream performance mode based on direction
  if (ADM_RX_DIR == pPayload->direction)
  {
    unStreamPerfMode = pAudStatAdmSvc->rxStreamSessionInfo[unIndex].stream_perf_mode;
  }
  else
  {
    unStreamPerfMode = pAudStatAdmSvc->txStreamSessionInfo[unIndex].stream_perf_mode;
  }

  // Disconnect
  if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == unStreamPerfMode)
      || (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == unStreamPerfMode))
  {
    result = Adm_DirectStreamDisconnect(pAudStatAdmSvc, pPayload, eClient);
  }
  else if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == unStreamPerfMode)
  {
    result = Adm_LlnpStreamDisconnect(pAudStatAdmSvc, pPayload, eClient);
  }
  else
  {
    if(pPayload->is_compressed)
    {
      result = Adm_MsgStRtrStreamDisconnect(pAudStatAdmSvc, pPayload, eClient);
    }
    else
    {
      result = Adm_MsgMtMxStreamDisconnect(pAudStatAdmSvc, pPayload, eClient);
    }
  }

  __bailoutStreamDisconnect:
  elite_svc_send_ack(pMsg, result);
  return result;
}

void Adm_ResetCalPort(void *ptr, bool_t isCompressed)
{
  if (NULL == ptr)
  {
    return;
  }

  if(isCompressed)
  {
    ComprCoppInfo_t *pComprCopp = (ComprCoppInfo_t*)ptr;
    memset(pComprCopp, 0, sizeof(ComprCoppInfo_t));

    pComprCopp->unCoppID         = ADM_COPP_ID_INVALID;
    pComprCopp->unCoppTopologyID = AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE;
    pComprCopp->afe_port_id      = AFE_PORT_ID_INVALID;
    pComprCopp->strtr_port_id    = STRTR_INVALID_PORT_ID;
    pComprCopp->unCoppStatus     = ADM_COPP_STATUS_INACTIVE;

  }
  else
  {
    AdmCalPort_Type *phCalPort = (AdmCalPort_Type*)ptr;
    // Clear calport structure
    memset((void*)phCalPort, 0, sizeof(AdmCalPort_Type));

    // Initialize default values of cal port structure
    phCalPort->unCoppStatus                    = ADM_COPP_STATUS_INACTIVE;
    phCalPort->unCoppType                      = ADM_COPP_TYPE_NONE;
    phCalPort->unMtMxSampleRate                = ADM_SAMPLING_RATE_48K;
    phCalPort->unEID1.unSampleRate             = ADM_SAMPLING_RATE_48K;
    phCalPort->unEID2.unSampleRate             = ADM_SAMPLING_RATE_48K;
    phCalPort->unEID3.unSampleRate             = ADM_SAMPLING_RATE_48K;
    phCalPort->unCoppNumAfeFrames              = ADM_LEGACY_NUM_AFE_FRAMES;
    phCalPort->unPrimaryDevice                 = ADM_INVALID_PRIMARY_DEVICE;
    phCalPort->bIsCoppInLoopBackTopology       = FALSE;
    phCalPort->bIsCoppInDeviceLoopBackTopology = FALSE;
    phCalPort->bIsCoppConnectedToPseudoPort    = FALSE;
    phCalPort->unDevicePerfMode                = ADM_LEGACY_DEVICE_SESSION;
    phCalPort->unEID2.unAfePortID              = ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE;

  }
  return;
}

void Adm_InitCalPort(AdmCalPort_Type *phCalPort, adm_cmd_device_open_t *pCoppOpenParams)
{
  if (!phCalPort || !pCoppOpenParams)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: received bad pointers! phCalPort 0x%p, and Opencmd payload pointer 0x%p",
          phCalPort, pCoppOpenParams);
    return ;
  }

  if((pCoppOpenParams->opcode == ADM_CMD_DEVICE_OPEN_V7) || (pCoppOpenParams->opcode == ADM_CMD_DEVICE_OPEN_V8))
  {
    phCalPort->unCoppMode         = pCoppOpenParams->mode_of_operation;
    phCalPort->unMtMxSampleRate   = pCoppOpenParams->sample_rate_eid1;
    phCalPort->unCoppNumAfeFrames = ADM_LEGACY_NUM_AFE_FRAMES;
    phCalPort->unCoppType         = ADM_COPP_TYPE_AUDIO_COPP;
    phCalPort->unCoppTopologyID   = pCoppOpenParams->topology_id;
    phCalPort->unDevicePerfMode   = (uint16_t)Adm_GetDevicePerfModeInOpenCmd(pCoppOpenParams->flags);

    //eid1 info
    phCalPort->unEID1.unAfePortID   = pCoppOpenParams->endpoint_id_1;
    phCalPort->unEID1.unSampleRate = pCoppOpenParams->sample_rate_eid1;
    phCalPort->unEID1.unNumChannels = pCoppOpenParams->dev_num_channel_eid1;
    for (uint32_t i = 0; i < phCalPort->unEID1.unNumChannels; i++)
    {
       phCalPort->unEID1.unChannelMap[i] = pCoppOpenParams->dev_channel_mapping_eid1[i];
    }
    phCalPort->unEID1.unBytesPerSample = elite_data_get_bytes_per_sample(pCoppOpenParams->bit_width_eid1);
    phCalPort->unEID1.unBitWidth = pCoppOpenParams->bit_width_eid1;

    //eid2 info
    /* Set default params for Endpoint ID 2 channel map & number of channels and SR*/
    phCalPort->unEID2.unNumChannels    = ADM_NUM_CHANNELS_MONO;
    phCalPort->unEID2.unChannelMap[0]  = PCM_CHANNEL_C;
    phCalPort->unEID2.unSampleRate = pCoppOpenParams->sample_rate_eid1;
    phCalPort->unEID2.unBytesPerSample = ADM_BYTES_PER_SAMPLE_TWO;
    phCalPort->unEID2.unAfePortID      = pCoppOpenParams->endpoint_id_2;
    phCalPort->unEID2.unBitWidth       = ADM_BITS_PER_SAMPLE_16;

    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != pCoppOpenParams->endpoint_id_2)
    {
      phCalPort->unEID2.unSampleRate  = pCoppOpenParams->sample_rate_eid2;
      phCalPort->unEID2.unNumChannels = pCoppOpenParams->dev_num_channel_eid2;

      for (uint32_t i = 0; i < phCalPort->unEID2.unNumChannels; i++)
      {
        phCalPort->unEID2.unChannelMap[i] = pCoppOpenParams->dev_channel_mapping_eid2[i];
      }

      phCalPort->unEID2.unBytesPerSample = elite_data_get_bytes_per_sample(pCoppOpenParams->bit_width_eid2);
      phCalPort->unEID2.unBitWidth       = pCoppOpenParams->bit_width_eid2;
    }

    //eid3 info
    phCalPort->unEID3.unAfePortID   = pCoppOpenParams->endpoint_id_3;
    phCalPort->unEID3.unSampleRate  = pCoppOpenParams->sample_rate_eid3;
    phCalPort->unEID3.unNumChannels = pCoppOpenParams->dev_num_channel_eid3;

    for (uint32_t i = 0; i < phCalPort->unEID3.unNumChannels; i++)
    {
      phCalPort->unEID3.unChannelMap[i] = pCoppOpenParams->dev_channel_mapping_eid3[i];
    }

    phCalPort->unEID3.unBytesPerSample = elite_data_get_bytes_per_sample(pCoppOpenParams->bit_width_eid3);
    phCalPort->unEID3.unBitWidth       = pCoppOpenParams->bit_width_eid3;

  }
  return;
}


static  ADSPResult Adm_MsgStreamMtMxReconfig(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient)
{
  ADSPResult                           result = ADSP_EOK;
  EliteMsg_CustomAdmStreamMtMxReConfig     *pPayload = (EliteMsg_CustomAdmStreamMtMxReConfig *) pMsg->pPayload;
  uint16_t                                 *pSnIDToPortIDMap, *pSnIDToPrCOPPIDMap, unCoppID;
  uint32_t                                 bytes_per_sample, unOutPortID, unNumOutBufs, unFrameSize;
  uint16_t                                 unIndex = ADM_INVALID_INDEX;
  elite_svc_handle_t                  *pMtMxHandle = pAudStatAdmSvc->hTxMatrix;
  elite_svc_handle_t                  *pSvc2Connect = pPayload->phPort;
  uint32_t                                  unBufferingMs = pPayload->buffering_ms;
  uint8_t unNativeModeFlags = 0;

  if (ADM_TX_DIR != pPayload->direction)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: Adm_MsgStreamMtMxReconfig rcvd invalid dir [%lu]", pPayload->direction);
    result = ADSP_EBADPARAM;
    goto __bailoutStreamMtMxReconfig;
  }

  unIndex = Adm_SessionStreamIDToIndex(pAudStatAdmSvc, ADM_TX_DIR, (uint16_t)(pPayload->unSessionID), eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    result = ADSP_EBADPARAM;
    goto __bailoutStreamMtMxReconfig;
  }

  pSnIDToPortIDMap = &(pAudStatAdmSvc->sessionIDToTxMtMxOutPortIDMap[0]);
  pSnIDToPrCOPPIDMap = &(pAudStatAdmSvc->txSessionIDToPrimCOPPIDMap[0]);
  unOutPortID = (uint32_t)(pSnIDToPortIDMap[unIndex]);
  unCoppID = pSnIDToPrCOPPIDMap[unIndex];

  MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "TX Adm_MsgStreamMtMxReconfig, SessionID: 0x%lX, Index: %d, OutPortID: %lu, PriCOPPID: %d",
        pPayload->unSessionID, unIndex, unOutPortID, unCoppID);

  //If this session is connected to a primary COPP whose corresponding matrix port is not running at 44.1 kHz
  //then, the o/p buffer frame size will be 5ms (default).
  unNumOutBufs = (unBufferingMs + (ADM_FRAME_SIZE_5MS - 1))/ADM_FRAME_SIZE_5MS;
  unFrameSize = ADM_FRAME_SIZE_5MS;

  bytes_per_sample = elite_data_get_bytes_per_sample(pPayload->bits_per_sample);

  if (TRUE == pPayload->bMtMxPassNativeNumChannels)
  {
    unNativeModeFlags = (1 << ADM_BIT_SHIFT_NATIVE_MODE_CHANNELS);
  }

  MSG_7(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Adm_MsgStreamMtMxReconfig, TX ReconfigMtMxOutPort cmd, unOutPortID=%lu, Byt/samp=%lu, NatMode=0x%x, #ch=%lu, Buff = %lu ms, #Buff = %lu, FrSize = %lu, Pull mode",
        unOutPortID, bytes_per_sample, pPayload->bMtMxPassNativeNumChannels, pPayload->num_channels, unBufferingMs, unNumOutBufs, unFrameSize);

  if (ADSP_FAILED(result = Adm_SendCmdReconfigMtMxOutPort(pAudStatAdmSvc, unOutPortID, PULL_MODE,
                                                          pPayload->num_channels,
                                                          &(pPayload->channel_mapping[0]),
                                                          pMtMxHandle, &pSvc2Connect, pPayload->bits_per_sample,unNumOutBufs, unNativeModeFlags)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ReconfigMtMxOutPort cmd failed, result = %d", result);
  }

  __bailoutStreamMtMxReconfig:
  elite_svc_send_ack(pMsg, result);
  return result;
}

static  ADSPResult Adm_AprDeviceCloseCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  ADSPResult          result       = ADSP_EOK;
  elite_apr_port_t    port         = elite_apr_if_get_dst_port(pPkt);
  uint16_t            unPortID     = ADM_GET_COPP_ID(port);

  if(ADSP_EOK == Adm_CheckCompDevIDValidity(pAdmStatSvc, unPortID))
  {
    result = Adm_DeviceCloseCmdHelperThread(pAdmStatSvc, pPkt);
  }
  else if(ADSP_EOK == Adm_CheckCoppValidity(pAdmStatSvc, unPortID, ADM_INVALID_DIRECTION))
  {
    result = Adm_DeviceCloseCmdHelperThread(pAdmStatSvc, pPkt);
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM Device Close rcvd invalid/inactive COPP ID/Device ID [%d]", unPortID);
    result = ADSP_EBADPARAM;
  }

  if(ADSP_FAILED(result))
  {
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  }

  return result;

}

static  ADSPResult Adm_DeviceCloseCmdLPCMHandler(AdmStatSvc_InfoType *pAdmStatSvc, elite_apr_packet_t *pPkt,
                                                 qurt_elite_queue_t *pRspQ)
{
  ADSPResult                   result = ADSP_EOK;
  int                          joinResult;
  uint16_t                     unCoppID;
  elite_svc_handle_t           **pphCopp, **pphAfePort;
  AdmCalPort_Type              *phCalPort;
  AdmDevSessionDelayParam_Type *pSessionDelayParam;
  qurt_elite_thread_t          coppThreadID;

  elite_apr_port_t port = elite_apr_if_get_dst_port(pPkt);
  unCoppID = ADM_GET_COPP_ID(port);

  phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
  pSessionDelayParam = &(pAdmStatSvc->pDevSessionDelayParam[unCoppID]);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_DEVICE_CLOSE_V5, COPP ID = %d", unCoppID);

  /* check if device performance mode is ULL*/
  if (ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
  {
    return (Adm_UllDeviceCloseCmdHandler(pAdmStatSvc, pPkt, unCoppID, eASM_TYPE, pRspQ));
  }
  else if (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode)
  {
    return (Adm_LlnpDeviceCloseCmdHandler(pAdmStatSvc, pPkt, unCoppID, eASM_TYPE, pRspQ));
  }
  else if (ADM_ULTRA_LOW_LATENCY_POST_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode)
  {
    return (Adm_UllppDeviceCloseCmdHandler(pAdmStatSvc, pPkt, unCoppID, eASM_TYPE, pRspQ));
  }

  pphCopp    = &(phCalPort->phDevCopp);
  pphAfePort = &(phCalPort->unEID1.phAfePort);

  if(TX_DIR == phCalPort->unCoppDirection)
  {
    /**************************************************************************************/
    /* Sequence to close Tx path COPreP:                                                  */
    /* i. Disable AFE port (stop it from sending samples to downstream COPreP)            */
    /* ii. Disconnect COPreP from MXAT input port (stop it from sending samples to MXAT)  */
    /* iii Close MXAT input port (return any held-up resources to upstreaem COPreP)       */
    /* iv. Destroy COPreP (also returns any held-up resources to upstream AFE port)       */
    /* v. Disconnect AFE port.                                                            */
    /**************************************************************************************/

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISABLE cmd (AFE Tx) on EP1: %d", phCalPort->unEID1.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID, *pphAfePort,
                                                      ELITEMSG_CUSTOM_AFECLIENTDISABLE,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISABLE cmd (AFE Tx) failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    if (((ADM_COPP_TYPE_VPTX == phCalPort->unCoppType) || ((ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType) && phCalPort->phDevCoppEcRef)) &&
        (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID) )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISABLE cmd (AFE Rx) on EP2: %d", phCalPort->unEID2.unAfePortID);

      if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                        phCalPort->unEID2.phAfePort,
                                                        ELITEMSG_CUSTOM_AFECLIENTDISABLE,
                                                        pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISABLE cmd (AFE Rx) failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
    }

    if (ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)
    {
      //Send ELITE_CMD_DISCONNECT to audio COPP.
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing COPP_DISCONNECT cmd");

      if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                              &((phCalPort->mtMxPort).phMtMxInPort->portHandle),
                                              ELITE_CMD_DISCONNECT)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
    }
    else
    {
      //Send ELITE_CMD_STOP_SERVICE to VPTx.
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing VPTx_STOP cmd");

      if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                              &((phCalPort->mtMxPort).phMtMxInPort->portHandle), ELITE_CMD_STOP_SERVICE)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: VPTx_STOP cmd failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
    }

    //Now, destroy audio matrix input port. This will make sure it returns PP's bufs back to PP before PP can be destroyed.
    elite_svc_handle_t *pMtMxHandle = pAdmStatSvc->hTxMatrix;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing CLOSE_MT_MX_IN_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxInPort(pAdmStatSvc,
                                                             (phCalPort->mtMxPort).phMtMxInPort->inPortID,
                                                             pMtMxHandle, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CLOSE_MT_MX_IN_PORT cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    //Store the COPP's thread ID before destroying it, so it can be used later for joining.
    coppThreadID = (*pphCopp)->threadId;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing COPP_DESTROY cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                            NULL, ELITE_CMD_DESTROY_SERVICE)))
    {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP_DESTROY cmd failed");
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISCONNECT cmd (AFE Tx) on EP1: %d", phCalPort->unEID1.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID, *pphAfePort,
                                                      ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Tx) failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    if( (   (ADM_COPP_TYPE_VPTX == phCalPort->unCoppType) || ( phCalPort->phDevCoppEcRef && (ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)) ) &&
        (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID) )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Tx ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISCONNECT cmd (AFE Rx) on EP2: %d", phCalPort->unEID2.unAfePortID);

      if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                        phCalPort->unEID2.phAfePort,
                                                        ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                        pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Rx) failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }

    }
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "All cmds to stop Tx Device in ADM_CMD_DEVICE_CLOSE have been issued");
  }
  else
  {
    /**************************************************************************************/
    /* Sequence to close Rx path COPP:                                                    */
    /* i. Disable MXAR output port (stop it from sending samples to downstream COPP)      */
    /* ii. Disconnect COPP from AFE port (stop it from sending samples to AFE port)       */
    /* iii Disconnect AFE port (return any held-up resources to upstreaem COPP)           */
    /* iv. Destroy COPP (also returns any held-up resources to upstream MXAR output port) */
    /* v. Disconnect MXAR output port.                                                    */
    /**************************************************************************************/

    elite_svc_handle_t *pMtMxHandle = pAdmStatSvc->hRxMatrix;

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Rx ADM_CMD_DEVICE_CLOSE, issuing DISABLE_MT_MX_OUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdDisableMtMxOutPort(pAdmStatSvc,
                                                           (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                           pMtMxHandle, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISABLE_MT_MX_OUT_PORT cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Rx ADM_CMD_DEVICE_CLOSE, issuing COPP_DISCONNECT cmd");

    if (ADSP_FAILED(result  = AdmSendCoppMsg(*pphCopp, pRspQ,
                                             *pphAfePort, ELITE_CMD_DISCONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Rx ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISCONNECT cmd on EP1: %d", phCalPort->unEID1.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                      *pphAfePort, ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    //Store the COPP's thread ID before destroying it, so it can be used later for joining.
    coppThreadID = (*pphCopp)->threadId;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Rx ADM_CMD_DEVICE_CLOSE, issuing COPP_DESTROY cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                            NULL, ELITE_CMD_DESTROY_SERVICE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DESTROY cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Rx ADM_CMD_DEVICE_CLOSE, issuing DISCONNECT_MT_MX_OUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxOutPort(pAdmStatSvc,
                                                              (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                              pMtMxHandle, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISCONNECT_MT_MX_OUT_PORT cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
    (phCalPort->mtMxPort).phMtMxOutPort = NULL;

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "All cmds to stop Rx Device in ADM_CMD_DEVICE_CLOSE have been issued");
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of ADM_CMD_DEVICE_CLOSE Waiting for COPP to join");
  qurt_elite_thread_join(coppThreadID, &joinResult);

  if (ADSP_FAILED(joinResult))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP thread join failed, result = %d", joinResult);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, joinResult);
    return joinResult;
  }
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP thread joined in Device in ADM_CMD_DEVICE_CLOSE ");

  //De-register the PP callback info with ADM database.
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of ADM_CMD_DEVICE_CLOSE, de-registering PP clbk");
  if (ADSP_FAILED(result = Adm_DataBaseDeRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: De-registering PP clbk failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Remove this Device ID (COPP ID) from any existing session mapping masks
  Adm_RemoveCoppIDFromSessionMappingMask(pAdmStatSvc, unCoppID, phCalPort->unCoppDirection);

  uint16_t  unCoppDirection = phCalPort->unCoppDirection;

  pSessionDelayParam->unCoppBufDelay = 0;
  pSessionDelayParam->unCoppAlgDelay = 0;
  pSessionDelayParam->unAFEDelay_EP1 = 0;
  pSessionDelayParam->unAFEDelay_EP2 = 0;
  pSessionDelayParam->unAFEDelay_EP3 = 0;
  *pphCopp = NULL;
  *pphAfePort = NULL;

  if(RX_DIR == unCoppDirection)
  {
    // Detect primary device of all active streams and devices.
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of ADM_CMD_DEVICE_CLOSE, updating primary device/port");
    if (ADSP_FAILED(result = Adm_DetectAndUpdatePrimaryDevicePcm(pAdmStatSvc, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: updating primary device/port failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP/COPreP %d closed.", unCoppID);

  result = AudDevMgr_RequestHwResources(pAdmStatSvc);

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static  ADSPResult Adm_DeviceCloseCmdLPCMDeviceLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc, elite_apr_packet_t *pPkt,
                                                               qurt_elite_queue_t *pRspQ)
{
  int                 joinResult;
  uint16_t            unCoppID;
  elite_svc_handle_t  **pphCopp,    **pphAfePort;
  qurt_elite_thread_t coppThreadID;

  ADSPResult                   result              = ADSP_EOK;
  elite_apr_port_t             port                = elite_apr_if_get_dst_port(pPkt);
  AdmCalPort_Type              *phCalPort          = NULL;
  AdmDevSessionDelayParam_Type *pSessionDelayParam = NULL;

  unCoppID = ADM_GET_COPP_ID(port);

  phCalPort          = &pAdmStatSvc->deviceCalPort[unCoppID];
  pSessionDelayParam = &(pAdmStatSvc->pDevSessionDelayParam[unCoppID]);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing Device LB ADM_CMD_DEVICE_CLOSE_V5, COPP ID = %d", unCoppID);

  pphCopp = &(phCalPort->phDevCopp);
  pphAfePort = &(phCalPort->unEID1.phAfePort);

  {
    /**************************************************************************************/
    /* Sequence to close Device LB path device session:                                                  */
    /* i. Disable source AFE ports (stop it from sending samples to downstream COPP)            */
    /* ii. Disconnect COPP from Sink Port(AFE Rx) (stop it from sending samples to Sink Port)  */
    /* iii. Disconnect Sink port (AFE Rx)       */
    /* iv. Destroy COPP (also returns any held-up resources to upstream AFE port)       */
    /* v. Disconnect source AFE ports.                                                            */
    /**************************************************************************************/

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISABLE cmd (source near port AFE Tx) on EP1: %d", phCalPort->unEID1.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                      *pphAfePort,
                                                      ELITEMSG_CUSTOM_AFECLIENTDISABLE,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISABLE cmd (source near port AFE Tx) failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISABLE cmd (source far port AFE Rx) on EP2: %d", phCalPort->unEID2.unAfePortID);

      if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                        phCalPort->unEID2.phAfePort,
                                                        ELITEMSG_CUSTOM_AFECLIENTDISABLE,
                                                        pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISABLE cmd (source far poer AFE Rx) failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
    }
    if (ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)
    {
      //Send ELITE_CMD_DISCONNECT to audio COPP.
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing COPP_DISCONNECT cmd");

      if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                              phCalPort->unEID3.phAfePort, ELITE_CMD_DISCONNECT)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: COPP_DISCONNECT cmd failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
    }
    else
    {
      //Send ELITE_CMD_STOP_SERVICE to VPTx COPP.
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing VPTx_STOP cmd");
      if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                              phCalPort->unEID3.phAfePort, ELITE_CMD_STOP_SERVICE)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: VPTx_STOP cmd failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
    }

    //Now, disconnect Sink port (AFE Rx port)
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISCONNECT cmd sink port (AFE Rx) on EP3: %d", phCalPort->unEID3.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID3.unAfePortID,
                                                      phCalPort->unEID3.phAfePort,
                                                      ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: AFE_PORT_DISCONNECT cmd (AFE Rx Sink port) failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    //Store the COPP's thread ID before destroying it, so it can be used later for joining.
    coppThreadID = (*pphCopp)->threadId;
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing COPP_DESTROY cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                            NULL, ELITE_CMD_DESTROY_SERVICE)))
    {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM device LB: COPP_DESTROY cmd failed");
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISCONNECT cmd (AFE Tx) on EP1: %d", phCalPort->unEID1.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                      *pphAfePort, ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: AFE_PORT_DISCONNECT cmd (AFE Tx) failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_CLOSE, issuing AFE_PORT_DISCONNECT cmd (AFE Rx) on EP2: %d", phCalPort->unEID2.unAfePortID);

      if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                        phCalPort->unEID2.phAfePort, ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                        pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: AFE_PORT_DISCONNECT cmd (AFE Rx) failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }

    }
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "All cmds to stop Device LB in ADM_CMD_DEVICE_CLOSE have been issued");
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM device LB: As part of ADM_CMD_DEVICE_CLOSE Waiting for COPP to join");

  qurt_elite_thread_join(coppThreadID, &joinResult);
  if (ADSP_FAILED(joinResult))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: COPP thread join failed, result = %d", joinResult);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, joinResult);
    return joinResult;
  }
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM device LB: COPP thread joined in Device in ADM_CMD_DEVICE_CLOSE ");

  //De-register the PP callback info with ADM database.
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of device LB ADM_CMD_DEVICE_CLOSE, de-registering PP clbk");

  if (ADSP_FAILED(result = Adm_DataBaseDeRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: De-registering PP clbk failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  pSessionDelayParam->unCoppBufDelay = 0;
  pSessionDelayParam->unCoppAlgDelay = 0;
  pSessionDelayParam->unAFEDelay_EP1 = 0;
  pSessionDelayParam->unAFEDelay_EP2 = 0;
  pSessionDelayParam->unAFEDelay_EP3 = 0;
  *pphCopp = NULL;
  *pphAfePort = NULL;

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Device LB COPP %d closed.", unCoppID);

  result = AudDevMgr_RequestHwResources(pAdmStatSvc);

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_AprMtMxMapRoutingsHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt, adm_client_type_t eClient)
{
  AdmStatSvc_InfoType                *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_matrix_map_routings_v5_t      *pRoutingPayload;
  adm_session_map_node_v5_t             *pSessionMapNode;
  ADSPResult result = ADSP_EOK;
  uint16_t                           *pSnIDToPortIDMap, *pSnIDToPrCOPPIDMap, unCoppID;
  AdmCalPort_Type                    *phCalPort;
  elite_svc_handle_t                 *hMatrix;
  uint32_t                           i, j, unSessionSampleRate, unCOPPsAttached2OtherSessions;
  bool_t bReCheckReCfgOfConnIpPorts = FALSE;
  uint16_t unCoppIDRecfg = 0, unIndex = ADM_INVALID_INDEX;
  uint32_t unTargetSampleRate = 0;
  uint32_t matrix_id; //Specifies whether the matrix ID is Audio Rx (0) or Audio Tx (1)

  pRoutingPayload = (adm_cmd_matrix_map_routings_v5_t*)elite_apr_if_get_payload_ptr(pPkt);

  if((ADM_LPCM_AUDIO_OUT == pRoutingPayload->matrix_id) ||
      (ADM_MATRIX_ID_AUDIO_RX == pRoutingPayload->matrix_id))
  {
    matrix_id = ADM_MATRIX_ID_AUDIO_RX;
  }
  else if( (ADM_LPCM_AUDIO_IN == pRoutingPayload->matrix_id) ||
      (ADM_MATRIX_ID_AUDIO_TX == pRoutingPayload->matrix_id) ||
      (ADM_LSM_IN == pRoutingPayload->matrix_id) )
  {
    matrix_id = ADM_MATRIX_ID_AUDIO_TX;
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Error:Rcvd invalid Matrix ID:[%lu] in ADM_CMD_MATRIX_MAP_ROUTINGS_V5", pRoutingPayload->matrix_id);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
    return ADSP_EBADPARAM;
  }

  //Audio Matrix understands only port ID's, so ADM must translate session ID's and COPP ID's into port ID's.
  adm_session_map_node_v5_t *pTmp2 = (adm_session_map_node_v5_t*)(pRoutingPayload+1);

  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_MATRIX_MAP_ROUTINGS_V5, matrix ID = %lu, num sessions = %lu for client type [%d]",
        pRoutingPayload->matrix_id, pRoutingPayload->num_sessions, eClient);

  if (ADM_MATRIX_ID_AUDIO_RX == matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToRxMtMxInPortIDMap[0]);
  }
  else
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToTxMtMxOutPortIDMap[0]);
  }


  for (i = 0; i < pRoutingPayload->num_sessions; i++)
  {
    pSessionMapNode =  pTmp2;
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: SessionID = 0x%hX, num copps = %d", pSessionMapNode->session_id, pSessionMapNode->num_copps);

    //Extract the session and stream ID from the incoming ID and validate them.
    uint16_t extractedSessionID = 0, extractedStreamID = 0;
    extractedSessionID = (0xff00 & pSessionMapNode->session_id) >> 8;
    extractedStreamID  = (0x00ff & pSessionMapNode->session_id);

    if (eASM_TYPE == eClient)
    {
      if(
          (0 == pSessionMapNode->session_id) ||
          ((pSessionMapNode->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
              ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                  (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
      )
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: MapRoutings Rcvd invalid SessionID [0x%hX] for client [%d]", pSessionMapNode->session_id, eClient);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
        return ADSP_EBADPARAM;
      }
    }

    if (eLSM_TYPE == eClient)
    {
      if (0 == pSessionMapNode->session_id || LSM_MAX_NUM_SESSIONS < pSessionMapNode->session_id)
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: MapRoutings Rcvd invalid SessionID [0x%x] for client [%d]", pSessionMapNode->session_id, eClient);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
        return ADSP_EBADPARAM;
      }
    }

    //Map the incoming  SSID to Index
    unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)matrix_id, pSessionMapNode->session_id, eClient);
    if(ADM_INVALID_INDEX == unIndex)
    {
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
      return ADSP_EBADPARAM;
    }

    //Get hold of pSessionInfo AND if incoming SSID is legacy, map it to contemporary SSID
    AdmStreamSessionInfo_Type *pSessionInfo;
    if (ADM_MATRIX_ID_AUDIO_RX == matrix_id)
    {
      pSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
      pSessionMapNode->session_id = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
    }
    else
    {
      pSessionInfo = &(pAdmStatSvc->txStreamSessionInfo[unIndex]);
      pSessionMapNode->session_id = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
    }

    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Contemporary SessionID = 0x%hX, num copps = %d",
          pSessionMapNode->session_id, pSessionMapNode->num_copps);

    // Special handling for ULL, LLNP, ULLPP modes.
    if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pSessionInfo->stream_perf_mode)
        || (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode))
    {
      if (eLSM_TYPE == eClient)
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid ULL/ULLPP stream session:[0x%x] for client type [%d]",
              pSessionMapNode->session_id, result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
        return ADSP_EBADPARAM;
      }
      result = Adm_DirectMapRoutingsHandler(pAdmStatSvc,
                                            pSessionMapNode,
                                            matrix_id, eClient,
                                            pAdmStatSvc->admInlineRspQ);
      if (ADSP_FAILED(result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Routing of ULL/ULLPP stream session:[0x%hX] to device failed, result = %d",
              pSessionMapNode->session_id, result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }

      // Matrix will use this session_id value to skip mapping of this session.
      pSessionMapNode->session_id = MT_MX_ULL_SESSION;
      if (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode)
      {
        pSessionMapNode->session_id = MT_MX_ULLPP_SESSION;
      }

      /* Update session mapping node pointer. An ULLPP stream session will be connected to single
          ULLPP device session (one COPP).
          if number of COPP's is odd, there's a reserved field after the last valid COPP ID*/
      pTmp2 = (adm_session_map_node_v5_t*)( (uint16_t*)(pTmp2+1) + 2);
    }
    else if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode)
    {
      if (eLSM_TYPE == eClient)
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid LLNP stream session:[0x%x] for client type [%d]",
              pSessionMapNode->session_id, eClient);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
        return ADSP_EBADPARAM;
      }
      result = Adm_LlnpMtMxMapRoutingsHandler(pAdmStatSvc,
                                              pSessionMapNode,
                                              matrix_id, eClient,
                                              pAdmStatSvc->admInlineRspQ);
      if (ADSP_FAILED(result))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Routing of LLNP stream session:[0x%hX] to device failed, result = %d",
              pSessionMapNode->session_id, result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }
      // Matrix will use this session_id value to skip mapping of this session.
      pSessionMapNode->session_id = MT_MX_LLNP_SESSION;

      /* Update session mapping node pointer. An LLNP stream sesion will be connected to single
          LLNP device session (one COPP).
          if number of COPP's is odd, there's a reserved field after the last valid COPP ID*/
      pTmp2 = (adm_session_map_node_v5_t*)( (uint16_t*)(pTmp2+1) + 2);
    }
    else
    {
      //Reset session mapping mask.
      Adm_ResetSessionMappingMask(pAdmStatSvc, pSessionMapNode->session_id, matrix_id, eClient);

      uint16_t *pCoppID = (uint16_t*) (pTmp2 + 1);
      uint16_t unBackupSessionID = pSessionMapNode->session_id;
      if (ADM_MATRIX_ID_AUDIO_RX == matrix_id)
      {
        //Session -> Primary COPP Mapping table database
        pSnIDToPrCOPPIDMap = &(pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[0]);

        pSessionMapNode->session_id = pSnIDToPortIDMap[unIndex];
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Session ID translated to MXAR i/p port ID = %d", pSessionMapNode->session_id);

        //Derive session sampling rate from copp sample rate
        //1. Initialize session sampling rate to zero.
        unSessionSampleRate = 0;
        unCOPPsAttached2OtherSessions = 0;

        for (j = 0; j < pSessionMapNode->num_copps; j++)
        {
          unCoppID = *pCoppID;

          //2. If COPP ID is invalid, error out.
          if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,unCoppID,ADM_INVALID_DIRECTION)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID [%d]", unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

          //At this point, assumption is that this is a valid COPP ID. Check for the ADM device loopback COPP.
          if (phCalPort->bIsCoppInDeviceLoopBackTopology)
          {
            result  = ADSP_EBADPARAM;
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid COPP ID [%d]", unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          //At this point, assumption is that this is a valid COPP ID. Check the direction. Do not check for ADM loopback COPP.
          if (phCalPort->unCoppDirection != matrix_id && FALSE == phCalPort->bIsCoppInLoopBackTopology)
          {
            result  = ADSP_EBADPARAM;
            MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid direction for COPP ID [%d], COPP Dir=%d, MtMx Dir=%lu", unCoppID, phCalPort->unCoppDirection, matrix_id);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          //check COPP performance mode
          if ((ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
              || (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == phCalPort->unDevicePerfMode)
              || (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == phCalPort->unDevicePerfMode))
          {
            result  = ADSP_EBADPARAM;
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid map command to map non-ULL/ULLPP/LLNP session [0x%hX] to ULL/ULLPP/LLNP COPP ID [%d]",
                  unBackupSessionID, unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          //3. check if this COPP is already mapped to another session */
          if (0 != phCalPort->unNumConnectedSessionsRx)
          {
            //4. Check if session is trying to map two MtMx o/p ports running at two different sampling rates that are already attached to another session.
            if ((unSessionSampleRate != phCalPort->unMtMxSampleRate) && (0 != unCOPPsAttached2OtherSessions))
            {
              MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd unsuported routing mode Session ID [0x%hX] COPP ID [%d]",
                    unBackupSessionID, unCoppID);
              elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
              return result;
            }
            unCOPPsAttached2OtherSessions = unCOPPsAttached2OtherSessions + 1;
            // Force the session sampling rate to already connected MtMx o/p port sampling rate.
            unSessionSampleRate = phCalPort->unMtMxSampleRate;
          }

          //5. Update session sampling rate if MtMx o/p port sampling rate is higher.
          if (unSessionSampleRate < phCalPort->unMtMxSampleRate)
          {
            unSessionSampleRate = phCalPort->unMtMxSampleRate;
          }
          pCoppID++;
        }

        //6. Reconfigure POPP output sampling rate if sessions sampling rate is not 48KHz.
        pCoppID = (uint16_t*) (pTmp2 + 1);
        unCoppID = *pCoppID;
        phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
        pSessionInfo = &gpAdmStatSvc->rxStreamSessionInfo[unIndex];
        if (pSessionInfo->unSessionSampleRate != unSessionSampleRate)
        {
          //7. Move audio matrix input port state to READY
          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On Session ID 0x%hX, moving the audio matrix i/p %d to READY state, expected fs: %lu",unBackupSessionID, pSessionMapNode->session_id, unSessionSampleRate);
          if (ADSP_FAILED(result = Adm_SendCmdMtMxPortStateChange(pAdmStatSvc,
                                                                  pSessionMapNode->session_id,
                                                                  MATRIX_MIXER_PORT_DIR_INPUT,
                                                                  pAdmStatSvc->hRxMatrix, unSessionSampleRate)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ELITEMSG_CUSTOM_MT_MX_PORT_STATE_CHANGE cmd failed, result = %d", result);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
            return result;
          }

          //8. Send message to ASM with sampling rate information
          MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On Session ID 0x%hX, setting session sampling rate: %lu via ASM",   unBackupSessionID, unSessionSampleRate);
          if (ADSP_FAILED(result = Adm_SendCmdAsmSetOutputSamplingRate(pAdmStatSvc,
                                                                       unSessionSampleRate,
                                                                       unBackupSessionID)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ELITEMSG_CUSTOM_ASM_CFG_PP_OUTPUT_SAMPLE_RATE cmd failed, result = %d", result);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
            return result;
          }
          //update connected session sampling rate.
          pSessionInfo->unSessionSampleRate = unSessionSampleRate;
        }

        pCoppID = (uint16_t*) (pTmp2 + 1);
        for (j = 0; j < pSessionMapNode->num_copps; j++)
        {
          unCoppID = *pCoppID;

          //If COPP ID is invalid, error out.
          if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,unCoppID,ADM_INVALID_DIRECTION)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID [%d]", unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }
          phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

          //At this point, assumption is that this is a valid COPP ID. Check the direction. Do not check for ADM loopback COPP.
          if (phCalPort->unCoppDirection != matrix_id && FALSE == phCalPort->bIsCoppInLoopBackTopology)
          {
            result  = ADSP_EBADPARAM;
            MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid direction for COPP ID [%d], COPP Dir=%d, MtMx Dir=%lu", unCoppID, phCalPort->unCoppDirection, matrix_id);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          //If session sampling rate is different compared to MtMx o/p port sampling rate, reconfigure output port sampling rate to session sampling rate.
          if (unSessionSampleRate != phCalPort->unMtMxSampleRate)
          {
            //Reconfigure output port sampling rate
            uint32_t unOutPortID = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;
            MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On COPP ID %d, setting COPP sampling rate: %lu via MtMx o/p port %lu",
                  unCoppID, unSessionSampleRate, unOutPortID);
            if (ADSP_FAILED(result = Adm_SendCmdReconfigMtMxOutPortSampleRate(pAdmStatSvc,
                                                                              unOutPortID,
                                                                              pAdmStatSvc->hRxMatrix,
                                                                              unSessionSampleRate)))
            {
              MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RECONFIGURE_OUTPUT cmd failed, result = %d", result);
              elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
              return result;
            }

            /*Update MtMx o/p port sample rate with new rate*/
            phCalPort->unMtMxSampleRate = unSessionSampleRate;

            //Later on, we need to check if changing this sampling rate on this o/p port (COPP) resulted in any other i/p ports to be reconfigured (via ASM)
            bReCheckReCfgOfConnIpPorts = TRUE;
            unCoppIDRecfg = unCoppID;
            unTargetSampleRate = unSessionSampleRate;
          }

          //Update session mapping mask
          Adm_UpdateSessionMappingMask(pAdmStatSvc, unBackupSessionID, unCoppID, matrix_id, eClient);

          *pCoppID++ = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;
          MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP ID %d translating to o/p port ID = %lu",
                unCoppID, (phCalPort->mtMxPort).phMtMxOutPort->outPortID);

          if (TRUE == bReCheckReCfgOfConnIpPorts)
          {
            result = Adm_ReCheckReCfgOfConnIpPorts(pAdmStatSvc, unCoppIDRecfg, unTargetSampleRate);

            bReCheckReCfgOfConnIpPorts = FALSE;
            unCoppIDRecfg = 0;
            unTargetSampleRate = 0;

            if (ADSP_FAILED(result))
            {
              elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
              return result;
            }
          }
        }
      }
      else
      {
        /* TX path */
        //Session -> Primary COPP Mapping table database
        pSnIDToPrCOPPIDMap = &(pAdmStatSvc->txSessionIDToPrimCOPPIDMap[0]);

        pSessionMapNode->session_id = pSnIDToPortIDMap[unIndex];
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Session ID translated to o/p port ID = %d", pSessionMapNode->session_id);

        /*derive session sampling rate from copp sample rate*/
        /*1. Initialize session sampling rate to zero*/
        unSessionSampleRate = 0;
        unCOPPsAttached2OtherSessions = 0;

        for (j = 0; j < pSessionMapNode->num_copps; j++)
        {
          unCoppID = *pCoppID;

          //2. if COPP ID is invalid, error out.
          if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,unCoppID,ADM_INVALID_DIRECTION)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID [%d]", unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

          //At this point, assumption is that this is a valid COPP ID. Check for the ADM device loopback COPP.
          if (phCalPort->bIsCoppInDeviceLoopBackTopology)
          {
            result  = ADSP_EBADPARAM;
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid COPP ID [%d]", unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          //At this point, assumption is that this is a valid COPP ID. Check the direction. Do not check for ADM loopback COPP.
          if (phCalPort->unCoppDirection != matrix_id && FALSE == phCalPort->bIsCoppInLoopBackTopology)
          {
            result  = ADSP_EBADPARAM;
            MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid direction for COPP ID [%d], COPP Dir=%d, MtMx Dir=%lu", unCoppID, phCalPort->unCoppDirection, matrix_id);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          // Check COPP performance mode
          if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == phCalPort->unDevicePerfMode)
          {
            result  = ADSP_EBADPARAM;
            MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid map command to map non LLNP session [0x%hX] to LLNP COPP ID [%d]",
                  unBackupSessionID, unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          //3. check if this COPP is already mapped to another session.
          if (0 != phCalPort->unNumConnectedSessionsTx)
          {
            //4. Check if session is trying to map two MtMx i/p ports running at two different sampling rates that are already attached to another session.
            if ((unSessionSampleRate != phCalPort->unMtMxSampleRate) && (0 != unCOPPsAttached2OtherSessions))
            {
              MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd unsuported routing mode Session ID [0x%hX] COPP ID [%d]",
                    unBackupSessionID, unCoppID);
              elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
              return result;
            }
            unCOPPsAttached2OtherSessions = unCOPPsAttached2OtherSessions + 1;
            // Force the session sampling rate to already connected MtMx i/p port sampling rate.
            unSessionSampleRate = phCalPort->unMtMxSampleRate;
          }

          //5. update session sampling rate if MtMx i/p port sampling rate is higher.
          //do not select fractional rate as session rate.
          if ( (unSessionSampleRate < phCalPort->unMtMxSampleRate))
          {
            unSessionSampleRate = phCalPort->unMtMxSampleRate;
          }

          /*6. Check if this copp topology is VpTx Topology. Force session sample rate to 48kHz*/
          if(ADM_COPP_TYPE_VPTX == phCalPort->unCoppType)
          {
            unSessionSampleRate = ADM_SAMPLING_RATE_48K;
            break;
          }
          pCoppID++;
        }
        // if this is SSSD scenario with fractional rate device, select fractional rate as session sampling rate.
        if ((unSessionSampleRate == 0) && (1 == pSessionMapNode->num_copps))
        {
          uint16_t *pCoppID = (uint16_t*) (pTmp2 + 1);
          unCoppID = *pCoppID;
          phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
          unSessionSampleRate = phCalPort->unMtMxSampleRate;
        }
        else if ((unSessionSampleRate == 0) && (1 < pSessionMapNode->num_copps))
        {
          // if there are multiple fractional rate devices, select 48kHz rate as session sampling rate.
          unSessionSampleRate = ADM_SAMPLING_RATE_48K;
        }

        /*7. Reconfigure matrix mixer output port sampling rate*/
        pSessionInfo = &gpAdmStatSvc->txStreamSessionInfo[unIndex];
        if (pSessionInfo->unSessionSampleRate != unSessionSampleRate)
        {
          //reconfigure output port sampling rate
          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On Session ID 0x%hX, setting Session sampling rate: %lu via MtMx o/p port %d",
                unBackupSessionID, unSessionSampleRate, pSessionMapNode->session_id);
          if (ADSP_FAILED(result = Adm_SendCmdReconfigMtMxOutPortSampleRate(pAdmStatSvc,
                                                                            pSessionMapNode->session_id,
                                                                            pAdmStatSvc->hTxMatrix,
                                                                            unSessionSampleRate)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RECONFIGURE_OUTPUT cmd failed, result = %d", result);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
            return result;
          }
          //update connected session sampling rate.
          pSessionInfo->unSessionSampleRate = unSessionSampleRate;
        }

        pCoppID = (uint16_t*) (pTmp2 + 1);

        for (j = 0; j < pSessionMapNode->num_copps; j++)
        {
          unCoppID = *pCoppID;

          //If COPP ID is invalid, error out.
          if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,unCoppID,ADM_INVALID_DIRECTION)))
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID [%d]", unCoppID);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }
          phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

          //At this point, assumption is that this is a valid COPP ID. Check the direction. Do not check for ADM loopback COPP.
          if (phCalPort->unCoppDirection != matrix_id && FALSE == phCalPort->bIsCoppInLoopBackTopology)
          {
            result  = ADSP_EBADPARAM;
            MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid direction for COPP ID [%d], COPP Dir=%d, MtMx Dir=%lu", unCoppID, phCalPort->unCoppDirection, matrix_id);
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
            return result;
          }

          /* if MtMx i/p port sampling rate is not equal to session sampling rate reconfigure COPreP output rate*/
          /* with required sample rate. Not required for VpTx as they always output at 48kHz    */
          if ( (phCalPort->unMtMxSampleRate != unSessionSampleRate) &&
              (ADM_COPP_TYPE_VPTX != phCalPort->unCoppType) )
          {
            //Reconfigure output port sampling rate.
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On COPP ID %d, setting COPreP sampling rate: %lu directly",
                  unCoppID, unSessionSampleRate);
            if (ADSP_FAILED(result = Adm_SendCmdCoppSetOutputSamplingRate(phCalPort->phDevCopp,
                                                                          pAdmStatSvc->admInlineRspQ,
                                                                          unSessionSampleRate)))
            {
              MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RECONFIGURE COPP output sample rate cmd failed, result = %d", result);
              elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
              return result;
            }
            //Update MtMx i/p port sample rate with new rate.
            phCalPort->unMtMxSampleRate = unSessionSampleRate;
          }

          // If COPP Type is VpTx, COPP always give data at 48kHZ sample rate
          if (ADM_COPP_TYPE_VPTX == phCalPort->unCoppType)
          {
            phCalPort->unMtMxSampleRate = unSessionSampleRate;
          }

          //Update session mapping mask
          Adm_UpdateSessionMappingMask(pAdmStatSvc, unBackupSessionID, unCoppID, matrix_id, eClient);

          //For loopback mode COPP, use the TX matrix handle (2nd matrix), for regular COPP, use the TX matrix handle (1st matrix)
          if(FALSE == phCalPort->bIsCoppInLoopBackTopology)
          {
            *pCoppID++ = (phCalPort->mtMxPort).phMtMxInPort->inPortID;
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: copp id %d translating to i/p port id = %lu",
                  unCoppID, (phCalPort->mtMxPort).phMtMxInPort->inPortID);
          }
          else
          {
            *pCoppID++ = (phCalPort->mtMxPort2).phMtMxInPort->inPortID;
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: copp id %d translating to i/p port id = %lu",
                  unCoppID, (phCalPort->mtMxPort2).phMtMxInPort->inPortID);
          }

          //Update the Session -> Prinary COPP table mapping.
          if (0 == j)
          {
            pSnIDToPrCOPPIDMap[unIndex] = unCoppID;
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: TX Session ID [0x%hX] --> Primary COPreP ID [%d]", unBackupSessionID, unCoppID);
          }
        }
      }
      //If number of COPP's is odd, there's a reserved field after the last valid COPP ID.
      if (0 != (pSessionMapNode->num_copps % 2)) pCoppID++;

      pTmp2 = (adm_session_map_node_v5_t*) pCoppID; //The next Session Map Node will begin from here.
    }
  }

  if (ADM_MATRIX_ID_AUDIO_TX == matrix_id)
  {
    hMatrix = pAdmStatSvc->hTxMatrix;
  }
  else
  {
    hMatrix =  pAdmStatSvc->hRxMatrix;
  }

  //Send matrix map routing command to the audio matrix.
  if (ADSP_FAILED(result = Adm_SendCmdMapMtMxRoutings(pAdmStatSvc, pPkt, hMatrix)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_MATRIX_MAP_ROUTINGS_V5 cmd failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  if (ADM_MATRIX_ID_AUDIO_RX == matrix_id)
  {
    // Detect primary device of all active streams and devices.
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_MATRIX_MAP_ROUTINGS_V5, updating primary device/port");
    if (ADSP_FAILED(result = Adm_DetectAndUpdatePrimaryDevicePcm(pAdmStatSvc, pAdmStatSvc->admInlineRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: updating primary device/port failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_MATRIX_MAP_ROUTINGS_V5 completed with success, result = %d", result);

  return result;
}

static ADSPResult Adm_SetParams(void *pAudStatAdmSvc, void *pParams, elite_svc_handle_t *pCoppHandle,
                                uint32_t unCoppID, uint32_t opCode, DeviceCmdProcInfo_t *pDevCmd)
{
  ADSPResult result = ADSP_EOK;
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  int32_t *pSetParamsCmdBase = NULL;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Processing ADM_CMD_SET_PP_PARAMS_V5/V6.");

  if (NULL == pAudStatAdmSvc)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS cmd received null ptr, pAdmStatSvc!");
    return ADSP_EBADPARAM;
  }

  if (NULL == pParams)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS cmd received NULL params ptr!");
    return ADSP_EBADPARAM;
  }

  if (NULL == pCoppHandle)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS cmd received NULL COPP handle ptr!");
    return ADSP_EBADPARAM;
  }

  uint32_t memMapHandle, addrLsw, addrMsw, dataPyaloadSize, headerSize, calVersion;
  if (opCode == ADM_CMD_SET_PP_PARAMS_V5)
  {
    adm_cmd_set_pp_params_v5_t *paramHeader = (adm_cmd_set_pp_params_v5_t*)pParams;
    memMapHandle    = paramHeader->mem_map_handle;
    addrLsw         = paramHeader->data_payload_addr_lsw;
    addrMsw         = paramHeader->data_payload_addr_msw;
    dataPyaloadSize = paramHeader->data_payload_size;
    headerSize      = sizeof(adm_cmd_set_pp_params_v5_t);
    calVersion      = ELITEMSG_PARAM_ID_CAL;
  }
  else //ADM_CMD_SET_PP_PARAMS_V6
  {
    adm_cmd_set_pp_params_v6_t *paramHeader = (adm_cmd_set_pp_params_v6_t*)pParams;
    memMapHandle    = paramHeader->mem_map_handle;
    addrLsw         = paramHeader->data_payload_addr_lsw;
    addrMsw         = paramHeader->data_payload_addr_msw;
    dataPyaloadSize = paramHeader->data_payload_size;
    headerSize      = sizeof(adm_cmd_set_pp_params_v6_t);
    calVersion      = ELITEMSG_PARAM_ID_CAL_V2;
  }

  elite_mem_shared_memory_map_t *sMemNode =
      (elite_mem_shared_memory_map_t *)qurt_elite_memory_malloc(sizeof(elite_mem_shared_memory_map_t), QURT_ELITE_HEAP_DEFAULT);

  if(NULL == sMemNode)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to allocate memory for shm node during SetPPParam");
    return ADSP_EFAILED;
  }

  if (0 == memMapHandle)
  {
    //In-band case: Param data starts just past the last entry of the incoming payload's header
    pSetParamsCmdBase = (int32_t*)((int8_t*)pParams + headerSize);
    memset(sMemNode, 0 , sizeof(elite_mem_shared_memory_map_t));
  }
  else
  {
    //Out-band case : Ensure cache alignment of incoming physical address
    if (addrLsw & CACHE_ALIGNMENT_MASK)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band SetPPParam Incoming addr LSW is not aligned to cache line");
      result = ADSP_EBADPARAM;
      qurt_elite_memory_free(sMemNode);
      return result;
    }

    //Phy->Virt
    sMemNode->unMemMapHandle = memMapHandle;
    sMemNode->unMemMapClient = admMemoryMapClient;
    sMemNode->unPhysAddrLsw  = addrLsw;
    sMemNode->unPhysAddrMsw  = addrMsw;
    sMemNode->unMemSize      = dataPyaloadSize;

    result =  elite_mem_map_get_shm_attrib(sMemNode->unPhysAddrLsw, sMemNode->unPhysAddrMsw, sMemNode->unMemSize, sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band SetPPParam failed Phy->Virt");
      qurt_elite_memory_free(sMemNode);
      return result;
    }

    //Invalidate the cache
    result = elite_mem_invalidate_cache(sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band SetPPParam failed to invalidate cache");
      qurt_elite_memory_free(sMemNode);
      return result;
    }

    pSetParamsCmdBase = (int32_t*)(sMemNode->unVirtAddr);
  }

  pDevCmd->token = Adm_GenerateToken(eDEVICE,unCoppID);

  if (ADSP_FAILED(result= Adm_SendCmdCoppSetParams(pCoppHandle, pAdmStatSvc->admRspQ,
                                                   ELITE_CMD_SET_PARAM, pDevCmd->token,
                                                   pSetParamsCmdBase, dataPyaloadSize,
                                                   calVersion,sMemNode,FALSE)))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS_V5 cmd on COPP [%lu] failed, result = %d", unCoppID, result);
    qurt_elite_memory_free(sMemNode);
    return result;
  }

  pDevCmd->unRespsNeeded++;
  qurt_elite_memory_free(sMemNode);

  return result;
}

static ADSPResult Adm_AprSetParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  void *pIncomingAPRPayload;
  elite_apr_port_t port;

  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;

  uint32_t            unCoppID     = UINT32_MAX;
  ADSPResult          result       = ADSP_EOK;
  AdmCalPort_Type     *phCalPort   = NULL;
  elite_svc_handle_t  *pCoppHandle = NULL;
  DeviceCmdProcInfo_t *pDevCmd = NULL;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_SET_PP_PARAMS_V5/V6");

  if (NULL == pPkt)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS cmd received NULL apr pkt!");
    result = ADSP_EBADPARAM;
    goto __bailoutSetParamsCmdHandler;
  }

  port = elite_apr_if_get_dst_port(pPkt);

  // Extract the payload from the incoming APR Packet
  pIncomingAPRPayload = (void*)elite_apr_if_get_payload_ptr(pPkt);
  unCoppID = ADM_GET_COPP_ID(port);

  // Check the payload
  if ((unCoppID >= ADM_COMPRESSED_MIN_RX) && (unCoppID <= ADM_COMPRESSED_MAX_RX))
  {
    ComprCoppInfo_t *pComprCoppInfo;

    pComprCoppInfo = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[unCoppID - ADM_COMPRESSED_MIN_RX]);

    if (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE == pComprCoppInfo->unCoppTopologyID)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "ADM: ADM_CMD_SET_PP_PARAMS cmd on Compressed COPP %lu failed. Not supported in NONE topology",
            unCoppID);
      result = ADSP_EUNSUPPORTED;
      goto __bailoutSetParamsCmdHandler;
    }

    pCoppHandle = pComprCoppInfo->phDevCopp;
    pDevCmd = &pComprCoppInfo->devCmd;
  }
  else
  {
    // Check the validity of the COPP ID
    if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc, unCoppID, ADM_INVALID_DIRECTION)))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID %lu result = %d", unCoppID, result);
      goto __bailoutSetParamsCmdHandler;
    }

    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

    if ((ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
        || (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS cmd is not supported on LLNP/ULL COPP %lu. cmd failed", unCoppID);
      result = ADSP_EUNSUPPORTED;
      goto __bailoutSetParamsCmdHandler;
    }

    pCoppHandle = phCalPort->phDevCopp;
    pDevCmd = &phCalPort->devCmd;
  }

  // Issue the set param for the specified COPP
  result = Adm_SetParams(pAudStatAdmSvc, pIncomingAPRPayload, pCoppHandle, unCoppID, pPkt->opcode, pDevCmd);
  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS_V5 send failed with result = %d", result);
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
    goto __bailoutSetParamsCmdHandler;
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_SET_PP_PARAMS_V5 sent with success, result = %d", result);
    return result;
  }

  __bailoutSetParamsCmdHandler:
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  if(pDevCmd)
  {
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
  }

  return result;
}

static ADSPResult Adm_AprGetPPParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  uint32_t            unCoppID, unPayloadSize;
  AdmCalPort_Type     *phCalPort;
  elite_svc_handle_t  *pCoppHandle;
  elite_msg_any_t     msg;
  ComprCoppInfo_t     *pComprCoppInfo;


  int                      result               = ADSP_EOK;
  void                     *pIncomingAPRPayload = NULL;
  AdmStatSvc_InfoType      *pAdmStatSvc         = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  elite_apr_port_t         port                 = elite_apr_if_get_dst_port(pPkt);
  elite_msg_param_cal_v2_t *pGetParamMsgPayload = NULL;
  DeviceCmdProcInfo_t      *pDevCmd             = NULL;


  pIncomingAPRPayload = (void*)elite_apr_if_get_payload_ptr(pPkt);
  unCoppID            = ADM_GET_COPP_ID(port);

  // check if set param is called for compressed COPP
  if ((unCoppID >= ADM_COMPRESSED_MIN_RX) && (unCoppID <= ADM_COMPRESSED_MAX_RX))
  {
    pComprCoppInfo = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[unCoppID-ADM_COMPRESSED_MIN_RX]);

    if (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE == pComprCoppInfo->unCoppTopologyID)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "ADM: ADM_CMD_SET_PP_PARAMS cmd on Compressed COPP %lu failed. Not supported in NONE topology",
            unCoppID);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    pCoppHandle = pComprCoppInfo->phDevCopp;
    pDevCmd     = &pComprCoppInfo->devCmd;
  }
  else
  {
    // Check the validity of the COPP ID
    if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc, unCoppID, ADM_INVALID_DIRECTION)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID %lu", unCoppID);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    phCalPort   = &pAdmStatSvc->deviceCalPort[unCoppID];
    pCoppHandle = phCalPort->phDevCopp;

    if ((ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
        || (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_GET_PP_PARAMS cmd is not supported on LLNP/ULL COPP %lu. cmd failed", unCoppID);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
      return ADSP_EUNSUPPORTED;
    }
    pDevCmd = &phCalPort->devCmd;
  }

  //Create an FADD msg - common to both in-band and out-of-band.
  unPayloadSize = sizeof(elite_msg_param_cal_v2_t);

  pDevCmd->token = Adm_GenerateToken(eDEVICE,unCoppID);

  if(ADSP_FAILED(result = elite_msg_create_msg( &msg, &unPayloadSize, ELITE_CMD_GET_PARAM,
                                                pAdmStatSvc->admRspQ, pDevCmd->token, 0)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to create FADD msg for GET_PP_PARAM cmd, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
    return result;
  }

  pGetParamMsgPayload = (elite_msg_param_cal_v2_t*)msg.pPayload;

  uint32_t memMapHandle, addrLsw, addrMsw, paramMaxSize, respheaderSize, respCmd;
  if (pPkt->opcode == ADM_CMD_GET_PP_PARAMS_V5)
  {
    adm_cmd_get_pp_params_v5_t *paramHeader = (adm_cmd_get_pp_params_v5_t*)pIncomingAPRPayload;
    memMapHandle                   = paramHeader->mem_map_handle;
    addrLsw                        = paramHeader->data_payload_addr_lsw;
    addrMsw                        = paramHeader->data_payload_addr_msw;
    paramMaxSize                   = paramHeader->param_max_size;
    respheaderSize                 = sizeof(adm_cmd_rsp_get_pp_params_v5_t);
    pGetParamMsgPayload->unParamId = ELITEMSG_PARAM_ID_CAL;
    respCmd                        = ADM_CMDRSP_GET_PP_PARAMS_V5;
  }
  else //ADM_CMD_GET_PP_PARAMS_V6
  {
    adm_cmd_get_pp_params_v6_t *paramHeader = (adm_cmd_get_pp_params_v6_t*)pIncomingAPRPayload;
    memMapHandle                   = paramHeader->mem_map_handle;
    addrLsw                        = paramHeader->data_payload_addr_lsw;
    addrMsw                        = paramHeader->data_payload_addr_msw;
    paramMaxSize                   = paramHeader->param_max_size;
    respheaderSize                 = sizeof(adm_cmd_rsp_get_pp_params_v6_t);
    pGetParamMsgPayload->unParamId = ELITEMSG_PARAM_ID_CAL_V2;
    respCmd                        = ADM_CMDRSP_GET_PP_PARAMS_V6;
  }

  if (0 == memMapHandle)
  {
    //In-Band...
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_GET_PP_PARAMS_V5/V6.. In-Band!");
    elite_apr_packet_t *pCmdRspAprPkt = NULL;

    //CmdRSP payload contains status, modID,  paramID, param size, reserved field and the actual param values.
    uint32_t unCmdRspPayloadSize = respheaderSize + paramMaxSize;

    //APR alloc memory for in-band CmdRSP and fill the header.
    result = elite_apr_if_alloc_cmd_rsp(pAdmStatSvc->admAprHandle,
                                        elite_apr_if_get_dst_addr( pPkt),
                                        elite_apr_if_get_dst_port( pPkt),
                                        elite_apr_if_get_src_addr( pPkt),
                                        elite_apr_if_get_src_port( pPkt),
                                        elite_apr_if_get_client_token( pPkt),
                                        respCmd,
                                        unCmdRspPayloadSize,
                                        &pCmdRspAprPkt );

    if (ADSP_FAILED(result) || (NULL == pCmdRspAprPkt) )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to allocate APR pkt for InBand GetPPParams cmdrsp, result = %d", result);
      //Release the FADD msg that was bound to COPP.
      elite_msg_release_msg(&msg);
      //Send failure notification to the client processor.
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      return result;
    }

    //Give COPP pointer to the CmdRSP APR pkt's payload (Offset by the status to access the module ID).
    int32_t* pCmdRspAprPktBase = (int32_t*)elite_apr_if_get_payload_ptr(pCmdRspAprPkt);

    pGetParamMsgPayload->pnParamData = (int32*)((int8_t*)pCmdRspAprPktBase + respheaderSize);
    pGetParamMsgPayload->unSize      = paramMaxSize;

    memset((void*)&pGetParamMsgPayload->bufferMemNode, 0, sizeof(elite_mem_shared_memory_map_t));

    //Fill up the memory with the ModuleID and ParamID so that PP doesnt have to do it
    if (pPkt->opcode == ADM_CMD_GET_PP_PARAMS_V5)
    {
      adm_param_data_v5_t        *psPPParamData = (adm_param_data_v5_t *)(pGetParamMsgPayload->pnParamData);
      adm_cmd_get_pp_params_v5_t *paramHeader   = (adm_cmd_get_pp_params_v5_t*)pIncomingAPRPayload;

      psPPParamData->module_id  = paramHeader->module_id;
      psPPParamData->param_id   = paramHeader->param_id;
      psPPParamData->param_size = paramHeader->param_max_size;
      psPPParamData->reserved   = 0;
    }
    else //ADM_CMD_GET_PP_PARAMS_V6
    {
      adm_param_data_v6_t        *psPPParamData = (adm_param_data_v6_t *)(pGetParamMsgPayload->pnParamData);
      adm_cmd_get_pp_params_v6_t *paramHeader   = (adm_cmd_get_pp_params_v6_t*)pIncomingAPRPayload;

      psPPParamData->module_id   = paramHeader->module_id;
      psPPParamData->instance_id = paramHeader->instance_id;
      psPPParamData->reserved    = 0;
      psPPParamData->param_id    = paramHeader->param_id;
      psPPParamData->param_size  = paramHeader->param_max_size;
    }

    //Send FADD msg to PP svc and wait for ACK.
    result = qurt_elite_queue_push_back(pCoppHandle->cmdQ, (uint64_t*)&msg);

    if (ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to send GetParam to COPP %lu", unCoppID);
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutInBandGetPPParams;
    }

    pDevCmd->unRespsNeeded++;
    pDevCmd->pAprRspPkt = pCmdRspAprPkt;
    return result;

    __bailoutInBandGetPPParams:

    //Update the status
    if (pPkt->opcode == ADM_CMD_GET_PP_PARAMS_V5)
    {
      adm_cmd_rsp_get_pp_params_v5_t *pcmdRespHeader = (adm_cmd_rsp_get_pp_params_v5_t *)(pCmdRspAprPktBase);
      pcmdRespHeader->status = result;
    }
    else //ADM_CMD_GET_PP_PARAMS_V6
    {
      adm_cmd_rsp_get_pp_params_v6_t *pcmdRespHeader = (adm_cmd_rsp_get_pp_params_v6_t *)(pCmdRspAprPktBase);
      pcmdRespHeader->status = result;
    }
    //Free up the incoming apr packet since we create another one for CmdRSP already.
    elite_apr_if_free( pAdmStatSvc->admAprHandle,  pPkt);
    //Send the CmdRSP back to client proc.
    result |= elite_apr_if_async_send( pAdmStatSvc->admAprHandle, pCmdRspAprPkt );
    //Release the FADD msg that was bound to COPP.
    elite_msg_release_msg(&msg);
  }
  else
  {
    //Out-of-band...
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_GET_PP_PARAMS_V5/V6.. Out-of-Band!");

    elite_mem_shared_memory_map_t *sMemNode =
        (elite_mem_shared_memory_map_t *)qurt_elite_memory_malloc(sizeof(elite_mem_shared_memory_map_t), QURT_ELITE_HEAP_DEFAULT);

    if(NULL == sMemNode)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPParam failed to alloc memnode");
      result = ADSP_ENOMEMORY;
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutOutBandGetPPParams;
    }

    memset(sMemNode, 0, sizeof(elite_mem_shared_memory_map_t));

    //Ensure cache alignment of incoming physical address
    if(addrLsw & CACHE_ALIGNMENT_MASK)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPParam Incoming addr LSW is not aligned to cache line");
      result  = ADSP_EBADPARAM;
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutOutBandGetPPParams;
    }

    //Phy->Virt
    sMemNode->unMemMapHandle = memMapHandle;
    sMemNode->unMemMapClient = admMemoryMapClient;
    sMemNode->unPhysAddrLsw  = addrLsw;
    sMemNode->unPhysAddrMsw  = addrMsw;
    sMemNode->unMemSize      = paramMaxSize;

    result =  elite_mem_map_get_shm_attrib(sMemNode->unPhysAddrLsw, sMemNode->unPhysAddrMsw,
                                           sMemNode->unMemSize, sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPParam failed Phy->Virt");
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutOutBandGetPPParams;
    }

    //Fill up the FADD message
    pGetParamMsgPayload->pnParamData = (int32_t*)(sMemNode->unVirtAddr);
    pGetParamMsgPayload->unSize      = paramMaxSize;

    memscpy((void *) &pGetParamMsgPayload->bufferMemNode, sizeof(elite_mem_shared_memory_map_t),
            (void *)sMemNode, sizeof(elite_mem_shared_memory_map_t) );

    //Fill up the memory with the ModuleID and ParamID so that PP doesnt have to do it
    if (pPkt->opcode == ADM_CMD_GET_PP_PARAMS_V5)
    {
      adm_param_data_v5_t *psPPParamData = (adm_param_data_v5_t *)(pGetParamMsgPayload->pnParamData);
      adm_cmd_get_pp_params_v5_t *paramHeader = (adm_cmd_get_pp_params_v5_t*)pIncomingAPRPayload;
      psPPParamData->module_id  = paramHeader->module_id;
      psPPParamData->param_id   = paramHeader->param_id;
      psPPParamData->param_size = paramHeader->param_max_size;
      psPPParamData->reserved   = 0;
    }
    else //ADM_CMD_GET_PP_PARAMS_V6
    {
      adm_param_data_v6_t *psPPParamData = (adm_param_data_v6_t *)(pGetParamMsgPayload->pnParamData);
      adm_cmd_get_pp_params_v6_t *paramHeader = (adm_cmd_get_pp_params_v6_t*)pIncomingAPRPayload;
      psPPParamData->module_id   = paramHeader->module_id;
      psPPParamData->instance_id = paramHeader->instance_id;
      psPPParamData->reserved    = 0;
      psPPParamData->param_id    = paramHeader->param_id;
      psPPParamData->param_size  = paramHeader->param_max_size;
    }

    //Send FADD msg to PP svc and wait for ACK.
    result = qurt_elite_queue_push_back(pCoppHandle->cmdQ, (uint64_t*)&msg);
    if (ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to send GetParam to COPP %lu", unCoppID);
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutOutBandGetPPParams;
    }

    pDevCmd->unRespsNeeded++;

    memscpy((void *) &pDevCmd->sMemNode, sizeof(elite_mem_shared_memory_map_t),
            (void *)sMemNode, sizeof(elite_mem_shared_memory_map_t) );

    qurt_elite_memory_free(sMemNode);
    return result;

    __bailoutOutBandGetPPParams:
    //Update the status
    pGetParamMsgPayload->unResponseResult = result;

    //Send the response as the status in ADM_CMDRSP_GET_PP_PARAMS_V5/V6
    if (pPkt->opcode == ADM_CMD_GET_PP_PARAMS_V5)
    {
      adm_cmd_rsp_get_pp_params_v5_t response;
      response.status = result;
      AudDevMgr_GenerateAck(pPkt,
                            result,
                            &(response),
                            sizeof(response),
                            ADM_CMDRSP_GET_PP_PARAMS_V5);
    }
    else //ADM_CMD_GET_PP_PARAMS_V6
    {
      adm_cmd_rsp_get_pp_params_v6_t response;
      response.status = result;
      AudDevMgr_GenerateAck(pPkt,
                            result,
                            &(response),
                            sizeof(response),
                            ADM_CMDRSP_GET_PP_PARAMS_V6);
    }

    //Release the FADD msg that was bound to COPP.
    elite_msg_release_msg(&msg);

    if(sMemNode!=NULL)
      qurt_elite_memory_free(sMemNode);

  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_GET_PP_PARAMS_V5/V6 completed, result = %d", result);
  return result;
}


static ADSPResult Adm_AprGetPPTopoModuleCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  uint32_t             unCoppID, unPayloadSize;
  AdmCalPort_Type     *phCalPort;
  elite_msg_any_t      msg;
  elite_svc_handle_t  *pCoppHandle;

  int                 result               = ADSP_EOK;
  void                *pIncomingAPRPayload = NULL;
  AdmStatSvc_InfoType *pAdmStatSvc         = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  elite_apr_port_t    port                 = elite_apr_if_get_dst_port(pPkt);
  ComprCoppInfo_t     *pComprCoppInfo      = NULL;
  DeviceCmdProcInfo_t *pDevCmd             = NULL;

  EliteMsg_CustomCfg_GetPPTopologyModuleInfo *pMsgPayload = NULL;

  pIncomingAPRPayload = (void*)elite_apr_if_get_payload_ptr(pPkt);
  unCoppID            = ADM_GET_COPP_ID(port);

  // check if set param is called for compressed COPP
  if ((unCoppID >= ADM_COMPRESSED_MIN_RX) && (unCoppID <= ADM_COMPRESSED_MAX_RX))
  {
    pComprCoppInfo = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[unCoppID-ADM_COMPRESSED_MIN_RX]);

    pCoppHandle = pComprCoppInfo->phDevCopp;
    pDevCmd     = &pComprCoppInfo->devCmd;
  }
  else
  {
    // Check the validity of the COPP ID
    if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc, unCoppID, ADM_INVALID_DIRECTION)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID %lu", unCoppID);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    phCalPort   = &pAdmStatSvc->deviceCalPort[unCoppID];
    pCoppHandle = phCalPort->phDevCopp;

    if ((ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
        || (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_GET_PP_TOPO_MODULE_LIST cmd is not supported on ULL/LLNP COPP %lu. cmd failed", unCoppID);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
      return ADSP_EUNSUPPORTED;
    }
    pDevCmd = &phCalPort->devCmd;
  }

  //Create an FADD msg - common to both in-band and out-of-band.
  unPayloadSize = sizeof(elite_msg_custom_header_t);
  pDevCmd->token = Adm_GenerateToken(eDEVICE, unCoppID);

  if(ADSP_FAILED(result = elite_msg_create_msg( &msg, &unPayloadSize, ELITE_CUSTOM_MSG,
                                                pAdmStatSvc->admRspQ, pDevCmd->token, NULL)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to create FADD msg for GET_PP_TOPO_MODULE_INFO cmd, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
    return result;
  }

  pMsgPayload = (EliteMsg_CustomCfg_GetPPTopologyModuleInfo*)msg.pPayload;

  uint32_t memMapHandle, addrLsw, addrMsw, paramMaxSize, respHeaderSize, respCmd;
  if (pPkt->opcode == ADM_CMD_GET_PP_TOPO_MODULE_LIST)
  {
    adm_cmd_get_pp_topo_module_list_t *paramHeader = (adm_cmd_get_pp_topo_module_list_t*)pIncomingAPRPayload;
    memMapHandle             = paramHeader->mem_map_handle;
    addrLsw                  = paramHeader->data_payload_addr_lsw;
    addrMsw                  = paramHeader->data_payload_addr_msw;
    paramMaxSize             = paramHeader->param_max_size;
    respHeaderSize           = sizeof(adm_cmd_rsp_get_pp_topo_module_list_t);
    pMsgPayload->unSecOpCode = ELITEMSG_CUSTOM_GET_PP_TOPOLOGY_MODULES;
    respCmd                  = ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST;
  }
  else //ADM_CMD_GET_PP_TOPO_MODULE_LIST_V2
  {
    adm_cmd_get_pp_topo_module_list_v2_t *paramHeader = (adm_cmd_get_pp_topo_module_list_v2_t*)pIncomingAPRPayload;
    memMapHandle             = paramHeader->mem_map_handle;
    addrLsw                  = paramHeader->data_payload_addr_lsw;
    addrMsw                  = paramHeader->data_payload_addr_msw;
    paramMaxSize             = paramHeader->param_max_size;
    respHeaderSize           = sizeof(adm_cmd_rsp_get_pp_topo_module_list_v2_t);
    pMsgPayload->unSecOpCode = ELITEMSG_CUSTOM_GET_PP_TOPOLOGY_MODULES_V2;
    respCmd                  = ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST_V2;
  }

  if (0 == memMapHandle)
  {
    //In-Band...
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_GET_PP_TOPO_MODULE_LIST/V2.. In-Band!");
    elite_apr_packet_t             *pCmdRspAprPkt = NULL;

    //CmdRSP payload contains status, param size, reserved field and the actual module values.
    uint32_t unCmdRspPayloadSize = respHeaderSize + paramMaxSize;

    //APR alloc memory for in-band CmdRSP and fill the header.
    result = elite_apr_if_alloc_cmd_rsp( pAdmStatSvc->admAprHandle,
                                         elite_apr_if_get_dst_addr( pPkt),
                                         elite_apr_if_get_dst_port( pPkt),
                                         elite_apr_if_get_src_addr( pPkt),
                                         elite_apr_if_get_src_port( pPkt),
                                         elite_apr_if_get_client_token( pPkt),
                                         respCmd,
                                         unCmdRspPayloadSize,
                                         &pCmdRspAprPkt );

    if (ADSP_FAILED(result) || (NULL == pCmdRspAprPkt) )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to allocate APR pkt for InBand GetPPTopoModule cmdrsp, result = %d", result);
      //Release the FADD msg that was bound to COPP.
      elite_msg_release_msg(&msg);
      //Send failure notification to the client processor.
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      return result;
    }

    //Give COPP pointer to the CmdRSP APR pkt's payload (Offset by the status).
    int32_t* pCmdRspAprPktBase = (int32_t*)elite_apr_if_get_payload_ptr(pCmdRspAprPkt);

    if ((NULL != pComprCoppInfo) && (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE == pComprCoppInfo->unCoppTopologyID))
    {
      uint32_t num_modules = 0;
      ((audproc_topology_info_t*)((int8_t*)pCmdRspAprPktBase + respHeaderSize))->num_modules = num_modules;
      result = ADSP_EOK;
      // The num_modules is updated at the memory location after status update, in the return payload.
      // The rest of payload is not to be considered since num_modules itself = 0.
      // For compressed copp with no modules, message is not passed to pp svc, as it would not be present.
      // The Ack's payload is updated at this place and sent back to client
    }
    else
    {

      pMsgPayload->pnParamData = (int32_t*)((int8_t*)pCmdRspAprPktBase + respHeaderSize);
      pMsgPayload->unSize      = paramMaxSize;

      //Send FADD msg to PP svc and wait for ACK.
      result = qurt_elite_queue_push_back(pCoppHandle->cmdQ, (uint64_t*)&msg);

      if (ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to send GetPPtopoModule to COPP %lu", unCoppID);
        memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
        goto __bailoutInBandGetPPModules;
      }
      pDevCmd->unRespsNeeded++;
      pDevCmd->pAprRspPkt = pCmdRspAprPkt;
      return result;
    }
    __bailoutInBandGetPPModules:
    //Update the status
    if (pPkt->opcode == ADM_CMD_GET_PP_TOPO_MODULE_LIST)
    {
      adm_cmd_rsp_get_pp_topo_module_list_t *pcmdRespHeader = (adm_cmd_rsp_get_pp_topo_module_list_t *)(pCmdRspAprPktBase);
      pcmdRespHeader->status = result;
    }
    else //ADM_CMD_GET_PP_TOPO_MODULE_LIST_V2
    {
      adm_cmd_rsp_get_pp_topo_module_list_v2_t *pcmdRespHeader = (adm_cmd_rsp_get_pp_topo_module_list_v2_t *)(pCmdRspAprPktBase);
      pcmdRespHeader->status = result;
    }
    //Free up the incoming apr packet since we create another one for CmdRSP already.
    elite_apr_if_free( pAdmStatSvc->admAprHandle,  pPkt);
    //Send the CmdRSP back to client proc.
    result |= elite_apr_if_async_send( pAdmStatSvc->admAprHandle, pCmdRspAprPkt );
    //Release the FADD msg that was bound to COPP.
    elite_msg_release_msg(&msg);
  }
  else
  {
    //Out-of-band...
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_GET_PP_TOPO_MODULE_LIST/V2.. Out-of-Band!");

    elite_mem_shared_memory_map_t sMemNode;

    //Ensure cache alignment of incoming physical address
    if(addrLsw & CACHE_ALIGNMENT_MASK)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPtopoModule Incoming addr LSW is not aligned to cache line");
      result  = ADSP_EBADPARAM;
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutOutBandGetPPModules;
    }

    //Phy->Virt
    sMemNode.unMemMapHandle = memMapHandle;
    sMemNode.unMemMapClient = admMemoryMapClient;
    sMemNode.unPhysAddrLsw  = addrLsw;
    sMemNode.unPhysAddrMsw  = addrMsw;
    sMemNode.unMemSize      = paramMaxSize;

    result =  elite_mem_map_get_shm_attrib( sMemNode.unPhysAddrLsw,
                                            sMemNode.unPhysAddrMsw,
                                            sMemNode.unMemSize,
                                            &sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPtopoModule failed Phy->Virt");
      memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
      goto __bailoutOutBandGetPPModules;
    }

    if ((NULL != pComprCoppInfo) && (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE == pComprCoppInfo->unCoppTopologyID))
    {
      uint32_t num_modules = 0;

      audproc_topology_info_t *pPayload = (audproc_topology_info_t *)(sMemNode.unVirtAddr);
      pPayload->num_modules = num_modules;
      result                = ADSP_EOK;
      // The num_modules is updated at the virtual memory location, in the return payload. The rest of
      // payload is not to be considered since num_modules itself = 0.
      // For compressed copp with no modules, message is not passed to pp svc, as it would not be present.
      // The Ack's payload is updated at this place and sent back to client
    }
    else
    {
      //Fill up the FADD message
      pMsgPayload->pnParamData = (int32_t*)(sMemNode.unVirtAddr);
      pMsgPayload->unSize      = paramMaxSize;

      //Send FADD msg to PP svc and wait for ACK.
      result = qurt_elite_queue_push_back(pCoppHandle->cmdQ, (uint64_t*)&msg);
      if (ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to send GetPPtopoModule to COPP %lu", unCoppID);
        memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
        goto __bailoutOutBandGetPPModules;
      }

      pDevCmd->unRespsNeeded++;
      memscpy((void *) &pDevCmd->sMemNode, sizeof(elite_mem_shared_memory_map_t),
              (void *)&sMemNode, sizeof(elite_mem_shared_memory_map_t) );
      return result;
    }
    __bailoutOutBandGetPPModules:
    //Update the status
    pMsgPayload->unResponseResult = result;

    //Send the response as the status in ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST/V2
    if (pPkt->opcode == ADM_CMD_GET_PP_TOPO_MODULE_LIST)
    {
      adm_cmd_rsp_get_pp_topo_module_list_t response;
      response.status = result;
      AudDevMgr_GenerateAck(pPkt,
                            result,
                            &(response),
                            sizeof(response),
                            ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST);
    }
    else //ADM_CMD_GET_PP_TOPO_MODULE_LIST_V2
    {
      adm_cmd_rsp_get_pp_topo_module_list_v2_t response;
      response.status = result;
      AudDevMgr_GenerateAck(pPkt,
                            result,
                            &(response),
                            sizeof(response),
                            ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST_V2);
    }

    //Release the FADD msg that was bound to COPP.
    elite_msg_release_msg(&msg);
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_GET_PP_TOPO_MODULE_LIST/V2 completed, result = %d", result);
  return result;
}

static uint8_t Adm_NativeModeParamCallback(adm_cmd_device_open_t *pDevOpenCmdPayload)
{
  uint8_t unNativeModeFlags = 0;

  if (NULL == pDevOpenCmdPayload)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Native mode cb handler rcvd NULL payload ptr!");
    return ADSP_EBADPARAM;
  }

  if (ADM_CMD_DEVICE_OPEN_V8 == pDevOpenCmdPayload->opcode
      ||ADM_CMD_DEVICE_OPEN_V7 == pDevOpenCmdPayload->opcode
      || ADM_CMD_DEVICE_OPEN_V6 == pDevOpenCmdPayload->opcode
      || ADM_CMD_DEVICE_OPEN_V5 == pDevOpenCmdPayload->opcode)
  {
    bool_t bShouldPortOperateInNativeMode = Adm_IsNativeModeRequired(pDevOpenCmdPayload->topology_id);

    // if any of the above modules are present in the topology we'll need to enable channel and bit-width nativity
    if (TRUE == bShouldPortOperateInNativeMode)
    {
      unNativeModeFlags = ((1 << ADM_BIT_SHIFT_NATIVE_MODE_CHANNELS)| (1 << ADM_BIT_SHIFT_NATIVE_MODE_BIT_WIDTH));
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Native mode cb using pre-defined natmode settings = 0x%x", unNativeModeFlags);
    }
    else
    {
        if(pDevOpenCmdPayload->flags & ADM_BIT_MASK_DEVICE_BITWIDTH_NATIVITY_FLAG)
        {
            unNativeModeFlags |= (1 << ADM_BIT_SHIFT_NATIVE_MODE_BIT_WIDTH);
        }

        if(pDevOpenCmdPayload->flags & ADM_BIT_MASK_DEVICE_CHANNEL_NATIVITY_FLAG)
        {
            unNativeModeFlags |= (1 << ADM_BIT_SHIFT_NATIVE_MODE_CHANNELS);
        }

        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Native mode cb using natmode settings = 0x%x", unNativeModeFlags);
    }
  }
  else
  {
     MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Native mode cb handler rcvd invalid opCode 0x%08x", pDevOpenCmdPayload->opcode);
  }

  return unNativeModeFlags;
}

static ADSPResult Adm_ValidateDeviceOpenPayload(elite_apr_packet_t *pPkt)
{
  uint32_t            opCode       = 0;
  uint32_t            payloadSize  = 0;
  opCode      = elite_apr_if_get_opcode(pPkt);
  payloadSize = elite_apr_if_get_payload_size(pPkt);
  ADSPResult result = ADSP_EOK;

  if(ADM_CMD_DEVICE_OPEN_V8 == opCode)
  { // move size verification to a separate function
      uint32_t required_payload_size = sizeof(adm_cmd_device_open_v8_t);
      uint32_t ep1_payload_size = 0, ep2_payload_size = 0, ep3_payload_size = 0;
      adm_cmd_device_open_v8_t     *pDevOpenCmdPayload_v8;

      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_DEVICE_OPEN_V8");

      if (payloadSize < required_payload_size)
      {
          result = ADSP_EBADPARAM;
          MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                      "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                      opCode, required_payload_size);

          return result;
      }

      pDevOpenCmdPayload_v8 = (adm_cmd_device_open_v8_t *)elite_apr_if_get_payload_ptr(pPkt);
      if(pDevOpenCmdPayload_v8->endpoint_id_1 != ADM_CMD_COPP_OPEN_END_POINT_ID_1_IGNORE) // error if eid1 is invalid
      {
          adm_device_endpoint_t  *end_point_params;
          required_payload_size += sizeof(adm_device_endpoint_t);
          if (payloadSize < required_payload_size)
          {
              result = ADSP_EBADPARAM;
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                          "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                          opCode, required_payload_size);
              return result;
          }
          end_point_params = (adm_device_endpoint_t *)(pDevOpenCmdPayload_v8 + 1);
          ep1_payload_size = sizeof(adm_device_endpoint_t) + AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * end_point_params->dev_num_channel);
          required_payload_size += AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * end_point_params->dev_num_channel);
          if (payloadSize < required_payload_size)
          {
              result = ADSP_EBADPARAM;
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                          "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                          opCode, required_payload_size);
              return result;
          }

      }
      else
      {
           result = ADSP_EBADPARAM;
           MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                       "ADM rcvd payload with invalid EP_ID1");
           return result;
      }
      if(pDevOpenCmdPayload_v8->endpoint_id_2 != ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE)
      {
          adm_device_endpoint_t  *end_point_params;
          required_payload_size += sizeof(adm_device_endpoint_t);
          if (payloadSize < required_payload_size)
          {
              result = ADSP_EBADPARAM;
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                          "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                          opCode, required_payload_size);
              return result;
          }
          end_point_params = (adm_device_endpoint_t *)(pDevOpenCmdPayload_v8 + 1);
          end_point_params = (adm_device_endpoint_t *)(((uint8_t *)end_point_params) + ep1_payload_size);
          ep2_payload_size = sizeof(adm_device_endpoint_t) + AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * end_point_params->dev_num_channel);
          required_payload_size += AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * end_point_params->dev_num_channel);
          if (payloadSize < required_payload_size)
          {
              result = ADSP_EBADPARAM;
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                          "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                          opCode, required_payload_size);
              return result;
          }
      }
      if(pDevOpenCmdPayload_v8->endpoint_id_3 != ADM_CMD_COPP_OPEN_END_POINT_ID_3_IGNORE)
      {
          adm_device_endpoint_t  *end_point_params;
          required_payload_size += sizeof(adm_device_endpoint_t);
          if (payloadSize < required_payload_size)
          {
              result = ADSP_EBADPARAM;
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                          "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                          opCode, required_payload_size);
              return result;
          }
          end_point_params = (adm_device_endpoint_t *)(pDevOpenCmdPayload_v8 + 1);
          end_point_params = (adm_device_endpoint_t *)(((uint8_t *)end_point_params) + ep1_payload_size + ep2_payload_size);
          ep3_payload_size = sizeof(adm_device_endpoint_t) + AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * end_point_params->dev_num_channel);
          required_payload_size += AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * end_point_params->dev_num_channel);
          if (payloadSize < required_payload_size)
          {
              result = ADSP_EBADPARAM;
              MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
                          "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
                          opCode, required_payload_size);
              return result;
          }
      }
  }
  else if (ADM_CMD_DEVICE_OPEN_V7 == opCode)
  {
     MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_DEVICE_OPEN_V7");

     if (payloadSize != sizeof(adm_cmd_device_open_v7_t))
     {
       result = ADSP_EBADPARAM;
       MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
              "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
               opCode, sizeof(adm_cmd_device_open_v7_t));
       return result;
     }
   }
   else if (ADM_CMD_DEVICE_OPEN_V6 == opCode)
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_DEVICE_OPEN_V6");

      if (payloadSize != sizeof(adm_cmd_device_open_v6_t))
      {
         result = ADSP_EBADPARAM;
         MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
              "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
              opCode, sizeof(adm_cmd_device_open_v6_t));
         return result;
      }
   }
   else if (ADM_CMD_DEVICE_OPEN_V5 == opCode)
   {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_DEVICE_OPEN_V5");

      if (payloadSize != sizeof(adm_cmd_device_open_v5_t))
      {
         result = ADSP_EBADPARAM;
         MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
              "ADM rcvd payload with invalid size [%lu bytes] for cmd 0x%08x. Expected size = %d bytes", payloadSize,
              opCode, sizeof(adm_cmd_device_open_v5_t));
         return result;
      }
   }
   else
   {
      // invalid opCode error case
      result = ADSP_EBADPARAM;
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM rcvd payload with unsupported opCode [0x%08x]", opCode);
      return result;
   }

  return result;
}

static  ADSPResult Adm_AprDeviceOpenCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  ADSPResult          result       = ADSP_EOK;
  uint32_t            opCode       = 0;
  uint16_t            unCoppID     = UINT16_MAX;
  uint16_t mode_of_operation;
  uint32_t *pTopology_id;

  opCode      = elite_apr_if_get_opcode(pPkt);

  result = Adm_ValidateDeviceOpenPayload(pPkt);
  if(ADSP_FAILED(result))
  {
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
  }

  adm_cmd_device_open_v5_t             *pDevOpenCmdPayload_v5;
  pDevOpenCmdPayload_v5 = (adm_cmd_device_open_v5_t *)elite_apr_if_get_payload_ptr(pPkt);
  mode_of_operation = pDevOpenCmdPayload_v5->mode_of_operation;
  pTopology_id = &pDevOpenCmdPayload_v5->topology_id;

  if( ADM_CMD_DEVICE_OPEN_V8 == opCode)
  {
     adm_cmd_device_open_v8_t             *pDevOpenCmdPayload_v8;
     pDevOpenCmdPayload_v8 = (adm_cmd_device_open_v8_t *)elite_apr_if_get_payload_ptr(pPkt);
     mode_of_operation = pDevOpenCmdPayload_v8->mode_of_operation;
     pTopology_id = &pDevOpenCmdPayload_v8->topology_id;
  }

  //Use internal topology IDs for default (based on direction).
  Adm_GetInternalTopoID(pTopology_id, mode_of_operation);

  unCoppID = Adm_CalculateCoppID(pAdmStatSvc,mode_of_operation);

  if(ADM_COPP_ID_INVALID == unCoppID)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Open Cmd unable to allocate device ID");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;
  }

  result = Adm_DeviceOpenCmdHelperThread(pAdmStatSvc, mode_of_operation, pPkt, NULL, &unCoppID);

  if(ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM open cmd handling using helper thread failed with result = 0x%x", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  }

  return result;
}

static void Adm_DeviceParseOpenPayload(elite_apr_packet_t *pPkt,
                                       adm_cmd_device_open_t *pDevOpenCmdPayload)
{
    uint32_t opCode = elite_apr_if_get_opcode(pPkt);

    pDevOpenCmdPayload->opcode = opCode;
    if(ADM_CMD_DEVICE_OPEN_V8 == opCode)
    {
        // Since ADM Open V8 is not a superset of Open V5 or V6 or V7.
        adm_cmd_device_open_v8_t             *pDevOpenCmdPayload_v8;
        adm_device_endpoint_t  *end_point_params;
        uint32_t ep1_payload_size = 0, ep2_payload_size = 0, ep3_payload_size = 0;
        pDevOpenCmdPayload_v8 = (adm_cmd_device_open_v8_t *)elite_apr_if_get_payload_ptr(pPkt);
        pDevOpenCmdPayload->endpoint_id_1 = pDevOpenCmdPayload_v8->endpoint_id_1;
        pDevOpenCmdPayload->mode_of_operation = pDevOpenCmdPayload_v8->mode_of_operation;

        pDevOpenCmdPayload->endpoint_id_2 = pDevOpenCmdPayload_v8->endpoint_id_2;
        pDevOpenCmdPayload->endpoint_id_3 = pDevOpenCmdPayload_v8->endpoint_id_3;
        pDevOpenCmdPayload->topology_id = pDevOpenCmdPayload_v8->topology_id;
        pDevOpenCmdPayload->flags = pDevOpenCmdPayload_v8->flags;

        end_point_params = (adm_device_endpoint_t *)(pDevOpenCmdPayload_v8 + 1);
        pDevOpenCmdPayload->sample_rate_eid1 = end_point_params->sample_rate;
        pDevOpenCmdPayload->bit_width_eid1 = end_point_params->bit_width;
        pDevOpenCmdPayload->dev_num_channel_eid1 = end_point_params->dev_num_channel;
        pDevOpenCmdPayload->dev_channel_mapping_eid1 = (uint8_t *)(end_point_params + 1);
        ep1_payload_size = sizeof(adm_device_endpoint_t) + AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * pDevOpenCmdPayload->dev_num_channel_eid1);

        if(pDevOpenCmdPayload_v8->endpoint_id_2 != ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE)
        {
            end_point_params = (adm_device_endpoint_t *)(((uint8_t *)end_point_params) + ep1_payload_size);
            pDevOpenCmdPayload->sample_rate_eid2 = end_point_params->sample_rate;
            pDevOpenCmdPayload->bit_width_eid2 = end_point_params->bit_width;
            pDevOpenCmdPayload->dev_num_channel_eid2 = end_point_params->dev_num_channel;
            ep2_payload_size = sizeof(adm_device_endpoint_t) + AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * pDevOpenCmdPayload->dev_num_channel_eid2);
            pDevOpenCmdPayload->dev_channel_mapping_eid2 = (uint8_t *)(end_point_params + 1);
        }

        if(pDevOpenCmdPayload_v8->endpoint_id_3 != ADM_CMD_COPP_OPEN_END_POINT_ID_3_IGNORE)
        {
            end_point_params = (adm_device_endpoint_t *)(((uint8_t *)end_point_params) + ep1_payload_size + ep2_payload_size);
            pDevOpenCmdPayload->sample_rate_eid3 = end_point_params->sample_rate;
            pDevOpenCmdPayload->bit_width_eid3 = end_point_params->bit_width;
            pDevOpenCmdPayload->dev_num_channel_eid3 = end_point_params->dev_num_channel;
            ep3_payload_size = sizeof(adm_device_endpoint_t) + AUD_ROUNDTO4(sizeof(adm_device_endpoint_ch_map_t) * pDevOpenCmdPayload->dev_num_channel_eid3);
            pDevOpenCmdPayload->dev_channel_mapping_eid3 = (uint8_t *)(end_point_params + 1);
        }
    }
    else
    {
        // Since ADM Open V6 is a superset of Open V5 we can safely cast to the base structure and handle the open as a V5.
        adm_cmd_device_open_v5_t             *pDevOpenCmdPayload_v5;
        pDevOpenCmdPayload_v5 = (adm_cmd_device_open_v5_t *)elite_apr_if_get_payload_ptr(pPkt);
        pDevOpenCmdPayload->endpoint_id_1 = pDevOpenCmdPayload_v5->endpoint_id_1;
        pDevOpenCmdPayload->mode_of_operation = pDevOpenCmdPayload_v5->mode_of_operation;
        pDevOpenCmdPayload->endpoint_id_2 = pDevOpenCmdPayload_v5->endpoint_id_2;
        pDevOpenCmdPayload->topology_id = pDevOpenCmdPayload_v5->topology_id;
        pDevOpenCmdPayload->flags = pDevOpenCmdPayload_v5->flags;

        pDevOpenCmdPayload->sample_rate_eid1 = pDevOpenCmdPayload_v5->sample_rate;
        pDevOpenCmdPayload->bit_width_eid1 = pDevOpenCmdPayload_v5->bit_width;
        pDevOpenCmdPayload->dev_num_channel_eid1 = pDevOpenCmdPayload_v5->dev_num_channel;
        pDevOpenCmdPayload->dev_channel_mapping_eid1 = &pDevOpenCmdPayload_v5->dev_channel_mapping[0];

        if(ADM_CMD_DEVICE_OPEN_V6 == opCode)
        {
            adm_cmd_device_open_v6_t             *pDevOpenCmdPayload_v6;
            pDevOpenCmdPayload_v6 = (adm_cmd_device_open_v6_t *)elite_apr_if_get_payload_ptr(pPkt);
            pDevOpenCmdPayload->sample_rate_eid2 = pDevOpenCmdPayload_v6->sample_rate_eid2;
            pDevOpenCmdPayload->bit_width_eid2 = pDevOpenCmdPayload_v6->bit_width_eid2;
            pDevOpenCmdPayload->dev_num_channel_eid2 = pDevOpenCmdPayload_v6->dev_num_channel_eid2;
            pDevOpenCmdPayload->dev_channel_mapping_eid2 = &pDevOpenCmdPayload_v6->dev_channel_mapping_eid2[0];
        }
        else if(ADM_CMD_DEVICE_OPEN_V7 == opCode)
        {
            adm_cmd_device_open_v7_t             *pDevOpenCmdPayload_v7;
            pDevOpenCmdPayload_v7 = (adm_cmd_device_open_v7_t *)elite_apr_if_get_payload_ptr(pPkt);
            pDevOpenCmdPayload->sample_rate_eid2 = pDevOpenCmdPayload_v7->sample_rate_eid2;
            pDevOpenCmdPayload->bit_width_eid2 = pDevOpenCmdPayload_v7->bit_width_eid2;
            pDevOpenCmdPayload->dev_num_channel_eid2 = pDevOpenCmdPayload_v7->dev_num_channel_eid2;
            pDevOpenCmdPayload->dev_channel_mapping_eid2 = &pDevOpenCmdPayload_v7->dev_channel_mapping_eid2[0];
            pDevOpenCmdPayload->endpoint_id_3 = pDevOpenCmdPayload_v7->endpoint_id_3;
            pDevOpenCmdPayload->sample_rate_eid3 = pDevOpenCmdPayload_v7->sample_rate_eid3;
            pDevOpenCmdPayload->bit_width_eid3 = pDevOpenCmdPayload_v7->bit_width_eid3;
            pDevOpenCmdPayload->dev_num_channel_eid3 = pDevOpenCmdPayload_v7->dev_num_channel_eid3;
            pDevOpenCmdPayload->dev_channel_mapping_eid3 = &pDevOpenCmdPayload_v7->dev_channel_mapping_eid3[0];

        }
    }
}

static ADSPResult Adm_DeviceOpenCmdLPCMHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                               adm_cmd_device_open_t *pDevOpenCmdPayload,
                                               elite_apr_packet_t *pPkt,
                                               NativeModeHook cbNativeMode,
                                               uint16_t *unCreatedCoppID,
                                               qurt_elite_queue_t *pRspQ)
{
  ADSPResult result                     = ADSP_EOK;
  uint16_t   unNumChannels              = 1;
  bool_t     bIsInPortLive              = FALSE, bIsInPortBurstMode = FALSE;
  bool_t     bShouldAFETxBeDisconnected = FALSE;
  uint32_t   bytes_per_sample           = ADM_BYTES_PER_SAMPLE_TWO; /* default bytes per sample */
  uint32_t   unLogID                    = 0;

  uint16_t                     unCoppID, endPointID1;
  qurt_elite_thread_t          coppThreadID;
  AdmCalPort_Type              *phCalPort;
  elite_svc_handle_t           *pCoppHandle;
  AdmDevSessionDelayParam_Type *pSessionDelayParam;
  uint32_t opCode = pDevOpenCmdPayload->opcode;
  uint32_t                     unAfeNumBuffers,unAfeFrameSize;

  unCoppID = *unCreatedCoppID;
  endPointID1 = pDevOpenCmdPayload->endpoint_id_1;
  //Check for validity of endpointID1.
  if (ADSP_EOK == afe_port_id_validation(endPointID1))
  {
    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
    pSessionDelayParam = &(pAdmStatSvc->pDevSessionDelayParam[unCoppID]);
    phCalPort->unEID1.unAfePortID = endPointID1;
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid endpoint_id_1 [0x%X]", endPointID1);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;
  }

  if (AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT == pDevOpenCmdPayload->topology_id)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM:AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT is not supported in LPCM mode");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
    return ADSP_EUNSUPPORTED;
  }


  phCalPort->unEID1.unBytesPerSample = ADM_BYTES_PER_SAMPLE_TWO;
  phCalPort->unEID2.unBytesPerSample = ADM_BYTES_PER_SAMPLE_TWO;
  phCalPort->unEID2.unAfePortID      = pDevOpenCmdPayload->endpoint_id_2;
  phCalPort->unCoppMode              = pDevOpenCmdPayload->mode_of_operation;

  /* Check for validity of device performance mode received */
  /**
   *     1. get the device_perf_mode and check if they are valid
   *     2. return failure incase of invalid entries
   *     3. set COPP buffer duration to 10msec for ADM_LEGACY_DEVICE_SESSION &
   *                               1msec  for ADM_LOW_LATENCY_DEVICE_SESSION
   */

  /* for 44.1Khz, the duration is 10msec, which is set later for audio topology*/


  phCalPort->unDevicePerfMode = (uint16_t)Adm_GetDevicePerfModeInOpenCmd(pDevOpenCmdPayload->flags);

  if (ADM_ULTRA_LOW_LATENCY_POST_PROC_DEVICE_SESSION < phCalPort->unDevicePerfMode )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device_perf_mode in flags field [%d]", phCalPort->unDevicePerfMode);
    /* Return ack for failure */
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;

  }

  /* check if device performance mode is ULL*/
  if (ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
  {
    return (Adm_UllMultiChannelDeviceOpenCmdHandler(pAdmStatSvc, pPkt, unCoppID, pDevOpenCmdPayload, pRspQ));
  }
  /* check if device performance mode is LLNP*/
  else if (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode)
  {
    return (Adm_LlnpMultiChannelDeviceOpenCmdHandler(pAdmStatSvc, pPkt, unCoppID, pDevOpenCmdPayload, pRspQ));
  }
  /* check if device performance mode is ULLPP */
  else if (ADM_ULTRA_LOW_LATENCY_POST_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode)
  {
    return (Adm_UllppMultiChannelDeviceOpenCmdHandler(pAdmStatSvc, pPkt, unCoppID, pDevOpenCmdPayload, pRspQ));
  }

  switch (pDevOpenCmdPayload->mode_of_operation)
  {
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP:
    {
      phCalPort->unCoppDirection = RX_DIR;
      bIsInPortLive              = FALSE;
      bIsInPortBurstMode         = FALSE;

      if (AFE_PORT_ID_PSEUDOPORT_01 <= endPointID1)
      {
        phCalPort->bIsCoppConnectedToPseudoPort = TRUE;
      }

      break;
    }
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP:
    {
      phCalPort->unCoppDirection = TX_DIR;
      switch(endPointID1)
      {
        case AFE_PORT_ID_PSEUDOPORT_01:
        case AFE_PORT_ID_PSEUDOPORT_02:
        case AFE_PORT_ID_VOICE_RECORD_RX:
        case AFE_PORT_ID_VOICE_RECORD_TX:
        case AFE_PORT_ID_VOICE_PLAYBACK_TX:
        {
          bIsInPortLive      = FALSE;
          bIsInPortBurstMode = FALSE;
          phCalPort->bIsCoppConnectedToPseudoPort = TRUE;
          break;
        }
        default:
        {
          bIsInPortLive      = TRUE;
          bIsInPortBurstMode = FALSE;
          phCalPort->bIsCoppConnectedToPseudoPort = FALSE;
          break;
        }
      }
      break;
    }
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP:
    {
      phCalPort->unCoppDirection = TX_DIR;
      bIsInPortLive = FALSE;
      switch(endPointID1)
      {
        case AFE_PORT_ID_PSEUDOPORT_01:
        case AFE_PORT_ID_PSEUDOPORT_02:
        case AFE_PORT_ID_VOICE_RECORD_RX:
        case AFE_PORT_ID_VOICE_RECORD_TX:
        case AFE_PORT_ID_VOICE_PLAYBACK_TX:
        {
          bIsInPortBurstMode = FALSE;
          phCalPort->bIsCoppConnectedToPseudoPort = TRUE;
          break;
        }
        default:
        {
          bIsInPortBurstMode = FALSE;
          phCalPort->bIsCoppConnectedToPseudoPort = FALSE;
          break;
        }
      }
      break;
    }
  }

  //Verify that dev_num_channel value is (greater than 0) and (less than or equal to 32 if ADM V8 cmd is received else it should be less than or equal to 8)
  if ((ADM_NUM_CHANNELS_THIRTY_TWO < pDevOpenCmdPayload->dev_num_channel_eid1)
      || ((ADM_CMD_DEVICE_OPEN_V8 != opCode) && (ADM_NUM_CHANNELS_EIGHT < pDevOpenCmdPayload->dev_num_channel_eid1))
      || (ADM_NUM_CHANNELS_NULL == pDevOpenCmdPayload->dev_num_channel_eid1))
  {
     MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device num channels [%d], valid range: 1 - 8", pDevOpenCmdPayload->dev_num_channel_eid1);
     elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
     return ADSP_EFAILED;
  }

  if(ADSP_EOK == elite_cmn_topo_db_is_active_topology_present(1 << AVCS_TOPO_CFG_AREA_VOICE_BIT, pDevOpenCmdPayload->topology_id))
  {
    //Voice Proc Tx block
    phCalPort->unCoppType = ADM_COPP_TYPE_VPTX;

    /* Set default params for Endpoint ID 2 channel map & number of channels*/
    phCalPort->unEID2.unNumChannels   = ADM_NUM_CHANNELS_MONO;
    phCalPort->unEID2.unChannelMap[0] = PCM_CHANNEL_C;

    //Check for validity of sampling rate
    if(!Adm_IsValidSampleRateForVpTxTopo(pDevOpenCmdPayload->topology_id,pDevOpenCmdPayload->sample_rate_eid1))
    {
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    //Check that VpTx topologies are used in the Tx Direction only
    if ((ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP != pDevOpenCmdPayload->mode_of_operation)&&
        (ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP != pDevOpenCmdPayload->mode_of_operation))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Incorrect mode of operation [%d] for VPTX topology 0x%lX",
            pDevOpenCmdPayload->mode_of_operation, pDevOpenCmdPayload->topology_id);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    //At this point, sampling rate is valid
    //Note: For VpTx topology being created via device_open_v6, the sample rate
    //for eid2 will be updated later from the payload.
    //For creation, keep eid1 & eid2 sample rates the same

    phCalPort->unMtMxSampleRate    = pDevOpenCmdPayload->sample_rate_eid1;
    phCalPort->unEID1.unSampleRate = pDevOpenCmdPayload->sample_rate_eid1;
    phCalPort->unEID2.unSampleRate = pDevOpenCmdPayload->sample_rate_eid1;
    if(ADM_BITS_PER_SAMPLE_16 != pDevOpenCmdPayload->bit_width_eid1)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid PCM bit_width for VPTX  [%d], ",
            pDevOpenCmdPayload->bit_width_eid1);

      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }
    phCalPort->unEID1.unBitWidth = pDevOpenCmdPayload->bit_width_eid1;
    phCalPort->unEID2.unBitWidth = pDevOpenCmdPayload->bit_width_eid1;

    //At this point, we already have preset values for the following eid1 & eid2 variables
    // eid1 SR, BW  have preset values but CH & CHMAP TBD
    // eid2 SR, BW, CH & CHMAP.

    /* We have to account for 2 possible combinations w.r.t Open Cmd Version vs Vptx
        // 1. If Open_V5 is used for VpTx topologies    -> EID1 CH Info - Payload ; EID2 - Retain
        // 2. If Open_V6 is used for VpTx topologies    -> EID1 CH Info - Payload ; EID2 - Payload
     */

    if( (ADM_CMD_DEVICE_OPEN_V6 == opCode ||  ADM_CMD_DEVICE_OPEN_V7 == opCode || ADM_CMD_DEVICE_OPEN_V8 == opCode)&&
        (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != pDevOpenCmdPayload->endpoint_id_2))
    {
      // VpTx Fwk only supports a single sampling rate and bit-width is 16bits, hence eid2 SR and BW values are equals to eid1 SR and BW
      // The actual physical endpoints can run at any bit-width or sampling rate, but ADM will connect to the AFE always with the near port configuration.
      // AFE does the conversion BW and SR as needed on reference channel path.
      phCalPort->unEID2.unSampleRate = pDevOpenCmdPayload->sample_rate_eid1;
      phCalPort->unEID2.unBitWidth = pDevOpenCmdPayload->bit_width_eid1;
      phCalPort->unEID2.unBytesPerSample = elite_data_get_bytes_per_sample(pDevOpenCmdPayload->bit_width_eid1);
      phCalPort->unEID2.unNumChannels = pDevOpenCmdPayload->dev_num_channel_eid2;

      for (uint16_t i = 0; i <pDevOpenCmdPayload->dev_num_channel_eid2; i++)
      {
         phCalPort->unEID2.unChannelMap[i] = pDevOpenCmdPayload->dev_channel_mapping_eid2[i];
      }
      MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Configuring VpTx Far Reference media type: Received fs:%lu, bit-width:%d but sets fs:%lu, bit-width:%d",
           pDevOpenCmdPayload->sample_rate_eid2, pDevOpenCmdPayload->bit_width_eid2, phCalPort->unEID2.unSampleRate, pDevOpenCmdPayload->bit_width_eid1);

    }

    if( ADSP_FAILED(Adm_GetChannelConfigForVpTxTopo(pDevOpenCmdPayload->topology_id,
                                                    &unNumChannels,
                                                    &phCalPort->unEID1.unChannelMap[0])) )
    {
      unNumChannels = pDevOpenCmdPayload->dev_num_channel_eid1;
      for (uint16_t i = 0; i < pDevOpenCmdPayload->dev_num_channel_eid1; i++)
      {
        phCalPort->unEID1.unChannelMap[i] = pDevOpenCmdPayload->dev_channel_mapping_eid1[i];
      }
    }

    MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing CREATE_VPTX cmd, TopID: 0x%lX, fs: %lu, EP1: 0x%X, EP2: 0x%X, #mic: %d",
         pDevOpenCmdPayload->topology_id, pDevOpenCmdPayload->sample_rate_eid1, pDevOpenCmdPayload->endpoint_id_1, pDevOpenCmdPayload->endpoint_id_2, unNumChannels);

    vptx_create_params_v2_t create_param;
    memset(&create_param, 0, sizeof(vptx_create_params_v2_t));

    create_param.near_port_id      = pDevOpenCmdPayload->endpoint_id_1;
    create_param.far_port_id       = pDevOpenCmdPayload->endpoint_id_2;
    create_param.topology_id       = pDevOpenCmdPayload->topology_id;
    create_param.sampling_rate     = pDevOpenCmdPayload->sample_rate_eid1;
    create_param.session_num       = unCoppID;
    create_param.shared_mem_client = admMemoryMapClient;
    create_param.num_mics          = unNumChannels;
    create_param.num_ref_channels  = phCalPort->unEID2.unNumChannels;

    memscpy(&(create_param.channel_map_near),sizeof(create_param.channel_map_near),
            &(phCalPort->unEID1.unChannelMap), sizeof(phCalPort->unEID1.unChannelMap));
    memscpy(&(create_param.channel_map_far),sizeof(create_param.channel_map_far),
            &(phCalPort->unEID2.unChannelMap), sizeof(phCalPort->unEID2.unChannelMap));

    //1. Create the VPTX block.
    if (ADSP_FAILED(result = vptx_aud_create_v3((void **) &phCalPort->phDevCopp, (void **) &phCalPort->phDevCoppEcRef, &create_param)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Create VpTX failed with result=%d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    qurt_elite_mutex_lock(&pAdmStatSvc->admLock);
    pAdmStatSvc->unNumVpTxCoppOpenIssued++;
    if(ADM_MAX_COPP_OPEN_CTR < pAdmStatSvc->unNumVpTxCoppOpenIssued)
    {
      pAdmStatSvc->unNumVpTxCoppOpenIssued = 0;
    }
    unLogID = pAdmStatSvc->unNumVpTxCoppOpenIssued;
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

    //VoiceProcTx block provides its handle.
    pCoppHandle = phCalPort->phDevCopp;
    //VPTx thread ID. Used to destroy VPTx if cmd handler fails midway.
    coppThreadID = pCoppHandle->threadId;

    //2. Create an input port on the matrix mixer
    elite_svc_handle_t *pMtMxHandle = pAdmStatSvc->hTxMatrix;

    /* Since the VpTX module sends 20ms chunks, the TX audio matrix needs to operate in Burst mode and implicitly
              this path needs to have a lower priority because of the large window (20ms) */
    bIsInPortLive      = FALSE;
    bIsInPortBurstMode = TRUE;

    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing CONNECT_MT_MX_IN_PORT cmd, Live: %d, BM: %d",
          bIsInPortLive, bIsInPortBurstMode);

    /* low latency mode for Voice copp is not supported yet. Hence default to legacy mode.*/
    phCalPort->unDevicePerfMode = ADM_LEGACY_DEVICE_SESSION;

    if (ADSP_FAILED(result = Adm_SendCmdConnectMtMxInPort(pAdmStatSvc, 0xFFFFFFFF,
                                                          bIsInPortLive, bIsInPortBurstMode,
                                                          0, pMtMxHandle,
                                                          &((phCalPort->mtMxPort).phMtMxInPort),
                                                          NULL, unLogID,
                                                          NULL, phCalPort->unDevicePerfMode,
                                                          0, &(phCalPort->unEID1.pAfeDriftPtr),
                                                          FALSE,pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_MT_MX_IN_PORT cmd failed, result = %d", result);
      // Tear down the graph constructed thus far: 1. Destroy VPTx
      goto __bailoutTXDeviceOpen4;
    }

    //3. Provide the handle of the matrix mixer to the VoiceProcTx block via Connect cmd */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing CONNECT_VOICEPROCTX cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                            &((phCalPort->mtMxPort).phMtMxInPort->portHandle),
                                            ELITE_CMD_CONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_VOICEPROCTX cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Close MXAT input port */
      /* 2. Destroy VPTx */
      goto __bailoutTXDeviceOpen3;
    }

    phCalPort->unEID1.unNumChannels = unNumChannels;

    //4. Request connection of VoiceProcTx block with first AFE port - for near samples
    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd (AFE Tx), EP1: 0x%X, SR:%lu, num ch:%lu, bit width %lu",\
        endPointID1, pDevOpenCmdPayload->sample_rate_eid1, phCalPort->unEID1.unNumChannels, ADM_BITS_PER_SAMPLE_16);

    if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, endPointID1,
                                                   phCalPort->phDevCopp,
                                                   AFE_PP_OUT,
                                                   &(phCalPort->unEID1.phAfePort),
                                                   pDevOpenCmdPayload->sample_rate_eid1,
                                                   phCalPort->unEID1.unNumChannels,
                                                   &(phCalPort->unEID1.unChannelMap[0]),
                                                   ADM_FRAME_SIZE_1MS,
                                                   ADM_HIGHEST_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                   ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                   ADM_BITS_PER_SAMPLE_16,
                                                   &(phCalPort->unEID1.pAfeDriftPtr),
                                                   &(pSessionDelayParam->unAFEDelay_EP1),
                                                   FALSE,
                                                   pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_CONNECT_REQ cmd (AFE Tx) failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect from MXAT input port */
      /* 2. Close MXAT input port */
      /* 3. Destroy VPTx */
      goto __bailoutTXDeviceOpen2;
    }

    //5. If required, request connection of VoiceProcTx block with second AFE port - for far samples
    phCalPort->unEID2.unAfePortID = pDevOpenCmdPayload->endpoint_id_2;
    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != pDevOpenCmdPayload->endpoint_id_2)
    {
      MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd (AFE Rx), EP2: 0x%X, SR:%lu, num ch:%lu, bit-width %lu ",
            phCalPort->unEID2.unAfePortID, phCalPort->unEID2.unSampleRate, phCalPort->unEID2.unNumChannels, phCalPort->unEID2.unBitWidth );

      if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, pDevOpenCmdPayload->endpoint_id_2,
                                                     phCalPort->phDevCoppEcRef,
                                                     AFE_PP_OUT,
                                                     &(phCalPort->unEID2.phAfePort),
                                                     phCalPort->unEID2.unSampleRate,
                                                     phCalPort->unEID2.unNumChannels,
                                                     &(phCalPort->unEID2.unChannelMap[0]),
                                                     ADM_FRAME_SIZE_1MS,
                                                     ADM_HIGHEST_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                     ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                     phCalPort->unEID2.unBitWidth,
                                                     &(phCalPort->unEID2.pAfeDriftPtr),
                                                     &(pSessionDelayParam->unAFEDelay_EP2),
                                                     FALSE,
                                                     pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_CONNECT_REQ cmd (AFE Rx) failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. Disable AFE Tx port */
        /* 2. Disconnect from MXAT input port */
        /* 3. Close MXAT input port */
        /* 4. Destroy VPTx */
        /* 5. Disconnect AFE Tx port */
        goto __bailoutTXDeviceOpen1;
      }
    }

    //6. Send a Run cmd to the matrix mixer to trigger its input port */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing RUN_MT_MX_INPUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdRunMtMxPort(pAdmStatSvc,
                                                    (phCalPort->mtMxPort).phMtMxInPort->inPortID,
                                                    MATRIX_MIXER_PORT_DIR_INPUT, pMtMxHandle,
                                                    pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_MT_MX_INPUT_PORT cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. if VPTx was connected to AFE Rx (for far-end samples), disable AFE Rx port */
      /* 2. Disable AFE Tx port */
      /* 3. Disconnect from MXAT input port */
      /* 4. Close MXAT input port */
      /* 5. Destroy VPTx */
      /* 6. Disconnect AFE Tx port */
      /* 7. if VPTx was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
      goto __bailoutTXDeviceOpen0;
    }

    //7. Send a Start cmd to VPTx */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of ADM_CMD_DEVICE_OPEN, issuing START_VPTx cmd");
    if (ADSP_FAILED(result = Adm_SendCmdStartCopp(pCoppHandle, pRspQ,
                                                  (void*)(phCalPort->unEID1.pAfeDriftPtr), (void*)(phCalPort->unEID2.pAfeDriftPtr))))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: START_VPTx cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. if VPTx was connected to AFE Rx (for far-end samples), disable AFE Rx port */
      /* 2. Disable AFE Tx port */
      /* 3. Disconnect from MXAT input port */
      /* 4. Close MXAT input port */
      /* 5. Destroy VPTx */
      /* 6. Disconnect AFE Tx port */
      /* 7. if VPTx was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
      goto __bailoutTXDeviceOpen0;
    }

    //8. Attempt to setup the device cmd Q for the VpTx Copp
    result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, FALSE, TRUE);

    if(ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to setup devicecmdQ for COPP [%u]", unCoppID);
      /* Tear down the graph constructed thus far */
      /* 1. if VPTx was connected to AFE Rx (for far-end samples), disable AFE Rx port */
      /* 2. Disable AFE Tx port */
      /* 3. Disconnect from MXAT input port */
      /* 4. Close MXAT input port */
      /* 5. Destroy VPTx */
      /* 6. Disconnect AFE Tx port */
      /* 7. if VPTx was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
      goto __bailoutTXDeviceOpen0;
    }

  } //VpTx Copp
  else
  {
    //Audio COPP...
    phCalPort->unCoppType = ADM_COPP_TYPE_AUDIO_COPP;

    Adm_PrintChannelType(pDevOpenCmdPayload->dev_channel_mapping_eid1, pDevOpenCmdPayload->dev_num_channel_eid1);

    //For mono or stereo opens, if PCM_CHANNEL_INVALID was set, then set them to default mono/stereo channels
    if((ADM_NUM_CHANNELS_MONO == pDevOpenCmdPayload->dev_num_channel_eid1) && (PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[0]))
    {
       pDevOpenCmdPayload->dev_channel_mapping_eid1[0] = PCM_CHANNEL_C;
    }

    if((ADM_NUM_CHANNELS_STEREO == pDevOpenCmdPayload->dev_num_channel_eid1) &&
            ((PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[0]) || (PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[1])))
    {
       pDevOpenCmdPayload->dev_channel_mapping_eid1[0] = PCM_CHANNEL_L;
       pDevOpenCmdPayload->dev_channel_mapping_eid1[1] = PCM_CHANNEL_R;
    }

    //For non-mono, non-stereo types, PCM_CHANNEL_INVALID is invalid. So is any mapping greater than MAX_CHANNEL_MAPPING_NUMBER
    for (uint16_t i = 0; i < pDevOpenCmdPayload->dev_num_channel_eid1; i++)
    {
      if ((MAX_CHANNEL_MAPPING_NUMBER < pDevOpenCmdPayload->dev_channel_mapping_eid1[i]) || (PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[i]))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device channel mapping %d for channel #%d", pDevOpenCmdPayload->dev_channel_mapping_eid1[i], (i + 1));
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
        return ADSP_EFAILED;
      }
    }

    //Bit-width sanity
    if(pDevOpenCmdPayload->bit_width_eid1 < ADM_BITS_PER_SAMPLE_16 || pDevOpenCmdPayload->bit_width_eid1 > ADM_BITS_PER_SAMPLE_32)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid PCM bit_width  [%d], valid range: 16-32 bits",
            pDevOpenCmdPayload->bit_width_eid1);

      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }
    bytes_per_sample = elite_data_get_bytes_per_sample(pDevOpenCmdPayload->bit_width_eid1);
    phCalPort->unEID1.unBytesPerSample = bytes_per_sample;
    phCalPort->unEID1.unBitWidth       = pDevOpenCmdPayload->bit_width_eid1;

    //Sampling rate sanity
    if((0 == pDevOpenCmdPayload->sample_rate_eid1) || (ADM_SAMPLING_RATE_MAX < pDevOpenCmdPayload->sample_rate_eid1))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid sampling rate [%lu] for Audio COPP topology 0x%lX",
            pDevOpenCmdPayload->sample_rate_eid1, pDevOpenCmdPayload->topology_id);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }
    phCalPort->unMtMxSampleRate    = pDevOpenCmdPayload->sample_rate_eid1;
    phCalPort->unEID1.unSampleRate = pDevOpenCmdPayload->sample_rate_eid1;

    /* Validate the device sampling rate & then fetch the afe frame size*/
    if(ADSP_FAILED(is_valid_device_sampling_rate(phCalPort->unEID1.unSampleRate)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid sampling rate [%lu] for Audio COPP",
            phCalPort->unEID1.unSampleRate);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    uint32_t unCoppAfeFrameSizeInSamples;
    elite_svc_get_frame_size(phCalPort->unEID1.unSampleRate, &unCoppAfeFrameSizeInSamples);

    if (ADM_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
    {
      phCalPort->unCoppNumAfeFrames = ADM_LL_NUM_AFE_FRAMES;
    }
    else
    {
      phCalPort->unCoppNumAfeFrames = ADM_LEGACY_NUM_AFE_FRAMES;
    }

    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: device_perf_mode is [%hu] & afe_frame_size is [%lu] & COPP Buffer Num Frames is [%lu]",
          phCalPort->unDevicePerfMode, unCoppAfeFrameSizeInSamples, phCalPort->unCoppNumAfeFrames);

    if (phCalPort->unCoppDirection == RX_DIR)
    {
      // RX direction...
      //far-end port id or second endpoint ID is ignored on playback rx path.
      phCalPort->unEID2.unAfePortID = ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE;
#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE before creating COPP Svc %d",
            qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of Rx ADM_CMD_DEVICE_OPEN, issuing CREATE_COPP cmd, topologyID: 0x%lX, sampling rate %lu",
            pDevOpenCmdPayload->topology_id, pDevOpenCmdPayload->sample_rate_eid1);

      //Increment the Number of RX Audio COPP opened
      qurt_elite_mutex_lock(&pAdmStatSvc->admLock);
      pAdmStatSvc->unNumRxAudioCoppOpenIssued++;
      if(ADM_MAX_COPP_OPEN_CTR < pAdmStatSvc->unNumRxAudioCoppOpenIssued)
      {
        pAdmStatSvc->unNumRxAudioCoppOpenIssued = 0;
      }
      //Get a unique Log ID. PP may increment upto 16 times inside its code on every EOS and flush (flush doesnt apply for device path)
      unLogID = ADM_LOG_ID_BASE_RX + (pAdmStatSvc->unNumRxAudioCoppOpenIssued << 4);
      qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

      result = Adm_CreatePPSvc(pAdmStatSvc,
                               phCalPort,
                               pSessionDelayParam,
                               pDevOpenCmdPayload->topology_id,
                               DYNA_SVC_PP_TYPE_COPP,
                               unLogID);
      if (ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CREATE COPP cmd failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }

      //COPP provides its handle
      pCoppHandle = phCalPort->phDevCopp;
      //COPP thread ID. Used to destroy COPP if cmd handler fails midway
      coppThreadID = pCoppHandle->threadId;

#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE after creating COPP Svc %d",
            qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

      /* Specify output media format to COPP    */
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: cfg'ing to output %d channels", pDevOpenCmdPayload->dev_num_channel_eid1);

      if (ADSP_FAILED(result = adm_config_pp_output_media_format(pCoppHandle, pRspQ,
                                                                 pDevOpenCmdPayload->dev_num_channel_eid1,
                                                                 &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                                 pDevOpenCmdPayload->sample_rate_eid1, 0)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: PP_output_media_fmt cmd failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen4;
      }

      //Num Channels book keeping
      phCalPort->unEID1.unNumChannels = (uint32_t)pDevOpenCmdPayload->dev_num_channel_eid1;

      MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Rx ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd, EP1: 0x%X, SR: %lu, num ch: %lu, bit-width %lu", \
            endPointID1, pDevOpenCmdPayload->sample_rate_eid1, pDevOpenCmdPayload->dev_num_channel_eid1, phCalPort->unEID1.unBitWidth);

      if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, endPointID1,
                                                     phCalPort->phDevCopp,
                                                     AFE_RX_AUD_MIXER_IN,
                                                     &(phCalPort->unEID1.phAfePort),
                                                     pDevOpenCmdPayload->sample_rate_eid1,
                                                     pDevOpenCmdPayload->dev_num_channel_eid1,
                                                     &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                     phCalPort->unCoppNumAfeFrames,
                                                     ADM_NORMAL_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                     ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                     phCalPort->unEID1.unBitWidth,
                                                     &(phCalPort->unEID1.pAfeDriftPtr),
                                                     &(pSessionDelayParam->unAFEDelay_EP1),
                                                     FALSE,
                                                     pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_CONNECT_REQ cmd failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen4;
      }

      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Rx ADM_CMD_DEVICE_OPEN, issuing CONNECT_COPP cmd");
      if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                              phCalPort->unEID1.phAfePort,
                                              ELITE_CMD_CONNECT)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_COPP cmd failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen3;
      }

      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Rx ADM_CMD_DEVICE_OPEN, issuing CONNECT_MT_MX_OUT_PORT cmd");
      elite_svc_handle_t *pMtMxHandle = pAdmStatSvc->hRxMatrix;
      elite_svc_handle_t *pSvc2Connect = phCalPort->phDevCopp;

      // Configure nativity
      uint8_t unNativeModeFlags = cbNativeMode(pDevOpenCmdPayload);

      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of Rx ADM_CMD_COPP_OPEN, # ch: %lu, NatModeFlags=0x%x, Pull mode",
            phCalPort->unEID1.unNumChannels, unNativeModeFlags);

      if (ADSP_FAILED(result = Adm_SendCmdConnectMtMxOutPort(pAdmStatSvc, 0xFFFFFFFF, PULL_MODE,
                                                             pDevOpenCmdPayload->dev_num_channel_eid1,
                                                             &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                             0, pMtMxHandle, &pSvc2Connect,
                                                             &((phCalPort->mtMxPort).phMtMxOutPort),
                                                             NULL, phCalPort->unEID1.unBitWidth, 0, 0,
                                                             pDevOpenCmdPayload->sample_rate_eid1,
                                                             &(pSessionDelayParam->unCoppBufDelay),
                                                             &(pSessionDelayParam->unCoppAlgDelay),
                                                             &(pSessionDelayParam->unAFEDelay_EP1),
                                                             NULL,
                                                             ADM_NUM_BUFFERS_BETWEEN_MXAR_AND_COPP,
                                                             phCalPort->unDevicePerfMode,
                                                             unNativeModeFlags, 0, &(phCalPort->unEID1.pAfeDriftPtr),
                                                             pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_MT_MX_OUT_PORT cmd failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen3;
      }

      //Send a RUN cmd to Matrix Mixer
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Rx ADM_CMD_DEVICE_OPEN, issuing RUN_MT_MX_OUTPUT_PORT cmd");
      if (ADSP_FAILED(result = Adm_SendCmdRunMtMxPort(pAdmStatSvc,
                                                      (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                      MATRIX_MIXER_PORT_DIR_OUTPUT, pMtMxHandle,
                                                      pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_MT_MX_OUTPUT_PORT cmd failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen2;
      }

      //Send a RUN cmd to COPP
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Rx ADM_CMD_DEVICE_OPEN, issuing RUN_COPP cmd");
      if (ADSP_FAILED(result = Adm_SendCmdRunCopp(pCoppHandle, pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_COPP cmd failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen1;
      }


      //Register the PP callback info with ADM database
      if (ADSP_FAILED(result = Adm_DataBaseRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Registering PP clbk failed, result = %d", result);
        goto __bailoutCmdRxDeviceOpen1;
      }

      //Attempt to setup Device Cmd Q for Rx CoPP
      result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, FALSE, TRUE);

      if(ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to setup devicecmdQ for COPP [%u]", unCoppID);
        goto __bailoutCmdRxDeviceOpen0;
      }

    } //end of Audio Rx COPP
    else
    {
      //TX direction...
#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE before creating COPreP Svc %d",
            qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

      /* Set default params for Endpoint ID 2 media parameters */
      phCalPort->unEID2.unNumChannels    = ADM_NUM_CHANNELS_MONO;
      phCalPort->unEID2.unChannelMap[0]  = PCM_CHANNEL_C;
      phCalPort->unEID2.unSampleRate = pDevOpenCmdPayload->sample_rate_eid1;
      phCalPort->unEID2.unBitWidth       = ADM_BITS_PER_SAMPLE_16;
      phCalPort->unEID2.unBytesPerSample = ADM_BYTES_PER_SAMPLE_TWO;
      phCalPort->unEID2.unAfePortID      = pDevOpenCmdPayload->endpoint_id_2;

      if( (ADM_CMD_DEVICE_OPEN_V6 == opCode ||  ADM_CMD_DEVICE_OPEN_V7 == opCode || ADM_CMD_DEVICE_OPEN_V8 == opCode)&&
          (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != pDevOpenCmdPayload->endpoint_id_2))
      {
         phCalPort->unEID2.unSampleRate = pDevOpenCmdPayload->sample_rate_eid2;
         phCalPort->unEID2.unBytesPerSample = elite_data_get_bytes_per_sample(pDevOpenCmdPayload->bit_width_eid2);
         phCalPort->unEID2.unBitWidth = pDevOpenCmdPayload->bit_width_eid2;
         phCalPort->unEID2.unNumChannels = pDevOpenCmdPayload->dev_num_channel_eid2;

         for (uint16_t i = 0; i < pDevOpenCmdPayload->dev_num_channel_eid2; i++)
         {
             phCalPort->unEID2.unChannelMap[i] = pDevOpenCmdPayload->dev_channel_mapping_eid2[i];
         }
      }

      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing CREATE_COPP cmd, topologyID: 0x%08x",
            pDevOpenCmdPayload->topology_id);

      //Increment the Number of TX Audio COPP opened
      qurt_elite_mutex_lock(&pAdmStatSvc->admLock);
      pAdmStatSvc->unNumTxAudioCoppOpenIssued++;
      if(ADM_MAX_COPP_OPEN_CTR < pAdmStatSvc->unNumTxAudioCoppOpenIssued)
      {
        pAdmStatSvc->unNumTxAudioCoppOpenIssued = 0;
      }
      //Get a unique Log ID. PP may increment upto 16 times inside its code on every EOS and flush (flush doesnt apply for device path)
      unLogID = ADM_LOG_ID_BASE_TX + (pAdmStatSvc->unNumTxAudioCoppOpenIssued << 4);
      qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

      result = Adm_CreatePPSvc(pAdmStatSvc,
                               phCalPort,
                               pSessionDelayParam,
                               pDevOpenCmdPayload->topology_id,
                               DYNA_SVC_PP_TYPE_COPREP,
                               unLogID);
      if (ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CREATE_COPreP cmd failed, result = %d", result);
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
        return result;
      }

      //COPreP provides its handle
      pCoppHandle = phCalPort->phDevCopp;
      //COPreP thread ID. Used to destroy COPreP if cmd handler fails midway.
      coppThreadID = pCoppHandle->threadId;

      /* Specify output media format to COPreP    */
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: cfg'ing to output %d channels", pDevOpenCmdPayload->dev_num_channel_eid1);

      if (ADSP_FAILED(result = adm_config_pp_output_media_format(pCoppHandle, pRspQ,
                                                                 pDevOpenCmdPayload->dev_num_channel_eid1,
                                                                 &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                                 pDevOpenCmdPayload->sample_rate_eid1, 0)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: PP_output_media_fmt cmd failed, result = %d", result);
        goto __bailoutTXDeviceOpen4;
      }

#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE after creating COPreP Svc %d",
            qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

      //Use Matrix Handle to send Connect message to COPP...Create an Input port to Matrix in tx direction
      elite_svc_handle_t *pMtMxHandle = pAdmStatSvc->hTxMatrix;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing CONNECT_MT_MX_IN_PORT cmd, Live: %d, BM: %d",
            bIsInPortLive, bIsInPortBurstMode);

      if (ADSP_FAILED(result = Adm_SendCmdConnectMtMxInPort(pAdmStatSvc, 0xFFFFFFFF,
                                                            bIsInPortLive, bIsInPortBurstMode,
                                                            0, pMtMxHandle,
                                                            &((phCalPort->mtMxPort).phMtMxInPort),
                                                            NULL, unLogID,
                                                            NULL, phCalPort->unDevicePerfMode,
                                                            0, &(phCalPort->unEID1.pAfeDriftPtr),
                                                            FALSE, pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_MT_MX_IN_PORT cmd failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. Destroy COPreP */
        goto __bailoutTXDeviceOpen4;
      }

      //Provide handle of Matrix's Input Port to COPP and send Connect
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, " ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing CONNECT_COPreP cmd");
      if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                              &((phCalPort->mtMxPort).phMtMxInPort->portHandle),
                                              ELITE_CMD_CONNECT)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_COPreP cmd failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. Close MXAT input port */
        /* 2. Destroy COPreP */
        goto __bailoutTXDeviceOpen3;
      }

      //Num Channels book keeping
      phCalPort->unEID1.unNumChannels = (uint32_t)pDevOpenCmdPayload->dev_num_channel_eid1;

      if( phCalPort->phDevCoppEcRef && (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID) )
      {
        /*
         * For EC session connect to AFE with 1 msec framesize and 2 buffers.
         * 2 buffers is with the assumption that bg thread will be created if EC module
         * raises input threshold
         */
        unAfeNumBuffers = ADM_NORMAL_BUFFERING_BETWEEN_AFE_AND_CLIENT;
        unAfeFrameSize  = ADM_FRAME_SIZE_1MS;
      }
      else
      {
        unAfeFrameSize  = phCalPort->unCoppNumAfeFrames;
        unAfeNumBuffers = ADM_NORMAL_BUFFERING_BETWEEN_AFE_AND_CLIENT;
      }

      MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd, EP1: 0x%X, SR %lu, num ch %lu, bit-width %lu, frameSize %lx, NumAfeBuf %lu ", \
            endPointID1, pDevOpenCmdPayload->sample_rate_eid1, pDevOpenCmdPayload->dev_num_channel_eid1, phCalPort->unEID1.unBitWidth,unAfeFrameSize,unAfeNumBuffers);

      if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, endPointID1,
                                                     phCalPort->phDevCopp,
                                                     AFE_PP_OUT,
                                                     &(phCalPort->unEID1.phAfePort),
                                                     pDevOpenCmdPayload->sample_rate_eid1,
                                                     pDevOpenCmdPayload->dev_num_channel_eid1,
                                                     &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                     unAfeFrameSize,
                                                     unAfeNumBuffers,
                                                     ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                     phCalPort->unEID1.unBitWidth,
                                                     &(phCalPort->unEID1.pAfeDriftPtr),
                                                     &(pSessionDelayParam->unAFEDelay_EP1),
                                                     FALSE,
                                                     pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_CONNECT_REQ cmd failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. Disconnect from MXAT input port */
        /* 2. Close MXAT input port */
        /* 3. Destroy COPreP */
        goto __bailoutTXDeviceOpen2;
      }

      // If required (EC should be present and AFE port should be valid), request connection of audio corep block with second AFE port - for far samples
      if ( phCalPort->phDevCoppEcRef && ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
      {
        MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd (AFE EC Ref port (Rx port)), EP2: 0x%X, SR %lu, num ch %lu, bit-width %lu, frameSize %lx, NumAfeBuf %lu", \
              phCalPort->unEID2.unAfePortID, phCalPort->unEID2.unSampleRate, phCalPort->unEID2.unNumChannels, phCalPort->unEID2.unBitWidth,unAfeFrameSize,unAfeNumBuffers);

        if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                       phCalPort->phDevCoppEcRef,
                                                       AFE_PP_OUT,
                                                       &(phCalPort->unEID2.phAfePort),
                                                       phCalPort->unEID2.unSampleRate,
                                                       phCalPort->unEID2.unNumChannels,
                                                       &(phCalPort->unEID2.unChannelMap[0]),
                                                       unAfeFrameSize,
                                                       unAfeNumBuffers,
                                                       ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                       phCalPort->unEID2.unBitWidth,
                                                       &(phCalPort->unEID2.pAfeDriftPtr),
                                                       &(pSessionDelayParam->unAFEDelay_EP2),
                                                       FALSE,
                                                       pRspQ)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_CONNECT_REQ cmd (AFE EC Ref port (Rx)) failed, result = %d", result);
          /* Tear down the graph constructed thus far */
          /* 1. Disable AFE Tx port */
          /* 2. Disconnect from MXAT input port */
          /* 3. Close MXAT input port */
          /* 4. Destroy COPreP */
          /* 5. Disconnect AFE Tx port */
          goto __bailoutTXDeviceOpen1;
        }

        Adm_SendCmdCoppSetParamsDriftPtrSetup(pAdmStatSvc, unCoppID, unCoppID, pRspQ);

      }

      //Send a RUN cmd to Matrix Mixer
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing RUN_MT_MX_INPUT_PORT cmd");
      if (ADSP_FAILED(result = Adm_SendCmdRunMtMxPort(pAdmStatSvc, (phCalPort->mtMxPort).phMtMxInPort->inPortID,
                                                      MATRIX_MIXER_PORT_DIR_INPUT, pMtMxHandle,
                                                      pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_MT_MX_INPUT_PORT cmd failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. if COPreP was connected to AFE Rx (for far-end samples), disable AFE Rx port */
        /* 2. Disable AFE Tx port */
        /* 3. Disconnect from MXAT input port */
        /* 4. Close MXAT input port */
        /* 5. Destroy COPreP */
        /* 6. Disconnect AFE Tx port */
        /* 7. if COPreP was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
        goto __bailoutTXDeviceOpen0;
      }

      //Send a RUN cmd to COPreP
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Tx ADM_CMD_DEVICE_OPEN, issuing RUN_COPreP cmd");

      if (ADSP_FAILED(result = Adm_SendCmdRunCopp(pCoppHandle, pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_COPreP cmd failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. if COPrep was connected to AFE Rx (for far-end samples), disable AFE Rx port */
        /* 2. Disable AFE Tx port */
        /* 3. Disconnect from MXAT input port */
        /* 4. Close MXAT input port */
        /* 5. Destroy COPreP */
        /* 6. Disconnect AFE Tx port */
        /* 7. if COPrep was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
        goto __bailoutTXDeviceOpen0;
      }

      //Register the PP callback info with ADM database
      if (ADSP_FAILED(result = Adm_DataBaseRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Registering PP clbk failed, result = %d", result);
        goto __bailoutTXDeviceOpen0;
      }

      //Attempt to setup Device Cmd Q for Tx CoPP
      result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, FALSE, TRUE);

      if(ADSP_FAILED(result))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to setup devicecmdQ for COPP [%u]", unCoppID);
        goto __bailoutTXDeviceOpenAudioCmdQ;
      }

    } //Tx Audio Copp End

  } // End of Audio COPP

  //Send the cmd response back to the client processor.
  phCalPort->unCoppTopologyID                = pDevOpenCmdPayload->topology_id;
  phCalPort->bIsCoppInLoopBackTopology       = FALSE;
  phCalPort->bIsCoppInDeviceLoopBackTopology = FALSE;

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Opened COPP [%d]. LogID: 0x%lX", unCoppID, unLogID);

  result = AudDevMgr_RequestHwResources(pAdmStatSvc);

  return result;

  //Deregister PP CB for Audio Tx Copp
  __bailoutTXDeviceOpenAudioCmdQ:
  if(ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, calling DEREGISTER PP CB");
    if(ADSP_FAILED(result = Adm_DataBaseDeRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DEREGISTER PP CB failed, result = %d", result);
    }

  }

  __bailoutTXDeviceOpen0:

  //If COPreP is VPTX and it is connected to AFE Rx (for far-end samples), disable AFE Rx port
  if ( ((ADM_COPP_TYPE_VPTX == phCalPort->unCoppType) || ( phCalPort->phDevCoppEcRef && (ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)))
      &&  (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID) )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISABLE cmd (AFE Rx), EP2: 0x%X", phCalPort->unEID2.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                      phCalPort->unEID2.phAfePort,
                                                      ELITEMSG_CUSTOM_AFECLIENTDISABLE, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Rx) failed, result = %d", result);
    }
  }

  __bailoutTXDeviceOpen1:

  //1. Disable AFE Tx port
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISABLE cmd (AFE Tx), EP1: 0x%X", phCalPort->unEID1.unAfePortID);

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                    phCalPort->unEID1.phAfePort,
                                                    ELITEMSG_CUSTOM_AFECLIENTDISABLE, pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISABLE cmd (AFE Tx) failed, result = %d", result);
  }
  bShouldAFETxBeDisconnected = TRUE;

  __bailoutTXDeviceOpen2:

  //2. Disconnect from MXAT input port
  if (ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPreP_DISCONNECT cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                            &((phCalPort->mtMxPort).phMtMxInPort->portHandle),
                                            ELITE_CMD_DISCONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
    }
  }
  else
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing VPTx_STOP cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                            &((phCalPort->mtMxPort).phMtMxInPort->portHandle),
                                            ELITE_CMD_STOP_SERVICE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: VPTx_STOP cmd failed, result = %d", result);
    }
  }

  __bailoutTXDeviceOpen3:

  //3. Close MXAT input port
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing DISCONNECT_MT_MX_IN_PORT cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxInPort(pAdmStatSvc,
                                                           (phCalPort->mtMxPort).phMtMxInPort->inPortID,
                                                           pAdmStatSvc->hTxMatrix,
                                                           pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISCONNECT_MT_MX_IN_PORT cmd failed, result = %d", result);
  }

  __bailoutTXDeviceOpen4:

  //4. Destroy COPreP
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPreP_DESTROY cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                          NULL, ELITE_CMD_DESTROY_SERVICE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPreP_DESTROY cmd failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Waiting for COPreP to join");

  qurt_elite_thread_join(coppThreadID, &result);

  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPreP thread join failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPreP thread joined");

  //5. Disconnect from AFE Tx
  if (TRUE == bShouldAFETxBeDisconnected)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISCONNECT cmd (AFE Tx)");

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                      phCalPort->unEID1.phAfePort,
                                                      ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Tx) failed, result = %d", result);
    }

    //6. if COPreP is VPTX and it is connected to AFE Rx (for far-end samples), disconnect from AFE Rx
    if (( (ADM_COPP_TYPE_VPTX == phCalPort->unCoppType) || (phCalPort->phDevCoppEcRef && ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType))
        &&  ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
    {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISCONNECT cmd (AFE Rx)");
      if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                        phCalPort->unEID2.phAfePort,
                                                        ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                        pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Rx) failed, result = %d", result);
      }
    }
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
  return ADSP_EFAILED;

  //0: Deregister the AudPP Call Back for Audio COPP
  __bailoutCmdRxDeviceOpen0:

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, calling DEREGISTER PP CB ");

  if(ADSP_FAILED(result = Adm_DataBaseDeRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DEREGISTER PP CB failed, result = %d", result);
  }

  __bailoutCmdRxDeviceOpen1:

  //1. Disable audio matrix output port
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing DISABLE_MT_MX_OUT_PORT cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDisableMtMxOutPort(pAdmStatSvc,
                                                         (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                         pAdmStatSvc->hRxMatrix, pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISABLE_MT_MX_OUT_PORT cmd failed, result = %d", result);
  }

  __bailoutCmdRxDeviceOpen2:

  //2. Disconnect COPP from AFE Rx
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPP_DISCONNECT cmd");

  if (ADSP_FAILED(result  = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                           phCalPort->unEID1.phAfePort, ELITE_CMD_DISCONNECT)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
  }

  __bailoutCmdRxDeviceOpen3:

  //3. Disconnect AFE Rx
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISCONNECT cmd, EP1: 0x%X", phCalPort->unEID1.unAfePortID);

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                    phCalPort->unEID1.phAfePort,
                                                    ELITEMSG_CUSTOM_AFEDISCONNECT_REQ, pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd failed, result = %d", result);
  }

  __bailoutCmdRxDeviceOpen4:

  //4. Destroy COPP
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPP_DESTROY cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                          NULL, ELITE_CMD_DESTROY_SERVICE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP_DESTROY cmd failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Waiting for COPP to join");

  qurt_elite_thread_join(coppThreadID, &result);

  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP thread join failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP thread joined");

  //5. Disconnect audio matrix output port only if it was connected to COPP */
  if ((phCalPort->mtMxPort).phMtMxOutPort)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing DISCONNECT_MT_MX_OUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxOutPort(pAdmStatSvc,
                                                              (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                              pAdmStatSvc->hRxMatrix,
                                                              pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISCONNECT_MT_MX_OUT_PORT cmd failed, result = %d", result);
    }
    (phCalPort->mtMxPort).phMtMxOutPort = NULL;
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
  return ADSP_EFAILED;
}

static void Adm_PrintChannelType(const uint8_t *ch_map, int32_t num_channels)
{
  uint32_t *ch_map_word;
  QURT_ELITE_ALIGN(uint8_t ch_map_local[ADM_NUM_CHANNELS_THIRTY_TWO], 4); // align by 4
  memset(ch_map_local, 0, sizeof(ch_map_local));
  ch_map_word = (uint32_t *)ch_map_local;
  for(int32_t i = 0; i < num_channels; i++)
  {
    ch_map_local[i] = ch_map[i];
  }

   MSG_9(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
         "ADM: ADM_CMD_DEVICE_OPEN, dev_num_ch = %d channel mapping (4 channel maps per value) 0x%lx,0x%lx,0x%lx,0x%lx,0x%lx,0x%lx,0x%lx,0x%lx",
         num_channels, ch_map_word[0],
         ch_map_word[1],ch_map_word[2],
         ch_map_word[3],ch_map_word[4],
         ch_map_word[5],ch_map_word[6],
         ch_map_word[7]);

  return;
}


static  ADSPResult Adm_AprMatrixRampGainsCmdHandler_v5 (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_matrix_ramp_gains_v5_t         *pIncomingAPRPayload;
  adm_session_copp_gain_v5_t             *pSessionCOPPGain;
  ADSPResult                       result = ADSP_EOK;
  uint16_t                            *pSnIDToPortIDMap;
  AdmCalPort_Type                     *phCalPort;
  uint16_t                             unIndex = ADM_INVALID_INDEX, i, extractedSessionID = 0, extractedStreamID = 0;
  adm_client_type_t                    eClient = eASM_TYPE;

  pIncomingAPRPayload = (adm_cmd_matrix_ramp_gains_v5_t*)elite_apr_if_get_payload_ptr(pPkt);
  adm_session_copp_gain_v5_t *pTmp2 = (adm_session_copp_gain_v5_t*) (pIncomingAPRPayload + 1);
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains v5 [matrix ID, num gains] = [%lu, %d]", pIncomingAPRPayload->matrix_id, pIncomingAPRPayload->num_gains);

  //Audio Matrix understands only port ID's, so ADM must translate session ID's and COPP ID's  into port ID's
  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToRxMtMxInPortIDMap[0]);
  }
  else if (ADM_MATRIX_ID_AUDIO_TX == pIncomingAPRPayload->matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToTxMtMxOutPortIDMap[0]);
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGains Rcvd invalid Matrix ID [%lu]",pIncomingAPRPayload->matrix_id);
    result = ADSP_EBADPARAM;
    goto __bailoutMatrixRampGains;
  }

  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    for (i = 0; i < pIncomingAPRPayload->num_gains; i++)
    {
      pSessionCOPPGain = pTmp2;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID: 0x%hX, COPP ID: %d", pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      //Extract the session and stream ID from the incoming ID and validate them.
      extractedSessionID = (0xff00 & pSessionCOPPGain->session_id) >> 8;
      extractedStreamID  = (0x00ff & pSessionCOPPGain->session_id);

      if(
          (0 == pSessionCOPPGain->session_id) ||
          ((pSessionCOPPGain->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
              ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                  (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
      )
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX]", pSessionCOPPGain->session_id);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //Map the incoming  SSID to Index
      unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, ADM_RX_DIR, pSessionCOPPGain->session_id, eClient);
      if(ADM_INVALID_INDEX == unIndex)
      {
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //If incoming SSID is legacy, map it to contemporary SSID
      pSessionCOPPGain->session_id = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Contemporary Session ID: 0x%hX, COPP ID: %d",
            pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      //Check if stream session is a direct connection type
      AdmStreamSessionInfo_Type *pSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
      if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
          (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
          (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains is not supported in LLNP/ULL Session ID: 0x%hX", pSessionCOPPGain->session_id);
        result = ADSP_EUNSUPPORTED;
        goto __bailoutMatrixRampGains;
      }

      //Session->Port translation
      pSessionCOPPGain->session_id = pSnIDToPortIDMap[unIndex];
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID => MXAR i/p port ID %d", pSessionCOPPGain->session_id);
      if (ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS != pSessionCOPPGain->copp_id)
      {
        if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pSessionCOPPGain->copp_id,(uint16_t)pIncomingAPRPayload->matrix_id)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid/inactive COPP ID [%d]", pSessionCOPPGain->copp_id);
          result = ADSP_EBADPARAM;
          goto __bailoutMatrixRampGains;
        }
        phCalPort = &pAdmStatSvc->deviceCalPort[pSessionCOPPGain->copp_id];
        pSessionCOPPGain->copp_id = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;

        //Check if Ramp Gain command is issued on Device Loopback COPP
        if ( TRUE == phCalPort->bIsCoppInDeviceLoopBackTopology )
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: RampGains cmd is not supported on Device Loopback COPP [%lu]. Cmd Failed",pSessionCOPPGain->copp_id);
          result = ADSP_EUNSUPPORTED;
          goto __bailoutMatrixRampGains;
        }
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains COPP ID => MXAR o/p port ID %d", pSessionCOPPGain->copp_id);
      }

      //The next Session COPP Gain Node will begin from here.
      pTmp2++;
    }
    if (ADSP_FAILED(result = Adm_SendCmdMatrixRampGains(pAdmStatSvc, pPkt, pAdmStatSvc->hRxMatrix)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMatrixRampGains failed, result = %d", result);
      goto __bailoutMatrixRampGains;
    }
  }
  else
  {
    for (i = 0; i < pIncomingAPRPayload->num_gains; i++)
    {
      pSessionCOPPGain = pTmp2;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID: 0x%hX, COPP ID: %d", pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      //Extract the session and stream ID from the incoming ID and validate them.
      uint16_t extractedSessionID = 0, extractedStreamID = 0;
      extractedSessionID = (0xff00 & pSessionCOPPGain->session_id) >> 8;
      extractedStreamID  = (0x00ff & pSessionCOPPGain->session_id);

      if(
          (0 == pSessionCOPPGain->session_id) ||
          ((pSessionCOPPGain->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
              ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                  (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
      )
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX]", pSessionCOPPGain->session_id);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //Map the incoming  SSID to Index
      unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, ADM_TX_DIR, pSessionCOPPGain->session_id, eClient);
      if(ADM_INVALID_INDEX == unIndex)
      {
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //If incoming SSID is legacy, map it to contemporary SSID
      pSessionCOPPGain->session_id = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Contemporary Session ID: 0x%hX, COPP ID: %d",
            pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      //Check if stream session is LLNP
      AdmStreamSessionInfo_Type *pSessionInfo = &(pAdmStatSvc->txStreamSessionInfo[unIndex]);
      if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains is not supported in ULL Session ID: 0x%hX", pSessionCOPPGain->session_id);
        result = ADSP_EUNSUPPORTED;
        goto __bailoutMatrixRampGains;
      }

      //Session->Port translation
      pSessionCOPPGain->session_id = pSnIDToPortIDMap[unIndex];
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID => MXAT o/p port ID %d", pSessionCOPPGain->session_id);
      if (ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS != pSessionCOPPGain->copp_id)
      {
        if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pSessionCOPPGain->copp_id,(uint16_t)pIncomingAPRPayload->matrix_id)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGains Rcvd invalid/inactive COPP ID [%d]", pSessionCOPPGain->copp_id);
          result = ADSP_EBADPARAM;
          goto __bailoutMatrixRampGains;
        }
        phCalPort = &pAdmStatSvc->deviceCalPort[pSessionCOPPGain->copp_id];
        pSessionCOPPGain->copp_id = (phCalPort->mtMxPort).phMtMxInPort->inPortID;
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains COPP ID => MXAT i/p port ID %d", pSessionCOPPGain->copp_id);
      }

      //The next Session COPP Gain Node will begin from here.
      pTmp2++;
    }
    if (ADSP_FAILED(result = Adm_SendCmdMatrixRampGains(pAdmStatSvc, pPkt, pAdmStatSvc->hTxMatrix)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMatrixRampGains failed, result = %d", result);
      goto __bailoutMatrixRampGains;
    }
  }

  __bailoutMatrixRampGains:
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static  ADSPResult Adm_AprMatrixRampGainsCmdHandler_v6 (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_matrix_ramp_gains_v6_t         *pIncomingAPRPayload;
  adm_session_copp_gain_v6_t             *pSessionCOPPGain;
  ADSPResult                       result = ADSP_EOK;
  uint16_t                            *pSnIDToPortIDMap;
  AdmCalPort_Type                     *phCalPort;
  uint16_t                             unIndex = ADM_INVALID_INDEX, i, extractedSessionID = 0, extractedStreamID = 0;
  adm_client_type_t     eClient = eASM_TYPE;

  uint8_t *pSrc = NULL, *pDest = NULL;

  pIncomingAPRPayload = (adm_cmd_matrix_ramp_gains_v6_t*)elite_apr_if_get_payload_ptr(pPkt);
  adm_session_copp_gain_v6_t *pTmp2 = (adm_session_copp_gain_v6_t*) (pIncomingAPRPayload + 1);
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains v6 [matrix ID, num gains] = [%lu, %d]", pIncomingAPRPayload->matrix_id, pIncomingAPRPayload->num_gains);

  pSrc = (uint8_t*) (pIncomingAPRPayload + 1);
  pDest = pSrc;

  //Audio Matrix understands only port ID's, so ADM must translate session ID's and COPP ID's  into port ID's
  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToRxMtMxInPortIDMap[0]);
  }
  else if (ADM_MATRIX_ID_AUDIO_TX == pIncomingAPRPayload->matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToTxMtMxOutPortIDMap[0]);
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGains Rcvd invalid Matrix ID [%lu]",pIncomingAPRPayload->matrix_id);
    result = ADSP_EBADPARAM;
    goto __bailoutMatrixRampGains;
  }

  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    for (i = 0; i < pIncomingAPRPayload->num_gains; i++)
    {
      pSessionCOPPGain = pTmp2;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID: 0x%hX, COPP ID: %d", pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      eClient = (adm_client_type_t)pSessionCOPPGain->stream_type;
      if(ADM_CLIENT_NUM_ZERO < eClient)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGain cmd Rcvd invalid stream type value on RX path:%d", eClient);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //Extract the session and stream ID from the incoming ID and validate them.
      extractedSessionID = (0xff00 & pSessionCOPPGain->session_id) >> 8;
      extractedStreamID  = (0x00ff & pSessionCOPPGain->session_id);

      if(
          (0 == pSessionCOPPGain->session_id) ||
          ((pSessionCOPPGain->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
              ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                  (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
      )
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX] for ASM session", pSessionCOPPGain->session_id);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //Map the incoming  SSID to Index
      unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, ADM_RX_DIR, pSessionCOPPGain->session_id, eClient);
      if(ADM_INVALID_INDEX == unIndex)
      {
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //If incoming SSID is legacy, map it to contemporary SSID
      pSessionCOPPGain->session_id = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Contemporary Session ID: 0x%hX, COPP ID: %d",
            pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      //Check if stream session is a direct connection type
      AdmStreamSessionInfo_Type *pSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
      if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
          (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
          (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains is not supported in LLNP/ULL Session ID: 0x%hX", pSessionCOPPGain->session_id);
        result = ADSP_EUNSUPPORTED;
        goto __bailoutMatrixRampGains;
      }

      //Session->Port translation
      pSessionCOPPGain->session_id = pSnIDToPortIDMap[unIndex];
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID => MXAR i/p port ID %d", pSessionCOPPGain->session_id);
      if (ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS != pSessionCOPPGain->copp_id)
      {
        if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pSessionCOPPGain->copp_id, (uint16_t)pIncomingAPRPayload->matrix_id)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid/inactive COPP ID [%d]", pSessionCOPPGain->copp_id);
          result = ADSP_EBADPARAM;
          goto __bailoutMatrixRampGains;
        }
        phCalPort = &pAdmStatSvc->deviceCalPort[pSessionCOPPGain->copp_id];
        pSessionCOPPGain->copp_id = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;

        //Check if Ramp Gain command is issued on Device Loopback COPP
        if ( TRUE == phCalPort->bIsCoppInDeviceLoopBackTopology )
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: RampGains cmd is not supported on Device Loopback COPP [%lu]. Cmd Failed",pSessionCOPPGain->copp_id);
          result = ADSP_EUNSUPPORTED;
          goto __bailoutMatrixRampGains;
        }
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains COPP ID => MXAR o/p port ID %d", pSessionCOPPGain->copp_id);
      }

      //The next Session COPP Gain Node will begin from here.
      pTmp2++;

      /*Since V6 payload is super set of V5 payload data and in further matrix calls processing
            required only V5 payload data to process. So modified the V6 payload to the V5 compatible
            payload structure to avoid many changes to handle both V5 and V6 commands processing*/
      memscpy(pDest, sizeof(adm_session_copp_gain_v5_t), pSrc, sizeof(adm_session_copp_gain_v5_t) );
      pSrc+= sizeof(adm_session_copp_gain_v6_t);
      pDest+= sizeof(adm_session_copp_gain_v5_t);

    }

    if (ADSP_FAILED(result = Adm_SendCmdMatrixRampGains(pAdmStatSvc, pPkt, pAdmStatSvc->hRxMatrix)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMatrixRampGains failed, result = %d", result);
      goto __bailoutMatrixRampGains;
    }
  }
  else
  {
    for (i = 0; i < pIncomingAPRPayload->num_gains; i++)
    {
      pSessionCOPPGain = pTmp2;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID: 0x%hX, COPP ID: %d", pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      eClient = (adm_client_type_t)pSessionCOPPGain->stream_type;
      if(ADM_CLIENT_NUM_ONE < eClient)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGain cmd Rcvd invalid stream type value on Tx path:%d", eClient);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //Extract the session and stream ID from the incoming ID and validate them.
      uint16_t extractedSessionID = 0, extractedStreamID = 0;
      extractedSessionID = (0xff00 & pSessionCOPPGain->session_id) >> 8;
      extractedStreamID  = (0x00ff & pSessionCOPPGain->session_id);

      if (eASM_TYPE == eClient)
      {
        if(
            (0 == pSessionCOPPGain->session_id) ||
            ((pSessionCOPPGain->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
                ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                    (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
        )
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX]for ASM session", pSessionCOPPGain->session_id);
          result = ADSP_EBADPARAM;
          goto __bailoutMatrixRampGains;
        }
      }

      if (eLSM_TYPE == eClient)
      {
        if (0 == pSessionCOPPGain->session_id || LSM_MAX_NUM_SESSIONS < pSessionCOPPGain->session_id)
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX] for LSM session", pSessionCOPPGain->session_id);
          result = ADSP_EBADPARAM;
          goto __bailoutMatrixRampGains;
        }
      }
      //Map the incoming  SSID to Index
      unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, ADM_TX_DIR, pSessionCOPPGain->session_id, eClient);
      if(ADM_INVALID_INDEX == unIndex)
      {
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixRampGains;
      }

      //If incoming SSID is legacy, map it to contemporary SSID
      pSessionCOPPGain->session_id = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Contemporary Session ID: 0x%hX, COPP ID: %d",
            pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

      //Check if stream session is LLNP
      AdmStreamSessionInfo_Type *pSessionInfo = &(pAdmStatSvc->txStreamSessionInfo[unIndex]);
      if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains is not supported in ULL Session ID: 0x%hX", pSessionCOPPGain->session_id);
        result = ADSP_EUNSUPPORTED;
        goto __bailoutMatrixRampGains;
      }

      //Session->Port translation
      pSessionCOPPGain->session_id = pSnIDToPortIDMap[unIndex];
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID => MXAT o/p port ID %d", pSessionCOPPGain->session_id);
      if (ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS != pSessionCOPPGain->copp_id)
      {
        if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pSessionCOPPGain->copp_id,(uint16_t)pIncomingAPRPayload->matrix_id)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGains Rcvd invalid/inactive COPP ID [%d]", pSessionCOPPGain->copp_id);
          result = ADSP_EBADPARAM;
          goto __bailoutMatrixRampGains;
        }
        phCalPort = &pAdmStatSvc->deviceCalPort[pSessionCOPPGain->copp_id];
        pSessionCOPPGain->copp_id = (phCalPort->mtMxPort).phMtMxInPort->inPortID;
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains COPP ID => MXAT i/p port ID %d", pSessionCOPPGain->copp_id);
      }

      //The next Session COPP Gain Node will begin from here.
      pTmp2++;

      /*Since V6 payload is super set of V5 payload data and in further matrix calls processing
            required only V5 payload data to process. So modified the V6 payload to the V5 compatible
            payload structure to avoid many changes to handle both V5 and V6 commands processing*/
      memscpy(pDest, sizeof(adm_session_copp_gain_v5_t), pSrc, sizeof(adm_session_copp_gain_v5_t) );
      pSrc+= sizeof(adm_session_copp_gain_v6_t);
      pDest+= sizeof(adm_session_copp_gain_v5_t);

    }

    if (ADSP_FAILED(result = Adm_SendCmdMatrixRampGains(pAdmStatSvc, pPkt, pAdmStatSvc->hTxMatrix)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMatrixRampGains failed, result = %d", result);
      goto __bailoutMatrixRampGains;
    }
  }

  __bailoutMatrixRampGains:
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}


static  ADSPResult Adm_AprMatrixRampGainsCmdHandler_v7 (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
    AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
    adm_cmd_matrix_ramp_gains_v7_t         *pIncomingAPRPayload;
    adm_session_copp_gain_v7_t             *pSessionCOPPGain;
    ADSPResult                       result = ADSP_EOK;
    uint16_t                            *pSnIDToPortIDMap;
    AdmCalPort_Type                     *phCalPort;
    uint16_t                             unIndex = ADM_INVALID_INDEX, i, extractedSessionID = 0, extractedStreamID = 0;
    adm_client_type_t     eClient = eASM_TYPE;
    uint32_t gain_size = 0;

    pIncomingAPRPayload = (adm_cmd_matrix_ramp_gains_v7_t*)elite_apr_if_get_payload_ptr(pPkt);
    adm_session_copp_gain_v7_t *pTmp2 = (adm_session_copp_gain_v7_t*) (pIncomingAPRPayload + 1);
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains v7 [matrix ID, num gains] = [%lu, %d]", pIncomingAPRPayload->matrix_id, pIncomingAPRPayload->num_gains);

    //Audio Matrix understands only port ID's, so ADM must translate session ID's and COPP ID's  into port ID's
    if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
    {
       pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToRxMtMxInPortIDMap[0]);
    }
    else if (ADM_MATRIX_ID_AUDIO_TX == pIncomingAPRPayload->matrix_id)
    {
       pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToTxMtMxOutPortIDMap[0]);
    }
    else
    {
       MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGains Rcvd invalid Matrix ID [%lu]",pIncomingAPRPayload->matrix_id);
       result = ADSP_EBADPARAM;
       goto __bailoutMatrixRampGains;
    }

    if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
    {
       for (i = 0; i < pIncomingAPRPayload->num_gains; i++)
       {
          pSessionCOPPGain = pTmp2;
          MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID: 0x%hX, COPP ID: %d", pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

          eClient = (adm_client_type_t)pSessionCOPPGain->stream_type;
          if(ADM_CLIENT_NUM_ZERO < eClient)
          {
             MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGain cmd Rcvd invalid stream type value on RX path:%d", eClient);
             result = ADSP_EBADPARAM;
             goto __bailoutMatrixRampGains;
          }

          //Extract the session and stream ID from the incoming ID and validate them.
          extractedSessionID = (0xff00 & pSessionCOPPGain->session_id) >> 8;
          extractedStreamID  = (0x00ff & pSessionCOPPGain->session_id);

          if((0 == pSessionCOPPGain->session_id) ||
            ((pSessionCOPPGain->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
            ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
            (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID))))
            {
               MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX] for ASM session", pSessionCOPPGain->session_id);
               result = ADSP_EBADPARAM;
               goto __bailoutMatrixRampGains;
            }

            //Map the incoming  SSID to Index
            unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, ADM_RX_DIR, pSessionCOPPGain->session_id, eClient);
            if(ADM_INVALID_INDEX == unIndex)
            {
               result = ADSP_EBADPARAM;
               goto __bailoutMatrixRampGains;
            }

            //If incoming SSID is legacy, map it to contemporary SSID
            pSessionCOPPGain->session_id = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Contemporary Session ID: 0x%hX, COPP ID: %d",
                pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

            //Check if stream session is a direct connection type
            AdmStreamSessionInfo_Type *pSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
            if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
             (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
             (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode))
            {
               MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains is not supported in LLNP/ULL Session ID: 0x%hX", pSessionCOPPGain->session_id);
               result = ADSP_EUNSUPPORTED;
               goto __bailoutMatrixRampGains;
            }

            //Session->Port translation
            pSessionCOPPGain->session_id = pSnIDToPortIDMap[unIndex];
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID => MXAR i/p port ID %d", pSessionCOPPGain->session_id);
            if (ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS != pSessionCOPPGain->copp_id)
            {
               if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pSessionCOPPGain->copp_id, (uint16_t)pIncomingAPRPayload->matrix_id)))
               {
                  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid/inactive COPP ID [%d]", pSessionCOPPGain->copp_id);
                  result = ADSP_EBADPARAM;
                  goto __bailoutMatrixRampGains;
               }
               phCalPort = &pAdmStatSvc->deviceCalPort[pSessionCOPPGain->copp_id];
               pSessionCOPPGain->copp_id = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;

               //Check if Ramp Gain command is issued on Device Loopback COPP
               if ( TRUE == phCalPort->bIsCoppInDeviceLoopBackTopology )
               {
                  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: RampGains cmd is not supported on Device Loopback COPP [%lu]. Cmd Failed",pSessionCOPPGain->copp_id);
                  result = ADSP_EUNSUPPORTED;
                  goto __bailoutMatrixRampGains;
               }
               MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains COPP ID => MXAR o/p port ID %d", pSessionCOPPGain->copp_id);
            }

            //The next Session COPP Gain Node will begin from here.
            pTmp2++;

            gain_size = pSessionCOPPGain->num_channels * sizeof(adm_session_copp_gain_per_ch_t);
            gain_size = AUD_ROUNDTO4(gain_size);

            pTmp2 = (adm_session_copp_gain_v7_t *)(((int8_t *)pTmp2) + gain_size);
        }

        if (ADSP_FAILED(result = Adm_SendCmdMatrixRampGains(pAdmStatSvc, pPkt, pAdmStatSvc->hRxMatrix)))
        {
           MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMatrixRampGains failed, result = %d", result);
           goto __bailoutMatrixRampGains;
        }
    }
    else
    {
        for (i = 0; i < pIncomingAPRPayload->num_gains; i++)
        {
            pSessionCOPPGain = pTmp2;
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID: 0x%hX, COPP ID: %d", pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

            eClient = (adm_client_type_t)pSessionCOPPGain->stream_type;
            if(ADM_CLIENT_NUM_ONE < eClient)
            {
                MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGain cmd Rcvd invalid stream type value on Tx path:%d", eClient);
                result = ADSP_EBADPARAM;
                goto __bailoutMatrixRampGains;
            }

            //Extract the session and stream ID from the incoming ID and validate them.
            uint16_t extractedSessionID = 0, extractedStreamID = 0;
            extractedSessionID = (0xff00 & pSessionCOPPGain->session_id) >> 8;
            extractedStreamID  = (0x00ff & pSessionCOPPGain->session_id);

            if (eASM_TYPE == eClient)
            {
                if((0 == pSessionCOPPGain->session_id) ||
                  ((pSessionCOPPGain->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
                  ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                  (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID))))
                {
                    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX]for ASM session", pSessionCOPPGain->session_id);
                    result = ADSP_EBADPARAM;
                    goto __bailoutMatrixRampGains;
                }
            }

            if (eLSM_TYPE == eClient)
            {
                if (0 == pSessionCOPPGain->session_id || LSM_MAX_NUM_SESSIONS < pSessionCOPPGain->session_id)
                {
                    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains Rcvd invalid SessionID [0x%hX] for LSM session", pSessionCOPPGain->session_id);
                    result = ADSP_EBADPARAM;
                    goto __bailoutMatrixRampGains;
                }
            }
            //Map the incoming  SSID to Index
            unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, ADM_TX_DIR, pSessionCOPPGain->session_id, eClient);
            if(ADM_INVALID_INDEX == unIndex)
            {
                result = ADSP_EBADPARAM;
                goto __bailoutMatrixRampGains;
            }

            //If incoming SSID is legacy, map it to contemporary SSID
            pSessionCOPPGain->session_id = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Contemporary Session ID: 0x%hX, COPP ID: %d",
                pSessionCOPPGain->session_id, pSessionCOPPGain->copp_id);

            //Check if stream session is LLNP
            AdmStreamSessionInfo_Type *pSessionInfo = &(pAdmStatSvc->txStreamSessionInfo[unIndex]);
            if (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode)
            {
               MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error RampGains is not supported in ULL Session ID: 0x%hX", pSessionCOPPGain->session_id);
               result = ADSP_EUNSUPPORTED;
               goto __bailoutMatrixRampGains;
            }

            //Session->Port translation
            pSessionCOPPGain->session_id = pSnIDToPortIDMap[unIndex];
            MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains Session ID => MXAT o/p port ID %d", pSessionCOPPGain->session_id);
            if (ADM_CMD_MATRIX_RAMP_GAINS_COPP_ID_ALL_CONNECTED_COPPS != pSessionCOPPGain->copp_id)
            {
               if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pSessionCOPPGain->copp_id,(uint16_t)pIncomingAPRPayload->matrix_id)))
               {
                   MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RampGains Rcvd invalid/inactive COPP ID [%d]", pSessionCOPPGain->copp_id);
                   result = ADSP_EBADPARAM;
                   goto __bailoutMatrixRampGains;
               }
               phCalPort = &pAdmStatSvc->deviceCalPort[pSessionCOPPGain->copp_id];
               pSessionCOPPGain->copp_id = (phCalPort->mtMxPort).phMtMxInPort->inPortID;
               MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RampGains COPP ID => MXAT i/p port ID %d", pSessionCOPPGain->copp_id);
            }

            //The next Session COPP Gain Node will begin from here.
            pTmp2++;

            gain_size = pSessionCOPPGain->num_channels * sizeof(adm_session_copp_gain_per_ch_t);
            gain_size = AUD_ROUNDTO4(gain_size);

            pTmp2 = (adm_session_copp_gain_v7_t *)(((int8_t *)pTmp2) + gain_size);

        }

        if (ADSP_FAILED(result = Adm_SendCmdMatrixRampGains(pAdmStatSvc, pPkt, pAdmStatSvc->hTxMatrix)))
        {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMatrixRampGains failed, result = %d", result);
            goto __bailoutMatrixRampGains;
        }
    }

    __bailoutMatrixRampGains:
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
}

ADSPResult Adm_CheckCoppValidity(AdmStatSvc_InfoType *pAudStatAdmSvc, uint16_t unCoppID, uint16_t unDirection)
{
  AdmCalPort_Type   *phCalPort;

  if(ADM_INVALID_DIRECTION == unDirection)
  {
    if (ADM_MAX_COPPS <= unCoppID)
    {
      return ADSP_EBADPARAM;
    }
  }
  else if(ADM_RX_DIR == unDirection)
  {
    if((ADM_RX_COPP_ID_START > unCoppID) || (ADM_RX_COPP_ID_END < unCoppID))
    {
      return ADSP_EBADPARAM;
    }

  }
  else if(ADM_TX_DIR == unDirection)
  {
    if((ADM_TX_COPP_ID_START > unCoppID) || (ADM_TX_COPP_ID_END < unCoppID))
    {
      return ADSP_EBADPARAM;
    }
  }
  else
  {
    return ADSP_EBADPARAM;
  }

  phCalPort = &pAudStatAdmSvc->deviceCalPort[unCoppID];

  if (ADM_COPP_STATUS_INACTIVE == phCalPort->unCoppStatus)
  {
    return ADSP_ENOTREADY;
  }
  else if(ADM_COPP_STATUS_INIT == phCalPort->unCoppStatus || ADM_COPP_STATUS_DEINIT == phCalPort->unCoppStatus)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: device [%d] is in Init/Deinit State [%d]",unCoppID, phCalPort->unCoppStatus);
    return ADSP_EBADPARAM;
  }

  return ADSP_EOK;
}

static ADSPResult Adm_CheckCompDevIDValidity(AdmStatSvc_InfoType *pAudStatAdmSvc, uint16_t unDevID)
{
  if ((unDevID < ADM_COMPRESSED_MIN) || (unDevID > ADM_COMPRESSED_MAX))
  {
    return ADSP_EBADPARAM;
  }

  ComprCoppInfo_t *pComprCopp = NULL;
  uint16_t offset = 0;

  if(ADM_COMPRESSED_MIN_RX <= unDevID && ADM_COMPRESSED_MAX_RX >= unDevID)
  {
    offset = unDevID - ADM_COMPRESSED_MIN_RX;
    pComprCopp = (&(pAudStatAdmSvc->rxStRtrParams.compr_copp_info[offset]));
  }
  else if(ADM_COMPRESSED_MIN_TX <= unDevID && ADM_COMPRESSED_MAX_TX >= unDevID)
  {
    offset = (unDevID - ADM_COMPRESSED_MIN_TX);
    pComprCopp = (&(pAudStatAdmSvc->txStRtrParams.compr_copp_info[offset]));
  }

  if(pComprCopp)
  {
    if(ADM_COPP_STATUS_INACTIVE == pComprCopp->unCoppStatus)
    {
      return ADSP_ENOTREADY;
    }
    else if((ADM_COPP_STATUS_INIT == pComprCopp->unCoppStatus) || (ADM_COPP_STATUS_DEINIT == pComprCopp->unCoppStatus))
    {
      return ADSP_EBADPARAM;
    }
    else
    {
      return ADSP_EOK;
    }
  }
  return ADSP_EBADPARAM;
}

void Adm_ResetSessionMappingMask(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t sessionID, uint32_t matrixID, adm_client_type_t eClient)
{
  uint16_t                unCoppID;
  AdmCalPort_Type         *phCalPort;
  uint32_t                *pSessionMappingMask;



  uint16_t                unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)matrixID, sessionID, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    return;
  }
  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  if((ADM_MATRIX_ID_AUDIO_RX == matrixID) && (eASM_TYPE == eClient))
  {
    pSessionMappingMask = &(pAdmStatSvc->rxsessionMappingMask[unIndex]);
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RSMM Entr Rx: Mapping mask: %lu", *pSessionMappingMask);

    while(*pSessionMappingMask)
    {
      uint32_t unBitPosition = Q6_R_ct0_R(*pSessionMappingMask);
      *pSessionMappingMask ^= 1LL << unBitPosition;
      unCoppID = unBitPosition;
      phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

      phCalPort->unNumConnectedSessionsRx--;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RSMM Rx: Dec CoppID: %d # conn. sessions to %d",
            unCoppID, phCalPort->unNumConnectedSessionsRx);

    }

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RSMM Exit Rx: Mapping mask: %lu", *pSessionMappingMask);
  }
  else if(ADM_MATRIX_ID_AUDIO_TX == matrixID)
  {
    pSessionMappingMask = &(pAdmStatSvc->txsessionMappingMask[unIndex]);
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RSMM Entr Tx: Mapping mask: %lu", *pSessionMappingMask);

    while(*pSessionMappingMask)
    {
      uint32_t unBitPosition = Q6_R_ct0_R(*pSessionMappingMask);
      *pSessionMappingMask ^= 1LL << unBitPosition;
      unCoppID = unBitPosition;
      phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

      phCalPort->unNumConnectedSessionsTx--;
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RSMM Tx: Dec CoppID: %d # conn. sessions to %d",
            unCoppID, phCalPort->unNumConnectedSessionsTx);
    }

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RSMM Exit Tx: Mapping mask: %lu", *pSessionMappingMask);
  }
  else
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Invalid Direction: %lu or Client Type %d provided", matrixID, eClient);
  }
  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
}

void Adm_UpdateSessionMappingMask(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t sessionID, uint16_t unCoppID, uint32_t matrixID, adm_client_type_t eClient)
{
  AdmCalPort_Type         *phCalPort;
  uint32_t  *pSessionMappingMask;

  uint16_t                unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)matrixID, sessionID, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    return;
  }

  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  if((ADM_MATRIX_ID_AUDIO_RX == matrixID) && (eASM_TYPE == eClient))
  {
    pSessionMappingMask = &(pAdmStatSvc->rxsessionMappingMask[unIndex]);

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_USMM Entr Rx: Mapping mask: %lu",*pSessionMappingMask);

    *pSessionMappingMask |= (1LL << unCoppID);

    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

    phCalPort->unNumConnectedSessionsRx++;
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_USMM Rx: Inc coppID: %d # conn. sessions to %d",
          unCoppID, phCalPort->unNumConnectedSessionsRx);

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_USMM Exit Rx: Mapping mask: %lu", *pSessionMappingMask);
  }
  else if(ADM_MATRIX_ID_AUDIO_TX == matrixID)
  {
    pSessionMappingMask = &(pAdmStatSvc->txsessionMappingMask[unIndex]);

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_USMM Entr Tx: Mapping mask: %lu",*pSessionMappingMask);

    *pSessionMappingMask |= (1LL << unCoppID);

    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

    phCalPort->unNumConnectedSessionsTx++;
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_USMM Tx: Inc coppID: %d # conn. sessions to %d",
          unCoppID, phCalPort->unNumConnectedSessionsTx);

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_USMM Exit Tx: Mapping mask: %lu", *pSessionMappingMask);
  }
  else
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Invalid Direction: %lu or Client Type %d provided", matrixID, eClient);
  }
  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
}

void Adm_RemoveCoppIDFromSessionMappingMask(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t unCoppID, uint16_t unCoppDirection)
{
  uint32_t  *pSessionMappingMask;
  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  if(RX_DIR == unCoppDirection)
  {
    pSessionMappingMask = &(pAdmStatSvc->rxsessionMappingMask[0]);
  }
  else
  {
    pSessionMappingMask = &(pAdmStatSvc->txsessionMappingMask[0]);
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Removing COPP ID: %d from session mapping mask",unCoppID);

  for (uint16_t unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    *pSessionMappingMask &= ~(1LL << unCoppID);
    pSessionMappingMask++;
  }

  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
  return;
}


static uint16_t Adm_CalculateCoppID(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t direction)
{
  uint16_t    index,device_id_start,device_id_end;
  ComprCoppInfo_t *pComprCoppInfo = NULL;

  uint16_t unCoppID = ADM_COPP_ID_INVALID;
  uint16_t offset = 0;

  switch (direction)
  {
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP:
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_DEVICE_LOOPBACK:
    {
      device_id_start = ADM_RX_COPP_ID_START;
      device_id_end   = ADM_RX_COPP_ID_END;
      break;
    }
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP:
    {
      device_id_start = ADM_TX_COPP_ID_START;
      device_id_end   = ADM_TX_COPP_ID_END;
      break;
    }
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX:
    {
      device_id_start = 0;
      device_id_end   = ADM_COMPRESSED_MAX_RX - ADM_COMPRESSED_MIN_RX;
      offset          = ADM_COMPRESSED_MIN_RX;
      pComprCoppInfo  = &pAdmStatSvc->rxStRtrParams.compr_copp_info[0];
      break;
    }
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX:
    {
      device_id_start = 0;
      device_id_end   = ADM_COMPRESSED_MAX_TX - ADM_COMPRESSED_MIN_TX;
      offset          = ADM_COMPRESSED_MIN_TX;
      pComprCoppInfo  = &pAdmStatSvc->txStRtrParams.compr_copp_info[0];
      break;
    }
    default:
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Adm_CalculateCoppID: Invalid Mode =%d received ",direction);
      return unCoppID;
    }
  }

  if(pComprCoppInfo)
  {
    for (index = device_id_start; index <= device_id_end; index++,pComprCoppInfo++)
    {
      if(ADM_COPP_STATUS_INACTIVE == pComprCoppInfo->unCoppStatus)
      {
        unCoppID = index + offset;
        break;
      }
    }

  }
  else
  {
    for (index = device_id_start; index <= device_id_end; index++)
    {
      if(ADM_COPP_STATUS_INACTIVE == pAdmStatSvc->deviceCalPort[index].unCoppStatus)
      {
        unCoppID = index;
        break;
      }
    }
  }

  return unCoppID;
}

static  ADSPResult Adm_AprMatrixMuteCmdHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_matrix_mute_v5_t        *pIncomingAPRPayload;
  ADSPResult                                 result = ADSP_EOK;
  uint16_t                                      *pSnIDToPortIDMap;
  AdmCalPort_Type                        *phCalPort;
  uint16_t                                      unIndex = ADM_INVALID_INDEX, extractedSessionID = 0, extractedStreamID = 0;
  adm_client_type_t                 eClient = eASM_TYPE;
  uint32_t opCode = elite_apr_if_get_opcode(pPkt);

  // Mute V6 is a superset of V5 we can safely cast to the base structure and handle it as a V5.
  // Although V7 is not superset of V5 or V6 but first 3 params matrix id, copp id and session id are common
  // in all 3 and since we are using only those 3 here, payload can be read as v5.
  pIncomingAPRPayload = (adm_cmd_matrix_mute_v5_t*)elite_apr_if_get_payload_ptr(pPkt);
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_MATRIX_MUTE. Matrix ID [%lu]",pIncomingAPRPayload->matrix_id);

  if(ADM_CMD_MATRIX_MUTE_V6 == opCode)
  {
    adm_cmd_matrix_mute_v6_t *pIncomingV6APRPayload = (adm_cmd_matrix_mute_v6_t*) pIncomingAPRPayload;
    eClient = (adm_client_type_t)pIncomingV6APRPayload->stream_type;
  }
  else if(ADM_CMD_MATRIX_MUTE_V7 == opCode)
  {
      adm_cmd_matrix_mute_v7_t *pIncomingV7APRPayload = (adm_cmd_matrix_mute_v7_t*)elite_apr_if_get_payload_ptr(pPkt);
      eClient = (adm_client_type_t)pIncomingV7APRPayload->stream_type;
  }
  if(((ADM_CLIENT_NUM_ONE < eClient) && (ADM_MATRIX_ID_AUDIO_TX == pIncomingAPRPayload->matrix_id) ) ||
      ((ADM_CLIENT_NUM_ZERO < eClient) && (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Mute cmd Rcvd invalid stream type value:%d", eClient);
    result = ADSP_EBADPARAM;
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToRxMtMxInPortIDMap[0]);
  }
  else if (ADM_MATRIX_ID_AUDIO_TX == pIncomingAPRPayload->matrix_id)
  {
    pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToTxMtMxOutPortIDMap[0]);
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Mute Rcvd invalid Matrix ID [%lu]",pIncomingAPRPayload->matrix_id);
    result = ADSP_EBADPARAM;
    goto __bailoutMatrixMute;
  }

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Mute Session ID: 0x%hX, COPP ID: %d", pIncomingAPRPayload->session_id, pIncomingAPRPayload->copp_id);

  //Extract the session and stream ID from the incoming ID and validate them.
  extractedSessionID = (0xff00 & pIncomingAPRPayload->session_id) >> 8;
  extractedStreamID  = (0x00ff & pIncomingAPRPayload->session_id);

  if (eASM_TYPE == eClient)
  {
    if(
        (0 == pIncomingAPRPayload->session_id) ||
        ((pIncomingAPRPayload->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
            ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
    )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Mute Rcvd invalid SessionID [0x%hX] for ASM session", pIncomingAPRPayload->session_id);
      result = ADSP_EBADPARAM;
      goto __bailoutMatrixMute;
    }
  }

  if (eLSM_TYPE == eClient)
  {
    if (0 == pIncomingAPRPayload->session_id || LSM_MAX_NUM_SESSIONS < pIncomingAPRPayload->session_id)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Mute Rcvd invalid SessionID [0x%hX] for LSM session", pIncomingAPRPayload->session_id);
      result = ADSP_EBADPARAM;
      goto __bailoutMatrixMute;
    }
  }

  //Map the incoming  SSID to Index
  unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)pIncomingAPRPayload->matrix_id, pIncomingAPRPayload->session_id, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    result = ADSP_EBADPARAM;
    goto __bailoutMatrixMute;
  }

  //Get hold of pSessionInfo AND if incoming SSID is legacy, map it to contemporary SSID
  AdmStreamSessionInfo_Type *pSessionInfo;
  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    pSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
    pIncomingAPRPayload->session_id = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
  }
  else
  {
    pSessionInfo = &(pAdmStatSvc->txStreamSessionInfo[unIndex]);
    pIncomingAPRPayload->session_id = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
  }

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Mute Contemporary Session ID: 0x%hX, COPP ID: %d",
        pIncomingAPRPayload->session_id, pIncomingAPRPayload->copp_id);

  //Check if stream session is a direct connection type
  if ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
      (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode) ||
      (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pSessionInfo->stream_perf_mode))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Mute is not supported in LLNP/ULL Session ID 0x%hX", pIncomingAPRPayload->session_id);
    result = ADSP_EUNSUPPORTED;
    goto __bailoutMatrixMute;
  }

  //Translate Session ID to Audio matrix Port ID
  pIncomingAPRPayload->session_id = pSnIDToPortIDMap[unIndex];

  if (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->matrix_id)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Mute Session ID => MXAR i/p port ID %d", pIncomingAPRPayload->session_id);

    //Translate COPP ID to Audio matrix Port ID
    if (ADM_CMD_MATRIX_MUTE_COPP_ID_ALL_CONNECTED_COPPS != pIncomingAPRPayload->copp_id)
    {
      if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pIncomingAPRPayload->copp_id,(uint16_t)pIncomingAPRPayload->matrix_id)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Mute ADM rcvd invalid/inactive COPP ID [%d]", pIncomingAPRPayload->copp_id);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixMute;
      }
      phCalPort = &pAdmStatSvc->deviceCalPort[pIncomingAPRPayload->copp_id];
      pIncomingAPRPayload->copp_id = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;

      //Check if mute command is issued on Device Loopback COPP
      if ( TRUE == phCalPort->bIsCoppInDeviceLoopBackTopology )
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: MatrixMute cmd is not supported on Device Loopback COPP [%lu]. Cmd Failed",pIncomingAPRPayload->copp_id);
        result = ADSP_EUNSUPPORTED;
        goto __bailoutMatrixMute;
      }

      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Mute COPP ID => MXAR o/p port ID %d", pIncomingAPRPayload->copp_id);
    }

    //Call matrix muting setup routine
    if (ADSP_FAILED(result = Adm_SendCmdMatrixMute(pAdmStatSvc, pPkt, pAdmStatSvc->hRxMatrix)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Adm_SendCmdMatrixMute failed, result = %d", result);
      goto __bailoutMatrixMute;
    }
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Mute Session ID => MXAT o/p port id %d", pIncomingAPRPayload->session_id);

    //Translate COPP ID to Audio matrix Port ID
    if (ADM_CMD_MATRIX_MUTE_COPP_ID_ALL_CONNECTED_COPPS != pIncomingAPRPayload->copp_id)
    {
      if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc,pIncomingAPRPayload->copp_id,(uint16_t)pIncomingAPRPayload->matrix_id)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Mute ADM rcvd invalid/inactive COPP ID [%d]", pIncomingAPRPayload->copp_id);
        result = ADSP_EBADPARAM;
        goto __bailoutMatrixMute;
      }
      phCalPort = &pAdmStatSvc->deviceCalPort[pIncomingAPRPayload->copp_id];
      pIncomingAPRPayload->copp_id = (phCalPort->mtMxPort).phMtMxInPort->inPortID;
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Mute COPP ID => MXAT i/p port ID %d", pIncomingAPRPayload->copp_id);
    }

    //Call matrix muting setup routine
    if (ADSP_FAILED(result = Adm_SendCmdMatrixMute(pAdmStatSvc, pPkt, pAdmStatSvc->hTxMatrix)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Adm_SendCmdMatrixMute failed, result = %d", result);
      goto __bailoutMatrixMute;
    }
  }

  __bailoutMatrixMute:
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_AprAfeConnectCmdHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt, qurt_elite_queue_t *pRspQ)
{
  AdmStatSvc_InfoType               *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  ADSPResult                         result = ADSP_EOK;
  uint16_t contemporarySessionID = 0;
  adm_client_type_t                   eClient = eASM_TYPE;

  adm_cmd_connect_afe_port_v5_t *pIncomingAPRPayload =
      (adm_cmd_connect_afe_port_v5_t *)elite_apr_if_get_payload_ptr(pPkt);
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_CONNECT_AFE_PORT_V5. Router ID [%u]", pIncomingAPRPayload->mode);

  //default values used by ADM_CMD_CONNECT_AFE_PORT command
  uint32_t num_channels = 2;
  uint32_t sampling_rate = 48000;
  uint32_t  bits_per_sample = 16;
  num_channels = pIncomingAPRPayload->num_channels;
  sampling_rate = pIncomingAPRPayload->sampling_rate;

  if(((2 != num_channels) && (8 != num_channels)) || (0 == sampling_rate)|| (ADM_SAMPLING_RATE_MAX < sampling_rate))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "ADM: ADM_CMD_CONNECT_AFE_PORT_V5. Invalid number of channels or sampling rate in command, num_channels = %lu, sampling_rate = %lu",
          num_channels, sampling_rate);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
    return ADSP_EBADPARAM;
  }

  //This command does not support Multi stream/session.
  //Expanding this command would mean to have a newer version of this old command.
  //This command only supports classic connections (single stream per session).
  //The client has to use the ADM_CMD_DEVICE_OPEN_V5 and ADM_CMD_STREAM_DEVICE_MAP_ROUTINGS_V5 commands for multi stream/session.
  //The following session ID check is needed to make sure it is within the single stream per session range.
  //Valid Range: for session ID: 1 - ASM_MAX_SUPPORTED_SESSION_ID.
  if(0 == pIncomingAPRPayload->session_id || ASM_MAX_SUPPORTED_SESSION_ID < pIncomingAPRPayload->session_id)
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "ADM: ADM_CMD_CONNECT_AFE_PORT_V5. Invalid session ID: %d. This old API only supports one stream per session and the valid range is 1 - %d",
          pIncomingAPRPayload->session_id, ASM_MAX_SUPPORTED_SESSION_ID);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
    return ADSP_EBADPARAM;
  }

  //Map the incoming  SSID to Index
  uint16_t unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)(pIncomingAPRPayload->mode), pIncomingAPRPayload->session_id, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    return ADSP_EBADPARAM;
  }

  uint16_t device_id;
  uint32_t i, device_id_offset;
  ComprCoppInfo_t *pComprCoppInfo;
  if(ADM_STRTR_ID_TX == pIncomingAPRPayload->mode)
  {
    pComprCoppInfo = &(pAdmStatSvc->txStRtrParams.compr_copp_info[0]);
    device_id_offset = ADM_COMPRESSED_MIN_TX;

    //If incoming SSID is legacy, map it to contemporary SSID
    contemporarySessionID = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
  }
  else
  {
    pComprCoppInfo = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[0]);
    device_id_offset = ADM_COMPRESSED_MIN_RX;

    //If incoming SSID is legacy, map it to contemporary SSID
    contemporarySessionID = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
  }

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM ADM_CMD_CONNECT_AFE_PORT_V5 Incoming SSID: %d, Contemporary SSID: 0x%hX",
        pIncomingAPRPayload->session_id, contemporarySessionID);

  //identify any free device Ids
  for(i=0; i<STRTR_MAX_PORTS; i++)
  {
    if(AFE_PORT_ID_INVALID == pComprCoppInfo->afe_port_id)
    {
      pComprCoppInfo->afe_port_id = pIncomingAPRPayload->afe_port_id;
      break;
    }
    pComprCoppInfo++;
  }

  //no free device ids, which means that all connections are taken up
  if(STRTR_MAX_PORTS == i)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: No more ports available to open device in compressed audio mode");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_ENORESOURCE);
    return ADSP_ENORESOURCE;
  }

  //Derive device Id
  device_id = device_id_offset + i;

  if(ADM_STRTR_ID_RX == pIncomingAPRPayload->mode)
  {
    result = Adm_RxStRtrAfeConnectCmdHandler(pAudStatAdmSvc, FALSE, contemporarySessionID,
                                             pIncomingAPRPayload->afe_port_id, num_channels, sampling_rate, bits_per_sample,
                                             AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE, device_id, admMemoryMapClient, NULL, eClient, pRspQ);

  }
  else if(ADM_STRTR_ID_TX == pIncomingAPRPayload->mode)
  {
    result = Adm_TxStRtrAfeConnectCmdHandler(pAudStatAdmSvc, FALSE, contemporarySessionID,
                                             pIncomingAPRPayload->afe_port_id, num_channels, sampling_rate,
                                             AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE, device_id, eClient, pRspQ);
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Rcvd invalid Stream Router ID [%u]",pIncomingAPRPayload->mode);
    result = ADSP_EBADPARAM;
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_AprAfeDisconnectCmdHandler (AdmStatSvc_InfoType *pAudStatAdmSvc, elite_apr_packet_t *pPkt,
                                                  qurt_elite_queue_t *pRspQ)
{
  AdmStatSvc_InfoType               *pAdmStatSvc = pAudStatAdmSvc;
  ADSPResult                         result = ADSP_EOK;

  uint16_t afe_port_id;

  //get the AFE port Id from the device Id
  uint16_t device_id = (uint16_t)elite_apr_if_get_dst_port(pPkt);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM Device Disconnect rcvd on Port ID [%d]: Compressed", device_id);

  if(ADM_CMD_DISCONNECT_AFE_PORT_V5 == pPkt->opcode)
  {
    afe_port_id = device_id;
  }
  else //ADM_CMD_DEVICE_CLOSE_V5
  {
    Adm_GetAfePortIdFromDeviceId(pAdmStatSvc, device_id, &afe_port_id);
  }

  bool_t is_afe_port_rx = FALSE;
  bool_t is_afe_port_tx = FALSE;

  uint32_t i=0;
  for(i=0; i<STRTR_MAX_PORTS; i++)
  {
    if(afe_port_id == pAdmStatSvc->rxStRtrParams.compr_copp_info[i].afe_port_id)
    {
      is_afe_port_rx = TRUE;
      break;
    }

    if (afe_port_id == pAdmStatSvc->txStRtrParams.compr_copp_info[i].afe_port_id)
    {
      is_afe_port_tx = TRUE;
      break;
    }
  }

  //check if the given AFE ID is for Rx or Tx stream router
  if(is_afe_port_rx)
  {
    result = Adm_RxStRtrAfeDisconnectCmdHandler(pAudStatAdmSvc, afe_port_id, pRspQ);
  }
  else if(is_afe_port_tx)
  {
    result = Adm_TxStRtrAfeDisconnectCmdHandler(pAudStatAdmSvc, afe_port_id, pRspQ);
  }
  else
  {
    //Given AFE port is not connected, not to be treated as failure
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: ADM_CMD_AFE_DISCONNECT. Given AFE port %d is already disconnected, nothing to be done ", afe_port_id);
  }

  //Ack the APR command
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_SendCmdDestroySvc(elite_svc_handle_t *pHandle)
{
  ADSPResult                              result = ADSP_EOK;
  qurt_elite_bufmgr_node_t                bufMgrNode;
  int                                     nActualSize;
  elite_msg_any_t                         msg;

  if(ADSP_FAILED(result = elite_mem_get_buffer(sizeof(elite_msg_cmd_destroy_svc_t), &bufMgrNode, &nActualSize)))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to create mesage");
    return result;
  }

  elite_msg_cmd_destroy_svc_t *pDestroyPayload = (elite_msg_cmd_destroy_svc_t*) bufMgrNode.pBuffer;
  pDestroyPayload->pResponseQ = NULL; //No response required for Destroy cmd.
  pDestroyPayload->unClientToken = 0;
  pDestroyPayload->pBufferReturnQ = bufMgrNode.pReturnQ;

  msg.unOpCode = ELITE_CMD_DESTROY_SERVICE;
  msg.pPayload = (void*)pDestroyPayload;

  if (ADSP_FAILED(result = qurt_elite_queue_push_back(pHandle->cmdQ, (uint64_t*)(&msg))))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to push cmd to Mixer/Router Svc");
    return result;
  }
  return result;
}

static  ADSPResult Adm_MsgGetDevicePathDelay(AdmStatSvc_InfoType *pAudStatAdmSvc, elite_msg_any_t* pMsg, adm_client_type_t eClient)
{
  ADSPResult   result = ADSP_EOK;
  EliteMsg_CustomAdmGetDevicePathDelayCmd *pPayload = (EliteMsg_CustomAdmGetDevicePathDelayCmd *) pMsg->pPayload;
  uint32_t unDirection = pPayload->direction;
  uint32_t unTotalBufferingDelay = 0;
  uint32_t unTotalAlgorithmicDelay = 0;
  pPayload->device_path_buf_delay = 0;
  pPayload->device_path_alg_delay = 0;

  //Kw fix
  if (eLSM_TYPE == eClient)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: GetDevicePathDelay received for LSM session. Unsupported");
    result = ADSP_EBADPARAM;
    elite_svc_send_ack(pMsg,result);
    return result;
  }

  uint16_t unIndex = Adm_SessionStreamIDToIndex(pAudStatAdmSvc, (uint16_t)(unDirection), pPayload->session_id, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    result = ADSP_EBADPARAM;
    elite_svc_send_ack(pMsg, result);
    return result;
  }

  if(pPayload->is_compressed)
  {
    if(ADM_RX_DIR == unDirection)
    {
      //Total buffering delay in compressed playback path: AFE delay + Stream Router delay.
      qurt_elite_mutex_lock(&pAudStatAdmSvc->admLock);
      uint16_t index =  pAudStatAdmSvc->rxSessionIDToPrimCompressedDevIndexMap[unIndex];
      qurt_elite_mutex_unlock(&pAudStatAdmSvc->admLock);
      if ((ADM_INVALID_PRIMARY_DEVICE == index)|| (index >= STRTR_MAX_PORTS)) //The index cannot exceed STRTR_MAX_PORTS
      {
        elite_svc_send_ack(pMsg, ADSP_EOK);
        return ADSP_EOK;
      }
      unTotalBufferingDelay = (pAudStatAdmSvc->rxStRtrParams.unAFEDelay[index] + pAudStatAdmSvc->rxStRtrParams.unStrRtrDelay[index]);

      // Aggregate the algorithmic and buffering delays of the primary COPP if a compressed COPP exists.
      {
        qurt_elite_mutex_lock(&pAudStatAdmSvc->admLock);
        ComprCoppInfo_t *pComprCopp = &pAudStatAdmSvc->rxStRtrParams.compr_copp_info[pAudStatAdmSvc->rxSessionIDToPrimCompressedDevIndexMap[unIndex]];
        qurt_elite_mutex_unlock(&pAudStatAdmSvc->admLock);
        if (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE != pComprCopp->unCoppTopologyID)
        {
          unTotalBufferingDelay += pComprCopp->unCoppBufDelay;
          unTotalAlgorithmicDelay += pComprCopp->unCoppAlgDelay;
        }
      }

      MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: GetDevicePathDelay Session ID 0x%hX: RX AFE: %lu, StrRtr: %lu, Total Buffering Delay: %lu, Total Algorithmic Delay: %lu",
            pPayload->session_id, pAudStatAdmSvc->rxStRtrParams.unAFEDelay[index], pAudStatAdmSvc->rxStRtrParams.unStrRtrDelay[index], unTotalBufferingDelay, unTotalAlgorithmicDelay);
    }
    else
    {
      //Total buffering delay in compressed record path: max(AFE delay, Stream Router delay).
      qurt_elite_mutex_lock(&pAudStatAdmSvc->admLock);
      uint16_t index =  pAudStatAdmSvc->txSessionIDToPrimCompressedDevIndexMap[unIndex];
      qurt_elite_mutex_unlock(&pAudStatAdmSvc->admLock);
      if ((ADM_INVALID_PRIMARY_DEVICE == index) || (index >= STRTR_MAX_PORTS)) //index cannot exceed STRTR_MAX_PORTS
      {
        elite_svc_send_ack(pMsg, ADSP_EOK);
        return ADSP_EOK;
      }
      unTotalBufferingDelay = (pAudStatAdmSvc->txStRtrParams.unAFEDelay[index] > pAudStatAdmSvc->txStRtrParams.unStrRtrDelay[index]) ? pAudStatAdmSvc->txStRtrParams.unAFEDelay[index] : pAudStatAdmSvc->txStRtrParams.unStrRtrDelay[index];

      MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: GetDevicePathDelay Session ID 0x%hX: TX AFE: %lu, StrRtr: %lu, Total Buffering Delay: %lu, Total Algorithmic Delay: %lu",
            pPayload->session_id, pAudStatAdmSvc->txStRtrParams.unAFEDelay[index], pAudStatAdmSvc->txStRtrParams.unStrRtrDelay[index], unTotalBufferingDelay, unTotalAlgorithmicDelay);
    }
  }
  else
  {
    uint16_t                     *pSnIDToPrCOPPIDMap, unCoppID;
    AdmDevSessionDelayParam_Type *pSessionDelayParam;

    if(ADM_RX_DIR == unDirection)
    {
      pSnIDToPrCOPPIDMap = &(pAudStatAdmSvc->rxSessionIDToPrimCOPPIDMap[0]);
    }
    else
    {
      pSnIDToPrCOPPIDMap = &(pAudStatAdmSvc->txSessionIDToPrimCOPPIDMap[0]);
    }

    unCoppID = pSnIDToPrCOPPIDMap[unIndex];

    if (ADSP_FAILED(result = Adm_CheckCoppValidity(pAudStatAdmSvc, unCoppID, ADM_INVALID_DIRECTION)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: GetDevicePathDelay: Session ID 0x%hX not connected to valid COPP yet", pPayload->session_id);
      elite_svc_send_ack(pMsg, ADSP_EOK);
      return ADSP_EOK;
    }

    pSessionDelayParam = &(pAudStatAdmSvc->pDevSessionDelayParam[unCoppID]);

    uint32_t matrixDelay = 0;
    if(ADM_RX_DIR == unDirection)
    {
      //Total buffering delay in the playback un-compressed PCM path: AFE delay + COPP delay + MXAR delay.
      matrixDelay = pAudStatAdmSvc->unRxMtMxDelay[unIndex];
      unTotalBufferingDelay = pSessionDelayParam->unAFEDelay_EP1 + pSessionDelayParam->unCoppBufDelay + matrixDelay;
    }
    else
    {
      //Total buffering delay in the record un-compressed PCM path: max(AFE delay, COPreP delay, MXAT delay)
      matrixDelay = pAudStatAdmSvc->unTxMtMxDelay[unIndex];
      unTotalBufferingDelay = (pSessionDelayParam->unAFEDelay_EP1 > pSessionDelayParam->unCoppBufDelay) ? pSessionDelayParam->unAFEDelay_EP1 : pSessionDelayParam->unCoppBufDelay;
      unTotalBufferingDelay = (unTotalBufferingDelay > matrixDelay) ? unTotalBufferingDelay : matrixDelay;
    }
    unTotalAlgorithmicDelay = pSessionDelayParam->unCoppAlgDelay;

    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: GetDevicePathDelay: Session ID 0x%hX, Prim COPP %d", pPayload->session_id, unCoppID);
    MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: GetDevicePathDelay: AFE: %lu, COPP Buf: %lu, COPP Alg: %lu, MtMx: %lu, Total Buf delay: %lu, Total Alg delay: %lu",
          pSessionDelayParam->unAFEDelay_EP1, pSessionDelayParam->unCoppBufDelay, pSessionDelayParam->unCoppAlgDelay, matrixDelay, unTotalBufferingDelay, unTotalAlgorithmicDelay);
  }

  //Fill and send the response to ASM
  pPayload->device_path_buf_delay = unTotalBufferingDelay;
  pPayload->device_path_alg_delay = unTotalAlgorithmicDelay;
  elite_svc_send_ack(pMsg, result);
  return result;
}

static  ADSPResult Adm_AprAddTopologiesHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType               *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  ADSPResult                         result = ADSP_EOK;

  adm_cmd_add_topologies_v5_t *pPayload = (adm_cmd_add_topologies_v5_t*)elite_apr_if_get_payload_ptr(pPkt);

  // Map the buffer
  uint32_t phyAddrLsw = (uint32_t)(pPayload->data_payload_addr_lsw);
  uint32_t phyAddrMsw = (uint32_t)(pPayload->data_payload_addr_msw);

  bool_t isAlignedToCacheLine = ((phyAddrLsw & CACHE_ALIGNMENT_MASK) == 0);

  if (!isAlignedToCacheLine)
  {
    result = ADSP_EBADPARAM;

    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Physical address is not aligned to cache line.");
    goto done;
  }

  audproc_custom_topologies_t *pVirtAddr;
  {
    elite_mem_shared_memory_map_t bufferMemNode;
    bufferMemNode.unMemMapHandle = pPayload->mem_map_handle;
    bufferMemNode.unMemMapClient = admMemoryMapClient;
    result =  elite_mem_map_get_shm_attrib(phyAddrLsw, phyAddrMsw, pPayload->buffer_size, &bufferMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to map physical memory.");
      goto done;
    }

    // Since this buffer will be read, need to invalidate the cache.
    result = elite_mem_invalidate_cache(&bufferMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to invalidate memory.");
      goto done;
    }

    pVirtAddr = (audproc_custom_topologies_t*)(bufferMemNode.unVirtAddr);
  }

  {
    uint32_t buffer_size = pPayload->buffer_size;

    if (buffer_size < sizeof(audproc_custom_topologies_t))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Size of custom topologies buffer %lu bytes is insufficient.", buffer_size);
      result = ADSP_ENEEDMORE;
      goto done;
    }

    audproc_custom_topologies_t *pHeader = (pVirtAddr);
    pVirtAddr++;
    buffer_size -= sizeof(audproc_custom_topologies_t);

    uint32_t size_required = pHeader->num_topologies * sizeof(audproc_topology_definition_t);
    if (buffer_size < size_required)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Size of custom topologies array %lu bytes is insufficient. %lu bytes needed", buffer_size, size_required);
      result = ADSP_ENEEDMORE;
      goto done;
    }

    result = topo_db_add_topologies(TOPO_DB_CLIENT_TYPE_COPP, pHeader->num_topologies, (const audproc_topology_definition_t*)pVirtAddr);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to insert all COPP topologies into the database.");
      goto done;
    }

    result = topo_db_add_topologies(TOPO_DB_CLIENT_TYPE_COPREP, pHeader->num_topologies, (const audproc_topology_definition_t*)pVirtAddr);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to insert all COPREP topologies into the database.");
      goto done;
    }
  }

  done:
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);

  return result;
}

static ADSPResult Adm_AprSetMtMxStrtrDeviceParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_set_mtmx_strtr_dev_params_v1_t         *pIncomingAPRPayload;
  ADSPResult                                 result = ADSP_EOK;

  pIncomingAPRPayload = (adm_cmd_set_mtmx_strtr_dev_params_v1_t*)elite_apr_if_get_payload_ptr(pPkt);

  //Check the validity of the COPP ID/Device ID
  if (
      (ADSP_EOK != Adm_CheckCoppValidity(pAdmStatSvc,pIncomingAPRPayload->device_id, ADM_MATRIX_ID_AUDIO_RX)) &&
      (ADSP_EOK != Adm_CheckCompDevIDValidity(pAdmStatSvc, pIncomingAPRPayload->device_id))
  )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid device ID [%d]", pIncomingAPRPayload->device_id);
    result = ADSP_EBADPARAM;
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  uint32_t dataPayloadSize      = pIncomingAPRPayload->data_payload_size;
  int32_t *paramBase            = NULL;

  if (0 == pIncomingAPRPayload->mem_map_handle) //in-band
  {
    //Address just beyond the Set params header adm_cmd_set_mtmx_strtr_dev_params_v1_t
    //points to adm_mtmx_strtr_dev_param_data_t
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Processing ADM_CMD_SET_MTMX_STRTR_DEV_PARAMS_V1 cmd Inband on device_id:%hu", pIncomingAPRPayload->device_id);

    paramBase  = (int32_t *)( ((int8_t*) pIncomingAPRPayload) + sizeof(adm_cmd_set_mtmx_strtr_dev_params_v1_t));
  }
  else //out-of-band
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Processing ADM_CMD_SET_MTMX_STRTR_DEV_PARAMS_V1 cmd Out-of-band on device_id:%hu", pIncomingAPRPayload->device_id);

    if(pIncomingAPRPayload->data_payload_addr_lsw & CACHE_ALIGNMENT_MASK)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Physical memory address is not aligned to cache line, in set device param");
      result = ADSP_EBADPARAM;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    elite_mem_shared_memory_map_t sMemNode;
    sMemNode.unMemMapHandle = pIncomingAPRPayload->mem_map_handle;
    sMemNode.unMemMapClient = admMemoryMapClient;
    sMemNode.unPhysAddrLsw = pIncomingAPRPayload->data_payload_addr_lsw;
    sMemNode.unPhysAddrMsw = pIncomingAPRPayload->data_payload_addr_msw;
    sMemNode.unMemSize = (uint32_t)(dataPayloadSize);

    result =  elite_mem_map_get_shm_attrib(sMemNode.unPhysAddrLsw, sMemNode.unPhysAddrMsw, sMemNode.unMemSize, &sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to map physical memory for SetDeviceParam");
      result = ADSP_EFAILED;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    // Since this buffer will be read, need to invalidate the cache.
    result = elite_mem_invalidate_cache(&sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to invalidate cache for SetDeviceParam");
      result = ADSP_EFAILED;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
    paramBase  = (int32_t*)(sMemNode.unVirtAddr);
  }

  bool_t isCompressed = FALSE;
  if( ADSP_EOK == Adm_CheckCompDevIDValidity(pAdmStatSvc, pIncomingAPRPayload->device_id))
  {
    isCompressed = TRUE;
  }
  switch(isCompressed)
  {
    case FALSE:
    {
      uint32_t     unOutPortID;
      AdmCalPort_Type               *phCalPort;
      //Map COPP ID to o/p port ID
      if(ADM_MAX_COPPS < pIncomingAPRPayload->device_id) //Keep KW happy even though device ID is validated
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid device ID [%d]", pIncomingAPRPayload->device_id);
        result = ADSP_EBADPARAM;
      }
      else
      {
        phCalPort = &pAdmStatSvc->deviceCalPort[pIncomingAPRPayload->device_id];
        unOutPortID = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;
        result = Adm_SetMtMxDeviceParamsCmdHandler(pAdmStatSvc, pPkt, paramBase, dataPayloadSize,unOutPortID, pAdmStatSvc->hRxMatrix);
      }
      break;
    }
    case TRUE:
    {
      result = Adm_SetStRtrDeviceParamsCmdHandler(pAdmStatSvc, pPkt, paramBase, dataPayloadSize);
      break;
    }
  };

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_SET_MTMX_STRTR_DEV_PARAMS_V1 cmd on device_id[%hu] completed, result = %d", pIncomingAPRPayload->device_id, result);

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_AprGetMtMxStrtrDeviceParamsCmdHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_get_mtmx_strtr_dev_params_v1_t         *pIncomingAPRPayload;
  ADSPResult                                 result = ADSP_EOK;

  pIncomingAPRPayload = (adm_cmd_get_mtmx_strtr_dev_params_v1_t*)elite_apr_if_get_payload_ptr(pPkt);
  uint16_t unDeviceID= pIncomingAPRPayload->device_id;

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Processing ADM_CMD_GET_MTMX_STRTR_DEV_PARAMS_V1 cmd on device_id:%hu", unDeviceID);

  //Check the validity of the COPP ID/Device ID
  if (
      (ADSP_EOK != Adm_CheckCoppValidity(pAdmStatSvc,pIncomingAPRPayload->device_id, ADM_MATRIX_ID_AUDIO_RX)) &&
      (ADSP_EOK != Adm_CheckCompDevIDValidity(pAdmStatSvc, pIncomingAPRPayload->device_id))
  )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid device ID [%d]", pIncomingAPRPayload->device_id);
    result = ADSP_EBADPARAM;
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  bool_t isCompressed = FALSE;
  if( ADSP_EOK == Adm_CheckCompDevIDValidity(pAdmStatSvc, pIncomingAPRPayload->device_id))
  {
    isCompressed = TRUE;
  }
  switch(isCompressed)
  {
    case FALSE:
    {
      uint32_t     unOutPortID;
      AdmCalPort_Type               *phCalPort;
      //Map COPP ID to o/p port ID
      if(ADM_MAX_COPPS < pIncomingAPRPayload->device_id) //Keep KW happy even though device ID is validated
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid device ID [%d]", pIncomingAPRPayload->device_id);
        result = ADSP_EBADPARAM;
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      }
      else
      {
        phCalPort = &pAdmStatSvc->deviceCalPort[pIncomingAPRPayload->device_id];
        unOutPortID = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;
        result = Adm_GetMtMxDeviceParamsCmdHandler(pAdmStatSvc, pPkt, unOutPortID, pAdmStatSvc->hRxMatrix, admMemoryMapClient);
      }
      break;
    }
    case TRUE:
    {
      result = Adm_GetStRtrDeviceParamsCmdHandler(pAdmStatSvc, pPkt);
      break;
    }
  };

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: ADM_CMD_GET_MTMX_STRTR_DEV_PARAMS_V1 cmd on device_id[%hu] completed, result = %d", unDeviceID, result);

  return result;
}

static ADSPResult Adm_AprSetPspdMtMxStrtrParamsCmdHandler (void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                 *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_set_pspd_mtmx_strtr_params_v5_t         *pIncomingAPRPayload;
  ADSPResult                                 result = ADSP_EOK;
  adm_client_type_t                 eClient = eASM_TYPE;
  uint32_t opCode = elite_apr_if_get_opcode(pPkt);

  // PSPD SET V6 is a superset of V5 we can safely cast to the base structure and handle the PSPD cmd as a V5.
  pIncomingAPRPayload = (adm_cmd_set_pspd_mtmx_strtr_params_v5_t*)elite_apr_if_get_payload_ptr(pPkt);

  if(ADM_CMD_SET_PSPD_MTMX_STRTR_PARAMS_V6 == opCode)
  {
    adm_cmd_set_pspd_mtmx_strtr_params_v6_t *pIncomingV6APRPayload = (adm_cmd_set_pspd_mtmx_strtr_params_v6_t*) pIncomingAPRPayload;
    eClient = (adm_client_type_t)pIncomingV6APRPayload->stream_type;
  }
  if(((ADM_CLIENT_NUM_ONE < eClient) && (ADM_MATRIX_ID_AUDIO_TX == pIncomingAPRPayload->direction) ) ||
      ((ADM_CLIENT_NUM_ZERO < eClient) && (ADM_MATRIX_ID_AUDIO_RX == pIncomingAPRPayload->direction)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: PSPD cmd Rcvd invalid stream type value:%d", eClient);
    result = ADSP_EBADPARAM;
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Extract the session and stream ID from the incoming ID and validate them.
  uint16_t extractedSessionID = 0, extractedStreamID = 0;
  extractedSessionID = (0xff00 & pIncomingAPRPayload->session_id) >> 8;
  extractedStreamID  = (0x00ff & pIncomingAPRPayload->session_id);

  if (eASM_TYPE == eClient)
  {
    if(
        (0 == pIncomingAPRPayload->session_id) ||
        ((pIncomingAPRPayload->session_id > ASM_MAX_SUPPORTED_SESSION_ID) &&
            ((0 == extractedSessionID) || (extractedSessionID > ASM_MAX_SUPPORTED_SESSION_ID) ||
                (0 == extractedStreamID)  ||  (extractedStreamID  > ASM_MAX_SUPPORTED_STREAM_ID)))
    )
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: PSPD SetParams Rcvd invalid SessionID [0x%hX] for ASM session", pIncomingAPRPayload->session_id);
      result = ADSP_EBADPARAM;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
  }

  if (eLSM_TYPE == eClient)
  {
    if (0 == pIncomingAPRPayload->session_id || LSM_MAX_NUM_SESSIONS < pIncomingAPRPayload->session_id)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: PSPD SetParams Rcvd invalid SessionID [0x%hX] for LSM session", pIncomingAPRPayload->session_id);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
      return ADSP_EBADPARAM;
    }
  }

  //Check the validity of the COPP ID/Device ID
  if (
      (ADSP_EOK != Adm_CheckCoppValidity(pAdmStatSvc, pIncomingAPRPayload->device_id,pIncomingAPRPayload->direction )) &&
      (ADSP_EOK != Adm_CheckCompDevIDValidity(pAdmStatSvc, pIncomingAPRPayload->device_id))
  )
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid device ID [%hu] for direction:%hu", pIncomingAPRPayload->device_id,pIncomingAPRPayload->direction);
    result = ADSP_EBADPARAM;
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  uint32_t dataPayloadSize      = pIncomingAPRPayload->data_payload_size;
  int32_t *paramBase            = NULL;

  if (0 == pIncomingAPRPayload->mem_map_handle) //in-band
  {
    //Address just beyond the Set params header adm_cmd_set_pspd_mtmx_strtr_params_v5_t
    //points to adm_pspd_param_data_t
    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Inband Set PSPD MtMx/StrRtr Param, Dir: %d, SID: 0x%hX, DID: %d",
          pIncomingAPRPayload->direction,
          pIncomingAPRPayload->session_id, pIncomingAPRPayload->device_id);

    paramBase  = (int32_t *)(pIncomingAPRPayload + 1);
  }
  else //out-of-band
  {
    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Outband Set PSPD MtMx/StrRtr Param, Dir: %d, SID: 0x%hX, DID: %d",
          pIncomingAPRPayload->direction,
          pIncomingAPRPayload->session_id, pIncomingAPRPayload->device_id);

    if(pIncomingAPRPayload->data_payload_addr_lsw & CACHE_ALIGNMENT_MASK)
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Physical memory address is not aligned to cache line, in set param");
      result = ADSP_EBADPARAM;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    elite_mem_shared_memory_map_t sMemNode;
    sMemNode.unMemMapHandle = pIncomingAPRPayload->mem_map_handle;
    sMemNode.unMemMapClient = admMemoryMapClient;
    sMemNode.unPhysAddrLsw = pIncomingAPRPayload->data_payload_addr_lsw;
    sMemNode.unPhysAddrMsw = pIncomingAPRPayload->data_payload_addr_msw;
    sMemNode.unMemSize = (uint32_t)(dataPayloadSize);

    result =  elite_mem_map_get_shm_attrib(sMemNode.unPhysAddrLsw, sMemNode.unPhysAddrMsw, sMemNode.unMemSize, &sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to map physical memory for SetParam");
      result = ADSP_EFAILED;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    // Since this buffer will be read, need to invalidate the cache.
    result = elite_mem_invalidate_cache(&sMemNode);
    if (ADSP_FAILED(result))
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to invalidate cache for SetParam");
      result = ADSP_EFAILED;
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
    paramBase  = (int32_t*)(sMemNode.unVirtAddr);
  }

  //Map the incoming  SSID to Index
  uint16_t unIndex = ADM_INVALID_INDEX;
  unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, pIncomingAPRPayload->direction, pIncomingAPRPayload->session_id, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    result = ADSP_EBADPARAM;
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //If incoming SSID is legacy, map it to contemporary SSID
  if(ADM_RX_DIR == pIncomingAPRPayload->direction)
  {
    pIncomingAPRPayload->session_id = pAdmStatSvc->rxIndexToSessionStreamID[unIndex];
  }
  else
  {
    pIncomingAPRPayload->session_id = pAdmStatSvc->txIndexToSessionStreamID[unIndex];
  }
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: PSPD SetParams Contemporary Session ID: 0x%hX",
        pIncomingAPRPayload->session_id);

  bool_t isCompressed = FALSE;
  if((ADSP_EOK != Adm_CheckCoppValidity(pAdmStatSvc, pIncomingAPRPayload->device_id, pIncomingAPRPayload->direction)) &&
      (ADSP_EOK == Adm_CheckCompDevIDValidity(pAdmStatSvc, pIncomingAPRPayload->device_id)))
  {
    isCompressed = TRUE;
  }

  switch(isCompressed)
  {
    case FALSE:
    {
      uint16_t                      *pSnIDToPortIDMap;
      AdmCalPort_Type               *phCalPort;
      uint32_t                      unInPortID, unOutPortID;

      switch(pIncomingAPRPayload->direction)
      {
        case 0:
        {
          //RX Audio matrix

          //Map session ID to i/p port ID
          pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToRxMtMxInPortIDMap[0]);
          unInPortID = pSnIDToPortIDMap[unIndex];

          if(ADM_MAX_COPPS < pIncomingAPRPayload->device_id) //To keep KW happy
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: PSPD setparams cmd recvd invalid COPP ID [%d]. Cmd Failed",pIncomingAPRPayload->device_id);
            result = ADSP_EBADPARAM;
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
            return result;  
          }
          //Map COPP ID to o/p port ID
          phCalPort = &pAdmStatSvc->deviceCalPort[pIncomingAPRPayload->device_id];

          //Check if PSPD command is issued on Device Loopback COPP
          if ( TRUE == phCalPort->bIsCoppInDeviceLoopBackTopology )
          {
            MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: PSPD setparams cmd is not supported on Device Loopback COPP. Cmd Failed");
            result = ADSP_EUNSUPPORTED;
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
            return result;
          }
          unOutPortID = (phCalPort->mtMxPort).phMtMxOutPort->outPortID;

          MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM PSPD Set Param on RX matrix: i/p port %lu, o/p port %lu, Base: 0x%p, Size: %lu",
                unInPortID, unOutPortID, paramBase, dataPayloadSize);

          result = Adm_SetPspdMtMxParamsCmdHandler(pAdmStatSvc, pPkt, pIncomingAPRPayload,
                                                   paramBase, dataPayloadSize, unInPortID, unOutPortID, pAdmStatSvc->hRxMatrix);
          break;
        }
        case 1:
        {
          //Map session ID to o/p port ID
          pSnIDToPortIDMap = &(pAdmStatSvc->sessionIDToTxMtMxOutPortIDMap[0]);
          unOutPortID = pSnIDToPortIDMap[unIndex];

          if(ADM_MAX_COPPS < pIncomingAPRPayload->device_id) //To Keep KW happy
          {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: PSPD setparams cmd recvd invalid COPP ID [%d]. Cmd Failed",pIncomingAPRPayload->device_id);
            result = ADSP_EBADPARAM;
            elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
            return result;  
          }
          //Map COPP ID to i/p port ID
          phCalPort = &pAdmStatSvc->deviceCalPort[pIncomingAPRPayload->device_id];
          unInPortID = (phCalPort->mtMxPort).phMtMxInPort->inPortID;

          //TX Audio matrix
          MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM PSPD Set Param on TX matrix: i/p port %lu, o/p port %lu, Base: 0x%p, Size: %lu",
                unInPortID, unOutPortID, paramBase, dataPayloadSize);

          result = Adm_SetPspdMtMxParamsCmdHandler(pAdmStatSvc, pPkt, pIncomingAPRPayload,
                                                   paramBase, dataPayloadSize, unInPortID, unOutPortID, pAdmStatSvc->hTxMatrix);
          break;
        }
        default:
        {
          //Invalid direction
          result = ADSP_EBADPARAM;
          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM Set Param called with invalid direction %d", pIncomingAPRPayload->direction);
          elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
          return result;
        }
      };
      break;
    }
    case TRUE:
    {
      switch(pIncomingAPRPayload->direction)
      {
        case 0:
        {
          //RX stream router
          result = Adm_SetPspdRXStRtrParamsCmdHandler(pAdmStatSvc, pPkt, pIncomingAPRPayload, paramBase, dataPayloadSize);
          break;
        }
        case 1:
        {
          //TX stream router
          result = Adm_SetPspdTXStRtrParamsCmdHandler(pAdmStatSvc, pPkt, pIncomingAPRPayload, paramBase, dataPayloadSize);
          break;
        }
        default:
        {
          //Invalid direction
          result = ADSP_EBADPARAM;
          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM Set Param called with invalid direction %d", pIncomingAPRPayload->direction);
          elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
          return result;
        }
      };
      break;
    }
  };

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_DeviceOpenCmdLPCMLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                       adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                       elite_apr_packet_t *pPkt,
                                                       NativeModeHook cbNativeMode,
                                                       uint16_t *unCreatedCoppID,
                                                       qurt_elite_queue_t *pRspQ)
{
  uint16_t                     unCoppID;
  AdmCalPort_Type              *phCalPort;
  qurt_elite_thread_t          coppThreadID;
  elite_svc_handle_t           *pCoppHandle;
  AdmDevSessionDelayParam_Type *pSessionDelayParam;

  ADSPResult result           = ADSP_EOK;
  bool_t     bIsInPortLive    = FALSE, bIsInPortBurstMode = FALSE;
  uint32_t   bytes_per_sample = ADM_BYTES_PER_SAMPLE_TWO;
  uint32_t   unLogID          = 0;

  unCoppID = *unCreatedCoppID;

  phCalPort          = &pAdmStatSvc->deviceCalPort[unCoppID];
  pSessionDelayParam = &(pAdmStatSvc->pDevSessionDelayParam[unCoppID]);

  phCalPort->unEID1.unAfePortID      = ADM_CMD_COPP_OPEN_END_POINT_ID_1_IGNORE;
  phCalPort->unEID1.unBytesPerSample = ADM_BYTES_PER_SAMPLE_TWO;
  phCalPort->unEID1.unBitWidth       = ADM_BITS_PER_SAMPLE_16;
  phCalPort->unEID2.unAfePortID      = ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE;
  phCalPort->unCoppMode              = pDevOpenCmdPayload->mode_of_operation;

  if (AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT == pDevOpenCmdPayload->topology_id)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM:AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT is not supported in LPCM mode");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
    return ADSP_EUNSUPPORTED;
  }

  /* Check for validity of device performance mode received */
  /**
   *     1. get the device_perf_mode and check if they are valid
   *     2. return failure incase of invalid entries
   *     3. set COPP buffer duration to 10msec for ADM_LEGACY_DEVICE_SESSION &
   *                               1msec  for ADM_LOW_LATENCY_DEVICE_SESSION
   */
  /* for 44.1Khz, the duration is 10msec, which is set later for audio topology*/

  phCalPort->unDevicePerfMode = (uint16_t)Adm_GetDevicePerfModeInOpenCmd(pDevOpenCmdPayload->flags);
  if (ADM_LOW_LATENCY_DEVICE_SESSION < phCalPort->unDevicePerfMode )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device_perf_mode in flags field [%d]", phCalPort->unDevicePerfMode);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;
  }

  //Set up some parameters for loopback COPP
  phCalPort->unCoppDirection = RX_DIR;
  bIsInPortLive              = FALSE;
  bIsInPortBurstMode         = FALSE;

  if(ADSP_EOK == elite_cmn_topo_db_is_active_topology_present(1 << AVCS_TOPO_CFG_AREA_VOICE_BIT, pDevOpenCmdPayload->topology_id))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: VpTX COPP is not supported in loopback mode");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
    return ADSP_EUNSUPPORTED;
  }
  else
  {
    //Audio COPP...
    phCalPort->unCoppType = ADM_COPP_TYPE_AUDIO_COPP;

    Adm_PrintChannelType(pDevOpenCmdPayload->dev_channel_mapping_eid1, pDevOpenCmdPayload->dev_num_channel_eid1);

    //Verify that dev_num_channel value is (greater than 0) and (less than or equal to 8)
    if (ADM_NUM_CHANNELS_EIGHT < pDevOpenCmdPayload->dev_num_channel_eid1 ||
        ADM_NUM_CHANNELS_NULL == pDevOpenCmdPayload->dev_num_channel_eid1)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device num channels [%d], valid range: 1 - 8",
           pDevOpenCmdPayload->dev_num_channel_eid1);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    //For mono or stereo opens, if PCM_CHANNEL_INVALID was set, then set them to default mono/stereo channels
    if((ADM_NUM_CHANNELS_MONO == pDevOpenCmdPayload->dev_num_channel_eid1) && (PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[0]))
    {
       pDevOpenCmdPayload->dev_channel_mapping_eid1[0] = PCM_CHANNEL_C;
    }

   if((ADM_NUM_CHANNELS_STEREO == pDevOpenCmdPayload->dev_num_channel_eid1) &&
     ((PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[0]) || (PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[1])))
    {
       pDevOpenCmdPayload->dev_channel_mapping_eid1[0] = PCM_CHANNEL_L;
       pDevOpenCmdPayload->dev_channel_mapping_eid1[1] = PCM_CHANNEL_R;
    }

    //For non-mono, non-stereo types, PCM_CHANNEL_INVALID is invalid. So is any mapping greater than MAX_CHANNEL_MAPPING_NUMBER
    for (uint16_t i = 0; i < pDevOpenCmdPayload->dev_num_channel_eid1; i++)
    {
      if ((MAX_CHANNEL_MAPPING_NUMBER < pDevOpenCmdPayload->dev_channel_mapping_eid1[i]) || (PCM_CHANNEL_INVALID == pDevOpenCmdPayload->dev_channel_mapping_eid1[i]))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device channel mapping %d for channel #%d", pDevOpenCmdPayload->dev_channel_mapping_eid1[i], (i + 1));
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
        return ADSP_EFAILED;
      }
    }

    //Bit-width sanity
    if(pDevOpenCmdPayload->bit_width_eid1 < ADM_BITS_PER_SAMPLE_16 || pDevOpenCmdPayload->bit_width_eid1 > ADM_BITS_PER_SAMPLE_32)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid PCM bit_width  [%d], valid range: 16-32 bits",
              pDevOpenCmdPayload->bit_width_eid1);

      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }
    bytes_per_sample = elite_data_get_bytes_per_sample(pDevOpenCmdPayload->bit_width_eid1);
    phCalPort->unEID1.unBytesPerSample = bytes_per_sample;
    phCalPort->unEID1.unBitWidth = pDevOpenCmdPayload->bit_width_eid1;

    //Sampling rate sanity
    if((0 == pDevOpenCmdPayload->sample_rate_eid1) || (ADM_SAMPLING_RATE_MAX < pDevOpenCmdPayload->sample_rate_eid1))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid sampling rate [%lu] for Audio COPP topology %lu",
               pDevOpenCmdPayload->sample_rate_eid1, pDevOpenCmdPayload->topology_id);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }
    phCalPort->unMtMxSampleRate = pDevOpenCmdPayload->sample_rate_eid1;
    phCalPort->unEID1.unSampleRate = pDevOpenCmdPayload->sample_rate_eid1;

    /* Validate the device sampling rate & then fetch the afe frame size*/
    if(ADSP_FAILED(is_valid_device_sampling_rate(phCalPort->unEID1.unSampleRate)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid sampling rate [%lu] for Audio COPP",
            phCalPort->unEID1.unSampleRate);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EUNSUPPORTED;
    }
    uint32_t unCoppAfeFrameSizeInSamples;
    elite_svc_get_frame_size(pDevOpenCmdPayload->sample_rate_eid1, &unCoppAfeFrameSizeInSamples);

    if (ADM_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
    {
      phCalPort->unCoppNumAfeFrames = ADM_LL_NUM_AFE_FRAMES;
    }
    else
    {
      phCalPort->unCoppNumAfeFrames = ADM_LEGACY_NUM_AFE_FRAMES;
    }

#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE before creating COPP Svc %d",
          qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing CREATE_COPP cmd, topologyID: 0x%lX"
          "device_perf_mode is [%hu] & afe frame size is [%lu] & COPP Buffer Num Frames is [%lu]",\
          pDevOpenCmdPayload->topology_id, phCalPort->unDevicePerfMode, unCoppAfeFrameSizeInSamples, phCalPort->unCoppNumAfeFrames);

    //Increment the Number of RX Audio COPP opened
    qurt_elite_mutex_lock(&pAdmStatSvc->admLock);
    pAdmStatSvc->unNumRxAudioCoppOpenIssued++;
    if(ADM_MAX_COPP_OPEN_CTR < pAdmStatSvc->unNumRxAudioCoppOpenIssued)
    {
      pAdmStatSvc->unNumRxAudioCoppOpenIssued = 0;
    }
    //Get a unique Log ID
    unLogID = ADM_LOG_ID_BASE_RX + (pAdmStatSvc->unNumRxAudioCoppOpenIssued << 4);
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

    result = Adm_CreatePPSvc(pAdmStatSvc,
                             phCalPort,
                             pSessionDelayParam,
                             pDevOpenCmdPayload->topology_id,
                             DYNA_SVC_PP_TYPE_COPP,
                             unLogID);
    if (ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CREATE_COPP cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    //COPP provides its handle
    pCoppHandle = phCalPort->phDevCopp;
    //COPP thread ID. Used to destroy COPP if cmd handler fails midway
    coppThreadID = pCoppHandle->threadId;

#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE after creating COPP Svc %d",
          qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

    /* Specify output media format to COPP */
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: cfg'ing to output %d channels", pDevOpenCmdPayload->dev_num_channel_eid1);

    if (ADSP_FAILED(result = adm_config_pp_output_media_format(pCoppHandle, pRspQ,
                                                               pDevOpenCmdPayload->dev_num_channel_eid1,
                                                               &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                               pDevOpenCmdPayload->sample_rate_eid1, 0)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: PP_output_media_fmt cmd failed, result = %d", result);
      goto __bailoutLBDeviceOpen5;
    }

    //Num Channels book keeping
    phCalPort->unEID1.unNumChannels = (uint32_t)pDevOpenCmdPayload->dev_num_channel_eid1;

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of LB ADM_CMD_DEVICE_OPEN, # default ch: %lu",
          phCalPort->unEID1.unNumChannels);

    //Use Matrix Handle to send Connect message to COPP...Create an Input port to Matrix in tx direction
    elite_svc_handle_t *pMtMxHandle2 = pAdmStatSvc->hTxMatrix;

    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing CONNECT_MT_MX_IN_PORT cmd, Live: %d, BM: %d",
          bIsInPortLive, bIsInPortBurstMode);

    if (ADSP_FAILED(result = Adm_SendCmdConnectMtMxInPort(pAdmStatSvc, 0xFFFFFFFF,
                                                          bIsInPortLive, bIsInPortBurstMode,
                                                          0, pMtMxHandle2,
                                                          &((phCalPort->mtMxPort2).phMtMxInPort),
                                                          NULL, unLogID,
                                                          NULL, phCalPort->unDevicePerfMode,
                                                          0, NULL, TRUE,
                                                          pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_MT_MX_IN_PORT cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Destroy COPP */
      goto __bailoutLBDeviceOpen5;
    }

    //Provide handle of Matrix's Input Port to COPP and send Connect
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, " ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing CONNECT_COPP cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                            &((phCalPort->mtMxPort2).phMtMxInPort->portHandle),
                                            ELITE_CMD_CONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_COPP cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Close MXAT input port */
      /* 2. Destroy COPP */
      goto __bailoutLBDeviceOpen4;
    }

    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing CONNECT_MT_MX_OUT_PORT cmd");

    elite_svc_handle_t *pMtMxHandle  = pAdmStatSvc->hRxMatrix;
    elite_svc_handle_t *pSvc2Connect = phCalPort->phDevCopp;

    // Configure nativity
    uint8_t unNativeModeFlags = cbNativeMode(pDevOpenCmdPayload);

    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of LB ADM_CMD_COPP_OPEN, # ch: %lu, NatModeFlags=0b%08b, Pull mode",
          phCalPort->unEID1.unNumChannels, unNativeModeFlags);

    if (ADSP_FAILED(result = Adm_SendCmdConnectMtMxOutPort(pAdmStatSvc, 0xFFFFFFFF, PULL_MODE,
                                                           pDevOpenCmdPayload->dev_num_channel_eid1,
                                                           &(pDevOpenCmdPayload->dev_channel_mapping_eid1[0]),
                                                           0, pMtMxHandle, &pSvc2Connect,
                                                           &((phCalPort->mtMxPort).phMtMxOutPort),
                                                           NULL, phCalPort->unEID1.unBitWidth, 0, 0,
                                                           pDevOpenCmdPayload->sample_rate_eid1,
                                                           &(pSessionDelayParam->unCoppBufDelay),
                                                           &(pSessionDelayParam->unCoppAlgDelay),
                                                           &(pSessionDelayParam->unAFEDelay_EP1),
                                                           NULL,
                                                           ADM_NUM_BUFFERS_BETWEEN_MXAR_AND_COPP,
                                                           phCalPort->unDevicePerfMode,
                                                           unNativeModeFlags, 0, NULL,
                                                           pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CONNECT_MT_MX_OUT_PORT cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect from MXAT input port */
      /* 2. Close MXAT input port */
      /* 3. Destroy COPP */
      goto __bailoutLBDeviceOpen3;
    }

    //Send a RUN cmd to Matrix Mixer
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing RUN_MT_MX_OUTPUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdRunMtMxPort(pAdmStatSvc,
                                                    (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                    MATRIX_MIXER_PORT_DIR_OUTPUT, pMtMxHandle,
                                                    pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_MT_MX_OUTPUT_PORT cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect from MXAT input port */
      /* 2. Close MXAT input port */
      /* 3. Destroy COPP */
      /* 4. Disconnect from MXAR output port */
      goto __bailoutLBDeviceOpen2;
    }

    //Send a RUN cmd to Matrix Mixer
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing RUN_MT_MX_INPUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdRunMtMxPort(pAdmStatSvc, (phCalPort->mtMxPort2).phMtMxInPort->inPortID,
                                                    MATRIX_MIXER_PORT_DIR_INPUT, pMtMxHandle2,
                                                    pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_MT_MX_INPUT_PORT cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disable MXAR output port */
      /* 2. Disconnect from MXAT input port */
      /* 3. Close MXAT input port */
      /* 4. Destroy COPP */
      /* 5. Disconnect from MXAR output port */
      goto __bailoutLBDeviceOpen1;
    }

    //Send a RUN cmd to COPP
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of LB ADM_CMD_DEVICE_OPEN, issuing RUN_COPP cmd");

    if (ADSP_FAILED(result = Adm_SendCmdRunCopp(pCoppHandle, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: RUN_COPP cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disable MXAR output port */
      /* 2. Disconnect from MXAT input port */
      /* 3. Close MXAT input port */
      /* 4. Destroy COPP */
      /* 5. Disconnect from MXAR output port */
      goto __bailoutLBDeviceOpen1;
    }

    //Register the PP callback info with ADM database
    if (ADSP_FAILED(result = Adm_DataBaseRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Registering PP clbk failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disable MXAR output port */
      /* 2. Disconnect from MXAT input port */
      /* 3. Close MXAT input port */
      /* 4. Destroy COPP */
      /* 5. Disconnect from MXAR output port */
      goto __bailoutLBDeviceOpen1;
    }

    /* Attempt to setup the device Cmd Q for this LB COPP */
    result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, FALSE, TRUE);

    if(ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to setup devicecmdQ for COPP [%u]", unCoppID);
      goto __bailoutLBDeviceOpen1;
    }

  }

  //Send the cmd response back to the client processor.
  phCalPort->unCoppTopologyID                = pDevOpenCmdPayload->topology_id;
  phCalPort->bIsCoppInLoopBackTopology       = TRUE;
  phCalPort->bIsCoppInDeviceLoopBackTopology = FALSE;

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Opened LB COPP [%d]. LogID: 0x%lX", unCoppID, unLogID);

  result = AudDevMgr_RequestHwResources(pAdmStatSvc);

  return result;

  __bailoutLBDeviceOpen1:

  //1. Disable audio matrix output port
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing DISABLE_MT_MX_OUT_PORT cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDisableMtMxOutPort(pAdmStatSvc,
                                                         (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                         pAdmStatSvc->hRxMatrix,
                                                         pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISABLE_MT_MX_OUT_PORT cmd failed, result = %d", result);
  }

  __bailoutLBDeviceOpen2:

  //2. Disconnect from MXAT input port
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPP_DISCONNECT cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                          &((phCalPort->mtMxPort2).phMtMxInPort->portHandle),
                                          ELITE_CMD_DISCONNECT)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
  }

  __bailoutLBDeviceOpen3:

  //3. Close MXAT input port
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing DISCONNECT_MT_MX_IN_PORT cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxInPort(pAdmStatSvc,
                                                           (phCalPort->mtMxPort2).phMtMxInPort->inPortID,
                                                           pAdmStatSvc->hTxMatrix,
                                                           pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISCONNECT_MT_MX_IN_PORT cmd failed, result = %d", result);
  }

  __bailoutLBDeviceOpen4:
  __bailoutLBDeviceOpen5:

  //4. Destroy COPP
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPP_DESTROY cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                          NULL, ELITE_CMD_DESTROY_SERVICE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP_DESTROY cmd failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Waiting for COPP to join");

  qurt_elite_thread_join(coppThreadID, &result);

  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP thread join failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP thread joined");

  //5. Disconnect audio matrix output port only if it was connected to COPP */
  if ((phCalPort->mtMxPort).phMtMxOutPort)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing DISCONNECT_MT_MX_OUT_PORT cmd");

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxOutPort(pAdmStatSvc,
                                                              (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                              pAdmStatSvc->hRxMatrix,
                                                              pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISCONNECT_MT_MX_OUT_PORT cmd failed, result = %d", result);
    }
    (phCalPort->mtMxPort).phMtMxOutPort = NULL;
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
  return ADSP_EFAILED;
}

static ADSPResult Adm_ValidateDeviceLoopbackOpenParams(AdmStatSvc_InfoType *pAdmStatSvc,
                                                          adm_cmd_device_open_t *pDevOpenCmdPayload)
{
  ADSPResult  result = ADSP_EOK;

  //Check for validity of source port end_point_id_1.
  if (ADSP_EOK != afe_port_id_validation(pDevOpenCmdPayload->endpoint_id_1))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd Invalid Source endpoint_id_1 [%hu]", pDevOpenCmdPayload->endpoint_id_1);
    return ADSP_EBADPARAM;
  }

  //Check for validity of sink port end_point_id_3.
  if (ADSP_EOK != afe_port_id_validation(pDevOpenCmdPayload->endpoint_id_3))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd Invalid Sink endpoint_id_3 [%hu]", pDevOpenCmdPayload->endpoint_id_3);
    return ADSP_EBADPARAM;
  }

  // Check for validity of EID1 dev_num_channel
  if ((ADM_NUM_CHANNELS_THIRTY_TWO < pDevOpenCmdPayload->dev_num_channel_eid1)
      || ((ADM_CMD_DEVICE_OPEN_V8 != pDevOpenCmdPayload->opcode) && (ADM_NUM_CHANNELS_EIGHT < pDevOpenCmdPayload->dev_num_channel_eid1))
      || (ADM_NUM_CHANNELS_NULL == pDevOpenCmdPayload->dev_num_channel_eid1))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM rcvd invalid EID1 dev_num_channel [%hu], supports up to 8 channels", pDevOpenCmdPayload->dev_num_channel_eid1);
    return ADSP_EBADPARAM;
  }

  // Check for validity of EID3 dev_num_channel
  if ((ADM_NUM_CHANNELS_THIRTY_TWO < pDevOpenCmdPayload->dev_num_channel_eid3)
      || ((ADM_CMD_DEVICE_OPEN_V8 != pDevOpenCmdPayload->opcode) && (ADM_NUM_CHANNELS_EIGHT < pDevOpenCmdPayload->dev_num_channel_eid3))
      || (ADM_NUM_CHANNELS_NULL == pDevOpenCmdPayload->dev_num_channel_eid3))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM rcvd invalid EID3 dev_num_channel [%hu], supports up to 8 channels", pDevOpenCmdPayload->dev_num_channel_eid3);
    return ADSP_EBADPARAM;
  }

  // Check for validity of EID1 bit_width
  if(pDevOpenCmdPayload->bit_width_eid1 < ADM_BITS_PER_SAMPLE_16 || pDevOpenCmdPayload->bit_width_eid1 > ADM_BITS_PER_SAMPLE_32)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM rcvd invalid EID1 bit_width [%hu], valid range: 16-32 bits", pDevOpenCmdPayload->bit_width_eid1);
    return ADSP_EBADPARAM;
  }

  // Check for validity of EID3 bit_width
  if(pDevOpenCmdPayload->bit_width_eid3 < ADM_BITS_PER_SAMPLE_16 || pDevOpenCmdPayload->bit_width_eid3 > ADM_BITS_PER_SAMPLE_32)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM rcvd invalid EID3 bit_width [%hu], valid range: 16-32 bits", pDevOpenCmdPayload->bit_width_eid3);
    return ADSP_EBADPARAM;
  }

  // Check for validity of EID1 sample_rate
  if(ADSP_FAILED(is_valid_device_sampling_rate(pDevOpenCmdPayload->sample_rate_eid1)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM rcvd invalid EID1 sample_rate [%lu]Hz", pDevOpenCmdPayload->sample_rate_eid1);
    return ADSP_EBADPARAM;
  }

  // Check for validity of EID3 sample_rate
  if(ADSP_FAILED(is_valid_device_sampling_rate(pDevOpenCmdPayload->sample_rate_eid3)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
          "Error: ADM rcvd invalid EID3 sample_rate [%lu]Hz", pDevOpenCmdPayload->sample_rate_eid3);
    return ADSP_EBADPARAM;
  }

  if (AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT == pDevOpenCmdPayload->topology_id)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT is not supported in LPCM mode");
    return ADSP_EBADPARAM;
  }

  if(ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != pDevOpenCmdPayload->endpoint_id_2)
  {
    //Check for validity of source far port end_point_id_2.
    if (ADSP_EOK != afe_port_id_validation(pDevOpenCmdPayload->endpoint_id_2))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd Invalid Source far port endpoint_id_2 [%hu]", pDevOpenCmdPayload->endpoint_id_2);
      return ADSP_EBADPARAM;
    }

    // Check for validity of EID2 dev_num_channel
    if ((ADM_NUM_CHANNELS_THIRTY_TWO < pDevOpenCmdPayload->dev_num_channel_eid2)
        || ((ADM_CMD_DEVICE_OPEN_V8 != pDevOpenCmdPayload->opcode) && (ADM_NUM_CHANNELS_EIGHT < pDevOpenCmdPayload->dev_num_channel_eid2))
        || (ADM_NUM_CHANNELS_NULL == pDevOpenCmdPayload->dev_num_channel_eid2))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Error: ADM rcvd invalid EID2 dev_num_channel [%hu], supports up to 8 channels", pDevOpenCmdPayload->dev_num_channel_eid2);
      return ADSP_EBADPARAM;
    }

    // Check for validity of EID2 bit_width
    if(pDevOpenCmdPayload->bit_width_eid2 < ADM_BITS_PER_SAMPLE_16 || pDevOpenCmdPayload->bit_width_eid2 > ADM_BITS_PER_SAMPLE_32)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Error: ADM rcvd invalid EID2 bit_width [%hu], valid range: 16-32 bits", pDevOpenCmdPayload->bit_width_eid2);
      return ADSP_EBADPARAM;
    }

    // Check for validity of EID2 sample_rate
    if(ADSP_FAILED(is_valid_device_sampling_rate(pDevOpenCmdPayload->sample_rate_eid2)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Error: ADM rcvd invalid EID2 sample_rate [%lu]Hz", pDevOpenCmdPayload->sample_rate_eid2);
      return ADSP_EBADPARAM;
    }
  }

  return result;

}

static ADSPResult Adm_DeviceOpenCmdLPCMDeviceLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                             adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                             elite_apr_packet_t *pPkt,
                                                             NativeModeHook cbNativeMode,
                                                             uint16_t *unCreatedCoppID,
                                                             qurt_elite_queue_t *pRspQ)
{

  uint16_t                     unCoppID;
  AdmCalPort_Type              *phCalPort;
  qurt_elite_thread_t          coppThreadID;
  elite_svc_handle_t           *pCoppHandle;
  AdmDevSessionDelayParam_Type *pSessionDelayParam;

  ADSPResult result                     = ADSP_EOK;
  bool_t     bShouldAFETxBeDisconnected = FALSE;
  uint32_t   unLogID                    = 0;

  if ((ADM_CMD_DEVICE_OPEN_V7 != pDevOpenCmdPayload->opcode) && (ADM_CMD_DEVICE_OPEN_V8 != pDevOpenCmdPayload->opcode))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM rcvd payload with unsupported opCode for device loopback mode [0x%08x]", pDevOpenCmdPayload->opcode);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;
  }

  //Validate open params
  if (ADSP_EOK != Adm_ValidateDeviceLoopbackOpenParams(pAdmStatSvc, pDevOpenCmdPayload) )
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Device Loopback open failed due to invalid open params");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
    return ADSP_EBADPARAM;
  }
  unCoppID = *unCreatedCoppID;
  phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];

  // Update calport structure with validated device open params
  Adm_InitCalPort(phCalPort, pDevOpenCmdPayload );

  pSessionDelayParam = &(pAdmStatSvc->pDevSessionDelayParam[unCoppID]);

  /* Check for validity of device performance mode received */
  if (ADM_LOW_LATENCY_DEVICE_SESSION < phCalPort->unDevicePerfMode )
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: Invalid device_perf_mode in flags field [%d]", phCalPort->unDevicePerfMode);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;
  }

  //Set up some parameters for device loopback COPP
  phCalPort->unCoppDirection = RX_DIR;

  if(ADSP_EOK == elite_cmn_topo_db_is_active_topology_present(1 << AVCS_TOPO_CFG_AREA_VOICE_BIT, pDevOpenCmdPayload->topology_id))
  {
    //Voice Proc Tx block
    phCalPort->unCoppType = ADM_COPP_TYPE_VPTX;

    //Check for validity of sampling rate
    if(!Adm_IsValidSampleRateForVpTxTopo(pDevOpenCmdPayload->topology_id,pDevOpenCmdPayload->sample_rate_eid1))
    {
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    if(ADM_BITS_PER_SAMPLE_16 != pDevOpenCmdPayload->bit_width_eid1)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: Invalid PCM bit_width for VPTX  COPP [%d], ",
                pDevOpenCmdPayload->bit_width_eid1);

      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
      return ADSP_EFAILED;
    }

    uint16_t unNumChannels = 0;
    if( ADSP_FAILED(Adm_GetChannelConfigForVpTxTopo(pDevOpenCmdPayload->topology_id,
                                                    &unNumChannels,
                                                    &phCalPort->unEID1.unChannelMap[0])) )
    {
      unNumChannels = pDevOpenCmdPayload->dev_num_channel_eid1;
      for (uint16_t i = 0; i < pDevOpenCmdPayload->dev_num_channel_eid1; i++)
      {
          phCalPort->unEID1.unChannelMap[i] = pDevOpenCmdPayload->dev_channel_mapping_eid1[i];
      }
    }
    phCalPort->unEID1.unNumChannels = unNumChannels;

    MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Device LB ADM_CMD_DEVICE_OPEN, issuing CREATE_VPTX cmd, TopID: 0x%lX, fs: %lu, EP1: 0x%X, EP2: 0x%X, #mic: %lu",
           pDevOpenCmdPayload->topology_id, pDevOpenCmdPayload->sample_rate_eid1, pDevOpenCmdPayload->endpoint_id_1, pDevOpenCmdPayload->endpoint_id_2, phCalPort->unEID1.unNumChannels);

    vptx_create_params_v2_t create_param;
    memset(&create_param, 0, sizeof(vptx_create_params_v2_t));

    create_param.near_port_id      = pDevOpenCmdPayload->endpoint_id_1;
    create_param.far_port_id       = pDevOpenCmdPayload->endpoint_id_2;
    create_param.topology_id       = pDevOpenCmdPayload->topology_id;
    create_param.sampling_rate = pDevOpenCmdPayload->sample_rate_eid1;
    create_param.session_num       = unCoppID;
    create_param.shared_mem_client = admMemoryMapClient;
    create_param.num_mics          = phCalPort->unEID1.unNumChannels;
    create_param.num_ref_channels  = phCalPort->unEID2.unNumChannels;

    memscpy(&(create_param.channel_map_near),sizeof(create_param.channel_map_near),
            &(phCalPort->unEID1.unChannelMap), sizeof(phCalPort->unEID1.unChannelMap));
    memscpy(&(create_param.channel_map_far),sizeof(create_param.channel_map_far),
            &(phCalPort->unEID2.unChannelMap), sizeof(phCalPort->unEID2.unChannelMap));

    //1. Create the VPTX block.
    if (ADSP_FAILED(result = vptx_aud_create_v3((void **) &phCalPort->phDevCopp,
                                                (void **) &phCalPort->phDevCoppEcRef,
                                                &create_param)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Create VpTX failed with result=%d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

    pAdmStatSvc->unNumVpTxCoppOpenIssued++;
    if(ADM_MAX_COPP_OPEN_CTR < pAdmStatSvc->unNumVpTxCoppOpenIssued)
    {
      pAdmStatSvc->unNumVpTxCoppOpenIssued = 0;
    }

    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

    //VoiceProcTx block provides its handle.
    pCoppHandle  = phCalPort->phDevCopp;
    //VPTx thread ID. Used to destroy VPTx if cmd handler fails midway.
    coppThreadID = pCoppHandle->threadId;

    /* low latency mode for Voice copp is not supported yet. Hence default to legacy mode.*/
    phCalPort->unDevicePerfMode = ADM_LEGACY_DEVICE_SESSION;

    /* Since the VpTX module sends 20ms chunks, the port which connects to this block also configured to 20ms size buffer */

    //2. Request connection of VoiceProcTx block with Sink AFE port(RX)
    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of Device LB ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd (Sink AFE pot), EP3: 0x%X, SR %lu, num ch %lu, bit-width %lu",\
          phCalPort->unEID3.unAfePortID, phCalPort->unEID3.unSampleRate, phCalPort->unEID3.unNumChannels, phCalPort->unEID3.unBitWidth);

    if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID3.unAfePortID,
                                                   phCalPort->phDevCopp,
                                                   AFE_RX_AUD_MIXER_IN,
                                                   &(phCalPort->unEID3.phAfePort),
                                                   phCalPort->unEID3.unSampleRate,
                                                   phCalPort->unEID3.unNumChannels,
                                                   &(phCalPort->unEID3.unChannelMap[0]),
                                                   ADM_FRAME_SIZE_1MS,
                                                   ADM_HIGHEST_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                   ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                   phCalPort->unEID3.unBitWidth,
                                                   &(phCalPort->unEID3.pAfeDriftPtr),
                                                   &(pSessionDelayParam->unAFEDelay_EP3),
                                                   FALSE,
                                                   pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: Source port AFE_CONNECT_REQ cmd failed, result = %d", result);
      // Tear down the graph constructed thus far: 1.Destroy VPTx
      goto __bailoutCmdDeviceLoopbackOpen4;
    }

    //3. Provide the handle of the AFE Rx to the VoiceProcTx block via Connect cmd */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing CONNECT_VOICEPROCTX cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                            phCalPort->unEID3.phAfePort, ELITE_CMD_CONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB : Source port CONNECT_VOICEPROCTX cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect AFE Rx */
      /* 2. Destroy VPTx */
      goto __bailoutCmdDeviceLoopbackOpen3;
    }

    //4. Request connection of VoiceProcTx block with Source AFE port - for near samples
    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd, EP1: 0x%X, SR %lu, num ch %lu, bit-width %lu",\
          phCalPort->unEID1.unAfePortID, phCalPort->unEID1.unSampleRate, phCalPort->unEID1.unNumChannels, phCalPort->unEID1.unBitWidth);

    if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                   phCalPort->phDevCopp,
                                                   AFE_PP_OUT,
                                                   &(phCalPort->unEID1.phAfePort),
                                                   phCalPort->unEID1.unSampleRate,
                                                   phCalPort->unEID1.unNumChannels,
                                                   &(phCalPort->unEID1.unChannelMap[0]),
                                                   ADM_FRAME_SIZE_1MS,
                                                   ADM_HIGHEST_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                   ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                   phCalPort->unEID1.unBitWidth,
                                                   &(phCalPort->unEID1.pAfeDriftPtr),
                                                   &(pSessionDelayParam->unAFEDelay_EP1),
                                                   FALSE,
                                                   pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: Sink port AFE_CONNECT_REQ cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect VPTX COPP from AFE Rx port */
      /* 2. Disconnect AFE Rx */
      /* 3. Destroy VPTx */
      goto __bailoutCmdDeviceLoopbackOpen2;
      return ADSP_EFAILED;
    }

    //5. If required, request connection of VoiceProcTx block with second AFE port - for far samples
    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
    {
      MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd (AFE EC Ref port (Rx port)), EP2: 0x%X, SR %lu, num ch %lu, bit-width %lu",
            phCalPort->unEID2.unAfePortID, phCalPort->unEID2.unSampleRate, phCalPort->unEID2.unNumChannels, phCalPort->unEID2.unBitWidth);

      if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                     phCalPort->phDevCoppEcRef,
                                                     AFE_PP_OUT,
                                                     &(phCalPort->unEID2.phAfePort),
                                                     phCalPort->unEID2.unSampleRate,
                                                     phCalPort->unEID2.unNumChannels,
                                                     &(phCalPort->unEID2.unChannelMap[0]),
                                                     ADM_FRAME_SIZE_1MS,
                                                     ADM_HIGHEST_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                     ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                     phCalPort->unEID2.unBitWidth,
                                                     &(phCalPort->unEID2.pAfeDriftPtr),
                                                     &(pSessionDelayParam->unAFEDelay_EP2),
                                                     FALSE,
                                                     pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB : AFE_CONNECT_REQ cmd (AFE EC Ref port (Rx)) failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. Disable AFE Tx port */
        /* 2. Disconnect VPTX COPP from AFE RX port */
        /* 3. Disconnect AFE Rx port */
        /* 4. Destroy VPTx */
        /* 5. Disconnect AFE Tx port */
        goto __bailoutCmdDeviceLoopbackOpen1;
      }
    }

    //7. Send a Start cmd to VPTx */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing START_VPTx cmd");
    if (ADSP_FAILED(result = Adm_SendCmdStartCopp(pCoppHandle, pRspQ,
                                                  (void*)(phCalPort->unEID1.pAfeDriftPtr), (void*)(phCalPort->unEID2.pAfeDriftPtr))))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: START_VPTx cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. if VPTx was connected to AFE Rx (for far-end samples), disable AFE Rx port */
      /* 2. Disable AFE Tx port */
      /* 3. Disconnect VPTX COPP from AFE RX port*/
      /* 4. Disconnect AFE Rx port */
      /* 5. Destroy VPTx */
      /* 6. Disconnect AFE Tx port */
      /* 7. if VPTx was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
      goto __bailoutCmdDeviceLoopbackOpen0;
    }

    //8. Attempt to setup the device cmd Q for the VpTx Copp
    result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, FALSE, TRUE);

    if(ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to setup devicecmdQ for COPP [%u]", unCoppID);
      goto __bailoutCmdDeviceLoopbackOpen0;
    }
  }
  else
  {
    //Device Loop back Audio COPP...
    phCalPort->unCoppType = ADM_COPP_TYPE_AUDIO_COPP;

    //For mono or stereo opens, if PCM_CHANNEL_INVALID was set, then set them to default mono/stereo channels
    if((ADM_NUM_CHANNELS_MONO == phCalPort->unEID1.unNumChannels) && (PCM_CHANNEL_INVALID == phCalPort->unEID1.unChannelMap[0]))
    {
      phCalPort->unEID1.unChannelMap[0] = PCM_CHANNEL_C;
    }

    if((ADM_NUM_CHANNELS_STEREO == phCalPort->unEID1.unNumChannels) &&
        ((PCM_CHANNEL_INVALID == phCalPort->unEID1.unChannelMap[0]) || (PCM_CHANNEL_INVALID == phCalPort->unEID1.unChannelMap[1])))
    {
      phCalPort->unEID1.unChannelMap[0] = PCM_CHANNEL_L;
      phCalPort->unEID1.unChannelMap[1] = PCM_CHANNEL_R;
    }

    //For non-mono, non-stereo types, PCM_CHANNEL_INVALID is invalid. So is any mapping greater than MAX_CHANNEL_MAPPING_NUMBER
    for (uint16_t i = 0; i < phCalPort->unEID1.unNumChannels; i++)
    {
      if ((MAX_CHANNEL_MAPPING_NUMBER < phCalPort->unEID1.unChannelMap[i]) || (PCM_CHANNEL_INVALID == phCalPort->unEID1.unChannelMap[i]))
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid device channel mapping %d for channel #%d", phCalPort->unEID1.unChannelMap[i], (i + 1));
        elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
        return ADSP_EFAILED;
      }
    }

    uint32_t unCoppAfeFrameSizeInSamples;
    elite_svc_get_frame_size(pDevOpenCmdPayload->sample_rate_eid1, &unCoppAfeFrameSizeInSamples);

    if (ADM_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
    {
      phCalPort->unCoppNumAfeFrames = ADM_LL_NUM_AFE_FRAMES;
    }
    else
    {
      phCalPort->unCoppNumAfeFrames = ADM_LEGACY_NUM_AFE_FRAMES;
    }

#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE before creating COPP Svc %d",
          qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

    qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

    //Increment the Number of RX Audio COPP opened
    pAdmStatSvc->unNumRxAudioCoppOpenIssued++;
    if(ADM_MAX_COPP_OPEN_CTR < pAdmStatSvc->unNumRxAudioCoppOpenIssued)
    {
      pAdmStatSvc->unNumRxAudioCoppOpenIssued = 0;
    }
    //Get a unique Log ID
    unLogID = ADM_LOG_ID_BASE_TX + (pAdmStatSvc->unNumRxAudioCoppOpenIssued << 4);

    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"ADM: As part of Device LB ADM_CMD_DEVICE_OPEN, issuing CREATE_COPP cmd, topologyID: 0x%lX"
          "device_perf_mode is [%hu] & afe_frame_size is [%lu] & COPP Buffer Num Frames is [%lu]",
          pDevOpenCmdPayload->topology_id, phCalPort->unDevicePerfMode, unCoppAfeFrameSizeInSamples,
          phCalPort->unCoppNumAfeFrames);

    //1. Create the Audio COPP.
    result = Adm_CreatePPSvc(pAdmStatSvc,
                             phCalPort,
                             pSessionDelayParam,
                             pDevOpenCmdPayload->topology_id,
                             DYNA_SVC_PP_TYPE_COPP,
                             unLogID);
    if (ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: CREATE_COPP cmd failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }

    //COPP provides its handle
    pCoppHandle  = phCalPort->phDevCopp;
    //COPP thread ID. Used to destroy COPP if cmd handler fails midway
    coppThreadID = pCoppHandle->threadId;

#ifdef QURT_ELITE_DBG_HEAP_CONSUMPTION
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "HEAPUSE after creating COPP Svc %d",
          qurt_elite_globalstate.heap_stats.curr_heap);
#endif /* QURT_ELITE_DBG_HEAP_CONSUMPTION */

    /* 2. Specify output media format to COPP */
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM Device LB: cfg'ing to output %d channels", phCalPort->unEID3.unNumChannels);

    if (ADSP_FAILED(result = adm_config_pp_output_media_format(pCoppHandle, pRspQ,
                                                               phCalPort->unEID3.unNumChannels,
                                                               &(phCalPort->unEID3.unChannelMap[0]),
                                                               phCalPort->unEID3.unSampleRate,
                                                               phCalPort->unEID3.unBitWidth)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: PP_output_media_fmt cmd failed, result = %d", result);
      // Tear down the graph constructed thus far: 1.Destroy Audio COPP
      goto __bailoutCmdDeviceLoopbackOpen4;
    }

    //3. Request connection of Audio COPP with Sink AFE port(RX)
    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of device LB ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd(Sink port), EP3: 0x%X, SR %lu, num ch %lu, bit-width %lu", \
          phCalPort->unEID3.unAfePortID, phCalPort->unEID3.unSampleRate, phCalPort->unEID3.unNumChannels, phCalPort->unEID3.unBitWidth);

    if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID3.unAfePortID,
                                                   phCalPort->phDevCopp,
                                                   AFE_RX_AUD_MIXER_IN,
                                                   &(phCalPort->unEID3.phAfePort),
                                                   phCalPort->unEID3.unSampleRate,
                                                   phCalPort->unEID3.unNumChannels,
                                                   &(phCalPort->unEID3.unChannelMap[0]),
                                                   phCalPort->unCoppNumAfeFrames,
                                                   ADM_NORMAL_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                   ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                   phCalPort->unEID3.unBitWidth,
                                                   &(phCalPort->unEID3.pAfeDriftPtr),
                                                   &(pSessionDelayParam->unAFEDelay_EP3),
                                                   FALSE,
                                                   pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: AFE_CONNECT_REQ cmd failed, result = %d", result);
      // Tear down the graph constructed thus far: 1.Destroy COPP
      goto __bailoutCmdDeviceLoopbackOpen4;
    }

    //4. Provide the handle of the AFE Rx to the Audio COPP block via Connect cmd */
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing CONNECT_COPP cmd");

    if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                            phCalPort->unEID3.phAfePort, ELITE_CMD_CONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM device LB: CONNECT_COPP cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect AFE Rx */
      /* 2. Destroy COPP */
      goto __bailoutCmdDeviceLoopbackOpen3;
    }

    //5. Request connection of Audio COPP with Source AFE port - for near samples
    MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of Device LB ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd(source near port), EP1: 0x%X, SR %lu, num ch %lu, bit-width %lu", \
          phCalPort->unEID1.unAfePortID, phCalPort->unEID1.unSampleRate, phCalPort->unEID1.unNumChannels, phCalPort->unEID1.unBitWidth);
    if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                   phCalPort->phDevCopp,
                                                   AFE_PP_OUT,
                                                   &(phCalPort->unEID1.phAfePort),
                                                   phCalPort->unEID1.unSampleRate,
                                                   phCalPort->unEID1.unNumChannels,
                                                   &(phCalPort->unEID1.unChannelMap[0]),
                                                   phCalPort->unCoppNumAfeFrames,
                                                   ADM_NORMAL_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                   ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                   phCalPort->unEID1.unBitWidth,
                                                   &(phCalPort->unEID1.pAfeDriftPtr),
                                                   &(pSessionDelayParam->unAFEDelay_EP1),
                                                   FALSE,
                                                   pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: AFE_CONNECT_REQ cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. Disconnect COPP from AFE Rx port */
      /* 2. Disconnect AFE Rx */
      /* 3. Destroy COPP */
      goto __bailoutCmdDeviceLoopbackOpen2;
    }

    //6. If required, request connection of Audio COPP with second AFE port - for far samples
    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
    {
      MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing AFE_CONNECT_REQ cmd"
            "(AFE EC Ref port (Rx port)), EP2: 0x%X, SR %lu, num ch %lu, bit-width %lu",
            phCalPort->unEID2.unAfePortID, phCalPort->unEID2.unSampleRate, phCalPort->unEID2.unNumChannels, phCalPort->unEID2.unBitWidth);

      if (ADSP_FAILED(result = Adm_SendCmdConnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                     phCalPort->phDevCoppEcRef,
                                                     AFE_PP_OUT,
                                                     &(phCalPort->unEID2.phAfePort),
                                                     phCalPort->unEID2.unSampleRate,
                                                     phCalPort->unEID2.unNumChannels,
                                                     &(phCalPort->unEID2.unChannelMap[0]),
                                                     phCalPort->unCoppNumAfeFrames,
                                                     ADM_NORMAL_BUFFERING_BETWEEN_AFE_AND_CLIENT,
                                                     ELITEMSG_CUSTOM_AFECONNECT_REQ,
                                                     phCalPort->unEID2.unBitWidth,
                                                     &(phCalPort->unEID2.pAfeDriftPtr),
                                                     &(pSessionDelayParam->unAFEDelay_EP2),
                                                     FALSE,
                                                     pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_CONNECT_REQ cmd (AFE EC Ref port (Rx)) failed, result = %d", result);
        /* Tear down the graph constructed thus far */
        /* 1. Disable AFE Tx port */
        /* 2. Disconnect COPP from AFE RX port */
        /* 3. Disconnect AFE Rx port */
        /* 4. Destroy COPP */
        /* 5. Disconnect AFE Tx port */
        goto __bailoutCmdDeviceLoopbackOpen1;
      }
    }

    //7. Send a RUN cmd to COPP
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of device LB ADM_CMD_DEVICE_OPEN, issuing RUN_COPP cmd");

    if (ADSP_FAILED(result = Adm_SendCmdRunCopp(pCoppHandle, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: RUN_COPP cmd failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. if COPP was connected to AFE Rx (for far-end samples), disable AFE Rx port */
      /* 2. Disable AFE Tx port */
      /* 3. Disconnect COPP from AFE RX port*/
      /* 4. Disconnect AFE Rx port */
      /* 5. Destroy COPP */
      /* 6. Disconnect AFE Tx port */
      /* 7. if COPP was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
      goto __bailoutCmdDeviceLoopbackOpen0;
    }

    //Register the PP callback info with ADM database
    if (ADSP_FAILED(result = Adm_DataBaseRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device LB: Registering PP clbk failed, result = %d", result);
      /* Tear down the graph constructed thus far */
      /* 1. if COPP was connected to AFE Rx (for far-end samples), disable AFE Rx port */
      /* 2. Disable AFE Tx port */
      /* 3. Disconnect COPP from AFE RX port*/
      /* 4. Disconnect AFE Rx port */
      /* 5. Destroy COPP */
      /* 6. Disconnect AFE Tx port */
      /* 7. if COPP was connected to AFE Rx (for far-end samples), disconnect AFE Rx port */
      goto __bailoutCmdDeviceLoopbackOpen0;
    }
    //8. Attempt to setup the device cmd Q for the VpTx Copp
    result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, FALSE, TRUE);

    if(ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to setup devicecmdQ for COPP [%u]", unCoppID);
      goto __bailoutCmdDeviceLoopbackOpenCmdQ;
    }
  }

  //Send the cmd response back to the client processor.
  phCalPort->unCoppTopologyID                = pDevOpenCmdPayload->topology_id;
  phCalPort->bIsCoppInLoopBackTopology       = FALSE;
  phCalPort->bIsCoppInDeviceLoopBackTopology = TRUE;

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Opened Device LB COPP [%d]. LogID: 0x%lX", unCoppID, unLogID);

  result = AudDevMgr_RequestHwResources(pAdmStatSvc);

  return result;

  __bailoutCmdDeviceLoopbackOpenCmdQ:

  if(ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, calling DEREGISTER PP CB");
    if(ADSP_FAILED(result = Adm_DataBaseDeRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: function DEREGISTER PP CB failed with result = %d", result);
    }
  }

  __bailoutCmdDeviceLoopbackOpen0:

  //If COPP is connected to AFE Rx (for far-end samples), disable AFE Rx port
  if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISABLE cmd (AFE Rx), EP2: 0x%X", phCalPort->unEID2.unAfePortID);

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc,
                                                      phCalPort->unEID2.unAfePortID,
                                                      phCalPort->unEID2.phAfePort,
                                                      ELITEMSG_CUSTOM_AFECLIENTDISABLE,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Rx) failed, result = %d", result);
    }
  }

  __bailoutCmdDeviceLoopbackOpen1:

  //1. Disable AFE Tx port
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISABLE cmd (AFE Tx), EP1: 0x%X", phCalPort->unEID1.unAfePortID);

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc,
                                                    phCalPort->unEID1.unAfePortID,
                                                    phCalPort->unEID1.phAfePort,
                                                    ELITEMSG_CUSTOM_AFECLIENTDISABLE,
                                                    pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISABLE cmd (AFE Tx) failed, result = %d", result);
  }
  bShouldAFETxBeDisconnected = TRUE;

  __bailoutCmdDeviceLoopbackOpen2:

  //2. Disconnect COPP from AFE Rx
  if (ADM_COPP_TYPE_AUDIO_COPP == phCalPort->unCoppType)
  {
    //Send ELITE_CMD_DISCONNECT to audio COPP.
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPP_DISCONNECT cmd");

    if (ADSP_FAILED(result  = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                             phCalPort->unEID3.phAfePort,
                                             ELITE_CMD_DISCONNECT)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
    }
  }
  else
  {
    //Send ELITE_CMD_STOP_SERVICE to VPTx COPP.
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing VPTx_STOP cmd");

    if (ADSP_FAILED(result  = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                             phCalPort->unEID3.phAfePort,
                                             ELITE_CMD_STOP_SERVICE)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: VPTx_STOP cmd failed, result = %d", result);
    }
  }

  __bailoutCmdDeviceLoopbackOpen3:

  //3. Disconnect AFE Rx
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISCONNECT cmd, EP3: 0x%X", phCalPort->unEID3.unAfePortID);

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc,
                                                    phCalPort->unEID3.unAfePortID,
                                                    phCalPort->unEID3.phAfePort,
                                                    ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                    pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd failed, result = %d", result);
  }
  __bailoutCmdDeviceLoopbackOpen4:

  //4. Destroy COPP
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing COPP_DESTROY cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(pCoppHandle, pRspQ,
                                          NULL, ELITE_CMD_DESTROY_SERVICE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP_DESTROY cmd failed, result = %d", result);
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Waiting for COPP to join");

  qurt_elite_thread_join(coppThreadID, &result);

  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP thread join failed, result = %d", result);
  }
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP thread joined");

  //5. Disconnect from AFE Tx
  if (TRUE == bShouldAFETxBeDisconnected)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISCONNECT cmd (AFE Tx)");

    if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID1.unAfePortID,
                                                      phCalPort->unEID1.phAfePort,
                                                      ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                      pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Tx) failed, result = %d", result);
    }

    //6. if COPreP is VPTX and it is connected to AFE Rx (for far-end samples), disconnect from AFE Rx
    if (ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
    {
      MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of freeing up resources, issuing AFE_PORT_DISCONNECT cmd (AFE Rx)");
      if (ADSP_FAILED(result = Adm_SendCmdDisconnectAFE(pAdmStatSvc, phCalPort->unEID2.unAfePortID,
                                                        phCalPort->unEID2.phAfePort,
                                                        ELITEMSG_CUSTOM_AFEDISCONNECT_REQ,
                                                        pRspQ)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AFE_PORT_DISCONNECT cmd (AFE Rx) failed, result = %d", result);
      }
    }
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
  return ADSP_EFAILED;
}

static ADSPResult Adm_DeviceOpenCmdCompressedHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                     adm_cmd_device_open_t  *pDevOpenCmdPayload,
                                                     elite_apr_packet_t *pPkt,
                                                     NativeModeHook cbNativeMode,
                                                     uint16_t *unCreatedDeviceID,
                                                     qurt_elite_queue_t *pRspQ)
{
  uint16_t        device_id;
  uint32_t        num_channels;
  uint32_t        sampling_rate;
  uint32_t        bits_per_sample;
  uint32_t        device_id_offset;
  ComprCoppInfo_t *pComprCoppInfo;

  uint16_t          afe_port_id = pDevOpenCmdPayload->endpoint_id_1;
  ADSPResult        result      = ADSP_EOK;
  adm_client_type_t eClient     = eASM_TYPE;

  //Check for validity of end_point_id.
  if (ADSP_EOK != afe_port_id_validation(afe_port_id))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid endpoint_id_1 [0x%X]", afe_port_id);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EFAILED);
    return ADSP_EFAILED;
  }

  if ((AUDPROC_TOPOLOGY_ID_COMPRESSED_DEFAULT != pDevOpenCmdPayload->topology_id)
      && (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE != pDevOpenCmdPayload->topology_id))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid topology ID (0x%lX) for compressed use case", pDevOpenCmdPayload->topology_id);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
    return ADSP_EUNSUPPORTED;
  }

  if(ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX == pDevOpenCmdPayload->mode_of_operation)
  {
    if (AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE != pDevOpenCmdPayload->topology_id)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid topology ID (0x%lX) for compressed use case in Tx direction",
            pDevOpenCmdPayload->topology_id);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EUNSUPPORTED);
      return ADSP_EUNSUPPORTED;
    }

    pComprCoppInfo = &(pAdmStatSvc->txStRtrParams.compr_copp_info[0]);
    device_id_offset = ADM_COMPRESSED_MIN_TX;
  }
  else
  {
    pComprCoppInfo = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[0]);
    device_id_offset = ADM_COMPRESSED_MIN_RX;
  }

  //device Id to return in the command response
  device_id = *unCreatedDeviceID;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Device Open Compressed");

  num_channels = pDevOpenCmdPayload->dev_num_channel_eid1;
  sampling_rate = pDevOpenCmdPayload->sample_rate_eid1;
  bits_per_sample = pDevOpenCmdPayload->bit_width_eid1;

  if(((2 != num_channels) && (8 != num_channels)) || (0 == sampling_rate)|| (ADM_SAMPLING_RATE_MAX < sampling_rate))
  {
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
          "ADM: ADM Device Open Compressed, Invalid number of channels or sampling rate, num_channels = %lu, sampling_rate = %lu",
          num_channels, sampling_rate);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, ADSP_EBADPARAM);
    return ADSP_EBADPARAM;
  }

  if(ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX == pDevOpenCmdPayload->mode_of_operation)
  {
    //session_id can be set to 0 for device open since no connection to stream side is required
    result = Adm_RxStRtrAfeConnectCmdHandler(pAdmStatSvc, TRUE, 0, afe_port_id,
                                             num_channels, sampling_rate,bits_per_sample,
                                             pDevOpenCmdPayload->topology_id,device_id,
                                             admMemoryMapClient, pPkt, eClient,
                                             pRspQ);

    if (ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error %d in RX StRtr-AFE Connect", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
  }
  else if(ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX == pDevOpenCmdPayload->mode_of_operation)
  {
    //session_id can be set to 0 for device open since no connection to stream side is required
    result = Adm_TxStRtrAfeConnectCmdHandler(pAdmStatSvc, TRUE, 0, afe_port_id,
                                             num_channels, sampling_rate,
                                             AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE, device_id, eClient,
                                             pRspQ);

    if (ADSP_FAILED(result))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error %d in TX StRtr-AFE Connect", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Rcvd invalid Mode of Operation [%d]",pDevOpenCmdPayload->mode_of_operation);
    result = ADSP_EBADPARAM;
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Opened Compressed AFE port [0x%X]", afe_port_id);

  return result;
}

static  ADSPResult Adm_DeviceCloseCmdLPCMLoopBackHandler(AdmStatSvc_InfoType *pAdmStatSvc, elite_apr_packet_t *pPkt,
                                                         qurt_elite_queue_t *pRspQ)
{
  int                          joinResult;
  uint16_t                     unCoppID;
  elite_svc_handle_t           **pphCopp;
  AdmCalPort_Type              *phCalPort;
  AdmDevSessionDelayParam_Type *pSessionDelayParam;
  qurt_elite_thread_t          coppThreadID;

  ADSPResult       result = ADSP_EOK;
  elite_apr_port_t port   = elite_apr_if_get_dst_port(pPkt);

  unCoppID           = ADM_GET_COPP_ID(port);
  phCalPort          = &pAdmStatSvc->deviceCalPort[unCoppID];
  pSessionDelayParam = &(pAdmStatSvc->pDevSessionDelayParam[unCoppID]);
  pphCopp            = &(phCalPort->phDevCopp);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing LB ADM_CMD_DEVICE_CLOSE_V5, COPP ID = %d", unCoppID);


  /**************************************************************************************/
  /* Sequence to close LoopBack path COPP:                                              */
  /* 1. Disable RX matrix output port                                                   */
  /* 2. Disconnect COPP from MXAT input port                                            */
  /* 3. Close MXAT input port                                                           */
  /* 4. Destroy COPP                                                                    */
  /* 5. Disconnect RX matrix output  port                                               */
  /**************************************************************************************/

  //Step 1: Disable MXAR output port
  elite_svc_handle_t *pMtMxHandle = pAdmStatSvc->hRxMatrix;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of LB ADM_CMD_DEVICE_CLOSE, issuing DISABLE_MT_MX_OUT_PORT cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDisableMtMxOutPort(pAdmStatSvc,
                                                         (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                         pMtMxHandle, pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISABLE_MT_MX_OUT_PORT cmd failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Step 2: Send ELITE_CMD_DISCONNECT to audio COPP.
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of LB ADM_CMD_DEVICE_CLOSE, issuing COPP_DISCONNECT cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                          &((phCalPort->mtMxPort2).phMtMxInPort->portHandle), ELITE_CMD_DISCONNECT)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP_DISCONNECT cmd failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Step 3: Now, close audio matrix input port. This will make sure it returns PP's bufs back to PP before PP can be destroyed.
  elite_svc_handle_t *pMtMxHandle2 = pAdmStatSvc->hTxMatrix;
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of LB ADM_CMD_DEVICE_CLOSE, issuing CLOSE_MT_MX_IN_PORT cmd");

  if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxInPort(pAdmStatSvc,
                                                           (phCalPort->mtMxPort2).phMtMxInPort->inPortID,
                                                           pMtMxHandle2, pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: CLOSE_MT_MX_IN_PORT cmd failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Step4: Destroy COPP
  //Store the COPP's thread ID before destroying it, so it can be used later for joining.
  coppThreadID = (*pphCopp)->threadId;
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of LB ADM_CMD_DEVICE_CLOSE, issuing COPP_DESTROY cmd");

  if (ADSP_FAILED(result = AdmSendCoppMsg(*pphCopp, pRspQ,
                                          NULL, ELITE_CMD_DESTROY_SERVICE)))
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP_DESTROY cmd failed");
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Step 5: Disconnect MXAR output port
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of LB ADM_CMD_DEVICE_CLOSE, issuing DISCONNECT_MT_MX_OUT_PORT cmd");
  if (ADSP_FAILED(result = Adm_SendCmdDisconnectMtMxOutPort(pAdmStatSvc,
                                                            (phCalPort->mtMxPort).phMtMxOutPort->outPortID,
                                                            pMtMxHandle, pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: DISCONNECT_MT_MX_OUT_PORT cmd failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }
  (phCalPort->mtMxPort).phMtMxOutPort = NULL;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "All cmds to stop LB Device in ADM_CMD_DEVICE_CLOSE have been issued");
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: As part of LB ADM_CMD_DEVICE_CLOSE Waiting for COPP to join");

  qurt_elite_thread_join(coppThreadID, &joinResult);

  if (ADSP_FAILED(joinResult))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: COPP thread join failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return joinResult;
  }

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: COPP thread joined in Device in ADM_CMD_DEVICE_CLOSE ");

  //De-register the PP callback info with ADM database.
  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of ADM_CMD_DEVICE_CLOSE, de-registering PP clbk");

  if (ADSP_FAILED(result = Adm_DataBaseDeRegisterPPCb(unCoppID, phCalPort->structPPCallbackInfo, FALSE)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: De-registering PP clbk failed, result = %d", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
    return result;
  }

  //Remove this Device ID (COPP ID) from any existing session mapping masks
  Adm_RemoveCoppIDFromSessionMappingMask(pAdmStatSvc, unCoppID, 0);
  Adm_RemoveCoppIDFromSessionMappingMask(pAdmStatSvc, unCoppID, 1);

  uint16_t  unCoppDirection = phCalPort->unCoppDirection;

  pSessionDelayParam->unCoppBufDelay = 0;
  pSessionDelayParam->unCoppAlgDelay = 0;
  pSessionDelayParam->unAFEDelay_EP1 = 0;
  pSessionDelayParam->unAFEDelay_EP2 = 0;
  pSessionDelayParam->unAFEDelay_EP3 = 0;
  *pphCopp = NULL;

  if(RX_DIR == unCoppDirection)
  {
    // Detect primary device of all active streams and devices.
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "As part of ADM_CMD_DEVICE_CLOSE, updating primary device/port");

    if (ADSP_FAILED(result = Adm_DetectAndUpdatePrimaryDevicePcm(pAdmStatSvc, pRspQ)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: updating primary device/port failed, result = %d", result);
      elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
      return result;
    }
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: LB COPP %d closed.", unCoppID);

  result = AudDevMgr_RequestHwResources(pAdmStatSvc);

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}


static ADSPResult Adm_AprStreamDeviceMapRoutingsHandler(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  AdmStatSvc_InfoType                *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  adm_cmd_stream_device_map_routings_v5_t      *pRoutingPayload;
  ADSPResult result = ADSP_EOK;

  //adm_cmd_stream_device_map_routings_v5_t and adm_cmd_stream_device_unmap_routings_v5_t
  //are the same structure currently, so it is ok to typecast one as the other
  pRoutingPayload = (adm_cmd_stream_device_map_routings_v5_t*)elite_apr_if_get_payload_ptr(pPkt);

  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_STREAM_DEVICE_(UN)MAP_ROUTINGS_V5, mode = %lu, num sessions = %lu",
        pRoutingPayload->mode, pRoutingPayload->num_sessions);

  if((ADM_COMPRESSED_AUDIO_OUT == pRoutingPayload->mode) || (ADM_COMPRESSED_AUDIO_IN == pRoutingPayload->mode))
  {
    result = Adm_StRtrStreamDeviceMapRoutingsHandler(pAdmStatSvc, pRoutingPayload, pPkt->opcode, eASM_TYPE);
  }
  else if (ADM_LSM_IN == pRoutingPayload->mode)
  {
    result = Adm_AprMtMxMapRoutingsHandler(pAudStatAdmSvc,pPkt,eLSM_TYPE);
    return result;
    //Command is already ended in the MtMxMapRouting Handler. This will avoid duplication.
  }
  else if ((ADM_LPCM_AUDIO_IN == pRoutingPayload->mode) || (ADM_LPCM_AUDIO_OUT == pRoutingPayload->mode))
  {
    result = Adm_AprMtMxMapRoutingsHandler(pAudStatAdmSvc,pPkt,eASM_TYPE);
    return result;
    //Command is already ended in the MtMxMapRouting Handler. This will avoid duplication.
  }
  else
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Invalid mode (%lu) received in ADM_CMD_STREAM_DEVICE_(UN)MAP_ROUTING", pRoutingPayload->mode);
    result = ADSP_EUNSUPPORTED;
  }

  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);
  return result;
}

static ADSPResult Adm_ReCheckReCfgOfConnIpPorts(AdmStatSvc_InfoType *pAudStatAdmSvc, uint16_t unCoppIDRecfg, uint32_t unTargetSampleRate)
{
  uint16_t unIndex = 0, unSessionID = 0;
  ADSPResult result = ADSP_EOK;
  uint32_t unInPortID = 0;
  AdmStreamSessionInfo_Type *pSessionInfo;
  uint32_t *pSessionMappingMask;

  for (unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    pSessionMappingMask = &(pAudStatAdmSvc->rxsessionMappingMask[unIndex]);

    if ((1 << unCoppIDRecfg) & (*pSessionMappingMask))
    {
      unSessionID = pAudStatAdmSvc->rxIndexToSessionStreamID[unIndex];
      unInPortID = pAudStatAdmSvc->sessionIDToRxMtMxInPortIDMap[unIndex];
      pSessionInfo = &(pAudStatAdmSvc->rxStreamSessionInfo[unIndex]);

      MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: RX Index %d, SessionID 0x%hX,  i/p port %lu conn to COPPID %d, SessSR %lu, TgtCOPPSR %lu",
            unIndex, unSessionID, unInPortID, unCoppIDRecfg, pSessionInfo->unSessionSampleRate, unTargetSampleRate);

      if (pSessionInfo->unSessionSampleRate != unTargetSampleRate)
      {
        //Move audio matrix input port state to READY
        MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On SessionID 0x%hX, moving the audio matrix i/p %lu to READY state, expected fs: %lu",
              unSessionID, unInPortID, unTargetSampleRate);
        if (ADSP_FAILED(result = Adm_SendCmdMtMxPortStateChange(pAudStatAdmSvc,
                                                                unInPortID,
                                                                MATRIX_MIXER_PORT_DIR_INPUT,
                                                                pAudStatAdmSvc->hRxMatrix, unTargetSampleRate)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdMtMxPortStateChange failed, result = %d", result);
          return result;
        }

        //Send message to ASM with sampling rate information
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: On SessionID 0x%hX, setting session sampling rate: %lu via ASM", unSessionID, unTargetSampleRate);
        if (ADSP_FAILED(result = Adm_SendCmdAsmSetOutputSamplingRate(pAudStatAdmSvc,
                                                                     unTargetSampleRate,
                                                                     unSessionID)))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Adm_SendCmdAsmSetOutputSamplingRate failed, result = %d", result);
          return result;
        }

        //Update connected session sampling rate.
        pSessionInfo->unSessionSampleRate = unTargetSampleRate;
      }
    }
  }

  return result;
}

void Adm_ResetCompressedSessionMappingMask(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t sessionID, uint32_t strRtrID, adm_client_type_t eClient)
{
  uint32_t                *pSessionMappingMask;

  //Kw fix
  if (eLSM_TYPE == eClient)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM_RCSMM: Mapping mask received for LSM session. Unsupported");
    return ;
  }

  uint16_t unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)strRtrID, sessionID, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    return;
  }

  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  if(RX_STRTR_ID == strRtrID)
  {
    pSessionMappingMask = &(pAdmStatSvc->rxCompressedSessionMappingMask[unIndex]);
  }
  else
  {
    pSessionMappingMask = &(pAdmStatSvc->txCompressedSessionMappingMask[unIndex]);
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RCSMM Entr: Mapping mask: %lu", *pSessionMappingMask);

  *pSessionMappingMask = 0;

  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_RCSMM Exit: Mapping mask: %lu", *pSessionMappingMask);
}

void Adm_UpdateCompressedSessionMappingMask(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t sessionID, uint16_t unCoppID, uint32_t strRtrID, adm_ucsmm_mode_t mode, adm_client_type_t eClient)
{
  uint32_t  *pSessionMappingMask;
  uint16_t unCoppIDIndex, offset;

  //Kw fix
  if (eLSM_TYPE == eClient)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM_UCSMM: Mapping mask received for LSM session. Unsupported");
    return ;
  }

  uint16_t unIndex = Adm_SessionStreamIDToIndex(pAdmStatSvc, (uint16_t)strRtrID, sessionID, eClient);
  if(ADM_INVALID_INDEX == unIndex)
  {
    return;
  }
  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  if(RX_STRTR_ID == strRtrID)
  {
    pSessionMappingMask = &(pAdmStatSvc->rxCompressedSessionMappingMask[unIndex]);
    offset = ADM_COMPRESSED_MIN_RX;
  }
  else
  {
    pSessionMappingMask = &(pAdmStatSvc->txCompressedSessionMappingMask[unIndex]);
    offset = ADM_COMPRESSED_MIN_TX;
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_UCSMM Entr: Mapping mask: %lu",*pSessionMappingMask);

  unCoppIDIndex = unCoppID - offset;

  if(ADM_UCSMM_CONNECT == mode)
  {
    *pSessionMappingMask |= (1LL << unCoppIDIndex);
  }
  else
  {
    *pSessionMappingMask &= ~(1LL << unCoppIDIndex);
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM_UCSMM Exit: Mapping mask: %lu", *pSessionMappingMask);
  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
}

void Adm_RemoveCoppIDFromCompressedSessionMappingMask(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t unCoppID, uint16_t unCoppDirection)
{
  uint32_t  *pSessionMappingMask;
  uint16_t unCoppIDIndex, offset;

  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  if(RX_DIR == unCoppDirection)
  {
    pSessionMappingMask = &(pAdmStatSvc->rxCompressedSessionMappingMask[0]);
    offset = ADM_COMPRESSED_MIN_RX;
  }
  else
  {
    pSessionMappingMask = &(pAdmStatSvc->txCompressedSessionMappingMask[0]);
    offset = ADM_COMPRESSED_MIN_TX;
  }

  unCoppIDIndex = unCoppID - offset;
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "removing COPP ID: %d, COPP ID Index: %d from session mapping mask",unCoppID, unCoppIDIndex);

  for (uint16_t unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    *pSessionMappingMask &= ~(1LL << unCoppIDIndex);
    pSessionMappingMask++;
  }

  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
}

/* This function gives primary devices among devices present in cluster*/
static uint16_t Adm_GetPrimaryDevicePcm(AdmStatSvc_InfoType *pAdmStatSvc, uint32_t unDeviceClusterMask)
{
  uint16_t unPrimaryDevice = ADM_INVALID_PRIMARY_DEVICE, unNumConnectedSessions = 0;
  AdmCalPort_Type *phCalPort = NULL;

  // find out non loopback, non psuedo port device that is connected to maximum sessions
  uint32_t unMask = unDeviceClusterMask;
  while (unMask)
  {
    //check for device that has no resampling in COPP
    //if all devices have resampling, primary device will be zero.
    uint16_t unBitPosition = Q6_R_ct0_R(unMask);
    unMask ^= 1LL << unBitPosition;
    phCalPort = &pAdmStatSvc->deviceCalPort[unBitPosition];

    if ((FALSE == phCalPort->bIsCoppInLoopBackTopology) &&
        (FALSE == phCalPort->bIsCoppInDeviceLoopBackTopology) &&
        (FALSE == phCalPort->bIsCoppConnectedToPseudoPort) &&
        (phCalPort->unMtMxSampleRate == phCalPort->unEID1.unSampleRate) &&
        (phCalPort->unNumConnectedSessionsRx > unNumConnectedSessions))
    {
      unPrimaryDevice = unBitPosition;
      unNumConnectedSessions = phCalPort->unNumConnectedSessionsRx;
    }
  }
  if ( ADM_INVALID_PRIMARY_DEVICE == unPrimaryDevice)
  {
    //check for primary device (as all devices involve resampling)
    unMask = unDeviceClusterMask;
    while (unMask)
    {
      uint16_t unBitPosition = Q6_R_ct0_R(unMask);
      unMask ^= 1LL << unBitPosition;
      phCalPort = &pAdmStatSvc->deviceCalPort[unBitPosition];

      if ((FALSE == phCalPort->bIsCoppInLoopBackTopology) &&
          (FALSE == phCalPort->bIsCoppInDeviceLoopBackTopology) &&
          (FALSE == phCalPort->bIsCoppConnectedToPseudoPort) &&
          (phCalPort->unNumConnectedSessionsRx > unNumConnectedSessions))
      {
        unPrimaryDevice = unBitPosition;
        unNumConnectedSessions = phCalPort->unNumConnectedSessionsRx;
      }
    }
  }
  if ( ADM_INVALID_PRIMARY_DEVICE != unPrimaryDevice)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: regular device unCoppID:[%d] is primary device", unPrimaryDevice);
    return unPrimaryDevice;
  }

  // find out loopback/pseudo port device that is connected to maximum sessions
  unMask = unDeviceClusterMask;
  while (unMask)
  {
    //check for device that has no resampling in COPP
    //if all devices have resampling, primary device will be zero.
    uint16_t unBitPosition = Q6_R_ct0_R(unMask);
    unMask ^= 1LL << unBitPosition;
    phCalPort = &pAdmStatSvc->deviceCalPort[unBitPosition];

    if ((TRUE == phCalPort->bIsCoppInLoopBackTopology || TRUE == phCalPort->bIsCoppConnectedToPseudoPort) &&
        (FALSE == phCalPort->bIsCoppInDeviceLoopBackTopology) &&
        (phCalPort->unMtMxSampleRate == phCalPort->unEID1.unSampleRate) &&
        (phCalPort->unNumConnectedSessionsRx > unNumConnectedSessions))
    {
      unPrimaryDevice = unBitPosition;
      unNumConnectedSessions = phCalPort->unNumConnectedSessionsRx;
    }
  }
  if ( ADM_INVALID_PRIMARY_DEVICE == unPrimaryDevice)
  {
    //check for primary device (as all devices involve resampling)
    unMask = unDeviceClusterMask;
    while (unMask)
    {
      uint16_t unBitPosition = Q6_R_ct0_R(unMask);
      unMask ^= 1LL << unBitPosition;
      phCalPort = &pAdmStatSvc->deviceCalPort[unBitPosition];

      if ((TRUE == phCalPort->bIsCoppInLoopBackTopology || TRUE == phCalPort->bIsCoppConnectedToPseudoPort) &&
          (FALSE == phCalPort->bIsCoppInDeviceLoopBackTopology) &&
          (phCalPort->unNumConnectedSessionsRx > unNumConnectedSessions))
      {
        unPrimaryDevice = unBitPosition;
        unNumConnectedSessions = phCalPort->unNumConnectedSessionsRx;
      }
    }
  }
  if ( ADM_INVALID_PRIMARY_DEVICE != unPrimaryDevice)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: loopback device unCoppID:[%d] is primary device", unPrimaryDevice);
    return unPrimaryDevice;
  }

  return unPrimaryDevice;
}

/* This function gives primary devices among devices present in cluster*/
static uint16_t Adm_GetPrimaryDeviceCompressed(AdmStatSvc_InfoType *pAdmStatSvc, uint32_t unDeviceClusterMask)
{
  //select first one arbitrarily.
  uint16_t unPrimaryDeviceOffset = Q6_R_ct0_R(unDeviceClusterMask);

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: device Index:[%d] is primary device", unPrimaryDeviceOffset);

  return (unPrimaryDeviceOffset);

}

/* This function detects and updates primary ports of all active sessions and devices.
This is supported only on RX direction. Caller need to take care that this is called only
for RX direction*/
ADSPResult Adm_DetectAndUpdatePrimaryDevicePcm(AdmStatSvc_InfoType *pAdmStatSvc, qurt_elite_queue_t *pRspQ)
{
  ADSPResult result = ADSP_EOK;
  uint32_t unSessionClusterMask = 0, unDeviceClusterMask = 0;
  uint16_t unPrimaryDevice      = 0, unIndex = 0;
  AdmStreamSessionInfo_Type *pStreamSessionInfo = NULL;

  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  //first reset primary device information of sessions and devices.
  for (unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unIndex] = ADM_INVALID_PRIMARY_DEVICE;
  }

  AdmCalPort_Type *phCalPort;
  for (uint16_t unCoppID = 0; unCoppID < (ADM_MAX_COPPS); unCoppID++)
  {
    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
    phCalPort->unPrimaryDevice = ADM_INVALID_PRIMARY_DEVICE;
  }

  // cluster is defined as group of all sessions and devices that are connected
  for (unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    pStreamSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
    if ((ADM_INVALID_PRIMARY_DEVICE != pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unIndex]) ||
        ( 0 == pAdmStatSvc->rxsessionMappingMask[unIndex]) ||
        (ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode) ||
        (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode) ||
        (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode))
    {
      // if the session is already associated with primary device (or)
      // if the session is not connected to any device, no need to check primary device (or)
      // if the session is ULL/ULLPP session
      // if the session is a LLNP session
      // continue with other sessions.
      continue;
    }

    // check if this session shares any devices with any other sessions and identify all devices
    // that are shared.
    unSessionClusterMask = 1LL << (unIndex);
    unDeviceClusterMask = pAdmStatSvc->rxsessionMappingMask[unIndex];
    uint32_t unNextIndex = unIndex + 1;
    pStreamSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unNextIndex]);
    while(unNextIndex < ASM_MAX_SUPPORTED_SESSION_ID)
    {
      if ((ADM_INVALID_PRIMARY_DEVICE != pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unNextIndex]) ||
          ( 0 == pAdmStatSvc->rxsessionMappingMask[unNextIndex]) ||
          ( 0 != (unSessionClusterMask && (1LL << unNextIndex)))  ||
          (ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode) ||
          (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode) ||
          (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode))
      {
        // if the session is already associated with primary device (or)
        // if the session is not connected to any device, no need to check primary device (or).
        // if the session is already considered in the cluster (or)
        // if the session is ULL session
        // if the session is a LLNP session
        // continue with other sessions.
        unNextIndex++;
      }
      else
      {
        // check if this session shares any devices that are already present in device cluster
        if ((pAdmStatSvc->rxsessionMappingMask[unNextIndex]) & unDeviceClusterMask)
        {
          unDeviceClusterMask  |= pAdmStatSvc->rxsessionMappingMask[unNextIndex];
          unSessionClusterMask |= 1LL << unNextIndex;
          unNextIndex           = unIndex + 1;
        }
        else
        {
          unNextIndex++;
        }
      }
    }

    // check primary device of all devices in device cluster
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: unSessionClusterMask = 0x%lx, unDeviceClusterMask = 0x%lx",
          unSessionClusterMask, unDeviceClusterMask);

    if (unDeviceClusterMask) //TBD: is this check required? will it be zero when it reaches here?
    {
      unPrimaryDevice = Adm_GetPrimaryDevicePcm(pAdmStatSvc, unDeviceClusterMask);
      if (ADM_INVALID_PRIMARY_DEVICE == unPrimaryDevice)
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Primary output port detection failed");
        qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
        return ADSP_EFAILED;
      }
    }

    // for all sessions in cluster, update primary device
    while (unSessionClusterMask)
    {
      uint32_t unBitPosition = Q6_R_ct0_R(unSessionClusterMask);
      unSessionClusterMask ^= 1LL << unBitPosition;
      //check if this session is connected to unPrimaryDevice. Otherwise, find primary device for this session
      if (pAdmStatSvc->rxsessionMappingMask[unBitPosition] & (1 << unPrimaryDevice))
      {
        pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unBitPosition] = unPrimaryDevice;
      }
      else
      {
        uint16_t unSessionPrimaryDevice = Adm_GetPrimaryDevicePcm(pAdmStatSvc, pAdmStatSvc->rxsessionMappingMask[unBitPosition]);
        if (ADM_INVALID_PRIMARY_DEVICE == unSessionPrimaryDevice)
        {
          MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Primary output port detection failed");
          qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
          return ADSP_EFAILED;
        }
        pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unBitPosition] = unSessionPrimaryDevice;
      }
    }

    // for all devices in cluster, update primary device
    while (unDeviceClusterMask)
    {
      uint32_t unBitPosition = Q6_R_ct0_R(unDeviceClusterMask);
      unDeviceClusterMask ^= 1LL << unBitPosition;
      phCalPort = &pAdmStatSvc->deviceCalPort[unBitPosition];
      phCalPort->unPrimaryDevice = unPrimaryDevice;
    }
  }

  //set primary port information to all active copps
  for (uint16_t unCoppID = 0; unCoppID < ADM_MAX_COPPS; unCoppID++)
  {
    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
    // Primary device information should be available for all active, connected, non ULL RX sessions
    // that are not loopback sessions with only one session connected
    // SampleSlip is not supported for fractional sample rates
    if ((ADM_COPP_STATUS_ACTIVE == phCalPort->unCoppStatus) &&
        (RX_DIR == phCalPort->unCoppDirection) &&
        ( 0 != phCalPort->unNumConnectedSessionsRx ) &&
        (ADM_ULTRA_LOW_LATENCY_POST_PROC_DEVICE_SESSION != phCalPort->unDevicePerfMode) &&
        (ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION != phCalPort->unDevicePerfMode) &&
        (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION != phCalPort->unDevicePerfMode) &&
        (ADM_SAMPLING_RATE_44100 != phCalPort->unEID1.unSampleRate) &&
        (ADM_SAMPLING_RATE_88200 != phCalPort->unEID1.unSampleRate) &&
        (ADM_SAMPLING_RATE_176400 != phCalPort->unEID1.unSampleRate) )
    {
      //MAP:TBD: Do we have support for sample slip for fractional rates?
      if (ADM_INVALID_PRIMARY_DEVICE != phCalPort->unPrimaryDevice)
      {
        Adm_SendCmdCoppSetParamsDriftPtrSetup(pAdmStatSvc, unCoppID, phCalPort->unPrimaryDevice, pRspQ);
      }
      else
      {
        if (TRUE == phCalPort->bIsCoppInLoopBackTopology)
        {
          MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Active loopback unCoppID [%d] does not have primary device", unCoppID);
        }
        else
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Active RX unCoppID [%d] does not have primary device", unCoppID);
          qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
          return ADSP_EFAILED;
        }
      }
    }
  }

  //set primary port information to all matrix input ports.
  result = Adm_SetMtMxPrimaryOutputPort(pAdmStatSvc, pRspQ);
  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: set primary output port cmd failed, result = %d", result);
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
    return result;
  }

  //set primary device of ULL sessions. This is required as primary device information will be
  // used during device switch with ULL sessions.
  for (unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    pStreamSessionInfo = &(pAdmStatSvc->rxStreamSessionInfo[unIndex]);
    if ( ((ASM_ULTRA_LOW_LATENCY_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode) ||
        (ASM_ULTRA_LOW_LATENCY_POST_PROC_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode) ||
        (ASM_LOW_LATENCY_NO_PROC_STREAM_SESSION == pStreamSessionInfo->stream_perf_mode)) &&
        (0 != pAdmStatSvc->rxsessionMappingMask[unIndex]))
    {
      // since direct connections will be attached to only one device, primary device equal to attached device
      uint32_t unPrimaryDevice = Q6_R_ct0_R(pAdmStatSvc->rxsessionMappingMask[unIndex]);
      pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unIndex] = unPrimaryDevice;
      // update calport structure also.
      phCalPort = &pAdmStatSvc->deviceCalPort[unPrimaryDevice];
      phCalPort->unPrimaryDevice = unPrimaryDevice;
    }
  }
  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
  return result;
}

///* This function detects and updates primary ports of all active sessions and devices.
//This is supported only on RX direction. Caller need to take care that this is called only
//for RX direction*/
ADSPResult Adm_DetectAndUpdatePrimaryDeviceCompressed(AdmStatSvc_InfoType *pAdmStatSvc, qurt_elite_queue_t *pRspQ)
{
  ADSPResult result = ADSP_EOK;
  uint32_t unIndex = 0;
  uint32_t unSessionClusterMask=0,unDeviceClusterMask=0;
  uint16_t unPrimaryDeviceIndex = 0;
  ComprCoppInfo_t *pComprCopp;

  //first reset primary device information of sessions and devices.
  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);

  for (unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    pAdmStatSvc->rxSessionIDToPrimCompressedDevIndexMap[unIndex] = ADM_INVALID_PRIMARY_DEVICE;
  }
  for (uint16_t unCoppID = ADM_COMPRESSED_MIN_RX; unCoppID <= ADM_COMPRESSED_MAX_RX; unCoppID++)
  {
    pComprCopp = &pAdmStatSvc->rxStRtrParams.compr_copp_info[unCoppID - ADM_COMPRESSED_MIN_RX];
    pComprCopp->unPrimaryDevice = ADM_INVALID_PRIMARY_DEVICE;
  }

  // cluster is defined as group of all sessions and devices that are connected
  for (unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
  {
    if ((ADM_INVALID_PRIMARY_DEVICE != pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unIndex]) ||
        ( 0 == pAdmStatSvc->rxCompressedSessionMappingMask[unIndex]))
    {
      // if the session is already associated with primary device (or)
      // if the session is not connected to any device, no need to check primary device
      // continue with other sessions.
      continue;
    }

    // check if this session shares any devices with any other sessions and identify all devices
    // that are shared.
    unSessionClusterMask = 1LL << (unIndex);
    unDeviceClusterMask = pAdmStatSvc->rxCompressedSessionMappingMask[unIndex];
    uint32_t unNextIndex = unIndex + 1;
    while(unNextIndex < ASM_MAX_SUPPORTED_SESSION_ID)
    {
      if ((ADM_INVALID_PRIMARY_DEVICE != pAdmStatSvc->rxSessionIDToPrimCOPPIDMap[unNextIndex]) ||
          ( 0 == pAdmStatSvc->rxsessionMappingMask[unNextIndex]) ||
          ( 0 != (unSessionClusterMask && (1LL << unNextIndex))))
      {
        // if the session is already associated with primary device (or)
        // if the session is not connected to any device, no need to check primary device (or).
        // if the session is already considered in the cluster (or)
        // continue with other sessions.
        unNextIndex++;
      }
      else
      {
        // check if this session shares any devices that are already present in device cluster
        if ((pAdmStatSvc->rxCompressedSessionMappingMask[unNextIndex]) & unDeviceClusterMask)
        {
          unDeviceClusterMask |= pAdmStatSvc->rxCompressedSessionMappingMask[unNextIndex];
          unSessionClusterMask |= 1LL << unNextIndex;
          unNextIndex = unIndex + 1;
        }
        else
        {
          unNextIndex++;
        }
      }
    }

    // check primary device of all devices in device cluster
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: unSessionClusterMask = 0x%lx, unDeviceClusterMask = 0x%lx",
          unSessionClusterMask, unDeviceClusterMask);
    if (unDeviceClusterMask) //TBD: is this check required? will it be zero when it reaches here?
    {
      unPrimaryDeviceIndex = Adm_GetPrimaryDeviceCompressed(pAdmStatSvc, unDeviceClusterMask);
      if (ADM_INVALID_PRIMARY_DEVICE == unPrimaryDeviceIndex)
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Primary output port detection failed");
        qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
        return ADSP_EFAILED;
      }
    }

    // for all sessions in cluster, update primary device
    while (unSessionClusterMask)
    {
      uint32_t unBitPosition = Q6_R_ct0_R(unSessionClusterMask);
      unSessionClusterMask ^= 1LL << unBitPosition;
      pAdmStatSvc->rxSessionIDToPrimCompressedDevIndexMap[unBitPosition] = unPrimaryDeviceIndex;
    }

    // for all devices in cluster, update primary device
    while (unDeviceClusterMask)
    {
      uint32_t unBitPosition = Q6_R_ct0_R(unDeviceClusterMask);
      unDeviceClusterMask ^= 1LL << unBitPosition;
      pComprCopp = &pAdmStatSvc->rxStRtrParams.compr_copp_info[unBitPosition];
      pComprCopp->unPrimaryDevice = unPrimaryDeviceIndex;
    }
  }

  //set primary port information to all strtr input ports.
  result = Adm_SetStrtrPrimaryOutputPort(pAdmStatSvc, pRspQ);
  if (ADSP_FAILED(result))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: set primary output port cmd failed, result = %d", result);
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
    return result;
  }

  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
  return result;
}

uint16_t Adm_CalculateNextAvlIndex(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t direction, adm_client_type_t eClient)
{
  //Return the first available index in the appropriate direction

  //NOTE:
  //The caller of this function (StreamConnect command) assumes that the Session/Stream ID that
  //eventually be assigned to this index is of the 16-bit form with the first 8-bits indicating
  //the SessionID and the second 8 bits indicating the stream ID.
  //Example: 0x0A0B: Indicates SessionID = 0xA = 10 and StreamID = 0xB = 11.
  uint16_t  *pIndexToSessionStreamID;
  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);
  if((ADM_RX_DIR == direction) && (eASM_TYPE == eClient))
  {
    pIndexToSessionStreamID = &(pAdmStatSvc->rxIndexToSessionStreamID[0]);
  }
  else if(ADM_TX_DIR == direction)
  {
    pIndexToSessionStreamID = &(pAdmStatSvc->txIndexToSessionStreamID[0]);
  }
  else
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Invalid Direction: %d or Client type %d provided", direction,eClient);
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
    return ADM_INVALID_INDEX;
  }

  if (eASM_TYPE == eClient)
  {
    for(uint16_t unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
    {
      if(0 == pIndexToSessionStreamID[unIndex])
      {
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Direction: %d, Valid unused index found: %d for ASM client", direction, unIndex);
        qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
        return unIndex;
      }
    }
  }
  else if (eLSM_TYPE == eClient)
  {
    for (uint16_t unIndex = ASM_MAX_SUPPORTED_SESSION_ID; unIndex < ASM_MAX_SUPPORTED_SESSION_ID + LSM_MAX_NUM_SESSIONS; unIndex++)
    {
      if (0 == pIndexToSessionStreamID[unIndex])
      {
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Direction: %d, Valid unused index found: %d for LSM client", direction, unIndex);
        qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
        return unIndex;
      }
    }
  }

  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Direction: %d, Valid unused index not found", direction);
  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
  return ADM_INVALID_INDEX;
}

uint16_t Adm_SessionStreamIDToIndex(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t direction, uint16_t sessionStreamID,adm_client_type_t eClient)
{
  //Returns the index that hosts this sessionStreamID

  //NOTE:
  //The caller of this function may pass in the combinational Session/Stream ID.
  //Example: 0x0A0B: Indicates SessionID = 0xA = 10 and StreamID = 0xB = 11.
  //The caller of this function may pass in the legacy Session ID alone.
  //Example: 0x000A: Indicates SessionID = 0xA = 10 (Range: 0x0001 (1) to 0x000F (15)).
  //This function should be capable of handling either of these formats to do its search.

  uint16_t  *pIndexToSessionStreamID;
  qurt_elite_mutex_lock(&pAdmStatSvc->admLock);
  if((ADM_RX_DIR == direction) && (eASM_TYPE == eClient))
  {
    pIndexToSessionStreamID = &(pAdmStatSvc->rxIndexToSessionStreamID[0]);
  }
  else if(ADM_TX_DIR == direction)
  {
    pIndexToSessionStreamID = &(pAdmStatSvc->txIndexToSessionStreamID[0]);
  }
  else
  {
    MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Invalid Direction: %d or Client Type %d provided", direction, eClient);
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
    return ADM_INVALID_INDEX;
  }

  if(0 == sessionStreamID)
  {
    //Zero is not a valid Session/Stream ID
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Invalid SSID: 0 provided");
    qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
    return ADM_INVALID_INDEX;
  }

  if (eASM_TYPE == eClient)
  {
    for(uint16_t unIndex = 0; unIndex < ASM_MAX_SUPPORTED_SESSION_ID; unIndex++)
    {
      if(sessionStreamID <= ASM_MAX_SUPPORTED_SESSION_ID)
      {
        //Legacy sessionStreamID is provided with a number between 1 - ASM_MAX_SUPPORTED_SESSION_ID
        //In this case, search for the upper 8 bits in the array for this sessionStreamID.
        if((sessionStreamID) == ((pIndexToSessionStreamID[unIndex] & 0xff00) >> 8))
        {
          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Direction: %d, Legacy SessionStreamID: 0x%hX is hosted by index %d for ASM session", direction, sessionStreamID, unIndex);
          qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
          return unIndex;
        }
      }
      else
      {
        //Contemprorary sessionStreamID provided. A direct check will suffice.
        if(sessionStreamID == pIndexToSessionStreamID[unIndex])
        {
          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Direction: %d, SessionStreamID: 0x%hX is hosted by index %d for ASM session", direction, sessionStreamID, unIndex);
          qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
          return unIndex;
        }
      }
    }
  }
  else if (eLSM_TYPE == eClient)
  {
    for(uint16_t unIndex = ASM_MAX_SUPPORTED_SESSION_ID; unIndex < ASM_MAX_SUPPORTED_SESSION_ID + LSM_MAX_NUM_SESSIONS; unIndex++)
    {
      if(sessionStreamID == pIndexToSessionStreamID[unIndex])
      {
        MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Direction: %d, SessionStreamID: 0x%hX is hosted by index %d for LSM session", direction, sessionStreamID, unIndex);
        qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
        return unIndex;
      }
    }
  }

  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Error Direction: %d, SessionStreamID: 0x%hX of client %d is not hosted by any index", direction, sessionStreamID, eClient);
  qurt_elite_mutex_unlock(&pAdmStatSvc->admLock);
  return ADM_INVALID_INDEX;
}

ADSPResult is_valid_device_sampling_rate(uint32_t sample_rate)
{
  ADSPResult result = ADSP_EOK;

  switch(sample_rate)
  {
    case 8000:
    case 11025:
    case 12000:
    case 16000:
    case 22050:
    case 24000:
    case 32000:
    case 44100:
    case 48000:
    case 88200:
    case 96000:
    case 176400:
    case 192000:
    case 352800:
    case 384000:
      break;
    default:
      result = ADSP_EUNSUPPORTED;
      break;
  }
  return result;
}

ADSPResult Adm_CreatePPSvc(AdmStatSvc_InfoType *pAdmStatSvc,
                           AdmCalPort_Type *phCalPort,
                           AdmDevSessionDelayParam_Type *pSessionDelayParam,
                           uint32_t unTopology,
                           AudPP_AudProcType svcType,
                           uint32_t unLogID)
{
  ADSPResult result = ADSP_EFAILED;
  AudPPSvcInitParams_t PPParams;
  memset(&PPParams, 0, sizeof(AudPPSvcInitParams_t));
  PPParams.outputMediaTypeInitParams.keepInputSamplingRate = FALSE;
  PPParams.outputMediaTypeInitParams.outputSamplingRate = phCalPort->unEID1.unSampleRate;
  PPParams.outputMediaTypeInitParams.useNativeNumChannels = TRUE;
  PPParams.outputMediaTypeInitParams.outputNumChannels = 2; //NA: as NativeNumChannels is TRUE
  PPParams.outputMediaTypeInitParams.useNativeBitsPerSample = TRUE;
  PPParams.outputMediaTypeInitParams.outputBitsPerSample = 0;
  PPParams.outputBufferNumAfeFramesPerChannel = phCalPort->unCoppNumAfeFrames;
  PPParams.topology = unTopology;
  PPParams.type = svcType;
  PPParams.memoryMapClient = admMemoryMapClient;
  PPParams.pMsgCb = &(phCalPort->structPPCallbackInfo.cbFuntion);
  PPParams.pCtxt = &(phCalPort->structPPCallbackInfo.pContext);
  PPParams.pBufDelay = &(pSessionDelayParam->unCoppBufDelay);
  PPParams.pAlgorithmicDelay = &(pSessionDelayParam->unCoppAlgDelay);
  PPParams.initializeWithCompressedFormat = FALSE;
  PPParams.ulDataLogId = unLogID;
  PPParams.perf_mode = phCalPort->unDevicePerfMode;
  if(ADM_CMD_COPP_OPEN_END_POINT_ID_2_IGNORE != phCalPort->unEID2.unAfePortID)
  {
    PPParams.is_echo_canceller_session = TRUE;
  }
  else
  {
    PPParams.is_echo_canceller_session = FALSE;
  }
  /* Both input and output are non-real time for ADM Loopback.
     For other cases the default value 0, either input or output
     are real time is applicable.
  */
  if(TRUE == phCalPort->bIsCoppInLoopBackTopology)
  {
    PPParams.is_input_output_realtime = 2;
  }
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AudPP_CreateSvc EP_ID2 :0x%x and echo_cancel = %d", phCalPort->unEID2.unAfePortID, PPParams.is_echo_canceller_session);
  if (ADSP_FAILED(result = AudPP_CreateSvc(&PPParams, (void **) &phCalPort->phDevCopp, (void **) &phCalPort->phDevCoppEcRef)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: AudPP_CreateSvc cmd failed, result = %d", result);
    return result;
  }

  return result;
}
static ADSPResult Adm_RegisterDegisterPPEvents(void *pAudStatAdmSvc, elite_apr_packet_t *pPkt)
{
  void               *pIncomingAPRPayload;
  uint32_t           unPayloadSize;
  elite_apr_port_t   port;
  elite_svc_handle_t *pCoppHandle;
  elite_msg_any_t    msg;
  ComprCoppInfo_t    *pCompCoppInfo;

  uint32_t            unCoppID     = 0;
  ADSPResult          result       = ADSP_EOK;
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType *)pAudStatAdmSvc;
  AdmCalPort_Type     *phCalPort = NULL;
  DeviceCmdProcInfo_t *pDevCmd   = NULL;

  elite_msg_register_apr_event_t *pMsgPayload = NULL;

  MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM processing ADM_CMD_REGISTER_PP_EVENTS ");

  if(NULL == pPkt)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_REGISTER_PP_EVENTS received NULL apr pkt ");
    result = ADSP_EBADPARAM;
    goto __bailoutRegisterEventsHandler;
  }

  port = elite_apr_if_get_dst_port(pPkt);

  //extract the payload from the incoming packet
  pIncomingAPRPayload = (void *)elite_apr_if_get_payload_ptr(pPkt);
  unCoppID            = ADM_GET_COPP_ID(port);


  // check the payload
  if((unCoppID >= ADM_COMPRESSED_MIN_RX) && (unCoppID <= ADM_COMPRESSED_MAX_RX))
  {
    pCompCoppInfo = &(pAdmStatSvc->rxStRtrParams.compr_copp_info[unCoppID-ADM_COMPRESSED_MIN_RX]);

    if(AUDPROC_TOPOLOGY_ID_COMPRESSED_NONE == pCompCoppInfo->unCoppTopologyID)
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "ADM: ADM_CMD_REGISTER_PP_EVENTS cmd on  compressed COPP %lu failed. Not supported in NONE Topology",
            unCoppID);
      result =  ADSP_EFAILED;
      goto __bailoutRegisterEventsHandler;
    }

    pCoppHandle = pCompCoppInfo->phDevCopp;
    pDevCmd     = &pCompCoppInfo->devCmd;
  }
  else
  {
    // check the validity of COPP ID
    if( ADSP_FAILED(result = Adm_CheckCoppValidity(pAdmStatSvc, unCoppID, ADM_INVALID_DIRECTION)))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Error: ADM rcvd invalid/inactive COPP ID %lu", unCoppID);
      goto __bailoutRegisterEventsHandler;
    }

    phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
    pCoppHandle = phCalPort->phDevCopp;

    if ((ADM_ULTRA_LOW_LATENCY_DEVICE_SESSION == phCalPort->unDevicePerfMode)
        || (ADM_LOW_LATENCY_NO_PROC_DEVICE_SESSION == phCalPort->unDevicePerfMode))
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: ADM_CMD_REGISTER_PP_EVENTS cmd is not supported on LLNP/ULL COPP %lu. cmd failed", unCoppID);
      result = ADSP_EUNSUPPORTED;
      goto __bailoutRegisterEventsHandler;
    }

    pDevCmd = &phCalPort->devCmd;
  }

  unPayloadSize = sizeof(elite_msg_register_apr_event_t);
  pDevCmd->token = Adm_GenerateToken(eDEVICE,unCoppID);
  if(ADSP_FAILED(result = elite_msg_create_msg( &msg, &unPayloadSize,
                                                ELITE_CMD_REGISTER_APR_EVENT,
                                                pAdmStatSvc->admRspQ,
                                                pDevCmd->token,
                                                0)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: message create failed for register_apr_event. unCoppID %lu", unCoppID);
    //ack with error
    result = ADSP_ENOMEMORY;
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
    goto __bailoutRegisterEventsHandler;
  }

  pMsgPayload = (elite_msg_register_apr_event_t *)msg.pPayload;
  pMsgPayload->unSize       = elite_apr_if_get_payload_size(pPkt);
  pMsgPayload->pnParamData  = (int32_t*)elite_apr_if_get_payload_ptr(pPkt);
  pMsgPayload->src_port     = elite_apr_if_get_src_port(pPkt);
  pMsgPayload->src_addr     = elite_apr_if_get_src_addr(pPkt);
  pMsgPayload->dest_port    = elite_apr_if_get_dst_port(pPkt);
  pMsgPayload->dest_addr    = elite_apr_if_get_dst_addr(pPkt);
  pMsgPayload->apr_token    = pPkt->token;

  // send the message to PP service and wait for ack
  result = qurt_elite_queue_push_back(pCoppHandle->cmdQ, (uint64_t*)&msg);

  if(ADSP_FAILED(result))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to push cmd to PP");
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
    goto __bailoutRegisterMsgRelease;
  }

  pDevCmd->unRespsNeeded++;
  return result;

  __bailoutRegisterMsgRelease:
  elite_msg_release_msg(&msg);

  __bailoutRegisterEventsHandler:
  elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pPkt, result);

  return result;
}


static ADSPResult Adm_DeviceOpenCmdHelperThread(AdmStatSvc_InfoType *pAdmStatSvc,
                                                uint16_t open_mode,
                                                elite_apr_packet_t *pPkt,
                                                NativeModeHook cbNativeMode,
                                                uint16_t *unCreatedCoppID)
{
  bool_t           isCompressed = FALSE;
  uint32_t         unCoppID     = *unCreatedCoppID;
  ADSPResult       result       = ADSP_EOK;
  Adm_HelperThrd_t *pHelper     = NULL;

  void *ptr = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompressed);

  if(!ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to get calport struct for device ID [%d] ",unCoppID);
    return ADSP_EFAILED;
  }

  switch (open_mode)
  {
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP:
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_DEVICE_LOOPBACK:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP:
    {
      AdmCalPort_Type *phCalPort = (AdmCalPort_Type*)ptr;

      Adm_ResetCalPort(ptr, isCompressed);
      pHelper = &phCalPort->helperThrdInfo;

      pHelper->unCoppId       = unCoppID;
      pHelper->pPkt           = pPkt;
      pHelper->pOpenFn        = pAdmOpenDeviceHandler[open_mode];
      pHelper->unCmd          = OPEN;
      pHelper->pInstance      = pAdmStatSvc;
      phCalPort->unCoppStatus = ADM_COPP_STATUS_INIT;
      break;
    }
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX:
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX:
    {
      ComprCoppInfo_t *pComprCoppInfo = (ComprCoppInfo_t*)ptr;

      Adm_ResetCalPort(ptr, TRUE);
      pHelper = &pComprCoppInfo->helperThrdInfo;

      pHelper->unCoppId            = unCoppID;
      pHelper->pPkt                = pPkt;
      pHelper->pOpenFn             = pAdmOpenDeviceHandler[open_mode];
      pHelper->unCmd               = OPEN;
      pHelper->pInstance           = pAdmStatSvc;
      pComprCoppInfo->unCoppStatus = ADM_COPP_STATUS_INIT;

      break;
    }
    default:
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM rcvd open cmd with unsupported mode of operation [0x%04x]", open_mode);
      result = ADSP_EBADPARAM;
      return result;
    }
  }

  /* Initial validation all okay. Go ahead and launch the helper thread */
  pHelper->unRspOpcode = ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_OPEN_HELPER_THRD;

  char helper_name[13]; // 4 spaces for the unique id and one for the NULL terminator.
  snprintf(helper_name, 13, "%s%lX", ADM_HELPER_THREAD_NAME, unCoppID);

  if (ADSP_FAILED (result = qurt_elite_thread_launch(&(pHelper->tId), helper_name, \
                                                     NULL, ADM_HELPER_THREAD_OPEN_STACK_SIZE, \
                                                     elite_get_thrd_prio(ELITETHREAD_STAT_AUDIO_DEV_SVC_PRIO_ID), \
                                                     Adm_HelperThreadEntryFunc, (void*)pHelper, \
                                                     QURT_ELITE_HEAP_DEFAULT)))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Failed to create the helper thread for Device Open");

    Adm_ResetCalPort(ptr, isCompressed);
    memset(pHelper, 0, sizeof(Adm_HelperThrd_t));
    return result;
  }

  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Create Helper thread ID 0x%x for Device Open",pHelper->tId);
  AudDevMgr_RequestHwResources(pAdmStatSvc);
  return result;

}

static int Adm_HelperThreadEntryFunc(void *pArgs)
{
  Adm_HelperThrd_t *pHelper = (Adm_HelperThrd_t*)pArgs;
  AdmStatSvc_InfoType *pAdmStatSvc = pHelper->pInstance;
  ADSPResult result = ADSP_EOK;
  char admHelperRspQName[] = "ADMHlpRspQ";

  QURT_ELITE_ALIGN(static char admHelperQBuf[QURT_ELITE_QUEUE_GET_REQUIRED_BYTES(ADM_HELPER_THRD_RSP_Q_ELEMENTS)], 8);

  pHelper->pRspQ = (qurt_elite_queue_t *)(admHelperQBuf);

  if(ADSP_FAILED(result = qurt_elite_queue_init(admHelperRspQName, ADM_HELPER_THRD_RSP_Q_ELEMENTS, pHelper->pRspQ)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to create Helper respQ with result = 0x%x", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pHelper->pPkt, result);
    Adm_SendHelperThrdEndMsg(pHelper->pInstance, pHelper->unCoppId, result, pHelper->unRspOpcode);
    return result;
  }

  qurt_elite_channel_init(&pHelper->unChannel);

  if (ADSP_FAILED(result = qurt_elite_channel_addq(&pHelper->unChannel, pHelper->pRspQ, 0)))
  {
    MSG_1(MSG_SSID_QDSP6, DBG_FATAL_PRIO, "ADM: Error: Failed to add Helper rspQ to channel, result = 0x%x", result);
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pHelper->pPkt, result);
    Adm_SendHelperThrdEndMsg(pHelper->pInstance, pHelper->unCoppId, result, pHelper->unRspOpcode);
    return result;
  }

  if(OPEN == pHelper->unCmd)
  {
    adm_cmd_device_open_t        DevOpenCmdPayload = {0};
    //memset(&DevOpenCmdPayload, 0, sizeof(DevOpenCmdPayload));
    Adm_DeviceParseOpenPayload(pHelper->pPkt, &DevOpenCmdPayload);

    adm_cmd_device_open_t *pDevOpenCmdPayload = &DevOpenCmdPayload;
    result = pHelper->pOpenFn(pAdmStatSvc, pDevOpenCmdPayload, pHelper->pPkt, Adm_NativeModeParamCallback,
                              &pHelper->unCoppId, pHelper->pRspQ);
  }
  else if(CLOSE == pHelper->unCmd)
  {
    result = pHelper->pCloseFn(pAdmStatSvc, pHelper->pPkt, pHelper->pRspQ);
  }

  qurt_elite_queue_deinit(pHelper->pRspQ);
  qurt_elite_channel_destroy(&pHelper->unChannel);
  Adm_SendHelperThrdEndMsg(pHelper->pInstance, pHelper->unCoppId, result, pHelper->unRspOpcode);

  MSG(MSG_SSID_QDSP6, DBG_MED_PRIO, "ADM: Exiting Helper Thread");
  
  return result;
}

static void Adm_SendOpenCmdRspAprMsg(AdmStatSvc_InfoType *pAdmStatSvc, Adm_HelperThrd_t *pHelper)
{
  uint32_t opcode = elite_apr_if_get_opcode(pHelper->pPkt);

  if (ADM_CMD_DEVICE_OPEN_V8 == opcode)
  {
    // Send the V7 cmd response
    adm_cmd_rsp_device_open_v8_t deviceOpenCmdRsp;
    deviceOpenCmdRsp.status  = ADSP_EOK;
    deviceOpenCmdRsp.copp_id = pHelper->unCoppId;

    AudDevMgr_GenerateAck(pHelper->pPkt,
                          ADSP_EOK,
                          (void *)(&deviceOpenCmdRsp),
                          sizeof(adm_cmd_rsp_device_open_v8_t),
                          ADM_CMDRSP_DEVICE_OPEN_V8);
  }
  else if (ADM_CMD_DEVICE_OPEN_V7 == opcode)
  {
    // Send the V7 cmd response
    adm_cmd_rsp_device_open_v7_t deviceOpenCmdRsp;
    deviceOpenCmdRsp.status  = ADSP_EOK;
    deviceOpenCmdRsp.copp_id = pHelper->unCoppId;

    AudDevMgr_GenerateAck(pHelper->pPkt,
                          ADSP_EOK,
                          (void *)(&deviceOpenCmdRsp),
                          sizeof(adm_cmd_rsp_device_open_v7_t),
                          ADM_CMDRSP_DEVICE_OPEN_V7);
  }
  else if (ADM_CMD_DEVICE_OPEN_V6 == opcode)
  {
    // Send the V6 cmd response
    adm_cmd_rsp_device_open_v6_t deviceOpenCmdRsp;
    deviceOpenCmdRsp.status  = ADSP_EOK;
    deviceOpenCmdRsp.copp_id = pHelper->unCoppId;

    AudDevMgr_GenerateAck(pHelper->pPkt,
                          ADSP_EOK,
                          (void *)(&deviceOpenCmdRsp),
                          sizeof(adm_cmd_rsp_device_open_v6_t),
                          ADM_CMDRSP_DEVICE_OPEN_V6);
  }
  else if(ADM_CMD_DEVICE_OPEN_V5 == opcode)
  {
    // Send the V5 cmd response
    adm_cmd_rsp_device_open_v5_t deviceOpenCmdRsp;
    deviceOpenCmdRsp.status  = ADSP_EOK;
    deviceOpenCmdRsp.copp_id = pHelper->unCoppId;

    AudDevMgr_GenerateAck(pHelper->pPkt,
                          ADSP_EOK,
                          (void *)(&deviceOpenCmdRsp),
                          sizeof(adm_cmd_rsp_device_open_v5_t),
                          ADM_CMDRSP_DEVICE_OPEN_V5);
  }

}

static ADSPResult Adm_DeviceOpenCmdUnsupportedHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                      adm_cmd_device_open_t *pDevOpenCmdPayload,
                                                      elite_apr_packet_t *pPkt,
                                                      NativeModeHook cbNativeMode,
                                                      uint16_t *unCreatedCoppID,
                                                      qurt_elite_queue_t *pRspQ)
{
  return ADSP_EFAILED;
}

static uint16_t Adm_GetDeviceModeFromID(AdmStatSvc_InfoType *pAdmStatSvc,
                                        uint16_t unCoppID)
{
  uint16_t mode = 0;

  if(ADSP_EOK == Adm_CheckCompDevIDValidity(pAdmStatSvc, unCoppID))
  {
    if((ADM_COMPRESSED_MIN_RX <= unCoppID) && (unCoppID <= ADM_COMPRESSED_MAX_RX))
    {
      mode = ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX;

    }
    else
    {
      mode = ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX;
    }
  }
  else if(ADSP_EOK == Adm_CheckCoppValidity(pAdmStatSvc, unCoppID, ADM_INVALID_DIRECTION))
  {
    AdmCalPort_Type *phCalPort = &pAdmStatSvc->deviceCalPort[unCoppID];
    mode = phCalPort->unCoppMode;
  }

  return mode;
}

static ADSPResult Adm_SetParamResponseHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg)
{
  ADSPResult               result       = ADSP_EOK;
  AdmStatSvc_InfoType      *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  elite_msg_param_cal_v2_t *pCalType    = (elite_msg_param_cal_v2_t*)pMsg->pPayload;
  DeviceCmdProcInfo_t      *pDevCmd     = NULL;

  uint32_t token      = pCalType->unClientToken;
  uint16_t unCoppID   = Adm_GetIndexFromToken(token);
  bool_t   isCompr    = FALSE;
  uint32_t unCmdQMask = 0;

  void *pDevice = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompr);

  if(NULL == pDevice)
  {
    return ADSP_EBADPARAM;
  }

  if(isCompr)
  {
    pDevCmd    = &((ComprCoppInfo_t*)pDevice)->devCmd;
    unCmdQMask = ((ComprCoppInfo_t*)pDevice)->devCmdQMask;
  }
  else
  {
    pDevCmd    = &((AdmCalPort_Type*)pDevice)->devCmd;
    unCmdQMask = ((AdmCalPort_Type*)pDevice)->devCmdQMask;
  }

  if(token != pDevCmd->token)
  {
    return ADSP_EBADPARAM;
  }

  pDevCmd->unRespsNeeded--;
  pDevCmd->rspResult |= pCalType->unResponseResult;

  if(0 == pDevCmd->unRespsNeeded)
  {
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pDevCmd->pCurrPkt, pCalType->unResponseResult);
    Adm_AddDeviceCmdQToMask(pAdmStatSvc, unCmdQMask);
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
  }

  return result;

}

static ADSPResult Adm_GetParamResponseHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg)
{
  ADSPResult               result       = ADSP_EOK;
  AdmStatSvc_InfoType      *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  elite_msg_param_cal_v2_t *pCalType    = (elite_msg_param_cal_v2_t*)pMsg->pPayload;
  DeviceCmdProcInfo_t      *pDevCmd     = NULL;

  uint32_t           token      = pCalType->unClientToken;
  uint16_t           unCoppID   = Adm_GetIndexFromToken(token);
  bool_t             isCompr    = FALSE;
  uint32_t           unCmdQMask = 0;
  elite_apr_packet_t *pPkt      = NULL;

  void *pDevice = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompr);

  if(NULL == pDevice)
  {
    return ADSP_EBADPARAM;
  }

  if(isCompr)
  {
    pDevCmd    = &((ComprCoppInfo_t*)pDevice)->devCmd;
    unCmdQMask = ((ComprCoppInfo_t*)pDevice)->devCmdQMask;
  }
  else
  {
    pDevCmd    = &((AdmCalPort_Type*)pDevice)->devCmd;
    unCmdQMask = ((AdmCalPort_Type*)pDevice)->devCmdQMask;
  }

  if(token != pDevCmd->token)
  {
    return ADSP_EBADPARAM;
  }

  pDevCmd->unRespsNeeded--;
  pDevCmd->rspResult |= pCalType->unResponseResult;
  pPkt = pDevCmd->pCurrPkt;

  if(0 == pDevCmd->unRespsNeeded)
  {
    if(pDevCmd->pAprRspPkt) //In Band Get Param
    {
      if(ADM_CMD_GET_PP_PARAMS_V5 == pPkt->opcode)
      {
        adm_cmd_rsp_get_pp_params_v5_t *pRspHeader = (adm_cmd_rsp_get_pp_params_v5_t*)elite_apr_if_get_payload_ptr(pDevCmd->pAprRspPkt);
        pRspHeader->status = pDevCmd->rspResult;

        adm_param_data_v5_t *psPPParamData = (adm_param_data_v5_t *)(pCalType->pnParamData);
        psPPParamData->param_size = pCalType->unSize;
      }
      else //ADM_CMD_GET_PP_PARAMS_V6
      {
        adm_cmd_rsp_get_pp_params_v6_t *pRspHeader = (adm_cmd_rsp_get_pp_params_v6_t*)elite_apr_if_get_payload_ptr(pDevCmd->pAprRspPkt);
        pRspHeader->status = pDevCmd->rspResult;

        adm_param_data_v6_t *psPPParamData = (adm_param_data_v6_t *)(pCalType->pnParamData);
        psPPParamData->param_size = pCalType->unSize;
      }

      /* Free up the incoming packet */
      elite_apr_if_free(pAdmStatSvc->admAprHandle, pPkt);

      /* Send the response back to client */
      result |= elite_apr_if_async_send(pAdmStatSvc->admAprHandle, pDevCmd->pAprRspPkt);

    }
    else //OOB
    {
      if (ADM_CMD_GET_PP_PARAMS_V5 == pPkt->opcode)
      {
        adm_param_data_v5_t *psPPParamData = (adm_param_data_v5_t *)(pCalType->pnParamData);
        psPPParamData->param_size = pCalType->unSize;
      }
      else //ADM_CMD_GET_PP_PARAMS_V6
      {
        adm_param_data_v6_t *psPPParamData = (adm_param_data_v6_t *)(pCalType->pnParamData);
        psPPParamData->param_size = pCalType->unSize;
      }

      result = elite_mem_flush_cache(&pDevCmd->sMemNode);
      if (ADSP_FAILED(result))
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPParam failed to flush cache");
      }
      pDevCmd->rspResult |= result;

      //Send the response as the status in ADM_CMDRSP_GET_PP_PARAMS_V5/V6
      if (ADM_CMD_GET_PP_PARAMS_V5 == pPkt->opcode)
      {
        adm_cmd_rsp_get_pp_params_v5_t response;
        response.status = pDevCmd->rspResult;
        AudDevMgr_GenerateAck(pPkt,
                              pDevCmd->rspResult,
                              &(response),
                              sizeof(response),
                              ADM_CMDRSP_GET_PP_PARAMS_V5);
      }
      else //ADM_CMD_GET_PP_PARAMS_V6
      {
        adm_cmd_rsp_get_pp_params_v6_t response;
        response.status = pDevCmd->rspResult;
        AudDevMgr_GenerateAck(pPkt,
                              pDevCmd->rspResult,
                              &(response),
                              sizeof(response),
                              ADM_CMDRSP_GET_PP_PARAMS_V6);
      }

    }//End of OOB

    Adm_AddDeviceCmdQToMask(pAdmStatSvc, unCmdQMask);
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));

  }// ( 0 == unRespsNeeded)

  return result;
}

static ADSPResult Adm_GetPPTopoModulesRspHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg)
{
  ADSPResult                                 result       = ADSP_EOK;
  AdmStatSvc_InfoType                        *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  EliteMsg_CustomCfg_GetPPTopologyModuleInfo *pRsp        = (EliteMsg_CustomCfg_GetPPTopologyModuleInfo*)pMsg->pPayload;
  DeviceCmdProcInfo_t                        *pDevCmd     = NULL;

  uint32_t           token      = pRsp->unClientToken;
  uint16_t           unCoppID   = Adm_GetIndexFromToken(token);
  bool_t             isCompr    = FALSE;
  uint32_t           unCmdQMask = 0;
  elite_apr_packet_t *pPkt      = NULL;

  void *pDevice = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompr);

  if(NULL == pDevice)
  {
    return ADSP_EBADPARAM;
  }

  if(isCompr)
  {
    pDevCmd    = &((ComprCoppInfo_t*)pDevice)->devCmd;
    unCmdQMask = ((ComprCoppInfo_t*)pDevice)->devCmdQMask;
  }
  else
  {
    pDevCmd    = &((AdmCalPort_Type*)pDevice)->devCmd;
    unCmdQMask = ((AdmCalPort_Type*)pDevice)->devCmdQMask;
  }

  if(token != pDevCmd->token)
  {
    return ADSP_EBADPARAM;
  }

  pDevCmd->unRespsNeeded--;
  pDevCmd->rspResult |= pRsp->unResponseResult;
  pPkt = pDevCmd->pCurrPkt;

  if(0 == pDevCmd->unRespsNeeded)
  {
    if(pDevCmd->pAprRspPkt) //In Band Get Topo List
    {
      if(ADM_CMD_GET_PP_TOPO_MODULE_LIST == pPkt->opcode)
      {
        adm_cmd_rsp_get_pp_topo_module_list_t *pRspHeader =
            (adm_cmd_rsp_get_pp_topo_module_list_t*) elite_apr_if_get_payload_ptr(pDevCmd->pAprRspPkt);
        pRspHeader->status = pDevCmd->rspResult;
      }
      else //ADM_CMD_GET_PP_TOPO_MODULE_LIST_V2
      {
        adm_cmd_rsp_get_pp_topo_module_list_v2_t *pRspHeader =
            (adm_cmd_rsp_get_pp_topo_module_list_v2_t*) elite_apr_if_get_payload_ptr(pDevCmd->pAprRspPkt);
        pRspHeader->status = pDevCmd->rspResult;
      }

      /* Free up the incoming packet */
      elite_apr_if_free(pAdmStatSvc->admAprHandle, pPkt);

      /* Send the response back to client */
      result |= elite_apr_if_async_send(pAdmStatSvc->admAprHandle, pDevCmd->pAprRspPkt);

    }
    else //OOB
    {
      result = elite_mem_flush_cache(&pDevCmd->sMemNode);
      if (ADSP_FAILED(result))
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Out-band GetPPParam failed to flush cache");
      }
      pDevCmd->rspResult |= result;

      //Send the response as the status in ADM_CMDRSP_GET_PP_PARAMS_V5/V6
      if (ADM_CMD_GET_PP_TOPO_MODULE_LIST == pPkt->opcode)
      {
        adm_cmd_rsp_get_pp_topo_module_list_t response;
        response.status = pDevCmd->rspResult;
        AudDevMgr_GenerateAck(pPkt,
                              pDevCmd->rspResult,
                              &(response),
                              sizeof(response),
                              ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST);
      }
      else //ADM_CMD_GET_PP_TOPO_MODULE_LIST_V2
      {
        adm_cmd_rsp_get_pp_topo_module_list_v2_t response;
        response.status = pDevCmd->rspResult;
        AudDevMgr_GenerateAck(pPkt,
                              pDevCmd->rspResult,
                              &(response),
                              sizeof(response),
                              ADM_CMDRSP_GET_PP_TOPO_MODULE_LIST_V2);
      }

    }//End of OOB

    Adm_AddDeviceCmdQToMask(pAdmStatSvc, unCmdQMask);

    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));

  }// ( 0 == unRespsNeeded)
  return result;
}

static ADSPResult Adm_RegisterDeregisterAprEventRspHandler(void *pAudStatAdmSvc, elite_msg_any_t *pMsg)
{
  ADSPResult                     result       = ADSP_EOK;
  AdmStatSvc_InfoType            *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  elite_msg_register_apr_event_t *pMsgPayload = (elite_msg_register_apr_event_t*)pMsg->pPayload;
  DeviceCmdProcInfo_t            *pDevCmd     = NULL;

  uint32_t           token      = pMsgPayload->unClientToken;
  uint16_t           unCoppID   = Adm_GetIndexFromToken(token);
  bool_t             isCompr    = FALSE;
  uint32_t           unCmdQMask = 0;
  elite_apr_packet_t *pPkt      = NULL;

  void *pDevice = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompr);

  if(NULL == pDevice)
  {
    return ADSP_EBADPARAM;
  }

  if(isCompr)
  {
    pDevCmd    = &((ComprCoppInfo_t*)pDevice)->devCmd;
    unCmdQMask = ((ComprCoppInfo_t*)pDevice)->devCmdQMask;
  }
  else
  {
    pDevCmd    = &((AdmCalPort_Type*)pDevice)->devCmd;
    unCmdQMask = ((AdmCalPort_Type*)pDevice)->devCmdQMask;
  }

  if(token != pDevCmd->token)
  {
    return ADSP_EBADPARAM;
  }

  pDevCmd->unRespsNeeded--;
  pDevCmd->rspResult |= pMsgPayload->unResponseResult;
  pPkt = pDevCmd->pCurrPkt;

  if(0 == pDevCmd->unRespsNeeded)
  {
    elite_apr_if_end_cmd(pAdmStatSvc->admAprHandle, pDevCmd->pCurrPkt, pDevCmd->rspResult);
    Adm_AddDeviceCmdQToMask(pAdmStatSvc, unCmdQMask);

    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
  }
  return result;
}

static ADSPResult Adm_DeviceCloseCmdHelperThread(AdmStatSvc_InfoType *pAdmStatSvc,
                                                 elite_apr_packet_t *pPkt)
{
  uint16_t   unCoppID     = ADM_GET_COPP_ID(elite_apr_if_get_dst_port(pPkt));
  bool_t     isCompressed = FALSE;
  ADSPResult result       = ADSP_EOK;

  void *ptr = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompressed);

  if(!ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Adm: Failed to get calport struct for device [%d]",unCoppID);
    return ADSP_EFAILED;
  }

  uint16_t mode = Adm_GetDeviceModeFromID(pAdmStatSvc, unCoppID);

  if(0 == mode)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Device Close rcvd on invalid Device ID [%d]", unCoppID);
    result = ADSP_EBADPARAM;
    return result;
  }

  Adm_HelperThrd_t    *pHelper = NULL;
  DeviceCmdProcInfo_t *pDevCmd = NULL;

  switch (mode)
  {
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_RX_PATH_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_LIVE_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_TX_PATH_NON_LIVE_COPP:
    case ADM_CMD_COPP_OPEN_MODE_OF_OPERATION_LOOPBACK_COPP:
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_DEVICE_LOOPBACK:
    {
      AdmCalPort_Type *phCalPort = (AdmCalPort_Type*)ptr;
      pHelper = &phCalPort->helperThrdInfo;
      pDevCmd = &phCalPort->devCmd;

      pHelper->unCoppId = unCoppID;
      pHelper->pPkt = pPkt;
      pHelper->pCloseFn = pAdmCloseDeviceHandler[mode];
      pHelper->unCmd = CLOSE;
      pHelper->pInstance = pAdmStatSvc;
      phCalPort->unCoppStatus = ADM_COPP_STATUS_DEINIT;
      break;
    }
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_RX:
    case ADM_CMD_DEVICE_OPEN_MODE_OF_OPERATION_COMPRESSED_TX:
    {
      ComprCoppInfo_t *pComprCoppInfo = (ComprCoppInfo_t*)ptr;

      pHelper = &pComprCoppInfo->helperThrdInfo;
      pDevCmd = &pComprCoppInfo->devCmd;

      pHelper->unCoppId = unCoppID;
      pHelper->pPkt = pPkt;
      pHelper->pCloseFn = pAdmCloseDeviceHandler[mode];
      pHelper->unCmd = CLOSE;
      pHelper->pInstance = pAdmStatSvc;
      pComprCoppInfo->unCoppStatus = ADM_COPP_STATUS_DEINIT;

      break;
    }
    default:
    {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM close cmd attempted with unsupported mode of operation [0x%04x]", mode);
      result = ADSP_EBADPARAM;
      return result;
    }
  }

  pHelper->unRspOpcode = ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_CLOSE_HELPER_THRD;

  /* Initial validation all okay. Go ahead and launch the helper thread */

  char helper_name[13]; // 4 spaces for the unique id and one for the NULL terminator.
  snprintf(helper_name, 13, "%s%lX", ADM_HELPER_THREAD_NAME, (unsigned long)unCoppID);

  if (ADSP_FAILED (result = qurt_elite_thread_launch(&(pHelper->tId), helper_name, \
                                                     NULL, ADM_HELPER_THREAD_CLOSE_STACK_SIZE, \
                                                     elite_get_thrd_prio(ELITETHREAD_STAT_AUDIO_DEV_SVC_PRIO_ID), \
                                                     Adm_HelperThreadEntryFunc, (void*)pHelper, \
                                                     QURT_ELITE_HEAP_DEFAULT)))
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM Failed to create the helper thread for Device Close");
    memset(pHelper, 0, sizeof(Adm_HelperThrd_t));
    memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));

    if(isCompressed)
    {
      ((ComprCoppInfo_t*)ptr)->unCoppStatus = ADM_COPP_STATUS_ACTIVE;
    }
    else
    {
      ((AdmCalPort_Type*)ptr)->unCoppStatus = ADM_COPP_STATUS_ACTIVE;
    }
    return result;
  }
  else
  {
    pDevCmd->unRespsNeeded++;
  }
  
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Create Helper thread ID 0x%x for Device Close",pHelper->tId);
  AudDevMgr_RequestHwResources(pAdmStatSvc);

  return result;
}

static ADSPResult Adm_DeviceCloseCmdUnsupportedHandler(AdmStatSvc_InfoType *pAdmStatSvc,
                                                       elite_apr_packet_t *pPkt,
                                                       qurt_elite_queue_t *pRspQ)
{
  return ADSP_EFAILED;
}

static ADSPResult Adm_HelperThreadResponseHandler(void* pAudStatAdmSvc, elite_msg_any_t *pMsg)
{
  void                *pCalPort    = NULL;
  bool_t              isCompressed = FALSE;
  uint16_t            *pCoppStatus = NULL;
  ADSPResult          result       = ADSP_EOK;
  Adm_HelperThrd_t    *pHelper     = NULL;
  DeviceCmdProcInfo_t *pDevCmd     = NULL;

  AdmStatSvc_InfoType               *pAdmStatSvc = (AdmStatSvc_InfoType*)pAudStatAdmSvc;
  EliteMsg_CustomAdmRspHelperThread *pMsgPayload = (EliteMsg_CustomAdmRspHelperThread*)pMsg->pPayload;
  uint16_t                          unCoppID     = pMsgPayload->deviceId;

  pCalPort = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompressed);

  if(!pCalPort)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"ADM: HelperThreadRspHandler Failed to get CalPort struct for device ID %d",unCoppID);
    return ADSP_EFAILED;
  }

  if(isCompressed)
  {
    pHelper     = &(((ComprCoppInfo_t*)pCalPort)->helperThrdInfo);
    pDevCmd     = &(((ComprCoppInfo_t*)pCalPort)->devCmd);
    pCoppStatus = &(((ComprCoppInfo_t*)pCalPort)->unCoppStatus);
  }
  else
  {
    pHelper     = &(((AdmCalPort_Type*)pCalPort)->helperThrdInfo);
    pDevCmd     = &(((AdmCalPort_Type*)pCalPort)->devCmd);
    pCoppStatus = &(((AdmCalPort_Type*)pCalPort)->unCoppStatus);
  }

  if(ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_OPEN_HELPER_THRD == pMsgPayload->unSecOpCode)
  {
    qurt_elite_thread_t helperTid = pHelper->tId;
    uint32_t unCmdQMask = 0;
    if(ADSP_SUCCEEDED(pMsgPayload->unResponseResult))
    {
        *pCoppStatus = ADM_COPP_STATUS_ACTIVE;
        Adm_SendOpenCmdRspAprMsg(pAdmStatSvc, pHelper);
        if(isCompressed)
        {
          unCmdQMask = (((ComprCoppInfo_t*)pCalPort)->devCmdQMask);
        }
        else
        {
          unCmdQMask = (((AdmCalPort_Type*)pCalPort)->devCmdQMask);
        }

        Adm_AddDeviceCmdQToMask(pAdmStatSvc, unCmdQMask);
    }
    else //if status failed
    {
      Adm_ResetCalPort(pCalPort, isCompressed);
    }

    qurt_elite_thread_join(helperTid, &result);
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Helper thread ID 0x%x joined for open", helperTid);
    memset(pHelper, 0, sizeof(Adm_HelperThrd_t));
  }

  else if(ELITEMSG_CUSTOM_RESPONSE_FOR_DEVICE_CLOSE_HELPER_THRD == pMsgPayload->unSecOpCode)
  {
    qurt_elite_thread_t helperTid = pHelper->tId;
    pDevCmd->unRespsNeeded--;

    if(0 == pDevCmd->unRespsNeeded)
    {
      if(ADSP_SUCCEEDED(pMsgPayload->unResponseResult))
      {

        result = Adm_HandleDeviceCmdQReq(pAdmStatSvc, unCoppID, isCompressed, FALSE);

        if(ADSP_FAILED(result))
        {
          MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to Remove Cmd Q for device [%d]",unCoppID);

        }
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Removed Cmd Q for device [%d]",unCoppID);
        Adm_ResetCalPort(pCalPort, isCompressed);
      }
      else
      {
        memset(pHelper, 0, sizeof(Adm_HelperThrd_t));
        memset(pDevCmd, 0, sizeof(DeviceCmdProcInfo_t));
        *pCoppStatus = ADM_COPP_STATUS_ACTIVE;
      }

      qurt_elite_thread_join(helperTid, &result);
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: Helper thread ID 0x%x joined for close",helperTid);
      memset(pHelper, 0, sizeof(Adm_HelperThrd_t));

    }
  }
  else
  {
    return ADSP_EUNEXPECTED;
  }

  AudDevMgr_RequestHwResources(pAdmStatSvc);
  return result;
}

void Adm_GetDeviceCmdQ(void *pInstance, uint16_t unCoppID, qurt_elite_queue_t **pDestQ)
{
  void *pCalPort = NULL;
  bool_t isCompr = FALSE;
  AdmStatSvc_InfoType *pAdmStatSvc = (AdmStatSvc_InfoType*)pInstance;
  *pDestQ = NULL;

  pCalPort = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompr);
  if(!pCalPort)
  {
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "NULL calpOrt");
    return;
  }

  if(isCompr)
  {
    *pDestQ = ((ComprCoppInfo_t*)pCalPort)->pCmdQ;
  }
  else
  {
    *pDestQ = ((AdmCalPort_Type*)pCalPort)->pCmdQ;
  }
  return;
}

static void* Adm_GetCalPortStructFromCoppID(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t unCoppID, bool_t *isCompressed)
{
  void     *pCalPort = NULL;
  uint32_t offset    = 0;

  *isCompressed      = FALSE;
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "ADM: unCoppID = %d",unCoppID);
#endif

  if(ADM_COMPRESSED_MIN_RX <= unCoppID && ADM_COMPRESSED_MAX_RX >= unCoppID)
  {
    offset   = unCoppID - ADM_COMPRESSED_MIN_RX;
    pCalPort = (void*)(&(pAdmStatSvc->rxStRtrParams.compr_copp_info[offset]));

    *isCompressed = TRUE;
  }
  else if(ADM_COMPRESSED_MIN_TX <= unCoppID && ADM_COMPRESSED_MAX_TX >= unCoppID)
  {
    offset   = (unCoppID - ADM_COMPRESSED_MIN_TX);
    pCalPort = (void*)(&(pAdmStatSvc->txStRtrParams.compr_copp_info[offset]));

    *isCompressed = TRUE;
  }
  else if(unCoppID < ADM_MAX_COPPS)
  {
    pCalPort = (void*)(&(pAdmStatSvc->deviceCalPort[unCoppID]));
  }

  return pCalPort;

}

static uint32_t Adm_GetDeviceCmdQIndex(uint16_t unCoppID)
{
  uint32_t index            = unCoppID;
  uint32_t compr_base_index = (ADM_RX_COPP_ID_SIZE + ADM_TX_COPP_ID_SIZE); // Start from 9 + 9 = 18th array pos
  uint32_t offset           = 0;

  if(ADM_COMPRESSED_MIN_RX <= unCoppID && ADM_COMPRESSED_MAX_RX >= unCoppID)
  {
    index = 0;
    offset = unCoppID - ADM_COMPRESSED_MIN_RX;
  }
  else if(ADM_COMPRESSED_MIN_TX <= unCoppID && ADM_COMPRESSED_MAX_TX >= unCoppID)
  {
    index = 0;
    offset = (unCoppID - ADM_COMPRESSED_MIN_TX) + (ADM_COMPRESSED_MAX_RX - ADM_COMPRESSED_MIN_RX + 1);
  }
  else //Regular COPPs both compr_base_index and offset are zero
  {
    compr_base_index = 0;
  }

  index += compr_base_index + offset;
  return index;
}

static uint16_t Adm_GetDeviceIdFromChannelBit(uint32_t unChBit)
{
#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: unChBit = %d", unChBit);
#endif
  uint16_t  unCoppID           = unChBit - ADM_SVC_Q_CHANNEL_NUM_BITS;
  uint32_t compr_rx_base_index = (ADM_RX_COPP_ID_SIZE + ADM_TX_COPP_ID_SIZE + ADM_SVC_Q_CHANNEL_NUM_BITS); // First 20 entries for regular copps, sys Qs
  uint32_t compr_rx_size       = ADM_COMPRESSED_MAX_RX - ADM_COMPRESSED_MIN_RX + 1;

  uint32_t compr_tx_base_index = compr_rx_base_index + compr_rx_size;
  uint32_t compr_tx_size       = ADM_COMPRESSED_MAX_TX - ADM_COMPRESSED_MIN_TX + 1;
  uint32_t compr_end_index     = compr_tx_base_index + compr_tx_size;

  if(unChBit >= compr_tx_base_index && unChBit < compr_end_index)
  {
    unCoppID = (unChBit - compr_tx_base_index) + ADM_COMPRESSED_MIN_TX;
  }
  else if(unChBit >= compr_rx_base_index && unChBit < compr_tx_base_index)
  {
    unCoppID = (unChBit - compr_rx_base_index) + ADM_COMPRESSED_MIN_RX;
  }

#ifdef ADM_SVC_QUEUE_PROC_DBG
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: unCoppID = %d", unCoppID);
#endif

  return unCoppID;

}


ADSPResult Adm_HandleDeviceCmdQReq(AdmStatSvc_InfoType *pAdmStatSvc, uint16_t unCoppID, bool_t isCompressed, bool_t isSetup)
{
  void            *ptr        = NULL;
  ADSPResult      result      = ADSP_EOK;
  ComprCoppInfo   *pComprCopp = NULL;
  AdmCalPort_Type *phCalPort  = NULL;

  /* Fetch the appropriate device info struct based on COPP ID*/
  ptr = Adm_GetCalPortStructFromCoppID(pAdmStatSvc, unCoppID, &isCompressed);

  if(!ptr)
  {
    MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM; Failed to get calport struct for CoppID [%d]",unCoppID);
    return ADSP_EFAILED;
  }

  if(isCompressed)
  {
    pComprCopp = (ComprCoppInfo_t*)ptr;
  }
  else
  {
    phCalPort = (AdmCalPort_Type*)ptr;
  }

  if(TRUE == isSetup)
  {
    uint32_t unCmdQIndex, unCmdQMask;

    char aDevCmdQName[12]; // 4 spaces for the unique id and one for the NULL terminator.
    snprintf(aDevCmdQName, 12, "%s%lX", ADM_DEVICE_CMD_Q_NAME, (unsigned long)unCoppID);

    unCmdQIndex = Adm_GetDeviceCmdQIndex(unCoppID);

    if(unCmdQIndex >= ADM_MAX_DEVICE_SESSIONS)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Invalid index %d for device [%d] cmd Q ", unCmdQIndex, unCoppID);
      return ADSP_EFAILED;
    }

    unCmdQMask = 1 << (unCmdQIndex + ADM_SVC_Q_CHANNEL_NUM_BITS);
#ifdef ADM_SVC_QUEUE_PROC_DBG
    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: index %d for device [%d] cmd Q mask pos %d", unCmdQIndex, unCoppID,(unCmdQIndex + ADM_SVC_Q_CHANNEL_NUM_BITS));
#endif

    qurt_elite_queue_t *pTempDevCmdQ = (qurt_elite_queue_t*)&admDeviceCmdQ[unCmdQIndex];

    if (ADSP_FAILED(result = qurt_elite_queue_init(aDevCmdQName,ADM_DEVICE_CMD_Q_ELEMENTS,pTempDevCmdQ)))
    {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to init device command Q for device [%d] with result %d ", unCoppID, result);
      return result;
    }

    if(isCompressed)
    {
      if(!pComprCopp)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to get calport struct for device [%d] ", unCoppID);
        qurt_elite_queue_deinit(pTempDevCmdQ);
        return ADSP_EFAILED;
      }

      pComprCopp->pCmdQ = pTempDevCmdQ;
      if(ADSP_FAILED(result = qurt_elite_channel_addq(&pAdmStatSvc->admChannel, pComprCopp->pCmdQ, unCmdQMask)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to add devcmdQ to channel for device [%d] ", unCoppID);
        qurt_elite_queue_deinit(pTempDevCmdQ);
        return result;
      }

      pComprCopp->devCmdQMask = qurt_elite_queue_get_channel_bit(pComprCopp->pCmdQ);

      qurt_elite_atomic_or(&pAdmStatSvc->unEnabledDeviceSessionMask, pComprCopp->devCmdQMask);
    }
    else
    {
      if(!phCalPort)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to get calport struct for device [%d] ", unCoppID);
        qurt_elite_queue_deinit(pTempDevCmdQ);
        return ADSP_EFAILED;
      }

      phCalPort->pCmdQ = pTempDevCmdQ;
      if(ADSP_FAILED(result = qurt_elite_channel_addq(&pAdmStatSvc->admChannel, phCalPort->pCmdQ, unCmdQMask)))
      {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADM: Failed to add devcmdQ to channel for device [%d] ", unCoppID);
        qurt_elite_queue_deinit(pTempDevCmdQ);
        return result;
      }

      phCalPort->devCmdQMask = qurt_elite_queue_get_channel_bit(phCalPort->pCmdQ);
      qurt_elite_atomic_or(&pAdmStatSvc->unEnabledDeviceSessionMask, phCalPort->devCmdQMask);
    }

    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADM: devcmdQ setup success for [%d] ", unCoppID);
  } //if isSetup == TRUE
  else
  {
    if(isCompressed)
    {
      if(!pComprCopp)
      {
        return ADSP_EFAILED;
      }

      if(NULL == pComprCopp->pCmdQ)
      {
        return ADSP_EOK;
      }

      /* After close, pop and release all the other commands */
      elite_svc_deinit_cmd_queue(pComprCopp->pCmdQ);

      qurt_elite_atomic_and(&pAdmStatSvc->unEnabledDeviceSessionMask, ~(pComprCopp->devCmdQMask));
      Adm_RemoveDeviceCmdQFromMask(pAdmStatSvc, ~(pComprCopp->devCmdQMask));

      pComprCopp->devCmdQMask = 0;
      pComprCopp->pCmdQ = NULL;
    }
    else
    {
      if(!phCalPort)
      {
        return ADSP_EFAILED;
      }
      if(NULL == phCalPort->pCmdQ)
      {
        return ADSP_EOK;
      }

      /* After close, pop and release all the other commands */
      elite_svc_deinit_cmd_queue(phCalPort->pCmdQ);

      qurt_elite_atomic_and(&pAdmStatSvc->unEnabledDeviceSessionMask, ~(phCalPort->devCmdQMask));
      Adm_RemoveDeviceCmdQFromMask(pAdmStatSvc, ~(phCalPort->devCmdQMask));

      phCalPort->devCmdQMask = 0;
      phCalPort->pCmdQ = NULL;

    }

  }
  return result;
}

static ADSPResult AdmSvc_DeviceCmdQ_Unsupported(void* pInstance, elite_msg_any_t* pMsg)
{
  return ADSP_EUNSUPPORTED;
}
