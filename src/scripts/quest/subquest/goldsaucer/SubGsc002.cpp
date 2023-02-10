// FFXIVTheMovie.ParserV3.10
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"

using namespace Sapphire;

class SubGsc002 : public Sapphire::ScriptAPI::QuestScript
{
public:
  SubGsc002() : Sapphire::ScriptAPI::QuestScript( 65971 ){}; 
  ~SubGsc002() = default; 

  //SEQ_0, 1 entries
  //SEQ_1, 2 entries
  //SEQ_2, 1 entries
  //SEQ_3, 1 entries
  //SEQ_4, 1 entries
  //SEQ_5, 1 entries
  //SEQ_6, 1 entries
  //SEQ_255, 1 entries

  //ACTOR0 = 1011022
  //ACTOR1 = 1010448
  //ACTOR2 = 1011038
  //ACTOR3 = 1010478
  //ACTOR4 = 1011080
  //ACTOR5 = 1011079
  //ACTOR6 = 1011084
  //BGM0 = 250
  //LOCACTIONTIMELINE001 = 1072
  //LOCCHECKQUEST001 = 66996
  //LOCCHECKQUEST002 = 65625
  //LOCCHECKQUEST003 = 65964
  //LOCENPC001 = 1011586
  //LOCLEVELENPC001 = 5581118
  //LOCLEVELENPC002 = 5581208
  //LOCLEVELENPC003 = 5584143
  //LOCLEVELENPC004 = 5653245
  //LOCLEVELENPC005 = 5581064

  static constexpr auto EVENT_ON_TALK = 0;
  static constexpr auto EVENT_ON_EMOTE = 1;
  static constexpr auto EVENT_ON_BNPC_KILL = 2;
  static constexpr auto EVENT_ON_WITHIN_RANGE = 3;
  static constexpr auto EVENT_ON_ENTER_TERRITORY = 4;
  static constexpr auto EVENT_ON_EVENT_ITEM = 5;
  static constexpr auto EVENT_ON_EOBJ_HIT = 6;
  static constexpr auto EVENT_ON_SAY = 7;

private:
  void onProgress( World::Quest& quest, Entity::Player& player, uint32_t type, uint64_t param1, uint32_t param2, uint32_t param3 )
  {
    switch( quest.getSeq() )
    {
      case 0:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00000( quest, player ); // Scene00000: Normal(QuestOffer, TargetCanMove), id=unknown
        // +Callback Scene00001: Normal(Talk, QuestAccept, TargetCanMove), id=RECEPTIONIDT00434
        break;
      }
      case 1:
      {
        if( param1 == 1010448 ) // ACTOR1 = INFORMATION00435
        {
          if( quest.getUI8AL() != 1 )
          {
            Scene00002( quest, player ); // Scene00002: Normal(Talk, FadeIn, TargetCanMove, ENpcBind), id=INFORMATION00435
          }
          break;
        }
        if( param1 == 1011022 ) // ACTOR0 = RECEPTIONIDT00434
        {
          Scene00003( quest, player ); // Scene00003: Normal(Talk, TargetCanMove), id=RECEPTIONIDT00434
          break;
        }
        break;
      }
      case 2:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00004( quest, player ); // Scene00004: Normal(Talk, TargetCanMove), id=EXCHANGE00435
        break;
      }
      case 3:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00005( quest, player ); // Scene00005: Normal(Talk, FadeIn, TargetCanMove, ENpcBind), id=CARDSHOP00435
        break;
      }
      case 4:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00006( quest, player ); // Scene00006: Normal(Talk, FadeIn, TargetCanMove, ENpcBind), id=GATENPCA00435
        break;
      }
      case 5:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00007( quest, player ); // Scene00007: Normal(Talk, FadeIn, TargetCanMove), id=BUNNY00435
        break;
      }
      case 6:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00008( quest, player ); // Scene00008: Normal(Talk, FadeIn, TargetCanMove), id=GATENPCB00435
        break;
      }
      case 255:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00009( quest, player ); // Scene00009: Normal(Talk, FadeIn, QuestReward, QuestComplete, TargetCanMove), id=INFORMATION00435
        break;
      }
      default:
      {
        playerMgr().sendUrgent( player, "Sequence {} not defined.", quest.getSeq() );
        break;
      }
    }
  }

public:
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    onProgress( quest, player, EVENT_ON_TALK, actorId, 0, 0 );
  }

  void onEmote( World::Quest& quest, uint64_t actorId, uint32_t emoteId, Sapphire::Entity::Player& player ) override
  {
    playerMgr().sendDebug( player, "emote: {}", emoteId );
    onProgress( quest, player, EVENT_ON_EMOTE, actorId, 0, emoteId );
  }

  void onWithinRange( World::Quest& quest, Sapphire::Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    onProgress( quest, player, EVENT_ON_WITHIN_RANGE, static_cast< uint64_t >( param1 ), 0, 0 );
  }

  void onEnterTerritory( World::Quest& quest, Sapphire::Entity::Player& player, uint16_t param1, uint16_t param2 ) override
  {
    onProgress( quest, player, EVENT_ON_ENTER_TERRITORY, static_cast< uint64_t >( param1 ), static_cast< uint32_t >( param2 ), 0 );
  }
  void onEventItem( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId ) override
  {
    onProgress( quest, player, EVENT_ON_EVENT_ITEM, actorId, 0, 0 );
  }
  void onEObjHit( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId ) override
  {
    onProgress( quest, player, EVENT_ON_EOBJ_HIT, actorId, actionId, 0 );
  }
  void onSay( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t sayId ) override
  {
    onProgress( quest, player, EVENT_ON_SAY, actorId, sayId, 0 );
  }

private:
  void checkProgressSeq0( World::Quest& quest, Entity::Player& player )
  {
    quest.setSeq( 1 );
  }
  void checkProgressSeq1( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() == 1 )
    {
      quest.setUI8AL( 0 );
      quest.setBitFlag8( 1, false );
      quest.setSeq( 2 );
    }
  }
  void checkProgressSeq2( World::Quest& quest, Entity::Player& player )
  {
    quest.setSeq( 3 );
  }
  void checkProgressSeq3( World::Quest& quest, Entity::Player& player )
  {
    quest.setSeq( 4 );
  }
  void checkProgressSeq4( World::Quest& quest, Entity::Player& player )
  {
    quest.setSeq( 5 );
  }
  void checkProgressSeq5( World::Quest& quest, Entity::Player& player )
  {
    quest.setSeq( 6 );
  }
  void checkProgressSeq6( World::Quest& quest, Entity::Player& player )
  {
    quest.setSeq( 255 );
  }

  void Scene00000( World::Quest& quest, Entity::Player& player ) //SEQ_0: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00000: Normal(QuestOffer, TargetCanMove), id=unknown" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.numOfResults > 0 && result.getResult( 0 ) == 1 )
      {
        Scene00001( quest, player );
      }
    };
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, callback );
  }
  void Scene00001( World::Quest& quest, Entity::Player& player ) //SEQ_0: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00001: Normal(Talk, QuestAccept, TargetCanMove), id=RECEPTIONIDT00434" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      checkProgressSeq0( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, callback );
  }

  void Scene00002( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR1, UI8AL = 1, Flag8(1)=True(Todo:0)
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00002: Normal(Talk, FadeIn, TargetCanMove, ENpcBind), id=INFORMATION00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      quest.setUI8AL( 1 );
      quest.setBitFlag8( 1, true );
      eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
      checkProgressSeq1( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00003( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR0, <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00003: Normal(Talk, TargetCanMove), id=RECEPTIONIDT00434" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
    };
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, callback );
  }

  void Scene00004( World::Quest& quest, Entity::Player& player ) //SEQ_2: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00004: Normal(Talk, TargetCanMove), id=EXCHANGE00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      checkProgressSeq2( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, callback );
  }

  void Scene00005( World::Quest& quest, Entity::Player& player ) //SEQ_3: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00005: Normal(Talk, FadeIn, TargetCanMove, ENpcBind), id=CARDSHOP00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      checkProgressSeq3( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00006( World::Quest& quest, Entity::Player& player ) //SEQ_4: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00006: Normal(Talk, FadeIn, TargetCanMove, ENpcBind), id=GATENPCA00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      checkProgressSeq4( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 6, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00007( World::Quest& quest, Entity::Player& player ) //SEQ_5: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00007: Normal(Talk, FadeIn, TargetCanMove), id=BUNNY00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      checkProgressSeq5( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00008( World::Quest& quest, Entity::Player& player ) //SEQ_6: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00008: Normal(Talk, FadeIn, TargetCanMove), id=GATENPCB00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      checkProgressSeq6( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 8, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00009( World::Quest& quest, Entity::Player& player ) //SEQ_255: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubGsc002:65971 calling Scene00009: Normal(Talk, FadeIn, QuestReward, QuestComplete, TargetCanMove), id=INFORMATION00435" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.numOfResults > 0 && result.getResult( 0 ) == 1 )
      {
        player.finishQuest( getId(), result.getResult( 1 ) );
      }
    };
    eventMgr().playQuestScene( player, getId(), 9, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
};

EXPOSE_SCRIPT( SubGsc002 );
