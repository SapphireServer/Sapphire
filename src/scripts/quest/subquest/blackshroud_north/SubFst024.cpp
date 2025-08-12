// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: SubFst024_00099
// Quest Name: The Kindness of Strangers
// Quest ID: 65635
// Start NPC: 1000324 (Emeria)
// End NPC: 1000100 (Mother Miounne)

using namespace Sapphire;

class SubFst024 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000009
    /// Countable Num: 1 Seq: 2 Event: 9 Listener: 155
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000324
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
    static constexpr auto Actor0 = 1000324; // Emeria ( Pos: 333.364014 -6.459910 -69.749001  Teri: 154 )
    static constexpr auto Actor1 = 1000100; // Mother Miounne ( Pos: 23.849800 -8.000000 115.922997  Teri: 132 )
    static constexpr auto Enemy0 = 2313265; // 
    static constexpr auto Eobject0 = 2000009; // Destination ( Pos: 358.761993 -2.828320 4.701550  Teri: 154 )
    static constexpr auto EventActionSearch = 1;
    static constexpr auto EventActionWaiting2Middle = 12;
    static constexpr auto Item0 = 2000076;
    static constexpr auto LocFace1 = 617;
    static constexpr auto LocFace2 = 604;
    static constexpr auto Motion0 = 1;
    static constexpr auto Motion1 = 34;
    static constexpr auto NqChara01 = 1001503;
    static constexpr auto NqChara02 = 1001504;
    static constexpr auto NqChara03 = 1001505;
    static constexpr auto NqCharaNoName = 1006185;
    static constexpr auto NqPoint001 = 1556884;
    static constexpr auto NqPoint1000 = 2154510;
    static constexpr auto NqPoint1001 = 2154536;
    static constexpr auto NqPoint1002 = 2154537;
    static constexpr auto NqPoint1003 = 2154514;
    static constexpr auto NqPoint1004 = 2154513;
    static constexpr auto NqPoint1005 = 2154542;
    static constexpr auto NqPoint1006 = 2154543;
    static constexpr auto NqPoint002 = 1556885;
    static constexpr auto NqPoint003 = 2029185;

  public:
    SubFst024() : Sapphire::ScriptAPI::QuestScript( 65635 ){}; 
    ~SubFst024() = default; 

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
        if( quest.getSeq() == Seq2 )
          Scene00004( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00007( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
        {
          eventMgr().eventActionStart(
                  player, getId(), EventActionWaiting2Middle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00001( quest, player );
                  },
                  nullptr, 0 );
        }
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8BH( 1 );
        eventMgr().sendEventNotice( player, getId(), 0, 0 );
        quest.setSeq( Seq2 );
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst024::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst024::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst024::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst024::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst024::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00005( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | HIDE_UI, bindSceneReturn( &SubFst024::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubFst024::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubFst024::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( SubFst024 );