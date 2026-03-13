#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>
#include <Actor/BNpc.h>
#include <Util/UtilMath.h>
#include "Manager/PlayerMgr.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionJugulate : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionJugulate() : Sapphire::ScriptAPI::ActionScript( 2256 )
  {
  }

  static constexpr auto Potency = 80;
  static constexpr auto Duration = 2;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto dmg = action.calcDamage( Potency );

    if( ( pSource->getClass() == Common::ClassJob::Rogue || pSource->getClass() == Common::ClassJob::Ninja ) && pSource->getLevel() >= 36 && pSource->hasStatusEffect( KissOfTheWaspStatus ) )
      pActionBuilder->applyStatusEffect( pTarget, Stun, ( Duration * 1000 ), 0, true );// Todo: why wont this activate >.>

    pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
  }
};

EXPOSE_SCRIPT( ActionJugulate );