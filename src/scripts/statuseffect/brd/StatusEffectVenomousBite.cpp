#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include "StatusEffect/StatusEffect.h"
#include <Actor/Chara.h>
#include <Network/Util/PacketUtil.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectVenomousBite : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectVenomousBite() : Sapphire::ScriptAPI::StatusEffectScript( 124 )
  {
  }

  static constexpr uint32_t Potency = 40;

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    if( !actor.isAlive() )
      return;

    auto pSource = effect.getSrcActor();
    auto dmg = Math::CalcStats::calcActionDamage( *pSource, Potency, 1.0f );
    actor.takeDamage( dmg.first );

    if ( dmg.second == Sapphire::Common::CalcResultType::TypeCriticalDamageHp )
    {

    }

    Network::Util::Packet::sendHudParam( actor );

    if( dmg.first > 0 )
    {
      actor.onActionHostile( pSource );
    }
  }
};

EXPOSE_SCRIPT( StatusEffectVenomousBite );