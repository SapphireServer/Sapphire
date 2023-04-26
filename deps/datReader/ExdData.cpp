#include "ExdData.h"

#include "stream.h"

#include "GameData.h"
#include "File.h"

#include "ExdCat.h"

namespace xiv::exd
{
  ExdData::ExdData( dat::GameData& i_game_data )
  try : _game_data( i_game_data )
  {
    // Fetch the root.exl and get a stream from it
    auto root_exl = i_game_data.getFile( "exd/root.exl" );
    std::vector< char > dataCpy = root_exl->get_data_sections().front();
    xiv::utils::stream::vectorwrapbuf< char > databuf( dataCpy );
    std::istream stream( &databuf );

    // Skip the first line (EXLT,2)
    std::string line;
    std::getline( stream, line );

    // Read the remaining lines
    while( std::getline( stream, line ) && !line.empty() )
    {
      // Format is cat_name,XX
      // XX being an internal identifier
      // Get only the cat_name
      auto sep = line.find( ',' );
      auto category = line.substr( 0, sep );

      // Add to the list of category names
      // Create the empty category in the cats map
      // Instantiate the creation mutex for this category
      _cat_names.emplace_back( category );
      _cats[ category ] = nullptr;
      _cat_creation_mutexes[ category ] = std::make_unique< std::mutex >();
    }
  } catch( std::exception& e )
  {
    // In case of failure here, client is supposed to catch the exception because it is not recoverable on our side
    throw std::runtime_error( "ExdData initialization failed: " + std::string( e.what() ) );
  }

  const std::vector< std::string >& ExdData::get_cat_names() const
  {
    return _cat_names;
  }

  const Cat& ExdData::get_category( const std::string& i_cat_name )
  {
    // Get the category from its name
    auto cat_it = _cats.find( i_cat_name );
    if( cat_it == _cats.end() )
    {
      throw std::runtime_error( "Category not found: " + i_cat_name );
    }

    if( cat_it->second )
    {
      // If valid return it
      return *( cat_it->second );
    }
    else
    {
      // If not, create it and return it
      create_category( i_cat_name );
      return *( _cats[ i_cat_name ] );
    }
  }

  void ExdData::create_category( const std::string& i_cat_name )
  {
    // Lock mutex in this scope
    std::lock_guard< std::mutex > lock( *( _cat_creation_mutexes[ i_cat_name ] ) );
    // Maybe after unlocking it has already been created, so check (most likely if it blocked)
    if( !_cats[ i_cat_name ] )
    {
      _cats[ i_cat_name ] = std::make_unique< Cat >( _game_data, i_cat_name );
    }
  }
}// namespace xiv::exd