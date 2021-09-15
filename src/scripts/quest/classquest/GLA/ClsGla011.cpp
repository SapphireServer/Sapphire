// FFXIVTheMovie.ParserV3.3
// fake IsAnnounce table
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"

using namespace Sapphire;

class ClsGla011 : public Sapphire::ScriptAPI::EventScript
{
public:
  ClsGla011() : Sapphire::ScriptAPI::EventScript( 65821 ){}; 
  ~ClsGla011() = default; 

  //SEQ_0, 1 entries
  //SEQ_255, 1 entries

  //ACTOR0 = 1002277
  //ACTOR1 = 1001739
  static constexpr auto CLASSJOB = 1;
  //GEARSETUNLOCK = 1905
  //LOGMESSAGEMONSTERNOTEPAGEUNLOCK = 1010
  //UNLOCKIMAGECLASSGLA = 36

private:
  void onProgress( Entity::Player& player, uint64_t param1, uint32_t param2, uint32_t type, uint32_t param3 )
  {
    switch( player.getQuestSeq( getId() ) )
    {
      case 0:
      {
        Scene00000( player ); // Scene00000: Normal(Talk, QuestOffer, QuestAccept, TargetCanMove), id=LULUTSU
        break;
      }
      case 255:
      {
        Scene00001( player ); // Scene00001: Normal(Talk, YesNo, Message, FadeIn, QuestReward, QuestComplete, TargetCanMove, CanCancel), id=MYLLA
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
  }

  void Scene00000( Entity::Player& player )
  {
    player.sendDebug( "ClsGla011:65821 calling Scene00000: Normal(Talk, QuestOffer, QuestAccept, TargetCanMove), id=LULUTSU" );
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
    player.sendDebug( "ClsGla011:65821 calling Scene00001: Normal(Talk, YesNo, Message, FadeIn, QuestReward, QuestComplete, TargetCanMove, CanCancel), id=MYLLA" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        if( player.giveQuestRewards( getId(), result.param3 ) )
        {
          player.finishQuest( getId() );
          player.setEquippedMannequin( player.getEquippedMannequin() + 1 );
          player.setLevelForClass( 1, static_cast< Common::ClassJob > ( CLASSJOB ) );
        }
      }
    };
    player.playScene( getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
};

EXPOSE_SCRIPT( ClsGla011 );
