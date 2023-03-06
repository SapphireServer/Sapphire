#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

const uint16_t STATUS_ID_ENHANCED_ENPI = 1236;

class ActionEnpi7486 :
  public ScriptAPI::ActionScript
{
public:
  ActionEnpi7486() :
    ScriptAPI::ActionScript( 7486 )
  {
  }

  void onBeforeBuildEffect( Sapphire::World::Action::Action& action, uint8_t victimCounter, uint8_t validVictimCounter ) override
  {
    if( validVictimCounter > 0 )
    {
      auto pPlayer = action.getSourceChara()->getAsPlayer();
      assert( pPlayer );
      int kenki = pPlayer->gaugeSamGetKenki();
      auto level = pPlayer->getLevel();
      if( level >= 52 )
      {
        kenki += 5;
      }
      if( level >= 62 )
      {
        kenki += 5;
      }
      pPlayer->gaugeSamSetKenki( std::min( 100, kenki ) );
    }
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_ENHANCED_ENPI );
    if( effectEntry.second )
    {
      action.getSourceChara()->removeStatusEffect( effectEntry.first );
    }
  }

  void onBeforePreCheck( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_ENHANCED_ENPI );
    if( effectEntry.second )
    {
      action.getActionEntry().damagePotency = 320;
    }
  }
};

EXPOSE_SCRIPT( ActionEnpi7486 );