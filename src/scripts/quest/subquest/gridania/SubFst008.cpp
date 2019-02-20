#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst008_00032
// Quest Name: A Hard Nut to Crack
// Quest ID: 65568
// Start NPC: 1000372
// End NPC: 1000629

class SubFst008 :
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
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  uint32_t RewardItemOptional[3] = { 2999, 3010, 5824 };
  uint32_t RewardItemOptionalCount[3] = { 1, 1, 1 };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000372;
  static constexpr auto Actor1 = 1000311;
  static constexpr auto Actor2 = 1000629;
  static constexpr auto Item0 = 2000029;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq2Actor2 = 2;
  static constexpr auto Seq2Actor2Npctradeno = 99;
  static constexpr auto Seq2Actor2Npctradeok = 100;

public:
  SubFst008() :
    Sapphire::ScriptAPI::EventScript( 65568 )
  {
  };

  ~SubFst008()
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
      Scene00002( player );
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
                        player.setQuestUI8BH( getId(), 1 );
                        player.updateQuest( getId(), SeqFinish );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
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
                        if( result.param2 == 1 )
                        {
                          if( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.setQuestUI8BH( getId(), 0 );
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst008 );