#pragma once

namespace Sapphire::Common
{
  // todo: get rid of this struct and use an actual vector 3 class
  struct FFXIVARR_POSITION3
  {
    float x;
    float y;
    float z;
    inline bool operator == ( const FFXIVARR_POSITION3& target ) const;
  };

  struct Vector3
  {
    float x;
    float y;
    float z;
    inline bool operator == ( const Vector3& target ) const;
    inline bool operator == ( const FFXIVARR_POSITION3& target ) const;
  };

  struct Matrix33
  {
    float m[ 3 ][ 3 ];
  };
}
