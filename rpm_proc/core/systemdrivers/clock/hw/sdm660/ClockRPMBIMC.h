#ifndef CLOCKRPMBIMC_H
#define CLOCKRPMBIMC_H
/*
===========================================================================
*/
/**
  @file ClockRPMBIMC.h
  
  BIMC definitions for the MSM8994 RPM clock driver.
*/
/*  
  ====================================================================

  Copyright (c) 2013-2015 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/hw/sdm660/ClockRPMBIMC.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  11/27/13   vph     Initial version
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/
#include <DALSys.h>
#include <railway.h>
#include <npa.h>
#include <npa_resource.h>


/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/

/*===========================================================================
 * The BIMC clock plan is provided to the RPM by the bootloader (SBL) through
 * shared memory (SMEM).  The structure of that data needs to match in revision,
 * size and shape.  Any mismatch is a fatal error on boot.
 *
 * Any change to these structures needs to increase the CLOCK_BIMC_SMEM_VERSION
 * to indicate that older bootloaders will not work to prevent the shared memory
 * from being interpretted incorrectly
===========================================================================*/
#define CLOCK_BIMC_SMEM_VERSION       0x0003
/*
 * ClockBIMCTableType
 */
typedef enum
{
  CLOCK_BIMC_PLL,
  CLOCK_BIMC_DDR,

  CLOCK_BIMC_NUM_TABLES
} ClockBIMCTableType;

typedef struct
{
  uint16 nVersion;     /* A version number to verify matching SBL and RPM data structures */
  uint8  nNumConfig;   /* A count of how many data tables are provided */
  uint8  nHALNumSrc;   /* HAL_CLK_NUM_OF_SOURCES */
  uint8  nMinLevel;    /* Min DDR level index */
  uint8  nMaxLevel;    /* Max DDR level index */
  uint8  nActiveLevel; /* The level in use at the time of RPM handoff */
  uint8  nReserved;    /* Reserved */
  uint32 nConfigData;  /* An offset from the start of the shared memory to the first table header */
} ClockBIMCConfigInfo;

typedef struct
{
  uint16 nNodeSize;   /* Size of each struct (row) in the table */
  uint8  nNumNodes;   /* The total number of structs */
  uint8  eBIMCTable;  /* The type of table, actual type should be ClockBIMCTableType but need to force it to 8-bit */
  uint32 nNodeOffset; /* Offset from shared memory to the first struct of the table */
} ClockBIMCTableHeaderType;

/*=========================================================================
      Prototypes
==========================================================================*/

/*===========================================================================

  FUNCTION      Clock_BIMCSetFrequency

  DESCRIPTION   Sets BIMC clock frequencies (DDR, APPS, Modem & GFX ports),
                performing BIMC collapse/restore if needed.
  
  PARAMETERS    nNewClkKHz [in] - New clock speed (in KHz).

  DEPENDENCIES  None.

  RETURN VALUE  New clock speed (in KHz).

  SIDE EFFECTS  None.

===========================================================================*/
uint32 Clock_BIMCSetFrequency
(
  BIMCResourceType    *pBimcRes,
  uint32              nNewClkKHz
);


/*===========================================================================

  FUNCTION      Clock_BIMCSetClockConfig

  DESCRIPTION   This function is for setting BIMC frequency.  Due to the
                dependency on DDR with voltage, this function is using for 
                switching the voltage first, call ddr_pre_clock_switch, then
                switch the clock.
                  
  PARAMETERS    pClock      - Clock for setting voltage
                pNewConfig  - New config frequency

  DEPENDENCIES  None.

  RETURN VALUE  Pointer to all clocks NPA resource

  SIDE EFFECTS  None.

===========================================================================*/
DALResult Clock_BIMCSetClockConfig
(
  ClockNodeType       *pClock,
  ClockMuxConfigType  *pNewConfig
);


/* =========================================================================
**  Function : Clock_BIMCCopyPlanFromShared
** =========================================================================*/
/**
  This function reads the BIMC clock plan from shared memory and copies it
  into the clock data structures.

  NOTE: only supports one DDR RCG config table to cover all BIMC clients.

  @param 
      pTargCtxt [in] - Clock driver target context.

  @return
    TRUE : Success
    FALSE : Mismatched or missing data in shared memory.
*/
boolean Clock_BIMCCopyPlanFromShared( Clock_TargCtxtType *pTargCtxt );


#endif /* #ifndef CLOCKRPMBIMC_H */
