#include "ZoneServer.h"

#include <Version.h>
#include <Logging/Logger.h>
#include <Config/XMLConfig.h>

#include <MySqlBase.h>
#include <Connection.h>

#include <Network/Connection.h>
#include <Network/Hive.h>

#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Database/DbLoader.h>
#include <Database/CharaDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Database/PreparedStatement.h>
#include <Util/Util.h>

#include <boost/make_shared.hpp>
#include <thread>


Core::ServerZone::ServerZone( const std::string& configPath ) :
  m_configPath( configPath ),
  m_bRunning( true ),
  m_lastDBPingTime( 0 )
{
}

Core::ServerZone::~ServerZone()
{
}

bool Core::ServerZone::loadSettings( int32_t argc, char* argv[] )
{
  return true;
}

void Core::ServerZone::run( int32_t argc, char* argv[] )
{


}

void Core::ServerZone::printBanner() const
{
}

void Core::ServerZone::mainLoop()
{
  while( isRunning() )
  {
    this_thread::sleep_for( chrono::milliseconds( 50 ) );
    auto currTime = Util::getTimeSeconds();
  }
}

bool Core::ZoneServer::isRunning() const
{
  return m_bRunning;
}
