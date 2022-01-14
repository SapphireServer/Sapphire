// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsArc999_00181
// Quest Name: So You Want to Be an Archer
// Quest ID: 65717
// Start NPC: 1000197
// End NPC: 1000197

using namespace Sapphire;

class ClsArc999 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used

  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
  };
  static constexpr auto Actor0 = 1000197;

  // Entities found in the script data of the quest

public:
  ClsArc999() : Sapphire::ScriptAPI::QuestScript( 65717 ){};
  ~ClsArc999() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        Scene00000( quest, player );
        break;
      }
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsArc999::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), 0 );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Archer );
    }
  }
};

EXPOSE_SCRIPT( ClsArc999 );