#include "ServerLobby.h"

Core::ServerLobby g_serverLobby( "lobby.ini" );

int main( int32_t argc, char* argv[] )
{

  g_serverLobby.run( argc, argv );

  return 0;
}

