
#include <Connection.h>
#include <Network/Connection.h>
#include <Network/Hive.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "ServerMgr.h"

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

#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Service.h>
#include "Manager/LinkshellMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/HousingMgr.h"
#include "Manager/DebugCommandMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/ShopMgr.h"
#include "Manager/InventoryMgr.h"
#include "Manager/EventMgr.h"
#include "Manager/ItemMgr.h"
#include "Manager/MarketMgr.h"
#include "Manager/RNGMgr.h"
#include "Manager/NaviMgr.h"
#include "Manager/ActionMgr.h"
#include "Manager/MapMgr.h"
#include "Manager/ChatChannelMgr.h"
#include "Manager/PartyMgr.h"

#include "Territory/InstanceObjectCache.h"

using namespace Sapphire::World::Manager;

Sapphire::World::ServerMgr::ServerMgr( const std::string& configName ) :
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
  auto& configMgr = Common::Service< Common::ConfigMgr >::ref();

  Logger::info( "Loading config {0}", m_configName );

  bool failedLoad = false;

  // load global cfg first
  if( !configMgr.loadGlobalConfig( m_config.global ) )
  {
    Logger::fatal( "Error loading config global.ini, copying default..." );
    failedLoad = true;
  }

  if( !configMgr.loadConfig( m_configName ) )
  {
    Logger::fatal( "Error loading config {0}", m_configName );
    failedLoad = true;
  }

  if( failedLoad )
  {
    Logger::fatal( "If this is the first time starting the server, "
                   "we've copied the default configs for your editing pleasure." );
    return false;
  }

  // load world specific config
  m_config.scripts.hotSwap = configMgr.getValue( "Scripts", "HotSwap", true );
  m_config.scripts.path = configMgr.getValue< std::string >( "Scripts", "Path", "./compiledscripts/" );
  m_config.scripts.cachePath = configMgr.getValue< std::string >( "Scripts", "CachePath", "./cache/" );

  m_config.navigation.meshPath = configMgr.getValue< std::string >( "Navigation", "MeshPath", "navi" );

  m_config.network.disconnectTimeout = configMgr.getValue< uint16_t >( "Network", "DisconnectTimeout", 20 );
  m_config.network.listenIp = configMgr.getValue< std::string >( "Network", "ListenIp", "0.0.0.0" );
  m_config.network.listenPort = configMgr.getValue< uint16_t >( "Network", "ListenPort", 54992 );
  m_config.network.inRangeDistance = configMgr.getValue< float >( "Network", "InRangeDistance", 80.f );

  m_config.motd = configMgr.getValue< std::string >( "General", "MotD", "" );

  m_config.housing.defaultEstateName = configMgr.getValue< std::string >( "Housing", "DefaultEstateName", "Estate #{}" );

  m_port = m_config.network.listenPort;
  m_ip = m_config.network.listenIp;

  return true;
}

void Sapphire::World::ServerMgr::run( int32_t argc, char* argv[] )
{
  using namespace Sapphire;
  using namespace Sapphire::World;

  Logger::init( "log/world" );

  printBanner();

  Common::Service< Common::ConfigMgr >::set();
  if( !loadSettings( argc, argv ) )
  {
    Logger::fatal( "Unable to load settings!" );
    return;
  }

  Logger::setLogLevel( m_config.global.general.logLevel );

  Logger::info( "Setting up generated EXD data" );
  auto pExdData = std::make_shared< Data::ExdDataGenerated >();
  auto dataPath = m_config.global.general.dataPath;
  if( !pExdData->init( dataPath ) )
  {
    Logger::fatal( "Error setting up generated EXD data. Make sure that DataPath is set correctly in global.ini" );
    Logger::fatal( "DataPath: {0}", dataPath );
    return;
  }
  Common::Service< Data::ExdDataGenerated >::set( pExdData );

  auto pDb = std::make_shared< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  Sapphire::Db::DbLoader loader;
  loader.addDb( *pDb, m_config.global.database );
  if( !loader.initDbs() )
  {
    Logger::fatal( "Database not initialized properly!" );
    return;
  }
  Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::set( pDb );

  auto pChatChannelMgr = std::make_shared< Manager::ChatChannelMgr >();
  Common::Service< Manager::ChatChannelMgr >::set( pChatChannelMgr );

  Logger::info( "LinkshellMgr: Caching linkshells" );
  auto pLsMgr = std::make_shared< Manager::LinkshellMgr >();
  if( !pLsMgr->loadLinkshells() )
  {
    Logger::fatal( "Unable to load linkshells!" );
    return;
  }
  Common::Service< Manager::LinkshellMgr >::set( pLsMgr );

  auto pScript = std::make_shared< Scripting::ScriptMgr >();
  if( !pScript->init() )
  {
    Logger::fatal( "Failed to setup scripts!" );
    return;
  }
  Common::Service< Scripting::ScriptMgr >::set( pScript );

  Logger::info( "Setting up InstanceObjectCache" );
  auto pInstanceObjCache = std::make_shared< Sapphire::InstanceObjectCache >();
  Common::Service< Sapphire::InstanceObjectCache >::set( pInstanceObjCache );

  Logger::info( "MapMgr: Caching quests" );
  auto pMapMgr = std::make_shared< Manager::MapMgr >();
  Common::Service< Manager::MapMgr >::set( pMapMgr );

  auto pActionMgr = std::make_shared< Manager::ActionMgr >();
  Common::Service< Manager::ActionMgr >::set( pActionMgr );

  loadBNpcTemplates();

  auto pNaviMgr = std::make_shared< Manager::NaviMgr >();
  Common::Service< Manager::NaviMgr >::set( pNaviMgr );

  Logger::info( "TerritoryMgr: Setting up zones" );
  auto pTeriMgr = std::make_shared< Manager::TerritoryMgr >();
  auto pHousingMgr = std::make_shared< Manager::HousingMgr >();
  Common::Service< Manager::HousingMgr >::set( pHousingMgr );
  Common::Service< Manager::TerritoryMgr >::set( pTeriMgr );

  if( !pHousingMgr->init() )
  {
    Logger::fatal( "Failed to setup housing!" );
    return;
  }
  if( !pTeriMgr->init() )
  {
    Logger::fatal( "Failed to setup zones!" );
    return;
  }

  auto pMarketMgr = std::make_shared< Manager::MarketMgr >();
  Common::Service< Manager::MarketMgr >::set( pMarketMgr );

  if( !pMarketMgr->init() )
  {
    Logger::fatal( "Failed to setup market manager!" );
    return;
  }



  Network::HivePtr hive( new Network::Hive() );
  Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive );

  std::vector< std::thread > thread_list;
  thread_list.emplace_back( std::thread( std::bind( &Network::Hive::run, hive.get() ) ) );

  auto pDebugCom = std::make_shared< DebugCommandMgr >();
  auto pPlayerMgr = std::make_shared< Manager::PlayerMgr >();
  auto pShopMgr = std::make_shared< Manager::ShopMgr >();
  auto pInventoryMgr = std::make_shared< Manager::InventoryMgr >();
  auto pEventMgr = std::make_shared< Manager::EventMgr >();
  auto pItemMgr = std::make_shared< Manager::ItemMgr >();
  auto pRNGMgr = std::make_shared< Manager::RNGMgr >();
  auto pPartyMgr = std::make_shared< Manager::PartyMgr >();

  Common::Service< DebugCommandMgr >::set( pDebugCom );
  Common::Service< Manager::PlayerMgr >::set( pPlayerMgr );
  Common::Service< Manager::ShopMgr >::set( pShopMgr );
  Common::Service< Manager::InventoryMgr >::set( pInventoryMgr );
  Common::Service< Manager::EventMgr >::set( pEventMgr );
  Common::Service< Manager::ItemMgr >::set( pItemMgr );
  Common::Service< Manager::RNGMgr >::set( pRNGMgr );
  Common::Service< Manager::PartyMgr >::set( pPartyMgr );

  Logger::info( "World server running on {0}:{1}", m_ip, m_port );

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
  Logger::info( "Version: {0}", Version::VERSION );
  Logger::info( "Git Hash: {0}", Version::GIT_HASH );
  Logger::info( "Compiled: " __DATE__ " " __TIME__ );
  Logger::info( "===========================================================" );
}

void Sapphire::World::ServerMgr::mainLoop()
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  while( isRunning() )
  {
    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

    auto currTime = Common::Util::getTimeSeconds();
    auto tickCount = Common::Util::getTimeMs();

    terriMgr.updateTerritoryInstances( tickCount );

    scriptMgr.update();

    std::lock_guard< std::mutex > lock( m_sessionMutex );
    for( auto sessionIt : m_sessionMapById )
    {
      auto session = sessionIt.second;
      if( session && session->getPlayer() )
      {

        // if the player is in a zone, let the zone handler take care of his updates
        // else do it here.
        if( !session->getPlayer()->getCurrentTerritory() )
          session->update();

      }
    }

    if( currTime - m_lastDBPingTime > 3 )
    {
      db.keepAlive();
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
          Logger::info( "[{0}] Session removal", it->second->getId() );
          it = m_sessionMapById.erase( it );
          removeSession( pPlayer->getContentId() );
          removeSession( pPlayer->getName() );
          continue;
        }
      }

      // remove sessions that simply timed out
      if( diff > 20 )
      {
        Logger::info( "[{0}] Session time out", it->second->getId() );

        it->second->close();
        // if( it->second.unique() )
        {
          it = m_sessionMapById.erase( it );
          removeSession( pPlayer->getContentId() );
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
    Logger::error( "[{0}] Error creating session", session_id_str );
    return false;
  }

  Logger::info( "[{0}] Creating new session", session_id_str );

  std::shared_ptr< Session > newSession( new Session( sessionId ) );
  m_sessionMapById[ sessionId ] = newSession;

  if( !newSession->loadPlayer() )
  {
    Logger::error( "[{0}] Error loading player {0}", session_id_str );
    return false;
  }

  m_sessionMapByContentId[ newSession->getPlayer()->getContentId() ] = newSession;
  m_sessionMapByName[ newSession->getPlayer()->getName() ] = newSession;

  return true;

}

Sapphire::World::SessionPtr Sapphire::World::ServerMgr::getSession( uint32_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_sessionMapById.find( id );

  if( it != m_sessionMapById.end() )
    return ( it->second );

  return nullptr;
}

Sapphire::World::SessionPtr Sapphire::World::ServerMgr::getSession( uint64_t contentId )
{
  auto it = m_sessionMapByContentId.find( contentId );

  if( it != m_sessionMapByContentId.end() )
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

void Sapphire::World::ServerMgr::removeSession( uint32_t sessionId )
{
  m_sessionMapById.erase( sessionId );
}

void Sapphire::World::ServerMgr::removeSession( uint64_t contentId )
{
  m_sessionMapByContentId.erase( contentId );
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

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT name FROM charainfo WHERE characterid = " + std::to_string( playerId ) );

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
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::ZONE_SEL_BNPCTEMPLATES );
  auto res = db.query( stmt );

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

  Logger::debug( "BNpc Templates loaded: {0}", m_bNpcTemplateMap.size() );

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
  for( const auto& entry : m_bNpcTemplateMap )
  {
    if( entry.second->getId() == id )
      return entry.second;
  }

  return nullptr;
}

Sapphire::Common::Config::WorldConfig& Sapphire::World::ServerMgr::getConfig()
{
  return m_config;
}
