#include <filesystem>

#include <Util/Util.h>
#include <Network/PacketContainer.h>
#include <Logging/Logger.h>
#include <Service.h>

#include "Network/GameConnection.h"
#include "Actor/Player.h"
#include "WorldServer.h"
#include "Manager/PlayerMgr.h"

#include "Session.h"

using namespace Sapphire::World::Manager;
namespace fs = std::filesystem;

Sapphire::World::Session::Session( uint32_t entityId ) :
  m_entityId( entityId ),
  m_lastDataTime( Common::Util::getTimeSeconds() ),
  m_lastSqlTime( Common::Util::getTimeSeconds() ),
  m_isValid( false ),
  m_isReplaying( false ),
  m_lastPing( 0 )
{
}

void Sapphire::World::Session::setZoneConnection( Network::GameConnectionPtr pZoneCon )
{
  pZoneCon->m_conType = Network::ConnectionType::Zone;
  m_pZoneConnection = pZoneCon;
}

void Sapphire::World::Session::setChatConnection( Network::GameConnectionPtr pChatCon )
{
  pChatCon->m_conType = Network::ConnectionType::Chat;
  m_pChatConnection = pChatCon;
}

Sapphire::Network::GameConnectionPtr Sapphire::World::Session::getZoneConnection() const
{
  return m_pZoneConnection;
}

Sapphire::Network::GameConnectionPtr Sapphire::World::Session::getChatConnection() const
{
  return m_pChatConnection;
}

bool Sapphire::World::Session::loadPlayer()
{
  auto& server = Common::Service< World::WorldServer >::ref();

  m_isValid = false;

  m_pPlayer = server.getPlayer( m_entityId );

  if( !m_pPlayer )
    return false;

  // check and sync player data on login
  if( !server.syncPlayer( m_pPlayer->getCharacterId() ) )
    return false;

  m_isValid = true;
  return true;
}

void Sapphire::World::Session::close()
{
  if( m_pZoneConnection )
    m_pZoneConnection->disconnect();

  if( m_pChatConnection )
    m_pChatConnection->disconnect();

  // remove the session from the player
  if( m_pPlayer )
  {
    auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
    playerMgr.onLogout( *m_pPlayer );

    m_pPlayer->unload();
  }
}

uint32_t Sapphire::World::Session::getId() const
{
  return m_entityId;
}

int64_t Sapphire::World::Session::getLastDataTime() const
{
  return m_lastDataTime;
}

int64_t Sapphire::World::Session::getLastSqlTime() const
{
  return m_lastSqlTime;
}

bool Sapphire::World::Session::isValid() const
{
  return m_isValid;
}

void Sapphire::World::Session::updateLastDataTime()
{
  m_lastDataTime = Common::Util::getTimeSeconds();
}

void Sapphire::World::Session::updateLastSqlTime()
{
  m_lastSqlTime = Common::Util::getTimeSeconds();
}

void Sapphire::World::Session::startReplay( const std::string& path )
{
  if( !fs::exists( path ) )
  {
    PlayerMgr::sendDebug( *getPlayer(), "Couldn't find folder {}.", path );
    return;
  }

  m_replayCache.clear();

  std::vector< std::tuple< uint64_t, std::string > > loadedSets;

  for( auto it = fs::directory_iterator( fs::path( path ) );
       it != fs::directory_iterator(); ++it )
  {
    // Get the filename of the current element
    auto fileName = it->path().filename().string();
    auto unixTime = std::stoull( fileName.substr( 0, 14 ) );

    if( unixTime > 1000000000 )
    {
      loadedSets.emplace_back( unixTime, it->path().string() );
    }
  }

  sort( loadedSets.begin(), loadedSets.end(),
        []( const std::tuple< uint64_t, std::string >& left, const std::tuple< uint64_t, std::string >& right )
        {
          return std::get< 0 >( left ) < std::get< 0 >( right );
        } );

  uint64_t startTime = std::get< 0 >( loadedSets.at( 0 ) );

  for( auto set : loadedSets )
  {
    uint64_t setTime = std::get< 0 >( set );
    m_replayCache.emplace_back( Common::Util::getTimeMs() + ( ( setTime - startTime ) / 1 ), std::get< 1 >( set ) );

    Logger::info( "Registering {0} for {1}, oldTime {2}", std::get< 1 >( set ), setTime - startTime, setTime );
  }

  PlayerMgr::sendDebug( *getPlayer(), "Registered {0} sets for replay" ), m_replayCache.size();
  m_isReplaying = true;
}

void Sapphire::World::Session::stopReplay()
{
  m_isReplaying = false;
  m_replayCache.clear();
}

void Sapphire::World::Session::processReplay()
{
  int at = 0;
  test:
  for( const auto& set : m_replayCache )
  {
    if( (std::get< 0 >( set ) ) <= Common::Util::getTimeMs() )
    {
      m_pZoneConnection->injectPacket( std::get< 1 >( set ), *getPlayer().get() );
      m_replayCache.erase( m_replayCache.begin() + at );

      Logger::info( "Sent for {0}, left: {1}", std::get< 1 >( set ), std::to_string( m_replayCache.size() ) );
      goto test;
    }
    at++;

  }

  if( m_replayCache.empty() )
    m_isReplaying = false;
}

void Sapphire::World::Session::sendReplayInfo()
{
  std::string message = std::to_string( m_replayCache.size() ) + " Sets left in cache, ";

  if( m_isReplaying )
    message += " is active";
  else
    message += " is idle";

  PlayerMgr::sendDebug( *getPlayer(), message );
}

void Sapphire::World::Session::update()
{
  if( m_isReplaying )
    processReplay();

  if( m_pZoneConnection )
  {
    m_pZoneConnection->processInQueue();

    // SESSION LOGIC
    m_pPlayer->update( Common::Util::getTimeMs() );

    if( Common::Util::getTimeSeconds() - static_cast< uint32_t >( getLastSqlTime() ) > 10 )
    {
      updateLastSqlTime();
      m_pPlayer->updateSql();
    }

    m_pZoneConnection->processOutQueue();
  }

  if( m_pChatConnection )
  {
    m_pChatConnection->processInQueue();
    m_pChatConnection->processOutQueue();
  }

}

Sapphire::Entity::PlayerPtr Sapphire::World::Session::getPlayer() const
{
  return m_pPlayer;
}

void Sapphire::World::Session::setLastPing( uint32_t ping )
{
  m_lastPing = ping;
}

uint32_t Sapphire::World::Session::getLastPing() const
{
  return m_lastPing;
}