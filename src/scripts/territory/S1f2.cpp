#include <ScriptObject.h>
#include <Actor/Player.h>

#include "Script/NativeScriptApi.h"

using namespace Sapphire;

class S1f2 : public Sapphire::ScriptAPI::ZoneScript
{
public:
  S1f2() : Sapphire::ScriptAPI::ZoneScript( 135 )
  {
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {

  }

  void Scene00000( Entity::Player& player, uint32_t eventId )
  {
    eventMgr().playScene( player, eventId, 0, NONE, bindSceneReturn( &S1f2::Scene00000Return ) );
  }


  void onZoneInit() override
  {

  }

  void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    Scene00000( player, eventId );
  }

};

EXPOSE_SCRIPT( S1f2 );