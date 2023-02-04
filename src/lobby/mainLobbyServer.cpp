#include "ServerLobby.h"

#include <Util/CrashHandler.h>

Sapphire::Common::Util::CrashHandler crashHandler;

Sapphire::Lobby::ServerLobby g_serverLobby( "lobby.ini" );

int main( int32_t argc, char* argv[] )
{

  g_serverLobby.run( argc, argv );

  return 0;
}

