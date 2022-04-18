/** vi: tw=128 ts=3 sw=3 et
@file pd_dump.c
@brief This file contains the API details for the Protection Domain Monitor, API 1.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 - 2017 by Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/pd_mon/src/pd_dump.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "stdlib.h"
#include "stringl/stringl.h"

#include "qurt.h"
#include "qurt_printf.h"
#include "qurt_qdi_driver.h"
#include "qurt_thread_context.h"

#include "err.h"
#include "msg.h"
#include "tms_utils.h"
#include "tms_utils_msg.h"

#include "pd_dump.h"
#include "pd_elf.h"
#include "pd_elf_hexagon.h"
#include "pd_mon_qurt.h"
#include "pd_dump_security.h"
#include "pd_mon_dump.h"

#if defined(PD_MON_TRACER_SWEVT)
#include "tracer.h"
#include "pd_mon_tracer_swe.h"
#endif

#define PD_DUMP_MAX_BLOCK_SIZE 7

extern void dog_force_kick(void);
extern void err_qdi_invoke_user_process_cbs(uint32 pid);

#if defined(ADD_ROOT_PD_IMAGE_VER)
extern char QC_IMAGE_VERSION_STRING_AUTO_UPDATED[];
extern char IMAGE_VARIANT_STRING_AUTO_UPDATED[];
extern char OEM_IMAGE_VERSION_STRING_AUTO_UPDATED[];
extern char OEM_IMAGE_UUID_STRING_AUTO_UPDATED[];

#define PD_DUMP_IMAGE_VERSION_SIZE  128
#endif


/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

struct pd_dump_device_s /**< localized driver storage area */
{
   qurt_qdi_obj_t qdiobj; /**< required to be first */

   qurt_sysenv_procname_t pn; /**< client procname on open */

   uint32_t hash; /**< name hash */

   Elf32_Ehdr elf_hdr; /**< ELF header */

   pd_elf_prgtab_p elf_prgtab_head; /**< linked list builds prgtab */

   void * prgtab_phdr;

   pd_elf_sectab_p elf_sectab_head; /**< linked list builds sectab */

   struct pd_dump_device_s* next; /**< next device (one per user domain) */

   unsigned int counter; /**< read elf file counter */

   char filename[PD_DUMP_FILE_NAME_MAX]; /**< temporary filename construction buffer */

   int fd; /**< file descriptor rfs */

   void * unmapped_region_ptr; /**< virtual buffer addr for non-process data (tcb's) */

   uint32_t unmapped_region_sz; /**< virtual buffer size for non-process data (tcb's) */

   uint32_t * ptcb_dump_sz; /** Points to user PD memory, Populated during dump collection, TCB Dump size */
};

struct MemBlock_s /**< qurt supplied with QDI_OS_DUMP_PROCESS_EXIT */
{
   void* addr;
   unsigned long len;
};

struct Thread_s /**< qurt supplied with QDI_OS_DUMP_PROCESS_EXIT */
{
   qurt_thread_t tid;
};

const char* pd_mon_internal_prefix = "/ramdumps/pd_dump_"; /**< RFSA Volume */

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

static struct pd_dump_internal_s
{
   struct pd_dump_device_s* head;

   qurt_mutex_t mutex;

   boolean dump_enabled;

} pd_dump_internal;

/////////////////////////////////////////////////////////////////////
// Implementation Details
/////////////////////////////////////////////////////////////////////

static void pd_dump_device_release(qurt_qdi_obj_t* qdiobj)
{
   struct pd_dump_device_s* device_p_curr;
   struct pd_dump_device_s* device_p_prev;
   device_p_curr = NULL;
   device_p_prev = NULL;

   qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

   for (device_p_curr = pd_dump_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
   {
      if (qdiobj == (qurt_qdi_obj_t*)device_p_curr)
      {
         if (NULL == device_p_prev) /**< head check */
         {
            if ( pd_dump_internal.head->next == NULL)
            {
              pd_dump_internal.head = NULL;
            }
            else
            {
              pd_dump_internal.head->next = device_p_curr->next;
            }
         }

         else
         {
            device_p_prev->next = device_p_curr->next;
         }

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_R, 2, device_p_curr->hash, device_p_curr->pn.asid);
#endif
         TMS_MSG_HIGH_2( "device release %x %d", device_p_curr->hash, device_p_curr->pn.asid);

         free(device_p_curr);

         break;
      }

      device_p_prev = device_p_curr;
   }

   if (NULL == device_p_curr)
   {
   }

   qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */
}

static int pd_dump_device_invocation(int client_handle, qurt_qdi_obj_t* obj, int method, qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3, qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6, qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9)
{
   int rc;
   struct pd_dump_device_s* device_p = (struct pd_dump_device_s*)obj;
   qurt_sysenv_procname_t pn;

   /* client_handle means that we're asking this particular client handle to answer the question about its process */
   /* QDI_OS_SYSENV is the standard method for requesting this type of information */
   /* QDI_HANDLE_LOCAL_CLIENT means that this request originated locally */
   /* QURT_SYSENV_PROCNAME_TYPE is the specific piece of data being requested -- to fill in a qurt_sysenv_procname_t structure */
   /* &pn is the structure we want filled in */

   if (0 > (rc = qurt_qdi_handle_invoke(client_handle, QDI_OS_SYSENV, QDI_HANDLE_LOCAL_CLIENT, QURT_SYSENV_PROCNAME_TYPE, &pn)))
   {
#if defined(PD_MON_TRACER_SWEVT)
      tracer_event_simple_vargs(PD_DUMP_SWE_E, 2, 0, rc);
#endif
      TMS_MSG_ERROR_1( "cannot obtain client asid %d", rc);

      return rc;
   }

   rc = PD_DUMP_STATUS_ERROR; /**< failure */

   if (NULL == device_p)
   {
      return rc;
   }

   /* Driver Methods */

   switch (method)
   {
      /**
      INTERNAL, Default Method Handler
      */
      default:
      {
         rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9); /**< pass along */

         break; /**< switch () */
      }

      /**
      API, pd_dump_init 
      a1.ptr is redundant device name 
      a2.ptr is the address of unmapped vitual memory region 
      a3.num is the size of unmapped vitual memory region
      */
      case QDI_OPEN:
      {
         qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

         do
         {
            for (device_p = pd_dump_internal.head; NULL != device_p; device_p = device_p->next)
            {
               if (0 == tms_utils_chr_compare(device_p->pn.name, sizeof(device_p->pn.name), pn.name, sizeof(pn.name)))
               {
                  break; /**< for () */
               }
            }

            /** operate on new */

            if (NULL == device_p)
            {
               /** allocate new */

               if (NULL == (device_p = malloc(sizeof(*device_p))))
               {
                  break; /**< do while () */
               }

               /** initialize new */

               secure_memset(device_p, 0, sizeof(*device_p));

               device_p->qdiobj.invoke = pd_dump_device_invocation;
               device_p->qdiobj.refcnt = QDI_REFCNT_INIT;
               device_p->qdiobj.release = pd_dump_device_release;

               /** device object init */

               device_p->unmapped_region_ptr = a2.ptr; //validate when consumed
               device_p->unmapped_region_sz = a3.num;  //validate when consumed
               device_p->ptcb_dump_sz = a4.ptr;  //validate when consumed

               memsmove(&device_p->pn, sizeof(device_p->pn), &pn, sizeof(pn));

               device_p->hash = tms_utils_hash(device_p->pn.name, sizeof(device_p->pn.name));

               /** link into device list */

               device_p->next = pd_dump_internal.head;
               pd_dump_internal.head = device_p;
            }

            else
            {
               /** operate on existing */
            }

         } while (0);

         qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

         if (NULL == device_p)
         {
            rc = PD_DUMP_STATUS_ERROR; /**< failure */

#if defined(PD_MON_TRACER_SWEVT)
            tracer_event_simple_vargs(PD_DUMP_SWE_I, 2, 0, pn.asid);
#endif
            TMS_MSG_ERROR_2( "device open NULL NA %d == %d", pn.asid, rc);
         }

         else
         {
            rc = qurt_qdi_handle_create_from_obj_t(client_handle, (qurt_qdi_obj_t*)device_p); /**< return handle */

#if defined(PD_MON_TRACER_SWEVT)
            tracer_event_simple_vargs(PD_DUMP_SWE_I, 2, device_p->hash, pn.asid);
#endif
            TMS_MSG_HIGH_3( "device open %x %d == %d", device_p->hash, pn.asid, rc);
         }

         break; /**< switch () */
      }

      /**
      API, pd_dump_destroy
      */
      case QDI_CLOSE:
      {
         qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

         do
         {
            /** operate on existing */

         } while (0);

         qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

         rc = PD_DUMP_STATUS_ERROR; /**< handle does not close */

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_D, 2, device_p->hash, pn.asid);
#endif
         TMS_MSG_HIGH_3( "device close %x %d == %d", device_p->hash, pn.asid, rc);

         rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9); /**< pass along */

         break; /**< switch () */
      }

      /**
      INTERNAL, OS_DUMP_PROCESS_EXIT Handler
      a1.ptr is a pointer to a list of (address, size) pairs
      a2.num is the number of entries pointed to by a1.ptr
      a3.ptr is a pointer to a list of process Thread IDs 
      a4.num is the number of entries pointed to by a3.ptr 
      a5.num is deprecated
      */
      case QDI_OS_DUMP_PROCESS_EXIT:
      {
         unsigned int i;
         struct Thread_s* Thread = (struct Thread_s*)a3.ptr;
         struct MemBlock_s* MemBlock = (struct MemBlock_s*)a1.ptr;
         unsigned long BlockLen, BlockAddr;// Block;
         void* mbuf_head_p;
         size_t mbuf_sz, malloc_sz;
         boolean try_optimization = TRUE;
         unsigned int tcb_index, remaining_tcb_data, num_excluded_blocks = 0;
#if defined(ADD_ROOT_PD_IMAGE_VER)
         char img_ver_str[PD_DUMP_IMAGE_VERSION_SIZE];
#endif

         err_qdi_invoke_user_process_cbs(device_p->pn.asid);

         /* Check if PD Dumps is allowed according to security policy */
         if ( FALSE == pd_dump_security_debug_enabled() )
            break;

         /* Check if PD Dumps is disabled through dalcfg\servreg */
         if ( FALSE == pd_dump_internal.dump_enabled )
            break;


#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_EDB, 2, device_p->hash, pn.asid);
#endif
         TMS_MSG_SPRINTF_HIGH_3("device dump begin %s %x %d", device_p->pn.name, device_p->hash, pn.asid);

         dog_force_kick();

         qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

         do
         {
#if 0 //enable file is deprecated
            if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_ENABLE_TEMPLATE, pd_mon_internal_prefix, device_p->pn.name))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_EC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1( "device dump enable filename too long %d", pn.asid);

               break; /**< do while () */
            }

            device_p->fd = rfs_open(device_p->filename, RFS_O_RDONLY, 0755); /**< opens .enable file (read) */
			qurt_printf("Open .enable file: %d", device_p->fd);
			TMS_MSG_ERROR( "Open .enable file");

            if (0 > device_p->fd)
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_EC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1( "device dump not enabled %d", pn.asid);

               break; /**< do while () */
            }

            rfs_close(device_p->fd); /**< close .enable file (read) */
#endif //enable file

            if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_COUNT_TEMPLATE, pd_mon_internal_prefix, device_p->pn.name))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_RC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1( "device dump count read filename too long %d", pn.asid);

               break; /**< do while () */
            }

            device_p->fd = rfs_open(device_p->filename, RFS_O_RDONLY, 0755); /**< open .count file (read) */
			qurt_printf("Open .count file: %d", device_p->fd);
			TMS_MSG_ERROR( "Open .count file");

            if (0 > device_p->fd || sizeof(device_p->counter) != rfs_read(device_p->fd, (char*)&device_p->counter, sizeof(device_p->counter)))
            {
               device_p->counter = 0;

#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_RC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1( "device dump count read file not available %d", pn.asid);
            }

            else
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_RC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_2("device dump count read %d %d", device_p->counter, pn.asid);
            }

            rfs_close(device_p->fd); /**< close .count file (read) */

            /**< BEGIN ALLOCATIONS : BE SENSITIVE NOT TO LEAK MEMORY */

            do
            {
               device_p->elf_prgtab_head = NULL; /**< prepare ELF headers */
               device_p->elf_sectab_head = NULL; /**< prepare ELF headers */

               if (PD_ELF_STATUS_SUCCESS != pd_elf_init(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HIE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers init error %d", pn.asid);

                  break; /**< do while () */
               }

               // dumps the pn as program table NOTE section

               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".process", NT_HEXAGON_DUMP_PROCESS, &pn, sizeof(pn)))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .process %d", pn.asid);

                  break; /**< do while () */
               }

#if defined(ADD_ROOT_PD_IMAGE_VER)
               memset(img_ver_str, 0, PD_DUMP_IMAGE_VERSION_SIZE );
               strlcpy(img_ver_str, QC_IMAGE_VERSION_STRING_AUTO_UPDATED, PD_DUMP_IMAGE_VERSION_SIZE);
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".root_qc_image_version", NT_HEXAGON_DUMP_VERSION, img_ver_str, PD_DUMP_IMAGE_VERSION_SIZE ))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .process %d", pn.asid);

                  break; /**< do while () */
               }

               memset(img_ver_str, 0, PD_DUMP_IMAGE_VERSION_SIZE );
               strlcpy(img_ver_str, IMAGE_VARIANT_STRING_AUTO_UPDATED, PD_DUMP_IMAGE_VERSION_SIZE);
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".root_image_variant_string", NT_HEXAGON_DUMP_VERSION, img_ver_str, PD_DUMP_IMAGE_VERSION_SIZE ))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .process %d", pn.asid);

                  break; /**< do while () */
               }

               memset(img_ver_str, 0, PD_DUMP_IMAGE_VERSION_SIZE );
               strlcpy(img_ver_str, OEM_IMAGE_VERSION_STRING_AUTO_UPDATED, PD_DUMP_IMAGE_VERSION_SIZE);
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".root_oem_image_version", NT_HEXAGON_DUMP_VERSION, img_ver_str, PD_DUMP_IMAGE_VERSION_SIZE ))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .process %d", pn.asid);

                  break; /**< do while () */
               }

               memset(img_ver_str, 0, PD_DUMP_IMAGE_VERSION_SIZE );
               strlcpy(img_ver_str, OEM_IMAGE_UUID_STRING_AUTO_UPDATED, PD_DUMP_IMAGE_VERSION_SIZE);
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".root_oem_image_uuid", NT_HEXAGON_DUMP_VERSION, img_ver_str, PD_DUMP_IMAGE_VERSION_SIZE ))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .process %d", pn.asid);

                  break; /**< do while () */
               }
#endif

#if 0 //deprecated
               // dumps task control blocks as program table NOTE sections; these ARE NOT part of the dump memoryblocks, so
               // they are supplied as NOTE sections instead.

               for (i = 0; i < a4.num; i++)
               {
                  if (tms_utils_fmt(buf, sizeof(buf), ".context.0x%x@0x%x", a5.num, (unsigned int)Thread[i].addr)) {;}

                  if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, buf, NT_HEXAGON_DUMP_CONTEXT, Thread[i].addr, a5.num))
                  {
#if defined(PD_MON_TRACER_SWEVT)
                     tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                     TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .context %d", pn.asid);

                     break; /**< for () */
                  }
               }
#endif

               // dumps the memoryblocks as program table LOAD sections

               for (i = 0; i < a2.num; i++)
               {
                 BlockLen = MemBlock[i].len;
                 BlockAddr = (unsigned long) MemBlock[i].addr;

                 // hack
                 if ( BlockAddr == (unsigned long)device_p->unmapped_region_ptr )
                 {
                    continue;
                 }
                 if ( qurt_lookup_physaddr(BlockAddr)== 0 )
                 {
                    num_excluded_blocks++;
                    continue;
                 }

                 if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_LOAD, NULL, NT_NONE, (void*)BlockAddr, BlockLen))
                 {
#if defined(PD_MON_TRACER_SWEVT)
                    tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif  		    
                    TMS_MSG_ERROR_1( "device dump headers alloc error in prgtab .data %d", pn.asid);
             
                    break; /**< for () */
                 }
               }

               do //qurt_debug_thread_info region
               {
                  char *temp = NULL, *temp1;

                  //we are going to dynamically build our own structures
                  // { 
                  //    void * next_ptr;
                  //    qurt_debug_thread_info data;
                  // } one_block;

                  // prep for thread info dump
                  mbuf_sz = qurt_system_tcb_dump_get_size();
                  mbuf_head_p = NULL;

                  // ensure we have an area to write the data
                  if ((NULL==device_p->unmapped_region_ptr) || (mbuf_sz > device_p->unmapped_region_sz))
                  {
                     TMS_MSG_ERROR( "device dump no user allocation for qurt_debug_thread_info region");
                     break; /**< do () */
                  }

                  /* Check for overflow */
                  if ( mbuf_sz > UINT32_MAX / a4.num )
                  {
                     TMS_MSG_ERROR( "TCB Data exceeds size limit");
                     break; /**< do () */
                  }

                  remaining_tcb_data = a4.num * mbuf_sz;

                  if ( -1 ==  qurt_qdi_copy_to_user(client_handle, device_p->ptcb_dump_sz, &remaining_tcb_data, sizeof(uint32_t)))
                  {
                     TMS_MSG_ERROR( "Failed to update tcb dump size to user PD ");
                  }
                  
                  // build linked list of qurt_debug_thread_info structs
                  for (i = 0; i < a4.num; )
                  {
                     tcb_index = i;
                     // get the space
                     /* Check if optimization can be done */
                     if ( try_optimization == TRUE )
                     {
                        /* Get Max malloc size */
                        malloc_sz = mbuf_sz * PD_DUMP_MAX_BLOCK_SIZE;
                        malloc_sz = malloc_sz > remaining_tcb_data ? remaining_tcb_data:malloc_sz;

                        temp = malloc(malloc_sz + sizeof(void*) + sizeof(unsigned  int));
                        
                        if (NULL == temp)
                        {
                          try_optimization = FALSE;
                          
                          /* Try without opimization */
                          temp = malloc(mbuf_sz + sizeof(void*) + sizeof(unsigned  int));

                          if ( NULL == temp )
                          {
                            TMS_MSG_ERROR( "device dump could not malloc for qurt_debug_thread_info region");
   					          break; /**< for () */
                          }

                          malloc_sz = mbuf_sz;

                          ++i;
                          secure_memset(temp, 0, mbuf_sz + sizeof(void*) + sizeof(unsigned  int));
                          remaining_tcb_data -= mbuf_sz;

                        }
                        else
                        {
                          if ( malloc_sz == remaining_tcb_data)
                            i = i + remaining_tcb_data/mbuf_sz;
                          else
                            i = i + PD_DUMP_MAX_BLOCK_SIZE;

                          secure_memset(temp, 0, malloc_sz + sizeof(void*) + sizeof(unsigned  int));
                          remaining_tcb_data -= malloc_sz;
                        }
                      
                     }
                     else
                     {
                        /* Try without opimization */
                        temp = malloc(mbuf_sz + sizeof(void*) + sizeof(unsigned  int));

                        if ( NULL == temp )
                        {
                          TMS_MSG_ERROR( "device dump could not malloc for qurt_debug_thread_info region");
   					        break; /**< for () */
                        }

                        malloc_sz = mbuf_sz;

                        ++i;
                        secure_memset(temp, 0, mbuf_sz + sizeof(void*) + sizeof(unsigned  int));
                        remaining_tcb_data -= mbuf_sz;
                     }
                    
                     *(unsigned int*)(temp + sizeof(void*)) = malloc_sz;                  
                     // link the list
                     *(void**)temp = mbuf_head_p;

                     // fill the data
                     temp1 = temp + sizeof(void*) + sizeof(unsigned  int);
                     for  (; tcb_index <i && QURT_EOK == qurt_system_tcb_dump_get(Thread[tcb_index].tid, temp1, mbuf_sz); tcb_index++, temp1= temp1 + mbuf_sz );

                     if ( tcb_index != i )
                     {
                        TMS_MSG_ERROR( "device dump could fill qurt_debug_thread_info region");
                        break; /**< for () */
                     }

                     mbuf_head_p = temp;
                  }
                  
                  // store for later consumption
                  if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc_list(&device_p->elf_hdr, &device_p->elf_prgtab_head, a4.num * mbuf_sz, mbuf_head_p, malloc_sz, device_p->unmapped_region_ptr, device_p->unmapped_region_sz))
                  {
#if defined(PD_MON_TRACER_SWEVT)
                    tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif  		    
                    TMS_MSG_ERROR_1( "device dump headers alloc error in thread list %d", pn.asid);
             
                    break; /**< for () */
                  }  
                                 
               } while (0); 

               if ( num_excluded_blocks >= a2.num  )
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HSE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc failed %d", pn.asid);

                  break; /**< do while () */

               }

#if defined(ADD_ROOT_PD_IMAGE_VER)
               /* First +1 below is for TCB area and the second +1 is for note program header, +4 for image version Note section */
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_prepare_header(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->prgtab_phdr, a2.num +1 +1 + 4 - num_excluded_blocks ))
#else
               /* First +1 below is for TCB area and the second +1 is for note program header */
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_prepare_header(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->prgtab_phdr, a2.num +1 +1 - num_excluded_blocks ))
#endif
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HSE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in sectab %d", pn.asid);

                  break; /**< do while () */
               }

                // required NULL section table entry, ELF specification

               if (PD_ELF_STATUS_SUCCESS != pd_elf_sectab_alloc(&device_p->elf_hdr, &device_p->elf_sectab_head, SHT_NULL, SHN_UNDEF))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HSE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers alloc error in sectab %d", pn.asid);

                  break; /**< do while () */
               }

               if (PD_ELF_STATUS_SUCCESS != pd_elf_prepare_offsets(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HOE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump headers offsets error %d", pn.asid);

                  break; /**< do while () */
               }

               if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_ELF_TEMPLATE, pd_mon_internal_prefix, device_p->pn.name, device_p->counter))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_OE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump elf filename too long %d", pn.asid);

                  break; /**< do while () */
               }

               device_p->fd = rfs_open(device_p->filename, RFS_O_WRONLY | RFS_O_CREAT, 755); /**< open .elf file (write) */
			   qurt_printf("Open .elf file: %d", device_p->fd);
			   TMS_MSG_ERROR( "Open .elf file");

               if (0 > device_p->fd)
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_OE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump elf file not available %d", pn.asid);

                  break; /**< do while () */
               }

               if (PD_ELF_STATUS_SUCCESS != pd_elf_write(device_p->fd, &device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head, &device_p->prgtab_phdr))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_WE, 2, device_p->hash, pn.asid);
#endif
                  TMS_MSG_ERROR_1( "device dump elf file not written %d", pn.asid);

                  rfs_close(device_p->fd); /**< close .elf file (write) */

                  device_p->fd = rfs_open(device_p->filename, RFS_O_WRONLY | RFS_O_CREAT, 755); /**< open .elf file (write) */

                  if (0 > device_p->fd || sizeof(device_p->counter) != rfs_write(device_p->fd, (char*)&device_p->counter, sizeof(device_p->counter)))
                  {
                     TMS_MSG_ERROR_1( "device dump elf file truncated, no valid content %d", pn.asid);
                  }
                  else
                  {
                     TMS_MSG_ERROR_1( "device dump elf file truncated, invalid content %d", pn.asid);
                  }

                  break; /**< do while () */
               }

            } while (0); /**< memory potentially still allocated */

			qurt_printf("Write .elf file: %d completed", device_p->fd);
			TMS_MSG_ERROR( "Write .elf file completed");
            rfs_close(device_p->fd); /**< close .elf file (write) */

            if (PD_ELF_STATUS_SUCCESS != pd_elf_term(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head, &device_p->prgtab_phdr))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_HD, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1( "device dump headers destroy error %d", pn.asid);

               // ERR_FATAL("resources not released properly", 0, 0, 0);

               break; /**< do while () */
            }

            /**< END ALLOCATIONS : BE SENSITIVE NOT TO LEAK MEMORY */

            device_p->counter++;

            if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_COUNT_TEMPLATE, pd_mon_internal_prefix, device_p->pn.name))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_WC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1( "device dump count write filename too long %d", pn.asid);

               break; /**< do while () */
            }

            device_p->fd = rfs_open(device_p->filename, RFS_O_WRONLY | RFS_O_CREAT, 755); /**< open .count file (write) */
			qurt_printf("Open .count file: %d again", device_p->fd);
			TMS_MSG_ERROR( "Open .count file again");

            if (0 > device_p->fd || sizeof(device_p->counter) != rfs_write(device_p->fd, (char*)&device_p->counter, sizeof(device_p->counter)))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_WC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_1("device dump count write file not available %d", pn.asid);
            }

            else
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_WC, 2, device_p->hash, pn.asid);
#endif
               TMS_MSG_ERROR_2("device dump count write %d %d", device_p->counter, pn.asid);
            }

            rfs_close(device_p->fd); /**< close .count file (write) */

         } while (0);

         qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

         rc = PD_DUMP_STATUS_SUCCESS; /**< this code path always reports success; check F3 logs for information */

         // rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9);

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_EDE, 2, device_p->hash, pn.asid);
#endif
         TMS_MSG_HIGH_1( "device dump process exit %d", rc);

         break; /**< switch () */
      }
   }

   return rc;
}

/**
INTERNAL, QDI Opener Invocation Object
*/
static struct
{
   qurt_qdi_obj_t qdiobj;

} opener = { { pd_dump_device_invocation, QDI_REFCNT_PERM, 0 } };

/**
API, Initialization of service prior to use
@return
None.
*/
void pd_dump_host_init(void)
{
   qurt_pimutex_init(&pd_dump_internal.mutex); /**< serialize driver access */

   qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

   qurt_qdi_devname_register(PD_DUMP_DEVICE, &opener.qdiobj); /**< register driver */

   qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

   pd_mon_pd_dump_config(&pd_dump_internal.dump_enabled);
}

/**
Termination of service following use
@return
None.
*/
void pd_dump_host_term(void)
{
   /* NULL */ /* DECISION TO NOT CLEANUP SERVICE FOR POST MORTEM REASONS */
}
