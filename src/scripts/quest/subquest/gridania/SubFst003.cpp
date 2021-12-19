// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst003_00026
// Quest Name: Once Bitten, Twice Shy
// Quest ID: 65562
// Start NPC: 1000297
// End NPC: 1000315

using namespace Sapphire;

class SubFst003 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000315
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000297;
  static constexpr auto Actor1 = 1000315;
  static constexpr auto Item0 = 2000028;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq1Actor1Npctradeno = 99;
  static constexpr auto Seq1Actor1Npctradeok = 100;

public:
  SubFst003() : Sapphire::ScriptAPI::QuestScript( 65562 )
  {};

  ~SubFst003() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
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
        Scene00001( quest, player );
        break;
      }
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst003::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( SeqFinish );
      quest.setUI8BH( 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst003::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00100( quest, player );
    else
      Scene00099( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &SubFst003::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    eventMgr().playScene( player, getId(), 99, 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst003::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      if( player.giveQuestRewards( getId(), 0 ) )
        quest.setUI8BH( 0 );
      player.finishQuest( getId() );
    }

  }

};

EXPOSE_SCRIPT( SubFst003 );