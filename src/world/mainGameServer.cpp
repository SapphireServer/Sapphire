#include <iostream>

#include "ServerMgr.h"
#include <Framework.h>

#include <Config/ConfigMgr.h>

Sapphire::Framework g_fw;

using namespace Sapphire;
using namespace Sapphire::World;

bool setupFramework()
{
  auto pServer = std::make_shared< ServerMgr >( "config.ini" );
  g_fw.set< ServerMgr >( pServer );

  return true;
}

int main( int32_t argc, char* argv[] )
{
  if( !setupFramework() )
    return 0; // too fucking bad...

  g_fw.get< ServerMgr >()->run( argc, argv );
  return 0;
}
