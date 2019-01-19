#include "ServerLobby.h"

Sapphire::ServerLobby g_serverLobby( "lobby.ini" );

int main( int32_t argc, char* argv[] )
{

  g_serverLobby.run( argc, argv );

  return 0;
}

