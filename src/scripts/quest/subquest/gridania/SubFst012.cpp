// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst012_00038
// Quest Name: Parsemontrenomics
// Quest ID: 65574
// Start NPC: 1000768
// End NPC: 1000248

using namespace Sapphire;

class SubFst012 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH
  // UI8CL
  // UI8DH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000214
  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000218
  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000238
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000248
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000768;//Parsemontret
  static constexpr auto Actor1 = 1000214;//Gurthcid
  static constexpr auto Actor2 = 1000218;//Admiranda <<Tool Supplier>>
  static constexpr auto Actor3 = 1000238;//Alaric <<Independent Tinker>>
  static constexpr auto Actor4 = 1000248;//Ceinguled
  static constexpr auto Item0 = 2000081;
  static constexpr auto Item1 = 2000082;
  static constexpr auto Item2 = 2000083;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq1Actor2 = 2;
  static constexpr auto Seq1Actor3 = 3;
  static constexpr auto Seq2Actor4 = 4;
  static constexpr auto Seq2Actor4Npctradeno = 99;
  static constexpr auto Seq2Actor4Npctradeok = 100;

public:
  SubFst012() : Sapphire::ScriptAPI::QuestScript( 65574 ){};
  ~SubFst012() = default;

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
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00001( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00004( quest, player );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() && quest.getUI8BH() && quest.getUI8BL() )
    {
      quest.setSeq( SeqFinish );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 1 );
      quest.setUI8BL( 1 );
      quest.setUI8CH( 1 );
      quest.setUI8CL( 0 );
      quest.setUI8DH( 0 );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst012::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst012::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    quest.setUI8CH( 1 );
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubFst012::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setUI8CL( 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubFst012::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    quest.setUI8DH( 1 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubFst012::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00100( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst012::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst012::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( SubFst012 );