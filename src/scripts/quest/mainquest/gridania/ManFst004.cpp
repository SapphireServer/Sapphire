// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManFst004_00124
// Quest Name: Close to Home
// Quest ID: 65660
// Start NPC: 1001140
// End NPC: 1000100

using namespace Sapphire;

class ManFst004 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestBitFlag8
  // GetQuestUI8AL
  // GetQuestUI8BH
  // GetQuestUI8BL
  // GetQuestUI8CH

  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1001140;
  static constexpr auto Actor1 = 2;
  static constexpr auto Actor2 = 1000323;
  static constexpr auto Actor20 = 1000159;
  static constexpr auto Actor3 = 1000768;
  static constexpr auto Actor4 = 1000100;
  static constexpr auto Item0 = 2000120;
  static constexpr auto Poprange0 = 2280858;
  static constexpr auto RewardDesion = 1;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq0Actor0Lq = 50;
  static constexpr auto Seq1Actor0 = 4;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq1Actor1Wait = 51;
  static constexpr auto Seq1Actor2 = 2;
  static constexpr auto Seq1Actor3 = 3;
  static constexpr auto Seq1Actor3Npctradeno = 99;
  static constexpr auto Seq1Actor3Npctradeok = 100;
  static constexpr auto Seq2Actor4 = 5;
  static constexpr auto Territorytype0 = 132;
  static constexpr auto UnlockDesion = 14;

public:
  ManFst004() : Sapphire::ScriptAPI::QuestScript( 65660 )
  {};

  ~ManFst004() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == ManFst004::Actor0 )
    {
      Scene00000( quest, player );
    }
    else if( actorId == ManFst004::Actor1 )
    {
      // starting the Aetheryte eventaction
      // player.eventStart( actorId, 0x050002, 7, 0, 0);
      // starting the eventaction 0x13 ( attuning )
      eventMgr().eventActionStart( player, 0x050002, 0x13,
                                   [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                   {
                                     eventMgr().sendEventNotice( player, 0x050002, 0, 1, 0, 0 );
                                     player.registerAetheryte( 2 );
                                     player.setRewardFlag( Common::UnlockEntry::Return );
                                     Scene00051( quest, player );
                                   },
                                   nullptr, quest.getId() );
    }
    else if( actorId == ManFst004::Actor2 )
    {
      Scene00002( quest, player );
    }
    else if( actorId == ManFst004::Actor3 )
    {
      Scene00003( quest, player );
    }
    else if( actorId == ManFst004::Actor4 )
    {
      Scene00005( quest, player );
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 3 )
    {
      eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 );
    }
    else if( varIdx == 2 )
    {
      eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 );
    }
    else
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
    }

    auto QUEST_VAR_ATTUNE = quest.getUI8AL();
    auto QUEST_VAR_CLASS = quest.getUI8BH();
    auto QUEST_VAR_TRADE = quest.getUI8BL();

    if( QUEST_VAR_ATTUNE == 1 && QUEST_VAR_CLASS == 1 && QUEST_VAR_TRADE == 1 )
    {
      quest.setSeq( SeqFinish );
    }
  }

  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManFst004::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00050( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManFst004::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    checkQuestCompletion( quest, player, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManFst004::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    checkQuestCompletion( quest, player, 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManFst004::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00100( quest, player );
    }
    else
    {
      Scene00099( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManFst004::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().playQuestScene( player, getId(), 4, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst004::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // finish quest
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst004::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // accepting quest "close to home"
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 ); // receive key item
    // event is done, need to teleport to real zone.
    warpMgr().requestMoveTerritoryType( player, Common::WarpType::WARP_TYPE_NORMAL, Territorytype0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, HIDE_HOTBAR, bindSceneReturn( &ManFst004::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00001( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &ManFst004::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00004( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ManFst004::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH( 0 ); // remove key item, since we have just traded it
    quest.setUI8BL( 1 );
    checkQuestCompletion( quest, player, 2 );
  }

};

EXPOSE_SCRIPT( ManFst004 );