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
  static constexpr auto Seq0Actor0Lq = 50;
  static constexpr auto Territorytype0 = 130;

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
                                 player.sendEventNotice( 0x050002, 0, 1, 0, 0 );
                                 player.registerAetheryte( 2 );
                                 player.learnAction( Common::UnlockEntry::Return );
                                 Scene00001( player );
                               },
                               nullptr, getId() );
    }
  }

private:

  void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 1 )
    {
      player.sendEventNotice( getId(), 1, 0, 0, 0 );
    }
    else if( varIdx == 2 )
    {
      player.sendEventNotice( getId(), 2, 0, 0, 0 );
    }
    else
    {
      player.sendEventNotice( getId(), 0, 0, 0, 0 );
    }

    auto pQuest = player.getQuest( getId() );
    if( !pQuest )
      return;

    auto QUEST_VAR_ATTUNE = pQuest->getUI8AL();
    auto QUEST_VAR_CLASS = pQuest->getUI8BH();
    auto QUEST_VAR_TRADE = pQuest->getUI8BL();

    if( QUEST_VAR_ATTUNE == 1 && QUEST_VAR_CLASS == 1 && QUEST_VAR_TRADE == 1 )
    {
      pQuest->setSeq( SeqFinish );
    }
  }

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 ) // accept quest
                        {
                          Scene00050( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00002( player );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 2, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        auto pQuest = player.getQuest( getId() );
                        if( !pQuest )
                          return;

                        pQuest->setUI8BL( 1 );
                        checkQuestCompletion( player, 0 );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        auto pQuest = player.getQuest( getId() );
                        if( !pQuest )
                          return;

                        pQuest->setUI8AL( 1 );
                        checkQuestCompletion( player, 1 );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                          Scene00005( player );
                        }
                        else
                          return;
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        auto pQuest = player.getQuest( getId() );
                        if( !pQuest )
                          return;

                        pQuest->setUI8CH( 0 );
                        pQuest->setUI8BH( 1 );
                        checkQuestCompletion( player, 2 );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 7, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00008( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 8, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                            player.finishQuest( getId(), result.getResult( 1 ) );
                        }
                      } );
  }

  void Scene00050( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 50, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        auto pQuest = player.getQuest( getId() );
                        if( !pQuest )
                          return;
                        // on quest accept
                        pQuest->setSeq( Seq1 );
                        pQuest->setUI8CH( 1 ); // receive key item

                        // teleport to real ul'dah
                        player.forceZoneing( 130 );
                      } );
  }
};

EXPOSE_SCRIPT( ManWil004 );