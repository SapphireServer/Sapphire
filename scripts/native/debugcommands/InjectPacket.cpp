#include <ScriptObject.h>

#include <common/Network/PacketContainer.h>
#include <Session.h>
#include <Network/GameConnection.h>
#include <common/Network/CommonNetwork.h>

class InjectPacket : public DebugCommandScript
{
public:
   InjectPacket() : DebugCommandScript( "inject", "Injects a premade packet", 0 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      auto pSession = m_objects->m_zone->getSession( player.getId() );
      if( pSession )
         pSession->getZoneConnection()->injectPacket( data.c_str() + 7, player );
   }
};