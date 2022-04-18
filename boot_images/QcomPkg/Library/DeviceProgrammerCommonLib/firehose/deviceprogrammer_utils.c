/***********************************************************************
 * FILE: deviceprogrammer_utils.c
 *
 * Utility functions used by DeviceProgrammer
 *
 * Copyright (c) 2008-2016 Qualcomm Technologies Incorporated.
 * All Rights Reserved. QUALCOMM Proprietary
 *
 ***********************************************************************/

/*=======================================================================

                      EDIT HISTORY FOR FILE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/deviceprogrammer_utils.c#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ----------------------------------------------
2016-03-04   wek   Add threshold for get_time (1 year)
2015-05-18   wek   Change header file inclusion.
2014-10-02   ah    Major code clean up
2013-06-03   ah    Added legal header
2013-05-31   ab    Initial checkin
=======================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <limits.h>
#include <errno.h>
#include "deviceprogrammer_utils.h"
#include "stringl/stringl.h"
#include <string.h>

#include "boot_msm.h"
#include "crc.h"

/*=========================================================================

                            FUNCTION DEFINITIONS

=========================================================================*/

/*===========================================================================

**  Function :  get_time_count

** ==========================================================================
*/
/*!
*
* @brief
*  Returns the time count since bootup. Internal use only.
*
* @retval
*   a 32 bits counter value as the current value in TIMETICK_CLK register.
*
* @par Side Effects
*   None
*
*/
static uint32 get_time_count()
{
  uint32 curr_count;
  uint32 last_count;
  uint32 diff;

  // Grab current time count
  curr_count = HWIO_IN(TIMETICK_CLK);

  // Keep grabbing the time until a stable count is given
  do
  {
    last_count = curr_count;
    curr_count = HWIO_IN(TIMETICK_CLK);
    diff = curr_count - last_count;
  } while (diff > 5); /* If the tick is less than 5 then assume the clock is
  stable. This is to handle the case where the CPU instruction clock is slow
  (like RUMI) and we get two different readings between to counter reads */

  return curr_count;
}

// returns the time in microseconds
SIZE_T  get_time()
{
  uint32 curr_time_count = get_time_count();
  
  /* check if the count overflows*/
  /*
  if(curr_time_count < LOG_MAX_COUNT_VAL)
  {
  */
    /*Convert current time count into microseconds*/
    curr_time_count = CALCULATE_TIMESTAMP(curr_time_count);
  /*
  }
  else
  {
    curr_time_count = LOG_TIMESTAMP_OVERFLOW;
  }
  */

  return curr_time_count;
}

SIZE_T  get_rollover_time()
{
    return ((SIZE_T )1000 * (SIZE_T )LOG_TIMESTAMP_OVERFLOW);
}

void delaySeconds(SIZE_T  seconds) {
    SIZE_T  delay_time = seconds * MICROSECONDS_PER_SECOND;
    SIZE_T  timer_end_time = get_time() + delay_time;
    while (get_time() < timer_end_time);
}

boolean simpleStrReplace(char* haystack, const char* needle, const char* thorn) {
    char* current_haystack = haystack;
    char* pos;
    SIZE_T len_haystack = 0;
    SIZE_T len_needle   = 0;
    SIZE_T len_thorn    = 0;

    if (haystack == NULL || needle == NULL || thorn == NULL) {
        return FALSE;
    }

    len_haystack = strlen((const char *)haystack);
    len_needle = strlen((const char *)needle);
    len_thorn = strlen((const char *)thorn);

    if (len_thorn > len_needle) {
        return FALSE;
    }

    while ((pos = strstr(current_haystack, needle)) != NULL) {
        current_haystack = pos;
        memscpy(pos, len_haystack, thorn, len_thorn);
        current_haystack += len_thorn;
        memsmove(current_haystack, len_haystack,
                current_haystack + (len_needle - len_thorn),
                haystack + len_haystack - current_haystack);
    }
    return TRUE;
}

SIZE_T stringToNumber(const char* buffer, boolean *retval)
{
    char c;
    SIZE_T number = 0, ScaleFactor=10;
    int is_negative = 0;
    int i=0, Length = strlen(buffer);

    if (NULL == retval)
        return number;

    *retval = FALSE;    // assume false

    if (*buffer == '\0' || Length>19) 
        return number;

    i = 0;
    c = buffer[i];
    if (c == '-')
    {
      is_negative = 1;
      i++;
    }

    for(; i<Length; i++)
    {
        c = buffer[i];

        if(c>='0' && c<='9')
            number = (number*ScaleFactor)+(c-0x30);	// ScaleFactor = 10
        else if(c>='a' && c<='f')
            number = (number*ScaleFactor)+(c-87);	// i.e. 'a' = 97, so 97-87 = 10
        else if(c>='A' && c<='F')
            number = (number*ScaleFactor)+(c-55);	// i.e. 'A' = 65, so 65-55 = 10
        else if(c==',')
          continue;	// user did this 12,345
        else if(c=='x' || c=='X')
        {
          ScaleFactor = 16;	// this is a hex value
          continue;	// user did this 12,345
        }
        else if(c=='.')
          break;		// user did this 12.3, so return 12
        else
          return 0;	// user provided something unexpected, return 0
    }

    *retval = TRUE; // made it this far, all is well
    /* Check if the number started with '-', if it did, make it negative */
    if (is_negative != 0)
    {
      number = -1 * number;
    }

    return number;
}

boolean MyParseExpression(char* buffer, SIZE_T BufferLength, SIZE_T* result)
{
	SIZE_T i = 0, TempValue = 0;
	char Operand = '+', ch;

	*result = 0;

	for(i=0;i<BufferLength;i++)
	{
		ch = buffer[i];
		if(ch=='\0')
			break;
		else if(ch >= '0' && ch <= '9')		
		{
			TempValue = (TempValue*10)+(ch-0x30);
		}
		else
		{
			// we have a char that is NOT A NUMBER, so evaluate
			if(Operand == '+')		{ *result += TempValue;	}
			else if(Operand == '-') { *result -= TempValue;	}
			// all others ignored

			TempValue = 0;
			Operand = '+';		// defaults to adding 0 if we get a weird operand
			if(ch=='-')
			    Operand = '-';
		}
	}

	// in the event user does this "1+2+" i.e. forgets final number, it would be 0 anyway, so -0 or +0 makes no change
	if(Operand == '+')		{ *result += TempValue;	}
	else if(Operand == '-') { *result -= TempValue;	}


	return TRUE;
}

static int reflect
(
  int data,
  const uint32 len
)
{
    int ref = 0;
    uint32 i;

    for(i=0; i < len; i++) {
        if(data & 0x1) {
            ref |= (1 << ((len - 1) - i));
        }
        data = (data >> 1);
    }

   return ref;
}

/*===========================================================================

FUNCTION  calc_crc32

DESCRIPTION
  This function calculate CRC32 on input data.

DEPENDENCIES
  None

RETURN VALUE
  Returns CRC32 of given data

SIDE EFFECTS
  None

===========================================================================*/
uint32 calc_crc32
(
  const uint8   *data_in,
  const uint32  nbytes_in
)
{
    uint32 k = 8;                   // length of unit (i.e. byte)
    int MSB = 0;
    int gx = 0x04C11DB7;         // IEEE 32bit polynomial
    int regs = 0xFFFFFFFF;       // init to all ones
    int regsMask = 0xFFFFFFFF;   // ensure only 32 bit answer
    int regsMSB = 0;
    uint32 i, j;
    uint8 DataByte;

    if ( (data_in == NULL) || (nbytes_in == 0) )
        return 0;

    for( i=0; i < nbytes_in; i++) {
        DataByte = data_in[i];
        DataByte = reflect(DataByte,8);
        for(j=0; j < k; j++) {
            MSB = DataByte >> (k-1);  // get MSB
            MSB &= 1;                 // ensure just 1 bit
            regsMSB = (regs>>31) & 1; // MSB of regs
            regs = regs<<1;           // shift regs for CRC-CCITT
            if(regsMSB ^ MSB) {       // MSB is a 1
                regs = regs ^ gx;       // XOR with generator poly
            }
            regs = regs & regsMask;   // Mask off excess upper bits
            DataByte <<= 1;           // get to next bit
        }
    }

    regs = regs & regsMask;       // Mask off excess upper bits
    return reflect(regs,32) ^ 0xFFFFFFFF;
}
