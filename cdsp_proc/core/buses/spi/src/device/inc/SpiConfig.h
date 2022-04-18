#ifndef _SPICONFIG_H_
#define _SPICONFIG_H_
/*
===========================================================================

FILE:   SpiConfig.h

DESCRIPTION:

===========================================================================

        Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/buses/spi/src/device/inc/SpiConfig.h#1 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
01/16/15 vk     Created

===========================================================================
        Copyright (c) 2015-2016 Qualcomm Technologies Incorporated.
            All Rights Reserved.
         Qualcomm Confidentail & Proprietary

===========================================================================
*/
uint32 SpiConfig_GetMaxSourceClkFreqHz(void);
uint32 SpiConfig_GetMaxClkDividers(void);
void *SpiConfig_GetConfigObject(uint32 dev_instance);
#endif
