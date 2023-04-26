#pragma once

#include <vector>

#include <filesystem>
#include <stdint.h>
#include "bparse.h"

namespace xiv::dat
{
  enum class FileType :
    uint32_t
  {
    empty = 1,
    standard = 2,
    model = 3,
    texture = 4,
  };

  class Dat;

  // Basic file from the dats
  class File
  {
    friend class Dat;

  public:
    File();

    ~File() = default;

    // Returns the file type of the File object
    FileType get_type() const;

    // Returns a const reference to the data sections in the File object
    const std::vector< std::vector< char > >& get_data_sections() const;

    // Returns a reference to the data sections in the File object
    std::vector< std::vector< char > >& access_data_sections();

    // Exports the content of the File object to a file on disk at the given path
    void exportToFile( const std::filesystem::path& i_path ) const;

  protected:
    // Stores the file type of the File object
    FileType _type;

    // Stores the data sections of the File object as a vector of vectors of chars
    std::vector< std::vector< char > > _data_sections;
  };
}// namespace xiv::dat

