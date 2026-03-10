#pragma once

#include <cmath>
#include <cassert>

namespace Sapphire::Common
{
  struct Vector3
  {
    float x{ 0 }, y{ 0 }, z{ 0 };

    // Constructors
    constexpr Vector3() = default;
    constexpr Vector3( float x, float y, float z ) : x( x ), y( y ), z( z ) {}

    // Pointer access for Detour API (e.g., &pos.x or pos.f())
    const float* f() const { return &x; }
    float* f() { return &x; }

    // Basic arithmetic
    Vector3 operator+( const Vector3& v ) const { return { x + v.x, y + v.y, z + v.z }; }
    Vector3 operator-( const Vector3& v ) const { return { x - v.x, y - v.y, z - v.z }; }
    Vector3 operator*( float scalar ) const { return { x * scalar, y * scalar, z * scalar }; }
    Vector3 operator/( float scalar ) const
    {
      assert( scalar != 0.0f );
      return { x / scalar, y / scalar, z / scalar };
    }

    // Vector Logic
    float lengthSq() const { return x * x + y * y + z * z; }
    float length() const { return std::sqrt( lengthSq() ); }

    Vector3 normalize() const
    {
      float len = length();
      return len > 0 ? *this * ( 1.0f / len ) : Vector3();
    }

    static float distance( const Vector3& a, const Vector3& b )
    {
      return ( a - b ).length();
    }
  };

  struct Matrix33
  {
    float m[ 3 ][ 3 ];
  };
}
