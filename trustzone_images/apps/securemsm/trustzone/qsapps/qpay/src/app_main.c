
/**
   @file app_main.c
   @brief Sample trusted application to demonstrate use of GP TEE SE lib in
   @ conjunction with smart card service/HLOS daemon.
*/
/*=========================================================================
  Global Platform TEE SE  API Source File
  Description
  This file contains GP TEE SE API Implementation.

  # Copyright (c) 2015 - 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
  # Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/
/*===========================================================================
  Edit History
  when        who   what
  --------    ---   ----------------------------------------------------------
  16/03/2017  dc    Support for GP TEE SE API v1.1.1
  02/11/2016  dc    Remove qpay_api usage
  26/11/2016  dc    Set Response length to zero in case of TEE_ERROR_NO_DATA
  26/11/2015  dc    Add Support for TEE Secure Channel.
  07/09/2015  pm    Bug fixes.
  18/03/2015  pm    Initial Implementation of GP TEE SE API

  ===========================================================================*/

/*==========================================================================*
 *                             INCLUDE FILES                                *
 *==========================================================================*/

#include <stdint.h>
#include "tee_internal_se_api.h"
#include "tee_internal_se_api_ext.h"
#include "qsee_ese_service.h"
#include "EseDebug.h"

/*HLOS Controlling Daemon Commands Definitions*/

typedef enum {
  QPAY_OPEN_CONNECTION                      = 1, /*App service open and close*/
  QPAY_CLOSE_CONNECTION                     = 3,
  QPAY_SE_RESET                             = 4,  /* Secure Element has been reset from HLOS */
  QPAY_SE_SERVICE_OPEN                      = 41, /*Service Class*/
  QPAY_SE_SERVICE_CLOSE                     = 42,
  QPAY_SE_SERVICE_GET_READERS               = 43,
  QPAY_SE_READER_GET_PROPERTIES             = 51, /*Reader Class*/
  QPAY_SE_READER_GET_NAME                   = 52,
  QPAY_SE_READER_OPEN_SESSION               = 53,
  QPAY_SE_READER_CLOSE_SESSIONS             = 54,
  QPAY_SE_SESSION_ClOSE                     = 63, /*Session class*/
  QPAY_SE_SESSION_CLOSE_CHANNELS            = 64,
  QPAY_SE_SESSION_OPEN_BASIC_CHANNEL        = 65,
  QPAY_SE_SESSION_OPEN_LOGICAL_CHANNEL      = 66,
  QPAY_SE_CHANNEL_CLOSE                     = 71, /*Channel Class*/
  QPAY_SE_CHANNEL_SELECT_NEXT               = 72,
  QPAY_SE_CHANNEL_GET_SELECT_RESPONSE       = 73,
  QPAY_SE_CHANNEL_TRANSMIT                  = 74,
  QPAY_SE_CHANNEL_GET_RESPONSE_LENGTH       = 75, /* Secure Channel Protocol */
  QPAY_SE_SECURE_CHANNEL_OPEN               = 76,
  QPAY_SE_SECURE_CHANNEL_CLOSE              = 77,
  QPAY_SE_SECURE_CHANNEL_GET_SECURITY_LEVEL = 78
} qpay_cmd_id_t;

// clang-format off
#define QPAY_SE_STATUS_BYTE_LEN            1
#define QPAY_SE_CHANNEL_BYTE_LEN           1
#define QPAY_SE_OFFSET_STATUS_BYTE         0
#define QPAY_SE_OFFSET_CHANNEL_BYTE        1
#define QPAY_SE_OFFSET_PDU                 1
#define QPAY_SE_STATUS_SUCCESS             0x00
#define QPAY_SE_STATUS_FAILED              0xFF
// clang-format on

/* Input command data struct(TO TA from HLOS)*/
typedef struct
{
  uint32_t sessionHandle;
  uint32_t channelNumber;
  uint32_t cmd_id;
  uint32_t cmd_len; // Includes the status byte
  uint8_t  tApdu[QPAY_SE_STATUS_BYTE_LEN + QSEE_ESE_CPDU_MAX_SZ];
} __attribute__((packed)) qpay_cmd_t;

/* output command data struct(TO HLOS from TA)*/
typedef struct
{
  uint32_t sessionHandle;
  uint32_t channelNumber;
  uint32_t rsp_len;
  uint8_t  rApdu[QPAY_SE_STATUS_BYTE_LEN + QSEE_ESE_RPDU_MAX_SZ];
} __attribute__((packed)) qpay_rsp_t;

static TEE_SESessionHandle gSessionHandles[QSEE_ESE_MAX_NUM_OF_SESSIONS]    = { 0 };
static TEE_SEChannelHandle gChannelHandles[QSEE_ESE_MAX_NUMBER_OF_CHANNELS] = { 0 };
static TEE_SEServiceHandle gServiceHandle                                   = TEE_HANDLE_NULL;
static TEE_SEReaderHandle  gReaderHandle                                    = TEE_HANDLE_NULL;

/**
 *
 * Checks the returned value from GP TEE SE API and if its some error case
 * then it returns QPAY_SE_STATUS_FAILED(error indication) to HLOS daemon.
 *
 * @param   [in] retval : Incoming returned value from library.
 *
 * @return  None.
 **/
static uint8_t qpay_check_error(TEE_Result retval)
{
  uint8_t result = (uint8_t)retval;

  QSEE_ESE_ENTER("retval=%X", retval);

  if ((retval != QC_TEE_SE_WTX) && (retval != TEE_SUCCESS))
  {
    // QSEE_ESE_LOG_ERR("Returned from API %X will send QPAY_SE_STATUS_FAILED to HLOS", retval);

    /* Error Case*/
    result = QPAY_SE_STATUS_FAILED;
  }

  QSEE_ESE_EXIT("result=%X", result);

  return result;
}

/**
 *
 * Fills response APDU , status and other needed information by HLOS daemon in
 * response struct and returns that back to HLOS for further processing.
 *
 * @param   [out] rsp_ptr : response poiter buffer where R-APDU , status and other
 *                         information will be filled.
 *          [out] status : Status whether passed or failed or pending
 *          [in]  cmd    : Last command recieved from HLOS daemon as based on this
 *                         based on this cmd , needed response will be filled.
 *
 * @return  None.
 **/
static void qpay_get_rapdu(qpay_cmd_t *cmd_ptr, qpay_rsp_t *rsp_ptr, TEE_Result result)
{
  // QSEE_ESE_ENTER("result=%X", result);

  if (cmd_ptr && rsp_ptr)
  {
    rsp_ptr->rApdu[QPAY_SE_OFFSET_STATUS_BYTE] = qpay_check_error(result);

    switch (result)
    {
      case TEE_SUCCESS:

        if ((cmd_ptr->cmd_id == QPAY_SE_SESSION_OPEN_BASIC_CHANNEL) ||
            (cmd_ptr->cmd_id == QPAY_SE_SESSION_OPEN_LOGICAL_CHANNEL) ||
            (cmd_ptr->cmd_id == QPAY_SE_CHANNEL_TRANSMIT) ||
            (cmd_ptr->cmd_id == QPAY_SE_CHANNEL_GET_SELECT_RESPONSE) ||
            (cmd_ptr->cmd_id == QPAY_SE_CHANNEL_SELECT_NEXT))
        {
          // data already copied in buffer
          rsp_ptr->rsp_len += QPAY_SE_STATUS_BYTE_LEN;
        }
        else
        {
          /*Only result for rest of commands*/
          rsp_ptr->rsp_len = QPAY_SE_STATUS_BYTE_LEN;
        }

        break;

      case QC_TEE_SE_WTX:
        // data already copied in buffer
        rsp_ptr->rsp_len += QPAY_SE_STATUS_BYTE_LEN;
        break;

      case TEE_ERROR_NOT_SUPPORTED:
      case TEE_ERROR_ITEM_NOT_FOUND:
      case TEE_ERROR_61_SHORT_BUFFER:
      case TEE_ERROR_6C_SHORT_BUFFER:
      {
        TEE_Result retval = TEE_SEReaderGetStatus_ext(gReaderHandle,
                                                      rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                                      &rsp_ptr->rsp_len);

        if (retval == TEE_SUCCESS)
        {
          rsp_ptr->rApdu[QPAY_SE_OFFSET_STATUS_BYTE] = QPAY_SE_STATUS_FAILED;
          rsp_ptr->rsp_len += QPAY_SE_STATUS_BYTE_LEN;

          if ((result == TEE_ERROR_61_SHORT_BUFFER) || (result == TEE_ERROR_6C_SHORT_BUFFER))
          {
            rsp_ptr->rApdu[QPAY_SE_OFFSET_STATUS_BYTE] = QPAY_SE_STATUS_SUCCESS;
          }
        }
        else
        {
          /*Only result for rest of commands*/
          rsp_ptr->rsp_len = QPAY_SE_STATUS_BYTE_LEN;
        }
      }
      break;

      case TEE_ERROR_ACCESS_CONFLICT:
        rsp_ptr->rsp_len                           = QPAY_SE_STATUS_BYTE_LEN;
        rsp_ptr->rApdu[QPAY_SE_OFFSET_STATUS_BYTE] = QPAY_SE_STATUS_SUCCESS;
        break;

      default:
        rsp_ptr->rsp_len                           = QPAY_SE_STATUS_BYTE_LEN;
        rsp_ptr->rApdu[QPAY_SE_OFFSET_STATUS_BYTE] = QPAY_SE_STATUS_FAILED;
        break;
    }
  }

  // QSEE_ESE_EXIT();
}

static bool qpay_is_channel_handle_index_valid(uint8_t index)
{
  return index < QSEE_ESE_MAX_NUMBER_OF_CHANNELS;
}

static bool qpay_is_session_handle_valid(uint32_t handle)
{
  return handle < QSEE_ESE_MAX_NUM_OF_SESSIONS;
}

static uint32_t qpay_find_free_session_handle_index(void)
{
  uint32_t j     = 0;
  uint32_t index = QSEE_ESE_ARR_SZ(gSessionHandles);

  for (j = 0; j < QSEE_ESE_ARR_SZ(gSessionHandles); j++)
  {
    if (gSessionHandles[j] == TEE_HANDLE_NULL)
    {
      index = j;

      break;
    }
  }

  if (index >= QSEE_ESE_ARR_SZ(gSessionHandles))
  {
    QSEE_ESE_LOG_ERR("Unable to find free session handle");
  }

  return index;
}

static uint8_t qpay_find_free_channel_handle_index(void)
{
  uint8_t j     = 0;
  uint8_t index = QSEE_ESE_ARR_SZ(gChannelHandles);

  for (j = 0; j < QSEE_ESE_ARR_SZ(gChannelHandles); j++)
  {
    if (gChannelHandles[j] == TEE_HANDLE_NULL)
    {
      index = j;

      break;
    }
  }

  if (index >= QSEE_ESE_ARR_SZ(gChannelHandles))
  {
    QSEE_ESE_LOG_ERR("Unable to find free channel handle");
  }

  return index;
}

static TEE_Result qpay_find_channel_handle_index(uint8_t channelNumber)
{
  size_t     i     = 0;
  TEE_Result index = QSEE_ESE_ARR_SZ(gChannelHandles);

  for (i = 0; i < QSEE_ESE_ARR_SZ(gChannelHandles); i++)
  {
    if (gChannelHandles[i] != TEE_HANDLE_NULL)
    {
      uint32_t   nChannelNumber = QSEE_ESE_ARR_SZ(gChannelHandles);
      TEE_Result result         = TEE_SEChannelGetNumber_ext(gChannelHandles[i], &nChannelNumber);

      if ((result == TEE_SUCCESS) && (channelNumber == nChannelNumber))
      {
        index = i;
        break;
      }
    }
  }

  if (index >= QSEE_ESE_ARR_SZ(gChannelHandles))
  {
    QSEE_ESE_LOG_ERR("Invalid channel number %d", channelNumber);
  }

  return index;
}

static uint32_t qpay_get_number_of_sessions(void)
{
  uint32_t numOfSessions = 0;

  QSEE_ESE_ENTER();

  if (TEE_SEReaderGetSessionCount_ext(gReaderHandle, &numOfSessions) != TEE_SUCCESS)
  {
    numOfSessions = 0;
  }

  QSEE_ESE_EXIT("numOfSessions=%d", numOfSessions);

  return numOfSessions;
}

static TEE_Result qpay_channel_open(bool       bOpenBasic,
                                    uint32_t   sessionHandle,
                                    TEE_SEAID *seAID,
                                    uint8_t *  response,
                                    uint32_t * responseLen,
                                    uint32_t * channelNumber)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QSEE_ESE_ENTER("bOpenBasic=%d, sessionHandle=%X", bOpenBasic, sessionHandle);

  do
  {
    /* find free channel index to allocate handle to this request */
    const uint8_t channelIndex = qpay_find_free_channel_handle_index();

    if (!qpay_is_channel_handle_index_valid(channelIndex))
    {
      break;
    }

    const uint32_t sessionHandleIndex = sessionHandle - 1;

    if (!qpay_is_session_handle_valid(sessionHandleIndex))
    {
      break;
    }

    if (bOpenBasic)
    {
      retval = TEE_SESessionOpenBasicChannel(gSessionHandles[sessionHandleIndex],
                                             seAID,
                                             &gChannelHandles[channelIndex]);
    }
    else
    {
      retval = TEE_SESessionOpenLogicalChannel(gSessionHandles[sessionHandleIndex],
                                               seAID,
                                               &gChannelHandles[channelIndex]);
    }

    // Do not report response status if these areas to avoid confusng OEM debug
    if ((retval == TEE_ERROR_COMMUNICATION) || (retval == TEE_ERROR_SECURITY))
    {
      break;
    }

    uint32_t nChannelNumber = QSEE_ESE_ARR_SZ(gChannelHandles);

    // Try to get the channel number - the channel may have opened but failed to select
    // We get TEE_ERROR_ITEM_NOT_FOUND if channel failed to open
    retval = TEE_SEChannelGetNumber_ext(gChannelHandles[channelIndex], &nChannelNumber);

    if (retval == TEE_ERROR_ITEM_NOT_FOUND)
    {
      TEE_SEReaderGetStatus_ext(gReaderHandle, response, responseLen);

      // We still want to resurn the retval without updating it to success because
      // we failed to select a channel
      break;
    }

    if (*responseLen < QPAY_SE_CHANNEL_BYTE_LEN)
    {
      // expecting response buffer to have enough size for
      // channel number
      QSEE_ESE_LOG_ERR("Invalid rsp_len");
      retval = TEE_ERROR_BAD_PARAMETERS;
      break;
    }

    // Save the buffer length as we may need it later
    const uint32_t bufferLength         = *responseLen - QPAY_SE_CHANNEL_BYTE_LEN;
    uint32_t       selectResponseLength = bufferLength;

    // The response needs the channel number before the rest of the SELECT Response
    *response    = nChannelNumber;
    *responseLen = QPAY_SE_CHANNEL_BYTE_LEN;

    retval = TEE_SEChannelGetSelectResponse(gChannelHandles[channelIndex],
                                            response + QPAY_SE_CHANNEL_BYTE_LEN,
                                            &selectResponseLength);

    // TEE_ERROR_NO_DATA actually means we sent manage channel open successfully but did
    // not do the SELECT command i.e. no AID was specified with the command to open channel
    if (retval == TEE_ERROR_NO_DATA)
    {
      uint32_t statusLength = bufferLength;

      TEE_Result result = TEE_SEReaderGetStatus_ext(gReaderHandle,
                                                    response + QPAY_SE_CHANNEL_BYTE_LEN,
                                                    &statusLength);

      if (result != TEE_SUCCESS)
      {
        retval = result;
      }
      else if (statusLength != 0)
      {
        *responseLen += statusLength;

        retval = result;
      }

      break;
    }

    if (retval == TEE_SUCCESS)
    {
      *responseLen += selectResponseLength;
    }
    else
    {
      *responseLen = 0;
    }

  } while (0);

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_channel_transmit(uint8_t   channelNumber,
                                        uint8_t * command,
                                        uint32_t  commandLen,
                                        uint8_t * response,
                                        uint32_t *responseLen)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber=%d, commandLen=%d", channelNumber, commandLen);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    retval = TEE_SEChannelTransmit(gChannelHandles[channelIndex],
                                   command,
                                   commandLen,
                                   response,
                                   responseLen);
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_channel_close(uint8_t channelNumber)
{
  TEE_Result retval       = TEE_SUCCESS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber %d", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    TEE_SEChannelClose(gChannelHandles[channelIndex]);

    // Clear out copy of the channel handle
    gChannelHandles[channelIndex] = TEE_HANDLE_NULL;
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_session_close(uint32_t sessionHandle)
{
  TEE_Result     retval             = TEE_ERROR_BAD_PARAMETERS;
  const uint32_t sessionHandleIndex = sessionHandle - 1;

  QSEE_ESE_ENTER("sessionHandle=%X", sessionHandle);

  if (qpay_is_session_handle_valid(sessionHandleIndex))
  {
    /*Now close intended session*/
    TEE_SESessionClose(gSessionHandles[sessionHandleIndex]);

    /*Clear recorded session handle*/
    gSessionHandles[sessionHandleIndex] = TEE_HANDLE_NULL;

    retval = TEE_SUCCESS;
  }
  else
  {
    QSEE_ESE_LOG_INF("Invalid sessionHandle=%X", sessionHandle);
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_close_channels(uint32_t sessionHandle)
{
  TEE_Result     retval             = TEE_ERROR_BAD_PARAMETERS;
  const uint32_t sessionHandleIndex = sessionHandle - 1;

  QSEE_ESE_ENTER("sessionHandleIndex=%X", sessionHandleIndex);

  if (qpay_is_session_handle_valid(sessionHandleIndex))
  {
    size_t i = 0;

    /*Now close intended session*/
    TEE_SESessionCloseChannels(gSessionHandles[sessionHandleIndex]);

    for (i = 0; i < QSEE_ESE_ARR_SZ(gChannelHandles); i++)
    {
      if (gChannelHandles[i] != TEE_HANDLE_NULL)
      {
        TEE_SESessionHandle seSessionHandleTemp = TEE_HANDLE_NULL;

        retval = TEE_SEChannelGetSession_ext(gChannelHandles[i], &seSessionHandleTemp);

        if (retval != TEE_SUCCESS)
        {
          break;
        }

        if (seSessionHandleTemp == gSessionHandles[sessionHandleIndex])
        {
          gChannelHandles[i] = TEE_HANDLE_NULL;
        }
      }
    }
  }
  else
  {
    QSEE_ESE_LOG_INF("Invalid sessionHandle=%X", sessionHandle);
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_channel_get_select_rsp(uint8_t   channelNumber,
                                              uint8_t * response,
                                              uint32_t *responseLen)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber=%d", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    retval = TEE_SEChannelGetSelectResponse(gChannelHandles[channelIndex], response, responseLen);
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_channel_select_next(uint8_t   channelNumber,
                                           uint8_t * response,
                                           uint32_t *responseLen)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber=%d", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    retval = TEE_SEChannelSelectNext(gChannelHandles[channelIndex]);

    if (retval == TEE_SUCCESS)
    {
      retval = TEE_SEChannelGetSelectResponse(gChannelHandles[channelIndex], response, responseLen);
    }
    // TEE_ERROR_ITEM_NOT_FOUND indicates a response from the Secure Element did
    // not allow the selection of next applet
    else if (retval == TEE_ERROR_ITEM_NOT_FOUND)
    {
      retval = TEE_SEReaderGetStatus_ext(gReaderHandle, response, responseLen);
    }
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_session_open(uint32_t *sessionHandle)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QSEE_ESE_ENTER("numOfSessions=%d", qpay_get_number_of_sessions());

  if (sessionHandle != NULL)
  {
    const uint32_t sessionHandleIndex = qpay_find_free_session_handle_index();

    if (qpay_is_session_handle_valid(sessionHandleIndex))
    {
      retval = TEE_SEReaderOpenSession(gReaderHandle, &gSessionHandles[sessionHandleIndex]);

      if (retval == TEE_SUCCESS)
      {
        // We use the index as the session handle to the HLOS. But it cannot be zero so we offset it
        // by 1
        *sessionHandle = sessionHandleIndex + 1;

        QSEE_ESE_LOG_INF("Allocated sessionHandle=%X", *sessionHandle);
      }
    }
  }

  QSEE_ESE_EXIT("numOfSessions=%d, retval=%X", qpay_get_number_of_sessions(), retval);

  return retval;
}

static TEE_Result qpay_get_readers(TEE_SEReaderHandle *seReaderHandleList,
                                   uint32_t *          seReaderHandleListLen)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QSEE_ESE_ENTER("gReaderHandle=%X, gServiceHandle=%X", gReaderHandle, gServiceHandle);

  if (gServiceHandle != TEE_HANDLE_NULL)
  {
    if (gReaderHandle == TEE_HANDLE_NULL) // No reader allocated yet
    {
      retval = TEE_SEServiceGetReaders(gServiceHandle, &gReaderHandle, seReaderHandleListLen);

      if (retval == TEE_SUCCESS)
      {
        // Populate the list. We support just a single reader handle
        *seReaderHandleList = gReaderHandle;
      }
    }
    else
    {
      QSEE_ESE_LOG_INF("Reader handle %X are already allocated", gReaderHandle);

      // Populate the list. We support just a single reader handle
      *seReaderHandleList    = gReaderHandle;
      *seReaderHandleListLen = qpay_get_number_of_sessions();

      retval = TEE_SUCCESS;
    }
  }

  QSEE_ESE_EXIT("retval=%X, gReaderHandle=%X, gServiceHandle=%X",
                retval,
                gReaderHandle,
                gServiceHandle);

  return retval;
}

static TEE_Result qpay_channel_get_response_length(uint8_t channelNumber, uint32_t *responseLen)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber=%d", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    retval = TEE_SEChannelGetResponseLength(gChannelHandles[channelIndex], responseLen);
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_secure_channel_open(uint8_t channelNumber, TEE_SC_Params *scParams)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber=%d", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    const TEE_SEChannelHandle channelHandle = gChannelHandles[channelIndex];

    // We must close the secured channel before we secure it again as per v1.1.1 of GPD_SPE_024
    if (TEE_SESecureChannelGetSecurityLevel(channelHandle) != TEE_SC_NO_SECURE_MESSAGING)
    {
      TEE_SESecureChannelClose(channelHandle);
    }

    retval = TEE_SESecureChannelOpen(channelHandle, scParams);
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_secure_channel_close(uint8_t channelNumber)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    TEE_SESecureChannelClose(gChannelHandles[channelIndex]);

    // There was no panic if we got this far
    retval = TEE_SUCCESS;
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_close_sessions(void)
{
  TEE_Result retval = TEE_SUCCESS;

  QSEE_ESE_ENTER();

  // Close all the sessions for this reader. Allows resetting reader session resources
  TEE_SEReaderCloseSessions(gReaderHandle);

  secure_memset(gSessionHandles, 0, sizeof(gSessionHandles));

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_secure_element_reset(void)
{
  TEE_Result retval = TEE_SUCCESS;

  QSEE_ESE_ENTER();

  retval = qpay_close_sessions();

  secure_memset(gChannelHandles, 0, sizeof(gChannelHandles));

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_get_secure_channel_parameters(TEE_SC_Params *scParams)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QSEE_ESE_ENTER("scParams=%X", scParams);

  if (scParams)
  {
    // OEM must replace this key to correspond with the one provisioned
    // on the ESE. They (private, public) key pair would have provisioned
    // before this call.
    retval = TEE_ERROR_NOT_IMPLEMENTED;
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_reader_get_properties(uint8_t *response, uint32_t *responseLen)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QSEE_ESE_ENTER();

  if (response && responseLen && (*responseLen >= sizeof(TEE_SEReaderProperties)))
  {
    TEE_SEReaderProperties readerProperties;

    TEE_SEReaderGetProperties(gReaderHandle, &readerProperties);

    *responseLen = memscpy(response, *responseLen, &readerProperties, sizeof(readerProperties));

    if (*responseLen == sizeof(readerProperties))
    {
      retval = TEE_SUCCESS;
    }
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

static TEE_Result qpay_reader_get_name(uint8_t *response, uint32_t *responseLen)
{
  return TEE_SEReaderGetName(gReaderHandle, (char *)response, responseLen);
}

static TEE_Result qpay_channel_get_security_level(uint8_t   channelNumber,
                                                  uint8_t * response,
                                                  uint32_t *responseLen)
{
  TEE_Result retval       = TEE_ERROR_BAD_PARAMETERS;
  uint8_t    channelIndex = QSEE_ESE_ARR_SZ(gChannelHandles);

  QSEE_ESE_ENTER("channelNumber", channelNumber);

  channelIndex = qpay_find_channel_handle_index(channelNumber);

  if (qpay_is_channel_handle_index_valid(channelIndex))
  {
    uint32_t security_level = TEE_SESecureChannelGetSecurityLevel(gChannelHandles[channelIndex]);

    *responseLen = memscpy(response, *responseLen, &security_level, sizeof(security_level));

    if (*responseLen == sizeof(security_level))
    {
      retval = TEE_SUCCESS;
    }
  }

  QSEE_ESE_EXIT("retval=%X", retval);

  return retval;
}

/**
 *
 * invoked when trusted application is loaded.
 *
 * @param   void.
 *
 * @return  None.
 **/
void tz_app_init(void)
{
#ifdef QPAY_QSEE_LOG_SUPPORTED
  qsee_log_set_mask(QSEE_LOG_MSG_DEBUG | qsee_log_get_mask());
#else
  qsee_log_set_mask(QSEE_LOG_MSG_ERROR | QSEE_LOG_MSG_FATAL);
#endif // QPAY_QSEE_LOG_SUPPORTED

  QSEE_ESE_ENTER();

  QSEE_ESE_EXIT();
}

/**
 *
 * Handles commands coming from HLOS daemon and invokes corresponding method in
 * trusted application which internally invokes GP TEE APIs.

 * @param   [in] cmd     : Pointer to the command struct coming from HLOS.
 * @param   [in] cmdlen  : Length of comamnd from HLOS.Not being used by trusted application.
 * @param   [in] rsp_ptr : Pointer to the response struct which will be returned
 *                         back to HLOS after response is filled by GP TEE SE APIs.
 * @param   [in] rsplen  : Length of response from TZ.Not being used by trusted application.
 *
 * @return  None.
 **/

void tz_app_cmd_handler(void *cmd, uint32_t cmdlen, void *rsp, uint32_t rsplen)
{
  TEE_Result retval = TEE_ERROR_BAD_PARAMETERS;

  QSEE_ESE_ENTER("cmd=%X, cmdlen=%d, rsp=%X, rsplen=%d", cmd, cmdlen, rsp, rsplen);

  do
  {
    if ((cmd == NULL) || (rsp == NULL))
    {
      break;
    }

    static const uint64_t cmd_min_size = offsetof(qpay_cmd_t, tApdu) + QPAY_SE_STATUS_BYTE_LEN;
    static const uint64_t rsp_min_size = offsetof(qpay_rsp_t, rApdu) + QPAY_SE_STATUS_BYTE_LEN;

    if ((cmdlen < cmd_min_size) || (rsplen < rsp_min_size))
    {
      QSEE_ESE_LOG_ERR("cmdlen=%d, cmd_min_size=%d, rsplen=%d, rsp_min_size=%d",
                       cmdlen,
                       cmd_min_size,
                       rsplen,
                       rsp_min_size);

      break;
    }

    qpay_cmd_t *cmd_ptr = (qpay_cmd_t *)cmd;
    qpay_rsp_t *rsp_ptr = (qpay_rsp_t *)rsp;

    // status byte length already included in cmd_len
    if ((cmd_ptr->cmd_len < QPAY_SE_STATUS_BYTE_LEN) || ((cmd_min_size + cmd_ptr->cmd_len - QPAY_SE_STATUS_BYTE_LEN) > cmdlen))
    {
      QSEE_ESE_LOG_ERR("cmdlen=%d, cmd_min_size=%d, cmd_ptr->cmd_len=%d",
                       cmdlen,
                       cmd_min_size,
                       cmd_ptr->cmd_len);

      break;
    }

    QSEE_ESE_LOG_INF("HLOS cmd_id=%d, cmd_len=%d, rsp_len=%d, sessionHandle=%d, channelNumber=%d",
                     cmd_ptr->cmd_id,
                     cmd_ptr->cmd_len,
                     rsp_ptr->rsp_len,
                     cmd_ptr->sessionHandle,
                     cmd_ptr->channelNumber);

    // Include the status code in the debug print
    EseLogBuffer(cmd_ptr->tApdu, cmd_ptr->cmd_len, "HLOS2TA");

    // Validate the command size is consistent with buffer size
    if (cmd_ptr->cmd_len > sizeof(cmd_ptr->tApdu))
    {
      QSEE_ESE_LOG_ERR("Invalid cmd_len");
      break;
    }

    rsp_ptr->rsp_len = rsplen - rsp_min_size;

    switch (cmd_ptr->cmd_id)
    {
      case QPAY_OPEN_CONNECTION:
      case QPAY_SE_SERVICE_OPEN:
        // Initialize SE Service here and return available readers.
        retval = TEE_SEServiceOpen(&gServiceHandle);

        // TA already has an open handle
        if (retval == TEE_ERROR_ACCESS_CONFLICT)
        {
          retval = TEE_SUCCESS;
        }
        break;

      case QPAY_SE_SERVICE_GET_READERS:
      {
        TEE_SEReaderHandle seReaderHandle      = NULL;
        uint32_t           seReaderHandleCount = 1;

        retval = qpay_get_readers(&seReaderHandle, &seReaderHandleCount);

        if ((retval == TEE_SUCCESS) && seReaderHandle)
        {
          // Open a session in QSEE as the HLOS/SCS starts to communicate right away without
          // first
          // openning a session. We need a session to try open a basic/logical channel to
          // communicate
          if (qpay_get_number_of_sessions() == 0)
          {
            retval = qpay_session_open(&rsp_ptr->sessionHandle);
          }
        }
      }
      break;

      case QPAY_SE_READER_GET_PROPERTIES:
        retval =
          qpay_reader_get_properties(rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN, &rsp_ptr->rsp_len);
        break;

      case QPAY_SE_READER_GET_NAME:
        retval = qpay_reader_get_name(rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN, &rsp_ptr->rsp_len);
        break;

      case QPAY_SE_READER_OPEN_SESSION:
        retval = qpay_session_open(&rsp_ptr->sessionHandle);
        break;

      case QPAY_SE_SESSION_OPEN_BASIC_CHANNEL:
      case QPAY_SE_SESSION_OPEN_LOGICAL_CHANNEL:
        if (cmd_ptr->cmd_len >= QPAY_SE_STATUS_BYTE_LEN)
        {
          TEE_SEAID seAID = { NULL, 0 };

          if (cmd_ptr->cmd_len > QPAY_SE_STATUS_BYTE_LEN)
          {
            seAID.buffer    = cmd_ptr->tApdu + QPAY_SE_STATUS_BYTE_LEN;
            seAID.bufferLen = cmd_ptr->cmd_len - QPAY_SE_STATUS_BYTE_LEN;
          }

          if (seAID.bufferLen && seAID.buffer)
          {
            retval = qpay_channel_open(cmd_ptr->cmd_id == QPAY_SE_SESSION_OPEN_BASIC_CHANNEL,
                                       cmd_ptr->sessionHandle,
                                       &seAID,
                                       rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                       &rsp_ptr->rsp_len,
                                       &rsp_ptr->channelNumber);
          }
          else
          {
            retval = qpay_channel_open(cmd_ptr->cmd_id == QPAY_SE_SESSION_OPEN_BASIC_CHANNEL,
                                       cmd_ptr->sessionHandle,
                                       NULL,
                                       rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                       &rsp_ptr->rsp_len,
                                       &rsp_ptr->channelNumber);
          }
        }
        break;

      case QPAY_SE_CHANNEL_GET_SELECT_RESPONSE:
      {
        retval = qpay_channel_get_select_rsp(cmd_ptr->channelNumber,
                                             rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                             &rsp_ptr->rsp_len);

        // Either we did not send SELECT Command or the SELECT response status was not 0x9000
        if (retval == TEE_ERROR_NO_DATA)
        {
          rsp_ptr->rApdu[QPAY_SE_OFFSET_PDU] = 0; // No data
          rsp_ptr->rsp_len                   = 1; // Size of no data byte

          retval = TEE_SUCCESS;
        }
      }
      break;

      case QPAY_SE_CHANNEL_TRANSMIT:

        if (cmd_ptr->cmd_len >= (QPAY_SE_STATUS_BYTE_LEN + QPAY_SE_CHANNEL_BYTE_LEN))
        {
          const uint8_t CLA = cmd_ptr->tApdu[QPAY_SE_OFFSET_CHANNEL_BYTE];

          retval = qpay_channel_transmit(CLA & QSEE_ESE_APDU_CLA_CHANNEL_MASK,
                                         cmd_ptr->tApdu + QPAY_SE_OFFSET_CHANNEL_BYTE,
                                         cmd_ptr->cmd_len - QPAY_SE_OFFSET_CHANNEL_BYTE,
                                         rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                         &rsp_ptr->rsp_len);
        }
        break;

      case QPAY_SE_SESSION_ClOSE:
        retval = qpay_session_close(cmd_ptr->sessionHandle);
        break;

      case QPAY_SE_READER_CLOSE_SESSIONS:
        retval = qpay_close_sessions();
        break;

      case QPAY_SE_CHANNEL_CLOSE:

        if (cmd_ptr->cmd_len == (QPAY_SE_STATUS_BYTE_LEN + QPAY_SE_CHANNEL_BYTE_LEN))
        {
          const uint8_t CLA = cmd_ptr->tApdu[QPAY_SE_OFFSET_CHANNEL_BYTE];

          retval = qpay_channel_close(CLA & QSEE_ESE_APDU_CLA_CHANNEL_MASK);
        }
        break;

      case QPAY_SE_SESSION_CLOSE_CHANNELS:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = qpay_close_channels(cmd_ptr->sessionHandle);
        }
        break;

      case QPAY_SE_CHANNEL_SELECT_NEXT:

        if (cmd_ptr->cmd_len != 0)
        {
          retval = qpay_channel_select_next(cmd_ptr->channelNumber,
                                            rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                            &rsp_ptr->rsp_len);
        }
        break;

      case QPAY_CLOSE_CONNECTION:
      case QPAY_SE_SERVICE_CLOSE:
        TEE_SEServiceClose(gServiceHandle);

        gServiceHandle = TEE_HANDLE_NULL;

        retval = TEE_SUCCESS;
        break;

      case QPAY_SE_RESET:
        retval = qpay_secure_element_reset();
        break;

      case QPAY_SE_CHANNEL_GET_RESPONSE_LENGTH:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = qpay_channel_get_response_length(cmd_ptr->channelNumber, &rsp_ptr->rsp_len);
        }
        break;

      case QPAY_SE_SECURE_CHANNEL_OPEN:
        if (cmd_ptr->cmd_len != 0)
        {
          TEE_SC_Params scParams = { 0 };

          retval = qpay_get_secure_channel_parameters(&scParams);

          if (retval == TEE_SUCCESS)
          {
            retval = qpay_secure_channel_open(cmd_ptr->channelNumber, &scParams);
          }
        }
        break;

      case QPAY_SE_SECURE_CHANNEL_CLOSE:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = qpay_secure_channel_close(cmd_ptr->channelNumber);
        }
        break;

      case QPAY_SE_SECURE_CHANNEL_GET_SECURITY_LEVEL:
        if (cmd_ptr->cmd_len != 0)
        {
          retval = qpay_channel_get_security_level(cmd_ptr->channelNumber,
                                                   rsp_ptr->rApdu + QPAY_SE_STATUS_BYTE_LEN,
                                                   &rsp_ptr->rsp_len);
        }
        break;

      default:
        retval = QPAY_SE_STATUS_FAILED;
        QSEE_ESE_LOG_ERR("Unsupported command");
        break;
    }

    qpay_get_rapdu(cmd_ptr, rsp_ptr, retval);

    EseLogBuffer(rsp_ptr->rApdu, rsp_ptr->rsp_len, "TA2HLOS");

  } while (0);

  QSEE_ESE_EXIT("retval=%X", retval);
}

/**
 *
 * Trusted application shut down invoked from HLOS.
 *
 * @param   void.
 *
 * @return  None.
 **/
void tz_app_shutdown(void)
{
  QSEE_ESE_ENTER();

  QSEE_ESE_EXIT();
}
