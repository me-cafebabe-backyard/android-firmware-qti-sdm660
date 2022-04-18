#ifndef _QURT_QDI_PROXY
#define _QURT_QDI_PROXY

int qurt_qdi_proxy_ref_create(void);

int qurt_qdi_proxy_ref_add(int proxy_handle, int qdi_handle);

int qurt_qdi_proxy_ref_sub(int proxy_handle, int qdi_handle);

#endif /* QURT_QDI_PROXY_H */
