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

class ActionFightOrFlight : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionFightOrFlight() : Sapphire::ScriptAPI::ActionScript( FightOrFlight )
  {
  }

  static constexpr auto Duration = 20;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto duration = Duration;
    if( ( pSource->getClass() == Common::ClassJob::Gladiator || pSource->getClass() == Common::ClassJob::Paladin ) && pSource->getLevel() >= 28 )// Todo: check for parity
      duration += 10;

    auto currentPercent = pSource->getModifier( Common::ParamModifier::DamageDealtPercent );

    pActionBuilder->applyStatusEffectSelf( FightOrFlightStatus, ( duration * 1000 ), 0,
      {
        StatusModifier{ Common::ParamModifier::DamageDealtPercent, ( static_cast< int >(std::floor( currentPercent + 30 ) ) ) }
      },
      Flags, true );
  }
};

EXPOSE_SCRIPT( ActionFightOrFlight );