/*
===========================================================================
*/
/**
  @file uAonInt.c 
  
  The file contains the APIs required for retention in Island mode for the
  Sensors Low Power Island subsystem.
*/
/*  
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/InterruptController/src/qurt/kernel/uimage/uAonInt.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  10/01/14   cpaulo  Created.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "AonInt.h"
#include "HALaonint.h"
#include "qdss.h"


/* =========================================================================
**  Function : AonInt_RetentionEnter
** =========================================================================*/
/*
  See AonInt.h
*/

void AonInt_RetentionEnter( void )
{
   QDSS_RetentionEnter();
   HAL_aonint_RetentionEnter();
}


/* =========================================================================
**  Function : AonInt_RetentionExit
** =========================================================================*/
/*
  See AonInt.h
*/

void AonInt_RetentionExit( void )
{
  HAL_aonint_RetentionExit();
  QDSS_RetentionExit();
}
