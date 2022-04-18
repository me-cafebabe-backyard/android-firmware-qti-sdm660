typedef unsigned long uintptr_t;
typedef long intptr_t;
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef long intmax_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef unsigned long uintmax_t;
typedef int8_t int_fast8_t;
typedef int64_t int_fast64_t;
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_fast8_t;
typedef uint64_t uint_fast64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef unsigned char boolean;
typedef uint32_t bool32;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uintptr_t uintnt;
typedef uint8_t byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned char uint1;
typedef unsigned short uint2;
typedef unsigned int uint4;
typedef signed char int1;
typedef signed short int2;
typedef long int int4;
typedef signed int sint31;
typedef signed short sint15;
typedef signed char sint7;
typedef uint16 UWord16 ;
typedef uint32 UWord32 ;
typedef int32 Word32 ;
typedef int16 Word16 ;
typedef uint8 UWord8 ;
typedef int8 Word8 ;
typedef int32 Vect32 ;
      typedef long long int64;
      typedef unsigned long long uint64;
        typedef struct __attribute__((packed))
        { uint16 x; }
        unaligned_uint16;
        typedef struct __attribute__((packed))
        { uint32 x; }
        unaligned_uint32;
        typedef struct __attribute__((packed))
        { uint64 x; }
        unaligned_uint64;
        typedef struct __attribute__((packed))
        { int16 x; }
        unaligned_int16;
        typedef struct __attribute__((packed))
        { int32 x; }
        unaligned_int32;
        typedef struct __attribute__((packed))
        { int64 x; }
        unaligned_int64;
  extern dword rex_int_lock(void);
  extern dword rex_int_free(void);
    extern dword rex_fiq_lock(void);
    extern void rex_fiq_free(void);
   extern void rex_task_lock( void);
   extern void rex_task_free( void);
typedef unsigned long UINTN;
typedef uint32 DALBOOL;
typedef uint32 DALDEVICEID;
typedef uint32 DalPowerCmd;
typedef uint32 DalPowerDomain;
typedef uint32 DalSysReq;
typedef UINTN DALHandle;
typedef int DALResult;
typedef void * DALEnvHandle;
typedef void * DALSYSEventHandle;
typedef uint32 DALMemAddr;
typedef UINTN DALSYSMemAddr;
typedef uint32 DALInterfaceVersion;
typedef unsigned char * DALDDIParamPtr;
typedef struct DALEventObject DALEventObject;
struct DALEventObject
{
    uint32 obj[8];
};
typedef DALEventObject * DALEventHandle;
typedef struct _DALMemObject
{
   uint32 memAttributes;
   uint32 sysObjInfo[2];
   uint32 dwLen;
   uint32 ownerVirtAddr;
   uint32 virtAddr;
   uint32 physAddr;
}
DALMemObject;
typedef struct _DALDDIMemBufDesc
{
   uint32 dwOffset;
   uint32 dwLen;
   uint32 dwUser;
}
DALDDIMemBufDesc;
typedef struct _DALDDIMemDescList
{
   uint32 dwFlags;
   uint32 dwNumBufs;
   DALDDIMemBufDesc bufList[1];
}
DALDDIMemDescList;
typedef struct DALSysMemDescBuf DALSysMemDescBuf;
struct DALSysMemDescBuf
{
   DALSYSMemAddr VirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   uint32 size;
   uint32 user;
};
typedef struct DALSysMemDescList DALSysMemDescList;
struct DALSysMemDescList
{
   uint32 dwObjInfo; uint32 hOwnerProc; DALSYSMemAddr thisVirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   DALSYSMemAddr VirtualAddr;
   uint32 dwCurBufIdx;
   uint32 dwNumDescBufs;
   DALSysMemDescBuf BufInfo[1];
};
typedef struct DalDeviceInfo DalDeviceInfo;
struct DalDeviceInfo
{
   uint32 sizeOfActual;
   uint32 Version;
   char Name[32];
};
typedef struct DalDeviceStatus DalDeviceStatus;
struct DalDeviceStatus
{
   uint32 sizeOfActual;
   uint32 Status;
};
typedef struct DalDeviceHandle DalDeviceHandle;
typedef struct DalDevice DalDevice;
struct DalDevice
{
   DALResult (*Attach)(const char*,DALDEVICEID,DalDeviceHandle **);
   uint32 (*Detach)(DalDeviceHandle *);
   DALResult (*Init)(DalDeviceHandle *);
   DALResult (*DeInit)(DalDeviceHandle *);
   DALResult (*Open)(DalDeviceHandle *, uint32);
   DALResult (*Close)(DalDeviceHandle *);
   DALResult (*Info)(DalDeviceHandle *, DalDeviceInfo *, uint32);
   DALResult (*PowerEvent)(DalDeviceHandle *, DalPowerCmd, DalPowerDomain);
   DALResult (*SysRequest)(DalDeviceHandle *, DalSysReq, const void *, uint32,
                           void *,uint32, uint32*);
};
typedef struct DalInterface DalInterface;
struct DalInterface
{
   struct DalDevice DalDevice;
};
struct DalDeviceHandle
{
   uint32 dwDalHandleId;
   const DalInterface *pVtbl;
   void *pClientCtxt;
};
typedef struct DalDeviceHandle * DALDEVICEHANDLE;
typedef struct DalRemoteHandle DalRemoteHandle;
typedef struct DalRemote DalRemote;
struct DalRemote
{
   struct DalDevice DalDevice;
   DALResult (* FCN_0) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1 );
   DALResult (* FCN_1) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32 u2 );
   DALResult (* FCN_2) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32* p_u2 );
   DALResult (* FCN_3) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32 u2, uint32 u3 );
   DALResult (* FCN_4) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32 u2, uint32* p_u3 );
   DALResult (* FCN_5) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen);
   DALResult (* FCN_6) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * ibuf, uint32 ilen);
   DALResult (* FCN_7) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * obuf, uint32 olen, uint32 *oalen);
   DALResult (* FCN_8) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * obuf, uint32 olen);
   DALResult (* FCN_9) ( uint32 ddi_idx, DalDeviceHandle *h, void * obuf, uint32 olen );
   DALResult (* FCN_10)( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * ibuf, uint32 ilen, void * obuf, uint32 olen, uint32 * oalen);
   DALResult (* FCN_11) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * obuf, uint32 olen);
   DALResult (* FCN_12) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * obuf, uint32 olen, uint32 *oalen);
   DALResult (* FCN_13) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * ibuf2, uint32 ilen2, void * obuf, uint32 olen);
   DALResult (* FCN_14) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * obuf1, uint32 olen, void * obuf2, uint32 olen2, uint32 * oalen);
   DALResult (* FCN_15) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * ibuf2, uint32 ilen2, void * obuf2, uint32 olen2, uint32 *oalen, void * obuf, uint32 olen );
};
struct DalRemoteHandle
{
   uint32 dwDalHandleId;
   const DalRemote *pVtbl;
   void *pClientCtxt;
};
static __inline uint32
DalDevice_Detach(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Detach(_h);
}
static __inline DALResult
DalDevice_Init(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Init(_h);
}
static __inline DALResult
DalDevice_DeInit(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.DeInit(_h);
}
static __inline DALResult
DalDevice_PowerEvent(DalDeviceHandle *_h, DalPowerCmd PowerCmd,
                     DalPowerDomain PowerDomain)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.PowerEvent(_h,PowerCmd,PowerDomain);
}
static __inline DALResult
DalDevice_Open(DalDeviceHandle *_h, uint32 mode)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Open(_h,mode);
}
static __inline DALResult
DalDevice_Close(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Close(_h);
}
static __inline DALResult
DalDevice_Info(DalDeviceHandle *_h, DalDeviceInfo* info, uint32 infoSize)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Info(_h,info,infoSize);
}
static __inline DALResult
DalDevice_SysRequest(DalDeviceHandle *_h, DalSysReq ReqIdx,
                     const unsigned char* SrcBuf, int SrcBufLen,
                     unsigned char* DestBuf, uint32 DestBufLen, uint32* DestBufLenReq)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.SysRequest(_h,ReqIdx,SrcBuf,SrcBufLen,
                                          DestBuf,DestBufLen,DestBufLenReq);
}
DALResult
DAL_DeviceAttach(DALDEVICEID DeviceId,
                 DalDeviceHandle **phDevice);
DALResult
DAL_DeviceAttachLocal(const char *pszArg,DALDEVICEID DeviceId,
                      DalDeviceHandle **phDevice);
DALResult
DAL_DeviceAttachEx(const char *pszArg, DALDEVICEID DeviceId,
               DALInterfaceVersion ClientVersion,DalDeviceHandle **phDevice);
DALResult
DAL_DeviceAttachRemote(const char *pszArg,
                   DALDEVICEID DevId,
                   DALInterfaceVersion ClientVersion,
                   DalDeviceHandle **phDALDevice);
DALResult
DAL_DeviceDetach(DalDeviceHandle *hDevice);
DALResult
DAL_StringDeviceAttachLocal(const char *pszArg, const char *pszDevName,
                           DalDeviceHandle **phDalDevice);
DALResult
DAL_StringDeviceAttach(const char *pszDevName, DalDeviceHandle **phDalDevice);
DALResult
DAL_StringDeviceAttachEx(const char *pszArg,
      const char *pszDevName,
      DALInterfaceVersion ClientVersion,
      DalDeviceHandle **phDALDevice);
typedef struct DALREG_DriverInfo DALREG_DriverInfo;
struct DALREG_DriverInfo
{
 DALResult (*pfnDALNewFunc)(const char * , DALDEVICEID, DalDeviceHandle**);
 uint32 dwNumDevices;
 DALDEVICEID *pDeviceId;
};
typedef struct DALREG_DriverInfoList DALREG_DriverInfoList;
struct DALREG_DriverInfoList
{
 uint32 dwLen;
 DALREG_DriverInfo ** pDriverInfo;
};
typedef unsigned long DevCfgMemAddr;
typedef DevCfgMemAddr *DALSYSPropertyHandle;
typedef struct DALSYSPropertyVar DALSYSPropertyVar;
struct DALSYSPropertyVar
{
    uint32 dwType;
    uint32 dwLen;
    union
    {
        byte *pbVal;
        char *pszVal;
        uint32 dwVal;
        uint32 *pdwVal;
        const void *pStruct;
    }Val;
};
typedef struct DALSYSPropStructTblType DALSYSPropStructTblType ;
struct DALSYSPropStructTblType{
   uint32 dwSize;
   const void *pStruct;
};
typedef struct StringDevice StringDevice;
 struct StringDevice{
   const char *pszName;
   uint32 dwHash;
   uint32 dwOffset;
   DALREG_DriverInfo *pFunctionName;
   uint32 dwNumCollision;
   const uint32 *pdwCollisions;
};
typedef struct DALProps DALProps;
struct DALProps
{
   const byte *pDALPROP_PropBin;
   const void **pDALPROP_StructPtrs;
   const uint32 dwDeviceSize;
   const StringDevice *pDevices;
};
typedef enum
{
   DEVCFG_PROP_INFO_SOC,
   DEVCFG_PROP_INFO_PLATFORM,
   DEVCFG_PROP_INFO_INTERNAL,
   DEVCFG_PROP_INFO_OEM
}DEVCFG_PROP_INFO_TYPE;
typedef unsigned long size_t;
typedef struct __locale_struct * locale_t;
void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);
char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);
char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);
int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);
int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);
char *strchr (const char *, int);
char *strrchr (const char *, int);
size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);
size_t strlen (const char *);
char *strerror (int);
int bcmp (const void *, const void *, size_t);
void bcopy (const void *, void *, size_t);
void bzero (void *, size_t);
char *index (const char *, int);
char *rindex (const char *, int);
int ffs (int);
int ffsl (long);
int ffsll (long long);
int strcasecmp (const char *, const char *);
int strncasecmp (const char *, const char *, size_t);
int strcasecmp_l (const char *, const char *, locale_t);
int strncasecmp_l (const char *, const char *, size_t, locale_t);
char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);
void *memccpy (void *restrict, const void *restrict, int, size_t);
char *strsep(char **, const char *);
size_t strlcat (char *, const char *, size_t);
size_t strlcpy (char *, const char *, size_t);
DALResult
DALSYS_GetDALPropertyHandle(DALDEVICEID DeviceId, DALSYSPropertyHandle hDALProps);
DALResult
DALSYS_GetDALPropertyHandleEx(DALDEVICEID DeviceId,DALSYSPropertyHandle hDALProps,
                              DEVCFG_PROP_INFO_TYPE prop_info_type);
DALResult
DALSYS_GetDALPropertyHandleStr(const char *pszDevName, DALSYSPropertyHandle hDALProps);
DALResult
DALSYS_GetDALPropertyHandleStrEx(const char *pszDevName, DALSYSPropertyHandle hDALProps,
                                 DEVCFG_PROP_INFO_TYPE prop_info_type);
DALResult
DALSYS_GetPropertyValue(DALSYSPropertyHandle hDALProps, const char *pszName,
                  uint32 dwId,
                   DALSYSPropertyVar *pDALPropVar);
typedef void * DALSYSObjHandle;
typedef void * DALSYSSyncHandle;
typedef void * DALSYSMemHandle;
typedef void * DALSYSWorkLoopHandle;
typedef DALSYSMemAddr *DALSYSPropertyHandle;
typedef struct DALSYSEventObj DALSYSEventObj;
struct DALSYSEventObj
{
   unsigned long long _bSpace[64/sizeof(unsigned long long)];
};
typedef struct DALSYSSyncObj DALSYSSyncObj;
struct DALSYSSyncObj
{
   unsigned long long _bSpace[40/sizeof(unsigned long long)];
};
typedef struct DALSYSMemObj DALSYSMemObj;
struct DALSYSMemObj
{
   unsigned long long _bSpace[64/sizeof(unsigned long long)];
};
typedef struct DALSYSWorkLoopEventObj DALSYSWorkLoopEventObj;
struct DALSYSWorkLoopEventObj
{
   unsigned long long _bSpace[32/sizeof(unsigned long long)];
};
typedef struct DALSYSWorkLoopObj DALSYSWorkLoopObj;
struct DALSYSWorkLoopObj
{
   unsigned long long _bSpace[40/sizeof(unsigned long long)];
};
typedef void * DALSYSCallbackFuncCtx;
typedef void * (*DALSYSCallbackFunc)(void*,uint32,void*,uint32);
typedef struct DALSYSMemInfo DALSYSMemInfo;
struct DALSYSMemInfo
{
    DALSYSMemAddr VirtualAddr;
    DALSYSMemAddr PhysicalAddr;
    uint32 dwLen;
    uint32 dwMappedLen;
    uint32 dwProps;
};
typedef struct DALSYSBaseObj DALSYSBaseObj;
struct DALSYSBaseObj
{
   uint32 dwObjInfo;
   uint32 hOwnerProc;
   DALSYSMemAddr thisVirtualAddr;
};
typedef struct DALSYSMemObjBase DALSYSMemObjBase;
struct DALSYSMemObjBase
{
   uint32 dwObjInfo; uint32 hOwnerProc; DALSYSMemAddr thisVirtualAddr;
   uint32 dwLen;
   DALSYSMemAddr OwnerVirtualAddr;
   DALSYSMemAddr VirtualAddr;
   DALSYSMemAddr PhysicalAddr;
};
typedef DALResult
(*DALSYSWorkLoopExecute)
(
    DALSYSEventHandle,
    void *
);
typedef void
(*DALSYS_InitSystemHandleFncPtr)
(
    DalDeviceHandle * hDalDevice
);
typedef DALResult
(*DALSYS_DestroyObjectFncPtr)
(
    DALSYSObjHandle
);
typedef DALResult
(*DALSYS_CopyObjectFncPtr)
(
    DALSYSObjHandle,
    DALSYSObjHandle *
);
typedef DALResult
(*DALSYS_RegisterWorkLoopFncPtr)
(
    uint32,
    uint32,
    DALSYSWorkLoopHandle *,
    DALSYSWorkLoopObj *
);
typedef DALResult
(*DALSYS_AddEventToWorkLoopFncPtr)
(
    DALSYSWorkLoopHandle,
    DALSYSWorkLoopExecute,
    void *,
    DALSYSEventHandle,
    DALSYSSyncHandle
);
typedef DALResult
(*DALSYS_DeleteEventFromWorkLoopFncPtr)
(
    DALSYSWorkLoopHandle,
    DALSYSEventHandle
);
typedef DALResult
(*DALSYS_EventCreateFncPtr)
(
    uint32 ,
    DALSYSEventHandle *,
    DALSYSEventObj *
);
typedef DALResult
(*DALSYS_EventCtrlFncPtr)
(
    DALSYSEventHandle,
    uint32,
   uint32,
   void *,
   uint32
);
typedef DALResult
(*DALSYS_EventWaitFncPtr)
(
    DALSYSEventHandle
);
typedef DALResult
(*DALSYS_EventMultipleWaitFncPtr)
(
    DALSYSEventHandle*,
    int,
    uint32,
    uint32 *
);
typedef DALResult
(*DALSYS_SetupCallbackEventFncPtr)
(
    DALSYSEventHandle,
    DALSYSCallbackFunc,
    DALSYSCallbackFuncCtx
);
typedef DALResult
(*DALSYS_SyncCreateFncPtr)
(
    uint32,
    DALSYSSyncHandle *,
    DALSYSSyncObj *
);
typedef void
(*DALSYS_SyncEnterFncPtr)
(
    DALSYSSyncHandle
);
typedef void
(*DALSYS_SyncLeaveFncPtr)
(
    DALSYSSyncHandle
);
typedef DALResult
(*DALSYS_MemRegionAllocFncPtr)
(
    uint32,
    DALSYSMemAddr,
    DALSYSMemAddr,
    uint32,
    DALSYSMemHandle *,
    DALSYSMemObj *
);
typedef DALResult
(*DALSYS_MemRegionMapPhysFncPtr)
(
    DALSYSMemHandle,
    uint32,
    DALSYSMemAddr,
    uint32
);
typedef DALResult
(*DALSYS_MemInfoFncPtr)
(
    DALSYSMemHandle,
    DALSYSMemInfo *
);
typedef DALResult
(*DALSYS_CacheCommandFncPtr)
(
    uint32 ,
    DALSYSMemAddr,
    uint32
);
typedef DALResult
(*DALSYS_MallocFncPtr)
(
    uint32 ,
    void **
);
typedef DALResult
(*DALSYS_FreeFncPtr)
(
    void *
);
typedef void
(*DALSYS_BusyWaitFncPtr)
(
   uint32
);
typedef DALResult
(*DALSYS_MemDescAddBufFncPtr)
(
    DALSysMemDescList *,
    uint32,
    uint32,
    uint32
);
typedef DALResult
(*DALSYS_MemDescPrepareFncPtr)
(
    DALSysMemDescList *,
    uint32
);
typedef DALResult
(*DALSYS_MemDescValidateFncPtr)
(
    DALSysMemDescList *,
    uint32
);
typedef DALResult
(*DALSYS_GetDALPropertyHandleFncPtr)
(
    DALDEVICEID,
    DALSYSPropertyHandle
);
typedef DALResult
(*DAL_DeviceAttachFncPtr)
(
    const char *pszArg,
    DALDEVICEID,
    DalDeviceHandle **
);
typedef DALResult
(*DAL_DeviceDetachFncPtr)
(
    DalDeviceHandle *
);
typedef DALResult
(*DAL_DeviceAttachExFncPtr)
(
 const char *pszArg,
    DALDEVICEID DevId,
    DALInterfaceVersion ClientVersion,
    DalDeviceHandle **phDalDevice
);
typedef DALResult
(*DALSYS_GetPropertyValueFncPtr)
(
    DALSYSPropertyHandle,
    const char *,
    uint32,
    DALSYSPropertyVar *
);
typedef void
(*DALSYS_LogEventFncPtr)
(
    DALDEVICEID,
    uint32,
    const char *
);
typedef struct DALSYSFncPtrTbl DALSYSFncPtrTbl;
struct DALSYSFncPtrTbl
{
    DALSYS_InitSystemHandleFncPtr DALSYS_InitSystemHandleFnc;
    DALSYS_DestroyObjectFncPtr DALSYS_DestroyObjectFnc;
    DALSYS_CopyObjectFncPtr DALSYS_CopyObjectFnc;
    DALSYS_RegisterWorkLoopFncPtr DALSYS_RegisterWorkLoopFnc;
    DALSYS_AddEventToWorkLoopFncPtr DALSYS_AddEventToWorkLoopFnc;
    DALSYS_DeleteEventFromWorkLoopFncPtr DALSYS_DeleteEventFromWorkLoopFnc;
    DALSYS_EventCreateFncPtr DALSYS_EventCreateFnc;
    DALSYS_EventCtrlFncPtr DALSYS_EventCtrlFnc;
    DALSYS_EventWaitFncPtr DALSYS_EventWaitFnc;
    DALSYS_EventMultipleWaitFncPtr DALSYS_EventMultipleWaitFnc;
    DALSYS_SetupCallbackEventFncPtr DALSYS_SetupCallbackEventFnc;
    DALSYS_SyncCreateFncPtr DALSYS_SyncCreateFnc;
    DALSYS_SyncEnterFncPtr DALSYS_SyncEnterFnc;
    DALSYS_SyncLeaveFncPtr DALSYS_SyncLeaveFnc;
    DALSYS_MemRegionAllocFncPtr DALSYS_MemRegionAllocFnc;
    DALSYS_MemRegionMapPhysFncPtr DALSYS_MemRegionMapPhysFnc;
    DALSYS_MemInfoFncPtr DALSYS_MemInfoFnc;
    DALSYS_CacheCommandFncPtr DALSYS_CacheCommandFnc;
    DALSYS_MallocFncPtr DALSYS_MallocFnc;
    DALSYS_FreeFncPtr DALSYS_FreeFnc;
    DALSYS_BusyWaitFncPtr DALSYS_BusyWaitFnc;
    DALSYS_MemDescAddBufFncPtr DALSYS_MemDescAddBufFnc;
    DALSYS_MemDescPrepareFncPtr DALSYS_MemDescPrepareFnc;
    DALSYS_MemDescValidateFncPtr DALSYS_MemDescValidateFnc;
    DALSYS_GetDALPropertyHandleFncPtr DALSYS_GetDALPropertyHandleFnc;
    DAL_DeviceAttachFncPtr DALSYS_DeviceAttachFnc;
  DAL_DeviceAttachExFncPtr DALSYS_DeviceAttachExFnc;
  DAL_DeviceAttachExFncPtr DALSYS_DeviceAttachRemoteFnc;
    DAL_DeviceDetachFncPtr DALSYS_DeviceDetachFnc;
    DALSYS_GetPropertyValueFncPtr DALSYS_GetPropertyValueFnc;
    DALSYS_LogEventFncPtr DALSYS_LogEventFnc;
};
typedef DALResult
(*DALRemote_NewFncPtr)(const char *, DALDEVICEID, DalDeviceHandle **);
typedef int
(*DALRemote_CommonInitFncPtr)(void);
typedef void
(*DALRemote_IPCInitFcnPtr)(uint32);
typedef void
(*DALRemote_InitFncPtr)(void);
typedef DALSYSEventHandle
(*DALRemote_CreateEventFncPtr)(void *pClientCtxt, DALSYSEventHandle hRemote);
typedef uint32
(*DALRemoteInterProcessCallFncPtr)(void *in_buf, void *out_buf);
typedef void
(*DALRemote_DeinitFncPtr)(void);
typedef struct DALRemoteVtbl DALRemoteVtbl;
struct DALRemoteVtbl
{
   DALRemote_NewFncPtr DALRemote_NewFnc;
   DALRemote_CommonInitFncPtr DALRemote_CommonInitFnc;
   DALRemote_InitFncPtr DALRemote_InitFnc;
   DALRemote_DeinitFncPtr DALRemote_DeinitFnc;
   DALRemote_CreateEventFncPtr DALRemote_CreateEventFnc;
   DALRemote_CreateEventFncPtr DALRemote_CreatePayloadEventFnc;
   DALRemoteInterProcessCallFncPtr DALRemoteInterProcessCallFnc;
   DALRemote_IPCInitFcnPtr DALRemote_IPCInitFcn;
};
typedef struct DALSYSConfig DALSYSConfig;
struct DALSYSConfig
{
    void *pNativeEnv;
    uint32 dwConfig;
   DALRemoteVtbl *pRemoteVtbl;
};
void
DALSYS_InitMod(DALSYSConfig * pCfg);
void
DALSYS_DeInitMod(void);
void
DALSYS_InitSystemHandle(DalDeviceHandle *hDalDevice);
DALSYS_LogEventFncPtr
DALSYS_SetLogCfg(uint32 dwMaxLogLevel, DALSYS_LogEventFncPtr DALSysLogFcn);
DALResult
DALSYS_DestroyObject(DALSYSObjHandle hObj);
DALResult
DALSYS_CopyObject(DALSYSObjHandle hObjOrig, DALSYSObjHandle *phObjCopy );
DALResult
DALSYS_RegisterWorkLoop(uint32 dwPriority,
                  uint32 dwMaxNumEvents,
                  DALSYSWorkLoopHandle *phWorkLoop,
                  DALSYSWorkLoopObj *pWorkLoopObj);
DALResult
DALSYS_AddEventToWorkLoop(DALSYSWorkLoopHandle hWorkLoop,
                    DALSYSWorkLoopExecute pfnWorkLoopExecute,
                    void * pArg,
                    DALSYSEventHandle hEvent,
                    DALSYSSyncHandle hSync);
DALResult
DALSYS_DeleteEventFromWorkLoop(DALSYSWorkLoopHandle hWorkLoop,
                         DALSYSEventHandle hEvent);
DALResult
DALSYS_EventCreate(uint32 dwAttribs, DALSYSEventHandle *phEvent,
               DALSYSEventObj *pEventObj);
DALResult
DALSYS_EventCopy(DALSYSEventHandle hEvent,
             DALSYSEventHandle *phEventCopy,DALSYSEventObj *pEventObjCopy,
                 uint32 dwMarshalFlags);
DALResult
DALSYS_EventCtrlEx(DALSYSEventHandle hEvent, uint32 dwCtrl, uint32 dwParam,
                   void *pPayload, uint32 dwPayloadSize);
DALResult
DALSYS_EventWait(DALSYSEventHandle hEvent);
DALResult
DALSYS_EventMultipleWait(DALSYSEventHandle* phEvent, int nEvents,
                         uint32 dwTimeoutUs,uint32 *pdwEventIdx);
DALResult
DALSYS_SetupCallbackEvent(DALSYSEventHandle hEvent, DALSYSCallbackFunc cbFunc,
                          DALSYSCallbackFuncCtx cbFuncCtx);
DALResult
DALSYS_SyncCreate(uint32 dwAttribs,
                  DALSYSSyncHandle *phSync,
                  DALSYSSyncObj *pSyncObj);
void
DALSYS_SyncEnter(DALSYSSyncHandle hSync);
void
DALSYS_SyncLeave(DALSYSSyncHandle hSync);
DALResult
DALSYS_MemRegionAlloc(uint32 dwAttribs, DALSYSMemAddr VirtualAddr,
                      DALSYSMemAddr PhysicalAddr, uint32 dwLen, DALSYSMemHandle *phMem,
                  DALSYSMemObj *pMemObj);
DALResult
DALSYS_MemRegionMapPhys(DALSYSMemHandle hMem, uint32 dwVirtualBaseOffset,
                        DALSYSMemAddr PhysicalAddr, uint32 dwLen);
DALResult
DALSYS_MemInfo(DALSYSMemHandle hMem, DALSYSMemInfo *pMemInfo);
DALResult
DALSYS_CacheCommand(uint32 CacheCmd, DALSYSMemAddr VirtualAddr, uint32 dwLen);
DALResult
DALSYS_Malloc(uint32 dwSize, void **ppMem);
DALResult
DALSYS_Realloc(uint32 dwSize, void **ppMem);
DALResult
DALSYS_Free(void *pmem);
void
DALSYS_BusyWait(uint32 pause_time_us);
void
DALSYS_LogEvent(DALDEVICEID DeviceId, uint32 dwLogEventType, const char * pszFmt,
                ...);
DALRemoteVtbl *
DALSYS_GetRemoteInterfaceVtbl(void);
uint32 DALSYS_SetThreadPriority(uint32 priority);
uint32 _DALSYS_memscpy(void * pDest, uint32 iDestSz,
      const void * pSrc, uint32 iSrcSize);
typedef enum
{
    TZBSP_CFG_SUCCESS = 0x00,
    TZBSP_CFG_INVALID_INPUT = 0x01,
    TZBSP_CFG_BUFFER_TOO_SMALL = 0x02,
    TZBSP_CFG_ERROR_GET_PROP_HDLSTR = 0x03,
    TZBSP_CFG_ERROR_GET_PROP_VALUE = 0x04,
    TZBSP_CFG_ERROR_MEMSCPY = 0x05,
    TZBSP_CFG_UNKNOWN_TYPE = 0x06,
    TZBSP_CFG_MAX_ERROR_CODE = 0x7FFFFFFF
} tzbsp_cfg_error;
typedef struct
{
    uint32 dwType;
    uint32 dwLen;
    uint8 val[1];
} tzbsp_cfg_propvar_t;
typedef struct
{
    uint32 wQseeFatalErrFlag;
    uint32 wOemFatalErrFlag;
} tzbsp_reset_reason_pair_t;
typedef struct
{
    uint32 dwCount;
    tzbsp_reset_reason_pair_t *rst_reason;
} tzbsp_cfg_oem_reset_reason_t;
tzbsp_cfg_error tzbsp_cfg_getpropval
(
    const char *PropName,
    uint32 PropNameLen,
    uint32 PropId,
    tzbsp_cfg_propvar_t *pPropBuf,
    uint32 PropBufSz,
    uint32 *PropBufSzRet
);
static tzbsp_reset_reason_pair_t rst_reason_list[] =
{
  {0 , 0},
  {1 , 1},
  {2 , 2},
  {3 , 3},
  {4 , 4},
  {5 , 5},
  {6 , 6},
  {7 , 7},
  {8 , 8},
  {9 , 9},
  {10 , 10},
  {11 , 11},
  {12 , 12},
  {13 , 13},
  {14 , 14},
  {15 , 15},
  {16 , 16},
  {17 , 17},
  {18 , 18},
  {19 , 19},
  {20 , 20},
  {21 , 21},
  {22 , 22},
  {23 , 23},
  {24 , 24},
  {25 , 25},
  {26 , 26},
  {27 , 27},
  {28 , 28},
  {29 , 29},
  {30 , 30},
  {31 , 31},
  {32 , 32},
  {33 , 33},
  {34 , 34},
  {35 , 35},
  {36 , 36},
  {37 , 37},
  {38 , 38},
  {39 , 39},
  {40 , 40},
  {41 , 41},
  {42 , 42},
  {43 , 43},
  {44 , 44},
  {45 , 45},
  {46 , 46},
  {47 , 47},
  {48 , 48},
  {49 , 49},
  {50 , 50},
  {51 , 51},
  {52 , 52},
  {53 , 53},
  {54 , 54},
  {55 , 55},
  {56 , 56},
  {57 , 57},
  {58 , 58},
  {59 , 59},
  {60 , 60},
  {0xFFFFFFFF , 0xDEADD00D},
};
tzbsp_cfg_oem_reset_reason_t oem_rst_reason_list =
{
  sizeof(rst_reason_list)/sizeof(tzbsp_reset_reason_pair_t),
  rst_reason_list
};
