#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst030_00173
// Quest Name: The Nose Knows
// Quest ID: 65709
// Start NPC: 1000632
// End NPC: 1000632

class SubFst030 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestUI8AL
  // GetQuestUI8BH

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  static constexpr auto RewardItem = 4551;
  static constexpr auto RewardItemCount = 10;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000632;
  static constexpr auto Actor1 = 1000784;
  static constexpr auto Actor2 = 1000764;
  static constexpr auto Eobject0 = 2000146;
  static constexpr auto EventActionGatherShort = 6;
  static constexpr auto Item0 = 2000140;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq2Eobject0 = 2;
  static constexpr auto Seq2Eobject0Eventactionno = 99;
  static constexpr auto Seq2Eobject0Eventactionok = 100;
  static constexpr auto Seq3Actor2 = 3;
  static constexpr auto Seq3Actor2Npctradeno = 97;
  static constexpr auto Seq3Actor2Npctradeok = 98;
  static constexpr auto Seq4Actor0 = 4;

public:
  SubFst030() :
    Sapphire::ScriptAPI::EventScript( 65709 )
  {
  };

  ~SubFst030()
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
    else if( actor == Actor1 )
    {
      Scene00001( player );
    }
    else if( actor == Actor2 )
    {
      Scene00003( player );
    }
    else if( actor == Actor0 )
    {
      Scene00004( player );
    }
      // EOBJECT
    else if( actor == Eobject0 )
    {
      player.eventActionStart( getId(), 0x06,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00002( player );
                               },
                               nullptr, eventId );
    }
  }

private:

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
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00100( player );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00098( player );
                        }
                        else
                          Scene00097( player );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
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

  void Scene00097( Entity::Player& player )
  {
    player.playScene( getId(), 97, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.playScene( getId(), 97, 0, 0, 0 );
                      } );
  }

  void Scene00098( Entity::Player& player )
  {
    player.playScene( getId(), 98, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), SeqFinish );
                        player.sendQuestMessage( getId(), 2, 2, 0, 0 );
                      } );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.playScene( getId(), 99, 0, 0, 0 );
                      } );
  }

  void Scene00100( Entity::Player& player )
  {
    player.playScene( getId(), 100, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), 3 );
                        player.sendQuestMessage( getId(), 1, 2, 0, 0 );
                        player.setQuestUI8FL( getId(), 1 );
                        player.setQuestUI8BH( getId(), 1 );
                      } );
  }
};

EXPOSE_SCRIPT( SubFst030 );