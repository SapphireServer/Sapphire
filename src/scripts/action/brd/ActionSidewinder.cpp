#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionSidewinder : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSidewinder() : Sapphire::ScriptAPI::ActionScript( Sidewinder )
  {
  }

  static constexpr auto Potency = 100;
  static constexpr auto PotencyOneDot = 175;
  static constexpr auto PotencyBothDots = 260;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto sourceId = pSource->getId();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    auto potency = Potency;

    for( auto entry : pTarget->getStatusEffectMap() )
    {
      if( entry.second->getSrcActorId() == sourceId && ( entry.second->getId() == VenomousBiteStatus || entry.second->getId() == WindbiteStatus ) )
      {
        // We assume the player can't apply the same dot twice
        if( potency == Potency )
        {
          // First dot found
          potency = PotencyOneDot;
        }
        else
        {
          // Second dot found
          potency = PotencyBothDots;
          break;
        }
      }
    }

    auto dmg = action.calcDamage( potency );
    int32_t aggro = Sapphire::Math::CalcStats::calcDamageAggro( *pSource, dmg.first );
    pActionBuilder->damage( pSource, pTarget, dmg.first, aggro, dmg.second );
  }
};

EXPOSE_SCRIPT( ActionSidewinder );