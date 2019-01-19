#include <string>

namespace Sapphire::Util
{
  std::string base64_encode( uint8_t const*, uint32_t len );

  std::string base64_decode( const std::string& s );
}


