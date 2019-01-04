
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

#include <fstream>
#include <streambuf>
#include <regex>

Sapphire::Data::ExdDataGenerated g_exdData;

using namespace Sapphire;

//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );


int main()
{

  Logger::init( "struct_test" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }


  //Logger::info( "getting id list " );
  //auto idList = g_exdData.getGilShopIdList();

  //Logger::info( "getting id list done" );
  //for( auto id : idList )
  {
    auto teri1 = g_exdData.get< Sapphire::Data::GilShopItem >( 262440, 0 );
    Logger::info( "0 -> {0}", teri1->item );

    auto teri2 = g_exdData.get< Sapphire::Data::GilShopItem >( 262440, 1 );
    Logger::info( "1 -> {0} ", teri2->item );

    auto teri3 = g_exdData.get< Sapphire::Data::GilShopItem >( 262440, 2 );
    Logger::info( "2 -> {0}", teri3->item );
  }

  return 0;
}
