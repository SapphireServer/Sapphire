#ifndef XIV_EXD_EXH_H
#define XIV_EXD_EXH_H

#include <map>

#include "bparse.h"

namespace xivps3::exd
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
};

namespace xivps3::utils::bparse {
template<>
inline void reorder< xivps3::exd::ExhHeader >( xivps3::exd::ExhHeader& i_struct )
{
  for( int32_t i = 0; i < 0x4; ++i )
  {
    xivps3::utils::bparse::reorder( i_struct.magic[ i ] );
  }
  i_struct.unknown = xivps3::utils::bparse::byteswap( i_struct.unknown );
  xivps3::utils::bparse::reorder( i_struct.unknown );
  i_struct.data_offset = xivps3::utils::bparse::byteswap( i_struct.data_offset );
  xivps3::utils::bparse::reorder( i_struct.data_offset );
  i_struct.field_count = xivps3::utils::bparse::byteswap( i_struct.field_count );
  xivps3::utils::bparse::reorder( i_struct.field_count );
  i_struct.exd_count = xivps3::utils::bparse::byteswap( i_struct.exd_count );
  xivps3::utils::bparse::reorder( i_struct.exd_count );
  i_struct.language_count = xivps3::utils::bparse::byteswap( i_struct.language_count );
  xivps3::utils::bparse::reorder( i_struct.language_count );
}

template<>
inline void reorder< xivps3::exd::ExhMember >( xivps3::exd::ExhMember& i_struct )
{
  i_struct.type = xivps3::utils::bparse::byteswap( i_struct.type );
  xivps3::utils::bparse::reorder( i_struct.type );
  i_struct.offset = xivps3::utils::bparse::byteswap( i_struct.offset );
  xivps3::utils::bparse::reorder( i_struct.offset );
}

template<>
inline void reorder< xivps3::exd::ExhExdDef >( xivps3::exd::ExhExdDef& i_struct )
{
  i_struct.start_id = xivps3::utils::bparse::byteswap( i_struct.start_id );
  xivps3::utils::bparse::reorder( i_struct.start_id );
  i_struct.count_id = xivps3::utils::bparse::byteswap( i_struct.count_id );
  xivps3::utils::bparse::reorder( i_struct.count_id );
}
};

namespace xivps3
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

      ~Exh();

      const ExhHeader& get_header() const;

      const std::vector< ExhExdDef >& get_exd_defs() const;

      const std::vector< Language >& get_languages() const;

      const std::map< uint32_t, ExhMember >& get_members() const;

      const std::vector< ExhMember >& get_exh_members() const;

    protected:
      ExhHeader _header;
      // Members of the datastruct ordered(indexed) by offset
      std::map< uint32_t, ExhMember > _members;
      std::vector< ExhMember > _exh_defs;
      std::vector< ExhExdDef > _exd_defs;
      std::vector< Language > _languages;
    };

  }
}

#endif // XIV_EXD_EXH_H
