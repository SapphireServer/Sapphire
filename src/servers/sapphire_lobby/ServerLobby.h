#pragma once

#ifndef _CSERVERLOBBY_H_
#define _CSERVERLOBBY_H_

#include <map>

#include <boost/shared_ptr.hpp>
#include <Config/XMLConfig.h>

#include "Forwards.h"

const std::string LOBBY_VERSION = "0.0.5";

namespace Core
{
   class LobbySession;
   class XMLConfig;
   typedef std::map< std::string, LobbySessionPtr > LobbySessionMap;

   class ServerLobby
   {

      friend class LobbyConnection;
   private:

      LobbySessionMap m_sessionMap;
      std::string m_configPath;

      uint16_t m_port;
      std::string m_ip;

      boost::shared_ptr<XMLConfig> m_pConfig;

   public:
      ServerLobby( const std::string& configPath );
      ~ServerLobby( void );

      void run( int32_t argc, char* argv[] );

      bool loadSettings( int32_t argc, char* argv[] );

      void addSession( char* sessionId, LobbySessionPtr pSession )
      {
         m_sessionMap[std::string( sessionId )] = pSession;
      }
      
      boost::shared_ptr<XMLConfig> getConfig() const;

      LobbySessionPtr getSession( char* sessionId );
      uint32_t m_numConnections;

   };


}

#endif
