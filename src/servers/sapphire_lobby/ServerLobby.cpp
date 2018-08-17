
#include <stdio.h>
#include <time.h>
#include <map>

#include <Network/Hive.h>
#include <Network/Acceptor.h>

#include <Version.h>
#include <Logging/Logger.h>
#include <Config/ConfigMgr.h>

//#include "LobbySession.h"

#include "ServerLobby.h"

#include "GameConnection.h"
#include "RestConnector.h"
#include "Forwards.h"
#include <Forwards.h>

#include <thread>
#include <boost/thread.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

Core::Logger g_log;
Core::Network::RestConnector g_restConnector;

namespace Core {


   ServerLobby::ServerLobby( const std::string& configPath ) :
      m_configPath( configPath ),
      m_numConnections( 0 )
   {
      m_pConfig = boost::shared_ptr< ConfigMgr >( new ConfigMgr );
   }

   ServerLobby::~ServerLobby( void )
   {
   }

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
      g_log.setLogPath( "log/SapphireLobby" );
      g_log.init();

      g_log.info( "===========================================================" );
      g_log.info( "Sapphire Server Project " );
      g_log.info( "Version: " + Version::VERSION );
      g_log.info( "Git Hash: " + Version::GIT_HASH );
      g_log.info( "Compiled: " __DATE__ " " __TIME__ );
      g_log.info( "===========================================================" );

      if( !loadSettings( argc, argv ) )
      {
         g_log.fatal( "Error loading settings! " );
         return;
      }

      Network::HivePtr hive( new Network::Hive() );
      Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive );

      g_log.info( "Lobby server running on " + m_pConfig->getValue< std::string >( "LobbyNetwork.ListenIp", "0.0.0.0" ) + ":" + m_pConfig->getValue< std::string >( "LobbyNetwork.ListenPort", "80" ) );

      boost::thread_group worker_threads;
      worker_threads.create_thread( boost::bind( &Network::Hive::Run, hive.get() ) );
      worker_threads.join_all();

   }

   bool ServerLobby::loadSettings( int32_t argc, char* argv[] )
   {
      g_log.info( "Loading config " + m_configPath );

      if( !m_pConfig->loadConfig( m_configPath ) )
      {
         g_log.fatal( "Error loading config " + m_configPath );
         return false;
      }
      std::vector<std::string> args( argv + 1, argv + argc );
      for( size_t i = 0; i + 1 < args.size(); i += 2 )
      {
         std::string arg( "" );
         std::string val( "" );

         try
         {
            arg = boost::to_lower_copy( std::string( args[i] ) );
            val = std::string( args[i + 1] );

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
               m_pConfig->setValue < std::string >( "GlobalNetwork.ZoneHost", val );
            }
            else if( arg == "worldport" )
            {
               m_pConfig->setValue< std::string >( "GlobalNetwork.ZonePort", val );
            }
         }
         catch( ... )
         {
            g_log.error( "Error parsing argument: " + arg + " " + "value: " + val + "\n" );
            g_log.error( "Usage: <arg> <val> \n" );
         }
      }

      m_port = m_pConfig->getValue< uint16_t >( "LobbyNetwork.ListenPort", 54994 );
      m_ip = m_pConfig->getValue< std::string >( "LobbyNetwork.ListenIp", "0.0.0.0" );

      g_restConnector.restHost = m_pConfig->getValue< std::string >( "GlobalNetwork.RestHost" ) + ":" + m_pConfig->getValue< std::string >( "GlobalNetwork.RestPort" );
      g_restConnector.serverSecret = m_pConfig->getValue< std::string >( "GlobalParameters.ServerSecret" );

      return true;
   }
}
