#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst005_00028
// Quest Name: To the Bannock
// Quest ID: 65564
// Start NPC: 1000100
// End NPC: 1000421

class SubFst005 :
  public Sapphire::ScriptAPI::EventScript
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
  static constexpr auto RewardExpFactor = 200;
  static constexpr auto RewardGil = 127;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000100;
  static constexpr auto Actor1 = 1000421;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;

public:
  SubFst005() :
    Sapphire::ScriptAPI::EventScript( 65564 )
  {
  };

  ~SubFst005()
  {
  };

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

    if ( actor == Actor0 )
    {
      Scene00000( player );
    }
    else if ( actor == Actor1 )
    {
      Scene00001( player );
    }
  }

private:

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, 0,
                    [&]( Entity::Player& player, const Event::SceneResult& result )
                    {
                      if ( result.param2 == 1 )
                        player.updateQuest( getId(), SeqFinish );
                    } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, 0,
                    [&]( Entity::Player& player, const Event::SceneResult& result )
                    {
                      if ( result.param2 == 1 )
                      {
                        if ( player.giveQuestRewards( getId(), 0 ) )
                          player.finishQuest( getId() );
                      }
                    } );
  }
};

EXPOSE_SCRIPT( SubFst005 );