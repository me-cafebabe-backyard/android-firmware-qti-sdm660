
/*===========================================================================
Copyright (c) 2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
============================================================================*/

#ifndef __TEETEST_H
#define __TEETEST_H

#include "object.h"

#define TRUE                    1   /* Boolean true value. */
#define FALSE                   0   /* Boolean false value. */

#define ARRAY_SIZE(array)      (sizeof(array) / sizeof(array[0]))
#define MAX_SMC_ARGS            8
#define TEE_INT_SGI(xx)        (xx)

#define USEROBJECT_INVOKE_OUTBOUND  (ObjectInvoke)1
#define USEROBJECT_INVOKE_NULL      (ObjectInvoke)0
#define MAX_INBOUND_OBJECTS         4


#define ObjectCounts_indexBUFFERS(k)            \
   ObjectCounts_indexBI(k)

#define ObjectCounts_numBUFFERS(k)                      \
   (ObjectCounts_numBI(k) + ObjectCounts_numBO(k))

#define TEST_OK(func)                                                     \
  if (ret == Object_OK)                                                   \
  {                                                                       \
    ret = func;                                                           \
  }                                                                       \

#define TEST_NOT_OK(func)                                                 \
  if (ret == Object_OK)                                                   \
  {                                                                       \
      ret = func;                                                         \
      if(ret != Object_OK)                                                \
      {                                                                   \
        ret = Object_OK;                                                  \
      }                                                                   \
  }                                                                       \

#define TEST_TRUE(b)                                                      \
  if (ret == Object_OK)                                                   \
  {                                                                       \
    ret = ((b)) ? Object_OK : Object_ERROR;                               \
  }

#define TEST_FALSE(b) TEST_TRUE(!(b))

#define TEST_IOPEN(MINKAPI, TEE_OUTBOUND_OBJECT)                          \
  TEST_OK(IEnv_open(TEE_RemoteEnv_Object,                                 \
                    C ## MINKAPI ## _UID,                                 \
                    &TEE_OUTBOUND_OBJECT))

#define TEST_ICLOSE(MINKAPI, TEE_OUTBOUND_OBJECT)                         \
  TEST_OK(I ## MINKAPI ## _release(TEE_OUTBOUND_OBJECT))

#define TEST_ENTER                                                        \
  int ret = Object_OK;                                                    \
  Object TEE_RemoteEnv_Object = CEnv_create(ENV_REMOTE);

#define TEST_EXIT                                                         \
  return ret;


typedef unsigned char           boolean;
typedef uint32_t                uint32;
typedef uint32                  sd_tte_t;
typedef uint32                  l2tt_iter_t;
typedef uint32                  v_addr_t;
typedef unsigned long long int  uint64;
typedef unsigned char           uint8;
typedef unsigned long           uintnt;      /* Unsigned Native Integer
                                                Aarch32: 32 bits
                                                Aarch64: 64 bits        */

typedef enum
{
  E_SUCCESS            =  0,    /* Operation successful                  */
  E_FAILURE            =  1,    /* Operation failed due to unknown err   */

  E_RESERVED           = 0xFFFFFFFFU

} IxErrnoType;


typedef struct uint64_buf_s {
  uint32_t  l;
  uint32_t  h;
}uint64_buf_t;

typedef struct aes_vector_type
{
  uint8                alg;
  uint8                mode;
  uint8*               pt;
  uint32               pt_len;
  uint8*               key;
  uint32               key_len;
  uint8*               iv;
  uint32               iv_len;
  uint8*               ct;
  uint32               ct_len;
} __attribute__ ((packed)) aes_vector_type_t;

typedef struct object_ctx_s
{
  uint32  object_id;            /* smc id of the object                  */
}object_ctx_t;

size_t memscpy                        (void        *dst,            size_t       dst_size, const void  *src,  size_t       src_size);
int    tee_ipc_outbound               (ObjectCxt    ctx,            ObjectOp     op,       ObjectArg   *args, ObjectCounts k);
void   tee_ipc_inbound                (ObjectArg64 *ptr_object_arg, ObjectCounts k);
void   tee_ipc_return_from_inbound_asm(unsigned int regs);
void   tee_ipc_outbound_asm           (unsigned int regs);
void   tee_panic                      (void);

void   tee_int_enable                 (void);
uint32 tee_int_disable                (void);
void   tee_int_restore                (uint32       flags);


/* Flag to indicate an interrupt has been caught */
extern int           interrupt_exit;

typedef struct       tee_syscall_entry_s tee_syscall_entry_t;

#endif  /* __TEETEST_H */
