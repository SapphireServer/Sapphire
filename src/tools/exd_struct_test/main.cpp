
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
const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );


int main()
{

  Logger::init( "struct_test" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }

  auto gld = g_exdData.get< Sapphire::Data::ClassJob >( 1 );
  if( gld )
  {
    Logger::info( "got {0}", gld->name );
  }
  else
    Logger::warn( "failed to get classjob {}", 1 );


  return 0;
}
