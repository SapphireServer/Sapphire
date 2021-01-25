#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class WarpTaxi131088 : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi131088() :
    Sapphire::ScriptAPI::EventScript( 131088 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.eventFinish( getId(), 1 );
    player.sendDebug( "enter the walking sand..." );
    auto instance = player.getOrCreatePrivateInstance( 212 );
    if( instance )
    {
      Common::FFXIVARR_POSITION3 pos { 30, 1, 0 };
      player.setInstance( instance, pos );
    }
  }
};

EXPOSE_SCRIPT( WarpTaxi131088 );