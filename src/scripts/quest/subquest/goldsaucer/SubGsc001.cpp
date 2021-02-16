// FFXIVTheMovie.ParserV3.2
// id hint used:
//ACTOR1 = dummy1
//SCENE_2 = dummy1
//SCENE_5 = ELYENORA
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"

using namespace Sapphire;

class SubGsc001 : public Sapphire::ScriptAPI::EventScript
{
public:
  SubGsc001() : Sapphire::ScriptAPI::EventScript( 65970 ){}; 
  ~SubGsc001() = default; 

  //SEQ_0, 2 entries
  //SEQ_255, 3 entries

  //ACTOR0 = 1011565
  //ACTOR1 = 1011566
  //ACTOR2 = 1004433
  //BGM0 = 250
  //ITEM0 = 2001555
  //NCUT0 = 769
  //NCUT1 = 770
  //POPRANGE0 = 5654039
  //SCREENIMAGE0 = 272

private:
  void onProgress( Entity::Player& player, uint64_t param1, uint32_t param2, uint32_t type, uint32_t param3 )
  {
    switch( player.getQuestSeq( getId() ) )
    {
      case 0:
      {
        if( param1 == 1011565 || param2 == 1011565 ) // ACTOR0 = TRADER00434
        {
          Scene00000( player ); // Scene00000: Normal(QuestOffer), id=unknown
          // +Callback Scene00001: Normal(Talk, QuestAccept, TargetCanMove), id=TRADER00434
          break;
        }
        if( param1 == 1011566 || param2 == 1011566 ) // ACTOR1 = dummy1
        {
          Scene00002( player ); // Scene00002: Normal(None), id=dummy1
          break;
        }
        break;
      }
      //seq 255 event item ITEM0 = UI8BH max stack 1
      case 255:
      {
        if( param1 == 1004433 || param2 == 1004433 ) // ACTOR2 = ELYENORA
        {
          Scene00003( player ); // Scene00003: NpcTrade(Talk, TargetCanMove), id=unknown
          // +Callback Scene00004: Normal(Talk, YesNo, TargetCanMove, CanCancel), id=ELYENORA
          // +Callback Scene00005: Normal(CutScene, FadeIn, QuestReward, QuestComplete, AutoFadeIn), id=ELYENORA
          break;
        }
        if( param1 == 1011565 || param2 == 1011565 ) // ACTOR0 = TRADER00434
        {
          Scene00006( player ); // Scene00006: Normal(Talk, TargetCanMove), id=TRADER00434
          break;
        }
        if( param1 == 1011566 || param2 == 1011566 ) // ACTOR1 = unknown
        {
          Scene00007( player ); // Scene00007: Normal(None), id=unknown
          break;
        }
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
    player.updateQuest( getId(), 255 );
    player.setQuestUI8BH( getId(), 1 );
  }

  void Scene00000( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00000: Normal(QuestOffer), id=unknown" );
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
    player.sendDebug( "SubGsc001:65970 calling Scene00001: Normal(Talk, QuestAccept, TargetCanMove), id=TRADER00434" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq0( player );
    };
    player.playScene( getId(), 1, NONE, callback );
  }

  void Scene00002( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00002: Normal(None), id=dummy1" );
  }

  void Scene00003( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00003: NpcTrade(Talk, TargetCanMove), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        Scene00004( player );
      }
    };
    player.playScene( getId(), 3, NONE, callback );
  }
  void Scene00004( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00004: Normal(Talk, YesNo, TargetCanMove, CanCancel), id=ELYENORA" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 == 512 || ( result.param1 > 0 && result.param2 == 1 ) )
      {
        Scene00005( player );
      }
    };
    player.playScene( getId(), 4, NONE, callback );
  }
  void Scene00005( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00005: Normal(CutScene, FadeIn, QuestReward, QuestComplete, AutoFadeIn), id=ELYENORA" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        if( player.giveQuestRewards( getId(), result.param3 ) )
        {
          player.finishQuest( getId() );
          player.eventFinish( getId(), 1 );
          player.setPos( -34.5, 0.64, 100, false );
          player.setRot( -1.58 );
          player.forceZoneing( 144 );
        }
      }
    };
    player.playScene( getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00006( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00006: Normal(Talk, TargetCanMove), id=TRADER00434" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 6, NONE, callback );
  }

  void Scene00007( Entity::Player& player )
  {
    player.sendDebug( "SubGsc001:65970 calling Scene00007: Normal(None), id=unknown" );
  }
};

EXPOSE_SCRIPT( SubGsc001 );
