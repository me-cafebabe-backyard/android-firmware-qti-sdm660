#ifndef __QSPI_HWIO_H__
#define __QSPI_HWIO_H__
/*
===========================================================================
*/
/**
  @file qspi_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q3r93_BTO]
 
  This file contains HWIO register definitions for the following modules:
    QSPI

  'Include' filters applied: 
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/QuadSpiLib/qspi_hwio.h#1 $
  $DateTime: 2016/11/15 03:34:31 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include <..\Sdm660Pkg\Include\msmhwiobase.h>

/*----------------------------------------------------------------------------
 * MODULE: QSPI
 *--------------------------------------------------------------------------*/

#define QSPI_REG_BASE                                                                   (QSPI_BASE      + 0x00000000)
#define QSPI_REG_BASE_OFFS                                                              0x00000000

#define HWIO_QSPI_MSTR_CONFIG_ADDR                                                      (QSPI_REG_BASE      + 0x00000000)
#define HWIO_QSPI_MSTR_CONFIG_OFFS                                                      (QSPI_REG_BASE_OFFS + 0x00000000)
#define HWIO_QSPI_MSTR_CONFIG_RMSK                                                       0x3ffffd8
#define HWIO_QSPI_MSTR_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_MSTR_CONFIG_ADDR, HWIO_QSPI_MSTR_CONFIG_RMSK)
#define HWIO_QSPI_MSTR_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_MSTR_CONFIG_ADDR, m)
#define HWIO_QSPI_MSTR_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_MSTR_CONFIG_ADDR,v)
#define HWIO_QSPI_MSTR_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_MSTR_CONFIG_ADDR,m,v,HWIO_QSPI_MSTR_CONFIG_IN)
#define HWIO_QSPI_MSTR_CONFIG_TX_DATA_OE_DELAY_BMSK                                      0x3000000
#define HWIO_QSPI_MSTR_CONFIG_TX_DATA_OE_DELAY_SHFT                                           0x18
#define HWIO_QSPI_MSTR_CONFIG_TX_CS_N_DELAY_BMSK                                          0xc00000
#define HWIO_QSPI_MSTR_CONFIG_TX_CS_N_DELAY_SHFT                                              0x16
#define HWIO_QSPI_MSTR_CONFIG_TX_CLK_DELAY_BMSK                                           0x300000
#define HWIO_QSPI_MSTR_CONFIG_TX_CLK_DELAY_SHFT                                               0x14
#define HWIO_QSPI_MSTR_CONFIG_TX_DATA_DELAY_BMSK                                           0xc0000
#define HWIO_QSPI_MSTR_CONFIG_TX_DATA_DELAY_SHFT                                              0x12
#define HWIO_QSPI_MSTR_CONFIG_LPA_BASE_BMSK                                                0x3c000
#define HWIO_QSPI_MSTR_CONFIG_LPA_BASE_SHFT                                                    0xe
#define HWIO_QSPI_MSTR_CONFIG_SBL_EN_BMSK                                                   0x2000
#define HWIO_QSPI_MSTR_CONFIG_SBL_EN_SHFT                                                      0xd
#define HWIO_QSPI_MSTR_CONFIG_CHIP_SELECT_NUM_BMSK                                          0x1000
#define HWIO_QSPI_MSTR_CONFIG_CHIP_SELECT_NUM_SHFT                                             0xc
#define HWIO_QSPI_MSTR_CONFIG_SPI_MODE_BMSK                                                  0xc00
#define HWIO_QSPI_MSTR_CONFIG_SPI_MODE_SHFT                                                    0xa
#define HWIO_QSPI_MSTR_CONFIG_BIG_ENDIAN_MODE_BMSK                                           0x200
#define HWIO_QSPI_MSTR_CONFIG_BIG_ENDIAN_MODE_SHFT                                             0x9
#define HWIO_QSPI_MSTR_CONFIG_DMA_ENABLE_BMSK                                                0x100
#define HWIO_QSPI_MSTR_CONFIG_DMA_ENABLE_SHFT                                                  0x8
#define HWIO_QSPI_MSTR_CONFIG_PIN_WPN_BMSK                                                    0x80
#define HWIO_QSPI_MSTR_CONFIG_PIN_WPN_SHFT                                                     0x7
#define HWIO_QSPI_MSTR_CONFIG_PIN_HOLDN_BMSK                                                  0x40
#define HWIO_QSPI_MSTR_CONFIG_PIN_HOLDN_SHFT                                                   0x6
#define HWIO_QSPI_MSTR_CONFIG_FB_CLK_EN_BMSK                                                  0x10
#define HWIO_QSPI_MSTR_CONFIG_FB_CLK_EN_SHFT                                                   0x4
#define HWIO_QSPI_MSTR_CONFIG_FULL_CYCLE_MODE_BMSK                                             0x8
#define HWIO_QSPI_MSTR_CONFIG_FULL_CYCLE_MODE_SHFT                                             0x3

#define HWIO_QSPI_AHB_MASTER_CFG_ADDR                                                   (QSPI_REG_BASE      + 0x00000004)
#define HWIO_QSPI_AHB_MASTER_CFG_OFFS                                                   (QSPI_REG_BASE_OFFS + 0x00000004)
#define HWIO_QSPI_AHB_MASTER_CFG_RMSK                                                       0x3fff
#define HWIO_QSPI_AHB_MASTER_CFG_IN          \
        in_dword_masked(HWIO_QSPI_AHB_MASTER_CFG_ADDR, HWIO_QSPI_AHB_MASTER_CFG_RMSK)
#define HWIO_QSPI_AHB_MASTER_CFG_INM(m)      \
        in_dword_masked(HWIO_QSPI_AHB_MASTER_CFG_ADDR, m)
#define HWIO_QSPI_AHB_MASTER_CFG_OUT(v)      \
        out_dword(HWIO_QSPI_AHB_MASTER_CFG_ADDR,v)
#define HWIO_QSPI_AHB_MASTER_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_AHB_MASTER_CFG_ADDR,m,v,HWIO_QSPI_AHB_MASTER_CFG_IN)
#define HWIO_QSPI_AHB_MASTER_CFG_DMA_DONE_WAIT4RDY_DISABLE_BMSK                             0x2000
#define HWIO_QSPI_AHB_MASTER_CFG_DMA_DONE_WAIT4RDY_DISABLE_SHFT                                0xd
#define HWIO_QSPI_AHB_MASTER_CFG_HINNERSHARED_BMSK                                          0x1000
#define HWIO_QSPI_AHB_MASTER_CFG_HINNERSHARED_SHFT                                             0xc
#define HWIO_QSPI_AHB_MASTER_CFG_HSHARED_BMSK                                                0x800
#define HWIO_QSPI_AHB_MASTER_CFG_HSHARED_SHFT                                                  0xb
#define HWIO_QSPI_AHB_MASTER_CFG_HMEMTYPE_READ_TRANS_BMSK                                    0x700
#define HWIO_QSPI_AHB_MASTER_CFG_HMEMTYPE_READ_TRANS_SHFT                                      0x8
#define HWIO_QSPI_AHB_MASTER_CFG_USE_HMEMTYPE_LAST_ON_DESC_OR_CHAIN_BMSK                      0xc0
#define HWIO_QSPI_AHB_MASTER_CFG_USE_HMEMTYPE_LAST_ON_DESC_OR_CHAIN_SHFT                       0x6
#define HWIO_QSPI_AHB_MASTER_CFG_HMEMTYPE_LAST_TRANS_BMSK                                     0x38
#define HWIO_QSPI_AHB_MASTER_CFG_HMEMTYPE_LAST_TRANS_SHFT                                      0x3
#define HWIO_QSPI_AHB_MASTER_CFG_HMEMTYPE_START_MID_TRANS_BMSK                                 0x7
#define HWIO_QSPI_AHB_MASTER_CFG_HMEMTYPE_START_MID_TRANS_SHFT                                 0x0

#define HWIO_QSPI_MSTR_INT_ENABLE_ADDR                                                  (QSPI_REG_BASE      + 0x0000000c)
#define HWIO_QSPI_MSTR_INT_ENABLE_OFFS                                                  (QSPI_REG_BASE_OFFS + 0x0000000c)
#define HWIO_QSPI_MSTR_INT_ENABLE_RMSK                                                  0xf0030e0f
#define HWIO_QSPI_MSTR_INT_ENABLE_IN          \
        in_dword_masked(HWIO_QSPI_MSTR_INT_ENABLE_ADDR, HWIO_QSPI_MSTR_INT_ENABLE_RMSK)
#define HWIO_QSPI_MSTR_INT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_QSPI_MSTR_INT_ENABLE_ADDR, m)
#define HWIO_QSPI_MSTR_INT_ENABLE_OUT(v)      \
        out_dword(HWIO_QSPI_MSTR_INT_ENABLE_ADDR,v)
#define HWIO_QSPI_MSTR_INT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_MSTR_INT_ENABLE_ADDR,m,v,HWIO_QSPI_MSTR_INT_ENABLE_IN)
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_DMA_CHAIN_DONE_BMSK                                0x80000000
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_DMA_CHAIN_DONE_SHFT                                      0x1f
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_XIP_ACCESS_DURING_DMA_BMSK                         0x40000000
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_XIP_ACCESS_DURING_DMA_SHFT                               0x1e
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_XIP_ACCESS_UNMAPPED_SEGMENT_BMSK                   0x20000000
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_XIP_ACCESS_UNMAPPED_SEGMENT_SHFT                         0x1d
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_XIP_ACCESS_NOT_ENABLE_BMSK                         0x10000000
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_XIP_ACCESS_NOT_ENABLE_SHFT                               0x1c
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_DMA_ACCESS_DURING_XIP_BMSK                            0x20000
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_DMA_ACCESS_DURING_XIP_SHFT                               0x11
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_TRANSACTION_DONE_BMSK                                 0x10000
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_TRANSACTION_DONE_SHFT                                    0x10
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_WRITE_FIFO_OVERRUN_BMSK                                 0x800
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_WRITE_FIFO_OVERRUN_SHFT                                   0xb
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_WRITE_FIFO_FULL_BMSK                                    0x400
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_WRITE_FIFO_FULL_SHFT                                      0xa
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_WRITE_FIFO_EMPTY_BMSK                                   0x200
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_WRITE_FIFO_EMPTY_SHFT                                     0x9
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_HRESP_FROM_NOC_ERR_BMSK                                   0x8
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_HRESP_FROM_NOC_ERR_SHFT                                   0x3
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_RESP_FIFO_RDY_BMSK                                        0x4
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_RESP_FIFO_RDY_SHFT                                        0x2
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_RESP_FIFO_NOT_EMPTY_BMSK                                  0x2
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_RESP_FIFO_NOT_EMPTY_SHFT                                  0x1
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_RESP_FIFO_UNDERRUN_BMSK                                   0x1
#define HWIO_QSPI_MSTR_INT_ENABLE_EN_RESP_FIFO_UNDERRUN_SHFT                                   0x0

#define HWIO_QSPI_MSTR_INT_STATUS_ADDR                                                  (QSPI_REG_BASE      + 0x00000010)
#define HWIO_QSPI_MSTR_INT_STATUS_OFFS                                                  (QSPI_REG_BASE_OFFS + 0x00000010)
#define HWIO_QSPI_MSTR_INT_STATUS_RMSK                                                  0xf8030e0f
#define HWIO_QSPI_MSTR_INT_STATUS_IN          \
        in_dword_masked(HWIO_QSPI_MSTR_INT_STATUS_ADDR, HWIO_QSPI_MSTR_INT_STATUS_RMSK)
#define HWIO_QSPI_MSTR_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_QSPI_MSTR_INT_STATUS_ADDR, m)
#define HWIO_QSPI_MSTR_INT_STATUS_OUT(v)      \
        out_dword(HWIO_QSPI_MSTR_INT_STATUS_ADDR,v)
#define HWIO_QSPI_MSTR_INT_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_MSTR_INT_STATUS_ADDR,m,v,HWIO_QSPI_MSTR_INT_STATUS_IN)
#define HWIO_QSPI_MSTR_INT_STATUS_DMA_CHAIN_DONE_BMSK                                   0x80000000
#define HWIO_QSPI_MSTR_INT_STATUS_DMA_CHAIN_DONE_SHFT                                         0x1f
#define HWIO_QSPI_MSTR_INT_STATUS_XIP_ACCESS_DURING_DMA_BMSK                            0x40000000
#define HWIO_QSPI_MSTR_INT_STATUS_XIP_ACCESS_DURING_DMA_SHFT                                  0x1e
#define HWIO_QSPI_MSTR_INT_STATUS_XIP_ACCESS_UNMAPPED_SEGMENT_BMSK                      0x20000000
#define HWIO_QSPI_MSTR_INT_STATUS_XIP_ACCESS_UNMAPPED_SEGMENT_SHFT                            0x1d
#define HWIO_QSPI_MSTR_INT_STATUS_XIP_ACCESS_NOT_ENABLE_BMSK                            0x10000000
#define HWIO_QSPI_MSTR_INT_STATUS_XIP_ACCESS_NOT_ENABLE_SHFT                                  0x1c
#define HWIO_QSPI_MSTR_INT_STATUS_DMA_STATUS_BMSK                                        0x8000000
#define HWIO_QSPI_MSTR_INT_STATUS_DMA_STATUS_SHFT                                             0x1b
#define HWIO_QSPI_MSTR_INT_STATUS_DMA_ACCESS_DURING_XIP_BMSK                               0x20000
#define HWIO_QSPI_MSTR_INT_STATUS_DMA_ACCESS_DURING_XIP_SHFT                                  0x11
#define HWIO_QSPI_MSTR_INT_STATUS_TRANSACTION_DONE_BMSK                                    0x10000
#define HWIO_QSPI_MSTR_INT_STATUS_TRANSACTION_DONE_SHFT                                       0x10
#define HWIO_QSPI_MSTR_INT_STATUS_WRITE_FIFO_OVERRUN_BMSK                                    0x800
#define HWIO_QSPI_MSTR_INT_STATUS_WRITE_FIFO_OVERRUN_SHFT                                      0xb
#define HWIO_QSPI_MSTR_INT_STATUS_WRITE_FIFO_FULL_BMSK                                       0x400
#define HWIO_QSPI_MSTR_INT_STATUS_WRITE_FIFO_FULL_SHFT                                         0xa
#define HWIO_QSPI_MSTR_INT_STATUS_WRITE_FIFO_EMPTY_BMSK                                      0x200
#define HWIO_QSPI_MSTR_INT_STATUS_WRITE_FIFO_EMPTY_SHFT                                        0x9
#define HWIO_QSPI_MSTR_INT_STATUS_HRESP_FROM_NOC_ERR_BMSK                                      0x8
#define HWIO_QSPI_MSTR_INT_STATUS_HRESP_FROM_NOC_ERR_SHFT                                      0x3
#define HWIO_QSPI_MSTR_INT_STATUS_RESP_FIFO_RDY_BMSK                                           0x4
#define HWIO_QSPI_MSTR_INT_STATUS_RESP_FIFO_RDY_SHFT                                           0x2
#define HWIO_QSPI_MSTR_INT_STATUS_RESP_FIFO_NOT_EMPTY_BMSK                                     0x2
#define HWIO_QSPI_MSTR_INT_STATUS_RESP_FIFO_NOT_EMPTY_SHFT                                     0x1
#define HWIO_QSPI_MSTR_INT_STATUS_RESP_FIFO_UNDERRUN_BMSK                                      0x1
#define HWIO_QSPI_MSTR_INT_STATUS_RESP_FIFO_UNDERRUN_SHFT                                      0x0

#define HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR                                             (QSPI_REG_BASE      + 0x00000014)
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_OFFS                                             (QSPI_REG_BASE_OFFS + 0x00000014)
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_RMSK                                                 0xffff
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_IN          \
        in_dword_masked(HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR, HWIO_QSPI_PIO_TRANSFER_CONTROL_RMSK)
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_INM(m)      \
        in_dword_masked(HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR, m)
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_OUT(v)      \
        out_dword(HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR,v)
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_PIO_TRANSFER_CONTROL_ADDR,m,v,HWIO_QSPI_PIO_TRANSFER_CONTROL_IN)
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_REQUEST_COUNT_BMSK                                   0xffff
#define HWIO_QSPI_PIO_TRANSFER_CONTROL_REQUEST_COUNT_SHFT                                      0x0

#define HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR                                              (QSPI_REG_BASE      + 0x00000018)
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_OFFS                                              (QSPI_REG_BASE_OFFS + 0x00000018)
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_RMSK                                                   0x10f
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR, HWIO_QSPI_PIO_TRANSFER_CONFIG_RMSK)
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR, m)
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR,v)
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_PIO_TRANSFER_CONFIG_ADDR,m,v,HWIO_QSPI_PIO_TRANSFER_CONFIG_IN)
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_FRAGMENT_BMSK                                 0x100
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_FRAGMENT_SHFT                                   0x8
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_MULTI_IO_MODE_BMSK                                       0xe
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_MULTI_IO_MODE_SHFT                                       0x1
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_DIRECTION_BMSK                                  0x1
#define HWIO_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_DIRECTION_SHFT                                  0x0

#define HWIO_QSPI_PIO_TRANSFER_STATUS_ADDR                                              (QSPI_REG_BASE      + 0x0000001c)
#define HWIO_QSPI_PIO_TRANSFER_STATUS_OFFS                                              (QSPI_REG_BASE_OFFS + 0x0000001c)
#define HWIO_QSPI_PIO_TRANSFER_STATUS_RMSK                                              0xffff0000
#define HWIO_QSPI_PIO_TRANSFER_STATUS_IN          \
        in_dword_masked(HWIO_QSPI_PIO_TRANSFER_STATUS_ADDR, HWIO_QSPI_PIO_TRANSFER_STATUS_RMSK)
#define HWIO_QSPI_PIO_TRANSFER_STATUS_INM(m)      \
        in_dword_masked(HWIO_QSPI_PIO_TRANSFER_STATUS_ADDR, m)
#define HWIO_QSPI_PIO_TRANSFER_STATUS_WR_FIFO_BYTES_BMSK                                0xffff0000
#define HWIO_QSPI_PIO_TRANSFER_STATUS_WR_FIFO_BYTES_SHFT                                      0x10

#define HWIO_QSPI_PIO_DATAOUT_1BYTE_ADDR                                                (QSPI_REG_BASE      + 0x00000020)
#define HWIO_QSPI_PIO_DATAOUT_1BYTE_OFFS                                                (QSPI_REG_BASE_OFFS + 0x00000020)
#define HWIO_QSPI_PIO_DATAOUT_1BYTE_RMSK                                                      0xff
#define HWIO_QSPI_PIO_DATAOUT_1BYTE_OUT(v)      \
        out_dword(HWIO_QSPI_PIO_DATAOUT_1BYTE_ADDR,v)
#define HWIO_QSPI_PIO_DATAOUT_1BYTE_DATAIN_BMSK                                               0xff
#define HWIO_QSPI_PIO_DATAOUT_1BYTE_DATAIN_SHFT                                                0x0

#define HWIO_QSPI_PIO_DATAOUT_4BYTE_ADDR                                                (QSPI_REG_BASE      + 0x00000024)
#define HWIO_QSPI_PIO_DATAOUT_4BYTE_OFFS                                                (QSPI_REG_BASE_OFFS + 0x00000024)
#define HWIO_QSPI_PIO_DATAOUT_4BYTE_RMSK                                                0xffffffff
#define HWIO_QSPI_PIO_DATAOUT_4BYTE_OUT(v)      \
        out_dword(HWIO_QSPI_PIO_DATAOUT_4BYTE_ADDR,v)
#define HWIO_QSPI_PIO_DATAOUT_4BYTE_DATAIN_BMSK                                         0xffffffff
#define HWIO_QSPI_PIO_DATAOUT_4BYTE_DATAIN_SHFT                                                0x0

#define HWIO_QSPI_RD_FIFO_CONFIG_ADDR                                                   (QSPI_REG_BASE      + 0x00000028)
#define HWIO_QSPI_RD_FIFO_CONFIG_OFFS                                                   (QSPI_REG_BASE_OFFS + 0x00000028)
#define HWIO_QSPI_RD_FIFO_CONFIG_RMSK                                                          0x1
#define HWIO_QSPI_RD_FIFO_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_RD_FIFO_CONFIG_ADDR, HWIO_QSPI_RD_FIFO_CONFIG_RMSK)
#define HWIO_QSPI_RD_FIFO_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_RD_FIFO_CONFIG_ADDR, m)
#define HWIO_QSPI_RD_FIFO_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_RD_FIFO_CONFIG_ADDR,v)
#define HWIO_QSPI_RD_FIFO_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_RD_FIFO_CONFIG_ADDR,m,v,HWIO_QSPI_RD_FIFO_CONFIG_IN)
#define HWIO_QSPI_RD_FIFO_CONFIG_CONTINUOUS_MODE_BMSK                                          0x1
#define HWIO_QSPI_RD_FIFO_CONFIG_CONTINUOUS_MODE_SHFT                                          0x0

#define HWIO_QSPI_RD_FIFO_STATUS_ADDR                                                   (QSPI_REG_BASE      + 0x0000002c)
#define HWIO_QSPI_RD_FIFO_STATUS_OFFS                                                   (QSPI_REG_BASE_OFFS + 0x0000002c)
#define HWIO_QSPI_RD_FIFO_STATUS_RMSK                                                        0xfff
#define HWIO_QSPI_RD_FIFO_STATUS_IN          \
        in_dword_masked(HWIO_QSPI_RD_FIFO_STATUS_ADDR, HWIO_QSPI_RD_FIFO_STATUS_RMSK)
#define HWIO_QSPI_RD_FIFO_STATUS_INM(m)      \
        in_dword_masked(HWIO_QSPI_RD_FIFO_STATUS_ADDR, m)
#define HWIO_QSPI_RD_FIFO_STATUS_FIFO_EMPTY_BMSK                                             0x800
#define HWIO_QSPI_RD_FIFO_STATUS_FIFO_EMPTY_SHFT                                               0xb
#define HWIO_QSPI_RD_FIFO_STATUS_WR_CNTS_BMSK                                                0x7f0
#define HWIO_QSPI_RD_FIFO_STATUS_WR_CNTS_SHFT                                                  0x4
#define HWIO_QSPI_RD_FIFO_STATUS_RDY_64BYTE_BMSK                                               0x8
#define HWIO_QSPI_RD_FIFO_STATUS_RDY_64BYTE_SHFT                                               0x3
#define HWIO_QSPI_RD_FIFO_STATUS_RDY_32BYTE_BMSK                                               0x4
#define HWIO_QSPI_RD_FIFO_STATUS_RDY_32BYTE_SHFT                                               0x2
#define HWIO_QSPI_RD_FIFO_STATUS_RDY_16BYTE_BMSK                                               0x2
#define HWIO_QSPI_RD_FIFO_STATUS_RDY_16BYTE_SHFT                                               0x1
#define HWIO_QSPI_RD_FIFO_STATUS_FIFO_RDY_BMSK                                                 0x1
#define HWIO_QSPI_RD_FIFO_STATUS_FIFO_RDY_SHFT                                                 0x0

#define HWIO_QSPI_RD_FIFO_RESET_ADDR                                                    (QSPI_REG_BASE      + 0x00000030)
#define HWIO_QSPI_RD_FIFO_RESET_OFFS                                                    (QSPI_REG_BASE_OFFS + 0x00000030)
#define HWIO_QSPI_RD_FIFO_RESET_RMSK                                                           0x1
#define HWIO_QSPI_RD_FIFO_RESET_OUT(v)      \
        out_dword(HWIO_QSPI_RD_FIFO_RESET_ADDR,v)
#define HWIO_QSPI_RD_FIFO_RESET_RESET_FIFO_BMSK                                                0x1
#define HWIO_QSPI_RD_FIFO_RESET_RESET_FIFO_SHFT                                                0x0

#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_ADDR                                               (QSPI_REG_BASE      + 0x00000040)
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_OFFS                                               (QSPI_REG_BASE_OFFS + 0x00000040)
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_RMSK                                               0xffffffff
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_IN          \
        in_dword_masked(HWIO_QSPI_NEXT_DMA_DESC_ADDR_ADDR, HWIO_QSPI_NEXT_DMA_DESC_ADDR_RMSK)
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_INM(m)      \
        in_dword_masked(HWIO_QSPI_NEXT_DMA_DESC_ADDR_ADDR, m)
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_OUT(v)      \
        out_dword(HWIO_QSPI_NEXT_DMA_DESC_ADDR_ADDR,v)
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_NEXT_DMA_DESC_ADDR_ADDR,m,v,HWIO_QSPI_NEXT_DMA_DESC_ADDR_IN)
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_DMA_NEXT_DESCRIPTOR_BMSK                           0xffffffff
#define HWIO_QSPI_NEXT_DMA_DESC_ADDR_DMA_NEXT_DESCRIPTOR_SHFT                                  0x0

#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_ADDR                                            (QSPI_REG_BASE      + 0x00000044)
#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_OFFS                                            (QSPI_REG_BASE_OFFS + 0x00000044)
#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_RMSK                                            0xffffffff
#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_IN          \
        in_dword_masked(HWIO_QSPI_CURRENT_DMA_DESC_ADDR_ADDR, HWIO_QSPI_CURRENT_DMA_DESC_ADDR_RMSK)
#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_INM(m)      \
        in_dword_masked(HWIO_QSPI_CURRENT_DMA_DESC_ADDR_ADDR, m)
#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_DMA_CURRENT_DESCRIPTOR_BMSK                     0xffffffff
#define HWIO_QSPI_CURRENT_DMA_DESC_ADDR_DMA_CURRENT_DESCRIPTOR_SHFT                            0x0

#define HWIO_QSPI_CURRENT_MEM_ADDR_ADDR                                                 (QSPI_REG_BASE      + 0x00000048)
#define HWIO_QSPI_CURRENT_MEM_ADDR_OFFS                                                 (QSPI_REG_BASE_OFFS + 0x00000048)
#define HWIO_QSPI_CURRENT_MEM_ADDR_RMSK                                                 0xffffffff
#define HWIO_QSPI_CURRENT_MEM_ADDR_IN          \
        in_dword_masked(HWIO_QSPI_CURRENT_MEM_ADDR_ADDR, HWIO_QSPI_CURRENT_MEM_ADDR_RMSK)
#define HWIO_QSPI_CURRENT_MEM_ADDR_INM(m)      \
        in_dword_masked(HWIO_QSPI_CURRENT_MEM_ADDR_ADDR, m)
#define HWIO_QSPI_CURRENT_MEM_ADDR_DMA_MEM_PTR_BMSK                                     0xffffffff
#define HWIO_QSPI_CURRENT_MEM_ADDR_DMA_MEM_PTR_SHFT                                            0x0

#define HWIO_QSPI_HW_VERSION_ADDR                                                       (QSPI_REG_BASE      + 0x0000004c)
#define HWIO_QSPI_HW_VERSION_OFFS                                                       (QSPI_REG_BASE_OFFS + 0x0000004c)
#define HWIO_QSPI_HW_VERSION_RMSK                                                       0xffffffff
#define HWIO_QSPI_HW_VERSION_IN          \
        in_dword_masked(HWIO_QSPI_HW_VERSION_ADDR, HWIO_QSPI_HW_VERSION_RMSK)
#define HWIO_QSPI_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_QSPI_HW_VERSION_ADDR, m)
#define HWIO_QSPI_HW_VERSION_HW_VERSION_MAJOR_BMSK                                      0xf0000000
#define HWIO_QSPI_HW_VERSION_HW_VERSION_MAJOR_SHFT                                            0x1c
#define HWIO_QSPI_HW_VERSION_HW_VERSION_MINOR_BMSK                                       0xfff0000
#define HWIO_QSPI_HW_VERSION_HW_VERSION_MINOR_SHFT                                            0x10
#define HWIO_QSPI_HW_VERSION_HW_VERSION_STEP_BMSK                                           0xffff
#define HWIO_QSPI_HW_VERSION_HW_VERSION_STEP_SHFT                                              0x0

#define HWIO_QSPI_RD_FIFOn_ADDR(n)                                                      (QSPI_REG_BASE      + 0x00000050 + 0x4 * (n))
#define HWIO_QSPI_RD_FIFOn_OFFS(n)                                                      (QSPI_REG_BASE_OFFS + 0x00000050 + 0x4 * (n))
#define HWIO_QSPI_RD_FIFOn_RMSK                                                         0xffffffff
#define HWIO_QSPI_RD_FIFOn_MAXn                                                                 15
#define HWIO_QSPI_RD_FIFOn_INI(n)        \
        in_dword_masked(HWIO_QSPI_RD_FIFOn_ADDR(n), HWIO_QSPI_RD_FIFOn_RMSK)
#define HWIO_QSPI_RD_FIFOn_INMI(n,mask)    \
        in_dword_masked(HWIO_QSPI_RD_FIFOn_ADDR(n), mask)
#define HWIO_QSPI_RD_FIFOn_QSPI_RD_FIFO_DATA_BMSK                                       0xffffffff
#define HWIO_QSPI_RD_FIFOn_QSPI_RD_FIFO_DATA_SHFT                                              0x0

#define HWIO_QSPI_SAMPLING_CLK_CONFIG_ADDR                                              (QSPI_REG_BASE      + 0x00000090)
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_OFFS                                              (QSPI_REG_BASE_OFFS + 0x00000090)
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_RMSK                                                  0x1fff
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_SAMPLING_CLK_CONFIG_ADDR, HWIO_QSPI_SAMPLING_CLK_CONFIG_RMSK)
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_SAMPLING_CLK_CONFIG_ADDR, m)
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_SAMPLING_CLK_CONFIG_ADDR,v)
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_SAMPLING_CLK_CONFIG_ADDR,m,v,HWIO_QSPI_SAMPLING_CLK_CONFIG_IN)
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_EN_LOAD_CLK_CNTR_BMSK                                 0x1000
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_EN_LOAD_CLK_CNTR_SHFT                                    0xc
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE3_CLK_CNTR_INIT_VAL_BMSK                           0xe00
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE3_CLK_CNTR_INIT_VAL_SHFT                             0x9
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE2_CLK_CNTR_INIT_VAL_BMSK                           0x1c0
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE2_CLK_CNTR_INIT_VAL_SHFT                             0x6
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE1_CLK_CNTR_INIT_VAL_BMSK                            0x38
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE1_CLK_CNTR_INIT_VAL_SHFT                             0x3
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE0_CLK_CNTR_INIT_VAL_BMSK                             0x7
#define HWIO_QSPI_SAMPLING_CLK_CONFIG_LANE0_CLK_CNTR_INIT_VAL_SHFT                             0x0

#define HWIO_QSPI_SAMPLING_CLK_STATUS_ADDR                                              (QSPI_REG_BASE      + 0x00000094)
#define HWIO_QSPI_SAMPLING_CLK_STATUS_OFFS                                              (QSPI_REG_BASE_OFFS + 0x00000094)
#define HWIO_QSPI_SAMPLING_CLK_STATUS_RMSK                                                     0x1
#define HWIO_QSPI_SAMPLING_CLK_STATUS_IN          \
        in_dword_masked(HWIO_QSPI_SAMPLING_CLK_STATUS_ADDR, HWIO_QSPI_SAMPLING_CLK_STATUS_RMSK)
#define HWIO_QSPI_SAMPLING_CLK_STATUS_INM(m)      \
        in_dword_masked(HWIO_QSPI_SAMPLING_CLK_STATUS_ADDR, m)
#define HWIO_QSPI_SAMPLING_CLK_STATUS_LOAD_CLK_CNTR_ACK_BMSK                                   0x1
#define HWIO_QSPI_SAMPLING_CLK_STATUS_LOAD_CLK_CNTR_ACK_SHFT                                   0x0

#define HWIO_QSPI_CHAR_CFG_ADDR                                                         (QSPI_REG_BASE      + 0x00000098)
#define HWIO_QSPI_CHAR_CFG_OFFS                                                         (QSPI_REG_BASE_OFFS + 0x00000098)
#define HWIO_QSPI_CHAR_CFG_RMSK                                                              0x1f1
#define HWIO_QSPI_CHAR_CFG_IN          \
        in_dword_masked(HWIO_QSPI_CHAR_CFG_ADDR, HWIO_QSPI_CHAR_CFG_RMSK)
#define HWIO_QSPI_CHAR_CFG_INM(m)      \
        in_dword_masked(HWIO_QSPI_CHAR_CFG_ADDR, m)
#define HWIO_QSPI_CHAR_CFG_OUT(v)      \
        out_dword(HWIO_QSPI_CHAR_CFG_ADDR,v)
#define HWIO_QSPI_CHAR_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_CHAR_CFG_ADDR,m,v,HWIO_QSPI_CHAR_CFG_IN)
#define HWIO_QSPI_CHAR_CFG_CHAR_STATUS_BMSK                                                  0x1e0
#define HWIO_QSPI_CHAR_CFG_CHAR_STATUS_SHFT                                                    0x5
#define HWIO_QSPI_CHAR_CFG_DIRECTION_BMSK                                                     0x10
#define HWIO_QSPI_CHAR_CFG_DIRECTION_SHFT                                                      0x4
#define HWIO_QSPI_CHAR_CFG_ENABLE_BMSK                                                         0x1
#define HWIO_QSPI_CHAR_CFG_ENABLE_SHFT                                                         0x0

#define HWIO_QSPI_CHAR_DATA_MISOn_ADDR(n)                                               (QSPI_REG_BASE      + 0x0000009c + 0x4 * (n))
#define HWIO_QSPI_CHAR_DATA_MISOn_OFFS(n)                                               (QSPI_REG_BASE_OFFS + 0x0000009c + 0x4 * (n))
#define HWIO_QSPI_CHAR_DATA_MISOn_RMSK                                                      0xffff
#define HWIO_QSPI_CHAR_DATA_MISOn_MAXn                                                           3
#define HWIO_QSPI_CHAR_DATA_MISOn_INI(n)        \
        in_dword_masked(HWIO_QSPI_CHAR_DATA_MISOn_ADDR(n), HWIO_QSPI_CHAR_DATA_MISOn_RMSK)
#define HWIO_QSPI_CHAR_DATA_MISOn_INMI(n,mask)    \
        in_dword_masked(HWIO_QSPI_CHAR_DATA_MISOn_ADDR(n), mask)
#define HWIO_QSPI_CHAR_DATA_MISOn_OUTI(n,val)    \
        out_dword(HWIO_QSPI_CHAR_DATA_MISOn_ADDR(n),val)
#define HWIO_QSPI_CHAR_DATA_MISOn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QSPI_CHAR_DATA_MISOn_ADDR(n),mask,val,HWIO_QSPI_CHAR_DATA_MISOn_INI(n))
#define HWIO_QSPI_CHAR_DATA_MISOn_DIN_ACTUAL_BMSK                                           0xff00
#define HWIO_QSPI_CHAR_DATA_MISOn_DIN_ACTUAL_SHFT                                              0x8
#define HWIO_QSPI_CHAR_DATA_MISOn_DOUT_DATA_DIN_EXP_BMSK                                      0xff
#define HWIO_QSPI_CHAR_DATA_MISOn_DOUT_DATA_DIN_EXP_SHFT                                       0x0

#define HWIO_QSPI_CHAR_DATA_MOSIn_ADDR(n)                                               (QSPI_REG_BASE      + 0x000000ac + 0x4 * (n))
#define HWIO_QSPI_CHAR_DATA_MOSIn_OFFS(n)                                               (QSPI_REG_BASE_OFFS + 0x000000ac + 0x4 * (n))
#define HWIO_QSPI_CHAR_DATA_MOSIn_RMSK                                                     0xfffff
#define HWIO_QSPI_CHAR_DATA_MOSIn_MAXn                                                           3
#define HWIO_QSPI_CHAR_DATA_MOSIn_INI(n)        \
        in_dword_masked(HWIO_QSPI_CHAR_DATA_MOSIn_ADDR(n), HWIO_QSPI_CHAR_DATA_MOSIn_RMSK)
#define HWIO_QSPI_CHAR_DATA_MOSIn_INMI(n,mask)    \
        in_dword_masked(HWIO_QSPI_CHAR_DATA_MOSIn_ADDR(n), mask)
#define HWIO_QSPI_CHAR_DATA_MOSIn_OUTI(n,val)    \
        out_dword(HWIO_QSPI_CHAR_DATA_MOSIn_ADDR(n),val)
#define HWIO_QSPI_CHAR_DATA_MOSIn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QSPI_CHAR_DATA_MOSIn_ADDR(n),mask,val,HWIO_QSPI_CHAR_DATA_MOSIn_INI(n))
#define HWIO_QSPI_CHAR_DATA_MOSIn_DATA_OE_BMSK                                             0xff000
#define HWIO_QSPI_CHAR_DATA_MOSIn_DATA_OE_SHFT                                                 0xc
#define HWIO_QSPI_CHAR_DATA_MOSIn_CHAR_MODE_BMSK                                             0xf00
#define HWIO_QSPI_CHAR_DATA_MOSIn_CHAR_MODE_SHFT                                               0x8
#define HWIO_QSPI_CHAR_DATA_MOSIn_DOUT_DATA_DIN_EXP_BMSK                                      0xff
#define HWIO_QSPI_CHAR_DATA_MOSIn_DOUT_DATA_DIN_EXP_SHFT                                       0x0

#define HWIO_QSPI_CHAR_CS_Nn_ADDR(n)                                                    (QSPI_REG_BASE      + 0x000000bc + 0x4 * (n))
#define HWIO_QSPI_CHAR_CS_Nn_OFFS(n)                                                    (QSPI_REG_BASE_OFFS + 0x000000bc + 0x4 * (n))
#define HWIO_QSPI_CHAR_CS_Nn_RMSK                                                          0xfffff
#define HWIO_QSPI_CHAR_CS_Nn_MAXn                                                                1
#define HWIO_QSPI_CHAR_CS_Nn_INI(n)        \
        in_dword_masked(HWIO_QSPI_CHAR_CS_Nn_ADDR(n), HWIO_QSPI_CHAR_CS_Nn_RMSK)
#define HWIO_QSPI_CHAR_CS_Nn_INMI(n,mask)    \
        in_dword_masked(HWIO_QSPI_CHAR_CS_Nn_ADDR(n), mask)
#define HWIO_QSPI_CHAR_CS_Nn_OUTI(n,val)    \
        out_dword(HWIO_QSPI_CHAR_CS_Nn_ADDR(n),val)
#define HWIO_QSPI_CHAR_CS_Nn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QSPI_CHAR_CS_Nn_ADDR(n),mask,val,HWIO_QSPI_CHAR_CS_Nn_INI(n))
#define HWIO_QSPI_CHAR_CS_Nn_DATA_OE_BMSK                                                  0xff000
#define HWIO_QSPI_CHAR_CS_Nn_DATA_OE_SHFT                                                      0xc
#define HWIO_QSPI_CHAR_CS_Nn_CHAR_MODE_BMSK                                                  0xf00
#define HWIO_QSPI_CHAR_CS_Nn_CHAR_MODE_SHFT                                                    0x8
#define HWIO_QSPI_CHAR_CS_Nn_DOUT_DATA_DIN_EXP_BMSK                                           0xff
#define HWIO_QSPI_CHAR_CS_Nn_DOUT_DATA_DIN_EXP_SHFT                                            0x0

#define HWIO_QSPI_TEST_BUS_SEL_ADDR                                                     (QSPI_REG_BASE      + 0x000000c4)
#define HWIO_QSPI_TEST_BUS_SEL_OFFS                                                     (QSPI_REG_BASE_OFFS + 0x000000c4)
#define HWIO_QSPI_TEST_BUS_SEL_RMSK                                                           0x1f
#define HWIO_QSPI_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_QSPI_TEST_BUS_SEL_ADDR, HWIO_QSPI_TEST_BUS_SEL_RMSK)
#define HWIO_QSPI_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_QSPI_TEST_BUS_SEL_ADDR, m)
#define HWIO_QSPI_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_QSPI_TEST_BUS_SEL_ADDR,v)
#define HWIO_QSPI_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_TEST_BUS_SEL_ADDR,m,v,HWIO_QSPI_TEST_BUS_SEL_IN)
#define HWIO_QSPI_TEST_BUS_SEL_TEST_BUS_SEL_BMSK                                              0x1f
#define HWIO_QSPI_TEST_BUS_SEL_TEST_BUS_SEL_SHFT                                               0x0

#define HWIO_QSPI_TEST_BUS_REG_ADDR                                                     (QSPI_REG_BASE      + 0x000000c8)
#define HWIO_QSPI_TEST_BUS_REG_OFFS                                                     (QSPI_REG_BASE_OFFS + 0x000000c8)
#define HWIO_QSPI_TEST_BUS_REG_RMSK                                                     0xffffffff
#define HWIO_QSPI_TEST_BUS_REG_IN          \
        in_dword_masked(HWIO_QSPI_TEST_BUS_REG_ADDR, HWIO_QSPI_TEST_BUS_REG_RMSK)
#define HWIO_QSPI_TEST_BUS_REG_INM(m)      \
        in_dword_masked(HWIO_QSPI_TEST_BUS_REG_ADDR, m)
#define HWIO_QSPI_TEST_BUS_REG_TEST_BUS_BMSK                                            0xffffffff
#define HWIO_QSPI_TEST_BUS_REG_TEST_BUS_SHFT                                                   0x0

#define HWIO_QSPI_MSTR_INT1_ENABLE_ADDR                                                 (QSPI_REG_BASE      + 0x000000d0)
#define HWIO_QSPI_MSTR_INT1_ENABLE_OFFS                                                 (QSPI_REG_BASE_OFFS + 0x000000d0)
#define HWIO_QSPI_MSTR_INT1_ENABLE_RMSK                                                 0xf0030e0f
#define HWIO_QSPI_MSTR_INT1_ENABLE_IN          \
        in_dword_masked(HWIO_QSPI_MSTR_INT1_ENABLE_ADDR, HWIO_QSPI_MSTR_INT1_ENABLE_RMSK)
#define HWIO_QSPI_MSTR_INT1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_QSPI_MSTR_INT1_ENABLE_ADDR, m)
#define HWIO_QSPI_MSTR_INT1_ENABLE_OUT(v)      \
        out_dword(HWIO_QSPI_MSTR_INT1_ENABLE_ADDR,v)
#define HWIO_QSPI_MSTR_INT1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_MSTR_INT1_ENABLE_ADDR,m,v,HWIO_QSPI_MSTR_INT1_ENABLE_IN)
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_DMA_CHAIN_DONE_BMSK                               0x80000000
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_DMA_CHAIN_DONE_SHFT                                     0x1f
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_XIP_ACCESS_DURING_DMA_BMSK                        0x40000000
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_XIP_ACCESS_DURING_DMA_SHFT                              0x1e
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_XIP_ACCESS_UNMAPPED_SEGMENT_BMSK                  0x20000000
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_XIP_ACCESS_UNMAPPED_SEGMENT_SHFT                        0x1d
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_XIP_ACCESS_NOT_ENABLE_BMSK                        0x10000000
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_XIP_ACCESS_NOT_ENABLE_SHFT                              0x1c
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_DMA_ACCESS_DURING_XIP_BMSK                           0x20000
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_DMA_ACCESS_DURING_XIP_SHFT                              0x11
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_TRANSACTION_DONE_BMSK                                0x10000
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_TRANSACTION_DONE_SHFT                                   0x10
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_WRITE_FIFO_OVERRUN_BMSK                                0x800
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_WRITE_FIFO_OVERRUN_SHFT                                  0xb
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_WRITE_FIFO_FULL_BMSK                                   0x400
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_WRITE_FIFO_FULL_SHFT                                     0xa
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_WRITE_FIFO_EMPTY_BMSK                                  0x200
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_WRITE_FIFO_EMPTY_SHFT                                    0x9
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_HRESP_FROM_NOC_ERR_BMSK                                  0x8
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_HRESP_FROM_NOC_ERR_SHFT                                  0x3
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_RESP_FIFO_RDY_BMSK                                       0x4
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_RESP_FIFO_RDY_SHFT                                       0x2
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_RESP_FIFO_NOT_EMPTY_BMSK                                 0x2
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_RESP_FIFO_NOT_EMPTY_SHFT                                 0x1
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_RESP_FIFO_UNDERRUN_BMSK                                  0x1
#define HWIO_QSPI_MSTR_INT1_ENABLE_EN_RESP_FIFO_UNDERRUN_SHFT                                  0x0

#define HWIO_QSPI_MSTR_INT1_STATUS_ADDR                                                 (QSPI_REG_BASE      + 0x000000d4)
#define HWIO_QSPI_MSTR_INT1_STATUS_OFFS                                                 (QSPI_REG_BASE_OFFS + 0x000000d4)
#define HWIO_QSPI_MSTR_INT1_STATUS_RMSK                                                 0xf0030e0f
#define HWIO_QSPI_MSTR_INT1_STATUS_IN          \
        in_dword_masked(HWIO_QSPI_MSTR_INT1_STATUS_ADDR, HWIO_QSPI_MSTR_INT1_STATUS_RMSK)
#define HWIO_QSPI_MSTR_INT1_STATUS_INM(m)      \
        in_dword_masked(HWIO_QSPI_MSTR_INT1_STATUS_ADDR, m)
#define HWIO_QSPI_MSTR_INT1_STATUS_OUT(v)      \
        out_dword(HWIO_QSPI_MSTR_INT1_STATUS_ADDR,v)
#define HWIO_QSPI_MSTR_INT1_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_MSTR_INT1_STATUS_ADDR,m,v,HWIO_QSPI_MSTR_INT1_STATUS_IN)
#define HWIO_QSPI_MSTR_INT1_STATUS_DMA_CHAIN_DONE_BMSK                                  0x80000000
#define HWIO_QSPI_MSTR_INT1_STATUS_DMA_CHAIN_DONE_SHFT                                        0x1f
#define HWIO_QSPI_MSTR_INT1_STATUS_XIP_ACCESS_DURING_DMA_BMSK                           0x40000000
#define HWIO_QSPI_MSTR_INT1_STATUS_XIP_ACCESS_DURING_DMA_SHFT                                 0x1e
#define HWIO_QSPI_MSTR_INT1_STATUS_XIP_ACCESS_UNMAPPED_SEGMENT_BMSK                     0x20000000
#define HWIO_QSPI_MSTR_INT1_STATUS_XIP_ACCESS_UNMAPPED_SEGMENT_SHFT                           0x1d
#define HWIO_QSPI_MSTR_INT1_STATUS_XIP_ACCESS_NOT_ENABLE_BMSK                           0x10000000
#define HWIO_QSPI_MSTR_INT1_STATUS_XIP_ACCESS_NOT_ENABLE_SHFT                                 0x1c
#define HWIO_QSPI_MSTR_INT1_STATUS_DMA_ACCESS_DURING_XIP_BMSK                              0x20000
#define HWIO_QSPI_MSTR_INT1_STATUS_DMA_ACCESS_DURING_XIP_SHFT                                 0x11
#define HWIO_QSPI_MSTR_INT1_STATUS_TRANSACTION_DONE_BMSK                                   0x10000
#define HWIO_QSPI_MSTR_INT1_STATUS_TRANSACTION_DONE_SHFT                                      0x10
#define HWIO_QSPI_MSTR_INT1_STATUS_WRITE_FIFO_OVERRUN_BMSK                                   0x800
#define HWIO_QSPI_MSTR_INT1_STATUS_WRITE_FIFO_OVERRUN_SHFT                                     0xb
#define HWIO_QSPI_MSTR_INT1_STATUS_WRITE_FIFO_FULL_BMSK                                      0x400
#define HWIO_QSPI_MSTR_INT1_STATUS_WRITE_FIFO_FULL_SHFT                                        0xa
#define HWIO_QSPI_MSTR_INT1_STATUS_WRITE_FIFO_EMPTY_BMSK                                     0x200
#define HWIO_QSPI_MSTR_INT1_STATUS_WRITE_FIFO_EMPTY_SHFT                                       0x9
#define HWIO_QSPI_MSTR_INT1_STATUS_HRESP_FROM_NOC_ERR_BMSK                                     0x8
#define HWIO_QSPI_MSTR_INT1_STATUS_HRESP_FROM_NOC_ERR_SHFT                                     0x3
#define HWIO_QSPI_MSTR_INT1_STATUS_RESP_FIFO_RDY_BMSK                                          0x4
#define HWIO_QSPI_MSTR_INT1_STATUS_RESP_FIFO_RDY_SHFT                                          0x2
#define HWIO_QSPI_MSTR_INT1_STATUS_RESP_FIFO_NOT_EMPTY_BMSK                                    0x2
#define HWIO_QSPI_MSTR_INT1_STATUS_RESP_FIFO_NOT_EMPTY_SHFT                                    0x1
#define HWIO_QSPI_MSTR_INT1_STATUS_RESP_FIFO_UNDERRUN_BMSK                                     0x1
#define HWIO_QSPI_MSTR_INT1_STATUS_RESP_FIFO_UNDERRUN_SHFT                                     0x0

#define HWIO_QSPI_XIP_MASTER_CFG_ADDR                                                   (QSPI_REG_BASE      + 0x00000200)
#define HWIO_QSPI_XIP_MASTER_CFG_OFFS                                                   (QSPI_REG_BASE_OFFS + 0x00000200)
#define HWIO_QSPI_XIP_MASTER_CFG_RMSK                                                      0xeff19
#define HWIO_QSPI_XIP_MASTER_CFG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_MASTER_CFG_ADDR, HWIO_QSPI_XIP_MASTER_CFG_RMSK)
#define HWIO_QSPI_XIP_MASTER_CFG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_MASTER_CFG_ADDR, m)
#define HWIO_QSPI_XIP_MASTER_CFG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_MASTER_CFG_ADDR,v)
#define HWIO_QSPI_XIP_MASTER_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_MASTER_CFG_ADDR,m,v,HWIO_QSPI_XIP_MASTER_CFG_IN)
#define HWIO_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_3_BMSK                      0x80000
#define HWIO_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_3_SHFT                         0x13
#define HWIO_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_2_BMSK                      0x40000
#define HWIO_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_2_SHFT                         0x12
#define HWIO_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_1_BMSK                      0x20000
#define HWIO_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_1_SHFT                         0x11
#define HWIO_QSPI_XIP_MASTER_CFG_AHBCLK_FREQ_BMSK                                           0xff00
#define HWIO_QSPI_XIP_MASTER_CFG_AHBCLK_FREQ_SHFT                                              0x8
#define HWIO_QSPI_XIP_MASTER_CFG_DMA_TRANS_BOUNDARY_BMSK                                      0x10
#define HWIO_QSPI_XIP_MASTER_CFG_DMA_TRANS_BOUNDARY_SHFT                                       0x4
#define HWIO_QSPI_XIP_MASTER_CFG_PROGRAM_ERASE_ONGOING_BMSK                                    0x8
#define HWIO_QSPI_XIP_MASTER_CFG_PROGRAM_ERASE_ONGOING_SHFT                                    0x3
#define HWIO_QSPI_XIP_MASTER_CFG_XIP_ENABLE_BMSK                                               0x1
#define HWIO_QSPI_XIP_MASTER_CFG_XIP_ENABLE_SHFT                                               0x0

#define HWIO_QSPI_XIP_MASTER_STATUS_ADDR                                                (QSPI_REG_BASE      + 0x00000204)
#define HWIO_QSPI_XIP_MASTER_STATUS_OFFS                                                (QSPI_REG_BASE_OFFS + 0x00000204)
#define HWIO_QSPI_XIP_MASTER_STATUS_RMSK                                                       0x3
#define HWIO_QSPI_XIP_MASTER_STATUS_IN          \
        in_dword_masked(HWIO_QSPI_XIP_MASTER_STATUS_ADDR, HWIO_QSPI_XIP_MASTER_STATUS_RMSK)
#define HWIO_QSPI_XIP_MASTER_STATUS_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_MASTER_STATUS_ADDR, m)
#define HWIO_QSPI_XIP_MASTER_STATUS_XIP_AWAITING_ARBITRATION_BMSK                              0x2
#define HWIO_QSPI_XIP_MASTER_STATUS_XIP_AWAITING_ARBITRATION_SHFT                              0x1
#define HWIO_QSPI_XIP_MASTER_STATUS_XIP_ACTIVE_BMSK                                            0x1
#define HWIO_QSPI_XIP_MASTER_STATUS_XIP_ACTIVE_SHFT                                            0x0

#define HWIO_QSPI_XIP_GENERAL_CFG_ADDR                                                  (QSPI_REG_BASE      + 0x00000208)
#define HWIO_QSPI_XIP_GENERAL_CFG_OFFS                                                  (QSPI_REG_BASE_OFFS + 0x00000208)
#define HWIO_QSPI_XIP_GENERAL_CFG_RMSK                                                       0x7ff
#define HWIO_QSPI_XIP_GENERAL_CFG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_GENERAL_CFG_ADDR, HWIO_QSPI_XIP_GENERAL_CFG_RMSK)
#define HWIO_QSPI_XIP_GENERAL_CFG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_GENERAL_CFG_ADDR, m)
#define HWIO_QSPI_XIP_GENERAL_CFG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_GENERAL_CFG_ADDR,v)
#define HWIO_QSPI_XIP_GENERAL_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_GENERAL_CFG_ADDR,m,v,HWIO_QSPI_XIP_GENERAL_CFG_IN)
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_PIO_DISABLE_BMSK                                       0x400
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_PIO_DISABLE_SHFT                                         0xa
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_CLEAR_ERR_UPON_IDLE_BMSK                               0x200
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_CLEAR_ERR_UPON_IDLE_SHFT                                 0x9
#define HWIO_QSPI_XIP_GENERAL_CFG_MOSI_OE_DELAY_FIX_DIS_BMSK                                 0x100
#define HWIO_QSPI_XIP_GENERAL_CFG_MOSI_OE_DELAY_FIX_DIS_SHFT                                   0x8
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_DMA_ARB_PRIORITY_BMSK                                   0x80
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_DMA_ARB_PRIORITY_SHFT                                    0x7
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_ACCESS_UNMAPPED_SEGMENT_REGION_MASK_BMSK                0x40
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_ACCESS_UNMAPPED_SEGMENT_REGION_MASK_SHFT                 0x6
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_ACCESS_UNMAPPED_SEGMENT_OFFSET_MASK_BMSK                0x20
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_ACCESS_UNMAPPED_SEGMENT_OFFSET_MASK_SHFT                 0x5
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_ACCESS_NOT_ENABLE_MASK_BMSK                             0x10
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_ACCESS_NOT_ENABLE_MASK_SHFT                              0x4
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_CGC_EN_BMSK                                              0x8
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_CGC_EN_SHFT                                              0x3
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_SWAP_RD_BYTES_BMSK                                       0x4
#define HWIO_QSPI_XIP_GENERAL_CFG_XIP_SWAP_RD_BYTES_SHFT                                       0x2
#define HWIO_QSPI_XIP_GENERAL_CFG_GENERATE_PATTERN_UPON_ACCESS_ERR_BMSK                        0x2
#define HWIO_QSPI_XIP_GENERAL_CFG_GENERATE_PATTERN_UPON_ACCESS_ERR_SHFT                        0x1
#define HWIO_QSPI_XIP_GENERAL_CFG_BYPASS_DISABLE_BMSK                                          0x1
#define HWIO_QSPI_XIP_GENERAL_CFG_BYPASS_DISABLE_SHFT                                          0x0

#define HWIO_QSPI_XIP_INST_PH_CONFIG_ADDR                                               (QSPI_REG_BASE      + 0x00000210)
#define HWIO_QSPI_XIP_INST_PH_CONFIG_OFFS                                               (QSPI_REG_BASE_OFFS + 0x00000210)
#define HWIO_QSPI_XIP_INST_PH_CONFIG_RMSK                                               0xffff0006
#define HWIO_QSPI_XIP_INST_PH_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_INST_PH_CONFIG_ADDR, HWIO_QSPI_XIP_INST_PH_CONFIG_RMSK)
#define HWIO_QSPI_XIP_INST_PH_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_INST_PH_CONFIG_ADDR, m)
#define HWIO_QSPI_XIP_INST_PH_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_INST_PH_CONFIG_ADDR,v)
#define HWIO_QSPI_XIP_INST_PH_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_INST_PH_CONFIG_ADDR,m,v,HWIO_QSPI_XIP_INST_PH_CONFIG_IN)
#define HWIO_QSPI_XIP_INST_PH_CONFIG_LINEAR_BURST_INST_OPCODE_BMSK                      0xff000000
#define HWIO_QSPI_XIP_INST_PH_CONFIG_LINEAR_BURST_INST_OPCODE_SHFT                            0x18
#define HWIO_QSPI_XIP_INST_PH_CONFIG_WRAP_BURST_INST_OPCODE_BMSK                          0xff0000
#define HWIO_QSPI_XIP_INST_PH_CONFIG_WRAP_BURST_INST_OPCODE_SHFT                              0x10
#define HWIO_QSPI_XIP_INST_PH_CONFIG_DDR_SDR_SELECTOR_BMSK                                     0x4
#define HWIO_QSPI_XIP_INST_PH_CONFIG_DDR_SDR_SELECTOR_SHFT                                     0x2
#define HWIO_QSPI_XIP_INST_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK                                   0x2
#define HWIO_QSPI_XIP_INST_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT                                   0x1

#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDR                                               (QSPI_REG_BASE      + 0x00000214)
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_OFFS                                               (QSPI_REG_BASE_OFFS + 0x00000214)
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_RMSK                                                   0xff06
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDR, HWIO_QSPI_XIP_ADDR_PH_CONFIG_RMSK)
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDR, m)
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDR,v)
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDR,m,v,HWIO_QSPI_XIP_ADDR_PH_CONFIG_IN)
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDRESS_LENGTH_BMSK                                    0xff00
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_ADDRESS_LENGTH_SHFT                                       0x8
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_DDR_SDR_SELECTOR_BMSK                                     0x4
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_DDR_SDR_SELECTOR_SHFT                                     0x2
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK                                   0x2
#define HWIO_QSPI_XIP_ADDR_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT                                   0x1

#define HWIO_QSPI_XIP_MODE_PH_CONFIG_ADDR                                               (QSPI_REG_BASE      + 0x00000218)
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_OFFS                                               (QSPI_REG_BASE_OFFS + 0x00000218)
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_RMSK                                               0xff000007
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_MODE_PH_CONFIG_ADDR, HWIO_QSPI_XIP_MODE_PH_CONFIG_RMSK)
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_MODE_PH_CONFIG_ADDR, m)
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_MODE_PH_CONFIG_ADDR,v)
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_MODE_PH_CONFIG_ADDR,m,v,HWIO_QSPI_XIP_MODE_PH_CONFIG_IN)
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_MODE_BYTE_VALUE_BMSK                               0xff000000
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_MODE_BYTE_VALUE_SHFT                                     0x18
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_DDR_SDR_SELECTOR_BMSK                                     0x4
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_DDR_SDR_SELECTOR_SHFT                                     0x2
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK                                   0x2
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT                                   0x1
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_MODE_PHASE_ENABLE_BMSK                                    0x1
#define HWIO_QSPI_XIP_MODE_PH_CONFIG_MODE_PHASE_ENABLE_SHFT                                    0x0

#define HWIO_QSPI_XIP_DATA_PH_CONFIG_ADDR                                               (QSPI_REG_BASE      + 0x00000220)
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_OFFS                                               (QSPI_REG_BASE_OFFS + 0x00000220)
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_RMSK                                                      0x6
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_DATA_PH_CONFIG_ADDR, HWIO_QSPI_XIP_DATA_PH_CONFIG_RMSK)
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_DATA_PH_CONFIG_ADDR, m)
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_DATA_PH_CONFIG_ADDR,v)
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_DATA_PH_CONFIG_ADDR,m,v,HWIO_QSPI_XIP_DATA_PH_CONFIG_IN)
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_DDR_SDR_SELECTOR_BMSK                                     0x4
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_DDR_SDR_SELECTOR_SHFT                                     0x2
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK                                   0x2
#define HWIO_QSPI_XIP_DATA_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT                                   0x1

#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_ADDR                                            (QSPI_REG_BASE      + 0x00000224)
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_OFFS                                            (QSPI_REG_BASE_OFFS + 0x00000224)
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_RMSK                                            0xff03ff07
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_ADDR, HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_RMSK)
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_ADDR, m)
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_ADDR,v)
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_ADDR,m,v,HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_IN)
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_OP_CODE_BMSK                            0xff000000
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_OP_CODE_SHFT                                  0x18
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_T_SUSPEND_PROG_DELAY_BMSK                          0x3ff00
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_T_SUSPEND_PROG_DELAY_SHFT                              0x8
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_DDR_SDR_SELECTOR_BMSK                                  0x4
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_DDR_SDR_SELECTOR_SHFT                                  0x2
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK                                0x2
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT                                0x1
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_ENABLE_BMSK                                    0x1
#define HWIO_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_ENABLE_SHFT                                    0x0

#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_ADDR                                             (QSPI_REG_BASE      + 0x00000228)
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_OFFS                                             (QSPI_REG_BASE_OFFS + 0x00000228)
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_RMSK                                             0xff03ff07
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_IN          \
        in_dword_masked(HWIO_QSPI_XIP_RESUME_PH_CONFIG_ADDR, HWIO_QSPI_XIP_RESUME_PH_CONFIG_RMSK)
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_RESUME_PH_CONFIG_ADDR, m)
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_RESUME_PH_CONFIG_ADDR,v)
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_RESUME_PH_CONFIG_ADDR,m,v,HWIO_QSPI_XIP_RESUME_PH_CONFIG_IN)
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_RESUME_OP_CODE_BMSK                              0xff000000
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_RESUME_OP_CODE_SHFT                                    0x18
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_T_RESUME_PROG_DELAY_BMSK                            0x3ff00
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_T_RESUME_PROG_DELAY_SHFT                                0x8
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_DDR_SDR_SELECTOR_BMSK                                   0x4
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_DDR_SDR_SELECTOR_SHFT                                   0x2
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK                                 0x2
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT                                 0x1
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_RESUME_ENABLE_BMSK                                      0x1
#define HWIO_QSPI_XIP_RESUME_PH_CONFIG_RESUME_ENABLE_SHFT                                      0x0

#define HWIO_QSPI_XIP_REGION_n_SIZE_ADDR(n)                                             (QSPI_REG_BASE      + 0x00000230 + 0x4 * (n))
#define HWIO_QSPI_XIP_REGION_n_SIZE_OFFS(n)                                             (QSPI_REG_BASE_OFFS + 0x00000230 + 0x4 * (n))
#define HWIO_QSPI_XIP_REGION_n_SIZE_RMSK                                                    0x1fff
#define HWIO_QSPI_XIP_REGION_n_SIZE_MAXn                                                         3
#define HWIO_QSPI_XIP_REGION_n_SIZE_INI(n)        \
        in_dword_masked(HWIO_QSPI_XIP_REGION_n_SIZE_ADDR(n), HWIO_QSPI_XIP_REGION_n_SIZE_RMSK)
#define HWIO_QSPI_XIP_REGION_n_SIZE_INMI(n,mask)    \
        in_dword_masked(HWIO_QSPI_XIP_REGION_n_SIZE_ADDR(n), mask)
#define HWIO_QSPI_XIP_REGION_n_SIZE_OUTI(n,val)    \
        out_dword(HWIO_QSPI_XIP_REGION_n_SIZE_ADDR(n),val)
#define HWIO_QSPI_XIP_REGION_n_SIZE_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QSPI_XIP_REGION_n_SIZE_ADDR(n),mask,val,HWIO_QSPI_XIP_REGION_n_SIZE_INI(n))
#define HWIO_QSPI_XIP_REGION_n_SIZE_REGION_SIZE_BMSK                                        0x1fff
#define HWIO_QSPI_XIP_REGION_n_SIZE_REGION_SIZE_SHFT                                           0x0

#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_ADDR(n)                                         (QSPI_REG_BASE      + 0x00000270 + 0x4 * (n))
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_OFFS(n)                                         (QSPI_REG_BASE_OFFS + 0x00000270 + 0x4 * (n))
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_RMSK                                            0xfffff000
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_MAXn                                                     3
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_INI(n)        \
        in_dword_masked(HWIO_QSPI_XIP_REGION_n_SPI_BASE_ADDR(n), HWIO_QSPI_XIP_REGION_n_SPI_BASE_RMSK)
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_INMI(n,mask)    \
        in_dword_masked(HWIO_QSPI_XIP_REGION_n_SPI_BASE_ADDR(n), mask)
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_OUTI(n,val)    \
        out_dword(HWIO_QSPI_XIP_REGION_n_SPI_BASE_ADDR(n),val)
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QSPI_XIP_REGION_n_SPI_BASE_ADDR(n),mask,val,HWIO_QSPI_XIP_REGION_n_SPI_BASE_INI(n))
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_REGION_SPI_BASE_BMSK                            0xfffff000
#define HWIO_QSPI_XIP_REGION_n_SPI_BASE_REGION_SPI_BASE_SHFT                                   0xc

#define HWIO_QSPI_XIP_ERR_PATTERN_ADDR                                                  (QSPI_REG_BASE      + 0x00000310)
#define HWIO_QSPI_XIP_ERR_PATTERN_OFFS                                                  (QSPI_REG_BASE_OFFS + 0x00000310)
#define HWIO_QSPI_XIP_ERR_PATTERN_RMSK                                                  0xffffffff
#define HWIO_QSPI_XIP_ERR_PATTERN_IN          \
        in_dword_masked(HWIO_QSPI_XIP_ERR_PATTERN_ADDR, HWIO_QSPI_XIP_ERR_PATTERN_RMSK)
#define HWIO_QSPI_XIP_ERR_PATTERN_INM(m)      \
        in_dword_masked(HWIO_QSPI_XIP_ERR_PATTERN_ADDR, m)
#define HWIO_QSPI_XIP_ERR_PATTERN_OUT(v)      \
        out_dword(HWIO_QSPI_XIP_ERR_PATTERN_ADDR,v)
#define HWIO_QSPI_XIP_ERR_PATTERN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QSPI_XIP_ERR_PATTERN_ADDR,m,v,HWIO_QSPI_XIP_ERR_PATTERN_IN)
#define HWIO_QSPI_XIP_ERR_PATTERN_ERR_PATTERN_BMSK                                      0xffffffff
#define HWIO_QSPI_XIP_ERR_PATTERN_ERR_PATTERN_SHFT                                             0x0


#endif /* __QSPI_HWIO_H__ */
