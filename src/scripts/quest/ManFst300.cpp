// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManFst300_00511
// Quest Name: A Hero in the Making
// Quest ID: 66047
// Start NPC: 1005116
// End NPC: 1005122

using namespace Sapphire;

class ManFst300 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag24
  // BitFlag8
  // UI8AL //Limsa
  // UI8BH //Gridania
  // UI8BL //Ul'dah

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1003785
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1004883
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1004884
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1004885
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2001690
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1005116;//Minfilia
  static constexpr auto Actor1 = 1003785;//Tataru
  static constexpr auto Actor2 = 1004883;//Flame Officer
  static constexpr auto Actor3 = 1004884;//Serpent Officer
  static constexpr auto Actor4 = 1004885;//Storm Officer
  static constexpr auto Actor5 = 1001029;//Zanthael <Storm Sergeant>
  static constexpr auto Actor6 = 1004870;
  static constexpr auto Actor7 = 1004871;
  static constexpr auto Actor8 = 1004872;
  static constexpr auto Actor9 = 1004874;
  static constexpr auto Actor10 = 1004875;
  static constexpr auto Actor11 = 1004876;
  static constexpr auto Actor12 = 1006179;
  static constexpr auto Actor13 = 1004880;
  static constexpr auto Actor14 = 1004881;
  static constexpr auto Actor15 = 1004882;
  static constexpr auto Actor16 = 1006173;
  static constexpr auto Actor17 = 1006174;
  static constexpr auto Actor18 = 1006175;
  static constexpr auto Actor19 = 1006181;
  static constexpr auto Actor20 = 1006183;
  static constexpr auto Actor21 = 1006184;
  static constexpr auto Actor22 = 1006177;
  static constexpr auto Actor23 = 1006178;
  static constexpr auto Actor24 = 1005122;//Minfilia
  static constexpr auto Eobject0 = 2001690;//Destination (Griadnia)
  static constexpr auto Eobject1 = 2001691;//Destination (Ul'dah)
  static constexpr auto EventActionWaiting = 10;
  static constexpr auto LocAction1 = 1002;
  static constexpr auto LocActor0 = 1003783;
  static constexpr auto LocSe1 = 42;
  static constexpr auto LocTalkshape1 = 6;
  static constexpr auto Ncut0 = 89;
  static constexpr auto Ncut1 = 90;
  static constexpr auto Ncut2 = 151;
  static constexpr auto Ncut3 = 91;
  static constexpr auto Ncut4 = 152;
  static constexpr auto Ncut5 = 92;
  static constexpr auto Ncut6 = 153;
  static constexpr auto Ncut7 = 93;

public:
  ManFst300() : Sapphire::ScriptAPI::QuestScript( 66047 ){};
  ~ManFst300() = default;

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
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00030( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00035( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00031( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00036( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq1 )
          Scene00005( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00032( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00037( quest, player );
        break;
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq2 )
          Scene00010( quest, player );
        break;
      }
      case Actor6:
      {
        break;
      }
      case Actor7:
      {
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
        break;
      }
      case Actor10:
      {
        break;
      }
      case Actor11:
      {
        break;
      }
      case Actor12:
      {
        break;
      }
      case Actor13:
      {
        break;
      }
      case Actor14:
      {
        break;
      }
      case Actor15:
      {
        break;
      }
      case Actor16:
      {
        break;
      }
      case Actor17:
      {
        break;
      }
      case Actor18:
      {
        break;
      }
      case Actor19:
      {
        break;
      }
      case Actor20:
      {
        break;
      }
      case Actor21:
      {
        break;
      }
      case Actor22:
      {
        break;
      }
      case Actor23:
      {
        break;
      }
      case Actor24:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00033( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionWaiting,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00007( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionWaiting,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00009( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() >= 1 && quest.getUI8BH() >= 1 && quest.getUI8BL() >= 1 )
    {
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ManFst300::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst300::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    //TODO:Doesn't fade back in? Is it waiting for warp? I don't think so.
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &ManFst300::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ManFst300::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ManFst300::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ManFst300::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ManFst300::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst300::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setBitFlag24( 1, true );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ManFst300::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst300::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    quest.setBitFlag24( 2, true );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ManFst300::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst300::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ManFst300::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ManFst300::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &ManFst300::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ManFst300::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ManFst300::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &ManFst300::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &ManFst300::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ManFst300::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ManFst300::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ManFst300::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ManFst300::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &ManFst300::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &ManFst300::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &ManFst300::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &ManFst300::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, NONE, bindSceneReturn( &ManFst300::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &ManFst300::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &ManFst300::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, NONE, bindSceneReturn( &ManFst300::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &ManFst300::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, NONE, bindSceneReturn( &ManFst300::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &ManFst300::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst300::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, NONE, bindSceneReturn( &ManFst300::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, NONE, bindSceneReturn( &ManFst300::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, NONE, bindSceneReturn( &ManFst300::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( ManFst300 );