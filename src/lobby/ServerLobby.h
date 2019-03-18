#ifndef _SERVERLOBBY_H_
#define _SERVERLOBBY_H_

#include <map>
#include <memory>

#include <Config/ConfigDef.h>
#include "Forwards.h"

const std::string LOBBY_VERSION = "0.0.5";

namespace Sapphire
{
  class LobbySession;
  class ConfigMgr;

  using LobbySessionMap = std::map< std::string, LobbySessionPtr >;

  class ServerLobby
  {

    friend class LobbyConnection;

  private:

    LobbySessionMap m_sessionMap;
    std::string m_configPath;

    uint16_t m_port;
    std::string m_ip;

    std::shared_ptr< ConfigMgr > m_pConfig;

  public:
    ServerLobby( const std::string& configPath );

    ~ServerLobby( void ) = default;

    void run( int32_t argc, char* argv[] );

    bool loadSettings( int32_t argc, char* argv[] );

    void addSession( char* sessionId, LobbySessionPtr pSession )
    {
      m_sessionMap[ std::string( sessionId ) ] = pSession;
    }

    Sapphire::Common::Config::LobbyConfig& getConfig();

    LobbySessionPtr getSession( char* sessionId );

    uint32_t m_numConnections;

    Sapphire::Common::Config::LobbyConfig m_config;

  };

}

#endif
