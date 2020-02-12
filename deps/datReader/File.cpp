#include "File.h"

#include <fstream>

namespace xiv::dat
{

  File::File() :
    _type( FileType::empty )
  {
  }

  File::~File()
  {
  }

  FileType File::get_type() const
  {
    return _type;
  }

  const std::vector< std::vector< char>>& File::get_data_sections() const
  {
    return _data_sections;
  }

  std::vector< std::vector< char>>& File::access_data_sections()
  {
    return _data_sections;
  }

  void File::exportToFile( const std::filesystem::path& i_path ) const
  {
    std::ofstream ofs( i_path.string(), std::ios_base::binary | std::ios_base::out );
    for( auto& data_section : _data_sections )
    {
      ofs.write( data_section.data(), data_section.size() );
    }
    ofs.close();
  }

}
