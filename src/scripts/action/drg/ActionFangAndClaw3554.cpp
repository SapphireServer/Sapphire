#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_SHARPER_FANG_AND_CLAW = 802;
const uint16_t STATUS_ID_ENHANCED_WHEELING_THRUST = 803;
const uint16_t STATUS_ID_RAIDEN_THRUST_READY = 1863;

class ActionFangAndClaw3554 :
  public ScriptAPI::ActionScript
{
public:
  ActionFangAndClaw3554() :
    ScriptAPI::ActionScript( 3554 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_SHARPER_FANG_AND_CLAW );
    if( effectEntry.second )
    {
      auto pPlayer = action.getSourceChara()->getAsPlayer();
      action.getSourceChara()->removeStatusEffect( effectEntry.first );
      if( pPlayer->gaugeDrgGetDragonState( Common::DrgState::BloodOfTheDragon ) )
      {
        uint16_t dragonTimer = pPlayer->gaugeDrgGetDragonTimer();
        dragonTimer = std::min( 30000, dragonTimer + 10000 );
        pPlayer->gaugeDrgSetDragonTimer( dragonTimer, true );
      }
      if( pPlayer->getLastComboActionId() == 84 )
      {
        auto pEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_ENHANCED_WHEELING_THRUST, action.getSourceChara(), action.getSourceChara(), 10000, 3000 );
        action.getEffectbuilder()->applyStatusEffect( action.getSourceChara(), action.getSourceChara(), pEffect );
      }
      if( pPlayer->getLastComboActionId() == 3556 )
      {
        auto pEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_RAIDEN_THRUST_READY, action.getSourceChara(), action.getSourceChara(), 10000, 3000 );
        action.getEffectbuilder()->applyStatusEffect( action.getSourceChara(), action.getSourceChara(), pEffect );
      }
    }
    else
    {
      action.disableGenericHandler();
      action.interrupt();
    }
  }
};

EXPOSE_SCRIPT( ActionFangAndClaw3554 );