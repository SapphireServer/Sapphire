#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionShifu7479 :
  public ScriptAPI::ActionScript
{
public:
  ActionShifu7479() :
    ScriptAPI::ActionScript( 7479 )
  {
  }

  void onBeforeBuildEffect( Sapphire::World::Action::Action& action, uint8_t victimCounter, uint8_t validVictimCounter ) override
  {
    if( validVictimCounter > 0 && action.isCorrectCombo() )
    {
      auto pPlayer = action.getSourceChara()->getAsPlayer();
      assert( pPlayer );
      if( pPlayer->getLevel() >= 62 )
      {
        pPlayer->gaugeSamSetKenki( std::min( 100, pPlayer->gaugeSamGetKenki() + 5 ) );
      }
    }
  }
};

EXPOSE_SCRIPT( ActionShifu7479 );