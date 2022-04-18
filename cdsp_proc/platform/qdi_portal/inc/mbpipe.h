#ifndef MBPIPE_H
#define MBPIPE_H
#include "qurt.h"
#include "qurt_mailbox.h"

struct mbpipe;

//! pipe desinged for multiple senders single reader
int mbpipe_connect(int tries,               //! number of times to poll for client
                   char myname[8],          //! myname name
                   char client[8],          //! client name
                   qurt_mailbox_receiver_cfg_t client_domain, //! client domain
                   struct mbpipe **po);     //! return value

//! closes the pipe, write and read should fail
void mbpipe_close(struct mbpipe *me);

//! closes and frees
void mbpipe_destroy(struct mbpipe *me);
void mbpipe_stats(struct mbpipe *me, uint64_t *read, uint64_t *written, uint64_t *wusecs);

/**
 * Read a single buffer.  Only supports single reader.
 * @param pread, bytes read
 * @pleft, minimum number of bytes left, more may be in buffer
 * @retval, 0 on succes, other error if port is closed.
 */
int mbpipe_read(struct mbpipe *me, char *data, int num, int *pread, int *pleft);
/**
 * Write multiple memory regions as a single buffer.
 * @retval, 0 on succes, other error if pipe is closed.
 */
int mbpipe_writev(struct mbpipe *me, char *data[], int sz[], int num);

static __inline int mbpipe_write(struct mbpipe *me, char *data, int size) {
   return mbpipe_writev(me, &data, &size, 1);
}

#endif // MBPIPE_H
