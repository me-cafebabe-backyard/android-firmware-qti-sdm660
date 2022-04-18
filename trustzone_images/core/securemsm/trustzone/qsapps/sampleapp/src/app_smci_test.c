/*===========================================================================
  Copyright (c) 2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
  ===========================================================================*/

/*===========================================================================

  EDIT HISTORY FOR FILE
  $Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/sampleapp/src/app_smci_test.c#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

  # when       who     what, where, why
  # --------   ---     ---------------------------------------------------------

  ===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "CHavenTokenApp.h"
#include "ITestSMCInvoke.h"
#include "qsee_env.h"
#include "qsee_log.h"
#include "qsee_time.h"

#define INVALID_TIME  "-1"
#define CMD_NAME  "__name__"
#define CMD_TIME  "__hlostime__"

extern const char *TA_APP_NAME;

int run_smci_time_test()
{
   Object o = Object_NULL;
   int32_t err = 0;
   char bufOut[32] = {0};
   size_t lenOut = 0;

   static char bufIn[] = CMD_TIME;

   // This test expects smplserv to be loaded. smplserv exposes the ITestSMCInvoke
   // service in disguise as the HavenTokenApp service, so that it's available to
   // HLOS via clientEnv.
   err = qsee_open(CHavenTokenApp_UID, &o);
   if (!Object_isOK(err)) {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s() qsee_open() failed, err = %d", __FUNCTION__, err);
      goto bail;
   }

   err = ITestSMCInvoke_test(o, bufIn, sizeof(bufIn), bufOut, sizeof(bufOut), &lenOut);
   if (!Object_isOK(err)) {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s() FAILED, expected Object_OK,  err=%d", __FUNCTION__, err);
      goto bail;
   }
   // make sure the returned buffer is 0-terminated, since we're going to print it
   bufOut[sizeof(bufOut)-1]=0;

   // check the content of the returned buffer
   if (strncmp(bufOut,INVALID_TIME,sizeof(INVALID_TIME)) != 0) {
      qsee_log(QSEE_LOG_MSG_DEBUG, "%s() SUCCESS, returned=%s", __FUNCTION__, bufOut);
   } else {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s() FAILED, returned=%s", __FUNCTION__, bufOut);
      err = -1;
   }

bail:

   Object_RELEASE_IF(o);
   return err;
}

int run_smci_name_test()
{
   Object o = Object_NULL;
   int32_t err = 0;
   char bufOut[64] = {0};
   size_t lenOut = 0;

   static char bufIn[] = CMD_NAME;

   err = qsee_open(CHavenTokenApp_UID, &o);
   if (!Object_isOK(err)) {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s() qsee_open() failed, err = %d", __FUNCTION__, err);
      goto bail;
   }

   err = ITestSMCInvoke_test(o, bufIn, sizeof(bufIn), bufOut, sizeof(bufOut), &lenOut);
   if (!Object_isOK(err)) {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s() FAILED, expected Object_OK,  err=%d", __FUNCTION__, err);
      goto bail;
   }
   // make sure the returned buffer is 0-terminated, since we're going to print it
   bufOut[sizeof(bufOut)-1]=0;

   // check the content of the returned buffer
   if (strncmp(bufOut,TA_APP_NAME,sizeof(bufOut)) == 0) {
      qsee_log(QSEE_LOG_MSG_DEBUG, "%s() SUCCESS, returned=%s", __FUNCTION__, bufOut);
   } else {
      qsee_log(QSEE_LOG_MSG_ERROR, "%s() FAILED, returned=%s", __FUNCTION__, bufOut);
      err = -1;
   }

bail:

   Object_RELEASE_IF(o);
   return err;
}

int run_hlos_time()
{
   // go to HLOS to get time via a listener.
   // this command is only intended to cause a listener call and verify its success
   int err = 0;
   struct tztimespec timeSpec  = {0, 0};

   err = time_getutcsec(&timeSpec);
   qsee_log(QSEE_LOG_MSG_DEBUG, "%s(): time_getutcsec: %d", __FUNCTION__, err);

   return err;
}
