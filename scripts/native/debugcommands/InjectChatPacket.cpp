#include <ScriptObject.h>

#include <common/Network/PacketContainer.h>
#include <Session.h>
#include <Network/GameConnection.h>
#include <common/Network/CommonNetwork.h>


class InjectChatPacket : public DebugCommandScript
{
public:
   InjectChatPacket() : DebugCommandScript( "injectc", "Injects a premade chat packet", 1 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      auto pSession = m_objects->m_zone->getSession( player.getId() );
      if( pSession )
         pSession->getChatConnection()->injectPacket( data.c_str() + 8, player );
   }
};