#ifndef _MATRIX4_H
#define _MATRIX4_H

#include <cstdint>
#include <cmath>

// https://github.com/jpd002/Play--Framework/tree/master/include/math
struct matrix4
{
  // 4x4
  float grid[16];

  matrix4()
  {
    memset( &grid[ 0 ], 0, sizeof( grid ) );
  }

  float operator()( int row, int col ) const
  {
    return grid[ ( row * 4 ) + col ];
  }

  float& operator()( int row, int col )
  {
    return grid[ ( row * 4 ) + col ];
  }

  static matrix4 rotateX( float angle )
  {
    matrix4 ret = matrix4();
    ret( 0, 0 ) = 1.000000000f;
    ret( 1, 1 ) = cos( angle );
    ret( 1, 2 ) = -sin( angle );
    ret( 2, 1 ) = sin( angle );
    ret( 2, 2 ) = cos( angle );
    ret( 3, 3 ) = 1.000000000f;
    return ret;
  }

  static matrix4 rotateY( float angle )
  {
    matrix4 ret = matrix4();
    ret( 0, 0 ) = cos( angle );
    ret( 0, 2 ) = sin( angle );
    ret( 1, 1 ) = 1.000000000f;
    ret( 2, 0 ) = -sin( angle );
    ret( 2, 2 ) = cos( angle );
    ret( 3, 3 ) = 1.000000000f;
    return ret;
  }

  static matrix4 rotateZ( float angle )
  {
    matrix4 ret = matrix4();
    ret( 0, 0 ) = cos( angle );
    ret( 0, 1 ) = -sin( angle );
    ret( 1, 0 ) = sin( angle );
    ret( 1, 1 ) = cos( angle );
    ret( 2, 2 ) = 1.000000000f;
    ret( 3, 3 ) = 1.000000000f;
    return ret;
  }

  static matrix4 scale( float x, float y, float z )
  {
    matrix4 ret = matrix4();
    ret( 0, 0 ) = x;
    ret( 1, 1 ) = y;
    ret( 2, 2 ) = z;
    ret( 3, 3 ) = 1;

    return ret;
  }

  static matrix4 translate( float x, float y, float z )
  {
    matrix4 ret = matrix4();
    ret( 0, 0 ) = 1;
    ret( 1, 1 ) = 1;
    ret( 2, 2 ) = 1;
    ret( 3, 3 ) = 1;

    ret( 3, 0 ) = x;
    ret( 3, 1 ) = y;
    ret( 3, 2 ) = z;
    return ret;
  }

  matrix4 operator*( const matrix4& rhs ) const
  {
    matrix4 ret;
    for( unsigned int i = 0; i < 4; i++ )
    {
      ret( i, 0 ) =
        ( *this )( i, 0 ) * rhs( 0, 0 ) + ( *this )( i, 1 ) * rhs( 1, 0 ) + ( *this )( i, 2 ) * rhs( 2, 0 ) +
        ( *this )( i, 3 ) * rhs( 3, 0 );
      ret( i, 1 ) =
        ( *this )( i, 0 ) * rhs( 0, 1 ) + ( *this )( i, 1 ) * rhs( 1, 1 ) + ( *this )( i, 2 ) * rhs( 2, 1 ) +
        ( *this )( i, 3 ) * rhs( 3, 1 );
      ret( i, 2 ) =
        ( *this )( i, 0 ) * rhs( 0, 2 ) + ( *this )( i, 1 ) * rhs( 1, 2 ) + ( *this )( i, 2 ) * rhs( 2, 2 ) +
        ( *this )( i, 3 ) * rhs( 3, 2 );
      ret( i, 3 ) =
        ( *this )( i, 0 ) * rhs( 0, 3 ) + ( *this )( i, 1 ) * rhs( 1, 3 ) + ( *this )( i, 2 ) * rhs( 2, 3 ) +
        ( *this )( i, 3 ) * rhs( 3, 3 );
    }
    return ret;
  }
};

#endif
