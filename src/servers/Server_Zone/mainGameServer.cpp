#include <iostream>

#include "ServerZone.h"
#include <boost/algorithm/string.hpp>

Core::ServerZone g_serverZone( "config/settings_zone.xml" );

int main( int32_t argc, char* argv[] )
{
   // i hate to do this, but we need to set this first...
   for(auto i = 1; i < argc; ++i )
   {
      auto arg = boost::to_lower_copy( std::string( argv[i] ) );

      // trim '-' from start of arg
      arg = arg.erase( 0, arg.find_first_not_of( '-' ) );
      if( arg == "sId" && argc > i + 1 )
      {
         g_serverZone.setServerId( std::atol( argv[i + 1] ) );
         break;
      }
   }
   g_serverZone.run( argc, argv );
   return 0;
}