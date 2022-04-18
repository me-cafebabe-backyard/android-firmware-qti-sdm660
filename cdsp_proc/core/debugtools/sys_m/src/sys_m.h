#ifndef SYS_M_H
#define SYS_M_H
/*===========================================================================

           S Y S _ M . H

DESCRIPTION

Copyright (c) 2011-16 by Qualcomm Technologies Incorporated. All Rights Reserved.

===========================================================================
DESCRIPTION
High level system monitor
===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/sys_m/src/sys_m.h#1 $

===========================================================================*/
#include "qmi_csi.h"
#include "rcevt.h"
#include "tms_utils_msg.h"

#define SYS_M_SMEM_SSR_REASON_LPASS0  SMEM_SSR_REASON_LPASS0
#define SYS_M_SMEM_SSR_REASON_DSPS0  SMEM_SSR_REASON_DSPS0
#define SMEM_SSR_REASON_MSS0  SMEM_SSR_REASON_MSS0
/**
* Below SMEM item number is approved by go/SMEM_ID_REQ.
*
* For CDSP SFR, 601 is smem item number. 
* Refer https://jira.qualcomm.com/jira/browse/SMEMIDREQ-2
*/
#define SYS_M_SMEM_SSR_REASON_CDSP0  601

#define SYS_M_MSG_HIGH(fmt)  \
   TMS_MSG_HIGH("SYS_M_PREFIX:" fmt)
#define SYS_M_MSG_HIGH_1(fmt, a)  \
   TMS_MSG_HIGH_1("SYS_M_PREFIX:" fmt, a)
#define SYS_M_MSG_HIGH_2(fmt, a, b)  \
   TMS_MSG_HIGH_2("SYS_M_PREFIX:" fmt, a, b)
#define SYS_M_MSG_HIGH_3(fmt, a, b, c)  \
   TMS_MSG_HIGH_3("SYS_M_PREFIX:" fmt, a, b, c)
#define SYS_M_MSG_STR_1(fmt, a)  \
   TMS_MSG_SPRINTF_HIGH_1("SYS_M_PREFIX:" fmt, a)
#define SYS_M_MSG_ERR(fmt)  \
   TMS_MSG_ERROR("SYS_M_PREFIX:" fmt)
#define SYS_M_MSG_ERR_1(fmt, a)  \
   TMS_MSG_ERROR_1("SYS_M_PREFIX:" fmt, a)


typedef enum SYS_M_COMMUNICATION_T
{
    SYS_M_SMSM_P2P       = 0,
    SYS_M_QMI            = 1
} SYS_M_COMMUNICATION_TYPE;




//begin shutdown
void sys_m_shutdown(SYS_M_COMMUNICATION_TYPE);

//shutdown function
void sys_m_shutdown_internal(void);

/**
  call the registered callback to release all SMEM spinlock
  after entering into STM while gracefull shutdown.

  @return
   TRUE : Success
   FALSE: Failure

  @dependencies
  None.
*/
void sys_m_shutdown_terminate_in_STM(void);

/**
 *
 * @brief sys_m_signal_modules
 *
 * Signal interested modules of a system monitor event.  After all clients have completed
 * notification, acknowledge to apps
 *
*/
void sys_m_signal_modules(RCEVT_HANDLE handle);


//internal QMI init function
qmi_csi_service_handle ssctl_v02_qmi_ser_init(qmi_csi_os_params *os_params);

#define SYS_M_QMI_v02_SIG     0x00100000

#define SYS_M_SMP2P_PORT_OUT        "slave-kernel"
#define SYS_M_SMP2P_PORT_IN         "master-kernel"
#define SYS_M_XPU_ERR_STRING        "sys_m:xpu_error"
#define SYS_M_SMP2P_TZ_PORT_IN      "tz2mpss_smp2p"


#endif  /* SYS_M_H */
