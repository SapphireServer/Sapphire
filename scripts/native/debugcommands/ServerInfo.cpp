#include <ScriptObject.h>

#include <common/Version.h>

class ServerInfo : public DebugCommandScript
{
public:
   ServerInfo() : DebugCommandScript( "serverinfo", "Displays server build information", 0 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      player.sendDebug( "Sapphire Zone " + Version::VERSION + "\nRev: " + Version::GIT_HASH );
      player.sendDebug( "Compiled: " __DATE__ " " __TIME__ );
      player.sendDebug( "Sessions: " + std::to_string( m_objects->m_zone->getSessionCount() ) );
   }
};