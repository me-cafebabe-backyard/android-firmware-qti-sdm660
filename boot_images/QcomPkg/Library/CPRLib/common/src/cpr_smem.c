/**
 * @file:  cpr_smem.c
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/CPRLib/common/src/cpr_smem.c#2 $
 * $Change: 11185940 $
 */
#include "cpr_smem.h"
#include "cpr_image.h"
#include "cpr_logs.h"
#include "cpr_utils.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define CURRENT_SMEM_CFG_VERSION 2

#define INCREMENT_OFFSET(size)                                                    \
do{                                                                               \
    *currOffset += (size);                                                        \
    if(*currOffset >= hdr->smemSize)                                              \
        CPR_LOG_FATAL("Exceeded memory (0x%x/0x%x)", *currOffset, hdr->smemSize); \
}while(0)

#define GET_BUFFER()    (((uint8*)hdr) + *currOffset)

//******************************************************************************
// V2 Defines
//******************************************************************************

typedef struct __attribute__ ((__packed__))
{
    uint32 mode;  // cpr_voltage_mode
    int16  decodedFuseSteps;
    int16  decodedFuseOffset;
    uint16 enableCount;
    uint16 targetsCount;
    uint16 submodesCount;
} cpr_smem_mode_state;

typedef struct __attribute__ ((__packed__))
{
    uint16  size;              // in bytes
    uint32  id;                // cpr_rail_id
    uint32  controlMode;       // cpr_control_mode
    int32   marginAdjustments[CPR_MARGIN_ADJUSTMENT_MAX];
    int16   decodedFuseAging;
    uint32  activeVoltageMode; // cpr_voltage_mode
    uint8   modeStateCount;
} cpr_smem_rail_hdr;

typedef struct __attribute__ ((__packed__))
{
    uint8   version;
    uint8   railCount;
    uint16  dataSize;       // Data size written to SMEM to get offset.
    uint16  smemSize;       // SMEM buffer size
} cpr_smem_hdr;

//******************************************************************************
// Local Helper Functions
//******************************************************************************

/*==============================================================================
 *
 * Writes SMEM header and increments offset.
 *
 */
static cpr_smem_hdr* cpr_smem_write_header(void* buf, uint32 bufSize, uint32 *currOffset)
{
    cpr_smem_hdr* hdr = (cpr_smem_hdr*)buf;

    hdr->version   = CURRENT_SMEM_CFG_VERSION;
    hdr->railCount = 0;
    hdr->smemSize  = bufSize;
    hdr->dataSize  = 0;

    INCREMENT_OFFSET(sizeof(cpr_smem_hdr));

    return hdr;
}

/*==============================================================================
 *
 * Reads SMEM header and increments offset.
 *
 */
static cpr_smem_hdr* cpr_smem_read_header(void* buf, uint32 *currOffset)
{
    cpr_smem_hdr* hdr = (cpr_smem_hdr*)buf;

    INCREMENT_OFFSET(sizeof(cpr_smem_hdr));

    return hdr;
}

/*==============================================================================
 *
 * Writes rail header and increments offset.
 *
 */
static cpr_smem_rail_hdr* cpr_smem_write_rail_header(cpr_smem_hdr* hdr, uint32 *currOffset, cpr_rail_state* state)
{
    cpr_smem_rail_hdr* railHdr = (cpr_smem_rail_hdr*) GET_BUFFER();

    hdr->railCount++;

    INCREMENT_OFFSET(sizeof(cpr_smem_rail_hdr));

    railHdr->id          = state->id;
    railHdr->controlMode = state->cMode;

    for(int i = 0; i < CPR_MARGIN_ADJUSTMENT_MAX; i++)
    {
        railHdr->marginAdjustments[i] = state->marginAdjustments[i];
    }

    railHdr->decodedFuseAging = state->decodedFuseAging;

    if(state->activeMode)
    {
        railHdr->activeVoltageMode = state->activeMode->mode;
    }
    else
    {
        railHdr->activeVoltageMode = 0;
    }

    railHdr->modeStateCount = 0;

    return railHdr;
}

/*==============================================================================
 *
 * Reads rail header and increments offset.
 * If a rail config is not for the given rail, sets offset to the next rail config and
 * returns NULL.
 *
 */
static cpr_smem_rail_hdr* cpr_smem_read_rail_header(cpr_smem_hdr* hdr, uint32 *currOffset, cpr_rail* rail, cpr_rail_state* state)
{
    cpr_smem_rail_hdr* railHdr = (cpr_smem_rail_hdr*) GET_BUFFER();

    if(railHdr->id == rail->id)
    {
        INCREMENT_OFFSET(sizeof(cpr_smem_rail_hdr));

        state->id    = (cpr_domain_id)railHdr->id;
        state->cMode = (cpr_control_mode)railHdr->controlMode;

        for(int i = 0; i < CPR_MARGIN_ADJUSTMENT_MAX; i++)
        {
            state->marginAdjustments[i] = railHdr->marginAdjustments[i];
        }

        state->decodedFuseAging = railHdr->decodedFuseAging;

        if(railHdr->activeVoltageMode)
        {
            state->activeMode = &state->modeSettings[cpr_utils_get_mode_idx(rail, (cpr_voltage_mode)railHdr->activeVoltageMode )];
        }
        else
        {
            state->activeMode = NULL;
        }
    }
    else
    {
        /*
         * Set offset to the next rail.
         */
        *currOffset += railHdr->size;

        /*
         * Return NULL to indicate the rail config was not for the given rail.
         */
        railHdr = NULL;
    }

    return railHdr;
}

/*==============================================================================
 *
 * Writes target quotients and increments offset.
 *
 */
typedef struct
{
    uint16 ro;
    uint32 quotient;
} cpr_quotient_smem; /* old cpr_quotient type. Avoid BOOT/RPM dependency */

static void cpr_smem_write_target_quotients(cpr_smem_hdr* hdr, uint32 *currOffset, cpr_mode_settings* modeSetting)
{
    for(int i = 0; i < modeSetting->targetsCount; i++)
    {
        cpr_quotient_smem* target = (cpr_quotient_smem*) GET_BUFFER();

        INCREMENT_OFFSET(sizeof(cpr_quotient_smem));

        target->ro       = modeSetting->targets[i].ro;
        target->quotient = modeSetting->targets[i].quotient;

        //cpr_image_memscpy(target, &(modeSetting->targets[i]), sizeof(cpr_quotient));
    }
}

/*==============================================================================
 *
 * Reads target quotients and increments offset.
 *
 */
static void cpr_smem_read_target_quotients(cpr_smem_hdr* hdr, uint32 *currOffset, cpr_mode_settings* modeSetting)
{
    for(int i = 0; i < modeSetting->targetsCount; i++)
    {
        cpr_quotient_smem* target = (cpr_quotient_smem*) GET_BUFFER();

        INCREMENT_OFFSET(sizeof(cpr_quotient_smem));

        modeSetting->targets[i].ro       = target->ro;
        modeSetting->targets[i].quotient = target->quotient;

        //cpr_image_memscpy(&(modeSetting->targets[i]), target, sizeof(cpr_quotient));
    }
}

/*==============================================================================
 *
 * Writes submode settings and increments offset.
 *
 */
static void cpr_smem_write_sub_modes(cpr_smem_hdr* hdr, uint32 *currOffset, cpr_mode_settings* modeSetting)
{
    for(int i = 0; i < modeSetting->subModesCount; i++)
    {
        cpr_submode_settings *submode = (cpr_submode_settings*) GET_BUFFER();

        INCREMENT_OFFSET(sizeof(cpr_submode_settings));

        cpr_image_memscpy(submode, &(modeSetting->subModes[i]), sizeof(cpr_submode_settings));
    }
}

/*==============================================================================
 *
 * Reads submode settings and increments offset.
 *
 */
static void cpr_smem_read_sub_modes(cpr_smem_hdr* hdr, uint32 *currOffset, cpr_mode_settings* modeSetting)
{
    for(int i = 0; i < modeSetting->subModesCount; i++)
    {
        cpr_submode_settings *submode = (cpr_submode_settings*) GET_BUFFER();

        INCREMENT_OFFSET(sizeof(cpr_submode_settings));

        cpr_image_memscpy(&(modeSetting->subModes[i]), submode, sizeof(cpr_submode_settings));
    }
}

/*==============================================================================
 *
 * Writes rail mode settings and increments offset.
 * Stores the byte size of the rail config in the rail header in order to search
 * rail config easily.
 * Stores the byte size of the entire data written to the SMEM in order to get
 * offset for the next rail config.
 *
 */
static void cpr_smem_write_rail_state(cpr_smem_hdr* hdr, cpr_smem_rail_hdr* railHdr, uint32 *currOffset, cpr_rail_state* state)
{
    for(int i = 0; i < state->modeSettingsCount; i++)
    {
        cpr_mode_settings* modeSetting = &(state->modeSettings[i]);
        cpr_smem_mode_state* modeState = (cpr_smem_mode_state*) GET_BUFFER();

        railHdr->modeStateCount++;

        INCREMENT_OFFSET(sizeof(cpr_smem_mode_state));

        modeState->mode              = modeSetting->mode;
        modeState->decodedFuseSteps  = modeSetting->decodedFuseSteps;
        modeState->decodedFuseOffset = modeSetting->decodedFuseOffset;
        modeState->enableCount       = modeSetting->enableCount;
        modeState->targetsCount      = modeSetting->targetsCount;
        modeState->submodesCount     = modeSetting->subModesCount;

        cpr_smem_write_target_quotients(hdr, currOffset, modeSetting);
        cpr_smem_write_sub_modes(hdr, currOffset, modeSetting);

        /*
         * Last 2 bytes of cpr_submode_settings is padded.
         * Make use of the space to pass the total margin info
         * which was used to calculate target quotients
         * without breaking SMEM data structure.
         */
        *(int16*)(((uint8*)hdr) + *currOffset - 2) = modeSetting->totalMarginMV;
    }

    railHdr->size = (uint16)((uint8*)hdr + *currOffset - (uint8*)railHdr);
    hdr->dataSize = *currOffset;
}

/*==============================================================================
 *
 * Reads rail mode settings and increments offset.
 *
 */
static void cpr_smem_read_rail_state(cpr_smem_hdr* hdr, cpr_smem_rail_hdr* railHdr, uint32 *currOffset, cpr_rail* rail, cpr_rail_state* state)
{
    for(int i = 0; i < railHdr->modeStateCount; i++)
    {
        cpr_mode_settings* modeSetting;
        cpr_smem_mode_state* modeState = (cpr_smem_mode_state*) GET_BUFFER();

        INCREMENT_OFFSET(sizeof(cpr_smem_mode_state));

        modeSetting = &(state->modeSettings[cpr_utils_get_mode_idx(rail, (cpr_voltage_mode)modeState->mode )]);

        modeSetting->mode              = (cpr_voltage_mode)modeState->mode;
        modeSetting->decodedFuseSteps  = modeState->decodedFuseSteps;
        modeSetting->decodedFuseOffset = modeState->decodedFuseOffset;
        modeSetting->enableCount       = modeState->enableCount;

        if(!modeSetting->targets)
        {
            if(modeState->targetsCount)
            {
                modeSetting->targets = cpr_image_malloc( modeState->targetsCount * sizeof(cpr_quotient) );
            }
        }
        else
        {
            /*
             * Do we need to realloc instead of abort?
             */
            CPR_ASSERT( modeSetting->targetsCount >= modeState->targetsCount );

        }

        modeSetting->targetsCount = modeState->targetsCount;

        if(!modeSetting->subModes)
        {
            if(modeState->submodesCount)
            {
                modeSetting->subModes = cpr_image_malloc( modeState->submodesCount * sizeof(cpr_submode_settings) );
            }
        }
        else
        {
            /*
             * Do we need to realloc instead of abort?
             */
            CPR_ASSERT( modeSetting->subModesCount >= modeState->submodesCount );
        }

        modeSetting->subModesCount = modeState->submodesCount;

        cpr_smem_read_target_quotients(hdr, currOffset, modeSetting);
        cpr_smem_read_sub_modes(hdr, currOffset, modeSetting);

        /*
         * Last 2 bytes of cpr_submode_settings is padded.
         * Make use of the space to pass the total margin info
         * which was used to calculate target quotients
         * without breaking SMEM data structure.
         */
        modeSetting->totalMarginMV = *(int16*)(((uint8*)hdr) + *currOffset - 2);
    }
}

/*==============================================================================
 *
 * Reads CPR config for the rail in SMEM in the below format and updates config data.
 *
 *  -----------------------------------------------------
 *   cpr_smem_hdr
 *  -----------------------------------------------------
 *   cpr_smem_rail_hdr[0]
 *  -----------------------------------------------------
 *       cpr_smem_mode_state[0]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *      -------------------------------------------------
 *       ...
 *      -------------------------------------------------
 *       cpr_smem_mode_state[modeSettingsCount-1]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *  -----------------------------------------------------
 *   ...
 *  -----------------------------------------------------
 *   cpr_smem_rail_hdr[cpr_smem_hdr.railCount-1]
 *  -----------------------------------------------------
 *       cpr_smem_mode_state[0]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *      -------------------------------------------------
 *       ...
 *      -------------------------------------------------
 *       cpr_smem_mode_state[modeSettingsCount-1]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *  -----------------------------------------------------
 */
static void deserialize_v2(cpr_rail* rail, cpr_rail_state* state, void* buf, uint32 size)
{
    uint32 currOffset = 0;
    cpr_smem_hdr* hdr = cpr_smem_read_header(buf, &currOffset);
    boolean foundRail = false;

    for(int i = 0; i < hdr->railCount; i++)
    {
        cpr_smem_rail_hdr* railHdr = cpr_smem_read_rail_header(hdr, &currOffset, rail, state);

        if(railHdr)
        {
            foundRail = true;

            cpr_smem_read_rail_state(hdr, railHdr, &currOffset, rail, state);

            break;
        }
    }

    CPR_ASSERT( foundRail );
}

//******************************************************************************
// Public API Functions
//******************************************************************************

/*==============================================================================
 *
 * Reads CPR config for the rail in SMEM and updates config data.
 *
 */
void cpr_smem_deserialize_config(cpr_rail* rail, cpr_rail_state* state)
{
    uint32 size;
    cpr_smem_hdr* hdr;

    cpr_image_open_remote_cfg( (void**)&hdr, &size );

    switch(hdr->version)
    {
        case CURRENT_SMEM_CFG_VERSION: deserialize_v2( rail, state, hdr, size ); break;

        default:
            CPR_LOG_FATAL( "Unsupported serialization version: %u", hdr->version );
    }

    cpr_image_close_remote_cfg();
}

/*==============================================================================
 *
 * Writes CPR config for the rail to SMEM in the below format.
 *
 *  -----------------------------------------------------
 *   cpr_smem_hdr
 *  -----------------------------------------------------
 *   cpr_smem_rail_hdr[0]
 *  -----------------------------------------------------
 *       cpr_smem_mode_state[0]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *      -------------------------------------------------
 *       ...
 *      -------------------------------------------------
 *       cpr_smem_mode_state[modeSettingsCount-1]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *  -----------------------------------------------------
 *   ...
 *  -----------------------------------------------------
 *   cpr_smem_rail_hdr[cpr_smem_hdr.railCount-1]
 *  -----------------------------------------------------
 *       cpr_smem_mode_state[0]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *      -------------------------------------------------
 *       ...
 *      -------------------------------------------------
 *       cpr_smem_mode_state[modeSettingsCount-1]
 *      -------------------------------------------------
 *           cpr_quotient[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_quotient[targetsCount-1]
 *          ---------------------------------------------
 *           cpr_submode_settings[0]
 *          ---------------------------------------------
 *           ...
 *          ---------------------------------------------
 *           cpr_submode_settings[subModesCount-1]
 *  -----------------------------------------------------
 */
void cpr_smem_serialize_config(cpr_rail_state* state, boolean append)
{
    uint32 currOffset = 0;
    uint32 size;
    void* buf;
    cpr_smem_hdr* hdr;
    cpr_rail *rail = cpr_utils_get_rail(state->id);

    CPR_ASSERT(rail);

    cpr_image_open_remote_cfg( &buf, &size );

    if(!append)
    {
        hdr = cpr_smem_write_header(buf, size, &currOffset);
    }
    else
    {
        hdr = (cpr_smem_hdr*)buf;

        currOffset = hdr->dataSize;
    }

    CPR_LOG_INFO(" Exporting %s rail state (offset: 0x%x)", rail->name, currOffset);

    cpr_smem_rail_hdr* railHdr = cpr_smem_write_rail_header(hdr, &currOffset, state);

    cpr_smem_write_rail_state(hdr, railHdr, &currOffset, state);

    cpr_image_close_remote_cfg();
}

