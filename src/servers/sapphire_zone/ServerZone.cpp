#include "ServerZone.h"

#include <common/Version.h>
#include <common/Logging/Logger.h>
#include <common/Config/XMLConfig.h>
#include <common/Version.h>

#include <MySqlBase.h>
#include <Connection.h>

#include <common/Network/Connection.h>
#include <common/Network/Hive.h>

#include <common/Exd/ExdDataGenerated.h>
#include <common/Network/PacketContainer.h>
#include <common/Database/DbLoader.h>
#include <common/Database/CharaDbConnection.h>
#include <common/Database/DbWorkerPool.h>
#include <common/Database/PreparedStatement.h>

#include "Network/GameConnection.h"
#include "Session.h"

#include "Zone/TerritoryMgr.h"

#include "DebugCommand/DebugCommandHandler.h"

#include "Script/ScriptMgr.h"
#include "Linkshell/LinkshellMgr.h"

#include "Social/Manager/SocialMgr.h"

#include "Forwards.h"
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include <thread>
#include <common/Util/Util.h>

#include "Framework.h"

Core::Framework g_framework;
Core::Logger g_log;

Core::ServerZone::ServerZone( const std::string& configPath )
   : m_configPath( configPath ),
     m_bRunning( true ),
     m_lastDBPingTime( 0 )
{
   m_pConfig = XMLConfigPtr( new XMLConfig );
}

Core::ServerZone::~ServerZone()
{
}

Core::XMLConfigPtr Core::ServerZone::getConfig() const
{
   return m_pConfig;
}

size_t Core::ServerZone::getSessionCount() const
{
   return m_sessionMapById.size();
}

bool Core::ServerZone::registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId,
                                             uint32_t bnpcNameId, uint32_t modelId, std::string aiName )
{

   auto it = m_bnpcTemplates.find( templateName );

   if( it != m_bnpcTemplates.end() )
   {
      g_framework.getLogger().error( templateName + " already registered, skipping..." );
      return false;
   }

   Entity::BattleNpcTemplatePtr pNpcTemplate( new Entity::BattleNpcTemplate( templateName, bnpcBaseId, bnpcNameId, modelId, aiName ) );
   m_bnpcTemplates[templateName] = pNpcTemplate;

   return true;
}

Core::Entity::BattleNpcTemplatePtr Core::ServerZone::getBnpcTemplate( std::string templateName )
{
   auto it = m_bnpcTemplates.find( templateName );

   if (it != m_bnpcTemplates.end())
      return nullptr;

   return it->second;
}

bool Core::ServerZone::loadSettings( int32_t argc, char* argv[] )
{
   g_framework.getLogger().info( "Loading config " + m_configPath );

   if( !m_pConfig->loadConfig( m_configPath ) )
   {
      g_framework.getLogger().fatal( "Error loading config " + m_configPath );
      return false;
   }

   std::vector<std::string> args( argv + 1, argv + argc );
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
            m_pConfig->setValue< std::string >( "Settings.General.ListenIP", val );
         }
         else if( arg == "p" || arg == "port" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.ListenPort", val );
         }
         else if( arg == "exdpath" || arg == "datapath" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.DataPath", val );
         }
         else if( arg == "s" || arg == "scriptpath" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.ScriptPath", val );
         }
         else if( arg == "h" || arg == "dbhost" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Host", val );
         }
         else if( arg == "dbport" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Port", val );
         }
         else if( arg == "u" || arg == "user" || arg == "dbuser" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Username", val );
         }
         else if( arg == "pass" || arg == "dbpass" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Pass", val );
         }
         else if( arg == "d" || arg == "db" || arg == "database" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Database", val );
         }
      }
      catch( ... )
      {
         g_framework.getLogger().error( "Error parsing argument: " + arg + " " + "value: " + val + "\n" );
         g_framework.getLogger().error( "Usage: <arg> <val> \n" );
      }
   }

   g_framework.getLogger().info( "Setting up generated EXD data" );
   if( !g_framework.getExdDataGen().init( m_pConfig->getValue< std::string >( "Settings.General.DataPath", "" ) ) )
   {
      g_framework.getLogger().fatal( "Error setting up generated EXD data " );
      return false;
   }

   Core::Db::DbLoader loader;

   Core::Db::ConnectionInfo info;
   info.password = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Pass", "" );
   info.host = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Host", "127.0.0.1" );
   info.database = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Database", "sapphire" );
   info.port = m_pConfig->getValue< uint16_t >( "Settings.General.Mysql.Port", 3306 );
   info.user = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Username", "root" );
   info.syncThreads = m_pConfig->getValue< uint8_t >( "Settings.General.Mysql.SyncThreads", 2 );
   info.asyncThreads = m_pConfig->getValue< uint8_t >( "Settings.General.Mysql.AsyncThreads", 2 );

   loader.addDb( g_framework.getCharaDb(), info );
   if( !loader.initDbs() )
      return false;

   m_port = m_pConfig->getValue< uint16_t >( "Settings.General.ListenPort", 54992 );
   m_ip = m_pConfig->getValue< std::string >( "Settings.General.ListenIp", "0.0.0.0" );

   return true;
}

void Core::ServerZone::run( int32_t argc, char* argv[] )
{
   // TODO: add more error checks for the entire initialisation
   /*g_log.setLogPath( "log/SapphireZone_" );
   g_log.init();*/

   printBanner();

   g_framework.getLogger().setLogPath( "log/SapphireZone_" );
   g_framework.getLogger().init();

   g_log = g_framework.getLogger();
   
   if ( !g_framework.initSocialGroups() )
   {
      g_framework.getLogger().fatal( "Unable to initialize social groups!" );
   }

   if( !loadSettings( argc, argv ) )
   {
      g_framework.getLogger().fatal( "Unable to load settings!" );
      return;
   }

   g_framework.getLogger().info( "LinkshellMgr: Caching linkshells" );
   if( !g_framework.getLinkshellMgr().loadLinkshells() )
   {
      g_framework.getLogger().fatal( "Unable to load linkshells!" );
      return;
   }

   g_framework.getFriendsListMgr().findGroupById( 0 );

   Network::HivePtr hive( new Network::Hive() );
   Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive );

   g_framework.getScriptMgr().init();

   g_framework.getLogger().info( "TerritoryMgr: Setting up zones" );
   g_framework.getTerritoryMgr().init();

   std::vector< std::thread > thread_list;
   thread_list.emplace_back( std::thread( std::bind( &Network::Hive::Run, hive.get() ) ) );

   g_framework.getLogger().info( "Server listening on port: " + std::to_string( m_port ) );
   g_framework.getLogger().info( "Ready for connections..." );

   mainLoop();

   for( auto& thread_entry : thread_list )
   {
      thread_entry.join();
   }

}

void Core::ServerZone::printBanner() const
{
   g_framework.getLogger().info("===========================================================" );
   g_framework.getLogger().info( "Sapphire Server Project " );
   g_framework.getLogger().info( "Version: " + Version::VERSION );
   g_framework.getLogger().info( "Git Hash: " + Version::GIT_HASH );
   g_framework.getLogger().info( "Compiled: " __DATE__ " " __TIME__ );
   g_framework.getLogger().info( "===========================================================" );
}

void Core::ServerZone::mainLoop()
{
   while( isRunning() )
   {
      this_thread::sleep_for( chrono::milliseconds( 50 ) );


      auto currTime = Util::getTimeSeconds();

      g_framework.getTerritoryMgr().updateTerritoryInstances( currTime );

      g_framework.getScriptMgr().update();

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
         g_framework.getCharaDb().keepAlive();
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
               g_framework.getLogger().info("[" + std::to_string(it->second->getId() ) + "] Session removal" );
               it = this->m_sessionMapById.erase( it );
               removeSession( pPlayer->getName() );
               continue;
            }
         }

         // remove sessions that simply timed out
         if( diff > 20 )
         {
            g_framework.getLogger().info("[" + std::to_string( it->second->getId() ) + "] Session time out" );

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
   std::lock_guard< std::mutex > lock( m_sessionMutex );

   const std::string session_id_str = std::to_string( sessionId );

   auto it = m_sessionMapById.find( sessionId );

   if( it != m_sessionMapById.end() )
   {
      g_framework.getLogger().error( "[" + session_id_str + "] Error creating session" );
      return false;
   }

   g_framework.getLogger().info( "[" + session_id_str + "] Creating new session" );

   boost::shared_ptr<Session> newSession( new Session( sessionId ) );
   m_sessionMapById[sessionId] = newSession;

   if( !newSession->loadPlayer() )
   {
      g_framework.getLogger().error( "[" + session_id_str + "] Error loading player " + session_id_str );
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

