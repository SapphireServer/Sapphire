// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst037_00174
// Quest Name: No Quarter Given
// Quest ID: 65710
// Start NPC: 1000612
// End NPC: 1000612

using namespace Sapphire;

class SubFst037 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 2 Seq: 1 Event: 5 Listener: 743
  /// Countable Num: 2 Seq: 1 Event: 5 Listener: 744
  /// Countable Num: 2 Seq: 1 Event: 5 Listener: 745
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000612
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000612;
  static constexpr auto Enemy0 = 192;//743; <- WRONG INFO
  static constexpr auto Enemy1 = 193;//744; <- WRONG INFO
  static constexpr auto Enemy2 = 194;//745; <- WRONG INFO

public:
  SubFst037() : Sapphire::ScriptAPI::QuestScript( 65710 ){};
  ~SubFst037() = default;

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
        else if( quest.getSeq() == SeqFinish )
          Scene00002( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    auto credit = 0;

    switch( bnpc.getBNpcNameId() )
    {
      case Enemy0:
      {
        credit = quest.getUI8AL();

        quest.setUI8AL( credit + 1 );
        if( credit + 1 <= 2 )
          eventMgr().sendEventNotice( player, getId(), 0, 2, credit + 1, 2 );

        break;
      }
      case Enemy1:
      {
        credit = quest.getUI8BH();

        quest.setUI8BH( credit + 1 );
        if( credit + 1 <= 2 )
          eventMgr().sendEventNotice( player, getId(), 1, 2, credit + 1, 2 );

        break;
      }
      case Enemy2:
      {
        credit = quest.getUI8BL();

        quest.setUI8BL( credit + 1 );
        if( credit + 1 <= 2 )
          eventMgr().sendEventNotice( player, getId(), 2, 2, credit + 1, 2 );

        break;
      }
    }

    checkQuestCompletion( quest, player );
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto credit192 = quest.getUI8AL();
    auto credit193 = quest.getUI8BH();
    auto credit194 = quest.getUI8BL();

    if( credit192 >= 2 && credit193 >= 2 && credit194 >= 2 )
      quest.setSeq( SeqFinish );
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst037::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst037::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst037::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubFst037 );