#include "ConfigMgr.h"
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/**
 * Loads an ini file and parses it
 * @param configName the name of ini file relative to m_configFolderRoot to load alongside global.ini
 * @return true if loading was successful
 */
bool Sapphire::ConfigMgr::loadConfig( const std::string& configName )
{
  // get global config
  auto configFile = fs::path( fs::path( m_configFolderRoot ) / configName );

  if( !fs::exists( configFile ) )
  {
    copyDefaultConfig( configName );
    return false;
  }

  m_pInih = std::unique_ptr< INIReader >( new INIReader( configFile.string() ) );

  if( m_pInih->ParseError() < 0 )
    return false;

  initConfigData();

  return true;
}

bool Sapphire::ConfigMgr::loadGlobalConfig( Common::Config::GlobalConfig& config, const std::string& configName )
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
  config.parameters.dataPath = getValue< std::string >( "Parameters", "DataPath", "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
  config.parameters.serverSecret = getValue< std::string >( "Parameters", "ServerSecret", "default" );
  config.parameters.worldID = getValue< uint16_t >( "Parameters", "WorldID", 67 );
  config.parameters.defaultGMRank = getValue< uint8_t >( "Parameters", "DefaultGMRank", 255 );

  // network
  config.network.zoneHost = getValue< std::string >( "Network", "ZoneHost", "127.0.0.1" );
  config.network.zonePort = getValue< uint16_t >( "Network", "ZonePort", 54992 );
  config.network.lobbyHost = getValue< std::string >( "Network", "LobbyHost", "127.0.0.1" );
  config.network.lobbyPort = getValue< uint16_t >( "Network", "LobbyPort", 54994 );
  config.network.restHost = getValue< std::string >( "Network", "RestHost", "127.0.0.1" );
  config.network.restPort = getValue< uint16_t >( "Network", "RestPort", 80 );

  return true;
}

bool Sapphire::ConfigMgr::copyDefaultConfig( const std::string& configName )
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

void Sapphire::ConfigMgr::initConfigData()
{
  // lobby
//  m_pConfig->lobby.worldID = getValue< uint16_t >( "Lobby", "WorldID", 67 );
//  m_pConfig->lobby.allowNoSessionConnect = getValue< bool >( "Lobby", "AllowNoSessionConnect", false );
//  m_pConfig->lobby.worldName = getValue< std::string >( "Lobby", "WorldName", "Sapphire" );
//
//  // lobby network
//  m_pConfig->lobbyNetwork.listenIp = getValue< std::string >( "LobbyNetwork", "ListenIp", "0.0.0.0" );
//  m_pConfig->lobbyNetwork.listenPort = getValue< uint16_t >( "LobbyNetwork", "ListenPort", 54994 );
//
//  // character creation
//  m_pConfig->characterCreation.defaultGMRank = getValue< uint8_t >( "CharacterCreation", "DefaultGMRank", 255 );
//
//  // rest network
//  m_pConfig->restNetwork.listenIP = getValue< std::string >( "RestNetwork", "ListenIp", "0.0.0.0" );
//  m_pConfig->restNetwork.listenPort = getValue< uint16_t >( "RestNetwork", "ListenPort", 80 );
}