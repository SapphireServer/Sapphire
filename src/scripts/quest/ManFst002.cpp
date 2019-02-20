#include <Actor/Player.h>
#include <ScriptObject.h>
#include "Event/EventHandler.h"
#include "Manager/EventMgr.h"
#include "Framework.h"

// Quest Script: ManFst002_00124
// Quest Name: Close to Home
// Quest ID: 65660
// Start NPC: 1001140
// End NPC: 1000100

using namespace Sapphire;

class ManFst002 : public Sapphire::ScriptAPI::EventScript
{
private:

  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_1 = 1;
  static constexpr auto SEQ_2 = 2;
  static constexpr auto SEQ_FINISH = 255;
  //this.SEQ_OFFER = ?;

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  static constexpr auto RewardGil = 107;

  // Entities found in the script data of the quest
  // some of these may be useful
  static constexpr auto ACTOR0 = 1001140;
  static constexpr auto ACTOR1 = 2;
  static constexpr auto ACTOR2 = 1000251;
  static constexpr auto ACTOR20 = 1000159;
  static constexpr auto ACTOR3 = 1000768;
  static constexpr auto ACTOR4 = 1000100;
  static constexpr auto BIND_ACTOR0 = 6229224;
  static constexpr auto HOW_TO_DESION = 13;
  static constexpr auto HOW_TO_MAP_AND_NAVI = 4;
  static constexpr auto ITEM0 = 2000074;
  static constexpr auto LOC_ACTOR0 = 1003159;
  static constexpr auto LOC_MARKER_01 = 2153091;
  static constexpr auto LOC_MARKER_02 = 2153104;
  static constexpr auto LOC_MARKER_03 = 2153111;
  static constexpr auto LOC_MARKER_04 = 2154539;
  static constexpr auto LOC_MARKER_05 = 2154540;
  static constexpr auto LOC_MARKER_06 = 2154541;
  static constexpr auto LOC_MARKER_07 = 2210446;
  static constexpr auto LOC_MARKER_08 = 2210454;
  static constexpr auto LOC_MARKER_09 = 2210461;
  static constexpr auto LOC_MOTION0 = 799;
  static constexpr auto POPRANGE0 = 2280858;
  static constexpr auto REWARD_DESION = 1;
  static constexpr auto SEQ_0_ACTOR0 = 0;
  static constexpr auto SEQ_0_ACTOR0_LQ = 50;
  static constexpr auto SEQ_1_ACTOR0 = 4;
  static constexpr auto SEQ_1_ACTOR1 = 1;
  static constexpr auto SEQ_1_ACTOR1_WAIT = 51;
  static constexpr auto SEQ_1_ACTOR2 = 2;
  static constexpr auto SEQ_1_ACTOR3 = 3;
  static constexpr auto SEQ_1_ACTOR3_NPCTRADENO = 99;
  static constexpr auto SEQ_1_ACTOR3_NPCTRADEOK = 100;
  static constexpr auto SEQ_2_ACTOR4 = 5;
  static constexpr auto TERRITORYTYPE0 = 132;
  static constexpr auto UNLOCK_DESION = 14;


  void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 3 )
      player.sendQuestMessage( getId(), 1, 0, 0, 0 );
    else if( varIdx == 2 )
      player.sendQuestMessage( getId(), 2, 0, 0, 0 );
    else
      player.sendQuestMessage( getId(), 0, 0, 0, 0 );

    auto var_attuned = player.getQuestUI8AL( static_cast< uint16_t >( getId() ) );
    auto var_class = player.getQuestUI8BH( static_cast< uint16_t >( getId() ) );
    auto var_trade = player.getQuestUI8BL( static_cast< uint16_t >( getId() ) );

    if( var_attuned == 1 && var_class == 1 && var_trade == 1 )
      player.updateQuest( getId(), SEQ_FINISH );
  }

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // accept quest
        Scene00050( player );
    };

    player.playScene( getId(), SEQ_0_ACTOR0, HIDE_HOTBAR, 0, 0, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkQuestCompletion( player, 0 );
    };

    player.playScene( getId(), SEQ_1_ACTOR1, 0x0EFB, 0, 0, callback );
  }

  void Scene00002( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BH( getId(), 1 );
      checkQuestCompletion( player, 3 );
    };

    player.playScene( getId(), SEQ_1_ACTOR2, NONE, 0, 0, callback );
  }

  void Scene00003( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 )
        Scene00100( player );
      else
        Scene00099( player );
    };

    player.playScene( getId(), SEQ_1_ACTOR3, NONE, 0, 0, callback );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), SEQ_1_ACTOR0, NONE, 0, 0 );
  }

  void Scene00005( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // finish quest
      {
        if( player.giveQuestRewards( getId(), 0 ) )
          player.finishQuest( getId() );
      }
    };

    player.playScene( getId(), SEQ_2_ACTOR4, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, 0, 0, callback );
  }

  void Scene00050( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      // on quest accept
      player.updateQuest( getId(), SEQ_1 );
      player.setQuestUI8CH( getId(), 1 ); // receive key item

      // teleport to real gridania
      player.forceZoneing( TERRITORYTYPE0 );
    };

    player.playScene( getId(), SEQ_0_ACTOR0_LQ, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, 0, 0, callback );
  }

  void Scene00051( Entity::Player& player )
  {
    player.playSceneChain( getId(), SEQ_1_ACTOR1_WAIT, NONE, bindScene( &ManFst002::Scene00001 ) );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playSceneChain( getId(), SEQ_1_ACTOR3_NPCTRADENO, NONE, bindScene( &ManFst002::Scene00005 ) );
  }

  void Scene00100( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8CH( getId(), 0 ); // remove traded key item
      player.setQuestUI8BL( getId(), 1 );

      checkQuestCompletion( player, 2 );
    };

    player.playScene( getId(), SEQ_1_ACTOR3_NPCTRADEOK, 0x0EFB, 0, 0, callback );
  }

public:
  ManFst002() :
    Sapphire::ScriptAPI::EventScript( 65621 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR0 )
      Scene00000( player );
    else if( actor == ACTOR1 )
    {
      // attune
      auto event = [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
      {
        player.sendQuestMessage( 0x050002, 0, 1, 0, 0 );
        player.registerAetheryte( 2 );
        player.learnAction( 1 );

        Scene00051( player );
      };

      player.eventActionStart( 0x050002, 0x13, event, nullptr, 0x050002 );

    }
    else if( actor == ACTOR2 )
      Scene00002( player );
    else if( actor == ACTOR3 )
      Scene00003( player );
    else if( actor == ACTOR4 )
      Scene00005( player );
  }
};

EXPOSE_SCRIPT( ManFst002 );