#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <StatusEffect/StatusEffect.h>
#include <Actor/Player.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectThunder : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectThunder() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::ThunderStatus )
  {
  }  
  static constexpr uint32_t Potency = 40;
  void onApply( Sapphire::Entity::Chara& actor ) override
  {
  }

  void onTick( Sapphire::Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    if( !actor.isAlive() )
      return;

    auto pSource = effect.getSrcActor();
    auto pPlayer = pSource->getAsPlayer();
    auto weaponDamage = pSource->getMagicalWeaponDamage();
    auto dmg = Math::CalcStats::calcActionDamage( *pSource, Potency, Common::BaseParam::Intelligence, weaponDamage );
    float damageVal = dmg.first;

    statusEffectMgr().damage( pSource, actor.getAsChara(), static_cast< int32_t >( damageVal ) );
  }
};

EXPOSE_SCRIPT( StatusEffectThunder );