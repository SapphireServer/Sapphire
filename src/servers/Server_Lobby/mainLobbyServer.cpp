#include "ServerLobby.h"

Core::ServerLobby g_serverLobby( "config/settings_lobby.xml" );

int main( int argc, char* argv[] )
{

   g_serverLobby.run( argc, argv );

   return 0;
}

