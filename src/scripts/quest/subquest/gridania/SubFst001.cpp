#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst001_00024
// Quest Name: Coarse Correspondence
// Quest ID: 65560
// Start NPC: 1000206
// End NPC: 1000233

class SubFst001 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_FINISH = 255;
  static constexpr auto ACTOR0 = 1000206;
  static constexpr auto ACTOR1 = 1000233;
  static constexpr auto ITEM0 = 2000079;
  static constexpr auto SEQ_0_ACTOR0 = 0;
  static constexpr auto SEQ_1_ACTOR1 = 1;
  static constexpr auto SEQ_1_ACTOR1_NPCTRADENO = 99;
  static constexpr auto SEQ_1_ACTOR1_NPCTRADEOK = 100;

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // accept quest
      {
        player.setQuestUI8AL( getId(), 1 );
        player.setQuestUI8BH( getId(), 1 );
        player.updateQuest( getId(), SEQ_FINISH );
      }
    };

    player.playScene( getId(), 0, NONE, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, NONE );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, NONE );
  }

  void Scene00100( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // accept quest
      {
        if( player.giveQuestRewards( getId(), 0 ) )
          player.finishQuest( getId() );
      }
    };

    player.playScene( getId(), 100, NONE, callback );
  }


public:
  SubFst001() :
    Sapphire::ScriptAPI::EventScript( 65560 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR0 )
    {
      if( !player.hasQuest( getId() ) )
        Scene00000( player );
      else
        Scene00001( player );
    }
    else if( actor == ACTOR1 )
    {
      if( !player.hasQuest( getId() ) )
        Scene00099( player );
      else
        Scene00100( player );
    }
  }
};

EXPOSE_SCRIPT( SubFst001 );