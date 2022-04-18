#ifndef QDI_PORTAL_H
#define QDI_PORTAL_H
#include <stdlib.h>
#include "qurt.h"
#include "qurt_qdi_driver.h"

struct portal {
   qurt_qdi_obj_t obj;     //! qdi object
   const char *name;       //! registration name
   int h;                  //! my handle, unreferenced
   void* ctx;              //! user context pointer
   /**
    * can free(me) safely
    */
   void (*release)(struct portal *me);
   /**
    * me->name == name just return a new allocated instance of the same portal
    */
   int (*open_self)(struct portal *me, int caller, const char* name, struct portal **po);
   /**
    * return a new "struct portal" for the remote object
    * Call "qdi_portal_init" on the new client.
    */
   int (*open)(struct portal *me, int caller,
               const char* name, 
               qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3,
               qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6,
               qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9,
               struct portal **po);
   int (*copy_from_user)(struct portal *me, int caller, void *dst, void *src, int size); 
   int (*copy_to_user)(struct portal *me, int caller, void *dst, void *src, int size); 
   /**
    * forward the invoke to the remote side
    */
   int (*invoke)(struct portal *me, int caller, qurt_qdi_obj_t *pobj, int method,
                 qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3,
                 qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6,
                 qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9);
};

/**
 * initializes me, call this first, then set the ctx and vtbl
 */
void qdi_portal_init(struct portal *me);

/**
 * registers the object under me->name
 */
int qdi_portal_register(struct portal *me);
#endif // QDI_PORTAL_H
