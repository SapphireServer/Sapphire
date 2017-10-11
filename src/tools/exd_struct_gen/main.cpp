
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
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <fstream>


Core::Logger g_log;
Core::Data::ExdData g_exdData;


const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
//const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv" );

std::string generateEnum( const std::string& exd )
{

   auto& cat = g_exdData.m_exd_data->get_category( exd );
   auto exh = cat.get_header();
   auto exhMem = exh.get_exh_members();

   for( auto member : exhMem )
   {
      g_log.info( std::to_string( static_cast< uint8_t >( member.type ) ) + "\n" ); 
   }
   
   return "";
}

int main()
{

   g_log.init();


   g_log.info( "Setting up EXD data" );
   if( !g_exdData.init( datLocation  ) )
   {
      g_log.fatal( "Error setting up EXD data " );
      return 0;
   }
  
   std::string result = 
   "/* This file has been automatically generated.\n   Changes will be lost upon regeneration.\n   To change the content edit tools/exd_struct_gen */\n";

   result += generateEnum( "Quest" );      
   g_log.info( result );
   return 0;
}
