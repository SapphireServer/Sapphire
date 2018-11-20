#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Common.h>

#include <mutex>
#include <map>

#include "ForwardsZone.h"

namespace Core {

class ServerMgr
{
public:
  ServerMgr( const std::string& configName );

  ~ServerMgr();

  void run( int32_t argc, char* argv[] );

  bool createSession( uint32_t sessionId );

  void removeSession( uint32_t sessionId );
  void removeSession( const std::string& playerName );

  SessionPtr getSession( uint32_t id );
  SessionPtr getSession( const std::string& playerName );

  size_t getSessionCount() const;

  uint16_t getWorldId() const;
  void setWorldId( uint16_t worldId );

  void mainLoop();

  bool isRunning() const;

  void printBanner() const;

  bool loadSettings( int32_t argc, char* argv[] );
  void loadBNpcTemplates();

  Entity::BNpcTemplatePtr getBNpcTemplate( const std::string& key );
  Entity::BNpcTemplatePtr getBNpcTemplate( uint32_t id );

  std::string getPlayerNameFromDb( uint32_t playerId );

private:
  uint16_t m_port;
  std::string m_ip;
  int64_t m_lastDBPingTime;
  bool m_bRunning;
  uint16_t m_worldId;

  std::string m_configName;

  std::mutex m_sessionMutex;

  std::map< uint32_t, SessionPtr > m_sessionMapById;
  std::map< std::string, SessionPtr > m_sessionMapByName;
  std::map< uint32_t, uint32_t > m_zones;
  std::map< std::string, Entity::BNpcTemplatePtr > m_bNpcTemplateMap;

};

}

#endif

