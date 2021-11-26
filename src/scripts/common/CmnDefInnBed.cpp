#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnDefInnBed :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefInnBed() :
    Sapphire::ScriptAPI::EventScript( 720916 )
  {
  }

  // menu
  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.getResult( 0 ) > 0 )
        Scene00001( player, result.getResult( 0 ) );
    };

    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, { 1 }, callback );
  }

  // lay down
  void Scene00001( Entity::Player& player, uint16_t param )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00002( player, result.getResult( 0 ) );
    };

    eventMgr().playScene( player, getId(), 1, 0xF32E48F8, { 1, param } , callback );
  }

  // logout
  void Scene00002( Entity::Player& player, uint16_t param )
  {
    eventMgr().playScene( player, getId(), 2, 0xF32E48F8, { 1, param }, nullptr );
  }

  // wake up
  void Scene00100( Entity::Player& player )
  {
    auto callback = []( Entity::Player& player, const Event::SceneResult& result )
    {};

    eventMgr().playScene( player, getId(), 100, 0x800, callback );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }

  void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
    Scene00100( player );
  }
};

EXPOSE_SCRIPT( CmnDefInnBed );