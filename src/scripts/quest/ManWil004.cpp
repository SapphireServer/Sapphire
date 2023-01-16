#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManWil004_00570
// Quest Name: Close to Home
// Quest ID: 66106
// Start NPC: 1003988
// End NPC: 1001353

using namespace Sapphire;

class ManWil004 : public Sapphire::ScriptAPI::QuestScript
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
  static constexpr auto Actor1 = 1002279;
  static constexpr auto Actor2 = 1003908; 
  static constexpr auto Actor20 = 1001637;
  static constexpr auto Actor3 = 1001353;
  static constexpr auto Aetheryte0 = 9;
  static constexpr auto BindActor0 = 6229228;
  static constexpr auto Item0 = 2000388;
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
  static constexpr auto Territorytype0 = 130;

  static constexpr auto SEQ_0_ACTOR0 = 0;
  static constexpr auto SEQ_1_ACTOR1 = 1;
  static constexpr auto SEQ_1_ACTOR2 = 2;
  static constexpr auto SEQ_1_ACTOR3 = 3;
  static constexpr auto SEQ_1_ACTOR4 = 4;
  static constexpr auto SEQ_1_ACTOR5 = 5;
  static constexpr auto SEQ_1_ACTOR8 = 8;
  static constexpr auto SEQ_0_ACTOR0_LQ = 50;

public:
  ManWil004() : Sapphire::ScriptAPI::QuestScript( 66106 )
  {
  };

  ~ManWil004()
  {
  };

  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      Scene00000( player );
    }
    else if( actorId == Actor1 )
    {
      Scene00003( player );
    }
    else if( actorId == Actor2 )
    {
      Scene00004( player );
    }
    else if( actorId == Actor3 )
    {
      Scene00008( player );
    }
    else if( actorId == Aetheryte0 )
    {

      eventMgr().eventActionStart( player, 0x050002, 0x13,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 eventMgr().sendEventNotice( player, 0x050002, 0, 1, 0, 0 );
                                 player.registerAetheryte( 2 );
                                 player.setRewardFlag( Common::UnlockEntry::Return );
                                 Scene00051( quest, player );
                               },
                               nullptr, getId() );
    }
  }

private:

  //varIdx refers to the noticeId
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


    auto var_attuned = quest.getUI8AL();
    auto var_class = quest.getUI8BH();
    auto var_trade = quest.getUI8BL();


    if( var_attuned == 1 && var_class == 1 && var_trade == 1 )
    {
      quest.setSeq( SeqFinish );
    }
  }

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_0_ACTOR0, HIDE_HOTBAR, bindSceneReturn( &ManWil004::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
      Scene00050( player );
  }

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR1, 0x0EFB, bindSceneReturn( &ManWil004::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002(player);
  }

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestSceneChain( player, getId(), 51, NONE, bindQuestScene( &ManWil004::Scene00001 ) );
  }

  void Scene00002( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR2, NONE, bindSceneReturn( &ManWil004::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL(1);
    checkQuestCompletion( quest, player, 0 );
  }

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR3, HIDE_HOTBAR, bindSceneReturn( &ManWil004::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL(1);
    checkQuestCompletion( quest, player, 1 );
  }

  void Scene00004( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR4, HIDE_HOTBAR, bindSceneReturn( &ManWil004::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if(result.getResult(0) == 1)
    {
      Scene00005( player );
    } else
    {
      return;
    }
  }

  void Scene00005( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManWil004::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH(0);
    quest.setUI8BH(1);
    checkQuestCompletion( quest, player, 2 );
  }

  void Scene00008( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR8, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManWil004::Scene00008Return ) );

  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  void Scene00050( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_0_ACTOR0_LQ, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManWil004::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // on quest accept
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 ); // receive key item

    // teleport to real Uldah
    player.forceZoneing( Territorytype0 );
  }
};

EXPOSE_SCRIPT( ManWil004 );