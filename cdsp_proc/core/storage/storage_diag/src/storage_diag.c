/***********************************************************************
 * storage_diag.c
 *
 * Storage Diag module to test any storage module via Diag commands.
 * Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 *
 * Storage Diag module to test any storage module via Diag commands.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.qdsp6/1.0.c2/storage/storage_diag/src/storage_diag.c#1 $ $DateTime: 2020/02/10 01:57:30 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-05-06   dks   Add OS abstraction layer
2015-04-30   dks   Collect debug_info from rfs_read and rfs_write APIs.
2014-10-20   dks   Remove rfs and tftp dependency
2014-09-19   dks   Add hooks to extract performance numbers.
2014-08-26   rp    Bring in changes from target-unit-testing.
2014-08-04   rp    Create

===========================================================================*/


#include "storage_diag_config_i.h"
#include "storage_diag.h"
#include "storage_diag_assert.h"
#include "storage_diag_msg.h"
#include "fs_os.h"
#include "fs_os_malloc.h"

#include "comdef.h"
#include "queue.h"
#include "diagpkt.h"
#include "diagcmd.h"
#include "rfs_api.h"

#include "fs_public.h"
#include "fs_errno.h"
#include "fs_lib.h"

#ifndef FEATURE_STORAGE_DIAG_COMPILE_WITHOUT_EFS
  #include "fs_priv_funcs.h"
#endif

#include "rfs_utils.h"
#include "rfs_errno.h"
#include <stringl/stringl.h>


/* Lint wants parens around macro but compile will fail */
/*lint -save -e773 */
#define VOID_PACKED_PTR        PACKED void * PACKED_POST
#define DECLARE_DIAG_FN(fn)    VOID_PACKED_PTR fn (VOID_PACKED_PTR, uint16)
/*lint -restore */


enum storage_diag_result_type
{
  STORAGE_DIAG_RESULT_SUCCESS             = 0,
  STORAGE_DIAG_RESULT_FAILED              = 1,
  STORAGE_DIAG_RESULT_INVALID_ARG         = 2,
  STORAGE_DIAG_RESULT_INVALID_HANDLE      = 3,
  STORAGE_DIAG_RESULT_NOMEM               = 4,
  STORAGE_DIAG_RESULT_NOT_STARTED         = 5,
  STORAGE_DIAG_RESULT_STILL_RUNNING       = 6,
  STORAGE_DIAG_RESULT_UNKNOWN_CMD         = 7,
  STORAGE_DIAG_RESULT_BAD_PKT_LEN         = 8,
  STORAGE_DIAG_RESULT_CREATE_THREAD_FAIL  = 9,
  STORAGE_DIAG_RESULT_NOENTRY             = 10,
  STORAGE_DIAG_RESULT_NOACCESS            = 11,
  STORAGE_DIAG_RESULT_NOPERMISSION        = 12,
  STORAGE_DIAG_RESULT_EXISTS              = 13,
  STORAGE_DIAG_RESULT_NODEV               = 14,
  STORAGE_DIAG_RESULT_MAX_FDS             = 15,
  STORAGE_DIAG_RESULT_NO_SPACE            = 16,
  STORAGE_DIAG_RESULT_NAME_TOO_LONG       = 17,
  STORAGE_DIAG_RESULT_DEVICE_BUSY         = 18,
  STORAGE_DIAG_RESULT_TIMEOUT             = 19,
  STORAGE_DIAG_RESULT_INVALID_CONFIG      = 20,
  STORAGE_DIAG_RESULT_OP_NOT_SUPPORTED    = 21,
};


static enum storage_diag_result_type
storage_diag_map_rfs_errors (int rfs_errno)
{
  switch (rfs_errno)
  {
     case RFS_ENOERROR:
       return STORAGE_DIAG_RESULT_SUCCESS;

     case RFS_ENOENT:
       return STORAGE_DIAG_RESULT_NOENTRY;

     case RFS_EACCESS:
       return STORAGE_DIAG_RESULT_NOACCESS;

     case RFS_ENOMEM:
       return STORAGE_DIAG_RESULT_NOMEM;

     case RFS_EPERM:
       return STORAGE_DIAG_RESULT_NOPERMISSION;

     case RFS_EBADF:
       return STORAGE_DIAG_RESULT_INVALID_HANDLE;

     case RFS_EEXISTS:
       return STORAGE_DIAG_RESULT_EXISTS;

     case RFS_ENODEV:
       return STORAGE_DIAG_RESULT_NODEV;

     case RFS_EINVAL:
       return STORAGE_DIAG_RESULT_INVALID_ARG;

     case RFS_EMFILE:
       return STORAGE_DIAG_RESULT_MAX_FDS;

     case RFS_ENOSPC:
       return STORAGE_DIAG_RESULT_NO_SPACE;

     case RFS_ENAMETOOLONG:
       return STORAGE_DIAG_RESULT_NAME_TOO_LONG;

     case RFS_EBUSY:
       return STORAGE_DIAG_RESULT_DEVICE_BUSY;

     case RFS_ETIMEOUT:
       return STORAGE_DIAG_RESULT_TIMEOUT;

     case RFS_ECONFIG:
       return STORAGE_DIAG_RESULT_INVALID_CONFIG;

     case RFS_ENOTSUPPORTED:
       return STORAGE_DIAG_RESULT_OP_NOT_SUPPORTED;

     case RFS_ESYSTEM:
     default:
       return STORAGE_DIAG_RESULT_FAILED;
  }
}

/*--------------------------------------------------------------------
 * storage-diag : cmd_q
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_add_req_hdr_type
{
  diagpkt_subsys_header_type hdr;
  uint32 run_in_thread;
  uint32 run_later;
  uint32 reserved;
  uint32 sub_cmd_id;
  uint32 sub_cmd_req_pkt_len;
} PACKED_POST;

PACKED struct storage_diag_cmd_q_add_req_type
{
  struct storage_diag_cmd_q_add_req_hdr_type hdr;
  uint8  sub_cmd_req_pkt[STORAGE_DIAG_CMD_Q_MAX_PKT_SIZE];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rsp_hdr_type
{
  diagpkt_subsys_header_type hdr;
  uint32 result;
  uint32 state;
  uint32 cmd_q_handle;
  uint32 sub_cmd_id;
  struct rfs_debug_info_type dbg_info;
  uint32 sub_cmd_rsp_pkt_len;
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rsp_type
{
  struct storage_diag_cmd_q_rsp_hdr_type hdr;
  uint8  sub_cmd_rsp_pkt[STORAGE_DIAG_CMD_Q_MAX_PKT_SIZE];
} PACKED_POST;


enum storage_diag_cmd_q_node_state
{
  STORAGE_DIAG_CMD_STATE_NOT_STARTED     = 0,
  STORAGE_DIAG_CMD_STATE_RUNNING         = 1,
  STORAGE_DIAG_CMD_STATE_COMPLETE        = 2,
};

struct storage_diag_cmd_q_node_type
{
  q_link_type link;
  q_type      *done_q_ptr;

  uint32 cmd_q_id;
  enum storage_diag_cmd_q_node_state state;

  uint32 cmd_q_req_len;
  struct storage_diag_cmd_q_add_req_type cmd_q_req;

  uint32 cmd_q_rsp_len;
  struct storage_diag_cmd_q_rsp_type cmd_q_rsp;

  fs_os_thread_t thread_handle;
  char thread_name[20];
};

struct storage_diag_info_type
{
  uint32 cmd_q_id;
  q_type cmd_q;
};

static struct storage_diag_info_type storage_diag_info;
static fs_os_mutex_t storage_diag_mutex;


typedef void (*STORAGE_DIAG_CMD_Q_HANDLER) (
              struct storage_diag_cmd_q_node_type *cmd_q_node);


/* Lint wants parens around macro but compile will fail */
/*lint -save -e773 */
#define DECLARE_CMD_Q_DIAG_FN(fn) \
              static void fn (struct storage_diag_cmd_q_node_type *cmd_q_node)
/*lint -restore */


DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_hello_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_efs_to_rfs_dir_copy_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_rfs_write_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_cmd_id_rfs_put_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_cmd_id_rfs_get_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_cmd_id_rfs_write_perf_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_cmd_id_rfs_read_perf_handler);
DECLARE_CMD_Q_DIAG_FN(storage_diag_cmd_q_cmd_id_fs_qmi_handler);

enum storage_diag_cmd_q_cmd_id_type
{
  STORAGE_DIAG_CMD_Q_CMD_ID_HELLO                      = 0,
  STORAGE_DIAG_CMD_Q_CMD_ID_EFS_TO_RFS_DIR_COPY        = 1,
  STORAGE_DIAG_CMD_Q_CMD_ID_RFS_WRITE                  = 2,
  STORAGE_DIAG_CMD_Q_CMD_ID_RFS_PUT                    = 3,
  STORAGE_DIAG_CMD_Q_CMD_ID_RFS_GET                    = 4,
  STORAGE_DIAG_CMD_Q_CMD_ID_RFS_WRITE_PERF             = 5,
  STORAGE_DIAG_CMD_Q_CMD_ID_RFS_READ_PERF              = 6,
  STORAGE_DIAG_CMD_Q_CMD_ID_FS_QMI                     = 7,
};

struct storage_diag_cmd_q_tbl_type
{
  uint32 cmd_id;
  STORAGE_DIAG_CMD_Q_HANDLER cmd_q_handler;
};

static struct storage_diag_cmd_q_tbl_type storage_diag_cmd_q_tbl[] =
{
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_HELLO,
    storage_diag_cmd_q_hello_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_EFS_TO_RFS_DIR_COPY,
    storage_diag_cmd_q_efs_to_rfs_dir_copy_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_RFS_WRITE,
    storage_diag_cmd_q_rfs_write_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_RFS_PUT,
    storage_diag_cmd_q_cmd_id_rfs_put_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_RFS_GET,
    storage_diag_cmd_q_cmd_id_rfs_get_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_RFS_GET,
    storage_diag_cmd_q_cmd_id_rfs_get_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_RFS_WRITE_PERF,
    storage_diag_cmd_q_cmd_id_rfs_write_perf_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_RFS_READ_PERF,
    storage_diag_cmd_q_cmd_id_rfs_read_perf_handler
  },
  {
    STORAGE_DIAG_CMD_Q_CMD_ID_FS_QMI,
    storage_diag_cmd_q_cmd_id_fs_qmi_handler
  },
};

static uint32 storage_diag_cmd_q_tbl_count =
    (sizeof (storage_diag_cmd_q_tbl) / sizeof (storage_diag_cmd_q_tbl[0]));

static struct storage_diag_cmd_q_tbl_type*
storage_diag_cmd_q_tbl_get_entry (uint32 sub_cmd_id)
{
  uint32 i;
  struct storage_diag_cmd_q_tbl_type *tbl_entry = NULL;

  for ( i = 0; i < storage_diag_cmd_q_tbl_count; ++i )
  {
    tbl_entry = &storage_diag_cmd_q_tbl[i];
    if (tbl_entry->cmd_id == sub_cmd_id)
      return tbl_entry;
  }

  return NULL;
}

/*--------------------------------------------------------------------
 * cmd-q handler
 *-------------------------------------------------------------------*/

static void
storage_diag_memset_diag_pkt (uint8 *diag_pkt_buf, uint32 diag_pkt_buf_len)
{
  uint32 hdr_size, payload_len;

  hdr_size = sizeof (diagpkt_subsys_header_type);

  STORAGE_DIAG_ASSERT (diag_pkt_buf != NULL);
  STORAGE_DIAG_ASSERT (diag_pkt_buf_len > hdr_size);

  diag_pkt_buf += hdr_size;
  payload_len = diag_pkt_buf_len - hdr_size;
  memset (diag_pkt_buf, 0, payload_len);
}


static void
storage_diag_cmd_change_state (struct storage_diag_cmd_q_node_type *cmd_node,
                               enum storage_diag_cmd_q_node_state new_state)
{
  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (new_state <= STORAGE_DIAG_CMD_STATE_COMPLETE);

  fs_os_mutex_lock (&storage_diag_mutex);

  switch (cmd_node->state)
  {
    case STORAGE_DIAG_CMD_STATE_NOT_STARTED:
      STORAGE_DIAG_ASSERT (new_state == STORAGE_DIAG_CMD_STATE_RUNNING);
      cmd_node->state = new_state;
      break;

    case STORAGE_DIAG_CMD_STATE_RUNNING:
      STORAGE_DIAG_ASSERT (new_state == STORAGE_DIAG_CMD_STATE_COMPLETE);
      cmd_node->state = new_state;
      break;

    case STORAGE_DIAG_CMD_STATE_COMPLETE:
      STORAGE_DIAG_ASSERT (0); /* Already reached last state*/
      break;

    default:
      STORAGE_DIAG_ASSERT (0);
      break;
  }

  fs_os_mutex_unlock (&storage_diag_mutex);
}

static void
storage_diag_cmd_q_execute_node (struct storage_diag_cmd_q_node_type *cmd_node)
{
  struct storage_diag_cmd_q_add_req_type *cmd_q_req = NULL;
  struct storage_diag_cmd_q_rsp_type *cmd_q_rsp = NULL;
  struct storage_diag_cmd_q_tbl_type *cmd_q_tbl_entry = NULL;

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len > 0);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  storage_diag_cmd_change_state (cmd_node, STORAGE_DIAG_CMD_STATE_RUNNING);

  cmd_q_req = &cmd_node->cmd_q_req;
  cmd_q_rsp = &cmd_node->cmd_q_rsp;

  cmd_q_tbl_entry =
      storage_diag_cmd_q_tbl_get_entry (cmd_q_req->hdr.sub_cmd_id);
  if (cmd_q_tbl_entry == NULL)
  {
    STORAGE_DIAG_MSG_ERROR_1 ("storage_diag_cmd_q_execute_node uknown cmd %d",
                               cmd_q_req->hdr.sub_cmd_id);
    cmd_q_rsp->hdr.result = STORAGE_DIAG_RESULT_UNKNOWN_CMD;
    goto End;
  }

  cmd_q_tbl_entry->cmd_q_handler (cmd_node);

End:
  storage_diag_cmd_change_state (cmd_node, STORAGE_DIAG_CMD_STATE_COMPLETE);
  return;
}

fs_os_thread_return_type
storage_diag_cmd_q_add_handler_thread_proc (void *thread_param)
{
  struct storage_diag_cmd_q_node_type *cmd_node = NULL;

  STORAGE_DIAG_MSG_HIGH_0 ("thread-proc start");

  cmd_node = (struct storage_diag_cmd_q_node_type *)thread_param;
  STORAGE_DIAG_ASSERT (cmd_node != NULL);

  storage_diag_cmd_q_execute_node (cmd_node);

  STORAGE_DIAG_MSG_HIGH_0 ("thread-proc end");

  return (fs_os_thread_return_type) NULL;
}


static int
storage_diag_cmd_q_compare_func (void *item_ptr, void *compare_val)
{
  struct storage_diag_cmd_q_node_type *cmd_node = NULL;
  uint32 *compare_val_ptr, cmd_q_id;
  int match = 0;

  STORAGE_DIAG_ASSERT (item_ptr != NULL);
  STORAGE_DIAG_ASSERT (compare_val != NULL);

  cmd_node = (struct storage_diag_cmd_q_node_type *)item_ptr;

  compare_val_ptr = (uint32 *)compare_val;
  cmd_q_id = *compare_val_ptr;

  if (cmd_node->cmd_q_id == cmd_q_id)
  {
    match = 1;
  }

  return match;
}




/*--------------------------------------------------------------------
 * cmd-q handler : hello
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_hello_req_type
{
  uint32 print_this_number;
} PACKED_POST;

PACKED struct storage_diag_cmd_q_hello_rsp_type
{
  uint32 print_this_number;
} PACKED_POST;

static void
storage_diag_cmd_q_hello_handler (struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 req_pkt_len, full_rsp_pkt_len, hello_rsp_pkt_len;
  struct storage_diag_cmd_q_hello_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_hello_rsp_type *rsp_pkt = NULL;

  STORAGE_DIAG_MSG_HIGH_0 ("cmd-q hello handler start");

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req.hdr.sub_cmd_id ==
                       STORAGE_DIAG_CMD_Q_CMD_ID_HELLO);

  req_pkt_len  = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len += sizeof (struct storage_diag_cmd_q_hello_req_type);

  full_rsp_pkt_len  = sizeof (struct storage_diag_cmd_q_rsp_hdr_type);
  hello_rsp_pkt_len = sizeof (struct storage_diag_cmd_q_hello_rsp_type);
  full_rsp_pkt_len += hello_rsp_pkt_len;

  if (cmd_node->cmd_q_req_len != req_pkt_len)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("hello-cmd-q : bad req-pkt [%d < %d]",
                             cmd_node->cmd_q_req_len, req_pkt_len);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  if (cmd_node->cmd_q_rsp_len < full_rsp_pkt_len)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("hello-cmd-q : bad rsp-pkt [%d < %d]",
                             cmd_node->cmd_q_rsp_len, full_rsp_pkt_len);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  req_pkt = (struct storage_diag_cmd_q_hello_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_hello_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  rsp_pkt->print_this_number = req_pkt->print_this_number + 1;
  cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = hello_rsp_pkt_len;

  STORAGE_DIAG_MSG_HIGH_2 ("cmd-q hello handler 1 : %d : %d",
                           (int)req_pkt->print_this_number,
                           (int)rsp_pkt->print_this_number);

  End:
  STORAGE_DIAG_MSG_HIGH_0 ("cmd-q hello handler end");
  return;
}



/*--------------------------------------------------------------------
 * cmd-q handler : efs_to_rfs_dir_copy
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_efs_to_rfs_dir_copy_req_type
{
  uint8 efs_path[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_efs_to_rfs_dir_copy_rsp_type
{
  uint32 num_files_copied;
} PACKED_POST;



struct storage_diag_cmd_q_efs_dir_iter_param_type
{
  q_link_type   link;
  q_type        *done_q_ptr;

  uint32 file_size;
  char efs_path[STORAGE_DIAG_MAX_PATH_LEN];
  char rfs_path[STORAGE_DIAG_MAX_PATH_LEN];
};

#ifndef FEATURE_STORAGE_DIAG_COMPILE_WITHOUT_EFS

int
storage_diag_efs_iter_cb (char *path, struct fs_stat *sbuf, const void *param)
{
  q_type *efs_iter_cb_q;
  struct storage_diag_cmd_q_efs_dir_iter_param_type *iter_node = NULL;
  uint32 iter_node_size;
  int efs_path_len;
  char *temp_path;

  STORAGE_DIAG_ASSERT (path != NULL);
  STORAGE_DIAG_ASSERT (sbuf != NULL);
  STORAGE_DIAG_ASSERT (param != NULL);
  efs_iter_cb_q = (q_type *)param;

  STORAGE_DIAG_MSG_HIGH_2 ("storage_diag_efs_iter_cb %s %d\n", path, sbuf->st_size);

  efs_path_len = strlen (path);
  if (efs_path_len > STORAGE_DIAG_MAX_PATH_LEN)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("cmd-q efs_2_rfs handler efs_iter_cb 2: %d",
                             (int)efs_path_len);
    return -1;
  }

  iter_node_size = sizeof (struct storage_diag_cmd_q_efs_dir_iter_param_type);
  iter_node = fs_os_malloc (iter_node_size);
  if (iter_node == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("cmd-q efs_2_rfs handler malloc-fail 3:");
    return -1;
  }

  iter_node->file_size = sbuf->st_size;

  strlcpy (iter_node->efs_path, path, sizeof (iter_node->efs_path));
  temp_path = strrchr (path, '/');
  if (temp_path != NULL)
  {
    ++temp_path;
  }
  else
  {
    temp_path = path;
  }

  snprintf (iter_node->rfs_path, sizeof (iter_node->rfs_path),
            "/readwrite/%s", temp_path);

  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q efs_2_rfs handler file-size: %d",
                           (int)iter_node->file_size);

  STORAGE_DIAG_MSG_STRING_1 ("%s", iter_node->efs_path);
  STORAGE_DIAG_MSG_STRING_1 ("%s", iter_node->rfs_path);

  q_link (iter_node, &iter_node->link);
  q_put (efs_iter_cb_q, &iter_node->link);

  return 0;
}

static int
storage_diag_copy_efs_to_rfs (struct storage_diag_cmd_q_efs_dir_iter_param_type *iter_node)
{
  uint8 *file_buf = NULL;
  int result;

  STORAGE_DIAG_ASSERT (iter_node != NULL);

  STORAGE_DIAG_MSG_STRING_1 ("%s", iter_node->efs_path);
  STORAGE_DIAG_MSG_STRING_1 ("%s", iter_node->rfs_path);

  file_buf = fs_os_malloc (iter_node->file_size);
  if (file_buf == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("cmd-q efs_2_rfs handler malloc-failed: %d",
                             (int)iter_node->file_size);
    result = STORAGE_DIAG_RESULT_NOMEM;
    goto End;
  }

  result = efs_get (iter_node->efs_path, file_buf, iter_node->file_size);
  if (result != iter_node->file_size)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("cmd-q efs_2_rfs handler efs_get failed: %d : %d",
                             (int)result, (int)efs_errno);
    result = STORAGE_DIAG_RESULT_FAILED;
    goto End;
  }

  result = rfs_put (iter_node->rfs_path, file_buf, iter_node->file_size,
                    RFS_O_CREAT | RFS_O_WRONLY | RFS_O_TRUNC, 0644);
  if (result != iter_node->file_size)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("cmd-q efs_2_rfs handler rfs_put failed: %d",
                             (int)result);
    result = STORAGE_DIAG_RESULT_FAILED;
    goto End;
  }

End:
  if (file_buf != NULL)
  {
    fs_os_free (file_buf);
  }

  return 0;
}

#endif /* FEATURE_STORAGE_DIAG_COMPILE_WITHOUT_EFS */

static void
storage_diag_cmd_q_efs_to_rfs_dir_copy_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp;
  struct storage_diag_cmd_q_efs_to_rfs_dir_copy_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_efs_to_rfs_dir_copy_rsp_type *rsp_pkt = NULL;
  struct storage_diag_cmd_q_efs_dir_iter_param_type efs_iter_cb_param;
  struct storage_diag_cmd_q_efs_dir_iter_param_type *iter_node = NULL;
  struct storage_diag_cmd_q_efs_dir_iter_param_type *temp_iter_node = NULL;
  q_type *efs_iter_cb_param_q_ptr = NULL;
  int result;

  STORAGE_DIAG_MSG_HIGH_0 ("cmd-q efs_2_rfs handler start");

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_efs_to_rfs_dir_copy_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_efs_to_rfs_dir_copy_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("cmd-q efs_2_rfs handler bad-len: %d > %d",
                             (int)cmd_node->cmd_q_req_len, (int)temp);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  efs_iter_cb_param_q_ptr = fs_os_malloc (sizeof (q_type));
  if (efs_iter_cb_param_q_ptr == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("cmd-q efs_2_rfs handler malloc-failed: %d",
                             (int)sizeof (q_type));
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_NOMEM;
    goto End;
  }

  rsp_pkt->num_files_copied = 0;
  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;

  memset (&efs_iter_cb_param, 0, sizeof (efs_iter_cb_param));

  q_init (efs_iter_cb_param_q_ptr);

#ifdef FEATURE_STORAGE_DIAG_COMPILE_WITHOUT_EFS
  (void) req_pkt;
  (void) result;
  (void) temp_iter_node;
  (void) iter_node;
  cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
#else /* FEATURE_STORAGE_DIAG_COMPILE_WITHOUT_EFS */

  fs_os_mutex_lock (&storage_diag_mutex);

  result = efs_iter ((const char *)req_pkt->efs_path, 0,
                     storage_diag_efs_iter_cb, efs_iter_cb_param_q_ptr);

  fs_os_mutex_unlock (&storage_diag_mutex);

  if (result != 0)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("cmd-q efs_2_rfs handler efs_iter failed: %d : %d",
                             (int)result, (int)efs_errno);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_FAILED;
    goto End;
  }

  iter_node = q_next (efs_iter_cb_param_q_ptr, &efs_iter_cb_param_q_ptr->link);
  while (iter_node != NULL)
  {
    STORAGE_DIAG_MSG_STRING_1 ("%s", iter_node->efs_path);
    ++rsp_pkt->num_files_copied;

    result = storage_diag_copy_efs_to_rfs (iter_node);

    temp_iter_node = iter_node;
    iter_node = q_next (efs_iter_cb_param_q_ptr, &iter_node->link);
    fs_os_free (temp_iter_node);
  }

  cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
#endif /* FEATURE_STORAGE_DIAG_COMPILE_WITHOUT_EFS */

End:
  if (efs_iter_cb_param_q_ptr != NULL)
  {
    fs_os_free (efs_iter_cb_param_q_ptr);
  }
  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q efs_2_rfs handler complete: %d", (int)0);
  return;
}

/*--------------------------------------------------------------------
 * cmd-q handler : rfs_write
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_rfs_write_req_type
{
  uint32 num_files;
  uint32 file_size;
  uint32 file_size_incr;
  uint32 write_size;
  uint32 write_size_incr;
  uint32 seed_val;
  uint32 verify_file_after_each_write;
  uint8  file_name[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rfs_write_rsp_type
{
  uint32 num_files_created;
} PACKED_POST;

static void
storage_diag_cmd_q_rfs_write_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp, file_size;
  struct storage_diag_cmd_q_rfs_write_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rfs_write_rsp_type *rsp_pkt = NULL;
  char *file_name = NULL;
  int i, result;

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_rfs_write_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_rfs_write_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  rsp_pkt->num_files_created = 0;
  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;

  file_name = fs_os_malloc (STORAGE_DIAG_MAX_PATH_LEN);
  if (file_name == NULL)
  {
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_NOMEM;
    goto End;
  }

  file_size = req_pkt->file_size;
  for ( i = 0; i < req_pkt->num_files; ++i )
  {
    snprintf (file_name, STORAGE_DIAG_MAX_PATH_LEN, "%s-%d",
              req_pkt->file_name, i);

    result = rfs_util_create_file (file_name, req_pkt->file_size,
                   req_pkt->write_size, req_pkt->write_size_incr,
                   req_pkt->seed_val++, req_pkt->verify_file_after_each_write);
    if (result != 0)
    {
      STORAGE_DIAG_MSG_STRING_1 ("file creation failed. : %s", file_name);
      STORAGE_DIAG_MSG_STRING_1 ("size of file : %d", req_pkt->file_size);
    }
    file_size += req_pkt->file_size_incr;
    ++rsp_pkt->num_files_created;
  }

  cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;

End:
  if (file_name != NULL)
  {
    fs_os_free (file_name);
  }

  return;
}


/*--------------------------------------------------------------------
 * cmd-q handler : rfs_put
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_rfs_put_req_type
{
  uint32 file_size;
  uint32 oflag;
  uint32 mode;
  uint32 buf_seed;
  uint32 verify_file;
  uint8  file_name[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rfs_put_rsp_type
{
  uint32 bytes_written;
  int32 error_num;
  uint8 verify_check_passed;
} PACKED_POST;


static void
storage_diag_cmd_q_cmd_id_rfs_put_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp;
  struct storage_diag_cmd_q_rfs_put_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rfs_put_rsp_type *rsp_pkt = NULL;
  int result;

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_rfs_put_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_rfs_put_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    STORAGE_DIAG_MSG_ERROR_3 ("RFS put received with bad len: %d, %d, %d",
                              cmd_node->cmd_q_req_len, temp, req_pkt_len);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  STORAGE_DIAG_MSG_HIGH_2 ("RFS put req received %s, %d", req_pkt->file_name,
                           req_pkt->file_size);

  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;

  result = rfs_util_put ((const char *)req_pkt->file_name, req_pkt->file_size,
                         req_pkt->buf_seed, req_pkt->oflag,
                         req_pkt->mode, req_pkt->verify_file,
                         &cmd_node->cmd_q_rsp.hdr.dbg_info);
  rsp_pkt->bytes_written = result;
  if (result == req_pkt->file_size)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("RFS put success");
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->error_num = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->verify_check_passed = 1;
  }
  else
  {
    STORAGE_DIAG_MSG_ERROR_1 ("RFS put failed with result %d", result);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_FAILED;
    rsp_pkt->error_num = storage_diag_map_rfs_errors (result);
    rsp_pkt->verify_check_passed = 0;
  }

End:
  return;
}

/*--------------------------------------------------------------------
 * cmd-q handler : rfs_get
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_rfs_get_req_type
{
  uint32 file_size;
  uint32 buf_seed;
  uint32 verify_file;
  uint8  file_name[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rfs_get_rsp_type
{
  uint32 bytes_read;
  int32 error_num;
  uint8 verify_check_passed; /* True or fasle */
} PACKED_POST;


/*-------------------------------------------------------------------
  EFS QMI Put/Get command handler
-------------------------------------------------------------------*/

enum storage_diag_fs_qmi_op {
  STORAGE_DIAG_FS_QMI_OP_PUT,
  STORAGE_DIAG_FS_QMI_OP_GET,
  STORAGE_DIAG_FS_QMI_OP_PUT_GET
};

PACKED struct storage_diag_cmd_q_fs_qmi_req_type
{
  uint8  op;
  uint32 file_size;
  int    oflag;
  int    mode;
  uint8  buf_seed;
  uint8  fake_op;
  uint8  file_name[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_fs_qmi_rsp_type
{
  uint32 bytes_accessed;
  int32  error_num;
  uint8  verify_check_passed;
} PACKED_POST;

static void
storage_diag_cmd_q_cmd_id_fs_qmi_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp;
  struct storage_diag_cmd_q_fs_qmi_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_fs_qmi_rsp_type *rsp_pkt = NULL;
  int result, i;
  uint8 *buffer = NULL, *verify_buffer = NULL;
  uint8 seed;

  STORAGE_DIAG_MSG_HIGH_0 ("fs_qmi_put_get req received");

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_fs_qmi_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_fs_qmi_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    STORAGE_DIAG_MSG_ERROR_2 ("fs_qmi_put_get req bad size %d %d",
                              cmd_node->cmd_q_req_len, temp);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    return;
  }

  STORAGE_DIAG_MSG_HIGH_0 ("Good fs_qmi_put_get req recd");

  if (req_pkt->fake_op == 1)
  {
    STORAGE_DIAG_MSG_ERROR_0 ("fs_qmi_put_get faking operation as successful");
    result = 0;
    goto End;
  }

  rsp_pkt->bytes_accessed = 0;
  rsp_pkt->error_num = 0;
  rsp_pkt->verify_check_passed = 0xFF;
  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;

#ifdef FEATURE_STORAGE_DIAG_COMPILE_EFS_LIB

  buffer = fs_os_malloc (req_pkt->file_size);
  if (buffer == NULL)
  {
    STORAGE_DIAG_MSG_ERROR_1 ("fs_qmi_put_get buffer malloc failed %d",
                              req_pkt->file_size);
    result = -1;
    rsp_pkt->error_num = ENOMEM;
    goto End;
  }

  seed = req_pkt->buf_seed;
  for (i = 0; i < req_pkt->file_size; i++)
  {
    buffer[i] = seed++;
  }

  STORAGE_DIAG_MSG_ERROR_1 ("fs_qmi_put_get buf filled with seed starting %d",
                            req_pkt->buf_seed);

  if (req_pkt->op == STORAGE_DIAG_FS_QMI_OP_GET ||
      req_pkt->op == STORAGE_DIAG_FS_QMI_OP_PUT_GET)
  {
    verify_buffer = fs_os_malloc (req_pkt->file_size);
    if (verify_buffer  == NULL)
    {
      STORAGE_DIAG_MSG_ERROR_1 ("fs_qmi_put_get verify buff malloc failed %d",
                                req_pkt->file_size);
      result = -1;
      rsp_pkt->error_num = ENOMEM;
      goto End;
    }
  }

  switch (req_pkt->op)
  {
    case STORAGE_DIAG_FS_QMI_OP_PUT:
      result = efs_put ((char *)req_pkt->file_name, buffer, req_pkt->file_size,
                        req_pkt->oflag, req_pkt->mode);
      if (result != 0)
      {
        STORAGE_DIAG_MSG_ERROR_2 ("fs_qmi_put_get put failed %d %d", result,
                                  efs_errno);
        rsp_pkt->error_num = efs_errno;
        goto End;
      }
      break;

    case STORAGE_DIAG_FS_QMI_OP_GET:
      result = efs_get ((char *)req_pkt->file_name, verify_buffer,
               req_pkt->file_size);
      if (result != req_pkt->file_size)
      {
        STORAGE_DIAG_MSG_ERROR_2 ("fs_qmi_put_get get failed %d %d", result,
                                  efs_errno);
        rsp_pkt->bytes_accessed = result;
        rsp_pkt->error_num = efs_errno;
        result = -1;
        goto End;
      }
      result = 0;
      break;

    case STORAGE_DIAG_FS_QMI_OP_PUT_GET:
      result = efs_put ((char *)req_pkt->file_name, buffer, req_pkt->file_size,
                        req_pkt->oflag, req_pkt->mode);
      if (result != 0)
      {
        STORAGE_DIAG_MSG_ERROR_2 ("fs_qmi_put_get put failed %d %d", result,
                                  efs_errno);
        rsp_pkt->error_num = efs_errno;
        goto End;
      }

      result = efs_get ((char *)req_pkt->file_name, verify_buffer,
                         req_pkt->file_size);
      if (result != req_pkt->file_size)
      {
        STORAGE_DIAG_MSG_ERROR_2 ("fs_qmi_put_get get failed %d %d", result,
                                  efs_errno);
        rsp_pkt->bytes_accessed = result;
        rsp_pkt->error_num = efs_errno;
        result = -1;
        goto End;
      }
      result = 0;
      break;

    default:
      STORAGE_DIAG_MSG_ERROR_1 ("fs_qmi_put_get unknown op %d", req_pkt->op);
      result = -1;
      efs_errno = EINVAL;
      goto End;
  }

  if (req_pkt->op == STORAGE_DIAG_FS_QMI_OP_GET ||
      req_pkt->op == STORAGE_DIAG_FS_QMI_OP_PUT_GET)
  {
    result = memcmp (buffer, verify_buffer, req_pkt->file_size);
    if (result != 0)
    {
      STORAGE_DIAG_MSG_ERROR_2 ("fs_qmi_put_get verify failed %d %d",
                                req_pkt->file_size, result);
      rsp_pkt->bytes_accessed = req_pkt->file_size;
      rsp_pkt->verify_check_passed = 0;
      rsp_pkt->error_num = result;
      result = -1;
      goto End;
    }
  }
#else
  (void) seed;
  (void) i;
  result = -1;
  rsp_pkt->error_num = ENODEV;
#endif

End:
  if (result == 0)
  {
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->bytes_accessed = req_pkt->file_size;
    rsp_pkt->error_num = 0;
    rsp_pkt->verify_check_passed = 1;
    STORAGE_DIAG_MSG_HIGH_1 ("fs_qmi_put_get success %d",
                              rsp_pkt->bytes_accessed );
  }
  else
  {
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_FAILED;
    STORAGE_DIAG_MSG_ERROR_3 ("fs_qmi_put_get failed %d %d %d",
                              rsp_pkt->bytes_accessed, efs_errno,
                              rsp_pkt->verify_check_passed);
  }

  if (buffer != NULL)
  {
    fs_os_free (buffer);
  }
  if (verify_buffer != NULL)
  {
    fs_os_free (verify_buffer);
  }

  return;
}


static void
storage_diag_cmd_q_cmd_id_rfs_get_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp, file_size;
  struct storage_diag_cmd_q_rfs_get_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rfs_get_rsp_type *rsp_pkt = NULL;
  int result;

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_rfs_get_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_rfs_get_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    STORAGE_DIAG_MSG_ERROR_3 ("RFS get received with bad len: %d, %d, %d",
                              cmd_node->cmd_q_req_len, temp, req_pkt_len);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  STORAGE_DIAG_MSG_HIGH_2 ("RFS get req received %s, %d", req_pkt->file_name,
                           req_pkt->file_size);

  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;

  file_size = req_pkt->file_size;
  result = rfs_util_get ((const char *)req_pkt->file_name, file_size,
                         req_pkt->buf_seed, req_pkt->verify_file,
                         &cmd_node->cmd_q_rsp.hdr.dbg_info);
  rsp_pkt->bytes_read = result;
  if (result == file_size)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("RFS get success");
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->error_num = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->verify_check_passed = 1;
  }
  else
  {
    STORAGE_DIAG_MSG_ERROR_1 ("RFS get failed with result %d", result);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_FAILED;
    rsp_pkt->error_num = storage_diag_map_rfs_errors (result);
    rsp_pkt->verify_check_passed = 0;
  }

End:
  return;
}


/*--------------------------------------------------------------------
 * cmd-q handler : rfs_write_perf
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_rfs_write_perf_req_type
{
  uint32 offset;
  uint32 write_size;
  uint32 oflag;
  uint32 mode;
  uint32 buf_seed;
  uint8  file_name[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rfs_write_perf_rsp_type
{
  uint32 bytes_written;
  int32 error_num;
} PACKED_POST;


static void
storage_diag_cmd_q_cmd_id_rfs_write_perf_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp;
  struct storage_diag_cmd_q_rfs_write_perf_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rfs_write_perf_rsp_type *rsp_pkt = NULL;
  int result;

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_rfs_write_perf_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_rfs_write_perf_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    STORAGE_DIAG_MSG_ERROR_3("RFS write perf received with bad len: %d,%d,%d",
                              cmd_node->cmd_q_req_len, temp, req_pkt_len);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  STORAGE_DIAG_MSG_HIGH_3 ("RFS write perf req received %s, %d, %d",
              req_pkt->file_name, req_pkt->offset, req_pkt->write_size);

  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;
  result = rfs_util_write((const char *)req_pkt->file_name, req_pkt->offset,
                        req_pkt->write_size, req_pkt->buf_seed, req_pkt->oflag,
                        req_pkt->mode, &cmd_node->cmd_q_rsp.hdr.dbg_info);
  rsp_pkt->bytes_written = result;
  if (result == req_pkt->write_size)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("RFS write perf success");
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->error_num = STORAGE_DIAG_RESULT_SUCCESS;
  }
  else
  {
    STORAGE_DIAG_MSG_ERROR_1 ("RFS write perf failed with result %d", result);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_FAILED;
    rsp_pkt->error_num = storage_diag_map_rfs_errors (result);
  }

End:
  return;
}

/*--------------------------------------------------------------------
 * cmd-q handler : rfs_write_perf
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_rfs_read_perf_req_type
{
  uint32 offset;
  uint32 read_size;
  uint8  file_name[STORAGE_DIAG_MAX_PATH_LEN];
} PACKED_POST;

PACKED struct storage_diag_cmd_q_rfs_read_perf_rsp_type
{
  uint32 bytes_read;
  int32 error_num;
} PACKED_POST;


static void
storage_diag_cmd_q_cmd_id_rfs_read_perf_handler (
        struct storage_diag_cmd_q_node_type *cmd_node)
{
  uint32 hdr_len, req_pkt_len, rsp_pkt_len, temp;
  struct storage_diag_cmd_q_rfs_read_perf_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rfs_read_perf_rsp_type *rsp_pkt = NULL;
  int result;

  hdr_len = sizeof (struct storage_diag_cmd_q_add_req_hdr_type);
  req_pkt_len = sizeof (*req_pkt);
  rsp_pkt_len = sizeof (*rsp_pkt);

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_req_len >= hdr_len);
  STORAGE_DIAG_ASSERT (cmd_node->cmd_q_rsp_len ==
                       sizeof (struct storage_diag_cmd_q_rsp_type));

  req_pkt = (struct storage_diag_cmd_q_rfs_read_perf_req_type *)
              &cmd_node->cmd_q_req.sub_cmd_req_pkt[0];
  rsp_pkt = (struct storage_diag_cmd_q_rfs_read_perf_rsp_type *)
              &cmd_node->cmd_q_rsp.sub_cmd_rsp_pkt[0];

  temp = hdr_len + req_pkt_len;
  if (cmd_node->cmd_q_req_len > temp)
  {
    STORAGE_DIAG_MSG_ERROR_3("RFS read perf received with bad len: %d,%d,%d",
                              cmd_node->cmd_q_req_len, temp, req_pkt_len);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_BAD_PKT_LEN;
    goto End;
  }

  STORAGE_DIAG_MSG_HIGH_3 ("RFS read perf req received %s, %d, %d",
                req_pkt->file_name, req_pkt->offset, req_pkt->read_size);

  cmd_node->cmd_q_rsp.hdr.sub_cmd_rsp_pkt_len = rsp_pkt_len;

  result = rfs_util_read((const char *)req_pkt->file_name, req_pkt->offset,
                        req_pkt->read_size, &cmd_node->cmd_q_rsp.hdr.dbg_info);
  rsp_pkt->bytes_read = result;
  if (result == req_pkt->read_size)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("RFS read perf success");
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
    rsp_pkt->error_num = STORAGE_DIAG_RESULT_SUCCESS;
  }
  else
  {
    STORAGE_DIAG_MSG_ERROR_1 ("RFS read perf failed with result %d", result);
    cmd_node->cmd_q_rsp.hdr.result = STORAGE_DIAG_RESULT_FAILED;
    rsp_pkt->error_num = storage_diag_map_rfs_errors (result);
  }

End:
  return;
}

/*--------------------------------------------------------------------
 * storage-diag : Main commands.
 *-------------------------------------------------------------------*/
enum storage_diag_cmd_id_type
{
  STORAGE_DIAG_CMD_HELLO              = STORAGE_DIAG_CMD_OFFSET + 0,
  STORAGE_DIAG_CMD_CMD_Q_ADD          = STORAGE_DIAG_CMD_OFFSET + 1,
  STORAGE_DIAG_CMD_CMD_Q_GET_RESULTS  = STORAGE_DIAG_CMD_OFFSET + 2,
  STORAGE_DIAG_CMD_CMD_Q_RUN          = STORAGE_DIAG_CMD_OFFSET + 3,
  STORAGE_DIAG_CMD_CHANGE_TFTP_CONFIG = STORAGE_DIAG_CMD_OFFSET + 4,
};

DECLARE_DIAG_FN (storage_diag_hello_handler);
DECLARE_DIAG_FN (storage_diag_cmd_q_add_handler);
DECLARE_DIAG_FN (storage_diag_cmd_q_get_results_handler);
DECLARE_DIAG_FN (storage_diag_cmd_q_run_handler);
DECLARE_DIAG_FN (storage_diag_change_tftp_cfg_handler);


struct storage_diag_hello_req_type;
struct storage_diag_hello_rsp_type;

static const diagpkt_user_table_entry_type storage_diag_tbl[] =
{
  {
    STORAGE_DIAG_CMD_HELLO,
    STORAGE_DIAG_CMD_HELLO,
    storage_diag_hello_handler
  },
  {
    STORAGE_DIAG_CMD_CMD_Q_ADD,
    STORAGE_DIAG_CMD_CMD_Q_ADD,
    storage_diag_cmd_q_add_handler
  },
  {
    STORAGE_DIAG_CMD_CMD_Q_GET_RESULTS,
    STORAGE_DIAG_CMD_CMD_Q_GET_RESULTS,
    storage_diag_cmd_q_get_results_handler
  },
  {
    STORAGE_DIAG_CMD_CMD_Q_RUN,
    STORAGE_DIAG_CMD_CMD_Q_RUN,
    storage_diag_cmd_q_run_handler
  },
  {
    STORAGE_DIAG_CMD_CHANGE_TFTP_CONFIG,
    STORAGE_DIAG_CMD_CHANGE_TFTP_CONFIG,
    storage_diag_change_tftp_cfg_handler
  },
};

/*--------------------------------------------------------------------
  Hello command handler
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_hello_req_type
{
  diagpkt_subsys_header_type hdr;
  uint32 print_this_number;
} PACKED_POST;

PACKED struct storage_diag_hello_rsp_type
{
  diagpkt_subsys_header_type hdr;
  uint32 result;
  uint32 print_this_number;
} PACKED_POST;

VOID_PACKED_PTR
storage_diag_hello_handler (VOID_PACKED_PTR req_ptr, uint16 pkt_len)
{
  struct storage_diag_hello_req_type *req_pkt;
  struct storage_diag_hello_rsp_type *rsp_pkt;
  uint32 hello_req_pkt_size;
  uint32 hello_rsp_pkt_size;
  static char efs_team_build_id[200];

  hello_req_pkt_size = sizeof (struct storage_diag_hello_req_type);
  if (pkt_len != hello_req_pkt_size)
  {
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, pkt_len);
  }

  req_pkt = (struct storage_diag_hello_req_type *)req_ptr;

  snprintf (efs_team_build_id, sizeof (efs_team_build_id), "%s at %s",
            __DATE__, __TIME__);

  STORAGE_DIAG_MSG_STRING_1 ("Build compiled on %s", efs_team_build_id);

  STORAGE_DIAG_MSG_HIGH_1 ("Hello req recd with : %d",
                           (int)req_pkt->print_this_number);

  hello_rsp_pkt_size = sizeof (struct storage_diag_hello_rsp_type);
  rsp_pkt = (struct storage_diag_hello_rsp_type *)
             diagpkt_subsys_alloc (DIAG_SUBSYS_STORAGE,
                                   STORAGE_DIAG_CMD_HELLO,
                                   hello_rsp_pkt_size);
  STORAGE_DIAG_ASSERT (rsp_pkt != NULL);

  rsp_pkt->print_this_number = req_pkt->print_this_number + 1;
  rsp_pkt->result = STORAGE_DIAG_RESULT_SUCCESS;

  return rsp_pkt;
}


/*--------------------------------------------------------------------
  TFTP change config command handler
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_ch_tftp_cfg_req_type
{
  diagpkt_subsys_header_type hdr;
  struct rfs_config_info_type config;
} PACKED_POST;

PACKED struct storage_diag_ch_tftp_cfg_rsp_type
{
  diagpkt_subsys_header_type hdr;
  uint32 result;
} PACKED_POST;

VOID_PACKED_PTR
storage_diag_change_tftp_cfg_handler (VOID_PACKED_PTR req_ptr, uint16 pkt_len)
{
  struct storage_diag_ch_tftp_cfg_req_type *req_pkt;
  struct storage_diag_ch_tftp_cfg_rsp_type *rsp_pkt;
  uint32 req_pkt_size;
  uint32 rsp_pkt_size;
  int result;

  req_pkt_size = sizeof (struct storage_diag_ch_tftp_cfg_req_type);
  if (pkt_len != req_pkt_size)
  {
    STORAGE_DIAG_MSG_ERROR_2 ("TFTP Change cfg req recd with bad size %d %d",
                              pkt_len, req_pkt_size);
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, pkt_len);
  }

  req_pkt = (struct storage_diag_ch_tftp_cfg_req_type *)req_ptr;

  STORAGE_DIAG_MSG_HIGH_0 ("TFTP Change cfg req recd");

  rsp_pkt_size = sizeof (struct storage_diag_ch_tftp_cfg_rsp_type);
  rsp_pkt = (struct storage_diag_ch_tftp_cfg_rsp_type *)
            diagpkt_subsys_alloc (DIAG_SUBSYS_STORAGE,
                                  STORAGE_DIAG_CMD_CHANGE_TFTP_CONFIG,
                                  rsp_pkt_size);
  STORAGE_DIAG_ASSERT (rsp_pkt != NULL);

  result = rfs_set_config (&(req_pkt->config));
  if (result != 0)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("Failed to change tftp cfg %d", result);
    rsp_pkt->result = STORAGE_DIAG_RESULT_FAILED;
    goto End;
  }

  STORAGE_DIAG_MSG_HIGH_0 ("Changed tftp cfg");
  rsp_pkt->result = STORAGE_DIAG_RESULT_SUCCESS;

End:
  return rsp_pkt;
}

int
storage_diag_thread_create (struct storage_diag_cmd_q_node_type *cmd_node,
                            fs_os_thread_return_type (*thread_proc) (void *))
{
  int result;
  fs_os_thread_attr_t thread_attr;

  STORAGE_DIAG_ASSERT (cmd_node != NULL);
  STORAGE_DIAG_ASSERT (thread_proc != NULL);

  STORAGE_DIAG_MSG_HIGH_0 ("storage_diag thread_create");

  fs_os_thread_attr_init (&thread_attr);

  thread_attr.thread_name = cmd_node->thread_name;
  thread_attr.stack_size = FS_OS_THREAD_DEFAULT_STACK_SIZE;
  result = fs_os_thread_create (&cmd_node->thread_handle, &thread_attr,
                                thread_proc, cmd_node);
  if (result != 0)
  {
    STORAGE_DIAG_MSG_ERROR_2 ("thread_create failed error: %d %s", result,
                              strerror (result));
  }

  return result;
}


/*--------------------------------------------------------------------
 * cmd-q : add-cmd handler
 *-------------------------------------------------------------------*/
VOID_PACKED_PTR
storage_diag_cmd_q_add_handler (VOID_PACKED_PTR req_ptr, uint16 req_ptr_len)
{
  struct storage_diag_cmd_q_add_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rsp_type *rsp_pkt = NULL;
  struct storage_diag_cmd_q_rsp_type *cmd_q_rsp;
  struct storage_diag_cmd_q_node_type *cmd_node = NULL;
  uint32 req_pkt_size, rsp_pkt_size, cmd_node_size;
  int result, *temp_data;

  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-add handler : %d",
                           (int)req_ptr_len);

  req_pkt_size = sizeof (struct storage_diag_cmd_q_add_req_type);
  if (req_ptr_len > req_pkt_size)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("cmd-q-add handler : %d > %d",
                               (int)req_ptr_len, (int)req_pkt_size);
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  req_pkt = (struct storage_diag_cmd_q_add_req_type *)req_ptr;
  if (req_pkt == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("cmd-q-add handler : req_ptr is NULL");
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  rsp_pkt_size = sizeof (struct storage_diag_cmd_q_rsp_type);
  rsp_pkt = (struct storage_diag_cmd_q_rsp_type *)
             diagpkt_subsys_alloc (DIAG_SUBSYS_STORAGE,
                                   STORAGE_DIAG_CMD_CMD_Q_ADD,
                                   rsp_pkt_size);
  if (rsp_pkt == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("cmd-q-add handler : rsp_ptr is NULL");
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  storage_diag_memset_diag_pkt ((uint8 *)rsp_pkt, rsp_pkt_size);

  fs_os_mutex_lock (&storage_diag_mutex);

  cmd_node_size = sizeof (struct storage_diag_cmd_q_node_type);
  cmd_node = (struct storage_diag_cmd_q_node_type *)
                               fs_os_malloc (cmd_node_size);
  if (cmd_node == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_0 ("cmd-q-add handler : cmd_ptr is NULL");
    rsp_pkt->hdr.result = STORAGE_DIAG_RESULT_NOMEM;
    goto End;
  }

  ++storage_diag_info.cmd_q_id;
  if (storage_diag_info.cmd_q_id == 0)
    storage_diag_info.cmd_q_id = 1;

  memset (cmd_node, 0, cmd_node_size);

  cmd_node->cmd_q_id = storage_diag_info.cmd_q_id;
  cmd_node->state = STORAGE_DIAG_CMD_STATE_NOT_STARTED;
  cmd_node->cmd_q_req_len = req_ptr_len;
  memscpy (&cmd_node->cmd_q_req, sizeof (cmd_node->cmd_q_req),
           (void *)req_ptr, req_ptr_len);
  cmd_node->cmd_q_rsp_len = rsp_pkt_size;
  snprintf (cmd_node->thread_name, sizeof (cmd_node->thread_name),
            "sdiag-%d", (int)storage_diag_info.cmd_q_id);

  rsp_pkt->hdr.result = STORAGE_DIAG_RESULT_FAILED;
  rsp_pkt->hdr.state = STORAGE_DIAG_CMD_STATE_NOT_STARTED;
  rsp_pkt->hdr.cmd_q_handle = storage_diag_info.cmd_q_id;
  rsp_pkt->hdr.sub_cmd_id = req_pkt->hdr.sub_cmd_id;
  rsp_pkt->hdr.sub_cmd_rsp_pkt_len = 0;

  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-add handler : cmd-id is %d",
                           (int)cmd_node->cmd_q_id);

  STORAGE_DIAG_MSG_HIGH_3 ("cmd-q-add handler : req_pkt : %d : %d : %d",
                           (int)req_pkt->hdr.run_in_thread,
                           (int)req_pkt->hdr.run_later,
                           (int)req_pkt->hdr.reserved);

  temp_data = (int *)&req_pkt->sub_cmd_req_pkt[0];

  STORAGE_DIAG_MSG_HIGH_3 ("cmd-q-add handler : req_pkt 2 : %d : %d : %d",
                           (int)req_pkt->hdr.sub_cmd_id,
                           (int)req_pkt->hdr.sub_cmd_req_pkt_len,
                           (int)*temp_data);

  if (req_pkt->hdr.run_in_thread)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-add handler : pthread 1 cmd-id is %d",
                             (int)cmd_node->cmd_q_id);

    q_link (cmd_node, &cmd_node->link);
    q_put (&storage_diag_info.cmd_q, &cmd_node->link);

    if (!req_pkt->hdr.run_later)
    {
      STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-add handler : pthread 2 cmd-id is %d",
                               (int)cmd_node->cmd_q_id);

      result = storage_diag_thread_create (cmd_node,
                                  storage_diag_cmd_q_add_handler_thread_proc);
      if (result != 0)
      {
        STORAGE_DIAG_MSG_HIGH_2 ("cmd-q-add hldr: thread created failed for \
          cmd-id %d, result %d", (int)cmd_node->cmd_q_id, result);
        rsp_pkt->hdr.result = STORAGE_DIAG_RESULT_CREATE_THREAD_FAIL;
        goto Cleanup;
      }
    }
    rsp_pkt->hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
    goto End;
  }
  else
  {
    storage_diag_cmd_q_execute_node (cmd_node);
    cmd_q_rsp = &cmd_node->cmd_q_rsp;
    rsp_pkt->hdr.result = cmd_q_rsp->hdr.result;
    rsp_pkt->hdr.state = STORAGE_DIAG_CMD_STATE_COMPLETE;
    memscpy (&rsp_pkt->hdr.dbg_info, sizeof (rsp_pkt->hdr.dbg_info),
             &cmd_q_rsp->hdr.dbg_info, sizeof (rsp_pkt->hdr.dbg_info));
    rsp_pkt->hdr.sub_cmd_rsp_pkt_len = cmd_q_rsp->hdr.sub_cmd_rsp_pkt_len;
    memscpy (rsp_pkt->sub_cmd_rsp_pkt, sizeof (rsp_pkt->sub_cmd_rsp_pkt),
             cmd_q_rsp->sub_cmd_rsp_pkt,
            cmd_q_rsp->hdr.sub_cmd_rsp_pkt_len);
  }

Cleanup:
  if (cmd_node != NULL)
  {
    fs_os_free (cmd_node);
  }

End:
  fs_os_mutex_unlock (&storage_diag_mutex);
  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-add handler : done. cmd-id is %d",
                           (int)cmd_node->cmd_q_id);
  return rsp_pkt;
}

/*--------------------------------------------------------------------
 * cmd-q : get-results handler
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_get_results_req_type
{
  diagpkt_subsys_header_type hdr;
  uint32 cmd_q_handle;
} PACKED_POST;

VOID_PACKED_PTR
storage_diag_cmd_q_get_results_handler (VOID_PACKED_PTR req_ptr,
                                        uint16 req_ptr_len)
{
  struct storage_diag_cmd_q_get_results_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_rsp_type *rsp_pkt = NULL;
  struct storage_diag_cmd_q_rsp_type *cmd_q_rsp = NULL;
  struct storage_diag_cmd_q_node_type *cmd_node = NULL;
  uint32 req_pkt_size, rsp_pkt_size;
  void *compare_val;

  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-get handler : req-len %d",
                           (int)req_ptr_len);

  req_pkt_size = sizeof (struct storage_diag_cmd_q_get_results_req_type);
  if (req_ptr_len != req_pkt_size)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("cmd-q-get handler : req-len ! req_pkt %d ! %d",
                             (int)req_ptr_len, (int)req_pkt_size);
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  req_pkt = (struct storage_diag_cmd_q_get_results_req_type *)req_ptr;
  if (req_pkt == NULL)
  {
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-get handler : hdl : %d",
                           (int)req_pkt->cmd_q_handle);

  rsp_pkt_size = sizeof (struct storage_diag_cmd_q_rsp_type);
  rsp_pkt = (struct storage_diag_cmd_q_rsp_type *)
             diagpkt_subsys_alloc (DIAG_SUBSYS_STORAGE,
                                   STORAGE_DIAG_CMD_CMD_Q_GET_RESULTS,
                                   rsp_pkt_size);
  if (rsp_pkt == NULL)
  {
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  storage_diag_memset_diag_pkt ((uint8 *)rsp_pkt, rsp_pkt_size);

  fs_os_mutex_lock (&storage_diag_mutex);

  compare_val = (void *)&req_pkt->cmd_q_handle;

  cmd_node = (struct storage_diag_cmd_q_node_type *)
               q_linear_search (&storage_diag_info.cmd_q,
                                storage_diag_cmd_q_compare_func,
                                compare_val);
  if (cmd_node == NULL)
  {
    STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-get handler : invalid hdl : %d",
                             (int)req_pkt->cmd_q_handle);
    rsp_pkt->hdr.result = STORAGE_DIAG_RESULT_INVALID_HANDLE;
    goto End;
  }

  STORAGE_DIAG_MSG_HIGH_2 ("cmd-q-get handler : found hdl : %d : %d",
                           (int)req_pkt->cmd_q_handle, (int)cmd_node->state);

  rsp_pkt->hdr.result = STORAGE_DIAG_RESULT_SUCCESS;
  rsp_pkt->hdr.cmd_q_handle = cmd_node->cmd_q_id;
  rsp_pkt->hdr.sub_cmd_id = cmd_node->cmd_q_req.hdr.sub_cmd_id;

  switch (cmd_node->state)
  {
    case STORAGE_DIAG_CMD_STATE_NOT_STARTED:
    {
      rsp_pkt->hdr.state = STORAGE_DIAG_CMD_STATE_NOT_STARTED;
      STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-get handler : not-started. hdl : %d",
                               (int)req_pkt->cmd_q_handle);
    }
    break;

    case STORAGE_DIAG_CMD_STATE_RUNNING:
    {
      STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-get handler : running. hdl : %d",
                               (int)req_pkt->cmd_q_handle);
      rsp_pkt->hdr.state = STORAGE_DIAG_CMD_STATE_NOT_STARTED;
    }
    break;

    case STORAGE_DIAG_CMD_STATE_COMPLETE:
    {
      int *temp;
      cmd_q_rsp = &cmd_node->cmd_q_rsp;
      rsp_pkt->hdr.result = cmd_q_rsp->hdr.result;
      rsp_pkt->hdr.state = STORAGE_DIAG_CMD_STATE_COMPLETE;
      memscpy (&rsp_pkt->hdr.dbg_info, sizeof (rsp_pkt->hdr.dbg_info),
               &cmd_q_rsp->hdr.dbg_info, sizeof (rsp_pkt->hdr.dbg_info));
      rsp_pkt->hdr.sub_cmd_rsp_pkt_len = cmd_q_rsp->hdr.sub_cmd_rsp_pkt_len;
      memscpy (rsp_pkt->sub_cmd_rsp_pkt, sizeof (rsp_pkt->sub_cmd_rsp_pkt),
               cmd_q_rsp->sub_cmd_rsp_pkt, cmd_q_rsp->hdr.sub_cmd_rsp_pkt_len);
      (void) fs_os_thread_join (cmd_node->thread_handle, NULL);

      q_delete (&storage_diag_info.cmd_q, &cmd_node->link);
      fs_os_free (cmd_node);
      temp = (int *)&rsp_pkt->sub_cmd_rsp_pkt[0];
      STORAGE_DIAG_MSG_HIGH_3 ("cmd-q-get handler : complete : %d : %d : %d",
                               (int)req_pkt->cmd_q_handle,
                               (int)cmd_q_rsp->hdr.sub_cmd_rsp_pkt_len,
                               (int)*temp);
    }
    break;

    default:
    {
      STORAGE_DIAG_ASSERT (0);
    }
    break;
  }

End:
  fs_os_mutex_unlock (&storage_diag_mutex);
  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-get handler : done hdl : %d",
                           (int)req_pkt->cmd_q_handle);
  return rsp_pkt;
}

/*--------------------------------------------------------------------
 * cmd-q : run-q handler
 *-------------------------------------------------------------------*/
PACKED struct storage_diag_cmd_q_run_req_type
{
  diagpkt_subsys_header_type hdr;
  uint32 result;
} PACKED_POST;

PACKED struct storage_diag_cmd_q_run_rsp_type
{
  diagpkt_subsys_header_type hdr;
  uint32 result;
  uint32 total_req_in_q;
  uint32 run_req_count;
  uint32 run_req_fail_count;
} PACKED_POST;

VOID_PACKED_PTR
storage_diag_cmd_q_run_handler (VOID_PACKED_PTR req_ptr, uint16 req_ptr_len)
{
  struct storage_diag_cmd_q_run_req_type *req_pkt = NULL;
  struct storage_diag_cmd_q_run_rsp_type *rsp_pkt = NULL;
  struct storage_diag_cmd_q_node_type *cmd_node = NULL;
  uint32 req_pkt_size, rsp_pkt_size;
  int result;

  STORAGE_DIAG_MSG_HIGH_1 ("cmd-q-run handler : req_ptr_len : %d",
                           (int)req_ptr_len);

  req_pkt_size = sizeof (struct storage_diag_cmd_q_run_req_type);
  if (req_ptr_len != req_pkt_size)
  {
    STORAGE_DIAG_MSG_HIGH_2 ("cmd-q-run handler : req_ptr_len : %d ! %d",
                             (int)req_ptr_len, (int)req_pkt_size);
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  req_pkt = (struct storage_diag_cmd_q_run_req_type *)req_ptr;
  if (req_pkt == NULL)
  {
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  rsp_pkt_size = sizeof (*rsp_pkt);
  rsp_pkt = (struct storage_diag_cmd_q_run_rsp_type *)
             diagpkt_subsys_alloc (DIAG_SUBSYS_STORAGE,
                                   STORAGE_DIAG_CMD_CMD_Q_RUN, rsp_pkt_size);
  if (rsp_pkt == NULL)
  {
    return diagpkt_err_rsp (DIAG_BAD_LEN_F, req_ptr, req_ptr_len);
  }

  storage_diag_memset_diag_pkt ((uint8 *)rsp_pkt, rsp_pkt_size);

  fs_os_mutex_lock (&storage_diag_mutex);

  cmd_node = q_next (&storage_diag_info.cmd_q, &storage_diag_info.cmd_q.link);
  while (cmd_node != NULL)
  {
    ++rsp_pkt->total_req_in_q;
    if (cmd_node->state == STORAGE_DIAG_CMD_STATE_NOT_STARTED)
    {
      ++rsp_pkt->run_req_count;
      result = storage_diag_thread_create (cmd_node,
                            storage_diag_cmd_q_add_handler_thread_proc);
      if (result != 0)
      {
        ++rsp_pkt->run_req_fail_count;
      }
    }

    cmd_node = q_next (&storage_diag_info.cmd_q, &cmd_node->link);
  }

  STORAGE_DIAG_MSG_HIGH_3 ("cmd-q-run handler : status : %d : %d : %d",
                           (int)rsp_pkt->total_req_in_q,
                           (int)rsp_pkt->run_req_count,
                           (int)rsp_pkt->run_req_fail_count);

  fs_os_mutex_unlock (&storage_diag_mutex);

  rsp_pkt->result = STORAGE_DIAG_RESULT_SUCCESS;

  return rsp_pkt;
}

void
storage_diag_init (void)
{
  fs_os_mutex_init (&storage_diag_mutex);
  fs_os_mutex_lock (&storage_diag_mutex);

  memset (&storage_diag_info, 0, sizeof (storage_diag_info));

  q_init (&storage_diag_info.cmd_q);

  DIAGPKT_DISPATCH_TABLE_REGISTER (DIAG_SUBSYS_STORAGE, storage_diag_tbl);

  fs_os_mutex_unlock (&storage_diag_mutex);
}
