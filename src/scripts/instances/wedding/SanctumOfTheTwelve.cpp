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
    player.setPosAndSendActorMove( 0, 250, -50, player.getRot() );
  }

  void onLeaveTerritory( PublicContent& instance, Entity::Player& player ) override
  {
  }

  void onEnterTerritory( PublicContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
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