#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_BRUTAL_SHELL = 1898;

class ActionBrutalShell16139 :
  public ScriptAPI::ActionScript
{
public:
  ActionBrutalShell16139() :
    ScriptAPI::ActionScript( 16139 )
  {
  }

  void onBeforeBuildEffect( Sapphire::World::Action::Action& action, uint8_t victimCounter, uint8_t validVictimCounter ) override
  {
    if( validVictimCounter > 0 && action.isCorrectCombo() )
    {
      auto chara = action.getSourceChara();
      auto heal = action.calcHealing( 150 );
      heal.first = Math::CalcStats::applyHealingReceiveMultiplier( *chara, heal.first );
      action.getEffectbuilder()->heal( chara, chara, heal.first, heal.second );

      if( chara->getLevel() >= 52 && heal.first > 0 )
      {
        World::Action::StatusEffectEntry effectEntry;
        effectEntry.effectType = static_cast< uint32_t >( Common::StatusEffectType::Shield );
        effectEntry.effectValue1 = static_cast< int32_t >( heal.first );
        auto pNewEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_BRUTAL_SHELL, action.getSourceChara(), chara, 10000, 3000 );
        pNewEffect->replaceEffectEntry( effectEntry );
        action.getEffectbuilder()->applyStatusEffect( chara, chara, pNewEffect );
      }
    }
  }
};

EXPOSE_SCRIPT( ActionBrutalShell16139 );