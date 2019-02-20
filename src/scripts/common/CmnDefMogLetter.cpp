#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnDefMogLetter :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefMogLetter() :
    Sapphire::ScriptAPI::EventScript( 720898 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, 0,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }
};

EXPOSE_SCRIPT( CmnDefMogLetter );