
#include <Connection.h>
#include <Network/Connection.h>
#include <Network/Hive.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "WorldServer.h"

#include <Version.h>
#include <Logging/Logger.h>
#include <Config/ConfigMgr.h>

#include <Exd/ExdData.h>
#include <Database/DatabaseDef.h>

#include "Actor/Player.h"

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
#include "Manager/ChatChannelMgr.h"
#include "Manager/QuestMgr.h"
#include "Manager/PartyMgr.h"
#include "Manager/FriendListMgr.h"
#include "Manager/BlacklistMgr.h"

#include "ContentFinder/ContentFinder.h"

#include "Territory/InstanceObjectCache.h"

using namespace Sapphire::World::Manager;

Sapphire::World::WorldServer::WorldServer( const std::string& configName ) :
  m_configName( configName ),
  m_bRunning( true ),
  m_lastDBPingTime( 0 ),
  m_worldId( 67 )
{
}

Sapphire::World::WorldServer::~WorldServer()
{
}

size_t Sapphire::World::WorldServer::getSessionCount() const
{
  return m_sessionMapById.size();
}

bool Sapphire::World::WorldServer::loadSettings( int32_t argc, char* argv[] )
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
  m_config.skipOpening = configMgr.getValue( "General", "SkipOpening", false );

  m_config.housing.defaultEstateName = configMgr.getValue< std::string >( "Housing", "DefaultEstateName", "Estate #{}" );

  m_port = m_config.network.listenPort;
  m_ip = m_config.network.listenIp;

  return true;
}

void Sapphire::World::WorldServer::run( int32_t argc, char* argv[] )
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
  auto pExdData = std::make_shared< Data::ExdData >();
  auto dataPath = m_config.global.general.dataPath;
  if( !pExdData->init( dataPath ) )
  {
    Logger::fatal( "Error setting up generated EXD data. Make sure that DataPath is set correctly in global.ini" );
    Logger::fatal( "DataPath: {0}", dataPath );
    return;
  }
  Common::Service< Data::ExdData >::set( pExdData );

  auto pDb = std::make_shared< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  Sapphire::Db::DbLoader loader;
  loader.addDb( *pDb, m_config.global.database );
  if( !loader.initDbs() )
  {
    Logger::fatal( "Database not initialized properly!" );
    return;
  }
  Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::set( pDb );

  Logger::info( "Loading all players" );
  if( !loadPlayers() )
  {
    Logger::fatal( "Failed to load players!" );
    return;
  }

  auto pChatChannelMgr = std::make_shared< Manager::ChatChannelMgr >();
  Common::Service< Manager::ChatChannelMgr >::set( pChatChannelMgr );

  auto pLsMgr = std::make_shared< Manager::LinkshellMgr >();

  Logger::info( "LinkshellMgr: Caching linkshells" );
  if( !pLsMgr->loadLinkshells() )
  {
    Logger::fatal( "Unable to load linkshells!" );
    return;
  }
  Common::Service< Manager::LinkshellMgr >::set( pLsMgr );

  Logger::info( "Setting up InstanceObjectCache" );
  auto pInstanceObjCache = std::make_shared< Sapphire::InstanceObjectCache >();
  Common::Service< Sapphire::InstanceObjectCache >::set( pInstanceObjCache );

  auto pActionMgr = std::make_shared< Manager::ActionMgr >();
  Common::Service< Manager::ActionMgr >::set( pActionMgr );

  auto pNaviMgr = std::make_shared< Manager::NaviMgr >();
  Common::Service< Manager::NaviMgr >::set( pNaviMgr );

  Logger::info( "TerritoryMgr: Setting up zones" );
  auto pTeriMgr = std::make_shared< Manager::TerritoryMgr >();
  auto pHousingMgr = std::make_shared< Manager::HousingMgr >();
  Common::Service< Manager::HousingMgr >::set( pHousingMgr );
  Common::Service< Manager::TerritoryMgr >::set( pTeriMgr );

  auto pScript = std::make_shared< Scripting::ScriptMgr >();
  if( !pScript->init() )
  {
    Logger::fatal( "Failed to setup scripts!" );
    return;
  }
  Common::Service< Scripting::ScriptMgr >::set( pScript );

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
  auto pQuestMgr = std::make_shared< Manager::QuestMgr >();
  auto pPartyMgr = std::make_shared< Manager::PartyMgr >();
  auto pFriendMgr = std::make_shared< Manager::FriendListMgr >();
  auto pBlacklistMgr = std::make_shared< Manager::BlacklistMgr >();
  auto contentFinder = std::make_shared< ContentFinder >();

  Common::Service< DebugCommandMgr >::set( pDebugCom );
  Common::Service< Manager::PlayerMgr >::set( pPlayerMgr );
  Common::Service< Manager::ShopMgr >::set( pShopMgr );
  Common::Service< Manager::InventoryMgr >::set( pInventoryMgr );
  Common::Service< Manager::EventMgr >::set( pEventMgr );
  Common::Service< Manager::ItemMgr >::set( pItemMgr );
  Common::Service< Manager::RNGMgr >::set( pRNGMgr );
  Common::Service< Manager::QuestMgr >::set( pQuestMgr );
  Common::Service< Manager::PartyMgr >::set( pPartyMgr );
  Common::Service< Manager::FriendListMgr >::set( pFriendMgr );
  Common::Service< Manager::BlacklistMgr >::set( pBlacklistMgr );
  Common::Service< ContentFinder >::set( contentFinder );

  Logger::info( "World server running on {0}:{1}", m_ip, m_port );

  mainLoop();

  for( auto& thread_entry : thread_list )
  {
    thread_entry.join();
  }

}

uint16_t Sapphire::World::WorldServer::getWorldId() const
{
  return m_worldId;
}

void Sapphire::World::WorldServer::setWorldId( uint16_t worldId )
{
  m_worldId = worldId;
}

void Sapphire::World::WorldServer::printBanner() const
{
  Logger::info( "===========================================================" );
  Logger::info( "Sapphire Server Project " );
  Logger::info( "Version: {0}", Version::VERSION );
  Logger::info( "Git Hash: {0}", Version::GIT_HASH );
  Logger::info( "Compiled: " __DATE__ " " __TIME__ );
  Logger::info( "===========================================================" );
}

void Sapphire::World::WorldServer::mainLoop()
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  auto& contentFinder = Common::Service< ContentFinder >::ref();

  while( isRunning() )
  {
    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

    auto currTime = Common::Util::getTimeSeconds();
    auto tickCount = Common::Util::getTimeMs();

    terriMgr.updateTerritoryInstances( tickCount );

    scriptMgr.update();

    contentFinder.update();

    updateSessions( currTime );

    DbKeepAlive( currTime );
  }
}

void Sapphire::World::WorldServer::DbKeepAlive( uint32_t currTime )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  if( currTime - m_lastDBPingTime > 3 )
  {
    db.keepAlive();
    m_lastDBPingTime = currTime;
  }
}

void Sapphire::World::WorldServer::updateSessions( uint32_t currTime )
{
  std::queue< uint32_t > sessionRemovalQueue;
  std::lock_guard< std::mutex > lock( m_sessionMutex );
  for( const auto& [ id, session ] : m_sessionMapById )
  {
    if( !session || !session->getPlayer() )
      continue;

    // if the player is in a zone, let the zone handler take care of his updates, else do it here.
    if( !session->getPlayer()->isConnected() )
      session->update();

    auto diff = difftime( currTime, session->getLastDataTime() );
    auto& player = *session->getPlayer();

    // remove session of players marked for removal ( logoff / kick )
    if( ( player.isMarkedForRemoval() && diff > 5 ) || diff > 20 )
    {
      Logger::info( "[{0}] Session removal", session->getId() );
      session->close();
      sessionRemovalQueue.push( session->getId() );
    }
  }

  while( !sessionRemovalQueue.empty() )
  {
    auto removalId = sessionRemovalQueue.front();
    sessionRemovalQueue.pop();
    if( auto session = getSession( removalId ) )
      removeSession( *session->getPlayer() );
  }
}

bool Sapphire::World::WorldServer::createSession( uint32_t sessionId )
{
  std::lock_guard< std::mutex > lock( m_sessionMutex );

  const auto sessionIdStr = std::to_string( sessionId );

  auto pSession = getSession( sessionId );

  if( pSession )
  {
    Logger::error( "[{0}] Error creating session, already in list", sessionIdStr );
    return false;
  }

  Logger::info( "[{0}] Creating new session", sessionIdStr );

  auto newSession = std::make_shared< Session >( sessionId );
  if( !newSession->loadPlayer() )
  {
    Logger::error( "[{0}] Error loading player {0}", sessionIdStr );
    return false;
  }

  m_sessionMapById[ sessionId ] = newSession;
  m_sessionMapByName[ newSession->getPlayer()->getName() ] = newSession;
  m_sessionMapByCharacterId[ newSession->getPlayer()->getCharacterId() ] = newSession;

  return true;
}

void Sapphire::World::WorldServer::removeSession( uint32_t sessionId )
{
  auto pSession = getSession( sessionId );
  if( !pSession )
    return;

  m_sessionMapById.erase( sessionId );
  m_sessionMapByName.erase( pSession->getPlayer()->getName() );
  m_sessionMapByCharacterId.erase( pSession->getPlayer()->getCharacterId() );
}

Sapphire::World::SessionPtr Sapphire::World::WorldServer::getSession( uint32_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_sessionMapById.find( id );

  if( it != m_sessionMapById.end() )
    return ( it->second );

  return nullptr;
}

Sapphire::World::SessionPtr Sapphire::World::WorldServer::getSession( uint64_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_sessionMapByCharacterId.find( id );

  if( it != m_sessionMapByCharacterId.end() )
    return ( it->second );

  return nullptr;
}

Sapphire::World::SessionPtr Sapphire::World::WorldServer::getSession( const std::string& playerName )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );

  auto it = m_sessionMapByName.find( playerName );

  if( it != m_sessionMapByName.end() )
    return ( it->second );

  return nullptr;
}

void Sapphire::World::WorldServer::removeSession( const Entity::Player& player )
{
  auto session = getSession( player.getCharacterId() );
  if( session )
    m_sessionMapById.erase( session->getId() );

  m_sessionMapByName.erase( player.getName() );
  m_sessionMapByCharacterId.erase( player.getCharacterId() );
}

bool Sapphire::World::WorldServer::isRunning() const
{
  return m_bRunning;
}

std::vector< Sapphire::World::SessionPtr > Sapphire::World::WorldServer::searchSessionByName( const std::string& playerName )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );

  std::vector< Sapphire::World::SessionPtr > results{};

  for( auto it = m_sessionMapByName.begin(); it != m_sessionMapByName.end(); ++it ) {
    if( it->first.find( playerName ) != std::string::npos ) {
      results.push_back( it->second );
    }
  }
  
  return results;
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::getPlayer( uint32_t entityId )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_playerMapById.find( entityId );

  if( it != m_playerMapById.end() )
    return ( it->second );

  // not found (new character?) - we'll load from DB and hope it's there
  return loadPlayer( entityId );
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::getPlayer( uint64_t characterId )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_playerMapByCharacterId.find( characterId );

  if( it != m_playerMapByCharacterId.end() )
    return ( it->second );

  // not found (new character?) - we'll load from DB and hope it's there
  return loadPlayer( characterId );
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::getPlayer( const std::string& playerName )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_playerMapByName.find( playerName );

  if( it != m_playerMapByName.end() )
    return ( it->second );

  // not found (new character?) - we'll load from DB and hope it's there
  return loadPlayer( playerName );
}


std::string Sapphire::World::WorldServer::getPlayerNameFromDb( uint64_t characterId, bool forceDbLoad )
{
  if( !forceDbLoad )
  {
    auto it = m_playerMapByCharacterId.find( characterId );

    if( it != m_playerMapByCharacterId.end() )
      return ( it->second->getName() );
  }

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT name FROM charainfo WHERE characterid = " + std::to_string( characterId ) );

  if( !res->next() )
    return "Unknown";

  std::string playerName = res->getString( 1 );

  return playerName;
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::addPlayer( uint64_t characterId )
{
  auto pPlayer = Entity::make_Player();

  if( !pPlayer->loadFromDb( characterId ) )
    return nullptr;

  m_playerMapById[ pPlayer->getId() ] = pPlayer;
  m_playerMapByCharacterId[ pPlayer->getCharacterId() ] = pPlayer;
  m_playerMapByName[ pPlayer->getName() ] = pPlayer;

  return pPlayer;
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::loadPlayer( uint32_t entityId )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT CharacterId FROM charainfo WHERE EntityId = " + std::to_string( entityId ) );
  if( !res || !res->next() )
    return nullptr;

  uint64_t characterId = res->getUInt64( 1 );

  return addPlayer( characterId );
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::loadPlayer( uint64_t characterId )
{
  return addPlayer( characterId );
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::loadPlayer( const std::string& playerName )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT CharacterId FROM charainfo WHERE Name = " + playerName );
  if( !res || !res->next() )
    return nullptr;

  uint64_t characterId = res->getUInt64( 1 );

  return addPlayer( characterId );
}

bool Sapphire::World::WorldServer::loadPlayers()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT CharacterId FROM charainfo" );

  // no players or failed
  while( res->next() )
  {
    uint64_t characterId = res->getUInt64( 1 );
    if( !addPlayer( characterId ) )
      return false;
  }

  return true;
}

Sapphire::Entity::PlayerPtr Sapphire::World::WorldServer::syncPlayer( uint64_t characterId )
{
  auto pPlayer = getPlayer( characterId );
  if( !pPlayer )
    return nullptr;

  // get our cached last db write
  auto lastCacheSync = pPlayer->getLastDBWrite();

  // update this player's last db write
  if( !pPlayer->syncLastDBWrite() )
    return nullptr;

  // get db last write
  auto dbSync = pPlayer->getLastDBWrite();


  // db was updated and we lost track of it  - update
  // @todo for now, always reload the player on login.
  //if( dbSync != lastCacheSync )
  {
    // clear current maps
    m_playerMapById[ pPlayer->getId() ] = nullptr;
    m_playerMapByName[ pPlayer->getName() ] = nullptr;
    m_playerMapByCharacterId[ pPlayer->getCharacterId() ] = nullptr;

    if( !pPlayer->loadFromDb( characterId ) )
      return nullptr;

    m_playerMapById[ pPlayer->getId() ] = pPlayer;
    m_playerMapByCharacterId[ pPlayer->getCharacterId() ] = pPlayer;
    m_playerMapByName[ pPlayer->getName() ] = pPlayer;
  }

  return pPlayer;
}

std::map< int32_t, Sapphire::World::WorldServer::BNPCMap >& Sapphire::World::WorldServer::getBNpcTeriMap()
{
  return m_bNpcTerritoryMap;
}

Sapphire::Common::Config::WorldConfig& Sapphire::World::WorldServer::getConfig()
{
  return m_config;
}

void Sapphire::World::WorldServer::queueForPlayer( uint64_t characterId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket )
{
  auto pSession = getSession( characterId );
  if( !pSession )
    return;

  auto pZoneCon = pSession->getZoneConnection();
  if( pZoneCon )
    pZoneCon->queueOutPacket( pPacket );

}

void Sapphire::World::WorldServer::queueForPlayer( uint64_t characterId, std::vector< Sapphire::Network::Packets::FFXIVPacketBasePtr > packets )
{
  auto pSession = getSession( characterId );
  if( !pSession )
    return;

  auto pZoneCon = pSession->getZoneConnection();
  if( pZoneCon )
    for( auto& packet : packets )
    {
      pZoneCon->queueOutPacket( packet );
    }
}