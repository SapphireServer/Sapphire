#include "Exd.h"

#include "bparse.h"
#include "stream.h"
#include <fstream>
#include "Exh.h"

using xiv::utils::bparse::extract;

namespace xiv::exd
{
  Exd::Exd( std::shared_ptr< Exh > i_exh, const std::vector< std::shared_ptr< dat::File>>& i_files )
  {
    _exh = i_exh;
    _files = i_files;


    // Iterates over all the files
    const uint32_t member_count = static_cast< uint32_t >( _exh->get_members().size() );
    for( auto& file_ptr : _files )
    {
      // Get a stream
      std::vector< char > dataCpy = file_ptr->get_data_sections().front();
      std::istringstream iss( std::string( dataCpy.begin(), dataCpy.end() ) );

      // Extract the header and skip to the record indices
      auto exd_header = extract< ExdHeaderMinimal >( iss );
      iss.seekg( 0x20 );

      // Preallocate and extract the record_indices
      const uint32_t record_count = exd_header.index_size / sizeof( ExdRecordIndexData );
      std::vector< ExdRecordIndexData > record_indices;
      record_indices.reserve( record_count );
      for( uint32_t i = 0; i < record_count; ++i )
      {
        auto recordIndex = extract< ExdRecordIndexData >( iss );
        _idCache[ recordIndex.id ] = ExdCacheEntry{ file_ptr, recordIndex.offset };
      }
    }
  }

  Exd::~Exd()
  {
  }

  const std::vector< Field > Exd::get_row( uint32_t id, uint32_t subRow )
  {

    auto cacheEntryIt = _idCache.find( id );
    if( cacheEntryIt == _idCache.end() )
      throw std::runtime_error( "Id not found: " + std::to_string( id ) );

    // Iterates over all the files
    const uint32_t member_count = static_cast< uint32_t >( _exh->get_members().size() );
    auto& file_ptr = cacheEntryIt->second.file;

    std::vector< char > dataCpy = file_ptr->get_data_sections().front();
    std::istringstream iss( std::string( dataCpy.begin(), dataCpy.end() ) );

    // Get the vector fields for the given record and preallocate it
    auto fields = _data[ id ];
    fields.reserve( member_count );
    iss.seekg( cacheEntryIt->second.offset + 6 );

    uint8_t subRows = *reinterpret_cast< uint8_t* >( &dataCpy[ cacheEntryIt->second.offset + 5 ] );

    if( subRow >= subRows )
      throw std::runtime_error( "Out of bounds sub-row!" );

    int offset = cacheEntryIt->second.offset + 6 + ( subRow * _exh->get_header().data_offset + 2 * ( subRow + 1 ) );

    for( auto& member_entry : _exh->get_exh_members() )
    {
      // Seek to the position of the member to extract.
      // 6 is because we have uint32_t/uint16_t at the start of each record
      iss.seekg( offset + member_entry.offset );

      // Switch depending on the type to extract
      switch( member_entry.type )
      {
        case DataType::string:
          // Extract the offset to the actual string
          // Seek to it then extract the actual string
        {
          throw std::runtime_error( "String not implemented for variant 2!" );
          //auto string_offset = extract<uint32_t>( iss, "string_offset", false );
          //iss.seekg( cacheEntryIt->second.offset + 6 + _exh->get_header().data_offset + string_offset );
          //fields.emplace_back( utils::bparse::extract_cstring( iss, "string" ) );
        }
          break;

        case DataType::boolean:
          fields.emplace_back( extract< bool >( iss, "bool" ) );
          break;

        case DataType::int8:
          fields.emplace_back( extract< int8_t >( iss, "int8_t" ) );
          break;

        case DataType::uint8:
          fields.emplace_back( extract< uint8_t >( iss, "uint8_t" ) );
          break;

        case DataType::int16:
          fields.emplace_back( extract< int16_t >( iss, "int16_t", false ) );
          break;

        case DataType::uint16:
          fields.emplace_back( extract< uint16_t >( iss, "uint16_t", false ) );
          break;

        case DataType::int32:
          fields.emplace_back( extract< int32_t >( iss, "int32_t", false ) );
          break;

        case DataType::uint32:
          fields.emplace_back( extract< uint32_t >( iss, "uint32_t", false ) );
          break;

        case DataType::float32:
          fields.emplace_back( extract< float >( iss, "float", false ) );
          break;

        case DataType::uint64:
          fields.emplace_back( extract< uint64_t >( iss, "uint64_t", false ) );
          break;

        default:
          auto type = static_cast< uint16_t >( member_entry.type );
          if( type < 0x19 || type > 0x20 )
            throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
          uint64_t val = extract< uint64_t >( iss, "bool" );
          int32_t shift = type - 0x19;
          int32_t i = 1 << shift;
          val &= i;
          fields.emplace_back( ( val & i ) == i );
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

    // Iterates over all the files
    const uint32_t member_count =  static_cast< uint32_t >( _exh->get_members().size() );
    auto& file_ptr = cacheEntryIt->second.file;

    std::vector< char > dataCpy = file_ptr->get_data_sections().front();
    std::istringstream iss( std::string( dataCpy.begin(), dataCpy.end() ) );

    // Get the vector fields for the given record and preallocate it
    auto fields = _data[ id ];
    fields.reserve( member_count );
    iss.seekg( cacheEntryIt->second.offset + 6 );

    uint8_t subRows = *reinterpret_cast< uint8_t* >( &dataCpy[ cacheEntryIt->second.offset + 5 ] );

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
          auto string_offset = extract< uint32_t >( iss, "string_offset", false );
          iss.seekg( cacheEntryIt->second.offset + 6 + _exh->get_header().data_offset + string_offset );
          fields.emplace_back( utils::bparse::extract_cstring( iss, "string" ) );
        }
          break;

        case DataType::boolean:
          fields.emplace_back( extract< bool >( iss, "bool" ) );
          break;

        case DataType::int8:
          fields.emplace_back( extract< int8_t >( iss, "int8_t" ) );
          break;

        case DataType::uint8:
          fields.emplace_back( extract< uint8_t >( iss, "uint8_t" ) );
          break;

        case DataType::int16:
          fields.emplace_back( extract< int16_t >( iss, "int16_t", false ) );
          break;

        case DataType::uint16:
          fields.emplace_back( extract< uint16_t >( iss, "uint16_t", false ) );
          break;

        case DataType::int32:
          fields.emplace_back( extract< int32_t >( iss, "int32_t", false ) );
          break;

        case DataType::uint32:
          fields.emplace_back( extract< uint32_t >( iss, "uint32_t", false ) );
          break;

        case DataType::float32:
          fields.emplace_back( extract< float >( iss, "float", false ) );
          break;

        case DataType::uint64:
          fields.emplace_back( extract< uint64_t >( iss, "uint64_t", false ) );
          break;

        default:
          auto type = static_cast< uint16_t >( member_entry.type );
          if( type < 0x19 || type > 0x20 )
            throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
          uint64_t val = extract< uint64_t >( iss, "bool" );
          int32_t shift = type - 0x19;
          int32_t i = 1 << shift;
          val &= i;
          fields.emplace_back( ( val & i ) == i );
          break;
      }
    }
    return fields;

  }

  // Get all rows
  const std::map< uint32_t, std::vector< Field>>& Exd::get_rows()
  {
    // Iterates over all the files
    const uint32_t member_count =  static_cast< uint32_t >( _exh->get_members().size() );
    for( auto& file_ptr : _files )
    {
      // Get a stream
      std::vector< char > dataCpy = file_ptr->get_data_sections().front();
      std::istringstream iss( std::string( dataCpy.begin(), dataCpy.end() ) );

      // Extract the header and skip to the record indices
      auto exd_header = extract< ExdHeaderMinimal >( iss );
      iss.seekg( 0x20 );

      // Preallocate and extract the record_indices
      const uint32_t record_count = exd_header.index_size / sizeof( ExdRecordIndexData );
      std::vector< ExdRecordIndexData > record_indices;
      record_indices.reserve( record_count );
      for( uint32_t i = 0; i < record_count; ++i )
      {
        record_indices.emplace_back( extract< ExdRecordIndexData >( iss ) );
      }

      for( auto& record_index : record_indices )
      {
        // Get the vector fields for the given record and preallocate it
        auto& fields = _data[ record_index.id ];
        fields.reserve( member_count );

        for( auto& member_entry : _exh->get_exh_members() )
          //for( auto& member_entry : _exh->get_members() )
        {
          // Seek to the position of the member to extract.
          // 6 is because we have uint32_t/uint16_t at the start of each record
          iss.seekg( record_index.offset + 6 + member_entry.offset );

          // Switch depending on the type to extract
          switch( member_entry.type )
          {
            case DataType::string:
              // Extract the offset to the actual string
              // Seek to it then extract the actual string
            {
              auto string_offset = extract< uint32_t >( iss, "string_offset", false );
              iss.seekg( record_index.offset + 6 + _exh->get_header().data_offset + string_offset );
              fields.emplace_back( utils::bparse::extract_cstring( iss, "string" ) );
            }
              break;

            case DataType::boolean:
              fields.emplace_back( extract< bool >( iss, "bool" ) );
              break;

            case DataType::int8:
              fields.emplace_back( extract< int8_t >( iss, "int8_t" ) );
              break;

            case DataType::uint8:
              fields.emplace_back( extract< uint8_t >( iss, "uint8_t" ) );
              break;

            case DataType::int16:
              fields.emplace_back( extract< int16_t >( iss, "int16_t", false ) );
              break;

            case DataType::uint16:
              fields.emplace_back( extract< uint16_t >( iss, "uint16_t", false ) );
              break;

            case DataType::int32:
              fields.emplace_back( extract< int32_t >( iss, "int32_t", false ) );
              break;

            case DataType::uint32:
              fields.emplace_back( extract< uint32_t >( iss, "uint32_t", false ) );
              break;

            case DataType::float32:
              fields.emplace_back( extract< float >( iss, "float", false ) );
              break;

            case DataType::uint64:
              fields.emplace_back( extract< uint64_t >( iss, "uint64_t", false ) );
              break;

            default:
              auto type = static_cast< uint16_t >( member_entry.type );
              if( type < 0x19 || type > 0x20 )
                throw std::runtime_error( "Unknown DataType: " + std::to_string( type ) );
              uint64_t val = extract< uint64_t >( iss, "bool" );
              int32_t shift = type - 0x19;
              int32_t i = 1 << shift;
              val &= i;
              fields.emplace_back( ( val & i ) == i );
              break;
          }
        }
      }
    }
    return _data;
  }

}

