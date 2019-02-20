#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

// Quest Script: ManSea001_00107
// Quest Name: Coming to Limsa Lominsa
// Quest ID: 65643
// Start NPC: 1001028
// End NPC: 1002697

using namespace Sapphire;

class ManSea001 :
  public Sapphire::ScriptAPI::EventScript
{
private:

  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_1 = 1;
  static constexpr auto SEQ_FINISH = 255;

  static constexpr auto ACTOR0 = 1001028;
  static constexpr auto ACTOR1 = 1002732;
  static constexpr auto ACTOR2 = 1002697;
  static constexpr auto CUT_EVENT = 202;
  static constexpr auto EOBJECT0 = 2001679;
  static constexpr auto EOBJECT1 = 2001680;
  static constexpr auto EVENT_ACTION_SEARCH = 1;
  static constexpr auto LOC_ACTOR0 = 1002732;
  static constexpr auto LOC_POS_ACTOR0 = 4107186;
  static constexpr auto OPENING_EVENT_HANDLER = 1245185;
  static constexpr auto POPRANGE0 = 4127803;
  static constexpr auto TERRITORYTYPE0 = 181;

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, 8192,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          player.setOpeningSequence( 2 );
                          Scene00001( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playSceneChain( getId(), 1, DISABLE_SKIP | HIDE_HOTBAR | SET_BASE, bindScene( &ManSea001::Scene00002 ) );
  }

  void Scene00002( Entity::Player& player )
  {
    player.updateQuest( getId(), SEQ_1 );
    player.playSceneChain( getId(), 2, NONE, bindScene( &ManSea001::Scene00003 ) );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, NONE,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.eventStart( result.actorId, OPENING_EVENT_HANDLER, Event::EventHandler::Nest, 0, 0 );
                        player.playScene( OPENING_EVENT_HANDLER, 0x1E, HIDE_HOTBAR | NO_DEFAULT_CAMERA, 1, 0 );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, NONE, 0, 0 );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playSceneChain( getId(), 5, HIDE_HOTBAR, bindScene( &ManSea001::Scene00006 ) );
  }

  void Scene00006( Entity::Player& player )
  {
    player.playScene( getId(), 6, INVIS_OTHER_PC,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          player.updateQuest( getId(), SEQ_FINISH );
                          player.prepareZoning( player.getZoneId(), true, 1, 0 );
                          player.changePosition( 9, 40, 14, 2 );
                        }
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    player.playScene( getId(), 7, NONE, 0, 0 );
  }

  void Scene00008( Entity::Player& player )
  {
    player.playScene( getId(), 8, NONE, 0, 0 );
  }

  void Scene00009( Entity::Player& player )
  {
    player.playScene( getId(), 9, NONE, 0, 0 );
  }

  void Scene00010( Entity::Player& player )
  {
    player.playScene( getId(), 10, NONE, 0, 0 );
  }

  void Scene00011( Entity::Player& player )
  {
    player.playSceneChain( getId(), 11, 0x2c02, 0, 0, bindScene( &ManSea001::Scene00012 ) );
  }

  void Scene00012( Entity::Player& player )
  {
    player.playScene( getId(), 12, INVIS_OTHER_PC,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 ) // finish quest
                        {
                          if( player.giveQuestRewards( getId(), 0 ) )
                            player.finishQuest( getId() );
                        }
                      } );
  }

  void Scene00013( Entity::Player& player )
  {
    player.playScene( getId(), 13, NONE, 0, 0 );
  }

public:
  ManSea001() :
    Sapphire::ScriptAPI::EventScript( 65643 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR0 )
      Scene00000( player );
    else if( actor == ACTOR1 )
      Scene00005( player );
    else if( actor == ACTOR2 )
      Scene00011( player );
  }
};

EXPOSE_SCRIPT( ManSea001 );