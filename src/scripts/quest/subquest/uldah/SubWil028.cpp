#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil028_00389
// Quest Name: Fantastic Voyage
// Quest ID: 65925
// Start NPC: 1001678
// End NPC: 1001497

class SubWil028 :
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
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  static constexpr auto RewardGil = 122;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001678;
  static constexpr auto Actor1 = 1001497;
  static constexpr auto Item0 = 2000241;

public:
  SubWil028() :
    Sapphire::ScriptAPI::EventScript( 65925 )
  {
  };

  ~SubWil028()
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
  }

private:

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          player.updateQuest( getId(), SeqFinish );
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
                        if( result.param2 == 1 )
                        {
                          if( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }
};

EXPOSE_SCRIPT( SubWil028 );