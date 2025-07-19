// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include "Actor/BNpc.h"

// Quest Script: ClsPgl020_00533
// Quest Name: Way of the Pugilist
// Quest ID: 66069
// Start NPC: 1001286 (Gagaruna)
// End NPC: 1003817 (Hamon)

using namespace Sapphire;

class ClsPgl020 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH
    // UI8BL

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1003817
    /// Countable Num: 3 Seq: 2 Event: 5 Listener: 351
    /// Countable Num: 3 Seq: 2 Event: 5 Listener: 385
    /// Countable Num: 3 Seq: 2 Event: 5 Listener: 205
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1003817
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
    static constexpr auto Actor0 = 1001286; // Gagaruna ( Pos: -88.966698 2.550000 -51.144600  Teri: 130 )
    static constexpr auto Actor1 = 1003817; // Hamon ( Pos: -74.541298 1.999990 -42.379501  Teri: 130 )
    static constexpr auto Enemy0 = 262; // Qiqirn Gullroaster
    static constexpr auto Enemy1 = 632; // Trenchclaw Sahagin ( Pos: 80.837502 68.925400 -218.042999  Teri: 134 )
    static constexpr auto Enemy2 = 318; // Mottled Eft ( Pos: 15.554700 0.648601 -59.534698  Teri: 141 )
    static constexpr auto EventActionSearch = 1;
    static constexpr auto LocAction1 = 112;
    static constexpr auto LocAction2 = 113;
    static constexpr auto LocAction3 = 961;
    static constexpr auto LogmessageMonsterNotePageUnlock = 1013;
    static constexpr auto UnlockImageMonsterNote = 32;

  public:
    ClsPgl020() : Sapphire::ScriptAPI::QuestScript( 66069 ){}; 
    ~ClsPgl020() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      if( quest.getSeq() == Seq0 )
        Scene00000( quest, player );
    }
    else if( actorId == Actor1 )
    {
      if( quest.getSeq() == Seq1 )
        Scene00002( quest, player );
      else if( quest.getSeq() == SeqFinish )
        Scene00003( quest, player );
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcNameId() != Enemy0 && bnpc.getBNpcNameId() != Enemy1 && bnpc.getBNpcNameId() != Enemy2 )
      return;
    else
    {
      if( bnpc.getBNpcNameId() == Enemy0 && quest.getUI8AL() < 3 )
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        eventMgr().sendEventNotice( player, getId(), 1, 0, quest.getUI8AL(), 3 );
        checkQuestCompletion( quest, player );
      }
      else if( bnpc.getBNpcNameId() == Enemy1 && quest.getUI8BH() < 3 )
      {
        quest.setUI8BH( quest.getUI8BH() + 1 );
        eventMgr().sendEventNotice( player, getId(), 2, 0, quest.getUI8BH(), 3 );
        checkQuestCompletion( quest, player );
      }
      else if( bnpc.getBNpcNameId() == Enemy2 && quest.getUI8BL() < 3 )
      {
        quest.setUI8BL( quest.getUI8BL() + 1 );
        eventMgr().sendEventNotice( player, getId(), 3, 0, quest.getUI8BL(), 3 );
        checkQuestCompletion( quest, player );
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto QUEST_VAR_UI8AL = quest.getUI8AL();
    auto QUEST_VAR_UI8BH = quest.getUI8BH();
    auto QUEST_VAR_UI8BL = quest.getUI8BL();

    if( QUEST_VAR_UI8AL == 3 && QUEST_VAR_UI8BH == 3 && QUEST_VAR_UI8BL == 3 )
    {
      quest.setSeq( SeqFinish );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsPgl020::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00001( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsPgl020::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | HIDE_UI, bindSceneReturn( &ClsPgl020::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if (result.getResult(0) == 1)
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
      quest.setSeq( Seq2 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsPgl020::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00004( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsPgl020::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( ClsPgl020 );