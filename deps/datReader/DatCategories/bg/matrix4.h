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

  // Multiplies two 4x4 matrices and returns the result
  matrix4 operator*( const matrix4& rhs ) const
  {
    matrix4 ret;

    // Iterate through each row of the resulting matrix
    for( unsigned int row = 0; row < 4; row++ )
    {
      // Iterate through each column of the resulting matrix
      for( unsigned int col = 0; col < 4; col++ )
      {
        // Calculate the value for the current cell by summing the product of the corresponding row and column elements
        float value = 0;
        for( unsigned int k = 0; k < 4; k++ )
        {
          value += ( *this )( row, k ) * rhs( k, col );
        }

        // Assign the calculated value to the corresponding cell of the resulting matrix
        ret( row, col ) = value;
      }
    }

    return ret;
  }
};

#endif
