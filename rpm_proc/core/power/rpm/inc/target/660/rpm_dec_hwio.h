#ifndef __RPM_DEC_HWIO_H__
#define __RPM_DEC_HWIO_H__
/*
===========================================================================
*/
/**
  @file rpm_dec_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    RPM_DEC

  'Include' filters applied: PAGE_SELECT[RPM_DEC] 
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

  $Header: //components/rel/rpm.bf/1.8/core/power/rpm/inc/target/660/rpm_dec_hwio.h#2 $
  $DateTime: 2016/11/07 22:46:44 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"



/*----------------------------------------------------------------------------
 * MODULE: RPM_DEC
 *--------------------------------------------------------------------------*/

#define RPM_DEC_REG_BASE                                                    (RPM_BASE      + 0x00080000)

#define HWIO_RPM_PAGE_SELECT_ADDR                                           (RPM_DEC_REG_BASE      + 0x00000070)
#define HWIO_RPM_PAGE_SELECT_RMSK                                                 0x3f
#define HWIO_RPM_PAGE_SELECT_IN          \
        in_dword_masked(HWIO_RPM_PAGE_SELECT_ADDR, HWIO_RPM_PAGE_SELECT_RMSK)
#define HWIO_RPM_PAGE_SELECT_INM(m)      \
        in_dword_masked(HWIO_RPM_PAGE_SELECT_ADDR, m)
#define HWIO_RPM_PAGE_SELECT_OUT(v)      \
        out_dword(HWIO_RPM_PAGE_SELECT_ADDR,v)
#define HWIO_RPM_PAGE_SELECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_PAGE_SELECT_ADDR,m,v,HWIO_RPM_PAGE_SELECT_IN)
#define HWIO_RPM_PAGE_SELECT_PAGE_SELECT_BMSK                                     0x3f
#define HWIO_RPM_PAGE_SELECT_PAGE_SELECT_SHFT                                      0x0


#endif /* __RPM_DEC_HWIO_H__ */
