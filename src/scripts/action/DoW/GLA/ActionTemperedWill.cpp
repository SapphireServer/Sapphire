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

class ActionTemperedWill : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTemperedWill() : Sapphire::ScriptAPI::ActionScript( TemperedWill )
  {
  }

  static constexpr auto Duration = 10;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( pSource->hasStatusEffect( Blind ) )
      pSource->removeSingleStatusEffectById( Blind );

    if( pSource->hasStatusEffect( Heavy ) )
      pSource->removeSingleStatusEffectById( Heavy );

    pActionBuilder->applyStatusEffectSelf( TemperedWillStatus, ( Duration * 1000 ), 0, {}, Flags, true ); // Todo figure out how to add knockback/draw-in resistance
  }
};

EXPOSE_SCRIPT( ActionTemperedWill );