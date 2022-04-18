/** @file MpPowerLib.h
   
  The Multicore power  common definitions

  Copyright (c) 2015, Qualcomm Technologies, Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Include/Library/MpPowerLib.h#2 $ 
  $DateTime: 2016/08/19 05:58:45 $ 
  $Author: c_mvanim $ 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/24/15   rli     Initial revision
=============================================================================*/
#ifndef __MPPOWERLIB_H_
#define __MPPOWERLIB_H_


/*=========================================================================
      Include Files
==========================================================================*/

/*===========================================================================

                        Defines and Structs

===========================================================================*/

/*===========================================================================

                        Public Functions

===========================================================================*/
/**
  @brief MpPowerInit - chipset-specific initialization
  @return - EFI_SUCCESS on success, otherwise error status
*/
EFI_STATUS MpPowerInit (VOID);

/**
  @brief MpPower - chipset-specific multicore enablement
  @param[in]  CoreNum - number of cores
  @return - EFI_SUCCESS on success, otherwise error status
*/
EFI_STATUS MpPower (UINTN  CoreNum);



#endif // __MPPOWERLIB_H_
