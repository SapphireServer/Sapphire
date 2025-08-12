#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionFlamingArrow : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionFlamingArrow() : Sapphire::ScriptAPI::ActionScript( FlamingArrow )
  {
  }

  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::GroundTarget );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    pSource->spawnAreaObject( FlamingArrow, 196, action.getActionData()->data().EffectRange, action.getPos() );
    pActionBuilder->applyStatusEffectSelf( FlamingArrowStatus, 30000, 0, { }, Flags, false );

  }
};

EXPOSE_SCRIPT( ActionFlamingArrow );