#include <Actor/Player.h>
#include <ScriptObject.h>
#include "Event/EventHandler.h"
#include "Manager/EventMgr.h"
#include <Service.h>

// Quest Script: ManFst002_00124
// Quest Name: Close to Home
// Quest ID: 65660
// Start NPC: 1001140
// End NPC: 1000100

using namespace Sapphire;

class ManFst002 : public Sapphire::ScriptAPI::QuestScript
{
private:

  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

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


  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 3 )
      player.sendEventNotice( getId(), 1, 0, 0, 0 );
    else if( varIdx == 2 )
      player.sendEventNotice( getId(), 2, 0, 0, 0 );
    else
      player.sendEventNotice( getId(), 0, 0, 0, 0 );

    auto var_attuned = quest.getUI8AL();
    auto var_class = quest.getUI8BH();
    auto var_trade = quest.getUI8BL();

    if( var_attuned == 1 && var_class == 1 && var_trade == 1 )
      quest.setSeq( SeqFinish );
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_0_ACTOR0, HIDE_HOTBAR, bindSceneReturn( &ManFst002::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
      Scene00050( quest, player );
  }

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR1, 0x0EFB, bindSceneReturn( &ManFst002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    checkQuestCompletion( quest, player, 0 );
  }

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR2, NONE, bindSceneReturn( &ManFst002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    checkQuestCompletion( quest, player, 3 );
  }

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR3, NONE, bindSceneReturn( &ManFst002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00100( quest, player );
    else
      Scene00099( quest, player );
  }

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), SEQ_1_ACTOR0, NONE );
  }

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_2_ACTOR4, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst002::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // finish quest
    {
      if( player.giveQuestRewards( getId(), 0 ) )
        player.finishQuest( getId() );
    }
  }

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_0_ACTOR0_LQ, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst002::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // on quest accept
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 ); // receive key item

    // teleport to real gridania
    player.forceZoneing( TERRITORYTYPE0 );
  }

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestSceneChain( player, getId(), SEQ_1_ACTOR1_WAIT, NONE, bindQuestScene( &ManFst002::Scene00001 ) );
  }

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestSceneChain( player, getId(), SEQ_1_ACTOR3_NPCTRADENO, NONE, bindQuestScene( &ManFst002::Scene00005 ) );
  }

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), SEQ_1_ACTOR3_NPCTRADEOK, 0x0EFB, bindSceneReturn( &ManFst002::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH( 0 ); // remove traded key item
    quest.setUI8BL( 1 );
    checkQuestCompletion( quest, player, 2 );
  }

public:
  ManFst002() : Sapphire::ScriptAPI::QuestScript( 65621 )
  {
  }

  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {

    if( actorId == ACTOR0 )
      Scene00000( quest, player );
    else if( actorId == ACTOR1 )
    {
      // attune
      auto event = [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
      {
        player.sendEventNotice( 0x050002, 0, 1, 0, 0 );
        player.registerAetheryte( 2 );
        player.learnAction( Common::UnlockEntry::Return );

        Scene00051( quest, player );
      };

      eventMgr().eventActionStart( player, 0x050002, 0x13, event, nullptr, 0x050002 );

    }
    else if( actorId == ACTOR2 )
      Scene00002( quest, player );
    else if( actorId == ACTOR3 )
      Scene00003( quest, player );
    else if( actorId == ACTOR4 )
      Scene00005( quest, player );
  }
};

EXPOSE_SCRIPT( ManFst002 );