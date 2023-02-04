#include "Dat.h"

#include "zlib.h"

#include "File.h"

namespace {
  const uint32_t model_section_count = 0xB;
}

namespace xivps3::dat
{
  struct DatFileHeader
  {
    uint32_t size;
    FileType entry_type;
    uint32_t total_uncompressed_size;
    uint32_t unknown[0x2];
  };

  struct DatBlockRecord
  {
    uint32_t offset;
    uint32_t size;
    uint32_t unknown[0x4];
    SqPackBlockHash block_hash;
  };

  struct DatBlockHeader
  {
    uint32_t size;
    uint32_t unknown1;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
  };

  struct DatStdFileBlockInfos
  {
    uint32_t offset;
    uint16_t size;
    uint16_t uncompressed_size;
  };

  struct DatMdlFileBlockInfos
  {
    uint32_t unknown1;
    uint32_t uncompressed_sizes[::model_section_count];
    uint32_t compressed_sizes[::model_section_count];
    uint32_t offsets[::model_section_count];
    uint16_t block_ids[::model_section_count];
    uint16_t block_counts[::model_section_count];
    uint32_t unknown2[0x2];
  };

  struct DatTexFileBlockInfos
  {
    uint32_t offset;
    uint32_t size;
    uint32_t uncompressed_size;
    uint32_t block_id;
    uint32_t block_count;
  };
}

namespace xivps3::utils::bparse
{
  template<>
  inline void reorder< xivps3::dat::DatFileHeader >( xivps3::dat::DatFileHeader& i_struct )
  {
    xivps3::utils::bparse::reorder( i_struct.size );
    xivps3::utils::bparse::reorder( i_struct.entry_type );
    xivps3::utils::bparse::reorder( i_struct.total_uncompressed_size );
    i_struct.size = xivps3::utils::bparse::byteswap( i_struct.size );
    i_struct.entry_type = xivps3::utils::bparse::byteswap( i_struct.entry_type );
    i_struct.total_uncompressed_size = xivps3::utils::bparse::byteswap( i_struct.total_uncompressed_size );
    for( int32_t i = 0; i < 0x2; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.unknown[ i ] );
    }
  }

  template<>
  inline void reorder< xivps3::dat::DatBlockRecord >( xivps3::dat::DatBlockRecord& i_struct )
  {
    i_struct.offset = xivps3::utils::bparse::byteswap( i_struct.offset );
    i_struct.size = xivps3::utils::bparse::byteswap( i_struct.size );
    for( int32_t i = 0; i < 0x4; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.unknown[ i ] );
    }
    xivps3::utils::bparse::reorder( i_struct.block_hash );
  }

  template<>
  inline void reorder< xivps3::dat::DatBlockHeader >( xivps3::dat::DatBlockHeader& i_struct )
  {
    xivps3::utils::bparse::reorder( i_struct.size );
    xivps3::utils::bparse::reorder( i_struct.unknown1 );
    xivps3::utils::bparse::reorder( i_struct.compressed_size );
    xivps3::utils::bparse::reorder( i_struct.uncompressed_size );

    i_struct.size = xivps3::utils::bparse::byteswap( i_struct.size );
    i_struct.unknown1 = xivps3::utils::bparse::byteswap( i_struct.unknown1 );
    i_struct.compressed_size = xivps3::utils::bparse::byteswap( i_struct.compressed_size );
    i_struct.uncompressed_size = xivps3::utils::bparse::byteswap( i_struct.uncompressed_size );
  }

  template<>
  inline void reorder< xivps3::dat::DatStdFileBlockInfos >( xivps3::dat::DatStdFileBlockInfos& i_struct )
  {
    xivps3::utils::bparse::reorder( i_struct.offset );
    xivps3::utils::bparse::reorder( i_struct.size );
    xivps3::utils::bparse::reorder( i_struct.uncompressed_size );

    i_struct.offset = xivps3::utils::bparse::byteswap( i_struct.offset );
    i_struct.size = xivps3::utils::bparse::byteswap( i_struct.size );
    i_struct.uncompressed_size = xivps3::utils::bparse::byteswap( i_struct.uncompressed_size );
  }

  template<>
  inline void reorder< xivps3::dat::DatMdlFileBlockInfos >( xivps3::dat::DatMdlFileBlockInfos& i_struct )
  {
    xivps3::utils::bparse::reorder( i_struct.unknown1 );
    for( auto i = 0; i < ::model_section_count; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.uncompressed_sizes[ i ] );
    }
    for( auto i = 0; i < ::model_section_count; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.compressed_sizes[ i ] );
    }
    for( auto i = 0; i < ::model_section_count; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.offsets[ i ] );
    }
    for( auto i = 0; i < ::model_section_count; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.block_ids[ i ] );
    }
    for( auto i = 0; i < ::model_section_count; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.block_counts[ i ] );
    }
    for( auto i = 0; i < 0x2; ++i )
    {
      xivps3::utils::bparse::reorder( i_struct.unknown2[ i ] );
    }
  }

  template<>
  inline void reorder< xivps3::dat::DatTexFileBlockInfos >( xivps3::dat::DatTexFileBlockInfos& i_struct )
  {
    xivps3::utils::bparse::reorder( i_struct.offset );
    xivps3::utils::bparse::reorder( i_struct.size );
    xivps3::utils::bparse::reorder( i_struct.uncompressed_size );
    xivps3::utils::bparse::reorder( i_struct.block_id );
    xivps3::utils::bparse::reorder( i_struct.block_count );
  }
}

using xivps3::utils::bparse::extract;

namespace xivps3::dat
{

  Dat::Dat( const std::filesystem::path& i_path, uint32_t i_nb ) :
    SqPack( i_path ),
    m_num( i_nb )
  {
    auto block_record = extract< DatBlockRecord >( m_handle );
    block_record.offset *= 0x80;
    isBlockValid( block_record.offset, block_record.size, block_record.block_hash );
  }

  Dat::~Dat()
  {
  }

  std::unique_ptr< File > Dat::getFile( uint32_t i_offset )
  {
    std::unique_ptr< File > outputFile( new File() );
    {
      // Lock in this scope
      std::lock_guard< std::mutex > lock( m_fileMutex );

      // Seek to the start of the header of the file record and extract it
      m_handle.seekg( i_offset );
      auto file_header = extract< DatFileHeader >( m_handle );

      switch( file_header.entry_type )
      {
        case FileType::empty:
          throw std::runtime_error( "File is empty" );

        case FileType::standard:
        {
          outputFile->_type = FileType::standard;

          auto number_of_blocks = extract< uint32_t >( m_handle, "number_of_blocks", false );

          // Just extract offset infos for the blocks to extract
          std::vector< DatStdFileBlockInfos > std_file_block_infos;
          extract< DatStdFileBlockInfos >( m_handle, number_of_blocks, std_file_block_infos );

          // Pre allocate data vector for the whole file
          outputFile->_data_sections.resize( 1 );
          auto& data_section = outputFile->_data_sections.front();

          data_section.reserve( file_header.total_uncompressed_size );
          // Extract each block
          for( auto& file_block_info : std_file_block_infos )
          {
            extractBlock( i_offset + file_header.size + file_block_info.offset, data_section );
          }
        }
          break;

        case FileType::model:
        {
          outputFile->_type = FileType::model;

          auto mdlBlockInfo = extract< DatMdlFileBlockInfos >( m_handle );

          // Getting the block number and read their sizes
          const uint32_t block_count = mdlBlockInfo.block_ids[ ::model_section_count - 1 ] +
                                       mdlBlockInfo.block_counts[ ::model_section_count - 1 ];
          std::vector< uint16_t > block_sizes;
          extract< uint16_t >( m_handle, "block_size", block_count, block_sizes );

          // Preallocate sufficient space
          outputFile->_data_sections.resize( ::model_section_count );

          for( uint32_t i = 0; i < ::model_section_count; ++i )
          {
            // Preallocating for section
            auto& data_section = outputFile->_data_sections[ i ];
            data_section.reserve( mdlBlockInfo.uncompressed_sizes[ i ] );

            uint32_t current_offset = i_offset + file_header.size + mdlBlockInfo.offsets[ i ];
            for( uint32_t j = 0; j < mdlBlockInfo.block_counts[ i ]; ++j )
            {
              extractBlock( current_offset, data_section );
              current_offset += block_sizes[ mdlBlockInfo.block_ids[ i ] + j ];
            }
          }
        }
          break;

        case FileType::texture:
        {
          outputFile->_type = FileType::texture;

          // Extracts mipmap entries and the block sizes
          auto sectionCount = extract< uint32_t >( m_handle, "sections_count" );

          std::vector< DatTexFileBlockInfos > texBlockInfo;
          extract< DatTexFileBlockInfos >( m_handle, sectionCount, texBlockInfo );

          // Extracting block sizes
          uint32_t block_count = texBlockInfo.back().block_id + texBlockInfo.back().block_count;
          std::vector< uint16_t > block_sizes;
          extract< uint16_t >( m_handle, "block_size", block_count, block_sizes );

          outputFile->_data_sections.resize( sectionCount + 1 );

          // Extracting header in section 0
          const uint32_t header_size = texBlockInfo.front().offset;
          auto& header_section = outputFile->_data_sections[ 0 ];
          header_section.resize( header_size );

          m_handle.seekg( i_offset + file_header.size );
          m_handle.read( header_section.data(), header_size );

          // Extracting other sections
          for( uint32_t i = 0; i < sectionCount; ++i )
          {
            auto& data_section = outputFile->_data_sections[ i + 1 ];
            auto& section_infos = texBlockInfo[ i ];
            data_section.reserve( section_infos.uncompressed_size );

            uint32_t current_offset = i_offset + file_header.size + section_infos.offset;
            for( uint32_t j = 0; j < section_infos.block_count; ++j )
            {
              extractBlock( current_offset, data_section );
              current_offset += block_sizes[ section_infos.block_id + j ];
            }
          }
        }
          break;

        default:
          throw std::runtime_error(
            "Invalid entry_type: " + std::to_string( static_cast<uint32_t>(file_header.entry_type) ) );
      }
    }

    return outputFile;
  }

  void Dat::extractBlock( uint32_t i_offset, std::vector< char >& o_data )
  {
    m_handle.seekg( i_offset );

    auto block_header = extract< DatBlockHeader >( m_handle );

    // Resizing the vector to write directly into it
    const uint32_t data_size = o_data.size();
    o_data.resize( data_size + block_header.uncompressed_size );

    // 32000 in compressed_size means it is not compressed so take uncompressed_size
    if( block_header.compressed_size == 32000 )
    {
      m_handle.read( o_data.data() + data_size, block_header.uncompressed_size );
    }
    else
    {
      // If it is compressed use zlib
      // Read the data to be decompressed
      std::vector< char > temp_buffer( block_header.compressed_size );
      m_handle.read( temp_buffer.data(), block_header.compressed_size );

      utils::zlib::no_header_decompress( reinterpret_cast<uint8_t*>(temp_buffer.data()),
                                         temp_buffer.size(),
                                         reinterpret_cast<uint8_t*>(o_data.data() + data_size),
                                         block_header.uncompressed_size );
    }
  }

  uint32_t Dat::getNum() const
  {
    return m_num;
  }

}
