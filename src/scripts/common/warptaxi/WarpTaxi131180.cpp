#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131180 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131180() :
    Sapphire::ScriptAPI::EventScript( 131180 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.forceZoneing( 144, -42, 0, 100, -1.58, true );
  }
};

EXPOSE_SCRIPT( WarpTaxi131180 );