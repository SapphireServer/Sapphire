// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsMar998_00181
// Quest Name: Way of the Maruader
// Quest ID: 65846
// Start NPC: 1000926
// End NPC: 1000927

using namespace Sapphire;

class ClsMar998 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used

  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    SEQ0      = 0,
    SEQFINISH = 255
  };
  static constexpr auto Actor0 = 1000926;
  static constexpr auto Actor1 = 1000927;

  // Entities found in the script data of the quest

public:
  ClsMar998() : Sapphire::ScriptAPI::QuestScript(65846) {};
  ~ClsMar998() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk(World::Quest& quest, Entity::Player& player, uint64_t actorId) override
  {
    switch ( actorId )
    {
    case Actor0:
    {
      if (quest.getSeq() == SEQ0) {
        Scene00000(quest, player);
      }
      break;
    }
    case Actor1:
      if (quest.getSeq() == SEQFINISH) {
        Scene00001(quest, player);
      }
      break;
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000(World::Quest& quest, Entity::Player& player)
  {
    eventMgr().playQuestScene(player, getId(), 0, NONE, bindSceneReturn(&ClsMar998::Scene00000Return));
  }

  void Scene00000Return(World::Quest& quest, Entity::Player& player, const Event::SceneResult& result)
  {
    if (result.getResult( 0 ) == 1)
    {
      quest.setSeq(SEQFINISH);
    }
  }

  void Scene00001(World::Quest& quest, Entity::Player& player)
  {
    eventMgr().playQuestScene(player, getId(), 1, NONE, bindSceneReturn(&ClsMar998::Scene00001Return));
  }

  void Scene00001Return(World::Quest& quest, Entity::Player& player, const Event::SceneResult& result)
  {
    if (result.getResult( 0 ) == 1)
    {
      player.finishQuest(getId());
      player.setLevelForClass(1, Sapphire::Common::ClassJob::Marauder);
      player.setMaxGearSets(player.getMaxGearSets() + 1);
    }
  }
};

EXPOSE_SCRIPT(ClsMar998);