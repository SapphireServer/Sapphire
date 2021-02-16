// FFXIVTheMovie.ParserV3.2
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"

using namespace Sapphire;

class SubGsc002 : public Sapphire::ScriptAPI::EventScript
{
public:
  SubGsc002() : Sapphire::ScriptAPI::EventScript( 65971 ){}; 
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

private:
  void onProgress( Entity::Player& player, uint64_t param1, uint32_t param2, uint32_t type, uint32_t param3 )
  {
    switch( player.getQuestSeq( getId() ) )
    {
      case 0:
      {
        Scene00000( player ); // Scene00000: Normal(QuestOffer, TargetCanMove), id=unknown
        // +Callback Scene00001: Normal(Talk, QuestAccept, TargetCanMove), id=RECEPTIONIDT00434
        break;
      }
      case 1:
      {
        if( param1 == 1010448 || param2 == 1010448 ) // ACTOR1 = INFORMATION00435
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00002( player ); // Scene00002: Normal(Talk, FadeIn, TargetCanMove), id=INFORMATION00435
          }
          break;
        }
        if( param1 == 1011022 || param2 == 1011022 ) // ACTOR0 = RECEPTIONIDT00434
        {
          Scene00003( player ); // Scene00003: Normal(Talk, TargetCanMove), id=RECEPTIONIDT00434
          break;
        }
        break;
      }
      case 2:
      {
        Scene00004( player ); // Scene00004: Normal(Talk, TargetCanMove), id=EXCHANGE00435
        break;
      }
      case 3:
      {
        Scene00005( player ); // Scene00005: Normal(Talk, FadeIn, TargetCanMove), id=CARDSHOP00435
        break;
      }
      case 4:
      {
        Scene00006( player ); // Scene00006: Normal(Talk, FadeIn, TargetCanMove), id=GATENPCA00435
        break;
      }
      case 5:
      {
        Scene00007( player ); // Scene00007: Normal(Talk, FadeIn, TargetCanMove), id=BUNNY00435
        break;
      }
      case 6:
      {
        Scene00008( player ); // Scene00008: Normal(Talk, FadeIn, TargetCanMove), id=GATENPCB00435
        break;
      }
      case 255:
      {
        Scene00009( player ); // Scene00009: Normal(Talk, FadeIn, QuestReward, QuestComplete, TargetCanMove), id=INFORMATION00435
        break;
      }
      default:
      {
        player.sendUrgent( "Sequence {} not defined.", player.getQuestSeq( getId() ) );
        break;
      }
    }
  }

public:
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );
    onProgress( player, actorId, actor, 0, 0 );
  }

  void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player ) override
  {
    auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );
    onProgress( player, actorId, actor, 1, emoteId );
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    onProgress( player, npcId, 0, 2, 0 );
  }

  void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    onProgress( player, param1, param1, 3, 0 );
  }

  void onEnterTerritory( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
    onProgress( player, param1, param2, 4, 0 );
  }

private:
  void checkProgressSeq0( Entity::Player& player )
  {
    player.updateQuest( getId(), 1 );
  }
  void checkProgressSeq1( Entity::Player& player )
  {
    if( player.getQuestUI8AL( getId() ) == 1 )
    {
      player.setQuestUI8AL( getId(), 0 );
      player.updateQuest( getId(), 2 );
    }
  }
  void checkProgressSeq2( Entity::Player& player )
  {
    player.updateQuest( getId(), 3 );
  }
  void checkProgressSeq3( Entity::Player& player )
  {
    player.updateQuest( getId(), 4 );
  }
  void checkProgressSeq4( Entity::Player& player )
  {
    player.updateQuest( getId(), 5 );
  }
  void checkProgressSeq5( Entity::Player& player )
  {
    player.updateQuest( getId(), 6 );
  }
  void checkProgressSeq6( Entity::Player& player )
  {
    player.updateQuest( getId(), 255 );
  }

  void Scene00000( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00000: Normal(QuestOffer, TargetCanMove), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        Scene00001( player );
      }
    };
    player.playScene( getId(), 0, NONE, callback );
  }
  void Scene00001( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00001: Normal(Talk, QuestAccept, TargetCanMove), id=RECEPTIONIDT00434" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq0( player );
    };
    player.playScene( getId(), 1, NONE, callback );
  }

  void Scene00002( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00002: Normal(Talk, FadeIn, TargetCanMove), id=INFORMATION00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq1( player );
    };
    player.playScene( getId(), 2, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00003( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00003: Normal(Talk, TargetCanMove), id=RECEPTIONIDT00434" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 3, NONE, callback );
  }

  void Scene00004( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00004: Normal(Talk, TargetCanMove), id=EXCHANGE00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq2( player );
    };
    player.playScene( getId(), 4, NONE, callback );
  }

  void Scene00005( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00005: Normal(Talk, FadeIn, TargetCanMove), id=CARDSHOP00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq3( player );
    };
    player.playScene( getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00006( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00006: Normal(Talk, FadeIn, TargetCanMove), id=GATENPCA00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq4( player );
    };
    player.playScene( getId(), 6, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00007( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00007: Normal(Talk, FadeIn, TargetCanMove), id=BUNNY00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq5( player );
    };
    player.playScene( getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00008( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00008: Normal(Talk, FadeIn, TargetCanMove), id=GATENPCB00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq6( player );
    };
    player.playScene( getId(), 8, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00009( Entity::Player& player )
  {
    player.sendDebug( "SubGsc002:65971 calling Scene00009: Normal(Talk, FadeIn, QuestReward, QuestComplete, TargetCanMove), id=INFORMATION00435" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        if( player.giveQuestRewards( getId(), result.param3 ) )
        {
          player.finishQuest( getId() );
        }
      }
    };
    player.playScene( getId(), 9, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
};

EXPOSE_SCRIPT( SubGsc002 );
