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

class StatusEffectMagesBalladAura : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectMagesBalladAura() : Sapphire::ScriptAPI::StatusEffectScript( MagesBalladStatus )
  {
  }

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    auto statusMap = effect.getModifiers();
    auto potency = statusMap[ Common::ParamModifier::Refresh ];

    auto pSource = effect.getSrcActor();
    auto mpGained = Math::CalcStats::calcMpRefresh( potency, pSource->getLevel() );

    actor.setMp( actor.getMp() + mpGained );
  }
};

EXPOSE_SCRIPT( StatusEffectMagesBalladAura );