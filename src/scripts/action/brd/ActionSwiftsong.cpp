#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionSwiftsong : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSwiftsong() : Sapphire::ScriptAPI::ActionScript( Swiftsong )
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

    if( pSource->hasStatusEffect( SwiftsongAura ) )
      pSource->removeSingleStatusEffectById( SwiftsongAura );
    else
    {
      pActionBuilder->applyStatusEffectSelf( SwiftsongAura, 0, 20, {}, Flags, false );
    }
  }
};

EXPOSE_SCRIPT( ActionSwiftsong );