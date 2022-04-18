#ifndef __AFE_USBA_DRIVER_I_H__
#define __AFE_USBA_DRIVER_I_H__
/*==============================================================================
$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/pcie/src/AFEPCIeDriver_i.h#1 $
$DateTime: 2018/06/19 06:00:11 $
$Author: pwbldsvc $
$Change: 16448086 $
$Revision: #1 $

FILE:     AFEUSBAudioDriver_i.h

DESCRIPTION: This file should declaration of internal structures used by USB Audio driver

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Copyright (c) 2016 QUALCOMM Technologies, Inc.  All Rights Reserved.
QUALCOMM Technologies, Inc Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
==============================================================================*/
/*============================================================================
EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order. Please
use ISO format for dates.

$Header: //components/dev/avs.adsp/2.8/mangeshk.AVS.ADSP.2.8.USBAudio/afe/drivers/afe/usba/src/AFEUSBAudioDriver_i.h#1 
$ $DateTime: 2018/06/19 06:00:11 $ $Author: pwbldsvc $

when        who  what, where, why
----------  ---  ----------------------------------------------------------
03-16-2016  mk  Initial Draft

============================================================================*/
#include "AFEInternal.h"
#include "AFEInterface.h"
#include "qurt_elite.h"
#include "AFEPCIeDriver.h"
#include "adsp_afe_service_commands.h"
#include "avtimer_drv_api.h"
#include "AFEDeviceDriver.h"
#include "VoiceTimerMsgs.h"
#include "ipa_vop.h"
/*=====================================================================
 Macros
 ======================================================================*/

/*=====================================================================
 Typedef's
 ======================================================================*/
 
typedef struct pcie_driver_state
{
  bool_t                  is_initialized;
  /* is pcie driver initialized */
} pcie_driver_state_t;

typedef struct afe_pcie_driver_t
{
  void*  pcie_driver_hdl;     /**< Handle to PCIe audio driver */
  int32_t  acc_avt_drift_us;
  int64_t  avtimer_qtimer_offset;
}afe_pcie_driver_t;

typedef struct afe_pcie_vfr_timing_t
{
  qurt_elite_queue_t  *vtm_cmdq_ptr; // pointer to voice timer cmd Q
  uint32_t						is_new_offset_registered;
  uint32_t            vfr_mode;
  uint32_t            vsid;
  uint32_t            vfr_cycle_us;
  uint32_t            ul_offset_1;
  uint32_t            ul_offset_2;
  uint32_t            dl_offset_1;
  uint32_t            dl_offset_2;
  Vtm_SubUnsubMsg_t   vtm_sub_1;
  Vtm_SubUnsubMsg_t   vtm_sub_2;
} afe_pcie_vfr_timing_t;

typedef struct afe_pcie_dl_buf_with_ul_offset_header_t
{
  uint64_t      sample_number;
  uint64_t      time_stamp;
  uint64_t      ul_schedule_ts;
} afe_pcie_dl_buf_with_ul_offset_header_t;

typedef struct afe_pcie_dev_cfg_info
{
  uint32_t cfg_version;
  uint32_t dev_params_version;
  uint32_t sample_rate;
  uint16_t bit_width;
  uint16_t bytes_per_channel;
  uint16_t num_channels;
  uint16_t data_format;
  uint32_t frame_size;
  uint32_t timer_source;
  uint32_t vsid_value;
  
} afe_pcie_dev_cfg_info_t;

typedef struct afe_pcie_dev_state_struct_t
{
  // high level driver specific handles
  afe_dev_port_t          *afe_port_ptr;

  // configuration passed from apps
  afe_pcie_dev_cfg_info_t afe_pcie_dev_cfg;

  afe_pcie_driver_t       pcie_drv;
  afe_pcie_vfr_timing_t   afe_pcie_vfr_timing;
  uint32_t cb_counter;
  uint32_t dma_counter;  
  uint32_t time_sync_counter;    
  afe_pcie_dl_buf_with_ul_offset_header_t ul_offset_info;
	ipa_vop_resp_cb_err_code_e resp;
} afe_pcie_dev_state_struct_t;

/*=====================================================================
 Functions
 ======================================================================*/



#endif /*#ifndef __AFE_USBA_DRIVER_I_H__*/
