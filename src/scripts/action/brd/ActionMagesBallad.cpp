#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionMagesBallad : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionMagesBallad() : Sapphire::ScriptAPI::ActionScript( MagesBallad )
  {
  }

  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::Permanent );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( pSource->getMp() == 0 )
      return;

    if( pSource->hasStatusEffect( MagesBalladAura ) )
      pSource->removeSingleStatusEffectById( MagesBalladAura );
    else
      pActionBuilder->applyStatusEffectSelf( MagesBalladAura, 0, 0, { StatusModifier{ Common::ParamModifier::DamageDealtPercent, -10 } }, Flags, false );
  }
};

EXPOSE_SCRIPT( ActionMagesBallad );