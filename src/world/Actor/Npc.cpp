#include <Network/PacketContainer.h>
#include "Action/Action.h"
#include "Territory/Territory.h"

#include "Player.h"
#include "Npc.h"
#include "Common.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

Sapphire::Entity::Npc::Npc( ObjKind type ) : Chara( type )
{

}

Sapphire::Entity::Npc::~Npc()
{
}
