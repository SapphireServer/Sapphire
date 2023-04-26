#include "ConfigMgr.h"
#include <iostream>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

using namespace Sapphire;
using namespace Sapphire::Common;

/**
 * Loads an ini file and parses it
 * @param configName the name of ini file relative to m_configFolderRoot to load alongside global.ini
 * @return true if loading was successful
 */
bool ConfigMgr::loadConfig( const std::string& configName )
{
  // get global config
  auto configFile = fs::path( fs::path( m_configFolderRoot ) / configName );

  if( !fs::exists( configFile ) )
  {
    copyDefaultConfig( configName );
    return false;
  }

  m_pInih = std::make_unique< INIReader >( configFile.string() );

  if( m_pInih->ParseError() < 0 )
    return false;

  return true;
}

bool ConfigMgr::loadGlobalConfig( Common::Config::GlobalConfig& config, const std::string& configName )
{
  auto configFile = fs::path( fs::path( m_configFolderRoot ) / configName );

  if( !fs::exists( configFile ) )
  {
    copyDefaultConfig( configName );
    return false;
  }

  m_pInih = std::make_unique< INIReader >( configFile.string() );
  if( m_pInih->ParseError() < 0 )
    return false;

  // database
  config.database.host = getValue< std::string >( "Database", "Host", "127.0.0.1" );
  config.database.port = getValue< uint16_t >( "Database", "Port", 3306 );
  config.database.database = getValue< std::string >( "Database", "Database", "sapphire" );
  config.database.user = getValue< std::string >( "Database", "Username", "sapphire" );
  config.database.password = getValue< std::string >( "Database", "Password", "" );
  config.database.syncThreads = getValue< uint8_t >( "Database", "SyncThreads", 2 );
  config.database.asyncThreads = getValue< uint8_t >( "Database", "AsyncThreads", 2 );

  // params
  config.general.dataPath = getValue< std::string >( "General", "DataPath", "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
  config.general.dataVersion = getValue< std::string >( "General", "DataVersion", "2016.07.05.0000.0001" );
  config.general.serverSecret = getValue< std::string >( "General", "ServerSecret", "default" );
  config.general.worldID = getValue< uint16_t >( "General", "WorldID", 67 );
  config.general.defaultGMRank = getValue< uint8_t >( "General", "DefaultGMRank", 255 );
  config.general.logLevel = getValue< uint8_t >( "General", "LogLevel", 1 );
  config.general.logFilter = getValue< uint32_t >( "General", "LogFilter", 0 );

  // network
  config.network.zoneHost = getValue< std::string >( "Network", "ZoneHost", "127.0.0.1" );
  config.network.zonePort = getValue< uint16_t >( "Network", "ZonePort", 54992 );
  config.network.lobbyHost = getValue< std::string >( "Network", "LobbyHost", "127.0.0.1" );
  config.network.lobbyPort = getValue< uint16_t >( "Network", "LobbyPort", 54994 );
  config.network.restHost = getValue< std::string >( "Network", "RestHost", "127.0.0.1" );
  config.network.restPort = getValue< uint16_t >( "Network", "RestPort", 80 );

  return true;
}

bool ConfigMgr::copyDefaultConfig( const std::string& configName )
{
  fs::path configPath( m_configFolderRoot );
  configPath /= configName;

  if( !fs::exists( configPath.string() + m_configDefaultSuffix ) )
  {
    // no default file :(
    return false;
  }

  fs::copy_file( configPath.string() + m_configDefaultSuffix, configPath );

  return true;
}