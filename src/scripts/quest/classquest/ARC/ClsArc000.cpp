// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsArc000_00021
// Quest Name: Way of the Archer
// Quest ID: 65557
// Start NPC: 1000197
// End NPC: 1000200

using namespace Sapphire;

class ClsArc000 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000200
  /// Countable Num: 3 Seq: 2 Event: 5 Listener: 37
  /// Countable Num: 3 Seq: 2 Event: 5 Listener: 49
  /// Countable Num: 3 Seq: 2 Event: 5 Listener: 47
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000200
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
  static constexpr auto Actor0 = 1000197;
  static constexpr auto Actor1 = 1000200;
  static constexpr auto Enemy0 = 37;
  static constexpr auto Enemy1 = 49;
  static constexpr auto Enemy2 = 47;
  static constexpr auto LocFace0 = 604;
  static constexpr auto LocFace1 = 605;
  static constexpr auto LogmessageMonsterNotePageUnlock = 1008;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq3Actor1 = 2;
  static constexpr auto UnlockImageMonsterNote = 32;

public:
  ClsArc000() : Sapphire::ScriptAPI::QuestScript( 65557 ){};
  ~ClsArc000() = default;

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
        else
          Scene00002( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    if( bnpc.getBNpcNameId() != Enemy0 && bnpc.getBNpcNameId() != Enemy1 && bnpc.getBNpcNameId() != Enemy2 )
      return;

    switch( bnpc.getBNpcNameId() )
    {
      case Enemy0:
      {
        auto currentKC37 = quest.getUI8AL();

        if( currentKC37 + 1 >= 3 )
        {
          checkQuestCompletion( quest, player, 1 );
          quest.setUI8AL( currentKC37 + 1 );
        }
        else
        {
          quest.setUI8AL( currentKC37 + 1 );
          eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC37 + 1, 3 );
        }

        break;
      }
      case Enemy1:
      {
        auto currentKC49 = quest.getUI8BH();

        if( currentKC49 + 1 >= 3 )
        {
          checkQuestCompletion( quest, player, 2 );
          quest.setUI8BH( currentKC49 + 1 );
        }
        else
        {
          quest.setUI8BH( currentKC49 + 1 );
          eventMgr().sendEventNotice( player, getId(), 2, 2, currentKC49 + 1, 3 );
        }

        break;
      }
      case Enemy2:
      {
        auto currentKC47 = quest.getUI8BL();

        if( currentKC47 + 1 >= 3 )
        {
          checkQuestCompletion( quest, player, 3 );
          quest.setUI8BL( currentKC47 + 1 );
        }
        else
        {
          quest.setUI8BL( currentKC47 + 1 );
          eventMgr().sendEventNotice( player, getId(), 3, 2, currentKC47 + 1, 3 );
        }

        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 1 )
      eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 );
    else if( varIdx == 2 )
      eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 );
    else
      eventMgr().sendEventNotice( player, getId(), 3, 0, 0, 0 );

    auto QUEST_ONKILL_37 = quest.getUI8AL();
    auto QUEST_ONKILL_49 = quest.getUI8BH();
    auto QUEST_ONKILL_47 = quest.getUI8BL();

    if( QUEST_ONKILL_37 >= 3 && QUEST_ONKILL_49 >= 3 && QUEST_ONKILL_47 >= 3 )
    {
      quest.setSeq( SeqFinish );
    }
  }

  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsArc000::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc000::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
      quest.setSeq( Seq2 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsArc000::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.setSystemActionUnlocked( Sapphire::Common::UnlockEntry::HuntingLog );
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsArc000 );