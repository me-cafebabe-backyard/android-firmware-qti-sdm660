/*============================================================================
  micro_ULog.c

  Public-facing/support micro_ULog functions.

  Copyright (c) 2012-2016 QUALCOMM Technologies, Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/
/* $Header: //components/rel/core.qdsp6/1.0.c2/services/diag/micro_diagbuffer/src/micro_ULog.c#1 $ */
#include "micro_ULog.h"
#include "CoreVerify.h"

/**
 * Macros
 */
#if defined(__cplusplus)
#define MICRO_ULOG_INLINE inline
#else
#define MICRO_ULOG_INLINE __inline
#endif

#define MICRO_ULOG_TYPE_LOG_HEADER_VERSION   0x00001000

/* Log status flags */
#define MICRO_ULOG_STATUS_DEFINED      (0x01 << 0)
#define MICRO_ULOG_STATUS_ENABLED      (0x01 << 1)

/* Log transports */
#define MICRO_ULOG_TRANSPORT_RAM  0
#define MICRO_ULOG_TRANSPORT_STM  1
#define MICRO_ULOG_TRANSPORT_ALT 2

/* Micro Ulog timestamps are 64-bit */
#define MICRO_ULOG_TIMESTAMP_SIZE  8

/* Feature flags */
#define MICRO_ULOG_FF1_64_BIT_TS 0x1
#define MICRO_ULOG_FF1_WLOCK     0x2

/* Length is the top 16 bits of the first word in a message */
#define MICRO_ULOG_LENGTH_MASK  0xFFFF0000
#define MICRO_ULOG_LENGTH_SHIFT 16

/* Individual micro Ulog messages are limited to 128 bytes */
#define MICRO_ULOG_MAX_MSG_SIZE 128
#define MICRO_ULOG_MIN_MSG_SIZE 8

/* The minimum size of a micro Ulog buffer size */
#define MICRO_ULOG_MIN_BUF_SIZE 64

/* To speed writes, the log buffer is always powers of two in length.
 * bufSizeMask is bufSize-1, allowing us to simply mask it with the read and
 * write indices to yield the actual memory pointer.
 */
#define MICRO_ULOG_BUFSIZE_MASK(log) (log->bufSize-1)

/* Include the header for QDSS API */
//#include "QDSSLite.h"
  
#define MICRO_ULOG_QDSS_SUCCESS   0
#define MICRO_ULOG_QDSS_FAIL     -1

/* Alloc the QDSS port. Return MICRO_ULOG_QDSS_SUCCESS/FAIL */
#define MICRO_ULOG_QDSS_ALLOC( x )  1/* QDSSAllocPort(x) */

/* Free the QDSS port, if necessary */
#define MICRO_ULOG_QDSS_FREE( x )   /* TBD */

/* QDSS Write routines */
#define MICRO_ULOG_QDSS_TS_WRITE( log, firstContent, firstCount )   /* QDSSWriteOSTPacket(log->stmPort, QDSSOSTHeader(TRACER_ENTITY_ULOG, log->protocol_num), firstContent, firstCount);*/
#define MICRO_ULOG_QDSS_NO_TS_WRITE( log, secondContent, secondCount )  /* QDSSWriteOSTPacket(log->stmPort, QDSSOSTHeader(TRACER_ENTITY_ULOG, log->protocol_num), secondContent, secondCount);*/

/**
 * Target-specific overrides
     */

#ifdef WINSIM

/* TODO: Need to update with appropriate PC API */
#define MICRO_ULOG_INIT_TIMESTAMP()
#define MICRO_ULOG_GETTIME64()                ( 0 )
#define MICRO_ULOG_TARGET_LOCK_INIT( x )      ( x = 1 )
#define MICRO_ULOG_LOCK_GET( x )              ( 0 )
#define MICRO_ULOG_LOCK_RELEASE( x )          ( 0 )

#elif defined(USE_ISLAND) //defined(ADSP_8994) Working with Chris/Spencer to define a global flag for use in code. Hardcoded for now
#include "uTimetick.h"

#define MICRO_ULOG_INIT_TIMESTAMP()
#define MICRO_ULOG_GETTIME64()                  (uint64)uTimetick_Get()
#define MICRO_ULOG_TARGET_LOCK_INIT( x )        qurt_rmutex_init( &x )
#define MICRO_ULOG_TARGET_LOCK_GET( x )         qurt_rmutex_lock( &x )
#define MICRO_ULOG_TARGET_LOCK_RELEASE( x )     qurt_rmutex_unlock( &x )

#elif 0// defined(FEATURE_REX) || defined(FEATURE_RIVAIMG) /* WCNSS */

static DalDeviceHandle * micro_ULogTimerHandle;

/**
 * <!-- micro_ULog_InitTimeStampHandle -->
 */
static void MICRO_ULOG_INLINE micro_ULog_InitTimeStampHandle( void )
  {
  CORE_VERIFY( micro_ULogTimerHandle == NULL );
  DalTimetick_Attach( "SystemTimer", &micro_ULogTimerHandle );
}

/**
 * <!-- micro_ULog_GetDalsysTimeStamp -->
 */
static uint64 MICRO_ULOG_INLINE micro_ULog_GetDalsysTimeStamp( void )
{
  uint64 timestamp;
  CORE_VERIFY_PTR( micro_ULogTimerHandle );

  DalTimetick_GetTimetick64( micro_ULogTimerHandle, &timestamp );
  return timestamp;
    }

#define MICRO_ULOG_GETTIME64()                 micro_ULog_GetDalsysTimeStamp()
#define MICRO_ULOG_INIT_TIMESTAMP()            micro_ULog_InitTimeStampHandle()
#define MICRO_ULOG_TARGET_LOCK_INIT( x )       DALSYS_SyncCreate( DALSYS_SYNC_ATTR_RESOURCE, (MICRO_ULOG_MUTEX_TYPE*)&x, NULL )
#define MICRO_ULOG_TARGET_LOCK_GET( x )        DALSYS_SyncEnter( x )
#define MICRO_ULOG_TARGET_LOCK_RELEASE( x )    DALSYS_SyncLeave( x )

#endif

#define MICRO_ULOG_LOCK_LOG( log ) \
do {\
  if ( log->feature_flags1 & MICRO_ULOG_FF1_WLOCK )\
  {\
    MICRO_ULOG_TARGET_LOCK_GET( log->lock );\
  }\
} while(0)

#define MICRO_ULOG_UNLOCK_LOG( log ) \
do {\
  if ( log->feature_flags1 & MICRO_ULOG_FF1_WLOCK )\
  {\
    MICRO_ULOG_TARGET_LOCK_RELEASE( log->lock );\
  }\
} while(0)

/**
 * Compiler or build env related overrides
 */
#if defined (WINSIM) || defined (WIN_DEBUGGER_EXTENSION)
#include "stdio.h"
#define MICRO_ULOG_STRLCPY(a, b, c) strcpy_s(a, c, b)

#elif defined (__GNUC__)
#include "stdio.h"
#include <stringl/stringl.h>
#define MICRO_ULOG_STRLCPY strlcpy

#else
#include <string.h>
#define MICRO_ULOG_STRLCPY strlcpy

#endif

/**
 * Enums
 */

/* Data subtypes stored in log message headers */
typedef enum
  {
  MICRO_ULOG_SUBTYPE_RESERVED_FOR_RAW = 0,
  MICRO_ULOG_SUBTYPE_REALTIME_PRINTF,
  MICRO_ULOG_SUBTYPE_REALTIME_BYTEDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_STRINGDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_WORDDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_CSVDATA,
  MICRO_ULOG_SUBTYPE_REALTIME_VECTOR,
  MICRO_ULOG_SUBTYPE_REALTIME_MULTIPART,
  MICRO_ULOG_SUBTYPE_REALTIME_MULTIPART_STREAM_END,
  MICRO_ULOG_SUBTYPE_REALTIME_TOKENIZED_STRING,
  MICRO_ULOG_SUBTYPE_RESERVED1,
  MICRO_ULOG_SUBTYPE_RESERVED2,
  MICRO_ULOG_SUBTYPE_RESERVED3,
  MICRO_ULOG_SUBTYPE_RAW8,
  MICRO_ULOG_SUBTYPE_RAW16,
  MICRO_ULOG_SUBTYPE_RAW32,

  /* Force enum to 32-bits */
  MICRO_ULOG_SUBTYPE_REALTIME_UINT32 = 0x7FFFFFFF
} MICRO_ULOG_REALTIME_SUBTYPES;

/* Exception/error conditions are indicated by one/more of the below bits
   set in MICRO_ULOG_TYPE.usageData */
typedef enum
  {
  /* Not an error condition; indicates that the log has wrapped atleast once */
  MICRO_ULOG_LOG_WRAPPED = 0x0001,

  /* There was an attempt to write a message too large for the buffer.
     The message was dropped */
  MICRO_ULOG_ERR_LARGEMSG = 0x0002,

  MICRO_ULOG_ERR_LARGEMSGOUT = 0x0004, // A message too large for the output
                                       // buffer was dropped because it could
                                       // not fit.

  /* The log has been reset atleast once */
  MICRO_ULOG_ERR_RESET = 0x0008,

  /* Force enum to 32-bits */
  MICRO_ULOG_ERR_UINT32 = 0x7FFFFFFF
} MICRO_ULOG_STATUS_TYPE;

/**
 * Routines
 */

/* Linked list of all logs in the system */
struct
  {
  MICRO_ULOG_MUTEX_TYPE gLock;
  MICRO_ULOG_TYPE *logHead;
} micro_ulogContext;

/**
 * Function prototypes for vTable entries
 */
static micro_ULogResult
micro_ULogInternal_STMWrite( micro_ULogHandle log,
                             uint32 firstMsgSize, const char *firstMsgData,
                             uint32 secondMsgSize, const char *secondMsgData );

/**
 * Vtables for common transports
 */
static MICRO_ULOG_CORE_VTABLE CoreVtableSTM =
        {
  micro_ULogInternal_STMWrite,
};

/**
 * <!-- micro_ULog_ConvertSize -->
 *
 * @brief Ulog message buffer sizes must be a power of 2 and atleast 64 bytes.
 */
static MICRO_ULOG_INLINE uint32 micro_ULogInternal_ConvertSize( uint32 size )
{
  uint32 output;

  if ( size < MICRO_ULOG_MIN_BUF_SIZE )
  {
    size = MICRO_ULOG_MIN_BUF_SIZE;
  }

  /* Compute the nearest power of 2 < size */
  output = 0;
  while ( size != 1 )
  {
    size >>= 1;
    output++;
  }
  output = 1 << output;

  return output;
}


/**
 * <!-- micro_ULog_Init -->
 *
 * @brief Initialize micro_Ulog
 */
static void micro_ULog_Init( void )
{
  /* micro_ULog globals are initialized when the first log is created */
  if ( micro_ulogContext.logHead == NULL )
  {
    MICRO_ULOG_TARGET_LOCK_INIT( micro_ulogContext.gLock );
  }
}

/**
 * <!-- micro_ULog_CreateLog -->
 *
 * @brief Creates a new lockless microUlog in the given memory buffer.
 * Users are required to use the MICRO_ULOG_MEM_NEEDED macro to compute the
 * size of memory buffer to pass in, based on desired message buffer size.
 *
 * @param hPtr : [OUT] Pass in the address of a micro_UlogHandle; will be set
 * to the newly created microUlog
 * @param logName : name of the log, must be < MICRO_ULOG_MAX_NAME_SIZE
 * @param mem : Pointer to the memory to create the microUlog in
 * @param finalMsgBufSize : [OUT] Returns the actual size of the microUlog's
 * message buffer
 * @param memSize : Size of memory pointed to by "mem"
 *
 * @return MICRO_ULOG_SUCCESS on success, MICRO_ULOG_ERR_BUFFER_TOO_SMALL if
 * the provided memory does not allow creation of a microUlog with a 64-byte
 * message buffer size, MICRO_ULOG_ERROR on other errors
 */
micro_ULogResult micro_ULog_CreateLog( micro_ULogHandle *hPtr,
                                       const char * logName,
                                       char * mem,
                                       uint32 *pFinalMsgBufSize,
                                       uint32 memSize )
{
  MICRO_ULOG_TYPE * log;
  uint32 namelen;
  uint32 realBufferSize;
  uint32 remainingSpace = 0;

  if ( !hPtr || !mem )
  {
    return MICRO_ULOG_ERROR;
  }

  if ( memSize < MICRO_ULOG_PADCOUNT(sizeof(MICRO_ULOG_TYPE)) )
  {
    return (MICRO_ULOG_ERROR);
  }

  remainingSpace = memSize - MICRO_ULOG_PADCOUNT(sizeof(MICRO_ULOG_TYPE));

  /* Verify there is enough space for atleast a MICRO_ULOG_MIN_BUF_SIZE-byte
     sized msg buffer */
  if ( remainingSpace < MICRO_ULOG_MIN_BUF_SIZE )
  {
    return MICRO_ULOG_ERR_BUFFER_TOO_SMALL;
  }

  /* Validate the name of the log */
  namelen = strlen( logName );
  if ( namelen > MICRO_ULOG_MAX_NAME_SIZE || namelen == 0 )
  {
    return MICRO_ULOG_ERR_INVALIDNAME;
  }

  micro_ULog_Init();

  memset( (void *)mem, 0, memSize );

  /* Round down to the nearest power of two */
  realBufferSize = micro_ULogInternal_ConvertSize( remainingSpace );

  log = (MICRO_ULOG_TYPE *)mem;

  MICRO_ULOG_STRLCPY( log->name, logName, MICRO_ULOG_MAX_NAME_SIZE + 1 );

  /* Link in the log into the list */
  MICRO_ULOG_TARGET_LOCK_GET( micro_ulogContext.gLock );
  log->next = micro_ulogContext.logHead;
  micro_ulogContext.logHead = log;
  MICRO_ULOG_TARGET_LOCK_RELEASE( micro_ulogContext.gLock );

  /* Initialize flags */
  log->version = MICRO_ULOG_TYPE_LOG_HEADER_VERSION;
  log->transport = MICRO_ULOG_TRANSPORT_RAM;
  log->feature_flags1 = MICRO_ULOG_FF1_64_BIT_TS;

  /* Assign buffer */
  log->buffer = mem + MICRO_ULOG_PADCOUNT( sizeof(MICRO_ULOG_TYPE) );
  log->bufSize = realBufferSize;

  MICRO_ULOG_INIT_TIMESTAMP();

  /* Enable the log */
  log->logStatus |= (MICRO_ULOG_STATUS_DEFINED | MICRO_ULOG_STATUS_ENABLED);

  /* Assign the log we just created to the handle the caller passed in */
  *hPtr = (micro_ULogHandle)log;

  /* If asked to return the finalMsgBufSize, do so */
  if ( pFinalMsgBufSize )
  {
    *pFinalMsgBufSize = realBufferSize;
  }

  return MICRO_ULOG_SUCCESS;
}

/**
 * <!-- micro_ULog_CreateLockableLog -->
 *
 * @brief Creates a new lockable microUlog in the given memory buffer.
 * Users are required to use the MICRO_ULOG_MEM_NEEDED macro to compute the
 * size of memory buffer to pass in, based on desired message buffer size.
 *
 * @param hPtr : [OUT] Pass in the address of a micro_UlogHandle; will be set
 * to the newly created microUlog
 * @param logName : name of the log, must be < MICRO_ULOG_MAX_NAME_SIZE
 * @param mem : Pointer to the memory to create the microUlog in
 * @param finalMsgBufSize : [OUT] Returns the actual size of the microUlog's
 * message buffer
 * @param memSize : Size of memory pointed to by "mem"
 * 
 * @return MICRO_ULOG_SUCCESS on success, MICRO_ULOG_ERR_BUFFER_TOO_SMALL if
 * the provided memory does not allow creation of a microUlog with a 64-byte
 * message buffer size, MICRO_ULOG_ERROR on other errors
 */
micro_ULogResult
micro_ULog_CreateLockableLog( micro_ULogHandle *hPtr,
                                               const char * logName,
                                               char * mem,
                              uint32 *pFinalMsgBufSize,
                                               uint32 memSize )
{
  MICRO_ULOG_TYPE * log;
  micro_ULogResult ret;

  ret = micro_ULog_CreateLog( hPtr, logName, mem, pFinalMsgBufSize, memSize );

  if ( ret != MICRO_ULOG_SUCCESS )
  {
    return ret;
  }

  log = (MICRO_ULOG_TYPE *)(*hPtr);

  /* Create lock */
  MICRO_ULOG_TARGET_LOCK_INIT( log->lock );

  /* Tag the log as lockable */
  log->feature_flags1 |= MICRO_ULOG_FF1_WLOCK;
  return MICRO_ULOG_SUCCESS;
}

/**
 * <!-- micro_ULog_ResetLog -->
 *
 * @brief Resets a log by moving the read and write pointers to the beginning
 * of the circular RAM buffer.
 */
static micro_ULogResult micro_ULog_ResetLog( micro_ULogHandle log )
{
  if ( !log )
  {
    return MICRO_ULOG_ERROR;
  }

  MICRO_ULOG_LOCK_LOG( log );

  /* Set all indices back to zero and clear flags */
  log->write = 0;
  log->readWriter = 0;
  log->read = 0;
  log->readFlags = 0;

  /* Set a reset bit in usageData and increment resetCount to indicate
     that this happened */
  log->usageData = MICRO_ULOG_ERR_RESET;
  ++log->resetCount;

  MICRO_ULOG_UNLOCK_LOG( log );

  return MICRO_ULOG_SUCCESS;
      }

/**
 * <!-- micro_ULogInternal_FreeSpaceForNewMsg -->
 *
 * @brief Returns MICRO_ULOG_SUCCESS if it is able to free space (by possibly
 * invalidating older messages) for an incoming message with the given size.
 */

#define MICRO_ULOG_MAX_FREE_ATTEMPTS \
                   (MICRO_ULOG_MAX_MSG_SIZE/MICRO_ULOG_MIN_MSG_SIZE)

static micro_ULogResult
micro_ULogInternal_FreeSpaceForNewMsg( MICRO_ULOG_TYPE *log,
                                       uint32 newMsgSize )
{
  uint32 oldMsgSize;
  uint32 bufferNeeded;
  uint32 freeAttempts = 0;
  uint32 bufsize_mask = MICRO_ULOG_BUFSIZE_MASK( log );

  /* Impossible to make space if newMsgSize is bigger than the buffer size */
  if ( newMsgSize > log->bufSize )
      {
    log->usageData |= MICRO_ULOG_ERR_LARGEMSG;
    return MICRO_ULOG_ERROR;
  }

  /* Determine if there is enough free space for the new message.
   * If not, remove old messages until there is enough room.
   *
   * In order to add the message:
   * Current message data in buffer = write - readWriter
   * Current message data + new message <= Buffer size
   */
  bufferNeeded = (log->write - log->readWriter) + newMsgSize;

  /* Loop until we create enough space for the new message */
  while ( bufferNeeded > log->bufSize )
  {
    /* Detect a a wrap condition. We're about to move the readWriter forward
     * to free up space. This will overwrite the oldest messages in the log.
     * 99% of the time SW on the device isn't reading the logs, so read is 0
     * and read == readWriter == 0 indicates that we've wrapped for the first
     * time. We tag usageData with MICRO_ULOG_LOG_WRAPPED to indicate this.
     */
    if ( log->read == log->readWriter )
        {
      log->usageData |= MICRO_ULOG_LOG_WRAPPED;
        }

    /* Remove the oldest message to free memory for the new message */
    oldMsgSize =
                 ((*((uint32 *)&log->buffer[log->readWriter & bufsize_mask])
                   & MICRO_ULOG_LENGTH_MASK) >> MICRO_ULOG_LENGTH_SHIFT);

    oldMsgSize = MICRO_ULOG_PADCOUNT( oldMsgSize );
    log->readWriter += oldMsgSize;
    if ( bufferNeeded >= oldMsgSize )
    {
      bufferNeeded -= oldMsgSize;
    }
    else
    {
      /* We have made enough room for the next msg,
         hence bytes needed in the buffer = 0 */
      bufferNeeded = 0;
    }

    /* We've seen rare crash reports where this loop gets stuck because these
     * critical pointers get corrupted due to hardware memory corruption.
     * If the log is ever in an impossible state, reset it.
     */
    if ( (log->write - log->readWriter) > log->bufSize )
    {
      micro_ULog_ResetLog( log );
      bufferNeeded = newMsgSize;
    }

    /* Making space for new logs relies on the integrity of previous logs.
     * In rare hardware memory corruption cases, this reliance can cause
     * problems with this loop. As failsafe, this loop cannot run more than
     * the times needed to free space for the largest possible message
     * (MICRO_ULOG_MAX_MSG_SIZE). There is no log message smaller than 
     * MICRO_ULOG_MIN_MSG_SIZE, so any attempt to make space more than
     * MICRO_ULOG_MAX_MSG_SIZE/MICRO_ULOG_MIN_MSG_SIZE times will cause a
     * log reset.
     */
    freeAttempts++;
    if ( freeAttempts > MICRO_ULOG_MAX_FREE_ATTEMPTS ||
         oldMsgSize > MICRO_ULOG_MAX_MSG_SIZE ||
         oldMsgSize < MICRO_ULOG_MIN_MSG_SIZE )
    {
      micro_ULog_ResetLog( log );
      bufferNeeded = newMsgSize;
  }
}

  return MICRO_ULOG_SUCCESS;
}

/**
 * <!-- micro_ULogInternal_PrepareForMessage -->
 *
 * @brief Prepares the log for the next message, removing old entries as
 * necessary. Fails if message is too big or if space cannot be cleared.
 */
static MICRO_ULOG_INLINE micro_ULogResult
micro_ULogInternal_PrepareForMessage( MICRO_ULOG_TYPE *log, uint32 msgCount )
{
  uint32 newMsgSize = MICRO_ULOG_PADCOUNT( msgCount );

  if ( newMsgSize > MICRO_ULOG_MAX_MSG_SIZE )
  {
    return MICRO_ULOG_ERROR;
  }

  return micro_ULogInternal_FreeSpaceForNewMsg( log, newMsgSize );
  }

/**
 * <!-- micro_ULogInternal_UsesFastWrite -->
 *
 * @brief Check to see if fast writes can be used, or whether Vtable
 * writes must be used.
 */
static MICRO_ULOG_INLINE boolean
micro_ULogInternal_UsesFastWrite( MICRO_ULOG_TYPE *log )
  {
  return ( log->transportVTable == NULL );
  }
  
/**
 * <!-- micro_ULogInternal_FastFmtSizeTS -->
 *
 * @brief Routine to write the format, message size and timestamp into logs
 * that can use fast RAM writes (RAM as transport, no tees).
 */
static MICRO_ULOG_INLINE micro_ULogResult
micro_ULogInternal_FastFmtSizeTS( MICRO_ULOG_TYPE *log,
                                  uint32 size, uint32 msg_format,
                                  uint32 *pStartIdx )
  {
  micro_ULogResult ret = MICRO_ULOG_SUCCESS;
  uint32 *wordPtr;
  uint64 timestamp;
  uint32 bufsize_mask = MICRO_ULOG_BUFSIZE_MASK( log );

  MICRO_ULOG_LOCK_LOG( log );

  ret = micro_ULogInternal_PrepareForMessage( log, size );
  if ( ret != MICRO_ULOG_SUCCESS )
  {
    MICRO_ULOG_UNLOCK_LOG( log );
    return ret;
  }

  /* Save the start_idx for caller */
  *pStartIdx = log->write;

  /* Len/format word */
  wordPtr = (uint32 *)&(log->buffer[log->write & bufsize_mask]);
  *wordPtr = msg_format; /* len remains at 0 until the msg is written */
  log->write += 4;

  timestamp = MICRO_ULOG_GETTIME64(); 
  //write the lower 32 bits of the timestamp
  wordPtr = (uint32 *)&(log->buffer[log->write & bufsize_mask]); 
  *wordPtr = (uint32)timestamp;
  log->write += 4;

  //write the upper 32 bits of the timestamp
  wordPtr = (uint32 *)&(log->buffer[log->write & bufsize_mask]); 
  *wordPtr = (uint32)((uint64)timestamp >> 32);
  log->write += 4; 

  /* Lock will be released in caller */
  return ret;
      }

/**
 * <!-- micro_ULog_RealTimeVprintf -->
 *
 * @brief Writes printf data to the specified log
 * Example: micro_ULog_RealTimePrintf(handle, 3, "test %d: %s", 1, "complete");
 *
 * @param log : Handle to the microUlog
 * @param dataCount : Number of word-sized parameters in the given va_list
 * @param ap : A variable list of arguments to the printf
 *
 * @return MICRO_ULOG_SUCCESS on success, MICRO_ULOG_ERROR on error
 */
micro_ULogResult micro_ULog_RealTimeVprintf( micro_ULogHandle log,
                                             uint32 dataCount,
                                             const char *formatStr,
                                             va_list ap )
      {
  uint32 total_size;
  uint32 bufsize_mask;
  uint64 timestamp;
  uint32 *wordPtr;
        uint32 i;
  micro_ULogResult ret = MICRO_ULOG_SUCCESS;

  if ( !log || !(log->logStatus & MICRO_ULOG_STATUS_ENABLED) || dataCount > 10 )
        {
    return MICRO_ULOG_ERROR;
      }

  bufsize_mask = MICRO_ULOG_BUFSIZE_MASK( log );

  /* len/fmt + sizeof(formatStr) + TS + data */
  total_size = 4 + sizeof(formatStr) + MICRO_ULOG_TIMESTAMP_SIZE + dataCount * 4;

  if ( micro_ULogInternal_UsesFastWrite( log ) )
      { 
    uint32 size_idx;
    ret = micro_ULogInternal_FastFmtSizeTS(
                                            log, total_size, MICRO_ULOG_SUBTYPE_REALTIME_PRINTF, &size_idx );
    if ( ret == MICRO_ULOG_SUCCESS )
        {
      /* Format string */
      wordPtr = (uint32 *)&(log->buffer[log->write & bufsize_mask]);
      *wordPtr = (uint32)formatStr;
      log->write += 4;

      /* Arguments */
      for ( i = 0; i < dataCount; i++ )
      {
        wordPtr = (uint32 *)&(log->buffer[log->write & bufsize_mask]);
        *wordPtr = (uint32)va_arg( ap, uint32 );
        log->write += 4;
        }

      /* Update the message length */
      wordPtr = (uint32 *)&(log->buffer[size_idx & bufsize_mask]);
      *wordPtr |= ((total_size << MICRO_ULOG_LENGTH_SHIFT) &
                      MICRO_ULOG_LENGTH_MASK);

      /* Release the lock, acquired within FastFmtSizeTS */
      MICRO_ULOG_UNLOCK_LOG( log );
      }
    }
  else /* no fastwrite */
  {
    uint32 dataArray[15];
    uint32 *dataPtr = dataArray;

    /* Message metadata */
    *dataPtr++ = MICRO_ULOG_SUBTYPE_REALTIME_PRINTF;

    timestamp = MICRO_ULOG_GETTIME64();
    *dataPtr++ = (uint32)timestamp;
    *dataPtr++ = (uint32)(timestamp >> 32);

    /* Format string */
    *dataPtr++ = (uint32)formatStr;

    /* Arguments */
    for ( i = 0; i < dataCount; i++ )
  {
      *dataPtr++ = va_arg( ap, uint32 );
  }

    ret = log->transportVTable->write( log, total_size,
                                       (char *)dataArray, 0, NULL );
}
  return ret;
  }


/**
 * <!-- micro_ULog_RealTimePrintf -->
 *
 * @brief Writes printf data to the specified log
 * Example: micro_ULog_RealTimePrintf(handle, 3, "test %d: %s", 1, "complete");
 *
 * @param log : Handle to the microUlog
 * @param dataCount : Number of word-sized parameters in the given printf
 *
 * @return MICRO_ULOG_SUCCESS on success, MICRO_ULOG_ERROR on error
 */
micro_ULogResult micro_ULog_RealTimePrintf( micro_ULogHandle log,
                                            uint32 dataCount,
                                            const char * formatStr, ... )
{
  va_list ap;
  micro_ULogResult ret;

  va_start( ap, formatStr );
  ret = micro_ULog_RealTimeVprintf( log, dataCount, formatStr, ap );
  va_end( ap );

  return ret;
}

/**
 * <!-- micro_ULog_RealTimeData -->
 * 
 * @brief Writes "dataCount" number of 32-bit words to the specified log
 */
#ifndef DEFEATURE_REALTIMEDATA
micro_ULogResult micro_ULog_RealTimeData( micro_ULogHandle log,
                                          uint32 dataCount, ... )
{
  uint32 total_size;
  uint64 timestamp;
  va_list ap;
  uint32 i;
  uint32 * wordPtr;
  uint32 bufsize_mask;
  micro_ULogResult ret = MICRO_ULOG_SUCCESS;

  if ( !log || !(log->logStatus & MICRO_ULOG_STATUS_ENABLED) ||
       dataCount > 10 || dataCount == 0 )
  {
    return MICRO_ULOG_ERROR;
  }

  bufsize_mask = MICRO_ULOG_BUFSIZE_MASK( log );

  /* len/fmt + TS + data */
  total_size = 4 + MICRO_ULOG_TIMESTAMP_SIZE + dataCount * 4;

  if ( micro_ULogInternal_UsesFastWrite( log ) )
  {
    uint32 size_idx;
    ret = micro_ULogInternal_FastFmtSizeTS(
                                            log, total_size,
                                            MICRO_ULOG_SUBTYPE_REALTIME_WORDDATA, &size_idx );
    if ( ret == MICRO_ULOG_SUCCESS )
  {
      va_start( ap, dataCount );
      for ( i = 0; i < dataCount; i++ )
      {
        wordPtr = (uint32 *)&(log->buffer[log->write & bufsize_mask]);
        *wordPtr = (uint32)va_arg( ap, uint32 );
        log->write += 4;
      }
      va_end( ap );

      /* Update the message length */
      wordPtr = (uint32 *)&(log->buffer[size_idx & bufsize_mask]);
      *wordPtr |= ((total_size << MICRO_ULOG_LENGTH_SHIFT) &
                      MICRO_ULOG_LENGTH_MASK);

      /* Release the lock, acquired within FastFmtSizeTS */
      MICRO_ULOG_UNLOCK_LOG( log );
    }
  }
  else
  {
    uint32 dataArray[15];
    uint32 *dataPtr = dataArray;

        *dataPtr++ = MICRO_ULOG_SUBTYPE_REALTIME_WORDDATA;
        timestamp = MICRO_ULOG_GETTIME64();
        *dataPtr++ = (uint32)timestamp;
        *dataPtr++ = (uint32)((uint64)timestamp >> 32);

        va_start( ap, dataCount );
        for ( i = 0; i < dataCount; i++ )
        {
          *dataPtr++ = va_arg( ap, uint32 );
        }
        va_end( ap );

    ret = log->transportVTable->write( log, total_size,
                                       (char *)dataArray, 0, NULL );
      }
  return ret;
  }
#endif

/**
 * <!-- micro_ULog_Enable -->
 *
 * @brief Enable the log
 */
micro_ULogResult micro_ULog_Enable( micro_ULogHandle log )
{
  micro_ULogResult ret = MICRO_ULOG_SUCCESS;

  if ( !log )
  {
    return MICRO_ULOG_ERROR;
  }

  if ( (log->logStatus & MICRO_ULOG_STATUS_DEFINED) == 0 ||
       log->buffer == NULL )
  {
    ret = MICRO_ULOG_ERR_INITINCOMPLETE;
  }
  else if ( log->logStatus & MICRO_ULOG_STATUS_ENABLED )
  {
    ret = MICRO_ULOG_ERR_ALREADYENABLED;
  }
  else
  {
    log->logStatus |= MICRO_ULOG_STATUS_ENABLED;
}

  return ret;
}

/**
 * <!-- micro_ULog_SetTransport -->
 *
 * @brief Sets the transport of the microUlog to the given handler
 */
micro_ULogResult
micro_ULog_SetTransport( micro_ULogHandle log,
                         MICRO_ULOG_CORE_VTABLE *transportVTable )
{
  if ( !log )
  {
    return MICRO_ULOG_ERROR;
  }

  log->transportVTable = transportVTable;
  log->transport = MICRO_ULOG_TRANSPORT_ALT;

  return MICRO_ULOG_SUCCESS;
}

/**
 * <!-- micro_ULogInternal_STMWrite -->
 *
 * @brief The write routine for logs that use QDSS as transport
 */
static micro_ULogResult
micro_ULogInternal_STMWrite( micro_ULogHandle log,
                             uint32 firstMsgSize, const char *firstMsgData,
                             uint32 secondMsgSize, const char *secondMsgData )
{
  CORE_VERIFY( log->transport == MICRO_ULOG_TRANSPORT_STM );

  MICRO_ULOG_QDSS_TS_WRITE( log, firstMsgData, firstMsgSize );
  if ( secondMsgSize != 0 )
  {
    MICRO_ULOG_QDSS_NO_TS_WRITE( log, secondMsgData, secondMsgSize );
  }
  return MICRO_ULOG_SUCCESS;
}

/**
 * <!-- micro_ULog_SetTransportToSTM -->
 * 
 * @brief Sets the transport of the microUlog to QDSS/STM
 */
micro_ULogResult micro_ULog_SetTransportToSTM( micro_ULogHandle log )
{
  micro_ULogResult ret = MICRO_ULOG_SUCCESS;

  if ( !log )
  {
    return MICRO_ULOG_ERROR;
  }

  if ( log->transport != MICRO_ULOG_TRANSPORT_STM )
  {
    if ( MICRO_ULOG_QDSS_ALLOC( &log->stmPort ) == MICRO_ULOG_QDSS_SUCCESS )
    {
      log->transportVTable = &CoreVtableSTM;
      log->transport = MICRO_ULOG_TRANSPORT_STM;
    }
    else
    {
      ret = MICRO_ULOG_ERROR;
    }
  }
  return ret;
}

/**
 * <!-- micro_ULog_SetTransportToRAM -->
 *
 * @brief Sets the transport of the microUlog (back) to RAM
 */
micro_ULogResult micro_ULog_SetTransportToRAM( micro_ULogHandle log )
{
  if ( !log )
  {
    return MICRO_ULOG_ERROR;
  }

  /* Deregister if the current transport was QDSS */
  if ( log->transport == MICRO_ULOG_TRANSPORT_STM )
  {
    MICRO_ULOG_QDSS_FREE( &log->stmPort );
  }

  log->transportVTable = NULL;
  log->transport = MICRO_ULOG_TRANSPORT_RAM;

  return MICRO_ULOG_SUCCESS;
}

#ifdef FEATURE_FAST7
/**
 * <!-- micro_ULog_Fast7WordWrite -->
 *
 * @brief A special routines that writes 7 words to the specified log in a
 * format compatible with Raw Ulogs. This function works on a log that ONLY
 * contains Fast7 messages to optimize the way space is freed when the log
 * wraps. It CANNOT be mixed with other types of writes to the same log.
 * Doing so would corrupt messages in that log.
 *
 * NOTE: Routine assumes a LOCKLESS log
 */
micro_ULogResult micro_ULog_Fast7WordWrite( micro_ULogHandle log,
                                            uint32 message[7] )
{
  if ( !log )
  {
    return MICRO_ULOG_ERROR;
  }

  if ( micro_ULogInternal_UsesFastWrite( log ) )
  {
    uint32 *buffer = (uint32 *)log->buffer;
    uint32 bufSize = log->bufSize;
    uint32 bufSizeMask = MICRO_ULOG_BUFSIZE_MASK( log );
    uint32 msgSize = 7 * sizeof(uint32);
    uint32 msgTotalSize = 4 + msgSize; /* len/fmt + data */
    uint32 bufferNeeded = log->write - log->readWriter + msgTotalSize;
    uint32 size_idx;

    if ( bufferNeeded > bufSize )
    {
      if ( log->read == log->readWriter )
      {
        /* Mark up the log as wrapped */
        log->usageData |= MICRO_ULOG_LOG_WRAPPED;
      }
      /* Advance the readWriter pointer forward by 1 message. Note how this is
       * a speed optimization from normal ULogs. Since all messages are 8 words
       * long, erasing the old message doesn't require reading the message and
       * advancing the readWriter by the old message size. We simply jump
       * readWriter forward 8 words. This is faster, but exactly why this
       * Fast7 API can't be used with other APIs in the same log.
       */
      log->readWriter += msgTotalSize;
    }

    /* 'zero' size to an appropriate word index and increment write pointer */
    size_idx = (log->write & bufSizeMask) >> 2;
    buffer[size_idx] = 0;
    log->write += 4;

    /* write message out to buffer (except for size) */
    memcpy( &buffer[size_idx + 1], message, msgSize );
    log->write += msgSize;

    /* finally, store size and format */
    buffer[size_idx] =
                       (msgTotalSize << 16) | MICRO_ULOG_SUBTYPE_RESERVED_FOR_RAW;
  }
  else
  {
    /* Log does not use fast RAM; use VTable writes instead */
    uint32 logbuf[8];
    /* The first word of the message has size and the msg format */
    logbuf[0] =
                0x20 << MICRO_ULOG_LENGTH_SHIFT | MICRO_ULOG_SUBTYPE_RESERVED_FOR_RAW;
    /* put the rest of the message in the buffer */
    memcpy( logbuf + 1, message, 7 * sizeof(uint32) );
    /* send the prepared log message */
    log->transportVTable->write( log, 8 * sizeof(uint32),
                                 (char *)logbuf, 0, NULL );
  }

  return MICRO_ULOG_SUCCESS;
}
#endif /* FEATURE_FAST7 */
