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

class ActionKissOfTheViper : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionKissOfTheViper() : Sapphire::ScriptAPI::ActionScript( KissOfTheViper )
  {
  }

  static constexpr auto Percentage = 10;
  static constexpr auto Flags = static_cast< int32_t >( Common::StatusEffectFlag::BuffCategory ) |
                                static_cast< int32_t >( Common::StatusEffectFlag::Permanent ) |
                                static_cast< int32_t >( Common::StatusEffectFlag::CanStatusOff );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    auto percentage = Percentage;
    if( ( pSource->getClass() == Common::ClassJob::Rogue || pSource->getClass() == Common::ClassJob::Ninja ) && pSource->getLevel() >= 40 )// Todo: check for parity
      percentage += 5;

    if( pSource->hasStatusEffect( KissOfTheViperStatus ) )
    {
      pSource->removeSingleStatusEffectById( KissOfTheViperStatus );// Todo: make weapon poisons a flag and disable when action is used that has the flag all others before activating new
      return;
    }
    else if( pSource->hasStatusEffect( KissOfTheWaspStatus ) )
    {
      pSource->removeSingleStatusEffectById( KissOfTheWaspStatus );
    }
    pActionBuilder->applyStatusEffectSelf( KissOfTheViperStatus, 0, 0,
      {
        StatusModifier{ Common::ParamModifier::PhysicalDamagePercent, percentage }
      },
      Flags, false );
  }
};

EXPOSE_SCRIPT( ActionKissOfTheViper );