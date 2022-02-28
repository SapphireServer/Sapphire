// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: FesEvn001_01287
// Quest Name: Burgeoning Dread
// Quest ID: 66823
// Start NPC: 1005540
// End NPC: 1000168

using namespace Sapphire;

class FesEvn001 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8DL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 5010000
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 5010000
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1005540;//Khloe Pajhiri
  static constexpr auto Actor2 = 1000168;//Vorsaile Heuloix
  static constexpr auto CutEvent1 = 416;
  static constexpr auto Fate0 = 680;//Tower of Power (Lower La Noscea)
  static constexpr auto Fate1 = 682;//Tower of Power (South Shroud)
  static constexpr auto Fate2 = 684;//Tower of Power (Western Thanalan)
  static constexpr auto Fate3 = 686;//Tower of Power (Southern Thanalan)
  static constexpr auto Fate4 = 688;//Tower of Power (Middle La Noscea)
  static constexpr auto Fate5 = 690;//Tower of Power (Eastern La Noscea)
  //TODO: Might need FateIDs 679,681,683,685,687,689 for Embiggened Spriggans FATE
  static constexpr auto Item0 = 2001165;
  static constexpr auto ScreenimageAccepted = 127;
  static constexpr auto ScreenimageComplete = 128;

public:
  FesEvn001() : Sapphire::ScriptAPI::QuestScript( 66823 ){};
  ~FesEvn001() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00002( quest, player );
        break;
      }
    }
  }

  //TODO: This func doesn't exist, leaving behind for future implementation
  void onFateComplete( World::Quest& quest, Entity::Player& player, uint32_t fateId )
  {
    if( fateId == Fate0 || fateId == Fate1 || fateId == Fate2 || fateId == Fate3 || fateId == Fate4 || fateId == Fate5 ) //Tower of Power FATE
      quest.setUI8AH( 1 );
    else if( quest.getUI8AH() > 0 && (fateId == 679 || fateId == 681 || fateId == 683 || fateId == 685 || fateId == 687 || fateId == 689) ) //Embiggened Spriggans FATE
    {
      quest.setUI8AH( 0 );
      quest.setUI8BH( 1 );
      quest.setSeq( SeqFinish );
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &FesEvn001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &FesEvn001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &FesEvn001::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &FesEvn001::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00004( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &FesEvn001::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00005( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &FesEvn001::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( FesEvn001 );