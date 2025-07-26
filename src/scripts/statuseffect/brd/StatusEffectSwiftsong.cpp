#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

#include "Util/UtilMath.h"

#include <Network/CommonActorControl.h>
#include <Network/Util/PacketUtil.h>

#include "Manager/PartyMgr.h"
#include <algorithm>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectSwiftsong : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectSwiftsong() : Sapphire::ScriptAPI::StatusEffectScript( SwiftsongBuff )
  {
  }

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    if (!actor.isAlive())
    {
      actor.removeSingleStatusEffectById( SwiftsongBuff );
      return;
    }

    if( actor.isPlayer() && actor.getAsPlayer()->isInCombat() )
    {
      actor.removeSingleStatusEffectById( SwiftsongBuff );
      return;
    }
    if( actor.isBattleNpc() && actor.getAsBNpc()->getState() == Sapphire::Entity::BNpcState::Combat )
    {
      actor.removeSingleStatusEffectById( SwiftsongBuff );
      return;
    }
  }
};

EXPOSE_SCRIPT( StatusEffectSwiftsong );