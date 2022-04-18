#ifndef QDSS_CSR_CONFIG_H
#define QDSS_CSR_CONFIG_H

/*=============================================================================

FILE:         qdss_csr_config.h

DESCRIPTION:  

================================================================================
              Copyright (c) 2015 Qualcomm Technologies, Inc.
                         All Rights Reserved.
                QUALCOMM Proprietary and Confidential
==============================================================================*/


#define QDSS_QDSSCSR_REG_BASE_PHYS      (0x66001000) 


//These are not used any more.
//Debug agent is the preferred way to enable 
//HW events on boot-up. In
#define HWEVENT_MUX_CTRL_0 0x0
#define HWEVENT_MUX_CTRL_1 0x0
#define HWEVENT_MUX_CTRL_2 0x0
#define HWEVENT_MUX_CTRL_3 0x0

// STMAWID_DEFAULT   0
// STMAWID_BAMDMA    28
// STMAWID_RESERVED  3

#define QDSS_CSR_STMAWID_ASSIGNMENTS       0x03020100  
#define QDSS_CSR_STM_BURST_TRANSALATORS    0x0  //Disable everything by default


#endif //QDSS_CSR_CONFIG_H
