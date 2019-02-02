#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst002_00025
// Quest Name: Quarrels with Squirrels
// Quest ID: 65561
// Start NPC: 1000263
// End NPC: 1000263

class SubFst002 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_1 = 1;
  static constexpr auto SEQ_2 = 2;
  static constexpr auto SEQ_FINISH = 255;
  static constexpr auto ACTOR0 = 1000263;
  static constexpr auto ENEMY0 = 37;
  static constexpr auto SEQ_0_ACTOR0 = 0;
  static constexpr auto SEQ_2_ACTOR0 = 1;

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // accept quest
      {
        player.updateQuest( getId(), SEQ_1 );
      }
    };

    player.playScene( getId(), 0, NONE, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // finish quest
      {
        if( player.giveQuestRewards( getId(), 0 ) )
          player.finishQuest( getId() );
      }
    };

    player.playScene( getId(), 1, NONE, callback );
  }

public:
  SubFst002() :
    Sapphire::ScriptAPI::EventScript( 65561 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR0 && !player.hasQuest( getId() ) )
      Scene00000( player );
    else if( actor == ACTOR0 && player.getQuestSeq( getId() ) == SEQ_FINISH )
      Scene00001( player );
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    if( npcId != ENEMY0 )
      return;

    auto currentKC = player.getQuestUI8AL( getId() ) + 1;

    if( currentKC >= 6 )
      player.updateQuest( getId(), SEQ_FINISH );
    else
    {
      player.setQuestUI8AL( getId(), currentKC );
      player.sendQuestMessage( getId(), 0, 2, currentKC, 6 );
    }
  }
};
