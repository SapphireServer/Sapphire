// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsHrv600_02052
// Quest Name: 連載最終回「種は国境を越えて」
// Quest ID: 67588
// Start NPC: 1013240
// End NPC: 1000815

using namespace Sapphire;

class ClsHrv600 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1013241
  /// Countable Num: 1 Seq: 2 Event: 1 Listener: 1013246
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1013247
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1013240
  /// Countable Num: 1 Seq: 5 Event: 1 Listener: 1000815
  /// Countable Num: 1 Seq: 6 Event: 1 Listener: 1013241
  /// Countable Num: 1 Seq: 7 Event: 1 Listener: 1013246
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1013247
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
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1013240;//Mujih Mewrilah
  static constexpr auto Actor1 = 1013241;//Basyle
  static constexpr auto Actor2 = 1013246;//Aubierault
  static constexpr auto Actor3 = 1013247;//Vainctoroix
  static constexpr auto Actor4 = 1000815;//Fufucha
  static constexpr auto Actor5 = 1013245;//Martineau
  static constexpr auto BindActor0 = 5888239;
  static constexpr auto BindActor1 = 5888241;
  static constexpr auto EventBaseFrightened = 983;
  static constexpr auto EventLink = 1002;
  static constexpr auto Item0 = 2001665;
  static constexpr auto Item1 = 2001666;
  static constexpr auto LocIdle0 = 996;
  static constexpr auto Ncut01 = 955;
  static constexpr auto Ritem0 = 12900;
  static constexpr auto SeIdEventLinkshellGc = 42;

public:
  ClsHrv600() : Sapphire::ScriptAPI::QuestScript( 67588 ){};
  ~ClsHrv600() = default;

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
        else if( quest.getSeq() == Seq1 )
          Scene00005( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00028( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00031( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00007( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00013( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00016( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00021( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00027( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00029( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00014( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00018( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00024( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00009( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00015( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00019( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00025( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq2 )
          Scene00006( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00012( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00030( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq3 )
          Scene00010( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00020( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00026( quest, player );
        break;
      }
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsHrv600::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsHrv600::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
    quest.setUI8BL( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00017( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
    player.collectHandInItems( { Ritem0 } );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00022( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00023( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsHrv600::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( Seq6 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( Seq7 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsHrv600::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 6, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, HIDE_HOTBAR, bindSceneReturn( &ClsHrv600::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( ClsHrv600 );