#include "conv.h"

namespace xiv::utils::conv
{

  float half2float( const uint16_t i_value )
  {
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;

    t1 = i_value & 0x7fff;                  // Non-sign bits
    t2 = i_value & 0x8000;                  // Sign bit
    t3 = i_value & 0x7c00;                  // Exponent
    t1 <<= 13;                              // Align mantissa on MSB
    t2 <<= 16;                              // Shift sign bit into position

    t1 += 0x38000000;                       // Adjust bias

    t1 = ( t3 == 0 ? 0 : t1 );              // Denormals-as-zero

    t1 |= t2;                               // Re-insert sign bit

    return *reinterpret_cast< float* >( &t1 );
  }

  float ubyte2float( const uint8_t i_value )
  {
    return i_value / 255.0f;
  }

}

