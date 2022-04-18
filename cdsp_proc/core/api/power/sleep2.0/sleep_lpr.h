#ifndef SLEEP_LPR_H
#define SLEEP_LPR_H
/*==============================================================================
  FILE:         sleep_lpr.h
  
  OVERVIEW:     This file provides the public externs and definitions that
                are exported by the sleep module for accessing the sleep LPR
                node and functions.

  DEPENDENCIES: None

                Copyright (c) 2010-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/api/power/sleep2.0/sleep_lpr.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "comdef.h"
#include "npa.h"
#include "sleep_stats.h"
#include "sleep_npa.h"

/*==============================================================================
                             MACRO DEFINITIONS
 =============================================================================*/
/**
 * @brief SLEEP_LPR_SUCCESS
 *
 * Function completed successfully. 
 */
#define SLEEP_LPR_SUCCESS 0

/**
 * @brief SLEEP_LPR_FAILED
 *
 * Function failed. 
 */
#define SLEEP_LPR_FAILED 1

/* Used to create the bitmask passed in requests to /sleep/lpr. */
/**
 * @brief SLEEP_LPRM_NUM
 *
 * Used to create the bitmask that corresponds to mode enable/disable
 * request to /sleep/lpr
 */
#define SLEEP_LPRM_NUM(x) (1 << (x))

/**
 * @brief SLEEP_ALL_LPRMS
 *
 * Bitmask representing all modes (basically all 1's)
 */
#define SLEEP_ALL_LPRMS (NPA_MAX_STATE)

/* Utility macros to fill the core fields of various sleep structures
 * 
 * @FIXME: move to core/utils.  Macro to assist in declaring the dependency and
 * exclusion arrays. */
#define CORE_ARRAY_SIZE(array)  (sizeof(array)/sizeof(array[0]))
#define CORE_ARRAY(array)       CORE_ARRAY_SIZE(array), array
#define CORE_EMPTY_ARRAY        0, NULL

/*==============================================================================
                        GENERAL SLEEP DESCRIPTION
 =============================================================================*/

/* Sleep LPR management node
 *
 * The sleep LPR node is responsible for allowing registration of low power
 * resources (LPR's) each of which have one or more low power resource mode
 * (LPRM).  LPR's are resources critical to the compute path that will not be
 * needed when the processor is idle as turning them off provides a desirable
 * power savings (depending on the current dynamic conditions).
 *  
 * There are basically two tiers at which resources are filtered for whether or
 * not they enter a low power mode. The first is the explicit LPRM tracking:
 * NPA nodes for the affected resources will make requests into the sleep LPR
 * node.  Requests into the sleep LPR node are 32-bit bitmasks, where each set
 * bit is an enable signal for a given LPRM.  The mapping between bits and
 * LPRM's can be queried from the LPR node (see below for more detail).  Unless
 * an LPRM is requested by at least one client of the sleep LPR node, they are
 * considered explicity disabled and will not be considered for entry at idle
 * time.
 *  
 * The second and more complex tier is the sleep "solver."  The solver's task
 * is to look at all the enabled LPRM's and select the low power modes which
 * result in optimal power consumption based on the current expected sleep
 * period, latency restrictions, and temperature.  The solver functions
 * independently of the sleep LPR node, other than a simple query to figure out
 * which LPRM's are currently enabled.
 *
 * Making a request into this node (and thereby indicating to the LPRM tracking
 * system that a mode is able to be entered when the CPU has become idle) does
 * not mean that the resource necessarily *will* be put to sleep.  The actual
 * decision to select a sleep mode for entry is not made until idle time, when
 * the sleep solver will select modes based on what configurations would
 * provide the optimal power savings given the conditions that exist (expected
 * sleep length, latency budget, etc.). 
 *
 * However, when nobody has made a request into this node with a given bit set,
 * the LPRM associated with that bit is considered disabled.  This means that
 * regardless of whatever conditions may exist, the LPM solver cannot select a
 * low power resource mode until someone has made a request to enable it.
 *
 *                == Summary of supported operations ==
 *
 * Query this node with query id SLEEP_LPR_QUERY_BITMASK:
 *    - Takes an LPRM name string as an input in the 'reference' field.
 *    - LPRM name string should be immutable.
 *    - Returns the bitmask that should be requested into the sleep LPR field
 *      when the LPRM should be enabled as an output in the value field.
 *
 * Query this node with query id SLEEP_LPR_QUERY_RESOURCES:
 *    - Returns a pointer to the internal array of registered LPR's.  The array
 *      is returned in the reference field, but should only be accessed while
 *      in an INTLOCK'd context, as the array is raw internal node state.  This
 *      query should be exclusively used by the sleep solver to enumerate
 *      modes.
 *
 * Query this node with query id NPA_QUERY_CURRENT_STATE:
 *    - Returns a bitwise OR of all currently requested bitmasks.  This is
 *      basically the mask of LPRM's that are considered for selection when the
 *      sleep solver runs.
 *
 * Make a required request into this node:
 *    - For each set bit in the request bitmask, enables the associated LPRM
 *      for selection when the sleep solver runs.
 *
 * Complete a request into this node:
 *    - Remove the previously enabled LPRM's from consideration when the sleep
 *      solver runs.
 */

/*==============================================================================
                           GLOBAL TYPE DEFINITIONS
 =============================================================================*/
/**
 * @brief The prototype for a function called when the low power mode should be
 *        set up to happen at sleep time.
 *  
 * Each low power mode is required to define a function of this type.  Its
 * purpose it to isolate the code required to enter a low power mode in an
 * easy-to-call way.  This allows us to call or not call the code based on
 * whether this particular mode was selected. 
 *  
 * Note that this function is NOT allowed to fail.  You should place all checks
 * for whether the power mode can be entered outside of the actual sleep mode
 * selection via LPM mask bits.
 *
 * @param wakeup_tick: Absolute wake-up tick.
 */
typedef void (*sleep_enter_func)(uint64 wakeup_tick);

/**
 * @brief The prototype for a function called when the low power mode should be
 *        torn down.
 *  
 * Each low power mode is required to define a function of this type.  Its
 * purpose it to isolate the code required to clean up after a low power mode
 * in an easy-to-call way.  This allows us to call the exit functions for modes
 * that we entered during sleep. 
 *  
 * It is safe to assume that exit functions will only be called if the
 * associated enter function was called first. 
 */
typedef void (*sleep_exit_func)(void);

/**
 * @brief The prototype for the function that gets called when a low power
 *        resource is initialized from Sleep framework. 
 *
 * Each low power resource (LPR) must be initialized before it is used. Sleep
 * framework can do so if pointer to an init function (that adheres following
 * prototype) is provided in LPR definition. If the init function needs to 
 * be called outside sleep framework, a NULL pointer can be used for that
 * field in the resource definition. In either case, it MUST be ensured that
 * all necessary initialization has been performed before any of resource's 
 * low power mode is entered for the first time.
 */
typedef void (*sleep_lpr_init_func_type)(void);

/**
 * @brief Enum that will map various LPRM options (like reference count and
 *        use of locks) to that mode's attribute bitmask.
 */
typedef enum
{
  /* No Attributes */
  SLEEP_MODE_ATTR_NONE = 0,
  
  /* Obsolete flag that can be reused */
  SLEEP_MODE_ATTR_UNUSED1 = 1 << 0,

  /* Mode that must be reentered when the solver chooses the same synth mode */
  SLEEP_MODE_ATTR_MULTIPLE_ENTRY = 1 << 1,

  /* Obsolete flag that can be reused */
  SLEEP_MODE_ATTR_UNUSED4 = 1 << 2,
  
  /* Mode will return its own backoff latency enter & exit times
   * This should only be used for the power collapse LPRM where automatic
   * monitoring would not work */
  SLEEP_MODE_ATTR_NO_AUTO_LATENCY_TRACK = 1 << 3,

  /*  A LPR component mode with this attribute provides enter and
   *  exit functions that can be executed at active time.
   *
   *  A Synth LPR with all component modes have this attribute set 
   *  can be executed and selected by the run-time solver */
  SLEEP_MODE_ATTR_LPR_CACHEABLE = 1 << 4,

  /* Sets bit field for all the attributes defined above and enforces enum
   * of 32bit size */
  SLEEP_MODE_ALL_ATTRS = 0x7FFFFFFF,
}sleep_mode_attribute;

/* Forward declaration of low power resource (LPR) and modes (LPRM) structs */
typedef struct sleep_lpr_s  sleep_lpr;
typedef struct sleep_lprm_s sleep_lprm;

/* struct to store low power mode information */ 
struct sleep_lprm_s
{
  /* The name of this low power mode, independent of the resoruce name.  For
   * example, for apps processor core voltage retention-only, mode this would
   * be "retention" as the resource name is already embedded in the owning
   * resource structure. Names must be valid C-language identifiers. */
  const char *mode_name;
  
  /* Index value (determined via SleepSynth tool) for indexing into dynamic
   * data structures */
  uint32 dynamic_num;

  /* Functions that implement the actual entry/setup and exit/teardown of a 
   * mode. Either of them must be provided. */
  sleep_enter_func  enter_func;
  sleep_exit_func   exit_func;

  /* Back-pointer to parent LPR */
  sleep_lpr *parent_LPR;

  /* Attributes for the mode */
  uint32 attributes;

  /* Current status of this mode */
  unsigned char mode_enabled;

  /* Setting from global config in efs/NV ram */
  unsigned char global_config_disabled;

  /* Sleep statistics for this sleep LPRM*/
  sleepStats_mode_stats mode_statistics;

  /* Array of synthLPRM's that this component mode is part of. */
  void **synth_LPRM_parent_array;

  /* Count of synth parents that this LPRM belongs to */
  uint32 synth_LPRM_parent_count;
};

/* Struct that contains information of Low Power Resource (LPR). It will be 
 * defined by user who wants to register his LPR with sleep system. */
struct sleep_lpr_s
{
  /* The name associated with this resource, that is used to reference the
   * resource by other LPRs.  This name can be used to indicate the LPR name
   * and the LPRM group name.  The name must be a valid C-language identifier.
   * Further more, if the control of this resource is via an NPA resource, the
   * name of the LPR should be the "file" part of the NPA resource name (e.g.
   * an NPA resource named "/xo/cxo" would have a corresponding LPR named just
   * "cxo"). */
  const char *resource_name;

  /* The number of low power modes this resource has. */
  uint32 mode_count;

  /* The list of low power modes this resource can enter, preferred modes
   * listed first. */
  sleep_lprm *modes;

  /* Resource initiliazation function */
  sleep_lpr_init_func_type init;

  /* Indicates if this LPR has already been registered with sleep subsystem */
  unsigned char registered;

  /* Indicates the number of times the LPR has been entered */
  uint32 run_count;
};

/*==============================================================================
                        GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * @brief Register a low power resource (and all its associated modes) with the
 *        sleep subsystem.
 *
 * This function is intended to be called once per LPR at startup time.  It
 * registers all of the LPRM's of the resource with the sleep LPR node.
 * This function works in conjunction with the LPRs generated from 
 * an LPR configuration file.  Call this function instead of sleep_define_lpr
 * and pass in the name of the low power resource (eg. "cxo") to register
 * the resource.
 *
 * @param name:          Low power resource name we want to register with sleep 
 *                       system.
 * @param client_handle: The NPA client handle associated with the above LPR
 *
 * @return SLEEP_LPR_SUCCESS if the resource name was found, 
 *         SLEEP_LPR_FAILED if the resource name was not found
 */
int sleepLPR_define(const char* name, npa_client_handle client_handle);

/** 
 * sleep_define_lpr_str
 * @deprecated use sleepLPR_define
 */
#define sleep_define_lpr_str  sleepLPR_define

/**
 * @brief Register a low power island resource (and all its associated modes) with the
 *        sleep subsystem.
 *
 * This function is intended to be called once per LPI at startup time.  It
 * registers all of the LPIM's of the resource with the sleep LPR node.
 * This function works in conjunction with the LPRs generated from 
 * an LPR configuration file.
 *
 * @param name:          Low power island resource name we want to register with sleep 
 *                       system.
 * @param client_handle: The NPA client handle associated with the above LPI
 *
 * @return SLEEP_LPR_SUCCESS if the resource name was found, 
 *         SLEEP_LPR_FAILED if the resource name was not found
 */
int sleepLPI_define(const char* name, npa_client_handle client_handle);

#ifdef __cplusplus
}
#endif

#endif /* SLEEP_LPR_H */

