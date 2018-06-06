#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Common.h>

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <map>

namespace Core {

  class ServerZone
  {
  public:
    ServerZone( const std::string& configPath );
    ~ServerZone();

    void run( int32_t argc, char* argv[] );

    bool loadSettings( int32_t argc, char* argv[] );

    void mainLoop();

    bool isRunning() const;

    void printBanner() const;

  private:

    uint16_t m_port;
    std::string m_ip;
    int64_t m_lastDBPingTime;

    bool m_bRunning;

    std::string m_configPath;

    std::map< uint32_t, uint32_t > m_zones;

  };

}

#endif


