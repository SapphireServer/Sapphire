#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil004_00153
// Quest Name: Unholy Matrimony
// Quest ID: 65689
// Start NPC: 1001291
// End NPC: 1003896

class SubWil004 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestBitFlag8
  // GetQuestUI8AH
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
  static constexpr auto RewardItemCount = 5;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001291;
  static constexpr auto Actor1 = 1001292;
  static constexpr auto Actor2 = 1003896;
  static constexpr auto Eobject0 = 2000691;
  static constexpr auto Eobject1 = 2000692;
  static constexpr auto Eobject2 = 2000693;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000137;

public:
  SubWil004() :
    Sapphire::ScriptAPI::EventScript( 65689 )
  {
  };

  ~SubWil004()
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
      Scene00001( player );
    }
    else if( actor == Actor2 )
    {
      Scene00008( player );
    }
      //EOBJECTS CHECK
    else if( actor == Eobject0 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00003( player );
                               },
                               nullptr, eventId );
    }
    else if( actor == Eobject1 )
    {
      player.eventActionStart( getId(), 0x01,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00005( player );
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
  }

private:

  void checkQuestCompletion( Entity::Player& player )
  {
    auto currentCC = player.getQuestUI8AL( getId() );
    auto currentQC = player.getQuestUI8BH( getId() );

    player.sendQuestMessage( getId(), 1, 3, currentCC + 1, 3 );

    if( currentCC + 1 >= 3 )
    {
      player.updateQuest( getId(), SeqFinish );
      player.setQuestUI8AH( getId(), currentCC + 1 );
      player.setQuestUI8AL( getId(), currentCC + 1 );
      player.setQuestUI8BH( getId(), 0 );
    }
    else
    {
      player.setQuestUI8AH( getId(), currentCC + 1 );
      player.setQuestUI8AL( getId(), currentCC + 1 );
      player.setQuestUI8BH( getId(), currentQC - 1 );
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
                        player.updateQuest( getId(), Seq2 );
                        player.sendQuestMessage( getId(), 0, 2, 0, 0 );
                        player.setQuestUI8BH( getId(), 3 );
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
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 7, true );
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
                        player.setQuestBitFlag8( getId(), 6, true );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00007( player );
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    player.playScene( getId(), 7, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 5, true );
                      } );
  }

  void Scene00008( Entity::Player& player )
  {
    player.playScene( getId(), 8, HIDE_HOTBAR,
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
                      } );
  }

  void Scene00011( Entity::Player& player )
  {
    player.playScene( getId(), 11, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
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
                      } );
  }

  void Scene00014( Entity::Player& player )
  {
    player.playScene( getId(), 14, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }
};

EXPOSE_SCRIPT( SubWil004 );