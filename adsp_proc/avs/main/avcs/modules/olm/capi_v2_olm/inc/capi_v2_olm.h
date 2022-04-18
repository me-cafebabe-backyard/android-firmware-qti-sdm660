/**
@file capi_v2_olm.h

@brief This header files contains the interface functions for OLM module

 */

/*========================================================================

Edit History

when          who            what, where, why
--------      ---            -------------------------------------------------------
18/9/2017     RV             Initial version
==========================================================================*/

/*-----------------------------------------------------------------------
Copyright (c) 2017-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
-----------------------------------------------------------------------*/

#ifndef CAPI_V2_OLM_H_
#define CAPI_V2_OLM_H_

#include "capi_v2.h"

#define OLM_REMOTE_RSP_MSG ELITE_APR_PACKET

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "Elite_CAPI_V2.h"

/*----------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/

capi_v2_err_t capi_v2_olm_get_static_properties (
    capi_v2_proplist_t *init_set_properties,
    capi_v2_proplist_t *static_properties);


capi_v2_err_t capi_v2_olm_init (
    capi_v2_t*              _pif,
    capi_v2_proplist_t      *init_set_properties);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* CAPI_V2_OLM_H_ */
