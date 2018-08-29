
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

using namespace boost::system;
namespace filesys = boost::filesystem;

#include <fstream>
#include <streambuf>
#include <regex>
#include <map>

Core::Logger g_log;
Core::Data::ExdDataGenerated g_exdData;

//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );

struct StatusEffect
{
  uint16_t effect_id;
  uint16_t unknown1;
  float duration;
  uint32_t sourceActorId;
};

struct FFXIVIpcNpcSpawn
{
  uint32_t gimmickId; // needs to be existing in the map, mob will snap to it
  uint8_t u2b;
  uint8_t u2ab;
  uint8_t gmRank;
  uint8_t u3b;

  uint8_t aggressionMode; // 1 passive, 2 aggressive
  uint8_t onlineStatus;
  uint8_t u3c;
  uint8_t pose;

  uint32_t u4;

  uint64_t targetId;
  uint32_t u6;
  uint32_t u7;
  uint64_t mainWeaponModel;
  uint64_t secWeaponModel;
  uint64_t craftToolModel;

  uint32_t u14;
  uint32_t u15;
  uint32_t bNPCBase;
  uint32_t bNPCName;
  uint32_t u18;
  uint32_t u19;
  uint32_t directorId;
  uint32_t spawnerId;
  uint32_t parentActorId;
  uint32_t hPMax;
  uint32_t hPCurr;
  uint32_t displayFlags;
  uint16_t fateID;
  uint16_t mPCurr;
  uint16_t tPCurr;
  uint16_t mPMax;
  uint16_t tPMax;
  uint16_t modelChara;
  uint16_t rotation;
  uint16_t activeMinion;
  uint8_t spawnIndex;
  uint8_t state;
  uint8_t persistantEmote;
  uint8_t modelType;
  uint8_t subtype;
  uint8_t voice;
  uint16_t u25c;
  uint8_t enemyType;
  uint8_t level;
  uint8_t classJob;
  uint8_t u26d;
  uint16_t u27a;
  uint8_t currentMount;
  uint8_t mountHead;
  uint8_t mountBody;
  uint8_t mountFeet;
  uint8_t mountColor;
  uint8_t scale;
  uint32_t u29b;
  uint32_t u30b;
  StatusEffect effect[30];
  float posX;
  float posY;
  float posZ;
  uint32_t models[10];
  char name[32];
  uint8_t look[26];
  char fcTag[6];
  uint32_t unk30;
  uint32_t unk31;
  uint8_t bNPCPartSlot;
  uint8_t unk32;
  uint16_t unk33;
  uint32_t unk34;
};


std::vector< std::string > getAllFilesInDir( const std::string& dirPath,
                                             const std::vector< std::string > dirSkipList = {} )
{

  // Create a vector of string
  std::vector< std::string > listOfFiles;
  try
  {
    // Check if given path exists and points to a directory
    if( filesys::exists( dirPath ) && filesys::is_directory( dirPath ) )
    {
      // Create a Recursive Directory Iterator object and points to the starting of directory
      filesys::recursive_directory_iterator iter( dirPath );

      // Create a Recursive Directory Iterator object pointing to end.
      filesys::recursive_directory_iterator end;

      // Iterate till end
      while( iter != end )
      {
        // Check if current entry is a directory and if exists in skip list
        if( filesys::is_directory( iter->path() ) &&
            ( std::find( dirSkipList.begin(), dirSkipList.end(), iter->path().filename() ) != dirSkipList.end() ) )
        {
          // Skip the iteration of current directory pointed by iterator
#ifdef USING_BOOST
          // Boost Fileystsem  API to skip current directory iteration
          iter.no_push();
#else
          // c++17 Filesystem API to skip current directory iteration
          iter.disable_recursion_pending();
#endif
        }
        else
        {
          // Add the name in vector
          listOfFiles.push_back( iter->path().string() );
        }

        error_code ec;
        // Increment the iterator to point to next entry in recursive iteration
        iter.increment( ec );
        if( ec )
        {
          std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
        }
      }
    }
  }
  catch( std::system_error& e )
  {
    std::cerr << "Exception :: " << e.what();
  }
  return listOfFiles;
}


int main()
{

  g_log.init();

  g_log.info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    g_log.fatal( "Error setting up EXD data " );
    return 0;
  }

  std::map< int, std::vector< FFXIVIpcNpcSpawn > > nameToPacketList;
  std::map< int, std::vector< FFXIVIpcNpcSpawn > > zoneToPacketList;

  auto listOfFiles = getAllFilesInDir( "G:\\programming\\sapphire\\github\\ffxivmon\\bin\\CapturedNpcs",
                                       { ".svn", "logs", "backup" } );

  for( auto file : listOfFiles )
  {
    if( !filesys::is_directory( file ) )
    {
      auto pos = file.find_last_of( "\\" );
      if( pos != std::string::npos )
      {
        auto str = file.substr( 0, pos );
        pos = str.find_last_of( "\\" );
        auto zone = str.substr( pos + 1 );
        //g_log.info( zone );

        FFXIVIpcNpcSpawn packet;
        std::ifstream is;
        is.open( file, std::ios::binary );
        is.seekg( 0x20, std::ios::beg );
        is.read( ( char* ) &packet, sizeof( FFXIVIpcNpcSpawn ) );
        is.close();


        if( packet.subtype != 2 &&
            packet.subtype != 3 &&
            packet.enemyType != 0 &&
            packet.spawnerId == 0xE0000000 &&
            packet.fateID == 0 )
          zoneToPacketList[ std::stoi( zone ) ].push_back( packet );

      }

    }

    /*  if( filesys::is_directory( file ) )
      {
         auto pos = file.find_last_of( "\\" );
         if( pos != std::string::npos )
         {
            auto zoneIdStr = file.substr( pos + 1 );
            auto teri1 = g_exdData.get< Core::Data::TerritoryType >( std::stoi( zoneIdStr ) );
            g_log.info( zoneIdStr + " - " + teri1->name );
         }
      }
      else
      {
         FFXIVIpcNpcSpawn packet;
         std::ifstream is;
         is.open( file, std::ios::binary );
         is.seekg( 0x20, std::ios::beg );
         is.read( ( char* )&packet, sizeof( FFXIVIpcNpcSpawn ) );
         is.close();

         nameToPacketList[ packet.bNPCName ].push_back( packet );

         auto nameStruct = g_exdData.get< Core::Data::BNpcName >( packet.bNPCName );
         //g_log.info( nameStruct->singular + " " + std::to_string( packet.bNPCBase ) );
      }
*/

  }

  for( auto entry : zoneToPacketList )
  {

    //auto nameStruct = g_exdData.get< Core::Data::BNpcName >( entry.first );
    auto teri1 = g_exdData.get< Core::Data::TerritoryType >( entry.first );
    auto teriPlaceName = g_exdData.get< Core::Data::PlaceName >( teri1->placeName );
    g_log.info( std::to_string( entry.first ) + " - " + teri1->name + " - " + teriPlaceName->name );
    g_log.info( "Mob Count: " + std::to_string( entry.second.size() ) );

    for( auto mob : entry.second )
    {
      nameToPacketList[ mob.bNPCName ].push_back( mob );

      auto nameStruct = g_exdData.get< Core::Data::BNpcName >( mob.bNPCName );
      //g_log.info( nameStruct->singular + " " + std::to_string( packet.bNPCBase ) );
    }

    g_log.info( "Unique Mobs: " + std::to_string( nameToPacketList.size() ) );

    for( auto mobName : nameToPacketList )
    {
      auto nameStruct = g_exdData.get< Core::Data::BNpcName >( mobName.first );
      g_log.info( "|--> " + nameStruct->singular + "(" + std::to_string( mobName.second.size() ) + ")" );

      for( FFXIVIpcNpcSpawn instance : mobName.second )
      {

        std::string modelStr = "[";

        for( auto modelEntry : instance.models )
        {
          modelStr += std::to_string( modelEntry ) + ", ";
        }

        modelStr += "]";


        std::string cusStr = "[";

        for( auto cusEntry : instance.look )
        {
          cusStr += std::to_string( cusEntry ) + ", ";
        }

        cusStr += "]";


        //g_log.info( "|----> " + std::to_string( instance.bNPCBase ) + " " + std::to_string( instance.posX ) + ", " + std::to_string( instance.posY ) + ", " + std::to_string( instance.posZ )  );
        /*g_log.info( "|----> " + std::to_string( instance.bNPCBase ) +
                    " " + std::to_string( instance.mainWeaponModel ) +
                    ", " + std::to_string( instance.secWeaponModel ) +
                    ", " + std::to_string( instance.aggressionMode ) +
                    ", " + std::to_string( instance.enemyType ) +
                    ", " + std::to_string( instance.onlineStatus ) +
                    ", " + std::to_string( instance.pose ) +
                    ", " + std::to_string( instance.modelChara ) +
                    ", " + std::to_string( instance.displayFlags ) + ", " + modelStr + ", " + cusStr + ", " + std::to_string( instance.gimmickId ) );*/

        g_log.info( "|----> " + std::to_string( instance.bNPCBase ) +
                    " " + std::to_string( instance.u2ab ) +
                    ", " + std::to_string( instance.u2b ) +
                    ", " + std::to_string( instance.u3b ) +
                    ", " + std::to_string( instance.u3c ) +
                    ", " + std::to_string( instance.u4 ) +
                    ", " + std::to_string( instance.u6 ) +
                    ", " + std::to_string( instance.u7 ) +
                    ", " + std::to_string( instance.u14 ) +
                    ", " + std::to_string( instance.u15 ) +
                    ", " + std::to_string( instance.u18 ) +
                    ", " + std::to_string( instance.u19 ) +
                    ", " + std::to_string( instance.u25c ) +
                    ", " + std::to_string( instance.u26d ) +
                    ", " + std::to_string( instance.u27a ) +
                    ", " + std::to_string( instance.u29b ) +
                    ", " + std::to_string( instance.u30b ) +
                    ", " + std::to_string( instance.unk30 ) +
                    ", " + std::to_string( instance.unk31 ) +
                    ", " + std::to_string( instance.unk32 ) +
                    ", " + std::to_string( instance.unk33 ) +
                    ", " + std::to_string( instance.unk34 ) );
      }
    }
    nameToPacketList.clear();
  }

  /*g_log.info( "getting id list " );
  auto idList = g_exdData.getTerritoryTypeIdList();

  g_log.info( "getting id list done" );
  for( auto id : idList )
  {
     auto teri1 = g_exdData.get<Core::Data::TerritoryType>( id );

     g_log.info( teri1->name );
  }*/

  return 0;
}
