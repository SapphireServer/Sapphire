#pragma once

#include <string>
#include <cstdint>

namespace Sapphire::Common::Util
{
  std::string base64Encode( uint8_t const*, uint32_t len );

  std::string base64Decode( const std::string& s );
}


