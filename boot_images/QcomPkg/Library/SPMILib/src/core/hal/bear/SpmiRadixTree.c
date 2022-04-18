/**
 * @file:  SpmiRadixTree.c
 * 
 * Copyright (c) 2013-2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/hal/bear/SpmiRadixTree.c#2 $
 * $Change: 11185940 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 08/06/15  More than 256 chan support.
 * 06/11/15 Added zeroing of the radix tree.
 * 11/3/14  Automatic channel assignment
 * 10/1/13  Initial Version
 */

#include <string.h>
#include "SpmiMaster.h"
#include "SpmiBusCfg.h"
#include "SpmiHal.h"
#include "SpmiInfo.h"

//******************************************************************************
// Local Helper Functions
//******************************************************************************

static uint32 SpmiMaster_CreateMappingTableEntry(uint32 uBitIndex,
                                                 uint32 uBranchResult0Flag,
                                                 uint32 uBranchResult0,
                                                 uint32 uBranchResult1Flag,
                                                 uint32 uBranchResult1)
{
    return ((uBitIndex          << HWIO_SPMI_MAPPING_TABLE_REGk_BIT_INDEX_SHFT)            & HWIO_SPMI_MAPPING_TABLE_REGk_BIT_INDEX_BMSK) |
           ((uBranchResult0Flag << HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_0_FLAG_SHFT) & HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_0_FLAG_BMSK) |
           ((uBranchResult0     << HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_0_SHFT)      & HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_0_BMSK) |
           ((uBranchResult1Flag << HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_1_FLAG_SHFT) & HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_1_FLAG_BMSK) |
           ((uBranchResult1     << HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_1_SHFT)      & HWIO_SPMI_MAPPING_TABLE_REGk_BRANCH_RESULT_1_BMSK);
}

static void SpmiMaster_UpdateMappingImageEntry(uint8 * base_addr,
                                               uint32 uEntryIndex,
                                               uint8 ucBitIndex,
                                               uint8 ucBitValue,
                                               boolean bIsResult,
                                               uint32 ucTarget)
{
    uint32 uFlag;
    uint32 uNewEntryValue;

    enum {
        RESULT = 0, BRANCH = 1
    };

    uFlag = (TRUE == bIsResult) ? RESULT : BRANCH;
    
    uNewEntryValue = SPMI_HWIO_IN( HWIO_SPMI_MAPPING_TABLE_REGk_ADDR( base_addr, uEntryIndex ) );

    if (1 == ucBitValue) {
        uNewEntryValue |= SpmiMaster_CreateMappingTableEntry( ucBitIndex,
                                                              0,
                                                              0,
                                                              uFlag,
                                                              ucTarget );
    } else /* 0 == bitValue */ {
        uNewEntryValue |= SpmiMaster_CreateMappingTableEntry( ucBitIndex,
                                                              uFlag,
                                                              ucTarget,
                                                              0,
                                                              0 );
    }
    
    SPMI_HWIO_OUT( HWIO_SPMI_MAPPING_TABLE_REGk_ADDR( base_addr, uEntryIndex ), uNewEntryValue );
}

static uint8 SpmiMaster_CreateMappingImage(uint8 * base_addr,
                                           SpmiBusCfg_ChannelCfg* entries,
                                           uint32 numEntries,
                                           uint32 uEntryIndex,
                                           uint8 ucMsbIndex)
{
    uint8 ucOnes = 0;
    uint16 usMsbCompareMask = (1 << ucMsbIndex);
    uint8 ucNewMsbIndex = ucMsbIndex - 1;
    uint32 uNextEntryIndex = 0;

    /* Count number of values with a '1' at ucMsbIndex  */
    while ((ucOnes < numEntries) && 
           (((entries[ucOnes].slaveId << 8) | entries[ucOnes].periphId) & usMsbCompareMask)) 
    {
        ++ucOnes;
    }

    /* All relevant values match at MSB, continue to next ucMsbIndex */
    if ((ucOnes == numEntries) || (0 == ucOnes)) {
        return SpmiMaster_CreateMappingImage( base_addr,
                                              entries,
                                              numEntries,
                                              uEntryIndex,
                                              ucNewMsbIndex );
    }

    /* Split is possible, first handle all values with '1' at ucMsbIndex */
    if (1 == ucOnes) { /* RESULT, target APID must be at (sortedPairs[0].apid) */
        SpmiMaster_UpdateMappingImageEntry( base_addr,
                                            uEntryIndex,
                                            ucMsbIndex,
                                            1,
                                            TRUE,
                                            entries[0].channel );

        /* When deploying the subtree for '0' continue from uEntryIndex+1 */
        uNextEntryIndex = uEntryIndex + 1;
    } else { /* BRANCH, target table entry is (uEntryIndex+1) */
        SpmiMaster_UpdateMappingImageEntry( base_addr,
                                            uEntryIndex,
                                            ucMsbIndex,
                                            1,
                                            FALSE,
                                            uEntryIndex + 1 );

        /* Continue recursively with all values with '1' at ucMsbIndex */
        uNextEntryIndex =  SpmiMaster_CreateMappingImage( base_addr,
                                                          entries,
                                                          ucOnes,
                                                          uEntryIndex + 1,
                                                          ucNewMsbIndex );
    }

    /* Now handle all values with '0' at ucMsbIndex */
    if (ucOnes == numEntries - 1) { /* RESULT, target APID must be at (sortedPairs[uEntries-1].apid) */
        SpmiMaster_UpdateMappingImageEntry( base_addr,
                                            uEntryIndex,
                                            ucMsbIndex,
                                            0,
                                            TRUE,
                                            entries[numEntries - 1].channel );
    } else {
        /* BRANCH to the entry after the subtree for '1' */
        SpmiMaster_UpdateMappingImageEntry( base_addr,
                                            uEntryIndex,
                                            ucMsbIndex,
                                            0,
                                            FALSE,
                                            uNextEntryIndex );

        /* Continue recursively with all values with '0' at ucMsbIndex */
        uNextEntryIndex =  SpmiMaster_CreateMappingImage( base_addr,
                                                          (&entries[ucOnes]),
                                                          (numEntries - ucOnes),
                                                          uNextEntryIndex,
                                                          ucNewMsbIndex );
    }

    /* Return the entry after the last one which was configured */
    return uNextEntryIndex;
}

//******************************************************************************
// Public API Functions
//******************************************************************************

void SpmiMaster_LoadRadixTree(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries)
{
    uint32 index;
    uint8 * base_addr = pDev->baseAddrs;

    /* Zero the radixtree.*/
    for (index = 0; index < SPMI_NUM_MAPPING_TABLE_ENTRIES(pDev); index++) {
       SPMI_HWIO_OUT( HWIO_SPMI_MAPPING_TABLE_REGk_ADDR( base_addr, index ), 0 );	    
    }
	
   
    if (1 == numEntries)
    {
        /* Configure the first entry to the APID result */
        SpmiMaster_UpdateMappingImageEntry( base_addr,
                                            0,
                                            0,
                                            entries[0].periphId & 0x1,
                                            TRUE,
                                            entries[0].channel );
    } 
    else if (2 <= numEntries) {
        /* Configure recursively for any real mapping (2 entries or more) */
        SpmiMaster_CreateMappingImage( base_addr, entries, numEntries, 0, 11 );
    }
}
