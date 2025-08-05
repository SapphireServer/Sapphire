#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>

#include "Manager/PlayerMgr.h"

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
      playerMgr().onSkillProc( *pPlayer, 1 );
    }

    Network::Util::Packet::sendActorControl( actor.getInRangePlayerIds( actor.isPlayer() ), actor.getId(), Network::ActorControl::ActorControlType::HPFloatingText, 0,
      Common::CalcResultType::TypeDamageHp, damageVal );
    Network::Util::Packet::sendHudParam( actor );
  }
};

EXPOSE_SCRIPT( StatusEffectVenomousBite );