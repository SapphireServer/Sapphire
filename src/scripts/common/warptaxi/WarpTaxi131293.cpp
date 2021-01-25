#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131293 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131293() :
    Sapphire::ScriptAPI::EventScript( 131293 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.forceZoneing( 759, 146.2, -4.17, 55.15, 0, true );
  }
};

EXPOSE_SCRIPT( WarpTaxi131293 );