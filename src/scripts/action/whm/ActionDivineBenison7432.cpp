#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_DEVINE_BENISON = 1218;

class ActionDivineBenison7432 :
  public ScriptAPI::ActionScript
{
public:
  ActionDivineBenison7432() :
    ScriptAPI::ActionScript( 7432 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pTarget = action.getHitChara();
    if( pTarget )
    {
      float shieldValue = action.calcHealing( 500 ).first; // 500 ptc worth of shield
      shieldValue = Math::CalcStats::applyHealingReceiveMultiplier( *pTarget, shieldValue );

      auto oldEffect = pTarget->getStatusEffectById( STATUS_ID_DEVINE_BENISON );
      if( !oldEffect.second || oldEffect.second->getEffectEntry().getRemainingShield() <= shieldValue )
      {
        World::Action::StatusEffectEntry effectEntry;
        effectEntry.init( Common::StatusEffectType::Shield, shieldValue, 0, 0, 0 );
        auto pNewEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_DEVINE_BENISON, action.getSourceChara(), pTarget, 15000, 3000 );
        pNewEffect->replaceEffectEntry( effectEntry );
        action.getEffectbuilder()->applyStatusEffect( pTarget, action.getSourceChara(), pNewEffect );
      }
      else
        action.getEffectbuilder()->statusNoEffect( pTarget, STATUS_ID_DEVINE_BENISON );
    }
  }
};

EXPOSE_SCRIPT( ActionDivineBenison7432 );