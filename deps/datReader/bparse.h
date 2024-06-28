#ifndef XIV_UTILS_BPARSE_H
#define XIV_UTILS_BPARSE_H

#include <type_traits>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstdint>

namespace xiv::utils::bparse
{

  // Internal macro for byteswapping
  template< int N >
  void byteswap_impl( char (& bytes)[N] )
  {
    for( auto p = std::begin( bytes ), end = std::end( bytes ) - 1; p < end; ++p, --end )
    {
      std::swap( *p, *end );
    }
  }

  // byteswapping any type (no pointers to array)
  template< typename T >
  T byteswap( T value )
  {
    byteswap_impl( *reinterpret_cast<char ( * )[sizeof( T )]>(&value) );
    return value;
  }

  // Read a struct from a stream
  template< typename StructType >
  void read( std::istream& i_stream, StructType& i_struct )
  {
    static_assert( std::is_pod< StructType >::value, "StructType must be a POD to be able to use read." );
    i_stream.read( reinterpret_cast<char*>( &i_struct ), sizeof( StructType ) );
  }

  // By default a type does not need reordering
  template< typename StructType >
  void reorder( StructType& i_struct )
  {
  }

  // "Overload" for passed struct as arg
  template< typename StructType >
  void extract( std::istream& i_stream, StructType& o_struct )
  {
    read( i_stream, o_struct );
    reorder( o_struct );
  }

  // This should not copy because of RVO
  // Extract a struct from a stream and log it
  template< typename StructType >
  StructType extract( std::istream& i_stream )
  {
    StructType temp_struct;
    extract< StructType >( i_stream, temp_struct );
    return temp_struct;
  }

  template< typename StructType >
  void extract( std::istream& i_stream, uint32_t i_size, std::vector< StructType >& o_structs )
  {
    o_structs.reserve( i_size );
    for( uint32_t i = 0; i < i_size; ++i )
    {
      o_structs.emplace_back( extract< StructType >( i_stream ) );
    }
  }

  // For simple (integral) types just provide name and endianness directly
  template< typename StructType >
  StructType extract( std::istream& i_stream, const std::string& i_name, bool i_is_le = true )
  {
    StructType temp_struct;
    read( i_stream, temp_struct );
    if( !i_is_le )
    {
      temp_struct = byteswap( temp_struct );
    }
    return temp_struct;
  }

  template< typename StructType >
  void extract( std::istream& i_stream, const std::string& i_name, uint32_t i_size, std::vector< StructType >& o_structs,
                bool i_is_le = true )
  {
    o_structs.reserve( i_size );
    for( uint32_t i = 0; i < i_size; ++i )
    {
      o_structs.emplace_back( extract< StructType >( i_stream, i_name ) );
    }
  }

  template< typename StructType >
  StructType extract( std::vector< char >& data, uint32_t pos, bool isLe = true )
  {
    StructType tempStruct = *reinterpret_cast< StructType* >( &data[ pos ] );

    if( std::is_class< StructType >::value )
    {
      reorder( tempStruct );
    }
    else if( !isLe )
    {
      tempStruct = byteswap( tempStruct );
    }
    return tempStruct;
  }

  // For cstrings
  std::string extract_cstring( std::istream& i_stream, const std::string& i_name );

  std::string extract_cstring( std::vector< char >& data, uint32_t pos );

}

#endif // XIV_UTILS_BPARSE_H
