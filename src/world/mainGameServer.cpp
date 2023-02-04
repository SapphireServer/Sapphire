#include <iostream>

#include "WorldServer.h"

#include <Util/CrashHandler.h>
#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::World;

[[maybe_unused]]
Common::Util::CrashHandler crashHandler;

int main( int32_t argc, char* argv[] )
{
  auto pServer = std::make_shared< WorldServer >( "world.ini" );

  Common::Service< WorldServer >::set( pServer );

  pServer->run( argc, argv );
  return 0;
}
