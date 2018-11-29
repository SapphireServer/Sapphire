
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


Sapphire::Logger g_log;
Sapphire::Data::ExdDataGenerated g_exdData;


//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );


int main()
{

  g_log.init();

  g_log.info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    g_log.fatal( "Error setting up EXD data " );
    return 0;
  }


  //g_log.info( "getting id list " );
  //auto idList = g_exdData.getGilShopIdList();

  //g_log.info( "getting id list done" );
  //for( auto id : idList )
  {
    auto teri1 = g_exdData.get< Sapphire::Data::GilShopItem >( 262440, 0 );
    g_log.info( "0 -> " + std::to_string( teri1->item ) );

    auto teri2 = g_exdData.get< Sapphire::Data::GilShopItem >( 262440, 1 );
    g_log.info( "1 -> " + std::to_string( teri2->item ) );

    auto teri3 = g_exdData.get< Sapphire::Data::GilShopItem >( 262440, 2 );
    g_log.info( "2 -> " + std::to_string( teri3->item ) );
  }

  return 0;
}
