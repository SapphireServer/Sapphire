// FFXIVTheMovie.ParserV3.3
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"

using namespace Sapphire;

class ClsGla020 : public Sapphire::ScriptAPI::EventScript
{
public:
  ClsGla020() : Sapphire::ScriptAPI::EventScript( 65789 ){}; 
  ~ClsGla020() = default; 

  //SEQ_0, 1 entries
  //SEQ_1, 1 entries
  //SEQ_2, 3 entries
  //SEQ_255, 1 entries

  //ACTOR0 = 1002277
  //ACTOR1 = 1001739
  //ENEMY0 = 351
  //ENEMY1 = 385
  //ENEMY2 = 205
  //LOGMESSAGEMONSTERNOTEPAGEUNLOCK = 1010
  //UNLOCKIMAGEMONSTERNOTE = 32

private:
  void onProgress( Entity::Player& player, uint64_t param1, uint32_t param2, uint32_t type, uint32_t param3 )
  {
    switch( player.getQuestSeq( getId() ) )
    {
      case 0:
      {
        Scene00000( player ); // Scene00000: Normal(Talk, YesNo, QuestOffer, QuestAccept, TargetCanMove), id=LULUTSU
        break;
      }
      case 1:
      {
        Scene00001( player ); // Scene00001: Normal(Talk, YesNo, FadeIn, TargetCanMove, CanCancel), id=MYLLA
        break;
      }
      case 2:
      {
        if( param1 == 351 || param2 == 351 ) // ENEMY0 = unknown
        {
          if( player.getQuestUI8AL( getId() ) != 3 )
          {
            player.setQuestUI8AL( getId(), player.getQuestUI8AL( getId() ) + 1 );
            checkProgressSeq2( player );
          }
          break;
        }
        if( param1 == 385 || param2 == 385 ) // ENEMY1 = unknown
        {
          if( player.getQuestUI8BH( getId() ) != 3 )
          {
            player.setQuestUI8BH( getId(), player.getQuestUI8BH( getId() ) + 1 );
            checkProgressSeq2( player );
          }
          break;
        }
        if( param1 == 205 || param2 == 205 ) // ENEMY2 = unknown
        {
          if( player.getQuestUI8BL( getId() ) != 3 )
          {
            Scene00002( player ); // Scene00002: Normal(None), id=unknown
          }
          break;
        }
        break;
      }
      case 255:
      {
        Scene00005( player ); // Scene00005: Normal(Talk, Message, QuestReward, QuestComplete, TargetCanMove, SystemTalk), id=MYLLA
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
    player.updateQuest( getId(), 2 );
  }
  void checkProgressSeq2( Entity::Player& player )
  {
    if( player.getQuestUI8AL( getId() ) == 3 )
      if( player.getQuestUI8BH( getId() ) == 3 )
        if( player.getQuestUI8BL( getId() ) == 3 )
        {
          player.setQuestUI8AL( getId(), 0 );
          player.setQuestUI8BH( getId(), 0 );
          player.setQuestUI8BL( getId(), 0 );
          player.updateQuest( getId(), 255 );
        }
  }

  void Scene00000( Entity::Player& player )
  {
    player.sendDebug( "ClsGla020:65789 calling Scene00000: Normal(Talk, YesNo, QuestOffer, QuestAccept, TargetCanMove), id=LULUTSU" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        checkProgressSeq0( player );
      }
    };
    player.playScene( getId(), 0, HIDE_UI, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    player.sendDebug( "ClsGla020:65789 calling Scene00001: Normal(Talk, YesNo, FadeIn, TargetCanMove, CanCancel), id=MYLLA" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 == 512 || ( result.param1 > 0 && result.param2 == 1 ) )
      {
        checkProgressSeq1( player );
      }
    };
    player.playScene( getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }



  void Scene00002( Entity::Player& player )
  {
    player.sendDebug( "ClsGla020:65789 calling Scene00002: Normal(None), id=unknown" );
    player.setQuestUI8BL( getId(), player.getQuestUI8BL( getId() ) + 1 );
    checkProgressSeq2( player );
  }

  void Scene00005( Entity::Player& player )
  {
    player.sendDebug( "ClsGla020:65789 calling Scene00005: Normal(Talk, Message, QuestReward, QuestComplete, TargetCanMove, SystemTalk), id=MYLLA" );
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
    player.playScene( getId(), 5, HIDE_UI, callback );
  }
};

EXPOSE_SCRIPT( ClsGla020 );
