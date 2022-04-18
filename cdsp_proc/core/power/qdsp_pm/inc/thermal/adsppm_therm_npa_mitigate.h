#ifndef ADSPPM_THERM_NPA_MITIGATE_H
#define ADSPPM_THERM_NPA_MITIGATE_H

/*============================================================================
  FILE:         therm_npa_mitigate.h
  
  OVERVIEW:     Thermal NPA mitigation resources header file.
 
              
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

============================================================================*/
/*=======================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/inc/thermal/adsppm_therm_npa_mitigate.h#1 $
$DateTime: 2020/02/10 01:57:30 $
$Author: pwbldsvc $
========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "comdef.h"

/*
===============================================================================

                             TYPE DEFINITION(S)

===============================================================================
*/

#define LPICX_NODE_NAME "/vdd/lpicx"
#define LPICX_ADSPPM_CLIENT_NAME "adsppmLpiCx"

/*
===============================================================================

                           GLOBAL FUNCTION DECLARATIONS

===============================================================================
*/

/**
  @brief adsppm_therm_npa_mitigate_init

  Thermal mitigate init function.
*/
void adsppm_therm_npa_mitigate_init( void );


#ifdef __cplusplus
}
#endif

#endif /* THERM_NPA_MITIGATE_H */
