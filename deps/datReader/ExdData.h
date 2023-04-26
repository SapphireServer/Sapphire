#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <mutex>

#include <filesystem>

namespace xiv
{
   namespace dat
   {
      class GameData;
   }
   namespace exd
   {

      class Cat;

      // Interface for retrieval of exd data - Main entry point
      // the game_data object should outlive the exd_data object
      class ExdData
      {
      public:
          // Need an initialized dat::GameData to retrieve the files from the dat
          ExdData( dat::GameData& i_game_data );
          ~ExdData() = default;

          // Get the list of thenames of the categories
          const std::vector< std::string >& get_cat_names() const;

          // Get a category by its name
          const Cat& get_category( const std::string& i_cat_name );

          // Export in csv in base flder i_ouput_path
          void export_as_csvs( const std::filesystem::path& i_output_path );

      protected:
          // Lazy instantiation of category
          void create_category( const std::string& i_cat_name );

          // Reference to the game_data object
          dat::GameData& _game_data;

          // Categories, indexed by their name
          std::unordered_map< std::string, std::unique_ptr< Cat > > _cats;
          // List of category names = m_cats.keys()
          std::vector< std::string > _cat_names;
          // Mutexes used to avoid race condition when lazy instantiating a category
          std::unordered_map< std::string, std::unique_ptr< std::mutex > > _cat_creation_mutexes;
      };

   }// namespace exd
}// namespace xiv
