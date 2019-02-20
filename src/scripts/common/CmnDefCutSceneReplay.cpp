#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnDefCutSceneReplay :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefCutSceneReplay() :
    Sapphire::ScriptAPI::EventScript( 721028 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 != 0 )
      {
        Scene00001( player, result.param2 );
      }
    };

    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 1, callback );
  }

  void Scene00001( Entity::Player& player, uint16_t returnScene )
  {
    auto callback = []( Entity::Player& player, const Event::SceneResult& result )
    {
      // todo: this is fucked
    };

    player.playScene( getId(), 1, 0xFB2EC8F8, 0, 1, returnScene, callback );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};


EXPOSE_SCRIPT( CmnDefCutSceneReplay );