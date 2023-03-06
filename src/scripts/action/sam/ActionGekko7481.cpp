#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionGekko7481 :
  public ScriptAPI::ActionScript
{
public:
  ActionGekko7481() :
    ScriptAPI::ActionScript( 7481 )
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
      if( /*positional &&*/ level >= 52 )
      {
        kenki += 5;
      }
      if( level >= 62 )
      {
        kenki += 5;
      }
      pPlayer->gaugeSamSetKenki( std::min( 100, kenki ) );
      if( level >= 30 )
      {
        pPlayer->gaugeSamSetSen( Common::SamSen::Getsu, true );
      }
    }
  }
};

EXPOSE_SCRIPT( ActionGekko7481 );