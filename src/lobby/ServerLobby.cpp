
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

  ServerLobby::~ServerLobby( void ) = default;

  LobbySessionPtr ServerLobby::getSession( char* sessionId )
  {
    return g_restConnector.getSession( sessionId );
  }

  ConfigMgrPtr ServerLobby::getConfig() const
  {
    return m_pConfig;
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

    auto pFw = std::make_shared< Framework >();
    Network::HivePtr hive( new Network::Hive() );
    Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive, pFw );

    Logger::info(
      "Lobby server running on " + m_pConfig->getValue< std::string >( "LobbyNetwork", "ListenIp", "0.0.0.0" ) + ":" +
      m_pConfig->getValue< std::string >( "LobbyNetwork", "ListenPort", "80" ) );

    std::vector< std::thread > threadGroup;

    threadGroup.emplace_back( std::bind( &Network::Hive::Run, hive.get() ) );

    for( auto& thread : threadGroup )
      if( thread.joinable() )
        thread.join();

  }

  bool ServerLobby::loadSettings( int32_t argc, char* argv[] )
  {
    Logger::info( "Loading config {0}", m_configPath );

    if( !m_pConfig->loadConfig( m_configPath ) )
    {
      Logger::fatal( "Error loading config {0}", m_configPath );
      Logger::fatal( "If this is the first time starting the server, we've copied the default one for your editing pleasure." );
      return false;
    }
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
          m_pConfig->setValue< std::string >( "LobbyNetwork.ListenIp", val );
        }
        else if( arg == "p" || arg == "port" )
        {
          m_pConfig->setValue< std::string >( "LobbyNetwork.LobbyPort", val );
        }
        else if( arg == "worldip" || arg == "worldip" )
        {
          m_pConfig->setValue< std::string >( "GlobalNetwork.ZoneHost", val );
        }
        else if( arg == "worldport" )
        {
          m_pConfig->setValue< std::string >( "GlobalNetwork.ZonePort", val );
        }
      }
      catch( ... )
      {
        Logger::error( "Error parsing argument: {0} value: {1}\n", arg, val );
        Logger::error( "Usage: <arg> <val> \n" );
      }
    }

    m_port = m_pConfig->getValue< uint16_t >( "LobbyNetwork", "ListenPort", 54994 );
    m_ip = m_pConfig->getValue< std::string >( "LobbyNetwork", "ListenIp", "0.0.0.0" );

    g_restConnector.restHost = m_pConfig->getValue< std::string >( "GlobalNetwork", "RestHost" ) + ":" +
                               m_pConfig->getValue< std::string >( "GlobalNetwork", "RestPort" );
    g_restConnector.serverSecret = m_pConfig->getValue< std::string >( "GlobalParameters", "ServerSecret" );

    return true;
  }
}
