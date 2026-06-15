#pragma once 


#include "sfr/common/status_codes.h"
#include <cstdint>
typedef enum sfr_types_e {
  SFR_T_VOID,
  SFR_T_UNKNOW,
   SFR_T_INT,
   SFR_T_FLOAT,
   SFR_T_DOUBLE,
   SFR_T_STRING,
   SFR_T_ARRAY,
   SFR_T_BOOL,
   SFR_T_JSON_OBJECT
} sfr_types_t;



