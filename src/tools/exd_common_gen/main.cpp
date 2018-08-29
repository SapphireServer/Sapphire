
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <iostream>
#include <cctype>
#include <set>
#include <Exd/ExdData.h>
#include <Logging/Logger.h>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <fstream>


Core::Logger g_log;
Core::Data::ExdData g_exdData;


//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
const std::string datLocation(
  "C:\\Data\\Games\\Final Fantasy XIV\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv" );

std::string generateEnum( const std::string& exd, int8_t nameIndex, const std::string& type, bool useLang = true )
{

  xiv::dat::GameData data( datLocation );
  xiv::exd::ExdData eData( data );

  std::map< std::string, uint32_t > nameMap;

  std::string result = "\n   ///////////////////////////////////////////////////////////\n";
  result += "   //" + exd + ".exd\n";
  result += "   enum class " + exd + " : " + type + "\n";
  result += "   {\n";
  auto lang = useLang ? xiv::exd::Language::en : xiv::exd::Language::none;
  auto access = g_exdData.setupDatAccess( exd, lang );
  auto rows = access.get_rows();

  for( auto row : rows )
  {
    auto& fields = row.second;
    uint32_t id = row.first;
    auto test = boost::get< std::string >( &fields.at( nameIndex ) );
    if( !test )
      continue;
    auto str = *test;
    str.erase( boost::remove_if( str, boost::is_any_of( ",_-':!(){} \x02\x1f\x01\x03" ) ), str.end() );
    if( str.empty() )
      continue;
    str[ 0 ] = std::toupper( str[ 0 ] );

    auto it = nameMap.find( str );
    if( it != nameMap.end() )
    {
      nameMap[ str ]++;
      str = str + std::to_string( nameMap[ str ] );
    }
    else
    {
      nameMap[ str ] = 0;
    }

    result += "      " + str + " = " + std::to_string( id ) + ",\n";

  }

  /*
  result +=
          "      bool operator==( const " + exd + "& t, const " + type + "& g ) { return static_cast< " + type + " >( t ) == g; }\n"
          "      bool operator==( const " + type + "& g, const " + exd + "& t ) { return static_cast< " + type + " >( t ) == g; }\n";
  */

  result += "   };\n";

  return result;

}

int main()
{

  g_log.init();


  g_log.info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    g_log.fatal( "Error setting up EXD data " );
    return 1;
  }

  std::string result = "#ifndef _COMMON_GEN_H_\n#define _COMMON_GEN_H_\n";

  result += "\n#include <stdint.h>\n\n";

  result +=
    "/* This file has been automatically generated.\n   Changes will be lost upon regeneration.\n   To change the content edit tools/exd_common_gen */\n";


  result += "namespace Core {\n";
  result += "namespace Common {\n";
  result += generateEnum( "ActionCategory", 0, "uint8_t" );
  result += generateEnum( "BeastReputationRank", 1, "uint8_t" );
  result += generateEnum( "BeastTribe", 11, "uint8_t" );
  result += generateEnum( "ClassJob", 0, "uint8_t" );
  result += generateEnum( "ContentType", 0, "uint8_t" );
  result += generateEnum( "EmoteCategory", 0, "uint8_t" );
  result += generateEnum( "ExVersion", 0, "uint8_t" );
  result += generateEnum( "GrandCompany", 0, "uint8_t" );
  result += generateEnum( "GuardianDeity", 0, "uint8_t" );
  result += generateEnum( "ItemUICategory", 0, "uint8_t" );
  result += generateEnum( "ItemSearchCategory", 0, "uint8_t" );
  result += generateEnum( "OnlineStatus", 2, "uint8_t" );
  result += generateEnum( "Race", 1, "uint8_t" );
  result += generateEnum( "Tribe", 0, "uint8_t" );
  result += generateEnum( "Town", 0, "uint8_t" );
  result += generateEnum( "Weather", 1, "uint8_t" );
  result += "}\n";
  result += "}\n#endif\n";
  g_log.info( result );
  return 0;
}
