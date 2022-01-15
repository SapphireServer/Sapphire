#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManWil002_00568
// Quest Name: Close to Home
// Quest ID: 66104
// Start NPC: 1003988
// End NPC: 1001353

using namespace Sapphire;

class ManWil002 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestBitFlag8
  // GetQuestUI8AL
  // GetQuestUI8BH
  // GetQuestUI8BL
  // GetQuestUI8CH

  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  static constexpr auto RewardGil = 107;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003988;
  static constexpr auto Actor1 = 1002277;
  static constexpr auto Actor2 = 1003908;
  static constexpr auto Actor20 = 1001637;
  static constexpr auto Actor3 = 1001353;
  static constexpr auto Aetheryte0 = 9;
  static constexpr auto BindActor0 = 6229228;
  static constexpr auto Item0 = 2000386;
  static constexpr auto LocAction1 = 605;
  static constexpr auto LocAction2 = 1005;
  static constexpr auto LocMarker01 = 4009142;
  static constexpr auto LocMarker02 = 4009152;
  static constexpr auto LocPosCam1 = 4105872;
  static constexpr auto LocPosCam2 = 4105874;
  static constexpr auto LocPosCam3 = 4009150;
  static constexpr auto LocPosCam4 = 4143488;
  static constexpr auto Poprange0 = 4110794;
  static constexpr auto Reward0 = 1;
  static constexpr auto Screenimage0 = 14;
  static constexpr auto Seq0Actor0Lq = 50;
  static constexpr auto Territorytype0 = 130;

public:
  ManWil002() : Sapphire::ScriptAPI::QuestScript( 66104 )
  {
  };

  ~ManWil002()
  {
  };

  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      Scene00000( quest, player );
    }
    else if( actorId == Actor1 )
    {
      Scene00003( quest, player );
    }
    else if( actorId == Actor2 )
    {
      Scene00004( quest, player );
    }
    else if( actorId == Actor3 )
    {
      Scene00008( quest, player );
    }
    else if( actorId == Aetheryte0 )
    {
      eventMgr().eventActionStart( player, 0x050002, 0x13,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 eventMgr().sendEventNotice( player, 0x050002, 0, 1, 0, 0 );
                                 player.registerAetheryte( 2 );
                                 player.setSystemActionUnlocked( Common::UnlockEntry::Return );
                                 Scene00001( quest, player );
                               },
                               nullptr, getId() );
    }
  }

private:

  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 1 )
    {
      eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 );
    }
    else if( varIdx == 2 )
    {
      eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 );
    }
    else
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
    }

    auto QUEST_VAR_ATTUNE = quest.getUI8AL();
    auto QUEST_VAR_CLASS = quest.getUI8BH();
    auto QUEST_VAR_TRADE = quest.getUI8BL();

    if( QUEST_VAR_ATTUNE == 1 && QUEST_VAR_CLASS == 1 && QUEST_VAR_TRADE == 1 )
    {
      quest.setSeq( SeqFinish );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00050( quest, player );
    }
  }

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManWil002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    checkQuestCompletion( quest, player, 0 );
  }

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    checkQuestCompletion( quest, player, 1 );
  }

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00005( quest, player );
    }
  }

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManWil002::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH( 0 );
    quest.setUI8BH( 1 );
    checkQuestCompletion( quest, player, 2 );
  }

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR );
  }

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR );
  }

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManWil002::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, HIDE_HOTBAR, bindSceneReturn( &ManWil002::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // On quest accept
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 ); // Receive key item

    // Teleport to real ul'dah
    player.forceZoneing( 130 );
  }
};

EXPOSE_SCRIPT( ManWil002 );