#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionYukikaze7480 :
  public ScriptAPI::ActionScript
{
public:
  ActionYukikaze7480() :
    ScriptAPI::ActionScript( 7480 )
  {
  }

  void onBeforeBuildEffect( Sapphire::World::Action::Action& action, uint8_t victimCounter, uint8_t validVictimCounter ) override
  {
    if( validVictimCounter > 0 && action.isCorrectCombo() )
    {
      auto pPlayer = action.getSourceChara()->getAsPlayer();
      assert( pPlayer );
      int kenki = pPlayer->gaugeSamGetKenki();
      auto level = pPlayer->getLevel();
      if( level >= 52 )
      {
        kenki += 10;
      }
      if( level >= 62 )
      {
        kenki += 5;
      }
      pPlayer->gaugeSamSetKenki( std::min( 100, kenki ) );
      if( level >= 50 )
      {
        pPlayer->gaugeSamSetSen( Common::SamSen::Setsu, true );
      }
    }
  }
};

EXPOSE_SCRIPT( ActionYukikaze7480 );