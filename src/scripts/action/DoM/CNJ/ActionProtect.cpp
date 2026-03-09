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

class ActionProtect : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionProtect() : Sapphire::ScriptAPI::ActionScript( Protect )
  {
  }

  static constexpr auto Radius = 15;
  static constexpr auto Duration = 1800;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pCenter = action.getHitChara(); // Todo: this is always empty on players, why?
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( !pCenter )
      pCenter = pSource;

    for( auto& pActor : pCenter->getInRangeActors( true ) )
    {
      auto pTarget = pActor->getAsChara();

      if( !pTarget->isFriendly( *pSource ) )
        continue;

      if( Common::Util::distance( pSource->getPos(), pTarget->getPos() ) > Radius )
        continue;

      pActionBuilder->applyStatusEffect( pTarget, ProtectCnjStatus, ( Duration * 1000 ), 0,
        {
          StatusModifier{ Common::ParamModifier::DefensePercent, 10 }
        },
        Flags, false, true );
    }
  }
};

EXPOSE_SCRIPT( ActionProtect );