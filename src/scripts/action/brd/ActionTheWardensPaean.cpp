#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTheWardensPaean : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTheWardensPaean() : Sapphire::ScriptAPI::ActionScript( TheWardensPaean )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    int slotToRemove = -1;

    /*for( auto entry : pTarget->getStatusEffectMap() )
    {
      if( entry.second->getFlag() & static_cast< uint32_t >( Common::StatusEffectFlag::CanDispel ) )
      {
        slotToRemove = entry.first;
        break;
      }
    }

    if (slotToRemove > -1)
    {
      pTarget->removeStatusEffect( slotToRemove );
    }*/

    pActionBuilder->applyStatusEffect( pTarget, TheWardensPaeanStatus, 30000, 0, {}, 1025, false, true );
  }
};

EXPOSE_SCRIPT( ActionTheWardensPaean );