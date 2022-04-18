/**
 * @file UsbfnDwc3Util.c
 *
 * @brief Utility macros for debug messages and status checking.
 *
 * @copyright Copyright (C) 2013 by QUALCOMM Technologies, Inc.  All Rights Reserved.
 */
/*==============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/10/13   mliss   Initial implementation
 =============================================================================*/

#include "UsbfnDwc3Util.h"


/*
 * See header for description.
 */
CHAR8 *
PrintBusSpeed(
  IN  DWC_DEVICE_CONNECT_SPEED const Spd
  )
{
  switch (Spd){
  case DWC_SUPER_SPEED:
    return "DWC_SUPER_SPEED";
  case DWC_HIGH_SPEED:
    return "DWC_HIGH_SPEED";
  case DWC_LOW_SPEED:
    return "DWC_LOW_SPEED";
  case DWC_FULL_SPEED:
    return "DWC_FULL_SPEED";
  case DWC_FULL_SPEED_48:
    return "DWC_FULL_SPEED_48";
  default:
    return "Unknown Speed";
  }
}

/*
 * See header for description.
 */
CHAR8 *
PrintDevEvtType(
  IN UINT32 EvtType
  )
{
  switch (EvtType){
  case DWC_EVT_DEV_DISCONNECT_EVENT:
    return "DWC_EVT_DEV_DISCONNECT_EVENT";
  case DWC_EVT_DEV_USB_RESET:
    return "DWC_EVT_DEV_USB_RESET";
  case DWC_EVT_DEV_CONNECT_DONE:
    return "DWC_EVT_DEV_CONNECT_DONE";
  case DWC_EVT_DEV_USB_LINK_STATE_CHANGE:
    return "DWC_EVT_DEV_USB_LINK_STATE_CHANGE";
  case DWC_EVT_DEV_RESUME_REMOTE_WAKE_UP:
    return "DWC_EVT_DEV_RESUME_REMOTE_WAKE_UP";
  case DWC_EVT_DEV_HIBERNATION_REQUEST:
    return "DWC_EVT_DEV_HIBERNATION_REQUEST";
  case DWC_EVT_DEV_U3L2L1_SUSPEND:
    return "DWC_EVT_DEV_U3L2L1_SUSPEND";
  case DWC_EVT_DEV_START_OF_FRAME:
    return "DWC_EVT_DEV_START_OF_FRAME";
  case DWC_EVT_DEV_ERRATIC_ERROR:
    return "DWC_EVT_DEV_ERRATIC_ERROR";
  case DWC_EVT_DEV_CMD_COMPLETE:
    return "DWC_EVT_DEV_CMD_COMPLETE";
  case DWC_EVT_DEV_EVENT_BUFFER_OVERFLOW:
    return "DWC_EVT_DEV_EVENT_BUFFER_OVERFLOW";
  case DWC_EVT_DEV_VNDR_DEV_TST_LMP_RCVED:
    return "DWC_EVT_DEV_VNDR_DEV_TST_LMP_RCVED";
  default:
    return "Unknown Device Event";
  }
}

/*
 * See header for description.
 */
CHAR8 *
PrintEpCommandType(
  IN UINT32   EpCommand
  )
{
  switch (EpCommand){
  case DWC_EP_CMD_SET_EP_CONFIG_VAL:
    return "DWC_EP_CMD_SET_EP_CONFIG";
  case DWC_EP_CMD_SET_EP_XFER_RSC_CONFIG_VAL:
    return "DWC_EP_CMD_SET_EP_XFER_RSC_CONFIG";
  case DWC_EP_CMD_GET_EP_STATE_VAL:
    return "DWC_EP_CMD_GET_EP_STATE";
  case DWC_EP_CMD_SET_STALL_VAL:
    return "DWC_EP_CMD_SET_STALL";
  case DWC_EP_CMD_CLEAR_STALL_VAL:
    return "DWC_EP_CMD_CLEAR_STALL";
  case DWC_EP_CMD_START_XFER_VAL:
    return "DWC_EP_CMD_START_XFER";
  case DWC_EP_CMD_UPDATE_XFER_VAL:
    return "DWC_EP_CMD_UPDATE_XFER";
  case DWC_EP_CMD_END_XFER_VAL:
    return "DWC_EP_CMD_END_XFER";
  case DWC_EP_CMD_START_NEW_CONFIG_VAL:
    return "DWC_EP_CMD_START_NEW_CONFIG";
  default:
    return "unknown ep command type";
  }
}

/*
 * See header for description.
 */
CHAR8 *
PrintEpEvtType(
  IN UINT32 EvtType
  )
{
  switch (EvtType) {
  case DWC_EVT_EP_RSV0:
    return "DWC_EVT_EP_RSV0";
  case DWC_EVT_EP_XFER_COMPLETE:
    return "DWC_EVT_EP_XFER_COMPLETE";
  case DWC_EVT_EP_XFER_IN_PROGRESS:
    return "DWC_EVT_EP_XFER_IN_PROGRESS";
  case DWC_EVT_EP_XFER_NOT_READY:
    return "DWC_EVT_EP_XFER_NOT_READY";
  case DWC_EVT_EP_RSV1:
    return "DWC_EVT_EP_RSV1";
  case DWC_EVT_EP_STREAM:
    return "DWC_EVT_EP_STREAM";
  case DWC_EVT_EP_EP_CMD_COMPLETE:
    return "DWC_EVT_EP_EP_CMD_COMPLETE";
  default:
    return "Unknown EP Event";
  }
}

/*
 * See header for description.
 */
CHAR8 *
PrintLinkState(
  IN BOOLEAN        IsSuperSpeedEvt,
  IN USB_LINK_STATE LinkState
  )
{
  if (IsSuperSpeedEvt) {
    switch (LinkState) {
    case LS_U0:
      return "LS_U0";
    case LS_U1:
      return "LS_U1";
    case LS_U3:
      return "LS_U3";
    case LS_SS_DIS:
      return "LS_SS_DIS";
    case LS_RX_DET:
      return "LS_RX_DET";
    case LS_SS_INACT:
      return "LS_SS_INACT";
    case LS_POLL:
      return "LS_POLL";
    case LS_RECOV:
      return "LS_RECOV";
    case LS_HRESET:
      return "LS_HRESET";
    case LS_CMPLY:
      return "LS_CMPLY";
    case LS_LPBK:
      return "LS_LPBK";
    case LS_RESUME_RESET:
      return "LS_RESUME_RESET";
    default:
      return "Unknown Link State";
    }
  } else {
    switch (LinkState) {
    case LS_ON:
      return "LS_ON";
    case LS_SLEEP:
      return "LS_SLEEP";
    case LS_SUSPEND:
      return "LS_SUSPEND";
    case LS_DIS:
      return "LS_DISCONNECTED";
    case LS_EARLY_SUSPEND:
      return "LS_EARLY_SUSPEND";
    case LS_RESET:
      return "LS_RESET";
    case LS_RESUME:
      return "LS_RESUME";
    case LS_DEFAULT_INIT:
      return "LS_DEFAULT_INIT";
    default:
      return "Unknown Non-SuperSpeed Link State";
    }
  }
}

