#ifndef __QDSS_HWIO_H__
#define __QDSS_HWIO_H__
/*
===========================================================================
*/
/**
  @file qdss_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    QDSS_QDSS_QDSSCSR

  'Include' filters applied: QDSSCLKVOTE 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/rpm.bf/1.8/core/power/rpm/inc/target/660/qdss_hwio.h#2 $
  $DateTime: 2016/11/07 22:46:44 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"



/*----------------------------------------------------------------------------
 * MODULE: QDSS_QDSS_QDSSCSR
 *--------------------------------------------------------------------------*/

#define QDSS_QDSS_QDSSCSR_REG_BASE                                                            (QDSS_SOC_DBG_BASE      + 0x00001000)

#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_ADDR                                            (QDSS_QDSS_QDSSCSR_REG_BASE      + 0x00000058)
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_RMSK                                            0xffffffff
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_IN          \
        in_dword_masked(HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_ADDR, HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_RMSK)
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_INM(m)      \
        in_dword_masked(HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_ADDR, m)
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_OUT(v)      \
        out_dword(HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_ADDR,v)
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_ADDR,m,v,HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_IN)
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_CLKVOTE_BMSK                                    0xffffffff
#define HWIO_QDSS_QDSS_CS_QDSSCSR_QDSSCLKVOTE_CLKVOTE_SHFT                                           0x0


#endif /* __QDSS_HWIO_H__ */
