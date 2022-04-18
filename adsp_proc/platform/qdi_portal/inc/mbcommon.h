#ifndef MBCOMMON_H
#define MBCOMMON_H

#include <stdint.h>
#include "qurt.h"
#include "qurt_qdi_driver.h"
#include "AEEQList.h"

enum command {
   COMMAND_INVOKE,
   COMMAND_INVOKE_RSP,
   COMMAND_WAKE,
   COMMAND_COPY_TO_USER,
   COMMAND_COPY_FROM_USER,
   COMMAND_COPY_FROM_USER_RSP,
   COMMAND_SUSPEND_CLIENT,
};
struct invoke_hdr {
   enum command type;
   uintptr_t ctx;
   uintptr_t go;
   int method;
};

struct invoke {
   enum command type;
   uintptr_t ctx;
   uintptr_t go;
   int method;
   qurt_qdi_arg_t a[9];
};

struct invoke_rsp {
   enum command type;
   uintptr_t ctx;
   int rv;
};

struct wake {
   enum command type;
   uintptr_t fut;
};

struct copy_to_user_hdr {
   enum command type;
   int size;
   uintptr_t dst;
};

struct copy_to_user {
   enum command type;
   int size;
   uintptr_t dst;
   char data[1]; //! overallocated
};

struct copy_from_user {
   enum command type;
   int size;
   uintptr_t src;
   uintptr_t ctx;
};

struct copy_from_user_rsp_hdr {
   enum command type;
   uintptr_t ctx;
};

struct copy_from_user_rsp {
   enum command type;
   uintptr_t ctx;
   char data[1]; //! overallocated
};

union commands {
   enum command type;
   struct invoke_hdr ihdr;
   struct invoke inv;
   struct invoke_rsp invrsp;
   struct wake wake;
   struct copy_to_user_hdr c2uhdr;
   struct copy_to_user c2u;
   struct copy_from_user cfu;
   struct copy_from_user_rsp_hdr cfursphdr;
   struct copy_from_user_rsp cfursp;
};

struct thread {
   QNode qn;
   int rv;
   unsigned fut;
   char *dst;
   int size;
};

#endif //MBCOMMON_H
