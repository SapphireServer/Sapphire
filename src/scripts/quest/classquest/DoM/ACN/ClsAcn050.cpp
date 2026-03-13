// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsAcn050_00455
// Quest Name: What's in the Box
// Quest ID: 65991
// Start NPC: 1000909 (Thubyrgeim)
// End NPC: 1000909 (Thubyrgeim)

using namespace Sapphire;

class ClsAcn050 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 5 Listener: 339
    /// Countable Num: 1 Seq: 1 Event: 5 Listener: 118
    /// Countable Num: 1 Seq: 2 Event: 1 Listener: 1000909
    /// Countable Num: 1 Seq: 3 Event: 1 Listener: 2002266
    /// Countable Num: 1 Seq: 4 Event: 5 Listener: 39
    /// Countable Num: 0 Seq: 255 Event: 5 Listener: 39
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
    static constexpr auto Actor0 = 1000909; // Thubyrgeim ( Pos: -326.360992 12.893700 10.001000  Teri: 129 )
    static constexpr auto CutClsacn05010 = 44;
    static constexpr auto Enemy0 = 339; // Tempered Orator ( Pos: 56.076900 -13.504300 39.169899  Teri: 138 ) //vv
    static constexpr auto Enemy1 = 118; // Midge Swarm ( Pos: -77.578903 -58.467999 155.332001  Teri: 145 )  // unused?
    static constexpr auto Enemy2 = 4260926; // Tree slug A
    static constexpr auto Enemy3 = 4260927; // Tree slug B
    static constexpr Common::QuestEobject Eobject0 = { 2002266, 134, { -0.112231, 26.103201, 196.542007 }, 1.000000 }; // Practice Crates Seq3
    static constexpr Common::QuestEobject Eobject1 = { 2001889, 134, { -0.076355, 24.396400, 196.550995 }, 0.991760 }; // 訓練用の木箱
    static constexpr Common::QuestEobject Eobject2 = { 2002476, 134, { -0.088241, 25.966101, 196.565002 }, 1.000000 }; // Practice Crate Seq4
    static constexpr auto EventActionProcessUpperMiddle = 32; // Search crates
    static constexpr auto EventActionSearch = 1;
    static constexpr auto Item0 = 2000796; // Practice Crate
    static constexpr auto LocActor0 = 1005190; // K'lyhia
    static constexpr auto LocFace0 = 604;
    static constexpr auto LocFace1 = 605;
    static constexpr auto LocPosActor0 = 4310134; // 
    static constexpr auto LocPosActor1 = 4314130; // 

    static constexpr auto Enemy4 = 393; // wild dodo
    static constexpr auto Enemy5 = 405; // mandregora
    static constexpr auto Enemy6 = 39; // tree slug

  public:
    ClsAcn050() : Sapphire::ScriptAPI::QuestScript( 65991 ){}; 
    ~ClsAcn050() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        switch( quest.getSeq() )
        {
          case Seq0:
          {
            Scene00000( quest, player );
            break;
          }
          case Seq2:
          {
            Scene00002( quest, player );
            break;
          }
          case SeqFinish:
          {
            Scene00012( quest, player );
            break;
          }
        }
      }
      case Eobject0.id:
      {
        if( quest.getSeq() == Seq3 )
        {
          eventMgr().eventActionStart( player, getId(), EventActionProcessUpperMiddle, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) { Scene00004( quest, player ); }, nullptr, 0 );
          break;
        }
      }
      case Eobject2.id:
      {
        if( quest.getSeq() == Seq4 )
        {
          eventMgr().eventActionStart( player, getId(), EventActionProcessUpperMiddle, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) { Scene00009( quest, player ); }, nullptr, 0 );
          break;
        }
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcNameId() != Enemy4 && bnpc.getBNpcNameId() != Enemy5 && bnpc.getBNpcNameId() != Enemy6 )
      return;

    if ( quest.getSeq() == Seq1 )
    {
      auto currentKC393 = quest.getUI8AL() + 1;
      auto currentKC405 = quest.getUI8BH() + 1;

      switch( bnpc.getBNpcNameId() )
      {
        case Enemy4:
        {
          if( currentKC393 <= 3 )
          {
            quest.setUI8AL( currentKC393 );
            eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC393, 3 );
            if( currentKC393 == 3 )
              checkQuestCompletion( quest, player );
          }
          break;
        }
        case Enemy5:
        {
          if( currentKC405 <= 3 )
          {
            quest.setUI8BH( currentKC405 );
            eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC405, 3 );
            if( currentKC405 == 3 )
              checkQuestCompletion( quest, player );
          }
          break;
        }
      }
    }
    else if( quest.getSeq() == Seq3 )
    {
      auto currentKC39 = quest.getUI8AL() + 1;
      if( bnpc.getBNpcNameId() == Enemy6 )
      {
        if( currentKC39 <= 2 )
        {
          quest.setUI8AL( currentKC39 );
          if( currentKC39 == 2 )
            checkQuestCompletion( quest, player );
        }
      }
    }
  }

  private:
    void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
    {
      switch (quest.getSeq())
      {
        case Seq1:
        {
          auto currentKC394 = quest.getUI8AL();
          auto currentKC405 = quest.getUI8BH();

          if( currentKC394 == 3 && currentKC405 == 3 )
          {
            quest.setUI8AL( 0 );
            quest.setUI8BH( 0 );
            quest.setSeq( Seq2 );
          }
          break;
        }
        case Seq3:
        {
          auto currentKC39 = quest.getUI8AL();

          if( currentKC39 == 2 )
          {
            quest.setUI8AL( 0 );
            quest.setBitFlag8( 1, false );
            eventMgr().sendEventNotice( player, getId(), 3, 0, 0, 0 );
            quest.setSeq( Seq4 );
          }
          break;
        }
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsAcn050::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsAcn050::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////
  
  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsAcn050::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsAcn050::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    //You sense a hostile presence!
    eventMgr().playQuestScene( player, getId(), 4, NO_DEFAULT_CAMERA, bindSceneReturn( &ClsAcn050::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy2, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy0->hateListAdd( player.getAsPlayer(), 1 );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy3, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy1->hateListAdd( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsAcn050::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsAcn050::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsAcn050::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ClsAcn050::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsAcn050::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendEventNotice( player, getId(), 4, 0, 0, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ClsAcn050::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ClsAcn050::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ClsAcn050::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00013( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ClsAcn050::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ClsAcn050 );