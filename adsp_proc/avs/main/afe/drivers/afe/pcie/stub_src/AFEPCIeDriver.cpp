/*==============================================================================
$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/pcie/stub_src/AFEPCIeDriver.cpp#1 $
$DateTime: 2018/06/19 06:00:11 $
$Author: pwbldsvc $
$Change: 16448086 $
$Revision: #1 $

FILE:     AFEPCIeDriver.cpp

DESCRIPTION: Main Interface to the AFE PCIE driver

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

$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/pcie/stub_src/AFEPCIeDriver.cpp#1 $ $DateTime: 2018/06/19 06:00:11 $ $Author: pwbldsvc $

when        who  what, where, why
----------  ---  ----------------------------------------------------------
02-22-2016  mk  Initial Draft


============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/
#include "AFEPCIeDriver.h"

/*=====================================================================
 Globals
 ======================================================================*/

/*=====================================================================
 Functions
 ======================================================================*/

/**
 * Perform PCIE port initialization 
 *
 * @param[in] afe_svc_ptr pointer for AFE static service 
 *  
 * @return  ADSP_EOK on success, an error code on error
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_port_init(aud_stat_afe_svc_t* afe_svc_ptr)
{

	return ADSP_EUNSUPPORTED;
}

/**
 * Perform PCIE port de-initialization 
 *
 * @param[in] afe_svc_ptr pointer for AFE static service 
 *  
 * @return  ADSP_EOK on success, an error code on error
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_port_deinit(aud_stat_afe_svc_t* afe_svc_ptr)
{

	return ADSP_EUNSUPPORTED;
}

/**
 * Perform one time initialization of the AFE PCIE driver
 *
 * @return  ADSP_EOK on success, an error code on faliure
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_driver_init(void)
{

    return ADSP_EUNSUPPORTED;
}

/**
 * Perform de-initialization of the AFE PCIE driver
 *
 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult  afe_pcie_driver_deinit(void)
{
	return ADSP_EUNSUPPORTED;
}

/**
  @brief Sets the offsets from VFR  at which read/write 
         operations need to be triggered. 

  @param[in] afe_port_ptr pointer to AFE device port structure
  @param[in] rw_offset struct payload.  

  @return  ADSP_EOK on success, an error code on error

 */
ADSPResult afe_pcie_voice_set_rw_offsets(afe_dev_port_t* afe_port_ptr, elite_msg_any_t *pMsg)
{
  return ADSP_EUNSUPPORTED;
}
/**
  @brief Perform configuration of PCIE device for the given
         configuration

  @param[in] afe_port_ptr pointer to AFE device port structure
  @param[in] p_cfg pointer to AFE port PCIE device config
        strcutre
  @param[in] cfg_payload_size config struct payload size
  @param[in] cfg_ver -> config version

  @return  ADSP_EOK on success, an error code on error

 */
ADSPResult afe_set_pcie_cfg (afe_dev_port_t* afe_port_ptr, int8_t *p_cfg, uint16_t cfg_payload_size, uint32_t param_id)
{
	return ADSP_EUNSUPPORTED;
}

ADSPResult afe_get_pcie_cfg (afe_dev_port_t *afe_port_ptr, int8_t *param_buf_ptr, uint32_t payload_size, uint16_t *params_buffer_len_req_ptr, uint32_t param_id)
{
	return ADSP_EUNSUPPORTED;
}

/**
  @brief Open the configured PCIE device for data transfers

  @param[in] afe_port_ptr pointer to AFE device port structure

  @return  ADSP_EOK on success, an error code on error

 */
ADSPResult  afe_pcie_open (afe_dev_port_t* afe_port_ptr)
{
	return ADSP_EUNSUPPORTED;
}

/**
 * Close the configured PCIE device. 
 *
 * @param[in] afe_port_ptr pointer to AFE device port structure
 *  
 * @return
 * ADSP_EOK on success, an error code on error 
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult	afe_pcie_close(afe_dev_port_t* afe_port_ptr)
{
	return ADSP_EUNSUPPORTED;
}

/**
 * Data is fetched from PCIE core bsp driver to local 
 * buffer in case of Mic path (Tx path) 
 *
 * @param[in] afe_port_ptr pointer to AFE device port structure
 *  
 * @param[in] pBuffer - buffer to store the fetched data 
 *  
 * @param[in] numSamples - number of samples to be fetched
 *  
 * @return  ADSP_EOK on success, an error code on error 
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_read(afe_dev_port_t *afe_port_ptr, int16_t *pBuffer, uint32_t numSamples)
{
  return ADSP_EUNSUPPORTED;
}

/**
 * Device data will be writen to corebsp PCIE driver from
 * local buffer in case of Speaker path (Rx path) 
 *
 * @param[in] afe_port_ptr pointer to AFE device port structure
 *  
 * @param[in] pBuffer - data buffer to be pushed into DMA buffer
 *  
 * @param[in] numSamples - number of samples to be copied
 *  
 * @return
 * ADSP_EOK in case of success, otherwise corresponding error 
 * code 
 *  
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_write(afe_dev_port_t *afe_port_ptr,  int16_t  *pBuffer, uint32_t numSamples)
{
  return ADSP_EUNSUPPORTED;
}


/**
 * Update drift for PCIE port.
 *
 * @param[in] pDevPort Pointer to the instance of the port.
 * @return
 * void pointer to the handle.
 *
 * @dependencies
 * None.
 */
ADSPResult afe_update_avt_drift_for_pcie_port(afe_dev_port_t *afe_port_ptr)
{
  return ADSP_EUNSUPPORTED;
}

/**
 * For providing the delay introduced in PCIE driver data
 * path delay
 *
 * @param[in] port_id port id of the PCIE device
 *@param[out] data_path_delay_us is the delay introduced due 
 *    to internal buffering of PCIE driver
  
 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_driver_pcie_get_data_path_delay(afe_dev_port_t *afe_port_ptr, uint64_t* data_path_delay_us)

{
  *data_path_delay_us = 0;
  return ADSP_EUNSUPPORTED;
}

/**
 * For providing the header size required specific 
 * to the given port.
 *
 * @param[in] port_id  of the PCIe device
 * @param[out] Header size required for the port.

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_driver_pcie_get_header_size(afe_dev_port_t *afe_port_ptr, uint32_t* header_size)
{
  *header_size = 0;
  return ADSP_EUNSUPPORTED;
}

/**
 * For getting the timestamp from UAC driver
 * @param[in] port_id port id of the PCIE device

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_pcie_get_timestamp(afe_dev_port_t *afe_port_ptr)
{
  return ADSP_EUNSUPPORTED;
}

/**
 * For restoring PCIE device configuration
 * @param[in] port_id port id of the PCIE device

 * @return  ADSP_EOK on success, an error code on error
 *
 * @dependencies
 * None.
 *
 */
ADSPResult afe_restore_pcie_cfg(afe_dev_port_t *afe_port_ptr)
{
  return ADSP_EUNSUPPORTED;
}


