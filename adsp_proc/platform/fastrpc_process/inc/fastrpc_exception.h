#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

/**
 * this will either crash or stop the exception handler
 *
 * @retval, ignore this value
 */
volatile int* exception_handler_stop(void);

int exception_handler_start(void);

#endif // EXCEPTION_HANDLER_H
