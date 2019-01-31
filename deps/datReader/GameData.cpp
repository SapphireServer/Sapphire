#include "GameData.h"

#include <string>
#include <sstream>
#include <algorithm>

#include <map>
#include <zlib/zlib.h>

#include "bparse.h"
#include "DatCat.h"
#include "File.h"

namespace
{
    // Relation between category number and category name
    // These names are taken straight from the exe, it helps resolve dispatching when getting files by path

    std::unordered_map< std::string, uint32_t > categoryNameToIdMap = 
       {{"common",          0x00},
        {"bgcommon",        0x01},
        {"bg",              0x02},
        {"cut",             0x03},
        {"chara",           0x04},
        {"shader",          0x05},
        {"ui",              0x06},
        {"sound",           0x07},
        {"vfx",             0x08},
        {"ui_script",       0x09},
        {"exd",             0x0A},
        {"game_script",     0x0B},
        {"music",           0x0C}
   };

    std::unordered_map< uint32_t, std::string > categoryIdToNameMap = 
       {{0x00,              "common"},
        {0x01,              "bgcommon"},
        {0x02,              "bg"},
        {0x03,              "cut"},
        {0x04,              "chara"},
        {0x05,              "shader"},
        {0x06,              "ui"},
        {0x07,              "sound"},
        {0x08,              "vfx"},
        {0x09,              "ui_script"},
        {0x0A,              "exd"},
        {0x0B,              "game_script"},
        {0x0C,              "music"}};
}

namespace xiv
{
namespace dat
{

GameData::GameData(const std::experimental::filesystem::path& path) try :
    m_path(path)
{
   int maxExLevel = 0;

   // msvc has retarded stdlib implementation
#ifdef _WIN32
  static constexpr auto sep = "\\";
#else
  static constexpr auto sep = std::experimental::filesystem::path::preferred_separator;
#endif
  
   // Determine which expansions are available
   while( std::experimental::filesystem::exists( std::experimental::filesystem::path( m_path.string() + sep + "ex" + std::to_string( maxExLevel + 1 ) + sep + "ex" + std::to_string( maxExLevel + 1 ) + ".ver" ) ) )
   {
      maxExLevel++;
   }
   

   // Iterate over the files in path
   for( auto it = std::experimental::filesystem::directory_iterator( m_path.string() + "//ffxiv" ); it != std::experimental::filesystem::directory_iterator(); ++it )
   {
      // Get the filename of the current element
      auto filename = it->path().filename().string();

      // If it contains ".win32.index" this is most likely a hit for a category
      if( filename.find( ".win32.index" ) != std::string::npos &&  filename.find( ".win32.index2" ) == std::string::npos )
      {
         // Format of indexes is XX0000.win32.index, so fetch the hex number for category number
         std::istringstream iss( filename.substr( 0, 2 ) );
         uint32_t cat_nb;
         iss >> std::hex >> cat_nb;


         // Add to the list of category number
         // creates the empty category in the cats map
         // instantiate the creation mutex for this category
         m_catNums.push_back( cat_nb );
         m_cats[cat_nb] = std::unique_ptr<Cat>();
         m_catCreationMutexes[cat_nb] = std::unique_ptr<std::mutex>( new std::mutex() );

         // Check for expansion
         for( int exNum = 1; exNum <= maxExLevel; exNum++ )
         {
            const std::string path = m_path.string() + sep + buildDatStr( "ex" + std::to_string( exNum ), cat_nb, exNum, 0, "win32", "index" );

            if( std::experimental::filesystem::exists( std::experimental::filesystem::path( path ) ) )
            {

               int chunkCount = 0;

               for(int chunkTest = 0; chunkTest < 256; chunkTest++ )
               {
                  if( std::experimental::filesystem::exists( m_path.string() + sep + buildDatStr( "ex" + std::to_string( exNum ), cat_nb, exNum, chunkTest, "win32", "index" ) ) )
                  {
                     m_exCats[cat_nb].exNumToChunkMap[exNum].chunkToCatMap[chunkTest] = std::unique_ptr<Cat>();
                     chunkCount++;
                  }
               }      

            }
         }
      }
   }

}
catch( std::exception& e )
{
   // In case of failure here, client is supposed to catch the exception because it is not recoverable on our side
   throw std::runtime_error( "GameData initialization failed: " + std::string( e.what() ) );
}

GameData::~GameData()
{

}

const std::string GameData::buildDatStr( const std::string folder, const int cat, const int exNum, const int chunk, const std::string platform, const std::string type )
{
   char dat[1024];
   sprintf( dat, "%s/%02x%02x%02x.%s.%s", folder.c_str(), cat, exNum, chunk, platform.c_str(), type.c_str() );
   return std::string( dat );
}

const std::vector<uint32_t>& GameData::getCatNumbers() const
{
    return m_catNums;
}

std::unique_ptr<File> GameData::getFile(const std::string& path)
{
   // Get the hashes, the category from the path then call the getFile of the category
   uint32_t dirHash;
   uint32_t filenameHash;
   getHashes( path, dirHash, filenameHash );

   return getCategoryFromPath( path ).getFile( dirHash, filenameHash );
}

bool GameData::doesFileExist(const std::string& path)
{
   uint32_t dirHash;
   uint32_t filenameHash;
   getHashes( path, dirHash, filenameHash );

   return getCategoryFromPath( path ).doesFileExist( dirHash, filenameHash );
}

bool GameData::doesDirExist(const std::string& i_path)
{
   uint32_t dirHash;
   uint32_t filenameHash;
   getHashes( i_path, dirHash, filenameHash );

   return getCategoryFromPath( i_path ).doesDirExist( dirHash );
}

const Cat& GameData::getCategory(uint32_t catNum)
{
   // Check that the category number exists
   auto catIt = m_cats.find( catNum );
   if( catIt == m_cats.end() )
   {
      throw std::runtime_error( "Category not found: " + std::to_string( catNum ) );
   }

   // If it exists and already instantiated return it
   if( catIt->second )
   {
      return *( catIt->second );
   }
   else
   {
      // Else create it and return it
      createCategory( catNum );
      return *( m_cats[catNum] );
   }
}

const Cat& GameData::getCategory(const std::string& catName)
{
   // Find the category number from the name
   auto categoryNameToIdMapIt = ::categoryNameToIdMap.find( catName );
   if( categoryNameToIdMapIt == ::categoryNameToIdMap.end() )
   {
      throw std::runtime_error( "Category not found: " + catName );
   }

   // From the category number return the category
   return getCategory( categoryNameToIdMapIt->second );
}

const Cat& GameData::getExCategory( const std::string& catName, uint32_t exNum, const std::string& path )
{
   // Find the category number from the name
   auto categoryMapIt = ::categoryNameToIdMap.find( catName );
   if( categoryMapIt == ::categoryNameToIdMap.end() )
   {
      throw std::runtime_error( "Category not found: " + catName );
   }

   uint32_t dirHash;
   uint32_t filenameHash;
   getHashes( path, dirHash, filenameHash );

   for( auto const& chunk : m_exCats[categoryMapIt->second].exNumToChunkMap[exNum].chunkToCatMap )
   {
      if( !chunk.second )
         createExCategory( categoryMapIt->second );

      if( chunk.second->doesFileExist( dirHash, filenameHash ) )
      {
         return *( chunk.second );
      }
   }

   throw std::runtime_error( "Chunk not found for path: " + path );
}

const Cat& GameData::getCategoryFromPath(const std::string& path)
{
   // Find the first / in the string, paths are in the format CAT_NAME/..../.../../....
   auto firstSlashPos = path.find( '/' );
   if( firstSlashPos == std::string::npos )
   {
      throw std::runtime_error( "Path does not have a / char: " + path );
   }

   if( path.substr( firstSlashPos + 1, 2) == "ex" )
   {
      return getExCategory( path.substr( 0, firstSlashPos ), std::stoi( path.substr( firstSlashPos + 3, 1 ) ), path );
   }
   else
   {
      // From the sub string found beforethe first / get the category
      return getCategory( path.substr( 0, firstSlashPos ) );
   }
}

void GameData::getHashes(const std::string& path, uint32_t& dirHash, uint32_t& filenameHash) const
{
   // Convert the path to lowercase before getting the hashes
   std::string pathLower;
   pathLower.resize( path.size() );
   std::transform( path.begin(), path.end(), pathLower.begin(), ::tolower );

   // Find last / to separate dir from filename
   auto lastSlashPos = pathLower.rfind( '/' );
   if( lastSlashPos == std::string::npos )
   {
      throw std::runtime_error( "Path does not have a / char: " + path );
   }

   std::string dirPart = pathLower.substr( 0, lastSlashPos );
   std::string filenamePart = pathLower.substr( lastSlashPos + 1 );

   // Get the crc32 values from zlib, to compensate the final XOR 0xFFFFFFFF that isnot done in the exe we just reXOR
   dirHash = crc32( 0, reinterpret_cast<const uint8_t*>( dirPart.data() ), dirPart.size() ) ^ 0xFFFFFFFF;
   filenameHash = crc32( 0, reinterpret_cast<const uint8_t*>( filenamePart.data() ), filenamePart.size() ) ^ 0xFFFFFFFF;
}

void GameData::createCategory(uint32_t catNum)
{
   // Lock mutex in this scope
   std::lock_guard<std::mutex> lock( *( m_catCreationMutexes[catNum] ) );
   // Maybe after unlocking it has already been created, so check (most likely if it blocked)
   if( !m_cats[catNum] )
   {
      // Get the category name if we have it
      std::string catName;
      auto categoryMapIt = ::categoryIdToNameMap.find( catNum );
      if( categoryMapIt != ::categoryIdToNameMap.end() )
      {
         catName = categoryMapIt->second;
      }

      // Actually creates the category
      m_cats[catNum] = std::unique_ptr<Cat>( new Cat( m_path, catNum, catName ) );
   }
}

void GameData::createExCategory( uint32_t catNum )
{
   // Maybe after unlocking it has already been created, so check (most likely if it blocked)
   if( !m_exCats[catNum].exNumToChunkMap[1].chunkToCatMap[0] )
   {
      // Get the category name if we have it
      std::string catName;
      auto categoryMapIt = ::categoryIdToNameMap.find( catNum );
      if( categoryMapIt != ::categoryIdToNameMap.end() )
      {
         catName = categoryMapIt->second;
      }

      for( auto const& ex : m_exCats[catNum].exNumToChunkMap )
      {
         for( auto const& chunk : m_exCats[catNum].exNumToChunkMap[ex.first].chunkToCatMap )
         {
            // Actually creates the category
            m_exCats[catNum].exNumToChunkMap[ex.first].chunkToCatMap[chunk.first] = std::unique_ptr<Cat>( new Cat( m_path, catNum, catName, ex.first, chunk.first ) );
         }
      }
   }
}

}
}
