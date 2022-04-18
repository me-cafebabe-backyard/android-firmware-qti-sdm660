// Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#ifndef __QSEE_OPEN_H
#define __QSEE_OPEN_H

#include "object.h"
#include <stdarg.h>

// A UID that does not identify any service.
//
#define QSEE_OPEN_INVALID_ID 0


// Set the object to be used as the environment for the process.
//
extern void qsee_set_env(Object o);

// Printf function used by common lib for logging messages to the environment
//
extern void qsee_printf_ap(const char* fmt, va_list ap);

// Request a service from the system.
//
// On success, *objOut will hold the resulting object reference and
// Object_OK will be returned.  In this case, the caller will hold a
// reference to the object and is responsible for releasing it at some
// point.
//
// Otherwise, a non-zero value defined in IOpener will be returned. The
// value of objOut will be non-deterministic in case of an error and
// the caller should not access it.
//
extern int32_t qsee_open(uint32_t uid, Object *objOut);


// Request a service from the system if it has not already been obtained.
//
// If the object has already been obtained, it will be returned and
// the object reference will not be retained (the caller does not need to
// call release once for each successful call).
//
// Singleton objects are declared statically within the qsee_open_singleton
// function.   This is to allow qsee shims to be linked into commonlib 
// while keeping the object reference in the app's static data. 
//
// On failure, Object_NULL is returned.
//
extern Object qsee_open_singleton(uint32_t classID);

#endif /* __QSEE_OPEN_H */
