#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil006_00165
// Quest Name: The Great Gladiator
// Quest ID: 65701
// Start NPC: 1001295
// End NPC: 1001299

class SubWil006 :
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
  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardItem = 5594;
  static constexpr auto RewardItemCount = 10;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001295;
  static constexpr auto Actor1 = 1002280;
  static constexpr auto Actor2 = 1001299;
  static constexpr auto Item0 = 2000201;

public:
  SubWil006() :
    Sapphire::ScriptAPI::EventScript( 65701 )
  {
  };

  ~SubWil006()
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
      Scene00004( player );
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
                          player.setQuestUI8BH( getId(), 1 );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          Scene00002( player );
                        }
                        else
                        {
                          Scene00003( player );
                        }
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), SeqFinish );
                        player.sendQuestMessage( getId(), 0, 2, 0, 0 );
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

EXPOSE_SCRIPT( SubWil006 );