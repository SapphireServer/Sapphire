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

    eventMgr().playScene( player, getId(), 1, HIDE_HOTBAR | NO_DEFAULT_CAMERA, callback );
  }

  // create linkshell
  void Scene00002( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 2, HIDE_HOTBAR );
  }

  // rename linkshell
  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, HIDE_HOTBAR );
  }

  // remove linkshell
  void Scene00004( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 4, HIDE_HOTBAR );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00001( player );
  }

  void onYield( uint32_t eventId, uint16_t sceneId, uint8_t yieldId, Entity::Player& player, const std::string& resultString, uint64_t resultInt ) override
  {
    auto errorCode = 0u;
    switch( sceneId )
    {
      case 2:
      {
        auto ls = linkshellMgr().createLinkshell( resultString, player );
        if( !ls )
          errorCode = 0x15a;

        eventMgr().resumeScene( player, eventId, sceneId, yieldId, { errorCode } );
        linkshellMgr().finishLinkshellAction( resultString, errorCode, player, 1 );
        break;
      }
      case 3:
      {
        auto ls = linkshellMgr().renameLinkshell( resultInt, resultString, player );
        if( !ls )
          errorCode = 0x15a;
        eventMgr().resumeScene( player, eventId, sceneId, yieldId, { errorCode } );
        linkshellMgr().finishLinkshellAction( resultString, errorCode, player, 3 );
        break;
      }
    }
  }

};

EXPOSE_SCRIPT( CmnDefLinkShell );