// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: JobWhm450_01082
// Quest Name: Following in His Footsteps
// Quest ID: 66618
// Start NPC: 1006751
// End NPC: 1006751

using namespace Sapphire;

class JobWhm450 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH
  // UI8CL
  // UI8DH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002396
  /// Countable Num: 0 Seq: 1 Event: 2 Listener: 2002396
  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002397
  /// Countable Num: 0 Seq: 2 Event: 2 Listener: 2002397
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 2002398
  /// Countable Num: 0 Seq: 4 Event: 2 Listener: 2002398
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1006751
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2002399
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
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006751;  //Raya-o-Senna
  static constexpr auto Eobject0 = 2002396;//Epitaph to Philosophy
  static constexpr auto Eobject1 = 2002397;//Epitaph to Discovery
  static constexpr auto Eobject2 = 2002398;//Epitaph to Fluidity
  static constexpr auto Eobject3 = 2002399;//Epitaph to Infancy
  static constexpr auto Eobject4 = 2002401;
  static constexpr auto Eobject5 = 2002402;
  static constexpr auto Eobject6 = 2002400;//Epitaph to Expiry
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000939;
  static constexpr auto Item1 = 2000940;
  static constexpr auto Item2 = 2000941;
  static constexpr auto Item3 = 2000943;
  static constexpr auto Item4 = 2000942;
  static constexpr auto LocAction0Wsget = 995;
  static constexpr auto LocActor1 = 1007861;
  static constexpr auto LocActor2 = 1007862;
  static constexpr auto LocFace0 = 604;
  static constexpr auto LocFace1 = 617;
  static constexpr auto LocLogMes = 3652;
  static constexpr auto LocPosActor1 = 4307833;
  static constexpr auto LocPosActor2 = 4307834;
  static constexpr auto LocVfx1 = 241;
  static constexpr auto LocVfx2 = 413;
  static constexpr auto LocWs = 184;
  static constexpr auto Logmessage0 = 3657;
  static constexpr auto Ritem0 = 3687;
  static constexpr auto Ritem1 = 3894;
  static constexpr auto Ritem2 = 3463;
  static constexpr auto Ritem3 = 2902;
  static constexpr auto Ritem0Icon = 48242;
  static constexpr auto Ritem1Icon = 48219;
  static constexpr auto Ritem2Icon = 45189;
  static constexpr auto Ritem3Icon = 40616;
  static constexpr auto VfxReaction = 177;

public:
  JobWhm450() : Sapphire::ScriptAPI::QuestScript( 66618 ){};
  ~JobWhm450() = default;

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
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00014( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00022( quest, player );
        break;
      }
      case Eobject0:
      {
        Scene00002( quest, player );
        break;
      }
      case Eobject1:
      {
        Scene00004( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00006( quest, player );
        break;
      }
      case Eobject3:
      {
        Scene00009( quest, player );
        break;
      }
      case Eobject6:
      {
        Scene00020( quest, player );
        break;
      }
    }
  }

  void onEmote( World::Quest& quest, uint64_t actorId, uint32_t emoteId, Entity::Player& player ) override
  {
    if( emoteId == 58 )
    {
      if( actorId == Eobject0 )
        Scene00003( quest, player );
      else if( actorId == Eobject1 )
        Scene00005( quest, player );
      else if( actorId == Eobject2 )
        Scene00007( quest, player );
      else if( actorId == Eobject6 )
        Scene00021( quest, player );
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() >= 1 && quest.getUI8BH() >= 1 && quest.getUI8BL() >= 1 )
    {
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 );
      quest.setUI8CH( 0 );
      quest.setUI8CL( 0 );
      quest.setUI8DH( 0 );
      quest.setSeq( Seq2 );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &JobWhm450::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &JobWhm450::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 );
    quest.setUI8CL( 1 );
    quest.setUI8DH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 0, { Ritem0Icon } );
    playerMgr().sendLogMessage( player, Logmessage0 );
    quest.setUI8AL( 1 );
    quest.setUI8CH( 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 1, { Ritem2Icon } );
    playerMgr().sendLogMessage( player, Logmessage0 );
    quest.setUI8BH( 1 );
    quest.setUI8CL( 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 2, {Ritem1Icon} );
    playerMgr().sendLogMessage( player, Logmessage0 );
    quest.setUI8BL( 1 );
    quest.setUI8DH( 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &JobWhm450::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq3 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &JobWhm450::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &JobWhm450::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &JobWhm450::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &JobWhm450::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00015( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &JobWhm450::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( Seq5 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &JobWhm450::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &JobWhm450::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &JobWhm450::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &JobWhm450::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &JobWhm450::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 6, { Ritem3Icon } );
    playerMgr().sendLogMessage( player, Logmessage0 );
    quest.setSeq( SeqFinish );
    quest.setUI8BH( 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &JobWhm450::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &JobWhm450::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( JobWhm450 );