#ifndef FAST_PLAYBACK_REGISTRY_H_
#define FAST_PLAYBACK_REGISTRY_H_

#include "sns_common.h"
#include "sns_reg_api_v02.h"

# define SNS_REG_MODULE              SNS_MODULE_DSPS_SCM
# define SNS_REG_MODULE_PRIORITY     SNS_MODULE_PRI_DSPS_SSM
# define SNS_REG_MODULE_STK_SIZE     SNS_MODULE_STK_SIZE_DSPS_SCM
# define SNS_REG_PROCESSOR_TYPE      SNS_PROC_SSC_V01
//# define SNS_SAM_SMR_SVC_PRI         SNS_SMR_SVC_PRI_MED
/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
 * fpb_registry_storage_init
 *
 * @brief Initializes the registry file settings
 */
sns_err_code_e fpb_registry_storage_init( const char* sns_reg_filename );

/**
 * fpb_registry_register_service
 *
 * @brief Registers the registry with the SMR
 */
sns_err_code_e fpb_registry_register_service(void);
void
sns_reg_task( void *argPtr );
#endif /* FAST_PLAYBACK_REGISTRY_H_ */
