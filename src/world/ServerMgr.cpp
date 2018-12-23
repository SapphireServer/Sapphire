
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
#include "Manager/DebugCommandMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/ShopMgr.h"
#include "Manager/InventoryMgr.h"
#include "Manager/EventMgr.h"
#include "Manager/ItemMgr.h"

using namespace Sapphire::World::Manager;

Sapphire::World::ServerMgr::ServerMgr( const std::string& configName, FrameworkPtr pFw ) :
  Manager::BaseManager( pFw ),
  m_configName( configName ),
  m_bRunning( true ),
  m_lastDBPingTime( 0 ),
  m_worldId( 67 )
{
}

Sapphire::World::ServerMgr::~ServerMgr()
{
}

size_t Sapphire::World::ServerMgr::getSessionCount() const
{
  return m_sessionMapById.size();
}

bool Sapphire::World::ServerMgr::loadSettings( int32_t argc, char* argv[] )
{
  auto pConfig = framework()->get< Sapphire::ConfigMgr >();

  Logger::info( "Loading config " + m_configName );

  if( !pConfig->loadConfig( m_configName ) )
  {
    Logger::fatal( "Error loading config " + m_configName );
    Logger::fatal( "If this is the first time starting the server, we've copied the default one for your editing pleasure." );
    return false;
  }

  m_port = pConfig->getValue< uint16_t >( "ZoneNetwork", "ListenPort", 54992 );
  m_ip = pConfig->getValue< std::string >( "ZoneNetwork", "ListenIp", "0.0.0.0" );

  return true;
}

void Sapphire::World::ServerMgr::run( int32_t argc, char* argv[] )
{
  using namespace Sapphire;
  using namespace Sapphire::World;

  Logger::init( "log/world" );

  printBanner();

  auto pConfig = std::make_shared< ConfigMgr >();
  framework()->set< ConfigMgr >( pConfig );
  if( !loadSettings( argc, argv ) )
  {
    Logger::fatal( "Unable to load settings!" );
    return;
  }

  Logger::info( "Setting up generated EXD data" );
  auto pExdData = std::make_shared< Data::ExdDataGenerated >();
  auto dataPath = pConfig->getValue< std::string >( "GlobalParameters", "DataPath", "" );
  if( !pExdData->init( dataPath ) )
  {
    Logger::fatal( "Error setting up generated EXD data. Make sure that DataPath is set correctly in config.ini" );
    Logger::fatal( "DataPath: " + dataPath );
    return;
  }
  framework()->set< Data::ExdDataGenerated >( pExdData );

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
    Logger::fatal( "Database not initialized properly!" );
    return;
  }
  framework()->set< Db::DbWorkerPool< Db::ZoneDbConnection > >( pDb );

  Logger::info( "LinkshellMgr: Caching linkshells" );
  auto pLsMgr = std::make_shared< Manager::LinkshellMgr >( framework() );
  if( !pLsMgr->loadLinkshells() )
  {
    Logger::fatal( "Unable to load linkshells!" );
    return;
  }
  framework()->set< Manager::LinkshellMgr >( pLsMgr );

  auto pScript = std::make_shared< Scripting::ScriptMgr >( framework() );
  if( !pScript->init() )
  {
    Logger::fatal( "Failed to setup scripts!" );
    return;
  }
  framework()->set< Scripting::ScriptMgr >( pScript );

  Logger::info( "TerritoryMgr: Setting up zones" );
  auto pTeriMgr = std::make_shared< Manager::TerritoryMgr >( framework() );
  auto pHousingMgr = std::make_shared< Manager::HousingMgr >( framework() );
  framework()->set< Manager::HousingMgr >( pHousingMgr );
  framework()->set< Manager::TerritoryMgr >( pTeriMgr );
  if( !pTeriMgr->init() )
  {
    Logger::fatal( "Failed to setup zones!" );
    return;
  }

  loadBNpcTemplates();

  Network::HivePtr hive( new Network::Hive() );
  Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive, framework() );

  std::vector< std::thread > thread_list;
  thread_list.emplace_back( std::thread( std::bind( &Network::Hive::Run, hive.get() ) ) );

  auto pDebugCom = std::make_shared< DebugCommandMgr >( framework() );
  auto pPlayerMgr = std::make_shared< Manager::PlayerMgr >( framework() );
  auto pShopMgr = std::make_shared< Manager::ShopMgr >( framework() );
  auto pInventoryMgr = std::make_shared< Manager::InventoryMgr >();
  auto pEventMgr = std::make_shared< Manager::EventMgr >( framework() );
  auto pItemMgr = std::make_shared< Manager::ItemMgr >( framework() );

  framework()->set< DebugCommandMgr >( pDebugCom );
  framework()->set< Manager::PlayerMgr >( pPlayerMgr );
  framework()->set< Manager::ShopMgr >( pShopMgr );
  framework()->set< Manager::InventoryMgr >( pInventoryMgr );
  framework()->set< Manager::ItemMgr >( pItemMgr );

  Logger::info( "World server running on " + m_ip + ":" + std::to_string( m_port ) );

  mainLoop();

  for( auto& thread_entry : thread_list )
  {
    thread_entry.join();
  }

}

uint16_t Sapphire::World::ServerMgr::getWorldId() const
{
  return m_worldId;
}

void Sapphire::World::ServerMgr::setWorldId( uint16_t worldId )
{
  m_worldId = worldId;
}

void Sapphire::World::ServerMgr::printBanner() const
{
  Logger::info( "===========================================================" );
  Logger::info( "Sapphire Server Project " );
  Logger::info( "Version: " + Version::VERSION );
  Logger::info( "Git Hash: " + Version::GIT_HASH );
  Logger::info( "Compiled: " __DATE__ " " __TIME__ );
  Logger::info( "===========================================================" );
}

void Sapphire::World::ServerMgr::mainLoop()
{
  auto pTeriMgr = framework()->get< TerritoryMgr >();
  auto pScriptMgr = framework()->get< Scripting::ScriptMgr >();
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

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
          Logger::info( "[" + std::to_string( it->second->getId() ) + "] Session removal" );
          it = m_sessionMapById.erase( it );
          removeSession( pPlayer->getName() );
          continue;
        }
      }

      // remove sessions that simply timed out
      if( diff > 20 )
      {
        Logger::info( "[" + std::to_string( it->second->getId() ) + "] Session time out" );

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

bool Sapphire::World::ServerMgr::createSession( uint32_t sessionId )
{
  std::lock_guard< std::mutex > lock( m_sessionMutex );

  const auto session_id_str = std::to_string( sessionId );

  auto it = m_sessionMapById.find( sessionId );

  if( it != m_sessionMapById.end() )
  {
    Logger::error( "[" + session_id_str + "] Error creating session" );
    return false;
  }

  Logger::info( "[" + session_id_str + "] Creating new session" );

  std::shared_ptr< Session > newSession( new Session( sessionId ) );
  m_sessionMapById[ sessionId ] = newSession;

  if( !newSession->loadPlayer() )
  {
    Logger::error( "[" + session_id_str + "] Error loading player " + session_id_str );
    return false;
  }

  m_sessionMapByName[ newSession->getPlayer()->getName() ] = newSession;

  return true;

}

void Sapphire::World::ServerMgr::removeSession( uint32_t sessionId )
{
  m_sessionMapById.erase( sessionId );
}

Sapphire::World::SessionPtr Sapphire::World::ServerMgr::getSession( uint32_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_sessionMapById.find( id );

  if( it != m_sessionMapById.end() )
    return ( it->second );

  return nullptr;
}

Sapphire::World::SessionPtr Sapphire::World::ServerMgr::getSession( const std::string& playerName )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );

  auto it = m_sessionMapByName.find( playerName );

  if( it != m_sessionMapByName.end() )
    return ( it->second );

  return nullptr;
}

void Sapphire::World::ServerMgr::removeSession( const std::string& playerName )
{
  m_sessionMapByName.erase( playerName );
}


bool Sapphire::World::ServerMgr::isRunning() const
{
  return m_bRunning;
}

std::string Sapphire::World::ServerMgr::getPlayerNameFromDb( uint32_t playerId, bool forceDbLoad )
{
  if( !forceDbLoad )
  {
    auto it = m_playerNameMapById.find( playerId );

    if( it != m_playerNameMapById.end() )
      return ( it->second );
  }

  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT name FROM charainfo WHERE characterid = " + std::to_string( playerId ) );

  if( !res->next() )
    return "Unknown";

  std::string playerName = res->getString( 1 );
  updatePlayerName( playerId, playerName );

  return playerName;
}

void Sapphire::World::ServerMgr::updatePlayerName( uint32_t playerId, const std::string & playerNewName )
{
  m_playerNameMapById[ playerId ] = playerNewName;
}

void Sapphire::World::ServerMgr::loadBNpcTemplates()
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pTeriMgr = framework()->get< TerritoryMgr >();

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

  Logger::debug( "BNpc Templates loaded: " + std::to_string( m_bNpcTemplateMap.size() ) );

}

Sapphire::Entity::BNpcTemplatePtr Sapphire::World::ServerMgr::getBNpcTemplate( const std::string& key )
{
  auto it = m_bNpcTemplateMap.find( key );

  if( it == m_bNpcTemplateMap.end() )
    return nullptr;

  return it->second;
}

Sapphire::Entity::BNpcTemplatePtr Sapphire::World::ServerMgr::getBNpcTemplate( uint32_t id )
{
  for( auto entry : m_bNpcTemplateMap )
  {
    if( entry.second->getId() == id )
      return entry.second;
  }

  return nullptr;
}
