#ifndef XIV_DAT_SQPACK_H
#define XIV_DAT_SQPACK_H

#include <fstream>

#include <filesystem>

#include "bparse.h"


namespace xivps3::dat
{
  typedef uint64_t HashType64;
  struct SqPackBlockHash
  {
    HashType64 hash;
    uint8_t reserved[0x0B];
    uint32_t padding[0xB];
  };
}

namespace xivps3::utils::bparse
{
  template<>
  inline void reorder< xivps3::dat::SqPackBlockHash >( xivps3::dat::SqPackBlockHash& i_struct )
  {
    i_struct.hash = xivps3::utils::bparse::byteswap( i_struct.hash );
    for( auto i = 0; i < 0x14; ++i )
    {
    //  xivps3::utils::bparse::reorder( i_struct.hash[ i ] );

    }
    for( auto i = 0; i < 0xB; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.padding[ i ] );
    }
  }
};

namespace xivps3::dat
{

  class SqPack
  {

  public:
    // Full path to the sqpack file
    SqPack( const std::filesystem::path& i_path );

    virtual ~SqPack();

  protected:
    // Checks that a given block is valid iven its hash
    void isBlockValid( uint32_t i_offset, uint32_t i_size, const SqPackBlockHash& i_block_hash );

    // File handle
    std::ifstream m_handle;
  };

}

#endif // XIV_DAT_SQPACK_H
