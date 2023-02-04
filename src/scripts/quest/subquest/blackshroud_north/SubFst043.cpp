// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst043_00199
// Quest Name: A Clear Sign
// Quest ID: 65735
// Start NPC: 1000172
// End NPC: 1000627

using namespace Sapphire;

class SubFst043 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 2 Seq: 1 Event: 1 Listener: 2000143
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000144
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000172;
  static constexpr auto Actor1 = 1000627;
  static constexpr auto Eobject0 = 2000143;
  static constexpr auto Eobject1 = 2000144;
  static constexpr auto EventActionProcessMiddle = 16;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Eobject0 = 1;
  static constexpr auto Seq1Eobject0Eventactionno = 99;
  static constexpr auto Seq1Eobject0Eventactionok = 100;
  static constexpr auto Seq1Eobject1 = 2;
  static constexpr auto Seq1Eobject1Eventactionno = 97;
  static constexpr auto Seq1Eobject1Eventactionok = 98;
  static constexpr auto Seq2Actor1 = 3;

public:
  SubFst043() : Sapphire::ScriptAPI::QuestScript( 65735 )
  {};

  ~SubFst043() = default;

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
        if( quest.getSeq() == SeqFinish )
          Scene00003( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart( player, getId(), EventActionProcessMiddle,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00001( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart( player, getId(), EventActionProcessMiddle,
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
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto credit = quest.getUI8AL();

    if( credit + 1 >= 2 )
    {
      quest.setUI8AL( credit + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, credit + 1, 2 );
      quest.setSeq( SeqFinish );
    }
    else
    {
      quest.setUI8AL( credit + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, credit + 1, 2 );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00100( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00098( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst043::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 1, true );
  }

};

EXPOSE_SCRIPT( SubFst043 );