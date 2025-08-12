#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectFlamingArrow : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectFlamingArrow() : Sapphire::ScriptAPI::StatusEffectScript( FlamingArrowStatus )
  {
  }

  static constexpr auto Potency = 40;

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    auto inRange = actor.getInRangeActors();
    for( auto& pActor : inRange )
    {
      if( !pActor->isChara() )
        continue;
      auto pChara = pActor->getAsChara();

      const auto& pos = actor.getAreaObjectPos();
      if( Common::Util::distance( pos, pChara->getPos() ) < 5.f )
      {
        auto dmg = Math::CalcStats::calcActionDamage( *pChara, Potency, 1.0f );
        float damageVal = dmg.first;
        Common::CalcResultType damageType = dmg.second;

        statusEffectMgr().damage( actor.getAsChara(), pChara, static_cast< int32_t >( damageVal ) );
      }
    }
  }

  void onRemove( Entity::Chara& actor ) override
  {
    actor.despawnAreaObject( FlamingArrow );
  }

  void onExpire( Entity::Chara& actor ) override
  {
    actor.despawnAreaObject( FlamingArrow );
  }
};

EXPOSE_SCRIPT( StatusEffectFlamingArrow );