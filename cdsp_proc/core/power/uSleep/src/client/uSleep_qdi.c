/*============================================================================== 
  FILE:         uSleep_qdi.c

  OVERVIEW:     Implements QDI layer for uSleep API's in island mode

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/client/uSleep_qdi.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdlib.h>
#include "comdef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "uSleep_qdi.h"
#include "client_os.h"
#include "qurt.h"

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Client QDI opener object */
uSleep_qdi_opener g_uSleepClientObj;

/* Data structure required for QDI init */
const uSleep_qdi_opener g_uSleepOpenerData = 
{
  {uSleep_QDIInvoke, QDI_REFCNT_PERM, 0} 
};

/*==============================================================================
                           INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * uSleep_QDISetLowPowerMode
 * 
 * @brief QDI interface function to set low power mode
 *  
 * @return Status from function call (see function for values) 
 */
static inline uint32 uSleep_QDISetLowPowerMode(int                client_handle, 
                                               uSleep_power_mode  mode) 
{
  return(uSleep_setLowPowerMode(mode));
}

/**
 * uSleep_QDIExit
 * 
 * @brief QDI interface function to exit uImage mode and return to normal 
 *        operational mode 
 *  
 * @return Status from function call (see function for values) 
 */
static inline uint32 uSleep_QDIExit(int client_handle)
{
  return(uSleep_exit());
}

/**
 * uSleep_QDIGetCriticalExitTime
 * 
 * @brief QDI interface function to get the current DDR timer exit value
 *  
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
static inline uint32 uSleep_QDIGetCriticalExitTime(int    client_handle,
                                                   uint64 *exitTime)
{
  uint64 tempTime;
  int    status;
  uint32 rtnValue = USLEEP_SUCCESS;

  tempTime = uSleep_getCriticalExitTime();

  status = qurt_qdi_copy_to_user(client_handle, exitTime, &tempTime,
                                 sizeof(uint64));

  if(status < 0)
  {
    rtnValue = USLEEP_FAILURE;
  }

  return rtnValue;
}

/**
 * uSleep_QDIIsExitRequested
 * 
 * @brief QDI interface function to get the exit request status
 *  
 * @return function value
 */
static inline uint32 uSleep_QDIIsExitRequested(int client_handle)
{
  return(uSleep_isExitRequested());
}

/*==============================================================================
                           EXTERNAL FUNCTIONS
 =============================================================================*/
/*
 * uSleep_QDIInvoke
 */
int uSleep_QDIInvoke(int             client_handle,
                     qurt_qdi_obj_t  *pobj,
                     int             method,
                     qurt_qdi_arg_t  a1,
                     qurt_qdi_arg_t  a2,
                     qurt_qdi_arg_t  a3,
                     qurt_qdi_arg_t  a4,
                     qurt_qdi_arg_t  a5,
                     qurt_qdi_arg_t  a6,
                     qurt_qdi_arg_t  a7,
                     qurt_qdi_arg_t  a8,
                     qurt_qdi_arg_t  a9)
{
   uSleep_qdi_opener *clntobj = (uSleep_qdi_opener *)pobj;
   
   switch(method)
   {
     case QDI_ISLAND_CHECK_ALLOC:
       return TRUE;
        
     case QDI_OPEN:
       return uSleep_QDIOpen(client_handle, clntobj);

     case USLEEP_QDI_EXIT: 
       return uSleep_QDIExit(client_handle);

     case USLEEP_QDI_SET_LOW_POWER_MODE:
       return uSleep_QDISetLowPowerMode(client_handle, 
                                        (uSleep_power_mode)a1.num);

     case USLEEP_QDI_INSERT_CALLBACK:
       return uSleep_QDIInsertCallback(client_handle, 
                                       (uSleep_signals *)a1.ptr);

     case USLEEP_QDI_ADD_CALLBACK_LATENCY:
       return uSleep_QDIAddCallbackLatency(client_handle,
                                           (uint32)a1.num,
                                           (uint32)a2.num);

     case USLEEP_QDI_GET_CRITICAL_EXIT_TIME:
       return uSleep_QDIGetCriticalExitTime(client_handle, (uint64 *)a1.ptr);

     case USLEEP_QDI_IS_EXIT_REQUESTED:
       return uSleep_QDIIsExitRequested(client_handle);

     default:
       return -1;
   }
}

