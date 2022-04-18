/*============================================================================== 
  FILE:         uSleep_qdi.c

  OVERVIEW:     QDI layer for uSleep API's in DDR mode

  DEPENDENCIES: None
  
                Copyright (c) 2014,2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/client/ddr/uSleep_qdi.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "DALStdDef.h"
#include "uSleep_qdi.h"
#include "client_os.h"
#include "qurt.h"

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
extern uSleep_qdi_opener        g_uSleepClientObj;
extern const uSleep_qdi_opener  g_uSleepOpenerData;

/*==============================================================================
                           EXTERNAL FUNCTIONS
 =============================================================================*/
/*
 * uSleep_QDIRelease
 */ 
void uSleep_QDIRelease(qurt_qdi_obj_t *obj)
{
  return;
}

/*
 * uSleep_QDIOpen
 */
int uSleep_QDIOpen(int client_handle, uSleep_qdi_opener *me)
{
   g_uSleepClientObj.qdiobj.invoke   = uSleep_QDIInvoke;
   g_uSleepClientObj.qdiobj.refcnt   = QDI_REFCNT_INIT;
   g_uSleepClientObj.qdiobj.release  = uSleep_QDIRelease;
   
   return qurt_qdi_handle_create_from_obj_t(client_handle, 
                                            &g_uSleepClientObj.qdiobj);
}

/*
 * uSleep_QDIInit
 */
void uSleep_QDIInit(void)
{
  qurt_qdi_register_devname(USLEEP_QDI_DRIVER_NAME, &g_uSleepOpenerData.qdiobj);
  return;
}

/*
 * uSleep_QDIInsertCallback
 */
uint32 uSleep_QDIInsertCallback(int            client_handle, 
                                uSleep_signals *signal)
{
  return (uSleep_registerUserNotificationCallback(signal));
}

/*
 * uSleep_QDIAddCallbackLatency
 */
uint32 uSleep_QDIAddCallbackLatency(int     client_handle,
                                    uint32  enterLat,
                                    uint32  exitLat)
{
  return (uSleep_addUserCallbackLatency(enterLat, exitLat));
}

