// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManWil002_00568
// Quest Name: Close to Home
// Quest ID: 66104
// Start NPC: 1003988 (Momodi)
// End NPC: 1001353 (Momodi)

using namespace Sapphire;

class ManWil002 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH
    // UI8BL
    // UI8CH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 9
    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1002277
    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1003908
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1003988
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1003988; // Momodi ( Pos: 21.077101 7.450000 -78.813400  Teri: 182 )
    static constexpr auto Actor1 = 1002277; // Lulutsu ( Pos: -97.520401 6.973330 23.605700  Teri: 131 )
    static constexpr auto Actor2 = 1003908; // Seseroga ( Pos: 137.957001 3.982560 -41.092602  Teri: 131 )
    static constexpr auto Actor3 = 1001353; // Momodi ( Pos: 21.072599 7.450000 -78.782303  Teri: 130 )
    static constexpr auto Actor20 = 1001637; // Nenebaru
    static constexpr auto Aetheryte0 = 9;
    static constexpr auto BindActor0 = 6229228; // 
    static constexpr auto Item0 = 2000386;
    static constexpr auto LocAction1 = 605;
    static constexpr auto LocAction2 = 1005;
    static constexpr auto LocPosCam1 = 4105872;
    static constexpr auto LocPosCam2 = 4105874;
    static constexpr auto LocPosCam3 = 4009150;
    static constexpr auto LocPosCam4 = 4143488;
    static constexpr auto Poprange0 = 4110794;
    static constexpr auto Reward0 = 1;
    static constexpr auto Screenimage0 = 14;
    static constexpr auto Seq0Actor0Lq = 50; // Goblin Thug
    static constexpr auto Territorytype0 = 130;

  public:
    ManWil002() : Sapphire::ScriptAPI::QuestScript( 66104 ){}; 
    ~ManWil002() = default; 

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
        Scene00003( quest, player );
        break;
      }
      case Actor2:
      {
        Scene00004( quest, player );
        break;
      }
      case Actor3:
      {
        Scene00008( quest, player );
        break;
      }
      case Aetheryte0:
      {
        eventMgr().eventActionStart( player, getId(), 0x13, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
              player.registerAetheryte( Aetheryte0 );
              player.setRewardFlag( Common::UnlockEntry::Return );
              Scene00002( quest, player ); }, nullptr, getId() );
        break;
      }
      case Actor20:
      {
        break;
      }
    }
  }


  private:
    void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
    {
      auto var_Attune = quest.getUI8AL();
      auto var_Class = quest.getUI8BH();
      auto var_Trade = quest.getUI8BL();

      if( var_Attune == 1 && var_Class == 1 && var_Trade == 1 )
      {
        quest.setSeq( SeqFinish );
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00050( quest, player );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // Turn in quest item
    {
      quest.setUI8CH( 0 );
      Scene00005( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil002::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ManWil002::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ManWil002::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil002::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil002::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // On quest accept
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 );// Receive key item

    // Teleport to real ul'dah
    warpMgr().requestMoveTerritoryType( player, Common::WarpType::WARP_TYPE_NORMAL, 130 );
  }

};

EXPOSE_SCRIPT( ManWil002 );