#ifndef PM_NPA_DEVICE_BOOST__H
#define PM_NPA_DEVICE_BOOST__H
/*===========================================================================


P M    N P A   BOOST D E V I C E    H E A D E R    F I L E

DESCRIPTION
This file contains prototype definitions npa device layer

Copyright (c) 2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.



when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
01/29/13   aks     Adding support for Boost as separate peripheral 
===========================================================================*/

/*===========================================================================

INCLUDE FILES

===========================================================================*/

#include "pm_npa_device.h"


/*===========================================================================

TYPE DEFINITIONS

===========================================================================*/
typedef struct  
{
    // [Disable (default), Enable] — max aggregation (left to right)
    unsigned sw_enable_key; // PM_NPA_KEY_SOFTWARE_ENABLE
    unsigned sw_enable_size; // 4
    unsigned sw_enable_value;

}pm_npa_boost_kvps;

extern npa_resource_plugin pm_npa_boost_kvps_plugin;


#define PMIC_DEV_RMT_RSRC_BOOST( chipid, rtype, index, rpm_name_index )   \
{                                                                        \
    PMIC_DEV_RSRC_NAME_VEC_IN( chipid, rtype, index ),                   \
    rpm_name_index,                                                      \
    PMIC_NPA_RMT_PROTOCOL_RPM_TYPE,                                      \
    &pm_npa_boost_kvps_plugin,                                            \
    npa_remote_resource_local_aggregation_no_initial_request_driver_fcn, \
    "kvps",                                                              \
    sizeof(pm_npa_boost_kvps)/sizeof(npa_resource_state),                 \
    NPA_RESOURCE_VECTOR_STATE                                            \
}


#endif // PM_NPA_DEVICE_BOOST__H

