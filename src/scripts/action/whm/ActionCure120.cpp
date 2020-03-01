#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_FREECURE = 155;

class ActionCure120 :
  public ScriptAPI::ActionScript
{
public:
  ActionCure120() :
    ScriptAPI::ActionScript( 120 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    if( action.getSourceChara()->getLevel() >= 30 && Math::CalcStats::getRandomNumber0To99() < 15 )
    {
      auto pEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_FREECURE, action.getSourceChara(), action.getSourceChara(), 15000, 3000 );
      action.getEffectbuilder()->applyStatusEffect( action.getSourceChara(), action.getSourceChara(), pEffect );
    }
  }
};

EXPOSE_SCRIPT( ActionCure120 );