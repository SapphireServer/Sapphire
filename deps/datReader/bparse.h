#pragma once
#include <type_traits>
#include <iomanip>
#include <sstream>
#include <vector>

namespace xiv::utils::bparse
{

  // Helper struct for compile-time unrolling of byteswap
  template< int N, bool Unroll >
  struct byteswap_impl_helper
  {
    static void swap( char ( &bytes )[ N ], int start )
    {
      // Intentionally left empty. This specialization should never be used.
    }
  };

  // Specialization of byteswap_impl_helper for compile-time unrolling (true)
  template< int N >
  struct byteswap_impl_helper< N, true >
  {
    static void swap( char ( &bytes )[ N ], int start )
    {
      // Swap pairs of bytes recursively, unrolling the loop at compile-time
      if constexpr( N >= 2 )
      {
        std::swap( bytes[ start ], bytes[ N - start - 1 ] );
        if constexpr( N >= 4 )
        {
          std::swap( bytes[ start + 1 ], bytes[ N - start - 2 ] );
          if constexpr( N >= 6 )
          {
            std::swap( bytes[ start + 2 ], bytes[ N - start - 3 ] );
            if constexpr( N >= 8 )
            {
              std::swap( bytes[ start + 3 ], bytes[ N - start - 4 ] );
            }
          }
        }
      }
    }
  };

  template< int N >
  struct byteswap_impl_helper< N, false >
  {
    static void swap( char ( &bytes )[ N ], int start )
    {
      // Swap pairs of bytes using a loop
      for( auto p = std::begin( bytes ), end = std::end( bytes ) - 1; p < end;
           ++p, --end )
      {
        std::swap( *p, *end );
      }
    }
  };

  template< int N >
  void byteswap_impl( char ( &bytes )[ N ] )
  {
    // Decide whether to use compile-time unrolling or loop-based swapping
    constexpr bool Unroll = N <= 8;
    byteswap_impl_helper< N, Unroll >::swap( bytes, 0 );
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
    static_assert( std::is_trivially_copyable< StructType >::value, "StructType must be a POD to be able to use read." );
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

  std::string extract_cstring( std::istream& i_stream, const std::string& i_name );

}
