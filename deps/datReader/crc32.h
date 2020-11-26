#ifndef XIV_UTILS_CRC32_H
#define XIV_UTILS_CRC32_H

#include <cstdint>
#include <vector>
#include <string>

namespace xiv::utils::crc32
{

  // Normal crc32 computation from a given intial crc value, use zlib.crc32 instead, the final XOR 0xFFFFFFFF is not done
  uint32_t compute( const std::string& i_input, uint32_t init_crc = 0xFFFFFFFF );

  // Computes the 4 missing bytes XXXX such as init_crc = crc32(prefix_string)
  // and string_to_find = prefix_string + XXXX + i_input
  uint32_t rev_compute( const std::string& i_input, uint32_t init_crc = 0 );

  void generate_hashes_1( std::string& i_format, const uint32_t i_first_index, std::vector< uint32_t >& o_hashes );

  void generate_hashes_2( std::string& i_format, const uint32_t i_first_index, const uint32_t i_second_index,
                          std::vector< uint32_t >& o_hashes );

}

#endif // XIV_UTILS_CRC32_H
