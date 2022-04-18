#ifndef RPM_DEFINITIONS_H
#define RPM_DEFINITIONS_H
/*===========================================================================
                             rpm_definitions.h

SERVICES:

DESCRIPTION:
  Verbose description of what is defined by this header file. Typically
  describes the service provided by the classes, macros, etc. defined in
  this file.

PUBLIC CLASSES AND FUNCTIONS:

INITIALIZATION AND SEQUENCING REQUIREMENTS:
  Description...

Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "sleep_lpr.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------

#define SLEEP_VDD_MIN_ENTER_LATENCY 0x6000
#define SLEEP_VDD_MIN_EXIT_LATENCY 0x9000

#define SLEEP_HALT_ENTER_LATENCY 0x100
#define SLEEP_HALT_EXIT_LATENCY 0x100

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
#ifdef DDR_LPR_TRACING
typedef struct
{
  uint32 SCMO_RCH[2];
  uint32 SCMO_WCH[2];
  uint32 SCMO_CMD_BUF[2];
  uint32 DPE_DRAM[2];
  uint32 DPE_MEMC[2];
  uint32 BIMC_M_APP[2];
  uint32 BIMC_M_MMSS[2];
  uint32 BIMC_M_SYS[2];
  uint32 BIMC_M_DSP;
} ddr_register_cache_t;
#endif

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------
extern int    cx_id, mx_id;
boolean is_sleep_debug_enabled(void);

//===========================================================================
//                             Class Definitions
//===========================================================================


#endif
