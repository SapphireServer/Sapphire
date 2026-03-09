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

class ActionDeathBlossom : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionDeathBlossom() : Sapphire::ScriptAPI::ActionScript( DeathBlossom )
  {
  }

  static constexpr auto Radius = 5;
  static constexpr auto Potency = 100;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto dmg = action.calcDamage( Potency );

    for( auto& pActor : pSource->getInRangeActors() )
    {
      auto pTarget = pActor->getAsChara();

      if( !pTarget->isBattleNpc() || Common::Util::distance( pSource->getPos(), pTarget->getPos() ) > Radius || pTarget->isFriendly( *pSource ) )
        continue;

      pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
    }
  }
};

EXPOSE_SCRIPT( ActionDeathBlossom );