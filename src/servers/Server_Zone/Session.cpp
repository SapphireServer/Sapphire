#include <time.h>

#include <Server_Common/Util/Util.h>
#include <Server_Common/Network/PacketContainer.h>
#include "Network/GameConnection.h"
#include "Session.h"

#include "Actor/Player.h"

Core::Session::Session( uint32_t sessionId )
   : m_sessionId( sessionId )
   , m_lastDataTime( static_cast< uint32_t >( Util::getTimeSeconds() ) )
   , m_lastSqlTime( static_cast< uint32_t >( Util::getTimeSeconds() ) )
   , m_isValid( false )
{

   //   boost::posix_time::ptime now = boost::date_time::not_a_date_time;
   //   now = boost::posix_time::microsec_clock::universal_time();

}

Core::Session::~Session()
{
}

void Core::Session::setZoneConnection( Network::GameConnectionPtr pZoneCon )
{
   pZoneCon->m_conType = Network::ConnectionType::Zone;
   m_pZoneConnection = pZoneCon;
}

void Core::Session::setChatConnection( Network::GameConnectionPtr pChatCon )
{
    pChatCon->m_conType = Network::ConnectionType::Chat;
    m_pChatConnection = pChatCon;
}

Core::Network::GameConnectionPtr Core::Session::getZoneConnection() const
{
   return m_pZoneConnection;
}

Core::Network::GameConnectionPtr Core::Session::getChatConnection() const
{
    return m_pChatConnection;
}


bool Core::Session::loadPlayer()
{

   m_pPlayer = Entity::PlayerPtr( new Entity::Player() );

   if( !m_pPlayer->load( m_sessionId, shared_from_this() ) )
   {
      m_isValid = false;
      return false;
   }
   
   m_isValid = true;

   return true;

}

void Core::Session::close()
{
   if( m_pZoneConnection )
      m_pZoneConnection->Disconnect();

   if( m_pChatConnection )
      m_pChatConnection->Disconnect();

   // remove the session from the player
   if( m_pPlayer )
      // reset the zone, so the zone handler knows to remove the actor
      m_pPlayer->setCurrentZone( nullptr );
}

uint32_t Core::Session::getId() const
{
   return m_sessionId;
}

uint32_t Core::Session::getLastDataTime() const
{
   return m_lastDataTime;
}

uint32_t Core::Session::getLastSqlTime() const
{
   return m_lastSqlTime;
}

bool Core::Session::isValid() const
{
   return m_isValid;
}

void Core::Session::updateLastDataTime()
{
   m_lastDataTime = static_cast< uint32_t >( Util::getTimeSeconds() );
}

void Core::Session::updateLastSqlTime()
{
   m_lastSqlTime = static_cast< uint32_t >( Util::getTimeSeconds() );
}

void Core::Session::update()
{
   if( m_pZoneConnection )
   {
      m_pZoneConnection->processInQueue();
      
      // SESSION LOGIC
      m_pPlayer->update( Util::getTimeMs() );

      if( ( static_cast< uint32_t >( Util::getTimeSeconds() ) - static_cast< uint32_t >( getLastSqlTime() ) ) > 10  )
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

Core::Entity::PlayerPtr Core::Session::getPlayer() const
{
   return m_pPlayer;
}

