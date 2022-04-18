/**
 * @file:  SpmiBusCfg.c
 * 
 * Copyright (c) 2013-2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/hal/bear/SpmiBusCfg.c#2 $
 * $Change: 11185940 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 11/3/14  Automatic channel assignment
 * 9/2/14   Enabled security features when channel info is set
 * 10/1/13  Initial Version
*/

#include "SpmiBusCfg.h"
#include "SpmiBusInternal.h"
#include "SpmiUtils.h"
#include "SpmiLogs.h"
#include "SpmiHal.h"
#include "SpmiMaster.h"
#include "PmicArb.h"
#include "SpmiOs.h"
#include "SpmiInfo.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define DEFAULT_MASTER_ID 0
#define INIT_CHECK() do { if(!initialized) { return SPMI_FAILURE_NOT_INITIALIZED; } } while(FALSE)

//******************************************************************************
// Global Data
//******************************************************************************

static boolean initialized = FALSE;
static SpmiInfo *pSpmiInfo;

//******************************************************************************
// Local Helper Functions
//******************************************************************************

typedef boolean (*CmprFunc)(const SpmiBusCfg_ChannelCfg*, const SpmiBusCfg_ChannelCfg*);

static boolean ppidCmpr(const SpmiBusCfg_ChannelCfg* c1, const SpmiBusCfg_ChannelCfg* c2)
{
    if(c2->slaveId == c1->slaveId) {
        return c2->periphId > c1->periphId;
    }
    
    return c2->slaveId > c1->slaveId;
}

static boolean ownerCmpr(const SpmiBusCfg_ChannelCfg* c1, const SpmiBusCfg_ChannelCfg* c2)
{    
    if(c1->periphOwner == c2->periphOwner) {
        return c1->intOwner > c2->intOwner;
    }
    
    return c1->periphOwner > c2->periphOwner;
}

static void shellSort(SpmiBusCfg_ChannelCfg* entries, uint32 numEntries, CmprFunc cmpr)
{
    // https://en.wikipedia.org/wiki/Shellsort
    static const uint8 gaps[] = {57, 23, 10, 4, 1};
    uint32 i, k;
    
    for(i = 0; i < sizeof(gaps) / sizeof(uint8); i++) 
    {
        uint8 gap = gaps[i];
        
        for(k = gap; k < numEntries; k++)
        {
            SpmiBusCfg_ChannelCfg tmp = entries[k];
            uint32 j = k;
            
            while(j >= gap && cmpr( &entries[j - gap], &tmp ))
            {
                entries[j] = entries[j-gap];
                j -= gap;
            }
            
            entries[j] = tmp;
        }
    }
}

static Spmi_Result assignChannel(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* entry, boolean autoAssignChan)
{
    boolean chanReserved;
    
    do
    {
        chanReserved = FALSE;
        
        if(autoAssignChan) {
            entry->channel = pDev->nextChanIdx;
        }

        if(entry->channel > (SPMI_NUM_CHANNELS_SUPPORTED(pDev) - 1))
        {
            if(autoAssignChan && pDev->dynamicChannelMode)
            {
                SPMI_LOG_VERBOSE( "Exhausted channels. Rolling over." );
                entry->channel = 0;
            }
            else {
                return SPMI_FAILURE_INVALID_CHAN_NUM;
            }
        }
     
        pDev->nextChanIdx = entry->channel + 1;
        
        if(pDev->reservedChanEn) 
        {
            if(entry->channel == pDev->reservedChan) {
                    chanReserved = TRUE;
            }
        }
        
        if(!autoAssignChan && chanReserved) {
            return SPMI_FAILURE_CHANNEL_RESERVED;
        }
        
    } while(autoAssignChan && chanReserved);
    
    return SPMI_SUCCESS;
}


static Spmi_Result configChannels(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries, 
                                  SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount, 
                                  boolean autoAssignChan, boolean configHW, boolean legacySorted)
{
    uint32 i;
    uint32 rgIdx = 0;
    Spmi_Result rslt;
    SpmiBusCfg_RGConfig channelRG;
    SpmiBusCfg_RGConfig interruptRG;
    SpmiBusCfg_ChannelCfg* entry = NULL;
    uint8 * base_addr = pDev->baseAddrs;
    
    INIT_CHECK();
    
    if(entries == NULL || numEntries == 0 || (rgCfg != NULL && rgCount == NULL)) {
        return SPMI_FAILURE_INVALID_PARAMETER;
    }
    
    if(numEntries > SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        return SPMI_FAILURE_TOO_MANY_ENTRIES;
    }
    if(autoAssignChan) {
        pDev->nextChanIdx = 0;
    }
    
    if(configHW)
    {
        // Zero table
        for (i = 0; i < SPMI_NUM_CHANNELS_SUPPORTED(pDev); i++) {
            SPMI_HWIO_OUT( HWIO_PMIC_ARB_REG_CHNLn_ADDR( base_addr, i ), 0 );
        }
        if (SPMI_SUCCESS != (rslt = PmicArb_InvalidateCache(pDev))) {
           return rslt;
        }
    }
    
    if(rgCfg != NULL)
    {
        shellSort(entries, numEntries, ownerCmpr);

        channelRG.owner = entries[0].periphOwner;
        channelRG.startIdx = 0;
        channelRG.startAddr = (uint32) HWIO_PMIC_ARBq_CHNLn_CMD_ADDR( base_addr, 0, 0 );

        interruptRG.owner = entries[0].intOwner;
        interruptRG.startIdx = 0;
        interruptRG.startAddr = (uint32) HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, 0 );
    }
    
    for (i = 0; i < numEntries; i++)
    {
        entry = &entries[i];

        if(entry->slaveId > SPMI_MAX_SLAVE_ID) {
            SPMI_LOG_ERROR( "Invalid slaveId: %d", entry->slaveId );
            return SPMI_FAILURE_INVALID_SLAVE_ID;
        }
        
        if(entry->intOwner >= SPMI_NUM_MASTERS(pDev)) {
            SPMI_LOG_ERROR( "Invalid intOwner: %d", entry->intOwner );
            return SPMI_FAILURE_INVALID_OWNER;
        }
        
        if(rgCfg != NULL &&
           entry->periphOwner >= SPMI_NUM_MASTERS(pDev) && 
           entry->periphOwner != SPMI_OPEN_OWNER) 
        {
            SPMI_LOG_ERROR( "Invalid periphOwner: %d", entry->periphOwner );
            return SPMI_FAILURE_INVALID_OWNER;
        }
        
        if(configHW) {
            rslt = SpmiBusCfg_ConfigureChannel( pDev, entry, autoAssignChan );
            if(SPMI_SUCCESS == rslt) {
               rslt = PmicArb_AddCacheEntry(pDev, entry->channel, entry->slaveId, entry->periphId);
            }
        }
        else {
            uint32 regChan;
            uint8 sid, addr;
                
            rslt = assignChannel( pDev, entry, autoAssignChan );
            if(SPMI_SUCCESS == rslt) {
               regChan = SPMI_HWIO_IN( HWIO_PMIC_ARB_REG_CHNLn_ADDR( base_addr, entry->channel ) );
               sid = SPMI_HWIO_GET_FIELD_VALUE( regChan, HWIO_PMIC_ARB_REG_CHNLn_SID );
               addr = SPMI_HWIO_GET_FIELD_VALUE( regChan, HWIO_PMIC_ARB_REG_CHNLn_ADDRESS );

               if(sid != entry->slaveId || addr != entry->periphId) {
                  return SPMI_FAILURE_INVALID_CHAN_NUM;
               }
            }
            
        }
        
        if(rslt != SPMI_SUCCESS) {
            return rslt;
        }
        
        if(rgCfg != NULL)
        {
            if(entry->periphOwner != channelRG.owner)
            {
                if(rgIdx == *rgCount) {
                    return SPMI_FAILURE_NOT_ENOUGH_RGS;
                }
                
                channelRG.endIdx = entry->channel - 1;
                channelRG.size = (uint32) HWIO_PMIC_ARBq_CHNLn_CMD_ADDR( base_addr, 0, entry->channel ) - channelRG.startAddr;
                rgCfg[rgIdx++] = channelRG;

                channelRG.owner = entry->periphOwner;
                channelRG.startIdx = entry->channel;
                channelRG.startAddr = (uint32) HWIO_PMIC_ARBq_CHNLn_CMD_ADDR( base_addr, 0, entry->channel );
            }

            if(entry->intOwner != interruptRG.owner)
            {
                if(rgIdx == *rgCount) {
                    return SPMI_FAILURE_NOT_ENOUGH_RGS;
                }
                
                interruptRG.endIdx = entry->channel - 1;
                interruptRG.size = (uint32) HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, entry->channel ) - interruptRG.startAddr;
                rgCfg[rgIdx++] = interruptRG;

                interruptRG.owner = entry->intOwner;
                interruptRG.startIdx = entry->channel;
                interruptRG.startAddr = (uint32) HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, entry->channel );
            }
        }
    }

    if(rgCfg != NULL)
    {
        channelRG.endIdx = entry->channel;
        channelRG.size = (uint32) HWIO_PMIC_ARBq_CHNLn_CMD_ADDR( base_addr, 0, entry->channel + 1 ) - channelRG.startAddr;

            if(rgIdx == *rgCount) {
                return SPMI_FAILURE_NOT_ENOUGH_RGS;
            }
            
            rgCfg[rgIdx++] = channelRG;
        

        if(rgIdx == *rgCount) {
            return SPMI_FAILURE_NOT_ENOUGH_RGS;
        }

        interruptRG.endIdx = entry->channel;
        interruptRG.size = (uint32) HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, entry->channel + 1 ) - interruptRG.startAddr;
        rgCfg[rgIdx++] = interruptRG;
    }
    
    if(rgCount != NULL) {
        *rgCount = rgIdx;
    }
    
    if(configHW && !pDev->dynamicChannelMode)
    {
        // Load the SPMI radix tree
        if(!legacySorted) {
            shellSort(entries, numEntries, ppidCmpr);
        }
        SpmiMaster_LoadRadixTree( pDev, entries, numEntries );
    
        // Enable security now that the tables are configured
        SPMI_HWIO_OUT_SET( HWIO_SPMI_CMPR_EN_REG_ADDR(base_addr), HWIO_SPMI_CMPR_EN_REG_CMPR_ENABLE_BMSK );
        SPMI_HWIO_OUT_CLEAR( HWIO_SPMI_SEC_DISABLE_REG_ADDR(base_addr), HWIO_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_BMSK );

        // Enable interrupt processing
        SPMI_HWIO_OUT_SET( HWIO_SPMI_MWB_ENABLE_REG_ADDR(base_addr), HWIO_SPMI_MWB_ENABLE_REG_MWB_ENABLE_BMSK );
    }
    
    return SPMI_SUCCESS;
}

//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiBusCfg_Init(boolean initHw)
{
    uint32 i;
    Spmi_Result rslt;
    SpmiDevInfo *pDev;
    
    if (!initialized) 
    {
        SPMI_LOG_INIT();

        if ((rslt = SpmiOs_Init(&pSpmiInfo)) != SPMI_SUCCESS) {
            return rslt;
        }
        
        initialized = TRUE;
    }
    
    for(i = 0; i < pSpmiInfo->uNumDevices; i++) 
    {
        if(initHw) 
        {
            pDev = SPMI_PDEV(pSpmiInfo, i);    
            if((rslt = SpmiMaster_ConfigHW( pDev, DEFAULT_MASTER_ID, SPMI_CFG_FULL )) != SPMI_SUCCESS) {
                return rslt;
            }
        }
    }

    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_DeInit()
{
    initialized = FALSE;
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_GetChannelInfo(uint8 busId, uint16 channel, uint8* slaveId, uint8* periphId, uint8* owner)
{
    uint8 * base_addr;
    SpmiDevInfo *pDev;

    INIT_CHECK();
    pDev = SPMI_PDEV(pSpmiInfo, busId);
    base_addr = pDev->baseAddrs;
    if(channel >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        return SPMI_FAILURE_INVALID_CHAN_NUM;
    }
    
    *slaveId = SPMI_HWIO_IN_FIELD( HWIO_PMIC_ARB_REG_CHNLn_ADDR( base_addr, channel ),
                                   HWIO_PMIC_ARB_REG_CHNLn_SID );
    
    *periphId = SPMI_HWIO_IN_FIELD( HWIO_PMIC_ARB_REG_CHNLn_ADDR( base_addr, channel ),
                                    HWIO_PMIC_ARB_REG_CHNLn_ADDRESS );
    
    *owner = SPMI_HWIO_IN_FIELD( HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR( base_addr, channel ),
                                 HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER );
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_GetPeripherialInfo(uint8 busId, uint8 slaveId, uint8 periphId, uint16* channel, uint8* owner)
{
    uint32 i;
    uint8 * base_addr;
    SpmiDevInfo *pDev;
    
    INIT_CHECK();
    pDev = SPMI_PDEV(pSpmiInfo, busId);
    base_addr = pDev->baseAddrs;
    
    if(slaveId > SPMI_MAX_SLAVE_ID) {
        return SPMI_FAILURE_INVALID_SLAVE_ID;
    }
    
    uint16 ppid = SLAVE_PERIPH_TO_PPID( slaveId, periphId );

    for(i = 0; i < SPMI_NUM_CHANNELS_SUPPORTED(pDev); i++)
    {
        if(ppid == SPMI_HWIO_IN_FIELD( HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR( base_addr, i ), 
                                       HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID ))
        {
            *channel = i;
            *owner = SPMI_HWIO_IN_FIELD( HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR( base_addr, i ),
                                         HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER );
            return SPMI_SUCCESS;
        }   
    }

    return SPMI_FAILURE_CHANNEL_NOT_FOUND;
}

Spmi_Result SpmiBusCfg_SetDynamicChannelMode(uint8 busId, boolean enabled)
{
    SpmiDevInfo *pDev;
    uint8 * base_addr;
    
    pDev = SPMI_PDEV(pSpmiInfo, busId);
    base_addr = pDev->baseAddrs;    
    // If we are changing the channel -> ppid mapping, the security 
    // and interrupt tables wont be in sync (assuming they were populated)
    // and we dont have the information to update them; so interrupts and security aren't supported.
    if(enabled) 
    {
        SPMI_LOG_WARNING( "Disabling security and interrupts" );
        SPMI_HWIO_OUT_CLEAR( HWIO_SPMI_CMPR_EN_REG_ADDR( base_addr ), HWIO_SPMI_CMPR_EN_REG_CMPR_ENABLE_BMSK );
        SPMI_HWIO_OUT_SET( HWIO_SPMI_SEC_DISABLE_REG_ADDR( base_addr ), HWIO_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_BMSK );
        SPMI_HWIO_OUT_CLEAR( HWIO_SPMI_MWB_ENABLE_REG_ADDR( base_addr ), HWIO_SPMI_MWB_ENABLE_REG_MWB_ENABLE_BMSK );
    }
    
    pDev->dynamicChannelMode = enabled;
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_ConfigureChannel(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* entry, boolean autoAssignChan)
{
    Spmi_Result rslt;
    uint32 reg;
    uint8 * base_addr = pDev->baseAddrs;
    
    if((rslt = assignChannel( pDev, entry, autoAssignChan )) != SPMI_SUCCESS) {
        return rslt;
    }
    
    // Update the channel address translation table - used by owner and observer channels
    reg = SPMI_HWIO_SET_FIELD_VALUE( entry->slaveId, HWIO_PMIC_ARB_REG_CHNLn_SID );
    reg |= SPMI_HWIO_SET_FIELD_VALUE( entry->periphId, HWIO_PMIC_ARB_REG_CHNLn_ADDRESS );
    
    SPMI_HWIO_OUT( HWIO_PMIC_ARB_REG_CHNLn_ADDR( base_addr, entry->channel ), reg );

    if(!pDev->dynamicChannelMode)
    {
        // Update peripheral interrupt ownership table
        reg = SPMI_HWIO_SET_FIELD_VALUE( SLAVE_PERIPH_TO_PPID( entry->slaveId, entry->periphId ),
                                         HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_APID2PPID );

        reg |= SPMI_HWIO_SET_FIELD_VALUE( entry->intOwner,
                                          HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER );

        SPMI_HWIO_OUT( HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR( base_addr, entry->channel ), reg );
    }
    
    SPMI_LOG_VERBOSE( "%sBus Addr:0x%x, PPID %01X %02X (intOwner %d, chanOwner %d) @ chan %d",
                      pDev->dynamicChannelMode ? "*" : "", base_addr,
                      entry->slaveId, entry->periphId, entry->intOwner, 
                      entry->periphOwner, entry->channel );
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_ConfigureChannels(SpmiBusCfg_ChannelCfg* entries, uint32 numEntries)
{
    return configChannels( SPMI_PDEV(pSpmiInfo,0), entries, numEntries, NULL, NULL, FALSE, TRUE, TRUE );
}

Spmi_Result SpmiBusCfg_ConfigurePeripherals(uint8 busId, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries, 
                                            SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount)
{
    return configChannels( SPMI_PDEV(pSpmiInfo,busId), entries, numEntries, rgCfg, rgCount, TRUE, TRUE, FALSE );
}

Spmi_Result SpmiBusCfg_CalculateRGConfig(uint8 busId, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries, 
                                         SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount)
{
    return configChannels( SPMI_PDEV(pSpmiInfo,busId), entries, numEntries, rgCfg, rgCount, TRUE, FALSE, FALSE );
}

Spmi_Result SpmiBusCfg_ConfigurePvcPort(uint8 busId, const SpmiBusCfg_PvcPortCfg* portCfg)
{
    uint32 i;
    uint8 * base_addr;
    SpmiDevInfo *pDev;

    INIT_CHECK();
    pDev = SPMI_PDEV(pSpmiInfo, busId);
    base_addr = pDev->baseAddrs;

    if(portCfg->pvcPortId >= SPMI_NUM_PVC_PORTS(pDev) ) 
    {
        return SPMI_FAILURE_INVALID_PORT_ID;
    }
    
    SPMI_HWIO_OUT_FIELD( HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR( base_addr, portCfg->pvcPortId ), 
                         HWIO_PMIC_ARB_PVC_PORTn_CTL_SPMI_PRIORITY,
                         portCfg->priority );

    if(portCfg->numPpids > SPMI_NUM_PVC_PPIDS(pDev) ) {
        return SPMI_FAILURE_TOO_MANY_ENTRIES;
    }
    
    for(i = 0; i < portCfg->numPpids; i++) 
    {
        if(portCfg->ppids[i].slaveId > SPMI_MAX_SLAVE_ID) {
            return SPMI_FAILURE_INVALID_SLAVE_ID;
        }

        SPMI_HWIO_OUT_FIELD( HWIO_PMIC_ARB_PVCn_ADDRm_ADDR( base_addr, portCfg->pvcPortId, i ), 
                             HWIO_PMIC_ARB_PVCn_ADDRm_SID, 
                             portCfg->ppids[i].slaveId );
        
        SPMI_HWIO_OUT_FIELD( HWIO_PMIC_ARB_PVCn_ADDRm_ADDR( base_addr, portCfg->pvcPortId, i ), 
                             HWIO_PMIC_ARB_PVCn_ADDRm_ADDRESS, 
                             portCfg->ppids[i].address );
    }

    // Enable the individual port
    SPMI_HWIO_OUT_SET( HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR( base_addr , portCfg->pvcPortId ),
                       HWIO_PMIC_ARB_PVC_PORTn_CTL_PVC_PORT_EN_BMSK );

    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_SetPortPriorities(uint8 busId, uint8* ports, uint32 numPorts)
{
    uint32 i;
    SpmiDevInfo *pDev;
    uint8 * base_addr;
    
    INIT_CHECK();
    pDev = SPMI_PDEV(pSpmiInfo, busId);
    base_addr = pDev->baseAddrs;
    
    if(numPorts > SPMI_NUM_PORT_PRIORITIES(pDev)) {
        return SPMI_FAILURE_TOO_MANY_ENTRIES;
    }
    
    for(i = 0; i < numPorts; i++) 
    {
       if(ports[i] > SPMI_NUM_PVC_PORTS(pDev)) {
            return SPMI_FAILURE_INVALID_PORT_ID;
        }

       SPMI_HWIO_OUT( HWIO_PMIC_ARB_PRIORITIESn_ADDR( base_addr, i ), 
                             ports[i] );
    }
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusCfg_SetPVCPortsEnabled(uint8 busId, boolean enable)
{
    uint8 * base_addr;

    INIT_CHECK();
    base_addr = SPMI_BID2ADDR(pSpmiInfo, busId);
    
    SPMI_HWIO_OUT_FIELD( HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR( base_addr ), 
                         HWIO_PMIC_ARB_PVC_INTF_CTL_PVC_INTF_EN, 
                         enable );
    return SPMI_SUCCESS;
}
