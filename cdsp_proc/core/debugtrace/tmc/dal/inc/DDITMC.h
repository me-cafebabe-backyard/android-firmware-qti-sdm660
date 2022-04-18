#ifndef DDITMC_H
#define DDITMC_H

//========================================================================
//
//                             Edit History
//
// $Header: //components/rel/core.qdsp6/1.0.c2/debugtrace/tmc/dal/inc/DDITMC.h#1 $
//
//========================================================================
//             Copyright (c) 2011 Qualcomm Technologies Incorporated.
//                    All Rights Reserved.
//                    QUALCOMM Proprietary
//========================================================================

#include "DalDevice.h"

#define DALTMC_STRING_INTERFACE_VERSION DALINTERFACE_VERSION(1,1)

#define TMC_MODE_CIRCULAR_BUFFER  0x0
#define TMC_MODE_SW_FIFO          0x1
#define TMC_MODE_HW_FIFO          0x2


typedef struct DalTMC DalTMC;
struct DalTMC
{
   struct DalDevice DalDevice;
   DALResult (*GetMode)(DalDeviceHandle * _h,uint8 *pMode);
   DALResult (*SetMode)(DalDeviceHandle * _h,uint8 mode);
   DALResult (*GetTraceBuffer)(DalDeviceHandle * _h,uint32 *pdwAddr, uint32 *pdwBufLen);
   DALResult (*SetTraceBuffer)(DalDeviceHandle * _h,uint32 dwAddr, uint32 dwBufLen);

   DALResult (*EnableTrace)(DalDeviceHandle * _h);
   DALResult (*DisableTrace)(DalDeviceHandle * _h);
   DALResult (*ReadTrace)(DalDeviceHandle * _h, byte * buf, uint32  nBufLen, uint32 * pnLenRead);
   DALResult (*Flush)(DalDeviceHandle * _h, int  flags);
   DALResult (*GetParam)(DalDeviceHandle * _h, uint32  param, uint32  *uVal);
   DALResult (*SetParam)(DalDeviceHandle * _h, uint32  param, uint32  uVal);
   DALResult (*SaveRegisters)(DalDeviceHandle * _h, byte *buf, uint32 nBufLen);
};

typedef struct DalTMCHandle DalTMCHandle;
struct DalTMCHandle
{
   uint32 dwDalHandleId;
   const DalTMC * pVtbl;
   void * pClientCtxt;
};

#define DAL_TMCDeviceAttach(DevId,hDalDevice)\
        DAL_StringDeviceAttachEx(NULL,DevId,DALTMC_STRING_INTERFACE_VERSION,hDalDevice)


static __inline DALResult
DalTMC_GetMode(DalDeviceHandle * _h,uint8 *pMode)
{
   return ((DalTMCHandle *)_h)->pVtbl->GetMode( _h,pMode);
}

static __inline DALResult
DalTMC_SetMode(DalDeviceHandle * _h,uint8 mode)
{
   return ((DalTMCHandle *)_h)->pVtbl->SetMode( _h, mode);
}

static __inline DALResult
DalTMC_GetTraceBuffer(DalDeviceHandle * _h,uint32 *pdwAddr, uint32 *pdwBufLen)
{
   return ((DalTMCHandle *)_h)->pVtbl->GetTraceBuffer(_h,pdwAddr,pdwBufLen);
}

static __inline DALResult
DalTMC_SetTraceBuffer(DalDeviceHandle * _h,uint32 dwAddr, uint32 dwBufLen)
{
   return ((DalTMCHandle *)_h)->pVtbl->SetTraceBuffer( _h,dwAddr,dwBufLen);
}



static __inline DALResult
DalTMC_EnableTrace(DalDeviceHandle * _h)
{
   return ((DalTMCHandle *)_h)->pVtbl->EnableTrace( _h);
}


static __inline DALResult
DalTMC_DisableTrace(DalDeviceHandle * _h)
{
   return ((DalTMCHandle *)_h)->pVtbl->DisableTrace( _h);
}


static __inline DALResult
DalTMC_ReadTrace(DalDeviceHandle * _h, byte * buf, uint32  nBufLen, uint32 * pnLenRead)
{
   return ((DalTMCHandle *)_h)->pVtbl->ReadTrace( _h, buf, nBufLen, pnLenRead);
}

#define TMC_FLUSH_NOBLOCK 0
#define TMC_FLUSH_BLOCK   1
#define TMC_FLUSH_STOP    2


static __inline DALResult
DalTMC_Flush(DalDeviceHandle * _h, int  flags)
{
   return ((DalTMCHandle *)_h)->pVtbl->Flush( _h, flags);
}


static __inline DALResult
DalTMC_GetParam(DalDeviceHandle * _h, uint32  param, uint32  *puVal)
{
   return ((DalTMCHandle *)_h)->pVtbl->GetParam( _h, param, puVal);
}


static __inline DALResult
DalTMC_SetParam(DalDeviceHandle * _h, uint32  param, uint32  uVal)
{
   return ((DalTMCHandle *)_h)->pVtbl->SetParam( _h, param, uVal);
}


static __inline DALResult
DalTMC_SaveRegisters(DalDeviceHandle * _h, byte * buf, uint32  nBufLen)
{
   return ((DalTMCHandle *)_h)->pVtbl->SaveRegisters( _h, buf, nBufLen);
}


#endif //DDITMC_H
