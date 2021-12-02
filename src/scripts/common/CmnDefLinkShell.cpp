#include <ScriptObject.h>
#include <Actor/Player.h>

#define ACTION_CREATE 2
#define ACTION_RENAME 3
#define ACTION_REMOVE 4

using namespace Sapphire;

class CmnDefLinkShell :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefLinkShell() :
    Sapphire::ScriptAPI::EventScript( 0xB0006 )
  {
  }

  void Scene00001( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      switch( result.getResult( 0 ) )
      {
        case ACTION_CREATE:
          Scene00002( player );
          break;

        case ACTION_RENAME:
          Scene00003( player );
          break;

        case ACTION_REMOVE:
          Scene00004( player );
          break;
      }
    };

    eventMgr().playScene( player, getId(), 1, 0, callback );
  }

  // create linkshell
  void Scene00002( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      linkshellMgr().createLinkshell( result.resultString, player );
      eventMgr().resumeScene( player, result.eventId, result.sceneId, { 0x15a } );
    };

    eventMgr().playScene( player, getId(), 2, 0, callback );
  }

  // rename linkshell
  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, 0 );
  }

  // remove linkshell
  void Scene00004( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 4, 0 );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00001( player );
  }
};

EXPOSE_SCRIPT( CmnDefLinkShell );