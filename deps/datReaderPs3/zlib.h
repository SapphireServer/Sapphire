#ifndef XIV_UTILS_ZLIB_H
#define XIV_UTILS_ZLIB_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace xivps3::utils::zlib
{

  void compress( const std::vector< char >& in, std::vector< char >& out );

  void no_header_decompress( uint8_t* in, size_t in_size, uint8_t* out, size_t out_size );

}

#endif // XIV_UTILS_ZLIB_H
