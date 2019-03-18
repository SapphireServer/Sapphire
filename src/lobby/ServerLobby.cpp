
#include <stdio.h>
#include <time.h>
#include <map>

#include <Network/Hive.h>
#include <Network/Acceptor.h>

#include <Version.h>
#include <Logging/Logger.h>
#include <Config/ConfigMgr.h>

#include "Framework.h"

#include "ServerLobby.h"

#include "GameConnection.h"
#include "RestConnector.h"
#include "Forwards.h"
#include <Forwards.h>

#include <thread>

Sapphire::Network::RestConnector g_restConnector;

namespace Sapphire
{


  ServerLobby::ServerLobby( const std::string& configPath ) :
    m_configPath( configPath ),
    m_numConnections( 0 )
  {
    m_pConfig = std::make_shared< ConfigMgr >();
  }

  LobbySessionPtr ServerLobby::getSession( char* sessionId )
  {
    return g_restConnector.getSession( sessionId );
  }

  Sapphire::Common::Config::LobbyConfig& ServerLobby::getConfig()
  {
    return m_config;
  }

  void ServerLobby::run( int32_t argc, char* argv[] )
  {
    Logger::init( "log/lobby" );

    Logger::info( "===========================================================" );
    Logger::info( "Sapphire Server Project " );
    Logger::info( "Version: " + Version::VERSION );
    Logger::info( "Git Hash: " + Version::GIT_HASH );
    Logger::info( "Compiled: " __DATE__ " " __TIME__ );
    Logger::info( "===========================================================" );

    if( !loadSettings( argc, argv ) )
    {
      Logger::fatal( "Error loading settings! " );
      return;
    }

    Logger::setLogLevel( m_config.global.general.logLevel );

    auto pFw = std::make_shared< Framework >();
    Network::HivePtr hive( new Network::Hive() );
    Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive, pFw );

    Logger::info( "Lobby server running on {0}:{1}", m_ip, m_port );

    std::vector< std::thread > threadGroup;

    threadGroup.emplace_back( std::bind( &Network::Hive::run, hive.get() ) );

    for( auto& thread : threadGroup )
      if( thread.joinable() )
        thread.join();

  }

  bool ServerLobby::loadSettings( int32_t argc, char* argv[] )
  {
    Logger::info( "Loading config {0}", m_configPath );

    bool failedLoad = false;
    if( !m_pConfig->loadGlobalConfig( m_config.global, "global.ini" ) )
    {
      Logger::fatal( "Error loading config global.ini, copying default..." );
      failedLoad = true;
    }

    if( !m_pConfig->loadConfig( m_configPath ) )
    {
      Logger::fatal( "Error loading config {0}", m_configPath );
      failedLoad = true;
    }

    if( failedLoad )
    {
      Logger::fatal( "If this is the first time starting the server, "
                     "we've copied the default configs for your editing pleasure." );
      return false;
    }

    // load lobby config
    m_config.allowNoSessionConnect = m_pConfig->getValue< bool >( "Lobby", "AllowNoSessionConnect", false );
    m_config.worldName = m_pConfig->getValue< std::string >( "Lobby", "WorldName", "Sapphire" );

    m_config.network.listenIp = m_pConfig->getValue< std::string >( "Network", "ListenIp", "0.0.0.0" );
    m_config.network.listenPort = m_pConfig->getValue< uint16_t >( "Network", "ListenPort", 54994 );

    std::vector< std::string > args( argv + 1, argv + argc );
    for( size_t i = 0; i + 1 < args.size(); i += 2 )
    {
      std::string arg( "" );
      std::string val( "" );

      try
      {
        std::transform( arg.begin(), arg.end(), arg.begin(), [](unsigned char c){ return std::tolower( c ); } );
        val = std::string( args[ i + 1 ] );

        // trim '-' from start of arg
        arg = arg.erase( 0, arg.find_first_not_of( '-' ) );

        if( arg == "ip" )
        {
          // todo: ip addr in config
          m_config.network.listenIp = val;
        }
        else if( arg == "p" || arg == "port" )
        {
          m_config.network.listenPort = std::stoi( val );
        }
        else if( arg == "worldip" || arg == "worldip" )
        {
          m_config.global.network.zoneHost = val;
        }
        else if( arg == "worldport" )
        {
          m_config.global.network.zonePort = std::stoi( val );
        }
      }
      catch( ... )
      {
        Logger::error( "Error parsing argument: {0} value: {1}\n", arg, val );
        Logger::error( "Usage: <arg> <val> \n" );
      }
    }

    m_port = m_config.network.listenPort;
    m_ip = m_config.network.listenIp;


    g_restConnector.restHost = m_config.global.network.restHost + ":" +
                               std::to_string( m_config.global.network.restPort );
    g_restConnector.serverSecret = m_config.global.general.serverSecret;

    return true;
  }
}
