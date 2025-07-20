#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include "StatusEffect/StatusEffect.h"
#include <Actor/Chara.h>
#include <Network/Util/PacketUtil.h>
#include <Network/CommonActorControl.h>
#include <Math/CalcStats.h>
#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectVenomousBite : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectVenomousBite() : Sapphire::ScriptAPI::StatusEffectScript( VenomousBite )
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

    if( pPlayer && damageType == Common::CalcResultType::TypeCriticalDamageHp )
    {

    }
    auto& exdData = Common::Service< Data::ExdData >::ref();
    auto actionData = exdData.getRow< Excel::Action >( Bloodletter );
    pPlayer->setRecastGroup( actionData->data().RecastGroup, 0 );// TODO: Does not seem to have the nice reset effect like in retail where the CD circle does a quick spin

    Network::Util::Packet::sendActorControl( actor.getInRangePlayerIds( actor.isPlayer() ), actor.getId(), Network::ActorControl::ActorControlType::HPFloatingText, 0,
                                             Common::CalcResultType::TypeDamageHp, damageVal );
    //Network::Util::Packet::sendRecastGroups( *( pSource->getAsPlayer() ) );

    if( damageVal > 0 )
    {
      actor.onActionHostile( pSource );
    }
  }
};

EXPOSE_SCRIPT( StatusEffectVenomousBite );