
/*===========================================================================
Copyright (c) 2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
============================================================================*/
#include <string.h>
#include "teetest.h"
#include "teetest_public.h"
#include "teetest_mmu.h"
#include "teetest_hal_qgic.h"
#include "object.h"
#include "ObjectTable.h"

#include "IDeviceID.h"
#include "IEnv.h"
#include "IPVC.h"

#include "CPVC.h"
#include "CCipher.h"
#include "ICipher.h"
#include "CUptime.h"
#include "IUptime.h"
#include "CDeviceID.h"
#include "CHdmiStatus.h"
#include "IHdmiStatus.h"

#include "CGuestVM_open.h"
#include "CEnv_open.h"


#define UNREFERENCED_PARAMETER(x) (void)(x)

static unsigned char __attribute__((section("SVC_STACK"),aligned(4096))) svc_stack[0x8000];
static unsigned char __attribute__((section("UND_STACK"),aligned(4096))) und_stack[0x1000];
static unsigned char __attribute__((section("ABT_STACK"),aligned(4096))) abt_stack[0x1000];
static unsigned char __attribute__((section("FIQ_STACK"),aligned(4096))) fiq_stack[0x1000];
static unsigned char __attribute__((section("IRQ_STACK"),aligned(4096))) irq_stack[0x1000];

/*===========================================================================
 * Individual Test Data and Functions
 ===========================================================================*/
uint8 aes_key_1[] =
{
  0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
  0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};

/* AES-128 ECB test vectors */
uint8 aes_plain_text_1[] =
{
  0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
  0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};

uint8 aes_cipher_text_1[] =
{
  0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
  0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
};

/* AES-128 CBC test vectors */
uint8 aes_plain_text_2[] = {
  0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f,
  0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93,
  0x17, 0x2a
};

uint8 aes_key_2[] = {
  0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2,
  0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf,
  0x4f, 0x3c
};

uint8 aes_iv_2[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
  0x0e, 0x0f
};

uint8 aes_cipher_text_2[] = {
   0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46,
   0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d
};

/* AES-128 and AES-256 test vectors array */
aes_vector_type_t aes_test_vectors[] =
{
  {CCipherAES128_UID, ICipher_MODE_CTS, aes_plain_text_2,
   sizeof(aes_plain_text_2), aes_key_2, 16, aes_iv_2,
   16, aes_cipher_text_2, 16},

  {CCipherAES128_UID, ICipher_MODE_ECB, aes_plain_text_1,
   sizeof(aes_plain_text_1), aes_key_1, 16, NULL,
   16, aes_cipher_text_1, 16}
};

/*===========================================================================
 * External Data and Functions
 ===========================================================================*/

extern int tee_test_i2c_init(Object TEE_RemoteEnv_Object);
extern int tee_test_i2c(void);
extern int tee_test_i2c_cleanup(void);

extern int tee_test_crypto(void);

/*===========================================================================
 * Local Data and Functions
 ===========================================================================*/

/* Get the stacks as relative to the current PC */
unsigned int get_svc_stack(void) {
  return ((unsigned int)&svc_stack + sizeof(svc_stack));
}

unsigned int get_und_stack(void) {
  return ((unsigned int)&und_stack + sizeof(und_stack));
}

unsigned int get_abt_stack(void) {
  return ((unsigned int)&abt_stack + sizeof(abt_stack));
}

unsigned int get_fiq_stack(void) {
  return ((unsigned int)&fiq_stack + sizeof(fiq_stack));
}

unsigned int get_irq_stack(void) {
  return ((unsigned int)&irq_stack + sizeof(irq_stack));
}

static uint32 smc[MAX_SMC_ARGS] = {0};
static Object tee_Objects[MAX_INBOUND_OBJECTS];
static int32_t tee_ObjectRefs[MAX_INBOUND_OBJECTS];
static ObjectTable tee_object_table = {&tee_Objects[0], &tee_ObjectRefs[0], MAX_INBOUND_OBJECTS};


/*
 *  Transfer buffer pointers and contents into physical memory
 */
static int writeBufs(int ndx, int ndxEnd, ObjectArg64  *ptr_phys_args, ObjectArg *args, ObjectBuf64 phys_arg)
{
  for (; ndx < ndxEnd; ndx++)
  {
    ptr_phys_args[ndx].b.ptr_l = phys_arg.ptr_l;
    ptr_phys_args[ndx].b.ptr_h = 0;
    ptr_phys_args[ndx].b.size_l = args[ndx].b.size;
    ptr_phys_args[ndx].b.size_h = 0;

    /* Valid to pass NULL ptr for out buffer case */
    if(args[ndx].b.ptr != NULL)
    {
      memscpy (phys_arg.ptr_l, phys_arg.size_l, args[ndx].b.ptr, args[ndx].b.size);
    }

    phys_arg.ptr_l += args[ndx].b.size;
  }
  return Object_OK;
}


/*
 *  Transfer buffer pointers from physical memory
 */
static int readBufs(int ndx, int ndxEnd, ObjectArg64  *ptr_phys_args, ObjectArg *args)
{

  /* transfer the args into the physical buffer */
  for (; ndx < ndxEnd; ndx++)
  {
    args[ndx].b.ptr  = ptr_phys_args[ndx].b.ptr_l;
    args[ndx].b.size = ptr_phys_args[ndx].b.size_l;

    /* Map in the memory in to the TeeTest address space */
    tee_mmu_map ((unsigned int)args[ndx].b.ptr,
                 (unsigned int)args[ndx].b.ptr, args[ndx].b.size, 0x017);
  }

  return Object_OK;
}
/*
 *  Transfer the contents of filled output buffers from physical into virtual mem.
 */
static int readOutBufs(int ndx, int ndxEnd, ObjectArg64 * ptr_phys_args, ObjectArg *args)
{
  /* For each arg */
  for (; ndx < ndxEnd; ndx++)
  {
    // out buffer means ptr_phys_args[ndx].b.ptr_l provided by remote
    if(ptr_phys_args[ndx].b.ptr_l != NULL)
    {
      memscpy (args[ndx].b.ptr, args[ndx].b.size, ptr_phys_args[ndx].b.ptr_l, ptr_phys_args[ndx].b.size_l);
    }
    else
    {
      return Object_ERROR;
    }
  }

  return Object_OK;
}

/*
 *  Transfer returned objects from to TEE from physical to virtual mem.
 */
static int readObjs(int ndx, int ndxEnd, ObjectArg64 * ptr_phys_args, ObjectArg *args)
{
  /* For each arg */
  for (; ndx < ndxEnd; ndx++)
  {
    args[ndx].o.context = ptr_phys_args[ndx].o.context_l;

    /* We should not get nothing here */
    if(ptr_phys_args[ndx].o.invoke_l == USEROBJECT_INVOKE_NULL)
    {
      return Object_ERROR_REMOTE;
    }
    else
    {
      args[ndx].o.invoke = (ObjectInvoke)tee_ipc_outbound;
    }
  }

  return Object_OK;
}

/*
 * Transfer objects for return to from TEE from virtual to physical mem.
 */
static int writeObjs(int ndx, int ndxEnd, ObjectArg64 * ptr_phys_args, ObjectArg *args)
{
  int ret = Object_OK;

  /* For each arg */
  for (; ndx < ndxEnd; ndx++)
  {
    Object o = args[ndx].o;
    if ( !Object_isNull(o) )
    {
      int object_handle = ObjectTable_addObject(&tee_object_table, o);
      if (object_handle < 0)
      {
        // Error allocating an entry in the object table
        ret = Object_ERROR_NOSLOTS;
        ptr_phys_args[ndx].o.invoke_l = USEROBJECT_INVOKE_NULL;
        ptr_phys_args[ndx].o.invoke_h = 0;
      }
      else
      {
        ptr_phys_args[ndx].o.invoke_l = USEROBJECT_INVOKE_OUTBOUND;
        ptr_phys_args[ndx].o.invoke_h = 0;

        ptr_phys_args[ndx].o.context_l = (ObjectCxt) object_handle;
        ptr_phys_args[ndx].o.context_h = 0;
      }
    }
  }

  return ret;
}

/*===========================================================================
 *  Function :  memscpy
 * ==========================================================================
 */
size_t memscpy(void        *dst,
               size_t       dst_size,
               const void  *src,
               size_t       src_size)
{
  size_t copy_size = (dst_size <= src_size)? dst_size : src_size;
  memcpy(dst, src, copy_size);
  return copy_size;
}

/*===========================================================================
 *  Function :  enable_el1_mmu
 * ==========================================================================
 */
/**
 * Called during init to program MMU related system registers and
 * enable the MMU
 *
 * @param ttbr0 Translation table base registeer
 * @param nmrr  Memory attribute register
 * @param prrr  Memory attribute register
 */
void enable_el1_mmu(uint32 ttbr0, uint32 nmrr, uint32 prrr);

/* Assign 32kB for the L1 table. A 16kB aligned pointer will
 * be assigned to this table at run time. */
sd_tte_t  l1_region[32*1024];
l1_tt_t  *l1;
l2_tt_t   __attribute__((section("L2_TT_MEM"),aligned(4096))) l2[NUM_L2_TTS];

unsigned int tee_physical_load_address = 0;
unsigned int tee_length_in_kb          = 0;
unsigned int ipc_addr                  = 0;
unsigned int ipc_size                  = 0;

static inline uint32 get_ttbr_mem_attrs(void) { return TTBR0_MEM_ATTS; }
static inline uint32 get_el1_nmrr      (void) { return NMRR;           }
static inline uint32 get_el1_prrr      (void) { return PRRR;           }

static        void   tee_init          (uint32 *ipc_addr, uint32 ipc_addr_size);
static        void   tee_loop          (uint32 *ipc_addr, uint32 ipc_addr_size);

void tee_test_c_entry(
  unsigned int r0,
  unsigned int r1,
  unsigned int r2,
  unsigned int r3)
{

  /* 'C' entry point for the TEE test application */

  /* Save the input parameters, we probably need these */
  tee_boot_info_t *boot_info = (tee_boot_info_t *)r0;
  uint32           arch      = r1;
  UNREFERENCED_PARAMETER(      r2);
  UNREFERENCED_PARAMETER(      r3);

  tee_physical_load_address  = (uint32)  boot_info->ddr_mem.start;
  tee_length_in_kb           = (uint32)((1023 + boot_info->ddr_mem.end - boot_info->ddr_mem.start) / 1024);

  /* L1 table setup. Since this code is relocatable we must
   * ensure that the L1 table pointer is on a 16KB boundary */
  l1 = (l1_tt_t *)(&l1_region);
  l1 = (l1_tt_t *)((uint32)l1 + (16 * 1024));
  l1 = (l1_tt_t *)((uint32)l1 & (  ~0x3FFF));

  /* L1 Table Configuration */
  tee_mmu_init();
  /* First map the entire memory region as
   *
   *   normal memory
   *   innner write through, no write alloc
   *   outer  write through, no write alloc
   *
   *     _____________________________________________________________________
   *    |                               |  |  |     |     |       |  |  |  |  |
   *    |31---------------------------12|11|10|--9--|8---6|5-----4|-3|-2|-1|-0|
   *    |     Phys Address base         |nG| S|AP[2]| TEX |AP[1:0]| C| B| 1|XN|
   *    |     Phys Address base         |0 | 0|  0  | 000 |  01   | 1| 1| 1| 0|
   *    |_______________________________|__|__|_____|_____|_______|__|__|__|__|
   */
  tee_mmu_map (tee_physical_load_address, tee_physical_load_address, tee_length_in_kb, 0x01E);
  /* Now remap the translation table regions as
   *
   *   normal memory
   *   non-cacheable
   *   xn
   *
   *     _____________________________________________________________________
   *    |                               |  |  |     |     |       |  |  |  |  |
   *    |31---------------------------12|11|10|--9--|8---6|5-----4|-3|-2|-1|-0|
   *    |     Phys Address base         |nG| S|AP[2]| TEX |AP[1:0]| C| B| 1|XN|
   *    |     Phys Address base         |0 | 0|  0  | 000 |  01   | 0| 1| 1| 1|
   *    |_______________________________|__|__|_____|_____|_______|__|__|__|__|
   */
  tee_mmu_map ((uint32)l1,   (uint32)l1,  16,                  0x017);
  tee_mmu_map ((uint32)&l2,  (uint32)&l2, (sizeof(l2) / 1024), 0x017);
  /* Map in the IPC memory as per the translation table regions */
  tee_mmu_map (ipc_addr = r0, r0,         4,                   0x017);

  /* Map in the QGIC */
  tee_mmu_map (HWIO_GICD_SGIR_ADDR, HWIO_GICD_SGIR_ADDR, 1024, 0x017);

  /* Enable the MMU */
  enable_el1_mmu((uint32)l1 | get_ttbr_mem_attrs(),
                 get_el1_nmrr(),
                 get_el1_prrr());


  /* At this point the TEE has booted and the MMU is enabled. Now we enter the
   * TEE init code to finish the boot processes */
  tee_init((uint32 *)ipc_addr, ipc_size = 0x1000);
}

/*
 * Assemble an outbound message
 *
 */
int tee_ipc_outbound(ObjectCxt ctx, ObjectOp op, ObjectArg *args, ObjectCounts k)
{
  int    ret = Object_ERROR;
  uint32 flags;

  ObjectArg64 *ptr_phys_args  = (ObjectArg64 *) (ipc_addr);
  ObjectBuf64 phys_arg;

  phys_arg.ptr_l = (void *)(ptr_phys_args + ObjectCounts_total(k));
  phys_arg.ptr_h = 0;
  phys_arg.size_l = (ipc_addr + ipc_size - (uint32) phys_arg.ptr_l);
  phys_arg.size_h = 0;

  ret = writeBufs(ObjectCounts_indexBI(k), ObjectCounts_indexOI(k), ptr_phys_args, args, phys_arg);

  if(ret == Object_OK)
  {
    /* Post an outbound object */
    smc[0] = (uint32)TEE_IPC_OUTBOUND_SMC_ID;
    smc[1] = (uint32)TEE_IPC_OUTBOUND_SMC_PARAM_ID;
    smc[2] = (uint32)ctx;
    smc[3] = (uint32)op;
    smc[4] = (uint32)k;
    smc[5] = (uint32)ipc_addr;

    /* Disable interrupts round an outbound call */
    flags = tee_int_disable();

    /* Outbound SMC */
    tee_ipc_outbound_asm((uint32)&smc);

    /* Restore interrupt flags as per state prior to outbound SMC */
    tee_int_restore(flags);

    /* Result code is in smc[1] */
    ret = (int) smc[1];
  }

  if(ret == Object_OK)
  {
    /* Get arg pointer to buffers out */
    ptr_phys_args = (ObjectArg64 *)(ipc_addr);
    readOutBufs(ObjectCounts_indexBO(k), ObjectCounts_indexOI(k), ptr_phys_args, args);
  }

  if(ret == Object_OK)
  {
    /* Get arg pointer to objects out */
    ptr_phys_args = (ObjectArg64 *)(ipc_addr);
    ret = readObjs(ObjectCounts_indexOO(k), ObjectCounts_total(k), ptr_phys_args, args);
  }
  return ret;
}

/*
 * Disassemble an inbound message
 *
 */
void tee_ipc_inbound(ObjectArg64 *ptr_phys_args, ObjectCounts k)
{
  ObjectArg * args = (ObjectArg *)(ptr_phys_args);
  /* convert the input buffers */
  readBufs(ObjectCounts_indexBI(k), ObjectCounts_indexOI(k), ptr_phys_args, args);
}

/* This function is used by the TEE to return from an INBOUND LOADING SMC
 * When it returns, the return value signals the event, and regs contains
 * the NS register.
 */
static void tee_ipc_return_from_inbound_loading(int ret)
{
  smc[0] = TEE_IPC_RETURN_FROM_INBOUND_SMC_ID;
  smc[1] = ret;
  tee_ipc_return_from_inbound_asm((unsigned int)&smc);
}

/* This function is used by the TEE to return from an INBOUND SMC
 * When it returns, the return value signals the event, and regs contains
 * the NS register.
 */
static void tee_ipc_return_from_inbound(ObjectArg64 *args, ObjectCounts k, int ret)
{
  /* Interrupts are always disabled on returning from the TEE */
  (void)tee_int_disable();

  /* Get arg pointer to objects  */
  ObjectArg64 * ptr_phys_args = args;
  writeObjs(ObjectCounts_indexOO(k), ObjectCounts_total(k), ptr_phys_args, (ObjectArg *)args);

  smc[0] = TEE_IPC_RETURN_FROM_INBOUND_SMC_ID;
  smc[1] = ret;
  tee_ipc_return_from_inbound_asm((unsigned int)&smc);
}

static void tee_init(uint32 *ipc_addr, uint32 ipc_addr_size) {
  /* Branch to the main SMC handler loop */
  tee_loop(ipc_addr, ipc_addr_size);
}

static void tee_loop(uint32 *ipc_addr, uint32 ipc_addr_size)
{
  int ret = Object_OK;
  volatile uint32 loop_flag = 1;
  Object TEE_Outbound_Object;
  /* Prepare a local ENV object to handle inbounds*/
  Object TEE_LocalEnv_Object = CEnv_create(ENV_LOCAL);
  /* Add the ENV object to the object table */
  (void) ObjectTable_addObject(&tee_object_table, TEE_LocalEnv_Object);

  /* Prepare an opener object */
  Object TEE_RemoteEnv_Object = CEnv_create(ENV_REMOTE);

  /* Open the interface on the remote OS */
  TEST_OK(IEnv_open(TEE_RemoteEnv_Object, CDeviceID_UID, &TEE_Outbound_Object));

  /* IDeviceID_readJtagID Test */
  uint32 jtag_id = 0xDEAD;
  TEST_OK(IDeviceID_readJtagID(TEE_Outbound_Object, &jtag_id))

  if(jtag_id == 0xDEAD)
  {
    ret = Object_ERROR;
  }

  /* IDeviceID_getComponentVersion Test */
  uint8_t imp_version[128] = {0};
  size_t  imp_version_len  = sizeof(imp_version);
  TEST_OK(IDeviceID_getComponentVersion(TEE_Outbound_Object, IDeviceID_QSEE_VERSION, imp_version, imp_version_len, &imp_version_len));
  /* IDeviceID_getImplementationVersion Test with short buffer */
  imp_version_len = 100;
  TEST_NOT_OK(IDeviceID_getComponentVersion(TEE_Outbound_Object, IDeviceID_QSEE_VERSION, imp_version, imp_version_len, &imp_version_len));

  /* IEnv_log Test*/
  char   *log      = "Hello This is TEE";
  uint32  log_size = strlen(log) + 1;
  TEST_OK(IEnv_log(TEE_RemoteEnv_Object, log, log_size);)

  /* IDeviceID_release Test */
  TEST_OK(IDeviceID_release(TEE_Outbound_Object))
  /* Bad IDeviceID_readJTAG Test */
  TEST_NOT_OK(IDeviceID_readJtagID(TEE_Outbound_Object, &jtag_id))

  /* IEnv_open Test */
  TEST_OK(IEnv_open(TEE_RemoteEnv_Object, CDeviceID_UID, &TEE_Outbound_Object))
  /* Bad IOpener_open Test */
  TEST_NOT_OK(IOpener_open(TEE_Outbound_Object, CDeviceID_UID, &TEE_Outbound_Object))

  /* HDMI STATUS Test */
  uint32_t hdmiEnable, hdmiSense, hdcpAuth;
  TEST_OK(IEnv_open(TEE_RemoteEnv_Object, CHdmiStatus_UID, &TEE_Outbound_Object))
  TEST_OK(IHdmiStatus_hdmiStatusRead(TEE_Outbound_Object, &hdmiEnable, &hdmiSense, &hdcpAuth))
  TEST_OK(IHdmiStatus_release(TEE_Outbound_Object))

  uint8 encrypted_key[100];
  aes_test_vectors[0].pt = &encrypted_key[0];
  aes_test_vectors[0].pt_len = sizeof(encrypted_key);

  /* IEnv Open Test */
  TEST_OK(IEnv_open(TEE_RemoteEnv_Object, aes_test_vectors[0].alg, &TEE_Outbound_Object))
  /* ICipher_setParamAsData Test */
  TEST_OK(ICipher_setParamAsData(TEE_Outbound_Object, ICipher_PARAM_KEY, aes_test_vectors[0].key, aes_test_vectors[0].key_len))
  /* ICipher_setParamAsU32 Test */
  TEST_OK(ICipher_setParamAsU32(TEE_Outbound_Object, ICipher_PARAM_MODE, aes_test_vectors[0].mode))
  /* ICipher_setParamAsU32 Test */
  TEST_OK(ICipher_setParamAsData(TEE_Outbound_Object, ICipher_PARAM_IV,  aes_test_vectors[0].iv, aes_test_vectors[0].iv_len))

  /* ICipher_encrypt Test */
  size_t ct_len_out;
  TEST_OK(ICipher_encrypt(TEE_Outbound_Object, aes_test_vectors[0].pt, aes_test_vectors[0].pt_len, aes_test_vectors[0].ct, aes_test_vectors[0].ct_len, &ct_len_out))

  /* ICipher_release Test */
  TEST_OK(ICipher_release(TEE_Outbound_Object))

  /* IUptime Test */
  uint64 upTime;
  TEST_OK(IEnv_open(TEE_RemoteEnv_Object, CUptime_UID, &TEE_Outbound_Object))
  /* IUptime_getUptime Test */
  TEST_OK(IUptime_getUptime(TEE_Outbound_Object, &upTime))
  /* IUptime_getUptimeUS Test */
  TEST_OK(IUptime_getUptimeUS(TEE_Outbound_Object, &upTime))
  TEST_OK(IUptime_release(TEE_Outbound_Object))

  /* I2C Test */
#if 0  
  TEST_OK(tee_test_i2c_init(TEE_RemoteEnv_Object));
  TEST_OK(tee_test_i2c());
  TEST_OK(tee_test_i2c_cleanup());
#endif

  /* Run the Crypto Tests */
  TEST_OK(tee_test_crypto());

  /* Initialization is now complete. Return, now waiting for an
   * SMC from the HLOS */
  tee_ipc_return_from_inbound_loading(ret);

  /* SMC has been received */
  while(loop_flag)
  {
    uint32 smc_id = 0, param_id = 0, nargs = 0, object_handle;
    tee_syscall_entry_t *sc_entry = NULL;
    ObjectCounts k;
    ObjectArg64 *args;
    ObjectOp     op;

    smc_id        = (uint32       )(smc[0] & 0xFFFFFFFFULL);
    object_handle = (uint32       )(smc[1] & 0xFFFFFFFFULL);
    op            = (ObjectOp     )(smc[2] & 0xFFFFFFFFULL);
    k             = (ObjectCounts )(smc[3] & 0xFFFFFFFFULL);
    args          = (ObjectArg64 *)(smc[4] & 0xFFFFFFFFULL);
    ret           = Object_OK;

    if (!IS_OWNER_TRUSTED_OS(TEE_SYSCALL_OWNER_ID(smc_id)) ||  smc_id != TEE_IPC_INBOUND_SMC_ID)
    {
      ret = Object_ERROR;
    }
    else
    {

      /* Clear the flag set when the TEE receives either an IRQ or an FIQ */
      interrupt_exit = 0;

      /* Allow interrupts to occur from this point onwards. If we exited last time with
       * interrupts disabled, the host may have had handled the interrupt and so TEE will
       * get no indication of the end of the interrupt. We therefore re-enable here on re-entry
       * each time */
      tee_int_enable();

      // Lookup the object from its handle
      const Object TEE_Inbound_Object = ObjectTable_recoverObject(&tee_object_table, object_handle);

      if (Object_isNull(TEE_Inbound_Object))
      {
        ret = Object_ERROR_BADOBJ;
      }

      if(ret == Object_OK)
      {
        tee_ipc_inbound(args, k);

        /* execute the operation */
        ret = Object_invoke(TEE_Inbound_Object, op, (ObjectArg *)args, k);
      }
    }
    /* Return from the inbound SMC */
    tee_ipc_return_from_inbound(args, (ret == Object_OK) ? k : 0, ret);
  }
}

/* Panic loop!!! */
void tee_panic(void) {
  volatile int i = 1;
  while (i) {
    /* Wait here for the debugger!!! */
  }
}
