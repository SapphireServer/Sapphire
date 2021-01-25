#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131268 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131268() :
    Sapphire::ScriptAPI::EventScript( 131268 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.forceZoneing( 614, -491.1, 1.137, 540.47, 2.258, true );
  }
};

EXPOSE_SCRIPT( WarpTaxi131268 );