#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil019_00392
// Quest Name: Decisions, Decisions
// Quest ID: 65928
// Start NPC: 1001680
// End NPC: 1001691

class SubWil019 : public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestUI8AL

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardGil = 111;
  static constexpr auto RewardItem = 5539;
  static constexpr auto RewardItemCount = 1;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001680;
  static constexpr auto Actor1 = 1001691;

public:
  SubWil019() :
    Sapphire::ScriptAPI::EventScript( 65928 )
  {
  };

  ~SubWil019()
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
                          if( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubWil019 );