
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

const std::string datLocation( "/home/mordred/sqpack" );
//const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );

bool invalidChar( char c ) 
{  
  return !( c >= 0 && c < 128 );   
} 
void stripUnicode( std::string& str ) 
{ 
    str.erase( std::remove_if( str.begin(), str.end(), invalidChar ), str.end() ); 
   str.erase(std::remove_if(str.begin(), str.end(),
                            [](char c) { return !std::isalpha(c) && !std::isdigit(c) && !std::isspace(c) && !std::ispunct(c); }),
             str.end()); 
}

int main()
{

  Logger::init( "action_parse" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }
  auto idList = g_exdData.getActionIdList();

  for( auto id : idList )
  {
  auto gld = g_exdData.get< Sapphire::Data::Action >( id );
  auto gld1 = g_exdData.get< Sapphire::Data::ActionTransient >( id );
  if( gld )
  {
    Logger::info( "got {0}", gld->name );
    std::string desc = gld1->description;
    stripUnicode( desc );;
    desc = std::regex_replace( desc, std::regex( "HI" ), "\n" );
    desc = std::regex_replace( desc, std::regex( "IH" ), "" );
//    Logger::info( "got {0}", desc );
    
    std::smatch sm;
    std::regex r(R"(with a potency of \d*)");
    if( std::regex_search(desc, sm, r ) )
    {
      std::string potStr = sm.str();
      auto pos = potStr.find_last_of( " " );
      if( pos  != std::string::npos )
      {
        potStr = potStr.substr( pos + 1 );
	Logger::info( "Base Potency: {}", potStr);
      }
    }
    
    std::smatch sm1;
    std::regex r1(R"(\d* when executed from a target's rear)");
    if( std::regex_search(desc, sm1, r1 ) )
    {
      std::string potStr = sm1.str();
      auto pos = potStr.find_first_of( " " );
      if( pos  != std::string::npos )
      {
        potStr = potStr.substr( 0, pos );
	Logger::info( "Rear Potency: {}", potStr);
      }
    }

    std::smatch sm2;
    std::regex r2(R"(\d* when executed from a target's flank)");
    if( std::regex_search(desc, sm2, r2 ) )
    {
      std::string potStr = sm2.str();
      auto pos = potStr.find_first_of( " " );
      if( pos  != std::string::npos )
      {
        potStr = potStr.substr( 0, pos );
	Logger::info( "Flank Potency: {}", potStr);
      }
    }

    std::smatch sm3;
    std::regex r3(R"(\d* when executed in front of target)");
    if( std::regex_search(desc, sm3, r3 ) )
    {
      std::string potStr = sm3.str();
      auto pos = potStr.find_first_of( " " );
      if( pos  != std::string::npos )
      {
        potStr = potStr.substr( 0, pos );
	Logger::info( "Frontal Potency: {}", potStr);
      }
    }
    
    std::smatch sm4;
    std::regex r4(R"(Combo Potency: \d*)");
    if( std::regex_search(desc, sm4, r4 ) )
    {
      std::string potStr = sm4.str();
      auto pos = potStr.find_last_of( " " );
      if( pos  != std::string::npos )
      {
        potStr = potStr.substr( pos + 1 );
	Logger::info( "Combo Potency: {}", potStr);
      }
    }

  }
  else
    Logger::warn( "failed to get classjob {}", 1 );
  }

  return 0;
}
