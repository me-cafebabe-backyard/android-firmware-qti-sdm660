/*============================================================================

FILE:      DalChipInfoLocal.c

DESCRIPTION:
  This file implements the portion of the ChipInfo DAL that reads information
  from the hardware.

PUBLIC CLASSES:
  ChipInfo_DriverInit
  ChipInfo_DriverDeInit

============================================================================
        Copyright (c) 2010,2015 Qualcomm Technologies, Inc.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
============================================================================
 
when       who     what, where, why
--------   ---     --------------------------------------------------------
06/10/15   pbitra    Added QDF2432 support.
05/26/15   pbitra    Added APQ8096 support.
07/29/14   pbitra     Updated for 8996.
07/11/11   pbitra     Fixed warnings.
01/15/13   pbitra     Updated 8974 V2.0 info and added 9x25 updates
============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "DalChipInfo.h"
#include "DDIHWIO.h"
#include "Library/BaseLib.h"


/*=========================================================================
      Type Definitions
==========================================================================*/


/*
 * DalChipInfoDataLUTType
 *
 * Static per-chip data definitions.
 *
 * szChipId:  String representing the MSM name.
 * szProcessorName : String representing the Processor name.
 * nFamily:   Chip Family enum.
 * nModem:    Bitmask of supported modems on this MSM.
 */
typedef struct
{
  const char          *szChipId;
  const char          *szProcessorName;
  DalChipInfoFamilyType nFamily;
  DalChipInfoModemType nModem;
} DalChipInfoDataLUTType;


/*
 * Define some modem combination shortcuts.
 */
#define DALCHIPINFO_MODEM_1XEVDO       (DALCHIPINFO_MODEM_1X | DALCHIPINFO_MODEM_EVDO)
#define DALCHIPINFO_MODEM_1XEVDO_REVA  (DALCHIPINFO_MODEM_1XEVDO | DALCHIPINFO_MODEM_EVDO_REVA)
#define DALCHIPINFO_MODEM_1XEVDO_REVB  (DALCHIPINFO_MODEM_1XEVDO_REVA | DALCHIPINFO_MODEM_EVDO_REVB)
#define DALCHIPINFO_MODEM_WWAN         (DALCHIPINFO_MODEM_1XEVDO_REVB | DALCHIPINFO_MODEM_GSM | DALCHIPINFO_MODEM_UMTS)


/*=========================================================================
      Data Definitions
==========================================================================*/

/*
 * DALCHIPINFO_MFGNUM_*
 *
 * Manufacturer IDs
 */
#define DALCHIPINFO_MFGNUM_QUALCOMM 0x170

/*
 * DALCHIPINFO_PARTNUM_*
 *
 * Definitions of part number fields.
 */

#define DALCHIPINFO_PARTNUM_MSM8996        0x947
#define DALCHIPINFO_PARTNUM_APQ8096        0x03E

#define DALCHIPINFO_PARTNUM_MSM8996SG      0x05F
#define DALCHIPINFO_PARTNUM_APQ8096SG      0x064
#define DALCHIPINFO_PARTNUM_MSM8996SGAU    0x06F
#define DALCHIPINFO_PARTNUM_APQ8096SGAU    0x071

#define DALCHIPINFO_PARTNUM_QDF2432        0x944

#define DALCHIPINFO_PARTNUM_MSM8998        0x05E
#define DALCHIPINFO_PARTNUM_APQ8098        0x062

#define DALCHIPINFO_PARTNUM_MDM9250        0x032
#define DALCHIPINFO_PARTNUM_MDM9255        0x034
#define DALCHIPINFO_PARTNUM_MDM9350        0x039
#define DALCHIPINFO_PARTNUM_MDM9650        0x03A
#define DALCHIPINFO_PARTNUM_MDM9655        0x03B
#define DALCHIPINFO_PARTNUM_MDM9665        0xFFF

#define DALCHIPINFO_PARTNUM_MSM8997        0x06C

#define DALCHIPINFO_PARTNUM_SDM660         0x08C
#define DALCHIPINFO_PARTNUM_SDA660         0x09C

#define DALCHIPINFO_PARTNUM_SDM658         0x08D
#define DALCHIPINFO_PARTNUM_SDA658         0x09D

#define DALCHIPINFO_PARTNUM_SDM630         0x0AC
#define DALCHIPINFO_PARTNUM_SDA630         0x0BC

#define DALCHIPINFO_PARTNUM_SDM636         0x0CC
#define DALCHIPINFO_PARTNUM_SDA636         0x0CD

#define DALCHIPINFO_PARTNUM_SDM455         0x0EF

/*
 * amPartMap
 *
 * Map of part numbers to logical parts.
 */
DalChipInfoPartMapType amPartMap[] =
{
  { DALCHIPINFO_PARTNUM_MSM8996,    DALCHIPINFO_ID_MSM8996   },
  { DALCHIPINFO_PARTNUM_APQ8096,    DALCHIPINFO_ID_APQ8096   },
  { DALCHIPINFO_PARTNUM_QDF2432,    DALCHIPINFO_ID_QDF2432   },
  { DALCHIPINFO_PARTNUM_MSM8998,    DALCHIPINFO_ID_MSM8998   },
  { DALCHIPINFO_PARTNUM_MDM9250,    DALCHIPINFO_ID_MDM9250   },        
  { DALCHIPINFO_PARTNUM_MDM9255,    DALCHIPINFO_ID_MDM9255   },        
  { DALCHIPINFO_PARTNUM_MDM9350,    DALCHIPINFO_ID_MDM9350   },        
  { DALCHIPINFO_PARTNUM_MDM9650,    DALCHIPINFO_ID_MDM9650   },        
  { DALCHIPINFO_PARTNUM_MDM9655,    DALCHIPINFO_ID_MDM9655   },  
  { DALCHIPINFO_PARTNUM_MSM8997,    DALCHIPINFO_ID_MSM8997   }, 
  { DALCHIPINFO_PARTNUM_SDM660,     DALCHIPINFO_ID_SDM660    },
  { DALCHIPINFO_PARTNUM_SDA660,     DALCHIPINFO_ID_SDA660    },
  { DALCHIPINFO_PARTNUM_SDM630,     DALCHIPINFO_ID_SDM630    },
  { DALCHIPINFO_PARTNUM_SDA630,     DALCHIPINFO_ID_SDA630    },
  { DALCHIPINFO_PARTNUM_SDM658,     DALCHIPINFO_ID_SDM658    },
  { DALCHIPINFO_PARTNUM_SDA658,     DALCHIPINFO_ID_SDA658    },
  { DALCHIPINFO_PARTNUM_APQ8098,    DALCHIPINFO_ID_APQ8098   },
  { DALCHIPINFO_PARTNUM_SDM636,     DALCHIPINFO_ID_SDM636    },
  { DALCHIPINFO_PARTNUM_SDA636,     DALCHIPINFO_ID_SDA636    },
  { DALCHIPINFO_PARTNUM_SDM455,     DALCHIPINFO_ID_SDM455    },

};

/*
 * chipIdMap
 *
 * Map of logical parts to DalChipInfoDataLUT indexes.
 */
DalChipInfoIdMapType chipIdMap[] =
{
  { DALCHIPINFO_ID_UNKNOWN,  0   },
  { DALCHIPINFO_ID_MSM8996,  1   },
  { DALCHIPINFO_ID_APQ8096,  2   },
  { DALCHIPINFO_ID_QDF2432,  3   },
  { DALCHIPINFO_ID_MSM8998,  4   },
  { DALCHIPINFO_ID_MDM9250,  5   },        
  { DALCHIPINFO_ID_MDM9255,  6   },   
  { DALCHIPINFO_ID_MDM9350,  7   },    
  { DALCHIPINFO_ID_MDM9650,  8   },     
  { DALCHIPINFO_ID_MDM9655,  9   },     
  { DALCHIPINFO_ID_MSM8997,  10  },  
  { DALCHIPINFO_ID_SDM660,   11  },
  { DALCHIPINFO_ID_SDA660,   12  },
  { DALCHIPINFO_ID_SDM630,   13  },
  { DALCHIPINFO_ID_SDA630,   14  },
  { DALCHIPINFO_ID_SDM658,   15  },
  { DALCHIPINFO_ID_SDA658,   16  },
  { DALCHIPINFO_ID_APQ8098,  17  },
  { DALCHIPINFO_ID_SDM636,   18  },
  { DALCHIPINFO_ID_SDA636,   19  },
  { DALCHIPINFO_ID_SDM455,   20  },

};

#define DALCHIPINFO_ID_MAP_SIZE (sizeof(amPartMap) / sizeof(amPartMap[0]))
#define DALCHIPINFO_CHIPID_MAP_SIZE (sizeof(chipIdMap) / sizeof(chipIdMap[0]))

/*
 * DalChipInfoDataLUT
 *
 * Array of chip id strings, families and modem support indexed by MSM ID.
 */
static const DalChipInfoDataLUTType DalChipInfoDataLUT[DALCHIPINFO_CHIPID_MAP_SIZE] =
{
  { "UNKNOWN",   "UNKNOWN",  DALCHIPINFO_FAMILY_UNKNOWN,  0 },
  { "MSM8996",   "UNKNOWN",  DALCHIPINFO_FAMILY_MSM8996,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "APQ8096",   "UNKNOWN",  DALCHIPINFO_FAMILY_MSM8996,  0 },
  { "QDF2432",   "UNKNOWN",  DALCHIPINFO_FAMILY_QDF2432,  0 },
  { "MSM8998",   "UNKNOWN",  DALCHIPINFO_FAMILY_MSM8998,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9250",   "UNKNOWN",  DALCHIPINFO_FAMILY_MDM9x55,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9255",   "UNKNOWN",  DALCHIPINFO_FAMILY_MDM9x55,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9350",   "UNKNOWN",  DALCHIPINFO_FAMILY_MDM9x55,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9650",   "UNKNOWN",  DALCHIPINFO_FAMILY_MDM9x55,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MDM9655",   "UNKNOWN",  DALCHIPINFO_FAMILY_MDM9x55,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "MSM8997",   "UNKNOWN",  DALCHIPINFO_FAMILY_MSM8997,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },  
  { "SDM660",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM660,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "SDA660",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM660,  0 },
  { "SDM630",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM630,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "SDA630",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM630,  0 },
  { "SDM658",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM660,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "SDA658",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM660,  0 },
  { "APQ8098",   "UNKNOWN",  DALCHIPINFO_FAMILY_MSM8998,  0 },
  { "SDM636",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM660,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },
  { "SDA636",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM660,  0 },
  { "SDM455",    "UNKNOWN",  DALCHIPINFO_FAMILY_SDM630,  DALCHIPINFO_MODEM_WWAN | DALCHIPINFO_MODEM_CGPS | DALCHIPINFO_MODEM_LTE },

};



/*
 * ChipFamilyArray0
 *
 * Array of ChipFamilies with Family Number 0.
 */
DalChipInfoFamilyType ChipFamilyArray0[] =
{
  DALCHIPINFO_FAMILY_MSM8974,
  DALCHIPINFO_FAMILY_MDM9x25,
  DALCHIPINFO_FAMILY_MSM8x26,
  DALCHIPINFO_FAMILY_APQ8084,
  DALCHIPINFO_FAMILY_MSM8926,
  DALCHIPINFO_FAMILY_MSM8x62,
  DALCHIPINFO_FAMILY_MPQ8092,
  DALCHIPINFO_FAMILY_MDM9x35,
  DALCHIPINFO_FAMILY_MSM8974_PRO,
  DALCHIPINFO_FAMILY_FSM9900,
  DALCHIPINFO_FAMILY_UNKNOWN,
  DALCHIPINFO_FAMILY_MSM8994,
};

/*
 * ChipFamilyArray1
 *
 * Array of ChipFamilies with Family Number 1.
 */
DalChipInfoFamilyType ChipFamilyArray1[] =
{
  DALCHIPINFO_FAMILY_MSM8x10,
  
};

/*
 * ChipFamilyArray2
 *
 * Array of ChipFamilies with Family Number 2.
 */
DalChipInfoFamilyType ChipFamilyArray2[] =
{
  DALCHIPINFO_FAMILY_MSM8916,
  DALCHIPINFO_FAMILY_MSM8936,
  DALCHIPINFO_FAMILY_MDM9x45,
  DALCHIPINFO_FAMILY_MSM8909,
  DALCHIPINFO_FAMILY_MSM8956,
  DALCHIPINFO_FAMILY_QCA961x,
  DALCHIPINFO_FAMILY_MSM8929,
  DALCHIPINFO_FAMILY_MSM8952,
};


/*
 * ChipFamilyArray3
 *
 * Array of ChipFamilies with Family Number 3.
 */
DalChipInfoFamilyType ChipFamilyArray3[] =
{
  DALCHIPINFO_FAMILY_MSM8996,
  DALCHIPINFO_FAMILY_MSM8993,
  DALCHIPINFO_FAMILY_MSM8998,
  DALCHIPINFO_FAMILY_UNKNOWN,
  DALCHIPINFO_FAMILY_MSM8996SG,
  DALCHIPINFO_FAMILY_MSM8997,  
  DALCHIPINFO_FAMILY_SDM660,
  DALCHIPINFO_FAMILY_SDM630,
};


/*=========================================================================
      Macros
==========================================================================*/
#define DALCHIPINFO_FAMILY_ARRAY0_SIZE (sizeof(ChipFamilyArray0) / sizeof(ChipFamilyArray0[0]))
#define DALCHIPINFO_FAMILY_ARRAY1_SIZE (sizeof(ChipFamilyArray1) / sizeof(ChipFamilyArray1[0]))
#define DALCHIPINFO_FAMILY_ARRAY2_SIZE (sizeof(ChipFamilyArray2) / sizeof(ChipFamilyArray2[0]))
#define DALCHIPINFO_FAMILY_ARRAY3_SIZE (sizeof(ChipFamilyArray3) / sizeof(ChipFamilyArray3[0]))

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* =========================================================================
**  Function : Chipinfo_GetFamily
** =========================================================================*/

void ChipInfo_GetFamily
(
  ChipInfoDrvCtxt       *pCtxt,
  DalChipInfoFamilyType *peFamily,
  uint32                nSOCHWVerNum
)
{
  DalChipInfoFamilyType ChipFamily = DALCHIPINFO_FAMILY_UNKNOWN;
  uint32 ChipFamilyNum = 0;
  uint32 ChipDeviceNum = 0;
  uint32 deviceNumBmsk, deviceNumShft;
  uint32 familyNumBmsk, familyNumShft;
  DALSYSPropertyVar PropVar;


  DALSYS_GetPropertyValue(pCtxt->hProps,"DEVICE_NUMBER_BMSK",0,&PropVar);
  deviceNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"DEVICE_NUMBER_SHFT",0,&PropVar);
  deviceNumShft = PropVar.Val.dwVal;

  ChipDeviceNum = (nSOCHWVerNum & deviceNumBmsk) >> deviceNumShft;

  DALSYS_GetPropertyValue(pCtxt->hProps,"FAMILY_NUMBER_BMSK",0,&PropVar);
  familyNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"FAMILY_NUMBER_SHFT",0,&PropVar);
  familyNumShft = PropVar.Val.dwVal;

  ChipFamilyNum = (nSOCHWVerNum & familyNumBmsk) >> familyNumShft;

  switch (ChipFamilyNum)
  {
    case 0:  
    {
      if (ChipDeviceNum >= DALCHIPINFO_FAMILY_ARRAY0_SIZE)
      {
        ChipFamily =  DALCHIPINFO_FAMILY_UNKNOWN;
      }
      else
      {
        ChipFamily =  ChipFamilyArray0[ChipDeviceNum]; 
      }
      break;
    }
    case 1:
    {
      if (ChipDeviceNum >= DALCHIPINFO_FAMILY_ARRAY1_SIZE)
      {
        ChipFamily =  DALCHIPINFO_FAMILY_UNKNOWN;
      }
      else
      {
        ChipFamily =  ChipFamilyArray1[ChipDeviceNum]; 
      }
      break;
    }
    case 2:
    {
      if (ChipDeviceNum >= DALCHIPINFO_FAMILY_ARRAY2_SIZE)
      {
        ChipFamily =  DALCHIPINFO_FAMILY_UNKNOWN;
      }
      else
      {
        ChipFamily =  ChipFamilyArray2[ChipDeviceNum]; 
      }
      break;
    }
    case 3:
    {
      if (ChipDeviceNum >= DALCHIPINFO_FAMILY_ARRAY3_SIZE)
      {
        ChipFamily =  DALCHIPINFO_FAMILY_UNKNOWN;
      }
      else
      {
        ChipFamily =  ChipFamilyArray3[ChipDeviceNum]; 
      }
      break;
    }
    default: 
    {
      ChipFamily =  DALCHIPINFO_FAMILY_UNKNOWN; 
      break;
    }
  }

  *peFamily = ChipFamily;

  return;

} /* END Chipinfo_GetFamily */


/* ===========================================================================
**  ChipInfo_GetPart
**
** ======================================================================== */

void ChipInfo_GetPart
(
  ChipInfoDrvCtxt     *pCtxt,
  DalChipInfoIdType   *pePart,
  uint32              nHWRevNum
)
{
  uint32 nPart, n;

  /*
   * Read the part number.
   */
  ChipInfo_GetRawPart(pCtxt, &nPart, nHWRevNum);

  /*
   * Look up using the table.
   */
  for (n = 0; n < DALCHIPINFO_ID_MAP_SIZE; n++)
  {
    if (nPart == amPartMap[n].nPart)
    {
      *pePart = amPartMap[n].ePart;
      break;
    }
  }

  if (n == DALCHIPINFO_ID_MAP_SIZE)
  {
    *pePart = DALCHIPINFO_ID_UNKNOWN;
  }

} /* END ChipInfo_GetPart */


/* ===========================================================================
**  ChipInfo_GetVersion
**
** ======================================================================== */

void ChipInfo_GetVersion
(
  ChipInfoDrvCtxt        *pCtxt,
  DalChipInfoVersionType *pnVersion,
  uint32                 nSOCHWVersion
)
{
  uint32 majNumBmsk, majNumShft, minNumBmsk, minNumShft, majorNum;
  DALSYSPropertyVar PropVar;


  DALSYS_GetPropertyValue(pCtxt->hProps,"MAJOR_VERSION_BMSK",0,&PropVar);
  majNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"MAJOR_VERSION_SHFT",0,&PropVar);
  majNumShft = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"MINOR_VERSION_BMSK",0,&PropVar);
  minNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"MINOR_VERSION_SHFT",0,&PropVar);
  minNumShft = PropVar.Val.dwVal;

  /* If MAJOR VERSION is 0x0 we treat it as 0x1 to provide correct versioninfo on Dino*/
  majorNum = (nSOCHWVersion & majNumBmsk) >> majNumShft;
  if( majorNum == 0x0)
  {
    majorNum = 0x1;
  }
  *pnVersion = DALCHIPINFO_VERSION(
     (majorNum),
      ((nSOCHWVersion & minNumBmsk) >> minNumShft));

} /* END ChipInfo_GetVersion */


/* ===========================================================================
**  ChipInfo_GetManufacturer
**
** ======================================================================== */

void ChipInfo_GetManufacturer
(
  ChipInfoDrvCtxt             *pCtxt,
  DalChipInfoManufacturerType *peManufacturer,
  uint32                      nHWRevNum
)
{
  uint32 pnRawManufacturer;

  ChipInfo_GetRawManufacturer(pCtxt, &pnRawManufacturer, nHWRevNum);
  switch(pnRawManufacturer)
    {
    case DALCHIPINFO_MFGNUM_QUALCOMM:
    {
      *peManufacturer = DALCHIPINFO_MFG_QUALCOMM;
      break;
    }

    default:
    {
      *peManufacturer = DALCHIPINFO_MFG_UNKNOWN;
      break;
    }
  }

} /* END ChipInfo_GetManufacturer */


/* ===========================================================================
**  ChipInfo_GetRawManufacturer
**
** ======================================================================== */

void ChipInfo_GetRawManufacturer
(
  ChipInfoDrvCtxt     *pCtxt,
  uint32 *pnRawManufacturer,
  uint32 nHWRevNum
)
{

  uint32 mfgIdBmsk, mfgIdShft;
  DALSYSPropertyVar PropVar;


  DALSYS_GetPropertyValue(pCtxt->hProps,"QUALCOMM_MFG_ID_BMSK",0,&PropVar);
  mfgIdBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"QUALCOMM_MFG_ID_SHFT",0,&PropVar);
  mfgIdShft = PropVar.Val.dwVal;

  *pnRawManufacturer = (nHWRevNum & mfgIdBmsk) >> mfgIdShft;

} /* END ChipInfo_GetRawManufacturer */


/* ===========================================================================
**  ChipInfo_GetRawPart
**
** ======================================================================== */

void ChipInfo_GetRawPart
(
  ChipInfoDrvCtxt     *pCtxt,
  uint32 *pnRawPart,
  uint32 nHWRevNum
)
{

  uint32 partNumBmsk, partNumShft;
  DALSYSPropertyVar PropVar;

  DALSYS_GetPropertyValue(pCtxt->hProps,"PARTNUM_BMSK",0,&PropVar);
  partNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"PARTNUM_SHFT",0,&PropVar);
  partNumShft = PropVar.Val.dwVal;

  *pnRawPart = (nHWRevNum & partNumBmsk) >> partNumShft;

} /* END ChipInfo_GetRawPart */


/* ===========================================================================
**  ChipInfo_GetRawVersion
**
** ======================================================================== */

void ChipInfo_GetRawVersion
(
  ChipInfoDrvCtxt     *pCtxt,
  uint32 *pnRawVersion,
  uint32 nHWRevNum
)
{
  uint32 versionIdBmsk, versionIdShft;
  DALSYSPropertyVar PropVar;

  DALSYS_GetPropertyValue(pCtxt->hProps,"VERSION_ID_BMSK",0,&PropVar);
  versionIdBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"VERSION_ID_SHFT",0,&PropVar);
  versionIdShft = PropVar.Val.dwVal;

  *pnRawVersion = (nHWRevNum & versionIdBmsk) >> versionIdShft;

} /* END ChipInfo_GetRawVersion */


/* ===========================================================================
**  ChipInfo_GetFoundry
**
** ======================================================================== */

void ChipInfo_GetFoundry
(
  ChipInfoDrvCtxt        *pCtxt,
  DalChipInfoFoundryIdType *pnFoundry,
  uint32                 nFoundryNum
)
{
  uint32 nFoundryBmsk, nFoundryShft;
  DALSYSPropertyVar PropVar;
  uint32 nFoundryRaw;

 
  DALSYS_GetPropertyValue(pCtxt->hProps,"FOUNDRY_BMSK",0,&PropVar);
  nFoundryBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"FOUNDRY_SHFT",0,&PropVar);
  nFoundryShft = PropVar.Val.dwVal;
  nFoundryRaw = (nFoundryNum & nFoundryBmsk) >> nFoundryShft;

  if(nFoundryRaw >= (DALCHIPINFO_NUM_FOUNDRYIDS - 1 ))
  {
	  *pnFoundry = DALCHIPINFO_FOUNDRYID_UNKNOWN;
  }
  else
  {
	  *pnFoundry = (DalChipInfoFoundryIdType)(nFoundryRaw + 1);
  }

} /* END ChipInfo_GetFoundry */


/* ===========================================================================
**  ChipInfo_GetRawChipDeviceFamily
**
** ======================================================================== */

void ChipInfo_GetRawChipDeviceFamily
(
  ChipInfoDrvCtxt        *pCtxt,
  uint32                 *pnRawDeviceFamily,
  uint32                 nSOCHWVersion
)
{
  uint32 familyNumBmsk, familyNumShft;
  DALSYSPropertyVar PropVar;


  DALSYS_GetPropertyValue(pCtxt->hProps,"FAMILY_NUMBER_BMSK",0,&PropVar);
  familyNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"FAMILY_NUMBER_SHFT",0,&PropVar);
  familyNumShft = PropVar.Val.dwVal;

  *pnRawDeviceFamily = (nSOCHWVersion & familyNumBmsk) >> familyNumShft;

} /* END ChipInfo_GetRawChipDeviceFamily */



/* ===========================================================================
**  ChipInfo_GetRawChipDeviceNumber
**
** ======================================================================== */
void ChipInfo_GetRawChipDeviceNumber
(
  ChipInfoDrvCtxt        *pCtxt,
  uint32                 *pnRawDeviceNumber,
  uint32                 nSOCHWVersion
)
{
  uint32 deviceNumBmsk, deviceNumShft;
  DALSYSPropertyVar PropVar;


  DALSYS_GetPropertyValue(pCtxt->hProps,"DEVICE_NUMBER_BMSK",0,&PropVar);
  deviceNumBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"DEVICE_NUMBER_SHFT",0,&PropVar);
  deviceNumShft = PropVar.Val.dwVal;

  *pnRawDeviceNumber = (nSOCHWVersion & deviceNumBmsk) >> deviceNumShft;

} /* END ChipInfo_GetRawChipDeviceFamily */


/* ===========================================================================
**  ChipInfo_ReadQFPROMChipId
**
** ======================================================================== */

void ChipInfo_ReadQFPROMChipId
(
  ChipInfoDrvCtxt     *pCtxt,
  DalChipInfoQFPROMChipIdType *pQFPROMChipId,
  uint32 nSerialNumHi
)
{

  uint32 chipIdBmsk, chipIdShft;
  DALSYSPropertyVar PropVar;

  DALSYS_GetPropertyValue(pCtxt->hProps,"QFPROM_CHIP_ID_BMSK",0,&PropVar);
  chipIdBmsk = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"QFPROM_CHIP_ID_SHFT",0,&PropVar);
  chipIdShft = PropVar.Val.dwVal;

  *pQFPROMChipId = (nSerialNumHi & chipIdBmsk) >> chipIdShft;

} /* END ChipInfo_GetQFPROMChipId */


/*=========================================================================
      Implementation
==========================================================================*/


/*==========================================================================

  FUNCTION      ChipInfo_DriverInit

  DESCRIPTION   See DDIChipInfo.h

==========================================================================*/

DALResult ChipInfo_DriverInit
(
  ChipInfoDrvCtxt     *pCtxt
)
{
  DALResult eResult = DAL_SUCCESS;
  DALSYSPropertyVar PropVar;
  UINTN nHWIORegAddr = 0, nSOCHWVerRegAddr = 0, nSerialNumRegAddr =0, nFoundryRegAddr = 0;
  uint32 nHWRevNum, nSOCHWVerNum, nFoundryNum;
  UINTN nHWRevNumPhysAddress, nSOCHWVerPhysAddress, nFoundryPhysAddress;
  uint32 n,nPart=0;
  uint32  nSerialNum;
    
  /* Get the property handle */
  DALSYS_GetDALPropertyHandle(DALDEVICEID_CHIPINFO,pCtxt->hProps);

  DALSYS_GetPropertyValue(pCtxt->hProps,"HWREVNUM_PHYS_ADDR",0,&PropVar);
  nHWRevNumPhysAddress = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"SOC_HW_VERSION_PHYS_ADDR",0,&PropVar);
  nSOCHWVerPhysAddress = PropVar.Val.dwVal;

  DALSYS_GetPropertyValue(pCtxt->hProps,"FOUNDRY_PHYS_ADDR",0,&PropVar);
  nFoundryPhysAddress = PropVar.Val.dwVal;

  /*-----------------------------------------------------------------------*/
  /* Attach to the HWIO DAL.                                               */
  /*-----------------------------------------------------------------------*/
  eResult = DAL_DeviceAttach(DALDEVICEID_HWIO, &pCtxt->phDalHWIO);
  if (eResult == DAL_SUCCESS)
  {
     eResult = DalHWIO_MapRegionByAddress(pCtxt->phDalHWIO, (uint8*)nHWRevNumPhysAddress,(uint8 **)&nHWIORegAddr);
     eResult |= DalHWIO_MapRegionByAddress(pCtxt->phDalHWIO, (uint8*)nSOCHWVerPhysAddress,(uint8 **)&nSOCHWVerRegAddr);
     eResult |= DalHWIO_MapRegionByAddress(pCtxt->phDalHWIO, (uint8*)nFoundryPhysAddress,(uint8 **)&nFoundryRegAddr);
  }
  else
  {
    nHWIORegAddr = nHWRevNumPhysAddress;
    nSOCHWVerRegAddr = nSOCHWVerPhysAddress;
    nFoundryRegAddr = nFoundryPhysAddress;
  }
  DALSYS_GetPropertyValue(pCtxt->hProps,"HWREVNUM_OFFSET",0,&PropVar);
  nHWIORegAddr = PropVar.Val.dwVal  + nHWIORegAddr;
  DALSYS_GetPropertyValue(pCtxt->hProps,"SOC_HW_VERSION_OFFSET",0,&PropVar);
  nSOCHWVerRegAddr = PropVar.Val.dwVal  + nSOCHWVerRegAddr;
  DALSYS_GetPropertyValue(pCtxt->hProps,"SERIAL_NUM_OFFSET",0,&PropVar);
  nSerialNumRegAddr = PropVar.Val.dwVal  + nFoundryRegAddr;
  DALSYS_GetPropertyValue(pCtxt->hProps,"FOUNDRY_OFFSET",0,&PropVar);
  nFoundryRegAddr = PropVar.Val.dwVal  + nFoundryRegAddr;

  nHWRevNum = *(uint32*)nHWIORegAddr;
  nSOCHWVerNum = *(uint32*)nSOCHWVerRegAddr;
  nFoundryNum = *(uint32*)nFoundryRegAddr;

  /*-----------------------------------------------------------------------*/
  /* Read chip information from HW.                                        */
  /*-----------------------------------------------------------------------*/

  ChipInfo_GetVersion(pCtxt,(DalChipInfoVersionType *)&pCtxt->nChipVersion, nSOCHWVerNum);
  ChipInfo_GetRawChipDeviceFamily(pCtxt, &pCtxt->nRawDeviceFamily, nSOCHWVerNum);
  ChipInfo_GetRawChipDeviceNumber(pCtxt, &pCtxt->nRawDeviceNumber, nSOCHWVerNum);  
  ChipInfo_GetPart(pCtxt,(DalChipInfoIdType *)&pCtxt->eChipId, nHWRevNum);
  ChipInfo_GetRawVersion(pCtxt,&pCtxt->nRawChipVersion, nHWRevNum);
  ChipInfo_GetRawPart(pCtxt,&pCtxt->nRawChipId, nHWRevNum);
  ChipInfo_GetFamily(pCtxt,(DalChipInfoFamilyType *)&pCtxt->eChipFamily, nSOCHWVerNum);
  ChipInfo_GetFoundry(pCtxt,(DalChipInfoFoundryIdType *)&pCtxt->eFoundryId, nFoundryNum);
  nSerialNum = *(uint32*)nSerialNumRegAddr;
  pCtxt->nSerialNum = ((DalChipInfoSerialNumType)nSerialNum);
  ChipInfo_ReadQFPROMChipId(pCtxt,(DalChipInfoQFPROMChipIdType *)&pCtxt->nQFPROMChipId, *(uint32*)(nSerialNumRegAddr+4));

  /*-----------------------------------------------------------------------*/
  /* Check for override of the ChipId from the properties.                 */
  /*-----------------------------------------------------------------------*/

  if (pCtxt->eChipId == DALCHIPINFO_ID_UNKNOWN)
  {
    eResult = DALSYS_GetPropertyValue(pCtxt->hProps, "ChipIdOverride", 0, &PropVar);

    if (eResult == DAL_SUCCESS)
    {
      pCtxt->eChipId = (DalChipInfoIdType)PropVar.Val.dwVal;
      pCtxt->nChipVersion = 0x00010000;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Fill in derived information.                                          */
  /*-----------------------------------------------------------------------*/

  /*
   * Look up using the table.
   */
  for (n = 0; n < DALCHIPINFO_CHIPID_MAP_SIZE; n++)
  {
    if (pCtxt->eChipId == chipIdMap[n].ePart)
    {
      nPart = chipIdMap[n].nPart;
      break;
    }
  }

  if (n == DALCHIPINFO_CHIPID_MAP_SIZE)
  {
    nPart = 0;
  }
  pCtxt->nModemSupport = DalChipInfoDataLUT[nPart].nModem;
  strlcpy(
    pCtxt->szChipIdString, DalChipInfoDataLUT[nPart].szChipId,
    DALCHIPINFO_MAX_ID_LENGTH);

  strlcpy(
    pCtxt->szProcessorNameString, DalChipInfoDataLUT[nPart].szProcessorName,
    DALCHIPINFO_MAX_ID_LENGTH);

  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END ChipInfo_DriverInit */


/*==========================================================================

  FUNCTION      ChipInfo_DriverDeInit

  DESCRIPTION   See DDIChipInfo.h

==========================================================================*/

DALResult ChipInfo_DriverDeInit
(
  ChipInfoDrvCtxt *pCtxt
)
{
  if (pCtxt->phDalHWIO != NULL)
  {
    DalDevice_Close(pCtxt->phDalHWIO);
  }

  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END ChipInfo_DriverDeInit */


