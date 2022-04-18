#/**
 * @file:  SpmiOsImage.c
 * 
 * Copyright (c) 2013-2016 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/pmic/spmi/src/platform/os/rpm/SpmiOsImage.c#1 $
 * $Change: 11690628 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 11/3/14  Automatic channel assignment
 * 10/1/13  Initial Version
 */

#include "SpmiOs.h"
#include "busywait.h"
#include "SpmiInfo.h"
#include "SpmiOsLogs.h"
#include "SpmiOsTarget.h"
#include "SpmiLogs.h"
#include "timetick.h"
#include "DALSys.h"

//******************************************************************************
// Global Data
//******************************************************************************

extern SpmiInfo * pSpmiBlockInfo;

ULogHandle spmiLogHandle;

static boolean timeInit = FALSE;
static SpmiOs_IsrPtr spmiIsr = NULL;
static void* spmiCtx = NULL;
static uint32 interruptNum;

//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiOs_Init(SpmiInfo **ppSpmiInfo)
{
   *ppSpmiInfo = pSpmiBlockInfo;
   return SPMI_SUCCESS;
}

boolean SpmiOs_HandleTransactionError(SpmiDevInfo *pDev, Spmi_Result* rslt, PmicArbCmd cmd, 
                                      uint8 slaveId, uint16 address, uint8 tries)
{
    return FALSE;
}

void SpmiOs_Wait(uint32 us)
{
    busywait( us );
}

Spmi_Result SpmiOs_Malloc(uint32 size, void** buf)
{
    if(DALSYS_Malloc( size, buf ) == DAL_SUCCESS) {
        DALSYS_memset( *buf, 0, size );
        return SPMI_SUCCESS;
    }    
    
    return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
}

Spmi_Result SpmiOs_Free(void* buf)
{
    if(DALSYS_Free( buf ) == DAL_SUCCESS) {
        return SPMI_SUCCESS;
    }
    
    return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
}

static void spmiIsrWrapper(void) __irq
{
    spmiIsr( spmiCtx );
    interrupt_clear( interruptNum );
}

Spmi_Result SpmiOs_RegisterISR(SpmiDevInfo *pDev, SpmiOs_IsrPtr isr)
{
    SpmiTargetConfig *pSpmiTgt = (SpmiTargetConfig*)pDev->target;
    
    if(isr == NULL) {
        return SPMI_FAILURE_INVALID_PARAMETER;
    }
    
    interruptNum = pSpmiTgt->interruptVec;
    spmiIsr = isr;
    spmiCtx = pDev;
    interrupt_set_isr( interruptNum, spmiIsrWrapper );
    interrupt_configure( interruptNum, LEVEL_HIGH );
    interrupt_enable( interruptNum );
    
    return SPMI_SUCCESS;
}

uint64 SpmiOs_GetTimeTick(void)
{
    if(!timeInit) {
        timetick_init();
        timeInit = TRUE;
    }
    
    return timetick_get64();
}

SpmiOs_ClkStatus SpmiOs_GetSerialClkState(SpmiDevInfo *pDev)
{
    return SPMI_CLK_STATUS_NOT_SUPPORTED;
}

SpmiOs_ClkStatus SpmiOs_GetAhbClkState(SpmiDevInfo *pDev)
{
    return SPMI_CLK_STATUS_NOT_SUPPORTED;
}
