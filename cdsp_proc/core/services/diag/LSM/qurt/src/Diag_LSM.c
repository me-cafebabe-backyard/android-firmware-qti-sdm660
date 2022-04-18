
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Diag Legacy Service Mapping DLL

GENERAL DESCRIPTION

Implementation of entry point and Initialization functions for Diag_LSM.dll.


EXTERNALIZED FUNCTIONS
Diag_LSM_Init
Diag_LSM_DeInit

INITIALIZATION AND SEQUENCING REQUIREMENTS


Copyright (c) 2007-2010, 2012-2018 by QUALCOMM Technologies, Incorporated. All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

$Header: //components/rel/core.qdsp6/1.0.c2/services/diag/LSM/qurt/src/Diag_LSM.c#1 $

when       who    what, where, why
--------   ---    ----------------------------------------------------------
03/21/18   gn     Tagging the data with dynamic diag IDs
02/21/17   ph     Tag DIAG ID header to all the diag packets sent out.
02/08/17   nk     Added Log_submit() test case for User-PD
05/12/16   sa     Circular Mode for UserPD buffer
10/13/16   ph     Added handshake in the startup function of new task.
10/03/16   as     Migrated mutex lock calls to qurt_pimutex_lock()
10/03/16   gn     Changes to support common PW for ADSP, CDSP and SLPI
06/20/16   sa     Added MSG_SPRINTF stress tests
05/12/16   ph     SMD references removal and code clean up.
01/06/15   ph     Stress test tasks now get created with correct priority.
11/18/15   gn     Added loopback command in user PD.
07/15/15   xy     Fixed UserPD stress test issue
07/10/15   rh     Added delayed response UserPD test.
06/18/15   sa     Added support for time sync feature.
04/28/15   vk     Enabled exit from Diag_LSM_Init on timer create failure.
11/25/14   ph     Removed test case DIAGDIAG_STRESS_TEST_ERR_FATAL_ISR.
11/14/14  jtm/vk  Multi-PD Optimizations
10/09/14   sr     Added stress test in UserPD
07/06/14   ph     Added support for Diag over STM
03/11/14   sr     Resolved compiler warnings
12/23/13   ph     Included header files required to account for removal of ASSERT macro
10/21/13   sr     Init the mutex diag_lsm_ref_count_mutex only once although
                  diag_LSM_init() is called multiple times.
10/10/12   sg     Print the failure cases in Debug Buffer when Diag_LSM_Init is called
07/05/12   sg     Changes to bringup Diag MultiPD
06/29/10   mad    Eliminating TerminateThread() call altogether. If Diag_LSM_RxThread
                  does not exit gracefully in 100ms, do not do anything.
06/28/10   mad    Signalling Diag_LSM_RxThread to exit gracefully. The thread
                  is terminated if it does not return within 100ms.
06/25/10   mad    Minimizing error-window for the case where CreateFile fails:
                  Instead of calling the blanket De-Init(), just reset what is
                  necessary, before returning from Diag_LSM_Init().
                  Also, check for INVALID_HANDLE_VALUE before calling IOCTL
                  in RegisterForMaskChange().
06/24/10   mad    CreateFile() is called for WDG driver, if Handle value
                  is INVALID OR NULL
04/21/10   sg     Inclusion of diag_v.h for diag_client_maskchange()
04/21/10   sg     Fix to close handles after we terminate the thread
04/20/10   sg     Fixing memory leak with ghDiag_Pkt_Process_Event,ghRxThread
12/03/09   sg     CreateThread() change to return HTHREAD, instead of HANDLE
09/16/09   sg     Included diagpkt.h for the definitions of diag packets
                  Tx and RX Max Sizes macros
06/04/09   mad    Closed Registry key in CreateWaitThread() to fix memory leak.
01/22/09   mad    Now calling Diag_LSM_DeInit() from Diag_LSM_Init(), if
                  windiag driver Open() call fails
01/15/09   mad    Added Synch. Event to signal diag thread reg. processing
                  packet from common table(e.g. mask change)
01/15/09   mad    Priority of Rx thread is now equal to diag thread priority
12/03/08   mad    Changes to take out Component services, and use
                   filesystem calls to access windiag driver, for diag
                  stream-driver model. Added an RxThread that waits for
                  mask-change and incoming-packet events.
10/31/08   mad    Fix for crash in Diag_LSM_Log_Init() when Diag_LSM_Init()-DeInit()
                  is called multiple times. Reset global handles etc explicitly to
                  NULL, in Diag_LSM_DeInit(), so they get initialized correctly
                  in the subsequent Diag_LSM_Init() call.
09/03/08   mad    Added reference count to maintain Diag_LSM functionality,
                  when multiple clients in same process call Diag_LSM_Init()
                  and Diag_LSM_DeInit().
04/23/08   JV     Added calls to functions that update masks during bring-up.
                  LSM registers for a mask change during Init.Now calling
                      diagpkt_bindpkt with the UnBind ID during de-init.
04/14/08   JV     Created instance of IDiagPktRsp
03/19/08   JV     Added packet service to init and de-init functions.
02/05/08   mad    Moved declarations for Diag_LSM_Init() and Diag_LSM_DeInit()
                  to Diag_LSM.h. This will enable clients to include
                  Diag_LSM.h and call the functions directly.
01/15/08   mad    Removed explicit linking to a1Host.lib, now using
                  LoadLibrary() and GetProcAddress() to call functions
                  exported by a1Host.dll. This was done to avoid a1Host.dll
                  being loaded implicitly upon loading of Diag_LSM.dll.
11/29/07   mad    Created

===========================================================================*/

/* separating windows-specific includes, in case this file is featurised
and made common later. */

#include "comdef.h"
#include "Diag_LSMi.h"
#include "DiagSvc_Malloc.h"
#include "Diag_LSM_Event_i.h"
#include "Diag_LSM_Log_i.h"
#include "Diag_LSM_Msg_i.h"
#include "diagpkti.h" /* For definition of diag_cmd_rsp */
#include "Diag_LSM_Pkt_i.h"
#include "diag_shared_i.h" /* For different constants */
#include "diagpkt.h"
#include "diag_v.h"
#include "qurt_qdi.h"
#include "qurt.h"
#include "Diag_LSM.h"
#include "diagdiag_v.h"
#include "diagstub.h"
#include "Diag_LSM_Qdi_wrapper.h"
#include "stdio.h"
#include "diagbuf_mpd_type.h"
#include "diagbuf_mpd.h"

#include "Diag_LSM_stm.h"
#include "osal.h"
#include "event_defs.h"
#include "event.h"
#include "npa.h"
#include "qw.h"
#include "stringl.h"
#include "diag_cfg.h"  /* For DIAG_MULTIPD_BUF_SIZE */
#include "ULogFront.h"
#include "diag_param.h"
#include "servreg_locator.h" /*For servreg API to get process name*/
#include "diag_diagIDi.h"

ULogHandle diag_err_log_handle = NULL;
/* Action Codes for RegisterForMaskChange() function */
#define MASK_CHANGE_REGISTER     0
#define MASK_CHANGE_DEREGISTER   1

#define DIAG_LSM_STACK_SIZE      (1024 * 4)
unsigned long long diag_lsm_stack[DIAG_LSM_STACK_SIZE];

/* Extern section */
extern diagbuf_mpd_type *diagmpd_buf;

/* Static section */
static boolean TerminateWaitThread(void);
static boolean CreateWaitThread(void);
static boolean RegisterForMaskChange(uint32 ActionCode);


/* Global */
int diag_qdi_handle = -1;
qurt_thread_t thread_id;
/* This process's receive thread channel ID */

/* This process's pid */
int diag_pid;
/*A reference count to maintain the number of
clients in the same process. This will be used to:
1. Prevent re-initialization if already initialized in the same process
2. Prevent De-Initialization if other clients are still using Diag_LSM
*/
uint32 gnDiag_LSM_Ref_Count = 0;
qurt_mutex_t diag_lsm_ref_count_mutex;
static unsigned int diag_lsm_ref_count_mutex_init = FALSE;
unsigned long long diag_lsm_stack[4096];


/* Stores info, wheather Q is initialised or not */
boolean diag_stress_test_task_q_init = FALSE;
/* Predetermined sequence for stress test*/
byte pseudo_array[] = { 6, 2, 4, 5, 3, 0, 1, 2, 5, 0, 3, 1, 6, 4 };

/*Queue with stress test task*/
q_type diag_stress_test_task_q;
osal_thread_attr_t diagdiag_stress_attr;

/* Internal function declarations*/

/* To track the time API to be used */
diag_time_api_types diag_time_api_to_use_lsm = 0;

/* Variable related to the time API configuration */
boolean diag_time_initialized_lsm = FALSE;  /* Track if the diag time API is initialized */
static int diag_time_init_begin_lsm = FALSE;

/* Function pointer to update the time API to be used */
uint8 (*diag_time_get_LSM)(qword);

PACKED void * stress_test_task (
  PACKED void *req_pkt,
  uint16 pkt_len
);

void Diag_LSM_stresstest(
   uint32 params
);


PACKED void* Diag_LSM_Health_Command( PACKED void *req_pkt, uint16 pkt_len );
PACKED void* diag_lsm_loopback( PACKED void *req_pkt, uint16 pkt_len );

PACKED void * diag_LSM_test_cmd_handler (
  PACKED void *req_pkt,
  uint16 pkt_len
);
PACKED void* diag_pd_buf_mode_change( PACKED void *req_pkt,uint16 pkt_len);

PACKED void* Diag_LSM_Delay_Test(PACKED void *req_pkt, uint16 pkt_len);

#ifdef USER_PD_STRESS_TEST_CMD_CODE
static const diagpkt_user_table_entry_type diag_userpd_test_tbl[] =
{
  {USER_PD_STRESS_TEST_CMD_CODE, USER_PD_STRESS_TEST_CMD_CODE, diag_LSM_test_cmd_handler},
};
#endif
#ifdef USER_PD_V2_TEST_CMD_CODE
static const diagpkt_user_table_entry_type test_tbl_v2[] =
{
  {USER_PD_V2_TEST_CMD_CODE, USER_PD_V2_TEST_CMD_CODE, Diag_LSM_Delay_Test},
};
#endif
uint8 diag_get_diagID_LSM(void);

/*===========================================================================
FUNCTION   Diag_LSM_Init

DESCRIPTION
  Initializes the Diag Legacy Service Mapping Layer.

DEPENDENCIES
  Successful initialization of Diag in User PD requires Diag_LSM_Init to be
  called in UserPD.
  This function can be called multiple times; mutex initialization should happen only once

RETURN VALUE
  FALSE = failure, else TRUE

SIDE EFFECTS
  None

===========================================================================*/

boolean Diag_LSM_Init(byte *pParam)
{
  uint8* qsr4_guid_ptr = NULL;
  char* process_name;
  if (qurt_atomic_compare_and_set(&diag_lsm_ref_count_mutex_init, FALSE, TRUE))
  {
    qurt_pimutex_init(&diag_lsm_ref_count_mutex);
  }
  qurt_pimutex_lock(&diag_lsm_ref_count_mutex);
  if (0 == gnDiag_LSM_Ref_Count)
  {
    diag_pid = qurt_getpid();
    if (0 > diag_qdi_handle)
    {
      diag_qdi_handle = qurt_qdi_open("/dev/diag");
      if (diag_qdi_handle < 0)
      {
        printf(" \nDiag_LSM_Init : QDI open failed\n");
        qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
        return (FALSE);
      }

      ULogFront_RealTimeInit(&diag_err_log_handle,"DiagErrorsLSM", DIAG_ERR_ULOG_SIZE, ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
      ULogFront_RealTimePrintf(diag_err_log_handle,0,"LSM diag init");
	  
      //Now need to initialize the diagbuf used for the PD
      //This has to be done this way, so the user PD can get a pointer to the shared buffer that is created
      if ( diag_lsm_get_diag_buf(&diagmpd_buf, DIAG_MULTIPD_BUF_SIZE, diag_pid) < 0 )
      {
        printf("\nDiag_LSM_Init : Failed to get buffer pointer from Guest OS\n");
        Diag_LSM_DeInit();
        return (FALSE);
      }

      /*
      Set the diagID of the user process. This returns hard-coded value now
      and is migrated to dynamic diagID implementation in future.
      */


      if ( diag_lsm_init_event_queue(&diagmpd_buf, DIAG_MPD_EVENT_HEAP_SIZE) < 0 )
      {
        printf("\nDiag_LSM_Init : Failed to setup event structs");
        Diag_LSM_DeInit();
        return (FALSE);
      }

      if (osal_create_diag_timer_ex(&diagmpd_buf->diagbuf_mpd_drain_timer, osal_thread_self(), diagbuf_mpd_set_drain_timer, 0) != OSAL_SUCCESS)
      {
        printf("\nDiag_LSM_Init : Failed to create drain timer for the PD\n");
        Diag_LSM_DeInit();
        return (FALSE);
      }
    }
    if (!DiagSvc_Malloc_Init())
    {
      printf("Diag_LSM_Init : SVC malloc failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

    if(!RegisterForMaskChange(MASK_CHANGE_REGISTER))
    {    
      printf("Diag_LSM_Init : registerformaskchange failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return FALSE;
    }
    
    /*request for process_name from TMS and then make QDI call to let rootPD request diagID from APPS*/
    process_name=servreg_get_local_domain();
    if(!diag_lsm_request_diagID(process_name,qsr4_guid_ptr))
    {
      Diag_LSM_DeInit();
      qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

    if (!CreateWaitThread())
    {
      printf("Diag_LSM_Init : createwaitthread failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

    if (!Diag_LSM_Pkt_Init())
    {
      printf("Diag_LSM_Init : lsm pkt init failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

    
    if (!Diag_LSM_Log_Init())
    {
      printf("Diag_LSM_Init : lsm log init failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

    if (!Diag_LSM_Event_Init())
    {
      printf("Diag_LSM_Init : lsm event init failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

    if (!Diag_LSM_Msg_Init())
    {
      printf("Diag_LSM_Init : lsm msg init failed\n");
      Diag_LSM_DeInit();
      qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
      return (FALSE);
    }

#ifdef FEATURE_DIAG_STM
    diag_stm_init();
#endif

    if(FALSE == diag_time_initialized_lsm)
    {
      diag_time_init_LSM();
    }

    #ifdef USER_PD_STRESS_TEST_CMD_CODE
      DIAGPKT_DISPATCH_TABLE_REGISTER (DIAG_SUBSYS_DIAG_SERV, diag_userpd_test_tbl);
      #endif
#ifdef USER_PD_V2_TEST_CMD_CODE
      DIAGPKT_DISPATCH_TABLE_REGISTER_V2_DELAY (DIAG_SUBSYS_CMD_VER_2_F, DIAG_SUBSYS_DIAG_SERV, test_tbl_v2);
#endif
  } /*end if(!InterlockedCompareExchange(&gnDiag_LSM_Ref_Count,1,0) */
  gnDiag_LSM_Ref_Count += 1;
  qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
  return (TRUE);
}                               /* Diag_LSM_Init */

/*===========================================================================

FUNCTION    Diag_LSM_DeInit

DESCRIPTION
  De-Initialize the Diag service.

DEPENDENCIES
  None.

RETURN VALUE
  FALSE = failure, else TRUE.

SIDE EFFECTS
  None

===========================================================================*/

boolean Diag_LSM_DeInit(void)
{
  boolean bReturn = TRUE;
  qurt_pimutex_lock(&diag_lsm_ref_count_mutex);
  if (1 < gnDiag_LSM_Ref_Count)
  {
    //Someone's still using diag, so just count down and go on with business...
    gnDiag_LSM_Ref_Count -= 1;
    qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
    return (bReturn);
  }
  else if (0 == gnDiag_LSM_Ref_Count)
  {
    qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
    return (TRUE);
  }

  DiagSvc_Malloc_Exit();

  if (!Diag_LSM_Event_DeInit() || !Diag_LSM_Pkt_DeInit() || !Diag_LSM_Log_DeInit() || !Diag_LSM_Msg_DeInit())
    bReturn = FALSE;

  if (!RegisterForMaskChange(MASK_CHANGE_DEREGISTER))
    bReturn = FALSE;

  if (!TerminateWaitThread())
  {
    bReturn = FALSE;
  }

  if (!osal_delete_timer(&diagmpd_buf->diagbuf_mpd_drain_timer))
  {
    bReturn = FALSE;
  }

  if (0 != qurt_qdi_close(diag_qdi_handle))
  {
    bReturn = FALSE;
  }
  diag_qdi_handle = -1;
  //We uninitialized things because it's the last one, so mark this as having 0 references.
  gnDiag_LSM_Ref_Count = 0;
  qurt_pimutex_unlock(&diag_lsm_ref_count_mutex);
  return (bReturn);
}     /* Diag_LSM_DeInit */

/*===========================================================================

FUNCTION DIAG_LSM_TEST_CMD_HANDLER

DESCRIPTION
  This procedure handles the test command for stress test and health statistic
  commands

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACKED void* diag_LSM_test_cmd_handler(
   PACKED void *req_pkt,
   uint16 pkt_len
   )
{
  diag_LSM_test_cmd_rsp_type *rsp = NULL;
  diag_LSM_test_cmd_req_type *req = (diag_LSM_test_cmd_req_type *)req_pkt;

  if (req_pkt == NULL)
  {
    return (diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len));
  }

  switch (req->opcode)
  {
     case DIAGDIAG_STRESS_TEST_OPCODE:
       rsp = stress_test_task(req_pkt, pkt_len);
       return ((void *)rsp);
       break;
     case DIAGDIAG_HEALTH_CMD_OPCODE:
       rsp = Diag_LSM_Health_Command(req_pkt, pkt_len);
       return ((void *)rsp);
       break;
     case DIAGDIAG_LOOPBACK_CMD_OPCODE:
       rsp = diag_lsm_loopback(req_pkt, pkt_len);
       return ((void *)rsp);
       break;
     case DIAGDIAG_PD_BUF_MODE_OPCODE:
     rsp = diag_pd_buf_mode_change(req_pkt, pkt_len);
       return ((void *)rsp);
       break;
     default:
       return (diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len));
       break;
  }

}

/*===========================================================================

FUNCTION DIAG_LSM_DELAY_TEST

DESCRIPTION
  This function creates a standard command response and a delayed response.

RETURN VALUE
  NULL

============================================================================*/
PACKED void* Diag_LSM_Delay_Test(
   PACKED void *req_pkt,
   uint16 pkt_len
   )
{
  uint32 delayed_rsp_id = 0;
  diagdiag_delayed_rsp_test_rsp_type *rsp = (diagdiag_delayed_rsp_test_rsp_type *)
                                             diagpkt_subsys_alloc_v2(DIAG_SUBSYS_DIAG_SERV, USER_PD_V2_TEST_CMD_CODE,
                                                                     sizeof(diagdiag_lsm_delayed_rsp_test_rsp_type));
  MSG(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"Sending delayed responses");
  if(rsp)
  {
    delayed_rsp_id = rsp->delayed_rsp_id;
    diagpkt_commit(rsp);
  }
  else
  {
    MSG(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"Out of memory- Cannot send the response");
  }

  rsp = NULL;

  rsp = (diagdiag_delayed_rsp_test_rsp_type *)diagpkt_subsys_alloc_v2_delay(DIAG_SUBSYS_DIAG_SERV, USER_PD_STRESS_TEST_CMD_CODE,
                                                                            delayed_rsp_id, sizeof(diagdiag_lsm_delayed_rsp_test_rsp_type));
  if(rsp)
  {
    rsp->response_cnt = 1;
    diagpkt_delay_commit(rsp);
  }
  else
  {
    MSG(MSG_SSID_DIAG, MSG_LEGACY_HIGH,
                "Out of memory- Cannot send the delayed response");
  }

  return NULL;
}

/*===========================================================================

FUNCTION DIAG_MPDBUF_MODE_CHANGE

DESCRIPTION
  This function changes the value of 'diagbuf_mpd_mode' which controls UserPD buffer reading

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACKED void* diag_pd_buf_mode_change(
     PACKED void *req_pkt,
     uint16 pkt_len)

{

  diag_LSM_test_cmd_rsp_type *rsp = NULL;
  uint16 req_len = 0;
  uint8 mode=0;
  diag_LSM_test_cmd_req_type *req = (diag_LSM_test_cmd_req_type *)req_pkt;
  if (req_pkt == NULL)
  {
    return (diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len));
  }

  req_len = FPOS(diag_LSM_test_cmd_req_type, cmd_type);

  /*Packet length should be atleast req_length*/
  if (pkt_len < req_len)
  {
    return (diagpkt_err_rsp(DIAG_BAD_LEN_F, req_pkt, pkt_len));
  }
  mode = req->cmd_type.pd_buf_mode;
  rsp = (diag_LSM_test_cmd_rsp_type *)diagpkt_subsys_alloc(DIAG_SUBSYS_DIAG_SERV,
                                                           USER_PD_STRESS_TEST_CMD_CODE, pkt_len);

  if(rsp!=NULL)
  {
    rsp->opcode = req->opcode;
    rsp->rsp_cmd_type.pd_buf_mode = diag_set_pd_buf_mode(mode);
   // memscpy(rsp,pkt_len,req_pkt,pkt_len);
  }

  return (rsp);
}


/*===========================================================================

FUNCTION DIAG_LSM_HEALTH_COMMAND

DESCRIPTION
  This procedure collects/resets and send LSM health statistics.

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACKED void* Diag_LSM_Health_Command(
   PACKED void *req_pkt,
   uint16 pkt_len
   )
{
  /* Initialization */
  diagpkt_subsys_cmd_code_type cmd_code;
  uint16 health_rsp_len = 0;
  uint16 req_len = 0;
  diag_LSM_test_cmd_rsp_type *rsp = NULL;

  diag_LSM_test_cmd_req_type *req = (diag_LSM_test_cmd_req_type *)req_pkt;

  if (req_pkt == NULL)
  {
    return (diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len));
  }

  cmd_code = req->cmd_type.diag_LSM_health_command;

  req_len = FPOS(diag_LSM_test_cmd_req_type, cmd_type) + sizeof(uint16);
  if (pkt_len != req_len)
  {
    return (diagpkt_err_rsp(DIAG_BAD_LEN_F, req_pkt, pkt_len));
  }

  health_rsp_len = FPOS(diag_LSM_test_cmd_rsp_type, rsp_cmd_type) + sizeof(diag_LSM_health_cmd_type);

  rsp = (diag_LSM_test_cmd_rsp_type *)diagpkt_subsys_alloc(DIAG_SUBSYS_DIAG_SERV,
                                                           USER_PD_STRESS_TEST_CMD_CODE, health_rsp_len);

  if (rsp != NULL)
  {
    rsp->opcode = req->opcode;
    rsp->rsp_cmd_type.health_cmd.cmd_code = cmd_code;
    switch (cmd_code)
    {
       case DIAGDIAG_GET_ALLOC_COUNT_F3_Q6:
       case DIAGDIAG_GET_ALLOC_COUNT_F3_MODEM:
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_msg_alloc_count();
         break;
       case DIAGDIAG_GET_DROP_COUNT_F3_Q6:
       case DIAGDIAG_GET_DROP_COUNT_F3_MODEM:
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_msg_drop_count();
         break;
       case DIAGDIAG_RESET_DROP_COUNT_F3_Q6:
       case DIAGDIAG_RESET_DROP_COUNT_F3_MODEM:
         diagbuf_mpd_reset_msg_alloc_drop_counts();
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_msg_drop_count();
         break;
       case DIAGDIAG_GET_ALLOC_COUNT_LOG_Q6:
       case DIAGDIAG_GET_ALLOC_COUNT_LOG_MODEM:
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_log_alloc_count();
         break;
       case DIAGDIAG_GET_DROP_COUNT_LOG_Q6:
       case DIAGDIAG_GET_DROP_COUNT_LOG_MODEM:
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_log_drop_count();
         break;
       case DIAGDIAG_RESET_DROP_COUNT_LOG_Q6:
       case DIAGDIAG_RESET_DROP_COUNT_LOG_MODEM:
         diagbuf_mpd_reset_log_alloc_drop_counts();
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_log_drop_count();
         break;
     case DIAGDIAG_GET_ALLOC_COUNT_EVENT_Q6:
       case DIAGDIAG_GET_ALLOC_COUNT_EVENT_MODEM:
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_event_alloc_count();
         break;
       case DIAGDIAG_GET_DROP_COUNT_EVENT_Q6:
       case DIAGDIAG_GET_DROP_COUNT_EVENT_MODEM:
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_event_drop_count();
         break;
       case DIAGDIAG_RESET_DROP_COUNT_EVENT_Q6:
       case DIAGDIAG_RESET_DROP_COUNT_EVENT_MODEM:
         diagbuf_mpd_reset_event_alloc_drop_counts();
         rsp->rsp_cmd_type.health_cmd.drop_count = diagbuf_mpd_get_event_drop_count();
         break;
    }
  }

  return (rsp);
} /* Diag_LSM_Health_Command */

/*===========================================================================

FUNCTION DIAG_LSM_LOOPBACK

DESCRIPTION
  This procedure echos the request in the response.

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACKED void* diag_lsm_loopback( PACKED void *req_pkt, uint16 pkt_len )
{

  diag_LSM_test_cmd_rsp_type *rsp = NULL;
  uint16 req_len = 0;

  if (req_pkt == NULL)
  {
    return (diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len));
  }

  req_len = FPOS(diag_LSM_test_cmd_req_type, cmd_type);

  /*Packet length should be atleast req_length*/
  if (pkt_len < req_len)
  {
    return (diagpkt_err_rsp(DIAG_BAD_LEN_F, req_pkt, pkt_len));
  }

  rsp = (diag_LSM_test_cmd_rsp_type *)diagpkt_subsys_alloc(DIAG_SUBSYS_DIAG_SERV,
                                                           USER_PD_STRESS_TEST_CMD_CODE, pkt_len);

  if(rsp)
  {
    memscpy(rsp,pkt_len,req_pkt,pkt_len);
  }

  return ((void *)rsp);
}

/*===========================================================================

FUNCTION STRESS_TEST_TASK

DESCRIPTION
  This procedure sends a response to acknowledge that the test has been started.
  It then defines "num_tasks" tasks, with a requested priorities.
  The task startup functions tests flooding the link using the requested
  parameters.

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACKED void* stress_test_task(
   PACKED void *req_pkt,
   uint16 pkt_len
   )
{
  diag_LSM_test_cmd_rsp_type *rsp;
  diag_LSM_test_cmd_req_type *req = (diag_LSM_test_cmd_req_type *)req_pkt;
  int rsp_len = 0;
  /*  used to store and retrive data block from the Q */
  diag_stress_test_task_q_item_type *q_item = NULL;
  int i = 0;

  rsp_len = FPOS(diag_LSM_test_cmd_req_type, cmd_type) + FPOS(diag_LSM_stress_test_type, test)
     + sizeof(diag_per_task_test_info) * (req->cmd_type.stress_test_info.num_tasks);

  if (pkt_len != rsp_len)
  {
    return (diagpkt_err_rsp(DIAG_BAD_LEN_F, req_pkt, pkt_len));
  }

    #ifdef USER_PD_STRESS_TEST_CMD_CODE
    rsp = (diag_LSM_test_cmd_rsp_type *) diagpkt_subsys_alloc (
    DIAG_SUBSYS_DIAG_SERV,
    USER_PD_STRESS_TEST_CMD_CODE,
    rsp_len
    );
  #else
  /*Not a recognized PD - Currently USER_PD_STRESS_TEST_CMD_CODE is defined for
  Audio and Sensor PD*/
  return (diagpkt_err_rsp (DIAG_BAD_CMD_F, req_pkt, pkt_len));
  #endif

  /* Send the response acknowledging that the packet has been started */
  if (rsp != NULL)
  {
    memscpy((void *)rsp, rsp_len, (void *)req, rsp_len);

    /* Initialize the queue */
    if (diag_stress_test_task_q_init == FALSE)
    {
      (void)q_init(&diag_stress_test_task_q);
      diag_stress_test_task_q_init = TRUE;
    }

    for (i = 0; i < req->cmd_type.stress_test_info.num_tasks; i++)
    {
      /* Get memory from the system heap */
      q_item = (diag_stress_test_task_q_item_type *)malloc(
         sizeof(diag_stress_test_task_q_item_type));

      if (q_item != NULL)
      {
        memset(q_item, 0x0, sizeof(diag_stress_test_task_q_item_type));

        /* Initialize the link field */
        (void)q_link(q_item, &(q_item->link));

        /* Fill the data */
        q_item->data.task_info = req->cmd_type.stress_test_info.test[i];
        q_item->data.status = DIAG_TASK_INITIALIZED;
        q_item->data.unique_id = i;   /* Task IDs range from 0 to num_tasks-1 */

        /* Place q_item on the diag_stress_test_task_q */
        q_put(&diag_stress_test_task_q, &(q_item->link));
      }
      else
      { /* Failed  system malloc, handle this error */
        diagpkt_commit(rsp);
        rsp = NULL;
        MSG_4(MSG_SSID_DIAG, MSG_LEGACY_ERROR, "Failed to allocate q_item for stress test. cmd %d %d %d %d\n", req->header.opaque_header[0],
              req->header.opaque_header[1], req->header.opaque_header[2], req->header.opaque_header[3]);
        return (NULL);
      }
    }

    /* Commit the response before spawning the test task. */
    diagpkt_commit(rsp);

    rsp = NULL;
  }

  /* Get the head of the Q */
  q_item = (diag_stress_test_task_q_item_type *)q_check(&diag_stress_test_task_q);

  /* Loop until the end is reached */
  while (q_item != NULL)
  {
    /* if the task is not yet started */
    if (q_item->data.status == DIAG_TASK_INITIALIZED)
    {
      int diagdiag_stress_pri_array[32] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

      if (q_item->data.task_info.priority.pri_type == RELATIVE_PRI)
      {
          uint16 sleep_pri = SLEEP_PRI;
          uint16 diag_pri  = osal_thread_get_pri();

          if(diag_pri < sleep_pri )
          {
            /*1 is highest prio and 255 is lowest */
            if ( diag_pri + q_item->data.task_info.priority.pri < sleep_pri )
            {
                q_item->data.task_info.priority.pri += diag_pri;
            }
            else
            {
                q_item->data.task_info.priority.pri = sleep_pri - 1;
            }
          }
          else
          {
            /*1 is lowest prio and 255 is highest */
            if ( diag_pri + q_item->data.task_info.priority.pri < sleep_pri )
          {
                /*Priority cannot be negative*/
                q_item->data.task_info.priority.pri = sleep_pri + 1 ;
          }
          else
          {
                q_item->data.task_info.priority.pri += diag_pri ;
            }
          }
        }

      /* Start the task */
      /* stack is of type unsigned long long' */
      diagdiag_stress_attr.stack_size = (STRESS_TEST_STACK_SIZE * sizeof(unsigned long long));
      diagdiag_stress_attr.start_func = Diag_LSM_stresstest;
      diagdiag_stress_attr.arg = (void *)(&(q_item->data));
      diagdiag_stress_attr.name = "Diag_LSM_stresstest";
      diagdiag_stress_attr.priority = q_item->data.task_info.priority.pri;
      diagdiag_stress_attr.stack_address = q_item->data.stack;
      diagdiag_stress_attr.p_tskname = "DIAG_LSM_TEST";
      diagdiag_stress_attr.suspended = FALSE;
      diagdiag_stress_attr.dog_report_val = 0;

      /* Mark the task is running BEFORE creating the thread for multi-threaded case */
      if (q_item->data.status == DIAG_TASK_INITIALIZED)
      {
        q_item->data.status = DIAG_TASK_RUNNING;
      }

      if ((osal_create_thread(&(q_item->data.tcb), &diagdiag_stress_attr, diagdiag_stress_pri_array)) != 0)
      {
#ifdef FEATURE_Q_NO_SELF_QPTR
          q_delete( &diag_stress_test_task_q, &q_item->link );
#else
          q_delete  (&q_item->link);
#endif
          free(q_item);
          return NULL;
      }

    }
    /* go to the next Q item */
    q_item = q_next(&diag_stress_test_task_q, &q_item->link);
  }

  return (NULL);
}
/*===========================================================================

FUNCTION DIAG_LSM_STRESSTEST_CLEANUP_CB

DESCRIPTION
  This procedure is a cleanup function. It goes through the
  diag_stress_test_task_q, checks if any data block is ready to cleaned.
  If yes it removes the entry from the Q and frees the memory.

============================================================================*/
void diag_LSM_stresstest_cleanup_cb(void)
{
  diag_stress_test_task_q_item_type *q_cur_ptr = NULL;
  diag_stress_test_task_q_item_type *q_next_ptr = NULL;
  int status;

  q_cur_ptr = (diag_stress_test_task_q_item_type *)q_check(&diag_stress_test_task_q);
  while (q_cur_ptr != NULL)
  {
    // If the element in the queue is ready to be deleted
    if (q_cur_ptr->data.status == DIAG_TASK_DONE)
    {
      // mapped to no-ops for all OSes except QURT
      osal_thread_join(&(q_cur_ptr->data.tcb), &status);

      // cleanup OSAL related memory, queues, channel etc
      osal_delete_thread(&(q_cur_ptr->data.tcb));

      // store the next link
      q_next_ptr = (diag_stress_test_task_q_item_type *)q_next
         (&diag_stress_test_task_q, &q_cur_ptr->link);

      // Remove the data block from the Q
#ifdef FEATURE_Q_NO_SELF_QPTR
      q_delete(&diag_stress_test_task_q, &q_cur_ptr->link);
#else
      q_delete(&q_cur_ptr->link);
#endif


      // Free the memory
      free(q_cur_ptr);

      if (q_cur_ptr != NULL)
      {
        q_cur_ptr = NULL;
      }
      q_cur_ptr = q_next_ptr;
    }
    else
    {
      // store the next link
      q_cur_ptr = (diag_stress_test_task_q_item_type *)q_next
         (&diag_stress_test_task_q, &q_cur_ptr->link);
    }
  }
}

void Diag_LSM_RxThread(void *parameter)
{
  int return_val = 0;
  byte Req_Buf[DIAG_MAX_RX_PKT_SIZ];
  dword num_bytes_read = 0;
  int status = 0;
  do
  {
    return_val = diag_lsm_wait_for_event();
    if (return_val & SYNC_EVENT_DIAG_LSM_PKT_IDX)
    {
      num_bytes_read = diag_lsm_read_data(Req_Buf, DIAG_MAX_RX_PKT_SIZ);

      if (num_bytes_read <= DIAG_MAX_RX_PKT_SIZ)
      {
        diagpkt_LSM_process_request((void *)Req_Buf, (uint16)num_bytes_read, NULL, NULL);
      }
    }


	/* Do not ask for mask if diagID is not yet set */  
    if(diagmpd_buf->diagID != DIAGID_UNKNOWN_ID)
    {
      if (return_val & DIAG_EVENTSVC_MASK_CHANGE)
      {
        event_update_mask();
      }
      if (return_val & DIAG_LOGSVC_MASK_CHANGE)
      {
        log_update_mask();
      }
      if (return_val & DIAG_MSGSVC_MASK_CHANGE)
      {
        msg_update_mask();
      }
    }

    if(return_val & DIAG_DIAGID_CHANGE)
    {
      boolean status=FALSE;
      status = diag_get_diagID_LSM();
      /* Update the masks now if diagID was updated. */
      if(status == TRUE)
      {
        event_update_mask();
        log_update_mask();
        msg_update_mask();
      }
    }
	
    if(return_val & DIAG_TIME_API_CHANGE)
    {
      diag_set_time_api_LSM();
    }
#ifdef FEATURE_DIAG_STM
    if (return_val & DIAG_STM_MODE_CHANGE)
    {
      diag_stm_update_mode_LSM();
    }
#endif
    if (return_val & DIAG_KILL_RX_THREAD)
    {
      qurt_thread_exit(status);
    }
    if (return_val & DIAG_KILL_STRESS_TEST_THREAD)
    {
      diag_LSM_stresstest_cleanup_cb();
    }
  }while (1);

}
/*===========================================================================
DESCRIPTION
   Creates synchronization events for incoming packets and mask change.
   Creates the thread that waits on these synchronization events.
===========================================================================*/

boolean CreateWaitThread(void)
{
  boolean ret = TRUE;
  int ret_value = 0;
  qurt_thread_attr_t tattr;

  unsigned int stackbase;

  stackbase = (unsigned int)diag_lsm_stack;
  qurt_thread_attr_init(&tattr);
  qurt_thread_attr_set_stack_size(&tattr, ((DIAG_LSM_STACK_SIZE * 8) - 8));
  qurt_thread_attr_set_stack_addr(&tattr, (void *)((stackbase + 7) & (~7)));
  qurt_thread_attr_set_priority(&tattr, DIAG_PRI - 1);
  qurt_thread_attr_set_name(&tattr, "DIAG_LSM");
  ret_value = qurt_thread_create(&thread_id, &tattr, Diag_LSM_RxThread, NULL);

  if (ret_value == QURT_EFAILED)
  {
    ret = FALSE;
  }

  return (ret);
} /* CreateWaitThread() */

/*===========================================================================
DESCRIPTION
   Closes synchronization events for incoming packets and mask change.
   Signals the thread (Diag_LSM_RxThread) that waits on these synchronization
   events, to return.
===========================================================================*/
boolean TerminateWaitThread(void)
{
  int status;
  boolean bReturn = TRUE;
  qurt_qdi_handle_invoke(diag_qdi_handle, DIAG_QDI_KILL_RX_THREAD);

  qurt_thread_join(thread_id, &status);
  return (bReturn);
} /* TerminateWaitThread() */

/*===========================================================================
DESCRIPTION
   Used to register/deregister this client process with Diag driver,
   for mask-change synchronization event.
   (Diag Driver adds the event handle corresponding to the unique synch. event
   name to its table, and sets the event when there is a mask change. For
   De-registration, the entry is removed from the list.)
===========================================================================*/
boolean RegisterForMaskChange(uint32 ActionCode)
{
  boolean status = TRUE;
  if (diag_qdi_handle >= DIAG_FD_MIN_VALUE)
  {
    int IOCtrlCode = DIAG_IOCTL_ERROR;
    bindpkt_params_per_process *pbind_req_send =
       malloc(sizeof(bindpkt_params_per_process));
    if (pbind_req_send)
    {
      pbind_req_send->count = 1;
      pbind_req_send->cmd_code = 0;
      pbind_req_send->subsys_id = 0;
      pbind_req_send->cmd_code_lo = 0;
      pbind_req_send->cmd_code_hi = 0;
      pbind_req_send->proc_id = 0;
      pbind_req_send->event_id = 0;
      pbind_req_send->log_code = 0;
      pbind_req_send->client_id = diag_pid;
      switch (ActionCode)
      {
         case MASK_CHANGE_REGISTER:
           IOCtrlCode = DIAG_IOCTL_MASK_REG;
           break;
         case MASK_CHANGE_DEREGISTER:
           IOCtrlCode = DIAG_IOCTL_MASK_DEREG;
           break;
         default:
           break;
      }

      if (!diag_lsm_ioctl(IOCtrlCode, (byte *)pbind_req_send, sizeof(bindpkt_params_per_process), NULL, 0, NULL))
      {
        status = FALSE;
      }

      free(pbind_req_send);
    }
    else
    {
      status = FALSE;
    }
  }
  else
  {
    status = FALSE;
  }

  return (status);
}

/*===========================================================================
FUNCTION PSEUDO_RANDOM

DESCRIPTION
  This function returns a random number from pseudo array[]

PARAMETERS
  i    Any integer value

============================================================================*/
/* for repeatabilty use pseudo random numbers */
int pseudo_random(int i)
{
  i = i % (sizeof(pseudo_array) / sizeof(byte));
  if (i < 14)
    return (pseudo_array[i]);
  else
    return (0);
}

/*===========================================================================

FUNCTION DIAG_LSM_STRESSTEST

DESCRIPTION
  This procedure is a startup function. Floods the link with the requested
  test type packets.

PARAMETERS
  params   This is of type diag_stress_test_tcb_stack_type and has information
           about stress test (test type, number of iterations etc)

============================================================================*/
void Diag_LSM_stresstest(
   uint32 params
   )
{
  osal_sigs_t return_sigs;
  int return_val = 0;
  osal_timer_t sleep_timer;

  if (params == NULL)
  {
    return;
  }

  diag_stress_test_tcb_stack_type *local_data = (diag_stress_test_tcb_stack_type *)params;

  /* Pointers to stress test logs */
  LOG_STRESS_TEST_C_type *log_ptr;
  LOG_STRESS_TEST_64_type *log_ptr_64;
  LOG_STRESS_TEST_128_type *log_ptr_128;
  LOG_STRESS_TEST_256_type *log_ptr_256;
  LOG_STRESS_TEST_1K_type *log_ptr_1K;
  LOG_STRESS_TEST_2K_type *log_ptr_2K;
  LOG_STRESS_TEST_4K_type *log_ptr_4K;
  LOG_STRESS_TEST_6K_type *log_ptr_6K;

  uint16 log_index = 0;             /* Index used to fill char array */
  EVENT_PAYLOAD_INFO_type payload;  /* Store the payload info */
  uint32 payload_stress_test_complete = 0; /* payload for stress test complete event */
  boolean timer_init = FALSE;       /* timer initialized or not */
  int test_type = 0;   /* Stores the test type info requested */
  int num_iter_bef_sleep = 0; /* Keeps track of number of iterations before sleep */
  int i = 1;
  int N = local_data->task_info.num_iterations; /* Total number of iterations */
  int unique_id = local_data->unique_id; /* Get the task ID */

#if defined(DIAG_MMPM_SUPPORT )
  int client_id = 0;
#endif

/* Vote against sleep for stress test */
#if defined( DIAG_DYNAMIC_SLEEP )
  if (diagtest_npa_handle)
  {
    npa_issue_required_request(diagtest_npa_handle, 1);
  }

#elif defined (DIAG_MMPM_SUPPORT)
  client_id = diag_mmpm_register();
  /* Vote against power collapse on LPass when the test starts */
  diag_mmpm_config(client_id);
#endif

  /*Start the handshake so that the task is ready to start */
  return_val=osal_handshake_start(&(local_data->tcb));
  ASSERT(OSAL_SUCCESS == return_val);

  for (i = 1; i <= N; i++)
  {

    /* Special Case, test type is generated using random */
    if (local_data->task_info.priority.test_type == DIAGDIAG_STRESS_TEST_MSG_PSEUDO_RANDOM)
    {
      /* Pick the random test type from the array */
      test_type = pseudo_random(i);
    }
    else
    {
      test_type = local_data->task_info.priority.test_type;
    }

    /**********************************************************************************
     *
     * In all the following cases, the priority field is replaced by unique id field
     * to help the automation scripts differentiate between test tasks while parsing
     * the test logs.
     *
     **********************************************************************************/
    switch (test_type)
    {
       case DIAGDIAG_STRESS_TEST_MSG:
         MSG(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "Test MSG with no arg ");
         break;
       case DIAGDIAG_STRESS_TEST_MSG_1:
         MSG_1(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "MSG_1 Iter %d\n", i);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_2:
         MSG_2(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "MSG_2 Iter %d uid %d \n",i,unique_id);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_3:
         MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "MSG_3 Iter %d uid %d num_iter %d\n", i,
               unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_4:
         MSG_4(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "MSG_4 Iter %d uid %d num_iter %d procid %d\n", i,
               unique_id, N, DIAG_MY_PROC_ID);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_5:
         MSG_5(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "MSG_5 Iter %d uid %d num_iter %d procid %d %d\n", i,
               unique_id, N, DIAG_MY_PROC_ID, 5);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_6:
         MSG_6(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "MSG_6 Iter %d uid %d num_iter %d procid %d  %d  %d\n",
               i, unique_id, N, DIAG_MY_PROC_ID, 0, 0);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_STR:
         //TODO
         break;
       case DIAGDIAG_STRESS_TEST_MSG_SPRINTF_1:
         MSG_SPRINTF_1(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"MSG_SPRINTF_1 Iter %d\n", i);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_SPRINTF_2:
         MSG_SPRINTF_2(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"MSG_SPRINTF_2 Iter %d uid %d\n", i, unique_id);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_SPRINTF_3:
         MSG_SPRINTF_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"MSG_SPRINTF_3 Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_SPRINTF_4:
         MSG_SPRINTF_4(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"MSG_SPRINTF_4 Iter %d uid %d num_iter %d %s \n", i, unique_id, N, "4");
         break;
       case DIAGDIAG_STRESS_TEST_MSG_SPRINTF_5:
         MSG_SPRINTF_5(MSG_SSID_DIAG, MSG_LEGACY_HIGH,"MSG_SPRINTF_5 Iter %d uid %d num_iter %d %s %s \n",i, unique_id,N,"4", "5");
         break;
       case DIAGDIAG_STRESS_TEST_MSG_LOW:
         MSG_LOW("MSG_LOW Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_MED:
         MSG_MED("MSG_MED Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_HIGH:
         MSG_HIGH("Client MSG_HIGH Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_ERROR:
         MSG_ERROR("MSG_ERROR Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_MSG_FATAL:
         MSG_FATAL("MSG_FATAL Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_ERR:
         ERR("ERR Iter %d uid %d num_iter %d \n", i, unique_id, N);
         break;
       case DIAGDIAG_STRESS_TEST_ERR_FATAL:
         {
           int j;

          /* The ERR_FATAL test needs to make sure panic mode works.
             Generate a few messages and see if they make it out. */
          for (j = 0; j < 10; j++)
          {
            MSG_FATAL ("Panic mode test %d uid %d", j, unique_id, 0);
          }
        }
        ERR_FATAL("ERR_FATAL Iter %d uid %d num_iter %d \n",i,unique_id,N);
        break;
      case DIAGDIAG_STRESS_TEST_LOG:
        log_ptr = (LOG_STRESS_TEST_C_type *) log_alloc (LOG_DIAG_STRESS_TEST_C,
            sizeof(LOG_STRESS_TEST_C_type));
        if (log_ptr != NULL) {
          log_ptr->iteration = i;
          log_ptr->task_priority = unique_id;
          log_ptr->req_iterations = N;
          log_commit(log_ptr);
        }
        break;
      case DIAGDIAG_STRESS_TEST_EVENT_NO_PAYLOAD:
        event_report(EVENT_DIAG_STRESS_TEST_NO_PAYLOAD);
        break;
      case DIAGDIAG_STRESS_TEST_EVENT_WITH_PAYLOAD:
        payload.iteration = i;
        payload.task_priority = unique_id;
        payload.req_iterations = N;
        event_report_payload(EVENT_DIAG_STRESS_TEST_WITH_PAYLOAD,
          sizeof(EVENT_PAYLOAD_INFO_type),(void *) &payload);
        break;
      case DIAGDIAG_STRESS_TEST_LOG_64:
        log_ptr_64 = (LOG_STRESS_TEST_64_type *) log_alloc (LOG_DIAG_STRESS_TEST_C,
                                                            sizeof(LOG_STRESS_TEST_64_type));
        if (log_ptr_64 != NULL) {
          log_ptr_64->iteration = i;
          log_ptr_64->task_priority =unique_id;
          log_ptr_64->req_iterations = N;
          for ( log_index = 0; log_index < 13; log_index++ ) {
              log_ptr_64->payload[log_index] = 0x7EABBA7E;
          }
          log_commit(log_ptr_64);
        }
        break;
      case DIAGDIAG_STRESS_TEST_LOG_128:
        log_ptr_128 = (LOG_STRESS_TEST_128_type *) log_alloc (LOG_DIAG_STRESS_TEST_C,
                                                             sizeof(LOG_STRESS_TEST_128_type));
         if (log_ptr_128 != NULL)
         {
           log_ptr_128->iteration = i;
           log_ptr_128->task_priority = unique_id;
           log_ptr_128->req_iterations = N;
           for (log_index = 0; log_index < 29; log_index++)
           {
             log_ptr_128->payload[log_index] = 0x7EABBA7E;
           }
           log_commit(log_ptr_128);
         }
         break;
       case DIAGDIAG_STRESS_TEST_LOG_256:
         log_ptr_256 = (LOG_STRESS_TEST_256_type *)log_alloc(LOG_DIAG_STRESS_TEST_C,
                                                             sizeof(LOG_STRESS_TEST_256_type));
         if (log_ptr_256 != NULL)
         {
           log_ptr_256->iteration = i;
           log_ptr_256->task_priority = unique_id;
           log_ptr_256->req_iterations = N;
           for (log_index = 0; log_index < 61; log_index++)
           {
             log_ptr_256->payload[log_index] = 0x7EABBA7E;
           }
           log_commit(log_ptr_256);
         }
         break;
       case DIAGDIAG_STRESS_TEST_LOG_1K:
         log_ptr_1K = (LOG_STRESS_TEST_1K_type *)log_alloc(LOG_DIAG_STRESS_TEST_C,
                                                           sizeof(LOG_STRESS_TEST_1K_type));
         if (log_ptr_1K != NULL)
         {
           log_ptr_1K->iteration = i;
           log_ptr_1K->task_priority = unique_id;
           log_ptr_1K->req_iterations = N;
           for (log_index = 0; log_index < 253; log_index++)
           {
             log_ptr_1K->payload[log_index] = 0x7EABBA7E;
           }
           log_commit(log_ptr_1K);
         }
         break;
       case DIAGDIAG_STRESS_TEST_LOG_2K:
         log_ptr_2K = (LOG_STRESS_TEST_2K_type *)log_alloc(LOG_DIAG_STRESS_TEST_C,
                                                           sizeof(LOG_STRESS_TEST_2K_type));
         if (log_ptr_2K != NULL)
         {
           log_ptr_2K->iteration = i;
           log_ptr_2K->task_priority = unique_id;
           log_ptr_2K->req_iterations = N;
           for (log_index = 0; log_index < 509; log_index++)
           {
             log_ptr_2K->payload[log_index] = 0x7EABBA7E;
           }
           log_commit(log_ptr_2K);
         }
         break;
       case DIAGDIAG_STRESS_TEST_LOG_4K:
         log_ptr_4K = (LOG_STRESS_TEST_4K_type *)log_alloc(LOG_DIAG_STRESS_TEST_C,
                                                           sizeof(LOG_STRESS_TEST_4K_type));
         if (log_ptr_4K != NULL)
         {
           log_ptr_4K->iteration = i;
           log_ptr_4K->task_priority = unique_id;
           log_ptr_4K->req_iterations = N;
           for (log_index = 0; log_index < 1021; log_index++)
           {
             log_ptr_4K->payload[log_index] = 0x7EABBA7E;
           }
           log_commit(log_ptr_4K);
         }
         break;
       case DIAGDIAG_STRESS_TEST_LOG_6K:
         log_ptr_6K = (LOG_STRESS_TEST_6K_type *)log_alloc(LOG_DIAG_STRESS_TEST_C,
                                                           sizeof(LOG_STRESS_TEST_6K_type));
         if (log_ptr_6K != NULL)
         {
           log_ptr_6K->iteration = i;
           log_ptr_6K->task_priority = unique_id;
           log_ptr_6K->req_iterations = N;
           for (log_index = 0; log_index < 1533; log_index++)
           {
             log_ptr_6K->payload[log_index] = 0x7EABBA7E;
           }
           log_commit(log_ptr_6K);
         }
         break;
    case DIAGDIAG_STRESS_TEST_LOG_SUBMIT_64:
    {
      uint8 *log_pkt;
        log_pkt = (uint8 *)malloc(sizeof(LOG_STRESS_TEST_64_type));
          if (log_pkt != NULL)
          {
            log_ptr_64 = (LOG_STRESS_TEST_64_type *)(log_pkt);
            log_set_length(log_pkt, sizeof(LOG_STRESS_TEST_64_type));
            log_set_code(log_pkt, LOG_DIAG_STRESS_TEST_C);
            log_set_timestamp(log_pkt);

            log_ptr_64->iteration = i;
            log_ptr_64->task_priority = unique_id;
            log_ptr_64->req_iterations = N;
            for (log_index = 0; log_index < 13; log_index++)
            {
              log_ptr_64->payload[log_index] = 0x7EABBA7E;
            }

            log_submit(log_pkt);
            free(log_pkt);
          }
      else{
         MSG_1(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "Malloc failed in log_submit() test case.Iter %d\n",i);
      }
     }
        break;
       default:
         break;

    }
    num_iter_bef_sleep++;

    if ((local_data->task_info.num_iterations_before_sleep > 0)
        && (num_iter_bef_sleep == local_data->task_info.num_iterations_before_sleep))
    {

      if (timer_init == FALSE)
      {
        /* Defines a timer */
        osal_create_diag_timer(&sleep_timer, osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG);
        timer_init = TRUE;
      }

      /* Wait for sleep_duration. This blocks the current task, and
         different task with which is ready to run starts executing */
      (void)osal_timed_wait(osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG, &sleep_timer,
                            local_data->task_info.sleep_duration);

      /* Clear the signals. The block on the current task is cleared */
      return_val = osal_reset_sigs(osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG, &return_sigs);
      ASSERT(OSAL_SUCCESS == return_val);

      num_iter_bef_sleep = 0;
    }
  } /* end of for loop */

  /* Sleep before sending out EVENT_DIAG_STRESS_TEST_COMPLETED,
   to make sure the event can be allocated and is received by APS.
   In some test-cases, APS misses the event because it is sent out too
   early. */
  if (timer_init == FALSE)
  {
    /* Defines a timer */
    osal_create_diag_timer(&sleep_timer, osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG);
    timer_init = TRUE;
  }
  (void)osal_timed_wait(osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG, &sleep_timer, STRESS_TASK_SLEEP_TO_COMPLETE);

  /* Clear the signals. The block on the current task is cleared */
  return_val = osal_reset_sigs(osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG, &return_sigs);
  ASSERT(OSAL_SUCCESS == return_val);
  if (osal_thread_get_pri() <= DIAG_PRI)
  {
    /* This is done to make sure that the task gets killed before the
     cleanup function, running in diag context, removes the data from the Q */
    (void)osal_thread_set_pri(DIAG_PRI + 1);
  }
  /* Notify that a stress test task has completed for automation */
  event_report_payload(EVENT_DIAG_STRESS_TEST_COMPLETED, sizeof(int32), &payload_stress_test_complete);
  /* mark the task to be cleaned */
  local_data->status = DIAG_TASK_DONE;
/* Vote for sleep for diag stress test */
#if defined( DIAG_DYNAMIC_SLEEP )
  if (diagtest_npa_handle)
  {
    npa_cancel_request(diagtest_npa_handle);
  }

#elif defined(DIAG_MMPM_SUPPORT )
  /*Sleep for few seconds before voting for power collpase so that diag can drain the
  event stress test completed on lpass*/

  (void)osal_timed_wait(osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG, &sleep_timer, 10000);

  /* Clear the signals. The block on the current task is cleared */
  return_val = osal_reset_sigs(osal_thread_self(), DIAG_STRESS_TEST_SLEEP_SIG, &return_sigs);
  ASSERT(OSAL_SUCCESS == return_val);

  /* Vote for power collapse on LPass when the test completes */
  diag_mmpm_release(client_id);
  diag_mmpm_deregister(client_id);
#endif


  /* Delete the sleep timer */
  if (timer_init == TRUE)
  {
    return_val = osal_delete_timer(&sleep_timer);
    ASSERT(OSAL_SUCCESS == return_val);
  }
  /* mark the task to be cleaned */
  local_data->status = DIAG_TASK_DONE;

  /* Clean the stress test queue */
  diag_lsm_clear_stress_test_q();


  /* mapped to no-ops for all OSes except QURT */

  osal_thread_exit(0);
} /* stress_test_start_up */


boolean diag_time_init_LSM()
{
  if(!osal_atomic_compare_and_set((osal_atomic_word_t*)&diag_time_init_begin_lsm, FALSE, TRUE))
    return FALSE;

  diag_time_get_LSM = &time_get;
  diag_time_initialized_lsm = TRUE;

  return TRUE;
}


boolean diag_set_time_api_LSM()
{
  boolean status = TRUE;
  uint8 time_api;
  if(diag_qdi_handle>=DIAG_FD_MIN_VALUE)
  {
    dword Len_Recvd = 0;
    if(!(diag_lsm_ioctl(DIAG_IOCTL_GET_TIME_API, NULL,0, &time_api,sizeof(time_api), &Len_Recvd)) || Len_Recvd != sizeof(time_api) )
    {
      switch(time_api)
      {
        case DIAG_TIME_GET:
        {
          diag_time_get_LSM = time_get;
          status = TRUE;
        }
        break;
        case DIAG_TIME_GET_UPTIME:
        {
           diag_time_get_LSM = time_get_uptime;
           status = TRUE;
        }
        break;
        case DIAG_TIME_GET_TBD:
        {
          /* Remove this error fatal after TIME SYNC Phase 2 implementation*/
          ERR_FATAL("Invalid Time API to be set : %d", diag_time_api_to_use_lsm,0,0);
        }
        break;
        default:
        {
          status = FALSE;
        }
        break;
      }
    }
  }
  else
  {
    status = FALSE;
  }
  return status;
}
/*===========================================================================

FUNCTION diag_get_diagID_LSM

DESCRIPTION
  This procedure retieves the diag ID of the current process. It queries the root and
  gets the diagID assigned to the current process.

PARAMETERS
  None

RETURN VALUE
  TRUE if diagID is assigned to the current process.
  FALSE if unable to retrive diagID.

============================================================================*/
boolean diag_get_diagID_LSM()
{
  boolean status = FALSE;
  uint8 diagID = DIAGID_UNKNOWN_ID;
  char* process_name = NULL;

  process_name= servreg_get_local_domain();

  if(diag_qdi_handle>=DIAG_FD_MIN_VALUE)
  {
    dword Len_Recvd =0;
    if( !(diag_lsm_ioctl(DIAG_IOCTL_GET_DIAG_ID, (byte *)process_name, strlen(process_name)+1, &diagID, sizeof(diagID), &Len_Recvd)) || (Len_Recvd != sizeof(diagID)) )
    {
      return status;
    }
    if(diagmpd_buf)
    {
      diagmpd_buf->diagID = diagID;
      status = TRUE;
    }
  }
  return status;
}

