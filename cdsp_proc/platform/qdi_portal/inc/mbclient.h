#ifndef MBCLIENT_H
#define MBCLIENT_H

#include "mbcommon.h"

struct mbclient;
int mbclient_create(int asid, 
                    void (*pfn_exit)(void*),
                    void *ctx_exit,
                    struct mbclient **po);
int mbclient_start(struct mbclient *me);
void mbclient_stats(struct mbclient *me, uint64_t *nread, uint64_t *nwrite, uint64_t *wusecs);

//! error if pfn is already set
int mbclient_atexit(struct mbclient *me,
                    void (*pfn_exit)(void*),
                    void *ctx_exit);

void mbclient_destroy(struct mbclient *me);
void mbclient_suspend(struct mbclient *me);
int mbclient_invoke(struct mbclient *me, int nargs, struct invoke *inv, int *rsp);

#endif // MBCLIENT_H
