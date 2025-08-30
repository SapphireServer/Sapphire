// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsGla001_00177
// Quest Name: So You Want to Be a Gladiator
// Quest ID: 65713
// Start NPC: 1002277 (Lulutsu)
// End NPC: 1002277 (Lulutsu)

using namespace Sapphire;

class ClsGla001 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
    };

    static constexpr auto Actor0 = 1002277; // Lulutsu ( Pos: -97.520401 6.973330 23.605700  Teri: 131 )

    // Entities found in the script data of the quest

  public:
    ClsGla001() : Sapphire::ScriptAPI::QuestScript( 65713 ){}; 
    ~ClsGla001() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsGla001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      player.finishQuest( getId(), 0 );
    }
  }

};

EXPOSE_SCRIPT( ClsGla001 );