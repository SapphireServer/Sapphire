// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"
#include "Inventory/Item.h"

// Quest Script: JobWhm001_01124
// Quest Name: A Relic Reborn (Thyrus)
// Quest ID: 66660
// Start NPC: 1003075a
// End NPC: 1003075

using namespace Sapphire;

class JobWhm001 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002496
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 5010000
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 6 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 7 Event: 1 Listener: 1001304
  /// Countable Num: 0 Seq: 8 Event: 1 Listener: 5010000
  /// Countable Num: 0 Seq: 9 Event: 1 Listener: 1001304
  /// Countable Num: 0 Seq: 10 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 10 Event: 5 Listener: 756
  /// Countable Num: 0 Seq: 10 Event: 5 Listener: 758
  /// Countable Num: 0 Seq: 11 Event: 5 Listener: 757
  /// Countable Num: 0 Seq: 12 Event: 1 Listener: 1008161
  /// Countable Num: 0 Seq: 13 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 14 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 15 Event: 1 Listener: 5010000
  /// Countable Num: 0 Seq: 16 Event: 1 Listener: 1008161
  /// Countable Num: 0 Seq: 17 Event: 1 Listener: 1003075
  /// Countable Num: 0 Seq: 18 Event: 1 Listener: 1004582
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1003075
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    Seq5 = 5,
    Seq6 = 6,
    Seq7 = 7,
    Seq8 = 8,
    Seq9 = 9,
    Seq10 = 10,
    Seq11 = 11,
    Seq12 = 12,
    Seq13 = 13,
    Seq14 = 14,
    Seq15 = 15,
    Seq16 = 16,
    Seq17 = 17,
    Seq18 = 18,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003075;//Gerolt
  static constexpr auto Actor1 = 5010000;//Portley Moogle?
  static constexpr auto Actor2 = 1001304;//Rowena
  static constexpr auto Actor3 = 1008161;
  static constexpr auto Actor4 = 1004582;  //Fafajoni <<Flame Private>>
  static constexpr auto Enemy0 = 756;      //U'Ghamoro Quarryman
  static constexpr auto Enemy1 = 758;      //U'Ghamoro Priest
  static constexpr auto Enemy2 = 757;      //U'Ghamoro Bedesman
  static constexpr auto Eobject0 = 2002496;//Treasure Coffer
  static constexpr auto EventActionProcessMiddle = 16;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Instancedungeon0 = 20019;//Assumed to be A Relic Reborn: Chimera
  static constexpr auto Instancedungeon1 = 14;
  static constexpr auto Instancedungeon2 = 20020;
  static constexpr auto Instancedungeon3 = 20004;
  static constexpr auto Instancedungeon4 = 20006;
  static constexpr auto Instancedungeon5 = 20005;
  static constexpr auto Item0 = 2000993;
  static constexpr auto Item1 = 2001002;
  static constexpr auto Item2 = 2001011;
  static constexpr auto Item3 = 2001020;
  static constexpr auto Item4 = 2001029;
  static constexpr auto Item5 = 2001038;
  static constexpr auto Item6 = 2001047;
  static constexpr auto Item0Icon = 21003;
  static constexpr auto Item3Icon = 26002;
  static constexpr auto LocAction0 = 858;
  static constexpr auto LocAction1 = 995;
  static constexpr auto LocAction2 = 936;
  static constexpr auto LocItem1 = 2052;
  static constexpr auto LocPosActor0 = 4311940;
  static constexpr auto Ritem0 = 2049;//Madman's Whispering Rod
  static constexpr auto Ritem1 = 2046;//Unfinished Thyrus
  static constexpr auto Ritem2 = 6267;//Radz-at-Han Quenching Oil
  static constexpr auto Ritem1Icon = 32627;

public:
  JobWhm001() : Sapphire::ScriptAPI::QuestScript( 66660 ){};
  ~JobWhm001() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00004( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00006( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00009( quest, player );
        else if( quest.getSeq() == Seq9 )
          Scene00014( quest, player );
        else if( quest.getSeq() == Seq10 )
          Scene00017( quest, player );
        else if( quest.getSeq() == Seq11 )
          Scene00018( quest, player );
        else if( quest.getSeq() == Seq12 )
          Scene00020( quest, player );
        else if( quest.getSeq() == Seq13 )
          Scene00022( quest, player );
        else if( quest.getSeq() == Seq14 )
          Scene00023( quest, player );
        else if( quest.getSeq() == Seq15 )
          Scene00026( quest, player );
        else if( quest.getSeq() == Seq16 )
          Scene00027( quest, player );
        else if( quest.getSeq() == Seq17 )
          Scene00028( quest, player );
        else if( quest.getSeq() == Seq18 )
          Scene00029( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00031( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq10 )
          Scene00016( quest, player );
        else if( quest.getSeq() == Seq11 )
          Scene00019( quest, player );
        else if( quest.getSeq() == Seq14 )
          Scene00025( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq6 )
          Scene00011( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00012( quest, player );
        break;
      }
      case Actor3:
      {
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq12 )
          Scene00021( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionProcessMiddle,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00002( quest, player );
                },
                nullptr, 0 );
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    if( player.getEquippedWeapon()->getId() != Ritem1 ) return;
    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      {
        if( quest.getUI8AL() < 8 )
        {
          quest.setUI8AL( quest.getUI8AL() + 1 );
          eventMgr().sendEventNotice( player, getId(), 9, 2, quest.getUI8AL(), 8 );
          checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy1:
      {
        if( quest.getUI8BH() < 8 )
        {
          quest.setUI8BH( quest.getUI8BH() + 1 );
          eventMgr().sendEventNotice( player, getId(), 10, 2, quest.getUI8BH(), 8 );
          checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy2:
      {
        if( quest.getUI8BL() < 8 )
        {
          quest.setUI8BL( quest.getUI8BL() + 1 );
          eventMgr().sendEventNotice( player, getId(), 11, 2, quest.getUI8BL(), 8 );
          checkQuestCompletion( quest, player );
        }
        break;
      }
    }
  }

  //TODO:Placeholder, not really a func
  void onDungeonComplete( World::Quest& quest, Sapphire::Entity::Player& player, int dungeon )
  {
    if( quest.getSeq() == Seq4 && dungeon == Instancedungeon0 )//A Relic Reborn: Chimera
    {
      quest.setUI8BH( 1 );
      eventMgr().sendEventNotice( player, getId(), 3, 0 );
      quest.setSeq( Seq5 );
    }
    else if( quest.getSeq() == Seq7 && dungeon == Instancedungeon1 )//Amdapor Keep
    {
      quest.setUI8BH( 1 );
      eventMgr().sendEventNotice( player, getId(), 6, 0 );
      quest.setSeq( Seq8 );
    }
    else if( quest.getSeq() == Seq12 && dungeon == Instancedungeon2 )//A Relic Reborn: Hydra
    {
      eventMgr().sendEventNotice( player, getId(), 13, 0 );
      quest.setSeq( Seq13 );
    }
    else if( quest.getSeq() == Seq15 && dungeon == Instancedungeon3 )//Bowl of Embers (Hard)
    {
      quest.setUI8BH( 1 );
      eventMgr().sendEventNotice( player, getId(), 16, 0 );
      quest.setSeq( Seq16 );
    }
    else if( quest.getSeq() == Seq16 && dungeon == Instancedungeon4 )//Howling Eye (Hard)
    {
      quest.setUI8BL( 1 );
      eventMgr().sendEventNotice( player, getId(), 17, 0 );
      quest.setSeq( Seq17 );
    }
    else if( quest.getSeq() == Seq17 && dungeon == Instancedungeon5 )//Navel (Hard)
    {
      quest.setUI8CH( 1 );
      eventMgr().sendEventNotice( player, getId(), 18, 0 );
      quest.setSeq( Seq18 );
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getSeq() == Seq10 )
    {
      if( quest.getUI8AL() >= 8 && quest.getUI8BH() >= 8 && quest.getUI8BL() >= 8 )
      {
        quest.setUI8AL( 0 );
        quest.setUI8BH( 0 );
        quest.setUI8BL( 0 );
        quest.setSeq( Seq11 );
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &JobWhm001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &JobWhm001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &JobWhm001::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendNotice( player, getId(), 0, { Item0Icon } );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &JobWhm001::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &JobWhm001::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00005( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &JobWhm001::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 0 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &JobWhm001::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &JobWhm001::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: Unlock "A Relic Reborn: The Chimera"
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &JobWhm001::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &JobWhm001::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00010( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &JobWhm001::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 0 );
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( Seq6 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &JobWhm001::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( Seq7 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &JobWhm001::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00013( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &JobWhm001::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 7, { Item3Icon } );
    quest.setSeq( Seq9 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &JobWhm001::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00015( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &JobWhm001::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 0 );
    eventMgr().sendNotice( player, getId(), 8, { Ritem1Icon } );
    player.addItem( Ritem1 );
    quest.setSeq( Seq10 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &JobWhm001::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    player.addItem( Ritem1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &JobWhm001::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &JobWhm001::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 12, 0 );
    quest.setSeq( Seq12 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &JobWhm001::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    player.addItem( Ritem1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &JobWhm001::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &JobWhm001::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &JobWhm001::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 14, 0 );
    quest.setSeq( Seq14 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &JobWhm001::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00024( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &JobWhm001::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( player.collectHandInItems( { Ritem1 } ) )
    {
      eventMgr().sendEventNotice( player, getId(), 15, 0 );
      quest.setSeq( Seq15 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &JobWhm001::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    player.addItem( Ritem1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &JobWhm001::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, NONE, bindSceneReturn( &JobWhm001::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &JobWhm001::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &JobWhm001::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00030( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, NONE, bindSceneReturn( &JobWhm001::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 0 );
    quest.setUI8BL( 0 );
    quest.setUI8CH( 0 );
    eventMgr().sendEventNotice( player, getId(), 19, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &JobWhm001::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00032( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &JobWhm001::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      if( player.collectHandInItems( { Ritem2 } ) )
        player.finishQuest( getId() ); //TODO: Achievement
    }
  }
};

EXPOSE_SCRIPT( JobWhm001 );