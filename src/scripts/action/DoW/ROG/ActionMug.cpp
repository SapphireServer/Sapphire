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

class ActionMug : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionMug() : Sapphire::ScriptAPI::ActionScript( 2256 )
  {
  }

  static constexpr auto Potency = 140;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto dmg = action.calcDamage( Potency );
    auto absorb = 0.2f * dmg.first;

    if( ( pSource->getClass() == Common::ClassJob::Rogue || pSource->getClass() == Common::ClassJob::Ninja ) && pSource->getLevel() >= 40 && pSource->hasStatusEffect( KissOfTheViperStatus ) )
      pSource->heal( absorb );

      pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
  }
};

EXPOSE_SCRIPT( ActionMug );