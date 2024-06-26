#pragma once

namespace Sapphire::Common
{
  struct FFXIVARR_POSITION3
  {
    float x;
    float y;
    float z;
    inline bool operator == ( const FFXIVARR_POSITION3& target ) const;
    FFXIVARR_POSITION3 operator - ( const FFXIVARR_POSITION3& target ) const;
  };

  struct Vector3
  {
    float x;
    float y;
    float z;
    float reserve;
    inline bool operator == ( const Vector3& target ) const;
    Vector3 operator - ( const Vector3& target ) const;
  };

  struct Matrix33
  {
    float m[ 3 ][ 3 ];
  };
}
