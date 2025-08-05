#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionStraightShot : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionStraightShot() : Sapphire::ScriptAPI::ActionScript( StraightShot )
  {
  }

  static constexpr auto Potency = 140;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::CanStatusOff );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( auto status = pSource->getStatusEffectById( StraightShotReady ); status )
      status->setModifier( Common::ParamModifier::CriticalHit, 100 );
    

    auto dmg = action.calcDamage( Potency );
    pActionBuilder->damage( pSource, pTarget, dmg.first, 1, dmg.second );

    if( pTarget->getObjKind() != pSource->getObjKind() )
    {
      pSource->removeStatusEffectByFlag( Common::StatusEffectFlag::RemoveOnSuccessfulHit );
    }

    pSource->removeSingleStatusEffectById( StraightShotReady );
    pActionBuilder->applyStatusEffectSelf( StraightShotStatus, 20000, 0, { StatusModifier{ Common::ParamModifier::CriticalHitPercent, 10 } }, Flags, true );
  }
};

EXPOSE_SCRIPT( ActionStraightShot );