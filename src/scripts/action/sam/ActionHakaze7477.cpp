#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionHakaze7477 :
  public ScriptAPI::ActionScript
{
public:
  ActionHakaze7477() :
    ScriptAPI::ActionScript( 7477 )
  {
  }

  void onBeforeBuildEffect( Sapphire::World::Action::Action& action, uint8_t victimCounter, uint8_t validVictimCounter ) override
  {
    if( validVictimCounter > 0 )
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

EXPOSE_SCRIPT( ActionHakaze7477 );