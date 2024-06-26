#include <cmath>
#include "UtilMath.h"
#include "Common.h"
#include <cmath>

using namespace Sapphire::Common;

float Util::distanceSq( float x, float y, float z, float x1, float y1, float z1 )
{
  float deltaX = x - x1;
  float deltaY = y - y1;
  float deltaZ = z - z1;

  return ( deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ );
}

float Util::distance( float x, float y, float z, float x1, float y1, float z1 )
{
  return sqrtf( distanceSq( x, y, z, x1, y1, z1 ) );
}

float Util::distance( const Sapphire::Common::FFXIVARR_POSITION3& pos1,
                      const Sapphire::Common::FFXIVARR_POSITION3& pos2 )
{
  return sqrtf( distanceSq( pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z ) );
}

float Util::distance2DSq( float x, float y, float x1, float y1 )
{
  float deltaX = x - x1;
  float deltaY = y - y1;
  return ( deltaX * deltaX + deltaY * deltaY );
}

float Util::distance2D( float x, float y, float x1, float y1 )
{
  return sqrtf( distance2DSq( x, y, x1, y1 ) );
}

float Util::calcAngTo( float x, float y, float x1, float y1 )
{
  float dx = x1 - x;
  float dy = y1 - y;

  if( dx == 0.0f && dy == 0.0f )
    return 0.0f;

  if( dy != 0.0f )
  {
    return atan2( dy, dx );
  }
  else
  {
    return 0.0f;
  }
}

float Util::calcAngFrom( float x, float y, float x1, float y1 )
{
  float dx = x - x1;
  float dy = y - y1;

  if( dx == 0.0f && dy == 0.0f )
    return 0.0f;

  if( dy != 0.0f )
  {
    return atan2( dy, dx );
  }
  else
  {
    return 0.0f;
  }
}

uint16_t Util::floatToUInt16( float val )
{
  return static_cast< uint16_t >( ( ( val + 1000.0f ) * 100.0f ) * 0.32767501f );
}

uint16_t Util::floatToUInt16Rot( float val )
{
  return static_cast< uint16_t >( ( ( ( val + 3.1415927f ) * 100.f ) * 103.30219106f ) );
}

uint8_t Util::floatToUInt8Rot( float val )
{
  return static_cast< uint8_t >( 0x80 * ( ( val + PI ) ) / PI );
}

FFXIVARR_POSITION3 Util::getOffsettedPosition( const FFXIVARR_POSITION3& pos, float rot, float right, float up, float forward )
{
  FFXIVARR_POSITION3 ret{ pos };

  // height
  ret.y += up;

  // forward
  float angle = rot + ( PI / 2 );
  ret.x -= forward * cos( angle );
  ret.z += forward * sin( angle );

  // side
  ret.x -= right * cos( rot );
  ret.z += right * sin( rot );

  return ret;
}

FFXIVARR_POSITION3 Util::getKnockbackPosition( const FFXIVARR_POSITION3& origin, const FFXIVARR_POSITION3& pos, float distance )
{
  FFXIVARR_POSITION3 ret{ pos };

  float from = Common::Util::calcAngFrom( origin.x, origin.z, pos.x, pos.z );
  float angle = PI - from + ( PI / 2 );

  angle = angle + ( PI / 2 );
  ret.x -= distance * cos( angle );
  ret.z += distance * sin( angle );

  return ret;
}

FFXIVARR_POSITION3 Util::transform( const FFXIVARR_POSITION3& vector, const Matrix33& matrix )
{
  FFXIVARR_POSITION3 dst{};

  dst.x = vector.z * matrix.m[ 2 ][ 0 ] + vector.x * matrix.m[ 0 ][ 0 ] + vector.y * matrix.m[ 1 ][ 0 ];
  dst.y = vector.z * matrix.m[ 2 ][ 1 ] + vector.x * matrix.m[ 0 ][ 1 ] + vector.y * matrix.m[ 1 ][ 1 ];
  dst.z = vector.z * matrix.m[ 2 ][ 2 ] + vector.x * matrix.m[ 0 ][ 2 ] + vector.y * matrix.m[ 1 ][ 2 ];


  return dst;
}

float Util::eulerToDirection( const FFXIVARR_POSITION3 &euler )
{
  Matrix33 matrix;

  auto sinZ = sinf( euler.z );
  auto cosZ = cosf( euler.z );
  auto sinY = sinf( euler.y );
  auto cosY = cosf( euler.y );
  auto sinX = sinf( euler.x );
  auto cosX = cosf( euler.x );

  matrix.m[0][0] = cosZ * cosY;
  matrix.m[0][1] = sinZ * cosX;
  matrix.m[0][2] = sinZ * sinX + ( -cosZ * sinY ) * cosX;

  matrix.m[1][0] = -sinZ * cosY;
  matrix.m[1][1] = cosZ * cosX + ( -sinZ * sinY * sinX );
  matrix.m[1][2] = cosZ * sinX + sinZ * sinY * cosX;

  matrix.m[2][0] = sinY;
  matrix.m[2][1] = -cosY * sinX;
  matrix.m[2][2] = cosY * cosX;

  FFXIVARR_POSITION3 AXIS_Z{ 0.0f, 0.0f, 1.0f };
  auto result = transform( AXIS_Z, matrix );

  auto squared = result.z * result.z + result.x * result.x;
  auto v1{0.0f};
  auto v2{0.0f};

  if( squared > 0.00000011920929f )
  {
    auto ret = sqrtf( squared );
    ret = -( ( squared * ret ) * ret - 1.0f ) * ( 0.5f * ret ) + ret;
    ret = -( ( squared * ret ) * ret - 1.0f ) * ( 0.5f * ret ) + ret;
    v1 = result.z * ( -( ( ( squared * ret ) * ret ) - 1.0f ) * ( 0.5f * ret ) + ret );
    v2 = result.x * ( -( ( ( squared * ret ) * ret ) - 1.0f ) * ( 0.5f * ret ) + ret );
  }

  return atan2f( v2, v1 );
}

float Util::trunc( float value, uint8_t digitsToRemain )
{
  if( digitsToRemain == 0 )
    return std::floor( value );

  auto factor = static_cast< float >( std::pow( 10.f, digitsToRemain ) );

  return std::floor( value * factor ) / factor;
}
