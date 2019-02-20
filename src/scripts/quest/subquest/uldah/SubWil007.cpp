#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include <ctime>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil007_00167
// Quest Name: With Open Arms
// Quest ID: 65703
// Start NPC: 1007621
// End NPC: 1007621

class SubWil007 :
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
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardGil = 102;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1007621;
  static constexpr auto Actor1 = 1001297;
  static constexpr auto Actor2 = 1001692;
  static constexpr auto Actor3 = 1001693;
  static constexpr auto Actor4 = 1001697;
  static constexpr auto Actor5 = 1001698;
  static constexpr auto FirstQuest = 66130;

public:
  SubWil007() :
    Sapphire::ScriptAPI::EventScript( 65703 )
  {
  };

  ~SubWil007()
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
    if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
    {
      Scene00020( player );
    }
    else if( actor == Actor1 )
    {
      Scene00005( player );
    }
    else if( actor == Actor2 )
    {
      Scene00008( player );
    }
    else if( actor == Actor3 )
    {
      Scene00011( player );
    }
    else if( actor == Actor4 )
    {
      Scene00014( player );
    }
    else if( actor == Actor5 )
    {
      Scene00017( player );
    }
  }

  void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == Actor0 && emoteId == 41 && player.getQuestSeq( getId() ) == Seq1 )
    {
      Scene00003( player );
    }
    else if( actor == Actor1 && emoteId == 41 && player.getQuestSeq( getId() ) == Seq2 )
    {
      Scene00006( player );
    }
    else if( actor == Actor2 && emoteId == 41 && player.getQuestSeq( getId() ) == Seq2 )
    {
      Scene00009( player );
    }
    else if( actor == Actor3 && emoteId == 41 && player.getQuestSeq( getId() ) == Seq2 )
    {
      Scene00012( player );
    }
    else if( actor == Actor4 && emoteId == 41 && player.getQuestSeq( getId() ) == Seq2 )
    {
      Scene00015( player );
    }
    else if( actor == Actor5 && emoteId == 41 && player.getQuestSeq( getId() ) == Seq2 )
    {
      Scene00018( player );
    }
  }

private:

  void checkQuestCompletion( Entity::Player& player )
  {
    auto currentQC = player.getQuestUI8AL( getId() ) + 1;

    if( currentQC >= 5 )
    {
      player.updateQuest( getId(), SeqFinish );
      player.sendQuestMessage( getId(), 1, 2, currentQC, 5 );
    }
    else
    {
      player.setQuestUI8AL( getId(), currentQC );
      player.sendQuestMessage( getId(), 1, 2, currentQC, 5 );
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
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), Seq1 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), Seq2 );
                        player.sendQuestMessage( getId(), 0, 1, 0, 0 );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 7, true );
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    player.playScene( getId(), 7, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00008( Entity::Player& player )
  {
    player.playScene( getId(), 8, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00009( Entity::Player& player )
  {
    player.playScene( getId(), 9, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 6, true );
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
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 5, true );
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

  void Scene00015( Entity::Player& player )
  {
    player.playScene( getId(), 15, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 4, true );
                      } );
  }

  void Scene00016( Entity::Player& player )
  {
    player.playScene( getId(), 16, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00017( Entity::Player& player )
  {
    player.playScene( getId(), 17, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00018( Entity::Player& player )
  {
    player.playScene( getId(), 18, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 3, true );
                      } );
  }

  void Scene00019( Entity::Player& player )
  {
    player.playScene( getId(), 19, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00020( Entity::Player& player )
  {
    player.playScene( getId(), 20, HIDE_HOTBAR,
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

EXPOSE_SCRIPT( SubWil007 );