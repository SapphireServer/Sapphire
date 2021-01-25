#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131143 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131143() :
    Sapphire::ScriptAPI::EventScript( 131143 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.setPosAndSendActorMove( 0, -2, -23, 0 );
  }
};

EXPOSE_SCRIPT( WarpTaxi131143 );