#include <iostream>

#include "ServerZone.h"
#include <boost/algorithm/string.hpp>

#include "Framework.h"

extern Core::Framework g_framework;

int main( int32_t argc, char* argv[] )
{
   g_framework.getServerZone().run( argc, argv );
   return 0;
}