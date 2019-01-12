
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <iostream>
#include <cctype>
#include <set>
#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <algorithm>
#include <Util/Util.h>


#include <fstream>

Sapphire::Data::ExdDataGenerated g_exdData;

using namespace Sapphire;

//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );

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

    std::string value;
    try
    {
      value = std::get< std::string >( fields.at( nameIndex ) );
    }
    catch( std::bad_variant_access& )
    {
      continue;
    }

    std::string remove = ",_-':!(){} \x02\x1f\x01\x03";
    Sapphire::Util::eraseAllIn( value, remove );

    value[ 0 ] = std::toupper( value[ 0 ] );

    auto it = nameMap.find( value );
    if( it != nameMap.end() )
    {
      nameMap[ value ]++;
      value = value + std::to_string( nameMap[ value ] );
    }
    else
    {
      nameMap[ value ] = 0;
    }

    result += "      " + value + " = " + std::to_string( id ) + ",\n";

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

  Logger::init( "commongen" );


  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 1;
  }

  std::string result = "#ifndef _COMMON_GEN_H_\n#define _COMMON_GEN_H_\n";

  result += "\n#include <stdint.h>\n\n";

  result +=
    "/* This file has been automatically generated.\n   Changes will be lost upon regeneration.\n   To change the content edit tools/exd_common_gen */\n";


  result += "namespace Sapphire {\n";
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
  result += generateEnum( "HousingAppeal", 0, "uint8_t" );
  result += "}\n";
  result += "}\n#endif\n";
  Logger::info( result );
  return 0;
}
