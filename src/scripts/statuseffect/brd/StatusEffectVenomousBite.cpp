#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"
#include <action/Action.h>

#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>

#include <Network/Util/PacketUtil.h>
#include <Network/CommonActorControl.h>

#include <Math/CalcStats.h>
#include <stdlib.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectVenomousBite : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectVenomousBite() : Sapphire::ScriptAPI::StatusEffectScript( VenomousBiteStatus )
  {
  }

  static constexpr uint32_t Potency = 40;

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    if( !actor.isAlive() )
      return;

    auto pSource = effect.getSrcActor();
    auto pPlayer = pSource->getAsPlayer();
    auto dmg = Math::CalcStats::calcActionDamage( *pSource, Potency, 1.0f );
    float damageVal = dmg.first;
    Common::CalcResultType damageType = dmg.second;

    actor.takeDamage( damageVal );

    if( pPlayer && damageType == Common::CalcResultType::TypeCriticalDamageHp && pPlayer->getLevel() >= 48 && ( float ) rand() / ( float ) RAND_MAX <= 0.5 )
    {
      World::Action::Action action( pSource, Bloodletter, 0 );
      action.modifyCooldown( 0 ); // TODO: Does not seem to have the nice reset effect like in retail where the CD circle does a quick spin
    }

    Network::Util::Packet::sendActorControl( actor.getInRangePlayerIds( actor.isPlayer() ), actor.getId(), Network::ActorControl::ActorControlType::HPFloatingText, 0,
                                             Common::CalcResultType::TypeDamageHp, damageVal );
    

    if( damageVal > 0 )
    {
      actor.onActionHostile( pSource );
    }
  }
};

EXPOSE_SCRIPT( StatusEffectVenomousBite );