#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionHagakure7495 :
  public ScriptAPI::ActionScript
{
public:
  ActionHagakure7495() :
    ScriptAPI::ActionScript( 7495 )
  {
  }

  void onStart( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    assert( pPlayer );
    int kenki = pPlayer->gaugeSamGetKenki();
    if( pPlayer->gaugeSamGetSen( Common::SamSen::Getsu ) )
      kenki += 10;
    if( pPlayer->gaugeSamGetSen( Common::SamSen::Setsu ) )
      kenki += 10;
    if( pPlayer->gaugeSamGetSen( Common::SamSen::Ka ) )
      kenki += 10;
    pPlayer->gaugeSamSetKenki( std::min( 100, kenki ) );
  }
};

EXPOSE_SCRIPT( ActionHagakure7495 );