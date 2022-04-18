#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "comdef.h"
#include "rpm_hwio.h"
#include "HALhwio.h"

uint64_t time_service_now(void);

#ifdef __cplusplus
}
#endif

#endif // TIME_SERVICE_H

