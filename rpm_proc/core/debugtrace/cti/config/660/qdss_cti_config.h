#ifndef QDSS_CTI_CONFIG_H
#define QDSS_CTI_CONFIG_H

/*=============================================================================

FILE:         qdss_cti_config.h

DESCRIPTION:  

================================================================================
              Copyright (c) 2015 Qualcomm Technologies, Inc.
                         All Rights Reserved.
                QUALCOMM Proprietary and Confidential
==============================================================================*/


#define QDSS_CTI0_BASE_PHYS      (0x66010000) 

//CTIs of cores that needs to be halted with trigger
//This table is not used by default.
#define QDSS_ADSP_CTI_BASE_PHYS        (0x67044000) 
#define QDSS_RPM_CTI_BASE_PHYS         (0x67048000) 


#define CPU_DSP_CTIS {                         \
         QDSS_ADSP_CTI_BASE_PHYS,              \
         QDSS_RPM_CTI_BASE_PHYS,               \
         }

#endif //QDSS_CTI_CONFIG_H
