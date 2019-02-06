#ifndef _VECTOR3_H_
#define _VECTOR3_H_

namespace Sapphire::Common
{
  struct FFXIVARR_POSITION3
  {
    float x;
    float y;
    float z;
    inline bool operator == ( const FFXIVARR_POSITION3& target ) const;
  };
}

#endif