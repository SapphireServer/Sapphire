#include <Actor/Player.h>
#include <ScriptObject.h>

using namespace Sapphire;

class CmnRegWilMaterialize : public Sapphire::ScriptAPI::EventScript
{
public:
  CmnRegWilMaterialize() : Sapphire::ScriptAPI::EventScript( 0xB0054 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result ) {
        Scene00001( player );
    };

    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, { 1 }, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 1, 0, { 1 }, nullptr );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};

EXPOSE_SCRIPT( CmnRegWilMaterialize );
