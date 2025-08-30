// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsAcn001_00451
// Quest Name: So You Want to Be an Arcanist
// Quest ID: 65987
// Start NPC: 1000895 (Murie)
// End NPC: 1000895 (Murie)

using namespace Sapphire;

class ClsAcn001 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
    };

    static constexpr auto Actor0 = 1000895;

    // Entities found in the script data of the quest

  public:
    ClsAcn001() : Sapphire::ScriptAPI::QuestScript( 65987 ){}; 
    ~ClsAcn001() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
      Scene00000( quest, player );
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsAcn001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
        player.finishQuest( getId(), 0 );
    }
  }

};

EXPOSE_SCRIPT( ClsAcn001 );