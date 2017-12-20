#include <iostream>

#include "ServerZone.h"
#include <boost/algorithm/string.hpp>

Core::ServerZone g_serverZone( "config/settings_zone.xml" );

int main( int32_t argc, char* argv[] )
{
   g_serverZone.run( argc, argv );
   return 0;
}
