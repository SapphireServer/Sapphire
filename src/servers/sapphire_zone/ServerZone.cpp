#include "ServerZone.h"

#include <Version.h>
#include <Logging/Logger.h>
#include <Config/XMLConfig.h>
#include <Version.h>

#include <MySqlBase.h>
#include <Connection.h>

#include <Network/Connection.h>
#include <Network/Hive.h>

#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Database/DbLoader.h>
#include <Database/CharaDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Database/PreparedStatement.h>
#include <Util/Util.h>

#include "Actor/Player.h"

#include "Network/GameConnection.h"
#include "Session.h"

#include "Zone/TerritoryMgr.h"

#include "DebugCommand/DebugCommandHandler.h"

#include "Script/ScriptMgr.h"
#include "Linkshell/LinkshellMgr.h"

#include "Forwards.h"
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include <thread>

#include "Framework.h"

extern Core::Framework g_fw;

Core::ServerZone::ServerZone( const std::string& configPath ) :
   m_configPath( configPath ),
   m_bRunning( true ),
   m_lastDBPingTime( 0 )
{
}

Core::ServerZone::~ServerZone()
{
}

size_t Core::ServerZone::getSessionCount() const
{
   return m_sessionMapById.size();
}

bool Core::ServerZone::loadSettings( int32_t argc, char* argv[] )
{
   auto pLog = g_fw.get< Core::Logger >();
   auto pConfig = g_fw.get< Core::XMLConfig >();
   auto pExd = g_fw.get< Data::ExdDataGenerated >();
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();

   pLog->info( "Loading config " + m_configPath );

   if( !pConfig->loadConfig( m_configPath ) )
   {
      pLog->fatal( "Error loading config " + m_configPath );
      return false;
   }

   std::vector< std::string > args( argv + 1, argv + argc );
   for( uint32_t i = 0; i + 1 < args.size(); i += 2 )
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
            pConfig->setValue< std::string >( "Settings.General.ListenIP", val );
         }
         else if( arg == "p" || arg == "port" )
         {
            pConfig->setValue< std::string >( "Settings.General.ListenPort", val );
         }
         else if( arg == "exdpath" || arg == "datapath" )
         {
            pConfig->setValue< std::string >( "Settings.General.DataPath", val );
         }
         else if( arg == "s" || arg == "scriptpath" )
         {
            pConfig->setValue< std::string >( "Settings.General.ScriptPath", val );
         }
         else if( arg == "h" || arg == "dbhost" )
         {
            pConfig->setValue< std::string >( "Settings.General.Mysql.Host", val );
         }
         else if( arg == "dbport" )
         {
            pConfig->setValue< std::string >( "Settings.General.Mysql.Port", val );
         }
         else if( arg == "u" || arg == "user" || arg == "dbuser" )
         {
            pConfig->setValue< std::string >( "Settings.General.Mysql.Username", val );
         }
         else if( arg == "pass" || arg == "dbpass" )
         {
            pConfig->setValue< std::string >( "Settings.General.Mysql.Pass", val );
         }
         else if( arg == "d" || arg == "db" || arg == "database" )
         {
            pConfig->setValue< std::string >( "Settings.General.Mysql.Database", val );
         }
      }
      catch( ... )
      {
         pLog->error( "Error parsing argument: " + arg + " " + "value: " + val + "\n" );
         pLog->error( "Usage: <arg> <val> \n" );
      }
   }

   pLog->info( "Setting up generated EXD data" );
   if( !pExd->init( pConfig->getValue< std::string >( "Settings.General.DataPath", "" ) ) )
   {
      pLog->fatal( "Error setting up generated EXD data " );
      return false;
   }

   Core::Db::DbLoader loader;

   Core::Db::ConnectionInfo info;
   info.password = pConfig->getValue< std::string >( "Settings.General.Mysql.Pass", "" );
   info.host = pConfig->getValue< std::string >( "Settings.General.Mysql.Host", "127.0.0.1" );
   info.database = pConfig->getValue< std::string >( "Settings.General.Mysql.Database", "sapphire" );
   info.port = pConfig->getValue< uint16_t >( "Settings.General.Mysql.Port", 3306 );
   info.user = pConfig->getValue< std::string >( "Settings.General.Mysql.Username", "root" );
   info.syncThreads = pConfig->getValue< uint8_t >( "Settings.General.Mysql.SyncThreads", 2 );
   info.asyncThreads = pConfig->getValue< uint8_t >( "Settings.General.Mysql.AsyncThreads", 2 );

   loader.addDb( *pDb, info );
   if( !loader.initDbs() )
      return false;

   m_port = pConfig->getValue< uint16_t >( "Settings.General.ListenPort", 54992 );
   m_ip = pConfig->getValue< std::string >( "Settings.General.ListenIp", "0.0.0.0" );

   return true;
}

void Core::ServerZone::run( int32_t argc, char* argv[] )
{
   auto pLog = g_fw.get< Core::Logger>();
   auto pScript = g_fw.get< Scripting::ScriptMgr >();
   auto pLsMgr = g_fw.get< LinkshellMgr >();
   auto pTeriMgr = g_fw.get< TerritoryMgr >();

   printBanner();

   if( !loadSettings( argc, argv ) )
   {
      pLog->fatal( "Unable to load settings!" );
      return;
   }

   pLog->info( "LinkshellMgr: Caching linkshells" );
   if( !pLsMgr->loadLinkshells() )
   {
      pLog->fatal( "Unable to load linkshells!" );
      return;
   }

   Network::HivePtr hive( new Network::Hive() );
   Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive );

   pScript->init();

   pLog->info( "TerritoryMgr: Setting up zones" );
   pTeriMgr->init();

   std::vector< std::thread > thread_list;
   thread_list.emplace_back( std::thread( std::bind( &Network::Hive::Run, hive.get() ) ) );

   pLog->info( "Server listening on port: " + std::to_string( m_port ) );
   pLog->info( "Ready for connections..." );

   mainLoop();

   for( auto& thread_entry : thread_list )
   {
      thread_entry.join();
   }

}

void Core::ServerZone::printBanner() const
{
   auto pLog = g_fw.get< Core::Logger>();

   pLog->info("===========================================================" );
   pLog->info( "Sapphire Server Project " );
   pLog->info( "Version: " + Version::VERSION );
   pLog->info( "Git Hash: " + Version::GIT_HASH );
   pLog->info( "Compiled: " __DATE__ " " __TIME__ );
   pLog->info( "===========================================================" );
}

void Core::ServerZone::mainLoop()
{
   auto pLog = g_fw.get< Logger >();
   auto pTeriMgr = g_fw.get< TerritoryMgr >();
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();

   while( isRunning() )
   {
      this_thread::sleep_for( chrono::milliseconds( 50 ) );

      auto currTime = Util::getTimeSeconds();

      pTeriMgr->updateTerritoryInstances( currTime );

      pScriptMgr->update();

      lock_guard< std::mutex > lock( this->m_sessionMutex );
      for( auto sessionIt : this->m_sessionMapById )
      {
         auto session = sessionIt.second;
         if( session && session->getPlayer() )
         {

            // if the player is in a zone, let the zone handler take care of his updates
            // else do it here.
            if( !session->getPlayer()->getCurrentZone() )
               session->update();

         }
      }

      if( currTime - m_lastDBPingTime > 3 )
      {
         pDb->keepAlive();
         m_lastDBPingTime = currTime;
      }


      auto it = this->m_sessionMapById.begin();
      for( ; it != this->m_sessionMapById.end(); )
      {
         auto diff = std::difftime( currTime, it->second->getLastDataTime() );

         auto pPlayer = it->second->getPlayer();

         // remove session of players marked for removel ( logoff / kick )
         if( pPlayer->isMarkedForRemoval() && diff > 5 )
         {
            it->second->close();
            // if( it->second.unique() )
            {
               pLog->info("[" + std::to_string(it->second->getId() ) + "] Session removal" );
               it = this->m_sessionMapById.erase( it );
               removeSession( pPlayer->getName() );
               continue;
            }
         }

         // remove sessions that simply timed out
         if( diff > 20 )
         {
            pLog->info("[" + std::to_string( it->second->getId() ) + "] Session time out" );

            it->second->close();
            // if( it->second.unique() )
            {
               it = this->m_sessionMapById.erase( it );
               removeSession( pPlayer->getName() );
            }
         }
         else
         {
            ++it;
         }

      }

   }
}

bool Core::ServerZone::createSession( uint32_t sessionId )
{
   auto pLog = g_fw.get< Core::Logger>();

   std::lock_guard< std::mutex > lock( m_sessionMutex );

   const std::string session_id_str = std::to_string( sessionId );

   auto it = m_sessionMapById.find( sessionId );

   if( it != m_sessionMapById.end() )
   {
      pLog->error( "[" + session_id_str + "] Error creating session" );
      return false;
   }

   pLog->info( "[" + session_id_str + "] Creating new session" );

   boost::shared_ptr<Session> newSession( new Session( sessionId ) );
   m_sessionMapById[sessionId] = newSession;

   if( !newSession->loadPlayer() )
   {
      pLog->error( "[" + session_id_str + "] Error loading player " + session_id_str );
      return false;
   }

   m_sessionMapByName[newSession->getPlayer()->getName()] = newSession;

   return true;

}

void Core::ServerZone::removeSession( uint32_t sessionId )
{
   m_sessionMapById.erase( sessionId );
}

void Core::ServerZone::updateSession( uint32_t id )
{
   std::lock_guard< std::mutex > lock( m_sessionMutex );
   auto it = m_sessionMapById.find( id );

   if( it != m_sessionMapById.end() )
      it->second->loadPlayer();
}

Core::SessionPtr Core::ServerZone::getSession( uint32_t id )
{
   //std::lock_guard<std::mutex> lock( m_sessionMutex );

   auto it = m_sessionMapById.find( id );

   if( it != m_sessionMapById.end() )
      return ( it->second );

   return nullptr;
}

Core::SessionPtr Core::ServerZone::getSession( std::string playerName )
{
   //std::lock_guard<std::mutex> lock( m_sessionMutex );

   auto it = m_sessionMapByName.find( playerName );

   if (it != m_sessionMapByName.end())
      return (it->second);

   return nullptr;
}

void Core::ServerZone::removeSession( std::string playerName )
{
   m_sessionMapByName.erase( playerName );
}

void Core::ServerZone::updateSession( std::string playerName )
{
   std::lock_guard< std::mutex > lock( m_sessionMutex );
   auto it = m_sessionMapByName.find( playerName );

   if( it != m_sessionMapByName.end() )
      it->second->loadPlayer();
}

bool Core::ServerZone::isRunning() const
{
   return m_bRunning;
}

