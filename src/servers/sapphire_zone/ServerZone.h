#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Common.h>

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <map>

#include "Forwards.h"

namespace Core {

   class ServerZone
   {
   public:
      ServerZone( const std::string& configPath );
      ~ServerZone();

      void run( int32_t argc, char* argv[] );

      bool createSession( uint32_t sessionId );
      void removeSession( uint32_t sessionId );
      void removeSession( std::string playerName );

      bool loadSettings( int32_t argc, char* argv[] );

      SessionPtr getSession( uint32_t id );
      SessionPtr getSession( std::string playerName );

      size_t getSessionCount() const;

      void mainLoop();

      bool isRunning() const;

      void printBanner() const;

   private:

      uint16_t m_port;
      std::string m_ip;
      int64_t m_lastDBPingTime;

      bool m_bRunning;

      std::string m_configPath;

      std::mutex m_sessionMutex;

      std::map< uint32_t, SessionPtr > m_sessionMapById;
      std::map< std::string, SessionPtr > m_sessionMapByName;

      std::map< uint32_t, uint32_t > m_zones;

   };

}

#endif

