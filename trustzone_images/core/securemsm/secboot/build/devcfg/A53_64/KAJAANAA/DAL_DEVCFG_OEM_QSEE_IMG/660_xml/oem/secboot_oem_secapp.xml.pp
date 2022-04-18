# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem_secapp.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 327 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem_secapp.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem.h" 1
# 33 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h" 1
# 28 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned int uint32;




typedef unsigned short uint16;




typedef unsigned char uint8;




typedef signed int int32;




typedef signed short int16;




typedef signed char int8;
# 64 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned long long uint64;




typedef long long int64;





typedef unsigned char byte;





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
# 108 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
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
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem.h" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h" 1
# 41 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdio.h" 1







# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/features.h" 1
# 9 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdio.h" 2
# 22 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdio.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h" 1





typedef __builtin_va_list va_list;




typedef __builtin_va_list __isoc_va_list;
# 104 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef unsigned long size_t;
# 119 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef long ssize_t;
# 206 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef long off_t;
# 359 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef struct _IO_FILE FILE;
# 23 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdio.h" 2
# 52 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/stdio.h"
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);

char *fgets(char *restrict, int, FILE *restrict);




int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

int printf(const char *restrict, ...);
int fprintf(FILE *restrict, const char *restrict, ...);
int sprintf(char *restrict, const char *restrict, ...);
int snprintf(char *restrict, size_t, const char *restrict, ...);

int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

int scanf(const char *restrict, ...);
int fscanf(FILE *restrict, const char *restrict, ...);
int sscanf(const char *restrict, const char *restrict, ...);
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);




char *cuserid(char *);
void setlinebuf(FILE *);
void setbuffer(FILE *, char *, size_t);
int fgetc_unlocked(FILE *);
int fputc_unlocked(int, FILE *);
int fflush_unlocked(FILE *);
size_t fread_unlocked(void *, size_t, size_t, FILE *);
size_t fwrite_unlocked(const void *, size_t, size_t, FILE *);
void clearerr_unlocked(FILE *);
int feof_unlocked(FILE *);
int ferror_unlocked(FILE *);
int fileno_unlocked(FILE *);
int getw(FILE *);
int putw(int, FILE *);
char *fgetln(FILE *, size_t *);
int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, __isoc_va_list);
# 42 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h" 2
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/string.h" 1
# 25 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/string.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h" 1
# 371 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h"
typedef struct __locale_struct * locale_t;
# 26 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/string.h" 2

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



# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/strings.h" 1
# 11 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/strings.h"
# 1 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/bits/alltypes.h" 1
# 12 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/strings.h" 2




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
# 60 "/pkg/qct/software/llvm/release/arm/3.7.6/tools/lib64/include/string.h" 2





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
# 43 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h" 2





typedef enum
{
    CEML_ERROR_SUCCESS = 0x0,
    CEML_ERROR_FAILURE = 0x1,
    CEML_ERROR_INVALID_PARAM = 0x2,
    CEML_ERROR_NOT_SUPPORTED = 0x3,
    CEML_ERROR_SHK_NOT_BLOWN = 0x4
} CeMLErrorType;

typedef struct CeMLHashAlgoCntxType CeMLHashAlgoCntxType;

typedef struct CeMLCipherAlgoCntxType CeMLCipherAlgoCntxType;

typedef struct
{
  void *pvBase;
  uint32 dwLen;
}CEMLIovecType;

typedef struct
{
  CEMLIovecType *iov;
  uint32 size;
}CEMLIovecListType;

typedef enum
{
   CEML_HASH_ALGO = 0x1,
   CEML_CIPHER_ALGO = 0x2
} CeMLAlgoType;

typedef enum
{
    CEML_HASH_ALGO_SHA1 = 0x1,
    CEML_HASH_ALGO_SHA256 = 0x2,
    CEML_HASH_ALGO_INVALID = 0x7FFFFFFF
  } CeMLHashAlgoType;

typedef enum
  {
    CEML_HASH_MODE_HASH = 0x0,
    CEML_HASH_MODE_HMAC = 0x1,
    CEML_HASH_MODE_INVALID = 0x7FFFFFFF
  } CeMLHashModeType;

typedef enum
  {
    CEML_HASH_FIRST = 0,
    CEML_HASH_LAST = 1,
    CEML_HASH_SEQ_INVALID = 0x7FFFFFFF
  } CeMLHashSeqType;

typedef enum
  {
    CEML_HASH_PARAM_MODE = 0x01,
    CEML_HASH_PARAM_HMAC_KEY = 0x02,
    CEML_HASH_PARAM_AUTH_KEY = 0x03,
    CEML_HASH_PARAM_SEQ = 0x04,
    CEML_HASH_PARAM_INVALID = 0x7FFFFFFF
  } CeMLHashParamType;
# 121 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
typedef enum
{
    CEML_CIPHER_MODE_ECB = 0x0,
    CEML_CIPHER_MODE_CBC = 0x1,
    CEML_CIPHER_MODE_CTR = 0x2,
    CEML_CIPHER_MODE_XTS = 0x3,
    CEML_CIPHER_MODE_CCM = 0x4,
    CEML_CIPHER_MODE_CTS = 0x5,
    CEML_CIPHER_MODE_INVALID = 0x6,
  } CeMLCipherModeType;

typedef enum
  {
    CEML_CIPHER_ENCRYPT = 0x00,
  CEML_CIPHER_DECRYPT = 0x01
  } CeMLCipherDir;

typedef enum
  {
    CEML_CIPHER_PARAM_DIRECTION = 0x01,
    CEML_CIPHER_PARAM_KEY = 0x02,
    CEML_CIPHER_PARAM_IV = 0x03,
    CEML_CIPHER_PARAM_MODE = 0x04,
    CEML_CIPHER_PARAM_NONCE = 0x05,
    CEML_CIPHER_PARAM_XTS_KEY = 0x06,
    CEML_CIPHER_PARAM_XTS_DU_SIZE = 0x07,
    CEML_CIPHER_PARAM_CCM_PAYLOAD_LEN = 0x08,
    CEML_CIPHER_PARAM_CCM_MAC_LEN = 0x09,
    CEML_CIPHER_PARAM_HW_KEY_TYPE = 0x0A,
    CEML_CIPHER_PARAM_CCM_HDR_LEN = 0x10,
    CEML_CIPHER_PARAM_INVALID = 0x11
  } CeMLCipherParamType;
# 164 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
typedef enum
  {
    CEML_CIPHER_ALG_AES128 = 0x0,
    CEML_CIPHER_ALG_AES256 = 0x1,
    CEML_CIPHER_ALG_TRIPLE_DES = 0x2,
    CEML_CIPHER_ALG_INVALID = 0xFF,
  } CeMLCipherAlgType;

typedef enum
  {
    CEML_CIPHER_HW_KEY_OEM = 0,
  CEML_CIPHER_HW_KEY_QC = 1
  } CeMLCipherHWKeyType;

typedef struct
{
  void * pClientCtxt;
} CeMLCntxHandle;
# 194 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLInit (void);
# 209 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLDeInit (void);
# 223 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherReset(CeMLCntxHandle *ceMlHandle);
# 237 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLHashReset(CeMLCntxHandle *ceMlHandle);
# 251 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashInit (CeMLCntxHandle ** _h,
                     CeMLHashAlgoType pAlgo);
# 266 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashDeInit (CeMLCntxHandle ** _h);
# 283 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashUpdate (CeMLCntxHandle * _h,
                     CEMLIovecListType ioVecIn);
# 299 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashFinal (CeMLCntxHandle * _h,
                     CEMLIovecListType * ioVecOut);
# 317 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashAtomic (CeMLCntxHandle * _h,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType * ioVecOut);
# 338 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHmac (uint8 * key_ptr,
                     uint32 keylen,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType * ioVecOut,
                     CeMLHashAlgoType pAlgo);
# 361 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLCmac (uint8 *key_ptr,
                     uint32 keylen,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType *ioVecOut,
                     CeMLCipherAlgType pAlgo);
# 381 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashSetParam (CeMLCntxHandle * _h,
                     CeMLHashParamType nParamID,
                     const void *pParam,
                     uint32 cParam,
                     CeMLHashAlgoType pAlgo );
# 399 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLHashSetParamAsU32(CeMLCntxHandle *_h,
                                    CeMLHashParamType nParamID,
                                    const void *pParam);
# 416 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLHashSetParamAsData(CeMLCntxHandle *_h,
                                       CeMLHashParamType nParamID,
                                       const void *pParam,
                                       size_t cParam,
                                       CeMLHashAlgoType pAlgo);
# 434 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLCipherInit (CeMLCntxHandle ** _h,
                     CeMLCipherAlgType pAlgo);
# 449 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLCipherDeInit (CeMLCntxHandle ** _h);
# 465 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherSetParamAsU32(CeMLCntxHandle *_h,
                                                                         CeMLCipherParamType nParamID,
                                                                         void *pParam);
# 482 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherSetParamAsData(CeMLCntxHandle *_h,
                                                                          CeMLCipherParamType nParamID,
                                                                          const void *pParam,
                                                                          size_t cParam);
# 499 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherGetParamAsU32(CeMLCntxHandle *_h,
                                                                         CeMLCipherParamType nParamID,
                                                                         uint32 *pnOut);
# 516 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherGetParamAsData(CeMLCntxHandle *_h,
                                                                           CeMLCipherParamType nParamID,
                                                                           void *pParam,
                                                                           size_t *cParam);
# 537 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherSetParam (CeMLCntxHandle * ceMlHandle,
                                  CeMLCipherParamType nParamID,
                                  void *pParam,
                                  size_t cParam);
# 557 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLCipherGetParam (CeMLCntxHandle * _h,
                       CeMLCipherParamType nParamID,
                       void *pParam,
                       size_t *cParam );
# 577 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLCipherData (CeMLCntxHandle * _h,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType * ioVecOut);
# 595 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLHmacInit(CeMLCntxHandle** cntx,
                           CeMLHashAlgoType pAlgo);
# 610 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLHmacUpdate(CeMLCntxHandle* cntx,
                             CEMLIovecListType ioVecIn);
# 626 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType CeMLHmacFinal(CeMLCntxHandle* cntx,
                            CEMLIovecListType *ioVecOut);
# 646 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/cryptodrivers/ce/shared/inc/CeML.h"
CeMLErrorType
CeMLHashCipherData(CeMLCntxHandle *_h1,
                   CeMLCntxHandle *_h2,
                   CEMLIovecListType ioVecIn,
                   CEMLIovecListType * ioVecOut,
                   uint8 * hash_out,
                   uint32 hash_out_len);
# 35 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem.h" 2
# 50 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem.h"
typedef struct {
  uint8 root_of_trust[32];
} SecbootRootOfTrustType;
# 2 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.7.1-00006-S660AAAAANAZT-2_20200329_233006/b/HK11/trustzone_images/core/securemsm/secboot/honeybadger/oem/secboot_oem_secapp.xml" 2

<driver name="NULL">
  <!--
 <device id="/secboot/oem_secapp">
    <props name="sec_app_roots_of_trust" type="SecbootRootOfTrustType" array="True">
    {
      {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
      },
      {
        0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
        0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
        0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A,
        0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42,
      },
    }
    </props>
  <props name="use_root_of_trust_only" type=DALPROP_ATTR_TYPE_UINT32>
   0
  </props>
  <props name="msm_hw_id_upper" type=DALPROP_ATTR_TYPE_UINT32>
   0x9ABCDEF0
  </props>
  <props name="msm_hw_id_lower" type=DALPROP_ATTR_TYPE_UINT32>
   0xDEADBEEF
  </props>
  <props name="auth_use_serial_num" type=DALPROP_ATTR_TYPE_UINT32>
   1
  </props>
  <props name="serial_num" type=DALPROP_ATTR_TYPE_UINT32>
   0x12345678
  </props>
 </device>
  -->
</driver>
