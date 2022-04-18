#ifndef __RPM_IPC_H__
#define __RPM_IPC_H__
/*
===========================================================================
*/
/**
  @file rpm_ipc.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    RPM_DEC

  'Include' filters applied: RPM_IPC[RPM_DEC] 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/rpm.bf/1.8/core/dal/framework/sys/src/rpm/rpm_ipc.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: RPM_DEC
 *--------------------------------------------------------------------------*/

#define RPM_DEC_REG_BASE                                                 (RPM_BASE      + 0x00080000)

#define HWIO_RPM_IPC_ADDR                                                (RPM_DEC_REG_BASE      + 0x0000000c)
#define HWIO_RPM_IPC_RMSK                                                0xffffffff
#define HWIO_RPM_IPC_OUT(v)      \
        out_dword(HWIO_RPM_IPC_ADDR,v)
#define HWIO_RPM_IPC_RSRV_IPC_BMSK                                       0xf0000000
#define HWIO_RPM_IPC_RSRV_IPC_SHFT                                             0x1c
#define HWIO_RPM_IPC_APCS_TZ_IPC_BMSK                                     0xf000000
#define HWIO_RPM_IPC_APCS_TZ_IPC_SHFT                                          0x18
#define HWIO_RPM_IPC_SPARE_IPC_BMSK                                        0xf00000
#define HWIO_RPM_IPC_SPARE_IPC_SHFT                                            0x14
#define HWIO_RPM_IPC_WCN_IPC_BMSK                                           0xf0000
#define HWIO_RPM_IPC_WCN_IPC_SHFT                                              0x10
#define HWIO_RPM_IPC_MPSS_IPC_BMSK                                           0xf000
#define HWIO_RPM_IPC_MPSS_IPC_SHFT                                              0xc
#define HWIO_RPM_IPC_ADSP_IPC_BMSK                                            0xf00
#define HWIO_RPM_IPC_ADSP_IPC_SHFT                                              0x8
#define HWIO_RPM_IPC_APCS_HLOS_IPC_BMSK                                        0xf0
#define HWIO_RPM_IPC_APCS_HLOS_IPC_SHFT                                         0x4
#define HWIO_RPM_IPC_RPM_RSRV_BMSK                                              0xf
#define HWIO_RPM_IPC_RPM_RSRV_SHFT                                              0x0


#endif /* __RPM_IPC_H__ */

