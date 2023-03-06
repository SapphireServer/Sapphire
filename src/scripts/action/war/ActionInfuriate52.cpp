#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_NASCENT_CHAOS = 1897;

class ActionInfuriate52 :
  public ScriptAPI::ActionScript
{
public:
  ActionInfuriate52() :
    ScriptAPI::ActionScript( 52 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    assert( pPlayer );
    uint8_t ib = pPlayer->gaugeWarGetIb();
    ib = std::min( 100, ib + 50 );
    pPlayer->gaugeWarSetIb( ib );
    if( pPlayer->getLevel() >= 72 )
    {
      auto pEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_NASCENT_CHAOS, action.getSourceChara(), action.getSourceChara(), 30000, 3000 );
      action.getEffectbuilder()->applyStatusEffect( action.getSourceChara(), action.getSourceChara(), pEffect, 0 );
    }
  }
};

EXPOSE_SCRIPT( ActionInfuriate52 );