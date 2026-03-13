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

class ActionAwareness : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionAwareness() : Sapphire::ScriptAPI::ActionScript( Awareness )
  {
  }

  static constexpr auto Duration = 20;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto duration = Duration;
    if( ( pSource->getClass() == Common::ClassJob::Gladiator || pSource->getClass() == Common::ClassJob::Paladin ) && pSource->getLevel() >= 48 )// Todo: check for parity
      duration += 5;

    auto currentPercent = pSource->getModifier( Common::ParamModifier::CriticalHitResiliencePercent );

    pActionBuilder->applyStatusEffectSelf( AwarenessStatus, ( duration * 1000 ), 0,
      {
        StatusModifier{ Common::ParamModifier::CriticalHitResiliencePercent, ( static_cast< int >(std::floor( currentPercent + 25 ) ) ) }
      },
      Flags, true );
  }
};

EXPOSE_SCRIPT( ActionAwareness );