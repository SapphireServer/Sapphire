#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131137 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131137() :
    Sapphire::ScriptAPI::EventScript( 131137 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.setPosAndSendActorMove( 24.7, 20.1, -679.2, 0.82 );
  }
};

EXPOSE_SCRIPT( WarpTaxi131137 );