#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTheWanderersMinuet : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTheWanderersMinuet() : Sapphire::ScriptAPI::ActionScript( TheWanderersMinuet )
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

    if( pSource->hasStatusEffect( TheWanderersMinuetStatus ) )
      pSource->removeSingleStatusEffectById( TheWanderersMinuetStatus );
    else
    {
      int32_t aggro = Sapphire::Math::CalcStats::calcStatusAggro( *pSource );
      pActionBuilder->applyStatusEffectSelf( TheWanderersMinuetStatus, aggro, 0, 0, { StatusModifier{ Common::ParamModifier::DamageDealtPercent, 30 } }, Flags, false );
    }
  }
};

EXPOSE_SCRIPT( ActionTheWanderersMinuet );