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

class ActionHide : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionHide() : Sapphire::ScriptAPI::ActionScript( Hide )
  {
  }

  static constexpr auto Flags = static_cast< uint32_t >( Common::StatusEffectFlag::Permanent ) |
                                static_cast< uint32_t >( Common::StatusEffectFlag::Invisibilty ) |
                                static_cast< uint32_t >( Common::StatusEffectFlag::RemoveOnActionUse );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    pActionBuilder->applyStatusEffectSelf( HiddenStatus, 0, 0, {}, Flags, false );
  }
};

EXPOSE_SCRIPT( ActionHide );