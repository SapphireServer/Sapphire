#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_DIVE_READY = 1243;

class ActionMirageDive7399 :
  public ScriptAPI::ActionScript
{
public:
  ActionMirageDive7399() :
    ScriptAPI::ActionScript( 7399 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_DIVE_READY );
    if( effectEntry.second )
    {
      auto pPlayer = action.getSourceChara()->getAsPlayer();
      action.getSourceChara()->removeStatusEffect( effectEntry.first );
      if( pPlayer->gaugeDrgGetDragonState( Common::DrgState::BloodOfTheDragon ) || pPlayer->gaugeDrgGetDragonState( Common::DrgState::LifeOfTheDragon ) )
      {
        uint8_t eyes = pPlayer->gaugeDrgGetEyes();
        eyes = std::min( 2, eyes + 1 );
        pPlayer->gaugeDrgSetEyes( eyes );
      }
    }
    else
    {
      action.disableGenericHandler();
      action.interrupt();
    }
  }
};

EXPOSE_SCRIPT( ActionMirageDive7399 );