
#include <Connection.h>
#include <Network/Connection.h>
#include <Network/Hive.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "ServerMgr.h"
#include "Framework.h"

#include <Version.h>
#include <Logging/Logger.h>
#include <Config/ConfigMgr.h>

#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>

#include "Actor/Player.h"
#include "Actor/BNpcTemplate.h"


#include "Session.h"

#include "Manager/TerritoryMgr.h"
#include "Manager/LinkshellMgr.h"

#include "Script/ScriptMgr.h"

#include <Exd/ExdDataGenerated.h>

#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include "Manager/LinkshellMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/HousingMgr.h"
#include "DebugCommand/DebugCommandHandler.h"
#include "Manager/PlayerMgr.h"
#include "Manager/ShopMgr.h"


extern Sapphire::Framework g_fw;

using namespace Sapphire::World::Manager;

Sapphire::ServerMgr::ServerMgr( const std::string& configName ) :
  m_configName( configName ),
  m_bRunning( true ),
  m_lastDBPingTime( 0 ),
  m_worldId( 67 )
{
}

Sapphire::ServerMgr::~ServerMgr()
{
}

size_t Sapphire::ServerMgr::getSessionCount() const
{
  return m_sessionMapById.size();
}

bool Sapphire::ServerMgr::loadSettings( int32_t argc, char* argv[] )
{
  auto pLog = g_fw.get< Sapphire::Logger >();
  auto pConfig = g_fw.get< Sapphire::ConfigMgr >();

  pLog->info( "Loading config " + m_configName );

  if( !pConfig->loadConfig( m_configName ) )
  {
    pLog->fatal( "Error loading config " + m_configName );
    pLog->fatal( "If this is the first time starting the server, we've copied the default one for your editing pleasure." );
    return false;
  }

  m_port = pConfig->getValue< uint16_t >( "ZoneNetwork", "ListenPort", 54992 );
  m_ip = pConfig->getValue< std::string >( "ZoneNetwork", "ListenIp", "0.0.0.0" );

  return true;
}

void Sapphire::ServerMgr::run( int32_t argc, char* argv[] )
{
  using namespace Sapphire;
  using namespace Sapphire::World;

  auto pLog = std::make_shared< Logger >();
  pLog->setLogPath( "log/world" );
  pLog->init();
  g_fw.set< Logger >( pLog );

  printBanner();

  auto pConfig = std::make_shared< ConfigMgr >();
  g_fw.set< ConfigMgr >( pConfig );
  if( !loadSettings( argc, argv ) )
  {
    pLog->fatal( "Unable to load settings!" );
    return;
  }

  pLog->info( "Setting up generated EXD data" );
  auto pExdData = std::make_shared< Data::ExdDataGenerated >();
  auto dataPath = pConfig->getValue< std::string >( "GlobalParameters", "DataPath", "" );
  if( !pExdData->init( dataPath ) )
  {
    pLog->fatal( "Error setting up generated EXD data. Make sure that DataPath is set correctly in config.ini" );
    pLog->fatal( "DataPath: " + dataPath );
    return;
  }
  g_fw.set< Data::ExdDataGenerated >( pExdData );

  Sapphire::Db::ConnectionInfo info;
  info.password = pConfig->getValue< std::string >( "Database", "Password", "" );
  info.host = pConfig->getValue< std::string >( "Database", "Host", "127.0.0.1" );
  info.database = pConfig->getValue< std::string >( "Database", "Database", "sapphire" );
  info.port = pConfig->getValue< uint16_t >( "Database", "Port", 3306 );
  info.user = pConfig->getValue< std::string >( "Database", "Username", "root" );
  info.syncThreads = pConfig->getValue< uint8_t >( "Database", "SyncThreads", 2 );
  info.asyncThreads = pConfig->getValue< uint8_t >( "Database", "AsyncThreads", 2 );

  auto pDb = std::make_shared< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  Sapphire::Db::DbLoader loader;
  loader.addDb( *pDb, info );
  if( !loader.initDbs() )
  {
    pLog->fatal( "Database not initialized properly!" );
    return;
  }
  g_fw.set< Db::DbWorkerPool< Db::ZoneDbConnection > >( pDb );

  pLog->info( "LinkshellMgr: Caching linkshells" );
  auto pLsMgr = std::make_shared< Manager::LinkshellMgr >();
  if( !pLsMgr->loadLinkshells() )
  {
    pLog->fatal( "Unable to load linkshells!" );
    return;
  }
  g_fw.set< Manager::LinkshellMgr >( pLsMgr );

  auto pScript = std::make_shared< Scripting::ScriptMgr >();
  if( !pScript->init() )
  {
    pLog->fatal( "Failed to setup scripts!" );
    return;
  }
  g_fw.set< Scripting::ScriptMgr >( pScript );

  pLog->info( "TerritoryMgr: Setting up zones" );
  auto pTeriMgr = std::make_shared< Manager::TerritoryMgr >();
  auto pHousingMgr = std::make_shared< Manager::HousingMgr >();
  g_fw.set< Manager::HousingMgr >( pHousingMgr );
  g_fw.set< Manager::TerritoryMgr >( pTeriMgr );
  if( !pTeriMgr->init() )
  {
    pLog->fatal( "Failed to setup zones!" );
    return;
  }

  loadBNpcTemplates();

  Network::HivePtr hive( new Network::Hive() );
  Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive );

  std::vector< std::thread > thread_list;
  thread_list.emplace_back( std::thread( std::bind( &Network::Hive::Run, hive.get() ) ) );

  auto pDebugCom = std::make_shared< DebugCommandHandler >();
  auto pPlayerMgr = std::make_shared< Manager::PlayerMgr >();
  auto pShopMgr = std::make_shared< Manager::ShopMgr >();

  g_fw.set< DebugCommandHandler >( pDebugCom );
  g_fw.set< Manager::PlayerMgr >( pPlayerMgr );
  g_fw.set< Manager::ShopMgr >( pShopMgr );

  pLog->info( "World server running on " + m_ip + ":" + std::to_string( m_port ) );

  mainLoop();

  for( auto& thread_entry : thread_list )
  {
    thread_entry.join();
  }

}

uint16_t Sapphire::ServerMgr::getWorldId() const
{
  return m_worldId;
}

void Sapphire::ServerMgr::setWorldId( uint16_t worldId )
{
  m_worldId = worldId;
}

void Sapphire::ServerMgr::printBanner() const
{
  auto pLog = g_fw.get< Sapphire::Logger >();

  pLog->info( "===========================================================" );
  pLog->info( "Sapphire Server Project " );
  pLog->info( "Version: " + Version::VERSION );
  pLog->info( "Git Hash: " + Version::GIT_HASH );
  pLog->info( "Compiled: " __DATE__ " " __TIME__ );
  pLog->info( "===========================================================" );
}

void Sapphire::ServerMgr::mainLoop()
{
  auto pLog = g_fw.get< Logger >();
  auto pTeriMgr = g_fw.get< TerritoryMgr >();
  auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  while( isRunning() )
  {
    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

    auto currTime = Util::getTimeSeconds();

    pTeriMgr->updateTerritoryInstances( static_cast< uint32_t >( currTime ) );

    pScriptMgr->update();

    std::lock_guard< std::mutex > lock( m_sessionMutex );
    for( auto sessionIt : m_sessionMapById )
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


    auto it = m_sessionMapById.begin();
    for( ; it != m_sessionMapById.end(); )
    {
      auto diff = std::difftime( currTime, it->second->getLastDataTime() );

      auto pPlayer = it->second->getPlayer();

      // remove session of players marked for removel ( logoff / kick )
      if( pPlayer->isMarkedForRemoval() && diff > 5 )
      {
        it->second->close();
        // if( it->second.unique() )
        {
          pLog->info( "[" + std::to_string( it->second->getId() ) + "] Session removal" );
          it = m_sessionMapById.erase( it );
          removeSession( pPlayer->getName() );
          continue;
        }
      }

      // remove sessions that simply timed out
      if( diff > 20 )
      {
        pLog->info( "[" + std::to_string( it->second->getId() ) + "] Session time out" );

        it->second->close();
        // if( it->second.unique() )
        {
          it = m_sessionMapById.erase( it );
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

bool Sapphire::ServerMgr::createSession( uint32_t sessionId )
{
  auto pLog = g_fw.get< Sapphire::Logger >();

  std::lock_guard< std::mutex > lock( m_sessionMutex );

  const std::string session_id_str = std::to_string( sessionId );

  auto it = m_sessionMapById.find( sessionId );

  if( it != m_sessionMapById.end() )
  {
    pLog->error( "[" + session_id_str + "] Error creating session" );
    return false;
  }

  pLog->info( "[" + session_id_str + "] Creating new session" );

  std::shared_ptr< Session > newSession( new Session( sessionId ) );
  m_sessionMapById[ sessionId ] = newSession;

  if( !newSession->loadPlayer() )
  {
    pLog->error( "[" + session_id_str + "] Error loading player " + session_id_str );
    return false;
  }

  m_sessionMapByName[ newSession->getPlayer()->getName() ] = newSession;

  return true;

}

void Sapphire::ServerMgr::removeSession( uint32_t sessionId )
{
  m_sessionMapById.erase( sessionId );
}

Sapphire::SessionPtr Sapphire::ServerMgr::getSession( uint32_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );

  auto it = m_sessionMapById.find( id );

  if( it != m_sessionMapById.end() )
    return ( it->second );

  return nullptr;
}

Sapphire::SessionPtr Sapphire::ServerMgr::getSession( const std::string& playerName )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );

  auto it = m_sessionMapByName.find( playerName );

  if( it != m_sessionMapByName.end() )
    return ( it->second );

  return nullptr;
}

void Sapphire::ServerMgr::removeSession( const std::string& playerName )
{
  m_sessionMapByName.erase( playerName );
}


bool Sapphire::ServerMgr::isRunning() const
{
  return m_bRunning;
}

std::string Sapphire::ServerMgr::getPlayerNameFromDb( uint32_t playerId, bool forceDbLoad )
{
  if( !forceDbLoad )
  {
    auto it = m_playerNameMapById.find( playerId );

    if( it != m_playerNameMapById.end() )
      return ( it->second );
  }

  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT name FROM charainfo WHERE characterid = " + std::to_string( playerId ) );

  if( !res->next() )
    return "Unknown";

  std::string playerName = res->getString( 1 );
  updatePlayerName( playerId, playerName );

  return playerName;
}

void Sapphire::ServerMgr::updatePlayerName( uint32_t playerId, const std::string & playerNewName )
{
  m_playerNameMapById[ playerId ] = playerNewName;
}

void Sapphire::ServerMgr::loadBNpcTemplates()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pTeriMgr = g_fw.get< TerritoryMgr >();
  auto pLog = g_fw.get< Logger >();

  auto stmt = pDb->getPreparedStatement( Db::ZoneDbStatements::ZONE_SEL_BNPCTEMPLATES );

  auto res = pDb->query( stmt );

  while( res->next() )
  {
    //Id, Name, bNPCBaseId, bNPCNameId, mainWeaponModel,
    //secWeaponModel, aggressionMode, enemyType, pose,
    //modelChara, displayFlags, Look, Models

    auto id = res->getUInt( 1 );
    auto name = res->getString( 2 );
    auto bNPCBaseId = res->getUInt( 3 );
    auto bNPCNameId = res->getUInt( 4 );
    auto mainWeaponModel = res->getUInt64( 5 );
    auto secWeaponModel = res->getUInt64( 6 );
    auto aggressionMode = res->getUInt8( 7 );
    auto enemyType = res->getUInt8( 8 );
    auto pose = res->getUInt8( 9 );
    auto modelChara = res->getUInt( 10 );
    auto displayFlags = res->getUInt( 11 );
    auto look = res->getBlobVector( 12 );
    auto models = res->getBlobVector( 13 );

    auto bnpcTemplate = std::make_shared< Entity::BNpcTemplate >(
                                              id, bNPCBaseId, bNPCNameId, mainWeaponModel, secWeaponModel,
                                              aggressionMode, enemyType, 0, pose, modelChara, displayFlags,
                                              reinterpret_cast< uint32_t* >( &models[ 0 ] ),
                                              reinterpret_cast< uint8_t* >( &look[ 0 ] ) );

    m_bNpcTemplateMap[ name ] = bnpcTemplate;
  }

  pLog->debug( "BNpc Templates loaded: " + std::to_string( m_bNpcTemplateMap.size() ) );

}

Sapphire::Entity::BNpcTemplatePtr Sapphire::ServerMgr::getBNpcTemplate( const std::string& key )
{
  auto it = m_bNpcTemplateMap.find( key );

  if( it == m_bNpcTemplateMap.end() )
    return nullptr;

  return it->second;
}

Sapphire::Entity::BNpcTemplatePtr Sapphire::ServerMgr::getBNpcTemplate( uint32_t id )
{
  for( auto entry : m_bNpcTemplateMap )
  {
    if( entry.second->getId() == id )
      return entry.second;
  }

  return nullptr;
}
