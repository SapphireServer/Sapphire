#ifndef XIV_UTILS_CONV_H
#define XIV_UTILS_CONV_H

#include <cstdint>
#include <vector>
#include <ostream>

namespace xivps3::utils::conv
{
  float half2float( const uint16_t i_value );

  float ubyte2float( const uint8_t i_value );
}

#endif // XIV_UTILS_CONV_H
