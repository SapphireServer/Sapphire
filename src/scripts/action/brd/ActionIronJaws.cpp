#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionIronJaws : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionIronJaws() : Sapphire::ScriptAPI::ActionScript( IronJaws )
  {
  }

  static constexpr auto Potency = 100;
  static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::DebuffCategory ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::CanDispel ) |
                                    static_cast< uint32_t >( Common::StatusEffectFlag::ReplaceSameCaster );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto sourceId = pSource->getId();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    bool applyVenomousBite = false;
    bool applyWindbite = false;
    for( auto entry : pTarget->getStatusEffectMap() )
    {
      applyVenomousBite = applyVenomousBite || ( entry.second->getSrcActorId() == sourceId && entry.second->getId() == VenomousBiteStatus );
      applyWindbite = applyWindbite || ( entry.second->getSrcActorId() == sourceId && entry.second->getId() == WindbiteStatus );
      if( applyVenomousBite && applyWindbite )
        break;
    }

    auto dmg = action.calcDamage( Potency );
    pActionBuilder->damage( pSource, pTarget, dmg.first, 1, dmg.second );

    if( pTarget->getObjKind() != pSource->getObjKind() )
    {
      pSource->removeStatusEffectByFlag( Common::StatusEffectFlag::RemoveOnSuccessfulHit );
    }

    if( applyVenomousBite )
    {
      pActionBuilder->applyStatusEffect( pTarget, VenomousBiteStatus, 18000, 0, {}, Flags, false, true );
    }
    if( applyWindbite )
    {
      pActionBuilder->applyStatusEffect( pTarget, WindbiteStatus, 18000, 0, {}, Flags, false, true );
    }
  }
};

EXPOSE_SCRIPT( ActionIronJaws );