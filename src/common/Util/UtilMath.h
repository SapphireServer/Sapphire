#ifndef _UTILMATH_H
#define _UTILMATH_H

#include "Common.h"

#define PI 3.14159265358979323846f

namespace Sapphire::Common::Util
{

  float distanceSq( float x, float y, float z, float x1, float y1, float z1 );

  float distance( float x, float y, float z, float x1, float y1, float z1 );
  float distance( const Common::Vector3& pos1, const Common::Vector3& pos2 );

  float distance2DSq( float x, float y, float x1, float y1 );

  float distance2D( float x, float y, float x1, float y1 );

  float calcAngTo( float x, float y, float x1, float y1 );

  float calcAngFrom( float x, float y, float x1, float y1 );

  float trunc( float value, uint8_t digitsToRemain );

  uint16_t floatToUInt16( float val );

  uint16_t floatToUInt16Rot( float val );

  uint8_t floatToUInt8Rot( float val );

  float radiansToDegrees( float val );

  float degreesToRadians( float val );

  Vector3 getOffsettedPosition( const Vector3& pos, float rotation, float right, float up, float forward );

  Vector3 getKnockbackPosition( const Vector3& origin, const Vector3& pos, float distance );

  template < typename T >
  T clamp( T val, T minimum, T maximum )
  {
    if( val > maximum )
      return maximum;

    if( val < minimum )
      return minimum;

    return val;
  }

  Vector3 transform( const Vector3& vector, const Matrix33& matrix );

  float eulerToDirection( const Vector3& euler );

  float length( const Vector3& vec );

  Vector3 normalize( const Vector3& vec );
  
  float dot( const Vector3& vec1, const Vector3& vec2 );

  Vector3 projectY( const Vector3& vec );
}

#endif
