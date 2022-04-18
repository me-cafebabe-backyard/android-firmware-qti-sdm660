/*==================================================================
 *
 * FILE:        ddi_utils.h
 *
 * DESCRIPTION:
 *
 *
 *        Copyright © 2016 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 2016-12-15   zhz     Add utils
 * 2015-01-08   bh      Include LoaderUtils.h
 * 2014-12-02   wek     8996/XBL Compilation.
 * 2014-10-02   ah      Major code clean up
 * 2013-06-03   ah      Added legal header
 * 2013-05-31   ab      Initial checkin
 */

#ifndef DDI_UTILS_H
#define DDI_UTILS_H

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "LoaderUtils.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "comdef.h"
#include "boot_target.h" /* For definition of TIMETICK_CLK */

typedef int sSIZE_T;
typedef unsigned long long int SIZE_T;
#define SIZE_T_FORMAT "%llu"
#define SIZE_T_CONVERTER strtoull
#define SIZE_T_MAX ULLONG_MAX

/*===========================================================================
  The clock that is used to track time passing.
===========================================================================*/
#ifndef TIMETICK_CLK
#define TIMETICK_CLK  MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
#endif

/*===========================================================================
  Clock frequency is 32.768 KHz
  The number of microseconds per cycle is:
  1 / (32.768 KHz) = 30.52ms
  The int part is 30
===========================================================================*/
#define TIMETICK_CLK_SPEED_INT       30

/*===========================================================================
  Clock frequency is 32.768 KHz
  The number of microseconds per cycle is:
  1 / (32.768 KHz) = 30.52ms
  we round 0.52 to 1/2.
  Timestamp is calculated as : count*int + count/2
  Floating point arithmetic should not be used to avoid error and speed penalty
===========================================================================*/
#define CALCULATE_TIMESTAMP(COUNT) \
  ((COUNT)*TIMETICK_CLK_SPEED_INT + (COUNT)/2)

/*
  we are using 32 bits timestamp, the max counter value is:
  0xFFFFFFFF/31 = 138547732
  after this value the timestamp will overflow
*/
#define LOG_MAX_COUNT_VAL  138547732

/**
* return value when timestamp overflow happens
*/
#define LOG_TIMESTAMP_OVERFLOW  0xFFFFFFFF

#define MICROSECONDS_PER_SECOND 1000000

SIZE_T  get_time(void);
SIZE_T  get_rollover_time(void);
void delaySeconds(SIZE_T  seconds);

boolean simpleStrReplace(char* haystack, const char* needle, const char* thorn);
boolean stringReverse(char* astring);
boolean integerToString(int number, char* buffer, SIZE_T length);
SIZE_T stringToNumber(const char* buffer, boolean *retval);
boolean MyParseExpression(char* buffer, SIZE_T BufferLength, SIZE_T* result);
//boolean parseExpression(char* buffer, SIZE_T* result);
uint32 calc_crc32(const byte *data_in, const uint32  nbytes_in);
word calc_crc16_wrapper(byte *data_buf, SIZE_T bytes, word crc_value);
int pow(int base, int exp);
uint32 convertStrtoUint(char* str);
int convertStrtoInt(char* str);
char *ddi_strtok(char *restrict s, const char *restrict sep);
SIZE_T getlength(char* str);
SIZE_T CopyString(char *Dest, char *Source, SIZE_T  Dstart, SIZE_T  Sstart, SIZE_T  length, SIZE_T DestSize, SIZE_T SourceSize);
char *__stpcpy(char *restrict d, const char *restrict s);
int common_decimal_char_to_int(const char* inCharArr, boolean* convertRes);

#endif /* DDI_UTILS_H */

