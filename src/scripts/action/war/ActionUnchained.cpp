#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionUnchained : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionUnchained() : Sapphire::ScriptAPI::ActionScript( 50 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();

    if( !pPlayer )
      return;

    pPlayer->delModifier( Common::ParamModifier::DamageDealtPercent, -25 );

    action.applyStatusEffectSelf( Unchained );
    pPlayer->addStatusEffectByIdIfNotExist( Unchained, 20000, *pPlayer->getAsChara() );
  }
};

EXPOSE_SCRIPT( ActionUnchained );