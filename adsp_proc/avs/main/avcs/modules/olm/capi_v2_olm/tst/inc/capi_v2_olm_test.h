/*==========================================================================
 * Copyright (c) 2014-2015 QUALCOMM Technologies Incorporated.
 * All rights reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *==========================================================================*/

/**
 * @file capi_v2_olm_test.h 
 * Standalone Setup for CAPI_V2 modules. This can be used with any CAPI_V2
 * by defining 3 macros in makefile corresponding to capi_v2 header,
 * capi_v2 get static prop function and capi_v2 init function.
 */

/*==========================================================================
 * Edit History:
 * when         who         what, where, why
 * ----------   ---         ------------------------------------------------
 * 6/9/17   sranumul     CAPI_V2 OLM standslone setup

*/

#ifndef _CAPI_V2_OLM_TEST_H_

#define _CAPI_V2_OLM_TEST_H_

/*
 * Entry point function into the Capi V2 OLM test main function.
 */

int capi_v2_olm_test_main();

#define CAPI_V2_STATIC_PROP_FUNCTION capi_v2_olm_get_static_properties
#define CAPI_V2_INIT_FUNCTION  capi_v2_olm_init


#endif //_CAPI_V2_OLM_TEST_H_
