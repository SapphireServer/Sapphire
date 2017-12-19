#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Server_Common/Common.h>

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <map>

#include "Forwards.h"
#include "Actor/BattleNpcTemplate.h"

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
      void updateSession( uint32_t id );
      void updateSession( std::string playerName );

      XMLConfigPtr getConfig() const;

      size_t getSessionCount() const;

      bool registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId,
                                 uint32_t bnpcNameId, uint32_t modelId, std::string aiName );

      Entity::BattleNpcTemplatePtr getBnpcTemplate( std::string templateName );

      void mainLoop();

      bool isRunning() const;

      void printBanner() const;


   private:

      uint16_t m_port;
      std::string m_ip;
      uint32_t m_lastDBPingTime;

      bool m_bRunning;

      std::string m_configPath;

      XMLConfigPtr m_pConfig;

      std::mutex m_sessionMutex;

      std::map< uint32_t, SessionPtr > m_sessionMapById;
      std::map< std::string, SessionPtr > m_sessionMapByName;

      std::map< uint32_t, uint32_t > m_zones;

      std::map< std::string, Entity::BattleNpcTemplatePtr > m_bnpcTemplates;
      
   };

}

#endif

