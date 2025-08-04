#include <Action/Action.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

#include <Manager/TerritoryMgr.h>

#include <Common.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionHellfire : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionHellfire() : Sapphire::ScriptAPI::ActionScript( 458 )
  {
  }

  static constexpr auto Potency = 300;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();

    auto pActionBuilder = action.getActionResultBuilder();

    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pTeri = teriMgr.getTerritoryByGuId( pSource->getTerritoryId() );
    auto pInstance = pTeri->getAsInstanceContent();

    if( !pActionBuilder )
      return;

    for( auto& actor : pSource->getInRangeActors() )
    {
      if( !actor->isPlayer() )
        continue;

      auto pTarget = actor->getAsChara();

      // hellfire fail dmg is higher
      auto dmg = 1200;
      // hellfire success
      if( pInstance->getDirectorVar( 0 ) == 1 )
        dmg = 200;

      pActionBuilder->damage( pSource, pTarget->getAsChara(), dmg );
    }
  }
};

EXPOSE_SCRIPT( ActionHellfire );