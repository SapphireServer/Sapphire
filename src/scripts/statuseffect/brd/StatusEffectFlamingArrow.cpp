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
    if( auto pAreaObject = actor.getAreaObject(); pAreaObject->getActionId() == FlamingArrow )
    {
      // todo: probably use selectors
      for( auto& pActor : inRange )
      {
        // make sure we're only hitting enemies
        if( !pActor->isBattleNpc() || pActor->getAsBNpc()->getEnemyType() == Common::Friendly )
          continue;

        auto pChara = pActor->getAsChara();

        const auto& pos = pAreaObject->getPos();
        if( Common::Util::distance( pos, pChara->getPos() ) < 5.f )
        {
          auto dmg = Math::CalcStats::calcActionDamage( *effect.getSrcActor(), Potency, 1.0f );
          float damageVal = dmg.first;
          Common::CalcResultType damageType = dmg.second;

          statusEffectMgr().damage( effect.getSrcActor(), pChara, static_cast< int32_t >( damageVal ) );
        }
      }
    }
  }

  void onRemove( Entity::Chara& actor ) override
  {
    actor.despawnAreaObject();
  }

  void onExpire( Entity::Chara& actor ) override
  {
    actor.despawnAreaObject();
  }
};

EXPOSE_SCRIPT( StatusEffectFlamingArrow );