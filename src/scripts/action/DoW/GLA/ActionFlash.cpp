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

class ActionFlash : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionFlash() : Sapphire::ScriptAPI::ActionScript( Flash )
  {
  }

  static constexpr auto Radius = 5;
  static constexpr auto Duration = 12;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    auto dmg = action.calcDamage( 600 );

    for( auto& pActor : pSource->getInRangeActors() )
    {
      auto pTarget = pActor->getAsChara();

      if( pTarget->isFriendly( *pSource ) || Common::Util::distance( pSource->getPos(), pTarget->getPos() ) > Radius )
        continue;

      if( ( pSource->getClass() == Common::ClassJob::Gladiator || pSource->getClass() == Common::ClassJob::Paladin ) && pSource->getLevel() >= 20 )
        pActionBuilder->applyStatusEffect( pTarget, Blind, ( Duration * 1000 ), 0, true );

      pActor->getAsBNpc()->hateListUpdate( pSource, dmg.first ); // Todo: check for parity
      // it appears this works and hits with calculated enmity but hits for a second 215 seemingly out of nowhere
    }
  }
};

EXPOSE_SCRIPT( ActionFlash );