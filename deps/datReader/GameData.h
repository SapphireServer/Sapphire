#ifndef XIV_DAT_GAMEDATA_H
#define XIV_DAT_GAMEDATA_H

#include <memory>
#include <unordered_map>
#include <mutex>

#include <filesystem>

namespace xiv
{
namespace dat
{

class Cat;
class File;

// Interface to all the datfiles - Main entry point
// All the paths to files/dirs inside the dats are case-insensitive
class GameData
{
public:
   // This should be the path in which the .index/.datX files are located
   GameData( const std::filesystem::path& path );
   ~GameData();

   static const std::string buildDatStr( const std::string folder, const int cat, const int exNum, const int chunk, const std::string platform, const std::string type );

   // Returns all the scanned category number available in the path
   const std::vector<uint32_t>& getCatNumbers() const;

   // Return a specific category by its number (see getCatNumbers() for loops)
   const Cat& getCategory( uint32_t catNum );
   // Return a specific category by it's name (e.g.: "exd"/"game_script"/ etc...)
   const Cat& getCategory( const std::string& catName );

   const Cat& getExCategory( const std::string& catName, uint32_t exNum, const std::string& path );

   // Retrieve a file from the dats given its filename
   std::unique_ptr<File> getFile( const std::string& path );

   // Checks that a file exists
   bool doesFileExist( const std::string& path );

   // Checks that a dir exists, there must be a trailing / in the path
   // Note that it won't work for dirs that don't contain any file
   // e.g.:  - "ui/icon/" will return False
   //        - "ui/icon/000000/" will return True
   bool doesDirExist( const std::string& path );

protected:
   // Return a specific category given a path (calls const Cat& getCategory(const std::string& catName))
   const Cat& getCategoryFromPath( const std::string& path );

   // From a full path, returns the dirHash and the filenameHash
   void getHashes( const std::string& path, uint32_t& dirHash, uint32_t& filenameHash ) const;

   // Lazy instantiation of category
   void createCategory( uint32_t catNum );

   void createExCategory( uint32_t catNum );

   // Path given to constructor, pointing to the folder with the .index/.datX files
   const std::filesystem::path m_path;

   // Stored categories, indexed by their number, categories are instantiated and parsed individually when they are needed
   std::unordered_map<uint32_t, std::unique_ptr<Cat>> m_cats;

   // List of all the categories numbers, is equal to m_cats.keys()
   std::vector<uint32_t> m_catNums;

   // Map of all EX categories and their chunks, "CatNum - (ExNum - (ChunkNum - Cat))"
   // Map of all EX categories and their chunks, "CatNum - (ExNum - (ChunkNum - Cat))"
   using ChunkToCatMap = struct { std::unordered_map< uint32_t, std::unique_ptr< Cat > > chunkToCatMap; };
   using ExNumToChunkMap = struct { std::unordered_map< uint32_t, ChunkToCatMap > exNumToChunkMap; };
   using CatNumToExNumMap = std::unordered_map< uint32_t, ExNumToChunkMap >;
   CatNumToExNumMap m_exCats;
   std::unordered_map<uint32_t, std::unique_ptr<std::mutex>> m_catCreationMutexes;
};

}
}

#endif // XIV_DAT_GAMEDATA_H
