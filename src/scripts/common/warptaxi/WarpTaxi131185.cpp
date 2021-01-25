#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131185 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131185() :
    Sapphire::ScriptAPI::EventScript( 131185 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.forceZoneing( 418, 0, -2.6, 141.3, -3.1415, true );
  }
};

EXPOSE_SCRIPT( WarpTaxi131185 );