#include <ScriptObject.h>
#include <Actor/Player.h>

class ComDefMobHuntBoard :
  public EventScript
{
public:
  ComDefMobHuntBoard() :
    EventScript( 0xB00CA )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 1 );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};