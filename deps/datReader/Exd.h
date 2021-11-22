#ifndef XIV_EXD_EXD_H
#define XIV_EXD_EXD_H

#include <memory>
#include <map>
#include <unordered_map>
#include <set>

#include <variant>

#include "File.h"

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
    uint8_t subRows;
  };

  struct ExdRow
  {
    uint32_t rowId;
    uint8_t subRowId;
  };

  struct exdRowSort
  {
    constexpr bool operator()( const ExdRow& _Left, const ExdRow& _Right ) const
    {
      if( _Left.rowId == _Right.rowId )
        return _Left.subRowId < _Right.subRowId;

      return _Left.rowId < _Right.rowId;
    }
  };

  // Data for a given language
  class Exd
  {
  public:
    // exh: the header
    // files: the multiple exd files
    Exd()
    {
    }

    Exd( std::shared_ptr< Exh > exh, const std::vector< std::shared_ptr< dat::File > >& files );

    ~Exd();

    // Get a row by its id
    const std::vector< Field > get_row( uint32_t id );

    // Get a row by its id and sub-row
    const std::vector< Field > get_row( uint32_t id, uint32_t subRow );

    // Get all rows
    const std::map< ExdRow, std::vector< Field >, exdRowSort > get_rows();

  protected:
    std::shared_ptr< Exh > _exh;
    std::map< uint32_t, ExdCacheEntry > _idCache;
  };

}

#endif // XIV_EXD_EXD_H
