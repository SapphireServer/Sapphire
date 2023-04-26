#pragma once

#include <map>

#include "bparse.h"

namespace xiv::exd
{
  enum class DataType : uint16_t
  {
    string = 0,
    boolean = 1,
    int8 = 2,
    uint8 = 3,
    int16 = 4,
    uint16 = 5,
    int32 = 6,
    uint32 = 7,
    float32 = 9,
    uint64 = 11,
  };

  struct ExhHeader
  {
    char magic[0x4];
    uint16_t unknown;
    uint16_t data_offset;
    uint16_t field_count;
    uint16_t exd_count;
    uint16_t language_count;
    uint16_t unknown1;
    uint8_t u2;
    uint8_t variant;
  };

  struct ExhMember
  {
    DataType type;
    uint16_t offset;
  };

  struct ExhExdDef
  {
    uint32_t start_id;
    uint32_t count_id;
  };
};// namespace xiv::exd

namespace xiv::utils::bparse
{
  template<>
  inline void reorder< xiv::exd::ExhHeader >( xiv::exd::ExhHeader& i_struct )
  {
    for( int32_t i = 0; i < 0x4; ++i )
    {
      xiv::utils::bparse::reorder( i_struct.magic[ i ] );
    }
    i_struct.unknown = xiv::utils::bparse::byteswap( i_struct.unknown );
    xiv::utils::bparse::reorder( i_struct.unknown );
    i_struct.data_offset = xiv::utils::bparse::byteswap( i_struct.data_offset );
    xiv::utils::bparse::reorder( i_struct.data_offset );
    i_struct.field_count = xiv::utils::bparse::byteswap( i_struct.field_count );
    xiv::utils::bparse::reorder( i_struct.field_count );
    i_struct.exd_count = xiv::utils::bparse::byteswap( i_struct.exd_count );
    xiv::utils::bparse::reorder( i_struct.exd_count );
    i_struct.language_count = xiv::utils::bparse::byteswap( i_struct.language_count );
    xiv::utils::bparse::reorder( i_struct.language_count );
  }

  template<>
  inline void reorder< xiv::exd::ExhMember >( xiv::exd::ExhMember& i_struct )
  {
    i_struct.type = xiv::utils::bparse::byteswap( i_struct.type );
    xiv::utils::bparse::reorder( i_struct.type );
    i_struct.offset = xiv::utils::bparse::byteswap( i_struct.offset );
    xiv::utils::bparse::reorder( i_struct.offset );
  }

  template<>
  inline void reorder< xiv::exd::ExhExdDef >( xiv::exd::ExhExdDef& i_struct )
  {
    i_struct.start_id = xiv::utils::bparse::byteswap( i_struct.start_id );
    xiv::utils::bparse::reorder( i_struct.start_id );
    i_struct.count_id = xiv::utils::bparse::byteswap( i_struct.count_id );
    xiv::utils::bparse::reorder( i_struct.count_id );
  }
};// namespace xiv::utils::bparse

namespace xiv
{

  namespace dat
  {
    class File;
  }

  namespace exd
  {

    enum Language : uint16_t;

    // Header file for exd data
    class Exh
    {
    public:
      // The header file
      Exh( const dat::File& i_file );

      ~Exh() = default;

      // Returns a const reference to the ExhHeader object
      const ExhHeader& get_header() const;

      // Returns a const reference to a vector of ExhExdDef objects
      const std::vector< ExhExdDef >& get_exd_defs() const;

      // Returns a const reference to a vector of Language enums
      const std::vector< Language >& get_languages() const;

      // Returns a const reference to a map of ExhMember objects, indexed by their offset
      const std::map< uint32_t, ExhMember >& get_members() const;

      // Returns a const reference to a vector of ExhMember objects
      const std::vector< ExhMember >& get_exh_members() const;

    protected:
      ExhHeader _header;
      // Members of the datastruct ordered(indexed) by offset
      std::map< uint32_t, ExhMember > _members;
      std::vector< ExhMember > _exh_defs;
      std::vector< ExhExdDef > _exd_defs;
      std::vector< Language > _languages;
    };

  }// namespace exd
}// namespace xiv::exd