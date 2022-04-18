/*==============================================================================

  D A L   G P I O   I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
  This file has the direct connect GPIO interrupt support for the SDM660 target.

REFERENCES

        Copyright (c) 2016 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/GPIOInt/config/kernel/sdm660/adsp_slpi/GPIOInt_ConfigData.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/26/16   shm     First version for SDM660.
===========================================================================*/

#include "DALReg.h"
#include "DALDeviceId.h"
#include "DDIGPIOInt.h"
#include "HALgpioint.h"
#include "GPIOInt.h"

/*
 * LPASS interrupt config map
 */

GPIOIntConfigMapType interrupt_config_map[] =
{
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_0, 24,  GPIOINTF_EXTERNAL_CONFIG  }, /* dir_conn_irq_lpa_dsp 0 - owned by audio codec */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_1, 25,  GPIOINTF_EXTERNAL_CONFIG  }, /* dir_conn_irq_lpa_dsp 1 - owned by audio codec */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_2, 26,  0                         }, /* dir_conn_irq_lpa_dsp 2 */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_3, 27,  0                         }, /* dir_conn_irq_lpa_dsp 3 */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_4, 28,  0                         }, /* dir_conn_irq_lpa_dsp 4 */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_5, 29,  0                         }, /* dir_conn_irq_lpa_dsp 5 */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_6, 70,  0                         }, /* dir_conn_irq_sensors 0 */
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_7, 71,  0                         }, /* dir_conn_irq_sensors 1 */
  {67,           HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0                 }, /* Touch screen                      */
  {68,           HAL_GPIOINT_SUMMARY,         207, GPIOINTF_DIRECTINT_CONFIG }, /* Accelerometer interrupt           */
  {69,           HAL_GPIOINT_SUMMARY,         208, GPIOINTF_DIRECTINT_CONFIG }, /* Gyroscope interrupt               */
  {70,           HAL_GPIOINT_SUMMARY,         209, GPIOINTF_DIRECTINT_CONFIG }, /* Magnetometer data ready interrupt */
  {71,           HAL_GPIOINT_SUMMARY,         210, GPIOINTF_DIRECTINT_CONFIG }, /* ALSP & Gesture interrupts muxed   */
  {72,           HAL_GPIOINT_SUMMARY,         211, GPIOINTF_DIRECTINT_CONFIG }, /* Fingerprint Sensor Interrupt      */
  {73,           HAL_GPIOINT_SUMMARY,         212, GPIOINTF_DIRECTINT_CONFIG }, /* HRM Interrupt                     */
  {74,           HAL_GPIOINT_SUMMARY,         213, GPIOINTF_DIRECTINT_CONFIG }, /* Cap Sensor1 & Cap Sensor2 Muxed   */
  {75,           HAL_GPIOINT_SUMMARY,         214, GPIOINTF_DIRECTINT_CONFIG }, /* Hall Effect Sensor Interrupt      */
  {76,           HAL_GPIOINT_SUMMARY,         215, GPIOINTF_DIRECTINT_CONFIG }, /* Pressure Interrupt             */
};
