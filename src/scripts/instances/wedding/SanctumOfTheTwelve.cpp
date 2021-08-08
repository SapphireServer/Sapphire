#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

#include "Actor/Player.h"
#include "Territory/PublicContent.h"

using namespace Sapphire;

class SanctumOfTheTwelve : public Sapphire::ScriptAPI::PublicContentScript
{
public:
  SanctumOfTheTwelve() : Sapphire::ScriptAPI::PublicContentScript( 1 ) { }

  void onInit( PublicContent& instance ) override
  {

  }

  void onUpdate( PublicContent& instance, uint64_t tickCount ) override
  {

  }

  void onPlayerZoneIn( PublicContent& instance, Entity::Player& player ) override
  {
    if( instance.getCustomVar( 1 ) == 0 || instance.getCustomVar( 1 ) == player.getId() )
    {
      if( player.hasQuest( 67114 ) )
      {
        instance.setCustomVar( 1, player.getId() );
        instance.setDirectorUI8AL( player.getQuestUI8AH( 67114 ) );
        instance.setDirectorUI8BL( player.getQuestUI8AL( 67114 ) );
        instance.setDirectorUI8CL( player.getGuardianDeity() );
        instance.setDirectorUI8DL( player.getGuardianDeity() );
        instance.setDirectorUI8EL( player.getQuestUI8FH( 67114 ) );
        instance.setDirectorUI8FL( player.getQuestUI8FL( 67114 ) );
        instance.setDirectorUI8GL( 1 );
        instance.setDirectorUI8HL( 1 );
        instance.setDirectorUI8IL( 1 );
        instance.setDirectorUI8JL( 1 );
      }
    }
  }

  void onLeaveTerritory( PublicContent& instance, Entity::Player& player ) override
  {
  }

  void onEnterTerritory( PublicContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
    player.setPosAndSendActorMove( 0, 250, -50, player.getRot() );
    player.directorPlayScene( instance.getDirectorId(), 1, NONE, 0, 0, 0 );
  }
 
  void onDebug( Entity::Player& player, uint32_t param ) override
  {
    auto instance = player.getCurrentPublicContent();
    if( !instance || instance->getDirectorId() != getId() )
      return;
    player.sendUrgent( "SanctumOfTheTwelve: debug {}", param );

    player.eventStart( player.getId(), instance->getDirectorId(), Event::EventHandler::EnterTerritory, 1, player.getZoneId() );
    player.directorPlayScene( instance->getDirectorId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, 0, 1, param );
  }
 
};

EXPOSE_SCRIPT( SanctumOfTheTwelve );