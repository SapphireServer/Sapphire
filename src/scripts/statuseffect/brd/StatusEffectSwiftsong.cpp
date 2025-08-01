#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectSwiftsong : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectSwiftsong() : Sapphire::ScriptAPI::StatusEffectScript( SwiftsongStatus )
  {
  }

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    if (!actor.isAlive())
    {
      actor.removeSingleStatusEffectById( SwiftsongStatus );
      return;
    }

    if( actor.isPlayer() && actor.getAsPlayer()->isInCombat() )
    {
      actor.removeSingleStatusEffectById( SwiftsongStatus );
      return;
    }
    if( actor.isBattleNpc() && actor.getAsBNpc()->getState() == Sapphire::Entity::BNpcState::Combat )
    {
      actor.removeSingleStatusEffectById( SwiftsongStatus );
      return;
    }
  }
};

EXPOSE_SCRIPT( StatusEffectSwiftsong );