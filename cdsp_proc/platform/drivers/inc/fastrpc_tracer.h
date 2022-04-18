#include "qurt_qdi.h"
#include "qurt_types.h"

#define QDI_DRIVER_TRACER_NAME  "/dev/fastrpc_tracer"
#define QDI_TRACER_BASE         256
#define QDI_TRACER_WRITE_END    (QDI_TRACER_BASE + 0)

static __inline int fastrpc_tracer_qdi_open(void) {
   return qurt_qdi_open(QDI_DRIVER_TRACER_NAME);
}
static __inline int fastrpc_tracer_qdi_close(int handle) {
   return qurt_qdi_close(handle);
}
static __inline int fastrpc_tracer_qdi_write(int handle, const void *pv, unsigned len) {
   return qurt_qdi_handle_invoke(handle, QDI_WRITE, pv, len);
}
static __inline int fastrpc_tracer_qdi_write_end(int handle) {
   return qurt_qdi_handle_invoke(handle, QDI_TRACER_WRITE_END);
}
