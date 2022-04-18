#ifndef SPMIINFO_H
#define SPMIINFO_H

#include "SpmiTypes.h"

#define SPMI_BID2ADDR(SPMI_INFO,BID) ((SPMI_INFO)->devices[BID].baseAddrs )
#define SPMI_PDEV(SPMI_INFO,BID) (&(SPMI_INFO)->devices[(BID)] )

#define SPMI_NUM_BUSES_SUPPORTED(SPMI_INFO) ((SPMI_INFO)->uNumDevices)
#define SPMI_NUM_CHANNELS_SUPPORTED(PSPMI_DEV) ((PSPMI_DEV)->pGenerics->mNumChannels)
#define SPMI_NUM_PORT_PRIORITIES(PSPMI_DEV)     ((PSPMI_DEV)->pGenerics->mNumPortPriorities)
#define SPMI_NUM_PVC_PORTS(PSPMI_DEV)    ((PSPMI_DEV)->pGenerics->mNumPvcPorts)
#define SPMI_NUM_PVC_PPIDS(PSPMI_DEV)    ((PSPMI_DEV)->pGenerics->mNumPvcPortPPIDs)
#define SPMI_NUM_MASTERS(PSPMI_DEV)    ((PSPMI_DEV)->pGenerics->mNumMasters)
#define SPMI_NUM_PROG_RAM_REGS(PSPMI_DEV)    ((PSPMI_DEV)->pGenerics->mNumProgRamRegs)
#define SPMI_NUM_MAPPING_TABLE_ENTRIES(PSPMI_DEV)    ((PSPMI_DEV)->pGenerics->mNumMappingTableEntries)
#define SPMI_NUM_PIC_ACC_STATUS_REGS(PSPMI_DEV)    ((PSPMI_DEV)->pGenerics->mNumPicAccStatusRegs)


typedef struct SpmiDeviceGenerics {
   uint16 mNumChannels;
   uint16 mNumPortPriorities;
   uint16 mNumPvcPorts;
   uint16 mNumPvcPortPPIDs;
   uint16 mNumMasters;
   uint16 mNumProgRamRegs;
   uint16 mNumMappingTableEntries;
   uint16 mNumPicAccStatusRegs;
} SpmiDeviceGenerics;

typedef struct {
    int8 sid       :  5;
    int16 nextIdx  : 11;
} ChannelMapEntry;

typedef struct {
    uint8*                    baseAddrs;
    uint8                     uDevIdx;
    uint16                    reservedChan;
    uint16                    nextChanIdx;
    boolean                   reservedChanEn;
    boolean                   dynamicChannelMode;
    int16                    *periphMap;
    ChannelMapEntry          *channelMap;
    SpmiDeviceGenerics       *pGenerics;
    void                     *target;
} SpmiDevInfo;

typedef void (*PmicArbIsrCallback)(uint8 bid, uint16 channel, uint8 mask);

typedef struct SpmiInfo {
  uint8               owner;
  boolean             hasInterruptSupport;
  PmicArbIsrCallback  isrCallback;
  uint8               uNumDevices;
  SpmiDevInfo        *devices;
} SpmiInfo;

#endif // SPMIINFO_H
