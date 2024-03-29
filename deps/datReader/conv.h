#pragma once

#include <cstdint>
#include <vector>
#include <ostream>

namespace xiv::utils::conv
{
  float half2float( const uint16_t i_value );

  float ubyte2float( const uint8_t i_value );
}

