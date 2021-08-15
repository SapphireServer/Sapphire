#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131306 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131306() :
    Sapphire::ScriptAPI::EventScript( 131306 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.setPosAndNotifyClient( -466, 107.7, 107.7, -2 );
  }
};

EXPOSE_SCRIPT( WarpTaxi131306 );