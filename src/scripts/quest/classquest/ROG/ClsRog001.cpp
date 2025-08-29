// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsRog001_00101
// Quest Name: So You Want to Be a Rogue
// Quest ID: 65637
// Start NPC: 1009944 (Lonwoerd)
// End NPC: 1009944 (Lonwoerd)

using namespace Sapphire;

class ClsRog001 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
    };

    // Entities found in the script data of the quest
    static constexpr auto QstGaiuse218 = 66898;
    static constexpr auto QstSubsea016 = 65859;

    static constexpr auto Actor0 = 1009944; // Lonwoerd ( Pos: -152.656006 2.856240 243.188004  Teri: 129 )

  public:
    ClsRog001() : Sapphire::ScriptAPI::QuestScript( 65637 ){}; 
    ~ClsRog001() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsRog001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //if( result.getResult( 0 ) == 1 )
      //{
    if( player.isQuestCompleted( QstSubsea016 ) ) // Todo: Remove when quest is fixed
        player.finishQuest( getId(), result.getResult( 1 ) );
      //}
  }

};

EXPOSE_SCRIPT( ClsRog001 );