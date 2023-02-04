// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst001_00024
// Quest Name: Coarse Correspondence
// Quest ID: 65560
// Start NPC: 1000206
// End NPC: 1000233

using namespace Sapphire;

class SubFst001 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000233
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000206;
  static constexpr auto Actor1 = 1000233;
  static constexpr auto Item0 = 2000079;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq1Actor1Npctradeno = 99;
  static constexpr auto Seq1Actor1Npctradeok = 100;

public:
  SubFst001() : Sapphire::ScriptAPI::QuestScript( 65560 )
  {};

  ~SubFst001() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( !player.hasQuest( getId() ) )
          Scene00000( quest, player );
        else
          Scene00001( quest, player );
        break;
      }
      case Actor1:
      {
        if( !player.hasQuest( getId() ) )
          Scene00099( quest, player );
        else
          Scene00100( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setUI8AL( 1 );
      quest.setUI8BH( 1 );
      quest.setSeq( SeqFinish );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst001::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst001::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( SubFst001 );