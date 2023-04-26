#pragma once

#include <map>
#include <memory>
#include <unordered_map>

#include <variant>

#include "Exd/Common.h"
#include "Exd/Structs.h"
#include "Exh.h"
#include "File.h"
#include "bparse.h"
#include "stream.h"
#include <fstream>

namespace xiv::exd
{
  struct ExdHeaderMinimal {
    char magic[ 0x4 ];
    uint16_t unknown;
    uint16_t unknown2;
    uint32_t index_size;
  };

  struct ExdRecordIndexData {
    uint32_t id;
    uint32_t offset;
  };
}// namespace xiv::exd

namespace xiv::utils::bparse
{
  template<>
  inline void reorder< xiv::exd::ExdHeaderMinimal >( xiv::exd::ExdHeaderMinimal& i_struct )
  {
    for( int32_t i = 0; i < 0x4; ++i )
    {
      xiv::utils::bparse::reorder( i_struct.magic[ i ] );
    }
    i_struct.unknown = xiv::utils::bparse::byteswap( i_struct.unknown );
    xiv::utils::bparse::reorder( i_struct.unknown );
    i_struct.unknown2 = xiv::utils::bparse::byteswap( i_struct.unknown2 );
    xiv::utils::bparse::reorder( i_struct.unknown2 );
    i_struct.index_size = xiv::utils::bparse::byteswap( i_struct.index_size );
    xiv::utils::bparse::reorder( i_struct.index_size );
  }

  template<>
  inline void reorder< xiv::exd::ExdRecordIndexData >( xiv::exd::ExdRecordIndexData& i_struct )
  {
    i_struct.id = xiv::utils::bparse::byteswap( i_struct.id );
    xiv::utils::bparse::reorder( i_struct.id );
    i_struct.offset = xiv::utils::bparse::byteswap( i_struct.offset );
    xiv::utils::bparse::reorder( i_struct.offset );
  }
};// namespace xiv::utils::bparse

namespace xiv::exd
{

  class Exh;

  // Field type containing all the possible types in the data files
  using Field = std::variant<
          std::string,
          bool,
          int8_t,
          uint8_t,
          int16_t,
          uint16_t,
          int32_t,
          uint32_t,
          float,
          uint64_t >;

  struct ExdCacheEntry
  {
    std::shared_ptr< dat::File > file;
    uint32_t offset;
  };

  // Data for a given language
  class Exd
  {
  public:
    // i_exh: the header
    // i_files: the multiple exd files
    Exd() = default;

    Exd( std::shared_ptr< Exh > i_exh, const std::vector< std::shared_ptr< dat::File > >& i_files );

    ~Exd() = default;

    // Get a row by its id
    const std::vector< Field > get_row( uint32_t id );

    template< typename T >
    std::shared_ptr< Excel::ExcelStruct< T > > get_row( uint32_t id )
    {
      using namespace xiv::utils;
      auto cacheEntryIt = _idCache.find( id );
      if( cacheEntryIt == _idCache.end() )
        throw std::out_of_range( "Id not found: " + std::to_string( id ) );

      if( sizeof( T ) != _exh->get_header().data_offset )
      {
        throw std::runtime_error( "the struct size (" + std::to_string( sizeof( T ) ) + ") doesn't match the size in the header (" +
                std::to_string( _exh->get_header().data_offset ) + ")!" );
      }

      // Iterates over all the files
      const uint32_t member_count = static_cast< uint32_t >( _exh->get_members().size() );
      auto& file_ptr = cacheEntryIt->second.file;

      std::vector< char > dataCpy = file_ptr->get_data_sections().front();
      std::istringstream iss( std::string( dataCpy.begin(), dataCpy.end() ) );

      auto pSheet = std::make_shared< Excel::ExcelStruct< T > >();

      // Get the vector fields for the given record and preallocate it
      auto fields = _data[ id ];
      fields.reserve( member_count );
      iss.seekg( cacheEntryIt->second.offset + 6 );

      iss.read( reinterpret_cast< char* >( &pSheet.get()->_data ), sizeof( T ) );

      int stringCount = 0;
      for( auto& member_entry : _exh->get_exh_members() )
      {

        // Seek to the position of the member to extract.
        // 6 is because we have uint32_t/uint16_t at the start of each record
        iss.seekg( cacheEntryIt->second.offset + 6 + member_entry.offset );

        // Switch depending on the type to extract
        switch( member_entry.type )
        {
          case DataType::string:
            // Extract the offset to the actual string
            // Seek to it then extract the actual string
            {
              auto string_offset = bparse::extract< uint32_t >( iss, "string_offset", false );
              iss.seekg( cacheEntryIt->second.offset + 6 + _exh->get_header().data_offset + string_offset );
              std::string value = utils::bparse::extract_cstring( iss, "string" );
              auto it = pSheet->_strings.insert( pSheet->_strings.end(), value );
              *reinterpret_cast< uint32_t* >( pSheet->ptr() + member_entry.offset ) =
                      static_cast< uint32_t >( std::distance( pSheet->_strings.begin(), it ) );
            }
            break;

          case DataType::boolean:
            bparse::extract< bool >( iss, "bool" );
            break;

          case DataType::int8:
            bparse::extract< int8_t >( iss, "int8_t" );
            break;

          case DataType::uint8:
            bparse::extract< uint8_t >( iss, "uint8_t" );
            break;


          case DataType::int16:
          {
            int16_t value = bparse::extract< int16_t >( iss, "int16_t", false );
            *reinterpret_cast< int16_t* >( pSheet->ptr() + member_entry.offset ) = value;
          }
          break;

          case DataType::uint16:
          {
            uint16_t value = bparse::extract< uint16_t >( iss, "uint16_t", false );
            *reinterpret_cast< uint16_t* >( pSheet->ptr() + member_entry.offset ) = value;
          }
          break;

          case DataType::int32:
          {
            int32_t value = bparse::extract< int32_t >( iss, "int32_t", false );
            *reinterpret_cast< int32_t* >( pSheet->ptr() + member_entry.offset ) = value;
          }
          break;

          case DataType::uint32:
          {
            uint32_t value = bparse::extract< uint32_t >( iss, "uint32_t", false );
            *reinterpret_cast< uint32_t* >( pSheet->ptr() + member_entry.offset ) = value;
          }
          break;

          case DataType::float32:
          {
            float value = bparse::extract< float >( iss, "float", false );
            *reinterpret_cast< float* >( pSheet->ptr() + member_entry.offset ) = value;
          }
          break;

          case DataType::uint64:
          {
            uint64_t value = bparse::extract< uint64_t >( iss, "uint64_t", false );
            *reinterpret_cast< uint64_t* >( pSheet->ptr() + member_entry.offset ) = value;
          }
          break;

          default:
            auto type = static_cast< uint16_t >( member_entry.type );
            if( type < 0x19 || type > 0x20 )
              throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
            uint64_t val = bparse::extract< uint64_t >( iss, "bool" );
            int32_t shift = type - 0x19;
            int32_t i = 1 << shift;
            val &= i;
            fields.emplace_back( ( val & i ) == i );
            break;
        }
      }

      return pSheet;
    }

    // Get a row by its id and sub-row
    const std::vector< Field > get_row( uint32_t id, uint32_t subRow );

    // Get all rows
    const std::map< uint32_t, std::vector< Field > >& get_rows();

    // Get all rows
    template< typename T >
    const std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< T > > > get_sheet_rows()
    {
      std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< T > > > sheets;

      // Iterates over all the files
      const uint32_t member_count = static_cast< uint32_t >( _exh->get_members().size() );
      for( auto& file_ptr : _files )
      {
        // Get a stream
        std::vector< char > dataCpy = file_ptr->get_data_sections().front();
        std::istringstream iss( std::string( dataCpy.begin(), dataCpy.end() ) );

        // Extract the header and skip to the record indices
        auto exd_header = xiv::utils::bparse::extract< ExdHeaderMinimal >( iss );
        iss.seekg( 0x20 );

        // Preallocate and extract the record_indices
        const uint32_t record_count = exd_header.index_size / sizeof( ExdRecordIndexData );
        std::vector< ExdRecordIndexData > record_indices;
        record_indices.reserve( record_count );
        for( uint32_t i = 0; i < record_count; ++i )
        {
          record_indices.emplace_back( xiv::utils::bparse::extract< ExdRecordIndexData >( iss ) );
        }

        for( auto& record_index : record_indices )
        {
          auto cacheEntryIt = _idCache.find( record_index.id );
          if( cacheEntryIt == _idCache.end() )
            throw std::out_of_range( "Id not found: " + std::to_string( record_index.id ) );

          auto pSheet = std::make_shared< Excel::ExcelStruct< T > >();

          // Get the vector fields for the given record and preallocate it
          auto fields = _data[ record_index.id ];
          fields.reserve( member_count );
          iss.seekg( cacheEntryIt->second.offset + 6 );

          iss.read( reinterpret_cast< char* >( &pSheet.get()->_data ), sizeof( T ) );

          int stringCount = 0;
          for( auto& member_entry : _exh->get_exh_members() )
          {

            // Seek to the position of the member to extract.
            // 6 is because we have uint32_t/uint16_t at the start of each record
            iss.seekg( cacheEntryIt->second.offset + 6 + member_entry.offset );

            // Switch depending on the type to extract
            switch( member_entry.type )
            {
              case DataType::string:
                // Extract the offset to the actual string
                // Seek to it then extract the actual string
                {
                  auto string_offset = xiv::utils::bparse::extract< uint32_t >( iss, "string_offset", false );
                  iss.seekg( cacheEntryIt->second.offset + 6 + _exh->get_header().data_offset + string_offset );
                  std::string value = xiv::utils::bparse::extract_cstring( iss, "string" );
                  auto it = pSheet->_strings.insert( pSheet->_strings.end(), value );
                  *reinterpret_cast< uint32_t* >( pSheet->ptr() + member_entry.offset ) =
                          static_cast< uint32_t >( std::distance( pSheet->_strings.begin(), it ) );
                }
                break;

              case DataType::boolean:
                xiv::utils::bparse::extract< bool >( iss, "bool" );
                break;

              case DataType::int8:
                xiv::utils::bparse::extract< int8_t >( iss, "int8_t" );
                break;

              case DataType::uint8:
                xiv::utils::bparse::extract< uint8_t >( iss, "uint8_t" );
                break;


              case DataType::int16:
              {
                int16_t value = xiv::utils::bparse::extract< int16_t >( iss, "int16_t", false );
                *reinterpret_cast< int16_t* >( pSheet->ptr() + member_entry.offset ) = value;
              }
              break;

              case DataType::uint16:
              {
                uint16_t value = xiv::utils::bparse::extract< uint16_t >( iss, "uint16_t", false );
                *reinterpret_cast< uint16_t* >( pSheet->ptr() + member_entry.offset ) = value;
              }
              break;

              case DataType::int32:
              {
                int32_t value = xiv::utils::bparse::extract< int32_t >( iss, "int32_t", false );
                *reinterpret_cast< int32_t* >( pSheet->ptr() + member_entry.offset ) = value;
              }
              break;

              case DataType::uint32:
              {
                uint32_t value = xiv::utils::bparse::extract< uint32_t >( iss, "uint32_t", false );
                *reinterpret_cast< uint32_t* >( pSheet->ptr() + member_entry.offset ) = value;
              }
              break;

              case DataType::float32:
              {
                float value = xiv::utils::bparse::extract< float >( iss, "float", false );
                *reinterpret_cast< float* >( pSheet->ptr() + member_entry.offset ) = value;
              }
              break;

              case DataType::uint64:
              {
                uint64_t value = xiv::utils::bparse::extract< uint64_t >( iss, "uint64_t", false );
                *reinterpret_cast< uint64_t* >( pSheet->ptr() + member_entry.offset ) = value;
              }
              break;

              default:
                auto type = static_cast< uint16_t >( member_entry.type );
                if( type < 0x19 || type > 0x20 )
                  throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
                uint64_t val = xiv::utils::bparse::extract< uint64_t >( iss, "bool" );
                int32_t shift = type - 0x19;
                int32_t i = 1 << shift;
                val &= i;
                fields.emplace_back( ( val & i ) == i );
                break;
            }
          }

          sheets[ record_index.id ] = pSheet;
        }
      }

      return sheets;
    }

  protected:
    // Data indexed by the ID of the row, the vector is field with the same order as exh.members
    std::map< uint32_t, std::vector< Field > > _data;
    std::vector< std::shared_ptr< dat::File > > _files;
    std::shared_ptr< Exh > _exh;
    std::map< uint32_t, ExdCacheEntry > _idCache;
  };

}// namespace xiv::exd