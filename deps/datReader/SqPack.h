#pragma once

#include <fstream>

#include <filesystem>

#include "bparse.h"


namespace xiv::dat
{
  struct SqPackBlockHash
  {
    uint8_t hash[0x14];
    uint32_t padding[0xB];
  };
}// namespace xiv::dat

namespace xiv::utils::bparse
{
  template<>
  inline void reorder< xiv::dat::SqPackBlockHash >( xiv::dat::SqPackBlockHash& i_struct )
  {
    for( auto i = 0; i < 0x14; ++i )
    {
      xiv::utils::bparse::reorder( i_struct.hash[ i ] );
    }
    for( auto i = 0; i < 0xB; ++i )
    {
      xiv::utils::bparse::reorder( i_struct.padding[ i ] );
    }
  }
};// namespace xiv::utils::bparse

namespace xiv::dat
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

}// namespace xiv::dat
