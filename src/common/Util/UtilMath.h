#ifndef _UTILMATH_H
#define _UTILMATH_H

#include "Common.h"

#define PI 3.14159265358979323846f

namespace Sapphire::Common::Util
{
  // Computes the squared distance between two 3D points (x, y, z) and (x1, y1, z1)
  float distanceSq( float x, float y, float z, float x1, float y1, float z1 );

  // Computes the distance between two 3D points (x, y, z) and (x1, y1, z1)
  float distance( float x, float y, float z, float x1, float y1, float z1 );

  // Computes the distance between two 3D positions using FFXIVARR_POSITION3 structures
  float distance( const Common::FFXIVARR_POSITION3& pos1, const Common::FFXIVARR_POSITION3& pos2 );

  // Computes the squared distance between two 2D points (x, y) and (x1, y1)
  float distance2DSq( float x, float y, float x1, float y1 );

  // Computes the distance between two 2D points (x, y) and (x1, y1)
  float distance2D( float x, float y, float x1, float y1 );

  // Calculates the angle (in radians) to a point (x1, y1) from a point (x, y)
  float calcAngTo( float x, float y, float x1, float y1 );

  // Calculates the angle (in radians) from a point (x1, y1) to a point (x, y)
  float calcAngFrom( float x, float y, float x1, float y1 );

  // Truncates a floating-point value to a specified number of digits
  float trunc( float value, uint8_t digitsToRemain );

  // Converts a float to a uint16_t
  uint16_t floatToUInt16( float val );

  // Converts a float to a uint16_t representing a rotation angle
  uint16_t floatToUInt16Rot( float val );

  // Converts a float to a uint8_t representing a rotation angle
  uint8_t floatToUInt8Rot( float val );

  // Clamps a value between a minimum and maximum value
  template < typename T >
  T clamp( T val, T minimum, T maximum )
  {
    if( val > maximum )
      return maximum;

    if( val < minimum )
      return minimum;

    return val;
  }

  // Transforms a 3D position vector using a 3x3 matrix
  FFXIVARR_POSITION3 transform( const FFXIVARR_POSITION3& vector, const Matrix33& matrix );

  // Converts a 3D position representing Euler angles to a direction
  float eulerToDirection( const FFXIVARR_POSITION3& euler );
}

#endif
