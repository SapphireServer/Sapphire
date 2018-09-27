#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>


#include "Forwards.h"
#include "Action/Action.h"

#include "Zone/Zone.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "StatusEffect/StatusEffect.h"
#include "Action/ActionCollision.h"
#include "ServerZone.h"
#include "Session.h"
#include "Math/CalcBattle.h"
#include "Chara.h"
#include "Player.h"
#include "Npc.h"
#include "Zone/TerritoryMgr.h"
#include "Framework.h"
#include "Common.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;

Core::Entity::Npc::Npc( ObjKind type ) :
  Chara( type )
{

}

Core::Entity::Npc::~Npc()
{
}
