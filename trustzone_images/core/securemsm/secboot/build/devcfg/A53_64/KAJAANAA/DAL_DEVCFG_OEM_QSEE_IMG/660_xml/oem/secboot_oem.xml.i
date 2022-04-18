typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;
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
typedef __builtin_va_list va_list;
typedef __builtin_va_list __isoc_va_list;
typedef unsigned long size_t;
typedef long ssize_t;
typedef long off_t;
typedef struct _IO_FILE FILE;
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
CeMLErrorType
CeMLInit (void);
CeMLErrorType
CeMLDeInit (void);
CeMLErrorType CeMLCipherReset(CeMLCntxHandle *ceMlHandle);
CeMLErrorType CeMLHashReset(CeMLCntxHandle *ceMlHandle);
CeMLErrorType
CeMLHashInit (CeMLCntxHandle ** _h,
                     CeMLHashAlgoType pAlgo);
CeMLErrorType
CeMLHashDeInit (CeMLCntxHandle ** _h);
CeMLErrorType
CeMLHashUpdate (CeMLCntxHandle * _h,
                     CEMLIovecListType ioVecIn);
CeMLErrorType
CeMLHashFinal (CeMLCntxHandle * _h,
                     CEMLIovecListType * ioVecOut);
CeMLErrorType
CeMLHashAtomic (CeMLCntxHandle * _h,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType * ioVecOut);
CeMLErrorType
CeMLHmac (uint8 * key_ptr,
                     uint32 keylen,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType * ioVecOut,
                     CeMLHashAlgoType pAlgo);
CeMLErrorType
CeMLCmac (uint8 *key_ptr,
                     uint32 keylen,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType *ioVecOut,
                     CeMLCipherAlgType pAlgo);
CeMLErrorType
CeMLHashSetParam (CeMLCntxHandle * _h,
                     CeMLHashParamType nParamID,
                     const void *pParam,
                     uint32 cParam,
                     CeMLHashAlgoType pAlgo );
CeMLErrorType CeMLHashSetParamAsU32(CeMLCntxHandle *_h,
                                    CeMLHashParamType nParamID,
                                    const void *pParam);
CeMLErrorType CeMLHashSetParamAsData(CeMLCntxHandle *_h,
                                       CeMLHashParamType nParamID,
                                       const void *pParam,
                                       size_t cParam,
                                       CeMLHashAlgoType pAlgo);
CeMLErrorType
CeMLCipherInit (CeMLCntxHandle ** _h,
                     CeMLCipherAlgType pAlgo);
CeMLErrorType
CeMLCipherDeInit (CeMLCntxHandle ** _h);
CeMLErrorType CeMLCipherSetParamAsU32(CeMLCntxHandle *_h,
                                                                         CeMLCipherParamType nParamID,
                                                                         void *pParam);
CeMLErrorType CeMLCipherSetParamAsData(CeMLCntxHandle *_h,
                                                                          CeMLCipherParamType nParamID,
                                                                          const void *pParam,
                                                                          size_t cParam);
CeMLErrorType CeMLCipherGetParamAsU32(CeMLCntxHandle *_h,
                                                                         CeMLCipherParamType nParamID,
                                                                         uint32 *pnOut);
CeMLErrorType CeMLCipherGetParamAsData(CeMLCntxHandle *_h,
                                                                           CeMLCipherParamType nParamID,
                                                                           void *pParam,
                                                                           size_t *cParam);
CeMLErrorType CeMLCipherSetParam (CeMLCntxHandle * ceMlHandle,
                                  CeMLCipherParamType nParamID,
                                  void *pParam,
                                  size_t cParam);
CeMLErrorType CeMLCipherGetParam (CeMLCntxHandle * _h,
                       CeMLCipherParamType nParamID,
                       void *pParam,
                       size_t *cParam );
CeMLErrorType
CeMLCipherData (CeMLCntxHandle * _h,
                     CEMLIovecListType ioVecIn,
                     CEMLIovecListType * ioVecOut);
CeMLErrorType CeMLHmacInit(CeMLCntxHandle** cntx,
                           CeMLHashAlgoType pAlgo);
CeMLErrorType CeMLHmacUpdate(CeMLCntxHandle* cntx,
                             CEMLIovecListType ioVecIn);
CeMLErrorType CeMLHmacFinal(CeMLCntxHandle* cntx,
                            CEMLIovecListType *ioVecOut);
CeMLErrorType
CeMLHashCipherData(CeMLCntxHandle *_h1,
                   CeMLCntxHandle *_h2,
                   CEMLIovecListType ioVecIn,
                   CEMLIovecListType * ioVecOut,
                   uint8 * hash_out,
                   uint32 hash_out_len);
typedef struct {
  uint8 root_of_trust[32];
} SecbootRootOfTrustType;
<driver name="NULL">
  <!--
 <device id="/secboot/oem_general">
    <props name="root_of_trust" type="uint8" array="True">
    {
      0xDE, 0x01, 0xAD, 0x02, 0xBE, 0x03, 0xEF, 0x04,
      0xDE, 0x05, 0xAD, 0x06, 0xDE, 0x07, 0xAD, 0x08,
      0xDE, 0x09, 0xAD, 0x0A, 0xBE, 0x0B, 0xEF, 0x0C,
      0xDE, 0x0D, 0xAD, 0x0E, 0xDE, 0x0F, 0xAD, 0x10,
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
