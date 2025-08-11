
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
#include "Manager/TaskMgr.h"

#include "Task/TestTask.h"

#include "Script/ScriptMgr.h"

#include "Linkshell/Linkshell.h"
#include "FreeCompany/FreeCompany.h"

#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Service.h>
#include "Manager/AchievementMgr.h"
#include "Manager/LinkshellMgr.h"
#include "Manager/LootTableMgr.h"
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
#include "Manager/WarpMgr.h"
#include "Manager/FreeCompanyMgr.h"
#include "Manager/MapMgr.h"

#include "ContentFinder/ContentFinder.h"

#include "Territory/InstanceObjectCache.h"

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;

WorldServer::WorldServer( const std::string& configName ) :
  m_configName( configName ),
  m_bRunning( true ),
  m_lastDBPingTime( 0 ),
  m_worldId( 67 ),
  m_port( 0 )
{
}

size_t WorldServer::getSessionCount() const
{
  return m_sessionMapById.size();
}

bool WorldServer::loadSettings( int32_t argc, char* argv[] )
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

std::string readFileToString( const std::string& filename )
{
  // Open the file for reading
  std::ifstream file( filename );

  // Check if the file was opened successfully
  if( !file )
  {
    throw std::runtime_error( "Failed to open file" );
  }

  // Read the contents of the file into a string
  std::string fileContents( ( std::istreambuf_iterator< char >( file ) ),
                              std::istreambuf_iterator< char >() );

  // Close the file
  file.close();

  // Remove all newlines from the file contents
  fileContents.erase( std::remove( fileContents.begin(), fileContents.end(), '\n' ), fileContents.end() );
  fileContents.erase( std::remove( fileContents.begin(), fileContents.end(), '\r' ), fileContents.end() );


  // Return the file contents as a string
  return fileContents;
}

void WorldServer::run( int32_t argc, char* argv[] )
{
  using namespace Sapphire;

  auto start = Common::Util::getTimeMs();

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

  try
  {
    auto verPath = dataPath + "/../ffxivgame.ver";
    auto verString = readFileToString( verPath );
    if( verString != m_config.global.general.dataVersion )
    {
      Logger::fatal( "Sqpack version {} does not match expected version {}!", verString, m_config.global.general.dataVersion );
      return;
    }
  }
  catch ( const std::exception& e )
  {
    Logger::fatal( e.what() );
    return;
  }

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

  auto pRNGMgr = std::make_shared< Manager::RNGMgr >();
  Common::Service< Manager::RNGMgr >::set( pRNGMgr );

  auto pPlayerMgr = std::make_shared< Manager::PlayerMgr >();
  Logger::info( "Loading all players" );
  if( !pPlayerMgr->loadPlayers() )
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

  auto pFcMgr = std::make_shared< Manager::FreeCompanyMgr >();
  Logger::info( "FreeCompanyMgr: Caching free companies" );
  if( !pFcMgr->loadFreeCompanies() )
  {
    Logger::fatal( "Unable to load free companies!" );
    return;
  }
  Common::Service< Manager::FreeCompanyMgr >::set( pFcMgr );

  auto pAchvMgr = std::make_shared< Manager::AchievementMgr >();

  Logger::info( "AchievementMgr: Caching data" );
  if( !pAchvMgr->cacheAchievements() )
  {
    Logger::fatal( "Unable to cache achievements!" );
    return;
  }
  Common::Service< Manager::AchievementMgr >::set( pAchvMgr );

  auto pLootTableMgr = std::make_shared< Manager::LootTableMgr >();

  Logger::info( "LootTableMgr: Caching loot tables" );
  if( !pLootTableMgr->cacheLootTables() )
  {
    Logger::fatal( "Unable to cache loot tables!" );
    return;
  }
  Common::Service< Manager::LootTableMgr >::set( pLootTableMgr );

  Logger::info( "Setting up InstanceObjectCache" );
  auto pInstanceObjCache = std::make_shared< Sapphire::InstanceObjectCache >();
  Common::Service< Sapphire::InstanceObjectCache >::set( pInstanceObjCache );

  auto pActionMgr = std::make_shared< Manager::ActionMgr >();

  Logger::info( "ActionMgr: Caching action LUT" );
  if( !pActionMgr->cacheActionLut() )
  {
    Logger::fatal( "Unable to cache actions!" );
    return;
  }
  if( !pActionMgr->cacheActionShapeLut() )
  {
    Logger::fatal( "Unable to cache action shapes!" );
    return;
  }
  Common::Service< Manager::ActionMgr >::set( pActionMgr );

  auto pMapMgr = std::make_shared< Manager::MapMgr >();

  Logger::info( "MapMgr: Caching quests" );
  if( !pMapMgr->loadQuests() )
  {
    Logger::fatal( "Unable to cache quests!" );
    return;
  }
  Common::Service< Manager::MapMgr >::set( pMapMgr );

  auto pNaviMgr = std::make_shared< Manager::NaviMgr >();
  Common::Service< Manager::NaviMgr >::set( pNaviMgr );

  Logger::info( "TerritoryMgr: Setting up zones" );
  auto pTeriMgr = std::make_shared< Manager::TerritoryMgr >();
  auto pHousingMgr = std::make_shared< Manager::HousingMgr >();
  auto warpMgr = std::make_shared< Manager::WarpMgr >();
  Common::Service< Manager::HousingMgr >::set( pHousingMgr );
  Common::Service< Manager::TerritoryMgr >::set( pTeriMgr );
  Common::Service< Manager::WarpMgr >::set( warpMgr );

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
  try
  {
    Network::addServerToHive< Network::GameConnection >( m_ip, m_port, hive );
  } catch( std::exception& e )
  {
    Logger::fatal( "Error starting server: {0}", e.what() );
    return;
  }

  std::vector< std::thread > thread_list;
  thread_list.emplace_back( std::thread( std::bind( &Network::Hive::run, hive.get() ) ) );

  auto pDebugCom = std::make_shared< DebugCommandMgr >();
  auto pShopMgr = std::make_shared< Manager::ShopMgr >();
  auto pInventoryMgr = std::make_shared< Manager::InventoryMgr >();
  auto pEventMgr = std::make_shared< Manager::EventMgr >();
  auto pItemMgr = std::make_shared< Manager::ItemMgr >();
  auto pQuestMgr = std::make_shared< Manager::QuestMgr >();
  auto pPartyMgr = std::make_shared< Manager::PartyMgr >();
  auto pFriendMgr = std::make_shared< Manager::FriendListMgr >();
  auto pBlacklistMgr = std::make_shared< Manager::BlacklistMgr >();
  auto contentFinder = std::make_shared< ContentFinder >();
  auto taskMgr = std::make_shared< Manager::TaskMgr >();

  Common::Service< DebugCommandMgr >::set( pDebugCom );
  Common::Service< Manager::PlayerMgr >::set( pPlayerMgr );
  Common::Service< Manager::ShopMgr >::set( pShopMgr );
  Common::Service< Manager::InventoryMgr >::set( pInventoryMgr );
  Common::Service< Manager::EventMgr >::set( pEventMgr );
  Common::Service< Manager::ItemMgr >::set( pItemMgr );
  Common::Service< Manager::QuestMgr >::set( pQuestMgr );
  Common::Service< Manager::PartyMgr >::set( pPartyMgr );
  Common::Service< Manager::FriendListMgr >::set( pFriendMgr );
  Common::Service< Manager::BlacklistMgr >::set( pBlacklistMgr );
  Common::Service< ContentFinder >::set( contentFinder );
  Common::Service< Manager::TaskMgr >::set( taskMgr );

  Logger::debug( "Initialization took {0}ms", Common::Util::getTimeMs() - start );

  Logger::info( "World server running on {0}:{1}", m_ip, m_port );

  mainLoop();

  for( auto& thread_entry : thread_list )
  {
    thread_entry.join();
  }

}

uint16_t WorldServer::getWorldId() const
{
  return m_worldId;
}

void WorldServer::setWorldId( uint16_t worldId )
{
  m_worldId = worldId;
}

void WorldServer::printBanner() const
{
  Logger::info( "===========================================================" );
  Logger::info( "Sapphire Server Project " );
  Logger::info( "Version: {0}", Version::VERSION );
  Logger::info( "Git Hash: {0}", Version::GIT_HASH );
  Logger::info( "Compiled: " __DATE__ " " __TIME__ );
  Logger::info( "===========================================================" );
}

void WorldServer::mainLoop()
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  auto& contentFinder = Common::Service< ContentFinder >::ref();

  auto& taskMgr = Common::Service< World::Manager::TaskMgr >::ref();

  while( isRunning() )
  {
    auto tickCount = Common::Util::getTimeMs();

    auto currTime = Common::Util::getTimeSeconds();
    taskMgr.update( tickCount );
    updateSessions( currTime );

    if( tickCount - m_lastServerTick < 300 )
    {
      std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
      continue;
    }
    m_lastServerTick = tickCount;

    terriMgr.updateTerritoryInstances( tickCount );
    scriptMgr.update();
    contentFinder.update();


    DbKeepAlive( currTime );
  }
}

void WorldServer::DbKeepAlive( uint32_t currTime )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  if( currTime - m_lastDBPingTime > 3 )
  {
    db.keepAlive();
    m_lastDBPingTime = currTime;
  }
}

void WorldServer::updateSessions( uint32_t currTime )
{
  std::queue< uint32_t > sessionRemovalQueue;
  std::lock_guard< std::mutex > lock( m_sessionMutex );
  for( const auto& [ id, session ] : m_sessionMapById )
  {
    if( !session || !session->getPlayer() )
      continue;

    auto& player = *session->getPlayer();

    // if the player is in a zone, let the zone handler take care of his updates, else do it here.
    if( !player.isConnected() )
      session->update();

    auto diff = difftime( currTime, session->getLastDataTime() );

    // remove session of players marked for removal ( logoff / kick )
    if( ( player.isMarkedForRemoval() && diff > 5 ) || diff > 20 )
    {
      player.removeOnlineStatus( Common::OnlineStatus::Online );
      player.addOnlineStatus( Common::OnlineStatus::Offline );

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

bool WorldServer::createSession( uint32_t sessionId )
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
  m_sessionMapByCharacterId[ newSession->getPlayer()->getCharacterId() ] = newSession;

  return true;
}

void WorldServer::removeSession( uint32_t sessionId )
{
  auto pSession = getSession( sessionId );
  if( !pSession )
    return;

  m_sessionMapById.erase( sessionId );
  m_sessionMapByCharacterId.erase( pSession->getPlayer()->getCharacterId() );
}

SessionPtr WorldServer::getSession( uint32_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_sessionMapById.find( id );

  if( it != m_sessionMapById.end() )
    return ( it->second );

  return nullptr;
}

SessionPtr WorldServer::getSession( uint64_t id )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_sessionMapByCharacterId.find( id );

  if( it != m_sessionMapByCharacterId.end() )
    return ( it->second );

  return nullptr;
}

void WorldServer::removeSession( const Entity::Player& player )
{
  m_sessionMapById.erase( player.getId() );
  m_sessionMapByCharacterId.erase( player.getCharacterId() );
}

bool WorldServer::isRunning() const
{
  return m_bRunning;
}

Sapphire::Common::Config::WorldConfig& WorldServer::getConfig()
{
  return m_config;
}

void WorldServer::queueForPlayer( uint64_t characterId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket )
{
  auto pSession = getSession( characterId );
  if( !pSession )
    return;

  auto pZoneCon = pSession->getZoneConnection();
  if( pZoneCon )
    pZoneCon->queueOutPacket( pPacket );
}

void WorldServer::queueChatForPlayer( uint64_t characterId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket )
{
  auto pSession = getSession( characterId );
  if( !pSession )
    return;

  auto pChatCon = pSession->getChatConnection();
  if( pChatCon )
    pChatCon->queueOutPacket( pPacket );
}

void WorldServer::queueForPlayers( const std::set< uint64_t >& characterIds, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket )
{
  if( characterIds.empty() )
    return;

  for( auto& characterId : characterIds )
    queueForPlayer( characterId, pPacket );
}

void WorldServer::queueForPlayer( uint64_t characterId, std::vector< Sapphire::Network::Packets::FFXIVPacketBasePtr > packets )
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

void WorldServer::queueForPlayers( const std::set< uint64_t >& characterIds, std::vector< Sapphire::Network::Packets::FFXIVPacketBasePtr > packets )
{
  for( auto& characterId : characterIds )
    for( auto& packet : packets )
    {
      queueForPlayer( characterId, packet );
    }
}

void WorldServer::queueForLinkshell( uint64_t lsId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket, std::set< uint64_t > exceptionCharIdList )
{
  auto lsMgr = Common::Service< Manager::LinkshellMgr >::ref();

  auto ls = lsMgr.getLinkshellById( lsId );
  if( !ls )
    return;

  auto members = ls->getAllMemberIds();

  for( const auto& memberId : members )
  {
    if( exceptionCharIdList.count( memberId ) )
      continue;

    queueForPlayer( memberId, pPacket );
  }

}

void WorldServer::queueForFreeCompany( uint64_t fcId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket, std::set< uint64_t > exceptionCharIdList )
{
  auto fcMgr = Common::Service< Manager::FreeCompanyMgr >::ref();

  auto fc = fcMgr.getFreeCompanyById( fcId );
  if( !fc )
    return;

  auto members = fc->getMemberIdList();

  for( const auto& memberId : members )
  {
    if( exceptionCharIdList.count( memberId ) )
      continue;

    queueForPlayer( memberId, pPacket );
  }

}