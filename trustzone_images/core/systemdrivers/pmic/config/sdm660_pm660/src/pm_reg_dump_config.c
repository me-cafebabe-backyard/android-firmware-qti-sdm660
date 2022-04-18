/*! \file
*  \n
*  \brief  pm_reg_dump_config.c
*  \n
*  \n This file contains pmic configuration data specific for PMIC debug APIs.
*  \n
*  \n &copy; Copyright 2014-2016 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/pmic/config/sdm660_pm660/src/pm_reg_dump_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/16/16   aab     Added support to enable desired PMIC Register dump
01/26/16   vtw     Updated for Nazgul.
========================================================================== */

/*=========================================================================
      Include Files
==========================================================================*/

#include "pm_internal.h"

/*===========================================================================
Data Declarations
===========================================================================*/

/*
 * Array PMIC peripherals supply DDR rails.
 */
const pm_reg_dump_list_type pm_reg_dump_list[] =
{
  /* VDD_CX*/
   {0x3, 0x1A00, PM_PERIPH_TYPE_SMPS},    /* S3B_CTRL */
   {0x3, 0x1C00, PM_PERIPH_TYPE_SMPS},    /* S3B_FREQ */

   /* VDD_MX*/
   {0x3, 0x2000, PM_PERIPH_TYPE_SMPS},    /* S5B_CTRL */
   {0x3, 0x2200, PM_PERIPH_TYPE_SMPS},    /* S5B_FREQ */

  /* LPDDR4*/
   {0x3, 0x1400, PM_PERIPH_TYPE_SMPS},    /* S1B_CTRL */
   {0x3, 0x1600, PM_PERIPH_TYPE_SMPS},    /* S1B_FREQ */

  /* VDD_PX3*/
   {0x1, 0x1D00, PM_PERIPH_TYPE_SMPS},    /* L13A_CTRL */
   
  /* VDD_PX11*/
   {0x1, 0x4C00, PM_PERIPH_TYPE_SMPS},    /* LDO10A_CTRL */
   

  /* VDDA_EBI */  //Same as MX
   //{0x1, 0x2900, PM_PERIPH_TYPE_SMPS},    /* S8_CTRL */
   //{0x1, 0x2B00, PM_PERIPH_TYPE_SMPS},    /* S8_FREQ */

   /* LPDDR4X */ //external buck
   //{0x5, 0x1A00, PM_PERIPH_TYPE_SMPS},    /* S3_CTRL */
   //{0x5, 0x1C00, PM_PERIPH_TYPE_SMPS},    /* S3_FREQ */
   
   //Add single PMIC Reg list to dump below
   {0x1, 0x2649, PM_PERIPH_TYPE_SINGLE_REG},     /* Individual PMIC Reg */
   {0x1, 0x264F, PM_PERIPH_TYPE_SINGLE_REG},     /* Individual PMIC Reg */


  /* End of array */
   {0xf, 0xffff, PM_PERIPH_TYPE_INVALID}      /* End of list */
};

