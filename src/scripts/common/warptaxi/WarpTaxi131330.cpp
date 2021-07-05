#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131330 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131330() :
    Sapphire::ScriptAPI::EventScript( 131330 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.forceZoneing( 814, -464, 361.72, 14.84, -3.14, false );
  }
};

EXPOSE_SCRIPT( WarpTaxi131330 );