
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

#include <fstream>
#include <streambuf>
#include <regex>


Core::Logger g_log;
Core::Data::ExdDataGenerated g_exdData;


const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
//const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv" );


int main()
{

   g_log.init();

   g_log.info( "Setting up EXD data" );
   if( !g_exdData.init( datLocation ) )
   {
      g_log.fatal( "Error setting up EXD data " );
      return 0;
   }

   
   g_log.info( "getting id list " );
   auto idList = g_exdData.getTerritoryTypeIdList();

   g_log.info( "getting id list done" );
   for( auto id : idList )
   {
      auto teri1 = g_exdData.get<Core::Data::TerritoryType>( id );

      g_log.info( teri1->name );
   }

   return 0;
}
