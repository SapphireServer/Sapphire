#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131142 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131142() :
    Sapphire::ScriptAPI::EventScript( 131142 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.setPosAndSendActorMove( 0, -2, -31, 3.1415 );
  }
};

EXPOSE_SCRIPT( WarpTaxi131142 );