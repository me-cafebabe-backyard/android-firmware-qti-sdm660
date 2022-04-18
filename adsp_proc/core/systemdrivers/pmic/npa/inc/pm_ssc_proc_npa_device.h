#ifndef PM_SSC_PROC_NPA_DEVICE_H
#define PM_SSC_PROC_NPA_DEVICE_H

/*! \file
 *  
 *  \brief  pm_ssc_proc_npa_device.h ----This file contains prototype definitions npa device layer
 *  \details This file contains prototype definitions npa device layer
 *          and the #DEFINE for the devices
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation NPA Client Version: MSM8x26_PM8026_NPA_2012_10_19 - Approved
 *    PMIC code generation NPA Device Setting Value Version: MSM8x26_PM8026_NPA_2012_10_19 - Approved
 *    This file contains code for Target specific settings and modes.
 *  
 * Copyright (c) 2010-2015 Qualcomm Technologies, Inc.
 *        All Rights Reserved.
 * Qualcomm Technologies, Inc. Confidential and Proprietary.
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/pmic/npa/inc/pm_ssc_proc_npa_device.h#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_lib_api.h"         /* interface files for all library APIs */
#include "npa.h"
#include "npa_resource.h"

/* Device Remote Resource */
//#define PMIC_NPA_RMT_PROTOCOL_RPM_TYPE    "/protocol/rpm/rpm"

/*===========================================================================

FUNCTION pm_ssc_proc_npa_init

DESCRIPTION
    This function initializes the NPA for ssc.

    It does the following:
    1)  It initializes the PMIC NPA software driver for nodes and resources.

INPUT PARAMETERS
  None.

RETURN VALUE
  None.

DEPENDENCIES
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void pm_ssc_proc_npa_device_init(void);


#endif //PM_SSC_PROC_NPA_DEVICE_H


