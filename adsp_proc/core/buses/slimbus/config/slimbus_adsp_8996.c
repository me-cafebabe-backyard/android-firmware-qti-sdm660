/*
===========================================================================

FILE:         slimbus_bsp_data.c

DESCRIPTION:  This file implements the SLIMbus board support data.

===========================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/slimbus/config/slimbus_adsp_8996.c#1 $

when       who     what, where, why
--------   ---     -------------------------------------------------------- 
08/11/16   MJS     Support target configuration for voltage voting level.
05/23/16   MJS     Update BSP data for second instance.
02/05/16   MJS     Add support for multiple endpoints per port.
03/18/15   MJS     Support for second Slimbus instance.
09/09/14   mq      Multi-dataline support.
12/12/13   MJS     Initial revision for 8974 ADSP.

===========================================================================
             Copyright (c) 2013, 2014, 2015, 2016 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#include "DALSys.h"
#include "HALhwio.h"
#include "SlimBus.h"
#include "SlimBusDal.h"
#include "DDITlmm.h"


/* Slimbus BSP data */
SlimBusBSPType SlimBusBSP[] =
{
  {
    4,
    "SLIMBUS",
    { 0x00, 0x00, 0x60, 0x01, 0x17, 0x02 },
    "LPASS",
    0x001c0000,
    0x091c0000,
    0x09184000,
    11,
    12,
    0,
    { DAL_GPIO_CFG(70, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(71, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(72, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA) },
    71,
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3 }  /* Clock gears 0 through 10 */
  }
};

const SlimBusDeviceDalProps sbDeviceProps[] = 
{
    {0xc0, {0x00, 0x00, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc1, {0x00, 0x01, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc2, {0x00, 0x03, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc3, {0x00, 0x04, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc4, {0x00, 0x05, 0x60, 0x01, 0x17, 0x02}, 0x03},
    {0xca, {0x00, 0x00, 0xa0, 0x01, 0x17, 0x02}, 0x01},
    {0xcb, {0x00, 0x01, 0xa0, 0x01, 0x17, 0x02}, 0x03},
    {0xcc, {0x00, 0x00, 0x30, 0x01, 0x17, 0x02}, 0x01},
    {0xcd, {0x00, 0x01, 0x30, 0x01, 0x17, 0x02}, 0x01}
};

const uint32 sbNumDeviceProps = sizeof(sbDeviceProps) / sizeof(SlimBusDeviceDalProps);

/* Slimbus BSP data */
SlimBusBSPType SlimBusBSP2[] =
{
  {
    4,
    "SLIMBUS_QCA",
    { 0x01, 0x00, 0x60, 0x01, 0x17, 0x02 },
    "LPASS",
    0x00240000,
    0x09240000,
    0x09204000,
    86,
    87,
    0,
    { DAL_GPIO_CFG(74, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(73, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA) },
    73,
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3 }  /* Clock gears 0 through 10 */
  }
};

const SlimBusDeviceDalProps sbDeviceProps2[] = 
{
    {0xc5, {0x01, 0x00, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc6, {0x01, 0x01, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc7, {0x01, 0x03, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc8, {0x01, 0x04, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xc9, {0x01, 0x05, 0x60, 0x01, 0x17, 0x02}, 0x01},
    {0xce, {0x00, 0x00, 0x20, 0x01, 0x17, 0x02}, 0x01},
    {0xcf, {0x00, 0x01, 0x20, 0x01, 0x17, 0x02}, 0x01}
};

const uint32 sbNumDeviceProps2 = sizeof(sbDeviceProps2) / sizeof(SlimBusDeviceDalProps);

const MmpmRegParamType sbMmpmRegParam = 
{
  MMPM_REVISION,
  MMPM_CORE_ID_LPASS_SLIMBUS,
  MMPM_CORE_INSTANCE_0,
  "slimbus",
  PWR_CTRL_NONE,
  CALLBACK_NONE,
  NULL,
  0
};


const MmpmRegParamType sbMmpmRegParam2 = 
{
  MMPM_REVISION,
  MMPM_CORE_ID_LPASS_SLIMBUS,
  MMPM_CORE_INSTANCE_1,
  "slimbus_qca",
  PWR_CTRL_NONE,
  CALLBACK_NONE,
  NULL,
  0
};

