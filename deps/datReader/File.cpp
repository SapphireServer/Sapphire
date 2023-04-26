#include "File.h"

#include <fstream>

namespace xiv::dat
{

  File::File() :
    _type( FileType::empty )
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
    std::ofstream ofs( i_path, std::ios::binary | std::ios::out );

    if( !ofs )
    {
      throw std::runtime_error( "Failed to open the output file: " + i_path.string() );
    }

    for( const auto& data_section : _data_sections )
    {
      ofs.write( reinterpret_cast< const char* >( data_section.data() ), static_cast< std::streamsize >( data_section.size() ) );
    }

    // The file stream will be closed automatically when the ofstream object goes out of scope
    // ofs.close();
  }

}
