/*===========================================================================
                        PMIC SHUTDOWN PROTOCOL
   DESCRIPTION
   This file contains functions prototypes and variable/type/constant
   declarations for supporting Shutdown Services for the Qualcomm 
   PMIC chip set.


   Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.

===========================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
03/26/14   al      Updating file and making library common
10/02/13   al      New file
===========================================================================*/
/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "com_dtypes.h"
#include "PmicShutdown.h"

#include <Uefi.h>
#include "SpmiBus.h"
#include <Library/TimerLib.h>


/*=========================================================================*/
/*            PMIC register addresses and masksfor PON control             */
/*=========================================================================*/

#define PM_PON_PS_HOLD_RESET_CTL                   0x85A
#define PM_PON_PS_HOLD_RESET_CTL2                  0x85B
#define PM_PON_PS_HOLD_RESET_CTL_SHUTDOWN_MASK     0x0F
#define PM_PON_PS_HOLD_S2_RESET_EN_MASK            0x80

#define PM_PON_REVISION2                           0x801
#define PM_PON_DIG_MAJOR_MASK                      0xFF

EFI_STATUS
EFIAPI
PmicReadModifyWriteByte
(
   UINT32  SlaveId,     /* SlaveId*/
   UINT32  RegAddr,     /* PMIC register address */
   UINT32  Mask,        /* Bit mask used for this operation*/
   UINT32  Data         /* data */
   );

EFI_STATUS
EFIAPI
PmicReadLong
(
   UINT32 SlaveId,     /* SlaveId*/
   UINT32 RegAddr,      /* PMIC register address */
   UINT8  *Data,        /* data */
   UINT32 DataLen       /*Number of bytes read*/
   ); 

EFI_STATUS
EFIAPI
PmicWriteLong
(
   UINT32 SlaveId,     /* SlaveId*/
   UINT32 RegAddr,      /* PMIC register address */
   UINT8  Data,         /* data */
   UINT32 DataLen       /*Number of bytes read*/
   );


/*===========================================================================
                  FUNCTION DEFINITIONS
===========================================================================*/



/*=========================================================================== */
/*                      PmicShutdownReadModifyWrite()                             */
/*=========================================================================== */

/**
 * API for masked write to PMIC register.
 * 
 * @param SlaveId      SlaveId of the PMIC module
 * @param RegAddr      PMIC register address
 * @param Mask         Bit mask used for this operation
 * @param Data         Data to be written to the PMIC
 * 
 * @return boolean 
 *          EFI_SUCCESS - the read completed successfully 
 *          EFI_DEVICE_ERROR - error reading from the PMIC 
 */
EFI_STATUS
EFIAPI PmicReadModifyWriteByte
(
   UINT32  SlaveId,      /* SlaveId*/
   UINT32  RegAddr,      /* PMIC register address */
   UINT32  Mask,         /* Bit mask used for this operation*/
   UINT32  Data          /* data */
   )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINT8 TempRead = 0;

  if (SpmiBus_ReadModifyWriteLongByte((uint32)SlaveId,(SpmiBus_AccessPriorityType)0, (uint32)RegAddr, (uint32)Data, (uint32)Mask, (uint8 *)&TempRead))
  {
    Status = EFI_DEVICE_ERROR;
  }
  else
  {
    Status = EFI_SUCCESS;
  }
  return Status;
}

/**
 * API to read a PMIC register.
 * 
 * @param SlaveId      SlaveId of the PMIC module
 * @param RegAddr      PMIC register address
 * @param Data         pointer to store read 
 * 
 * @return boolean
 *          EFI_SUCCESS - the read completed successfully 
 *          EFI_DEVICE_ERROR - error reading from the PMIC
 */
EFI_STATUS
EFIAPI PmicReadLong
(
   UINT32  SlaveId,     /* SlaveId*/
   UINT32 RegAddr,      /* PMIC register address */
   UINT8  *Data,        /* data */
   UINT32 DataLen       /*Number of bytes read*/
   )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 TotalByteRead = 0;

  if (SpmiBus_ReadLong((uint32)SlaveId,(SpmiBus_AccessPriorityType) 0, (uint32)RegAddr,(uint8 *) Data, (uint32) DataLen, (uint32 *)&TotalByteRead))
  {
    Status = EFI_DEVICE_ERROR;
  }
  else
  {
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
 * API to write to PMIC register.
 * 
 * @param SlaveId      SlaveId of the PMIC module
 * @param RegAddr      PMIC register address
 * @param Data         Data to be written to the PMIC
 * 
 * @return boolean
 *          EFI_SUCCESS - the read completed successfully 
 *          EFI_DEVICE_ERROR - error reading from the PMIC
 */
EFI_STATUS
EFIAPI PmicWriteLong
(
   UINT32  SlaveId,     /* SlaveId*/
   UINT32 RegAddr,      /* PMIC register address */
   UINT8  Data,         /* data */
   UINT32 DataLen       /*Number of bytes read*/
   )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT8 DataWrite = Data;

  if (SpmiBus_WriteLong((uint32)SlaveId,(SpmiBus_AccessPriorityType)0, (uint32)RegAddr,(uint8 *) &DataWrite, (uint32)DataLen))
  {
    Status = EFI_DEVICE_ERROR;
  }
  else
  {
    Status = EFI_SUCCESS;
  }
  return Status;
}

/*===========================================================================
FUNCTION PmicShutdown                                EXTERNAL FUNCTION  
DESCRIPTION
    This function disables SMPL bit and writes normal shutdown to PS_HOLD_RESET_CTL register. With these features 
  disabled, PMIC shuts off if PS_HOLD pin goes low.

  EXAMPLE:
  // shutdown the PMIC. 
  EFI_STATUS Status = PmicShutdown();

  // Was shutdown successful? 
  if (EFI_SUCCESS == Status) 
  {
    //Pull down PS_HOLD
  }

RETURN VALUE
  Return value type: EFI_STATUS.
    - EFI_SUCCESS  = PS_HOLD is ready to be pulled down
    - EFI_DEVICE_ERROR = Shutdown failed to disable the WDOG and SMPL bits.
===========================================================================*/
EFI_STATUS
EFIAPI
PmicShutdown()
{
  EFI_STATUS Status = EFI_SUCCESS;

  /* Diable RESET_EN before normal shutdown*/
  if( PmicReadModifyWriteByte(0,PM_PON_PS_HOLD_RESET_CTL2,PM_PON_PS_HOLD_S2_RESET_EN_MASK,0x00))
    {
      return EFI_DEVICE_ERROR;
    }

  /*wait for approx 315 usec*/
  Status = MicroSecondDelay(315);

  if(EFI_ERROR(Status))
  {
    return Status;
  }

  /* PON_PS_HOLD_RESET_CTL <3:0> =0x04  for normal shutdown*/
  if(PmicReadModifyWriteByte(0,PM_PON_PS_HOLD_RESET_CTL,PM_PON_PS_HOLD_RESET_CTL_SHUTDOWN_MASK,0x04))
  {
    return EFI_DEVICE_ERROR;
  }

  /* Enable RESET_EN before normal shutdown*/
  if( PmicReadModifyWriteByte(0,PM_PON_PS_HOLD_RESET_CTL2,PM_PON_PS_HOLD_S2_RESET_EN_MASK,0x80))
    {
      return EFI_DEVICE_ERROR;
    }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
PmicHardReset()
{
  EFI_STATUS Status = EFI_SUCCESS;

  /* Disable RESET_EN before Hard Reset*/
  if( PmicReadModifyWriteByte(0,PM_PON_PS_HOLD_RESET_CTL2,PM_PON_PS_HOLD_S2_RESET_EN_MASK,0x00))
    {
      return EFI_DEVICE_ERROR;
    }

  /*wait for approx 315 usec*/
  Status = MicroSecondDelay(315);

  if(EFI_ERROR(Status))
  {
    return Status;
  }

  /* PON_PS_HOLD_RESET_CTL <3:0> =0x07  for Hard Reset*/
  if(PmicReadModifyWriteByte(0,PM_PON_PS_HOLD_RESET_CTL,PM_PON_PS_HOLD_RESET_CTL_SHUTDOWN_MASK,0x07))
  {
    return EFI_DEVICE_ERROR;
  }

  /* Enable RESET_EN before Hard Reset*/
  if( PmicReadModifyWriteByte(0,PM_PON_PS_HOLD_RESET_CTL2,PM_PON_PS_HOLD_S2_RESET_EN_MASK,0x80))
    {
      return EFI_DEVICE_ERROR;
    }

  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
PmicReset(pm_pon_reset_cfg_type Reset)
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINT8 RegData;

   if(Reset >= PM_PON_RESET_CFG_INVALID)
   {
      return EFI_INVALID_PARAMETER;
   }

   /* Diable RESET_EN before Reset*/

   if(PmicReadModifyWriteByte(0, PM_PON_PS_HOLD_RESET_CTL2, PM_PON_PS_HOLD_S2_RESET_EN_MASK, 0x00))
   {
      return EFI_DEVICE_ERROR;
   }

   /*wait for approx 315 usec*/
   Status = MicroSecondDelay(315);

   if(EFI_ERROR(Status))
   {
      return Status;
   }

   switch(Reset)
   {
   case PM_PON_RESET_CFG_WARM_RESET:                                              RegData = 1;    break;
   case PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:               RegData = 2;    break;
   case PM_PON_RESET_CFG_NORMAL_SHUTDOWN:                                         RegData = 4;    break;
   case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN:                              RegData = 5;    break;
   case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:                         RegData = 6;    break;
   case PM_PON_RESET_CFG_HARD_RESET:                                              RegData = 7;    break;
   case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET:                            RegData = 8;    break;
   case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET:                       RegData = 9;    break;
   case PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_SHUTDOWN:              RegData = 0xA;  break;
   case PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:         RegData = 0xB;  break;
   case PM_PON_RESET_CFG_WARM_RESET_THEN_SHUTDOWN:                                RegData = 0xC;  break;
   case PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET:                              RegData = 0xD;  break;
   case PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET:            RegData = 0xE;  break;
   case PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET:       RegData = 0xF;  break;
   default:
      return EFI_DEVICE_ERROR;
   }

   /* PON_PS_HOLD_RESET_CTL <3:0>  for Reset*/
   if(PmicReadModifyWriteByte(0, PM_PON_PS_HOLD_RESET_CTL, PM_PON_PS_HOLD_RESET_CTL_SHUTDOWN_MASK, RegData))
   {
      return EFI_DEVICE_ERROR;
   }

   /* Enable RESET_EN before Reset*/
   if(PmicReadModifyWriteByte(0, PM_PON_PS_HOLD_RESET_CTL2, PM_PON_PS_HOLD_S2_RESET_EN_MASK, 0x80))
   {
      return EFI_DEVICE_ERROR;
   }

   return EFI_SUCCESS;
}


