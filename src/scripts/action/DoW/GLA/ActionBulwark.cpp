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

class ActionBulwark : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionBulwark() : Sapphire::ScriptAPI::ActionScript( Bulwark )
  {
  }

  static constexpr auto Duration = 15;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    pActionBuilder->applyStatusEffectSelf( BulwarkStatus, ( Duration * 1000 ), 0,
      {
        StatusModifier{ Common::ParamModifier::BlockRate, 60 } // Todo: probly not right
      },
      Flags, true );
  }
};

EXPOSE_SCRIPT( ActionBulwark );