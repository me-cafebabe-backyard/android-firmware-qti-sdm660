/** @file SerialPortShLibImpl.c
   
  Contains Serial IO Shared Library loader and access functions.

  Copyright (c) 2012-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/18/14   jb      Update DCC support
 08/12/14   vk      Enable UART write
 07/09/14   vk      Skip uart_write till driver is available
 06/05/14   na      Set SyncIOEnable to TRUE for 8994 bring up
 03/28/14   vk      Set SyncIOEnable to TRUE for PRE_SIL
 10/22/13   vk      Update return types for 64 bit
 04/15/13   yg      Use buffer layer as top level serial port Lib
 01/24/13   yg      Add non blocking buffer layer
 12/10/12   yg      Buffer dynamically allocated by client
 09/17/12   yg      Initial Version

=============================================================================*/

#include "ShLib.h"
#include "Library/SerialPortShLib.h"
#include <Library/BaseMemoryLib.h>
#include "Uart.h"

/* Version 1.1 */
#define CURRENT_SIO_LIB_VERSION  0x00010001

/* Allocate buffer dynamically for UART Logging */
STATIC UINT8 *SerialPortBuffer;
STATIC UINT8 *EnQPtr, *DeQPtr;
STATIC UINT32 PortBufferSize;
STATIC BOOLEAN NoPortOut = FALSE;
STATIC BOOLEAN SyncIOEnable = TRUE;

extern SioPortLibType SioLib;

STATIC
UINTN
GetByteCountInBuffer (VOID)
{
  UINT8* BufferEndPtr;
  UINTN BytesToSend;

  if (SerialPortBuffer == NULL)
    return 0;

  BufferEndPtr = (UINT8*)SerialPortBuffer + PortBufferSize;

  if (EnQPtr >= DeQPtr)
    BytesToSend = EnQPtr - DeQPtr;
  else
    BytesToSend = BufferEndPtr - DeQPtr;

  return BytesToSend;
}

STATIC
UINTN
DequeueSendBufferedData (VOID)
{
  UINT8* BufferEndPtr;
  UINTN BytesToSend, BytesSent;

  if (SerialPortBuffer == NULL)
    return 0;

  BufferEndPtr = SerialPortBuffer + PortBufferSize;
  /*
   *  Scenario 1:       Start        DeQ       EnQ        End
   *
   *  Scenario 2:       Start           EnQ        DeQ    End
   * */
  BytesToSend = GetByteCountInBuffer ();

  if (BytesToSend)
  {
    BytesSent = uart_write (DeQPtr, BytesToSend);
#if 0 /* Enable if UART driver not available */
    BytesSent = BytesToSend;
#endif    
    DeQPtr += BytesSent;
    if (DeQPtr >= BufferEndPtr)
      DeQPtr = SerialPortBuffer;

    BytesToSend = GetByteCountInBuffer ();
  }
  return BytesToSend;
}

UINTN
SerialPortDrain (VOID)
{
  return DequeueSendBufferedData ();
}

UINTN
SerialPortFlush (VOID)
{
  UINTN BytesSent, TotalBytes = 0;

  do {
    BytesSent = DequeueSendBufferedData ();
    TotalBytes += BytesSent;
  }while (BytesSent);

  return TotalBytes;
}

/*
 *   UART Buffering design
 *
 *   SerialPortBuffer
 *   |
 *   |
 *   |<-------------------- PortBufferSize ------------------------------>|                                                                   
 *   V
 *   +-------------+----------------------+-------------------------------+
 *   |             |                      |                               |
 *   | Free        | Buffered Data        |   Free Space                  |
 *   |             |                      |                               |
 *   +-------------+----------------------+-------------------------------+
 *                 | Send to port =>      |
 *                 V                      +--> Add data here
 *                 DeQPtr (DQ)            EnQPtr (NQ)
 *
 *   NQ will be pointing to empty location where data can be written
 *   DQ will be pointing to filled location where valid data is prsent
 *   if NQ == DQ then there is no buffered data, ie whole buffer has been
 *   already sent.
 *
 *
 * */

/* Returns remaining number of bytes */
STATIC
UINTN
EnqueueData (UINT8* SrcDataBuffer, UINTN BytesToQueue)
{
  UINT8* BufferEndPtr;
  UINTN  FreeCnt;

  if (SerialPortBuffer == NULL)
    return BytesToQueue;

  BufferEndPtr = SerialPortBuffer + PortBufferSize;
  while (BytesToQueue)
  {
    /* See how much we can fill */
    if (EnQPtr >= DeQPtr)
      FreeCnt = BufferEndPtr - EnQPtr;
    else
    {
      FreeCnt = DeQPtr - EnQPtr;
      /* Don't allow EnQ and DeQ to be at the same position when data is there
       * since that represents empty condition */
      --FreeCnt;

      if (FreeCnt == 0)
        return BytesToQueue;
    }

    if (FreeCnt > BytesToQueue)
      FreeCnt = BytesToQueue;

    CopyMem (EnQPtr, SrcDataBuffer, FreeCnt);

    BytesToQueue -= FreeCnt;
    EnQPtr += FreeCnt;
    SrcDataBuffer += FreeCnt;

    if (EnQPtr >= BufferEndPtr)
      EnQPtr = SerialPortBuffer;
  }
        
  return BytesToQueue;
}

EFI_STATUS EFIAPI
SerialPortInitialize(void)
{
  return uart_initialize ();
}

BOOLEAN EFIAPI
SerialPortPoll(void)
{
  return uart_poll ();
}

UINTN EFIAPI
SerialPortRead(OUT UINT8 *user_buffer, IN UINTN bytes_requested)
{
  return uart_read (user_buffer, bytes_requested);
}

UINTN
SerialPortWrite (UINT8* Buffer, UINTN Bytes)
{
  UINT8* MsgBuff;
  UINTN BytesRemain, Sent;

  /* If buffered layer is available then
   * directly call into the driver layer
   * This happens only in the SEC module */
  if (SioLib.Write)
    return SioLib.Write (Buffer, Bytes);

  BytesRemain = Bytes;
  MsgBuff = Buffer;

  while (BytesRemain)
  {
    Sent = uart_write (MsgBuff, BytesRemain);
#if 0 /* Enable if UART dirver not available */
    Sent = BytesRemain;
#endif    
    MsgBuff += Sent;
    BytesRemain -= Sent;
  }

  return Bytes;
}

/*
 *  This is going through additional layer to control the output options
 *  Here the buffering and port output control options are available
 * */
UINTN
SerialBufferedWrite (UINT8* Buffer, UINTN Bytes)
{
  EnqueueData (Buffer, Bytes);

  if (NoPortOut == TRUE)
    return Bytes;

  if (SyncIOEnable)
    return SerialPortFlush ();
  else
    DequeueSendBufferedData ();

  return 0;
}

/* Control Port output and buffering options
 *
 * Refer to header file for Arg and Param values documentation
 */
UINTN
SerialPortControl (IN UINTN Arg, IN UINTN Param)
{
  switch (Arg)
  {
  case SIO_CONTROL_BUFFERING:
   /* Ignore, now always buffered */
    break;

  case SIO_CONTROL_PORTOUT:
    NoPortOut = Param;
    break;

  case SIO_CONTROL_SYNCHRONOUS_IO:
    SyncIOEnable = Param;
    break;

  default:
    break;
  }

  return 0;
}

VOID
EnableSynchronousSerialPortIO (VOID)
{
  SerialPortControl (SIO_CONTROL_SYNCHRONOUS_IO, TRUE);
}

SioPortLibType SioLib =
{
  .LibVersion = CURRENT_SIO_LIB_VERSION,
  .Read = SerialPortRead,
  .Write = NULL,
  .Drain = SerialPortDrain,
  .Flush = SerialPortFlush,
  .Poll = SerialPortPoll,
  .Control = SerialPortControl,
};

EFI_STATUS
SerialPortShLibInit ( IN  UINT8*   SerialBuffer  OPTIONAL, 
                      IN  UINT32   BufferSize    OPTIONAL)
{
  ShLibLoaderType *ShLibLoader;
  EFI_STATUS  LoadStatus;

  ShLibLoader = GetShLibLoader();
  if (ShLibLoader == NULL)
    return EFI_NOT_FOUND;

  SerialPortBuffer = NULL;
  PortBufferSize = 0;

#ifdef PRE_SIL
  SyncIOEnable = TRUE;
#endif  

  if ((SerialBuffer != NULL) && (BufferSize != 0) && 
      (((UINTN)SerialBuffer + BufferSize) > (UINTN)SerialBuffer))
  {
    SerialPortBuffer = SerialBuffer;
    EnQPtr = DeQPtr = SerialPortBuffer;
    PortBufferSize = BufferSize;
    ZeroMem (SerialPortBuffer, PortBufferSize);
  }

  LoadStatus = ShLibLoader->InstallLib (SIO_PORT_LIB_NAME, SioLib.LibVersion, (VOID*)&SioLib);

  SioLib.Write = SerialBufferedWrite;

  if (LoadStatus == LIB_SUCCESS)
    return EFI_SUCCESS;
  else
    return EFI_NOT_FOUND;
}


