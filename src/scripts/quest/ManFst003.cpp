#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

// Quest Script: ManFst003_00123
// Quest Name: Close to Home
// Quest ID: 65659
// Start NPC: 1001140
// End NPC: 1000100

using namespace Sapphire;

class ManFst003 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestBitFlag8
  // GetQuestUI8AL
  // GetQuestUI8BH
  // GetQuestUI8BL
  // GetQuestUI8CH

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  static constexpr auto RewardGil = 107;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001140;
  static constexpr auto Actor1 = 2;
  static constexpr auto Actor2 = 1000197;
  static constexpr auto Actor20 = 1000159;
  static constexpr auto Actor3 = 1000768;
  static constexpr auto Actor4 = 1000100;
  static constexpr auto BindActor0 = 6229224;
  static constexpr auto Item0 = 2000119;
  static constexpr auto LocActor0 = 1003159;
  static constexpr auto LocMarker01 = 2153091;
  static constexpr auto LocMarker02 = 2153104;
  static constexpr auto LocMarker03 = 2153111;
  static constexpr auto LocMarker04 = 2154539;
  static constexpr auto LocMarker05 = 2154540;
  static constexpr auto LocMarker06 = 2154541;
  static constexpr auto LocMarker07 = 2210446;
  static constexpr auto LocMarker08 = 2210454;
  static constexpr auto LocMarker09 = 2210461;
  static constexpr auto LocMotion0 = 799;
  static constexpr auto Poprange0 = 2280858;
  static constexpr auto RewardDesion = 1;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq0Actor0Lq = 50;
  static constexpr auto Seq1Actor0 = 4;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq1Actor1Wait = 51;
  static constexpr auto Seq1Actor2 = 2;
  static constexpr auto Seq1Actor3 = 3;
  static constexpr auto Seq1Actor3Npctradeno = 99;
  static constexpr auto Seq1Actor3Npctradeok = 100;
  static constexpr auto Seq2Actor4 = 5;
  static constexpr auto Territorytype0 = 132;
  static constexpr auto UnlockDesion = 14;

public:
  ManFst003() :
    Sapphire::ScriptAPI::EventScript( 65659 )
  {
  };

  ~ManFst003()
  {
  };

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == Actor0 )
    {
      Scene00000( player );
    }
    else if( actor == Actor1 )
    {
      player.eventActionStart( 0x050002, 0x13,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 player.sendQuestMessage( 0x050002, 0, 1, 0, 0 );
                                 player.registerAetheryte( 2 );
                                 player.learnAction( 1 );
                                 Scene00051( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Actor2 )
    {
      Scene00002( player );
    }
    else if( actor == Actor3 )
    {
      Scene00003( player );
    }
    else if( actor == Actor4 )
    {
      Scene00005( player );
    }
  }

private:

  void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 3 )
    {
      player.sendQuestMessage( getId(), 1, 0, 0, 0 );
    }
    else if( varIdx == 2 )
    {
      player.sendQuestMessage( getId(), 2, 0, 0, 0 );
    }
    else
    {
      player.sendQuestMessage( getId(), 0, 0, 0, 0 );
    }

    auto questId = getId();

    auto QUEST_VAR_ATTUNE = player.getQuestUI8AL( questId );
    auto QUEST_VAR_CLASS = player.getQuestUI8BH( questId );
    auto QUEST_VAR_TRADE = player.getQuestUI8BL( questId );

    if( QUEST_VAR_ATTUNE == 1 && QUEST_VAR_CLASS == 1 && QUEST_VAR_TRADE == 1 )
    {
      player.updateQuest( questId, SeqFinish );
    }
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00050( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setQuestUI8AL( getId(), 1 );
                        checkQuestCompletion( player, 0 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setQuestUI8BH( getId(), 1 );
                        checkQuestCompletion( player, 3 );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00100( player );
                        }
                        else
                        {
                          Scene00099( player );
                        }
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.playScene( getId(), 4, 0, 0, 0 );
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          if( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  }

  void Scene00050( Entity::Player& player )
  {
    player.playScene( getId(), 50, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), Seq1 );
                        player.setQuestUI8CH( getId(), 1 );
                        player.forceZoneing( 132 );
                      } );
  }

  void Scene00051( Entity::Player& player )
  {
    player.playScene( getId(), 51, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00001( player );
                      } );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00004( player );
                      } );
  }

  void Scene00100( Entity::Player& player )
  {
    player.playScene( getId(), 100, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setQuestUI8CH( getId(), 0 );
                        player.setQuestUI8BL( getId(), 1 );
                        checkQuestCompletion( player, 2 );
                      } );
  }
};

EXPOSE_SCRIPT( ManFst003 );