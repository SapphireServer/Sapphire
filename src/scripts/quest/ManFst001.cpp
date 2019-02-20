#include <Actor/Player.h>
#include <ScriptObject.h>
#include "Manager/EventMgr.h"
#include "Event/EventHandler.h"
#include "Framework.h"

// Quest Script: ManFst001_00039
// Quest Name: Coming to Gridania
// Quest ID: 65575
// Start NPC: 1001148
// End NPC: 1001140

using namespace Sapphire;

class ManFst001 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_FINISH = 255;

  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardGil = 103;

  static constexpr auto ACTOR0 = 1001148;
  static constexpr auto ACTOR1 = 1001140;
  static constexpr auto CUT_EVENT = 29;
  static constexpr auto EOBJECT0 = 2001659;
  static constexpr auto EOBJECT1 = 2001660;
  static constexpr auto EOBJECT7 = 2616477;
  static constexpr auto EVENT_ACTION_SEARCH = 1;
  static constexpr auto HOWTO_QUEST_ACCEPT = 12;
  static constexpr auto HOWTO_QUEST_ANNOUNCE = 2;
  static constexpr auto HOWTO_REWARD = 11;
  static constexpr auto HOWTO_TODO = 3;
  static constexpr auto OPENING_EVENT_HANDLER = 1245186;
  static constexpr auto SEQ_2_ACTOR1 = 2;

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // accept quest
      {
        player.setOpeningSequence( 2 );
        Scene00001( player );
      }
    };

    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playSceneChain( getId(), 1, DISABLE_SKIP | HIDE_HOTBAR | SET_BASE, bindScene( &ManFst001::Scene00002 ) );
  }

  void Scene00002( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), SEQ_FINISH );

      player.eventStart( result.actorId, OPENING_EVENT_HANDLER, Event::EventHandler::Nest, 0, 0 );
      player.playScene( OPENING_EVENT_HANDLER, 0x1E, HIDE_HOTBAR | NO_DEFAULT_CAMERA, 0, 0 );
    };

    player.playScene( getId(), 2, 0, 0, 0, callback );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playSceneChain( getId(), 4, FADE_OUT | HIDE_HOTBAR | CONDITION_CUTSCENE | HIDE_UI,
                           bindScene( &ManFst001::Scene00005 ) );
  }

  void Scene00005( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 )
      {
        if( player.giveQuestRewards( getId(), 0 ) )
          player.finishQuest( getId() );
      }
    };

    player.playScene( getId(), 5, INVIS_OTHER_PC, 0, 0, callback );
  }

public:
  ManFst001() :
    Sapphire::ScriptAPI::EventScript( 65575 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR0 )
      Scene00000( player );
    else if( actor == ACTOR1 )
      Scene00004( player );
  }
};

EXPOSE_SCRIPT( ManFst001 );