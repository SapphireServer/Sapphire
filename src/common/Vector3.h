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
    FFXIVARR_POSITION3 operator - ( const FFXIVARR_POSITION3& target ) const;
  };

  struct Vector3
  {
    float x;
    float y;
    float z;
    inline bool operator == ( const Vector3& target ) const;
<<<<<<< HEAD
    inline bool operator == ( const FFXIVARR_POSITION3& target ) const;
=======
    Vector3 operator - ( const Vector3& target ) const;
>>>>>>> 952391ae4f19e29cadc39df2eee97ed15e6067d3
  };

  struct Matrix33
  {
    float m[ 3 ][ 3 ];
  };
}
