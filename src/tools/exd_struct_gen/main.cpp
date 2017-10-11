
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
std::map< uint8_t, std::string > g_typeMap;


std::string generateEnum( const std::string& exd )
{

   auto& cat = g_exdData.m_exd_data->get_category( exd );
   auto exh = cat.get_header();
   auto exhMem = exh.get_exh_members();
  
   int count = 0;

   std::string result = "struct " + exd +"\n{\n";

   for( auto member : exhMem )
   {
      auto typei = static_cast< uint8_t >( member.type );
      auto it = g_typeMap.find( typei );

      std::string type;
      if( it != g_typeMap.end() )
         type = it->second; 
      else
         type = "bool(" + std::to_string( static_cast< uint8_t >( member.type ) ) + ")"; 
     
      result += "   " + type + " field" + std::to_string( count ) + ";\n";
   
      count++;
   }
   
   result += "};\n";
   
   return result;
}

int main()
{
   g_typeMap[0] = "char";
   g_typeMap[1] = "bool";
   g_typeMap[2] = "int8_t";
   g_typeMap[3] = "uint8_t";
   g_typeMap[4] = "int16_t";
   g_typeMap[5] = "uint16_t";
   g_typeMap[6] = "int32";
   g_typeMap[7] = "uint32_t";
   g_typeMap[9] = "float";
   g_typeMap[11] = "uint64_t";

   g_log.init();


   g_log.info( "Setting up EXD data" );
   if( !g_exdData.init( datLocation  ) )
   {
      g_log.fatal( "Error setting up EXD data " );
      return 0;
   }
  
   std::string result = 
   "/* This file has been automatically generated.\n   Changes will be lost upon regeneration.\n   To change the content edit tools/exd_struct_gen */\n";

   result += generateEnum( "TerritoryType" );      
   g_log.info( result );
   return 0;
}
