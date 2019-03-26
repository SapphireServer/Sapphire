#include <iostream>

#include "ServerMgr.h"
#include <Framework.h>

#include <Util/CrashHandler.h>

using namespace Sapphire;
using namespace Sapphire::World;

Common::Util::CrashHandler crashHandler;

int main( int32_t argc, char* argv[] )
{
  auto pFramework = Sapphire::make_Framework();
  auto pServer = std::make_shared< ServerMgr >( "world.ini", pFramework );
  pFramework->set< ServerMgr >( pServer );
  pServer->run( argc, argv );
  return 0;
}
