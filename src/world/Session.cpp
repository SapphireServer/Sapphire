#include <filesystem>
#include <time.h>

#include <Util/Util.h>
#include <Network/PacketContainer.h>
#include <Logging/Logger.h>

#include "Network/GameConnection.h"
#include "Actor/Player.h"

#include "Session.h"

namespace fs = std::filesystem;

Sapphire::World::Session::Session( uint32_t sessionId ) :
  m_sessionId( sessionId ),
  m_lastDataTime( Common::Util::getTimeSeconds() ),
  m_lastSqlTime( Common::Util::getTimeSeconds() ),
  m_isValid( false ),
  m_isReplaying( false )
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

  m_pPlayer = Entity::make_Player();

  if( !m_pPlayer->load( m_sessionId, shared_from_this() ) )
  {
    m_isValid = false;
    return false;
  }

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
    m_pPlayer->clearBuyBackMap();
    if( m_pPlayer->isInParty() )
    {
      m_pPlayer->getPartyLeader()->removePartyMember( m_pPlayer );
    }
    // do one last update to db
    m_pPlayer->updateSql();
    // reset the zone, so the zone handler knows to remove the actor
    m_pPlayer->setCurrentZone( nullptr );
  }
}

uint32_t Sapphire::World::Session::getId() const
{
  return m_sessionId;
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
    getPlayer()->sendDebug( "Couldn't find folder." );
    return;
  }

  m_replayCache.clear();

  std::vector< std::tuple< uint64_t, std::string > > loadedSets;

  for( auto it = fs::directory_iterator( fs::path( path ) );
       it != fs::directory_iterator(); ++it )
  {
    // Get the filename of the current element
    auto fileName = it->path().filename().string();
    auto unixTime = std::stoull( fileName.substr( 0, 14 ).c_str() );

    if( unixTime > 1000000000 )
    {
      loadedSets.push_back( std::tuple< uint64_t, std::string >( unixTime, it->path().string() ) );
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
    m_replayCache.push_back( std::tuple< uint64_t, std::string >(
      Common::Util::getTimeMs() + ( std::get< 0 >( set ) - startTime ), std::get< 1 >( set ) ) );

    Logger::info( "Registering {0} for {1}", std::get< 1 >( set ), std::get< 0 >( set ) - startTime );
  }

  getPlayer()->sendDebug( "Registered {0} sets for replay" ), m_replayCache.size();
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
  for( const auto& set : m_replayCache )
  {
    if( std::get< 0 >( set ) <= Common::Util::getTimeMs() )
    {
      m_pZoneConnection->injectPacket( std::get< 1 >( set ), *getPlayer().get() );
      m_replayCache.erase( m_replayCache.begin() + at );
      //g_framework.getLogger().info( "Sent for " + std::to_string( std::get< 0 >( set ) ) + ", left: " + std::to_string( m_replayCache.size() ) );
    }
    at++;
  }

  if( m_replayCache.size() == 0 )
    m_isReplaying = false;
}

void Sapphire::World::Session::sendReplayInfo()
{
  std::string message = std::to_string( m_replayCache.size() ) + " Sets left in cache, ";

  if( m_isReplaying )
    message += " is active";
  else
    message += " is idle";

  getPlayer()->sendDebug( message );
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

