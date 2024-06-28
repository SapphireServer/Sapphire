#include "Exd.h"

#include "bparse.h"
#include "Exh.h"

using xiv::utils::bparse::extract;


namespace xiv::exd
{
  struct ExdHeader
  {
    char magic[0x4];
    uint16_t unknown;
    uint16_t unknown2;
    uint32_t index_size;
  };

  struct ExdRecordIndex
  {
    uint32_t id;
    uint32_t offset;
  };
}

namespace xiv::utils::bparse {
template<>
  inline void reorder< xiv::exd::ExdHeader >( xiv::exd::ExdHeader& i_struct )
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
  inline void reorder< xiv::exd::ExdRecordIndex >( xiv::exd::ExdRecordIndex& i_struct )
  {
    i_struct.id = xiv::utils::bparse::byteswap( i_struct.id );
    xiv::utils::bparse::reorder( i_struct.id );
    i_struct.offset = xiv::utils::bparse::byteswap( i_struct.offset );
    xiv::utils::bparse::reorder( i_struct.offset );
  }
};

namespace xiv::exd
{
  Exd::Exd( std::shared_ptr< Exh > exh, const std::vector< std::shared_ptr< dat::File > >& files )
  {
    _exh = exh;


    // Iterates over all the files
    for( auto& file : files )
    {
      std::vector< char > dataCpy = file->get_data_sections().front();

      // Extract the header
      auto exdHeader = extract< ExdHeader >( dataCpy, 0 );

      const uint32_t recordCount = exdHeader.index_size / sizeof( ExdRecordIndex );
      for( uint32_t i = 0; i < recordCount; ++i )
      {
        auto recordIndex = extract< ExdRecordIndex >( dataCpy, 32 + ( i * sizeof( ExdRecordIndex ) ) );
        _idCache[ recordIndex.id ] = ExdCacheEntry{ file, recordIndex.offset + 6, extract< uint8_t >( dataCpy, recordIndex.offset + 5 ) };
      }
    }
  }

  Exd::~Exd()
  {
  }

  const std::vector< Field > Exd::get_row( uint32_t id, uint32_t subRow )
  {

    auto cacheEntryIt = _idCache.find( id );
    if( cacheEntryIt == _idCache.end() || subRow >= cacheEntryIt->second.subRows )
      throw std::runtime_error( "Id + SubId combination not found: " + std::to_string( id ) + "." + std::to_string( subRow ) );

    auto dataCpy = cacheEntryIt->second.file->get_data_sections().front();

    std::vector< Field > fields;
    fields.reserve( _exh->get_members().size() );

    uint32_t baseOffset = cacheEntryIt->second.offset + ( subRow * _exh->get_header().data_offset + 2 * ( subRow + 1 ) );

    for( auto& memberEntry : _exh->get_exh_members() )
    {
      // Switch depending on the type to extract
      switch( memberEntry.type )
      {
        case DataType::string:
          // Extract the offset to the actual string
          // Then extract the actual string from that offset
        {
          throw std::runtime_error( "String not implemented for variant 2!" );
          //auto string_offset = extract<uint32_t>( iss, "string_offset", false );
          //iss.seekg( cacheEntryIt->second.offset + 6 + _exh->get_header().data_offset + string_offset );
          //fields.emplace_back( utils::bparse::extract_cstring( iss, "string" ) );
        }
          break;

        case DataType::boolean:
          fields.emplace_back( extract< bool >( dataCpy, baseOffset + memberEntry.offset ) );
          break;

        case DataType::int8:
          fields.emplace_back( extract< int8_t >( dataCpy, baseOffset + memberEntry.offset ) );
          break;

        case DataType::uint8:
          fields.emplace_back( extract< uint8_t >( dataCpy, baseOffset + memberEntry.offset ) );
          break;

        case DataType::int16:
          fields.emplace_back( extract< int16_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
          break;

        case DataType::uint16:
          fields.emplace_back( extract< uint16_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
          break;

        case DataType::int32:
          fields.emplace_back( extract< int32_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
          break;

        case DataType::uint32:
          fields.emplace_back( extract< uint32_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
          break;

        case DataType::float32:
          fields.emplace_back( extract< float >( dataCpy, baseOffset + memberEntry.offset, false ) );
          break;

        case DataType::uint64:
          fields.emplace_back( extract< uint64_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
          break;

        default:
          auto type = static_cast< uint16_t >( memberEntry.type );
          if( type < 0x19 || type > 0x20 )
            throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
          fields.emplace_back( ( extract< uint8_t >( dataCpy, baseOffset + memberEntry.offset ) & ( 1 << ( type - 0x19 ) ) ) != 0 );
          break;
      }
    }
    return fields;

  }


  const std::vector< Field > Exd::get_row( uint32_t id )
  {

    auto cacheEntryIt = _idCache.find( id );
    if( cacheEntryIt == _idCache.end() )
      throw std::runtime_error( "Id not found: " + std::to_string( id ) );

    auto dataCpy = cacheEntryIt->second.file->get_data_sections().front();

    std::vector< Field > fields;
    fields.reserve( _exh->get_members().size() );

    auto stringBaseOffset = cacheEntryIt->second.offset + _exh->get_header().data_offset;

    for( auto& memberEntry : _exh->get_exh_members() )
    {
      // Switch depending on the type to extract
      switch( memberEntry.type )
      {
        case DataType::string:
          // Extract the offset to the actual string
          // Then extract the actual string from that offset
        {
          auto stringOffset = extract< uint32_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false );
          fields.emplace_back( utils::bparse::extract_cstring( dataCpy, stringBaseOffset + stringOffset ) );
        }
          break;

        case DataType::boolean:
          fields.emplace_back( extract< bool >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset ) );
          break;

        case DataType::int8:
          fields.emplace_back( extract< int8_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset ) );
          break;

        case DataType::uint8:
          fields.emplace_back( extract< uint8_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset ) );
          break;

        case DataType::int16:
          fields.emplace_back( extract< int16_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false ) );
          break;

        case DataType::uint16:
          fields.emplace_back( extract< uint16_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false ) );
          break;

        case DataType::int32:
          fields.emplace_back( extract< int32_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false ) );
          break;

        case DataType::uint32:
          fields.emplace_back( extract< uint32_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false ) );
          break;

        case DataType::float32:
          fields.emplace_back( extract< float >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false ) );
          break;

        case DataType::uint64:
          fields.emplace_back( extract< uint64_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset, false ) );
          break;

        default:
          auto type = static_cast< uint16_t >( memberEntry.type );
          if( type < 0x19 || type > 0x20 )
            throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
          fields.emplace_back( ( extract< uint8_t >( dataCpy, cacheEntryIt->second.offset + memberEntry.offset ) & ( 1 << ( type - 0x19 ) ) ) != 0 );
          break;
      }
    }
    return fields;

  }

  // Get all rows
  const std::map< ExdRow, std::vector< Field >, exdRowSort > Exd::get_rows()
  {
    std::map< ExdRow, std::vector< Field >, exdRowSort > data;

    // Iterates over all the cached ids
    const uint32_t memberCount = _exh->get_members().size();
    for( auto& cacheEntry : _idCache )
    {
      std::vector< char > dataCpy = cacheEntry.second.file->get_data_sections().front();

      auto baseOffset = cacheEntry.second.offset;
      auto stringBaseOffset = baseOffset + _exh->get_header().data_offset;

      for( int32_t i = 0; i < cacheEntry.second.subRows; i++ )
      {
        // Get the vector fields for the given record and preallocate it
        ExdRow row = { cacheEntry.first, static_cast< uint8_t >( i ) };
        auto& fields = data[ row ];
        fields.reserve( memberCount );

        if( _exh->get_header().variant == 2 )
          baseOffset = cacheEntry.second.offset + ( i * _exh->get_header().data_offset + 2 * ( i + 1 ) );

        for( auto& memberEntry : _exh->get_exh_members() )
          //for( auto& member_entry : _exh->get_members() )
        {
          // Switch depending on the type to extract
          switch( memberEntry.type )
          {
            case DataType::string:
              // Extract the offset to the actual string
              // Then extract the actual string from that offset
            {
              if( _exh->get_header().variant == 1 )
              {
                auto stringOffset = extract< uint32_t >( dataCpy, baseOffset + memberEntry.offset, false );
                fields.emplace_back( utils::bparse::extract_cstring( dataCpy, stringBaseOffset + stringOffset ) );
              }
              else if( _exh->get_header().variant == 2 )
              {
                throw std::runtime_error( "String not implemented for variant 2!" );
              }
            }
              break;

            case DataType::boolean:
              fields.emplace_back( extract< bool >( dataCpy, baseOffset + memberEntry.offset ) );
              break;

            case DataType::int8:
              fields.emplace_back( extract< int8_t >( dataCpy, baseOffset + memberEntry.offset ) );
              break;

            case DataType::uint8:
              fields.emplace_back( extract< uint8_t >( dataCpy, baseOffset + memberEntry.offset ) );
              break;

            case DataType::int16:
              fields.emplace_back( extract< int16_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
              break;

            case DataType::uint16:
              fields.emplace_back( extract< uint16_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
              break;

            case DataType::int32:
              fields.emplace_back( extract< int32_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
              break;

            case DataType::uint32:
              fields.emplace_back( extract< uint32_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
              break;

            case DataType::float32:
              fields.emplace_back( extract< float >( dataCpy, baseOffset + memberEntry.offset, false ) );
              break;

            case DataType::uint64:
              fields.emplace_back( extract< uint64_t >( dataCpy, baseOffset + memberEntry.offset, false ) );
              break;

            default:
              auto type = static_cast< uint16_t >( memberEntry.type );
              if( type < 0x19 || type > 0x20 )
                throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
              fields.emplace_back( ( extract< uint8_t >( dataCpy, baseOffset + memberEntry.offset ) & ( 1 << ( type - 0x19 ) ) ) != 0 );
              break;
          }
        }
      }
    }
    return data;

  }

}

