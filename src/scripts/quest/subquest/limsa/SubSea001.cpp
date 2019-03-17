#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubSea001_00111
// Quest Name: Making a Name
// Quest ID: 65647
// Start NPC: 1002698
// End NPC: 1003604

class SubSea001 :
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
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardItem = 4551;
  static constexpr auto RewardItemCount = 2;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1002698;
  static constexpr auto Actor1 = 1000969;
  static constexpr auto Actor2 = 1003604;
  static constexpr auto Eobject0 = 2001563;
  static constexpr auto Eobject1 = 2001564;
  static constexpr auto Eobject2 = 2001565;
  static constexpr auto Eobject3 = 2001566;
  static constexpr auto Eobject4 = 2001567;
  static constexpr auto Eobject5 = 2001568;
  static constexpr auto EventActionProcess = 14;
  static constexpr auto Item0 = 2000447;
  static constexpr auto Poprange0 = 4161445;
  static constexpr auto Quest0 = 65644;
  static constexpr auto Quest1 = 65645;
  static constexpr auto Territorytype0 = 129;

public:
  SubSea001() :
    Sapphire::ScriptAPI::EventScript( 65647 )
  {
  };

  ~SubSea001()
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
      Scene00002( player );
    }
    else if( actor == Actor2 )
    {
      Scene00016( player );
    }
      //EOBJECTS CHECK
    else if( actor == Eobject0 )
    {
      player.eventActionStart( getId(), 0x0E,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00003( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject1 )
    {
      player.eventActionStart( getId(), 0x0E,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00005( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject2 )
    {
      player.eventActionStart( getId(), 0x0E,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00007( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject3 )
    {
      player.eventActionStart( getId(), 0x0E,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00009( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject4 )
    {
      player.eventActionStart( getId(), 0x0E,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00011( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject5 )
    {
      player.eventActionStart( getId(), 0x0E,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00013( player );
                               },
                               nullptr, eventId );
    }
  };

private:

  void checkQuestCompletion( Entity::Player& player )
  {
    auto currentCC = player.getQuestUI8BH( getId() );

    player.sendQuestMessage( getId(), 1, 3, currentCC + 1, 6 );

    if( currentCC + 1 >= 6 )
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
                          player.updateQuest( getId(), 1 );
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( player.hasQuest( Quest0 ) || player.hasQuest( Quest1 ) )
                        {
                          if( result.param2 == 1 )
                          {
                            player.updateQuest( getId(), 2 );
                            player.changePosition( 10, 21, 13, -2 );
                            player.forceZoneing( Territorytype0 ); // teleport to real limsa
                          }
                        }
                        else
                          return;
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00004( player );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 1, true );
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00006( player );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 2, true );
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
                        Scene00010( player );
                      } );
  }

  void Scene00010( Entity::Player& player )
  {
    player.playScene( getId(), 10, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 4, true );
                      } );
  }

  void Scene00011( Entity::Player& player )
  {
    player.playScene( getId(), 11, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00012( player );
                      } );
  }

  void Scene00012( Entity::Player& player )
  {
    player.playScene( getId(), 12, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 5, true );
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
                        player.setQuestBitFlag8( getId(), 6, true );
                      } );
  }

  void Scene00015( Entity::Player& player )
  {
    player.playScene( getId(), 15, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.playScene( getId(), 15, 0, 0, 0 );
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
                            player.finishQuest( getId() );
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubSea001 );