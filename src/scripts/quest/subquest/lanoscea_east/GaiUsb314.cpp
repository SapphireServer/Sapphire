// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsb314_00855
// Quest Name: In the Company of Heroes
// Quest ID: 66391
// Start NPC: 1006676
// End NPC: 1006676

using namespace Sapphire;

class GaiUsb314 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag16
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH
  // UI8CL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1006314
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1006313
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1006315
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006316
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006676;//Y'shtola
  static constexpr auto Actor1 = 1006314;//Bronze-skinned Beauty
  static constexpr auto Actor2 = 1006313;
  static constexpr auto Actor3 = 1006315;
  static constexpr auto Actor4 = 1006316;//U'odh Nunh
  static constexpr auto Actor5 = 1006317;//Landenel
  static constexpr auto Actor6 = 1006318;//Brayflox Alltalks
  static constexpr auto Actor7 = 1006319;//Shamani Lohmani
  static constexpr auto Actor8 = 1006266;//Wheiskaet
  static constexpr auto BgmLvup = 23;
  static constexpr auto CutScene01 = 369;
  static constexpr auto Eobject0 = 2002075;
  static constexpr auto Eobject1 = 2002076;
  static constexpr auto Eobject2 = 2002077;
  static constexpr auto Eobject3 = 2002078;
  static constexpr auto Eobject4 = 2002079;
  static constexpr auto Eobject5 = 2002080;
  static constexpr auto Eobject6 = 2002081;
  static constexpr auto Eobject7 = 2002082;
  static constexpr auto Eobject8 = 2002598;//Exotic Feast (Seq2)
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocAction0 = 788;
  static constexpr auto LocAction1 = 1016;
  static constexpr auto LocAction2 = 683;
  static constexpr auto LocActor1 = 1006272;
  static constexpr auto LocEobj1 = 2002687;
  static constexpr auto LocPosActor0 = 4374246;
  static constexpr auto LocPosActor1 = 4258358;
  static constexpr auto LocPosCam1 = 4374251;
  static constexpr auto LocPosEobj1 = 4373897;

public:
  GaiUsb314() : Sapphire::ScriptAPI::QuestScript( 66391 ){};
  ~GaiUsb314() = default;

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
        else if( quest.getSeq() == SeqFinish )
          Scene00075( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00029( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00063( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00077( quest, player );
        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq1 )
          Scene00006( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00031( quest, player );
        else if( quest.getSeq() == Seq3 )
        {
          if( quest.getUI8BL() < 1 )
            Scene00055( quest, player );
          else
            Scene00056( quest, player );
        }
        else if( quest.getSeq() == SeqFinish )
          Scene00079( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq1 )
          Scene00007( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00032( quest, player );
        else if( quest.getSeq() == Seq3 )
        {
          if( quest.getUI8BH() < 1 )
            Scene00053( quest, player );
          else
            Scene00054( quest, player );
        }
        else if( quest.getSeq() == SeqFinish )
          Scene00080( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq1 )
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00033( quest, player );
        else if( quest.getSeq() == Seq3 )
        {
          if( quest.getUI8CH() < 1 )
            Scene00057( quest, player );
          else
            Scene00058( quest, player );
        }
        else if( quest.getSeq() == SeqFinish )
          Scene00081( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq1 )
          Scene00009( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00034( quest, player );
        else if( quest.getSeq() == Seq3 )
        {
          if( quest.getUI8CL() < 1 )
            Scene00059( quest, player );
          else
            Scene00061( quest, player );
        }
        else if( quest.getSeq() == SeqFinish )
          Scene00082( quest, player );
        break;
      }
      case Actor8:
      {
        if( quest.getSeq() == Seq3 )
          Scene00051( quest, player );
        break;
      }
      case Eobject8:
      {
        Scene00027( quest, player );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 2, quest.getUI8AH(), 5 );
    if( quest.getUI8AH() >= 5 )
    {
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsb314::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsb314::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00052( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 52, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00052Return ) );
  }

  void Scene00052Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00053( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 53, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00053Return ) );
  }

  void Scene00053Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00054( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 54, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00054Return ) );
  }

  void Scene00054Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00055( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 55, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00055Return ) );
  }

  void Scene00055Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00056( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 56, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00056Return ) );
  }

  void Scene00056Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00057( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 57, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00057Return ) );
  }

  void Scene00057Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00058( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 58, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00058Return ) );
  }

  void Scene00058Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00059( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 59, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00059Return ) );
  }

  void Scene00059Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CL( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00060( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 60, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00060Return ) );
  }

  void Scene00060Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00061( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 61, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00061Return ) );
  }

  void Scene00061Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00062( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 62, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00062Return ) );
  }

  void Scene00062Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00063( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 63, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00063Return ) );
  }

  void Scene00063Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00064( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 64, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00064Return ) );
  }

  void Scene00064Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00065( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 65, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00065Return ) );
  }

  void Scene00065Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00066( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 66, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00066Return ) );
  }

  void Scene00066Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00067( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 67, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00067Return ) );
  }

  void Scene00067Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00068( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 68, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00068Return ) );
  }

  void Scene00068Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00069( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 69, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00069Return ) );
  }

  void Scene00069Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00070( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 70, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00070Return ) );
  }

  void Scene00070Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00071( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 71, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00071Return ) );
  }

  void Scene00071Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00072( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 72, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00072Return ) );
  }

  void Scene00072Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00073( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 73, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00073Return ) );
  }

  void Scene00073Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00074( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 74, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00074Return ) );
  }

  void Scene00074Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00075( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 75, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsb314::Scene00075Return ) );
  }

  void Scene00075Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00076( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 76, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00076Return ) );
  }

  void Scene00076Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00077( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 77, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00077Return ) );
  }

  void Scene00077Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00078( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 78, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00078Return ) );
  }

  void Scene00078Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00079( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 79, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00079Return ) );
  }

  void Scene00079Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00080( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 80, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00080Return ) );
  }

  void Scene00080Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00081( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 81, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00081Return ) );
  }

  void Scene00081Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00082( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 82, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00082Return ) );
  }

  void Scene00082Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00083( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 83, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00083Return ) );
  }

  void Scene00083Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00084( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 84, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00084Return ) );
  }

  void Scene00084Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00085( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 85, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00085Return ) );
  }

  void Scene00085Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00086( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 86, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00086Return ) );
  }

  void Scene00086Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00087( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 87, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00087Return ) );
  }

  void Scene00087Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00088( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 88, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00088Return ) );
  }

  void Scene00088Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00089( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 89, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00089Return ) );
  }

  void Scene00089Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00091( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 91, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00091Return ) );
  }

  void Scene00091Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00092( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 92, HIDE_HOTBAR, bindSceneReturn( &GaiUsb314::Scene00092Return ) );
  }

  void Scene00092Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( GaiUsb314 );