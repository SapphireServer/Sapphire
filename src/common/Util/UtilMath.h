#ifndef _UTILMATH_H
#define _UTILMATH_H

#include "Common.h"

#define PI 3.14159265358979323846f

namespace Sapphire::Common::Util
{

  float distanceSq( float x, float y, float z, float x1, float y1, float z1 );

  float distance( float x, float y, float z, float x1, float y1, float z1 );
  float distance( const Common::FFXIVARR_POSITION3& pos1, const Common::FFXIVARR_POSITION3& pos2 );

  float distance2DSq( float x, float y, float x1, float y1 );

  float distance2D( float x, float y, float x1, float y1 );

  float calcAngTo( float x, float y, float x1, float y1 );

  float calcAngFrom( float x, float y, float x1, float y1 );

  float trunc( float value, uint8_t digitsToRemain );

  uint16_t floatToUInt16( float val );

  uint16_t floatToUInt16Rot( float val );

  uint8_t floatToUInt8Rot( float val );

  template < typename T >
  T clamp( T val, T minimum, T maximum )
  {
    if( val > maximum )
      return maximum;

    if( val < minimum )
      return minimum;

    return val;
  }

  FFXIVARR_POSITION3 transform( const FFXIVARR_POSITION3& vector, const Matrix33& matrix );

  float eulerToDirection( const FFXIVARR_POSITION3& euler );

  float length( const FFXIVARR_POSITION3& vec );

  FFXIVARR_POSITION3 normalize( const FFXIVARR_POSITION3& vec );
  
  float dot( const FFXIVARR_POSITION3& vec1, const FFXIVARR_POSITION3& vec2 );

  FFXIVARR_POSITION3 projectY( const FFXIVARR_POSITION3& vec );
}

#endif
