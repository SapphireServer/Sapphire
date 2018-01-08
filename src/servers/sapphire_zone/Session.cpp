#include <time.h>

#include <common/Util/Util.h>
#include <common/Network/PacketContainer.h>
#include "Network/GameConnection.h"
#include "Session.h"

#include "Actor/Player.h"
#include <boost/filesystem/operations.hpp>
#include <common/Logging/Logger.h>

extern Core::Logger g_log;

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

void Core::Session::startReplay( const std::string& folderpath )
{
   if( !boost::filesystem::exists(folderpath) )
   {
      getPlayer()->sendDebug( "Couldn't find folder." );
      return;
   }

   m_replayCache.clear();

   std::vector<std::tuple<uint64_t, std::string>> loadedSets;

   for( auto it = boost::filesystem::directory_iterator( boost::filesystem::path( folderpath ) ); it != boost::filesystem::directory_iterator(); ++it )
   {
      // Get the filename of the current element
      auto filename = it->path().filename().string();
      auto unixtime = atoi( filename.substr( 0, 10 ).c_str() );

      if( unixtime > 1000000000)
      {
         loadedSets.push_back( std::tuple<uint64_t, std::string>( unixtime, it->path().string() ) );
      }
   }

   sort( loadedSets.begin(), loadedSets.end(), [ ]( const std::tuple<uint64_t, std::string>& left, const std::tuple<uint64_t, std::string>& right)
   {
      return std::get<0>( left ) < std::get<0>( right );
   } );

   int startTime = std::get<0>( loadedSets.at( 0 ) );

   for( auto thing : loadedSets )
   {
      m_replayCache.push_back( std::tuple<uint64_t, std::string>( Util::getTimeSeconds() + ( std::get<0>( thing ) - startTime ), std::get<1>( thing ) ) );
      g_log.info( "Registering " + std::get<1>( thing ) + " for " + std::to_string( std::get<0>( thing ) - startTime ) );
   }

   getPlayer()->sendDebug( "Registered " + std::to_string( m_replayCache.size() ) + " sets for replay" );
   m_isReplaying = true;
}

void Core::Session::stopReplay()
{
   m_isReplaying = false;
   m_replayCache.clear();
}

void Core::Session::update()
{
   if( m_isReplaying )
   {
      int at = 0;
      for( auto const& set : m_replayCache ) {
         if( std::get<0>( set ) == Util::getTimeSeconds() )
         {
            m_pZoneConnection->injectPacket( std::get<1>( set ), *getPlayer().get() );
            m_replayCache.erase( m_replayCache.begin() + at );
         }
         at++;
      }
   }

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

