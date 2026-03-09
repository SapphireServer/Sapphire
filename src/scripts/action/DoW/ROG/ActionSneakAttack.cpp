#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>
#include <Actor/BNpc.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionSneakAttack : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSneakAttack() : Sapphire::ScriptAPI::ActionScript( SneakAttack )
  {
  }

  static constexpr auto Potency = 300;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto potency = Potency;
    if( pTarget->getAsBNpc()->isFacingTarget( *pSource ) )
      potency += 200;

    auto dmg = action.calcDamage( potency );

    pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
  }
};

EXPOSE_SCRIPT( ActionSneakAttack );