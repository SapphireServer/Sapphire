#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubSea012_00122
// Quest Name: Glory Days
// Quest ID: 65658
// Start NPC: 1003601
// End NPC: 1000972

class SubSea012 :
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
    SeqFinish = 255,
  };

  // Quest rewards 
  static constexpr auto RewardExpFactor = 100;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003601;
  static constexpr auto Actor1 = 1001024;
  static constexpr auto Actor2 = 1000972;
  static constexpr auto Enemy0 = 563;
  static constexpr auto Item0 = 2000454;

public:
  SubSea012() :
    Sapphire::ScriptAPI::EventScript( 65658 )
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
      Scene00003( player );
    }
   }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    if( npcId != Enemy0 )
       return;

    auto currentKC = player.getQuestUI8AL( getId() ) + 1;
    player.setQuestUI8BH( getId(), currentKC );
    player.setQuestUI8AL( getId(), currentKC );
    
    if( currentKC >= 4 )
      player.updateQuest( getId(), SeqFinish );
    else
       player.sendQuestMessage( getId(), 1, 2, currentKC, 4 );
  }

private:

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 )
        player.updateQuest( getId(), 1 );
    });
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, nullptr );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), 2 );
    });
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 )
        Scene00004( player );
    });
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 )
      {
        if( player.giveQuestRewards( getId(), 0 ) )
        {
          player.finishQuest( getId() );
        }
      }
    });
  }

};

EXPOSE_SCRIPT( SubSea012 );