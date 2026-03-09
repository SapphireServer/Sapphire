#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>
#include <Actor/BNpc.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionClericStance : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionClericStance() : Sapphire::ScriptAPI::ActionScript( ClericStance )
  {
  }

  static constexpr auto Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( pSource->hasStatusEffect( ClericStanceStatus ) )
    {

      pSource->removeSingleStatusEffectById( ClericStanceStatus );
    }
    else
    {
      // Todo: do i need to swap the stats manually or is that handled on client?
      auto currentPercent0 = pSource->getModifier( Common::ParamModifier::AttackMagicPotency );
      auto currentPercent1 = pSource->getModifier( Common::ParamModifier::HealingMagicPotency );

      pActionBuilder->applyStatusEffectSelf( ClericStanceStatus, 0, 0,
        {
          StatusModifier{ Common::ParamModifier::AttackMagicPotency, 500 },  // Todo: still dont know if these are right
          StatusModifier{ Common::ParamModifier::HealingMagicPotency, 100 } //
        },
        Flags, false );
    }
  }
};

EXPOSE_SCRIPT( ActionClericStance );