#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131091 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131091() :
    Sapphire::ScriptAPI::EventScript( 131091 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.sendDebug( "exit the walking sand..." );
    player.sendUrgent( "to go to other side of the door, walk up against it and type \"!nudge 4\"." );
    player.exitInstance();
  }
};

EXPOSE_SCRIPT( WarpTaxi131091 );