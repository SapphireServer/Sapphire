// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubWil070_00324
// Quest Name: Disorderly Conduct
// Quest ID: 65860
// Start NPC: 1001541 (Roger)
// End NPC: 1001541 (Roger)

using namespace Sapphire;

class SubWil070 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 4 Seq: 1 Event: 1 Listener: 1001462
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1001463
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001541; // Roger ( Pos: -99.395401 -11.380900 -41.723999  Teri: 141 )
    static constexpr auto Actor1 = 1001462; // Roundelph ( Pos: -93.339500 -11.350300 -41.367199  Teri: 141 )
    static constexpr auto Actor2 = 1001463; // Adalfuns ( Pos: -72.826401 -12.667800 -54.076199  Teri: 141 )
    static constexpr auto Actor3 = 1001465; // Solid Trunk ( Pos: -90.043503 -11.398500 -53.666000  Teri: 141 )
    static constexpr auto Actor4 = 1001466; // Ricard ( Pos: -89.735001 -11.350000 -51.539902  Teri: 141 )
    static constexpr auto Item0 = 2000234;
    static constexpr auto Item0Icon = 26153;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq1Actor1 = 1;
    static constexpr auto Seq1Actor2 = 2;
    static constexpr auto Seq1Actor3 = 3; 
    static constexpr auto Seq1Actor4 = 4; 
    static constexpr auto Seq2Actor0 = 5; 
    static constexpr auto Seq2Actor0Npctradeno = 99;
    static constexpr auto Seq2Actor0Npctradeok = 100;

  public:
    SubWil070() : Sapphire::ScriptAPI::QuestScript( 65860 ){}; 
    ~SubWil070() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == 0 )
          Scene00000( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00005( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == 1 )
          Scene00001( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == 1 )
          Scene00002( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == 1 )
          Scene00003( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == 1 )
          Scene00004( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }


  private:
    void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
    {
      if( varIdx == 1 )
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        quest.setUI8BH( quest.getUI8BH() + 1 );

        if (quest.getUI8AL() == 4)
          quest.setSeq( SeqFinish );
      }
      eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AL(), 4, Item0Icon } );
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubWil070::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( Seq1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubWil070::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 1 );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubWil070::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 1 );
    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubWil070::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 1 );
    quest.setBitFlag8( 3, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubWil070::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 1 );
    quest.setBitFlag8( 4, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubWil070::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00100( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubWil070::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubWil070::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( SubWil070 );