/*==============================================================================

  D A L   G P I O   I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
  This file has the direct connect GPIO interrupt support for the 8994 target
  UIMAGE. This file should not be included in Dev CFGs for dal. its strictly used for
  non dal uimage drivers.

REFERENCES

Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/GPIOInt/src/user/uimage/config/sdm660/uGPIOIntConfigData.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "com_dtypes.h"
#include "uGPIOIntUser.h"

/*
 * LPASS Sensors Direct Connect Interrupt Config Map.
 * Please note this is different from the Audio DSP direct connect map.
 */

uGPIOIntConfigMapType uGPIOIntConfigMap[] =
{
  {67, 0,  206, UGPIOINTF_DIRECTINT_CONFIG},  /* Touch screen                      */
  {68, 1,  207, UGPIOINTF_DIRECTINT_CONFIG},  /* Accelerometer interrupt           */
  {69, 2,  208, UGPIOINTF_DIRECTINT_CONFIG},  /* Gyroscope interrupt               */
  {70, 3,  209, UGPIOINTF_DIRECTINT_CONFIG},  /* Magnetometer data ready interrupt */
  {71, 4,  210, UGPIOINTF_DIRECTINT_CONFIG},  /* ALSP & Gesture interrupts muxed   */
  {72, 5,  211, UGPIOINTF_DIRECTINT_CONFIG},  /* Fingerprint Sensor Interrupt      */
  {73, 6,  212, UGPIOINTF_DIRECTINT_CONFIG},  /* HRM Interrupt                     */
  {74, 7,  213, UGPIOINTF_DIRECTINT_CONFIG},  /* Cap Sensor1 & Cap Sensor2 Muxed   */
  {75, 8,  214, UGPIOINTF_DIRECTINT_CONFIG},  /* Hall Effect Sensor Interrupt      */
  {76,  9,  215, UGPIOINTF_DIRECTINT_CONFIG},  /* Pressure Interrupt             */
  {0, 0, 0, 0}, /* End */
};









