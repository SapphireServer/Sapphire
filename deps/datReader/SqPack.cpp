#include "SqPack.h"

namespace xiv::dat {
  enum PlatformId :
    uint8_t
  {
    Win32,
    PS3,
    PS4
  };

  struct SqPackHeader
  {
    char magic[0x8];
    PlatformId platformId;
    uint8_t padding0[3];
    uint32_t size;
    uint32_t version;
    uint32_t type;
  };

  struct SqPackIndexHeader
  {
    uint32_t size;
    uint32_t type;
  };
}

namespace xiv::utils:: bparse
{
  template<>
  inline void reorder< xiv::dat::SqPackHeader >( xiv::dat::SqPackHeader& i_struct )
  {
    for( int32_t i = 0; i < 0x8; ++i )
    {
      xiv::utils::bparse::reorder( i_struct.magic[ i ] );
    }
    xiv::utils::bparse::reorder( i_struct.platformId );
    xiv::utils::bparse::reorder( i_struct.size );
    xiv::utils::bparse::reorder( i_struct.version );
    xiv::utils::bparse::reorder( i_struct.type );
  }

  template<>
  inline void reorder< xiv::dat::SqPackIndexHeader >( xiv::dat::SqPackIndexHeader& i_struct )
  {
    xiv::utils::bparse::reorder( i_struct.size );
    xiv::utils::bparse::reorder( i_struct.type );
  }
}

using xiv::utils::bparse::extract;

namespace xiv::dat
{

  // Open the file
  SqPack::SqPack( const std::filesystem::path& path ) :
    m_handle( path.string(), std::ios_base::in | std::ios_base::binary )
  {
    // Extract the header
    extract< SqPackHeader >( m_handle );

    // Skip until the IndexHeader the extract it
    m_handle.seekg( 0x400 );
    extract< SqPackIndexHeader >( m_handle );
  }

  SqPack::~SqPack()
  {
  }

  void SqPack::isBlockValid( uint32_t i_offset, uint32_t i_size, const SqPackBlockHash& i_block_hash )
  {
    // TODO
  }

}
