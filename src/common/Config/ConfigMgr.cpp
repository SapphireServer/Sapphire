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
  m_pConfig = std::make_shared< Common::Configuration >();

  // database
  m_pConfig->database.host = getValue< std::string >( "Database", "Host", "127.0.0.1" );
  m_pConfig->database.port = getValue< uint16_t >( "Database", "Port", 3306 );
  m_pConfig->database.database = getValue< std::string >( "Database", "Database", "sapphire" );
  m_pConfig->database.username = getValue< std::string >( "Database", "Username", "sapphire" );
  m_pConfig->database.password = getValue< std::string >( "Database", "Password", "" );
  m_pConfig->database.syncThreads = getValue< uint8_t >( "Database", "SyncThreads", 2 );
  m_pConfig->database.asyncThreads = getValue< uint8_t >( "Database", "AsyncThreads", 2 );

  // global parameters
  m_pConfig->globalParameters.dataPath = getValue< std::string >( "GlobalParameters", "DataPath", "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
  m_pConfig->globalParameters.serverSecret = getValue< std::string >( "GlobalParameters", "ServerSecret", "default" );

  // global network
  m_pConfig->globalNetwork.zoneHost = getValue< std::string >( "GlobalNetwork", "ZoneHost", "127.0.0.1" );
  m_pConfig->globalNetwork.zonePort = getValue< uint16_t >( "GlobalNetwork", "ZonePort", 54992 );
  m_pConfig->globalNetwork.lobbyHost = getValue< std::string >( "GlobalNetwork", "LobbyHost", "127.0.0.1" );
  m_pConfig->globalNetwork.lobbyPort = getValue< uint16_t >( "GlobalNetwork", "LobbyPort", 54994 );
  m_pConfig->globalNetwork.restHost = getValue< std::string >( "GlobalNetwork", "RestHost", "127.0.0.1" );
  m_pConfig->globalNetwork.restPort = getValue< uint16_t >( "GlobalNetwork", "RestPort", 80 );

  // lobby
  m_pConfig->lobby.worldID = getValue< uint16_t >( "Lobby", "WorldID", 67 );
  m_pConfig->lobby.allowNoSessionConnect = getValue< bool >( "Lobby", "AllowNoSessionConnect", false );
  m_pConfig->lobby.worldName = getValue< std::string >( "Lobby", "WorldName", "Sapphire" );

  // lobby network
  m_pConfig->lobbyNetwork.listenIp = getValue< std::string >( "LobbyNetwork", "ListenIp", "0.0.0.0" );
  m_pConfig->lobbyNetwork.listenPort = getValue< uint16_t >( "LobbyNetwork", "ListenPort", 54994 );

  // character creation
  m_pConfig->characterCreation.defaultGMRank = getValue< uint8_t >( "CharacterCreation", "DefaultGMRank", 255 );

  // rest network
  m_pConfig->restNetwork.listenIP = getValue< std::string >( "RestNetwork", "ListenIp", "0.0.0.0" );
  m_pConfig->restNetwork.listenPort = getValue< uint16_t >( "RestNetwork", "ListenPort", 80 );

  // scripts
  m_pConfig->scripts.hotSwap = getValue( "Scripts", "HotSwap", true );
  m_pConfig->scripts.path = getValue< std::string >( "Scripts", "Path", "./compiledscripts/" );
  m_pConfig->scripts.cachePath = getValue< std::string >( "Scripts", "CachePath", "./cache/" );

  // network
  m_pConfig->network.disconnectTimeout = getValue< uint16_t >( "Network", "DisconnectTimeout", 20 );

  // zone network
  m_pConfig->zoneNetwork.listenIp = getValue< std::string >( "ZoneNetwork", "ListenIp", "0.0.0.0" );
  m_pConfig->zoneNetwork.listenPort = getValue< uint16_t >( "ZoneNetwork", "ListenPort", 54992 );

  // general
  m_pConfig->general.motd = getValue< std::string >( "General", "MotD", "" );

  // housing
  m_pConfig->housing.defaultEstateName = getValue< std::string >( "Housing", "DefaultEstateName", "Estate #{}" );
}

Sapphire::ConfigMgr::ConfigurationPtr Sapphire::ConfigMgr::getConfig()
{
  return m_pConfig;
}