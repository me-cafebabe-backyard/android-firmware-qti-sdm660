#ifndef CTI_H
#define CTI_H
/*==============================================================================
  FILE:         cti.h
  
  OVERVIEW:     This file provides the externs and declarations needed for
                target specific code

  DEPENDENCIES: None

                Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/products/inc/cti.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "DDIChipInfo.h"

/////////////////////////////////////////////////////////////
////////////////////////Macros///////////////////////////////
//////////////////////////////////////////////////////////////
#define CTI_IMEM_BASE_8997           0x146B0000
#define CTI_IMEM_BASE_8998           0x146B0000
#define CTI_IMEM_BASE_8996           0x066BF000
#define CTI_IMEM_BASE_8994           0xFE87F000
#define CTI_IMEM_BASE_8992           0xFE80F000
#define CTI_IMEM_BASE_9X35           0xFE805000
#define CTI_IMEM_BASE_9X45           0x08600000
#define CTI_IMEM_BASE_8952	     0x08600000
#define CTI_IMEM_BASE_660            0x146B0000
#define CTI_IMEM_OFFSET_1            0x938
#define CTI_IMEM_OFFSET_2            0x93C
#define CTI_IMEM_OFFSET_3            0x940
//#define COOKIE_LOCATION         CTI_IMEM_3

#define COOKIE_BUSYWAIT         0x03444248
#define COOKIE_BKRPT            0x03444249
#define COOKIE_CRASH            0x0344424A
#define COOKIE_TRACE            0x0344424B
#define COOKIE_ETM_COMPARATOR   0x0344424C
#define COOKIE_DISABLE_SLEEP    0x0344424D
#define COOKIE_READ_REG         0x0344424E

#define MODEM_SELECT_MASK       0x2
#define ADSP_SELECT_MASK        0x4
#define PROCESSOR_SELECT_MASK   ADSP_SELECT_MASK

//////////////////////////////////////////////////////////////
////////////////////////Structs///////////////////////////////
//////////////////////////////////////////////////////////////
typedef struct 
{
  DALSYSWorkLoopHandle    handle;
  DALSYSEventHandle       event;
  
  // Event for trigger infinite loop in the WorkLoop
  DALSYSEventHandle         start_event;
  uint32                    cookie;
  uint32                    processor_select;
  uint32                    cookie_action;
  unsigned int              reg1;
  unsigned int              reg2;
  unsigned int              reg3;
  
} cti_target_config;

//////////////////////////////////////////////////////////////
////////////////////////Static Vars///////////////////////////
//////////////////////////////////////////////////////////////
static uint32 IMEM_Base, CTI_imem_1, CTI_imem_2, CTI_imem_3, Cookie_Location;


static DalDeviceHandle *hDALIntCtl;
//////////////////////////////////////////////////////////////
////////////////////////Function Declarations/////////////////
//////////////////////////////////////////////////////////////
static void CTI_Wakeup_Handler(uint32 param);

void cti_irq_init( void );

DALResult cti_workloop(DALSYSEventHandle hEvent, void *pCtx);

void cti_init_workloop( void );

volatile unsigned int cti_read_imem(void);

void cti_read_registers(void);




#endif //CTI_H