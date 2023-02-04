// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst030_00173
// Quest Name: The Nose Knows
// Quest ID: 65709
// Start NPC: 1000632
// End NPC: 1000632

using namespace Sapphire;

class SubFst030 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000784
  /// Countable Num: 1 Seq: 2 Event: 1 Listener: 2000146
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1000764
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000632
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000632;
  static constexpr auto Actor1 = 1000784;
  static constexpr auto Actor2 = 1000764;
  static constexpr auto Eobject0 = 2000146;
  static constexpr auto EventActionGatherShort = 6;
  static constexpr auto Item0 = 2000140;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq2Eobject0 = 2;
  static constexpr auto Seq2Eobject0Eventactionno = 99;
  static constexpr auto Seq2Eobject0Eventactionok = 100;
  static constexpr auto Seq3Actor2 = 3;
  static constexpr auto Seq3Actor2Npctradeno = 97;
  static constexpr auto Seq3Actor2Npctradeok = 98;
  static constexpr auto Seq4Actor0 = 4;

public:
  SubFst030() : Sapphire::ScriptAPI::QuestScript( 65709 )
  {};

  ~SubFst030() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( !player.hasQuest( getId() ) )
          Scene00000( quest, player );
        else
          Scene00004( quest, player );
        break;
      }
      case Actor1:
      {
        Scene00001( quest, player );
        break;
      }
      case Actor2:
      {
        Scene00003( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart( player, getId(), 0x06,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00002( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq2 );
    eventMgr().sendEventNotice( player, getId(), 0, 2, 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00100( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00098( quest, player );
    else
      Scene00097( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Needs replacement
    //eventMgr().playScene(player, getId(), 97, 0, 0, 0);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
    eventMgr().sendEventNotice( player, getId(), 2, 2, 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Needs replacement
    //eventMgr().playScene(player, getId(), 99, 0, 0, 0);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst030::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq3 );
    eventMgr().sendEventNotice( player, getId(), 1, 2, 0, 0 );
    quest.setUI8FL( 1 );
    quest.setUI8BH( 1 );
  }

};

EXPOSE_SCRIPT( SubFst030 );