#ifndef QURT_ISLAND_H
#define QURT_ISLAND_H

/**
  @file qurt_island.h 
  @brief  Prototypes of power API  
          The APIs allow entering and exiting island mode where the memory
          accesses are limited to local memory.

  EXTERNAL FUNCTIONS
   None.

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

Copyright (c) 2013  by Qualcomm Technologies, Inc.  All Rights Reserved.

=============================================================================*/
#include <qurt_thread.h>
#include <qurt_memory.h>
#include <qurt_alloc.h>
#include <qurt_error.h>

/** @cond */
enum qurt_island_attr_element_type {
    QURT_ISLAND_ATTR_INVALID,
    QURT_ISLAND_ATTR_INT,
    QURT_ISLAND_ATTR_THREAD,
    QURT_ISLAND_ATTR_MEMORY
};

struct qurt_island_attr_element {
    enum qurt_island_attr_element_type type;
    union {
        unsigned int interrupt;
        qurt_thread_t thread_id;
        struct {
            qurt_addr_t base_addr;
            qurt_size_t size;
        };
    };
};
/** @endcond */

/** QuRT island attributes */
typedef struct qurt_island_attr {
    /** @cond */
    int max_attrs;
    struct qurt_island_attr_element attrs[1];
    /** @endcond */
} qurt_island_attr_t;

/** Thread ID type */
typedef unsigned int qurt_island_t;

/**@ingroup func_qurt_island_attr_create
  Creates QuRT island attribute.\n
  This function allocates memory for island attributes. The memory can contain
  maximum number of attributes equal to max_attrs. All the attributes are
  initialized as "QURT_ISALND_ATTR_INVALID" type.
 
  @return
  QURT_EOK -- attr is created successfully. \n
  QURT_EMEM -- attr is not created successfully. \n

  @dependencies
  None.
 */
int qurt_island_attr_create (qurt_island_attr_t **attr, int max_attrs);

/**@ingroup func_qurt_island_attr_delete
  Deletes QuRT island attribute.\n
  This function frees memory allocated for QuRT island attributes.
 
  @return
  None. \n

  @dependencies
  None.
 */
void qurt_island_attr_delete (qurt_island_attr_t *attr);

/**@ingroup func_qurt_island_attr_set_interrupt
  Sets interrupt attribute.\n
  This function sets interrupt number to the island attribute.
 
  @datatypes
  #qurt_island_attr_t \n

  @param[in] interrupt number

  @return
  None. \n

  @dependencies
  None.
 */
void qurt_island_attr_set_interrupt (qurt_island_attr_t *attr, unsigned int interrupt);

/**@ingroup func_qurt_island_attr_set_mem
  Sets memory attribute.\n
  This function sets memory address range to the island attrbute.

  @datatypes
  #qurt_addr_t \n
  #qurt_size_t \n
  #qurt_island_attr_t \n
 
  @param[in] base_addr    Base address of the memory range
  @param[in] size         Size (in bytes) of the memory range
 
  @return
  None. \n

  @dependencies
  None.
 */
void qurt_island_attr_set_mem (qurt_island_attr_t *attr, qurt_addr_t base_addr, qurt_size_t size);

/**@ingroup func_qurt_island_attr_set_thread
  Sets thread attribute.\n
  This function sets thread id to the island attrbute.

  @datatypes
  #qurt_thread_t \n
  #qurt_island_attr_t \n
 
  @param[in] thread_id  Thread ID
 
  @return
  None. \n

  @dependencies
  None.
 */
void qurt_island_attr_set_thread  (qurt_island_attr_t *attr, qurt_thread_t thread_id);

/**@ingroup func_qurt_island_prepare
  Prepares for island mode.\n
  This function verifies if the attributes are valid for an island and creates internal data structures that can help enter island mode.
 
  @datatypes
  #qurt_island_t \n
  #qurt_island_attr_t \n

  @param[in] attr  Attributes that define the island
  @param[out] prepare_id ID that identify the island configuration, which is defined by the attributes.

  @return
  QURT_EOK -- prepare was successfully performed.  \n
  QURT_INVALID -- Attributes can't form an island. \n

  @dependencies
  None.
 */
int qurt_island_prepare (qurt_island_t *prepare_id, qurt_island_attr_t *attr);

/**@ingroup func_qurt_island_enter
  Enter island mode.\n
  This function triggers the island mode. The island is defined with the prepae_id. The system should be in single threaded Mode to be able to enter island mode.

  @datatypes
  #qurt_island_t \n

  @param[in] prepare_id ID returned as part of prepare.
 
  @return
  QURT_EOK -- Successfully entered island mode. \n
  QURT_ESTM -- System is not in Single Threaded Mode.

  @dependencies
  None.
 */
int qurt_island_enter (qurt_island_t prepare_id);

/**@ingroup func_qurt_island_exit
  Exit island mode.\n
  This function brings the system out of island mode. The should be in island mode to be able to bring the system out of island mode.
 
  @return
  QURT_EOK -- Operation was successfully performed. \n
  QURT_EFAILED -- The system is not brought of island mode.

  @dependencies
  None.
 */
int qurt_island_exit (void);

/**@ingroup func_qurt_island_exception_wait
  Registers the program exception handler.
  This function assigns the current thread as the QuRT island exception handler and suspends the
  thread until a exception occurs within island mode.

  When exception occurs in island mode, the thread is awakened with error information
  assigned to this operations parameters.

  @note1hang If no island exception handler is registered, or if the registered handler
             itself calls exit, then QuRT raises a kernel exception.
             If a thread runs in Supervisor mode, any errors are treated as kernel
             exceptions.

  @param[out]  ip      Pointer to the instruction memory address where the exception occurred.
  @param[out]  sp      Stack pointer.
  @param[out]  badva   Pointer to the virtual data address where the exception occurred due to memory access.
                       Pointer to the interrupt number when exception occured due to the reception of non island interrupt.
  @param[out]  cause   Pointer to the QuRT error result code.   

  @return
  Registry status: \n
  - Thread identifier -- Handler successfully registered. \n
  - QURT_EFATAL -- Registration failed.

  @dependencies
  None.
*/
unsigned int qurt_island_exception_wait (unsigned int *ip, unsigned int *sp,
                                         unsigned int *badva, unsigned int *cause);

#endif /* QURT_ISLAND_H */
