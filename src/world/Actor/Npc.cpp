#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>


#include "Forwards.h"
#include "Action/Action.h"

#include "Territory/Territory.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "ServerMgr.h"
#include "Session.h"
#include "Math/CalcBattle.h"
#include "Chara.h"
#include "Player.h"
#include "Npc.h"
#include "Manager/TerritoryMgr.h"
#include "Common.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Entity::Npc::Npc( ObjKind type ) :
  Chara( type )
{

}

Sapphire::Entity::Npc::~Npc()
{
}
