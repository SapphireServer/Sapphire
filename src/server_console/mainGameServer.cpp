#include <iostream>

#include "WorldServer.h"

#include <Util/CrashHandler.h>
#include <Service.h>

#include "Logging/Logger.h"
#include "Util/Util.h"

using namespace Sapphire;
using namespace Sapphire::World;

[[maybe_unused]]
Common::Util::CrashHandler crashHandler;

int main( int32_t argc, char* argv[] )
{
  Logger::init( "log/world" );

  auto pServer = std::make_shared< WorldServer >( "world.ini" );

  Common::Service< WorldServer >::set( pServer );

  pServer->init( argc, argv );

  while( pServer->isRunning() )
  {
    auto tickCount = Common::Util::getTimeMs();
    pServer->update( tickCount );
  }

  pServer->shutdown();
  return 0;
}
