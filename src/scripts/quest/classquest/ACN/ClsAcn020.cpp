// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsAcn020_00453
// Quest Name: Way of the Arcanist
// Quest ID: 65989
// Start NPC: 1000895 (Murie)
// End NPC: 1000909 (Thubyrgeim)

using namespace Sapphire;

class ClsAcn020 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH
    // UI8BL

    /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1000909
    /// Countable Num: 0 Seq: 2 Event: 5 Listener: 347
    /// Countable Num: 0 Seq: 2 Event: 5 Listener: 324
    /// Countable Num: 0 Seq: 2 Event: 5 Listener: 49
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000909
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
    static constexpr auto Actor0 = 1000895; // Murie ( Pos: -335.743988 12.893800 1.388490  Teri: 129 )
    static constexpr auto Actor1 = 1000909; // Thubyrgeim ( Pos: -326.360992 12.893700 10.001000  Teri: 129 )
    static constexpr auto Enemy0 = 347; // Shelfscale Reaver
    static constexpr auto Enemy1 = 324; // Fallen Wizard
    static constexpr auto Enemy2 = 49; // Little Ladybug ( Pos: 230.500000 52.037998 138.003998  Teri: 140 )
    static constexpr auto LocFace0 = 604;
    static constexpr auto LocFace1 = 605;
    static constexpr auto LogmessageMonsterNotePageUnlock = 1016;
    static constexpr auto UnlockImageMonsterNote = 32;

  public:
    ClsAcn020() : Sapphire::ScriptAPI::QuestScript( 65989 ){}; 
    ~ClsAcn020() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        Scene00000( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00003( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcBaseId() != Enemy0 && bnpc.getBNpcBaseId() != Enemy1 && bnpc.getBNpcBaseId() != Enemy2 )
      return;


    auto currentKC347 = quest.getUI8AL() + 1;
    auto currentKC324 = quest.getUI8BH() + 1;
    auto currentKC49 = quest.getUI8BL() + 1;

    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      { 
        if( currentKC347 <= 3 )
        {
          quest.setUI8AL( currentKC347 );
          eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC347, 3 );
          if( currentKC347 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy1:
      { 
        if( currentKC324 <= 3 )
        {
          quest.setUI8BH( currentKC324 );
          eventMgr().sendEventNotice( player, getId(), 2, 2, currentKC324, 3 );
          if( currentKC324 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy2:
      { 
        if( currentKC49 <= 3 )
        {
          quest.setUI8BL( currentKC49 );
          eventMgr().sendEventNotice( player, getId(), 3, 2, currentKC49, 3 );
          if( currentKC49 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
    }
  }

  private:
    void checkQuestCompletion( World::Quest & quest, Entity::Player & player )
    {
      auto currentKC347 = quest.getUI8AL();
      auto currentKC324 = quest.getUI8BH();
      auto currentKC49 = quest.getUI8BL();

      if( currentKC347 == 3 && currentKC324 == 3 && currentKC49 == 3 )
      {
        quest.setUI8AL( 0 );
        quest.setUI8BH( 0 );
        quest.setUI8BL( 0 );
        quest.setSeq( SeqFinish );
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsAcn020::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsAcn020::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | DISABLE_SKIP | HIDE_UI, bindSceneReturn( &ClsAcn020::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // Said yes in cutscene
    {
      quest.setSeq( Seq2 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsAcn020::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ClsAcn020 );