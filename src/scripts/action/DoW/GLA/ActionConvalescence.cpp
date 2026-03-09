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

class ActionConvalescence : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionConvalescence() : Sapphire::ScriptAPI::ActionScript( Convalescence )
  {
  }

  static constexpr auto Duration = 20;
  static constexpr auto Percentage = 20;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto percentage = Percentage;
    if( ( pSource->getClass() == Common::ClassJob::Gladiator || pSource->getClass() == Common::ClassJob::Paladin ) && pSource->getLevel() >= 32 )// Todo: check for parity
      percentage += 10;

    auto currentPercent = pSource->getModifier( Common::ParamModifier::HealingMagicRecoveryPercent ); // Todo: correct paramMod??

    pActionBuilder->applyStatusEffectSelf( ConvalescenceStatus, ( Duration * 1000 ), 0,
      {
        StatusModifier{ Common::ParamModifier::HealingMagicRecoveryPercent, ( static_cast< int >( std::floor( currentPercent + 20 ) ) ) }
      },
      Flags, true );
  }
};

EXPOSE_SCRIPT( ActionConvalescence );