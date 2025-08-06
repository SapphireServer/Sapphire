#include "ExdCat.h"

#include <fstream>

#include "GameData.h"

#include "Exh.h"
#include "Exd.h"

namespace
{
  // Suffix of the filenames given a language
  std::map<xiv::exd::Language, std::string> language_map =
  {
    {xiv::exd::Language::none, ""},
    {xiv::exd::Language::ja, "_ja"},
    {xiv::exd::Language::en, "_en"},
    {xiv::exd::Language::de, "_de"},
    {xiv::exd::Language::fr, "_fr"},
    {xiv::exd::Language::chs, "_chs"}
  };
}

namespace xiv::exd
{
  Cat::Cat( dat::GameData& i_game_data, const std::string& i_name ) :
    _name( i_name )
  {
    //XIV_INFO(xiv_exd_logger, "Initializing Cat with name: " << i_name);
    // creates the header .exh
    {
      auto header_file = i_game_data.getFile( "exd/" + i_name + ".exh" );
      _header = std::shared_ptr< Exh >( new Exh( *header_file ) );

    }

    for( auto language: _header->get_languages() )
    {
      // chs not yet in data files
      if( language == Language::en || language == Language::none )
      {
        // Get all the files for a given category/language, in case of multiple range of IDs in separate files (like Quest)
        std::vector< std::shared_ptr< dat::File>> files;
        for( auto& exd_def: _header->get_exd_defs() )
        {
          files.emplace_back( i_game_data.getFile(
            "exd/" + i_name + "_" + std::to_string( exd_def.start_id ) + language_map.at( language ) + ".exd" ) );
        }
        // Instantiate the data for this language
        _data[ language ] = std::make_unique< Exd >( _header, files );
      }
    }
  }

  Cat::~Cat()
  {

  }

  const std::string& Cat::get_name() const
  {
    return _name;
  }

  Exh& Cat::get_header()
  {
    return *_header;
  }

  Exd& Cat::get_data_ln( Language i_language )
  {
    auto ln_it = _data.find( i_language );
    if( ln_it == _data.end() )
    {
      throw std::runtime_error( "No data for language: " + std::to_string( uint16_t( i_language ) ) );
    }

    return *( ln_it->second );
  }

  Exd& Cat::get_data( Language language )
  {
    auto ln_it = _data.find( language );
    if( ln_it == _data.end() )
    {
      return get_data_ln( Language::none );
    }

    return *( ln_it->second );
  }

}
