#ifndef SYNTHLPI_H
#define SYNTHLPI_H
/*==============================================================================
  FILE:            synthLPI.h
  
  OVERVIEW:        Provides the synth LPI mode functions.
  
  DEPENDENCIES: None
 
                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/synthesizer/synthLPI.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "sleepi.h"
#include "synthTypes.h"
#include "synthLPR.h"

/*==============================================================================
                             FUNCTION DEFINITION
 =============================================================================*/
/**
 * synthLPI_getStatus
 *
 * @brief Function to see if this LPI enabled.
 *
 * The LPI is enabled if it has any mode which is selected by sleep solver 
 * as an enabled (or entered) mode during idle time.
 * 
 * @param synthLPI: Synth LPI to check
 * 
 * @return Returns SLEEP_ENABLED if the Synth LPI is enabled else SLEEP_DISABLED.
 */
sleep_status synthLPI_getStatus(sleep_synth_lpi *synthLPI);

/**
 * synthLPI_modeUpdated
 *
 * @brief This function updates the status of this sleep_synth_lpr with the registry
 *        according to input mode.
 *
 * The status of the sleep_synth_lpr is said to be changed when number of enabled modes
 * is reduced to zero from non-zero or vice versa.
 *
 * @param mode: Mode when made enabled/disabled may cause change in the
 *              status of sleep_synth_lpr.
 */
void synthLPI_modeUpdated(sleep_synth_lprm* synthLPRM);

/**
 * synthLPI_init
 *
 * @brief Sets up initial values for the synth mode
 *
 * @param synthLPI: Pointer to the presynthesized LPR
 */
void synthLPI_init(sleep_synth_lpi *synthLPI);

/**
 * synthLPI_define
 *
 * @brief This function will be called once per synthesized LPI at the start up 
 *        time to register a it with the sleep subsystem.
 *
 * Registering presynthesized LPIs requires apriori knowledge of all LPRs and 
 * their dependencies.
 *
 * @param synthLPI: Low power resource we want to register with sleep 
 *                  system.
 */
void synthLPI_define(sleep_synth_lpi *synthLPI);

#endif // SYNTHLPI_H

