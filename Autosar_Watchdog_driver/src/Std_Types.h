
#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#include "Platform_Types.h"
#include "Compiler.h"


typedef uint8 Std_ReturnType;

typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
} Std_VersionInfoType;


#define E_OK            0x00U
#define E_NOK           0x01U

#define STD_HIGH        0x01U
#define STD_LOW         0x00U

#define STD_ACTIVE      0x01U
#define STD_IDLE        0x00U

#define STD_ON          0x01U
#define STD_OFF         0x00U


#endif /* STD_TYPES_H_ */
