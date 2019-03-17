#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil018_00396
// Quest Name: No Lady Is an Island
// Quest ID: 65932
// Start NPC: 1001675
// End NPC: 1001675

class SubWil018 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestBitFlag8
  // GetQuestUI8AL
  // GetQuestUI8BH

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardGil = 102;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001675;
  static constexpr auto Eobject0 = 2000695;
  static constexpr auto Eobject1 = 2000696;
  static constexpr auto Eobject2 = 2000697;
  static constexpr auto Eobject3 = 2001089;
  static constexpr auto Eobject4 = 2001090;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000198;

public:
  SubWil018() :
    Sapphire::ScriptAPI::EventScript( 65932 )
  {
  };

  ~SubWil018()
  {
  };

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == Actor0 && !player.hasQuest( getId() ) )
    {
      Scene00000( player );
    }
    if( actor == Actor0 )
    {
      Scene00016( player );
    }
      //EOBJECTS CHECK
    else if( actor == Eobject0 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00001( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject1 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00004( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject2 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00007( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject3 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00010( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject4 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00013( player );
                               },
                               nullptr, eventId );
    }
  }

private:

  void checkQuestCompletion( Entity::Player& player )
  {
    auto currentCC = player.getQuestUI8AL( getId() );

    player.sendQuestMessage( getId(), 0, 3, currentCC + 1, 5 );

    if( currentCC + 1 >= 5 )
    {
      player.updateQuest( getId(), SeqFinish );
      player.setQuestUI8BH( getId(), currentCC + 1 );
      player.setQuestUI8AL( getId(), currentCC + 1 );
    }
    else
    {
      player.setQuestUI8BH( getId(), currentCC + 1 );
      player.setQuestUI8AL( getId(), currentCC + 1 );
    }
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          player.updateQuest( getId(), Seq1 );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00002( player );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 1, true );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00005( player );
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 2, true );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    player.playScene( getId(), 7, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00008( player );
                      } );
  }

  void Scene00008( Entity::Player& player )
  {
    player.playScene( getId(), 8, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 3, true );
                      } );
  }

  void Scene00009( Entity::Player& player )
  {
    player.playScene( getId(), 9, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00010( Entity::Player& player )
  {
    player.playScene( getId(), 10, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00011( player );
                      } );
  }

  void Scene00011( Entity::Player& player )
  {
    player.playScene( getId(), 11, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 4, true );
                      } );
  }

  void Scene00012( Entity::Player& player )
  {
    player.playScene( getId(), 12, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00013( Entity::Player& player )
  {
    player.playScene( getId(), 13, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00014( player );
                      } );
  }

  void Scene00014( Entity::Player& player )
  {
    player.playScene( getId(), 14, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 5, true );
                      } );
  }

  void Scene00015( Entity::Player& player )
  {
    player.playScene( getId(), 15, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00016( Entity::Player& player )
  {
    player.playScene( getId(), 16, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00017( player );
                        }
                        else
                        {
                          Scene00018( player );
                        }
                      } );
  }

  void Scene00017( Entity::Player& player )
  {
    player.playScene( getId(), 17, HIDE_HOTBAR,
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

  void Scene00018( Entity::Player& player )
  {
    player.playScene( getId(), 18, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }
};

EXPOSE_SCRIPT( SubWil018 );