#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManSea001_00107
// Quest Name: Coming to Limsa Lominsa
// Quest ID: 65643
// Start NPC: 1001028
// End NPC: 1002697

using namespace Sapphire;

class ManSea001 : public Sapphire::ScriptAPI::QuestScript
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
    eventMgr().playScene( player, getId(), 0, 8192,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                          player.setOpeningSequence( 2 );
                          Scene00001( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playSceneChain( player, getId(), 1, DISABLE_SKIP | HIDE_HOTBAR | SET_BASE, bindScene( &ManSea001::Scene00002 ) );
  }

  void Scene00002( Entity::Player& player )
  {
    auto pQuest = player.getQuest( getId() );
    if( !pQuest )
      return;

    pQuest->setSeq( SEQ_1 );
    eventMgr().playSceneChain( player, getId(), 2, NONE, bindScene( &ManSea001::Scene00003 ) );
  }

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, NONE,
      [&](Entity::Player& player, const Event::SceneResult& result)
                      {
                        eventMgr().eventStart( player, result.actorId, OPENING_EVENT_HANDLER, Event::EventHandler::Nest, 0, 0 );
                        eventMgr().playScene( player, OPENING_EVENT_HANDLER, 0x1E, HIDE_HOTBAR | NO_DEFAULT_CAMERA, { 1 } );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 4, NONE );
  }

  void Scene00005( Entity::Player& player )
  {
    eventMgr().playSceneChain( player, getId(), 5, HIDE_HOTBAR, bindScene( &ManSea001::Scene00006 ) );
  }

  void Scene00006( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 6, INVIS_OTHER_PC,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                          auto pQuest = player.getQuest( getId() );
                          if( !pQuest )
                            return;
                          pQuest->setSeq( SEQ_FINISH );
                          //player.prepareZoning( player.getTerritoryTypeId(), true, 1, 0 );
                          player.changePosition( 9, 40, 14, 2 );
                        }
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 7, NONE );
  }

  void Scene00008( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 8, NONE );
  }

  void Scene00009( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 9, NONE );
  }

  void Scene00010( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 10, NONE );
  }

  void Scene00011( Entity::Player& player )
  {
    eventMgr().playSceneChain( player, getId(), 11, 0x2c02, bindScene( &ManSea001::Scene00012 ) );
  }

  void Scene00012( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 12, INVIS_OTHER_PC,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 ) // finish quest
                        {
                          player.finishQuest( getId(), result.getResult( 1 ) );
                        }
                      } );
  }

  void Scene00013( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 13, NONE );
  }

public:
  ManSea001() : Sapphire::ScriptAPI::QuestScript( 65643 )
  {
  }

  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == ACTOR0 )
      Scene00000( player );
    else if( actorId == ACTOR1 )
      Scene00005( player );
    else if( actorId == ACTOR2 )
      Scene00011( player );
  }
};

EXPOSE_SCRIPT( ManSea001 );