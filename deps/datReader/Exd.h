#ifndef XIV_EXD_EXD_H
#define XIV_EXD_EXD_H

#include <memory>
#include <map>

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
  };

  // Data for a given language
  class Exd
  {
  public:
    // i_exh: the header
    // i_files: the multiple exd files
    Exd()
    {
    }

    Exd( std::shared_ptr< Exh > i_exh, const std::vector< std::shared_ptr< dat::File>>& i_files );

    ~Exd();

    // Get a row by its id
    const std::vector< Field > get_row( uint32_t id );

    // Get a row by its id and sub-row
    const std::vector< Field > get_row( uint32_t id, uint32_t subRow );

    // Get all rows
    const std::map< uint32_t, std::vector< Field>>& get_rows();

  protected:
    // Data indexed by the ID of the row, the vector is field with the same order as exh.members
    std::map< uint32_t, std::vector< Field>> _data;
    std::vector< std::shared_ptr< dat::File>> _files;
    std::shared_ptr< Exh > _exh;
    std::map< uint32_t, ExdCacheEntry > _idCache;
  };

}

#endif // XIV_EXD_EXD_H
