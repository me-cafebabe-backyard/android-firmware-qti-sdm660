#ifndef MBSERVER_H
#define MBSERVER_H

#include "mbcommon.h"

struct mbserver;
int mbserver_create(int asid,
                    int (*pfn_invoke)(void* ctx, struct invoke *i), void *ctx_invoke,
                    struct mbserver **po);

void mbserver_destroy(struct mbserver *me);
void mbserver_close(struct mbserver *me);

int mbserver_copy_from_user(struct mbserver *me, void *dst, const void *src, int size);
int mbserver_futex_wake(struct mbserver *me, unsigned *fut);
int mbserver_copy_to_user(struct mbserver *me, void *dst, const void *src, int size);
int mbserver_futex_create(struct mbserver *me, int val);
#endif // MBSERVER_H
