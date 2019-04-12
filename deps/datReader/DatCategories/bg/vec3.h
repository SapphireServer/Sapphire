#ifndef _VEC3_H
#define _VEC3_H

#include <cstdint>
#include "matrix4.h"

struct vec3
{
  float x, y, z;

  vec3()
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  vec3( float x, float y, float z )
  {
    this->x = x;
    this->y = y;
    this->z = z;
  };
};

static vec3 operator*( const vec3& lhs, const matrix4& rhs )
{
  vec3 ret;
  ret.x = rhs( 0, 0 ) * lhs.x + rhs( 0, 1 ) * lhs.y + rhs( 0, 2 ) * lhs.z;
  ret.y = rhs( 1, 0 ) * lhs.x + rhs( 1, 1 ) * lhs.y + rhs( 1, 2 ) * lhs.z;
  ret.z = rhs( 2, 0 ) * lhs.x + rhs( 2, 1 ) * lhs.y + rhs( 2, 2 ) * lhs.z;
  return ret;
};
#endif