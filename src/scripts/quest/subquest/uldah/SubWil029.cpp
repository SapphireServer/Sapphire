#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil029_00390
// Quest Name: Catch Your Breath
// Quest ID: 65926
// Start NPC: 1001313
// End NPC: 1001992

class SubWil029 :
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
  uint16_t RewardItemOptional[3] = { 2999, 3010, 5824 };
  uint16_t RewardItemOptionalCount[3] = { 1, 1, 1 };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001313;
  static constexpr auto Actor1 = 1001390;
  static constexpr auto Actor2 = 1001992;
  static constexpr auto Item0 = 2000410;

public:
  SubWil029() :
    Sapphire::ScriptAPI::EventScript( 65926 )
  {
  };

  ~SubWil029()
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
                        player.updateQuest( getId(), SeqFinish );
                        player.setQuestUI8BH( getId(), 1 );
                        player.sendQuestMessage( getId(), 0, 2, 0, 0 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00003( player );
                        }
                        else
                        {
                          Scene00004( player );
                        }
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
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

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }
};

EXPOSE_SCRIPT( SubWil029 );