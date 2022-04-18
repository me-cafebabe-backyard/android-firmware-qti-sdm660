#ifndef QURT_QDI_HANDLE_INVOKE_AS
#define QURT_QDI_HANDLE_INVOKE_AS

#include "qurt.h"
#include "qurt_qdi_driver.h"

#define qurt_qdi_handle_invoke_as(c,h,m,...) _QDMIA(c,h,m,##__VA_ARGS__,0,0,0,0,0,0,0,0,0)
#define _QDMIARG(x) ((qurt_qdi_arg_t){.num=(int)(x)})
#define _QDMIA(c,h,m,a1,a2,a3,a4,a5,a6,a7,a8,a9,...)     \
   qurt_qdi_raw_invoke_as((int)(c),(int)(h),(int)(m), \
                          _QDMIARG(a1), _QDMIARG(a2), _QDMIARG(a3), \
                          _QDMIARG(a4), _QDMIARG(a5), _QDMIARG(a6), \
                          _QDMIARG(a7), _QDMIARG(a8), _QDMIARG(a9))

static inline int qurt_qdi_raw_invoke_as(int c, int h, int m,
                                         qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3,
                                         qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6,
                                         qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9)
{
   qurt_qdi_obj_t *ptr;
   int ret;

   ret = -1;
   ptr = qurt_qdi_objref_get_from_handle(c, h);        // Ask the client handle to turn the handle into an object pointer.
   if (ptr) {
      ret = (*ptr->invoke)(c,ptr,m,a1,a2,a3,a4,a5,a6,a7,a8,a9);
      qurt_qdi_objref_release(ptr);
   }
   return ret;
}


#endif // QURT_QDI_HANDLE_INVOKE_AS
