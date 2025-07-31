// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst023
// Quest Name: Drink Your Beans, Dear
// Quest ID: 65634
// Start NPC: 1000656
// End NPC: 1000612

using namespace Sapphire;

class SubFst023 : public Sapphire::ScriptAPI::QuestScript
{

private:

  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000656;// Dametta ( Pos: 400.656006 -5.886250 -104.875000  Teri: 154 )
  static constexpr auto Enemy0 = 32;     // Microchu
  static constexpr auto Item0 = 2000077;
  static constexpr auto Seq0Actor0 = 0;            //
  static constexpr auto Seq2Actor0 = 1;            //
  static constexpr auto Seq2Actor0Npctradeno = 99; // Hecatoncheir Piledriver
  static constexpr auto Seq2Actor0Npctradeok = 100;// Hecatoncheir Blastmaster ( Pos: -135.210007 5.708900 -117.417999  Teri: 141 )

public:
  SubFst023() : Sapphire::ScriptAPI::QuestScript( 65634 ) {};
  ~SubFst023() = default;

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
        if( quest.getSeq() == SeqFinish )
          Scene00001( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq1 )
    {
      if( bnpc.getBNpcNameId() != Enemy0 )
        return;

      quest.setUI8AL( quest.getUI8AL() + 1 );
      quest.setUI8BH( quest.getUI8BH() + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 4 );

      if( quest.getUI8AL() >= 4 )
        quest.setSeq( SeqFinish );
    }    
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst023::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst023::Scene00001Return ) );
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
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst023::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst023::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubFst023 );