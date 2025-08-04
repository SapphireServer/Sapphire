#include <Action/Action.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

#include <Common.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionVulcanBurst : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionVulcanBurst() : Sapphire::ScriptAPI::ActionScript( 454 )
  {
  }

  static constexpr auto Potency = 300;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();

    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    for( auto& actor : pSource->getInRangeActors() )
    {
      
      auto pTarget = actor->getAsPlayer();
      if( !pTarget )
        continue;
      auto distance = Common::Util::distance( pSource->getPos(), actor->getPos() );
      if( distance > 20.f )
        continue;

      auto dmg = action.calcDamage( Potency );
      pActionBuilder->damage( pSource, pTarget->getAsChara(), dmg.first, dmg.second );

    if( dmg.first > 0 )
      pTarget->knockback( pSource->getPos(), 20.f );
    }
  }
};

EXPOSE_SCRIPT( ActionVulcanBurst );