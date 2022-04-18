#include "DALStdDef.h" 
#include "DALSysTypes.h" 


typedef struct
{
  const void * const * struct_ptrs;
  unsigned size_of_DALPROP_StructPtrs;
  const uint32* prop_bin;
  unsigned size_of_DALPROP_PropBin;
  const StringDevice* the_driver_list;
  unsigned driver_list_count;
  unsigned supported_chipset;
  char* section_start;
  char* section_limit;
} DALPROP_Target_Data;

typedef struct
{
    unsigned supported_target_count;
    const DALPROP_Target_Data**  supported_targets;
} DALPROP_Multi_Target_Data;

