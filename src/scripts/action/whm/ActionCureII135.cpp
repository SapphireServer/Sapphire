#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_FREECURE = 155;

class ActionCureII135 :
  public ScriptAPI::ActionScript
{
public:
  ActionCureII135() :
    ScriptAPI::ActionScript( 135 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_FREECURE );
    if( effectEntry.second )
    {
      action.getSourceChara()->removeStatusEffect( effectEntry.first );
    }
  }

  void onBeforePreCheck( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_FREECURE );
    if( effectEntry.second )
    {
      action.setPrimaryCost( Common::ActionPrimaryCostType::None, 0 );
    }
  }
};

EXPOSE_SCRIPT( ActionCureII135 );