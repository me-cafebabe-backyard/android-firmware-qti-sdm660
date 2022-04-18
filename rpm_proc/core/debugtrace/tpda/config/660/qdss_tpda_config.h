#ifndef QDSS_TPDA_CONFIG_H
#define QDSS_TPDA_CONFIG_H

/*=============================================================================

FILE:         qdss_tpda_config.h

DESCRIPTION:  

================================================================================
            Copyright (c) 2014 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/



#define  QDSS_QDSS_TPDA      	0x66004000	 
#define  QDSS_APPS_TPDA      	0x67bc2000

#define QDSS_TPDA_BASE_ADDRS {                  \
      QDSS_QDSS_TPDA,                           \
         QDSS_APPS_TPDA                         \
         }



#endif //QDSS_TPDA_CONFIG_H
