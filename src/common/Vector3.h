#pragma once

#include <cmath>

namespace Sapphire::Common
{
  struct FFXIVARR_POSITION3
  {
    float x;
    float y;
    float z;

    // Checks for equality between two FFXIVARR_POSITION3 objects
    inline bool operator==( const FFXIVARR_POSITION3& target ) const
    {
      return x == target.x && y == target.y && z == target.z;
    }

    // Adds two FFXIVARR_POSITION3 objects
    inline FFXIVARR_POSITION3 operator+( const FFXIVARR_POSITION3& target ) const
    {
      return { x + target.x, y + target.y, z + target.z };
    }

    // Subtracts two FFXIVARR_POSITION3 objects
    inline FFXIVARR_POSITION3 operator-( const FFXIVARR_POSITION3& target ) const
    {
      return { x - target.x, y - target.y, z - target.z };
    }
  };

  struct Vector3
  {
    float x;
    float y;
    float z;
    float reserve;

    // Checks for equality between two Vector3 objects
    inline bool operator==( const Vector3& target ) const
    {
      return x == target.x && y == target.y && z == target.z;
    }

    // Adds two Vector3 objects
    inline Vector3 operator+( const Vector3& target ) const
    {
      return { x + target.x, y + target.y, z + target.z, reserve };
    }

    // Subtracts two Vector3 objects
    inline Vector3 operator-( const Vector3& target ) const
    {
      return { x - target.x, y - target.y, z - target.z, reserve };
    }

    // Scales a Vector3 object by a scalar value
    inline Vector3 operator*( float scalar ) const
    {
      return { x * scalar, y * scalar, z * scalar, reserve };
    }

    // Computes the dot product of two Vector3 objects
    inline float dot( const Vector3& target ) const
    {
      return x * target.x + y * target.y + z * target.z;
    }

    // Computes the cross product of two Vector3 objects
    inline Vector3 cross( const Vector3& target ) const
    {
      return { y * target.z - z * target.y, z * target.x - x * target.z, x * target.y - y * target.x, reserve };
    }

    // Computes the length (magnitude) of a Vector3 object
    inline float length() const
    {
      return std::sqrt( x * x + y * y + z * z );
    }

    // Normalizes a Vector3 object
    inline Vector3 normalize() const
    {
      float len = length();
      return { x / len, y / len, z / len, reserve };
    }
  };

  struct Matrix33
  {
    float m[ 3 ][ 3 ];
  };
}// namespace Sapphire::Common