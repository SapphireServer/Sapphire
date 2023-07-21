
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
#include <string>
#include <Exd/ExdData.h>
#include <Exd/Structs.h>
#include <Logging/Logger.h>
#include <Common.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <streambuf>
#include <regex>

#include <filesystem>

namespace fs = std::filesystem;

using namespace Sapphire;
Sapphire::Data::ExdData g_exdDataGen;

//std::string datLocation( "F:\\client3.0\\game\\sqpack" );
std::string datLocation( "C:\\Data\\Dev\\ffxiv3.01\\game\\sqpack" );
//const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );

struct StatusModifier
{
  Common::ParamModifier modifier;
  int32_t value;
};

struct StatusEntry
{
  uint16_t id;
  int32_t duration;
  uint32_t flag;
  bool canApplyMultipleTimes;
  std::vector< StatusModifier > modifiers;
};

struct StatusEffect
{
  std::vector< StatusEntry > caster;
  std::vector< StatusEntry > target;
};

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
  std::vector< uint32_t > nextCombo{};
  StatusEffect statuses;
};

void to_json( nlohmann::ordered_json& j, const StatusModifier& statusModifier)
{
  j = nlohmann::ordered_json{
    { "modifier", statusModifier.modifier },
    { "value", statusModifier.value }
  };
}

void to_json( nlohmann::ordered_json& j, const StatusEntry& statusEntry )
{
  j = nlohmann::ordered_json{
    { "id", statusEntry.id },
    { "duration", statusEntry.duration },
    { "flag", statusEntry.flag },
    { "modifiers", statusEntry.modifiers }
  };
}

void to_json( nlohmann::ordered_json& j, const ActionEntry& action )
{
  j = nlohmann::ordered_json{
    { "name", action.name },
    { "potency", action.potency },
    { "comboPotency", action.comboPotency },
    { "flankPotency", action.flankPotency },
    { "frontPotency", action.frontPotency },
    { "rearPotency", action.rearPotency },
    { "curePotency", action.curePotency },
    { "restorePercentage", action.restorePercentage },
    { "nextCombo", action.nextCombo },
    { "statuses", {
        { "caster", action.statuses.caster },
        { "target", action.statuses.target },
      }
    }
  };
}

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

template< typename T >
std::string stringVec( const std::vector< T >& vec )
{
  if( vec.empty() )
    return "";

  std::ostringstream oss;
  std::copy( vec.begin(), vec.end() - 1, std::ostream_iterator< T >( oss, ", " ) );
  oss << vec.back();

  return oss.str();
}

int main( int argc, char* argv[] )
{

  Logger::init( "action_parse" );

  if( argc == 2 )
  {
    datLocation = std::string( argv[ 1 ] );
  }

  Logger::info( "Setting up EXD data" );
  if( !g_exdDataGen.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }
  auto idList = g_exdDataGen.getIdList< Excel::Action >();

  std::map< uint32_t, ActionEntry > actions;
  std::map< uint32_t, std::vector< uint32_t > > traversedCombos;

  auto total = idList.size();
  int cursor = 0;

  for( auto id : idList )
  {
    auto done = ( cursor++ / static_cast< float >( total ) ) * 100.f;
    if( cursor % 50 == 0 && cursor > 0 )
      Logger::info( "Processing {} actions of {} ({:.2f}%)", cursor, total, done );

    auto action = g_exdDataGen.getRow< Excel::Action >( id );

    //auto actionTransient = g_exdData.get< Sapphire::Data::ActionTransient >( id );
    if( action )
    {
      auto& actionData = action->data();

      if( actionData.UseClassJob == -1 || action->getString( actionData.Text.Name ).empty() )
        continue;

      //if( actionData.PvPOnly )
      //  continue;

   //   auto classJob = g_exdDataGen.getRow< Excel::ClassJob >( actionData.UseClassJob );
   //   if( !classJob )
   //     continue;

      // exclude dol/doh
    //  if( classJob->data().CraftingClassIndex > 0 )
    //    continue;

      auto ac = static_cast< Common::ActionCategory >( actionData.Category );
      if( ac != Common::ActionCategory::Ability &&
          ac != Common::ActionCategory::Autoattack &&
          ac != Common::ActionCategory::Spell &&
          ac != Common::ActionCategory::Weaponskill &&
          ac != Common::ActionCategory::LimitBreak )
        continue;

      ActionEntry entry{};

      entry.name = action->getString( actionData.Text.Name );
      entry.id = id;

      Logger::info( "  {0} - {1}", id, action->getString( actionData.Text.Name ) );
      std::string desc = action->getString( actionData.Text.Help );
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
      if( actionData.ComboParent )
        traversedCombos[ actionData.ComboParent ].push_back( id );
    }
    else
      Logger::warn( "failed to get classjob {}", 1 );
  }

  // dump entries
  Logger::info( "Found {} player actions", actions.size() );

  nlohmann::ordered_json output;
  Logger::info( std::to_string( traversedCombos.size() ) );
  for( const auto& action : actions )
  {
    auto data = action.second;
    // check if we have combo data to insert
    if( auto it{ traversedCombos.find( data.id ) }; it != std::end( traversedCombos ) )
      data.nextCombo = traversedCombos[ data.id ];
//    Logger::info( " - {:<5} {:<25} pot: {:<4} flank pot: {:<4} front pot: {:<4} rear pot: {:<4} cure pot: {:<4} restore %: {:<4}",
//                  action.first, data.name, data.potency, data.flankPotency, data.frontPotency, data.rearPotency,
//                  data.curePotency, data.restorePercentage );

    output[ std::to_string(action.first) ] = data;
  }

  std::ofstream outH( "actions/player.json" );
  outH << std::setw( 2 ) << output << std::endl;
  outH.close();

  return 0;
}
