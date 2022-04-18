/**
 * @file:  PmicArb.c
 * 
 * Copyright (c) 2013-2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/hal/bear/PmicArb.c#2 $
 * $Change: 11185940 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 12/5/14  Added check to limit the spmi channels equal to spmi interrupts
 * 11/3/14  Automatic channel assignment
 * 05/8/14  Moved the clock status check to other file.
 * 10/1/13  Initial Version
 */

#include "PmicArb.h"
#include "SpmiUtils.h"
#include "SpmiHal.h"
#include "SpmiLogs.h"
#include "SpmiOs.h"
#include "SpmiInfo.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define INVALID_SID -1
#define INVALID_DATA ((int16)0x200)

// Max number of bytes we can read/write at a time.
#define MAX_TRANSACTION_LEN 8

//******************************************************************************
// Global Data
//******************************************************************************


//******************************************************************************
// Local Helper Functions
//******************************************************************************


static void writeSpmiData(uint8 *base_addr, uint8 owner, uint16 channel, uint8* data, uint32 bytesToWrite)
{
    uint32 i;
    uint32 tmp = 0;
    
    for(i = 0; i < sizeof(uint32) && bytesToWrite > 0; i++, bytesToWrite--) {
        ((uint8*)&tmp)[i] = data[i];
    }
    
    SPMI_HWIO_OUT( HWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR( base_addr, owner, channel ), tmp );
    
    if(bytesToWrite > 0)
    {
        tmp = 0;
        for(i = 0; i < sizeof(uint32) && bytesToWrite > 0; i++, bytesToWrite--) {
            ((uint8*)&tmp)[i] = data[i + sizeof(uint32)];
        }
        
        SPMI_HWIO_OUT( HWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR( base_addr, owner, channel ), tmp );
    }
}

static void readSpmiData(uint8 *base_addr, uint8 owner, uint16 channel, uint8* data, uint32 bytesToRead)
{
    uint32 i;

    uint32 spmiData = SPMI_HWIO_IN( HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR( base_addr, owner, channel ) );
        
    for(i = 0; i < sizeof(uint32) && bytesToRead > 0; i++, bytesToRead--) {
        data[i] = ((uint8*)&spmiData)[i];
    }

    if(bytesToRead > 0)
    {
        spmiData = SPMI_HWIO_IN( HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR( base_addr, owner, channel ) );

        for(i = 0; i < sizeof(uint32) && bytesToRead > 0; i++, bytesToRead--) {
            data[i + sizeof(uint32)] = ((uint8*)&spmiData)[i];
        }
    }
}

static Spmi_Result waitForStatusDone(uint8 *base_addr, uint8 owner, boolean isObserver, uint16 channel)
{
    uint32 status = 0;
    uint32 timeout = SPMI_TIMEOUT_USEC;
    Spmi_Result result = SPMI_SUCCESS;
    
    while(status == 0 && timeout-- > 0)
    {
        SpmiOs_Wait( 1 );
        status = isObserver ? SPMI_HWIO_IN( HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR( base_addr, owner, channel ) ) :
                              SPMI_HWIO_IN( HWIO_PMIC_ARBq_CHNLn_STATUS_ADDR( base_addr, owner, channel ) );
    }
    
    if(status & HWIO_PMIC_ARBq_CHNLn_STATUS_DROPPED_BMSK) 
    {
        result = SPMI_FAILURE_TRANSACTION_DROPPED;
    }
    else if(status & HWIO_PMIC_ARBq_CHNLn_STATUS_DONE_BMSK)
    {
        if(status & HWIO_PMIC_ARBq_CHNLn_STATUS_FAILURE_BMSK) {
            result = SPMI_FAILURE_TRANSACTION_FAILED;
        }
        else if(status & HWIO_PMIC_ARBq_CHNLn_STATUS_DENIED_BMSK) {
            result = SPMI_FAILURE_TRANSACTION_DENIED;
        }
    }
    else if(SPMI_HWIO_IN_FIELD(HWIO_SPMI_GENI_CTRL_ADDR( base_addr ), HWIO_SPMI_GENI_CTRL_M_GENI_DISABLE) ) {
        result = SPMI_FAILURE_BUS_DISABLED;
    }
    else {
        result = SPMI_FAILURE_TRANSACTION_TIMEOUT;
    }

    return result;
}

static __inline boolean isTransactionDone(uint8 *base_addr, uint8 owner, boolean isObserver, uint16 channel)
{
    if(isObserver) {
        return SPMI_HWIO_IN_FIELD( HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR( base_addr, owner, channel ),
                                   HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE );
    } else {
        return SPMI_HWIO_IN_FIELD( HWIO_PMIC_ARBq_CHNLn_STATUS_ADDR( base_addr, owner, channel ),
                                   HWIO_PMIC_ARBq_CHNLn_STATUS_DONE );
    }
}

static __inline void writeCommand(uint8 *base_addr,
                                  uint8 owner, 
                                  boolean isObserver,
                                  PmicArbCmd cmd,
                                  uint16 channel,
                                  Spmi_AccessPriority priority,
                                  uint8 regOffset,
                                  uint32 len)
{
    if(isObserver) 
    {
        SPMI_HWIO_OUT( HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR( base_addr, owner, channel ),
                      (cmd                      << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_SHFT)   |
                      (SPMI_ACCESS_PRIORITY_LOW << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_SHFT) |
                      (regOffset                << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_SHFT)  |
                      (len                      << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_SHFT) );
    }
    else 
    {
        SPMI_HWIO_OUT( HWIO_PMIC_ARBq_CHNLn_CMD_ADDR( base_addr, owner, channel ),
                      (cmd       << HWIO_PMIC_ARBq_CHNLn_CMD_OPCODE_SHFT)   |
                      (priority  << HWIO_PMIC_ARBq_CHNLn_CMD_PRIORITY_SHFT) |
                      (regOffset << HWIO_PMIC_ARBq_CHNLn_CMD_ADDRESS_SHFT)  |
                      (len       << HWIO_PMIC_ARBq_CHNLn_CMD_BYTE_CNT_SHFT) );
    }
}


//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result PmicArb_Init(SpmiInfo *pSpmiInfo)
{
    Spmi_Result rslt;

    if((rslt = SpmiHal_Init()) != SPMI_SUCCESS) {
        return rslt;
    }
    
    // Cache all ppid -> channel mappings
    PmicArb_UpdateCache(pSpmiInfo);
    
    return SPMI_SUCCESS;
}

Spmi_Result PmicArb_InvalidateCache(SpmiDevInfo *pDev)
{
    uint32 k;
    
    for(k = 0; k <= SPMI_MAX_PERIPH_ID; k++) {
       pDev->periphMap[k] = INVALID_DATA;
        }

    for(k = 0; k < SPMI_NUM_CHANNELS_SUPPORTED(pDev); k++) {
       pDev->channelMap[k].sid = INVALID_SID;
       pDev->channelMap[k].nextIdx = INVALID_DATA;
    }
    
    return SPMI_SUCCESS;
}

Spmi_Result PmicArb_UpdateCache(SpmiInfo *pSpmiInfo)
{
    uint32 bid, chan;
    SpmiDevInfo *pDev;
    
    for(bid = 0; bid < pSpmiInfo->uNumDevices; bid++) 
    {
        pDev = SPMI_PDEV(pSpmiInfo,bid);
        uint8 * base_addr = pDev->baseAddrs;

        PmicArb_InvalidateCache(pDev);    
        for(chan = 0; chan < SPMI_NUM_CHANNELS_SUPPORTED(pDev); chan++) 
    {
            uint32 regChan = SPMI_HWIO_IN( HWIO_PMIC_ARB_REG_CHNLn_ADDR( base_addr, chan ) );
            uint8 sid = SPMI_HWIO_GET_FIELD_VALUE( regChan, HWIO_PMIC_ARB_REG_CHNLn_SID );
            uint8 addr = SPMI_HWIO_GET_FIELD_VALUE( regChan, HWIO_PMIC_ARB_REG_CHNLn_ADDRESS );

            PmicArb_AddCacheEntry( pDev, chan, sid, addr );
        }
    }
    
    return SPMI_SUCCESS;
}

Spmi_Result PmicArb_RemoveCacheEntry(SpmiDevInfo *pDev, uint32 chan)
{
   ChannelMapEntry* entry;
    int16* pMap = pDev->periphMap;
    ChannelMapEntry* cMap = pDev->channelMap;

    if(chan >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        return SPMI_FAILURE_INVALID_CHAN_NUM;
    }

    entry = &cMap[chan];

    if(entry->sid != INVALID_SID) 
    {
        int16 prevIdx = chan;
        uint8 periph;

        SPMI_LOG_TRACE( "  removing chan %d (out of chain)", chan);

        // Go around the world to locate the previous entry in the chain        
        while ((cMap[prevIdx].nextIdx & INVALID_DATA) == 0)
        {
            prevIdx = cMap[prevIdx].nextIdx;
        }

        periph = (uint8)(cMap[prevIdx].nextIdx & ~INVALID_DATA);
        prevIdx = pMap[periph];

        while( (prevIdx & INVALID_DATA) == 0 &&
               prevIdx != chan && 
               cMap[prevIdx].nextIdx != chan )
        {
            prevIdx = cMap[prevIdx].nextIdx;
        }

        if(prevIdx & INVALID_DATA)
        {
            return SPMI_BUS_FAILURE_GENERAL_FAILURE;
        }
    
        // pull newEntry out of its chain
        if(prevIdx != chan)
    {
            cMap[prevIdx].nextIdx = entry->nextIdx;
        }
        else
        {
            // This was the start of a chain -- update periphMap.
            pMap[periph] = entry->nextIdx;
            SPMI_LOG_TRACE( "  New head ptr - periph: %x, idx: %x", periph, pMap[periph]);
        }
        
        entry->sid = INVALID_SID;
        entry->nextIdx = INVALID_DATA;
    }
    
    return SPMI_SUCCESS;
}

Spmi_Result PmicArb_AddCacheEntry(SpmiDevInfo *pDev, uint32 chan, uint8 sid, uint8 periph)
{
    int16 chanIdx;
    boolean newRoot = FALSE;
    ChannelMapEntry* entry;
    ChannelMapEntry* newEntry;


    int16* pMap = pDev->periphMap;
    ChannelMapEntry* cMap = pDev->channelMap;
    
    if(chan >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        return SPMI_FAILURE_INVALID_CHAN_NUM;
    }
    
    if(pDev->reservedChanEn && (chan == pDev->reservedChan)) {
                SPMI_LOG_VERBOSE( "Not caching reserved channel: %d", chan);
                return SPMI_FAILURE_CHANNEL_RESERVED;
            }
    
    newEntry = &cMap[chan];
    
    SPMI_LOG_TRACE( "Add to cache - base_addr: 0x%p, chan %d: sid: %d, periph: %d (0x%x)",
                    pDev->baseAddrs, chan, sid, periph, periph );

    if(pMap[periph] == INVALID_DATA)
    {
        SPMI_LOG_TRACE("  first hit empty");
        newRoot = TRUE;
        pMap[periph] = chan;
    }
    
    // 1st entry
    chanIdx = pMap[periph];
    entry = &cMap[chanIdx];

    // If this isn't the start of a new chain, follow the existing one
    if(!newRoot)
    {
        int16 nextIdx = chanIdx;

        // go till the end of the chain or we hit the replacement
        do
        {
            chanIdx = nextIdx;
            entry = &cMap[chanIdx];
            nextIdx = entry->nextIdx;
            
            if(entry->sid == sid) {
                SPMI_LOG_TRACE( "  Ignoring dup @ chan %d", chanIdx );
                return SPMI_SUCCESS;
            }

            if(chanIdx == chan) {
                SPMI_LOG_TRACE( "  overwriting chan %d (in chain)", chan );
                newEntry->sid = sid;
                return SPMI_SUCCESS;
            }

        } while((entry->nextIdx & INVALID_DATA) == 0);
    }
        
    if(newEntry->sid != INVALID_SID) 
    {
        return SPMI_BUS_FAILURE_GENERAL_FAILURE;
    }

    // Extend the chain to new node
    entry->nextIdx = chan;

    newEntry->sid = sid;
    newEntry->nextIdx = INVALID_DATA | periph;

    return SPMI_SUCCESS;
}

void PmicArb_GetHwStatus(SpmiDevInfo *pDev, PmicArbHwStatus* status)
{
    uint8 * base_addr = pDev->baseAddrs;    
    if(status == NULL) {
        return;
    }
    
    status->irqStatus = SPMI_HWIO_IN( HWIO_SPMI_PROTOCOL_IRQ_STATUS_ADDR( base_addr ) );
    status->geniStatus = SPMI_HWIO_IN( HWIO_SPMI_GENI_STATUS_ADDR( base_addr ) );
    status->geniCtrl = SPMI_HWIO_IN( HWIO_SPMI_GENI_CTRL_ADDR( base_addr ) );
}


Spmi_Result PmicArb_FindChannel(SpmiDevInfo *pDev, uint8 slaveId, uint8 periph, uint16* channel)
{
    int16 idx;
    
    
    idx = pDev->periphMap[periph];
    
    while ((idx & INVALID_DATA) == 0)
    {
        ChannelMapEntry* entry = &pDev->channelMap[idx];

        if (entry->sid == slaveId) {
            *channel = idx;
            SPMI_LOG_TRACE( "Found chan: bid: %d, sid %d, periph: 0x%x = %d", 
                            bid, slaveId, periph, idx );
            return SPMI_SUCCESS;
        }

        idx = entry->nextIdx;
    }
    
    SPMI_LOG_TRACE( "Chan not found: bid: %d, sid %d, periph: 0x%x",
                    bid, slaveId, periph );
    
    // This peripheral is not supported
    return SPMI_FAILURE_CHANNEL_NOT_FOUND;
}


Spmi_Result PmicArb_ExecuteCommand(SpmiDevInfo *pDev,
                                   PmicArbCmd cmd,
                                   Spmi_AccessPriority priority,
                                   uint8 owner,
                                   uint16 channel,
                                   uint16 offset,
                                   uint8* data,
                                   uint32 dataLen,
                                   uint32* bytesTransacted)
{
    uint32 tmp;
    boolean doRead = FALSE;
    boolean doWrite = FALSE;
    uint8 * base_addr = pDev->baseAddrs;
    
         
    if(data == NULL || dataLen == 0) {
        return SPMI_FAILURE_INVALID_BUFFER;
    }
    
    if(bytesTransacted == NULL) {
        bytesTransacted = &tmp;
    }

    *bytesTransacted = 0;    
    
    switch(cmd)
    {
        case PMIC_ARB_CMD_EXTENDED_REG_READ_LONG:
            doRead = TRUE;
            break;
            
        case PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG:
            doWrite = TRUE;
            break;

        default:
            return SPMI_FAILURE_COMMAND_NOT_SUPPORTED;
    }
    
    while(dataLen > 0)
    {
        Spmi_Result result;
        
        // Check if the Done bit is set. If not, the previous transaction is stuck
        if(!isTransactionDone( base_addr, owner, doRead, channel )) {
            return SPMI_FAILURE_BUS_BUSY;
        }
    
        uint32 len = dataLen > MAX_TRANSACTION_LEN ? MAX_TRANSACTION_LEN : dataLen;
        
        if(doWrite) {
            writeSpmiData( base_addr, owner, channel, data + *bytesTransacted, len );
        }
        
        // This is the signal to start the transaction
        // len - 1 because value of 0 means 1 byte and increments from there
        writeCommand( base_addr, owner, doRead, cmd, channel, priority, offset + *bytesTransacted, len - 1 );
        
        if((result = waitForStatusDone( base_addr, owner, doRead, channel )) != SPMI_SUCCESS) {
            return result;
        }
        
        if(doRead) {
            readSpmiData( base_addr, owner, channel, data + *bytesTransacted, len );
        }
        
        dataLen -= len;
        *bytesTransacted += len;
    }
    
    return SPMI_SUCCESS;
}



