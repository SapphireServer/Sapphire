#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131166 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131166() :
    Sapphire::ScriptAPI::EventScript( 131166 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.enterPredefinedPrivateInstance( 395 );
  }
};

EXPOSE_SCRIPT( WarpTaxi131166 );