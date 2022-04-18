#ifndef FASTRPC_LOADER_H
#define FASTRPC_LOADER_H

struct smq_phy_page; 
/**
 * spawn a new process
 * prorcess_init, this gets called when a asid and client ahndle are known, but before we actually spawn
 */
int fastrpc_spawn(int pidA, const char* appsname, const char* elffile, int elfsize, const struct smq_phy_page* pages, int numPages, int attrs);
//! return 0 if the sid is in one of the loaded pages
int fastrpc_loader_check_load_sid(int asid, int sid);
int fastrpc_kill(int pidA);
int fastrpc_get_process_attrs(unsigned int);

#endif // FASTRPC_LOADER_H
