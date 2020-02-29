#include <iostream>

#include "ServerMgr.h"
#include <Framework.h>

#include <Util/CrashHandler.h>
#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::World;

[[maybe_unused]]
Common::Util::CrashHandler crashHandler;

int main( int32_t argc, char* argv[] )
{
  auto pFramework = make_Framework();
  auto pServer = std::make_shared< ServerMgr >( "world.ini", pFramework );

  Common::Service< ServerMgr >::set( pServer );

  pServer->run( argc, argv );
  return 0;
}
