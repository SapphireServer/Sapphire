// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst007_00031
// Quest Name: Essential Oil
// Quest ID: 65567
// Start NPC: 1000705
// End NPC: 1000705

using namespace Sapphire;

class SubFst007 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 6 Seq: 1 Event: 9 Listener: 49
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000705
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000705;
  static constexpr auto Enemy0 = 49;
  static constexpr auto Item0 = 2000098;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq2Actor0 = 1;
  static constexpr auto Seq2Actor0Npctradeno = 99;
  static constexpr auto Seq2Actor0Npctradeok = 100;

public:
  SubFst007() : Sapphire::ScriptAPI::QuestScript( 65567 ){};
  ~SubFst007() = default;

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
          Scene00001( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    if( bnpc.getBNpcNameId() != Enemy0 )
      return;

    auto currentKC = quest.getUI8AL();

    if( currentKC + 1 >= 6 )
    {
      quest.setUI8AL( currentKC + 1 );
      quest.setUI8BH( currentKC + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 6 );
      quest.setSeq( SeqFinish );
    }
    else
    {
      eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 6 );
      quest.setUI8AL( currentKC + 1 );
      quest.setUI8BH( currentKC + 1 );
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst007::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst007::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00100( quest, player );
    else
      Scene00099( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &SubFst007::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst007::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubFst007 );