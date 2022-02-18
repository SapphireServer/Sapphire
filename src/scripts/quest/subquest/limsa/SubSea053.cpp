// FFXIVTheMovie.ParserV3.9
// param used:
//ID_ACTOR1 = 4298896548
//ID_ACTOR2 = 4298896549
//ID_ACTOR3 = 4298896550
//ID_ACTOR4 = 4298896551
//ID_ACTOR5 = 4298896552
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"
#include "Territory/Territory.h"
#include <Manager/WarpMgr.h>

using namespace Sapphire;

class SubSea053 : public Sapphire::ScriptAPI::QuestScript
{
public:
  SubSea053() : Sapphire::ScriptAPI::QuestScript( 66001 ){}; 
  ~SubSea053() = default; 

  //SEQ_0, 1 entries
  //SEQ_1, 5 entries
  //SEQ_255, 1 entries

  //ACTOR0 = 1002626
  //ACTOR1 = 1002635
  //ACTOR2 = 1002636
  //ACTOR3 = 1002637
  //ACTOR4 = 1002638
  //ACTOR5 = 1002639
  //QSTACCEPTCHECK = 66000

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
        if( type != EVENT_ON_BNPC_KILL ) Scene00000( quest, player ); // Scene00000: Normal(Talk, QuestOffer, QuestAccept, TargetCanMove, SystemTalk, CanCancel), id=STAELWYRN
        break;
      }
      case 1:
      {
        if( param1 == 1002635 || param1 == 4298896548 ) // ACTOR1 = SEVRIN
        {
          if( !quest.getBitFlag8( 1 ) )
          {
            Scene00001( quest, player ); // Scene00001: Normal(Talk, NpcDespawn, TargetCanMove), id=SEVRIN
          }
          break;
        }
        if( param1 == 1002636 || param1 == 4298896549 ) // ACTOR2 = AYLMER
        {
          if( !quest.getBitFlag8( 2 ) )
          {
            Scene00002( quest, player ); // Scene00002: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=AYLMER
          }
          break;
        }
        if( param1 == 1002637 || param1 == 4298896550 ) // ACTOR3 = EYRIMHUS
        {
          if( !quest.getBitFlag8( 3 ) )
          {
            Scene00003( quest, player ); // Scene00003: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=EYRIMHUS
          }
          break;
        }
        if( param1 == 1002638 || param1 == 4298896551 ) // ACTOR4 = SOZAIRARZAI
        {
          if( !quest.getBitFlag8( 4 ) )
          {
            Scene00004( quest, player ); // Scene00004: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=SOZAIRARZAI
          }
          break;
        }
        if( param1 == 1002639 || param1 == 4298896552 ) // ACTOR5 = WAUTER
        {
          if( !quest.getBitFlag8( 5 ) )
          {
            Scene00005( quest, player ); // Scene00005: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=WAUTER
          }
          break;
        }
        break;
      }
      case 255:
      {
        if( type != EVENT_ON_BNPC_KILL ) Scene00006( quest, player ); // Scene00006: Normal(Talk, QuestReward, QuestComplete, TargetCanMove), id=STAELWYRN
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

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player ) override
  {
    onProgress( quest, player, EVENT_ON_BNPC_KILL, static_cast< uint64_t >( nameId ), entityId, 0 );
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
    if( quest.getUI8AL() == 5 )
    {
      quest.setUI8AL( 0 );
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
      quest.setBitFlag8( 4, false );
      quest.setBitFlag8( 5, false );
      quest.setSeq( 255 );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player ) //SEQ_0: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00000: Normal(Talk, QuestOffer, QuestAccept, TargetCanMove, SystemTalk, CanCancel), id=STAELWYRN" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.numOfResults > 0 && result.getResult( 0 ) == 1 )
      {
        checkProgressSeq0( quest, player );
      }
    };
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, callback );
  }

  void Scene00001( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR1, UI8AL = 5, Flag8(1)=True(Todo:0)
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00001: Normal(Talk, NpcDespawn, TargetCanMove), id=SEVRIN" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      quest.setUI8AL( quest.getUI8AL() + 1 );
      quest.setBitFlag8( 1, true );
      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
      checkProgressSeq1( quest, player );
    };
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, callback );
  }

  void Scene00002( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR2, UI8AL = 5, Flag8(2)=True(Todo:0)
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00002: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=AYLMER" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.errorCode == 0 )
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        quest.setBitFlag8( 2, true );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
        checkProgressSeq1( quest, player );
      }
    };
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, callback );
  }

  void Scene00003( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR3, UI8AL = 5, Flag8(3)=True(Todo:0)
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00003: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=EYRIMHUS" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.errorCode == 0 )
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        quest.setBitFlag8( 3, true );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
        checkProgressSeq1( quest, player );
      }
    };
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, callback );
  }

  void Scene00004( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR4, UI8AL = 5, Flag8(4)=True(Todo:0)
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00004: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=SOZAIRARZAI" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.errorCode == 0 )
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        quest.setBitFlag8( 4, true );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
        checkProgressSeq1( quest, player );
      }
    };
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, callback );
  }

  void Scene00005( World::Quest& quest, Entity::Player& player ) //SEQ_1: ACTOR5, UI8AL = 5, Flag8(5)=True(Todo:0)
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00005: Normal(Talk, NpcDespawn, TargetCanMove, Menu), id=WAUTER" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.errorCode == 0 )
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        quest.setBitFlag8( 5, true );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
        checkProgressSeq1( quest, player );
      }
    };
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, callback );
  }

  void Scene00006( World::Quest& quest, Entity::Player& player ) //SEQ_255: , <No Var>, <No Flag>
  {
    playerMgr().sendDebug( player, "SubSea053:66001 calling Scene00006: Normal(Talk, QuestReward, QuestComplete, TargetCanMove), id=STAELWYRN" );
    auto callback = [ & ]( World::Quest& quest, Entity::Player& player , const Event::SceneResult& result )
    {
      if( result.numOfResults > 0 && result.getResult( 0 ) == 1 )
      {
        player.finishQuest( getId(), result.getResult( 1 ) );
      }
    };
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, callback );
  }
};

EXPOSE_SCRIPT( SubSea053 );
