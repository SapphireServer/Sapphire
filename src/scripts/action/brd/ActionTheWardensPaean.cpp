#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

#include <Network/Util/PacketUtil.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTheWardensPaean : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTheWardensPaean() : Sapphire::ScriptAPI::ActionScript( TheWardensPaean )
  {
  }

  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::CanStatusOff );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( !pTarget )
    {
      pTarget = pSource;
    }

    pTarget->removeSingleStatusEffectByFlag( Common::StatusEffectFlag::CanDispel );
    pActionBuilder->applyStatusEffect( pTarget, TheWardensPaeanStatus, 30000, 0, {}, Flags, false, true );

    Network::Util::Packet::sendHudParam( *pTarget );
  }
};

EXPOSE_SCRIPT( ActionTheWardensPaean );