// FFXIVTheMovie.ParserV3.2
// id hint used:
//ACTOR1 = CEREMONYSHOP01578
//_ACTOR1 SET!!
//SCENE_100 REMOVED!!
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"
#include "Network/CommonActorControl.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

using namespace Sapphire;

class SubCts999 : public Sapphire::ScriptAPI::EventScript
{
public:
  SubCts999() : Sapphire::ScriptAPI::EventScript( 67114 ){}; 
  ~SubCts999() = default; 

  //SEQ_0, 1 entries
  //SEQ_1, 2 entries
  //SEQ_2, 2 entries
  //SEQ_3, 3 entries
  //SEQ_4, 3 entries
  //SEQ_5, 5 entries
  //SEQ_6, 5 entries
  //SEQ_7, 5 entries
  //SEQ_8, 4 entries
  //SEQ_9, 3 entries
  //SEQ_10, 2 entries
  //SEQ_11, 5 entries
  //SEQ_12, 6 entries
  //SEQ_255, 1 entries

  //ACTOR0 = 1009761
  //ACTOR1 = 1009762
  //ACTOR2 = 1002280
  //ACTOR3 = 1009763
  //ACTOR4 = 1010146
  //ACTOR5 = 5010000
  //ACTOR6 = 1009764
  //BINDACTOR1 = 4982903
  //CUTSCENESTYLE1 = 671
  //CUTSCENESTYLE21 = 666
  //CUTSCENESTYLE22 = 667
  //CUTSCENESTYLE23 = 668
  //EOBJECT0 = 2004588
  //EOBJECT1 = 2004589
  //EOBJECT10 = 2004598
  //EOBJECT11 = 2004599
  //EOBJECT2 = 2004590
  //EOBJECT3 = 2004591
  //EOBJECT4 = 2004592
  //EOBJECT5 = 2004593
  //EOBJECT6 = 2004594
  //EOBJECT7 = 2004595
  //EOBJECT8 = 2004596
  //EOBJECT9 = 2004597
  //INSTANCEDUNGEON0 = 65000
  //ITEM0 = 2001353
  //ITEM1 = 2001473
  //ITEMBALLOON = 9505
  //LCUTBGM1 = 98
  //LCUTCAMERABASE = 1010402
  //LCUTCAMPOSGLD1 = 2617105
  //LCUTPOSCAM1 = 5419810
  //LCUTPOSCAM2 = 5419811
  //LCUTPOSCAM3 = 5448857
  //LOCALEMOTE1 = 3757
  //NESTEVENTHANDLERSHOP = 262486
  //NESTEVENTHANDLERWARP = 131176
  //POPRANGE0 = 5039523
  //POPRANGE1 = 5038252
  //PUBLICCONTENT0 = 1
  //RESERVE0 = 0
  //REWARD0 = 229
  //REWARDWEDDINGBEAUTYSALON = 228
  //RITEM0 = 7005
  //RITEM1 = 8697
  //SCREENIMAGEACCEPTED = 260
  //SCREENIMAGECOMPLETE = 261
  //TERRITORYTYPE0 = 393
  //TERRITORYTYPE1 = 392

private:
  void onProgress( Entity::Player& player, uint64_t param1, uint32_t param2, uint32_t type, uint32_t param3 )
  {
    switch( player.getQuestSeq( getId() ) )
    {
      case 0:
      {
        Scene00000( player ); // Scene00000: Normal(Talk, QuestOffer, TargetCanMove, Menu, SystemTalk, CanCancel), id=CLARIBEL
        // +Callback Scene00001: Normal(Talk, FadeIn, QuestAccept, TargetCanMove, SystemTalk), id=CLARIBEL
        break;
      }
      case 1:
      {
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00002( player ); // Scene00002: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00003( player ); // Scene00003: Normal(Talk, TargetCanMove, SystemTalk), id=CLARIBEL
          break;
        }
        break;
      }
      case 2:
      {
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00004( player ); // Scene00004: Normal(Talk, TargetCanMove), id=CLARIBEL
          }
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00005( player ); // Scene00005: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 3 event item ITEM0 = UI8BH max stack 1
      case 3:
      {
        if( param1 == 1002280 || param2 == 1002280 ) // ACTOR2 = JEMIME
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00006( player ); // Scene00006: NpcTrade(Talk, TargetCanMove), id=unknown
            // +Callback Scene00007: Normal(Talk, FadeIn, TargetCanMove, Menu), id=JEMIME
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00008( player ); // Scene00008: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00009( player ); // Scene00009: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 4 event item ITEM0 = UI8BH max stack 1
      case 4:
      {
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00010( player ); // Scene00010: NpcTrade(Talk, TargetCanMove), id=unknown
            // +Callback Scene00011: Normal(Talk, FadeIn, TargetCanMove, SystemTalk), id=CLARIBEL
          }
          break;
        }
        if( param1 == 1002280 || param2 == 1002280 ) // ACTOR2 = JEMIME
        {
          Scene00012( player ); // Scene00012: Normal(Talk, TargetCanMove), id=JEMIME
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00013( player ); // Scene00013: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 5 event item ITEM0 = UI8CH max stack 1
      case 5:
      {
        if( param1 == 2004588 || param2 == 2004588 ) // EOBJECT0 = unknown
        {
          if( player.getQuestUI8BL( getId() ) != 1 )
          {
            Scene00014( player ); // Scene00014: Normal(SystemTalk), id=unknown
            // +Callback Scene00015: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00016: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004589 || param2 == 2004589 ) // EOBJECT1 = unknown
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00017( player ); // Scene00017: Normal(SystemTalk), id=unknown
            // +Callback Scene00018: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00019: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004590 || param2 == 2004590 ) // EOBJECT2 = unknown
        {
          if( player.getQuestUI8BH( getId() ) != 1 )
          {
            Scene00020( player ); // Scene00020: Normal(SystemTalk), id=unknown
            // +Callback Scene00021: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00022: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00023( player ); // Scene00023: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00024( player ); // Scene00024: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 6 event item ITEM0 = UI8CH max stack 1
      case 6:
      {
        if( param1 == 2004591 || param2 == 2004591 ) // EOBJECT3 = unknown
        {
          if( player.getQuestUI8BL( getId() ) != 1 )
          {
            Scene00025( player ); // Scene00025: Normal(SystemTalk), id=unknown
            // +Callback Scene00026: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00027: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004592 || param2 == 2004592 ) // EOBJECT4 = unknown
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00028( player ); // Scene00028: Normal(SystemTalk), id=unknown
            // +Callback Scene00029: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00030: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004593 || param2 == 2004593 ) // EOBJECT5 = unknown
        {
          if( player.getQuestUI8BH( getId() ) != 1 )
          {
            Scene00031( player ); // Scene00031: Normal(SystemTalk), id=unknown
            // +Callback Scene00032: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00033: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00034( player ); // Scene00034: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00035( player ); // Scene00035: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 7 event item ITEM0 = UI8CH max stack 1
      case 7:
      {
        if( param1 == 2004594 || param2 == 2004594 ) // EOBJECT6 = unknown
        {
          if( player.getQuestUI8BL( getId() ) != 1 )
          {
            Scene00036( player ); // Scene00036: Normal(SystemTalk), id=unknown
            // +Callback Scene00037: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00038: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004595 || param2 == 2004595 ) // EOBJECT7 = unknown
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00039( player ); // Scene00039: Normal(SystemTalk), id=unknown
            // +Callback Scene00040: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00041: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004596 || param2 == 2004596 ) // EOBJECT8 = unknown
        {
          if( player.getQuestUI8BH( getId() ) != 1 )
          {
            Scene00042( player ); // Scene00042: Normal(SystemTalk), id=unknown
            // +Callback Scene00043: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00044: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00045( player ); // Scene00045: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00046( player ); // Scene00046: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 8 event item ITEM0 = UI8BL max stack 1
      case 8:
      {
        if( param1 == 2004597 || param2 == 2004597 ) // EOBJECT9 = unknown
        {
          if( player.getQuestUI8BH( getId() ) != 1 )
          {
            Scene00047( player ); // Scene00047: Normal(SystemTalk), id=unknown
            // +Callback Scene00048: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00049: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 2004598 || param2 == 2004598 ) // EOBJECT10 = unknown
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00050( player ); // Scene00050: Normal(SystemTalk), id=unknown
            // +Callback Scene00051: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00052: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00053( player ); // Scene00053: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00054( player ); // Scene00054: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 9 event item ITEM0 = UI8BH max stack 1
      //seq 9 event item ITEM1 = UI8BL max stack 1
      case 9:
      {
        if( param1 == 2004599 || param2 == 2004599 ) // EOBJECT11 = unknown
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00055( player ); // Scene00055: Normal(SystemTalk), id=unknown
            // +Callback Scene00056: Normal(FadeIn, SystemTalk), id=unknown
            // +Callback Scene00057: Normal(SystemTalk), id=unknown
          }
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00058( player ); // Scene00058: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00059( player ); // Scene00059: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      //seq 10 event item ITEM1 = UI8BH max stack 1
      case 10:
      {
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          if( player.getQuestUI8AL( getId() ) != 1 )
          {
            Scene00060( player ); // Scene00060: NpcTrade(Talk, TargetCanMove), id=unknown
            // +Callback Scene00061: Normal(Talk, FadeIn, TargetCanMove), id=CLARIBEL
          }
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00062( player ); // Scene00062: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        break;
      }
      case 11:
      {
        if( param1 == 1009763 || param2 == 1009763 ) // ACTOR3 = RAITMEAUX
        {
          Scene00063( player ); // Scene00063: Normal(Talk, TargetCanMove, SystemTalk), id=RAITMEAUX
          break;
        }
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00064( player ); // Scene00064: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1010146 || param2 == 1010146 ) // ACTOR4 = CEREMONYGUIDE01578
        {
          Scene00065( player ); // Scene00065: Normal(Talk, YesNo, TargetCanMove), id=CEREMONYGUIDE01578
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00066( player ); // Scene00066: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        if( type == 4 ) // BASE_ID_TERRITORY_TYPE = unknown
        {
          player.queuePacket( Sapphire::Network::Packets::Server::makeActorControlSelf( getId(), Sapphire::Network::ActorControl::ActorControlType::CeremonyDecoration, player.getQuestUI8FH( getId() ), player.getQuestUI8FL( getId() ), 0, 0 ) );
          Scene00067( player ); // Scene00067: Normal(SetWeddingFestivalParam), id=unknown
          break;
        }
        break;
      }
      case 12:
      {
        if( param1 == 1009761 || param2 == 1009761 ) // ACTOR0 = CLARIBEL
        {
          Scene00068( player ); // Scene00068: Normal(Talk, TargetCanMove), id=CLARIBEL
          break;
        }
        if( param1 == 1009763 || param2 == 1009763 ) // ACTOR3 = RAITMEAUX
        {
          Scene00069( player ); // Scene00069: Normal(Talk, CutScene, FadeIn, TargetCanMove, SystemTalk), id=RAITMEAUX
          break;
        }
        if( param1 == 1009764 || param2 == 1009764 ) // ACTOR6 = ETOINELLE
        {
          Scene00070( player ); // Scene00070: Normal(Talk, YesNo, TargetCanMove, SystemTalk), id=ETOINELLE
          break;
        }
        if( param1 == 1010146 || param2 == 1010146 ) // ACTOR4 = CEREMONYGUIDE01578
        {
          Scene00071( player ); // Scene00071: Normal(Talk, YesNo, TargetCanMove), id=CEREMONYGUIDE01578
          break;
        }
        if( param1 == 1009762 || param2 == 1009762 ) // ACTOR1 = CEREMONYSHOP01578
        {
          Scene00072( player ); // Scene00072: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578
          break;
        }
        if( type == 4 ) // BASE_ID_TERRITORY_TYPE = unknown
        {
          player.queuePacket( Sapphire::Network::Packets::Server::makeActorControlSelf( getId(), Sapphire::Network::ActorControl::ActorControlType::CeremonyDecoration, player.getQuestUI8FH( getId() ), player.getQuestUI8FL( getId() ), 0, 0 ) );
          Scene00073( player ); // Scene00073: Normal(FadeIn, SetWeddingFestivalParam), id=unknown
          break;
        }
        break;
      }
      case 255:
      {
        Scene00074( player ); // Scene00074: Normal(Talk, QuestReward, QuestComplete, TargetCanMove, SystemTalk), id=CLARIBEL
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

  void onSaveData( Sapphire::Entity::Player& player, const Common::EventSaveData& data ) override
  {
    if( data.scene == 69 )
    {
      player.setQuestUI8AH( getId(), data.params[0] );
      player.setQuestUI8AL( getId(), data.params[1] );
      player.setQuestUI8BH( getId(), data.params[2] );
      player.setQuestUI8BL( getId(), data.params[3] );
      player.setQuestUI8CH( getId(), data.params[4] );
      player.setQuestUI8CL( getId(), data.params[5] );
      player.setQuestUI8DH( getId(), data.params[6] );
      player.setQuestUI8DL( getId(), data.params[7] );

      // retail does not save these two values here, we borrow them since they are unused.
      player.setQuestUI8FH( getId(), data.params[8] );
      player.setQuestUI8FL( getId(), data.params[9] );
      player.sendDebug( "Ceremony settings saved." );
    }
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
    if( player.getQuestUI8AL( getId() ) == 1 )
    {
      player.setQuestUI8AL( getId(), 0 );
      player.updateQuest( getId(), 3 );
      player.setQuestUI8BH( getId(), 1 );
    }
  }
  void checkProgressSeq3( Entity::Player& player )
  {
    if( player.getQuestUI8AL( getId() ) == 1 )
    {
      player.setQuestUI8AL( getId(), 0 );
      player.updateQuest( getId(), 4 );
    }
  }
  void checkProgressSeq4( Entity::Player& player )
  {
    if( player.getQuestUI8AL( getId() ) == 1 )
    {
      player.setQuestUI8AL( getId(), 0 );
      player.setQuestUI8BH( getId(), 0 );
      player.updateQuest( getId(), 5 );
    }
  }
  void checkProgressSeq5( Entity::Player& player )
  {
    if( player.getQuestUI8BL( getId() ) == 1 )
      if( player.getQuestUI8AL( getId() ) == 1 )
        if( player.getQuestUI8BH( getId() ) == 1 )
        {
          player.setQuestUI8BL( getId(), 0 );
          player.setQuestUI8AL( getId(), 0 );
          player.setQuestUI8BH( getId(), 0 );
          player.updateQuest( getId(), 6 );
        }
  }
  void checkProgressSeq6( Entity::Player& player )
  {
    if( player.getQuestUI8BL( getId() ) == 1 )
      if( player.getQuestUI8AL( getId() ) == 1 )
        if( player.getQuestUI8BH( getId() ) == 1 )
        {
          player.setQuestUI8BL( getId(), 0 );
          player.setQuestUI8AL( getId(), 0 );
          player.setQuestUI8BH( getId(), 0 );
          player.updateQuest( getId(), 7 );
        }
  }
  void checkProgressSeq7( Entity::Player& player )
  {
    if( player.getQuestUI8BL( getId() ) == 1 )
      if( player.getQuestUI8AL( getId() ) == 1 )
        if( player.getQuestUI8BH( getId() ) == 1 )
        {
          player.setQuestUI8BL( getId(), 0 );
          player.setQuestUI8AL( getId(), 0 );
          player.setQuestUI8BH( getId(), 0 );
          player.setQuestUI8CH( getId(), 0 );
          player.updateQuest( getId(), 8 );
        }
  }
  void checkProgressSeq8( Entity::Player& player )
  {
    if( player.getQuestUI8BH( getId() ) == 1 )
      if( player.getQuestUI8AL( getId() ) == 1 )
      {
        player.setQuestUI8BH( getId(), 0 );
        player.setQuestUI8AL( getId(), 0 );
        player.setQuestUI8BL( getId(), 0 );
        player.updateQuest( getId(), 9 );
      }
  }
  void checkProgressSeq9( Entity::Player& player )
  {
    if( player.getQuestUI8AL( getId() ) == 1 )
    {
      player.setQuestUI8AL( getId(), 0 );
      player.setQuestUI8BH( getId(), 0 );
      player.setQuestUI8BL( getId(), 0 );
      player.updateQuest( getId(), 10 );
      player.setQuestUI8BH( getId(), 1 );
    }
  }
  void checkProgressSeq10( Entity::Player& player )
  {
    if( player.getQuestUI8AL( getId() ) == 1 )
    {
      player.setQuestUI8AL( getId(), 0 );
      player.setQuestUI8BH( getId(), 0 );
      player.updateQuest( getId(), 11 );
    }
  }
  void checkProgressSeq11( Entity::Player& player )
  {
    player.updateQuest( getId(), 12 );
  }
  void checkProgressSeq12( Entity::Player& player )
  {
    player.updateQuest( getId(), 255 );
  }

  void Scene00000( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00000: Normal(Talk, QuestOffer, TargetCanMove, Menu, SystemTalk, CanCancel), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.sendUrgent( "force accepting quest..." );
      //if( result.param1 > 0 && result.param2 == 1 )
      {
        Scene00001( player );
      }
    };
    player.playScene( getId(), 0, NONE, callback );
  }
  void Scene00001( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00001: Normal(Talk, FadeIn, QuestAccept, TargetCanMove, SystemTalk), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq0( player );
    };
    player.playScene( getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00002( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00002: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq1( player );
    };
    player.playScene( getId(), 2, NONE, callback );
  }

  void Scene00003( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00003: Normal(Talk, TargetCanMove, SystemTalk), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 3, NONE, callback );
  }

  void Scene00004( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00004: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq2( player );
    };
    player.playScene( getId(), 4, NONE, callback );
  }

  void Scene00005( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00005: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 5, NONE, callback );
  }

  void Scene00006( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00006: NpcTrade(Talk, TargetCanMove), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        Scene00007( player );
      }
    };
    player.playScene( getId(), 6, NONE, callback );
  }
  void Scene00007( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00007: Normal(Talk, FadeIn, TargetCanMove, Menu), id=JEMIME" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      //if( result.param1 == 512 )
      {
        player.setQuestUI8AL( getId(), 1 );
        checkProgressSeq3( player );
      }
    };
    player.playScene( getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00008( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00008: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 8, NONE, callback );
  }

  void Scene00009( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00009: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 9, NONE, callback );
  }

  void Scene00010( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00010: NpcTrade(Talk, TargetCanMove), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        Scene00011( player );
      }
    };
    player.playScene( getId(), 10, NONE, callback );
  }
  void Scene00011( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00011: Normal(Talk, FadeIn, TargetCanMove, SystemTalk), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq4( player );
    };
    player.playScene( getId(), 11, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00012( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00012: Normal(Talk, TargetCanMove), id=JEMIME" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 12, NONE, callback );
  }

  void Scene00013( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00013: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 13, NONE, callback );
  }

  void Scene00014( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00014: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00015( player );
    };
    player.playScene( getId(), 14, NONE, callback );
  }
  void Scene00015( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00015: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00016( player );
    };
    player.playScene( getId(), 15, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00016( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00016: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BL( getId(), 1 );
      checkProgressSeq5( player );
    };
    player.playScene( getId(), 16, NONE, callback );
  }

  void Scene00017( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00017: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00018( player );
    };
    player.playScene( getId(), 17, NONE, callback );
  }
  void Scene00018( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00018: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00019( player );
    };
    player.playScene( getId(), 18, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00019( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00019: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq5( player );
    };
    player.playScene( getId(), 19, NONE, callback );
  }

  void Scene00020( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00020: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00021( player );
    };
    player.playScene( getId(), 20, NONE, callback );
  }
  void Scene00021( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00021: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00022( player );
    };
    player.playScene( getId(), 21, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00022( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00022: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BH( getId(), 1 );
      checkProgressSeq5( player );
    };
    player.playScene( getId(), 22, NONE, callback );
  }

  void Scene00023( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00023: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 23, NONE, callback );
  }

  void Scene00024( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00024: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 24, NONE, callback );
  }

  void Scene00025( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00025: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00026( player );
    };
    player.playScene( getId(), 25, NONE, callback );
  }
  void Scene00026( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00026: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00027( player );
    };
    player.playScene( getId(), 26, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00027( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00027: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BL( getId(), 1 );
      checkProgressSeq6( player );
    };
    player.playScene( getId(), 27, NONE, callback );
  }

  void Scene00028( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00028: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00029( player );
    };
    player.playScene( getId(), 28, NONE, callback );
  }
  void Scene00029( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00029: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00030( player );
    };
    player.playScene( getId(), 29, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00030( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00030: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq6( player );
    };
    player.playScene( getId(), 30, NONE, callback );
  }

  void Scene00031( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00031: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00032( player );
    };
    player.playScene( getId(), 31, NONE, callback );
  }
  void Scene00032( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00032: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00033( player );
    };
    player.playScene( getId(), 32, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00033( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00033: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BH( getId(), 1 );
      checkProgressSeq6( player );
    };
    player.playScene( getId(), 33, NONE, callback );
  }

  void Scene00034( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00034: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 34, NONE, callback );
  }

  void Scene00035( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00035: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 35, NONE, callback );
  }

  void Scene00036( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00036: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00037( player );
    };
    player.playScene( getId(), 36, NONE, callback );
  }
  void Scene00037( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00037: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00038( player );
    };
    player.playScene( getId(), 37, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00038( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00038: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BL( getId(), 1 );
      checkProgressSeq7( player );
    };
    player.playScene( getId(), 38, NONE, callback );
  }

  void Scene00039( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00039: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00040( player );
    };
    player.playScene( getId(), 39, NONE, callback );
  }
  void Scene00040( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00040: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00041( player );
    };
    player.playScene( getId(), 40, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00041( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00041: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq7( player );
    };
    player.playScene( getId(), 41, NONE, callback );
  }

  void Scene00042( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00042: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00043( player );
    };
    player.playScene( getId(), 42, NONE, callback );
  }
  void Scene00043( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00043: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00044( player );
    };
    player.playScene( getId(), 43, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00044( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00044: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BH( getId(), 1 );
      checkProgressSeq7( player );
    };
    player.playScene( getId(), 44, NONE, callback );
  }

  void Scene00045( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00045: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 45, NONE, callback );
  }

  void Scene00046( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00046: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 46, NONE, callback );
  }

  void Scene00047( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00047: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00048( player );
    };
    player.playScene( getId(), 47, NONE, callback );
  }
  void Scene00048( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00048: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00049( player );
    };
    player.playScene( getId(), 48, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00049( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00049: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8BH( getId(), 1 );
      checkProgressSeq8( player );
    };
    player.playScene( getId(), 49, NONE, callback );
  }

  void Scene00050( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00050: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00051( player );
    };
    player.playScene( getId(), 50, NONE, callback );
  }
  void Scene00051( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00051: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00052( player );
    };
    player.playScene( getId(), 51, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00052( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00052: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq8( player );
    };
    player.playScene( getId(), 52, NONE, callback );
  }

  void Scene00053( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00053: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 53, NONE, callback );
  }

  void Scene00054( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00054: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 54, NONE, callback );
  }

  void Scene00055( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00055: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00056( player );
    };
    player.playScene( getId(), 55, NONE, callback );
  }
  void Scene00056( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00056: Normal(FadeIn, SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00057( player );
    };
    player.playScene( getId(), 56, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }
  void Scene00057( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00057: Normal(SystemTalk), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq9( player );
    };
    player.playScene( getId(), 57, NONE, callback );
  }

  void Scene00058( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00058: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 58, NONE, callback );
  }

  void Scene00059( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00059: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 59, NONE, callback );
  }

  void Scene00060( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00060: NpcTrade(Talk, TargetCanMove), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        Scene00061( player );
      }
    };
    player.playScene( getId(), 60, NONE, callback );
  }
  void Scene00061( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00061: Normal(Talk, FadeIn, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.setQuestUI8AL( getId(), 1 );
      checkProgressSeq10( player );
    };
    player.playScene( getId(), 61, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, callback );
  }

  void Scene00062( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00062: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 62, NONE, callback );
  }

  void Scene00063( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00063: Normal(Talk, TargetCanMove, SystemTalk), id=RAITMEAUX" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 63, NONE, callback );
  }

  void Scene00064( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00064: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 64, NONE, callback );
  }

  void Scene00065( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00065: Normal(Talk, YesNo, TargetCanMove), id=CEREMONYGUIDE01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        uint8_t plan = 3; // standard = 1, golden = 2, platinum = 3
        player.setQuestUI8AH( getId(), 1 );
        switch( plan )
        {
          case 1:
            player.setQuestUI8AL( getId(), 1 );
            break;
          case 2:
            player.setQuestUI8AL( getId(), 2 );
            break;
          case 3:
            player.setQuestUI8AL( getId(), 5 );
            break;
        }
        player.setQuestUI8BH( getId(), 1 );
        player.setQuestUI8BL( getId(), 1 );
        player.setQuestUI8CH( getId(), 1 );
        player.setQuestUI8CL( getId(), 1 );
        player.setQuestUI8DH( getId(), 1 );
        player.setQuestUI8DL( getId(), 0 );

        player.setQuestUI8EH( getId(), plan );

        player.setQuestUI8FH( getId(), 1 ); // see onSaveData() for detail
        player.setQuestUI8FL( getId(), 1 ); // see onSaveData() for detail
        
        player.eventFinish( getId(), 1 );
        player.enterPredefinedPrivateInstance( 393 );
      }
    };
    player.playScene( getId(), 65, NONE, callback );
  }

  void Scene00066( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00066: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 66, NONE, callback );
  }

  void Scene00067( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00067: Normal(SetWeddingFestivalParam), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      checkProgressSeq11( player );
    };
    player.playScene( getId(), 67, NONE, callback );
  }

  void Scene00068( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00068: Normal(Talk, TargetCanMove), id=CLARIBEL" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 68, NONE, callback );
  }

  void Scene00069( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00069: Normal(Talk, CutScene, FadeIn, TargetCanMove, SystemTalk), id=RAITMEAUX" );

    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 == 768 && ( result.param2 >= 664 && result.param2 <= 670 ) )
      {
        player.playSceneChain( getId(), 69, 4203520, 0, 1, result.param2, bindScene( &SubCts999::Scene00069 ) );
      }
    };
    bool hideWelcomeDialog = true;
    auto pEvent = player.getEvent( getId() );
    if( pEvent )
    {
      hideWelcomeDialog = pEvent->getSceneChainCallback() != nullptr;
    }
    player.playScene( getId(), 69, HIDE_HOTBAR, 0, hideWelcomeDialog ? 1 : 0, 0, callback );
  }

  void Scene00070( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00070: Normal(Talk, YesNo, TargetCanMove, SystemTalk), id=ETOINELLE" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      //if( result.param1 > 0 && result.param2 == 1 )
      //{
      //}
      checkProgressSeq12( player );
    };
    player.playScene( getId(), 70, NONE, callback );
  }

  void Scene00071( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00071: Normal(Talk, YesNo, TargetCanMove), id=CEREMONYGUIDE01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param1 > 0 && result.param2 == 1 )
      {
        player.eventFinish( getId(), 1 );
        player.enterPredefinedPrivateInstance( 393 );
      }
    };
    player.playScene( getId(), 71, HIDE_HOTBAR, callback );
  }

  void Scene00072( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00072: Normal(Talk, TargetCanMove, SystemTalk), id=CEREMONYSHOP01578" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
    };
    player.playScene( getId(), 72, NONE, callback );
  }

  void Scene00073( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00073: Normal(FadeIn, SetWeddingFestivalParam), id=unknown" );
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      //checkProgressSeq12( player );
    };
    player.playScene( getId(), 73, HIDE_HOTBAR, callback );
  }

  void Scene00074( Entity::Player& player )
  {
    player.sendDebug( "SubCts999:67114 calling Scene00074: Normal(Talk, QuestReward, QuestComplete, TargetCanMove, SystemTalk), id=CLARIBEL" );
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
    player.playScene( getId(), 74, NONE, callback );
  }
};

EXPOSE_SCRIPT( SubCts999 );
