/**
 * @file:  SpmiBus.c
 * 
 * Copyright (c) 2013-2016 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/pmic/spmi/src/core/SpmiBus.c#1 $
 * $Change: 11690628 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 11/3/14  Automatic channel assignment
 * 6/19/14  Log Fatal if bus is busy
 * 05/8/14  To check the clock status for every transaction failure reason
 * 10/1/13  Initial Version
 */

#include "SpmiBus.h"
#include "SpmiOs.h"
#include "SpmiLogs.h"
#include "PmicArb.h"
#include "SpmiInfo.h"

//******************************************************************************
// Macros / Definitions
//******************************************************************************

#define NUM_DEBUG_TRANSACTIONS 10
#define NUM_DEBUG_FAILURES 5

#define INIT_CHECK() if(!spmiDrv.initialized) { return SPMI_FAILURE_NOT_INITIALIZED; }

typedef enum {
    NOT_SET,
    STARTED,
    FINISHED,
} BusDbgState;

typedef struct {
    uint8 vsid;
    uint16 pid;
    uint8 data0;
    Spmi_Result result;
    PmicArbCmd cmd;
    uint8 dataLen;
    uint64 startTime;
    uint32 duration;
    uint8 tries;
    BusDbgState state;
} BusDbgInfo;

typedef struct {
    BusDbgInfo info;
    PmicArbHwStatus hwStatus;
} BusErrDbgInfo;

typedef struct {
    uint8  busId;
    uint16 channel;
    uint8  mask;
    uint64 startTime;
    uint32 duration;
} IsrDbgInfo;

typedef struct
{
    uint8 busIdx;
    uint8 errorIdx;
    uint8 isrIdx;
    BusDbgInfo busTrans[NUM_DEBUG_TRANSACTIONS];
    BusErrDbgInfo errorTrans[NUM_DEBUG_FAILURES];
    IsrDbgInfo isrTrans[NUM_DEBUG_TRANSACTIONS];
    uint16 rsltCnt[SPMI_RESULT_MAX];
    boolean syncFlag;
} SpmiBusDebugInfo;

typedef struct _SpmiBusIsrConfig
{
    SpmiIsr isr;
    const void* ctx;
    uint8  bid;
    uint16 chan;
    uint8  mask;
    uint16 id;
    struct _SpmiBusIsrConfig* next;
} SpmiBusIsrConfig;

typedef struct 
{
    boolean initialized;
    uint16  uid;
    SpmiBusIsrConfig*** isrTable;
    SpmiBusDebugInfo debug;
    SpmiInfo        *pSpmiInfo;
} SpmiDrv;

//******************************************************************************
// Global Data
//******************************************************************************

SpmiDrv spmiDrv = {0};
boolean freeIsrNodes = FALSE;

//******************************************************************************
// Local Helper Functions
//******************************************************************************

static inline void debugTransStart(PmicArbCmd cmd, uint8 vSlaveId, uint16 address, uint32 len)
{
    SPMI_LOG_VERBOSE( "cmd %d / vsid: 0x%02x / addr: %x / len: %d", cmd, vSlaveId, address, len );
    
    spmiDrv.debug.busIdx = (spmiDrv.debug.busIdx + 1) % NUM_DEBUG_TRANSACTIONS;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].state = STARTED;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].cmd = cmd;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].vsid = vSlaveId;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].pid = address;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].dataLen = len;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].tries = 0;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].startTime = SpmiOs_GetTimeTick();
}

static inline void debugTransEnd(PmicArbCmd cmd, uint8 vSlaveId, uint16 address, uint32 len, 
                                 uint8* data, uint8 tries, Spmi_Result rslt)
{
    if(spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].cmd == cmd &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].vsid == vSlaveId &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].pid == address &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].dataLen == len) 
    {
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].state = FINISHED;
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].result = rslt;
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].tries = tries;
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].duration = 
        SpmiOs_GetTimeTick() - spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].startTime;
        
        if(data != NULL) {
            spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].data0 = *data;
        }

        if(rslt < SPMI_RESULT_MAX) {
            spmiDrv.debug.rsltCnt[rslt]++;
        }
    }
    else {
        spmiDrv.debug.syncFlag = TRUE;
    }
    
    if(rslt != SPMI_SUCCESS)
    {
        uint8 bid;
        spmiDecodeVSid( vSlaveId, &bid, NULL );
                
        spmiDrv.debug.errorIdx = (spmiDrv.debug.errorIdx + 1) % NUM_DEBUG_FAILURES;
        spmiDrv.debug.errorTrans[spmiDrv.debug.errorIdx].info = spmiDrv.debug.busTrans[spmiDrv.debug.busIdx];
        
        PmicArb_GetHwStatus( SPMI_PDEV(spmiDrv.pSpmiInfo, bid), &spmiDrv.debug.errorTrans[spmiDrv.debug.errorIdx].hwStatus );
        SPMI_LOG_WARNING( "cmd: %d / vsid: 0x%02x / addr: 0x%04x / len: %d / rslt: %d / tries: %d", 
                          cmd, vSlaveId, address, len, rslt,
                          spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].tries);
    }
}

static Spmi_Result debugExecute(PmicArbCmd cmd,
                                Spmi_AccessPriority priority,
                                uint8 vSlaveId,
                                uint16 address,
                                uint8* data,
                                uint32 len,
                                uint32* bytesTransacted)
{
    Spmi_Result rslt;
    boolean retry;
    uint8 slaveId;
    uint8 busId;
    uint8 tries = 0;
    SpmiDevInfo *pDev;
    uint16 channel;
    

    INIT_CHECK();
    
    spmiDecodeVSid( vSlaveId, &busId, &slaveId );
    if(busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo)) {
       return SPMI_FAILURE_INVALID_BUS_ID;
    }
    debugTransStart( cmd, vSlaveId, address, len );
    
    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo,busId);
    do 
    {
        tries++;
        retry = FALSE;
        rslt = PmicArb_FindChannel(pDev, slaveId, REG_ADDR_TO_PERIPH_ID( address ), &channel);
        if (SPMI_SUCCESS == rslt) {
           rslt = PmicArb_ExecuteCommand( pDev, cmd, priority,
                                          spmiDrv.pSpmiInfo->owner, channel,
                                          REG_ADDR_TO_REG_OFFSET( address ),
                                          data, len, bytesTransacted );     
        }

        // Adjust result if a more specific root cause can be found
        if(rslt != SPMI_SUCCESS) 
        {
            if(SpmiOs_GetAhbClkState( pDev ) == SPMI_CLK_OFF) {
                rslt = SPMI_FAILURE_AHB_CLK_IS_OFF;
            }
            else if(SpmiOs_GetSerialClkState( pDev ) == SPMI_CLK_OFF) {
                rslt = SPMI_FAILURE_SERIAL_CLK_IS_OFF;
            }

            retry = SpmiOs_HandleTransactionError( pDev, &rslt, cmd, slaveId, address, tries );
        }

    } while(retry);

    debugTransEnd( cmd, vSlaveId, address, len, data, tries, rslt );
    
    // Fail-fast by catching some irrecoverable errors
    if(rslt == SPMI_FAILURE_TRANSACTION_TIMEOUT) {
        SPMI_LOG_FATAL( "Timeout while executing SPMI transaction" );
    }
    else if(rslt == SPMI_FAILURE_BUS_BUSY) {
        SPMI_LOG_FATAL( "SPMI bus busy" );
    }
    
    return rslt;
}

static void channelIstDispatch(SpmiDevInfo *pDev, uint16 channel, uint8 mask)
{
    uint8 busId =  pDev->uDevIdx;   
    uint64 tick = SpmiOs_GetTimeTick();
    
    spmiDrv.debug.isrIdx = (spmiDrv.debug.isrIdx + 1) % NUM_DEBUG_TRANSACTIONS;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].busId = busId;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].channel = channel;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].mask = mask;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].startTime = tick;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].duration = 0;
    
    // This should never happen since we control the input to this
    if(channel >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        SPMI_LOG_ERROR( "ISR - Invalid channel: %d", channel );
        return;
    }
    
    SPMI_LOG_VERBOSE( "Bus %d ISR on chan %d", busId, channel );
    
    SpmiBusIsrConfig* userIsr = spmiDrv.isrTable[busId][channel];
    
    while(userIsr != NULL)
    {
        if(userIsr->isr != NULL) 
        {
            // Check if they want this particular interrupt
            uint8 userMask = mask & userIsr->mask;
            
            if(userMask)
            {
                SPMI_LOG_VERBOSE( "Calling user ISR with mask %x", userMask );

                uint64 usertick = SpmiOs_GetTimeTick();

                userIsr->isr( (void*)userIsr->ctx, userMask );

                SPMI_LOG_VERBOSE( "User ISR took %llx ticks", SpmiOs_GetTimeTick() - usertick );
            }
            else {
                SPMI_LOG_VERBOSE( "Bus %d ISR (%p) registered for channel %d (user mask %x), but not with this mask: %x ", 
                                  busId, userIsr->isr, channel, userIsr->mask, mask );
            }
        }
        
        userIsr = userIsr->next;
    }
    
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].duration = SpmiOs_GetTimeTick() - tick;
}



static boolean isInterruptOwner(uint8 *base_addr, uint8 owner, uint16 channel)
{
    return owner == SPMI_HWIO_IN_FIELD( HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_ADDR(base_addr, channel ),
                                                   HWIO_SPMI_PERIPHm_2OWNER_TABLE_REG_PERIPH2OWNER );
}

Spmi_Result SpmiPic_SetInterruptEnabled(SpmiDevInfo *pDev, uint8 owner, uint16 channel, boolean enabled)
{
   uint8 * base_addr = pDev->baseAddrs;    
    
    if(!isInterruptOwner( base_addr, owner, channel )) {
        return SPMI_FAILURE_COMMAND_NOT_ALLOWED;
    }
    
    if(channel >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
       return SPMI_FAILURE_INVALID_CHAN_NUM;
    }
    
    SPMI_LOG_VERBOSE( "ISR enabled: %d, Bus addr: 0x%p, Chan: %d, ", enabled, base_addr, channel );
    
    SPMI_HWIO_OUT_FIELD( HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, channel ), 
                         HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE, 
                         enabled );
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiPic_HandleIrq(SpmiDevInfo *pDev, uint8 owner)
{
    uint32 i, k;

    uint8 * base_addr = pDev->baseAddrs; 
    
    for(i = 0; i < SPMI_NUM_PIC_ACC_STATUS_REGS(pDev); i++) 
    {
        // Each bit in these registers represents a peripheral
        uint32 accStatus = SPMI_HWIO_IN( HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR( base_addr, owner, i ) );
        
        for(k = 0; (k < 32) && (accStatus != 0); k++) 
        {
            if((accStatus >> k) & 0x1) 
            {
                // This peripheral (channel) triggered the interrupt.  Check its individual mask
                uint16 channel = (i * 32) + k;
                uint32 accEnableStatus = SPMI_HWIO_IN_FIELD( HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, channel ), 
                                                             HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE);

                if(accEnableStatus) 
                {
                    uint8 mask = SPMI_HWIO_IN_FIELD( HWIO_SPMI_PIC_IRQ_STATUSn_ADDR( base_addr, channel ), 
                                                     HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS );

                    // Clear the status
                    SPMI_HWIO_OUT_FIELD( HWIO_SPMI_PIC_IRQ_CLEARn_ADDR( base_addr, channel ),
                                         HWIO_SPMI_PIC_IRQ_CLEARn_INT_CLEAR, mask );

                    // wait for the status to clear
                    while((mask & SPMI_HWIO_IN_FIELD( HWIO_SPMI_PIC_IRQ_STATUSn_ADDR( base_addr, channel ), HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS )) != 0);

                    channelIstDispatch(pDev, channel, mask);
                }
            }
        }
    }
    
    return SPMI_SUCCESS;
}

static void* SpmiBus_Isr(void* ctx)
{
   SpmiDevInfo *pDev = (SpmiDevInfo*)ctx;     

   if (NULL != pDev) {
      SpmiPic_HandleIrq(pDev, spmiDrv.pSpmiInfo->owner);
   }
   return NULL;
}

//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiBus_Init()
{
    Spmi_Result rslt;
    uint32 bid;
    SpmiDevInfo *pDev;
    
    if(spmiDrv.initialized) {
        return PmicArb_UpdateCache(spmiDrv.pSpmiInfo);
    }
    
    SPMI_LOG_INIT();

    if((rslt = SpmiOs_Init(&spmiDrv.pSpmiInfo)) != SPMI_SUCCESS) {
        return rslt;
    }
    
    if((rslt = PmicArb_Init( spmiDrv.pSpmiInfo)) != SPMI_SUCCESS) {
        return rslt;
    }

    spmiDrv.pSpmiInfo->hasInterruptSupport = FALSE;
    
    for(bid = 0; bid < SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo); bid++)
    {
        pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, bid);
        if((rslt = SpmiOs_RegisterISR( pDev, SpmiBus_Isr )) == SPMI_SUCCESS) {
            spmiDrv.pSpmiInfo->hasInterruptSupport = TRUE;
        }
    }
    
    if(spmiDrv.pSpmiInfo->hasInterruptSupport)
    {
        if((rslt = SpmiOs_Malloc( SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo) * 
                                        sizeof(SpmiBusIsrConfig*),
                                  (void**) &spmiDrv.isrTable )) != SPMI_SUCCESS) {
            return rslt;
        }
    }
    
    spmiDrv.initialized = TRUE;
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBus_DeInit()
{
    SpmiDevInfo *pDev;

    if(spmiDrv.isrTable != NULL) 
    {
        uint32 i, k;

        for(i = 0; i < SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo); i++)
        {
            SpmiBusIsrConfig** busISRs = spmiDrv.isrTable[i];
                        
            if(busISRs != NULL)
            {
                pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, i);    
                for(k = 0; k < SPMI_NUM_CHANNELS_SUPPORTED(pDev); k++)
                {
                    SpmiBusIsrConfig* curr = busISRs[k];
                    while(curr != NULL) 
                    {
                        SpmiBusIsrConfig* t = curr->next;
                        SpmiOs_Free( curr );
                        curr = t;
                    }
                }
                
                SpmiOs_Free( busISRs );
            }
        }
        
        SpmiOs_Free( spmiDrv.isrTable );
        spmiDrv.isrTable = NULL;
    }

    spmiDrv.initialized = FALSE;
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBus_ReadLong(uint32 vSlaveId,
                             Spmi_AccessPriority priority,
                             uint32 address,
                             uint8* data,
                             uint32 len,
                             uint32* bytesRead)
{
    return debugExecute( PMIC_ARB_CMD_EXTENDED_REG_READ_LONG, priority, vSlaveId, address, data, len, bytesRead );
}

Spmi_Result SpmiBus_WriteLong(uint32 vSlaveId,
                              Spmi_AccessPriority priority,
                              uint32 address,
                              uint8* data,
                              uint32 len)
{
    return debugExecute( PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, priority, vSlaveId, address, data, len, NULL );
}

Spmi_Result SpmiBus_Command(uint32 vSlaveId, Spmi_AccessPriority priority, Spmi_Command cmd)
{
    PmicArbCmd pmicArbCmd;
    
    switch(cmd)
    {
        case SPMI_COMMAND_RESET:    pmicArbCmd = PMIC_ARB_CMD_RESET; break;
        case SPMI_COMMAND_SLEEP:    pmicArbCmd = PMIC_ARB_CMD_SLEEP; break;
        case SPMI_COMMAND_SHUTDOWN: pmicArbCmd = PMIC_ARB_CMD_SHUTDOWN; break;
        case SPMI_COMMAND_WAKEUP:   pmicArbCmd = PMIC_ARB_CMD_WAKEUP; break;
        default:
            return SPMI_FAILURE_COMMAND_NOT_SUPPORTED;
    }
    
    return debugExecute( pmicArbCmd, priority, vSlaveId, 0, NULL, 0, NULL );
}

Spmi_Result SpmiBus_RegisterIsr(uint8 vSlaveId,
                                uint8 periph,
                                uint8 mask,
                                const SpmiIsr isr,
                                const void* ctx,
                                SpmiToken* token)
{
    uint16 channel;
    Spmi_Result rslt;
    uint8 slaveId;
    uint8 busId;
    SpmiDevInfo *pDev;

    INIT_CHECK();
    
    if(!spmiDrv.pSpmiInfo->hasInterruptSupport) {
        return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
    }
    
    if(mask == 0 || isr == NULL || token == NULL) {
        return SPMI_FAILURE_INVALID_PARAMETER;
    }
    
    spmiDecodeVSid( vSlaveId, &busId, &slaveId );
    if(busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo)) {
        return SPMI_FAILURE_INVALID_BUS_ID;
    }

    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, busId);
    if((rslt = PmicArb_FindChannel( pDev, slaveId, periph, &channel )) != SPMI_SUCCESS) {
        return rslt;
    }
    
    if(channel >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        SPMI_LOG_WARNING( "Couldn't get channel to set ISR. vSlaveId: %d, periph %d, channel %d", vSlaveId, periph, channel );
        return SPMI_FAILURE_CHANNEL_NOT_FOUND;
    }
    
    SpmiBusIsrConfig*** busISRs = &spmiDrv.isrTable[busId];
    
    if(*busISRs == NULL)
    {
        SPMI_LOG_VERBOSE( "Allocating buf for bus #%d ISRs", busId );
        if((rslt = SpmiOs_Malloc( SPMI_NUM_CHANNELS_SUPPORTED(pDev) * 
                                        sizeof(SpmiBusIsrConfig*),
                                  (void**) busISRs )) != SPMI_SUCCESS) {
            return rslt;
        }
    }
    
    SpmiBusIsrConfig** curr = &((*busISRs)[channel]);
        
    while(*curr != NULL && (*curr)->isr != NULL) 
    {
        curr = &(*curr)->next;
    }
    
    // If curr is null we are adding a node, if it is not null we are reusing a node that was 
    // unregistered, but not freed
    if(*curr == NULL)
    {
        SPMI_LOG_VERBOSE( "Registering new ISR node (bid: %d, chan: %d, mask: %d)", busId, channel, mask );
        if ((rslt = SpmiOs_Malloc( sizeof(SpmiBusIsrConfig), (void**) curr )) != SPMI_SUCCESS) {
            return rslt;
        }
    }
    else {
        SPMI_LOG_VERBOSE( "Registering existing ISR node (bid: %d, chan: %d, mask: %d)", busId, channel, mask );
    }
        
    (*curr)->isr = isr;
    (*curr)->ctx = ctx;
    (*curr)->bid = busId;
    (*curr)->chan = channel;
    (*curr)->mask = mask;
    (*curr)->id = ++spmiDrv.uid;
    
    token->id = (*curr)->id;
    token->bid = busId;
    token->chan = channel;
    
    return SpmiPic_SetInterruptEnabled( pDev, spmiDrv.pSpmiInfo->owner,channel, TRUE );
}

Spmi_Result SpmiBus_UnregisterIsr(SpmiToken* token, uint8 mask)
{
    boolean keepEnabled = FALSE;
    Spmi_Result rslt = SPMI_FAILURE_INVALID_TOKEN;
    SpmiDevInfo *pDev;

    INIT_CHECK();
        
    if(spmiDrv.pSpmiInfo->hasInterruptSupport) {
        return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
    }
    
    if(token == NULL) {
        return SPMI_FAILURE_INVALID_PARAMETER;
    }

    if(token->bid >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo)) 
    {
        SPMI_LOG_ERROR( "Invalid busId: %d", token->bid );
        return SPMI_FAILURE_INVALID_BUS_ID;
    }
    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, token->bid);

    if(token->chan >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) 
    {
        SPMI_LOG_ERROR( "Invalid channel: %d", token->chan );
        return SPMI_FAILURE_CHANNEL_NOT_FOUND;
    }
    
    SpmiBusIsrConfig* curr = spmiDrv.isrTable[token->bid][token->chan];
    SpmiBusIsrConfig* prev = NULL;
    
    while(curr != NULL) 
    {
        if(curr->id == token->id) 
        {
            SPMI_LOG_VERBOSE( "Unregistering ISR (bid %d: chan: %d, mask: %d)", token->bid, token->chan, mask );
            rslt = SPMI_SUCCESS;
            
            // Turn off any interrupts for this node
            curr->mask &= ~mask;

            if(curr->mask == 0) 
            {    
                curr->isr = NULL;
                curr->ctx = NULL;
                curr->id = 0;
                
                // Depending on the usage of register/unregister it might be
                // more efficient to not free the node and just reuse it when needed
                if(freeIsrNodes) 
                {
                    if(prev == NULL) 
                    {
                        spmiDrv.isrTable[token->bid][token->chan] = curr->next;
                        SpmiOs_Free( curr );
                        curr = spmiDrv.isrTable[token->bid][token->chan];
                    }
                    else 
                    {
                        prev->next = curr->next;
                        SpmiOs_Free( curr );
                        curr = prev->next;
                    }
                    
                    // This is just to continue checking if we need to disable 
                    // the actual interrupt in the pmic arb. Otherwise we could quit.
                    continue; 
                }
            }
        }
        
        if(curr->bid == token->bid && 
           curr->chan == token->chan && 
           curr->isr != NULL) 
        {
            keepEnabled = TRUE;
        }

        prev = curr;
        curr = curr->next;
    }
    
    if(!keepEnabled) {
        return SpmiPic_SetInterruptEnabled( pDev, spmiDrv.pSpmiInfo->owner, token->chan, FALSE );
    }
    
    return rslt;
}

Spmi_Result SpmiBus_ReadModifyWriteLongByte(uint32 vSlaveId,
                                            Spmi_AccessPriority priority,
                                            uint32 address,
                                            uint32 data,
                                            uint32 mask,
                                            uint8 *byteWritten)
{
    Spmi_Result rslt;
    uint8 readData;

    if((rslt = SpmiBus_ReadLong( vSlaveId, priority, address, &readData, 1, NULL )) != SPMI_SUCCESS) {
        return rslt;
    }

    readData &= ~mask;
    readData |= data & mask;

    if((rslt = SpmiBus_WriteLong( vSlaveId, priority, address, &readData, 1 )) != SPMI_SUCCESS) {
        return rslt;
    }

    *byteWritten = readData;

    return SPMI_SUCCESS;
}
