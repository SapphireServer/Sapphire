#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst015_00042
// Quest Name: Sylphic Gratitude
// Quest ID: 65578
// Start NPC: 1000286
// End NPC: 1000286

class SubFst015 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestBitFlag8
  // GetQuestUI8AL

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardGil = 110;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000286;
  static constexpr auto Eobject0 = 2000020;
  static constexpr auto Eobject1 = 2000021;
  static constexpr auto Eobject2 = 2000022;
  static constexpr auto Eobject3 = 2000023;
  static constexpr auto Eobject4 = 2000024;
  static constexpr auto Eobject5 = 2000025;
  static constexpr auto EventActionSearch = 1;

public:
  SubFst015() :
    Sapphire::ScriptAPI::EventScript( 65578 )
  {
  };

  ~SubFst015()
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
    else if( actor == Actor0 )
    {
      Scene00007( player );
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
                                 Scene00002( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject2 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00003( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject3 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00004( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject4 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00005( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject5 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00006( player );
                               },
                               nullptr, eventId );
    }
  }

private:

  void checkQuestCompletion( Entity::Player& player )
  {
    auto currentCC = player.getQuestUI8AL( getId() );

    player.sendQuestMessage( getId(), 0, 2, currentCC + 1, 6 );

    if( currentCC + 1 >= 6 )
    {
      player.updateQuest( getId(), SeqFinish );
    }
    else
    {
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
                        Scene00100( player );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00098( player );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00096( player );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00094( player );
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00092( player );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00090( player );
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    player.playScene( getId(), 7, HIDE_HOTBAR,
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

  void Scene00089( Entity::Player& player )
  {
    player.playScene( getId(), 89, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00090( Entity::Player& player )
  {
    player.playScene( getId(), 90, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 6, true );
                      } );
  }

  void Scene00091( Entity::Player& player )
  {
    player.playScene( getId(), 91, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00092( Entity::Player& player )
  {
    player.playScene( getId(), 92, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 5, true );
                      } );
  }

  void Scene00093( Entity::Player& player )
  {
    player.playScene( getId(), 93, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00094( Entity::Player& player )
  {
    player.playScene( getId(), 94, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 4, true );
                      } );
  }

  void Scene00095( Entity::Player& player )
  {
    player.playScene( getId(), 95, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00096( Entity::Player& player )
  {
    player.playScene( getId(), 96, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 3, true );
                      } );
  }

  void Scene00097( Entity::Player& player )
  {
    player.playScene( getId(), 97, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00098( Entity::Player& player )
  {
    player.playScene( getId(), 98, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 2, true );
                      } );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00100( Entity::Player& player )
  {
    player.playScene( getId(), 100, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 1, true );
                      } );
  }
};

EXPOSE_SCRIPT( SubFst015 );