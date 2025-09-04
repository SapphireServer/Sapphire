// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManWil005_00550
// Quest Name: Underneath the Sultantree
// Quest ID: 66086
// Start NPC: 1003995 (Papashan)
// End NPC: 1003995 (Papashan)

using namespace Sapphire;

class ManWil005 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information  
    // Quest vars / flags used
    // BitFlag8
    // UI8AL

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1003996
    /// Countable Num: 1 Seq: 2 Event: 1 Listener: 2001853
    /// Countable Num: 0 Seq: 255 Event: 15 Listener: 5020000
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      Seq2 = 2,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1003995; // Papashan ( Pos: 75.338402 2.138110 316.362000  Teri: 141 )
    static constexpr auto Actor1 = 1003996; // Hooded Lalafell ( Pos: 202.662994 14.104900 536.909973  Teri: 141 )
    static constexpr auto Actor2 = 1003997; // ×次女a ( Pos: 76.674599 2.137120 317.433014  Teri: 141 )
    static constexpr auto Actor3 = 1003998; // ×近衛a ( Pos: 77.176598 2.137340 315.631989  Teri: 141 )
    static constexpr auto Actor4 = 1003999; // ×近衛b ( Pos: 77.310501 2.136910 316.973999  Teri: 141 )
    static constexpr auto Actor5 = 1004000; // ×近衛c ( Pos: 78.402603 2.136520 316.269012  Teri: 141 )
    static constexpr auto Actor6 = 1004001; // Lilira ( Pos: 76.643402 2.136930 318.191010  Teri: 141 )
    static constexpr auto Actor20 = 1006171; // Lilira
    static constexpr auto Actor30 = 1006167; // 侍女a
    static constexpr auto Actor40 = 1006168; // 近衛a
    static constexpr auto Actor50 = 1006169; // 近衛b
    static constexpr auto Actor60 = 1006170; // 近衛c
    static constexpr auto CutScene02 = 141;
    static constexpr auto CutScene03 = 56;
    static constexpr auto CutScene04 = 142;
    static constexpr auto Eobject0 = 2001853; //  ( Pos: 202.638000 14.137900 536.905029  Teri: 141 )
    static constexpr auto EventActionSearch = 1; // Interaction
    static constexpr auto Questbattle0 = 37;
    static constexpr auto Seq0Actor0Lq = 50; // Goblin Thug
    static constexpr auto Territorytype0 = 270;
    static constexpr auto Territorytype1 = 141;

  public:
    ManWil005() : Sapphire::ScriptAPI::QuestScript( 66086 ){}; 
    ~ManWil005() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if (quest.getSeq() == Seq0)
        {
          Scene00000( quest, player );
        }
        else if (quest.getSeq() == SeqFinish)
        {
         Scene00006( quest, player );
        }
          
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
        break;
      }
      case Actor4:
      {
        break;
      }
      case Actor5:
      {
        break;
      }
      case Actor6:
      {
        break;
      }
      case Actor20:
      {
        break;
      }
      case Actor30:
      {
        break;
      }
      case Actor40:
      {
        break;
      }
      case Actor50:
      {
        break;
      }
      case Actor60:
      {
        break;
      }
    }
  }

  void onEnterTerritory( World::Quest& quest, Entity::Player& player, uint16_t param1, uint16_t param2 ) override
  {
    if( quest.getSeq() == Seq2 )
    {
      Scene00005( quest, player );
    }
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManWil005::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil005::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &ManWil005::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ManWil005::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ManWil005::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV | HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE | DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                                           // todo: wtf is 0x00100000
                                                           DISABLE_CANCEL_EMOTE,
                               bindSceneReturn( &ManWil005::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, FADE_OUT | HIDE_HOTBAR | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil005::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ManWil005::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ManWil005::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ManWil005::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ManWil005::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ManWil005::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( ManWil005 );