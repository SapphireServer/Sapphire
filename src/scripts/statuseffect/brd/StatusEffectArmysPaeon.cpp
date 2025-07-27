#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectArmysPaeon : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectArmysPaeon() : Sapphire::ScriptAPI::StatusEffectScript( ArmysPaeonStatus )
  {
  }

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    auto statusMap = effect.getModifiers();
    auto potency = statusMap[ Common::ParamModifier::TpRefresh ];

    auto pSource = effect.getSrcActor();

    actor.setTp( actor.getTp() + potency );
  }
};

EXPOSE_SCRIPT( StatusEffectArmysPaeon );