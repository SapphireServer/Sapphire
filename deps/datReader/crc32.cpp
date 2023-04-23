#include "crc32.h"

#include <array>
#include <string>

#include <zlib/zlib.h>

namespace internal
{
  using CrcTable = std::array< uint32_t, 0x100 >;

  constexpr CrcTable build_crc_table()
  {
    CrcTable crc_table{};
    for( size_t i = 0; i < 0x100; ++i )
    {
      uint32_t crc = i;
      for( size_t j = 0; j < 8; ++j )
      {
        crc = ( crc & 1 ) ? ( 0xEDB88320 ^ ( crc >> 1 ) ) : ( crc >> 1 );
      }
      crc_table[ i ] = crc;
    }
    return crc_table;
  }

  constexpr CrcTable build_rev_crc_table()
  {
    CrcTable rev_crc_table{};
    auto crc_table = build_crc_table();
    for( size_t i = 0; i < 0x100; ++i )
    {
      uint32_t crc = crc_table[ i ];
      rev_crc_table[ crc >> 24 ] = i + ( ( crc & 0xFFFFFF ) << 8 );
    }
    return rev_crc_table;
  }

  constexpr CrcTable crc_table = build_crc_table();
  constexpr CrcTable rev_crc_table = build_rev_crc_table();
}// namespace internal

namespace xiv::utils::crc32
{
  uint32_t compute( const std::string& i_input, uint32_t init_crc )
  {
    auto& crc_table = internal::crc_table;
    uint32_t crc = init_crc;
    for( size_t i = 0; i < i_input.size(); ++i )
    {
      crc = crc_table[ ( crc ^ i_input[ i ] ) & 0xFF ] ^ ( crc >> 8 );
    }
    return crc;
  }

  uint32_t rev_compute( const std::string& i_input, uint32_t init_crc )
  {
    auto& rev_crc_table = internal::rev_crc_table;
    uint32_t crc = init_crc;
    const auto input_size = i_input.size();
    for( size_t i = input_size; i > 0; --i )
    {
      crc = rev_crc_table[ crc >> 24 ] ^ ( ( crc << 8 ) & 0xFFFFFF00 ) ^ i_input[ input_size - i - 1 ];
    }
    for( size_t i = 0; i < 4; ++i )
    {
      crc = rev_crc_table[ crc >> 24 ] ^ ( ( crc << 8 ) & 0xFFFFFF00 );
    }
    return crc;
  }

  void generate_hashes_1( std::string& i_format, const uint32_t i_first_index, std::array< uint32_t, 10000 >& o_hashes )
  {
    const auto str_size = static_cast< uInt >( i_format.size() );

    uint32_t i = 0;
    for( char a = '0'; a <= '9'; ++a )
    {
      i_format[ i_first_index ] = a;
      for( char b = '0'; b <= '9'; ++b )
      {
        i_format[ i_first_index + 1 ] = b;
        for( char c = '0'; c <= '9'; ++c )
        {
          i_format[ i_first_index + 2 ] = c;
          for( char d = '0'; d <= '9'; ++d )
          {
            i_format[ i_first_index + 3 ] = d;
            o_hashes[ i ] = ::crc32( 0, reinterpret_cast< const Bytef* >( i_format.data() ), str_size ) ^ 0xFFFFFFFF;
            ++i;
          }
        }
      }
    }
  }

  void generate_hashes_2( std::string& i_format, const uint32_t i_first_index, const uint32_t i_second_index,
                          std::array< uint32_t, 100000000 >& o_hashes )
  {
    const auto str_size = static_cast< uInt >( i_format.size() );

    uint32_t i = 0;
    for( char a = '0'; a <= '9'; ++a )
    {
      i_format[ i_first_index ] = a;
      for( char b = '0'; b <= '9'; ++b )
      {
        i_format[ i_first_index + 1 ] = b;
        for( char c = '0'; c <= '9'; ++c )
        {
          i_format[ i_first_index + 2 ] = c;
          for( char d = '0'; d <= '9'; ++d )
          {
            i_format[ i_first_index + 3 ] = d;
            for( char e = '0'; e <= '9'; ++e )
            {
              i_format[ i_second_index ] = e;
              for( char f = '0'; f <= '9'; ++f )
              {
                i_format[ i_second_index + 1 ] = f;
                for( char g = '0'; g <= '9'; ++g )
                {
                  i_format[ i_second_index + 2 ] = g;
                  for( char h = '0'; h <= '9'; ++h )
                  {
                    i_format[ i_second_index + 3 ] = h;
                    o_hashes[ i ] = ::crc32( 0, reinterpret_cast< const Bytef* >( i_format.data() ), str_size ) ^ 0xFFFFFFFF;
                    ++i;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

}// namespace xiv::utils::crc32