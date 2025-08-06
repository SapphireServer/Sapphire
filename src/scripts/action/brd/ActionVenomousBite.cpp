#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionVenomousBite : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionVenomousBite() : Sapphire::ScriptAPI::ActionScript( VenomousBite )
  {
  }

  static constexpr auto Potency = 100;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::DebuffCategory ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::CanDispel ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::ReplaceSameCaster );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    auto dmg = action.calcDamage( Potency );
    int32_t aggro = Sapphire::Math::CalcStats::calcDamageAggro( *pSource, dmg.first );
    pActionBuilder->damage( pSource, pTarget, dmg.first, aggro, dmg.second );

    if( pTarget->getObjKind() != pSource->getObjKind() )
    {
      pSource->removeStatusEffectByFlag( Common::StatusEffectFlag::RemoveOnSuccessfulHit );
    }

    if( pPlayer && pPlayer->getLevel() >= 24 )
      pActionBuilder->applyStatusEffect( pTarget, VenomousBiteStatus, 0, 18000, 0, {}, Flags, false, true );
    else
      pActionBuilder->applyStatusEffect( pTarget, VenomousBiteStatus, 0, 9000, 0, {}, Flags, false, true );
    
  }
};

EXPOSE_SCRIPT( ActionVenomousBite );