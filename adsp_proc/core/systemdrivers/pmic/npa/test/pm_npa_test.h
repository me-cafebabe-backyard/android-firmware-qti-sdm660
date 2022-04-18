#ifndef PM_NPA_TEST_H
#define PM_NPA_TEST_H
/*===========================================================================

                  PM NPA TEST HEADER FILE

DESCRIPTION
  This file contains prototype definition for PMIC NPA test initialization.

Copyright (c) 2015 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/pmic/npa/test/pm_npa_test.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/18/15   pb      Added pm_npa.h to suppress compilation error
05/06/15   va      Ported from MPSS.
===========================================================================*/

#include "pm_npa.h"

/*===========================================================================

                        GLOBAL VARIABLES

===========================================================================*/

// The following are assigned values in pm_npa_test.c

extern char *rsrc_test_name;
extern unsigned num_of_test_nodes; //Need this for APT test if using test client
extern pm_npa_node_resource_info *node_rsrc_arr; //Need this for APT test if using test client

/*===========================================================================

                        GENERIC FUNCTION PROTOTYPES

===========================================================================*/
/** 
 * @name pm_npa_test_init 
 *  
 * @brief This initialization function is called to test
 *        PMIC NPA clients.This function creates the PMIC
 *        NPA test resources using the existing PMIC NPA
 *        client's static data but with a slightly
 *        different resource name or group id (using which
 *        the NPA request is usually made).
 * 
 *        For example, resource name for UIM1_ENABLE client
 *        is "/pmic/client/uim1_enable" (Refer to pmapp_npa.h
 *        public header) but the corresponding test client
 *        resource name would be "/pmic/tst_cl/uim1_enable"
 *        using which the NPA test request has to be made.
 * 
 * @param None
 *
 * @return None
 *
 */
void pm_npa_test_init(void);

#endif /* PM_NPA_TEST_H */
