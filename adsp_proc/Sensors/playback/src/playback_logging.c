#include <stdio.h>
#include "log.h"
#include "sns_log_api_public.h"
#include "sns_em.h"

/*============================================================================
  Global Data
  ===========================================================================*/
/* Flag to enable/disable all log packets */
STATIC bool enable_log_packets = true;

/* Output Log File (DLF format) */
FILE * log_result = NULL;

/**
 * Overridden function for logging
 * see log.h
 */
void log_set_length (void * ptr, unsigned int length)
{
  log_hdr_type *hdr_ptr = (log_hdr_type *) ptr;
  hdr_ptr->len = length;
}

/**
 * Overridden function for logging
 * see log.h
 */
void log_set_code (void * ptr, log_code_type code)
{
  log_hdr_type *hdr_ptr = (log_hdr_type *) ptr;
  hdr_ptr->code = (uint16_t) code;
}

/**
 * Overridden function for logging
 * see log.h
 */
void log_set_timestamp (void * ptr)
{
  log_hdr_type *hdr_ptr = (log_hdr_type *) ptr;
  hdr_ptr->ts[0] = 0;
  hdr_ptr->ts[1] = sns_em_get_timestamp();
}

/**
 * Overridden function for logging
 * see log.h
 */
boolean log_submit (void * ptr)
{
  log_hdr_type *hdr_ptr = (log_hdr_type *) ptr;

  fwrite(ptr, 1, hdr_ptr->len, log_result);

  return true;
}

/**
 * Overridden function for logging
 * see sns_log_api_public.h
 */
sns_err_code_e sns_logpkt_submit(uint32_t log_pkt_id,
                                 uint32_t log_pkt_size,
                                 PACK(void*) log_pkt)
{
  if (!enable_log_packets)
  {
    return SNS_ERR_NOTALLOWED;
  }

  if (NULL == log_pkt)
  {
    printf("ERROR! log_pkt is NULL!\n");
    return SNS_ERR_FAILED;
  }

  if (NULL == log_result)
  {
    printf("ERROR! log_result FILE* is NULL!\n");
    return SNS_ERR_FAILED;
  }

  log_set_length(log_pkt, log_pkt_size);
  log_set_code(log_pkt, log_pkt_id);
  log_submit(log_pkt);
  return SNS_SUCCESS;
}
