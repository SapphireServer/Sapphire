#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"
#include <Actor/Player.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>

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

    statusEffectMgr().damage( pSource, actor.getAsChara(), static_cast< int32_t >( damageVal ) );

    if( pPlayer && damageType == Common::CalcResultType::TypeCriticalDamageHp && pPlayer->getLevel() >= 48 && ( float ) rand() / ( float ) RAND_MAX <= 0.5 )
    {
      playerMgr().onSkillProc( *pPlayer, 1 );
    }
  }
};

EXPOSE_SCRIPT( StatusEffectVenomousBite );