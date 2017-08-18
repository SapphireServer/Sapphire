#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Server_Common/Common.h>

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <map>

#include "Forwards.h"
#include "src/servers/Server_Zone/Actor/BattleNpcTemplate.h"

namespace Core {

   class ServerZone
   {
   public:
      ServerZone( const std::string& configPath, uint16_t serverId = 0 );
      ~ServerZone();

      void run( int32_t argc, char* argv[] );

      void setServerId( uint16_t serverId );
      uint16_t getServerId() const;

      bool createSession( uint32_t sessionId );
      void removeSession( uint32_t sessionId );
      void removeSession( std::string playerName );

      bool loadSettings( int32_t argc, char* argv[] );

      SessionPtr getSession( uint32_t id );
      SessionPtr getSession( std::string playerName );
      void updateSession( uint32_t id );
      void updateSession( std::string playerName );

      XMLConfigPtr getConfig() const;

      bool registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId,
                                 uint32_t bnpcNameId, uint32_t modelId, std::string aiName );

      Entity::BattleNpcTemplatePtr getBnpcTemplate( std::string templateName );


   private:

      uint16_t m_serverId;
      uint16_t m_port;
      std::string m_ip;

      std::string m_configPath;

      XMLConfigPtr m_pConfig;

      std::mutex m_sessionMutex;

      std::map< uint32_t, SessionPtr > m_sessionMap;
      std::map< std::string, SessionPtr > m_playerSessionMap;

      std::map< uint32_t, uint32_t > m_zones;

      std::map< std::string, Entity::BattleNpcTemplatePtr > m_bnpcTemplates;
      
   };

}

#endif

