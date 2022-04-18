#ifndef GP_UTILS_H
#define GP_UTILS_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "gpTypes.h"

/*----------------------------------------------------------------------------
 * Constant defines
 * -------------------------------------------------------------------------*/
#define MINK_SUCCESS          0
#define MINK_GENERIC_ERROR   -1

//Loop Function for testing
#define LoopHere2() {volatile int er = 1; while(er);}

void
gp_print_uuid(
  TEE_UUID  uuid);

#endif /* GP_UTILS_H */
