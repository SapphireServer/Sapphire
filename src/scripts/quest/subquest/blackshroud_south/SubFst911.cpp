// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"

// Quest Script: SubFst911_01162
// Quest Name: My Feisty Little Chocobo
// Quest ID: 66698
// Start NPC: 1002754
// End NPC: 1000471

using namespace Sapphire;

class SubFst911 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1000471
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 2001467
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1000471
  /// Countable Num: 0 Seq: 4 Event: 5 Listener: 178
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000471
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1002754;
  static constexpr auto Actor1 = 1000471;
  static constexpr auto Enemy0 = 178;
  static constexpr auto Eobject0 = 2001467;
  static constexpr auto EventActionProcessMiddle = 16;
  static constexpr auto Item0 = 2000085;
  static constexpr auto Reward0 = 18;
  static constexpr auto Ritem0 = 4868;
  static constexpr auto Screenimage0 = 92;

public:
  SubFst911() : Sapphire::ScriptAPI::QuestScript( 66698 ){};
  ~SubFst911() = default;

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
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00005( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00007( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq2 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessMiddle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00003( quest, player );
                  },
                  nullptr, 0 );
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      {
        //TODO: Check if companion is spawned
        quest.setUI8AL( quest.getUI8AL() + 1 );
        eventMgr().sendEventNotice( player, getId(), 3, 2, quest.getUI8AL(), 3 );
        if( quest.getUI8AL() >= 3 )
        {
          quest.setUI8AL( 0 );
          quest.setSeq( SeqFinish );
        }
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst911::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst911::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst911::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq2 );
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst911::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq3 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst911::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubFst911::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00006( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubFst911::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq4 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setUI8BH( 0 );
    player.setRewardFlag( static_cast< Common::UnlockEntry >( Reward0 ) );
    player.setRewardFlag( static_cast< Common::UnlockEntry >( 17 ) );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubFst911::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( SubFst911 );