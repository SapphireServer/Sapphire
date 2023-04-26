#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace xiv::utils::zlib
{

  void compress( const std::vector< char >& in, std::vector< char >& out );

  void no_header_decompress( const uint8_t* in, size_t in_size, uint8_t* out, size_t out_size );

} // namespace xiv::utils::zlib
