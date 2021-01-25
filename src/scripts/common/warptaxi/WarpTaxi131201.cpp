#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131201 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131201() :
    Sapphire::ScriptAPI::EventScript( 131201 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.enterPredefinedPrivateInstance( 463 );
  }
};

EXPOSE_SCRIPT( WarpTaxi131201 );