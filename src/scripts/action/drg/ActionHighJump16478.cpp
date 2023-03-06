#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_DIVE_READY = 1243;

class ActionHighJump16478 :
  public ScriptAPI::ActionScript
{
public:
  ActionHighJump16478() :
    ScriptAPI::ActionScript( 16478 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {

    auto pPlayer = action.getSourceChara()->getAsPlayer();
    if( pPlayer->gaugeDrgGetDragonState( Common::DrgState::BloodOfTheDragon ) || pPlayer->gaugeDrgGetDragonState( Common::DrgState::LifeOfTheDragon ) )
    {
      auto pEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_DIVE_READY, action.getSourceChara(), action.getSourceChara(), 15000, 3000 );
      action.getEffectbuilder()->applyStatusEffect( action.getSourceChara(), action.getSourceChara(), pEffect );
    }
  }
};

EXPOSE_SCRIPT( ActionHighJump16478 );