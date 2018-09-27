#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Common.h>

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <map>

#include "ForwardsZone.h"

namespace Core {

class ServerZone
{
public:
  ServerZone( const std::string& configName );

  ~ServerZone();

  void run( int32_t argc, char* argv[] );

  bool createSession( uint32_t sessionId );

  void removeSession( uint32_t sessionId );
  void removeSession( const std::string& playerName );

  SessionPtr getSession( uint32_t id );
  SessionPtr getSession( const std::string& playerName );

  size_t getSessionCount() const;

  void mainLoop();

  bool isRunning() const;

  void printBanner() const;

  bool loadSettings( int32_t argc, char* argv[] );
  void loadBNpcTemplates();

  Entity::BNpcTemplatePtr getBNpcTemplate( const std::string& key );
  Entity::BNpcTemplatePtr getBNpcTemplate( uint32_t id );

private:
  uint16_t m_port;
  std::string m_ip;
  int64_t m_lastDBPingTime;

  bool m_bRunning;

  std::string m_configName;

  std::mutex m_sessionMutex;

  std::map< uint32_t, SessionPtr > m_sessionMapById;
  std::map< std::string, SessionPtr > m_sessionMapByName;

  std::map< uint32_t, uint32_t > m_zones;

  std::map< std::string, Entity::BNpcTemplatePtr > m_bNpcTemplateMap;

};

}

#endif

