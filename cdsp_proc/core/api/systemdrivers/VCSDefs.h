#ifndef VCSDEFS_H
#define VCSDEFS_H
/*
===========================================================================
*/
/**
  @file VCSDefs.h
  @brief Public definitions include file for accessing the VCS device driver.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      The VCS_Driver_API_mainpage.dox file contains all file/group
      descriptions that are in the output PDF generated using Doxygen and
      LaTeX. To edit or update any of the file/group text in the PDF, edit the
      VCS_Driver_mainpage.dox file or contact Tech Pubs.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/api/systemdrivers/VCSDefs.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  10/11/16   shm     First version for core.qdsp6.1.0

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "com_dtypes.h" /* for "uint32" */
#include "npa_resource.h"


/*=========================================================================
      Type Definitions
==========================================================================*/


/** @addtogroup vcs_functions
@{ */


/**
  Rail Identifiers
  This list should be common across all images.
 */
typedef enum
{
  VCS_RAIL_APCS,
  VCS_RAIL_CX,
  VCS_RAIL_MSS,
  VCS_RAIL_MX,
  VCS_RAIL_SSC_CX,
  VCS_RAIL_LPI_CX,
  VCS_RAIL_LPI_MX,

  VCS_RAIL_NUM_OF_RAILS
} VCSRailType;


/**
  Corner enums.

 * NOTE:
 * Whenever a new corner gets added, modified, or removed from this enum set a
 * corrosponding change must be made to the corner description array in
 * VCSDriver.c
 *
 * Failure to update both in tandem will result in a runtime fatal error.
 */
typedef enum
{
  VCS_CORNER_OFF            = 0,
  VCS_CORNER_RETENTION      = 1,
  VCS_CORNER_RETENTION_PLUS = 2,
  VCS_CORNER_LOW_MIN        = 3,
  VCS_CORNER_LOW_MINUS      = 4,
  VCS_CORNER_LOW            = 5,
  VCS_CORNER_LOW_PLUS       = 6,
  VCS_CORNER_NOMINAL        = 7,
  VCS_CORNER_NOMINAL_PLUS   = 8,
  VCS_CORNER_TURBO          = 9,
  VCS_CORNER_MAX            = VCS_CORNER_TURBO,

  VCS_CORNER_NUM_OF_CORNERS
} VCSCornerType;


/**
  Rail modes.

  pModeData argument when setting each mode:
    DEFAULT - This needs to be the current corner that the rail is configured to
              before switching back to default mode.  The client would perform a
              simple cast (e.g. (void *)VCS_CORNER_X).
    MVC     - No argument is processed for this mode.
 */
typedef enum
{
  VCS_RAIL_MODE_DEFAULT = 0,
  VCS_RAIL_MODE_MVC     = 1,

  VCS_RAIL_MODE_NUM_OF_MODES
} VCSRailModeType;


/*
 * VCS NPA Rail Events.
 */
typedef enum
{
  VCS_NPA_RAIL_EVENT_PRE_CHANGE   = NPA_TRIGGER_CUSTOM_EVENT1,
  VCS_NPA_RAIL_EVENT_POST_CHANGE  = NPA_TRIGGER_CUSTOM_EVENT2,
  VCS_NPA_RAIL_EVENT_LIMIT_MAX    = NPA_TRIGGER_CUSTOM_EVENT3,
} VCSNPARailEventType;


/*
 * VCS NPA LDO Events.
 */
typedef enum
{
  VCS_NPA_LDO_EVENT_PRE_CHANGE  = NPA_TRIGGER_CUSTOM_EVENT1,
  VCS_NPA_LDO_EVENT_POST_CHANGE = NPA_TRIGGER_CUSTOM_EVENT2,
} VCSNPALDOEventType;


/*
 * VCS NPA Rail Event Data.
 *
 * All fields are either:
 *   Non-zero when the state change is known prior to dispatching the event
 *   against the resource being monitored.
 *   For example: eCorner pre vs. post is always known.
 *
 *   Zero when the state change is unknown prior to dispatching the event
 *   against the resource being monitored.
 *   For example: nVoltageUV pre vs. post is not always known because the
 *   final voltage comes from CPR which is only known after the pre event has
 *   been dispatched. Another example is the voltage on CX/MX when changing
 *   corners as only RPM knows the actual voltage on those rails.
 */
typedef struct
{
  boolean bIsNAS ;            // Boolean indicates whether this change is NAS vs. CAS (immediate).

  struct
  {
    VCSCornerType eCorner;    // Voltage corner before the change event completes.
                              // Empty for limit max events.
    uint32        nVoltageUV; // Voltage in uV before the change event completes.
  } PreChange;
  struct
  {
    VCSCornerType eCorner;    // Voltage corner after the change event completes.
                              // New max corner for limit max events.
    uint32        nVoltageUV; // Voltage in uV after the change event completes.
  } PostChange;
} VCSNPARailEventDataType;


/*
 * VCS NPA LDO Event Data.
 */
typedef struct
{
  struct
  {
    VCSCornerType eCorner;    // Voltage corner before the change event completes.
    uint32        nVoltageUV; // Voltage in uV before the change event completes.
  } PreChange;
  struct
  {
    VCSCornerType eCorner;    // Voltage corner after the change event completes.
    uint32        nVoltageUV; // Voltage in uV after the change event completes.
  } PostChange;
} VCSNPALDOEventDataType;


/*
 * NPA Resources Exported by VCS
 *
 * CPU_0
 *   Broadcasts state changes on the CPU/LDO voltage.
 *
 * CX
 *   Resource for VDD_CX votes.
 *   Votes correspond to VCSCornerType enum values defined above.
 *
 * CX_ACTIVE_FLOOR
 *   Resource for voting on a global active floor of the rail.
 *   (votes only aggregated when the rail is on).
 *   Votes correspond to rail_voltage_level enum values defined in
 *   api/power/voltage_level.h
 *
 * SSC_CX
 *   SSC only. Resource for SSC CX votes. This is the main
 *   CX rail for SSC.
 *
 * SSC_CX_ACTIVE_FLOOR
 *   Similar to CX_ACTIVE_FLOOR but for SSC CX.
 *
 * MX
 *   Resource for VDD_MX votes.
 *   Votes correspond to VCSCornerType enum values defined above.
 *
 * MX_ACTIVE_FLOOR
 *   Resource for voting on a global active floor of the rail.
 *   (votes only aggregated when the rail is on).
 *   Votes correspond to rail_voltage_level enum values defined in
 *   api/power/voltage_level.h
 *
 * LPI_CX
 *   LPI only. Resource for LPI CX votes.
 *   This is the main CX rail for LPI.
 *
 * LPI_CX_ACTIVE_FLOOR
 *   Similar to CX_ACTIVE_FLOOR but for LPI CX.
 *
 * LPI_MX
 *   LPI only. Resource for LPI MX votes.
 *   This is the main MX rail for LPI.
 *
 * LPI_MX_ACTIVE_FLOOR
 *   Similar to CX_ACTIVE_FLOOR but for LPI MX.
 *
 */
#define VCS_NPA_RESOURCE_CPU_0                   "/vdd/cpu/0"
#define VCS_NPA_RESOURCE_VDD_CX                  "/vdd/cx"
#define VCS_NPA_RESOURCE_VDD_CX_ACTIVE_FLOOR     "/vdd/cx/active_floor"
#define VCS_NPA_RESOURCE_VDD_SSC_CX              "/vdd/ssccx"
#define VCS_NPA_RESOURCE_VDD_SSC_CX_ACIVE_FLOOR  "/vdd/ssccx/active_floor"
#define VCS_NPA_RESOURCE_VDD_MX                  "/vdd/mx"
#define VCS_NPA_RESOURCE_VDD_MX_ACTIVE_FLOOR     "/vdd/mx/active_floor"
#define VCS_NPA_RESOURCE_VDD_LPI_CX              "/vdd/lpicx"
#define VCS_NPA_RESOURCE_VDD_LPI_CX_ACTIVE_FLOOR "/vdd/lpicx/active_floor"
#define VCS_NPA_RESOURCE_VDD_LPI_MX              "/vdd/lpimx"
#define VCS_NPA_RESOURCE_VDD_LPI_MX_ACTIVE_FLOOR "/vdd/lpimx/active_floor"

/*
 * Temporary definition to ease MCPM integration.
 */
#define VCS_NPA_RESOURCE_LDO_MSS_Q6           VCS_NPA_RESOURCE_CPU_0


/** @} */ /* end_addtogroup vcs_functions */

/** @addtogroup npa_functions
@{ */
/** @name NPA Query Requests
@{ */

/**
  NPA query ID for the number of voltage levels.
  This query returns the number of voltage levels for the resource
  based on the target and configured limitations.
 */
#define VCS_NPA_QUERY_VOLTAGE_NUM_ENTRIES                                      \
  (NPA_QUERY_RESERVED_END + 1)

/**
  NPA query ID for the current voltage in uV.
  This query returns the current voltage in uV
  based on the target and configured limitations.
 */
#define VCS_NPA_QUERY_VOLTAGE_CURRENT_VOLTAGE_UV                               \
  (VCS_NPA_QUERY_VOLTAGE_NUM_ENTRIES + 1)

/**
  NPA query ID for the current voltage level enum value.
  This query returns the voltage level enum for the resource
  based on the target and configured limitations.
 */
#define VCS_NPA_QUERY_VOLTAGE_CURRENT_LEVEL_ID                                 \
  (VCS_NPA_QUERY_VOLTAGE_CURRENT_VOLTAGE_UV + 1)

/**
  NPA query ID for the voltage level id. This query gets the enum id
  for the requested level using the enum from VCSCornerType defined above.
  The actual voltage level is to be added to this ID (i.e., to query voltage
  level id for level 2, pass VCS_NPA_QUERY_VOLTAGE_LEVEL_ID + 2).
  This interfaces uses 0 as the first index.
 */
#define VCS_NPA_QUERY_VOLTAGE_LEVEL_ID                                         \
  (VCS_NPA_QUERY_VOLTAGE_CURRENT_LEVEL_ID + 1)

/**
  NPA query ID for the floor voltage at the requested level.
  The actual voltage level is to be added to this ID (i.e., to query
  voltage level id for level 2, pass VCS_NPA_QUERY_VOLTAGE_LEVEL_ID + 2).
  This interfaces uses 0 as the first index.
 */
#define VCS_NPA_QUERY_VOLTAGE_LEVEL_FLOOR                                      \
  (VCS_NPA_QUERY_VOLTAGE_LEVEL_ID + 0x20)

/**
  NPA query ID for the ceiling voltage at the requested level.
  The actual voltage level is to be added to this ID (i.e., to query
  voltage level id for level 2, pass VCS_NPA_QUERY_VOLTAGE_LEVEL_ID + 2).
  This interfaces uses 0 as the first index.
 */
#define VCS_NPA_QUERY_VOLTAGE_LEVEL_CEILING                                    \
  (VCS_NPA_QUERY_VOLTAGE_LEVEL_FLOOR + 0x20)

/**
  NPA query ID for the MVC safe voltage at the requested level.
  The actual voltage level is to be added to this ID (i.e., to query
  voltage level id for level 2, pass VCS_NPA_QUERY_VOLTAGE_LEVEL_ID + 2).
  This interfaces uses 0 as the first index.
 */
#define VCS_NPA_QUERY_VOLTAGE_LEVEL_MVC_SAFE                                   \
  (VCS_NPA_QUERY_VOLTAGE_LEVEL_CEILING + 0x20)


/** @} */ /* end_name_group NPA Query Requests */
/** @} */ /* end_addtogroup npa_functions */


#endif /* !VCSDEFS_H */
