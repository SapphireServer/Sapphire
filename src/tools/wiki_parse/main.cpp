
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

#include <fstream>
#include <streambuf>

#include <filesystem>

namespace fs = std::filesystem;

using namespace Sapphire;
Sapphire::Data::ExdData g_exdDataGen;

//std::string datLocation( "F:\\client3.0\\game\\sqpack" );
std::string datLocation( "C:\\Data\\Dev\\ffxiv3.35\\game\\sqpack" );
//const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );

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
  Logger::init( "wiki_parse" );

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

  // CFC list
  {

    auto cfcList = g_exdDataGen.getRows< Excel::ContentFinderCondition >();

    std::stringstream cfcOutputStream;

    auto total = cfcList.size();
    int cursor = 0;

    std::map< uint8_t, std::string > instanceContentTypeMap;
    instanceContentTypeMap[ 0 ] = "";
    instanceContentTypeMap[ 1 ] = "Raid";
    instanceContentTypeMap[ 2 ] = "Dungeon";
    instanceContentTypeMap[ 3 ] = "Guildhest";
    instanceContentTypeMap[ 4 ] = "Trial";
    instanceContentTypeMap[ 5 ] = "PvP (The Feast)";
    instanceContentTypeMap[ 6 ] = "PvP";
    instanceContentTypeMap[ 7 ] = "Quest Battle";
    instanceContentTypeMap[ 8 ] = "Hall of the Novice";
    instanceContentTypeMap[ 9 ] = "Deep Dungeon";
    instanceContentTypeMap[ 10 ] = "Treasure Hunt";
    instanceContentTypeMap[ 11 ] = "Event";
    instanceContentTypeMap[ 12 ] = "PvP (Rival Wings)";
    instanceContentTypeMap[ 13 ] = "Masked Carnivale";
    instanceContentTypeMap[ 14 ] = "Goldsaucer (Mahjong)";
    instanceContentTypeMap[ 15 ] = "Goldsaucer";


    cfcOutputStream << "| ID | Instance | Territory | Name | Type |" << std::endl
                    << "| --- | --- | --- | --- | --- |" << std::endl;

    for( const auto& [ id, cfc ] : cfcList )
    {
      auto done = ( cursor++ / static_cast< float >( total ) ) * 100.f;
      if( cursor % 50 == 0 && cursor > 0 )
        Logger::info( "Processing {} CFCs of {} ({:.2f}%)", cursor, total, done );

      if( id == 0 )
        continue;

      if( cfc )
      {
        auto& cfcData = cfc->data();

        auto pInstanceContent = g_exdDataGen.getRow< Excel::InstanceContent >( cfcData.InstanceContentId );
        if( !pInstanceContent )
          continue;

        auto name = pInstanceContent->getString( pInstanceContent->data().Text.Name );

        // cfc ID
        cfcOutputStream << "| " << std::to_string( id ) << " | ";

        // instance ID
        cfcOutputStream << std::to_string( cfcData.InstanceContentId ) << " | ";

        // territory type
        cfcOutputStream << std::to_string( pInstanceContent->data().TerritoryType ) << " | ";

        // instance name
        cfcOutputStream << name << " | ";

        // instance type
        cfcOutputStream << instanceContentTypeMap[ pInstanceContent->data().Type ] << " |" << std::endl;
      }
    }

    Logger::info( cfcOutputStream.str() );
    std::ofstream outH( "generated/cfc.txt" );
    outH << cfcOutputStream.str() << std::endl;
    outH.close();
  }

  // territory type list
  {
    
    enum TerritoryIntendedUse : uint8_t
    {
      Town = 0,
      OpenWorld = 1,
      Inn = 2,
      Dungeon = 3,
      JailArea = 5,
      OpeningArea = 6,
      BeforeTrialDung = 7,
      AllianceRaid = 8,
      OpenWorldInstanceBattle = 9,
      Trial = 10,
      HousingArea = 13,
      HousingPrivateArea = 14,
      MSQPrivateArea = 15,
      Raids = 16,
      RaidFights = 17,
      ChocoboSquare = 19,
      ChocoboTutorial = 21,
      Wedding = 22,
      GoldSaucer = 23,
      DiademV1 = 26,
      BeginnerTutorial = 27,
      PvPTheFeast = 28,
      MSQEventArea = 29,
      FreeCompanyGarrison = 30,
      PalaceOfTheDead = 31,
      TreasureMapInstance = 33,
      EventTrial = 36,
      TheFeastArea = 37,
      PrivateEventArea = 40,
      //Eureka = 41, // wat
    };

    std::map< uint8_t, std::string > teriTypeIntendedUseMap;
    for( int i = 0; i < 255; ++i )
    {
      teriTypeIntendedUseMap[ i ] = "Unknown";
    }
    teriTypeIntendedUseMap[ Town ] = "Town";
    teriTypeIntendedUseMap[ OpenWorld ] = "OpenWorld";
    teriTypeIntendedUseMap[ Inn ] = "Inn";
    teriTypeIntendedUseMap[ Dungeon ] = "Dungeon";
    teriTypeIntendedUseMap[ JailArea ] = "JailArea";
    teriTypeIntendedUseMap[ OpeningArea ] = "OpeningArea";
    teriTypeIntendedUseMap[ BeforeTrialDung ] = "BeforeTrialDung";
    teriTypeIntendedUseMap[ AllianceRaid ] = "AllianceRaid";
    teriTypeIntendedUseMap[ OpenWorldInstanceBattle ] = "OpenWorldInstanceBattle";
    teriTypeIntendedUseMap[ Trial ] = "Trial";
    teriTypeIntendedUseMap[ HousingArea ] = "HousingArea";
    teriTypeIntendedUseMap[ HousingPrivateArea ] = "HousingPrivateArea";
    teriTypeIntendedUseMap[ MSQPrivateArea ] = "MSQPrivateArea";
    teriTypeIntendedUseMap[ Raids ] = "Raids";
    teriTypeIntendedUseMap[ RaidFights ] = "RaidFights";
    teriTypeIntendedUseMap[ ChocoboSquare ] = "ChocoboSquare";
    teriTypeIntendedUseMap[ ChocoboTutorial ] = "ChocoboTutorial";
    teriTypeIntendedUseMap[ Wedding ] = "Wedding";
    teriTypeIntendedUseMap[ GoldSaucer ] = "GoldSaucer";
    teriTypeIntendedUseMap[ DiademV1 ] = "DiademV1";
    teriTypeIntendedUseMap[ BeginnerTutorial ] = "BeginnerTutorial";
    teriTypeIntendedUseMap[ PvPTheFeast ] = "PvPTheFeast";
    teriTypeIntendedUseMap[ MSQEventArea ] = "MSQEventArea";
    teriTypeIntendedUseMap[ FreeCompanyGarrison ] = "FreeCompanyGarrison";
    teriTypeIntendedUseMap[ PalaceOfTheDead ] = "PalaceOfTheDead";
    teriTypeIntendedUseMap[ TreasureMapInstance ] = "TreasureMapInstance";
    teriTypeIntendedUseMap[ EventTrial ] = "EventTrial";
    teriTypeIntendedUseMap[ TheFeastArea ] = "TheFeastArea";
    teriTypeIntendedUseMap[ PrivateEventArea ] = "PrivateEventArea";

    auto teriList = g_exdDataGen.getRows< Excel::TerritoryType >();

    std::stringstream teritypeOutputStream;

    teritypeOutputStream << "| ID | Place Name | Name | Intended Use |" << std::endl
                         << "| --- | --- | --- | --- |" << std::endl;

    auto total = teriList.size();
    int cursor = 0;

    for( const auto& [ id, teriType ] : teriList )
    {
      auto done = ( cursor++ / static_cast< float >( total ) ) * 100.f;
      if( cursor % 50 == 0 && cursor > 0 )
        Logger::info( "Processing {} teritypes of {} ({:.2f}%)", cursor, total, done );

      if( teriType )
      {
        auto& teriTypeData = teriType->data();

        auto name = teriType->getString( teriTypeData.Name );
        std::string placeName = "";

        auto pPlaceName = g_exdDataGen.getRow< Excel::PlaceName >( teriTypeData.Area );
        if( pPlaceName )
        {
          placeName = pPlaceName->getString( pPlaceName->data().Text.SGL );
        }

        if( placeName == "" )
          placeName = "[empty]";

        // teritype ID
        teritypeOutputStream << "| " << std::to_string( id ) << " | ";

        // aetheryte placename
        teritypeOutputStream << placeName << " | ";

        // name
        teritypeOutputStream << name << " | ";

        // territory intended use
        teritypeOutputStream << teriTypeIntendedUseMap[ teriTypeData.IntendedUse ] << " |" << std::endl;
        
      }
    }

    Logger::info( teritypeOutputStream.str() );
    std::ofstream outH( "generated/teritype.txt" );
    outH << teritypeOutputStream.str() << std::endl;
    outH.close();
  }

  // class/job list
  {
    auto classJobList = g_exdDataGen.getRows< Excel::ClassJob >();

    std::stringstream classjobOutputStream;

    classjobOutputStream << "| ID | Name | Short | Main Class |" << std::endl
                         << "| --- | --- | --- | --- |" << std::endl;

    auto total = classJobList.size();
    int cursor = 0;

    for( const auto& [ id, classJob ] : classJobList )
    {
      auto done = ( cursor++ / static_cast< float >( total ) ) * 100.f;
      if( cursor % 50 == 0 && cursor > 0 )
        Logger::info( "Processing {} classjobs of {} ({:.2f}%)", cursor, total, done );

      if( classJob )
      {
        auto& classJobData = classJob->data();

        auto name = classJob->getString( classJobData.Text.Name );
        auto shortName = classJob->getString( classJobData.Text.Abbreviation );

        // ID
        classjobOutputStream << "| " << std::to_string( id ) << " | ";

        // name
        classjobOutputStream << name << " | ";

        // short name
        classjobOutputStream << shortName << " | ";

        // main class
        classjobOutputStream << std::to_string( classJobData.MainClass ) << " |" << std::endl;
      }
    }

    Logger::info( classjobOutputStream.str() );
    std::ofstream outH( "generated/classjob.txt" );
    outH << classjobOutputStream.str() << std::endl;
    outH.close();
  }

  // achievement list
  {
    auto achvList = g_exdDataGen.getRows< Excel::Achievement >();

    enum class Type : uint8_t
    {
      None,
      General,
      LinkedAchievement,
      Classjob,
      Unknown_4,// Materia related? id 304
      Unknown_5,// Hunt related? id 1259
      Quest,    // Quests that need all required args met
      Unknown_7,
      Unknown_8,// Map discovery related
      QuestAny, // Quests that need any required args met
      ChocoboRank,
      PvPRank,
      WolvesDenMatches,
      WolvesDenWins,
      InstanceContent,
      BeastTribeReputation,
      Unknown_16,
      FrontlineMatches,
      FrontlineWinsGC,
      FrontlineWinsAll,
      AetherCurrent,
    };

    std::map< Common::Achievement::Type, std::string > achievementTypeMap;

    achievementTypeMap[ Common::Achievement::Type::None ] = "None";
    achievementTypeMap[ Common::Achievement::Type::General ] = "General";
    achievementTypeMap[ Common::Achievement::Type::LinkedAchievement ] = "LinkedAchievement";
    achievementTypeMap[ Common::Achievement::Type::Classjob ] = "Classjob";
    achievementTypeMap[ Common::Achievement::Type::Unknown_4 ] = "Unknown_4";
    achievementTypeMap[ Common::Achievement::Type::Unknown_5 ] = "Unknown_5";
    achievementTypeMap[ Common::Achievement::Type::Quest ] = "Quest";
    achievementTypeMap[ Common::Achievement::Type::Unknown_7 ] = "Unknown_7";
    achievementTypeMap[ Common::Achievement::Type::MapDiscovery ] = "MapDiscovery";
    achievementTypeMap[ Common::Achievement::Type::QuestAny ] = "QuestAny";
    achievementTypeMap[ Common::Achievement::Type::ChocoboRank ] = "ChocoboRank";
    achievementTypeMap[ Common::Achievement::Type::PvPRank ] = "PvPRank";
    achievementTypeMap[ Common::Achievement::Type::WolvesDenMatches ] = "WolvesDenMatches";
    achievementTypeMap[ Common::Achievement::Type::WolvesDenWins ] = "WolvesDenWins";
    achievementTypeMap[ Common::Achievement::Type::InstanceContent ] = "InstanceContent";
    achievementTypeMap[ Common::Achievement::Type::BeastTribeReputation ] = "BeastTribeReputation";
    achievementTypeMap[ Common::Achievement::Type::Unknown_16 ] = "Unknown_16";
    achievementTypeMap[ Common::Achievement::Type::FrontlineMatches ] = "FrontlineMatches";
    achievementTypeMap[ Common::Achievement::Type::FrontlineWinsGC ] = "FrontlineWinsGC";
    achievementTypeMap[ Common::Achievement::Type::FrontlineWinsAll ] = "FrontlineWinsAll";
    achievementTypeMap[ Common::Achievement::Type::AetherCurrent ] = "AetherCurrent";

    std::stringstream achvOutputStream;

    achvOutputStream << "| ID | Name | Type (Subtype) | Description |" << std::endl
                         << "| --- | --- | --- | --- |" << std::endl;

    auto total = achvList.size();
    int cursor = 0;

    for( const auto& [ id, pAchv ] : achvList )
    {
      auto done = ( cursor++ / static_cast< float >( total ) ) * 100.f;
      if( cursor % 50 == 0 && cursor > 0 )
        Logger::info( "Processing {} achievements of {} ({:.2f}%)", cursor, total, done );

      if( pAchv )
      {
        auto& achvData = pAchv->data();

        auto achvType = static_cast< Common::Achievement::Type >( achvData.ConditionType );
        std::string type = std::to_string( achvData.ConditionType );

        // verify if achievement type has already been added
        if( achvType == Common::Achievement::Type::General ||
            achvType == Common::Achievement::Type::Classjob ||
            achvType == Common::Achievement::Type::InstanceContent )
        {
          type = std::to_string( achvData.ConditionType ) + ", " + std::to_string( achvData.ConditionArg[ 0 ] );
        }

        auto name = pAchv->getString( achvData.Text.Name );
        auto desc = pAchv->getString( achvData.Text.Help );

        // ID
        achvOutputStream << "| " << std::to_string( id ) << " | ";

        // name
        achvOutputStream << name << " | ";

        // type (+subtype)
        achvOutputStream << achievementTypeMap[ achvType ] << " (" << type << ") | ";

        // desc
        achvOutputStream << desc << " |" << std::endl;
      }
    }

    Logger::info( achvOutputStream.str() );
    std::ofstream outH( "generated/achievement.txt" );
    outH << achvOutputStream.str() << std::endl;
    outH.close();
  }


  return 0;
}
