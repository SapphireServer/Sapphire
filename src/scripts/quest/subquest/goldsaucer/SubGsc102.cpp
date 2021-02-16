#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubGsc102_00437
// Quest Name: Triple Triad Trial
// Quest ID: 65973
// Start NPC: 1011060
// End NPC: 1011060

using namespace Sapphire;

class SubGsc102 : public Sapphire::ScriptAPI::EventScript
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
    static constexpr auto Actor0 = 1011060;
    static constexpr auto LevelNpc0 = 5581330;

  public:
    SubGsc102() : Sapphire::ScriptAPI::EventScript( 65973 ){}; 
    ~SubGsc102() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  void Scene00000( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        if( player.giveQuestRewards( getId(), result.param3 ) )
        {
          player.finishQuest( getId() );
        }
      }
    };

    player.playScene( getId(), 0, NONE, callback );
  }

};

EXPOSE_SCRIPT( SubGsc102 );