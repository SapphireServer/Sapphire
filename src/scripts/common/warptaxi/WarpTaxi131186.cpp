#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131186 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131186() :
    Sapphire::ScriptAPI::EventScript( 131186 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.forceZoneing( 155, -165, 304, -325, 0.78, true );
  }
};

EXPOSE_SCRIPT( WarpTaxi131186 );