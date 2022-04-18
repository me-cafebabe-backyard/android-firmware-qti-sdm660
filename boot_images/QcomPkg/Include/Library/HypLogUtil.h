

#ifndef __HYP_LOG_UTIL__
#define __HYP_LOG_UTIL__

/** @file
                              HypLogUtil.h

	Print latest message from the current Hypervisor circular buffer

    Copyright (c) 2015-2016 Qualcomm Technologies, Inc. All rights reserved.

**/

#include "com_dtypes.h"


#define HYP_INIT_LOG	coretest_hyp_log_init()
#define HYP_PRINT_LOG	printHypLog()

#define TZ_INIT_LOG 	coretest_tz_log_init()
#define TZ_PRINT_LOG	printTzBspLog()
// ==================================================================================

/**
  Descr: Print all message from the current Hypervisor circular buffer
*/
void printHypLog(void);

/**
  print all message from the current Hypervisor circular buffer.
*/
void printTzBspLog(void);


// TODO: Add support to prints out all of TZ related info like core PowerCollapse or others things....

//void printTzBootStats(void);

//void printTzResetStats (void);

void coretest_tz_log_init(void);
void coretest_hyp_log_init(void);

#endif // __HYP_LOG_UTIL__







