/**
  @file  EFIClock.h
  @brief Clock Protocol for UEFI.
*/
/*=============================================================================
  Copyright (c) 2010-2016 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/18/13   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 05/03/12   vishalo Merge in Techpubs Doxygen change
 03/20/12   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 01/26/12   vishalo Merge in Techpubs Doxygen change
 10/28/11   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 12/23/10   vs      Created.

=============================================================================*/
#ifndef __EFICLOCK_H__
#define __EFICLOCK_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @addtogroup efi_clock_constants
@{ */
/**
  Protocol version.
*/
#define EFI_CLOCK_PROTOCOL_VERSION 0x0000000000010005
/**
  Real-time protocol version.
*/
#define EFI_CLOCK_RT_PROTOCOL_VERSION 0x00010000
/** @} */ /* end_addtogroup efi_clock_constants */

/** @addtogroup efi_clock_protocol
@{ */
/*  Protocol GUID definition */
#define EFI_CLOCK_PROTOCOL_GUID \
  { 0x241AFAE6, 0x885F, 0x4F6C, {0xA7, 0xEA, 0xC2, 0x8E, 0xAB, 0x79, 0xC3, 0xE5 } }

/* RealTime (RT) Protocol ID */
#define EFI_CLOCK_RT_PROTOCOL_GUID \
  { 0x1E587FEF, 0x45A4, 0x4FA8, {0xFF, 0xFF, 0xFF, 0xFF, 0x1A, 0xC8, 0xFF, 0xB7 } }
/** @} */ /* end_addtogroup efi_clock_protocol */

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the CLOCK Protocol GUID.
*/
extern EFI_GUID gEfiClockProtocolGuid;

extern EFI_GUID gEfiClockRTProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/**
  Protocol declaration.
*/
typedef struct _EFI_CLOCK_PROTOCOL EFI_CLOCK_PROTOCOL;
/** @endcond */

/** @addtogroup efi_clock_data_types
@{ */
/* How to search for a matching frequency input */
/**
  Describes how frequency matching is performed for the clock frequency
  selection function, EFI_CLOCK_SET_FREQ_HZ(). The enumeration also indicates
  the units in Hz, kHz, or MHz.
*/
typedef enum
{
  EFI_CLOCK_FREQUENCY_HZ_AT_LEAST  = 0,
  /**< Frequency is the minimum allowed in Hz. */
  EFI_CLOCK_FREQUENCY_HZ_AT_MOST   = 1,
  /**< Frequency is the maximum allowed in Hz. */
  EFI_CLOCK_FREQUENCY_HZ_CLOSEST   = 2,
  /**< Closest match in Hz. */
  EFI_CLOCK_FREQUENCY_HZ_EXACT     = 3,
  /**< Exact match only in Hz. */

  EFI_CLOCK_FREQUENCY_KHZ_AT_LEAST = 0x10,
  /**< Frequency is the minimum allowed in kHz. */
  EFI_CLOCK_FREQUENCY_KHZ_AT_MOST  = 0x11,
  /**< Frequency is the maximum allowed in kHz. */
  EFI_CLOCK_FREQUENCY_KHZ_CLOSEST  = 0x12,
  /**< Closest match in kHz. */
  EFI_CLOCK_FREQUENCY_KHZ_EXACT    = 0x13,
  /**< Exact match only in kHz. */

  EFI_CLOCK_FREQUENCY_MHZ_AT_LEAST = 0x20,
  /**< Frequency is the minimum allowed in MHz. */
  EFI_CLOCK_FREQUENCY_MHZ_AT_MOST  = 0x21,
  /**< Frequency is the maximum allowed in MHz. */
  EFI_CLOCK_FREQUENCY_MHZ_CLOSEST  = 0x22,
  /**< Closest match in MHz. */
  EFI_CLOCK_FREQUENCY_MHZ_EXACT    = 0x23,
  /**< Exact match only in MHz. */
} EFI_CLOCK_FREQUENCY_TYPE;

/**
  Type of clock reset. This defines how the reset to the clock domain
  is to be handled.
 */
typedef enum
{
  EFI_CLOCK_RESET_DEASSERT = 0,  /**< Deassert the reset signal. */
  EFI_CLOCK_RESET_ASSERT   = 1,  /**< Assert and hold the reset signal. */
  EFI_CLOCK_RESET_PULSE    = 2   /**< Assert and immediately deassert. */
} EFI_CLOCK_RESET_TYPE;
/** @} */ /* end_addtogroup efi_clock_data_types */

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_CLOCK_GET_ID */
/** @ingroup efi_clock_get_id
  @par Summary
  Looks up a clock ID for a specified clock name.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockName             String name of the clock.
  @param[out] ClockId               Pointer where to fill in the clock ID.

  @par Description
  This function takes the name of a clock and returns a handle that
  can be used for making requests on that clock. Usually, this function
  must be the first to be invoked prior to using any other clock functions.
  The string name of the clock can be found in the software frequency
  plan, e.g., cc_uart2_clk.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_GET_ID)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  CONST CHAR8        *ClockName,
  OUT UINTN              *ClockId
  );


/* EFI_CLOCK_ENABLE */
/** @ingroup efi_clock_enable
  @par Summary
  Enables a specified clock. This function does not reference count
  recursive calls, but does perform tracking between multiple clients.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to enable.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_ENABLE)(
  IN EFI_CLOCK_PROTOCOL *This,
  IN UINTN              ClockId
  );


/* EFI_CLOCK_DISABLE */
/** @ingroup efi_clock_disable
  @par Summary
  Disables a clock.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to disable.

  @par Description
  This function removes the client's vote to enable a specified clock.
  There is no support for reference counting recursive calls; however, the
  driver will not disable the clock if a different client has made an
  enable request.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_DISABLE)(
  IN EFI_CLOCK_PROTOCOL *This,
  IN UINTN              ClockId
  );


/* EFI_CLOCK_IS_ENABLED */
/** @ingroup efi_clock_is_enabled
  @par Summary
  Checks the enabled state of a clock.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to check.
  @param[out] IsEnabled             Returns 1 if the clock is enabled;
                                    otherwise 0.

  @par Description
  This function checks if a specified clock is enabled or disabled. Note
  that this is not necessarily equivalent to the clock being active. A
  clock may be disabled by the local processor, but enabled by another one.
  Or if the hardware is misconfigured, the clock may be enabled, but not
  actively toggling.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_IS_ENABLED)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINTN              ClockId,
  OUT BOOLEAN            *IsEnabled
  );


/* EFI_CLOCK_IS_ON */
/** @ingroup efi_clock_is_on
  @par Summary
  Checks whether a specified clock is on. <i>On</i> means the clock
  is not just enabled, but is actually toggling.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to check.
  @param[out] IsOn                  Returns 1 if the clock is ON; otherwise 0.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_IS_ON)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINTN              ClockId,
  OUT BOOLEAN            *IsOn
  );


/* EFI_CLOCK_SET_FREQ_HZ */
/** @ingroup efi_clock_set_freq_hz
  @par Summary
  Sets the frequency of a clock.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock for which to set the frequency.
  @param[in]  Freq                  Clock frequency.
  @param[in]  Match                 Type of match request;
                                    see #EFI_CLOCK_FREQUENCY_TYPE for details.
                                    Values:
                                    - 0 -- Frequency is the minimum allowed
                                    - 1 -- Frequency is the maximum allowed
                                    - 2 -- Closest match
                                    - 3 -- Exact match only
                                    @tablebulletend
  @param[out] ResultFreq            Programmed clock frequency; can be NULL
                                    if the resulting frequency does not need
                                    to be checked.

  @par Description
  This function requests a frequency change for a specified clock. The driver
  selects the exact frequency based on the matching argument, which allows
  requesting a minimum or approximate frequency. There is no support for
  concurrent requests; the last request will be serviced and override any
  other minimum frequency requests.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_SET_FREQ_HZ)(
  IN  EFI_CLOCK_PROTOCOL        *This,
  IN  UINTN                     ClockId,
  IN  UINT32                    Freq,
  IN  EFI_CLOCK_FREQUENCY_TYPE  Match,
  OUT UINT32                    *ResultFreq
  );


/* EFI_CLOCK_GET_FREQ_HZ */
/** @ingroup efi_clock_get_freq_hz
  @par Summary
  Retrieves the current frequency of a clock in hertz. The retrieval
  is independent of whether or not the clock is running.

  @note1hang Only clocks controlled on the local processor can have the
             frequency retrieved.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to check.
  @param[out] FreqHz                Pointer to the UINT32 to be filled
                                    in with the frequency. A value
                                    of zero indicates that the frequency
                                    could not be determined.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_GET_FREQ_HZ)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINTN              ClockId,
  OUT UINT32             *FreqHz
  );


/* EFI_CLOCK_CALC_FREQ_HZ */
/** @ingroup efi_clock_calc_freq_hz
  @par Summary
  Calculates the frequency of a clock.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to check.
  @param[out] FreqHz                Pointer to the UINT32 to be filled
                                    in with the frequency. A value
                                    of zero indicates that the frequency
                                    could not be determined.

  @par Description
  This function calculates the current frequency of a clock in hertz using
  hardware counting circuits. This functionality depends on the hardware
  support being present, as well as available on the current processor. It
  also requires that the clock be enabled, which must be possible from
  the current environment.
  @par
  The frequency calculation is accurate to within a few kilohertz.
  The calculation takes a long time (at least a few milliseconds) and
  is intended only for testing purposes, not any real modes of operation.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_CALC_FREQ_HZ)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINTN              ClockId,
  OUT UINT32             *FreqHz
  );


/* EFI_CLOCK_SELECT_EXTERNAL_SOURCE */
/** @ingroup efi_clock_sel_external_source
  @par Summary
  Selects an external source for a clock.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to check.
  @param[in]  FreqHz                Source frequency in Hz. The value 0
                                    indicates that voltage scaling is not
                                    expected for this source.
  @param[in]  Source                Source to use. Pass the following values:
                                    - 0 -- Selects the first (or only) external
                                           source
                                    - 1 -- Selects the second external source
                                    - 2 -- etc.
                                    @tablebulletend
  @param[in]  Divider               Integer divider to use.
  @param[in]  VAL_M                 M value for any M/N counter (0 to bypass).
                                    Not all clock domains have M/N counters;
                                    these values will be ignored in such cases.
  @param[in]  VAL_N                 N value for any M/N counter.
  @param[in]  VAL_2D                Twice the D value for any M/N counter.
                                    The raw value is doubled to allow for
                                    half-integer duty cycles.

  @par Description
  This function selects an external source for a clock and configures the
  clock generator dividers. This is only necessary for clock domains that
  can be derived from a source outside the clock block such that
  EFI_CLOCK_SET_FREQ_HZ() cannot be used. Note that the caller must specify a
  nonzero value for the source clock's frequency if the caller expects the
  clock driver to provide voltage scaling support.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_SELECT_EXTERNAL_SOURCE)(
   IN EFI_CLOCK_PROTOCOL *This,
   IN UINTN              ClockId,
   IN UINT32             FreqHz,
   IN UINT32             Source,
   IN UINT32             Divider,
   IN UINT32             VAL_M,
   IN UINT32             VAL_N,
   IN UINT32             VAL_2D
   );


/* EFI_POWER_DOMAIN_GET_ID */
/** @ingroup efi_clock_power_domain_get_id
  @par Summary
  Looks up a power domain ID for a specified power domain name.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockPowerDomainName  String name of the power domain.
  @param[out] ClockPowerDomainId    Pointer where to fill in the power domain
                                    ID.

  @par Description
  This function takes the name of a power domain and returns a handle that
  can be used for making requests on that power domain. Usually, this function
  must be the first to be invoked prior to using any other power domain
  functions. The string name of the clock can be found in the software
  frequency plan, e.g., VDD_GRP.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_POWER_DOMAIN_GET_ID)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  CONST CHAR8        *ClockPowerDomainName,
  OUT UINTN              *ClockPowerDomainId
  );


/* EFI_POWER_DOMAIN_ENABLE */
/** @ingroup efi_clock_power_domain_enable
  @par Summary
  Enables a specified power domain.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockPowerDomainId    Power domain to enable.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_POWER_DOMAIN_ENABLE)(
  IN EFI_CLOCK_PROTOCOL *This,
  IN UINTN              ClockPowerDomainId
  );


/* EFI_POWER_DOMAIN_DISABLE */
/** @ingroup efi_clock_power_domain_disable
  @par Summary
  Disables a specified power domain.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockPowerDomainId    Power domain to disable.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_POWER_DOMAIN_DISABLE)(
  IN EFI_CLOCK_PROTOCOL *This,
  IN UINTN              ClockPowerDomainId
  );


/* EFI_CLOCK_ENTER_LOW_POWER_MODE */
/** @ingroup efi_clock_enter_low_power_mode
  @par Summary
  Enters the Low Power mode.

  @param[in]  This      Pointer to the EFI_CLOCK_PROTOCOL instance.

  @par Description
  This function is used to enter a Low Power state that facilitates
  rapid battery charging.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_ENTER_LOW_POWER_MODE)(
   IN EFI_CLOCK_PROTOCOL *This
   );


/* EFI_CLOCK_EXIT_LOW_POWER_MODE */
/** @ingroup efi_clock_exit_low_power_mode
  @par Summary
  Exits the Low Power mode.

  @param[in]  This      Pointer to the EFI_CLOCK_PROTOCOL instance.

  @par Description
  This function restores the system on chip to its previous state before
  it entered a Low Power state to facilitate rapid battery charging.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_EXIT_LOW_POWER_MODE)(
   IN EFI_CLOCK_PROTOCOL *This
   );

/* EFI_CLOCK_SET_CLOCK_DIVIDER */
/** @ingroup efi_clock_set_clock_divider
  @par Summary
  Sets the divider for a clock.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock for which to set the frequency.
  @param[in]  Divider               Clock divider in logical units; 0 is invalid.

  @par Description
  This function programs the divider for a specified clock. This
  functionality only applies to a small subset of clocks that have
  independent dividers off the main domain.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_SET_CLOCK_DIVIDER)(
  IN  EFI_CLOCK_PROTOCOL        *This,
  IN  UINTN                     ClockId,
  IN  UINT32                    Divider
  );


/* EFI_CLOCK_RESET */
/** @ingroup efi_clock_reset
  @par Summary
  This function allows resetting the hardware in a specified clock domain. The
  resetting is destructive to the hardware and requires reconfiguration
  after the reset is deasserted.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to reset.
  @param[in]  eReset                Type of reset: assert, deassert, or pulse.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_RESET)(
  IN EFI_CLOCK_PROTOCOL    *This,
  IN UINTN                  ClockId,
  IN EFI_CLOCK_RESET_TYPE   eReset
  );


/* EFI_CLOCK_GET_FREQ_HZ */
/** @ingroup efi_clock_get_freq_hz
  @par Summary
  Retrieves the frequency of a running CPU clock in hertz.
  @note1hang Only running CPU on the local processor can have the
             frequency retrieved.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[out] FreqHz                Pointer to the UINT32 to be filled
                                    in with the frequency. A value
                                    of zero indicates that the frequency
                                    could not be determined.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CPU_GET_FREQ_HZ)(
  IN  EFI_CLOCK_PROTOCOL *This,
  OUT UINT32             *FreqHz
  );

/* EFI_CLOCK_SET_EXT_SOURCE_DIV */
/** @ingroup efi_clock_set_ext_source_div
  @par Summary
  Set a clock external source Divider.

    @param  This      [in]        The EFI_CLOCK_PROTOCOL instance.
    @param  ClockName [in]        String name of the clock.
    @param  nDivider  [in]        The divider to be set.

  @par Description
  This function takes the name of a clock, and will Set a clock external source Divider
  associated to that clock.
  The string name of the clock can be found in the clock chapter of the
  chip HLD.  For example, "cc_uart2_clk".

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_CLOCK_SET_EXT_SOURCE_DIV)(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  CONST CHAR8        *ClockName,
  IN  UINT32              nDivider
  );


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_clock_protocol
  @par Summary
  Clock Protocol interface.

  @par Parameters
  @inputprotoparams{clock_proto_params.tex}
*/
struct _EFI_CLOCK_PROTOCOL {
   UINT64                           Version;
   EFI_CLOCK_GET_ID                 GetClockID;
   EFI_CLOCK_ENABLE                 EnableClock;
   EFI_CLOCK_DISABLE                DisableClock;
   EFI_CLOCK_IS_ENABLED             IsClockEnabled;
   EFI_CLOCK_IS_ON                  IsClockOn;
   EFI_CLOCK_SET_FREQ_HZ            SetClockFreqHz;
   EFI_CLOCK_GET_FREQ_HZ            GetClockFreqHz;
   EFI_CLOCK_CALC_FREQ_HZ           CalcClockFreqHz;
   EFI_CLOCK_SELECT_EXTERNAL_SOURCE SelectExternalSource;
   EFI_POWER_DOMAIN_GET_ID          GetClockPowerDomainID;
   EFI_POWER_DOMAIN_ENABLE          EnableClockPowerDomain;
   EFI_POWER_DOMAIN_DISABLE         DisableClockPowerDomain;
   EFI_CLOCK_ENTER_LOW_POWER_MODE   EnterLowPowerMode;
   EFI_CLOCK_EXIT_LOW_POWER_MODE    ExitLowPowerMode;
   EFI_CLOCK_SET_CLOCK_DIVIDER      SetClockDivider;
   EFI_CLOCK_RESET                  ResetClock;
   EFI_CPU_GET_FREQ_HZ              GetCpuFreqHz;
   EFI_CLOCK_SET_EXT_SOURCE_DIV     SetExternalSourceDiv;
};

#endif  /* __EFICLOCK_H__ */
