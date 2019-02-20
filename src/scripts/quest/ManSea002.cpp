#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

// Quest Script: ManSea002_00108
// Quest Name: Close to Home
// Quest ID: 65644
// Start NPC: 1002697
// End NPC: 1000972

using namespace Sapphire;

class ManSea002 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_1 = 1;
  static constexpr auto SEQ_FINISH = 255;


  static constexpr auto ACTOR0 = 1002697;
  static constexpr auto ACTOR1 = 1001217;
  static constexpr auto ACTOR2 = 1000926;
  static constexpr auto ACTOR3 = 1000972;
  static constexpr auto AETHERYTE0 = 8;
  static constexpr auto BIND_ACTOR0 = 6229226;
  static constexpr auto ITEM0 = 2000104;
  static constexpr auto LOC_ACTOR1 = 1001023;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 605;
  static constexpr auto LOC_POS_CAM1 = 4106696;
  static constexpr auto LOC_POS_CAM2 = 4106698;
  static constexpr auto REWARD0 = 1;
  static constexpr auto SCREENIMAGE0 = 14;
  static constexpr auto UNLOCK_DESION = 14;

public:
  ManSea002() :
    Sapphire::ScriptAPI::EventScript( 65644 )
  {
  }

  ~ManSea002()
  {
  };

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR0 )
    {
      Scene00000( player );
    }
    else if( actor == AETHERYTE0 )
    {
      player.eventActionStart( 0x050002, 0x13,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 player.sendQuestMessage( 0x050002, 0, 1, 0, 0 );
                                 player.registerAetheryte( 2 );
                                 player.learnAction( 1 );
                                 Scene00002( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == ACTOR1 )
    {
      Scene00004( player );
    }
    else if( actor == ACTOR2 )
    {
      Scene00006( player );
    }
    else if( actor == ACTOR3 )
    {
      Scene00007( player );
    }
  }

private:

  void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 1 )
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
      player.updateQuest( questId, SEQ_FINISH );
    }
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00001( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), SEQ_1 );
                        player.setQuestUI8CH( getId(), 1 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00003( player );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setQuestUI8BL( getId(), 1 );
                        checkQuestCompletion( player, 0 );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00005( player );
                        }
                        else
                          return;
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, 0, 0,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setQuestUI8CH( getId(), 0 );
                        player.setQuestUI8BH( getId(), 1 );
                        checkQuestCompletion( player, 1 );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setQuestUI8AL( getId(), 1 );
                        checkQuestCompletion( player, 2 );
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    player.playScene( getId(), 7, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, 0, 0,
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
};

EXPOSE_SCRIPT( ManSea002 );