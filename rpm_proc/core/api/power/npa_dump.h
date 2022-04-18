#ifndef NPA_DUMP_H
#define NPA_DUMP_H

#include "DALSys.h"

/*******************************************************************************
 *
 * npa_dump
 *
 * Dump the whole resource graph to the specified location.
 *
 * buffer   : the pointer to the memory space where the NPA dump is written
 * buf_size : the size of the memory space (must be a multiple of 4)
 */
void npa_dump(char* buffer, uint32 buf_size);

#endif /* NPA_DUMP_H */
