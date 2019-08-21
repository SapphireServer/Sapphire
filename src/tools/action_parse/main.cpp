
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
#include <Common.h>

#include <fstream>
#include <streambuf>
#include <regex>

#include <experimental/filesystem>

Sapphire::Data::ExdDataGenerated g_exdData;

namespace fs = std::experimental::filesystem;

using namespace Sapphire;

const std::string datLocation( "/home/mordred/sqpack" );
//const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );

struct ActionEntry
{
  uint32_t id;
  std::string name;
  uint32_t potency;
  uint32_t comboPotency;
  uint32_t flankPotency;
  uint32_t frontPotency;
  uint32_t rearPotency;
  uint32_t curePotency;
  uint32_t restorePercentage;
};

bool invalidChar( char c )
{
  return !( c >= 0 && c < 128 );
}

void stripUnicode( std::string& str )
{
  str.erase( std::remove_if( str.begin(), str.end(), invalidChar ), str.end() );
  str.erase( std::remove_if( str.begin(), str.end(),
                             []( char c )
                             {
                               return !std::isalpha( c ) && !std::isdigit( c ) && !std::isspace( c ) &&
                                      !std::ispunct( c );
                             } ),
             str.end() );
}

uint32_t stripNonNumerics( std::string& str )
{
  str.erase( std::remove_if( str.begin(), str.end(),
    []( char c )
    {
      return !std::isdigit( c );
    }), str.end() );

  return std::atoi( str.c_str() );
}

int main()
{

  Logger::init( "action_parse" );

  if( !fs::exists( "ActionLutData.cpp.tmpl" ) )
    throw std::runtime_error( "ActionLut.cpp.tmpl is missing in working directory" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }
  auto idList = g_exdData.getActionIdList();

  std::map< uint32_t, ActionEntry > actions;

  auto total = idList.size();
  int cursor = 0;

  for( auto id : idList )
  {
    auto done = ( cursor++ / static_cast< float >( total ) ) * 100.f;
    if( cursor % 50 == 0 && cursor > 0 )
      Logger::info( "Processing {} actions of {} ({:.2f}%)", cursor, total, done );

    auto action = g_exdData.get< Sapphire::Data::Action >( id );
    auto actionTransient = g_exdData.get< Sapphire::Data::ActionTransient >( id );
    if( action )
    {
      if( action->classJob == -1 || action->name.empty() )
        continue;

      if( action->isPvP )
        continue;

      auto classJob = g_exdData.get< Sapphire::Data::ClassJob >( action->classJob );
      if( !classJob )
        continue;

      // exclude dol/doh
      if( classJob->classJobCategory == 32 || classJob->classJobCategory == 33 )
        continue;

      auto ac = static_cast< Common::ActionCategory >( action->actionCategory );
      if( ac != Common::ActionCategory::Ability &&
          ac != Common::ActionCategory::Autoattack &&
          ac != Common::ActionCategory::Spell &&
          ac != Common::ActionCategory::Weaponskill &&
          ac != Common::ActionCategory::LimitBreak )
        continue;

      ActionEntry entry{};

      entry.name = action->name;
      entry.id = id;

      Logger::info( "  {0} - {1}", id, action->name );
      std::string desc = actionTransient->description;
      stripUnicode( desc );
      desc = std::regex_replace( desc, std::regex( "HI" ), "\n" );
      desc = std::regex_replace( desc, std::regex( "IH" ), "" );
//    Logger::info( "got {0}", desc );

      std::smatch sm;
      std::regex r( R"(with a potency of [\d,]*)" );
      if( std::regex_search( desc, sm, r ) )
      {
        std::string potStr = sm.str();
        auto pos = potStr.find_last_of( " " );
        if( pos != std::string::npos )
        {
          potStr = potStr.substr( pos + 1 );
//          Logger::info( "Base Potency: {}", potStr );
          entry.potency = stripNonNumerics( potStr );
        }
      }

      std::smatch sm1;
      std::regex r1( R"([\d,]* when executed from a target's rear)" );
      if( std::regex_search( desc, sm1, r1 ) )
      {
        std::string potStr = sm1.str();
        auto pos = potStr.find_first_of( " " );
        if( pos != std::string::npos )
        {
          potStr = potStr.substr( 0, pos );
//          Logger::info( "Rear Potency: {}", potStr );
          entry.rearPotency = stripNonNumerics( potStr );
        }
      }

      std::smatch sm2;
      std::regex r2( R"([\d,]* when executed from a target's flank)" );
      if( std::regex_search( desc, sm2, r2 ) )
      {
        std::string potStr = sm2.str();
        auto pos = potStr.find_first_of( " " );
        if( pos != std::string::npos )
        {
          potStr = potStr.substr( 0, pos );
//          Logger::info( "Flank Potency: {}", potStr );
          entry.flankPotency = stripNonNumerics( potStr );
        }
      }

      std::smatch sm3;
      std::regex r3( R"([\d,]* when executed in front of target)" );
      if( std::regex_search( desc, sm3, r3 ) )
      {
        std::string potStr = sm3.str();
        auto pos = potStr.find_first_of( " " );
        if( pos != std::string::npos )
        {
          potStr = potStr.substr( 0, pos );
//          Logger::info( "Frontal Potency: {}", potStr );
          entry.frontPotency = stripNonNumerics( potStr );
        }
      }

      std::smatch sm4;
      std::regex r4( R"(Combo Potency: [\d,]*)" );
      if( std::regex_search( desc, sm4, r4 ) )
      {
        std::string potStr = sm4.str();
        auto pos = potStr.find_last_of( " " );
        if( pos != std::string::npos )
        {
          potStr = potStr.substr( pos + 1 );
//          Logger::info( "Combo Potency: {}", potStr );
          entry.comboPotency = stripNonNumerics( potStr );
        }
      }

      std::smatch sm5;
      std::regex r5( R"(Cure Potency: [\d,]*)" );
      if( std::regex_search( desc, sm5, r5 ) )
      {
        std::string potStr = sm5.str();
        auto pos = potStr.find_last_of( " " );
        if( pos != std::string::npos )
        {
          potStr = potStr.substr( pos + 1 );
//          Logger::info( "Cure Potency: {}", potStr );
          entry.curePotency = stripNonNumerics( potStr );
        }
      }

      std::smatch sm6;
      std::regex r6( R"(Restores \d*%)" );
      if( std::regex_search( desc, sm6, r6 ) )
      {
        std::string resStr = sm6.str();
        auto pos = resStr.find_last_of( " " );
        if( pos != std::string::npos )
        {
          resStr = resStr.substr( pos + 1 );
//          Logger::info( "Cure Percentage: {}", resStr );
          entry.restorePercentage = stripNonNumerics( resStr );
        }
      }

      actions[ id ] = std::move( entry );
    }
    else
      Logger::warn( "failed to get classjob {}", 1 );
  }

  // dump entries
  Logger::info( "Found {} player actions", actions.size() );

  std::string output;
  for( const auto& action : actions )
  {
    const auto& data = action.second;
//    Logger::info( " - {:<5} {:<25} pot: {:<4} flank pot: {:<4} front pot: {:<4} rear pot: {:<4} cure pot: {:<4} restore %: {:<4}",
//                  action.first, data.name, data.potency, data.flankPotency, data.frontPotency, data.rearPotency,
//                  data.curePotency, data.restorePercentage );

    auto out = fmt::format( "  // {}\n  {{ {}, {{ {}, {}, {}, {}, {}, {} }} }},\n",
                            data.name, action.first,
                            data.potency, data.comboPotency,
                            data.flankPotency, data.frontPotency, data.rearPotency,
                            data.curePotency );

    output += out;
//    Logger::info( out );
  }

  std::ifstream ifs( "ActionLutData.cpp.tmpl" );

  std::string actionTmpl( ( std::istreambuf_iterator< char >( ifs ) ),
                            std::istreambuf_iterator< char >() );

  auto result = std::regex_replace( actionTmpl, std::regex( "%INSERT_GARBAGE%" ), output );

  std::ofstream outH( "ActionLutData.cpp" );
  outH << result;
  outH.close();

  return 0;
}
