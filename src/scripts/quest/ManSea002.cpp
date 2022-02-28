#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManSea002_00108
// Quest Name: Close to Home
// Quest ID: 65644
// Start NPC: 1002697
// End NPC: 1000972

using namespace Sapphire;

class ManSea002 : public Sapphire::ScriptAPI::QuestScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_1 = 1;
  static constexpr auto SEQ_FINISH = 255;


  static constexpr auto ACTOR0 = 1002697;
  static constexpr auto ACTOR1 = 1001217;
  static constexpr auto ACTOR2 = 1000926;
  static constexpr auto ACTOR3 = 1000972;
  static constexpr auto AETHERYTE0 = 8;
  static constexpr auto BIND_ACTOR0 = 6229226;
  static constexpr auto ITEM0 = 2000104;
  static constexpr auto LOC_ACTOR1 = 1001023;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 605;
  static constexpr auto LOC_POS_CAM1 = 4106696;
  static constexpr auto LOC_POS_CAM2 = 4106698;
  static constexpr auto REWARD0 = 1;
  static constexpr auto SCREENIMAGE0 = 14;
  static constexpr auto UNLOCK_DESION = 14;

public:
  ManSea002() :
    Sapphire::ScriptAPI::QuestScript( 65644 )
  {
  }

  ~ManSea002()
  {
  };

  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == ACTOR0 )
    {
      Scene00000( player );
    }
    else if( actorId == AETHERYTE0 )
    {
      eventMgr().eventActionStart( player, 0x050002, 0x13,
                               [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 eventMgr().sendEventNotice( player, 0x050002, 0, 1, 0, 0 );
                                 player.registerAetheryte( 2 );
                                 player.setRewardFlag( Common::UnlockEntry::Return );
                                 Scene00002( player );
                               },
                               nullptr, getId() );
    }
    else if( actorId == ACTOR1 )
    {
      Scene00004( player );
    }
    else if( actorId == ACTOR2 )
    {
      Scene00006( player );
    }
    else if( actorId == ACTOR3 )
    {
      Scene00007( player );
    }
  }

private:

  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
  {
    if( varIdx == 1 )
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
      quest.setSeq( SEQ_FINISH );
    }
  }

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                          Scene00001( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        quest.setSeq( SEQ_1 );
                        quest.setUI8CH( 1 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00003( player );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        quest.setUI8BL( 1 );
                        checkQuestCompletion( quest, player, 0 );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                          Scene00005( player );
                        }
                        else
                          return;
                      } );
  }

  void Scene00005( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        quest.setUI8CH( 0 );
                        quest.setUI8BH( 1 );
                        checkQuestCompletion( quest, player, 1 );
                      } );
  }

  void Scene00006( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        quest.setUI8AL( 1 );
                        checkQuestCompletion( quest, player, 2 );
                      } );
  }

  void Scene00007( Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                      [ & ]( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.getResult( 0 ) == 1 )
                        {
                          player.finishQuest( getId(), result.getResult( 1 ) );
                        }
                      } );
  }
};

EXPOSE_SCRIPT( ManSea002 );