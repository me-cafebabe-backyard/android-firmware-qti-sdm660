#ifndef __UGPIOInt_H
#define __UGPIOInt_H
/*===========================================================================

  D A L   G P I O   I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
  This modules contains enumeration definitions to support the Dal GPIO 
  interrupt controller. The definitions in this module are used internally 
  in the GPIO interrupt controller and are not to be exposed to the clients.

REFERENCES

       Copyright (c) 2016 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/GPIOInt/src/user/uimage/uGPIOIntUser.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/08/16   stu     Updating MAX_NUMBER_OF_UGPIOS to 10. There are only 
10/29/16   stu     Initial version for core.qdsp6.1.0
1/1/2010   aratin  First draft created. 
===========================================================================*/

#include "qurt.h"
#include "uGPIOInt.h"
#include "DDIGPIOMgr.h"

/*------------------------------------------------------------------------------
Declaring uGPIOInt Driver data
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 GPIO interrupt controller constant declarations.
------------------------------------------------------------------------------*/

#define UGPIOIST_TASKNAME_SIZE 16

/*
 * As an upper limit we keep the maximum number of GPIOs as 150. This number
 * needs to be updated if the GPIO number exceeds 150.
 * Also the number of GPIOs supported in uImage is 10 is a direct 1 to 1
 * relation to the number of direct connects currently available. This needs
 * to be updated if more GPIOs are to be supported in uImage.
 */
#define MAX_NUMBER_OF_UGPIOS        10
#define MAX_NUMBER_OF_GPIOS         150
#define UGPIOINTF_MPMINT            0x0002
#define UGPIOINTF_WAKEUP            0x0004
#define UGPIOINTF_REGISTERED        0x0008
#define UGPIOINTF_DIRECTINT_CONFIG  0x0010 /** Direct line to IntC */ 
#define UGPIOINT_IST_STACK_SIZE     1792

/*
 * Task signals are going to be the offset of which point they exist in the
 * state table:
 *   state[0] will be 0x1 << 0
 *   state[1] will be 0x1 << 1
 * One signal is reserved: SIG_INT_ABORT == 0x80000000
 */
#define UGPIOINT_TASK_INTMASK   0x7FFFFFFF

#define UGPIOINT_NOAONID 0xFF


/*=========================================================================

                           DATA TYPE DEFINITIONS

===========================================================================*/

/*
 * GPIOIntdata_type
 * Structure storing the details for a SUMMARY group interrupt
 */
typedef struct
{
  uGPIOINTISR                    isr;
  uGPIOINTISRCtx                 isr_param;
  uint32                         nInterruptMask;
  uint8                          intr_trigger;
  uint8                          gpio_intr_flags;
  uint8                          qurt_intr_id;
  uint8                          nGPIO;
  uint8                          nAONID;
} uGPIOIntDataType;
 

/*
 * uGPIOIntConfigMapType
 * Structure storing the interrupt data map accross all processors.
 * it matches with the DAL GPIOInt driver.
 * uint32          gpio;         GPIO pin number
 * uint32          interrupt_id; l1 main interrupt line for direct connects.
 * uint32          polarity;     polarity of the interrupt.
 */
typedef struct
{
  uint32                                 gpio;
  uint32                                 DirConnIntId;
  uint32                                 qurt_interrupt_id;
  uint32                                 flags;
} uGPIOIntConfigMapType;

/*
 * GPIOIntCntrlType
 *
 * Container for all local data.
 *
 * initialized: Indicates if the driver has been started or not.  Needed
 *              mostly because some compilers complain about empty structs.
 * table:       Table of registered GPIO_INT handler functions.
 * wakeup_isr:  ISR to invoke when a monitored GPIO interrupt triggers.
 */
typedef struct
{
  /* GPIOInt Dev state can be added by developers here */

  /* interrupt_state Table of registered GPIO_INT handler functions */
  DalDeviceHandle *              hGPIOMgr;
  uGPIOIntDataType               state[MAX_NUMBER_OF_UGPIOS];
  uint8                          aGPIOLUT[MAX_NUMBER_OF_GPIOS];
  qurt_thread_t                  nThreadID;
  uint8                          aISTStack[UGPIOINT_IST_STACK_SIZE];
  char                           aISTName[UGPIOIST_TASKNAME_SIZE];
  qurt_anysignal_t               ISTSignal;
  qurt_thread_attr_t             ThreadAttr;
  uint32                         nPriority;
  uint32                         nGPIOIntMask;
  uint32                         nGPIOIntRegistrationMask;
  uint32                         nISTStackSize;
  qurt_mutex_t                   uGPIOIntLock;
  int32                          ugpioint_qdi;
  
  /* Configuration map for direct connect interrupts.*/
  uGPIOIntConfigMapType          *puGPIOIntConfigMap;

  /* 
   * Number of direct connect interrupts.
   */
  uint32                        direct_intr_number;
      
  /* Flag to Initialize GPIOInt_Init is called first 
   * before anything else can attach 
   */
  uint8                          uGPIOInt_Init;

} uGPIOIntCntrlType;


/*=========================================================================

                      INTERNAL FUNCTION DEFINITIONS

===========================================================================*/


/*============================================================================= 
 
  FUNCTION      uGPIOInt_Init

  This is the main driver initialization function that is called in the
  GPIOInt DAL. \n

  DEPENDENCIES  None.
  @return
  UGPIOINT_SUCCESS -- Is returned if the uGPIOInt driver was correctly initialized. \n
  UGPIOINT_ERROR --  Is returned if the uGPIOInt initialization failed. \n
  @dependencies
  None.
 
=============================================================================*/
int32 uGPIOInt_Init
(
  void
);

/*=============================================================================

  FUNCTION      uGPIOInt_SetDirectConnectGPIOMapping

  DESCRIPTION   
  This function is used by the GPIOInt Dal driver to log the direct connect
  interrupts in DDR for Guest OS. This is so that in uimage the micro
  interrupt controller can trigger these interrupts quickly.

  PARAMETERS   
  
  uint32 gpio :         The GPIO pin whose interrupt state needs to be logged.
  uint32 qurt_intr_id : The QURT direct connect line to which the GPIO interrupt
                        is configured to.

  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio interrupt mapping
  is successfully communicated to the uGPIOInt driver.
  UGPIOINT_ERROR : this result is returned when the driver failed to set
  the interrupt mapping for uGPIOInt driver.
  

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_SetDirectConnectGPIOMapping
(
  uint32 gpio,
  uint32 qurt_intr_id
);

/*=============================================================================

  FUNCTION      uGPIOInt_ClearDirectConnectGPIOMapping

  DESCRIPTION   
  This function is used by the GPIOInt Dal driver clear the GPIO to main
  direct connect interrupt vector id.

  PARAMETERS   
  
  uint32 gpio :         The GPIO pin whose interrupt state needs to be cleared.
  
  DEPENDENCIES  None.

  RETURN VALUE  :
  UGPIOINT_SUCCESS : this result is obtained when the gpio interrupt mapping
  is successfully cleared from the uGPIOInt driver.
  UGPIOINT_ERROR : this result is returned when the driver failed to clear
  the interrupt mapping for uGPIOInt driver.
  

  SIDE EFFECTS  None.

=============================================================================*/
int32 uGPIOInt_ClearDirectConnectGPIOMapping
(
  uint32 gpio
);


#endif /*__UGPIOIntUser_H */
